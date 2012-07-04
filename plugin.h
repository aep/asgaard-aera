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

enum aera_type
{
    aera_null,
    aera_bool,
    aera_int,
    aera_double,
    aera_string,
    aera_array,
    aera_object
};


typedef const void *aera_item;
typedef aera_type (*aera_get_type) (aera_item);
typedef bool (*aera_is_null )   (aera_item);
typedef bool (*aera_get_bool)   (aera_item, bool    &v);
typedef bool (*aera_get_int)    (aera_item, int64_t &v);
typedef bool (*aera_get_double) (aera_item, double  &v);
typedef bool (*aera_get_string) (aera_item, const char *&v);
typedef void (*aera_done)       (aera_item);

typedef const void *aera_array_iterator;
typedef aera_array_iterator        (*aera_array_iterate) (aera_item);
typedef bool (*aera_array_end)     (aera_array_iterator);
typedef bool (*aera_array_next)    (aera_array_iterator, aera_item&);
typedef void (*aera_array_done)    (aera_array_iterator);

typedef const void *aera_object_iterator;
typedef aera_object_iterator       (*aera_object_iterate) (aera_item);
typedef bool (*aera_object_end)    (aera_object_iterator);
typedef bool (*aera_object_next)   (aera_object_iterator, aera_item&, aera_item&);
typedef void (*aera_object_done)   (aera_object_iterator);


typedef aera_item (*aera_create_null)   ();
typedef aera_item (*aera_create_bool)   (bool v);
typedef aera_item (*aera_create_int)    (int64_t v);
typedef aera_item (*aera_create_double) (double v);
typedef aera_item (*aera_create_string) (const char *v);
typedef aera_item (*aera_create_array)  ();
typedef bool      (*aera_append_array)  (aera_item, aera_item);
typedef aera_item (*aera_create_object) ();
typedef bool      (*aera_insert_object) (aera_item, aera_item, aera_item);



struct aera_type_interface
{
    aera_get_type         get_type;
    aera_is_null          is_null;
    aera_get_bool         get_bool;
    aera_get_int          get_int;
    aera_get_double       get_double;
    aera_get_string       get_string;
    aera_done             done;

    aera_array_iterate    array_iterate;
    aera_array_end        array_end;
    aera_array_next       array_next;
    aera_array_done       array_done;

    aera_object_iterate   object_iterate;
    aera_object_end       object_end;
    aera_object_next      object_next;
    aera_object_done      object_done;

    aera_create_null      create_null;
    aera_create_bool      create_bool;
    aera_create_int       create_int;
    aera_create_double    create_double;
    aera_create_string    create_string;
    aera_create_array     create_array;
    aera_append_array     append_array;
    aera_create_object    create_object;
    aera_insert_object    insert_object;
};




typedef const void *aera_context;
typedef aera_context (*aera_read) (int argc, char **argv);
typedef aera_item    (*aera_root) (aera_context);
typedef void         (*aera_close)(aera_context);

struct aera_plugin_interface
{
    aera_read  read;
    aera_root  root;
    aera_close close;
};

// these are the plugin symbols to be exported
typedef aera_plugin_interface *(*aera_plugin_t) ();
typedef aera_type_interface   *(*aera_types_t)  ();
typedef int (*aera_version_t) ();



#endif

