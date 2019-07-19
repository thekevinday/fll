/* FLL - Level 1
 * Project:       Serialized
 * Version:       0.4.3
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provides string processing functionality for what is to be defined as a serialized string.
 * Serialized strings are strings that can hold multiple values in a single variable.
 * An example of serialized content is the PATH environment variable where ':" separates data."
 */
#ifndef _FL_serialized_h
#define _FL_serialized_h

// libc includes
#include <string.h>

// fll-0 includes
#include <level_0/types.h>
#include <level_0/errors.h>
#include <level_0/strings.h>
#include <level_0/serialized.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_serialize_simple_
  // this function will append a string to the serialize.
  f_extern f_return_status fl_serialize_simple(const f_dynamic_string value, f_dynamic_string *serialized);
#endif // _di_fl_serialize_simple_

#ifndef _di_fl_unserialize_simple_
  // this function will unserialize a serialized string and store the results in an array of strings.
  f_extern f_return_status fl_unserialize_simple(const f_dynamic_string serialized, f_string_locations *locations);
#endif // _di_fl_unserialize_

#ifndef _di_fl_unserialize_simple_get_
  // this function will pull a single serialized value from the serialized string at the given index.
  f_extern f_return_status fl_unserialize_simple_get(const f_dynamic_string serialized, const f_array_length index, f_string_location *location);
#endif // _di_fl_unserialize_simple_get_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_serialized_h
