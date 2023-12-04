/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines dynamic string data.
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_string_dynamic_h
#define _F_string_dynamic_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A string that supports contains a size attribute to handle dynamic allocations and deallocations.
 *
 * Save the string size along with the string, so that strlen(..) commands can be avoided as much as possible.
 *
 * This is a sub-type of f_string_static_t, allowing it to be passed into any f_string_static_t type.
 *
 * The size should only be set to 0 when the string is not allocated (and therefore deallocation attempts must not be made).
 * This is necessary for the cases where f_string_static_t is used as a f_string_dynamic_t.
 *
 * string: The string.
 * size:   Total amount of allocated space.
 * used:   Total number of allocated spaces used.
 */
#ifndef _di_f_string_dynamic_t_
  typedef f_string_static_t f_string_dynamic_t;

  #define f_string_dynamic_t_initialize f_string_static_t_initialize

  #define macro_f_string_dynamic_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_string_dynamic_t_initialize_2(array, length) { array, length, length }

  #define macro_f_string_dynamic_t_clear(dynamic) macro_f_string_static_t_clear(dynamic)
#endif // _di_f_string_dynamic_t_

/**
 * Append the source string onto the destination.
 *
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_append_
  extern f_status_t f_string_dynamic_append(const f_string_dynamic_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_append_

/**
 * Append the source string onto the destination only if the string is not already at the end.
 *
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_append_assure_
  extern f_status_t f_string_dynamic_append_assure(const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_append_assure_

/**
 * Append the source string onto the destination only if the string is not already at the end.
 *
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_append_assure_nulless_
  extern f_status_t f_string_dynamic_append_assure_nulless(const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_append_assure_nulless_

/**
 * Append the source string onto the destination.
 *
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_append_nulless_
  extern f_status_t f_string_dynamic_append_nulless(const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_append_nulless_

/**
 * Append the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_mash_
  extern f_status_t f_string_dynamic_mash(const f_string_static_t glue, const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_mash_

/**
 * Append the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * Skips over NULL characters from glue and source when appending.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_mash_nulless_
  extern f_status_t f_string_dynamic_mash_nulless(const f_string_static_t glue, const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_mash_nulless_

/**
 * Prepend the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_mish_
  extern f_status_t f_string_dynamic_mish(const f_string_static_t glue, const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_mish_

/**
 * Prepend the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * Skips over NULL characters from glue and source when appending.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_mish_nulless_
  extern f_status_t f_string_dynamic_mish_nulless(const f_string_static_t glue, const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_mish_nulless_

/**
 * Append the source string onto the destination, but restricted to the given range.
 *
 * If range.stop is on or after source.used, then source.used - 1 is used as the stopping point.
 *
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *   F_data_not_eos if range.start >= source.used.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_append_
  extern f_status_t f_string_dynamic_partial_append(const f_string_static_t source, const f_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_append_

/**
 * Append the source string onto the destination only if the string is not already at the end and restricted to the given range.
 *
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *   F_data_not_eos if range.start >= source.used.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_append_assure_
  extern f_status_t f_string_dynamic_partial_append_assure(const f_string_static_t source, const f_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_append_assure_

/**
 * Append the source string onto the destination only if the string is not already at the end and restricted to the given range.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *   F_data_not_eos if range.start >= source.used.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_append_assure_nulless_
  extern f_status_t f_string_dynamic_partial_append_assure_nulless(const f_string_static_t source, const f_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_append_assure_nulless_

/**
 * Append the source string onto the destination, but restricted to the given range.
 *
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *   F_data_not_eos if range.start >= source.used.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_append_nulless_
  extern f_status_t f_string_dynamic_partial_append_nulless(const f_string_static_t source, const f_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_append_nulless_

/**
 * Append the source string onto the destination with the glue in between, but restricted to the given range.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *   F_data_not_eos if range.start >= source.used.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_mash_
  extern f_status_t f_string_dynamic_partial_mash(const f_string_static_t glue, const f_string_static_t source, const f_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_mash_

/**
 * Append the source string onto the destination with the glue in between, but restricted to the given range.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * Skips over NULL characters from glue and source when appending.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *   F_data_not_eos if range.start >= source.used.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_mash_nulless_
  extern f_status_t f_string_dynamic_partial_mash_nulless(const f_string_static_t glue, const f_string_static_t source, const f_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_mash_nulless_

/**
 * Prepend the source string onto the destination with the glue in between, but restricted to the given range.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *   F_data_not_eos if range.start >= source.used.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_mish_
  extern f_status_t f_string_dynamic_partial_mish(const f_string_static_t glue, const f_string_static_t source, const f_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_mish_

/**
 * Prepend the source string onto the destination with the glue in between, but restricted to the given range.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * Skips over NULL characters from glue and source when appending.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *   F_data_not_eos if range.start >= source.used.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_mish_nulless_
  extern f_status_t f_string_dynamic_partial_mish_nulless(const f_string_static_t glue, const f_string_static_t source, const f_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_mish_nulless_

/**
 * Prepend the source string onto the destination, but restricted to the given range.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * @param source
 *   The source string to prepend.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *   F_data_not_eos if range.start >= source.used.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_prepend_
  extern f_status_t f_string_dynamic_partial_prepend(const f_string_static_t source, const f_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_prepend_

/**
 * Prepend the source string onto the destination only if the string is not already at the beginning and restricted to the given range.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * @param source
 *   The source string to prepend.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *   F_data_not_eos if range.start >= source.used.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_prepend_assure_
  extern f_status_t f_string_dynamic_partial_prepend_assure(const f_string_static_t source, const f_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_prepend_assure_

/**
 * Prepend the source string onto the destination only if the string is not already at the beginning and restricted to the given range.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * @param source
 *   The source string to prepend.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *   F_data_not_eos if range.start >= source.used.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_prepend_assure_nulless_
  extern f_status_t f_string_dynamic_partial_prepend_assure_nulless(const f_string_static_t source, const f_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_prepend_assure_nulless_

/**
 * Prepend the source string onto the destination, but restricted to the given range.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * @param source
 *   The source string to prepend.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *   F_data_not_eos if range.start >= source.used.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_partial_prepend_nulless_
  extern f_status_t f_string_dynamic_partial_prepend_nulless(const f_string_static_t source, const f_range_t range, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_partial_prepend_nulless_

/**
 * Prepend the source string onto the destination.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * @param source
 *   The source string to prepend.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_prepend_
  extern f_status_t f_string_dynamic_prepend(const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_prepend_

/**
 * Prepend the source string onto the destination only if the string is not already at the beginning.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * @param source
 *   The source string to prepend.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_prepend_assure_
  extern f_status_t f_string_dynamic_prepend_assure(const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_prepend_assure_

/**
 * Prepend the source string onto the destination only if the string is not already at the beginning.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * @param source
 *   The source string to prepend.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_prepend_assure_nulless_
  extern f_status_t f_string_dynamic_prepend_assure_nulless(const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_prepend_assure_nulless_

/**
 * Prepend the source string onto the destination.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * @param source
 *   The source string to prepend.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not if source length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_prepend_nulless_
  extern f_status_t f_string_dynamic_prepend_nulless(const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_prepend_nulless_

/**
 * Seek the buffer location forward until EOL is reached.
 *
 * @param structure
 *   The buffer to traverse.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_okay on success.
 *   F_okay_eos on success, but stopped at end of string.
 *   F_okay_stop on success, but stopped at end of range.
 *   F_data_not on success, but there was no string data to seek.
 *   F_data_not_stop on success, but the range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_seek_line_
  extern f_status_t f_string_dynamic_seek_line(const f_string_static_t structure, f_range_t * const range);
#endif // _di_f_string_dynamic_seek_line_

/**
 * Seek the buffer location forward until the character (1-byte wide) or EOL is reached.
 *
 * @param structure
 *   The buffer to traverse.
 * @param seek_to_this
 *   A single-width character representing a character to seek to.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_okay on success.
 *   F_okay_eos on success, but stopped at end of string.
 *   F_okay_stop on success, but stopped at end of range.
 *   F_data_not on success, but there was no string data to seek.
 *   F_data_not_stop on success, but the range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_seek_line_to_
  extern f_status_t f_string_dynamic_seek_line_to(const f_string_static_t structure, const f_char_t seek_to_this, f_range_t * const range);
#endif // _di_f_string_dynamic_seek_line_to_

/**
 * Seek the buffer location forward until the character (1-byte wide) is reached.
 *
 * @param structure
 *   The buffer to traverse.
 * @param seek_to_this
 *   A single-width character representing a character to seek to.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_okay on success.
 *   F_okay_eos on success, but stopped at end of string.
 *   F_okay_stop on success, but stopped at end of range.
 *   F_data_not on success, but there was no string data to seek.
 *   F_data_not_stop on success, but the range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_seek_to_
  extern f_status_t f_string_dynamic_seek_to(const f_string_static_t structure, const f_char_t seek_to_this, f_range_t * const range);
#endif // _di_f_string_dynamic_seek_to_

/**
 * Guarantee that an end of string (NULL) exists at the end of the string.
 *
 * This is intended to be used for anything requiring NULL terminated strings.
 * This will reallocate more space if necessary.
 *
 * If destination size is 0, then it will be reallocated and have the NULL assigned at index 0.
 *
 * @param destination
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if string is too large to fit into the buffer.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_terminate_
  extern f_status_t f_string_dynamic_terminate(f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_terminate_

/**
 * Guarantee that an end of string (NULL) exists at the end of the string.
 *
 * This ensures that the terminating NULL not only exists but is not counted in destination.used.
 *
 * This is intended to be used for anything requiring NULL terminated strings whose used length cannot be counted.
 * This will reallocate more space if necessary.
 *
 * If destination size is 0, then it will be reallocated and have the NULL assigned at index 0.
 *
 * @param destination
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if string is too large to fit into the buffer.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_terminate_after_
  extern f_status_t f_string_dynamic_terminate_after(f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_terminate_after_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_dynamic_h
