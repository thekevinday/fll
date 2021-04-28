/**
 * FLL - Level 1
 *
 * Project: Utf File
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * UTF-8 File Operations.
 */
#ifndef _PRIVATE_FL_utf_file_h
#define _PRIVATE_FL_utf_file_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Special function for converting read buffer from 1-byte wide character buffer to a UTF-8 4-byte wide utf_character buffer.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param buffer_read
 *   The read buffer to process.
 * @param size_read
 *   The size of the read buffer.
 * @param buffer
 *   The UTF-8 4-byte wider utf_character buffer.
 * @param buffer_char
 *   A 1-byte wide character array of size 4 to cache the current buffer_read until all parts are read to store into buffer.
 * @param width
 *   The width of the last read (first) character.
 *   This is used to determine how much of buffer_char is to be filled before saving into buffer.
 * @param width_last
 *   The amount of width filled into buffer_char after executing this function.
 *   This may be something other than width when size_read is reached before the entire buffer_char is filled according to width.
 *
 * @see fl_utf_file_read()
 * @see fl_utf_file_read_range()
 * @see fl_utf_file_read_until()
 */
#if !defined(_di_fl_utf_file_read_) || !defined(_di_fl_utf_file_read_until_) || !defined(_di_fl_utf_file_read_range_)
  void private_fl_utf_file_process_read_buffer(const char *buffer_read, const ssize_t size_read, f_utf_string_dynamic_t *buffer, char buffer_char[], uint8_t *width, uint8_t *width_last) f_attribute_visibility_internal;
#endif // !defined(_di_fl_utf_file_read_) || !defined(_di_fl_utf_file_read_until_) || !defined(_di_fl_utf_file_read_range_)

/**
 * Private implementation of fl_utf_file_write_until().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param file
 *   The file to write to.
 *   The file must already be open.
 *   The file.size_write is forced to be no less than 4 (if greater than 0).
 * @param string
 *   The string to write to the file.
 * @param total
 *   The total bytes to write.
 * @param written
 *   The total bytes written.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success but range.stop exceeded buffer.used (only wrote up to buffer.used).
 *   F_none_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *   F_complete_not_utf_stop if max write was reached but was unable to completely write a given UTF-8 block (incomplete UTF-8 is not written, not even partially).
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fl_utf_file_write()
 * @see fl_utf_file_write_range()
 * @see fl_utf_file_write_until()
 */
#if !defined(_di_fl_utf_file_write_) || !defined(_di_fl_utf_file_write_until_) || !defined(_di_fl_utf_file_write_range_)
  extern f_status_t private_fl_utf_file_write_until(const f_file_t file, const f_utf_string_t string, const f_array_length_t total, f_array_length_t *written) f_attribute_visibility_internal;
#endif // !defined(_di_fl_utf_file_write_) || !defined(_di_fl_utf_file_write_until_) || !defined(_di_fl_utf_file_write_range_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_utf_file_h
