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
#include <level_0/string.h>

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

#ifndef _di_f_color_format_t_
  typedef struct {
    const int8_t *begin;
    const int8_t *end;
    const int8_t *medium;
  } f_color_format_t;

  #define f_color_format_t_initialize_linux     { "\033[", "m", ";" }
  #define f_color_format_t_initialize_xterminal { "\033[", "m", ";" }

  #define f_macro_color_format_t_clear(format) \
    format.begin = 0; \
    format.end = 0; \
    format.medium = 0;

  #define f_macro_color_format_t_set_linux(format) \
    format.begin = "\033["; \
    format.end = "m"; \
    format.medium =  ";";

  #define f_macro_color_format_t_set_xterminal(format) \
    format.begin = "\033["; \
    format.end = "m"; \
    format.medium =  ";";
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

  #define f_macro_color_t_clear(color) \
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

  #define f_macro_color_t_set_linux(color) \
    color.reset = "0"; \
    color.bold = "1"; \
    color.underline = "4"; \
    color.blink = "5"; \
    color.reverse = "7"; \
    color.conceal = "8"; \
    color.black = "30"; \
    color.red = "31"; \
    color.green = "32"; \
    color.yellow = "33"; \
    color.blue = "34"; \
    color.purple = "35"; \
    color.teal = "36"; \
    color.white = "37"; \
    color.black_bg = "40"; \
    color.red_bg = "41"; \
    color.green_bg = "42"; \
    color.yellow_bg = "43"; \
    color.blue_bg = "44"; \
    color.purple_bg = "45"; \
    color.teal_bg = "46"; \
    color.white_bg = "47"; \
    color.bright_black = "30"; \
    color.bright_red = "31"; \
    color.bright_green = "32"; \
    color.bright_yellow = "33"; \
    color.bright_blue = "34"; \
    color.bright_purple = "35"; \
    color.bright_teal = "36"; \
    color.bright_white = "37"; \
    color.bright_black_bg = "40"; \
    color.bright_red_bg = "41"; \
    color.bright_green_bg = "42"; \
    color.bright_yellow_bg = "43"; \
    color.bright_blue_bg = "44"; \
    color.bright_purple_bg = "45"; \
    color.bright_teal_bg = "46"; \
    color.bright_white_bg = "47";

  #define f_macro_color_t_set_xterminal(color) \
    color.reset = "0"; \
    color.bold = "1"; \
    color.underline = "4"; \
    color.blink = "5"; \
    color.reverse = "7"; \
    color.conceal = "8"; \
    color.black = "30"; \
    color.red = "31"; \
    color.green = "32"; \
    color.yellow = "33"; \
    color.blue = "34"; \
    color.purple = "35"; \
    color.teal = "36"; \
    color.white = "37"; \
    color.black_bg = "40"; \
    color.red_bg = "41"; \
    color.green_bg = "42"; \
    color.yellow_bg = "43"; \
    color.blue_bg = "44"; \
    color.purple_bg = "45"; \
    color.teal_bg = "46"; \
    color.white_bg = "47"; \
    color.bright_black = "90"; \
    color.bright_red = "91"; \
    color.bright_green = "92"; \
    color.bright_yellow = "93"; \
    color.bright_blue = "94"; \
    color.bright_purple= "95"; \
    color.bright_teal = "96"; \
    color.bright_white = "97"; \
    color.bright_black_bg = "100"; \
    color.bright_red_bg = "101"; \
    color.bright_green_bg = "102"; \
    color.bright_yellow_bg = "103"; \
    color.bright_blue_bg = "104"; \
    color.bright_purple_bg = "105"; \
    color.bright_teal_bg = "106"; \
    color.bright_white_bg = "107";
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

  #define f_macro_color_set_t_initialize(before, after) { before, after }

  #define f_macro_color_set_t_clear(set) \
    set.before = 0; \
    set.after = 0;
#endif // _di_f_color_set_t_

/**
 * Provide a global (static) color set of global (static) empty strings.
 */
#ifndef _di_f_color_set_string_empty_s_
  const static f_color_set_t f_color_set_empty_s = f_macro_color_set_t_initialize(&f_string_static_empty_s, &f_string_static_empty_s);
#endif // _di_f_color_set_string_empty_s_

/**
 * Provide a set of color contexts.
 *
 * This is intended to be used for printing, such that the printed code is prefixed with the "before" and postfixed with the "after", for each context.
 *
 * warning:      Color context associated with "warning".
 * error:        Color context associated with "error".
 * title:        Color context associated with "title".
 * notable:      Color context associated with "notable".
 * important:    Color context associated with "important".
 * standout:     Color context associated with "standout".
 * normal:       Color context associated with "normal".
 * normal_reset: Color context associated with "normal_reset".
 */
#ifndef _di_f_color_set_context_t_
  typedef struct {
    f_color_set_t warning;
    f_color_set_t error;
    f_color_set_t title;
    f_color_set_t notable;
    f_color_set_t important;
    f_color_set_t standout;
    f_color_set_t normal;
    f_color_set_t normal_reset;
  } f_color_set_context_t;

  #define f_color_set_context_t_initialize { f_color_set_t_initialize, f_color_set_t_initialize, f_color_set_t_initialize, f_color_set_t_initialize, f_color_set_t_initialize, f_color_set_t_initialize, f_color_set_t_initialize, f_color_set_t_initialize }

  #define f_macro_color_set_context_t_initialize(warning, error, title, notable, important, standout, normal, normal_reset) { warning, error, title, notable, important, standout, normal, normal_reset }

  #define f_macro_color_set_context_t_clear(set) \
    f_macro_color_set_t_clear(set.warning); \
    f_macro_color_set_t_clear(set.error); \
    f_macro_color_set_t_clear(set.title); \
    f_macro_color_set_t_clear(set.notable); \
    f_macro_color_set_t_clear(set.important); \
    f_macro_color_set_t_clear(set.standout); \
    f_macro_color_set_t_clear(set.normal); \
    f_macro_color_set_t_clear(set.normal_reset);

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
 * warning:      Color context associated with "warning".
 * error:        Color context associated with "error".
 * title:        Color context associated with "title".
 * notable:      Color context associated with "notable".
 * important:    Color context associated with "important".
 * standout:     Color context associated with "standout".
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
    f_string_dynamic_t normal;
    f_string_dynamic_t normal_reset;
  } f_color_context_t;

  #define f_color_context_t_initialize { f_color_t_initialize_linux, f_color_format_t_initialize_linux, f_color_mode_none, f_color_set_context_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize, f_string_dynamic_t_initialize }

  #define f_macro_color_context_t_clear(context) \
    f_macro_color_t_clear(context.list); \
    f_macro_color_format_t_clear(context.format); \
    context.mode = f_color_mode_none; \
    f_macro_color_set_context_t_clear(context.set); \
    f_macro_string_dynamic_t_clear(context.error); \
    f_macro_string_dynamic_t_clear(context.title); \
    f_macro_string_dynamic_t_clear(context.notable); \
    f_macro_string_dynamic_t_clear(context.important); \
    f_macro_string_dynamic_t_clear(context.standout); \
    f_macro_string_dynamic_t_clear(context.normal); \
    f_macro_string_dynamic_t_clear(context.normal_reset);

  #define f_macro_color_context_t_new(status, context) \
    f_macro_string_dynamic_t_new(status, context.reset, f_color_max_size + 1); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_new(status, context.warning,      f_color_max_size + 1); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_new(status, context.error,        f_color_max_size + 1); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_new(status, context.title,        f_color_max_size + 1); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_new(status, context.notable,      f_color_max_size + 1); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_new(status, context.important,    f_color_max_size + 1); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_new(status, context.standout,     f_color_max_size + 1); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_new(status, context.normal,       f_color_max_size + 1); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_new(status, context.normal_reset, f_color_max_size + 1);

  #define f_macro_color_context_t_delete(status, context) \
    f_macro_string_dynamic_t_delete(status, context.reset); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_delete(status, context.warning); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_delete(status, context.error); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_delete(status, context.title); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_delete(status, context.notable); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_delete(status, context.important); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_delete(status, context.standout); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_delete(status, context.normal); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_delete(status, context.normal_reset); \
    if (F_status_is_error_not(status)) f_macro_color_context_t_clear(context);

  #define f_macro_color_context_t_destroy(status, context, size) \
    f_macro_string_dynamic_t_destroy(status, context.reset); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_destroy(status, context.warning, size); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_destroy(status, context.error, size); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_destroy(status, context.title, size); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_destroy(status, context.notable, size); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_destroy(status, context.important, size); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_destroy(status, context.standout, size); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_destroy(status, context.normal); \
    if (F_status_is_error_not(status)) f_macro_string_dynamic_t_destroy(status, context.normal_reset); \
    if (F_status_is_error_not(status)) f_macro_color_context_t_clear(context);

  #define f_macro_color_context_t_delete_simple(context) \
    f_macro_string_dynamic_t_delete_simple(context.reset); \
    f_macro_string_dynamic_t_delete_simple(context.warning); \
    f_macro_string_dynamic_t_delete_simple(context.error); \
    f_macro_string_dynamic_t_delete_simple(context.title); \
    f_macro_string_dynamic_t_delete_simple(context.notable); \
    f_macro_string_dynamic_t_delete_simple(context.important); \
    f_macro_string_dynamic_t_delete_simple(context.standout); \
    f_macro_string_dynamic_t_delete_simple(context.normal); \
    f_macro_string_dynamic_t_delete_simple(context.normal_reset); \
    f_macro_color_context_t_clear(context);

  #define f_macro_color_context_t_destroy_simple(context, size) \
    f_macro_string_dynamic_t_destroy_simple(context.reset); \
    f_macro_string_dynamic_t_destroy_simple(context.warning, size); \
    f_macro_string_dynamic_t_destroy_simple(context.error, size); \
    f_macro_string_dynamic_t_destroy_simple(context.title, size); \
    f_macro_string_dynamic_t_destroy_simple(context.notable, size); \
    f_macro_string_dynamic_t_destroy_simple(context.important, size); \
    f_macro_string_dynamic_t_destroy_simple(context.standout, size); \
    f_macro_string_dynamic_t_destroy_simple(context.normal); \
    f_macro_string_dynamic_t_destroy_simple(context.normal_reset); \
    f_macro_color_context_t_clear(context);
#endif // _di_fl_color_context_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_color_h
