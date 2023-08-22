/**
 * FLL - Level 0
 *
 * Project: Color
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provide basic color output support (linux & xterm).
 * This is the Featureless LINUX Library, so there is no support for non-linux colors at this time.
 *
 * For simplicity purposes, all color code strings are required and assumed to be NULL terminated.
 */
#ifndef _F_color_h
#define _F_color_h

// Libc includes.
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/type_array.h>
#include <fll/level_0/string.h>

// FLL-0 color includes.
#include <fll/level_0/color/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Load the appropriate colors into the color context.
 *
 * This will handle the difference betweem xorg terminals and linux consoles.
 * If you wish to use non-standard colors either redefine this function or don't use it.
 *
 * This only supports the following color modes:
 *   - f_color_mode_not_e
 *   - f_color_mode_dark_e
 *   - f_color_mode_light_e
 *
 * The default/fallback behavior is f_color_xterminal.
 *
 * @param mode
 *   The color mode to load.
 * @param context
 *   The color context the load the color codes into.
 *   The context.mode is always set to the specified mode, even if it is not supported (except when there is an invalid parameter).
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success but mode is f_color_mode_none_e or not a supported mode.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by()
 *
 * @see memcpy()
 *
 * @see f_memory_array_increase_by()
 */
#ifndef _di_f_color_load_context_
  extern f_status_t f_color_load_context(const uint8_t mode, f_color_context_t * const context);
#endif // _di_f_color_load_context_

/**
 * Save color information to some string using one color code.
 *
 * This is environment sensitive.
 * If TERM is not defined or set to "linux", then macro_f_color_t_set_linux() is used.
 * Otherwise macro_f_color_t_set_xterminal() is used.
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
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by()
 *
 * @see memcpy()
 *
 * @see f_memory_array_increase_by()
 */
#ifndef _di_f_color_save_1_
  extern f_status_t f_color_save_1(const f_color_format_t format, const f_string_static_t color1, f_string_dynamic_t * const buffer);
#endif // _di_f_color_save_1_

/**
 * Save color information to some string using two color codes.
 *
 * This is environment sensitive.
 * If TERM is not defined or set to "linux", then macro_f_color_t_set_linux() is used.
 * Otherwise macro_f_color_t_set_xterminal() is used.
 *
 * @param format
 *   The color format parts.
 * @param color1
 *   A color to assign.
 * @param color2
 *   A second color to assign.
 *   Ignored if color1.used is 0.
 * @param buffer
 *   The string to save the colors to.
 *   The buffer will become NULL terminated after the appended string length.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by()
 *
 * @see memcpy()
 *
 * @see f_memory_array_increase_by()
 */
#ifndef _di_f_color_save_2_
  extern f_status_t f_color_save_2(const f_color_format_t format, const f_string_static_t color1, const f_string_static_t color2, f_string_dynamic_t * const buffer);
#endif // _di_f_color_save_2_

/**
 * Save color information to some string using three color codes.
 *
 * This is environment sensitive.
 * If TERM is not defined or set to "linux", then macro_f_color_t_set_linux() is used.
 * Otherwise macro_f_color_t_set_xterminal() is used.
 *
 * @param format
 *   The color format parts.
 * @param color1
 *   A color to assign.
 * @param color2
 *   A second color to assign.
 *   Ignored if color1.used is 0.
 * @param color3
 *   A third color to assign.
 *   Ignored if color1.used or color2.used is 0.
 * @param buffer
 *   The string to save the colors to.
 *   The buffer will become NULL terminated after the appended string length.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by()
 *
 * @see memcpy()
 *
 * @see f_memory_array_increase_by()
 */
#ifndef _di_f_color_save_3_
  extern f_status_t f_color_save_3(const f_color_format_t format, const f_string_static_t color1, const f_string_static_t color2, const f_string_static_t color3, f_string_dynamic_t * const buffer);
#endif // _di_f_color_save_3_

/**
 * Save color information to some string using four color codes.
 *
 * This is environment sensitive.
 * If TERM is not defined or set to "linux", then macro_f_color_t_set_linux() is used.
 * Otherwise macro_f_color_t_set_xterminal() is used.
 *
 * @param format
 *   The color format parts.
 * @param color1
 *   A color to assign.
 * @param color2
 *   A second color to assign.
 *   Ignored if color1.used is 0.
 * @param color3
 *   A third color to assign.
 *   Ignored if color1.used or color2.used is 0.
 * @param color4
 *   A fourth color to assign.
 *   Ignored if color1.used, color2.used, or color3.used is 0.
 * @param buffer
 *   The string to save the colors to.
 *   The buffer will become NULL terminated after the appended string length.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by()
 *
 * @see memcpy()
 *
 * @see f_memory_array_increase_by()
 */
#ifndef _di_f_color_save_4_
  extern f_status_t f_color_save_4(const f_color_format_t format, const f_string_static_t color1, const f_string_static_t color2, const f_string_static_t color3, const f_string_static_t color4, f_string_dynamic_t * const buffer);
#endif // _di_f_color_save_4_

/**
 * Save color information to some string using five color codes.
 *
 * Five colors is the max that may be associated with a single color format block.
 *
 * This is environment sensitive.
 * If TERM is not defined or set to "linux", then macro_f_color_t_set_linux() is used.
 * Otherwise macro_f_color_t_set_xterminal() is used.
 *
 * @param format
 *   The color format parts.
 * @param color1
 *   A color to assign.
 * @param color2
 *   A second color to assign.
 *   Ignored if color1.used is 0.
 * @param color3
 *   A third color to assign.
 *   Ignored if color1.used or color2.used is 0.
 * @param color4
 *   A fourth color to assign.
 *   Ignored if color1.used, color2.used, or color3.used is 0.
 * @param color5
 *   A fifth color to assign.
 *   Ignored if color1.used, color2.used, color3.used, or color4.used is 0.
 * @param buffer
 *   The string to save the colors to.
 *   The buffer will become NULL terminated after the appended string length.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_increase_by()
 *
 * @see memcpy()
 *
 * @see f_memory_array_increase_by()
 */
#ifndef _di_f_color_save_5_
  extern f_status_t f_color_save_5(const f_color_format_t format, const f_string_static_t color1, const f_string_static_t color2, const f_string_static_t color3, const f_string_static_t color4, const f_string_static_t color5, f_string_dynamic_t * const buffer);
#endif // _di_f_color_save_5_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_color_h
