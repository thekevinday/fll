/**
 * FLL - Level 1
 *
 * Project: Serialized
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides string processing functionality for what is to be defined as a serialized string.
 * Serialized strings are strings that can hold multiple values in a single variable.
 * An example of serialized content is the PATH environment variable where ":" separates data.
 */
#ifndef _FL_serialized_h
#define _FL_serialized_h

// libc includes
#include <string.h>

// fll-0 includes
#include <level_0/errors.h>
#include <level_0/serialized.h>
#include <level_0/strings.h>
#include <level_0/types.h>
#include <level_0/utf.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Serialized a string using the Simple serialize algorithm.
 *
 * The simple Serialize algorithm is akin to the PATH environment variable, example: PATH="/bin:/sbin:/usr/bin".
 *
 * To generate the above example, this would be called 3 times, with the following strings:
 *   1) value = "/bin", then: PATH="/bin".
 *   2) value = "/sbin", then: PATH="/bin:/sbin".
 *   3) value = "/usr/sbin", then: PATH="/bin:/sbin:/usr/sbin".
 *
 * @param value
 *   The string to append onto serialized.
 * @param serialized
 *   The dynamic string that represents a serialized set of strings.
 *
 * @return
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_reallocation_error (with error bit) on memory reallocation error.
 */
#ifndef _di_fl_serialize_simple_
  extern f_return_status fl_serialize_simple(const f_dynamic_string value, f_dynamic_string *serialized);
#endif // _di_fl_serialize_simple_

// @todo: implement fl_unserialize_simple() such that a new array of strings is allocated.

/**
 * Identify string positions within a serialized string using the Simple serialize algorithm.
 *
 * The simple Serialize algorithm is akin to the PATH environment variable, example: PATH="/bin:/sbin:/usr/bin".
 *
 * After processing the above example, there would be the following positions:
 *   1) start = 0, stop = 3.
 *   2) start = 5, stop = 9.
 *   3) start = 11, stop = 18.
 *
 * @param serialized
 *   A serialized string to de-serialize.
 * @param locations
 *   The locations within the serialized string representing distinct separate strings.
 *
 * @return
 *   f_none on success.
 *   f_incomplete_utf_on_eos if end of sting is reached before a complete UTF-8 character can be processed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_reallocation_error (with error bit) on memory reallocation error.
 */
#ifndef _di_fl_unserialize_simple_map_
  extern f_return_status fl_unserialize_simple_map(const f_dynamic_string serialized, f_string_locations *locations);
#endif // _di_fl_unserialize_simple_map_

/**
 * Unserialize a specific string using the Simple serialize algorithm.
 *
 * The simple Serialize algorithm is akin to the PATH environment variable, example: PATH="/bin:/sbin:/usr/bin".
 *
 * After processing the above example, there would be the following positions, for the given index:
 *   1) with index = 0, start = 0, stop = 3.
 *   2) with index = 1, start = 5, stop = 9.
 *   3) with index = 2, start = 11, stop = 18.
 *
 * @param serialized
 *   A serialized string to de-serialize.
 * @param index
 *   An index position within the serialized string to get the deserialized positions of.
 * @param location
 *   A location within the serialized string representing the string at the given index.
 *
 * @return
 *   f_none on success.
 *   f_none_on_eos on success at end of string.
 *   f_no_data_on_eos if end of string reached before index was reached.
 *   f_incomplete_utf_on_eos (with error bit) if end of string is reached before a complete UTF-8 character can be processed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_unserialize_simple_find_
  extern f_return_status fl_unserialize_simple_find(const f_dynamic_string serialized, const f_array_length index, f_string_location *location);
#endif // _di_fl_unserialize_simple_find_

// @todo: implement fl_unserialize_simple_get() such that a new string is allocated, if found.

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_serialized_h
