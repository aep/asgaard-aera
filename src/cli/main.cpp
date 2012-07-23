#include "../shared/plugin.h"
#include <QVariant>

#include <QCoreApplication>
#include <QStringList>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QLibrary>


struct StackItem
{
    QString fileName;
    aera_open_t    open;
    aera_pull_t    pull;
    aera_push_t    push;
    aera_close_t   close;;
    aera_context ctxi;
};

class AeraStack
{
public:
    QList<StackItem> stack;

    ~AeraStack()
    {
        //...
        // prev->type_interface->done(c);
        //from_plugin->close(from_ctx);
        // to_plugin->close(to_ctx);
    }

    void load(QString fileName, QStringList options)
    {
        StackItem item;
        item.fileName = fileName;
        QLibrary pluginLoader(fileName);

        if (!pluginLoader.load())
            qFatal("%s", qPrintable(pluginLoader.errorString ()));

        aera_version_t getVersion = reinterpret_cast<aera_version_t>(pluginLoader.resolve("aera_version"));
        if (!getVersion)
            qFatal("%s: missing aera_version", qPrintable(fileName));
        if (getVersion() != 1)
            qFatal("%s: strange version number", qPrintable(fileName));

        item.open  =  reinterpret_cast<aera_open_t>(pluginLoader.resolve("aera_open"));
        item.pull  =  reinterpret_cast<aera_pull_t>(pluginLoader.resolve("aera_pull"));
        item.push  =  reinterpret_cast<aera_push_t>(pluginLoader.resolve("aera_push"));
        item.close =  reinterpret_cast<aera_close_t>(pluginLoader.resolve("aera_close"));

        if (!item.open)
            qFatal("%s: missing symbol 'aera_open'", qPrintable(fileName));

        char ** argv = new char *[options.count()];
        for (int i = 0; i < options.count(); i++) {
            QByteArray l = options.at(i).toLocal8Bit();
            argv[i] = new char [l.size() + 1];
            strcpy(argv[i], l.data());
        }

        int e = item.open(options.count(), argv, &item.ctxi);

        if (e != AERA_E_SUCCESS)
            qFatal("%s: open failed: %s", qPrintable(fileName), aera_error_str[e]);
        for (int i = 0; i < options.count(); i++) {
            delete [] argv[i];
        }
        delete [] argv;

        stack.append(item);
    }


    void operator()()
    {
        // this is _non_ streaming
        // only because i designed the push/pull functions wrong
        // the actual iterators support streaming
        const StackItem *prev = 0;

        for (int i = 0; i < stack.count(); i++) {
            const StackItem *next = &stack.at(i);
            if (prev == 0) {
                prev = next;
                continue;
            }
            aera_item c;
            if (!prev->pull)
                qFatal("%s: can't pull: symbol 'aera_pull' is missing", qPrintable(prev->fileName));
            if (!next->push)
                qFatal("%s: can't push: symbol 'aera_push' is missing", qPrintable(next->fileName));

            int e = prev->pull(prev->ctxi, &c);
            if (e != AERA_E_SUCCESS)
                qFatal("%s: pull failed: %s", qPrintable(prev->fileName), aera_error_str[e]);
            e = next->push(next->ctxi, c);
            if (e != AERA_E_SUCCESS)
                qFatal("%s: push failed: %s", qPrintable(next->fileName), aera_error_str[e]);
            prev = next;
        }
    }
};



int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    QStringList args = app.arguments();
    args.takeFirst();

    AeraStack stack;


    for (int i = 0; i < args.count(); i++) {
        QString arg = args.at(i);
        if (arg.startsWith("-")) {
            qFatal("unknown argument %s", qPrintable(arg));
        } else {
            QStringList args = arg.split(' ', QString::SkipEmptyParts);
            QString fileName = args.takeFirst();
            stack.load(fileName,args);
        }
    }
    stack();
}
