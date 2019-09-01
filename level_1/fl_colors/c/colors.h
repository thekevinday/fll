/**
 * FLL - Level 1
 *
 * Project: Colors
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provide basic color output support (linux & xterm).
 * This is the Featureless LINUX Library, so there is no support for non-linux colors at this time.
 */
#ifndef _FL_colors_h
#define _FL_colors_h

// libc includes
#include <stdarg.h>
#include <string.h>

// fll-0 includes
#include <level_0/colors.h>
#include <level_0/status.h>
#include <level_0/file.h>
#include <level_0/strings.h>
#include <level_0/types.h>
#include <level_0/print.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_color_context_
  typedef struct {
    f_colors color_list;
    f_colors_format color_format;
    f_dynamic_string reset;
    f_dynamic_string warning;
    f_dynamic_string error;
    f_dynamic_string title;
    f_dynamic_string notable;
    f_dynamic_string important;
    f_dynamic_string standout;
    f_dynamic_string normal;
    f_dynamic_string normal_reset;
  } fl_color_context;

  #define fl_color_context_initialize { f_colors_initialize_linux, f_colors_format_initialize_linux, f_dynamic_string_initialize, f_dynamic_string_initialize, f_dynamic_string_initialize, f_dynamic_string_initialize, f_dynamic_string_initialize, f_dynamic_string_initialize, f_dynamic_string_initialize, f_dynamic_string_initialize, f_dynamic_string_initialize }

  #define fl_new_color_context(status, color_context) \
    f_macro_string_dynamic_resize(status, color_context.reset, f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.warning,      f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.error,        f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.title,        f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.notable,      f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.important,    f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.standout,     f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.normal,       f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.normal_reset, f_color_max_size + 1);

  #define fl_delete_color_context(status, color_context) \
    f_macro_string_dynamic_delete(status, color_context.reset); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_delete(status, color_context.warning); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_delete(status, color_context.error); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_delete(status, color_context.title); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_delete(status, color_context.notable); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_delete(status, color_context.important); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_delete(status, color_context.standout); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_delete(status, color_context.normal); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_delete(status, color_context.normal_reset);

  #define fl_destroy_color_context(status, color_context, size) \
    f_macro_string_dynamic_destroy(status, color_context.reset); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_destroy(status, color_context.warning, size); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_destroy(status, color_context.error, size); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_destroy(status, color_context.title, size); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_destroy(status, color_context.notable, size); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_destroy(status, color_context.important, size); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_destroy(status, color_context.standout, size); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_destroy(status, color_context.normal); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_destroy(status, color_context.normal_reset);
#endif // _di_fl_color_context_

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
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_color_set_
  extern f_return_status fl_color_set(FILE *file, const f_colors_format format, const char *color1, const char *color2, const char *color3, const char *color4, const char *color5);

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
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_reallocation_error (with error bit) on memory reallocation error.
 */
#ifndef _di_fl_color_save_
  extern f_return_status fl_color_save(f_dynamic_string *buffer, const f_colors_format format, const char *color1, const char *color2, const char *color3, const char *color4, const char *color5);

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
 * @param format
 *   The color format parts.
 * @param start_color
 *   The color code to place at the beginning of the string, set to 0 to disable.
 * @param stop_color
 *   The color code to place at the end of the string, set to 0 to disable.
 * @param string
 *   The string to print to the file or standard io.
 * @param ...
 *   Variable arguments, processed in the same way fprintf() processes them.
 *
 * @return
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_output_error (with error bit) on output error.
 */
#ifndef _di_fl_color_print_
  extern f_return_status fl_color_print(FILE *file, const f_dynamic_string start_color, const f_dynamic_string end_color, const char *string, ...);
#endif // _di_fl_color_print_

/**
 * Print a string, wrapped in a given start and stop color, and then print an EOL character.
 *
 * If the colors strings have nothing used in them, then this will only print the string.
 *
 * @param file
 *   The file or standard io.
 * @param format
 *   The color format parts.
 * @param start_color
 *   The color code to place at the beginning of the string, set to 0 to disable.
 * @param stop_color
 *   The color code to place at the end of the string, set to 0 to disable.
 * @param string
 *   The string to print to the file or standard io.
 * @param ...
 *   Variable arguments, processed in the same way fprintf() processes them.
 *
 * @return
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_output_error (with error bit) on output error.
 */
#ifndef _di_fl_color_print_line_
  extern f_return_status fl_color_print_line(FILE *file, const f_dynamic_string start_color, const f_dynamic_string end_color, const char *string, ...);
#endif // _di_fl_color_print_line_

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
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_output_error (with error bit) on output error.
 */
#ifndef _di_fl_color_print_code_
  extern f_return_status fl_color_print_code(FILE *file, const f_dynamic_string color);
#endif // _di_fl_color_print_code_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_colors_h
