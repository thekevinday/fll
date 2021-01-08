/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides string capabilities.
 *
 * It is highly recommended that all string arrays are set to a max size of f_string_length_t_size.
 * Any calculations against the length (aka: string.used) can always perform (A < B) operators such that the B is f_string_length_t_size + 1 without integer overflow.
 */
#ifndef _F_string_h
#define _F_string_h

// libc includes
#include <string.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/type.h>

// fll-0 string includes
#include <level_0/string-common.h>
#include <level_0/string_dynamic.h>
#include <level_0/string_map.h>
#include <level_0/string_quantity.h>
#include <level_0/string_range.h>
#include <level_0/string_triple.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Append the source string onto the destination.
 *
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_append_
  extern f_status_t f_string_append(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_f_string_append_

/**
 * Append the source string onto the destination, but only if the string is not already at the end.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_append_assure_
  extern f_status_t f_string_append_assure(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_f_string_append_assure_

/**
 * Append the source string onto the destination, but only if the string is not already at the end.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_append_assure_nulless_
  extern f_status_t f_string_append_assure_nulless(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_f_string_append_assure_nulless_

/**
 * Append the source string onto the destination.
 *
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_append_nulless_
  extern f_status_t f_string_append_nulless(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_f_string_append_nulless_

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
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_append_
  extern f_status_t f_string_dynamic_append(const f_string_static_t source, f_string_dynamic_t *destination);
#endif // _di_f_string_dynamic_append_

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
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_append_assure_
  extern f_status_t f_string_dynamic_append_assure(const f_string_static_t source, f_string_dynamic_t *destination);
#endif // _di_f_string_dynamic_append_assure_

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
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_append_assure_nulless_
  extern f_status_t f_string_dynamic_append_assure_nulless(const f_string_static_t source, f_string_dynamic_t *destination);
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
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_append_nulless_
  extern f_status_t f_string_dynamic_append_nulless(const f_string_static_t source, f_string_dynamic_t *destination);
#endif // _di_f_string_dynamic_append_nulless_

/**
 * Append the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_mash_
  extern f_status_t f_string_dynamic_mash(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, f_string_dynamic_t *destination);
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
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_mash_nulless_
  extern f_status_t f_string_dynamic_mash_nulless(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, f_string_dynamic_t *destination);
#endif // _di_f_string_dynamic_mash_nulless_

/**
 * Prepend the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_mish_
  extern f_status_t f_string_dynamic_mish(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, f_string_dynamic_t *destination);
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
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_mish_nulless_
  extern f_status_t f_string_dynamic_mish_nulless(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, f_string_dynamic_t *destination);
#endif // _di_f_string_dynamic_mish_nulless_

/**
 * Append the source string onto the destination, but restricted to the given range.
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
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_partial_append_
  extern f_status_t f_string_dynamic_partial_append(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
#endif // _di_f_string_dynamic_partial_append_

/**
 * Append the source string onto the destination, but only if the string is not already at the end and restricted to the given range
 *
 * This ignores NULL characters when comparing both the source and the destination.
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
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_partial_append_assure_
  extern f_status_t f_string_dynamic_partial_append_assure(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
#endif // _di_f_string_dynamic_partial_append_assure_

/**
 * Append the source string onto the destination, but only if the string is not already at the end and restricted to the given range
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
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_partial_append_assure_nulless_
  extern f_status_t f_string_dynamic_partial_append_assure_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
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
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_partial_append_nulless_
  extern f_status_t f_string_dynamic_partial_append_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
#endif // _di_f_string_dynamic_partial_append_nulless_

/**
 * Append the source string onto the destination with the glue in between, but restricted to the given range.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_partial_mash_
  extern f_status_t f_string_dynamic_partial_mash(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
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
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_partial_mash_nulless_
  extern f_status_t f_string_dynamic_partial_mash_nulless(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
#endif // _di_f_string_dynamic_partial_mash_nulless_

/**
 * Prepend the source string onto the destination with the glue in between, but restricted to the given range.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_partial_mish_
  extern f_status_t f_string_dynamic_partial_mish(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
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
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param range
 *   A range within the source to restrict the copy from.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_partial_mish_nulless_
  extern f_status_t f_string_dynamic_partial_mish_nulless(const f_string_t glue, const f_string_length_t glue_length, const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
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
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_partial_prepend_
  extern f_status_t f_string_dynamic_partial_prepend(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
#endif // _di_f_string_dynamic_partial_prepend_

/**
 * Prepend the source string onto the destination, but only if the string is not already at the end and restricted to the given range
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
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_partial_prepend_assure_
  extern f_status_t f_string_dynamic_partial_prepend_assure(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
#endif // _di_f_string_dynamic_partial_prepend_assure_

/**
 * Prepend the source string onto the destination, but only if the string is not already at the end and restricted to the given range
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
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_partial_prepend_assure_nulless_
  extern f_status_t f_string_dynamic_partial_prepend_assure_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
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
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_partial_prepend_nulless_
  extern f_status_t f_string_dynamic_partial_prepend_nulless(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination);
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
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_prepend_
  extern f_status_t f_string_dynamic_prepend(const f_string_static_t source, f_string_dynamic_t *destination);
#endif // _di_f_string_dynamic_prepend_

/**
 * Prepend the source string onto the destination, but only if the string is not already at the beginning.
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
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_prepend_assure_
  extern f_status_t f_string_dynamic_prepend_assure(const f_string_static_t source, f_string_dynamic_t *destination);
#endif // _di_f_string_dynamic_prepend_assure_

/**
 * Prepend the source string onto the destination, but only if the string is not already at the beginning.
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
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_prepend_assure_nulless_
  extern f_status_t f_string_dynamic_prepend_assure_nulless(const f_string_static_t source, f_string_dynamic_t *destination);
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
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_dynamic_prepend_nulless_
  extern f_status_t f_string_dynamic_prepend_nulless(const f_string_static_t source, f_string_dynamic_t *destination);
#endif // _di_f_string_dynamic_prepend_nulless_

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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if string is too large to fit into the buffer.
 */
#ifndef _di_f_string_dynamic_terminate_
  extern f_status_t f_string_dynamic_terminate(f_string_dynamic_t *destination);
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if string is too large to fit into the buffer.
 */
#ifndef _di_f_string_dynamic_terminate_after_
  extern f_status_t f_string_dynamic_terminate_after(f_string_dynamic_t *destination);
#endif // _di_f_string_dynamic_terminate_after_

/**
 * Append the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_mash_
  extern f_status_t f_string_mash(const f_string_t glue, const f_string_length_t glue_length, const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_f_string_mash_

/**
 * Append the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * Skips over NULL characters from glue and source when appending.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_mash_nulless_
  extern f_status_t f_string_mash_nulless(const f_string_t glue, const f_string_length_t glue_length, const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_f_string_mash_nulless_

/**
 * Prepend the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_mish_
  extern f_status_t f_string_mish(const f_string_t glue, const f_string_length_t glue_length, const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_f_string_mish_

/**
 * Prepend the source string onto the destination with the glue in between.
 *
 * If the destination string is empty, then no glue is appended.
 *
 * Skips over NULL characters from glue and source when appending.
 *
 * @param glue
 *   A string to append between the source and destination, such as a space: ' '.
 * @param glue_length
 *   The number of bytes the glue takes up.
 * @param source
 *   The source string to append.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source and glue are appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_mish_nulless_
  extern f_status_t f_string_mish_nulless(const f_string_t glue, const f_string_length_t glue_length, const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_f_string_mish_nulless_

/**
 * Prepend the source string onto the destination.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * @param source
 *   The source string to prepend.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_prepend_
  extern f_status_t f_string_prepend(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_f_string_prepend_

/**
 * Prepend the source string onto the destination, but only if the string is not already at the beginning.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 *
 * @param source
 *   The source string to prepend.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_prepend_assure_
  extern f_status_t f_string_prepend_assure(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_f_string_prepend_assure_

/**
 * Prepend the source string onto the destination, but only if the string is not already at the beginning.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 * Skips over NULL characters from source when prepending.
 *
 * @param source
 *   The source string to prepend.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_prepend_assure_nulless_
  extern f_status_t f_string_prepend_assure_nulless(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_f_string_prepend_assure_nulless_

/**
 * Prepend the source string onto the destination, but only if the string is not already at the beginning.
 *
 * Prepend operations require memory move operations and are therefore likely more expensive than append operations.
 *
 * This ignores NULL characters when comparing both the source and the destination.
 * Skips over NULL characters from source when prepending.
 *
 * @param source
 *   The source string to prepend.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The destination string the source is prepended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_f_string_prepend_nulless_
  extern f_status_t f_string_prepend_nulless(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_f_string_prepend_nulless_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_h
