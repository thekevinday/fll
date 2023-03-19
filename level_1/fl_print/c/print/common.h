/**
 * FLL - Level 1
 *
 * Project: Print
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by project print.
 *
 * This is auto-included by print.h and should not need to be explicitly included.
 */
#ifndef _FL_print_common_h
#define _FL_print_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Special print strings.
 *
 * fl_print_*_s:
 *   - debug:   A string used as part of the message when printing a debug.
 *   - error:   A string used as part of the message when printing an error.
 *   - warning: A string used as part of the message when printing a warning.
 */
#ifndef _di_fl_print_s_
  #define FL_print_debug_s   "DEBUG: "
  #define FL_print_error_s   "ERROR: "
  #define FL_print_warning_s "WARNING: "

  #define FL_print_debug_s_length   7
  #define FL_print_error_s_length   7
  #define FL_print_warning_s_length 9

  #ifndef _di_fl_print_debug_s_
    extern const f_string_static_t fl_print_debug_s;
  #endif // _di_fl_print_debug_s_

  #ifndef _di_fl_print_error_s_
    extern const f_string_static_t fl_print_error_s;
  #endif // _di_fl_print_error_s_

  #ifndef _di_fl_print_warning_s_
    extern const f_string_static_t fl_print_warning_s;
  #endif // _di_fl_print_warning_s_
#endif // _di_fl_print_s_

/**
 * Structure for facilitating colored or other managed printing.
 *
 * to:        The file to print to.
 * verbosity: The verbosity mode.
 * flag:      A set of flags, bitwise or otherwise, made available for more advanced manipulation.
 *
 * prefix: An optional prefix string for displaying before any special messages.
 * suffix: An optional suffix string for displaying after any special messages.
 *
 * context: The color codes for the entire error message.
 * notable: The color codes for a part of the message to make more visible.
 * set:     An optional pointer to a set of all available color contexts for explicit use.
 *
 * custom: A pointer to a data structure determined by some caller for more advanced manipulation.
 */
#ifndef _di_fl_print_t_
  typedef struct {
    f_file_t to;
    uint8_t verbosity;
    uint64_t flag;

    f_string_static_t prefix;
    f_string_static_t suffix;

    f_color_set_t context;
    f_color_set_t notable;
    f_color_set_context_t *set;

    void *custom;
  } fl_print_t;

  #define fl_print_t_initialize { \
    macro_f_file_t_initialize2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d), \
    f_console_verbosity_normal_e, \
    0, \
    f_string_static_t_initialize, \
    f_string_static_t_initialize, \
    f_color_set_t_initialize, \
    f_color_set_t_initialize, \
    0, \
    0, \
  }

  #define macro_fl_print_t_initialize(to, verbosity, flag, prefix, suffix, context, notable, set, custom) { \
    to, \
    verbosity, \
    flag, \
    prefix, \
    suffix, \
    context, \
    notable, \
    set, \
    custom, \
  }

  #define macro_fl_print_t_initialize_debug()               macro_fl_print_t_initialize(macro_f_file_t_initialize2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d), f_console_verbosity_normal_e, 0, fl_print_debug_s, f_string_static_t_initialize, f_color_set_t_initialize, f_color_set_t_initialize, 0, 0)
  #define macro_fl_print_t_initialize_debug2(suffix, set)   macro_fl_print_t_initialize(macro_f_file_t_initialize2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d), f_console_verbosity_normal_e, 0, fl_print_debug_s, suffix, f_color_set_t_initialize, f_color_set_t_initialize, set, 0)
  #define macro_fl_print_t_initialize_error()               macro_fl_print_t_initialize(macro_f_file_t_initialize2(F_type_error_d, F_type_descriptor_error_d, F_file_flag_write_only_d), f_console_verbosity_normal_e, 0, fl_print_error_s, f_string_static_t_initialize, f_color_set_t_initialize, f_color_set_t_initialize, 0, 0)
  #define macro_fl_print_t_initialize_error2(suffix, set)   macro_fl_print_t_initialize(macro_f_file_t_initialize2(F_type_error_d, F_type_descriptor_error_d, F_file_flag_write_only_d), f_console_verbosity_normal_e, 0, fl_print_error_s, suffix, f_color_set_t_initialize, f_color_set_t_initialize, set, 0)
  #define macro_fl_print_t_initialize_warning()             macro_fl_print_t_initialize(macro_f_file_t_initialize2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d), f_console_verbosity_normal_e, 0, fl_print_warning_s, f_string_static_t_initialize, f_color_set_t_initialize, f_color_set_t_initialize, 0, 0)
  #define macro_fl_print_t_initialize_warning2(suffix, set) macro_fl_print_t_initialize(macro_f_file_t_initialize2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d), f_console_verbosity_normal_e, 0, fl_print_warning_s, suffix, f_color_set_t_initialize, f_color_set_t_initialize, set, 0)
#endif // _di_fl_print_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_print_common_h
