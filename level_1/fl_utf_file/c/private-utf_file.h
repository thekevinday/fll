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
 *   F_none_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *   F_none_eos on success but range.stop exceeded buffer.used (only wrote up to buffer.used).
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_interrupted (with error bit) if interrupt was received.
 *   F_input_output (with error bit) on I/O error.
 *   F_file_open_not (with error bit) if file is not open.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *
 * @see fl_utf_file_write()
 * @see fl_utf_file_write_range()
 * @see fl_utf_file_write_until()
 */
#if !defined(fl_utf_file_write) || !defined(fl_utf_file_write_until) || !defined(fl_utf_file_write_range)
  extern f_return_status private_fl_utf_file_write_until(const f_file file, const f_utf_string string, const f_utf_string_length total, f_utf_string_length *written) f_gcc_attribute_visibility_internal;
#endif // !defined(fl_utf_file_write) || !defined(fl_utf_file_write_until) || !defined(fl_utf_file_write_range)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_utf_file_h
