#include "plugin.h"
#include <QVariant>

#include <QFile>
#include <QDebug>

QVariantList  qlistFromAera(aera_adaption *ad, aera_item item);
QVariantMap   qmapFromAera(aera_adaption *ad, aera_item item);
QVariant qvariantFromAera(aera_adaption *ad, aera_item item)
{
    aera_type t = ad->get_type(item);
    switch (t) {
        case aera_bool: {
            bool v;
            if (!ad->get_bool(item, v))
                return QVariant();
            return v;
        } case aera_int: {
            int64_t v;
            if (!ad->get_int(item, v))
                return QVariant();
            return qint64(v);
        } case aera_double: {
            double v;
            if (!ad->get_double(item, v))
                return QVariant();
            return v;
        } case aera_string: {
            const char *v;
            if (!ad->get_string(item, v))
                return QVariant();
            return v;
        } case aera_array: {
            return qlistFromAera(ad, item);
        } case aera_object: {
            return qmapFromAera(ad, item);
        }
        case aera_null:
        default:
          return QVariant();
    }
}

QVariantList qlistFromAera(aera_adaption *ad, aera_item item)
{
    QVariantList l;

    aera_array_iterator it = ad->array_iterate(item);
    if (!it)
        return QVariantList();

    while (!ad->array_end(it)) {
        aera_item t;
        if (!ad->array_next(it, t))
            break;
        l.append(qvariantFromAera(ad, t));
    }
    ad->array_done(it);
    return l;
}

QVariantMap qmapFromAera(aera_adaption *ad, aera_item item)
{
    QVariantMap m;
    int64_t count;
    if (!ad->get_object_size(item, count))
        return QVariantMap();
    for (int64_t i = 0; i < count; i++) {
        aera_item k;
        aera_item v;
        if (!ad->get_object_key(item, k, i))
            return QVariantMap();
        if (!ad->get_object_value(item, v, i))
            return QVariantMap();
        m.insert(qvariantFromAera(ad, k).toString(), qvariantFromAera(ad, v));
    }
    return m;
}



#define ACSV_T(item, _item) Object *item = _item ? reinterpret_cast<Object*> (const_cast<void*>(_item)) : 0;


namespace  csv
{

class Object
{
public:
    Object()
    {}
    virtual ~Object() {}

    virtual aera_type type() { return aera_null; };
    virtual bool array_next(aera_item &) { return false; };
    virtual bool array_end() { return true; }
    virtual aera_array_iterator array_iterate() { return 0; }
    virtual bool get_string(const char *&) { return false; }

};

class Item : public Object
{
public:
    Item(QByteArray i)
        : Object()
        , item(i)
    {
    }
    QByteArray item;

    virtual aera_type type() { return aera_string; }
    virtual bool get_string(const char *&v)
    {
        if (item.isNull())
            return false;

        v = item.data();

        return true;
    }
};

class ItemIterator : public Object
{
public:
    ItemIterator(QList<QByteArray> l)
        : Object()
        , line(l)
    {
    }
    QList<QByteArray> line;
    virtual bool array_next(aera_item &v)
    {
        if (line.isEmpty())
            return false;

        v = new Item(line.takeFirst());
        return true;
    }
    virtual bool array_end()
    {
        return line.isEmpty();
    }

};

class Row : public Object
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

class RowIterator : public Object
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

    virtual bool array_next(aera_item &v)
    {
        if (f.atEnd())
            return false;
        QByteArray lb = f.readLine();
        if (lb.endsWith('\n') || lb.endsWith('\r'))
            lb.chop(1);
        if (lb.endsWith('\n') || lb.endsWith('\r'))
            lb.chop(1);
        v = new Row(lb.split(separator));
        return true;
    }
    virtual bool array_end()
    {
        return f.atEnd();
    }
};

class Table : public Object
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

aera_type get_type (aera_item _item)
{
    ACSV_T(item, _item);
    if (!item)
        return aera_null;
    return item->type();
}
bool get_string (aera_item _item, const char *&v)
{
    ACSV_T(item, _item);
    if (!item)
        return aera_null;
    return item->get_string(v);
}
void destroy(aera_item _item)
{
    ACSV_T(item, _item);
    delete item;
}
aera_array_iterator array_iterate(aera_item _item)
{
    ACSV_T(item, _item);
    if (!item)
        return 0;
    return item->array_iterate();
}
bool array_end(aera_array_iterator _it)
{
    ACSV_T(item, _it);
    if (!item)
        return true;
    return item->array_end();
}
bool array_next(aera_array_iterator _it, aera_item &v)
{
    ACSV_T(item, _it);
    if (!item)
        return false;
    return item->array_next(v);
}
bool is_null(aera_item item)
{
    return item;
}
aera_item read(int argc, char **argv)
{
    if (argc < 2)
        return 0;

    Table *c = new Table(argv[0], argv[1][0]);
    return reinterpret_cast<aera_item>(c);
}

aera_adaption reader_adaption =
{
    csv::get_type,
    csv::is_null,
    0,
    0,
    0,
    csv::get_string,
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
    0,
    0,
    0,
    0,
    0,
    0,
    csv::destroy
};

}

int main(int argc, char **argv)
{
    aera_item c = csv::read(argc - 1, argv + 1);
    qDebug() << qvariantFromAera(&csv::reader_adaption, c);
}
