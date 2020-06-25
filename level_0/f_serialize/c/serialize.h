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
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/utf.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_serialize_splitters_
  #define f_serialize_simple_splitter     ':'
  #define f_serialize_delimited_splitter  '\''
  #define f_serialize_delimited_delimiter '\\'

  #define f_serialize_simple_splitter_string     ":"
  #define f_serialize_delimited_splitter_string  "'"
  #define f_serialize_delimited_delimiter_string "\\"
#endif // _di_f_serialize_splitters_

#ifndef _di_f_serialize_default_allocation_step_
  // provide a UTF-8 friendly allocation step.
  #define f_serialize_default_allocation_step 4
#endif // _di_f_serialize_default_allocation_step_

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
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_serialize_simple_
  extern f_return_status f_serialize_simple(const f_string_static value, f_string_dynamic *serialize);
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
 *   F_incomplete_utf_eos if end of sting is reached before a complete UTF-8 character can be processed.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_serialize_un_simple_
  extern f_return_status f_serialize_un_simple(const f_string_static serialize, f_string_dynamics *strings);
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
 *   F_incomplete_utf_eos if end of sting is reached before a complete UTF-8 character can be processed.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_serialize_un_simple_map_
  extern f_return_status f_serialize_un_simple_map(const f_string_static serialize, f_string_ranges *locations);
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
 *   F_incomplete_utf_eos (with error bit) if end of string is reached before a complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_serialize_un_simple_find_
  extern f_return_status f_serialize_un_simple_find(const f_string_static serialize, const f_array_length index, f_string_range *location);
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
 *   F_incomplete_utf_eos (with error bit) if end of string is reached before a complete UTF-8 character can be processed.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_serialize_un_simple_get_
  extern f_return_status f_serialize_un_simple_get(const f_string_static serialize, const f_array_length index, f_string_dynamic *dynamic);
#endif // _di_f_serialize_un_simple_get_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_serialize_h
