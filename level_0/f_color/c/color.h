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
#include <level_0/type.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_color_max_size_
  #define f_color_max_size 7
#endif // _di_f_color_max_size_

#ifndef _di_f_color_types_t_
  typedef uint8_t f_color_code_t;

  #define f_color_code_none      0
  #define f_color_code_linux     1
  #define f_color_code_xterminal 2
#endif // _di_f_color_types_t_

/**
 * Specify color modes.
 *
 * Color modes communicate how the color is supposed to be.
 *
 * The f_color_mode_none define designates that there is no assigned mode (the mode is undefined).
 * The f_color_mode_no_color define designates that the color mode is set to no color (disable colors).
 */
#ifndef _di_f_color_mode_t_
  typedef uint8_t f_color_mode_t;

  #define f_color_mode_none      0
  #define f_color_mode_no_color  1
  #define f_color_mode_dark      2
  #define f_color_mode_light     3
#endif // _di_f_color_mode_t_

/**
 * The purpose behind these data types are not to dynamically allocate data.
 * instead, they are intended to only point to existing data, so these should neither be allocated nor deallocated.
 */
#ifndef _di_f_color_control_t_
  typedef struct {
    const int8_t *blink;
    const int8_t *bold;
    const int8_t *conceal;
    const int8_t *reverse;
    const int8_t *underline;
  } f_color_control_t;

  #define f_color_control_t_initialize_names { "blink", "bold", "conceal", "reverse", "underline" }
#endif // _di_f_color_control_t_

/**
 * strong represents emphasis.
 */
#ifndef _di_f_color_standard_io_t_
  typedef struct {
    const int8_t *error;
    const int8_t *message;
    const int8_t *warning;
    const int8_t *strong_error;
    const int8_t *strong_message;
    const int8_t *strong_warning;
  } f_color_standard_io_t;

  #define f_color_standard_io_t_initialize_names { "error", "message", "warning", "strong_error", "strong_message", "strong_warning" }
#endif // _di_f_color_standard_io_t_

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
#ifndef _di_f_color_help_t_
  typedef struct {
    const int8_t *alert;
    const int8_t *command;
    const int8_t *comment;
    const int8_t *emphasize;
    const int8_t *standard;
    const int8_t *syntax;
    const int8_t *title;
    const int8_t *topic;
    const int8_t *version;
  } f_color_help_t;

  #define f_color_help_t_initialize_names { "alert", "command", "comment", "emphasize", "standard", "syntax", "title", "topic", "version" }
#endif // _di_f_color_help_t_

#ifndef _di_f_color_format_t_
  typedef struct {
    const int8_t *begin;
    const int8_t *end;
    const int8_t *medium;
  } f_color_format_t;

  #define f_color_format_t_initialize_linux     { "\033[", "m", ";" }
  #define f_color_format_t_initialize_xterminal { "\033[", "m", ";" }
#endif // _di_f_color_format_t_

/**
 * A structure containing all supported color codes.
 *
 * Different system will support a different set.
 *
 * Custom initializers are provided for common defaults:
 * - f_color_t_initialize_linux: ideal for linux console.
 * - f_color_t_initialize_xterminal: ideal for linux x-terminal.
 */
#ifndef _di_f_color_t_
  typedef struct {
    const int8_t *reset;
    const int8_t *bold;
    const int8_t *underline;
    const int8_t *blink;
    const int8_t *reverse;
    const int8_t *conceal;
    const int8_t *black;
    const int8_t *red;
    const int8_t *green;
    const int8_t *yellow;
    const int8_t *blue;
    const int8_t *purple;
    const int8_t *teal;
    const int8_t *white;
    const int8_t *black_bg;
    const int8_t *red_bg;
    const int8_t *green_bg;
    const int8_t *yellow_bg;
    const int8_t *blue_bg;
    const int8_t *purple_bg;
    const int8_t *teal_bg;
    const int8_t *white_bg;
    const int8_t *bright_black;
    const int8_t *bright_red;
    const int8_t *bright_green;
    const int8_t *bright_yellow;
    const int8_t *bright_blue;
    const int8_t *bright_purple;
    const int8_t *bright_teal;
    const int8_t *bright_white;
    const int8_t *bright_black_bg;
    const int8_t *bright_red_bg;
    const int8_t *bright_green_bg;
    const int8_t *bright_yellow_bg;
    const int8_t *bright_blue_bg;
    const int8_t *bright_purple_bg;
    const int8_t *bright_teal_bg;
    const int8_t *bright_white_bg;
  } f_color_t;

  #define f_color_t_initialize_linux     { "0", "1", "4", "5", "7", "8", "30", "31", "32", "33", "34", "35", "36", "37", "40", "41", "42", "43", "44", "45", "46", "47", "30", "31", "32", "33", "34", "35", "36", "37", "40", "41", "42", "43", "44", "45", "46", "47" }
  #define f_color_t_initialize_xterminal { "0", "1", "4", "5", "7", "8", "30", "31", "32", "33", "34", "35", "36", "37", "40", "41", "42", "43", "44", "45", "46", "47", "90", "91", "92", "93", "94", "95", "96", "97", "100", "101", "102", "103", "104", "105", "106", "107" }
#endif // _di_f_color_t_

/**
 * Provide global default global instances of f_color_t structures.
 *
 * Supported instances:
 * - f_color_format_linux: ideal for linux console.
 * - f_color_format_xterminal: ideal for linux x-terminal.
 */
#ifndef _di_f_color_default_
  static const f_color_format_t f_color_format_linux     = f_color_format_t_initialize_linux;
  static const f_color_format_t f_color_format_xterminal = f_color_format_t_initialize_xterminal;

  static const f_color_t f_color_linux     = f_color_t_initialize_linux;
  static const f_color_t f_color_xterminal = f_color_t_initialize_xterminal;
#endif // _di_f_color_default_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_color_h
