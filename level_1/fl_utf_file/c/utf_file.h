/**
 * FLL - Level 1
 *
 * Project: Utf File
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * UTF-8 File I/O Operations.
 */
#ifndef _FL_utf_file_h
#define _FL_utf_file_h

// libc includes
#include <string.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
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
 *   F_none on success.
 *   F_none_eof on success and EOF was reached.
 *   F_block (with error bit) if file descriptor is set to non-block and the read would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file (with error bit) if file descriptor is in an error state.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_incomplete_utf_eof (with error bit) if UTF-8 character was incomplete at the end of the file.
 *   F_incomplete_utf_stop (with error bit) if UTF-8 character was incomplete at a stop point (file.size_read).
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupted (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see read()
 */
#ifndef _di_fl_utf_file_read_
  extern f_return_status fl_utf_file_read(const f_file_t file, f_utf_string_dynamic_t *buffer);
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
 *   F_none on success.
 *   F_none_eof on success and EOF was reached.
 *   F_block (with error bit) if file descriptor is set to non-block and the read would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file (with error bit) if file descriptor is in an error state.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_incomplete_utf_eof (with error bit) if UTF-8 character was incomplete at the end of the file.
 *   F_incomplete_utf_stop (with error bit) if UTF-8 character was incomplete at a stop point (file.size_read).
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupted (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see read()
 */
#ifndef _di_fl_utf_file_read_block_
  extern f_return_status fl_utf_file_read_block(const f_file_t file, f_utf_string_dynamic_t *buffer);
#endif // _di_fl_utf_file_read_block_

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
 *   F_none on success.
 *   F_none_eof on success and EOF was reached.
 *   F_block (with error bit) if file descriptor is set to non-block and the read would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file (with error bit) if file descriptor is in an error state.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_incomplete_utf_eof (with error bit) if UTF-8 character was incomplete at the end of the file.
 *   F_incomplete_utf_stop (with error bit) if UTF-8 character was incomplete at a stop point (file.size_read).
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupted (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see read
 */
#ifndef _di_fl_utf_file_read_until_
  extern f_return_status fl_utf_file_read_until(const f_file_t file, f_utf_string_dynamic_t *buffer, const f_utf_string_length_t total);
#endif // _di_fl_utf_file_read_until_

/**
 * Write until entire buffer is written.
 *
 * @param file
 *   The file to write to.
 *   The file must already be open.
 * @param buffer
 *   The buffer to write to the file.
 * @param written
 *   The total bytes written.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success but range.stop exceeded buffer.used (only wrote up to buffer.used).
 *   F_none_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *   F_incomplete_utf_stop if max write was reached but was unable to completely write a given UTF-8 block (incomplete UTF-8 is not written, not even partially).
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file (with error bit) if file descriptor is in an error state.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupted (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_fl_utf_file_write_
  extern f_return_status fl_utf_file_write(const f_file_t file, const f_utf_string_static_t buffer, f_utf_string_length_t *written);
#endif // _di_fl_utf_file_write_

/**
 * Write until a single block is filled or entire buffer is written.
 *
 * To check how much was write into the buffer, record buffer->used before execution and compare to buffer->used after execution.
 *
 * @param file
 *   The file to write to.
 *   The file must already be open.
 * @param buffer
 *   The buffer to write to the file.
 * @param written
 *   The total bytes written.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success but range.stop exceeded buffer.used (only wrote up to buffer.used).
 *   F_none_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *   F_incomplete_utf_stop if max write was reached but was unable to completely write a given UTF-8 block (incomplete UTF-8 is not written, not even partially).
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file (with error bit) if file descriptor is in an error state.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupted (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_fl_utf_file_write_block_
  extern f_return_status fl_utf_file_write_block(const f_file_t file, const f_utf_string_static_t buffer, f_utf_string_length_t *written);
#endif // _di_fl_utf_file_write_block_

/**
 * Write until a given number or entire buffer is written.
 *
 * @param file
 *   The file to write to.
 *   The file must already be open.
 * @param buffer
 *   The buffer to write to the file.
 * @param total
 *   The total bytes to write, unless end of buffer is reached first.
 * @param written
 *   The total bytes written.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success but range.stop exceeded buffer.used (only wrote up to buffer.used).
 *   F_none_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *   F_incomplete_utf_stop if max write was reached but was unable to completely write a given UTF-8 block (incomplete UTF-8 is not written, not even partially).
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file (with error bit) if file descriptor is in an error state.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupted (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_fl_utf_file_write_until_
  extern f_return_status fl_utf_file_write_until(const f_file_t file, const f_utf_string_static_t buffer, const f_utf_string_length_t total, f_utf_string_length_t *written);
#endif // _di_fl_utf_file_write_until_

/**
 * Write a given range within the buffer.
 *
 * @param file
 *   The file to write to.
 *   The file must already be open.
 * @param buffer
 *   The buffer to write to the file.
 * @param range
 *   An inclusive start an stop range within the buffer to read.
 * @param written
 *   The total bytes written.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success but range.stop exceeded buffer.used (only wrote up to buffer.used).
 *   F_none_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *   F_incomplete_utf_stop if max write was reached but was unable to completely write a given UTF-8 block (incomplete UTF-8 is not written, not even partially).
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file (with error bit) if file descriptor is in an error state.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupted (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_fl_utf_file_write_range_
  extern f_return_status fl_utf_file_write_range(const f_file_t file, const f_utf_string_static_t buffer, const f_utf_string_range_t range, f_utf_string_length_t *written);
#endif // _di_fl_utf_file_write_range_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_utf_file_h
