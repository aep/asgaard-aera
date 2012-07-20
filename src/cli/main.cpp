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
    aera_type_interface *type_interface;
    aera_plugin_interface *plugin_interface;
    aera_context ctxi;
};

class AeraStack
{
public:
    QList<StackItem> stack;

    ~AeraStack()
    {
        //...
        //from_types->done(c);
        //from_plugin->close(from_ctx);
        // to_plugin->close(to_ctx);
    }

    void load(QString spec)
    {
        StackItem item;

        QStringList specl = spec.split(":");

        QLibrary pluginLoader(specl.takeFirst());

        if (!pluginLoader.load())
            qFatal("%s", qPrintable(pluginLoader.errorString ()));

        aera_version_t getVersion = reinterpret_cast<aera_version_t>(pluginLoader.resolve("aera_version"));
        if (!getVersion)
            qFatal("missing aera_version");
        if (getVersion() != 1)
            qFatal("strange version number");

        aera_plugin_t  getPlugin  = reinterpret_cast<aera_plugin_t>(pluginLoader.resolve("aera_plugin"));
        if (!getPlugin)
            qFatal("missing aera_plugin");
        aera_types_t  getTypes   = reinterpret_cast<aera_types_t>(pluginLoader.resolve("aera_types"));
        if (!getTypes)
            qFatal("missing aera_types");

        item.type_interface    = getTypes();
        item.plugin_interface  = getPlugin();

        char ** argv = new char *[specl.count()];
        for (int i = 0; i < specl.count(); i++) {
            QByteArray l = specl.at(i).toLocal8Bit();
            argv[i] = new char [l.size() + 1];
            strcpy(argv[i], l.data());
        }

        bool writeopen = !stack.isEmpty();

        if (writeopen) {
            item.ctxi = item.plugin_interface->write(specl.count(), argv);
        } else {
            item.ctxi = item.plugin_interface->read(specl.count(), argv);
        }
        for (int i = 0; i < specl.count(); i++) {
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
            if (prev== 0) {
                prev = next;
                continue;
            }

            aera_item c = prev->plugin_interface->pull(prev->ctxi);
            next->plugin_interface->push(next->ctxi, prev->type_interface, c);
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
            stack.load(arg);
        }
    }
    stack();
}
