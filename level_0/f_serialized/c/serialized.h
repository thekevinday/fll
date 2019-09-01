/**
 * FLL - Level 0
 *
 * Project: Serialized
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides string processing functionality for what is to be defined as a serialized string.
 * Serialized strings are strings that can hold multiple values in a single variable.
 * An example of serialized content is the PATH environment variable where ":" separates data.
 */
#ifndef _F_serialized_h
#define _F_serialized_h

// libc includes
#include <string.h>

// fll-0 includes
#include <level_0/string.h>
#include <level_0/type.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_serialized_splitters_
  #define f_serialized_simple_splitter     ':'
  #define f_serialized_delimited_splitter  '\''
  #define f_serialized_delimited_delimiter '\\'

  #define f_serialized_simple_splitter_string     ":"
  #define f_serialized_delimited_splitter_string  "'"
  #define f_serialized_delimited_delimiter_string "\\"
#endif // _di_f_serialized_splitters_

#ifndef _di_f_serialized_default_allocation_step_
  // provide a UTF-8 friendly allocation step.
  #define f_serialized_default_allocation_step 4
#endif // _di_f_serialized_default_allocation_step_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_serialized_h
