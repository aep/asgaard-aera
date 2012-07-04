#include "plugin.h"
#include <QVariant>

#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QLibrary>


// ----------------------------------------------------------------------

QVariantList  qlistFromAera(aera_type_interface *ad, aera_item item);
QVariantMap   qmapFromAera(aera_type_interface *ad, aera_item item);
QVariant qvariantFromAera(aera_type_interface *ad, aera_item item)
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

QVariantList qlistFromAera(aera_type_interface *ad, aera_item item)
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
        ad->done(t);
    }
    ad->array_done(it);
    return l;
}

QVariantMap qmapFromAera(aera_type_interface *ad, aera_item item)
{
    QVariantMap m;
    return m;
}

// ----------------------------------------------------------------------


// ----------------------------------------------------------------------



void toJson(QTextStream &out, int indention, aera_type_interface *ad, aera_item item);


void toJsonArray(QTextStream &out, int indention, aera_type_interface*ad, aera_item item)
{
    out << "[\n";
    ++indention;

    aera_array_iterator it = ad->array_iterate(item);
    if (!it) {
        out << "]";
        return;
    }

    bool first = true;
    out << QString(indention * 4, ' ');
    while (!ad->array_end(it)) {
        if (!first)
            out << ",\n" << QString(indention * 4, ' ');
        first = false;
        aera_item t;
        if (!ad->array_next(it, t))
            break;
        toJson(out, indention, ad, t);
        ad->done(t);
    }
    ad->array_done(it);

    --indention;
    out << "\n" <<  QString(indention * 4, ' ');
    out << "]";
}

void toJsonObject(QTextStream &out, int indention, aera_type_interface*ad, aera_item item)
{
    out << "{\n";
    ++indention;

    aera_object_iterator it = ad->object_iterate(item);
    if (!it) {
        out << "}";
        return;
    }

    bool first = true;
    out << QString(indention * 4, ' ');
    while (!ad->object_end(it)) {
        if (!first)
            out << ",\n" << QString(indention * 4, ' ');
        first = false;
        aera_item k;
        aera_item v;
        if (!ad->object_next(it, k, v))
            break;
        toJson(out, indention, ad, k);
        out << " : ";
        toJson(out, indention, ad, v);
        ad->done(k);
        ad->done(v);
    }
    ad->array_done(it);

    --indention;
    out << "\n" <<  QString(indention * 4, ' ');
    out << "}";
}


void toJson(QTextStream &out, int indention, aera_type_interface *ad, aera_item item)
{
    aera_type t = ad->get_type(item);
    switch (t) {
        case aera_bool: {
            bool v;
            if (!ad->get_bool(item, v))
                break;
            out << v;
            break;
        } case aera_int: {
            int64_t v;
            if (!ad->get_int(item, v))
                break;
            out << qint64(v);
            break;
        } case aera_double: {
            double v;
            if (!ad->get_double(item, v))
                break;
            out << v;
            break;
        } case aera_string: {
            const char *v;
            if (!ad->get_string(item, v))
                break;
            out << "'" << v << "'";
            break;
        } case aera_array:
            toJsonArray(out, indention, ad, item);
            break;
        case aera_object:
            toJsonObject(out, indention, ad, item);
            break;
        case aera_null:
            out << "<null>";
            break;
        default:
            out << "<invalid>";
            break;
    }
}






int main(int argc, char **argv)
{
    if (argc < 2)
        qFatal("usage aera plugin.so [plugin args]");

    QLibrary pluginLoader(argv[1]);

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



    aera_type_interface *type_interface = getTypes();
    aera_plugin_interface *plugin       = getPlugin();

    aera_context ctx = plugin->read(argc - 2, argv + 2);
    aera_item c = plugin->root(ctx);

    QTextStream out(stdout);
    toJson(out, 0, type_interface, c);
}
