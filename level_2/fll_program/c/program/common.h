/**
 * FLL - Level 2
 *
 * Project: Program
 * API Version: 0.7
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
 * Program data pipe codes.
 *
 * These are bit-wise codes used to designate that a particular pipe exists and is to be used.
 *
 * fll_program_data_pipe_*_e:
 *   - none:   No pipes are available for use.
 *   - error:  Error pipe is available for use.
 *   - input:  Input pipe is available for use.
 *   - output: Output pipe is available for use.
 */
#ifndef _di_fll_program_data_pipe_e_
  enum {
    fll_program_data_pipe_none_e   = 0x0,
    fll_program_data_pipe_error_e  = 0x1,
    fll_program_data_pipe_input_e  = 0x2,
    fll_program_data_pipe_output_e = 0x4,
  };
#endif // _di_fll_program_data_pipe_e_

/**
 * A common program structure to be used by simple programs needing no special structure.
 *
 * Complex programs or programs that need more data passed via the main should implement their own version of this.
 *
 * The umask() has design flaws as per specification that requires the umask be changed to read the value!
 * As a work-around, a umask variable is provided here so that umask() only ever need be called once.
 *
 * parameters:  The state of pre-defined parameters passed to the program.
 * environment: Environment variables passed to the program.
 *
 * umask: The umask settings, needed for avoiding calls to umask() to read the current umask.
 * pid:   The PID of the program.
 * child: Reserved for a child process, often representing the child return status or the child process ID.
 * pipe:  Designate that a pipe exists and is available for use.
 *
 * signal_check:    A counter used to map to for reducing the amount of actual signal check calls.
 * signal_received: The signal received (if 0, then no signal is received).
 * signal:          The process signal management structure.
 *
 * message: The output file for normal output messages (often stdout).
 * output:  The output file for normal/non-message output (often stdout or a file).
 * error:   The output file for error output messages.
 * warning: The output file for warning output messages.
 *
 * context: The color context.
 */
#ifndef _di_fll_program_data_t_
  typedef struct {
    f_console_parameters_t parameters;
    const f_string_t *     environment;

    mode_t umask;
    pid_t pid;
    int child;
    uint8_t pipe;

    uint32_t signal_received;
    uint16_t signal_check;
    f_signal_t signal;

    fl_print_t message;
    fl_print_t output;
    fl_print_t error;
    fl_print_t warning;
    fl_print_t debug;

    f_color_context_t context;
  } fll_program_data_t;

  #define fll_program_data_t_initialize \
    { \
      f_console_parameters_t_initialize, \
      0, \
      0, \
      0, \
      0, \
      fll_program_data_pipe_none_e, \
      0, \
      0, \
      f_signal_t_initialize, \
      fl_print_t_initialize, \
      fl_print_t_initialize, \
      macro_fl_print_t_initialize_error(), \
      macro_fl_print_t_initialize_warning(), \
      macro_fl_print_t_initialize_debug(), \
      f_color_context_t_initialize, \
    }

  #define macro_fll_program_data_t_initialize(parameters, environment, umask, pid, child, pipe, signal_received, signal_check, signal, message, output, error, warning, debug, context) { \
    parameters, \
    environment, \
    umask, \
    pid, \
    child, \
    pipe, \
    signal_received, \
    signal_check, \
    signal, \
    message, \
    output, \
    error, \
    warning, \
    debug, \
    context, \
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
