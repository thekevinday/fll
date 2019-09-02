/**
 * FLL - Level 0
 *
 * Project: Color
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provide basic color output support (linux & xterm).
 * This is the Featureless LINUX Library, so there is no support for non-linux colors at this time.
 */
#ifndef _F_color_h
#define _F_color_h

// fll-0 includes
#include <level_0/string.h>
#include <level_0/type.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_color_max_size_
  #define f_color_max_size 7
#endif // _di_f_color_max_size_

#ifndef _di_f_color_types_
  typedef f_min_u_int f_color_id;

  // f_color_id codes
  #define f_color_code_linux     0
  #define f_color_code_xterminal 1
#endif // _di_f_color_types_

/**
 * The purpose behind these data types are not to dynamically allocate data.
 * instead, they are intended to only point to existing data, so these should neither be allocated nor deallocated.
 */
#ifndef _di_f_color_control_
  typedef struct f_color_control {
    const char *blink;
    const char *bold;
    const char *conceal;
    const char *reverse;
    const char *underline;
  } f_color_control;

  #define f_color_control_names_initialize { "blink", "bold", "conceal", "reverse", "underline" }
#endif // _di_f_color_control_

/**
 * strong represents emphasis.
 */
#ifndef _di_f_color_standard_io_
  typedef struct {
    const char *error;
    const char *message;
    const char *warning;
    const char *strong_error;
    const char *strong_message;
    const char *strong_warning;
  } f_color_standard_io;

  #define f_color_standard_io_names_initialize { "error", "message", "warning", "strong_error", "strong_message", "strong_warning" }
#endif // _di_f_color_standard_io_

/**
 * alert = some form of alert such as 'Not Implemented Yet'.
 * command = color for a specific command, such as '-h'.
 * comment = not quite important text, but still should be seen.
 * emphasize = make sure something stands out to emphasize it.
 * standard = the normal text color.
 * syntax = color for syntax, such as '[' and '<'.
 * title = name printed.
 * topic = topic such as 'Usage'.
 * version = version printed.
 */
#ifndef _di_f_color_help_
  typedef struct {
    const char *alert;
    const char *command;
    const char *comment;
    const char *emphasize;
    const char *standard;
    const char *syntax;
    const char *title;
    const char *topic;
    const char *version;
  } f_color_help;

  #define f_color_help_names_initialize { "alert", "command", "comment", "emphasize", "standard", "syntax", "title", "topic", "version" }
#endif // _di_f_color_help_

#ifndef _di_f_color_format_
  typedef struct {
    const char *begin;
    const char *end;
    const char *medium;
  } f_color_format;

  #define f_color_format_initialize_linux     { "\033[", "m", ";" }
  #define f_color_format_initialize_xterminal { "\033[", "m", ";" }
#endif // _di_f_color_format_

/**
 * A structure containing all supported color codes.
 *
 * Different system will support a different set.
 *
 * Custom initializers are provided for common defaults:
 * - f_color_initialize_linux: ideal for linux console.
 * - f_color_initialize_xterminal: ideal for linux x-terminal.
 */
#ifndef _di_f_color_
  typedef struct {
    const char *reset;
    const char *bold;
    const char *underline;
    const char *blink;
    const char *reverse;
    const char *conceal;
    const char *black;
    const char *red;
    const char *green;
    const char *yellow;
    const char *blue;
    const char *purple;
    const char *teal;
    const char *white;
    const char *black_bg;
    const char *red_bg;
    const char *green_bg;
    const char *yellow_bg;
    const char *blue_bg;
    const char *purple_bg;
    const char *teal_bg;
    const char *white_bg;
    const char *bright_black;
    const char *bright_red;
    const char *bright_green;
    const char *bright_yellow;
    const char *bright_blue;
    const char *bright_purple;
    const char *bright_teal;
    const char *bright_white;
    const char *bright_black_bg;
    const char *bright_red_bg;
    const char *bright_green_bg;
    const char *bright_yellow_bg;
    const char *bright_blue_bg;
    const char *bright_purple_bg;
    const char *bright_teal_bg;
    const char *bright_white_bg;
  } f_color;

  #define f_color_initialize_linux     { "0", "1", "4", "5", "7", "8", "30", "31", "32", "33", "34", "35", "36", "37", "40", "41", "42", "43", "44", "45", "46", "47", "30", "31", "32", "33", "34", "35", "36", "37", "40", "41", "42", "43", "44", "45", "46", "47" }
  #define f_color_initialize_xterminal { "0", "1", "4", "5", "7", "8", "30", "31", "32", "33", "34", "35", "36", "37", "40", "41", "42", "43", "44", "45", "46", "47", "90", "91", "92", "93", "94", "95", "96", "97", "100", "101", "102", "103", "104", "105", "106", "107" }
#endif // _di_f_color_

/**
 * Provide global default global instances of f_color structures.
 *
 * Supported instances:
 * - f_color_format_linux: ideal for linux console.
 * - f_color_format_xterminal: ideal for linux x-terminal.
 */
#ifndef _di_f_color_default_
  static const f_color_format f_color_format_linux     = f_color_format_initialize_linux;
  static const f_color_format f_color_format_xterminal = f_color_format_initialize_xterminal;

  static const f_color f_color_linux     = f_color_initialize_linux;
  static const f_color f_color_xterminal = f_color_initialize_xterminal;
#endif // _di_f_color_default_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_color_h
