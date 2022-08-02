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
 * It is recommended that f_string_static_t are not otherwise casted into f_string_dynamic_t to avoid potential memory allocation issues.
 *
 * string: The string.
 * size:   Total amount of allocated space.
 * used:   Total number of allocated spaces used.
 */
#ifndef _di_f_string_dynamic_t_
  typedef f_string_static_t f_string_dynamic_t;

  #define f_string_dynamic_t_initialize f_string_static_t_initialize

  #define macro_f_string_dynamic_t_initialize(array, size, used) { array, size, used }
  #define macro_f_string_dynamic_t_initialize2(array, length) { array, length, length }

  #define macro_f_string_dynamic_t_clear(dynamic) macro_f_string_static_t_clear(dynamic)

  #define macro_f_string_dynamic_t_resize(status, dynamic, length) status = f_string_dynamic_resize(length, &dynamic);
  #define macro_f_string_dynamic_t_adjust(status, dynamic, length) status = f_string_dynamic_adjust(length, &dynamic);

  #define macro_f_string_dynamic_t_delete_simple(dynamic)  f_string_dynamic_resize(0, &dynamic);
  #define macro_f_string_dynamic_t_destroy_simple(dynamic) f_string_dynamic_adjust(0, &dynamic);

  #define macro_f_string_dynamic_t_increase(status, step, dynamic)      status = f_string_dynamic_increase(step, &dynamic);
  #define macro_f_string_dynamic_t_increase_by(status, dynamic, amount) status = f_string_dynamic_increase_by(amount, &dynamic);
  #define macro_f_string_dynamic_t_decrease_by(status, dynamic, amount) status = f_string_dynamic_decrease_by(amount, &dynamic);
  #define macro_f_string_dynamic_t_decimate_by(status, dynamic, amount) status = f_string_dynamic_decimate_by(amount, &dynamic);
#endif // _di_f_string_dynamic_t_

/**
 * An array of dynamic dynamics.
 *
 * array: The array of dynamic dynamics.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_string_dynamics_t_
  typedef f_string_statics_t f_string_dynamics_t;

  #define f_string_dynamics_t_initialize f_string_statics_t_initialize

  #define macro_f_string_dynamics_t_initialize(array, size, used) { array, size, used }
  #define macro_f_string_dynamics_t_initialize2(array, length) { array, length, length }

  #define macro_f_string_dynamics_t_clear(dynamics) macro_f_string_statics_t_clear(dynamics)

  #define macro_f_string_dynamics_t_resize(status, dynamics, length) status = f_string_dynamics_resize(length, &dynamics);
  #define macro_f_string_dynamics_t_adjust(status, dynamics, length) status = f_string_dynamics_adjust(length, &dynamics);

  #define macro_f_string_dynamics_t_delete_simple(dynamics)  f_string_dynamics_resize(0, &dynamics);
  #define macro_f_string_dynamics_t_destroy_simple(dynamics) f_string_dynamics_adjust(0, &dynamics);

  #define macro_f_string_dynamics_t_increase(status, step, dynamics)      status = f_string_dynamics_increase(step, &dynamics);
  #define macro_f_string_dynamics_t_increase_by(status, dynamics, amount) status = f_string_dynamics_increase_by(amount, &dynamics);
  #define macro_f_string_dynamics_t_decrease_by(status, dynamics, amount) status = f_string_dynamics_decrease_by(amount, &dynamics);
  #define macro_f_string_dynamics_t_decimate_by(status, dynamics, amount) status = f_string_dynamics_decimate_by(amount, &dynamics);
#endif // _di_f_string_dynamics_t_

/**
 * An array of dynamic dynamicss.
 *
 * array: The array of dynamic dynamicss.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_string_dynamicss_t_
  typedef f_string_staticss_t f_string_dynamicss_t;

  #define f_string_dynamicss_t_initialize f_string_staticss_t_initialize

  #define macro_f_string_dynamicss_t_initialize(array, size, used) { array, size, used }
  #define macro_f_string_dynamicss_t_initialize2(array, length) { array, length, length }

  #define macro_f_string_dynamicss_t_clear(dynamicss) macro_f_string_staticss_t_clear(dynamicss)

  #define macro_f_string_dynamicss_t_resize(status, dynamicss, length) status = f_string_dynamicss_resize(length, &dynamicss);
  #define macro_f_string_dynamicss_t_adjust(status, dynamicss, length) status = f_string_dynamicss_adjust(length, &dynamicss);

  #define macro_f_string_dynamicss_t_delete_simple(dynamicss)  f_string_dynamicss_resize(0, &dynamicss);
  #define macro_f_string_dynamicss_t_destroy_simple(dynamicss) f_string_dynamicss_adjust(0, &dynamicss);

  #define macro_f_string_dynamicss_t_increase(status, step, dynamicss)      status = f_string_dynamicss_increase(step, &dynamicss);
  #define macro_f_string_dynamicss_t_increase_by(status, dynamicss, amount) status = f_string_dynamicss_increase_by(amount, &dynamicss);
  #define macro_f_string_dynamicss_t_decrease_by(status, dynamicss, amount) status = f_string_dynamicss_decrease_by(amount, &dynamicss);
  #define macro_f_string_dynamicss_t_decimate_by(status, dynamicss, amount) status = f_string_dynamicss_decimate_by(amount, &dynamicss);
#endif // _di_f_string_dynamicss_t_

/**
 * Resize the dynamic string.
 *
 * @param length
 *   The new size to use.
 * @param dynamic
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_string_dynamic_adjust_
  extern f_status_t f_string_dynamic_adjust(const f_array_length_t length, f_string_dynamic_t * const dynamic);
#endif // _di_f_string_dynamic_adjust_

/**
 * Append the source string onto the destination.
 *
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
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
 *   F_none on success.
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
 *   F_none on success.
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
 *   F_none on success.
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
 * Resize the dynamic string to a smaller size.
 *
 * This will resize making the string smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param dynamic
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_decimate_by_
  extern f_status_t f_string_dynamic_decimate_by(const f_array_length_t amount, f_string_dynamic_t * const dynamic);
#endif // _di_f_string_dynamic_decimate_by_

/**
 * Resize the dynamic string to a smaller size.
 *
 * This will resize making the string smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param dynamic
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_decrease_by_
  extern f_status_t f_string_dynamic_decrease_by(const f_array_length_t amount, f_string_dynamic_t * const dynamic);
#endif // _di_f_string_dynamic_decrease_by_

/**
 * Resize the dynamic string to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param dynamic
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size) (or step is 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_increase_
  extern f_status_t f_string_dynamic_increase(const f_array_length_t step, f_string_dynamic_t * const dynamic);
#endif // _di_f_string_dynamic_increase_

/**
 * Resize the dynamic string to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param dynamic
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_increase_by_
  extern f_status_t f_string_dynamic_increase_by(const f_array_length_t amount, f_string_dynamic_t * const dynamic);
#endif // _di_f_string_dynamic_increase_by_

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
 *   F_none on success.
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
 *   F_none on success.
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
 *   F_none on success.
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
 *   F_none on success.
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
 *   F_none on success.
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
  extern f_status_t f_string_dynamic_partial_append(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
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
 *   F_none on success.
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
  extern f_status_t f_string_dynamic_partial_append_assure(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
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
 *   F_none on success.
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
  extern f_status_t f_string_dynamic_partial_append_assure_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
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
 *   F_none on success.
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
  extern f_status_t f_string_dynamic_partial_append_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
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
 *   F_none on success.
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
  extern f_status_t f_string_dynamic_partial_mash(const f_string_static_t glue, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
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
 *   F_none on success.
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
  extern f_status_t f_string_dynamic_partial_mash_nulless(const f_string_static_t glue, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
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
 *   F_none on success.
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
  extern f_status_t f_string_dynamic_partial_mish(const f_string_static_t glue, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
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
 *   F_none on success.
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
  extern f_status_t f_string_dynamic_partial_mish_nulless(const f_string_static_t glue, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
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
 *   F_none on success.
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
  extern f_status_t f_string_dynamic_partial_prepend(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
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
 *   F_none on success.
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
  extern f_status_t f_string_dynamic_partial_prepend_assure(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
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
 *   F_none on success.
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
  extern f_status_t f_string_dynamic_partial_prepend_assure_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
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
 *   F_none on success.
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
  extern f_status_t f_string_dynamic_partial_prepend_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t * const destination);
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
 *   F_none on success.
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
 *   F_none on success.
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
 *   F_none on success.
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
 *   F_none on success.
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
 * Resize the dynamic string.
 *
 * @param length
 *   The new size to use.
 * @param buffer
 *   The string to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_resize_
  extern f_status_t f_string_dynamic_resize(const f_array_length_t length, f_string_dynamic_t * const buffer);
#endif // _di_f_string_dynamic_resize_

/**
 * Seek the buffer location forward until EOL is reached.
 *
 * @param buffer
 *   The buffer to traverse.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success, but stopped at end of string.
 *   F_none_stop on success, but stopped at end of range.
 *   F_data_not on success, but there was no string data to seek.
 *   F_data_not_stop on success, but the range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_seek_line_
  extern f_status_t f_string_dynamic_seek_line(const f_string_static_t buffer, f_string_range_t * const range);
#endif // _di_f_string_dynamic_seek_line_

/**
 * Seek the buffer location forward until the character (1-byte wide) or EOL is reached.
 *
 * @param buffer
 *   The buffer to traverse.
 * @param seek_to_this
 *   A single-width character representing a character to seek to.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success, but stopped at end of string.
 *   F_none_stop on success, but stopped at end of range.
 *   F_data_not on success, but there was no string data to seek.
 *   F_data_not_stop on success, but the range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_seek_line_to_
  extern f_status_t f_string_dynamic_seek_line_to(const f_string_static_t buffer, const f_char_t seek_to_this, f_string_range_t * const range);
#endif // _di_f_string_dynamic_seek_line_to_

/**
 * Seek the buffer location forward until the character (1-byte wide) is reached.
 *
 * @param buffer
 *   The buffer to traverse.
 * @param seek_to_this
 *   A single-width character representing a character to seek to.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success, but stopped at end of string.
 *   F_none_stop on success, but stopped at end of range.
 *   F_data_not on success, but there was no string data to seek.
 *   F_data_not_stop on success, but the range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_seek_to_
  extern f_status_t f_string_dynamic_seek_to(const f_string_static_t buffer, const f_char_t seek_to_this, f_string_range_t * const range);
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
 *   F_none on success.
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
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if string is too large to fit into the buffer.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamic_terminate_after_
  extern f_status_t f_string_dynamic_terminate_after(f_string_dynamic_t * const destination);
#endif // _di_f_string_dynamic_terminate_after_

/**
 * Resize the dynamic string array.
 *
 * @param length
 *   The new size to use.
 * @param dynamics
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_string_dynamics_adjust_
  extern f_status_t f_string_dynamics_adjust(const f_array_length_t length, f_string_dynamics_t * const dynamics);
#endif // _di_f_string_dynamics_adjust_

/**
 * Append the single source string onto the destination.
 *
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination strings the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamics_append_
  extern f_status_t f_string_dynamics_append(const f_string_dynamic_t source, f_string_dynamics_t * const destination);
#endif // _di_f_string_dynamics_append_

/**
 * Append the source strings onto the destination.
 *
 * @param source
 *   The source strings to append.
 * @param destination
 *   The destination strings the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamics_append_all_
  extern f_status_t f_string_dynamics_append_all(const f_string_dynamics_t source, f_string_dynamics_t * const destination);
#endif // _di_f_string_dynamics_append_all_

/**
 * Resize the dynamic string array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param dynamics
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (size == 0) (or amount is 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamics_decimate_by_
  extern f_status_t f_string_dynamics_decimate_by(const f_array_length_t amount, f_string_dynamics_t * const dynamics);
#endif // _di_f_string_dynamics_decimate_by_

/**
 * Resize the dynamic string array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param dynamics
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (size == 0) (or amount is 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamics_decrease_by_
  extern f_status_t f_string_dynamics_decrease_by(const f_array_length_t amount, f_string_dynamics_t * const dynamics);
#endif // _di_f_string_dynamics_decrease_by_

/**
 * Increase the size of the dynamic string array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param dynamics
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamics_increase_
  extern f_status_t f_string_dynamics_increase(const f_array_length_t step, f_string_dynamics_t * const dynamics);
#endif // _di_f_string_dynamics_increase_

/**
 * Resize the dynamic string array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param dynamics
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamics_increase_by_
  extern f_status_t f_string_dynamics_increase_by(const f_array_length_t amount, f_string_dynamics_t * const dynamics);
#endif // _di_f_string_dynamics_increase_by_

/**
 * Resize the dynamic string array.
 *
 * @param length
 *   The new size to use.
 * @param dynamics
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamics_resize_
  extern f_status_t f_string_dynamics_resize(const f_array_length_t length, f_string_dynamics_t * const dynamics);
#endif // _di_f_string_dynamics_resize_

/**
 * Resize the dynamics string array.
 *
 * @param length
 *   The new size to use.
 * @param dynamicss
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_string_dynamicss_adjust_
  extern f_status_t f_string_dynamicss_adjust(const f_array_length_t length, f_string_dynamicss_t * const dynamicss);
#endif // _di_f_string_dynamicss_adjust_

/**
 * Append the single source string onto the destination.
 *
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination strings the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamicss_append_
  extern f_status_t f_string_dynamicss_append(const f_string_dynamics_t source, f_string_dynamicss_t * const destination);
#endif // _di_f_string_dynamicss_append_

/**
 * Append the source strings onto the destination.
 *
 * @param source
 *   The source strings to append.
 * @param destination
 *   The destination strings the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamicss_append_all_
  extern f_status_t f_string_dynamicss_append_all(const f_string_dynamicss_t source, f_string_dynamicss_t * const destination);
#endif // _di_f_string_dynamicss_append_all_

/**
 * Resize the dynamics string array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param dynamicss
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (size == 0) (or amount is 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamicss_decimate_by_
  extern f_status_t f_string_dynamicss_decimate_by(const f_array_length_t amount, f_string_dynamicss_t * const dynamicss);
#endif // _di_f_string_dynamicss_decimate_by_

/**
 * Resize the dynamics string array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param dynamicss
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (size == 0) (or amount is 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamicss_decrease_by_
  extern f_status_t f_string_dynamicss_decrease_by(const f_array_length_t amount, f_string_dynamicss_t * const dynamicss);
#endif // _di_f_string_dynamicss_decrease_by_

/**
 * Increase the size of the dynamics string array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param dynamicss
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamicss_increase_
  extern f_status_t f_string_dynamicss_increase(const f_array_length_t step, f_string_dynamicss_t * const dynamicss);
#endif // _di_f_string_dynamicss_increase_

/**
 * Resize the dynamics string array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param dynamicss
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamicss_increase_by_
  extern f_status_t f_string_dynamicss_increase_by(const f_array_length_t amount, f_string_dynamicss_t * const dynamicss);
#endif // _di_f_string_dynamicss_increase_by_

/**
 * Resize the dynamics string array.
 *
 * @param length
 *   The new size to use.
 * @param dynamicss
 *   The array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_dynamicss_resize_
  extern f_status_t f_string_dynamicss_resize(const f_array_length_t length, f_string_dynamicss_t * const dynamicss);
#endif // _di_f_string_dynamicss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_dynamic_h
