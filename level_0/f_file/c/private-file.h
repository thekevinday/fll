/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides structures and data types for a file I/O.
 * Provides operations for opening/closing files.
 */
#ifndef _PRIVATE_F_file_h
#define _PRIVATE_F_file_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of f_file_change_owner().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param path
 *   The path file name.
 * @param uid
 *   The new user id to use.
 * @param gid
 *   The new group id to use.
 *
 * @return
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_access_denied (with error bit) on access denied.
 *   f_invalid_name (with error bit) if the filename is too long.
 *   f_loop (with error bit) on loop error.
 *   f_file_not_found (with error bit) if file at path was not found.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_invalid_directory (with error bit) on invalid directory.
 *   f_prohibited (with error bit) if filesystem does not allow for file changes.
 *   f_read_only (with error bit) if file is read-only.
 *   f_error_input_output (with error bit) on I/O error.
 *   f_failure (with error bit) for any other (mkdir()) error.
 *
 * @see f_file_change_owner()
 * @see chown()
 */
#if !defined(_di_f_file_change_owner_) || !defined(_di_f_file_copy_)
  extern f_return_status private_f_file_change_owner(const f_string path, const uid_t uid, const gid_t gid) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_file_change_owner_) || !defined(_di_f_file_copy_)

/**
 * Private implementation of f_file_change_mode().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param path
 *   The path file name.
 * @param mode
 *   The new mode to use.
 *
 * @return
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_access_denied (with error bit) on access denied.
 *   f_invalid_name (with error bit) if the filename is too long.
 *   f_loop (with error bit) on loop error.
 *   f_file_not_found (with error bit) if file at path was not found.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_invalid_directory (with error bit) on invalid directory.
 *   f_prohibited (with error bit) if filesystem does not allow for file changes.
 *   f_read_only (with error bit) if file is read-only.
 *   f_error_input_output (with error bit) on I/O error.
 *   f_failure (with error bit) for any other (mkdir()) error.
 *
 * @see f_file_change_mode()
 * @see chmod()
 */
#if !defined(_di_f_file_change_mode_) || !defined(_di_f_file_copy_)
  extern f_return_status private_f_file_change_mode(const f_string path, const mode_t mode) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_file_change_mode_) || !defined(_di_f_file_copy_)

/**
 * Private implementation of f_file_create().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param path
 *   Full path to the file (including entire filename).
 * @param mode
 *   The file mode.
 * @param exclusive
 *   If TRUE, will fail when file already exists.
 *   If FALSE, will not fail if file already exists.
 *
 * @return
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_access_denied (with error bit) on access denied.
 *   f_loop (with error bit) on loop error.
 *   f_file_found (with error bit) if a file was found while exclusive is TRUE.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_prohibited (with error bit) if filesystem does not allow for removing.
 *   f_read_only (with error bit) if file is read-only.
 *   f_failure (with error bit) for any other (mkdir()) error.
 *   f_filesystem_quota_blocks (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   f_filesystem_quota_reached (with error bit) quota reached of filesystem is out of space.
 *   f_file_found (with error bit) of a directory aleady exists at the path.
 *   f_invalid_name (with error bit) on path name error.
 *   f_invalid_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   f_number_overflow (with error bit) on overflow error.
 *   f_interrupted (with error bit) when program received an interrupt signal, halting create.
 *   f_file_max_open (with error bit) when system-wide max open files is reached.
 *   f_busy (with error bit) if filesystem is too busy to perforrm write.
 *
 * @see f_file_create()
 * @see open()
 */
#if !defined(_di_f_file_create_) || !defined(_di_f_file_copy_)
  extern f_return_status private_f_file_create(f_string path, const mode_t mode, const bool exclusive) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_file_create_) || !defined(_di_f_file_copy_)

/**
 * Private implementation of f_file_open().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param file
 *   The data related to the file being opened.
 *   This will be updated with the file descriptor and file address.
 * @param path
 *   The path file name.
 *
 * @return
 *   f_none on success.
 *   f_file_not_found (with error bit) if the file was not found.
 *   f_file_error_open (with error bit) if the file is already open.
 *   f_file_error_descriptor (with error bit) if unable to load the file descriptor (the file pointer may still be valid).
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_file_open()
 * @see fopen()
 */
#if !defined(_di_f_file_open_) || !defined(_di_f_file_copy_)
  extern f_return_status private_f_file_open(f_file *file, const f_string path) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_file_open_) || !defined(_di_f_file_copy_)

/**
 * Private implementation of f_file_close().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param file
 *   The file to close.
 *
 * @return
 *   f_none on success.
 *   f_file_not_open (with error bit) if the file is not open.
 *   f_file_error_synchronize (with error bit) on fsync() failure.
 *   f_file_error_close (with error bit) if fclose() failed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_file_close()
 * @see fsync()
 * @see fclose()
 */
#if !defined(_di_f_file_close_) || !defined(_di_f_file_copy_)
  extern f_return_status private_f_file_close(f_file *file) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_file_close_) || !defined(_di_f_file_copy_)

/**
 * Private implementation of f_file_close().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param file_name
 *   The name of the file.
 * @param file_stat
 *   The statistics read.
 *
 * @return
 *   f_none on success.
 *   f_invalid_name (with error bit) if the name is somehow invalid.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_number_overflow (with error bit) on overflow error.
 *   f_invalid_directory (with error bit) on invalid directory.
 *   f_file_not_found (with error bit) if the file was not found.
 *   f_access_denied (with error bit) if access to the file was denied.
 *   f_loop (with error bit) if a loop occurred.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_file_stat()
 * @see stat()
 */
#if !defined(_di_f_file_stat_) || !defined(_di_f_file_copy_)
  extern f_return_status private_f_file_stat(const f_string file_name, struct stat *file_stat) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_file_stat_) || !defined(_di_f_file_copy_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_file_h
