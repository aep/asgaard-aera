#ifndef AERA_PLUGIN
#define AERA_PLUGIN

#include <inttypes.h>
#include <stdbool.h>

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
typedef const void *aera_array_iterator;
typedef aera_type (*aera_get_type) (aera_item);
typedef bool (*aera_is_null )   (aera_item);
typedef bool (*aera_get_bool)   (aera_item, bool    &v);
typedef bool (*aera_get_int)    (aera_item, int64_t &v);
typedef bool (*aera_get_double) (aera_item, double  &v);
typedef bool (*aera_get_string) (aera_item, const char *&v);

typedef aera_array_iterator        (*aera_array_iterate) (aera_item);
typedef bool (*aera_array_end)     (aera_array_iterator);
typedef bool (*aera_array_next)    (aera_array_iterator, aera_item&);
typedef void (*aera_array_done)    (aera_array_iterator);

typedef bool (*aera_get_object_size)  (aera_item, int64_t& i);
typedef bool (*aera_get_object_value) (aera_item, aera_item&, int64_t i);
typedef bool (*aera_get_object_key)   (aera_item, aera_item&, int64_t i);
typedef bool (*aera_lookup_object)    (aera_item, aera_item, int64_t& i);


typedef aera_item (*aera_create_null)   ();
typedef aera_item (*aera_create_bool)   (bool v);
typedef aera_item (*aera_create_int)    (int64_t v);
typedef aera_item (*aera_create_double) (double v);
typedef aera_item (*aera_create_string) (const char *v);
typedef aera_item (*aera_create_array)  ();
typedef bool      (*aera_append_array)  (aera_item, aera_item);
typedef aera_item (*aera_create_object) ();
typedef bool      (*aera_insert_object) (aera_item, aera_item, aera_item);


typedef void (*aera_destroy) (aera_item);

struct aera_adaption
{
    aera_get_type         get_type;
    aera_is_null          is_null;
    aera_get_bool         get_bool;
    aera_get_int          get_int;
    aera_get_double       get_double;
    aera_get_string       get_string;

    aera_array_iterate    array_iterate;
    aera_array_end        array_end;
    aera_array_next       array_next;
    aera_array_done       array_done;

    aera_get_object_size  get_object_size;
    aera_get_object_value get_object_value;
    aera_get_object_key   get_object_key;
    aera_lookup_object    lookup_object;
    aera_create_null      create_null;
    aera_create_bool      create_bool;
    aera_create_int       create_int;
    aera_create_double    create_double;
    aera_create_string    create_string;
    aera_create_array     create_array;
    aera_append_array     append_array;
    aera_create_object    create_object;
    aera_insert_object    insert_object;
    aera_destroy          array_destroy;
};

typedef const void *aera_context;



#endif

