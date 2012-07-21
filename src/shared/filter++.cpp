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

static void done(aera_item _item)
{
    FILTER_UNPACK(ctx, _item);
    if (!ctx)
        return;
    if (ctx->tif && ctx->filter)
        ctx->filter->done(ctx->tif, ctx->item);
    ctx->tif = 0;
    ctx->item = 0;
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
static void array_done(aera_item _item)
{
    FILTER_UNPACK(ctx, _item);
    if (!ctx)
        return;
    if (ctx->tif && ctx->filter)
        ctx->filter->array_done(ctx->tif, ctx->item);
    ctx->tif = 0;
    ctx->item = 0;
    delete ctx;
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
static void object_done(aera_item _item)
{
    FILTER_UNPACK(ctx, _item);
    if (!ctx)
        return;
    if (ctx->tif && ctx->filter)
        ctx->filter->object_done(ctx->tif, ctx->item);
    ctx->tif = 0;
    ctx->item = 0;
    delete ctx;
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
static void attribute_done(aera_item _item)
{
    FILTER_UNPACK(ctx, _item);
    if (!ctx)
        return;
    if (ctx->tif && ctx->filter)
        ctx->filter->attribute_done(ctx->tif, ctx->item);
    ctx->tif = 0;
    ctx->item = 0;
    delete ctx;
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
    AeraFilter::done,

    AeraFilter::array_iterate,
    AeraFilter::array_end,
    AeraFilter::array_next,
    AeraFilter::array_done,

    AeraFilter::object_iterate,
    AeraFilter::object_end,
    AeraFilter::object_next,
    AeraFilter::object_done,

    AeraFilter::attribute_iterate,
    AeraFilter::attribute_end,
    AeraFilter::attribute_next,
    AeraFilter::attribute_done,
};

aera_type Filter::type(aera_type_interface *tif, aera_item item)
{
    return tif->get_type(item);
}

aera_array_iterator Filter::array_iterate(aera_type_interface *tif, aera_item item)
{
    return tif->array_iterate(item);
}

bool Filter::array_next(aera_type_interface *tif, aera_item item, aera_item *v)
{
    return tif->array_next(item,v);
}

bool Filter::array_end(aera_type_interface *tif, aera_item item)
{
    return tif->array_end(item);
}

void Filter::array_done(aera_type_interface *tif, aera_item item)
{
    tif->array_done(item);
}

aera_object_iterator Filter::object_iterate(aera_type_interface *tif, aera_item item)
{
    return tif->object_iterate(item);
}

bool Filter::object_next(aera_type_interface *tif, aera_item item, const char **k, aera_item *v)
{
    return tif->object_next(item, k, v);
}

bool Filter::object_end(aera_type_interface *tif, aera_item item)
{
    return tif->object_end(item);
}

void Filter::object_done(aera_type_interface *tif, aera_item item)
{
    tif->object_done(item);
}

aera_attribute_iterator Filter::attribute_iterate(aera_type_interface *tif, aera_item item)
{
    return tif->attribute_iterate(item);
}

bool Filter::attribute_next(aera_type_interface *tif, aera_item item, const char **k, aera_item *v)
{
    return tif->attribute_next(item, k, v);
}

bool Filter::attribute_end(aera_type_interface *tif, aera_item item)
{
    return tif->attribute_end(item);
}

void Filter::attribute_done(aera_type_interface *tif, aera_item item)
{
    tif->attribute_done(item);
}

bool Filter::get_string(aera_type_interface *tif, aera_item item, const char **v)
{
    return tif->get_string(item, v);
}

bool Filter::get_double(aera_type_interface *tif, aera_item item, double *v)
{
    return tif->get_double(item, v);
}

void Filter::done(aera_type_interface *tif, aera_item item)
{
    tif->done(item);
}

};
