/* FLL - Level 1
 * Project:       Directory
 * Version:       0.4.2
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 *  Provides operations for directory handling
 */
#ifndef _FL_directory_h
#define _FL_directory_h

// libc includes
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

// fll-0 includes
#include <level_0/types.h>
#include <level_0/errors.h>
#include <level_0/strings.h>
#include <level_0/memory.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fl_directory_limitations_
  #define fl_directory_default_allocation_step f_memory_default_allocation_step
#endif // _di_fl_directory_limitations_

#ifndef _di_fl_directory_list_
  // put the names of each file and/or directory inside the names parameter
  extern f_return_status fl_directory_list(const f_string directory_path, f_dynamic_strings *names);
#endif // _di_fl_directory_list_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_directory_h
