/**
 * FLL - Level 2
 *
 * Project: Program
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by project program.
 *
 * This is auto-included by program.h and should not need to be explicitly included.
 */
#ifndef _FLL_program_common_h
#define _FLL_program_common_h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_program_parameters_
  #define FLL_program_parameter_filename_s  "filename"
  #define FLL_program_parameter_filenames_s "filename(s)"

  #define FLL_program_parameter_filename_s_length  8
  #define FLL_program_parameter_filenames_s_length 11

  extern const f_string_static_t fll_program_parameter_filename_s;
  extern const f_string_static_t fll_program_parameter_filenames_s;
#endif // _di_fll_program_parameters_

/**
 * A common program structure to be used by simple programs needing no special structure.
 *
 * Complex programs or programs that need more data passed via the main should implement their own version of this.
 *
 * parameters:   The state of pre-defined parameters passed to the program.
 * process_pipe: Designate whether or not to process the input pipe.
 * output:       The output file for general printing.
 * error:        The output file for error printing.
 * warning:      The output file for warning printing.
 * signal:       The process signal management structure.
 * signal_check: A counter used to map to for reducing the amount of actual signal check calls.
 * context:      The color context.
 */
#ifndef _di_fll_program_data_t_
  typedef struct {
    f_console_parameters_t parameters;

    uint16_t signal_check;
    bool process_pipe;

    fl_print_t output;
    fl_print_t error;
    fl_print_t warning;

    f_signal_t signal;

    f_color_context_t context;
  } fll_program_data_t;

  #define fll_program_data_t_initialize \
    { \
      f_console_parameters_t_initialize, \
      0, \
      F_false, \
      fl_print_t_initialize, \
      macro_fl_print_t_initialize_error(), \
      macro_fl_print_t_initialize_warning(), \
      f_signal_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_fll_program_data_t_

/**
 * Delete any dynamic allocated data on the program data object.
 *
 * @param data
 *   The program data object.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_console_parameters_delete().
 *
 * @see f_console_parameters_delete()
 */
#ifndef _di_fll_program_data_delete_
  extern f_status_t fll_program_data_delete(fll_program_data_t * const data);
#endif // _di_fll_program_data_delete_

/**
 * Destroy any dynamic allocated data on the program data object.
 *
 * @param data
 *   The program data object.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_console_parameters_destroy().
 *
 * @see f_console_parameters_destroy()
 */
#ifndef _di_fll_program_data_destroy_
  extern f_status_t fll_program_data_destroy(fll_program_data_t * const data);
#endif // _di_fll_program_data_destroy_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_program_common_h
