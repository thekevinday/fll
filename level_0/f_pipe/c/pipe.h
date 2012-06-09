/* FLL - Level 0
 * Project:       Pipe
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provides pipe functionality.
 *
 */
#ifndef _F_pipe_h
#define _F_pipe_h

// libc includes
#include <stdio.h>
#include <sys/stat.h>

// fll includes
#include <level_0/types.h>
#include <level_0/errors.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_f_pipe_
  #define f_pipe f_standard_input
#endif // _di_f_pipe_

#ifndef _di_f_pipe_exists_
  // returns f_true if the standard input contains piped data.
  extern f_return_status f_pipe_exists();
#endif // _di_f_pipe_exists_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_pipe_h
