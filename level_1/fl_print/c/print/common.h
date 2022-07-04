/**
 * FLL - Level 1
 *
 * Project: Print
 * API Version: 0.6
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
 * Structure for facilitating colored or other managed printing.
 *
 * to:        The file to print to.
 * verbosity: The verbosity mode.
 * prefix:    An optional prefix string for displaying before any special messages.
 * suffix:    An optional  suffix string for displaying after any special messages.
 * context:   The color codes for the entire error message.
 * notable:   The color codes for a part of the message to make more visible.
 * set:       An optional pointer to a set of all available color contexts for explicit use.
 */
#ifndef _di_fl_print_t_
  #define FL_print_debug_s   "DEBUG: "
  #define FL_print_error_s   "ERROR: "
  #define FL_print_warning_s "WARNING: "

  #define FL_print_debug_s_length   7
  #define FL_print_error_s_length   7
  #define FL_print_warning_s_length 9

  extern const f_string_static_t fl_print_debug_s;
  extern const f_string_static_t fl_print_error_s;
  extern const f_string_static_t fl_print_warning_s;

  typedef struct {
    f_file_t to;
    uint8_t verbosity;

    f_string_static_t prefix;
    f_string_static_t suffix;

    f_color_set_t context;
    f_color_set_t notable;
    f_color_set_context_t *set;
  } fl_print_t;

  #define fl_print_t_initialize { \
    macro_f_file_t_initialize2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d), \
    f_console_verbosity_normal_e, \
    f_string_static_t_initialize, \
    f_string_static_t_initialize, \
    f_color_set_t_initialize, \
    f_color_set_t_initialize, \
    0, \
  }

  #define macro_fl_print_t_initialize(to, verbosity, prefix, suffix, context, notable, set) { to, verbosity, prefix, suffix, context, notable, set }
  #define macro_fl_print_t_initialize_debug() macro_fl_print_t_initialize(macro_f_file_t_initialize2(F_type_debug_d, F_type_descriptor_debug_d, F_file_flag_write_only_d), f_console_verbosity_normal_e, fl_print_debug_s, f_string_static_t_initialize, f_color_set_t_initialize, f_color_set_t_initialize, 0)
  #define macro_fl_print_t_initialize_debug2(suffix, set) macro_fl_print_t_initialize(macro_f_file_t_initialize2(F_type_debug_d, F_type_descriptor_debug_d, F_file_flag_write_only_d), f_console_verbosity_normal_e, fl_print_debug_s, suffix, f_color_set_t_initialize, f_color_set_t_initialize, set)
  #define macro_fl_print_t_initialize_error() macro_fl_print_t_initialize(macro_f_file_t_initialize2(F_type_error_d, F_type_descriptor_error_d, F_file_flag_write_only_d), f_console_verbosity_normal_e, fl_print_error_s, f_string_static_t_initialize, f_color_set_t_initialize, f_color_set_t_initialize, 0)
  #define macro_fl_print_t_initialize_error2(suffix, set) macro_fl_print_t_initialize(macro_f_file_t_initialize2(F_type_error_d, F_type_descriptor_error_d, F_file_flag_write_only_d), f_console_verbosity_normal_e, fl_print_error_s, suffix, f_color_set_t_initialize, f_color_set_t_initialize, set)
  #define macro_fl_print_t_initialize_warning() macro_fl_print_t_initialize(macro_f_file_t_initialize2(F_type_warning_d, F_type_descriptor_warning_d, F_file_flag_write_only_d), f_console_verbosity_normal_e, fl_print_warning_s, f_string_static_t_initialize, f_color_set_t_initialize, f_color_set_t_initialize, 0)
  #define macro_fl_print_t_initialize_warning2(suffix, set) macro_fl_print_t_initialize(macro_f_file_t_initialize2(F_type_warning_d, F_type_descriptor_warning_d, F_file_flag_write_only_d), f_console_verbosity_normal_e, fl_print_warning_s, suffix, f_color_set_t_initialize, f_color_set_t_initialize, set)
#endif // _di_fl_print_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_print_common_h
