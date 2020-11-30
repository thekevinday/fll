/**
 * FLL - Level 2
 *
 * Project: Error
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines common data to be used for/by project error.
 *
 * This is auto-included by error.h and should not need to be explicitly included.
 */
#ifndef _FLL_error_common_h
#define _FLL_error_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Error file types.
 */
#ifndef _di_fll_error_file_type_
  enum {
    fll_error_file_type_file = 1,
    fll_error_file_type_directory,
    fll_error_file_type_pipe,
  };

  #define fll_error_file_type_string_directory "directory"
  #define fll_error_file_type_string_file      "file"
  #define fll_error_file_type_string_pipe      "pipe"

  #define fll_error_file_type_length_directory 9
  #define fll_error_file_type_length_file      4
  #define fll_error_file_type_length_pipe      4
#endif // _di_fll_error_file_type_

/**
 * Structure for facilitating the error printing.
 *
 * to:        The file to print to.
 * verbosity: The verbosity mode.
 * prefix:    A prefix string to display before the error.
 * context:   The color codes for the entire error message.
 * notable:   The color codes for a part of the message to make more visible.
 */
#ifndef _di_fll_error_print_t_
  #define fll_error_print_debug   "DEBUG: "
  #define fll_error_print_error   "ERROR: "
  #define fll_error_print_warning "WARNING: "

  #define fll_error_print_debug_length   7
  #define fll_error_print_error_length   7
  #define fll_error_print_warning_length 9

  typedef struct {
    f_file_t to;
    uint8_t verbosity;

    const char *prefix;

    f_color_set_t context;
    f_color_set_t notable;
  } fll_error_print_t;

  #define fll_error_print_t_initialize { \
    f_macro_file_t_initialize(f_type_error, f_type_descriptor_error, f_file_flag_write_only), \
    f_console_verbosity_normal, \
    fll_error_print_error, \
    f_color_set_t_initialize, \
    f_color_set_t_initialize, \
  }

  #define fll_macro_error_print_t_initialize(to, verbosity, prefix, context, notable) { to, verbosity, prefix, context, notable }
  #define fll_macro_error_print_t_initialize_debug() fll_macro_error_print_t_initialize(f_macro_file_t_initialize(f_type_debug, f_type_descriptor_debug, f_file_flag_write_only), f_console_verbosity_normal, fll_error_print_debug, f_color_set_t_initialize, f_color_set_t_initialize)
  #define fll_macro_error_print_t_initialize_warning() fll_macro_error_print_t_initialize(f_macro_file_t_initialize(f_type_warning, f_type_descriptor_warning, f_file_flag_write_only), f_console_verbosity_normal, fll_error_print_warning, f_color_set_t_initialize, f_color_set_t_initialize)
#endif // _di_fll_error_print_t_

/**
 * Set the context and notable to this to safely allow for fprintf uses when there is no color to be used.
 */
#ifndef _di_fll_error_string_null_s_
  const static f_string_static_t fll_error_string_null_s = f_macro_string_static_t_initialize("", 0);
#endif // _di_fll_error_string_null_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_error_common_h
