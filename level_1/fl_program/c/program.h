/**
 * FLL - Level 1
 *
 * Project: Program
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provide functions commonly used by FLL based programs.
 */
#ifndef _FL_program_h
#define _FL_program_h

// libc include
#include <stdio.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/strings.h>
#include <level_0/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_program_print_version_
  /**
   * Print version.
   *
   * @param version
   *   The version number to print.
   *
   * @return
   *   f_none on success.
   *   Error bit is set on error.
   */
  extern f_return_status fl_program_print_version(const f_string version);
#endif // _di_fl_program_print_version_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_program_h
