/**
 * FLL - Level 0
 *
 * Project: Serialize
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides string processing functionality for what is to be defined as a serialize string.
 * Serialized strings are strings that can hold multiple values in a single variable.
 * An example of serialize content is the PATH environment variable where ":" separates data.
 */
#ifndef _F_serialize_h
#define _F_serialize_h

// libc includes
#include <string.h>

// fll-0 includes
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>

// fll-0 serialize includes
#include <fll/level_0/serialize-common.h>

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
 *   The string to append onto serialize.
 * @param serialize
 *   The dynamic string that represents a serialize set of strings.
 *
 * @return
 *   F_none on success.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_serialize_simple_
  extern f_status_t f_serialize_simple(const f_string_static_t value, f_string_dynamic_t *serialize);
#endif // _di_f_serialize_simple_

/**
 * De-serialize the entire serialize string into multiple separate strings using the Simple serialize algorithm.
 *
 * The simple Serialize algorithm is akin to the PATH environment variable, example: PATH="/bin:/sbin:/usr/bin".
 *
 * After processing the above example, there would be the following positions:
 *   1) start = 0, stop = 3.
 *   2) start = 5, stop = 9.
 *   3) start = 11, stop = 18.
 *
 * @param serialize
 *   A serialize string to de-serialize.
 * @param strings
 *   An array of strings de-serialize from serialize.
 *
 * @return
 *   F_none on success.
 *   F_complete_not_utf_eos if end of sting is reached before a complete UTF-8 character can be processed.
 *   F_array_too_large (with error bit) if a buffer would exceed maximum length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_serialize_un_simple_
  extern f_status_t f_serialize_un_simple(const f_string_static_t serialize, f_string_dynamics_t *strings);
#endif // _di_f_serialize_un_simple_

/**
 * Identify string positions within a serialize string using the Simple serialize algorithm.
 *
 * The simple Serialize algorithm is akin to the PATH environment variable, example: PATH="/bin:/sbin:/usr/bin".
 *
 * After processing the above example, there would be the following positions:
 *   1) start = 0, stop = 3.
 *   2) start = 5, stop = 9.
 *   3) start = 11, stop = 18.
 *
 * @param serialize
 *   A serialize string to de-serialize.
 * @param locations
 *   The locations within the serialize string representing distinct separate strings.
 *
 * @return
 *   F_none on success.
 *   F_complete_not_utf_eos if end of sting is reached before a complete UTF-8 character can be processed.
 *   F_array_too_large (with error bit) if a buffer would exceed memory max length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_serialize_un_simple_map_
  extern f_status_t f_serialize_un_simple_map(const f_string_static_t serialize, f_string_ranges_t *locations);
#endif // _di_f_serialize_un_simple_map_

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
 * @param serialize
 *   A serialize string to de-serialize.
 * @param index
 *   An index position within the serialize string to get the deserialize positions of.
 * @param location
 *   A location within the serialize string representing the string at the given index.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success at end of string.
 *   F_data_not_eos if end of string reached before index was reached.
 *   F_complete_not_utf_eos (with error bit) if end of string is reached before a complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_serialize_un_simple_find_
  extern f_status_t f_serialize_un_simple_find(const f_string_static_t serialize, const f_array_length_t index, f_string_range_t *location);
#endif // _di_f_serialize_un_simple_find_

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
 * @param serialize
 *   A serialize string to de-serialize.
 * @param index
 *   An index position within the serialize string to get the deserialize positions of.
 * @param dynamic
 *   The unserialize string from the specified index.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success at end of string.
 *   F_data_not_eos if end of string reached before index was reached (dynamic->used is set to 0).
 *   F_complete_not_utf_eos (with error bit) if end of string is reached before a complete UTF-8 character can be processed.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_serialize_un_simple_get_
  extern f_status_t f_serialize_un_simple_get(const f_string_static_t serialize, const f_array_length_t index, f_string_dynamic_t *dynamic);
#endif // _di_f_serialize_un_simple_get_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_serialize_h
