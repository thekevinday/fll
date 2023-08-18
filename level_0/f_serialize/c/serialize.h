/**
 * FLL - Level 0
 *
 * Project: Serialize
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides string processing functionality for what is to be defined as a serialize string.
 * Serialized strings are strings that can hold multiple values in a single variable.
 * An example of serialize content is the PATH environment variable where ":" separates data.
 */
#ifndef _F_serialize_h
#define _F_serialize_h

// Libc includes.
#include <string.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>

// FLL-0 serialize includes.
#include <fll/level_0/serialize/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Deserialize the entire serialize string into multiple separate strings using the Simple serialize algorithm.
 *
 * The simple Serialize algorithm is akin to the PATH environment variable, example: PATH="/bin:/sbin:/usr/bin".
 *
 * After processing the above example, there would be strings derived from the following positions:
 *   1) start = 0, stop = 3.
 *   2) start = 5, stop = 9.
 *   3) start = 11, stop = 18.
 *
 * @param source
 *   A serialized string to deserialize.
 * @param destination
 *   An array of strings deserialize from the source string.
 *   The individual strings will be NULL terminated after destination.used on success.
 *   All deserialized values are appended to the destination.
 *
 * @return
 *   F_okay on success.
 *   F_complete_not_utf_eos if an incomplete UTF-8 character is found at the end of the source.
 *   F_data_not on success and source.used is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_append();
 *   Errors (with error bit) from: f_string_dynamics_increase_by();
 *
 * @see f_string_append()
 * @see f_string_dynamics_increase_by()
 */
#ifndef _di_f_serialize_from_simple_
  extern f_status_t f_serialize_from_simple(const f_string_static_t source, f_string_dynamics_t * const destination);
#endif // _di_f_serialize_from_simple_

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
 * @param source
 *   A serialized string to deserialize.
 * @param index
 *   The selected position within the serialize string to get the deserialize positions of.
 * @param destination
 *   The deserialized string from the specified index.
 *   This string is NULL terminated after destination.used on success.
 *
 * @return
 *   F_okay on success.
 *   F_okay_eos on success at end of string.
 *   F_data_not_eos if end of string reached before index was reached (dynamic->used is set to 0).
 *   F_data_not on success and source.used is 0.
 *
 *   F_complete_not_utf_eos (with error bit) if end of string is reached before a complete UTF-8 character can be processed.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_serialize_from_simple_select()
 * @see f_string_append()
 */
#ifndef _di_f_serialize_from_simple_get_
  extern f_status_t f_serialize_from_simple_get(const f_string_static_t source, const f_number_unsigned_t index, f_string_dynamic_t * const destination);
#endif // _di_f_serialize_from_simple_get_

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
 * @param source
 *   A serialized string to deserialize.
 * @param ranges
 *   The ranges within the serialize string representing distinct separate strings.
 *   All deserialized ranges are appended to the destination.
 *
 * @return
 *   F_okay on success.
 *   F_complete_not_utf_eos if an incomplete UTF-8 character is found at the end of the source.
 *   F_data_not on success and source.used is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_ranges_increase()
 *
 * @see f_string_ranges_increase()
 */
#ifndef _di_f_serialize_from_simple_range_
  extern f_status_t f_serialize_from_simple_range(const f_string_static_t source, f_string_ranges_t * const ranges);
#endif // _di_f_serialize_from_simple_range_

/**
 * Deserialize and select the address for a specific string using the Simple serialize algorithm.
 *
 * The simple serialize algorithm is akin to the PATH environment variable, example: PATH="/bin:/sbin:/usr/bin".
 *
 * After processing the above example, there would be the following positions, for the given index:
 *   1) with index = 0, start = 0, stop = 3.
 *   2) with index = 1, start = 5, stop = 9.
 *   3) with index = 2, start = 11, stop = 18.
 *
 * @param source
 *   A serialized string to deserialize.
 * @param index
 *   An index position within the serialize string to get the deserialize positions of.
 * @param range
 *   A range within the serialized string representing the string at the given index.
 *
 * @return
 *   F_okay on success.
 *   F_okay_eos on success at end of string.
 *   F_data_not on success and source.used is 0.
 *   F_data_not_eos if end of string reached before index was reached.
 *
 *   F_complete_not_utf_eos (with error bit) if end of string is reached before a complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_serialize_from_simple_select_
  extern f_status_t f_serialize_from_simple_select(const f_string_static_t source, const f_number_unsigned_t index, f_string_range_t * const range);
#endif // _di_f_serialize_from_simple_select_

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
 * @param source
 *   The string to append onto serialize.
 * @param destination
 *   The dynamic string that to store the serialized string.
 *   This string will be NULL terminated after destination.used on success.
 *   All serialized values are appended to the destination.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success and source.used is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_append();
 *   Errors (with error bit) from: f_string_dynamic_append_assure();
 *
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_append_assure()
 */
#ifndef _di_f_serialize_to_simple_
  extern f_status_t f_serialize_to_simple(const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_serialize_to_simple_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_serialize_h
