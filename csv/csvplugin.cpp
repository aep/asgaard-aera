#include "../plugin.h"

#include <QByteArray>
#include <QFile>

#define ACSV_T(item, _item) Object *item = _item ? reinterpret_cast<Object*> (const_cast<void*>(_item)) : 0;

namespace csv
{

class AERA_PLUGIN_LOCAL Object
{
public:
    Object()
    {}
    virtual ~Object() {}

    virtual aera_type type() { return aera_null; };
    virtual bool array_next(aera_item *) { return false; };
    virtual bool array_end() { return true; }
    virtual aera_array_iterator array_iterate() { return 0; }
    virtual bool get_string(const char **) { return false; }

};

class AERA_PLUGIN_LOCAL Item : public Object
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

class AERA_PLUGIN_LOCAL ItemIterator : public Object
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

class AERA_PLUGIN_LOCAL Row : public Object
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

class AERA_PLUGIN_LOCAL RowIterator : public Object
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

class AERA_PLUGIN_LOCAL Table : public Object
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

static aera_type get_type (aera_item _item)
{
    ACSV_T(item, _item);
    if (!item)
        return aera_null;
    return item->type();
}
static bool get_string (aera_item _item, const char **v)
{
    ACSV_T(item, _item);
    if (!item)
        return aera_null;
    return item->get_string(v);
}
static void destroy(aera_item _item)
{
    ACSV_T(item, _item);
    delete item;
}
static aera_array_iterator array_iterate(aera_item _item)
{
    ACSV_T(item, _item);
    if (!item)
        return 0;
    return item->array_iterate();
}
static bool array_end(aera_array_iterator _it)
{
    ACSV_T(item, _it);
    if (!item)
        return true;
    return item->array_end();
}
static bool array_next(aera_array_iterator _it, aera_item *v)
{
    ACSV_T(item, _it);
    if (!item)
        return false;
    return item->array_next(v);
}
static bool is_null(aera_item item)
{
    return item;
}
static aera_type_interface types =
{
    csv::get_type,
    csv::is_null,
    0,
    0,
    0,
    csv::get_string,
    csv::destroy,
    csv::array_iterate,
    csv::array_end,
    csv::array_next,
    csv::destroy,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};

static aera_context read(int argc, char **argv)
{
    if (argc < 2)
        return 0;

    Table *c = new Table(argv[0], argv[1][0]);
    return reinterpret_cast<aera_item>(c);
}

static aera_item pull(aera_context c)
{
    return c;
}

static void close(aera_context)
{
    // nothing to do. we didn't allocate in root()
}

static aera_plugin_interface plugin =
{
    csv::read,
    csv::pull,
    0,
    0,
    csv::close
};

}

extern "C" {

AERA_PLUGIN_EXPORT int aera_version ()
{
    return 1;
}
AERA_PLUGIN_EXPORT aera_type_interface *aera_types()
{
    return &csv::types;
}

AERA_PLUGIN_EXPORT aera_plugin_interface *aera_plugin()
{
    return &csv::plugin;
}

}

