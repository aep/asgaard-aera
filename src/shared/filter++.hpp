#ifndef AERAPP_H_salkdas
#define AERAPP_H_salkdas

namespace AeraFilter
{
    class AERA_PLUGIN_LOCAL Filter
    {
    public:
        virtual aera_type type(aera_type_interface *tif, aera_item item);

        virtual aera_array_iterator array_iterate(aera_type_interface *tif, aera_item item);
        virtual bool array_next(aera_type_interface *tif, aera_item item, aera_item *);
        virtual bool array_end(aera_type_interface *tif, aera_item item);

        virtual aera_object_iterator object_iterate(aera_type_interface *tif, aera_item item);
        virtual bool object_next(aera_type_interface *tif, aera_item item, const char **, aera_item *);
        virtual bool object_end(aera_type_interface *tif, aera_item item);

        virtual aera_attribute_iterator attribute_iterate(aera_type_interface *tif, aera_item item);
        virtual bool attribute_next(aera_type_interface *tif, aera_item item, const char **, aera_item *);
        virtual bool attribute_end(aera_type_interface *tif, aera_item item);

        virtual bool get_string(aera_type_interface *tif, aera_item item, const char **);
        virtual bool get_double(aera_type_interface *tif, aera_item item, double *);

        virtual void destroy(aera_type_interface *tif, aera_item item);
    };

    struct AERA_PLUGIN_LOCAL Box
    {
        // TODO: this should be a list of them, so you can push multiple times
        // right now multi-push just leaks the previous

        AeraFilter::Filter *filter;
        aera_type_interface *tif;
        const void *item;
    };

};

#endif
