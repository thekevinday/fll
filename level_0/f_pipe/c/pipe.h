/**
 * FLL - Level 0
 *
 * Project: Pipe
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides pipe functionality.
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
 * Default pipe sources.
 */
#ifndef _di_f_pipe_
  #define f_pipe         f_standard_input
  #define f_pipe_warning f_standard_warning
  #define f_pipe_error   f_standard_error
  #define f_pipe_debug   f_standard_debug
#endif // _di_f_pipe_

/**
 * Identify whether or not the default f_pipe source (generally standard input) contains piped data.
 *
 * @return
 *   f_true if there is piped data.
 *   f_false if there is no piped data.
 *   f_file_stat_error (with error bit) on stat() error.
 *
 * @see stat()
 */
#ifndef _di_f_pipe_exists_
  extern f_return_status f_pipe_exists();
#endif // _di_f_pipe_exists_

/**
 * Identify whether or not the default f_pipe_warning source (generally standard warning) contains piped data.
 *
 * For most systems, standard warning does not exist and instead maps to standard output.
 *
 * @return
 *   f_true if there is piped data.
 *   f_false if there is no piped data.
 *   f_file_stat_error (with error bit) on stat() error.
 *
 * @see stat()
 */
#ifndef _di_f_pipe_warning_exists_
  extern f_return_status f_pipe_warning_exists();
#endif // _di_f_pipe_warning_exists_

/**
 * Identify whether or not the default f_pipe_error source (generally standard error) contains piped data.
 *
 * @return
 *   f_true if there is piped data.
 *   f_false if there is no piped data.
 *   f_file_stat_error (with error bit) on stat() error.
 *
 * @see stat()
 */
#ifndef _di_f_pipe_error_exists_
  extern f_return_status f_pipe_error_exists();
#endif // _di_f_pipe_error_exists_

/**
 * Identify whether or not the default f_pipe_debug source (generally standard warning) contains piped data.
 *
 * For most systems, standard debug does not exist and instead maps to standard output.
 *
 * @return
 *   f_true if there is piped data.
 *   f_false if there is no piped data.
 *   f_file_stat_error (with error bit) on stat() error.
 *
 * @see stat()
 */
#ifndef _di_f_pipe_debug_exists_
  extern f_return_status f_pipe_debug_exists();
#endif // _di_f_pipe_debug_exists_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_pipe_h
