/**
 * FLL - Level 0
 *
 * Project: Color
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_color_h
#define _PRIVATE_F_color_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of f_color_save_1().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param format
 *   The color format parts.
 * @param color1
 *   A color to assign.
 * @param buffer
 *   The string to save the colors to.
 *   The buffer will become NULL terminated after the appended string length.
 *
 * @return
 *   F_okay on success.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by()
 *
 * @see memcpy()
 *
 * @see f_memory_array_increase_by()
 *
 * @see f_color_load_context()
 * @see f_color_save_1()
 */
#if !defined(_di_f_color_load_context_) || !defined(_di_f_color_save_1_)
  extern f_status_t private_f_color_save_1(const f_color_format_t format, const f_string_static_t color1, f_string_dynamic_t * const buffer) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_color_load_context_) || !defined(_di_f_color_save_1_)

/**
 * Private implementation of f_color_save_2().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param format
 *   The color format parts.
 * @param color1
 *   A color to assign.
 * @param buffer
 *   The string to save the colors to.
 *   The buffer will become NULL terminated after the appended string length.
 *
 * @return
 *   F_okay on success.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by()
 *
 * @see memcpy()
 *
 * @see f_memory_array_increase_by()
 *
 * @see f_color_load_context()
 * @see f_color_save_2()
 */
#if !defined(_di_f_color_load_context_) || !defined(_di_f_color_save_2_)
  extern f_status_t private_f_color_save_2(const f_color_format_t format, const f_string_static_t color1, const f_string_static_t color2, f_string_dynamic_t * const buffer) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_color_load_context_) || !defined(_di_f_color_save_2_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_color_h
