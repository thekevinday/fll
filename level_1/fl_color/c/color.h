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
#include <level_0/color.h>
#include <level_0/status.h>
#include <level_0/file.h>
#include <level_0/string.h>
#include <level_0/type.h>
#include <level_0/print.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_color_context_
  typedef struct {
    f_color color_list;
    f_color_format color_format;
    f_color_mode mode;
    f_string_dynamic reset;
    f_string_dynamic warning;
    f_string_dynamic error;
    f_string_dynamic title;
    f_string_dynamic notable;
    f_string_dynamic important;
    f_string_dynamic standout;
    f_string_dynamic normal;
    f_string_dynamic normal_reset;
  } fl_color_context;

  #define fl_color_context_initialize { f_color_initialize_linux, f_color_format_initialize_linux, f_color_mode_none, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize }

  #define fl_macro_color_context_new(status, color_context) \
    f_macro_string_dynamic_new(status, color_context.reset, f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.warning,      f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.error,        f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.title,        f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.notable,      f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.important,    f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.standout,     f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.normal,       f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.normal_reset, f_color_max_size + 1);

  #define fl_macro_color_context_delete(status, color_context) \
    f_macro_string_dynamic_delete(status, color_context.reset); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_delete(status, color_context.warning); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_delete(status, color_context.error); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_delete(status, color_context.title); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_delete(status, color_context.notable); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_delete(status, color_context.important); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_delete(status, color_context.standout); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_delete(status, color_context.normal); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_delete(status, color_context.normal_reset);

  #define fl_macro_color_context_destroy(status, color_context, size) \
    f_macro_string_dynamic_destroy(status, color_context.reset); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_destroy(status, color_context.warning, size); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_destroy(status, color_context.error, size); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_destroy(status, color_context.title, size); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_destroy(status, color_context.notable, size); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_destroy(status, color_context.important, size); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_destroy(status, color_context.standout, size); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_destroy(status, color_context.normal); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_destroy(status, color_context.normal_reset);

  #define fl_macro_color_context_delete_simple(color_context) \
    f_macro_string_dynamic_delete_simple(color_context.reset); \
    f_macro_string_dynamic_delete_simple(color_context.warning); \
    f_macro_string_dynamic_delete_simple(color_context.error); \
    f_macro_string_dynamic_delete_simple(color_context.title); \
    f_macro_string_dynamic_delete_simple(color_context.notable); \
    f_macro_string_dynamic_delete_simple(color_context.important); \
    f_macro_string_dynamic_delete_simple(color_context.standout); \
    f_macro_string_dynamic_delete_simple(color_context.normal); \
    f_macro_string_dynamic_delete_simple(color_context.normal_reset);

  #define fl_macro_color_context_destroy_simple(color_context, size) \
    f_macro_string_dynamic_destroy_simple(color_context.reset); \
    f_macro_string_dynamic_destroy_simple(color_context.warning, size); \
    f_macro_string_dynamic_destroy_simple(color_context.error, size); \
    f_macro_string_dynamic_destroy_simple(color_context.title, size); \
    f_macro_string_dynamic_destroy_simple(color_context.notable, size); \
    f_macro_string_dynamic_destroy_simple(color_context.important, size); \
    f_macro_string_dynamic_destroy_simple(color_context.standout, size); \
    f_macro_string_dynamic_destroy_simple(color_context.normal); \
    f_macro_string_dynamic_destroy_simple(color_context.normal_reset);

  #define fl_macro_color_context_resize(status, color_context) \
    f_macro_string_dynamic_resize(status, color_context.reset, f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.warning,      f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.error,        f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.title,        f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.notable,      f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.important,    f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.standout,     f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.normal,       f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.normal_reset, f_color_max_size + 1);

  #define fl_macro_color_context_adjust(status, color_context) \
    f_macro_string_dynamic_adjust(status, color_context.reset, f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.warning,      f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.error,        f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.title,        f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.notable,      f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.important,    f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.standout,     f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.normal,       f_color_max_size + 1); \
    if (f_status_is_not_error(status)) f_macro_string_dynamic_resize(status, color_context.normal_reset, f_color_max_size + 1);
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
  extern f_return_status fl_color_set(FILE *file, const f_color_format format, const int8_t *color1, const int8_t *color2, const int8_t *color3, const int8_t *color4, const int8_t *color5);

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
 *   f_error_reallocation (with error bit) on memory reallocation error.
 */
#ifndef _di_fl_color_save_
  extern f_return_status fl_color_save(f_string_dynamic *buffer, const f_color_format format, const int8_t *color1, const int8_t *color2, const int8_t *color3, const int8_t *color4, const int8_t *color5);

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
 *   f_error_output (with error bit) on output error.
 */
#ifndef _di_fl_color_print_
  extern f_return_status fl_color_print(FILE *file, const f_string_static start_color, const f_string_static end_color, const int8_t *string, ...);
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
 * @param format
 *   The color format parts.
 * @param start_color
 *   The color code to place at the beginning of the string, set to 0 to disable.
 * @param extra_color
 *   The color code to place immediately following the start_color, set to 0 to disable.
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
 *   f_error_output (with error bit) on output error.
 */
#ifndef _di_fl_color_print2_
  extern f_return_status fl_color_print2(FILE *file, const f_string_static start_color, const f_string_static extra_color, const f_string_static end_color, const int8_t *string, ...);
#endif // _di_fl_color_print2_

/**
 * Print a string, wrapped in a given start and stop color, then print an EOL character.
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
 *   f_error_output (with error bit) on output error.
 */
#ifndef _di_fl_color_print_line_
  extern f_return_status fl_color_print_line(FILE *file, const f_string_static start_color, const f_string_static end_color, const int8_t *string, ...);
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
 * @param format
 *   The color format parts.
 * @param start_color
 *   The color code to place at the beginning of the string, set to 0 to disable.
 * @param extra_color
 *   The color code to place immediately following the start_color, set to 0 to disable.
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
 *   f_error_output (with error bit) on output error.
 */
#ifndef _di_fl_color_print2_line_
  extern f_return_status fl_color_print2_line(FILE *file, const f_string_static start_color, const f_string_static extra_color, const f_string_static end_color, const int8_t *string, ...);
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
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_output (with error bit) on output error.
 */
#ifndef _di_fl_color_print_code_
  extern f_return_status fl_color_print_code(FILE *file, const f_string_static color);
#endif // _di_fl_color_print_code_

/**
 * Load the appropriate colors into the color context.
 *
 * This will handle the difference betweem xorg terminals and linux consoles.
 * If you wish to use non-standard colors either redefine this function or don't use it.
 *
 * @param context
 *   The color context the load the color codes into.
 * @param use_light_colors
 *   Set to f_true to use colors for light backgrounds.
 *   Set to f_false to use colors forr dark backgrounds.
 *
 * @return
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_reallocation (with error bit) on memory reallocation error.
 */
#ifndef _di_fl_color_load_context_
  extern f_return_status fl_color_load_context(fl_color_context *context, const bool use_light_colors);
#endif // _di_fl_color_load_context_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_color_h
