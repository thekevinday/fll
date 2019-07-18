/* FLL - Level 0
 * Project:       Strings
 * Version:       0.5.0
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provides string capabilities
 */
#ifndef _F_strings_h
#define _F_strings_h

// libc includes
#include <string.h>

// fll includes
#include <level_0/types.h>
#include <level_0/errors.h>
#include <level_0/memory.h>

#ifdef __cplusplus
extern "C" {
#endif

// BUG: for whatever reason strnlen is considered not included with -Wall, even with __USE_GNU defined
//      therefore this gets defined here
#ifndef _di_BUG_strnlen_
  f_extern size_t strnlen (f_const char *string, size_t max_length);
#endif // _di_BUG_strnlen_

// Define the end of string character
#ifndef _di_f_have_eos_
  #define f_eos '\0'
#endif // _di_f_have_eos_

// Define the end of line character
// FLL forbids '\r' and '\r\n' as end of line characters, \r will be silently ignored
#ifndef _di_f_have_eol_
  #define f_eol '\n'
#endif // _di_f_have_eol_

#ifndef _di_f_have_placeholder_
  #define f_placeholder '\0'
#endif // _di_f_have_placeholder_

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

// define the basic string type
#ifndef _di_f_have_string_
  typedef f_autochar *f_string;

  #define f_string_max_size   f_signed_long_size
  #define f_string_initialize f_eos

  #define f_new_string(status, string, length)   status = f_new_array((f_void_p *) & string, sizeof(f_string), length)
  #define f_delete_string(status, string, size)  status = f_delete((f_void_p *) & string, sizeof(f_string), size)
  #define f_destroy_string(status, string, size) status = f_destroy((f_void_p *) & string, sizeof(f_string), size)

  #define f_resize_string(status, string, old_length, new_length) \
    status = f_resize((f_void_p *) & string, sizeof(f_string), old_length, new_length)

  #define f_adjust_string(status, string, old_length, new_length) \
    status = f_adjust((f_void_p *) & string, sizeof(f_string), old_length, new_length)
#endif // _di_f_have_string_

#ifndef _di_f_string_length_
  typedef f_u_long f_string_length;

  #define f_string_length_printf string_format_long_integer

  #define f_new_string_length(status, string, length)   status = f_new_array((f_void_p *) & string, sizeof(f_string_length), length)
  #define f_delete_string_length(status, string)        status = f_delete((f_void_p *) & string)
  #define f_destroy_string_length(status, string, size) status = f_destroy((f_void_p *) & string, sizeof(f_string_length), size)

  #define f_resize_string_length(status, length, old_length, new_length) \
    status = f_resize((f_void_p *) & length, sizeof(f_string_length), old_length, new_length)

  #define f_adjust_string_length(status, length, old_length, new_length) \
    status = f_adjust((f_void_p *) & length, sizeof(f_string_length), old_length, new_length)
#endif // _di_f_string_length_

#ifndef _di_f_string_lengths_
  typedef struct {
    f_string_length *array;
    f_array_length  size;  // total amount of allocated space
    f_array_length  used;  // total number of allocated spaces used
  } f_string_lengths;

  #define f_string_lengths_initialize { 0, 0, 0 }

  #define f_delete_string_lengths(status, lengths) \
    f_delete_structure(status, lengths, f_string_length)

  #define f_destroy_string_lengths(status, lengths) \
    f_destroy_structure(status, lengths, f_string_length)

  #define f_resize_string_lengths(status, lengths, new_length) \
    f_resize_structure(status, lengths, f_string_length, new_length)

  #define f_adjust_string_lengths(status, lengths, new_length) \
    f_adjust_structure(status, lengths, f_string_length, new_length)
#endif // _di_f_string_lengths_

// designates a start and stop position that represents a sub-string inside of some parent string
// use this to avoid resizing, restructuring, and reallocating the parent string to separate the sub-string
#ifndef _di_f_string_location_
  typedef struct {
    f_string_length start;
    f_string_length stop;
  } f_string_location;

  #define f_string_location_initialize { 1, 0 }

  #define f_new_string_location(status, string_location, length)   status = f_new_array((f_void_p *) & string_location, sizeof(f_string_location), length)
  #define f_delete_string_location(status, string_location, size)  status = f_delete((f_void_p *) & string_location, sizeof(f_string_location), size)
  #define f_destroy_string_location(status, string_location, size) status = f_destroy((f_void_p *) & string_location, sizeof(f_string_location), size)

  #define f_resize_string_location(status, string_location, old_length, new_length) \
    status = f_resize((f_void_p *) & string_location, sizeof(f_string_location), old_length, new_length)

  #define f_adjust_string_location(status, string_location, old_length, new_length) \
    status = f_adjust((f_void_p *) & string_location, sizeof(f_string_location), old_length, new_length)
#endif // _di_f_string_location_

// an array of string locations
#ifndef _di_f_string_locations_
  typedef struct {
    f_string_location *array; // the array of string locations
    f_array_length    size;   // total amount of allocated space
    f_array_length    used;   // total number of allocated spaces used
  } f_string_locations;

  #define f_string_locations_initialize {0, 0, 0}

  #define f_delete_string_locations(status, locations) \
    f_delete_structure(status, locations, f_string_location)

  #define f_destroy_string_locations(status, locations) \
    f_destroy_structure(status, locations, f_string_location)

  #define f_resize_string_locations(status, locations, new_length) \
    f_resize_structure(status, locations, f_string_location, new_length)

  #define f_adjust_string_locations(status, locations, new_length) \
    f_adjust_structure(status, locations, f_string_location, new_length)
#endif // _di_f_string_locations_

// a string that supports contains a size attribute to handle dynamic allocations and deallocations
// save the string size along with the string, so that strlen(..) commands can be avoided as much as possible
#ifndef _di_f_dynamic_string_
  typedef struct {
    f_string        string; // the string itself
    f_string_length size;   // total amount of allocated space
    f_string_length used;   // total number of allocated spaces used
  } f_dynamic_string;

  #define f_dynamic_string_initialize { f_string_initialize, 0, 0 }

  #define f_delete_dynamic_string(status, dynamic) \
    status = f_delete((f_void_p *) & dynamic.string, sizeof(f_string), dynamic.size); \
    if (status == f_none) { \
      dynamic.size = 0; \
      dynamic.used = 0; \
    }

  #define f_destroy_dynamic_string(status, dynamic) \
    status = f_destroy((f_void_p *) & dynamic.string, sizeof(f_string), dynamic.size); \
    if (status == f_none) { \
      dynamic.size = 0; \
      dynamic.used = 0; \
    }

  #define f_resize_dynamic_string(status, dynamic, new_length) \
    status = f_resize((f_void_p *) & dynamic.string, sizeof(f_string), dynamic.size, new_length); \
    if (status == f_none) { \
      dynamic.size = new_length; \
      if (dynamic.used > dynamic.size) dynamic.used = new_length; \
    }

  #define f_adjust_dynamic_string(status, dynamic, new_length) \
    status = f_adjust((f_void_p *) & dynamic.string, sizeof(f_string), dynamic.size, new_length); \
    if (status == f_none) { \
      dynamic.size = new_length; \
      if (dynamic.used > dynamic.size) dynamic.used = new_length; \
    }
#endif // _di_f_dynamic_string_

// an array of dynamic strings
#ifndef _di_f_dynamic_strings_
  typedef struct {
    f_dynamic_string *array; // the array of dynamic strings
    f_string_length  size;   // total amount of allocated space
    f_string_length  used;   // total number of allocated spaces used
  } f_dynamic_strings;

  #define f_dynamic_strings_initialize { 0, 0, 0 }

  #define f_delete_dynamic_strings(status, dynamics) \
    status = f_none; \
    while (dynamics.size > 0) { \
      --dynamics.size; \
      f_delete_dynamic_string(status, dynamics.array[dynamics.size]); \
      if (status != f_none) break; \
    } \
    if (status == f_none) status = f_delete((f_void_p *) & dynamics.array, sizeof(f_dynamic_string), dynamics.size); \
    if (status == f_none) dynamics.used = 0;

  #define f_destroy_dynamic_strings(status, dynamics) \
    status = f_none; \
    while (dynamics.size > 0) { \
      --dynamics.size; \
      f_destroy_dynamic_string(status, dynamics.array[dynamics.size]); \
      if (status != f_none) break; \
    } \
    if (status == f_none) status = f_destroy((f_void_p *) & dynamics.array, sizeof(f_dynamic_string), dynamics.size); \
    if (status == f_none) dynamics.used = 0;

  #define f_resize_dynamic_strings(status, dynamics, new_length) \
    status = f_none; \
    if (new_length < dynamics.size) { \
      f_string_length i = dynamics.size - new_length; \
      for (; i < dynamics.size; ++i) { \
        f_delete_dynamic_string(status, dynamics.array[i]); \
        if (status != f_none) break; \
      } \
    } \
    if (status == f_none) status = f_resize((f_void_p *) & dynamics.array, sizeof(f_dynamic_string), dynamics.size, new_length); \
    if (status == f_none) { \
      if (new_length > dynamics.size) { \
        f_string_length i = dynamics.size; \
        for (; i < new_length; ++i) { \
          memset(&dynamics.array[i], 0, sizeof(f_string)); \
        } \
      } \
      dynamics.size = new_length; \
      if (dynamics.used > dynamics.size) dynamics.used = new_length; \
    }

  #define f_adjust_dynamic_strings(status, dynamics, new_length) \
    status = f_none; \
    if (new_length < dynamics.size) { \
      f_string_length i = dynamics.size - new_length; \
      for (; i < dynamics.size; ++i) { \
        f_destroy_dynamic_string(status, dynamics.array[i]); \
        if (status != f_none) break; \
      } \
    } \
    if (status == f_none) status = f_adjust((f_void_p *) & dynamics.array, sizeof(f_dynamic_string), dynamics.size, new_length); \
    if (status == f_none) { \
      if (new_length > dynamics.size) { \
        f_string_length i = dynamics.size; \
        for (; i < new_length; ++i) { \
          memset(&dynamics.array[i], 0, sizeof(f_dynamic_string)); \
        } \
      } \
      dynamics.size = new_length; \
      if (dynamics.used > dynamics.size) dynamics.used = new_length; \
    }
#endif // _di_f_dynamic_string_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_strings_h
