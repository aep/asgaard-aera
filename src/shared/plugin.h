#ifndef AERA_PLUGIN
#define AERA_PLUGIN

#include <inttypes.h>

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
    aera_null_t,
    aera_bool_t,
    aera_int_t,
    aera_double_t,
    aera_string_t,
    aera_enum_t,
    aera_array_t,
    aera_object_t
} aera_type;

typedef enum
{
    AERA_E_SUCCESS     = 0,
    AERA_E_BAD_DATA    = 1,
    AERA_E_BAD_CONTEXT = 2,
    AERA_E_IO          = 3,
} aera_errors;

struct aera_item_interface_s;
struct aera_array_interface_s;

// this is passed by value intentionally. 2x sizeof(void *) is cheap on intel. what about others?
typedef struct {const void *data; struct aera_type_interface_s *type;}    aera_item;
typedef struct {const void *data; struct aera_array_interface_s *type;}   aera_array;
typedef struct {const void *data; struct aera_object_interface_s *type;}  aera_object;

struct aera_type_interface_s
{
    int (*get_type)      (aera_item, aera_type *t);
    int (*is_null)       (aera_item);
    int (*get_int)       (aera_item, int64_t *v);
    int (*get_double)    (aera_item, double *v);
    int (*get_string)    (aera_item, const char **v);
    int (*done)          (aera_item);

    int (*get_array)     (aera_item, aera_array*);
    int (*get_object)    (aera_item, aera_object*);
};

struct aera_array_interface_s
{
    int (*next)         (aera_array, aera_item*);
    int (*done)         (aera_array);
};

struct aera_object_interface_s
{
    int (*next)         (aera_object, const char **k, aera_item*);
    int (*done)         (aera_object);
};

typedef struct aera_type_interface_s   aera_type_interface;
typedef struct aera_array_interface_s  aera_array_interface;
typedef struct aera_object_interface_s aera_object_interface;


typedef struct {const void *data;}  aera_context;
typedef struct
{
    int (*open) (int argc, char **argv, aera_context *);
    int (*pull) (aera_context, aera_item *);
    int (*push) (aera_context, aera_item);
    int (*close)(aera_context);
} aera_plugin_interface;

// these are the plugin symbols to be exported
typedef aera_plugin_interface *(*aera_plugin_t) ();
typedef int (*aera_version_t) ();



#endif

