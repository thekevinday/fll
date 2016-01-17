/* FLL - Level 1
 * Project:       File
 * Version:       0.5.0
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
extern "C" {
#endif

#ifndef _di_fl_file_read_
  f_extern f_return_status fl_file_read(f_file file, f_const f_file_position position, f_dynamic_string *buffer);
#endif // _di_fl_file_read_

#ifndef _di_fl_file_read_fifo_
  f_extern f_return_status fl_file_read_fifo(f_file file, f_dynamic_string *buffer);
#endif // _di_fl_file_read_fifo_

#ifndef _di_fl_file_write_
  f_extern f_return_status fl_file_write(f_file file, f_const f_dynamic_string buffer);
#endif // _di_fl_file_write_

#ifndef _di_fl_file_write_partial_
  f_extern f_return_status fl_file_write_partial(f_file file, f_const f_dynamic_string buffer, f_const f_string_location position);
#endif // _di_fl_file_write_partial_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_file_h
