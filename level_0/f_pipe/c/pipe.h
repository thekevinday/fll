/**
 * FLL - Level 0
 *
 * Project: Pipe
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides pipe functionality.
 *
 * @todo implement pipe() functionality.
 */
#ifndef _F_pipe_h
#define _F_pipe_h

// libc includes
#include <stdio.h>
#include <sys/stat.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/type.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Identify whether or not the standard input pipe source contains piped data.
 *
 * @return
 *   f_true if there is piped data.
 *   f_false if there is no piped data.
 *   f_file_error_stat (with error bit) on stat() error.
 *
 * @see fstat()
 */
#ifndef _di_f_pipe_input_exists_
  extern f_return_status f_pipe_input_exists();
#endif // _di_f_pipe_input_exists_

/**
 * Identify whether or not the standard warning pipe contains piped data.
 *
 * For most systems, standard warning does not exist and instead maps to standard output.
 *
 * @return
 *   f_true if there is piped data.
 *   f_false if there is no piped data.
 *   f_file_error_stat (with error bit) on stat() error.
 *
 * @see fstat()
 */
#ifndef _di_f_pipe_warning_exists_
  extern f_return_status f_pipe_warning_exists();
#endif // _di_f_pipe_warning_exists_

/**
 * Identify whether or not the standard error pipe source contains piped data.
 *
 * @return
 *   f_true if there is piped data.
 *   f_false if there is no piped data.
 *   f_file_error_stat (with error bit) on stat() error.
 *
 * @see fstat()
 */
#ifndef _di_f_pipe_error_exists_
  extern f_return_status f_pipe_error_exists();
#endif // _di_f_pipe_error_exists_

/**
 * Identify whether or not the standard debug pipe source contains piped data.
 *
 * For most systems, standard debug does not exist and instead maps to standard output.
 *
 * @return
 *   f_true if there is piped data.
 *   f_false if there is no piped data.
 *   f_file_error_stat (with error bit) on stat() error.
 *
 * @see fstat()
 */
#ifndef _di_f_pipe_debug_exists_
  extern f_return_status f_pipe_debug_exists();
#endif // _di_f_pipe_debug_exists_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_pipe_h
