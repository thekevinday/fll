/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides string capabilities.
 */
#ifndef _F_string_h
#define _F_string_h

// libc includes
#include <string.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/type.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * BUG: for whatever reason strnlen is considered not included with -Wall, even with __USE_GNU defined.
 *      therefore this gets defined here.
 */
#ifdef _en_BUG_strnlen_
  extern size_t strnlen (const char *string, size_t max_length);
#endif // _en_BUG_strnlen_

/**
 * Define the end of string character.
 */
#ifndef _di_f_string_has_eos_
  #define f_string_eos '\0'
#endif // _di_f_string_has_eos_

/**
 * Define the end of line character.
 * FLL forbids '\r' and '\r\n' as end of line characters, \r will be silently ignored.
 */
#ifndef _di_f_string_has_eol_
  #define f_string_eol '\n'
#endif // _di_f_string_has_eol_

#ifndef _di_f_string_has_placeholder_
  #define f_string_placeholder '\0'
#endif // _di_f_string_has_placeholder_

#ifndef _di_string_format_pointers_
  #define string_format_string             "%s"
  #define string_format_character          "%c"
  #define string_format_wide_string        "%ls"
  #define string_format_wide_character     "%lc"
  #define string_format_integer            "%i"
  #define string_format_unsigned           "%u"
  #define string_format_double             "%d"
  #define string_format_float              "%f"
  #define string_format_short_integer      "%hi"
  #define string_format_short_unsigned     "%hu"
  #define string_format_long_integer       "%li"
  #define string_format_long_unsigned      "%lu"
  #define string_format_long_double        "%ld"
  #define string_format_long_long_integer  "%lli"
  #define string_format_long_long_unsigned "%llu"
#endif // _di_string_format_pointers_

#ifndef _di_f_array_length_printf_
  #define f_array_length_printf       string_format_integer
  #define f_array_length_short_printf string_format_short_integer
  #define f_array_length_long_printf  string_format_long_integer
#endif // _di_f_array_length_printf_

/**
 * define the basic string type.
 */
#ifndef _di_f_string_
  typedef char *f_string;

  #define f_string_max_size   f_type_size_32_signed
  #define f_string_initialize f_string_eos

  #define f_macro_string_new(status, string, length)   status = f_memory_new((void **) & string, sizeof(f_string), length)
  #define f_macro_string_delete(status, string, size)  status = f_memory_delete((void **) & string, sizeof(f_string), size)
  #define f_macro_string_destroy(status, string, size) status = f_memory_destroy((void **) & string, sizeof(f_string), size)

  #define f_macro_string_resize(status, string, old_length, new_length) \
    status = f_memory_resize((void **) & string, sizeof(f_string), old_length, new_length)

  #define f_macro_string_adjust(status, string, old_length, new_length) \
    status = f_memory_adjust((void **) & string, sizeof(f_string), old_length, new_length)
#endif // _di_f_string_

#ifndef _di_f_string_length_
  typedef uint64_t f_string_length;

  #define f_string_length_printf string_format_long_integer

  #define f_macro_string_length_new(status, string, length)    status = f_memory_new((void **) & string, sizeof(f_string_length), length)
  #define f_macro_string_length_delete(status, string, length) status = f_memory_delete((void **) & string, sizeof(f_string_length), length)
  #define f_macro_string_length_destroy(status, string, size)  status = f_memory_destroy((f_void_P *) & string, sizeof(f_string_length), size)

  #define f_macro_string_length_resize(status, length, old_length, new_length) \
    status = f_memory_resize((void **) & length, sizeof(f_string_length), old_length, new_length)

  #define f_macro_string_length_adjust(status, length, old_length, new_length) \
    status = f_memory_adjust((void **) & length, sizeof(f_string_length), old_length, new_length)
#endif // _di_f_string_length_

/**
 * A structure containing an array of string lengths.
 *
 * array: the array of string lengths.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_lengths_
  typedef struct {
    f_string_length *array;
    f_array_length   size;
    f_array_length   used;
  } f_string_lengths;

  #define f_string_lengths_initialize { 0, 0, 0 }

  #define f_macro_string_lengths_clear(lengths) f_macro_memory_structure_clear(lengths)

  #define f_macro_string_lengths_new(status, lengths, length) f_macro_memory_structure_new(status, lengths, f_string_length, length)

  #define f_macro_string_lengths_delete(status, lengths) f_macro_memory_structure_delete(status, lengths, f_string_length)
  #define f_macro_string_lengths_destroy(status, lengths) f_macro_memory_structure_destroy(status, lengths, f_string_length)

  #define f_macro_string_lengths_resize(status, lengths, new_length) f_macro_memory_structure_resize(status, lengths, f_string_length, new_length)
  #define f_macro_string_lengths_adjust(status, lengths, new_length) f_macro_memory_structure_adjust(status, lengths, f_string_length, new_length)
#endif // _di_f_string_lengths_

/**
 * A structure designating a start and stop position that represents a sub-string inside of some parent string.
 *
 * Use this to avoid resizing, restructuring, and reallocating the parent string to separate the sub-string.
 *
 * In general, this project uses the start and stop position inclusively, meaning that a range of 0 to 1 would include positions 0 and position 1.
 * Therefore, 0 to 0 would be a position of 0.
 * Set start to some value larger than stop to designate no range.
 *
 * start: the start position.
 * stop: the stop position.
 */
#ifndef _di_f_string_location_
  typedef struct {
    f_string_length start;
    f_string_length stop;
  } f_string_location;

  #define f_string_location_initialize { 1, 0 }

  #define f_macro_string_location_new(status, string_location, length)   status = f_memory_new((void **) & string_location, sizeof(f_string_location), length)
  #define f_macro_string_location_delete(status, string_location, size)  status = f_memory_delete((void **) & string_location, sizeof(f_string_location), size)
  #define f_macro_string_location_destroy(status, string_location, size) status = f_memory_destroy((void **) & string_location, sizeof(f_string_location), size)

  #define f_macro_string_location_resize(status, string_location, old_length, new_length) \
    status = f_memory_resize((void **) & string_location, sizeof(f_string_location), old_length, new_length)

  #define f_macro_string_location_adjust(status, string_location, old_length, new_length) \
    status = f_memory_adjust((void **) & string_location, sizeof(f_string_location), old_length, new_length)
#endif // _di_f_string_location_

/**
 * An array of string locations.
 *
 * array: the array of string locations.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_locations_
  typedef struct {
    f_string_location *array;
    f_array_length    size;
    f_array_length    used;
  } f_string_locations;

  #define f_string_locations_initialize {0, 0, 0}

  #define f_macro_string_locations_clear(locations) f_macro_memory_structure_clear(locations)

  #define f_macro_string_locations_new(status, locations, length) f_macro_memory_structure_new(status, locations, f_string_location, length)

  #define f_macro_string_locations_delete(status, locations) f_macro_memory_structure_delete(status, locations, f_string_location)
  #define f_macro_string_locations_destroy(status, locations) f_macro_memory_structure_destroy(status, locations, f_string_location)

  #define f_macro_string_locations_resize(status, locations, new_length) f_macro_memory_structure_resize(status, locations, f_string_location, new_length)
  #define f_macro_string_locations_adjust(status, locations, new_length) f_macro_memory_structure_adjust(status, locations, f_string_location, new_length)
#endif // _di_f_string_locations_

/**
 * A string that supports contains a size attribute to handle dynamic allocations and deallocations.
 *
 * Save the string size along with the string, so that strlen(..) commands can be avoided as much as possible.
 *
 * string: the string.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_dynamic_
  typedef struct {
    f_string        string;
    f_string_length size;
    f_string_length used;
  } f_string_dynamic;

  #define f_string_dynamic_initialize { f_string_initialize, 0, 0 }

  #define f_clear_string_dynamic(dynamic) \
    dynamic.string = 0; \
    dynamic.size = 0; \
    dynamic.used = 0;

  #define f_macro_string_dynamic_new(status, dynamic, new_length) \
    f_clear_string_dynamic(dynamic) \
    status = f_memory_new((void **) & dynamic.string, sizeof(f_string), new_length); \
    if (status == f_none) { \
      dynamic.size = new_length; \
      dynamic.used = 0; \
    }

  #define f_macro_string_dynamic_delete(status, dynamic) \
    status = f_memory_delete((void **) & dynamic.string, sizeof(f_string), dynamic.size); \
    if (status == f_none) { \
      dynamic.size = 0; \
      dynamic.used = 0; \
    }

  #define f_macro_string_dynamic_destroy(status, dynamic) \
    status = f_memory_destroy((void **) & dynamic.string, sizeof(f_string), dynamic.size); \
    if (status == f_none) { \
      dynamic.size = 0; \
      dynamic.used = 0; \
    }

  #define f_macro_string_dynamic_resize(status, dynamic, new_length) \
    status = f_memory_resize((void **) & dynamic.string, sizeof(f_string), dynamic.size, new_length); \
    if (status == f_none) { \
      dynamic.size = new_length; \
      if (dynamic.used > dynamic.size) dynamic.used = new_length; \
    }

  #define f_macro_string_dynamic_adjust(status, dynamic, new_length) \
    status = f_memory_adjust((void **) & dynamic.string, sizeof(f_string), dynamic.size, new_length); \
    if (status == f_none) { \
      dynamic.size = new_length; \
      if (dynamic.used > dynamic.size) dynamic.used = new_length; \
    }
#endif // _di_f_string_dynamic_

/**
 * An array of dynamic strings.
 *
 * array: the array of dynamic strings.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_dynamics_
  typedef struct {
    f_string_dynamic *array;
    f_string_length  size;
    f_string_length  used;
  } f_string_dynamics;

  #define f_string_dynamics_initialize { 0, 0, 0 }

  #define f_clear_string_dynamics(dynamics) \
    dynamics.array = 0; \
    dynamics.size = 0; \
    dynamics.used = 0;

  #define f_macro_string_dynamics_new(status, dynamics, length) \
    dynamics.array = 0; \
    dynamics.size = 0; \
    dynamics.used = 0; \
    status = f_memory_new((void **) & dynamics.array, sizeof(f_string_dynamic), length); \
    if (status == f_none) { \
      dynamics.size = length; \
      dynamics.used = 0; \
    }

  #define f_macro_string_dynamics_delete(status, dynamics) \
    status = f_none; \
    while (dynamics.size > 0) { \
      --dynamics.size; \
      f_macro_string_dynamic_destroy(status, dynamics.array[dynamics.size]); \
      if (status != f_none) break; \
    } \
    if (status == f_none) status = f_memory_delete((void **) & dynamics.array, sizeof(f_string_dynamic), dynamics.size); \
    if (status == f_none) dynamics.used = 0;

  #define f_macro_string_dynamics_destroy(status, dynamics) \
    status = f_none; \
    while (dynamics.size > 0) { \
      --dynamics.size; \
      f_macro_string_dynamic_destroy(status, dynamics.array[dynamics.size]); \
      if (status != f_none) break; \
    } \
    if (status == f_none) status = f_memory_destroy((void **) & dynamics.array, sizeof(f_string_dynamic), dynamics.size); \
    if (status == f_none) dynamics.used = 0;

  #define f_macro_string_dynamics_resize(status, dynamics, new_length) \
    status = f_none; \
    if (new_length < dynamics.size) { \
      f_string_length i = dynamics.size - new_length; \
      for (; i < dynamics.size; ++i) { \
        f_macro_string_dynamic_destroy(status, dynamics.array[i]); \
        if (status != f_none) break; \
      } \
    } \
    if (status == f_none) status = f_memory_resize((void **) & dynamics.array, sizeof(f_string_dynamic), dynamics.size, new_length); \
    if (status == f_none) { \
      if (new_length > dynamics.size) { \
        f_string_length i = dynamics.size; \
        for (; i < new_length; ++i) { \
          memset(&dynamics.array[i], 0, sizeof(f_string_dynamic)); \
        } \
      } \
      dynamics.size = new_length; \
      if (dynamics.used > dynamics.size) dynamics.used = new_length; \
    }

  #define f_macro_string_dynamics_adjust(status, dynamics, new_length) \
    status = f_none; \
    if (new_length < dynamics.size) { \
      f_string_length i = dynamics.size - new_length; \
      for (; i < dynamics.size; ++i) { \
        f_macro_string_dynamic_destroy(status, dynamics.array[i], f_string_dynamic); \
        if (status != f_none) break; \
      } \
    } \
    if (status == f_none) status = f_memory_adjust((void **) & dynamics.array, sizeof(f_string_dynamic), dynamics.size, new_length); \
    if (status == f_none) { \
      if (new_length > dynamics.size) { \
        f_string_length i = dynamics.size; \
        for (; i < new_length; ++i) { \
          memset(&dynamics.array[i], 0, sizeof(f_string_dynamic)); \
        } \
      } \
      dynamics.size = new_length; \
      if (dynamics.used > dynamics.size) dynamics.used = new_length; \
    }
#endif // _di_f_string_dynamic_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_h
