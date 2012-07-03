#include "../plugin.h"
#include "rapidxml/rapidxml.hpp"

#include <fstream>
#include <vector>

#define ACSV_T(item, _item) Object *item = _item ? reinterpret_cast<Object*> (const_cast<void*>(_item)) : 0;

namespace xml
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

class Document : public Object
{
public:
    Document(int argc, char **argv)
        :Object()
    {
        if (argc < 1)
            return;

        // Read the xml file into a vector
        std::ifstream theFile (argv[0]);
        buffer = std::vector<char>((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
        buffer.push_back('\0');
        doc.parse<0>(&buffer[0]);
    }
    rapidxml::xml_document<> doc;
    std::vector<char> buffer;
};

static aera_type get_type (aera_item _item)
{
    ACSV_T(item, _item);
    if (!item)
        return aera_null;
    return item->type();
}
static bool get_string (aera_item _item, const char *&v)
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
static bool array_next(aera_array_iterator _it, aera_item &v)
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
    xml::get_type,
    xml::is_null,
    0,
    0,
    0,
    xml::get_string,
    xml::array_iterate,
    xml::array_end,
    xml::array_next,
    xml::destroy,
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
    xml::destroy
};

static aera_context read(int argc, char **argv)
{
    if (argc < 2)
        return 0;

    Table *c = new Table(argv[0], argv[1][0]);
    return reinterpret_cast<aera_item>(c);
}

static aera_item root(aera_context c)
{
    return c;
}

static void close(aera_context)
{
    // nothing to do. we didn't allocate in root()
}

static aera_plugin_interface plugin =
{
    xml::read,
    xml::root,
    xml::close
};

}

extern "C" {

int aera_version ()
{
    return 1;
}
aera_type_interface *aera_types()
{
    return &xml::types;
}

aera_plugin_interface *aera_plugin()
{
    return &xml::plugin;
}

}

