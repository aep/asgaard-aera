#include "../../shared/plugin.h"
#include "../../shared/plugin++.hpp"

#include <QByteArray>
#include <QFile>

#define ACSV_T(item, _item) Object *item = _item ? reinterpret_cast<Object*> (const_cast<void*>(_item)) : 0;

namespace csv
{
class AERA_PLUGIN_LOCAL Item : public Aera::Object
{
public:
    Item(QByteArray i)
        : Object()
        , item(i)
    {
    }
    QByteArray item;

    virtual aera_type type() { return aera_string; }
    virtual bool get_string(const char **v)
    {
        if (item.isNull())
            return false;

        *v = item.data();

        return true;
    }
};

class AERA_PLUGIN_LOCAL ItemIterator : public Aera::Object
{
public:
    ItemIterator(QList<QByteArray> l)
        : Object()
        , line(l)
    {
    }
    QList<QByteArray> line;
    virtual bool array_next(aera_item *v)
    {
        if (line.isEmpty())
            return false;

        *v = new Item(line.takeFirst());
        return true;
    }
    virtual bool array_end()
    {
        return line.isEmpty();
    }

};

class AERA_PLUGIN_LOCAL Row : public Aera::Object
{
public:
    Row(QList<QByteArray> l)
        : Object()
        , line (l)
    {
    }
    QList<QByteArray> line;
    virtual aera_type type() { return aera_array; }
    virtual aera_array_iterator array_iterate()
    {
        return new ItemIterator(line);
    }
};

class AERA_PLUGIN_LOCAL RowIterator : public Aera::Object
{
public:
    RowIterator(const QByteArray &fileName, char t)
        : Object()
        , separator(t)
    {
        f.setFileName(fileName);
        f.open(QFile::ReadOnly);
    }
    QFile f;
    char separator;

    virtual bool array_next(aera_item *v)
    {
        if (f.atEnd())
            return false;
        QByteArray lb = f.readLine();
        if (lb.endsWith('\n') || lb.endsWith('\r'))
            lb.chop(1);
        if (lb.endsWith('\n') || lb.endsWith('\r'))
            lb.chop(1);
        *v = new Row(lb.split(separator));
        return true;
    }
    virtual bool array_end()
    {
        return f.atEnd();
    }
};

class AERA_PLUGIN_LOCAL Table : public Aera::Object
{
public:
    Table(QByteArray f, char sep)
        : Object()
        , fileName(f)
        , separator(sep)
    {}
    QByteArray fileName;
    char separator;


    virtual aera_type type() { return aera_array; }
    virtual aera_array_iterator array_iterate()
    {
        return new RowIterator(fileName, separator);
    }
};

// ---------------------------------------------------------------------

struct Context
{
    QByteArray fileName;
    char separator;
};

static aera_context open(int argc, char **argv)
{
    if (argc < 2)
        return 0;

    Context *c = new Context;
    c->fileName = argv[0];
    c->separator = argv[1][0];
    return reinterpret_cast<aera_item>(c);
}

static aera_item pull(aera_context _c)
{
    const Context *c = reinterpret_cast<const Context *>(_c);
    Table *t = new Table(c->fileName, c->separator);
    return t;
}

static void close(aera_context _c)
{
    const Context *c = reinterpret_cast<const Context *>(_c);
    delete c;
}

static aera_plugin_interface plugin =
{
    csv::open,
    csv::pull,
    0,
    csv::close
};

}

#include "../../shared/plugin++.cpp"
extern "C" {

AERA_PLUGIN_EXPORT int aera_version ()
{
    return 1;
}
AERA_PLUGIN_EXPORT aera_type_interface *aera_types()
{
    return &Aera::types;
}

AERA_PLUGIN_EXPORT aera_plugin_interface *aera_plugin()
{
    return &csv::plugin;
}

}

