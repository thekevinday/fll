/* FLL - Level 1
 * Project:       Colors
 * Version:       0.2.0
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provide basic color output support (linux & xterm)
 * This is the Featureless LINUX Library, so there is no support for non-linux colors at this time.
 */
#ifndef _FL_colors_h
#define _FL_colors_h

// libc includes
#include <stdarg.h>
#include <string.h>

// fll-0 includes
#include <level_0/types.h>
#include <level_0/strings.h>
#include <level_0/file.h>
#include <level_0/colors.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fl_set_color_
  // this will accept some file or standard io, and push color information to that file or standard io
  extern f_return_status fl_set_color(f_file_type file, const f_colors_format format, const f_autochar *color1, const f_autochar *color2, const f_autochar *color3, const f_autochar *color4, const f_autochar *color5);

  #define fl_set_color1(file, format, color1)                                 fl_set_color(file, format, color1, 0, 0, 0, 0)
  #define fl_set_color2(file, format, color1, color2)                         fl_set_color(file, format, color1, color2, 0, 0, 0)
  #define fl_set_color3(file, format, color1, color2, color3)                 fl_set_color(file, format, color1, color2, color3, 0, 0)
  #define fl_set_color4(file, format, color1, color2, color3, color4)         fl_set_color(file, format, color1, color2, color3, color4, 0)
  #define fl_set_color5(file, format, color1, color2, color3, color4, color5) fl_set_color(file, format, color1, color2, color3, color4, color5)
#endif // _di_fl_set_color_


#ifndef _di_fl_save_color_
  // this will place all appropriate color effects into a string, handling any necessary allocations
  extern f_return_status fl_save_color(f_dynamic_string *buffer, const f_colors_format format, const f_autochar *color1, const f_autochar *color2, const f_autochar *color3, const f_autochar *color4, const f_autochar *color5);

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
  extern f_return_status fl_print_color(f_file_type file, const f_dynamic_string start_color, const f_dynamic_string end_color, const f_autochar *string, ...);
#endif // _di_fl_print_color_

#ifndef _di_fl_print_color_line_
  // this is identical to fl_print_color, but also prints a trailing newline
  extern f_return_status fl_print_color_line(f_file_type file, const f_dynamic_string start_color, const f_dynamic_string end_color, const f_autochar *string, ...);
#endif // _di_fl_print_color_line_

#ifndef _di_fl_print_color_code_
  // this will print a single color code so that all print commands following this command will print in color (or not..)
  // do not forget to print the color reset when done
  extern f_return_status fl_print_color_code(f_file_type file, const f_dynamic_string color);
#endif // _di_fl_print_color_code_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_colors_h
