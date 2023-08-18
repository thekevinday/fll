/**
 * FLL - Level 0
 *
 * Project: Serialize
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_serialize_h
#define _PRIVATE_F_serialize_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of f_serialize_from_simple_get().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   A serialized string to de-serialize.
 * @param index
 *   The selected position within the serialize string to get the deserialize positions of.
 * @param range
 *   A range within the serialize string representing the string at the given index.
 *
 * @return
 *   F_okay on success.
 *   F_okay_eos on success at end of string.
 *   F_data_not_eos if end of string reached before index was reached.
 *
 *   F_complete_not_utf_eos (with error bit) if end of string is reached before a complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#if !defined(_di_f_serialize_from_simple_get_) || !defined(_di_f_serialize_from_simple_select_)
  extern f_status_t private_f_serialize_from_simple_select(const f_string_static_t source, const f_number_unsigned_t index, f_string_range_t * const range) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_serialize_from_simple_get_) || !defined(_di_f_serialize_from_simple_select_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_serialize_h
