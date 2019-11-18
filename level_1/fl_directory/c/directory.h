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
#include <level_0/string.h>
#include <level_0/type.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_directory_limitations_
  #define fl_directory_default_allocation_step f_memory_default_allocation_step

  #define fl_directory_name_max 255
#endif // _di_fl_directory_limitations_

/**
 * Print the names of each file and/or directory inside the given directory.
 *
 * @param directory_path
 *   Filesystem path to the directory.
 * @param names
 *   Will be populated with the names of each file and/or directory inside the names parameter.
 *
 * @return
 *   f_none on success.
 *   f_no_data if directory is empty (@fixme: unlikely due to '.' and '..' probably always being returned.).
 *   f_failure (with error bit) if failed to read directory information.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_reallocation_error (with error bit) on memory reallocation error.
 */
#ifndef _di_fl_directory_list_
  extern f_return_status fl_directory_list(const f_string directory_path, f_string_dynamics *names);
#endif // _di_fl_directory_list_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_directory_h
