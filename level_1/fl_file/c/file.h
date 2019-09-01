/**
 * FLL - Level 1
 *
 * Project: File
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * File Operations.
 */
#ifndef _FL_file_h
#define _FL_file_h

// fll-0 includes
#include <level_0/file.h>
#include <level_0/string.h>
#include <level_0/type.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_file_read_
  /**
   * read file, specific positions.
   */
  extern f_return_status fl_file_read(f_file file, const f_file_position position, f_string_dynamic *buffer);
#endif // _di_fl_file_read_

#ifndef _di_fl_file_read_fifo_
  /**
   * read file, entire file.
   */
  extern f_return_status fl_file_read_fifo(f_file file, f_string_dynamic *buffer);
#endif // _di_fl_file_read_fifo_

#ifndef _di_fl_file_write_
  /**
   * write file, entire file.
   */
  extern f_return_status fl_file_write(f_file file, const f_string_dynamic buffer);
#endif // _di_fl_file_write_

#ifndef _di_fl_file_write_partial_
  /**
   * write file, specific positions.
   */
  extern f_return_status fl_file_write_partial(f_file file, const f_string_dynamic buffer, const f_string_location position);
#endif // _di_fl_file_write_partial_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_file_h
