#include "../plugin.h"


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct
{
    FILE *f;
} context;

void toJson(context *ctx, int indention, aera_type_interface *ad, aera_item item);


void toJsonArray(context *ctx, int indention, aera_type_interface *ad, aera_item item)
{
    fprintf(ctx->f, "[\n");
    ++indention;

    aera_array_iterator it = ad->array_iterate(item);
    if (!it) {
        fprintf(ctx->f, "]");
        return;
    }

    bool first = true;

    fprintf(ctx->f, "%*s", indention * 4, "");
    while (!ad->array_end(it)) {
        if (!first)
            fprintf(ctx->f, ",\n%*s", indention * 4, "");
        first = false;
        aera_item t;
        if (!ad->array_next(it, &t))
            break;
        toJson(ctx, indention, ad, t);
        ad->done(t);
    }
    ad->array_done(it);

    --indention;
    fprintf(ctx->f, "\n%*s]", indention * 4, "");
}

void toJsonObject(context *ctx, int indention, aera_type_interface*ad, aera_item item)
{
    fprintf(ctx->f, "{\n");
    ++indention;

    aera_object_iterator it = ad->object_iterate(item);
    if (!it) {
        fprintf(ctx->f, "}");
        return;
    }

    bool first = true;
    fprintf(ctx->f, "%*s", indention * 4, "");
    while (!ad->object_end(it)) {
        if (!first)
            fprintf(ctx->f, ",\n%*s", indention * 4, "");
        first = false;
        const char *k;
        aera_item v;
        if (!ad->object_next(it, &k, &v))
            break;
        fprintf(ctx->f, "%s : ", k);
        toJson(ctx, indention, ad, v);
        ad->done(v);
    }
    ad->array_done(it);

    --indention;
    fprintf(ctx->f, "\n%*s}", indention * 4, "");
}


void toJson(context *ctx, int indention, aera_type_interface *ad, aera_item item)
{
    aera_type t = ad->get_type(item);
    switch (t) {
        case aera_bool: {
            bool v;
            if (!ad->get_bool(item, &v))
                break;
            if (v)
                fprintf(ctx->f,"true");
            else
                fprintf(ctx->f,"false");
            break;
        } case aera_int: {
            int64_t v;
            if (!ad->get_int(item, &v))
                break;
                fprintf(ctx->f,"%lli", (long long int)v);
            break;
        } case aera_double: {
            double v;
            if (!ad->get_double(item, &v))
                break;
            fprintf(ctx->f,"%f", v);
            break;
        } case aera_string: {
            const char *v;
            if (!ad->get_string(item, &v))
                break;
            fprintf(ctx->f,"'%s'", v);
            break;
        } case aera_array:
            toJsonArray(ctx, indention, ad, item);
            break;
        case aera_object:
            toJsonObject(ctx, indention, ad, item);
            break;
        case aera_null:
        default:
            fprintf(ctx->f,"null");
            break;
    }
}

static aera_context write (int argc, char **argv)
{
    if (argc < 1)
        return 0;

    context *c = (context *)malloc(sizeof(context));

    if (strcmp(argv[0], "-") == 0) {
        c->f = stdout;
    } else {
        c->f = fopen(argv[0], "w");
        if (!c->f) {
            free(c);
            return 0;
        }
    }
    return c;
}

static bool push(aera_context c, aera_type_interface *tif, aera_item item)
{
    context *ctx = (context *)c;
    toJson(ctx, 0 , tif, item);
    fputc('\n', ctx->f);
    return true;
}

static void close(aera_context c)
{
    context *ctx = (context *)c;
    fclose(ctx->f);
    free(ctx);
}

static aera_plugin_interface plugin =
{
    0,
    0,
    write,
    push,
    close
};


AERA_PLUGIN_EXPORT int aera_version ()
{
    return 1;
}
AERA_PLUGIN_EXPORT aera_type_interface *aera_types()
{
    return 0;
}

AERA_PLUGIN_EXPORT aera_plugin_interface *aera_plugin()
{
    return &plugin;
}

