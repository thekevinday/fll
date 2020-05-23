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
#include <level_0/status.h>
#include <level_0/serialized.h>
#include <level_0/string.h>
#include <level_0/type.h>
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
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 */
#ifndef _di_fl_serialize_simple_
  extern f_return_status fl_serialize_simple(const f_string_static value, f_string_dynamic *serialized);
#endif // _di_fl_serialize_simple_

/**
 * De-serialized the entire serialized string into multiple separate strings using the Simple serialize algorithm.
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
 * @param strings
 *   An array of strings de-serialized from serialized.
 *
 * @return
 *   F_none on success.
 *   F_incomplete_utf_eos if end of sting is reached before a complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 */
#ifndef _di_fl_unserialize_simple_
  extern f_return_status fl_unserialize_simple(const f_string_static serialized, f_string_dynamics *strings);
#endif // _di_fl_unserialize_simple_

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
 *   F_none on success.
 *   F_incomplete_utf_eos if end of sting is reached before a complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 */
#ifndef _di_fl_unserialize_simple_map_
  extern f_return_status fl_unserialize_simple_map(const f_string_static serialized, f_string_ranges *locations);
#endif // _di_fl_unserialize_simple_map_

/**
 * Unserialize and find the address for a specific string using the Simple serialize algorithm.
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
 *   F_none on success.
 *   F_none_eos on success at end of string.
 *   F_data_not_eos if end of string reached before index was reached.
 *   F_incomplete_utf_eos (with error bit) if end of string is reached before a complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_unserialize_simple_find_
  extern f_return_status fl_unserialize_simple_find(const f_string_static serialized, const f_array_length index, f_string_range *location);
#endif // _di_fl_unserialize_simple_find_

/**
 * Unserialize and get a copy of a specific string using the Simple serialize algorithm.
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
 * @param dynamic
 *   The unserialized string from the specified index.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success at end of string.
 *   F_data_not_eos if end of string reached before index was reached (dynamic->used is set to 0).
 *   F_incomplete_utf_eos (with error bit) if end of string is reached before a complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 */
#ifndef _di_fl_unserialize_simple_get_
  extern f_return_status fl_unserialize_simple_get(const f_string_static serialized, const f_array_length index, f_string_dynamic *dynamic);
#endif // _di_fl_unserialize_simple_get_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_serialized_h
