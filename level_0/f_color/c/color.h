/**
 * FLL - Level 0
 *
 * Project: Color
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provide basic color output support (linux & xterm).
 * This is the Featureless LINUX Library, so there is no support for non-linux colors at this time.
 *
 * For simplicity purposes, all color code strings are required and assumed to be NULL terminated.
 */
#ifndef _F_color_h
#define _F_color_h

// libc includes
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

// fll-0 includes
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>

// fll-0 color includes
#include <fll/level_0/color-common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Load the appropriate colors into the color context.
 *
 * This will handle the difference betweem xorg terminals and linux consoles.
 * If you wish to use non-standard colors either redefine this function or don't use it.
 *
 * The default/fallback behavior is f_color_xterminal.
 *
 * @param context
 *   The color context the load the color codes into.
 * @param use_light_colors
 *   Set to F_true to use colors for light backgrounds.
 *   Set to F_false to use colors for dark backgrounds.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_color_load_context_
  extern f_status_t f_color_load_context(f_color_context_t *context, const bool use_light_colors);
#endif // _di_f_color_load_context_

/**
 * Save color information to some string.
 *
 * Up to 5 colors may be associted with a single color format block.
 *
 * This is environment sensitive.
 * If TERM is not defined or set to "linux", then macro_f_color_t_set_linux() is used.
 * Otherwise macro_f_color_t_set_xterminal() is used.
 *
 * @param buffer
 *   The string to save the colors to.
 * @param format
 *   The color format parts.
 * @param color1
 *   A color to assign, set to NULL to not use.
 * @param color2
 *   A color to assign, set to NULL to not use.
 * @param color3
 *   A color to assign, set to NULL to not use.
 * @param color4
 *   A color to assign, set to NULL to not use.
 * @param color5
 *   A color to assign, set to NULL to not use.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_color_save_
  extern f_status_t f_color_save(f_string_dynamic_t *buffer, const f_color_format_t format, const char *color1, const char *color2, const char *color3, const char *color4, const char *color5);

  #define macro_fl_color_save_1(buffer, format, color1)                                 f_color_save(buffer, format, color1, 0, 0, 0, 0);
  #define macro_fl_color_save_2(buffer, format, color1, color2)                         f_color_save(buffer, format, color1, color2, 0, 0, 0);
  #define macro_fl_color_save_3(buffer, format, color1, color2, color3)                 f_color_save(buffer, format, color1, color2, color3, 0, 0);
  #define macro_fl_color_save_4(buffer, format, color1, color2, color3, color4)         f_color_save(buffer, format, color1, color2, color3, color4, 0);
  #define macro_fl_color_save_5(buffer, format, color1, color2, color3, color4, color5) f_color_save(buffer, format, color1, color2, color3, color4, color5);
#endif // _di_f_color_save_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_color_h
