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
 * Given some file or standard io, and push color information to that file or standard io.
 *
 * Up to 5 colors may be associted with a single color format block.
 *
 * @param stream
 *   The file stream or standard output.
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_color_set_
  extern f_status_t f_color_set(FILE *stream, const f_color_format_t format, const char *color1, const char *color2, const char *color3, const char *color4, const char *color5);

  #define macro_fl_color_set_1(stream, format, color1)                                 f_color_set(stream, format, color1, 0, 0, 0, 0);
  #define macro_fl_color_set_2(stream, format, color1, color2)                         f_color_set(stream, format, color1, color2, 0, 0, 0);
  #define macro_fl_color_set_3(stream, format, color1, color2, color3)                 f_color_set(stream, format, color1, color2, color3, 0, 0);
  #define macro_fl_color_set_4(stream, format, color1, color2, color3, color4)         f_color_set(stream, format, color1, color2, color3, color4, 0);
  #define macro_fl_color_set_5(stream, format, color1, color2, color3, color4, color5) f_color_set(stream, format, color1, color2, color3, color4, color5);
#endif // _di_f_color_set_

/**
 * Given some file descriptor, and push color information to that descriptor.
 *
 * Up to 5 colors may be associted with a single color format block.
 *
 * @param id
 *   The file descriptor to print to.
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
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_color_set_to_
  extern f_status_t f_color_set_to(const int id, const f_color_format_t format, const char *color1, const char *color2, const char *color3, const char *color4, const char *color5);

  #define macro_fl_color_set_to_1(id, format, color1)                                 f_color_set_to(id, format, color1, 0, 0, 0, 0);
  #define macro_fl_color_set_to_2(id, format, color1, color2)                         f_color_set_to(id, format, color1, color2, 0, 0, 0);
  #define macro_fl_color_set_to_3(id, format, color1, color2, color3)                 f_color_set_to(id, format, color1, color2, color3, 0, 0);
  #define macro_fl_color_set_to_4(id, format, color1, color2, color3, color4)         f_color_set_to(id, format, color1, color2, color3, color4, 0);
  #define macro_fl_color_set_to_5(id, format, color1, color2, color3, color4, color5) f_color_set_to(id, format, color1, color2, color3, color4, color5);
#endif // _di_f_color_set_to_

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

/**
 * Print a string, wrapped in a given start and stop color.
 *
 * If the colors strings have nothing used in them, then this will only print the string.
 *
 * @param stream
 *   The file stream or standard output.
 * @param set
 *   The color set used for printing.
 * @param string
 *   The string to print.
 * @param ...
 *   Variable arguments, processed in the same way fprintf() processes them.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_color_print_
  extern f_status_t f_color_print(FILE *stream, const f_color_set_t set, const f_string_t string, ...);
#endif // _di_f_color_print_

/**
 * Print a string, wrapped in a given start, extra, and stop color.
 *
 * If the colors strings have nothing used in them, then this will only print the string.
 *
 * It is common for colors to be bolded.
 * This is intended to simplify printing bold colors.
 *
 * @param stream
 *   The file stream or standard output.
 * @param set
 *   The color set used for printing.
 * @param extra
 *   The a second color set used for printing, which gets appended after set.before and set.after, respectively.
 * @param string
 *   The string to print.
 * @param ...
 *   Variable arguments, processed in the same way fprintf() processes them.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_color_print2_
  extern f_status_t f_color_print2(FILE *stream, const f_color_set_t set, const f_color_set_t extra, const f_string_t string, ...);
#endif // _di_f_color_print2_

/**
 * Print a single color code to the given file or standard io.
 *
 * Be sure to forget to print the color reset when done.
 *
 * @param stream
 *   The file stream or standard output.
 * @param start_color
 *   The color code to print.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_print_dynamic().
 */
#ifndef _di_f_color_print_code_
  extern f_status_t f_color_print_code(FILE *stream, const f_string_static_t color);
#endif // _di_f_color_print_code_

/**
 * Print a single color code to the given file represented by a file descriptor.
 *
 * Be sure to forget to print the color reset when done.
 *
 * @param id
 *   The file descriptor to print to.
 * @param start_color
 *   The color code to print.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_print_to_dynamic().
 */
#ifndef _di_f_color_print_code_to_
  extern f_status_t f_color_print_code_to(const int id, const f_string_static_t color);
#endif // _di_f_color_print_code_to_

/**
 * Print a string, wrapped in a given start and stop color.
 *
 * If the colors strings have nothing used in them, then this will only print the string.
 *
 * @param id
 *   The file descriptor to print to.
 * @param set
 *   The color set used for printing.
 * @param string
 *   The string to print.
 * @param ...
 *   Variable arguments, processed in the same way fprintf() processes them.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_print_dynamic().
 */
#ifndef _di_f_color_print_to_
  extern f_status_t f_color_print_to(const int id, const f_color_set_t set, const f_string_t string, ...);
#endif // _di_f_color_print_to_

/**
 * Print a string, wrapped in a given start, extra, and stop color.
 *
 * If the colors strings have nothing used in them, then this will only print the string.
 *
 * It is common for colors to be bolded.
 * This is intended to simplify printing bold colors.
 *
 * @param id
 *   The file descriptor to print to.
 * @param set
 *   The color set used for printing.
 * @param extra
 *   The a second color set used for printing, which gets appended after set.before and set.after, respectively.
 * @param string
 *   The string to print.
 * @param ...
 *   Variable arguments, processed in the same way fprintf() processes them.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_print_dynamic().
 */
#ifndef _di_f_color_print2_to_
  extern f_status_t f_color_print2_to(const int id, const f_color_set_t set, const f_color_set_t extra, const f_string_t string, ...);
#endif // _di_f_color_print2_to_

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

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_color_h
