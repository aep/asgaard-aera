#include "../../shared/plugin.h"
#include "rapidxml/rapidxml.hpp"


#include <fstream>
#include <vector>
#include <cstdio>

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

    virtual bool object_next(aera_item &, aera_item &) { return false; };
    virtual bool object_end() { return true; }
    virtual aera_object_iterator object_iterate() { return 0; }

    virtual bool get_string(const char *&) { return false; }

};


class DomName : public Object
{
public:
    DomName(rapidxml::xml_node<> * n)
        : Object()
        , node (n)
    {
    }
    rapidxml::xml_node<> *node;
    virtual aera_type type() { return aera_string; };
    virtual bool get_string(const char *& v)
    {
        if (!node)
            return false;
        v = node->name();
        return true;
    }
};

class DomNode : public Object
{
public:
    DomNode(rapidxml::xml_node<> * n)
        : Object()
        , node (n)
    {
    }
    rapidxml::xml_node<> *node;
    virtual aera_type type()
    {
        if (!node)
            return aera_null;
        switch(node->type()) {
            case rapidxml::node_document:
            case rapidxml::node_element: {
                // in xml, a text thing is it's own node
                // we really want that to appear as value of the parent
                // thus, we need to check if this element only has one
                // element, a text node, and skip the object iteration on it.
                // otherwise we end up in { 'element': { '' : 'actualtext' } }

                rapidxml::xml_node<> * n  = node->first_node();
                if (!n->next_sibling())
                    if (n->type() == rapidxml::node_data || n->type() == rapidxml::node_cdata)
                        return aera_string;


                return aera_object;
                break;
            }
            case rapidxml::node_data:
            case rapidxml::node_cdata:
                return aera_string;
                break;
            case rapidxml::node_comment:
            case rapidxml::node_declaration:
            case rapidxml::node_doctype:
            case rapidxml::node_pi:
            default:
                return aera_null;
                break;
        }
    }
    virtual aera_object_iterator object_iterate();
    virtual bool get_string(const char *& v)
    {
        if (!node)
            return false;
        v = node->value();
        return true;
    }

};

class DomIterator : public Object
{
public:
    DomIterator(rapidxml::xml_node<> * n)
        : Object()
        , node (n)
    {
    }
    rapidxml::xml_node<> *node;

    virtual bool object_end()
    {
        return !node;
    }

    virtual bool object_next(aera_item &k, aera_item &v)
    {
        if (!node)
            return false;

        k = new DomName(node);
        v = new DomNode(node);

        node = node->next_sibling();
        return true;
    };
};

aera_object_iterator DomNode::object_iterate()
{
    if (!node)
        return 0;
    if (!node->type() == rapidxml::node_element)
        return 0;
    return new DomIterator(node->first_node());
}


class Document : public Object
{
public:
    Document(int argc, char **argv)
        : Object()
    {
        if (argc < 1)
            return;

        // Read the xml file into a vector
        file.open(argv[0]);
        buffer = std::vector<char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        buffer.push_back('\0');
        doc.parse<0>(&buffer[0]);

    }
    std::ifstream file;
    rapidxml::xml_document<> doc;
    std::vector<char> buffer;

    virtual aera_type type() { return aera_object; };
    virtual aera_object_iterator object_iterate()
    {
        return  new DomIterator(doc.first_node());
    }
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
static aera_object_iterator object_iterate(aera_item _item)
{
    ACSV_T(item, _item);
    if (!item)
        return 0;
    return item->object_iterate();
}
static bool object_end(aera_object_iterator _it)
{
    ACSV_T(item, _it);
    if (!item)
        return true;
    return item->object_end();
}
static bool object_next(aera_object_iterator _it, aera_item &k, aera_item &v)
{
    ACSV_T(item, _it);
    if (!item)
        return false;
    return item->object_next(k, v);
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
    xml::destroy,
    xml::array_iterate,
    xml::array_end,
    xml::array_next,
    xml::destroy,
    xml::object_iterate,
    xml::object_end,
    xml::object_next,
    xml::destroy,
    0,
    0,
    0,
    0,
    0,xml
    0,xml
    0,xml
    0,xml
    0
};

static aera_context read(int argc, char **argv)
{
    if (argc < 1)
        return 0;

    Document *c = new Document(argc, argv);
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

AERA_PLUGIN_EXPORT int aera_version ()
{
    return 1;
}
AERA_PLUGIN_EXPORT aera_type_interface *aera_types()
{
    return &xml::types;
}

AERA_PLUGIN_EXPORT aera_plugin_interface *aera_plugin()
{
    return &xml::plugin;
}

}

