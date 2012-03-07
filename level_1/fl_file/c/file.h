/* FLL - Level 1
 * Project:       File
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *   File Operations
 */
#ifndef _FL_file_h
#define _FL_file_h

// fll-0 includes
#include <level_0/types.h>
#include <level_0/strings.h>
#include <level_0/file.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fl_file_read_
  extern f_return_status fl_file_read(f_file file, const f_file_position position, f_dynamic_string *buffer);
#endif // _di_fl_file_read_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_file_h
