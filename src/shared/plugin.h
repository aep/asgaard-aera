#ifndef AERA_PLUGIN
#define AERA_PLUGIN

#include <inttypes.h>
#include <stdbool.h>

#if defined _WIN32 || defined __CYGWIN__
  #define AERA_PLUGIN_IMPORT __declspec(dllimport)
  #define AERA_PLUGIN_EXPORT __declspec(dllexport)
  #define AERA_PLUGIN_LOCAL
#else
  #if __GNUC__ >= 4
    #define AERA_PLUGIN_IMPORT __attribute__ ((visibility ("default")))
    #define AERA_PLUGIN_EXPORT __attribute__ ((visibility ("default")))
    #define AERA_PLUGIN_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define AERA_PLUGIN_IMPORT
    #define AERA_PLUGIN_EXPORT
    #define AERA_PLUGIN_LOCAL
  #endif
#endif

typedef enum
{
    aera_null,
    aera_bool,
    aera_int,
    aera_double,
    aera_string,
    aera_enum,
    aera_array,
    aera_object
} aera_type;

typedef const void *aera_item;
typedef const void *aera_array_iterator;
typedef const void *aera_object_iterator;
typedef const void *aera_attribute_iterator;

typedef struct
{
    aera_type  (*get_type)    (aera_item);
    bool       (*is_null)     (aera_item);
    bool       (*get_bool)    (aera_item, bool *v);
    bool       (*get_int)     (aera_item, int64_t *v);
    bool       (*get_double)  (aera_item, double *v);
    bool       (*get_string)  (aera_item, const char **v);
    void       (*done)        (aera_item);

    aera_array_iterator (*array_iterate) (aera_item);
    bool       (*array_end)     (aera_array_iterator);
    bool       (*array_next)    (aera_array_iterator, aera_item*);
    void       (*array_done)    (aera_array_iterator);

    aera_object_iterator (*object_iterate) (aera_item);
    bool       (*object_end)     (aera_object_iterator);
    bool       (*object_next)    (aera_object_iterator, const char **k, aera_item*);
    void       (*object_done)    (aera_object_iterator);

    aera_attribute_iterator (*attribute_iterate) (aera_item);
    bool       (*attribute_end)     (aera_attribute_iterator);
    bool       (*attribute_next)    (aera_attribute_iterator, const char **k, aera_item*);
    void       (*attribute_done)    (aera_attribute_iterator);
} aera_type_interface;

typedef const void *aera_context;


typedef struct
{
    aera_context (*open) (int argc, char **argv);
    aera_item    (*pull) (aera_context);
    bool         (*push) (aera_context, aera_type_interface *tif, aera_item);
    void         (*close)(aera_context);
} aera_plugin_interface;

// these are the plugin symbols to be exported
typedef aera_plugin_interface *(*aera_plugin_t) ();
typedef aera_type_interface   *(*aera_types_t)  ();
typedef int (*aera_version_t) ();



#endif

