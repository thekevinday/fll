/* FLL - Level 1
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
#ifndef _FL_serialized_h
#define _FL_serialized_h

// libc includes
#include <string.h>

// fll-0 includes
#include <level_0/strings.h>
#include <level_0/types.h>
#include <level_0/errors.h>
#include <level_0/serialized.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_serialize_
  // this function will append a string to the serialize.
  extern f_return_status fl_serialize(const f_dynamic_string value, f_serialized *serialized);
#endif // _di_fl_serialize_

#ifndef _di_fl_unserialize_
  // this function will unserialize a serialized string and store the results in an array of strings.
  extern f_return_status fl_unserialize(const f_serialized serialized, f_string_locations *locations);
#endif // _di_fl_unserialize_

#ifndef _di_fl_unserialize_get_
  // this function will pull a single serialized value from the serialized string at the given index.
  extern f_return_status fl_unserialize_get(const f_serialized serialized, const f_array_length index, f_string_location *location);
#endif // _di_fl_unserialize_get_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_serialized_h
