/* FLL - Level 1
 * Project:       Execute
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provides program execution operations similar to system()
 */
#ifndef _FL_execute_h
#define _FL_execute_h

// libc includes
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

// fll-0 includes
#include <level_0/strings.h>
#include <level_0/types.h>
#include <level_0/errors.h>
#include <level_0/memory.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fl_execute_path_
  // This will execute a program given some path + program name (such as "/bin/bash")
  extern f_return_status fl_execute_path(const f_string program_path, const f_dynamic_strings arguments, f_s_int *results);
#endif // _di_fl_execute_path_

#ifndef _di_fl_execute_program_
  // This will find the program based on PATH environment so that static paths do not have to be used as with f_execute_path
  extern f_return_status fl_execute_program(const f_string program_name, const f_string arguments[], f_s_int *results);
#endif // _di_fl_execute_program_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_execute_h
