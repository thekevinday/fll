/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
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
 * Private implementation of f_file_close().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param flush
 *   If TRUE, then perform flush before closing.
 *   If FALSE, then do not perform flush before closing.
 * @param id
 *   The file descriptor.
 *   The value gets set to -1.
 *
 * @return
 *   F_none on success.
 *
 *   F_file_close (with error bit) if fclose() failed for any other reason.
 *   F_file_descriptor (with error bit) if file descriptor is invalid.
 *   F_file_synchronize (with error bit) on flush failure.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_space_not (with error bit) if file system is out of space (or file system quota is reached).
 *
 * @see close()
 *
 * @see f_file_clone()
 * @see f_file_close()
 * @see f_file_close_flush()
 * @see f_file_copy()
 * @see f_file_create()
 * @see f_file_create_at()
 * @see f_file_stream_close()
 */
#if !defined(_di_f_file_clone_) || !defined(_di_f_file_close_) || !defined(_di_f_file_close_flush_) || !defined(_di_f_file_copy_) || !defined(_di_f_file_create_) || !defined(_di_f_file_create_at_) || !defined(_di_f_file_stream_close_)
  extern f_status_t private_f_file_close(const bool flush, int * const id) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_clone_) || !defined(_di_f_file_close_) || !defined(_di_f_file_close_flush_) || !defined(_di_f_file_copy_) || !defined(_di_f_file_create_) || !defined(_di_f_file_create_at_) || !defined(_di_f_file_stream_close_)

/**
 * Copy a file.
 *
 * The paths must not contain NULL except for the terminating NULL.
 * The paths must be NULL terminated.
 *
 * @param source
 *   The path to the file to copy from.
 * @param destination
 *   The path to copy to.
 * @param mode
 *   The file mode assigned to the destination file.
 * @param size_block
 *   The default number of chunks to read at a time with each chunk being 1-byte.
 *   Must be greater than 0.
 * @param exclusive
 *   If TRUE, will fail when file already exists.
 *   If FALSE, will not fail if file already exists (existing file will be replaced).
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_busy (with error bit) if file system is too busy to perform write.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_file_found (with error bit) if a file was found while exclusive is TRUE.
 *   F_file_open_max (with error bit) when system-wide max open files is reached.
 *   F_file_read (with error bit) on file read error.
 *   F_file_write (with error bit) on file write error.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for making changes.
 *   F_read_only (with error bit) if file is read-only.
 *   F_space_not (with error bit) if file system is out of space (or file system quota is reached).
 *   F_supported_not if copying a given type of file is unsupported.
 *   F_failure (with error bit) for any other error.
 *
 * @see open()
 *
 * @see f_file_copy()
 * @see f_file_clone()
 */
#if !defined(_di_f_file_copy_) || !defined(_di_f_file_clone_)
  extern f_status_t private_f_file_copy_content(const f_string_static_t source, const f_string_static_t destination, const f_number_unsigned_t size_block) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_copy_) || !defined(_di_f_file_clone_)

/**
 * Private implementation of f_file_create().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param path
 *   The path file name.
 * @param mode
 *   The file mode to open in.
 * @param exclusive
 *   If TRUE, will fail when file already exists.
 *   If FALSE, will not fail if file already exists.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_busy (with error bit) if file system is too busy to perform write.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_file_found (with error bit) if a file was found while exclusive is TRUE.
 *   F_file_open_max (with error bit) when system-wide max open files is reached.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for making changes.
 *   F_read_only (with error bit) if file is read-only.
 *   F_space_not (with error bit) if file system is out of space (or file system quota is reached).
 *   F_failure (with error bit) for any other error.
 *
 * @see open()
 *
 * @see f_file_copy()
 * @see f_file_create()
 */
#if !defined(_di_f_file_create_) || !defined(_di_f_file_copy_)
  extern f_status_t private_f_file_create(const f_string_static_t path, const mode_t mode, const bool exclusive) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_create_) || !defined(_di_f_file_copy_)

/**
 * Private implementation of f_file_create_at().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param mode
 *   The file mode to open in.
 * @param exclusive
 *   If TRUE, will fail when file already exists.
 *   If FALSE, will not fail if file already exists.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_busy (with error bit) if file system is too busy to perform write.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_file_found (with error bit) if a file was found while exclusive is TRUE.
 *   F_file_open_max (with error bit) when system-wide max open files is reached.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for making changes.
 *   F_read_only (with error bit) if file is read-only.
 *   F_space_not (with error bit) if file system is out of space (or file system quota is reached).
 *   F_failure (with error bit) for any other error.
 *
 * @see openat()
 *
 * @see f_file_create_at()
 */
#if !defined(_di_f_file_create_at_)
  extern f_status_t private_f_file_create_at(const int at_id, const f_string_static_t path, const mode_t mode, const bool exclusive) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_create_at_)

/**
 * Private implementation for creating directories.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param path
 *   The path file name.
 * @param mode
 *   The directory mode to use when creating.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_directory_link_max (with error bit) max links limit reached or exceeded.
 *   F_file_found (with error bit) if a file was found while exclusive is TRUE.
 *   F_file_found_not (with error bit) if file at path was not found.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for making changes.
 *   F_read_only (with error bit) if file is read-only.
 *   F_space_not (with error bit) if file system is out of space (or file system quota is reached).
 *   F_failure (with error bit) for any other error.
 *
 * @see mkdir()
 *
 * @see f_file_copy()
 */
#if !defined(_di_f_file_copy_)
  extern f_status_t private_f_file_create_directory(const f_string_static_t path, const mode_t mode) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_copy_)

/**
 * Private implementation of private_f_file_create_fifo().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param path
 *   The path file name.
 * @param mode
 *   The file mode to assign.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_file_found (with error bit) if a file was found while exclusive is TRUE.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or ififos are exhausted.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for making changes.
 *   F_space_not (with error bit) if file system is out of space (or file system quota is reached).
 *   F_supported_not (with error bit) for unsupported file types.
 *   F_failure (with error bit) for any other error.
 *
 * @see mkfifo()
 *
 * @see f_file_create_fifo()
 * @see f_file_copy()
 */
#if !defined(_di_f_file_create_fifo_) || !defined(_di_f_file_copy_)
  extern f_status_t private_f_file_create_fifo(const f_string_static_t path, const mode_t mode) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_create_fifo_) || !defined(_di_f_file_copy_)

/**
 * Private implementation of f_file_create_node().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param path
 *   The path file name.
 * @param mode
 *   The file mode to assign.
 * @param device
 *   The device number for character and block file types.
 *   Is ignored by pipe file types.
 * @param file
 *   The data related to the file being created.
 *   This will be updated with the file descriptor.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_file_found (with error bit) if a file was found while exclusive is TRUE.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for making changes.
 *   F_space_not (with error bit) if file system is out of space (or file system quota is reached).
 *   F_supported_not (with error bit) for unsupported file types.
 *   F_failure (with error bit) for any other error.
 *
 * @see mknod()
 *
 * @see f_file_copy()
 * @see f_file_create_device()
 * @see f_file_create_node()
 */
#if !defined(_di_f_file_create_device_) || !defined(_di_f_file_create_node_) || !defined(_di_f_file_copy_)
  extern f_status_t private_f_file_create_node(const f_string_static_t path, const mode_t mode, const dev_t device) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_create_device_) || !defined(_di_f_file_create_node_) || !defined(_di_f_file_copy_)

/**
 * Private implementation of f_file_create_node_at().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param mode
 *   The file mode to assign.
 * @param device
 *   The device number for character and block file types.
 *   Is ignored by pipe file types.
 * @param file
 *   The data related to the file being created.
 *   This will be updated with the file descriptor.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_directory_descriptor (with error bit) for bad directory descriptor for at_id.
 *   F_file_found (with error bit) if a file was found while exclusive is TRUE.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for making changes.
 *   F_space_not (with error bit) if file system is out of space (or file system quota is reached).
 *   F_failure (with error bit) for any other error.
 *   F_supported_not (with error bit) for unsupported file types.
 *
 * @see mknodat()
 *
 * @see f_file_create_device_at()
 * @see f_file_create_node_at()
 */
#if !defined(_di_f_file_create_device_at_) || !defined(_di_f_file_create_node_at_)
  extern f_status_t private_f_file_create_node_at(const int at_id, const f_string_static_t path, const mode_t mode, const dev_t device) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_create_device_at_) || !defined(_di_f_file_create_node_at_)

/**
 * Private implementation of f_file_flush().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param id
 *   The file descriptor.
 *
 * @return
 *   F_none is returned on success.
 *
 *   F_file_descriptor (with error bit) if file descriptor is invalid.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_input_output (with error bit) on I/O error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_space_not (with error bit) if file system is out of space (or file system quota is reached).
 *   F_supported_not (with error bit) if the file system or file type does not support flushing.
 *   F_file_synchronize (with error bit) on any other failure.
 *
 * @see fsync()
 *
 * @see f_file_clone()
 * @see f_file_close()
 * @see f_file_close_flush()
 * @see f_file_copy()
 * @see f_file_create()
 * @see f_file_create_at()
 * @see f_file_stream_close()
 */
#if !defined(_di_f_file_clone_) || !defined(_di_f_file_close_) || !defined(_di_f_file_close_flush_) || !defined(_di_f_file_copy_) || !defined(_di_f_file_create_) || !defined(_di_f_file_create_at_) || !defined(_di_f_file_stream_close_)
  extern f_status_t private_f_file_flush(const int id) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_clone_) || !defined(_di_f_file_close_) || !defined(_di_f_file_close_flush_) || !defined(_di_f_file_copy_) || !defined(_di_f_file_create_) || !defined(_di_f_file_create_at_) || !defined(_di_f_file_stream_close_)

/**
 * Private implementation of f_file_link().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param target
 *   A path that the link points to.
 * @param point
 *   A path to the link that does the pointing.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_busy (with error bit) if file system is too busy to perform write.
 *   F_file_found (with error bit) if a file aleady exists at the path.
 *   F_file_found_not (with error bit) if a parent path in point does not exist or is a broken symlink.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for creating or linking.
 *   F_read_only (with error bit) if file system is read-only.
 *   F_failure (with error bit) for any other error.
 *
 * @see symlink()
 *
 * @see f_file_copy()
 * @see f_file_link()
 */
#if !defined(_di_f_file_link_) || !defined(_di_f_file_copy_)
  extern f_status_t private_f_file_link(const f_string_static_t target, const f_string_static_t point) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_link_) || !defined(_di_f_file_copy_)

/**
 * Private implementation of f_file_link_at().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which point point path is relative to.
 * @param target
 *   A path that the link points to.
 * @param point
 *   A path to the link that does the pointing.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_busy (with error bit) if file system is too busy to perform write.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_directory_descriptor (with error bit) for bad directory descriptor for at_id.
 *   F_file_found (with error bit) if a file aleady exists at the path.
 *   F_file_found_not (with error bit) if a parent path in point does not exist or is a broken symlink.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for creating or linking.
 *   F_read_only (with error bit) if file system is read-only.
 *   F_failure (with error bit) for any other error.
 *
 * @see symlinkat()
 *
 * @see f_file_link_at()
 */
#if !defined(_di_f_file_link_at_)
  extern f_status_t private_f_file_link_at(const int at_id, const f_string_static_t target, const f_string_static_t point) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_link_at_)

/**
 * Private implementation of f_file_link_read().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param path
 *   The path file name.
 * @param size
 *   The file size in bytes, such as (struct stat).st_size.
 * @param target
 *   Will be replaced with the path in which the link points to.
 *   Will be NULL terminated with the NULL at target.string[target.used];
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_file_found_not (with error bit) if the file at path was not found.
 *   F_input_output (with error bit) on I/O error.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if link target path is too large for string buffer size.
 *   F_failure (with error bit) for any other error.
 *
 * @see readlink()
 *
 * @see f_file_copy()
 * @see f_file_link_read()
 * @see f_string_dynamic_increase_by()
 * @see f_string_dynamic_terminate_after()
 */
#if !defined(_di_f_file_link_read_) || !defined(_di_f_file_copy_)
  extern f_status_t private_f_file_link_read(const f_string_static_t path, const off_t size, f_string_dynamic_t * const target) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_link_read_) || !defined(_di_f_file_copy_)

/**
 * Private implementation of f_file_link_read_at().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param size
 *   The file size in bytes, such as (struct stat).st_size.
 * @param target
 *   Will be replaced with the path in which the link points to.
 *   Will be NULL terminated with the NULL at target.string[target.used];
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_directory_descriptor (with error bit) for bad directory descriptor for at_id.
 *   F_file_found_not (with error bit) if the file at path was not found.
 *   F_input_output (with error bit) on I/O error.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if link target path is too large for string buffer size.
 *   F_failure (with error bit) for any other error.
 *
 * @see readlinkat()
 *
 * @see f_file_link_read_at()
 * @see f_string_dynamic_increase_by()
 * @see f_string_dynamic_terminate_after()
 */
#if !defined(_di_f_file_link_read_at_)
  extern f_status_t private_f_file_link_read_at(const int at_id, const f_string_static_t path, const off_t size, f_string_dynamic_t * const target) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_link_read_at_)

/**
 * Private implementation of f_file_mode_set().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param path
 *   The path file name.
 * @param mode
 *   The new mode to use.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_access_mode (with error bit) if the current user does not have access to assign the file mode.
 *   F_directory (with error bit) on invalid directory.
 *   F_file_found_not (with error bit) if file at path was not found.
 *   F_input_output (with error bit) on I/O error.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_read_only (with error bit) if file is read-only.
 *   F_failure (with error bit) for any other error.
 *
 * @see chmod()
 *
 * @see f_file_copy()
 * @see f_file_mode_set()
 */
#if !defined(_di_f_file_mode_set_) || !defined(_di_f_file_copy_)
  extern f_status_t private_f_file_mode_set(const f_string_static_t path, const mode_t mode) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_mode_set_) || !defined(_di_f_file_copy_)

/**
 * Private implementation of f_file_open().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param path
 *   The path file name.
 * @param mode
 *   The file mode to open in.
 * @param file
 *   The data related to the file being opened.
 *   This will be updated with the file descriptor.
 *
 * @return
 *   F_none on success.
 *
 *   F_file_descriptor (with error bit) if unable to load the file descriptor (the file pointer may still be valid).
 *   F_file_found_not (with error bit) if the file was not found.
 *   F_file_open (with error bit) if the file is already open.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see open()
 *
 * @see f_file_copy()
 * @see f_file_open()
 */
#if !defined(_di_f_file_open_) || !defined(_di_f_file_copy_)
  extern f_status_t private_f_file_open(const f_string_static_t path, const mode_t mode, f_file_t * const file) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_open_) || !defined(_di_f_file_copy_)

/**
 * Private implementation of f_file_open_at().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param mode
 *   The file mode to open in.
 * @param file
 *   The data related to the file being opened.
 *   This will be updated with the file descriptor.
 *
 * @return
 *   F_none on success.
 *
 *   F_directory_descriptor (with error bit) for bad directory descriptor for at_id.
 *   F_file_found_not (with error bit) if the file was not found.
 *   F_file_open (with error bit) if the file is already open.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see openat()
 *
 * @see f_file_create_at()
 * @see f_file_open_at()
 */
#if !defined(_di_f_file_create_at_) || !defined(_di_f_file_open_at_)
  extern f_status_t private_f_file_open_at(const int at_id, const f_string_static_t path, const mode_t mode, f_file_t * const file) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_create_at_) || !defined(_di_f_file_open_at_)

/**
 * Private implementation of f_file_role_change().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param path
 *   The path file name.
 * @param uid
 *   The new user id to use.
 * @param gid
 *   The new group id to use.
 * @param dereference
 *   Set to TRUE to dereference symlinks (often is what is desired).
 *   Set to FALSE to operate on the symlink itself.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_access_group (with error bit) if the current user does not have access to assign the specified group.
 *   F_access_owner (with error bit) if the current user does not have access to assign the specified owner.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_directory (with error bit) on invalid directory.
 *   F_file_found_not (with error bit) if file at path was not found.
 *   F_input_output (with error bit) on I/O error.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_read_only (with error bit) if file is read-only.
 *   F_failure (with error bit) for any other error.
 *
 * @see chown()
 * @see lchown()
 *
 * @see f_file_copy()
 * @see f_file_role_change()
 */
#if !defined(_di_f_file_role_change_) || !defined(_di_f_file_copy_)
  extern f_status_t private_f_file_role_change(const f_string_static_t path, const uid_t uid, const gid_t gid, const bool dereference) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_role_change_) || !defined(_di_f_file_copy_)

/**
 * Private implementation of f_file_role_change_at().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param uid
 *   The new user id to use.
 * @param gid
 *   The new group id to use.
 * @param flag
 *   Any valid flag, such as F_file_at_path_empty_d, F_file_at_automount_no_d, or F_file_at_symlink_follow_no_d.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_access_group (with error bit) if the current user does not have access to assign the specified group.
 *   F_access_owner (with error bit) if the current user does not have access to assign the specified owner.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_directory (with error bit) on invalid directory.
 *   F_directory_descriptor (with error bit) for bad directory descriptor for at_id.
 *   F_file_found_not (with error bit) if file at path was not found.
 *   F_input_output (with error bit) on I/O error.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_read_only (with error bit) if file is read-only.
 *   F_failure (with error bit) for any other error.
 *
 * @see fchownat()
 *
 * @see f_file_role_change_at()
 */
#if !defined(_di_f_file_role_change_at_)
  extern f_status_t private_f_file_role_change_at(const int at_id, const f_string_static_t path, const uid_t uid, const gid_t gid, const int flag) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_role_change_at_)

/**
 * Private implementation of f_file_stat().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param file_name
 *   The name of the file.
 * @param dereference
 *   Set to TRUE to dereference symlinks.
 *   Set to FALSE to operate on the symlink itself.
 * @param file_stat
 *   The statistics read.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) if access to the file was denied.
 *   F_directory (with error bit) on invalid directory.
 *   F_file_found_not (with error bit) if the file was not found.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see lstat()
 * @see stat()
 *
 * @see f_file_clone()
 * @see f_file_copy()
 * @see f_file_exists()
 * @see f_file_group_read()
 * @see f_file_is()
 * @see f_file_link_read()
 * @see f_file_mode_read()
 * @see f_file_owner_read()
 * @see f_file_size()
 * @see f_file_stat()
 * @see f_file_touch()
 * @see f_file_type()
 */
#if !defined(_di_f_file_clone_) || !defined(_di_f_file_copy_) || !defined(_di_f_file_exists_) || !defined(_di_f_file_group_read_) || !defined(_di_f_file_is_) || !defined(_di_f_file_link_read_) || !defined(_di_f_file_mode_read_) || !defined(_di_f_file_owner_read_) || !defined(_di_f_file_size_) || !defined(_di_f_file_stat_) || !defined(_di_f_file_touch_) || !defined(_di_f_file_type_)
  extern f_status_t private_f_file_stat(const f_string_static_t file_name, const bool dereference, struct stat * const file_stat) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_clone_) || !defined(_di_f_file_copy_) || !defined(_di_f_file_exists_) || !defined(_di_f_file_group_read_) || !defined(_di_f_file_is_) || !defined(_di_f_file_link_read_) || !defined(_di_f_file_mode_read_) || !defined(_di_f_file_owner_read_) || !defined(_di_f_file_size_) || !defined(_di_f_file_stat_) || !defined(_di_f_file_touch_) || !defined(_di_f_file_type_)

/**
 * Private implementation of f_file_stat_at().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param file_name
 *   The name of the file.
 * @param flag
 *   Any valid flag, such as F_file_at_path_empty_d, F_file_at_automount_no_d, or F_file_at_symlink_follow_no_d.
 * @param file_stat
 *   The statistics read.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) if access to the file was denied.
 *   F_directory (with error bit) on invalid directory.
 *   F_file_found_not (with error bit) if the file was not found.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fstatat()
 *
 * @see f_file_exists_at()
 * @see f_file_link_read_at()
 * @see f_file_mode_read_at()
 * @see f_file_size_at()
 * @see f_file_stat_at()
 * @see f_file_touch_at()
 * @see f_file_type_at()
 */
#if !defined(_di_f_file_exists_at_) || !defined(_di_f_file_link_read_at_) || !defined(_di_f_file_mode_read_at_) || !defined(_di_f_file_size_at_) || !defined(_di_f_file_stat_at_) || !defined(_di_f_file_touch_at_) || !defined(_di_f_file_type_at_)
  extern f_status_t private_f_file_stat_at(const int at_id, const f_string_static_t file_name, const int flag, struct stat * const file_stat) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_exists_at_) || !defined(_di_f_file_link_read_at_) || !defined(_di_f_file_mode_read_at_) || !defined(_di_f_file_size_at_) || !defined(_di_f_file_stat_at_) || !defined(_di_f_file_touch_at_) || !defined(_di_f_file_type_at_)

/**
 * Private implementation of f_file_stat_by_id().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param id
 *   The file descriptor.
 * @param file_stat
 *   The statistics read.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) if access to the file was denied.
 *   F_directory (with error bit) on invalid directory.
 *   F_file_found_not (with error bit) if the file was not found.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fstat()
 *
 * @see f_file_size_by_id()
 * @see f_file_stat_by_id()
 */
#if !defined(_di_f_file_stat_by_id_) || !defined(_di_f_file_size_by_id_)
  extern f_status_t private_f_file_stat_by_id(const int id, struct stat * const file_stat) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_stat_by_id_) || !defined(_di_f_file_size_by_id_)

/**
 * Special function for use in the f_file_stream_open() and related functions.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param flag
 *   The file flag.
 *
 * @return
 *   A string representing the file mode for use in fopen(), fdopen(), or freopen().
 *
 * @see f_file_stream_open_descriptor()
 * @see f_file_stream_open()
 * @see f_file_stream_reopen()
 */
#if !defined(_di_f_file_stream_open_descriptor_) || !defined(_di_f_file_stream_open_) || !defined(_di_f_file_stream_reopen_)
  extern const f_string_t private_f_file_stream_open_mode_determine(const int flag) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_stream_open_descriptor_) || !defined(_di_f_file_stream_open_) || !defined(_di_f_file_stream_reopen_)

/**
 * Private implementation of f_file_stream_write_until().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param file
 *   The file to write to.
 *   The file must already be open.
 * @param buffer
 *   The string to write to the file.
 * @param total
 *   The total bytes to write.
 * @param written
 *   The total bytes to written.
 *
 * @return
 *   F_none on success.
 *   F_none_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *
 *   F_file_write (with error bit) on error during file write.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see flockfile()
 * @see fwrite_unlocked()
 * @see funlockfile()
 *
 * @see f_file_stream_write()
 * @see f_file_stream_write_block()
 * @see f_file_stream_write_range()
 * @see f_file_stream_write_until()
 */
#if !defined(_di_f_file_stream_write_) || !defined(_di_f_file_stream_write_block_) || !defined(_di_f_file_stream_write_until) || !defined(_di_f_file_stream_write_range)
  extern f_status_t private_f_file_stream_write_until(const f_file_t file, const f_string_static_t buffer, const f_array_length_t total, f_array_length_t * const written) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_stream_write_) || !defined(_di_f_file_stream_write_block_) || !defined(_di_f_file_stream_write_until) || !defined(_di_f_file_stream_write_range)

/**
 * Private implementation of f_file_write_until().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param file
 *   The file to write to.
 *   The file must already be open.
 * @param buffer
 *   The string to write to the file.
 * @param total
 *   The total bytes to write.
 * @param written
 *   The total bytes written.
 *
 * @return
 *   F_none on success.
 *   F_none_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file (with error bit) if file descriptor is in an error state.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 *
 * @see f_file_write()
 * @see f_file_write_block()
 * @see f_file_write_range()
 * @see f_file_write_until()
 */
#if !defined(_di_f_file_write_) || !defined(_di_f_file_write_block_) || !defined(_di_f_file_write_until_) || !defined(_di_f_file_write_range)
  extern f_status_t private_f_file_write_until(const f_file_t file, const f_string_static_t buffer, const f_array_length_t total, f_array_length_t * const written) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_file_write_) || !defined(_di_f_file_write_block_) || !defined(_di_f_file_write_until_) || !defined(_di_f_file_write_range)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_file_h
