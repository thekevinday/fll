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

/**
 * Load entire file into buffer.
 *
 * @param file
 *   The file to read from.
 * @param buffer
 *   The buffer to load the file into.
 *
 * @return
 *   f_none on success.
 *   f_none_on_eof on success and EOF was reached.
 *   f_file_not_open (with error bit) if file is not open.
 *   f_file_error_seek (with error bit) if file seek failed.
 *   f_file_error_read (with error bit) if file read failed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_reallocation (with error bit) on memory reallocation error.
 *   f_string_too_large (with error bit) if string is too large to fit into buffer.
 */
#ifndef _di_fl_file_read_
  extern f_return_status fl_file_read(f_file *file, f_string_dynamic *buffer);
#endif // _di_fl_file_read_

/**
 * Load file into buffer, based on specified positions.
 *
 * @param file
 *   The file to read from.
 * @param buffer
 *   The buffer to save the file.
 * @param position
 *   The file position to base reading off of.
 *
 * @return
 *   f_none on success.
 *   f_none_on_eof on success and EOF was reached.
 *   f_file_not_open (with error bit) if file is not open.
 *   f_file_error_seek (with error bit) if file seek failed.
 *   f_file_error_read (with error bit) if file read failed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_reallocation (with error bit) on memory reallocation error.
 *   f_string_too_large (with error bit) if string is too large to fit into buffer.
 */
#ifndef _di_fl_file_read_position_
  extern f_return_status fl_file_read_position(f_file *file, f_string_dynamic *buffer, const f_file_position position);
#endif // _di_fl_file_read_position

/**
 * Save entire buffer into file.
 *
 * @param file
 *   The file to save to.
 * @param buffer
 *   The buffer to save to the file.
 *
 * @return
 *   f_none on success.
 *   f_file_not_open (with error bit) if file is not open.
 *   f_file_error_write (with error bit) if write failed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_file_write_
  extern f_return_status fl_file_write(f_file *file, const f_string_dynamic buffer);
#endif // _di_fl_file_write_

/**
 * Save entire buffer into file, based on specified positions.
 *
 * @param file
 *   The file to save to.
 * @param buffer
 *   The buffer to save to the file.
 * @param position
 *   The file position to base writing off of.
 *
 * @return
 *   f_none on success.
 *   f_file_not_open (with error bit) if file is not open.
 *   f_file_error_write (with error bit) if write failed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_file_write_position_
  extern f_return_status fl_file_write_position(f_file *file, const f_string_dynamic buffer, const f_string_location position);
#endif // _di_fl_file_write_position_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_file_h
