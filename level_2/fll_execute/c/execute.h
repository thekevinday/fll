/**
 * FLL - Level 2
 *
 * Project: Execute
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides program execution operations similar to system().
 */
#ifndef _FLL_execute_h
#define _FLL_execute_h

// libc includes
#include <linux/limits.h> // defines PATH_MAX
#include <memory.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/types.h>

// fll-1 includes

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_execute_path_
  /**
   * This will execute a program given some path + program name (such as "/bin/bash").
   */
  extern f_return_status fll_execute_path(const f_string program_path, const f_string_dynamics arguments, f_s_int *results);
#endif // _di_fll_execute_path_

#ifndef _di_fll_execute_program_
  /**
   * This will find the program based on PATH environment so that static paths do not have to be used as with f_execute_path.
   */
  extern f_return_status fll_execute_program(const f_string program_name, const f_string_dynamics arguments, f_s_int *results);
#endif // _di_fll_execute_program_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_execute_h
