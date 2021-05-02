/**
 * FLL - Level 0
 *
 * Project: Serialize
 * API Version: 0.5
 * Licenses: lgplv2.1
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
 * Private implementation of f_serialize_un_simple_get().
 *
 * Intended to be shared to each of the different implementation variations.
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
 *
 *   F_complete_not_utf_eos (with error bit) if end of string is reached before a complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#if !defined(_di_f_serialize_un_simple_find_) || !defined(_di_f_serialize_un_simple_get_)
  extern f_status_t private_f_serialize_un_simple_find(const f_string_static_t serialize, const f_array_length_t index, f_string_range_t *location) f_attribute_visibility_internal;
#endif // !defined(_di_f_serialize_un_simple_find_) || !defined(_di_f_serialize_un_simple_get_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_serialize_h
