/**
 * FLL - Level 1
 *
 * Project: Utf File
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * UTF-8 File Operations.
 */
#ifndef _FL_utf_file_h
#define _FL_utf_file_h

// libc includes
#include <string.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/string.h>
#include <level_0/type.h>
#include <level_0/utf.h>
#include <level_0/file.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read until EOF is reached.
 *
 * To check how much was read into the buffer, record buffer->used before execution and compare to buffer->used after execution.
 *
 * @param file
 *   The file to read.
 *   The file must already be open.
 * @param buffer
 *   The buffer the file is being read into.
 *   The contents of the file is appended into this buffer.
 *
 * @return
 *   f_none on success.
 *   f_none_on_eof on success and EOF was reached.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_block (with error bit) if file descriptor is set to non-block and the read would result in a blocking operation.
 *   f_file_error_descriptor (with error bit) if the file descriptor is invalid.
 *   f_invalid_buffer (with error bit) if the buffer is invalid.
 *   f_interrupted (with error bit) if interrupt was received.
 *   f_error_input_output (with error bit) on I/O error.
 *   f_file_not_open (with error bit) if file is not open.
 *   f_file_is_type_directory (with error bit) if file descriptor represents a directory.
 *   f_incomplete_utf_on_eof (with error bit) if UTF-8 character was incomplete at the end of the file.
 *
 * @see read()
 */
#ifndef _di_fl_utf_file_read_
  extern f_return_status fl_utf_file_read(f_file *file, f_utf_string_dynamic *buffer);
#endif // _di_fl_utf_file_read_

/**
 * Read until a single block is filled or EOF is reached.
 *
 * To check how much was read into the buffer, record buffer->used before execution and compare to buffer->used after execution.
 *
 * @param file
 *   The file to read.
 *   The file must already be open.
 * @param buffer
 *   The buffer the file is being read into.
 *   The contents of the file is appended into this buffer.
 *
 * @return
 *   f_none on success.
 *   f_none_on_eof on success and EOF was reached.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_block (with error bit) if file descriptor is set to non-block and the read would result in a blocking operation.
 *   f_file_error_descriptor (with error bit) if the file descriptor is invalid.
 *   f_invalid_buffer (with error bit) if the buffer is invalid.
 *   f_interrupted (with error bit) if interrupt was received.
 *   f_error_input_output (with error bit) on I/O error.
 *   f_file_not_open (with error bit) if file is not open.
 *   f_file_is_type_directory (with error bit) if file descriptor represents a directory.
 *   f_incomplete_utf_on_eof (with error bit) if UTF-8 character was incomplete at the end of the file.
 *
 * @see read()
 */
#ifndef _di_f_utf_file_read_
  extern f_return_status f_utf_file_read_block(f_file *file, f_utf_string_dynamic *buffer);
#endif // _di_f_utf_file_read_

/**
 * Read until a given number or EOF is reached, storing it in the buffer.
 *
 * To check how much was read into the buffer, record buffer->used before execution and compare to buffer->used after execution.
 *
 * @param file
 *   The file to read.
 *   The file must already be open.
 * @param buffer
 *   The buffer the file is being read into.
 * @param total
 *   The total bytes to read, unless EOF is reached first.
 *
 * @return
 *   f_none on success.
 *   f_none_on_eof on success and EOF was reached.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_block (with error bit) if file descriptor is set to non-block and the read would result in a blocking operation.
 *   f_file_error_descriptor (with error bit) if the file descriptor is invalid.
 *   f_invalid_buffer (with error bit) if the buffer is invalid.
 *   f_interrupted (with error bit) if interrupt was received.
 *   f_error_input_output (with error bit) on I/O error.
 *   f_file_not_open (with error bit) if file is not open.
 *   f_file_is_type_directory (with error bit) if file descriptor represents a directory.
 *   f_incomplete_utf_on_eof (with error bit) if UTF-8 character was incomplete at the end of the file.
 *
 * @see read
 */
#ifndef _di_f_utf_file_read_until_
  extern f_return_status f_utf_file_read_until(f_file *file, f_utf_string_dynamic *buffer, const f_utf_string_length total);
#endif // _di_f_utf_file_read_until_







































/**
 * Load entire file into the UTF-8 buffer.
 *
 * This does not validate the UTF-8 codes.
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
 *   f_string_too_large (with error bit) if string is too large to fit into the buffer.
 *   f_incomplete_utf_on_eof (with error bit) if UTF-8 character was incomplete at the end of the file.
 */
#ifndef _di_fl_utf_file_read_
  extern f_return_status fl_utf_file_read(f_file *file, f_utf_string_dynamic *buffer);
#endif // _di_fl_utf_file_read_

/**
 * Load file into the UTF-8 buffer, based on specified positions.
 *
 * This does not validate the UTF-8 codes.
 *
 * @param file
 *   The file to read from.
 * @param buffer
 *   The buffer to save the file.
 * @param quantity
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
 *   f_string_too_large (with error bit) if string is too large to fit into the buffer.
 *   f_incomplete_utf_on_eof (with error bit) if UTF-8 character was incomplete at the end of the file.
 */
#ifndef _di_fl_utf_file_read_position_
  extern f_return_status fl_utf_file_read_position(f_file *file, f_utf_string_dynamic *buffer, const f_string_quantity quantity);
#endif // _di_fl_utf_file_read_position

/**
 * Save entire UTF-8 buffer into file.
 *
 * This does not validate the UTF-8 codes.
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
#ifndef _di_fl_utf_file_write_
  extern f_return_status fl_utf_file_write(f_file *file, const f_utf_string_static buffer);
#endif // _di_fl_utf_file_write_

/**
 * Save entire UTF-8 buffer into file, based on specified positions.
 *
 * This does not validate the UTF-8 codes.
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
#ifndef _di_fl_utf_file_write_position_
  extern f_return_status fl_utf_file_write_position(f_file *file, const f_utf_string_static buffer, const f_utf_string_range position);
#endif // _di_fl_utf_file_write_position_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_utf_file_h
