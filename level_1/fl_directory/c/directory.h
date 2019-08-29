/**
 * FLL - Level 1
 *
 * Project: Directory
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides operations for directory handling.
 */
#ifndef _FL_directory_h
#define _FL_directory_h

// libc includes
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/strings.h>
#include <level_0/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_directory_limitations_
  #define fl_directory_default_allocation_step f_memory_default_allocation_step

  #define fl_directory_name_max 255
#endif // _di_fl_directory_limitations_

#ifndef _di_fl_directory_list_
  /**
   * put the names of each file and/or directory inside the names parameter.
   */
  extern f_return_status fl_directory_list(const f_string directory_path, f_dynamic_strings *names);
#endif // _di_fl_directory_list_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_directory_h
