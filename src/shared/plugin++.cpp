namespace Aera
{

#define ACSV_T(item, _item) Object *item = _item ? reinterpret_cast<Object*> (const_cast<void*>(_item)) : 0;

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
        return false;
    return item->get_string(v);
}
static bool get_double (aera_item _item, double *v)
{
    ACSV_T(item, _item);
    if (!item)
        return false;
    return item->get_double(v);
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
static bool object_next(aera_object_iterator _it, const char **k, aera_item *v)
{
    ACSV_T(item, _it);
    if (!item)
        return false;
    return item->object_next(k, v);
}

static aera_attribute_iterator attribute_iterate(aera_item _item)
{
    ACSV_T(item, _item);
    if (!item)
        return 0;
    return item->attribute_iterate();
}
static bool attribute_end(aera_attribute_iterator _it)
{
    ACSV_T(item, _it);
    if (!item)
        return true;
    return item->attribute_end();
}
static bool attribute_next(aera_attribute_iterator _it, const char **k, aera_item *v)
{
    ACSV_T(item, _it);
    if (!item)
        return false;
    return item->attribute_next(k, v);
}
static bool is_null(aera_item item)
{
    return item;
}


static aera_type_interface types =
{
    Aera::get_type,
    Aera::is_null,
    0,
    0,
    Aera::get_double,
    Aera::get_string,
    Aera::destroy,

    Aera::array_iterate,
    Aera::array_end,
    Aera::array_next,
    Aera::destroy,

    Aera::object_iterate,
    Aera::object_end,
    Aera::object_next,
    Aera::destroy,

    Aera::attribute_iterate,
    Aera::attribute_end,
    Aera::attribute_next,
    Aera::destroy,
};

}


