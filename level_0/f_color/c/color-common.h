/**
 * FLL - Level 0
 *
 * Project: Color
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines common data to be used for/by project color.
 *
 * This is auto-included by color.h and should not need to be explicitly included.
 */
#ifndef _F_color_common_h
#define _F_color_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Color max size represents the maximum length of the resulting color string.
 *
 * This color max size does not include the terminating null.
 *
 * A color max size terminated represents the max size with the terminating null.
 */
#ifndef _di_f_color_max_size_
  #define F_color_max_size_d            7
  #define F_color_max_size_terminated_d 8
#endif // _di_f_color_max_size_

#ifndef _di_f_color_types_t_
  typedef char f_color_code_t;

  #define F_color_code_none_d      0
  #define F_color_code_linux_d     1
  #define F_color_code_xterminal_d 2
#endif // _di_f_color_types_t_

/**
 * Provide a global color related strings.
 */
#ifndef _di_f_color_strings_s_
  #define F_color_string_begin_s  "\033[";
  #define F_color_string_end_s    "m";
  #define F_color_string_medium_s ";";

  #define F_color_string_code_reset_s            "0"
  #define F_color_string_code_bold_s             "1"
  #define F_color_string_code_underline_s        "4"
  #define F_color_string_code_blink_s            "5"
  #define F_color_string_code_reverse_s          "7"
  #define F_color_string_code_conceal_s          "8"
  #define F_color_string_code_black_s            "30"
  #define F_color_string_code_red_s              "31"
  #define F_color_string_code_green_s            "32"
  #define F_color_string_code_yellow_s           "33"
  #define F_color_string_code_blue_s             "34"
  #define F_color_string_code_purple_s           "35"
  #define F_color_string_code_teal_s             "36"
  #define F_color_string_code_white_s            "37"
  #define F_color_string_code_black_bg_s         "40"
  #define F_color_string_code_red_bg_s           "41"
  #define F_color_string_code_green_bg_s         "42"
  #define F_color_string_code_yellow_bg_s        "43"
  #define F_color_string_code_blue_bg_s          "44"
  #define F_color_string_code_purple_bg_s        "45"
  #define F_color_string_code_teal_bg_s          "46"
  #define F_color_string_code_white_bg_s         "47"
  #define F_color_string_code_bright_black_s     "90"
  #define F_color_string_code_bright_red_s       "91"
  #define F_color_string_code_bright_green_s     "92"
  #define F_color_string_code_bright_yellow_s    "93"
  #define F_color_string_code_bright_blue_s      "94"
  #define F_color_string_code_bright_purple_s    "95"
  #define F_color_string_code_bright_teal_s      "96"
  #define F_color_string_code_bright_white_s     "97"
  #define F_color_string_code_bright_black_bg_s  "100"
  #define F_color_string_code_bright_red_bg_s    "101"
  #define F_color_string_code_bright_green_bg_s  "102"
  #define F_color_string_code_bright_yellow_bg_s "103"
  #define F_color_string_code_bright_blue_bg_s   "104"
  #define F_color_string_code_bright_purple_bg_s "105"
  #define F_color_string_code_bright_teal_bg_s   "106"
  #define F_color_string_code_bright_white_bg_s  "107"

  extern const f_string_t f_color_string_begin_s;
  extern const f_string_t f_color_string_end_s;
  extern const f_string_t f_color_string_medium_s;

  extern const f_string_t f_color_string_code_reset_s;
  extern const f_string_t f_color_string_code_bold_s;
  extern const f_string_t f_color_string_code_underline_s;
  extern const f_string_t f_color_string_code_blink_s;
  extern const f_string_t f_color_string_code_reverse_s;
  extern const f_string_t f_color_string_code_conceal_s;
  extern const f_string_t f_color_string_code_black_s;
  extern const f_string_t f_color_string_code_red_s;
  extern const f_string_t f_color_string_code_green_s;
  extern const f_string_t f_color_string_code_yellow_s;
  extern const f_string_t f_color_string_code_blue_s;
  extern const f_string_t f_color_string_code_purple_s;
  extern const f_string_t f_color_string_code_teal_s;
  extern const f_string_t f_color_string_code_white_s;
  extern const f_string_t f_color_string_code_black_bg_s;
  extern const f_string_t f_color_string_code_red_bg_s;
  extern const f_string_t f_color_string_code_green_bg_s;
  extern const f_string_t f_color_string_code_yellow_bg_s;
  extern const f_string_t f_color_string_code_blue_bg_s;
  extern const f_string_t f_color_string_code_purple_bg_s;
  extern const f_string_t f_color_string_code_teal_bg_s;
  extern const f_string_t f_color_string_code_white_bg_s;
  extern const f_string_t f_color_string_code_bright_black_s;
  extern const f_string_t f_color_string_code_bright_red_s;
  extern const f_string_t f_color_string_code_bright_green_s;
  extern const f_string_t f_color_string_code_bright_yellow_s;
  extern const f_string_t f_color_string_code_bright_blue_s;
  extern const f_string_t f_color_string_code_bright_purple_s;
  extern const f_string_t f_color_string_code_bright_teal_s;
  extern const f_string_t f_color_string_code_bright_white_s;
  extern const f_string_t f_color_string_code_bright_black_bg_s;
  extern const f_string_t f_color_string_code_bright_red_bg_s;
  extern const f_string_t f_color_string_code_bright_green_bg_s;
  extern const f_string_t f_color_string_code_bright_yellow_bg_s;
  extern const f_string_t f_color_string_code_bright_blue_bg_s;
  extern const f_string_t f_color_string_code_bright_purple_bg_s;
  extern const f_string_t f_color_string_code_bright_teal_bg_s;
  extern const f_string_t f_color_string_code_bright_white_bg_s;
#endif // _di_f_color_strings_s_

/**
 * Specify color modes.
 *
 * Color modes communicate how the color is supposed to be.
 *
 * F_color_mode_*:
 * - none:     define designates that there is no assigned mode (the mode is undefined).
 * - no_color: define designates that the color mode is set to no color (disable colors).
 * - dark:     define designates that the color mode is for dark backgrounds.
 * - light:    define designates that the color mode is for light backgrounds.
 */
#ifndef _di_f_color_mode_t_
  typedef uint8_t f_color_mode_t;

  #define F_color_mode_none_d      0
  #define F_color_mode_no_color_d  1
  #define F_color_mode_dark_d      2
  #define F_color_mode_light_d     3
#endif // _di_f_color_mode_t_

#ifndef _di_f_color_format_t_
  typedef struct {
    const char *begin;
    const char *end;
    const char *medium;
  } f_color_format_t;

  #define f_color_format_t_initialize_linux     { f_color_string_begin_s, f_color_string_end_s, f_color_string_medium_s }
  #define f_color_format_t_initialize_xterminal { f_color_string_begin_s, f_color_string_end_s, f_color_string_medium_s }

  #define macro_f_color_format_t_clear(format) \
    format.begin = 0; \
    format.end = 0; \
    format.medium = 0;

  #define macro_f_color_format_t_set_linux(format) \
    format.begin = f_color_string_begin_s; \
    format.end = f_color_string_end_s; \
    format.medium = f_color_string_medium_s;

  #define macro_f_color_format_t_set_xterminal(format) \
    format.begin = f_color_string_begin_s; \
    format.end = f_color_string_end_s; \
    format.medium = f_color_string_medium_s;
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
  } f_color_t;

  #define f_color_t_initialize_linux     { f_color_string_code_reset_s, f_color_string_code_bold_s, f_color_string_code_underline_s, f_color_string_code_blink_s, f_color_string_code_reverse_s, f_color_string_code_conceal_s, f_color_string_code_black_s, f_color_string_code_red_s, f_color_string_code_green_s, f_color_string_code_yellow_s, f_color_string_code_blue_s, f_color_string_code_purple_s, f_color_string_code_teal_s, f_color_string_code_white_s, f_color_string_code_black_bg_s, f_color_string_code_red_bg_s, f_color_string_code_green_bg_s, f_color_string_code_yellow_bg_s, f_color_string_code_blue_bg_s, f_color_string_code_purple_bg_s, f_color_string_code_teal_bg_s, f_color_string_code_white_bg_s, f_color_string_code_black_s, f_color_string_code_red_s, f_color_string_code_green_s, f_color_string_code_yellow_s, f_color_string_code_blue_s, f_color_string_code_purple_s, f_color_string_code_teal_s, f_color_string_code_white_s, f_color_string_code_black_bg_s, f_color_string_code_red_bg_s, f_color_string_code_green_bg_s, f_color_string_code_yellow_bg_s, f_color_string_code_blue_bg_s, f_color_string_code_purple_bg_s, f_color_string_code_teal_bg_s, f_color_string_code_white_bg_s }
  #define f_color_t_initialize_xterminal { f_color_string_code_reset_s, f_color_string_code_bold_s, f_color_string_code_underline_s, f_color_string_code_blink_s, f_color_string_code_reverse_s, f_color_string_code_conceal_s, f_color_string_code_black_s, f_color_string_code_red_s, f_color_string_code_green_s, f_color_string_code_yellow_s, f_color_string_code_blue_s, f_color_string_code_purple_s, f_color_string_code_teal_s, f_color_string_code_white_s, f_color_string_code_black_bg_s, f_color_string_code_red_bg_s, f_color_string_code_green_bg_s, f_color_string_code_yellow_bg_s, f_color_string_code_blue_bg_s, f_color_string_code_purple_bg_s, f_color_string_code_teal_bg_s, f_color_string_code_white_bg_s, f_color_string_code_bright_black_s, f_color_string_code_bright_red_s, f_color_string_code_bright_green_s, f_color_string_code_bright_yellow_s, f_color_string_code_bright_blue_s, f_color_string_code_bright_purple_s, f_color_string_code_bright_teal_s, f_color_string_code_bright_white_s, f_color_string_code_bright_black_bg_s, f_color_string_code_bright_red_bg_s, f_color_string_code_bright_green_bg_s, f_color_string_code_bright_yellow_bg_s, f_color_string_code_bright_blue_bg_s, f_color_string_code_bright_purple_bg_s, f_color_string_code_bright_teal_bg_s, f_color_string_code_bright_white_bg_s }

  #define macro_f_color_t_clear(color) \
    color.reset = 0; \
    color.bold = 0; \
    color.underline = 0; \
    color.blink = 0; \
    color.reverse = 0; \
    color.conceal = 0; \
    color.black = 0; \
    color.red = 0; \
    color.green = 0; \
    color.yellow = 0; \
    color.blue = 0; \
    color.purple = 0; \
    color.teal = 0; \
    color.white = 0; \
    color.black_bg = 0; \
    color.red_bg = 0; \
    color.green_bg = 0; \
    color.yellow_bg = 0; \
    color.blue_bg = 0; \
    color.purple_bg = 0; \
    color.teal_bg = 0; \
    color.white_bg = 0; \
    color.bright_black = 0; \
    color.bright_red = 0; \
    color.bright_green = 0; \
    color.bright_yellow = 0; \
    color.bright_blue = 0; \
    color.bright_purple = 0; \
    color.bright_teal = 0; \
    color.bright_white = 0; \
    color.bright_black_bg = 0; \
    color.bright_red_bg = 0; \
    color.bright_green_bg = 0; \
    color.bright_yellow_bg = 0; \
    color.bright_blue_bg = 0; \
    color.bright_purple_bg = 0; \
    color.bright_teal_bg = 0; \
    color.bright_white_bg = 0;

  #define macro_f_color_t_set_linux(color) \
    color.reset = f_color_string_code_reset_s; \
    color.bold = f_color_string_code_bold_s; \
    color.underline = f_color_string_code_underline_s; \
    color.blink = f_color_string_code_blink_s; \
    color.reverse = f_color_string_code_reverse_s; \
    color.conceal = f_color_string_code_conceal_s; \
    color.black = f_color_string_code_black_s; \
    color.red = f_color_string_code_red_s; \
    color.green = f_color_string_code_green_s; \
    color.yellow = f_color_string_code_yellow_s; \
    color.blue = f_color_string_code_blue_s; \
    color.purple = f_color_string_code_purple_s; \
    color.teal = f_color_string_code_teal_s; \
    color.white = f_color_string_code_white_s; \
    color.black_bg = f_color_string_code_black_bg_s; \
    color.red_bg = f_color_string_code_red_bg_s; \
    color.green_bg = f_color_string_code_green_bg_s; \
    color.yellow_bg = f_color_string_code_yellow_bg_s; \
    color.blue_bg = f_color_string_code_blue_bg_s; \
    color.purple_bg = f_color_string_code_purple_bg_s; \
    color.teal_bg = f_color_string_code_teal_bg_s; \
    color.white_bg = f_color_string_code_white_bg_s; \
    color.bright_black = f_color_string_code_black_s; \
    color.bright_red = f_color_string_code_red_s; \
    color.bright_green = f_color_string_code_green_s; \
    color.bright_yellow = f_color_string_code_yellow_s; \
    color.bright_blue = f_color_string_code_blue_s; \
    color.bright_purple = f_color_string_code_purple_s; \
    color.bright_teal = f_color_string_code_teal_s; \
    color.bright_white = f_color_string_code_white_s; \
    color.bright_black_bg = f_color_string_code_black_bg_s; \
    color.bright_red_bg = f_color_string_code_red_bg_s; \
    color.bright_green_bg = f_color_string_code_green_bg_s; \
    color.bright_yellow_bg = f_color_string_code_yellow_bg_s; \
    color.bright_blue_bg = f_color_string_code_blue_bg_s; \
    color.bright_purple_bg = f_color_string_code_purple_bg_s; \
    color.bright_teal_bg = f_color_string_code_teal_bg_s; \
    color.bright_white_bg = f_color_string_code_white_bg_s;

  #define macro_f_color_t_set_xterminal(color) \
    color.reset = f_color_string_code_reset_s; \
    color.bold = f_color_string_code_bold_s; \
    color.underline = f_color_string_code_underline_s; \
    color.blink = f_color_string_code_blink_s; \
    color.reverse = f_color_string_code_reverse_s; \
    color.conceal = f_color_string_code_conceal_s; \
    color.black = f_color_string_code_black_s; \
    color.red = f_color_string_code_red_s; \
    color.green = f_color_string_code_green_s; \
    color.yellow = f_color_string_code_yellow_s; \
    color.blue = f_color_string_code_blue_s; \
    color.purple = f_color_string_code_purple_s; \
    color.teal = f_color_string_code_teal_s; \
    color.white = f_color_string_code_white_s; \
    color.black_bg = f_color_string_code_black_bg_s; \
    color.red_bg = f_color_string_code_red_bg_s; \
    color.green_bg = f_color_string_code_green_bg_s; \
    color.yellow_bg = f_color_string_code_yellow_bg_s; \
    color.blue_bg = f_color_string_code_blue_bg_s; \
    color.purple_bg = f_color_string_code_purple_bg_s; \
    color.teal_bg = f_color_string_code_teal_bg_s; \
    color.white_bg = f_color_string_code_white_bg_s; \
    color.bright_black = f_color_string_code_bright_black_s; \
    color.bright_red = f_color_string_code_bright_red_s; \
    color.bright_green = f_color_string_code_bright_green_s; \
    color.bright_yellow = f_color_string_code_bright_yellow_s; \
    color.bright_blue = f_color_string_code_bright_blue_s; \
    color.bright_purple = f_color_string_code_bright_purple_s; \
    color.bright_teal = f_color_string_code_bright_teal_s; \
    color.bright_white = f_color_string_code_bright_white_s; \
    color.bright_black_bg = f_color_string_code_bright_black_bg_s; \
    color.bright_red_bg = f_color_string_code_bright_red_bg_s; \
    color.bright_green_bg = f_color_string_code_bright_green_bg_s; \
    color.bright_yellow_bg = f_color_string_code_bright_yellow_bg_s; \
    color.bright_blue_bg = f_color_string_code_bright_blue_bg_s; \
    color.bright_purple_bg = f_color_string_code_bright_purple_bg_s; \
    color.bright_teal_bg = f_color_string_code_bright_teal_bg_s; \
    color.bright_white_bg = f_color_string_code_bright_white_bg_s;
#endif // _di_f_color_t_

/**
 * Provide a set of two colors, a before and an after.
 *
 * This is intended to be used for printing, such that the printed code is prefixed with the "before" and postfixed with the "after".
 * These color strings should be NULL terminated.
 *
 * before: A pointer to the dynamic string representing the before color to assign, set to NULL to disable.
 * after:  A pointer to the dynamic string representing the after color to assign, set to NULL to disable.
 */
#ifndef _di_f_color_set_t_
  typedef struct {
    const f_string_static_t *before;
    const f_string_static_t *after;
  } f_color_set_t;

  #define f_color_set_t_initialize { 0, 0 }

  #define macro_f_color_set_t_initialize(before, after) { before, after }

  #define macro_f_color_set_t_clear(set) \
    set.before = 0; \
    set.after = 0;
#endif // _di_f_color_set_t_

/**
 * Provide a global color set of global (static) empty strings.
 */
#ifndef _di_f_color_set_string_empty_s_
  extern const f_color_set_t f_color_set_empty_s;
#endif // _di_f_color_set_string_empty_s_

/**
 * Provide a set of color contexts.
 *
 * This is intended to be used for printing, such that the printed code is prefixed with the "before" and postfixed with the "after", for each context.
 *
 * reset:        Reset the color context.
 * warning:      Color context associated with "warning".
 * error:        Color context associated with "error".
 * title:        Color context associated with "title".
 * notable:      Color context associated with "notable".
 * important:    Color context associated with "important".
 * standout:     Color context associated with "standout".
 * success:      Color context associated with "success".
 * normal:       Color context associated with "normal".
 * normal_reset: Color context associated with "normal_reset".
 */
#ifndef _di_f_color_set_context_t_
  typedef struct {
    f_color_set_t reset;
    f_color_set_t warning;
    f_color_set_t error;
    f_color_set_t title;
    f_color_set_t notable;
    f_color_set_t important;
    f_color_set_t standout;
    f_color_set_t success;
    f_color_set_t normal;
    f_color_set_t normal_reset;
  } f_color_set_context_t;

  #define f_color_set_context_t_initialize { f_color_set_t_initialize, f_color_set_t_initialize, f_color_set_t_initialize, f_color_set_t_initialize, f_color_set_t_initialize, f_color_set_t_initialize, f_color_set_t_initialize, f_color_set_t_initialize, f_color_set_t_initialize, f_color_set_t_initialize }

  #define macro_f_color_set_context_t_initialize(reset, warning, error, title, notable, important, standout, success, normal, normal_reset) { reset, warning, error, title, notable, important, standout, success, normal, normal_reset }

  #define macro_f_color_set_context_t_clear(set) \
    macro_f_color_set_t_clear(set.reset) \
    macro_f_color_set_t_clear(set.warning) \
    macro_f_color_set_t_clear(set.error) \
    macro_f_color_set_t_clear(set.title) \
    macro_f_color_set_t_clear(set.notable) \
    macro_f_color_set_t_clear(set.important) \
    macro_f_color_set_t_clear(set.standout) \
    macro_f_color_set_t_clear(set.success) \
    macro_f_color_set_t_clear(set.normal) \
    macro_f_color_set_t_clear(set.normal_reset)

#endif // _di_f_color_set_context_t_

/**
 * Provide a color context structure.
 *
 * This is intended to be used for printing, and this provides a management structure for all color context related data.
 *
 * list:         A list of colors, each with their specific color code string.
 * format:       The color code formatting strings.
 * mode:         A code representing the color mode.
 * set:          A collection of color context sets for direct use in color printing.
 * reset:        Reset the color context.
 * warning:      Color context associated with "warning".
 * error:        Color context associated with "error".
 * title:        Color context associated with "title".
 * notable:      Color context associated with "notable".
 * important:    Color context associated with "important".
 * standout:     Color context associated with "standout".
 * success:      Color context associated with "success".
 * normal:       Color context associated with "normal".
 * normal_reset: Color context associated with "normal_reset".
 */
#ifndef _di_f_color_context_t_
  typedef struct {
    f_color_t list;
    f_color_format_t format;
    f_color_mode_t mode;
    f_color_set_context_t set;
    f_string_dynamic_t reset;
    f_string_dynamic_t warning;
    f_string_dynamic_t error;
    f_string_dynamic_t title;
    f_string_dynamic_t notable;
    f_string_dynamic_t important;
    f_string_dynamic_t standout;
    f_string_dynamic_t success;
    f_string_dynamic_t normal;
    f_string_dynamic_t normal_reset;
  } f_color_context_t;

  #define f_color_context_t_initialize { f_color_t_initialize_linux, f_color_format_t_initialize_linux, F_color_mode_none_d, f_color_set_context_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize }

  #define macro_f_color_context_t_clear(context) \
    macro_f_color_t_clear(context.list) \
    macro_f_color_format_t_clear(context.format) \
    context.mode = F_color_mode_none_d; \
    macro_f_color_set_context_t_clear(context.set) \
    macro_f_string_dynamic_t_clear(context.reset) \
    macro_f_string_dynamic_t_clear(context.warning) \
    macro_f_string_dynamic_t_clear(context.error) \
    macro_f_string_dynamic_t_clear(context.title) \
    macro_f_string_dynamic_t_clear(context.notable) \
    macro_f_string_dynamic_t_clear(context.important) \
    macro_f_string_dynamic_t_clear(context.standout) \
    macro_f_string_dynamic_t_clear(context.success) \
    macro_f_string_dynamic_t_clear(context.normal) \
    macro_f_string_dynamic_t_clear(context.normal_reset)

  #define macro_f_color_context_t_new(status, context) \
    macro_f_string_dynamic_t_resize(status, context.reset, F_color_max_size_terminated_d) \
    if (F_status_is_error_not(status)) macro_f_string_dynamic_t_resize(status, context.reset, F_color_max_size_terminated_d) \
    if (F_status_is_error_not(status)) macro_f_string_dynamic_t_resize(status, context.warning, F_color_max_size_terminated_d) \
    if (F_status_is_error_not(status)) macro_f_string_dynamic_t_resize(status, context.error, F_color_max_size_terminated_d) \
    if (F_status_is_error_not(status)) macro_f_string_dynamic_t_resize(status, context.title, F_color_max_size_terminated_d) \
    if (F_status_is_error_not(status)) macro_f_string_dynamic_t_resize(status, context.notable, F_color_max_size_terminated_d) \
    if (F_status_is_error_not(status)) macro_f_string_dynamic_t_resize(status, context.important, F_color_max_size_terminated_d) \
    if (F_status_is_error_not(status)) macro_f_string_dynamic_t_resize(status, context.standout, F_color_max_size_terminated_d) \
    if (F_status_is_error_not(status)) macro_f_string_dynamic_t_resize(status, context.success, F_color_max_size_terminated_d) \
    if (F_status_is_error_not(status)) macro_f_string_dynamic_t_resize(status, context.normal, F_color_max_size_terminated_d) \
    if (F_status_is_error_not(status)) macro_f_string_dynamic_t_resize(status, context.normal_reset, F_color_max_size_terminated_d)

  #define macro_f_color_context_t_delete_simple(context) \
    macro_f_string_dynamic_t_delete_simple(context.reset) \
    macro_f_string_dynamic_t_delete_simple(context.warning) \
    macro_f_string_dynamic_t_delete_simple(context.error) \
    macro_f_string_dynamic_t_delete_simple(context.title) \
    macro_f_string_dynamic_t_delete_simple(context.notable) \
    macro_f_string_dynamic_t_delete_simple(context.important) \
    macro_f_string_dynamic_t_delete_simple(context.standout) \
    macro_f_string_dynamic_t_delete_simple(context.success) \
    macro_f_string_dynamic_t_delete_simple(context.normal) \
    macro_f_string_dynamic_t_delete_simple(context.normal_reset) \
    macro_f_color_context_t_clear(context)

  #define macro_f_color_context_t_destroy_simple(context, size) \
    macro_f_string_dynamic_t_destroy_simple(context.reset) \
    macro_f_string_dynamic_t_destroy_simple(context.warning, size) \
    macro_f_string_dynamic_t_destroy_simple(context.error, size) \
    macro_f_string_dynamic_t_destroy_simple(context.title, size) \
    macro_f_string_dynamic_t_destroy_simple(context.notable, size) \
    macro_f_string_dynamic_t_destroy_simple(context.important, size) \
    macro_f_string_dynamic_t_destroy_simple(context.standout, size) \
    macro_f_string_dynamic_t_destroy_simple(context.success, size) \
    macro_f_string_dynamic_t_destroy_simple(context.normal) \
    macro_f_string_dynamic_t_destroy_simple(context.normal_reset) \
    macro_f_color_context_t_clear(context)
#endif // _di_f_color__context_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_color_common_h
