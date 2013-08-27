/* FLL - Level 0
 * Project:       Colors
 * Version:       0.4.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provide basic color output support (linux & xterm)
 * This is the Featureless LINUX Library, so there is no support for non-linux colors at this time.
 */
#ifndef _F_colors_h
#define _F_colors_h

// fll-0 includes
#include <level_0/types.h>
#include <level_0/strings.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_f_color_max_size_
  #define f_color_max_size 7
#endif // _di_f_color_max_size_

#ifndef _di_f_color_types_
  typedef f_min_u_int f_color_id;

  // f_color_id codes
  #define f_color_linux     0
  #define f_color_xterminal 1
#endif // _di_f_color_types_

// the purpose behind these data types are not to dynamically allocate data
// instead, they are intended to only point to existing data, so these should neither be allocated nor deallocated
#ifndef _di_f_color_control_
  typedef struct f_color_control {
    const f_autochar *bold;
    const f_autochar *underline;
    const f_autochar *blink;
    const f_autochar *reverse;
    const f_autochar *conceal;
  } f_color_control;

  #define f_color_control_names_initialize { "bold", "underline", "blink", "reverse", "conceal" }
#endif // _di_f_color_control_

#ifndef _di_f_color_standard_io_
  typedef struct {
    const f_autochar *message;
    const f_autochar *warning;
    const f_autochar *error;
    const f_autochar *strong_message; // an emphasized message
    const f_autochar *strong_warning; // an emphasized warning
    const f_autochar *strong_error;   // an emphasized error
  } f_color_standard_io;

  #define f_color_standard_io_names_initialize { "message", "warning", "error", "strong_message", "strong_warning", "strong_error" }
#endif // _di_f_color_standard_io_

#ifndef _di_f_color_help_
  typedef struct {
    const f_autochar *title;     // name printed
    const f_autochar *version;   // version printed
    const f_autochar *topic;     // topic such as 'Usage'
    const f_autochar *command;   // color for a specific command, such as '-h'
    const f_autochar *syntax;    // color for syntax, such as '[' and '<'
    const f_autochar *alert;     // some form of alert such as 'Not Implemented Yet'
    const f_autochar *comment;   // not quite important text, but still should be seen
    const f_autochar *standard;  // the normal text color
    const f_autochar *emphasize; // make sure something stands out to emphasize it
  } f_color_help;

  #define f_color_help_names_initialize { "title", "version", "topic", "command", "syntax", "alert", "comment", "standard", "emphasize" }
#endif // _di_f_color_help_

#ifndef _di_f_colors_format_
  typedef struct {
    const f_autochar *begin;
    const f_autochar *medium;
    const f_autochar *end;
  } f_colors_format;

  #define f_colors_format_initialize_linux     { "\033[", ";", "m" }
  #define f_colors_format_initialize_xterminal { "\033[", ";", "m" }
#endif // _di_f_colors_format_

#ifndef _di_f_colors_
  typedef struct {
    const f_autochar *reset;
    const f_autochar *bold;
    const f_autochar *underline;
    const f_autochar *blink;
    const f_autochar *reverse;
    const f_autochar *conceal;
    const f_autochar *black;
    const f_autochar *red;
    const f_autochar *green;
    const f_autochar *yellow;
    const f_autochar *blue;
    const f_autochar *purple;
    const f_autochar *teal;
    const f_autochar *white;
    const f_autochar *black_bg;
    const f_autochar *red_bg;
    const f_autochar *green_bg;
    const f_autochar *yellow_bg;
    const f_autochar *blue_bg;
    const f_autochar *purple_bg;
    const f_autochar *teal_bg;
    const f_autochar *white_bg;
    const f_autochar *bright_black;
    const f_autochar *bright_red;
    const f_autochar *bright_green;
    const f_autochar *bright_yellow;
    const f_autochar *bright_blue;
    const f_autochar *bright_purple;
    const f_autochar *bright_teal;
    const f_autochar *bright_white;
    const f_autochar *bright_black_bg;
    const f_autochar *bright_red_bg;
    const f_autochar *bright_green_bg;
    const f_autochar *bright_yellow_bg;
    const f_autochar *bright_blue_bg;
    const f_autochar *bright_purple_bg;
    const f_autochar *bright_teal_bg;
    const f_autochar *bright_white_bg;
  } f_colors;

  #define f_colors_initialize_linux     { "0", "1", "4", "5", "7", "8", "30", "31", "32", "33", "34", "35", "36", "37", "40", "41", "42", "43", "44", "45", "46", "47", "30", "31", "32", "33", "34", "35", "36", "37", "40", "41", "42", "43", "44", "45", "46", "47" }
  #define f_colors_initialize_xterminal { "0", "1", "4", "5", "7", "8", "30", "31", "32", "33", "34", "35", "36", "37", "40", "41", "42", "43", "44", "45", "46", "47", "90", "91", "92", "93", "94", "95", "96", "97", "100", "101", "102", "103", "104", "105", "106", "107" }
#endif // _di_f_colors_

#ifndef _di_f_default_colors_
  static const f_colors_format f_colors_format_linux     = f_colors_format_initialize_linux;
  static const f_colors_format f_colors_format_xterminal = f_colors_format_initialize_xterminal;
  static const f_colors        f_colors_linux            = f_colors_initialize_linux;
  static const f_colors        f_colors_xterminal        = f_colors_initialize_xterminal;
#endif // _di_f_default_colors_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_colors_h
