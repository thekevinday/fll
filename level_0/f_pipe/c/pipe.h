/**
 * FLL - Level 0
 *
 * Project: Pipe
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides pipe functionality.
 */
#ifndef _F_pipe_h
#define _F_pipe_h

// Libc includes.
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Identify whether or not the standard input pipe source contains piped data.
 *
 * @return
 *   F_true if there is piped data.
 *   F_false if there is no piped data.
 *   F_file_stat (with error bit) on stat() error.
 *
 * @see fstat()
 */
#ifndef _di_f_pipe_input_exists_
  extern f_status_t f_pipe_input_exists(void);
#endif // _di_f_pipe_input_exists_

/**
 * Identify whether or not the standard warning pipe contains piped data.
 *
 * For most systems, standard warning does not exist and instead maps to standard output.
 *
 * @return
 *   F_true if there is piped data.
 *   F_false if there is no piped data.
 *
 *   F_file_stat (with error bit) on stat() error.
 *
 * @see fstat()
 */
#ifndef _di_f_pipe_warning_exists_
  extern f_status_t f_pipe_warning_exists(void);
#endif // _di_f_pipe_warning_exists_

/**
 * Identify whether or not the standard error pipe source contains piped data.
 *
 * @return
 *   F_true if there is piped data.
 *   F_false if there is no piped data.
 *
 *   F_file_stat (with error bit) on stat() error.
 *
 * @see fstat()
 */
#ifndef _di_f_pipe_error_exists_
  extern f_status_t f_pipe_error_exists(void);
#endif // _di_f_pipe_error_exists_

/**
 * Identify whether or not the standard debug pipe source contains piped data.
 *
 * For most systems, standard debug does not exist and instead maps to standard output.
 *
 * @return
 *   F_false if there is no piped data.
 *   F_true if there is piped data.
 *
 *   F_file_stat (with error bit) on stat() error.
 *
 * @see fstat()
 */
#ifndef _di_f_pipe_debug_exists_
  extern f_status_t f_pipe_debug_exists(void);
#endif // _di_f_pipe_debug_exists_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_pipe_h
