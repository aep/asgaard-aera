#ifndef AERAPP_H_salkdas
#define AERAPP_H_salkdas

namespace Aera
{

    class AERA_PLUGIN_LOCAL Object
    {
    public:
        Object()
        {}
        virtual ~Object() {}

        virtual aera_type type() { return aera_null; };

        virtual aera_array_iterator array_iterate() { return 0; }
        virtual bool array_next(aera_item *) { return false; };
        virtual bool array_end() { return true; }

        virtual aera_object_iterator object_iterate() { return 0; }
        virtual bool object_next(const char **, aera_item *) { return false; };
        virtual bool object_end() { return true; }

        virtual aera_attribute_iterator attribute_iterate() { return 0; }
        virtual bool attribute_next(const char **, aera_item *) { return false; };
        virtual bool attribute_end() { return true; }

        virtual bool get_string(const char **) { return false; }
        virtual bool get_double(double *) { return false; }
    };

};

#endif
