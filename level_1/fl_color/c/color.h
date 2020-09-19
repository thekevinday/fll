/**
 * FLL - Level 1
 *
 * Project: Color
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provide basic color output support (linux & xterm).
 * This is the Featureless LINUX Library, so there is no support for non-linux colors at this time.
 */
#ifndef _FL_color_h
#define _FL_color_h

// libc includes
#include <stdarg.h>
#include <string.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/color.h>
#include <level_0/file.h>
#include <level_0/print.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Given some file or standard io, and push color information to that file or standard io.
 *
 * Up to 5 colors may be associted with a single color format block.
 *
 * @param file
 *   The file or standard io.
 * @param format
 *   The color format parts.
 * @param color1
 *   A color to assign, set to 0 to disable.
 * @param color2
 *   A color to assign, set to 0 to disable.
 * @param color3
 *   A color to assign, set to 0 to disable.
 * @param color4
 *   A color to assign, set to 0 to disable.
 * @param color5
 *   A color to assign, set to 0 to disable.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_color_set_
  extern f_return_status fl_color_set(FILE *file, const f_color_format_t format, const int8_t *color1, const int8_t *color2, const int8_t *color3, const int8_t *color4, const int8_t *color5);

  #define fl_macro_color_set_1(file, format, color1)                                 fl_color_set(file, format, color1, 0, 0, 0, 0)
  #define fl_macro_color_set_2(file, format, color1, color2)                         fl_color_set(file, format, color1, color2, 0, 0, 0)
  #define fl_macro_color_set_3(file, format, color1, color2, color3)                 fl_color_set(file, format, color1, color2, color3, 0, 0)
  #define fl_macro_color_set_4(file, format, color1, color2, color3, color4)         fl_color_set(file, format, color1, color2, color3, color4, 0)
  #define fl_macro_color_set_5(file, format, color1, color2, color3, color4, color5) fl_color_set(file, format, color1, color2, color3, color4, color5)
#endif // _di_fl_color_set_

/**
 * Save color information to some string.
 *
 * Up to 5 colors may be associted with a single color format block.
 *
 * @param buffer
 *   The string to save the colors to.
 * @param format
 *   The color format parts.
 * @param color1
 *   A color to assign, set to 0 to disable.
 * @param color2
 *   A color to assign, set to 0 to disable.
 * @param color3
 *   A color to assign, set to 0 to disable.
 * @param color4
 *   A color to assign, set to 0 to disable.
 * @param color5
 *   A color to assign, set to 0 to disable.
 *
 * @return
 *   F_none on success.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_color_save_
  extern f_return_status fl_color_save(f_string_dynamic_t *buffer, const f_color_format_t format, const int8_t *color1, const int8_t *color2, const int8_t *color3, const int8_t *color4, const int8_t *color5);

  #define fl_macro_color_save_1(buffer, format, color1)                                 fl_color_save(buffer, format, color1, 0, 0, 0, 0)
  #define fl_macro_color_save_2(buffer, format, color1, color2)                         fl_color_save(buffer, format, color1, color2, 0, 0, 0)
  #define fl_macro_color_save_3(buffer, format, color1, color2, color3)                 fl_color_save(buffer, format, color1, color2, color3, 0, 0)
  #define fl_macro_color_save_4(buffer, format, color1, color2, color3, color4)         fl_color_save(buffer, format, color1, color2, color3, color4, 0)
  #define fl_macro_color_save_5(buffer, format, color1, color2, color3, color4, color5) fl_color_save(buffer, format, color1, color2, color3, color4, color5)
#endif // _di_fl_color_save_

/**
 * Print a string, wrapped in a given start and stop color.
 *
 * If the colors strings have nothing used in them, then this will only print the string.
 *
 * @param file
 *   The file or standard io.
 * @param set
 *   The color set used for printing.
 * @param string
 *   The string to print to the file or standard io.
 * @param ...
 *   Variable arguments, processed in the same way fprintf() processes them.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_print_dynamic().
 */
#ifndef _di_fl_color_print_
  extern f_return_status fl_color_print(FILE *file, const f_color_set_t set, const f_string_t string, ...);
#endif // _di_fl_color_print_

/**
 * Print a string, wrapped in a given start, extra, and stop color.
 *
 * If the colors strings have nothing used in them, then this will only print the string.
 *
 * It is common for colors to be bolded.
 * This is intended to simplify printing bold colors.
 *
 * @param file
 *   The file or standard io.
 * @param set
 *   The color set used for printing.
 * @param extra
 *   The a second color set used for printing, which gets appended after set.before and set.after, respectively.
 * @param string
 *   The string to print to the file or standard io.
 * @param ...
 *   Variable arguments, processed in the same way fprintf() processes them.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_print_dynamic().
 */
#ifndef _di_fl_color_print2_
  extern f_return_status fl_color_print2(FILE *file, const f_color_set_t set, const f_color_set_t extra, const f_string_t string, ...);
#endif // _di_fl_color_print2_

/**
 * Print a string, wrapped in a given start and stop color, then print an EOL character.
 *
 * If the colors strings have nothing used in them, then this will only print the string.
 *
 * @param file
 *   The file or standard io.
 * @param set
 *   The color set used for printing.
 * @param string
 *   The string to print to the file or standard io.
 * @param ...
 *   Variable arguments, processed in the same way fprintf() processes them.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_print_dynamic().
 */
#ifndef _di_fl_color_print_line_
  extern f_return_status fl_color_print_line(FILE *file, const f_color_set_t set, const f_string_t string, ...);
#endif // _di_fl_color_print_line_

/**
 * Print a string, wrapped in a given start, extra, and stop color, then print an EOL character.
 *
 * If the colors strings have nothing used in them, then this will only print the string.
 *
 * It is common for colors to be bolded.
 * This is intended to simplify printing bold colors.
 *
 * @param file
 *   The file or standard io.
 * @param set
 *   The color set used for printing.
 * @param extra
 *   The a second color set used for printing, which gets appended after set.before and set.after, respectively.
 * @param string
 *   The string to print to the file or standard io.
 * @param ...
 *   Variable arguments, processed in the same way fprintf() processes them.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_print_dynamic().
 */
#ifndef _di_fl_color_print2_line_
  extern f_return_status fl_color_print2_line(FILE *file, const f_color_set_t set, const f_color_set_t extra, const f_string_t string, ...);
#endif // _di_fl_color_print2_line_

/**
 * Print a single color code to the given file or standard io.
 *
 * Try not to forget to print the color reset when done.
 *
 * @param file
 *   The file or standard io.
 * @param start_color
 *   The color code to print.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_print_dynamic().
 */
#ifndef _di_fl_color_print_code_
  extern f_return_status fl_color_print_code(FILE *file, const f_string_static_t color);
#endif // _di_fl_color_print_code_

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
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_color_load_context_
  extern f_return_status fl_color_load_context(f_color_context_t *context, const bool use_light_colors);
#endif // _di_fl_color_load_context_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_color_h
