namespace AeraFilter
{

#define FILTER_UNPACK(box, _item) \
    Box *box = _item ? (reinterpret_cast<Box*> (const_cast<void*>(_item))) : 0; \

static aera_type get_type (aera_item _item)
{
    FILTER_UNPACK(ctx, _item);
    if (!ctx)
        return aera_null;
    if (!ctx->tif)
        return aera_null;
    if (!ctx->filter)
        return aera_null;
    return ctx->filter->type(ctx->tif, ctx->item);
}
static bool get_string (aera_item _item, const char **v)
{
    FILTER_UNPACK(ctx, _item);
    if (!ctx)
        return false;
    if (!ctx->tif)
        return false;
    if (!ctx->filter)
        return false;
    return ctx->filter->get_string(ctx->tif, ctx->item, v);
}
static bool get_double (aera_item _item, double *v)
{
    FILTER_UNPACK(ctx, _item);
    if (!ctx)
        return false;
    if (!ctx->tif)
        return false;
    if (!ctx->filter)
        return false;
    return ctx->filter->get_double(ctx->tif, ctx->item, v);
}

static void destroy(aera_item _item)
{
    FILTER_UNPACK(ctx, _item);
    if (!ctx)
        return;
    if (ctx->tif && ctx->filter)
        ctx->filter->destroy(ctx->tif, ctx->item);
    delete ctx;
}
static aera_array_iterator array_iterate(aera_item _item)
{
    FILTER_UNPACK(ctx, _item);
    if (!ctx)
        return 0;
    if (!ctx->tif)
        return 0;
    if (!ctx->filter)
        return 0;

    aera_array_iterator i = ctx->filter->array_iterate(ctx->tif, ctx->item);
    if (!i)
        return 0;
    Box *c = new Box(*ctx);
    c->item = i;
    return reinterpret_cast<aera_array_iterator>(c);
}
static bool array_end(aera_array_iterator _it)
{
    FILTER_UNPACK(ctx, _it);
    if (!ctx)
        return true;
    if (!ctx->tif)
        return true;
    if (!ctx->filter)
        return true;
    return ctx->filter->array_end(ctx->tif, ctx->item);
}
static bool array_next(aera_array_iterator _it, aera_item *v)
{
    FILTER_UNPACK(ctx, _it);
    if (!ctx)
        return false;
    if (!ctx->tif)
        return false;
    if (!ctx->filter)
        return false;

    aera_item vs;
    if (!ctx->filter->array_next(ctx->tif, ctx->item, &vs))
        return false;
    Box *c = new Box(*ctx);
    c->item = vs;
    *v = reinterpret_cast<aera_item>(c);
    return true;
}
static aera_object_iterator object_iterate(aera_item _item)
{
    FILTER_UNPACK(ctx, _item);
    if (!ctx)
        return 0;
    if (!ctx->tif)
        return 0;
    if (!ctx->filter)
        return 0;
    aera_object_iterator i = ctx->filter->object_iterate(ctx->tif, ctx->item);
    if (!i)
        return 0;
    Box *c = new Box(*ctx);
    c->item = i;
    return reinterpret_cast<aera_object_iterator>(c);
}
static bool object_end(aera_object_iterator _it)
{
    FILTER_UNPACK(ctx, _it);
    if (!ctx)
        return true;
    if (!ctx->tif)
        return true;
    if (!ctx->filter)
        return true;
    return ctx->filter->object_end(ctx->tif, ctx->item);
}
static bool object_next(aera_object_iterator _it, const char **k, aera_item *v)
{
    FILTER_UNPACK(ctx, _it);
    if (!ctx)
        return false;
    if (!ctx->tif)
        return false;
    if (!ctx->filter)
        return false;
    aera_item vs;
    if (!ctx->filter->object_next(ctx->tif, ctx->item, k, &vs))
        return false;
    Box *c = new Box(*ctx);
    c->item = vs;
    *v = reinterpret_cast<aera_item>(c);
    return true;
}

static aera_attribute_iterator attribute_iterate(aera_item _item)
{
    FILTER_UNPACK(ctx, _item);
    if (!ctx)
        return 0;
    if (!ctx->tif)
        return 0;
    if (!ctx->filter)
        return 0;
    aera_attribute_iterator i = ctx->filter->attribute_iterate(ctx->tif, ctx->item);
    if (!i)
        return 0;
    Box *c = new Box(*ctx);
    c->item = i;
    return reinterpret_cast<aera_attribute_iterator>(c);
}
static bool attribute_end(aera_attribute_iterator _it)
{
    FILTER_UNPACK(ctx, _it);
    if (!ctx)
        return true;
    if (!ctx->tif)
        return true;
    if (!ctx->filter)
        return true;
    return ctx->filter->attribute_end(ctx->tif, ctx->item);
}
static bool attribute_next(aera_attribute_iterator _it, const char **k, aera_item *v)
{
    FILTER_UNPACK(ctx, _it);
    if (!ctx)
        return false;
    if (!ctx->tif)
        return false;
    if (!ctx->filter)
        return false;
    aera_item vs;
    if (!ctx->filter->attribute_next(ctx->tif, ctx->item, k, &vs))
        return false;
    Box *c = new Box(*ctx);
    c->item = vs;
    *v = reinterpret_cast<aera_item>(c);
    return true;
}

static bool is_null(aera_item item)
{
    return item;
}

static aera_type_interface types =
{
    AeraFilter::get_type,
    AeraFilter::is_null,
    0,
    0,
    AeraFilter::get_double,
    AeraFilter::get_string,
    AeraFilter::destroy,

    AeraFilter::array_iterate,
    AeraFilter::array_end,
    AeraFilter::array_next,
    AeraFilter::destroy,

    AeraFilter::object_iterate,
    AeraFilter::object_end,
    AeraFilter::object_next,
    AeraFilter::destroy,

    AeraFilter::attribute_iterate,
    AeraFilter::attribute_end,
    AeraFilter::attribute_next,
    AeraFilter::destroy,
};


};
