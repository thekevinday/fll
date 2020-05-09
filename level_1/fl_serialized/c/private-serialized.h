/**
 * FLL - Level 1
 *
 * Project: Serialized
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_FL_serialized_h
#define _PRIVATE_FL_serialized_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of fl_unserialize_simple_get().
 *
 * Intended to be shared to each of the different implementation variations.
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
#if !defined(_di_fl_unserialize_simple_find_) || !defined(_di_fl_unserialize_simple_get_)
  extern f_return_status private_fl_unserialize_simple_find(const f_string_static serialized, const f_array_length index, f_string_range *location) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_unserialize_simple_find_) || !defined(_di_fl_unserialize_simple_get_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_serialized_h
