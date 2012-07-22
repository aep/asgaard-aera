#include "../../shared/plugin.h"


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct
{
    FILE *f;
} context;

static void toJson(context *ctx, int indention, aera_item item);


static void toJsonArray(context *ctx, int indention, aera_item item)
{
    fprintf(ctx->f, "[\n");
    ++indention;

    aera_array it;
    if (item.type->get_array(item, &it) != AERA_E_SUCCESS) {
        fprintf(ctx->f, "]");
        return;
    }

    int first = 1;

    fprintf(ctx->f, "%*s", indention * 4, "");
    for (;;) {
        aera_item t;
        if (it.type->next(it, &t) != AERA_E_SUCCESS)
            break;
        if (!first)
            fprintf(ctx->f, ",\n%*s", indention * 4, "");
        first = 0;
        toJson(ctx, indention, t);
        t.type->done(t);
    }
    it.type->done(it);

    --indention;
    fprintf(ctx->f, "\n%*s]", indention * 4, "");
}

static void toJsonObject(context *ctx, int indention, aera_item item)
{
    fprintf(ctx->f, "{\n");
    ++indention;

    aera_object it;
    if (item.type->get_object(item, &it) != AERA_E_SUCCESS) {
        fprintf(ctx->f, "}");
        return;
    }

    int first = 1;
    fprintf(ctx->f, "%*s", indention * 4, "");
    for (;;) {
        const char *k;
        aera_item v;
        if (it.type->next(it, &k, &v) != AERA_E_SUCCESS)
            break;
        if (!first)
            fprintf(ctx->f, ",\n%*s", indention * 4, "");
        first = 0;
        fprintf(ctx->f, "%s : ", k);
        toJson(ctx, indention, v);
        v.type->done(v);
    }
    it.type->done(it);

    --indention;
    fprintf(ctx->f, "\n%*s}", indention * 4, "");
}


static void toJson(context *ctx, int indention, aera_item item)
{
    aera_type t = aera_null_t;
    item.type->get_type(item, &t);
    switch (t) {
        case aera_bool_t:
        case aera_int_t: {
            int64_t v;
            if (item.type->get_int(item, &v) != AERA_E_SUCCESS)
                break;
                fprintf(ctx->f,"%lli", (long long int)v);
            break;
        } case aera_double_t: {
            double v;
            if (item.type->get_double(item, &v) != AERA_E_SUCCESS)
                break;
            fprintf(ctx->f,"%f", v);
            break;
        } case aera_string_t: {
            const char *v;
            if (item.type->get_string(item, &v) != AERA_E_SUCCESS)
                break;
            fprintf(ctx->f,"\"%s\"", v);
            break;
        } case aera_array_t:
            toJsonArray(ctx, indention,item);
            break;
        case aera_object_t:
            toJsonObject(ctx, indention, item);
            break;
        case aera_null_t:
        default:
            fprintf(ctx->f,"null");
            break;
    }
}

AERA_PLUGIN_EXPORT int aera_open(int argc, char **argv, aera_context *ctx)
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
            return AERA_E_IO;
        }
    }

    ctx->data = c;
    return AERA_E_SUCCESS;
}

AERA_PLUGIN_EXPORT int aera_push(aera_context c, aera_item item)
{
    if (!c.data)
        return AERA_E_BAD_CONTEXT;
    if (!item.data && !item.type)
        return AERA_E_BAD_DATA;
    context *ctx = (context *)c.data;
    toJson(ctx, 0, item);
    fputc('\n', ctx->f);
    return AERA_E_SUCCESS;
}

AERA_PLUGIN_EXPORT int aera_close(aera_context c)
{
    if (!c.data)
        return AERA_E_BAD_CONTEXT;
    context *ctx = (context *)c.data;
    fclose(ctx->f);
    free(ctx);
    return AERA_E_SUCCESS;
}

AERA_PLUGIN_EXPORT int aera_version ()
{
    return 1;
}
