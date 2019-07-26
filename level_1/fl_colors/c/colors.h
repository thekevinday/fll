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
#include <level_0/types.h>
#include <level_0/errors.h>
#include <level_0/strings.h>
#include <level_0/file.h>
#include <level_0/colors.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_color_context_
  typedef struct {
    f_colors         color_list;
    f_colors_format  color_format;
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
    f_resize_dynamic_string(status, color_context.reset, f_color_max_size + 1); \
    if (f_error_is_not_error(status)) f_resize_dynamic_string(status, color_context.warning,      f_color_max_size + 1); \
    if (f_error_is_not_error(status)) f_resize_dynamic_string(status, color_context.error,        f_color_max_size + 1); \
    if (f_error_is_not_error(status)) f_resize_dynamic_string(status, color_context.title,        f_color_max_size + 1); \
    if (f_error_is_not_error(status)) f_resize_dynamic_string(status, color_context.notable,      f_color_max_size + 1); \
    if (f_error_is_not_error(status)) f_resize_dynamic_string(status, color_context.important,    f_color_max_size + 1); \
    if (f_error_is_not_error(status)) f_resize_dynamic_string(status, color_context.standout,     f_color_max_size + 1); \
    if (f_error_is_not_error(status)) f_resize_dynamic_string(status, color_context.normal,       f_color_max_size + 1); \
    if (f_error_is_not_error(status)) f_resize_dynamic_string(status, color_context.normal_reset, f_color_max_size + 1);

  #define fl_delete_color_context(status, color_context) \
    f_delete_dynamic_string(status, color_context.reset); \
    if (f_error_is_not_error(status)) f_delete_dynamic_string(status, color_context.warning); \
    if (f_error_is_not_error(status)) f_delete_dynamic_string(status, color_context.error); \
    if (f_error_is_not_error(status)) f_delete_dynamic_string(status, color_context.title); \
    if (f_error_is_not_error(status)) f_delete_dynamic_string(status, color_context.notable); \
    if (f_error_is_not_error(status)) f_delete_dynamic_string(status, color_context.important); \
    if (f_error_is_not_error(status)) f_delete_dynamic_string(status, color_context.standout); \
    if (f_error_is_not_error(status)) f_delete_dynamic_string(status, color_context.normal); \
    if (f_error_is_not_error(status)) f_delete_dynamic_string(status, color_context.normal_reset);

  #define fl_destroy_color_context(status, color_context, size) \
    f_destroy_dynamic_string(status, color_context.reset); \
    if (f_error_is_not_error(status)) f_destroy_dynamic_string(status, color_context.warning, size); \
    if (f_error_is_not_error(status)) f_destroy_dynamic_string(status, color_context.error, size); \
    if (f_error_is_not_error(status)) f_destroy_dynamic_string(status, color_context.title, size); \
    if (f_error_is_not_error(status)) f_destroy_dynamic_string(status, color_context.notable, size); \
    if (f_error_is_not_error(status)) f_destroy_dynamic_string(status, color_context.important, size); \
    if (f_error_is_not_error(status)) f_destroy_dynamic_string(status, color_context.standout, size); \
    if (f_error_is_not_error(status)) f_destroy_dynamic_string(status, color_context.normal); \
    if (f_error_is_not_error(status)) f_destroy_dynamic_string(status, color_context.normal_reset);
#endif // _di_fl_color_context_

#ifndef _di_fl_set_color_
  // this will accept some file or standard io, and push color information to that file or standard io
  extern f_return_status fl_set_color(FILE *file, const f_colors_format format, const char *color1, const char *color2, const char *color3, const char *color4, const char *color5);

  #define fl_set_color1(file, format, color1)                                 fl_set_color(file, format, color1, 0, 0, 0, 0)
  #define fl_set_color2(file, format, color1, color2)                         fl_set_color(file, format, color1, color2, 0, 0, 0)
  #define fl_set_color3(file, format, color1, color2, color3)                 fl_set_color(file, format, color1, color2, color3, 0, 0)
  #define fl_set_color4(file, format, color1, color2, color3, color4)         fl_set_color(file, format, color1, color2, color3, color4, 0)
  #define fl_set_color5(file, format, color1, color2, color3, color4, color5) fl_set_color(file, format, color1, color2, color3, color4, color5)
#endif // _di_fl_set_color_


#ifndef _di_fl_save_color_
  // this will place all appropriate color effects into a string, handling any necessary allocations
  extern f_return_status fl_save_color(f_dynamic_string *buffer, const f_colors_format format, const char *color1, const char *color2, const char *color3, const char *color4, const char *color5);

  #define fl_save_color1(buffer, format, color1)                                 fl_save_color(buffer, format, color1, 0, 0, 0, 0)
  #define fl_save_color2(buffer, format, color1, color2)                         fl_save_color(buffer, format, color1, color2, 0, 0, 0)
  #define fl_save_color3(buffer, format, color1, color2, color3)                 fl_save_color(buffer, format, color1, color2, color3, 0, 0)
  #define fl_save_color4(buffer, format, color1, color2, color3, color4)         fl_save_color(buffer, format, color1, color2, color3, color4, 0)
  #define fl_save_color5(buffer, format, color1, color2, color3, color4, color5) fl_save_color(buffer, format, color1, color2, color3, color4, color5)
#endif // _di_fl_save_color_

#ifndef _di_fl_print_color_
  // this will wrap the passed text in the passed start and end colors
  // this will work like fprintf with the variable arguments
  // if the colors strings have nothing used in them, then this will only print the string
  extern f_return_status fl_print_color(FILE *file, const f_dynamic_string start_color, const f_dynamic_string end_color, const char *string, ...);
#endif // _di_fl_print_color_

#ifndef _di_fl_print_color_line_
  // this is identical to fl_print_color, but also prints a trailing newline
  extern f_return_status fl_print_color_line(FILE *file, const f_dynamic_string start_color, const f_dynamic_string end_color, const char *string, ...);
#endif // _di_fl_print_color_line_

#ifndef _di_fl_print_color_code_
  // this will print a single color code so that all print commands following this command will print in color (or not..)
  // do not forget to print the color reset when done
  extern f_return_status fl_print_color_code(FILE *file, const f_dynamic_string color);
#endif // _di_fl_print_color_code_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_colors_h
