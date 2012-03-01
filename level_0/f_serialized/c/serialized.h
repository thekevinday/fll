/* FLL - Level 0
 * Project:       Serialized
 * Version:       0.2.0
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provides string processing functionality for what is to be defined as a serialized string.
 * Serialized strings are strings that can hold multiple values in a single variable.
 * An example of serialized content is the PATH environment variable where ':" separates data."
 */
#ifndef _F_serialized_h
#define _F_serialized_h

// libc includes
#include <string.h>

// fll-0 includes
#include <level_0/strings.h>
#include <level_0/types.h>
#include <level_0/errors.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_f_serialized_strategies_
  // possible strategies.
  enum {
    f_serialized_strategy_simple,
    f_serialized_strategy_delimited, // FIXME: not implemented
    f_last_serialized_strategy,
  }; // enum

  #define f_serialized_strategy_simple_splitter ":"
  #define f_serialized_strategy_delimited_splitter "'"
  #define f_serialized_strategy_delimited_delimiter "\\"
#endif // _di_f_serialized_strategies_

#ifndef _di_f_serialized_default_allocation_step_
  #define f_serialized_default_allocation_step f_memory_default_allocation_step
#endif // _di_f_serialized_default_allocation_step_

#ifndef _di_f_serialized_
  typedef struct {
    f_string string;
    f_string_length size;      // total amount of allocated space
    f_string_length used;      // total number of allocated spaces used
    f_array_length variables;  // total number of serialized variables stored
    f_u_short strategy,        // serialized strategy in use
  } f_serialized;

  #define f_serialized_initialize { f_string_initialize, f_string_length_initialize, f_string_length_initialize, f_array_length_initialize, 0 }

  #define f_delete_serialized(status, serialized) \
    status = f_delete((void **) & serialized.string, sizeof(f_string), serialized.size); \
    if (status == f_none){ \
      serialized.size = 0; \
      serialized.used = 0; \
    }

  #define f_destroy_serialized(status, serialized) \
    status = f_destroy((void **) & serialized.string, sizeof(f_string), serialized.size); \
    if (status == f_none){ \
      serialized.size = 0; \
      serialized.used = 0; \
    }

  #define f_resize_serialized(status, serialized, new_length) \
    status = f_resize((void **) & serialized.string, sizeof(f_string), serialized.size, new_length); \
    if (status == f_none){ \
      serialized.size = new_length; \
      if (serialized.used > serialized.size) serialized.used = new_length; \
    }

  #define f_adjust_serialized(status, serialized, new_length) \
    status = f_adjust((void **) & serialized.string, sizeof(f_string), serialized.size, new_length); \
    if (status == f_none){ \
      serialized.size = new_length; \
      if (serialized.used > serialized.size) serialized.used = new_length; \
    }
#endif // _di_f_serialized_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_serialized_h
