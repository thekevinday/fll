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
 * Private implementation of f_file_change_mode().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param path
 *   The path file name.
 * @param mode
 *   The new mode to use.
 * @param dereference
 *   Set to TRUE to dereference symlinks (often is what is desired).
 *   Set to FALSE to operate on the symlink itself.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_access_denied (with error bit) on access denied.
 *   F_name (with error bit) if the filename is too long.
 *   F_loop (with error bit) on loop error.
 *   F_file_found_not (with error bit) if file at path was not found.
 *   F_memory_out (with error bit) if out of memory.
 *   F_directory (with error bit) on invalid directory.
 *   F_prohibited (with error bit) if filesystem does not allow for file changes.
 *   F_read_only (with error bit) if file is read-only.
 *   F_input_output (with error bit) on I/O error.
 *   F_failure (with error bit) for any other (mkdir()) error.
 *
 * @see f_file_change_mode()
 * @see f_file_copy()
 */
#if !defined(_di_f_file_change_mode_) || !defined(_di_f_file_copy_)
  extern f_return_status private_f_file_change_mode(const f_string path, const mode_t mode, const bool dereference) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_file_change_mode_) || !defined(_di_f_file_copy_)

/**
 * Private implementation of f_file_change_mode_at().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param mode
 *   The new mode to use.
 * @param flags
 *   Any valid flag, such as AT_EMPTY_PATH, AT_NO_AUTOMOUNT, or AT_SYMLINK_NO_FOLLOW.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_access_denied (with error bit) on access denied.
 *   F_name (with error bit) if the filename is too long.
 *   F_loop (with error bit) on loop error.
 *   F_file_found_not (with error bit) if file at path was not found.
 *   F_memory_out (with error bit) if out of memory.
 *   F_directory (with error bit) on invalid directory.
 *   F_prohibited (with error bit) if filesystem does not allow for file changes.
 *   F_read_only (with error bit) if file is read-only.
 *   F_input_output (with error bit) on I/O error.
 *   F_failure (with error bit) for any other (mkdir()) error.
 *
 * @see f_file_change_mode_at()
 * @see f_file_copy_at()
 */
#if !defined(_di_f_file_change_mode_at_) || !defined(_di_f_file_copy_at_)
  extern f_return_status private_f_file_change_mode_at(const int at_id, const f_string path, const mode_t mode, const int flags) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_file_change_mode_at_) || !defined(_di_f_file_copy_at_)

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
 * @param dereference
 *   Set to TRUE to dereference symlinks (often is what is desired).
 *   Set to FALSE to operate on the symlink itself.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_access_denied (with error bit) on access denied.
 *   F_name (with error bit) if the filename is too long.
 *   F_loop (with error bit) on loop error.
 *   F_file_found_not (with error bit) if file at path was not found.
 *   F_memory_out (with error bit) if out of memory.
 *   F_directory (with error bit) on invalid directory.
 *   F_prohibited (with error bit) if filesystem does not allow for file changes.
 *   F_read_only (with error bit) if file is read-only.
 *   F_input_output (with error bit) on I/O error.
 *   F_failure (with error bit) for any other (mkdir()) error.
 *
 * @see f_file_change_owner()
 * @see f_file_copy()
 */
#if !defined(_di_f_file_change_owner_) || !defined(_di_f_file_copy_)
  extern f_return_status private_f_file_change_owner(const f_string path, const uid_t uid, const gid_t gid, const bool dereference) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_file_change_owner_) || !defined(_di_f_file_copy_)

/**
 * Private implementation of f_file_change_owner_at().
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
 * @param flags
 *   Any valid flag, such as AT_EMPTY_PATH, AT_NO_AUTOMOUNT, or AT_SYMLINK_NO_FOLLOW.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_access_denied (with error bit) on access denied.
 *   F_name (with error bit) if the filename is too long.
 *   F_loop (with error bit) on loop error.
 *   F_file_found_not (with error bit) if file at path was not found.
 *   F_memory_out (with error bit) if out of memory.
 *   F_directory (with error bit) on invalid directory.
 *   F_prohibited (with error bit) if filesystem does not allow for file changes.
 *   F_read_only (with error bit) if file is read-only.
 *   F_input_output (with error bit) on I/O error.
 *   F_failure (with error bit) for any other (mkdir()) error.
 *
 * @see f_file_change_owner_at()
 * @see f_file_copy_at()
 */
#if !defined(_di_f_file_change_owner_at_) || !defined(_di_f_file_copy_at_)
  extern f_return_status private_f_file_change_owner_at(const int at_id, const f_string path, const uid_t uid, const gid_t gid, const int flags) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_file_change_owner_at_) || !defined(_di_f_file_copy_at_)

/**
 * Private implementation of f_file_close().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param id
 *   The file descriptor.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_file_descriptor (with error bit) if file descriptor is invalid.
 *   F_interrupted (with error bit) if interrupt was received.
 *   F_input_output (with error bit) on I/O error.
 *   F_filesystem_quota_blocks (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   F_filesystem_quota_reached (with error bit) quota reached of filesystem is out of space.
 *   F_file_synchronize (with error bit) on flush failure.
 *   F_file_close (with error bit) if fclose() failed for any other reason.
 *
 * @see f_file_close()
 * @see f_file_copy()
 */
#if !defined(_di_f_file_close_) || !defined(_di_f_file_copy_)
  extern f_return_status private_f_file_close(int *id) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_file_close_) || !defined(_di_f_file_copy_)

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
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_access_denied (with error bit) on access denied.
 *   F_loop (with error bit) on loop error.
 *   F_file_found (with error bit) if a file was found while exclusive is TRUE.
 *   F_memory_out (with error bit) if out of memory.
 *   F_prohibited (with error bit) if filesystem does not allow for removing.
 *   F_read_only (with error bit) if file is read-only.
 *   F_failure (with error bit) for any other (mkdir()) error.
 *   F_filesystem_quota_blocks (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   F_space_not (with error bit) if filesystem is out of space (or filesystem quota is reached).
 *   F_file_found (with error bit) of a directory aleady exists at the path.
 *   F_name (with error bit) on path name error.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_interrupted (with error bit) when program received an interrupt signal, halting create.
 *   F_file_open_max (with error bit) when system-wide max open files is reached.
 *   F_busy (with error bit) if filesystem is too busy to perforrm write.
 *   F_file_read (with error bit) on file read error.
 *   F_file_write (with error bit) on file write error.
 *
 * @see f_file_copy()
 * @see f_file_clone()
 */
#if !defined(_di_f_file_copy_) || !defined(_di_f_file_clone_)
  extern f_return_status private_f_file_copy_content(const f_string source, const f_string destination, const f_number_unsigned size_block) f_gcc_attribute_visibility_internal;
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
 * @param file
 *   The data related to the file being opened.
 *   This will be updated with the file descriptor and file address.
 *   This will be updated with the create flags (ignoring and overriding existing file.flags).
 * @param exclusive
 *   If TRUE, will fail when file already exists.
 *   If FALSE, will not fail if file already exists.
 * @param dereference
 *   Set to TRUE to dereferenc symlinks (often is what is desired).
 *   Set to FALSE to fail if the path is a symbolic link.
 *   This does not write symbolic links. (@todo add function f_create_link() for creating symbolic links.)
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_access_denied (with error bit) on access denied.
 *   F_loop (with error bit) on loop error.
 *   F_file_found (with error bit) if a file was found while exclusive is TRUE.
 *   F_memory_out (with error bit) if out of memory.
 *   F_prohibited (with error bit) if filesystem does not allow for removing.
 *   F_read_only (with error bit) if file is read-only.
 *   F_failure (with error bit) for any other (mkdir()) error.
 *   F_filesystem_quota_blocks (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   F_filesystem_quota_reached (with error bit) quota reached of filesystem is out of space.
 *   F_file_found (with error bit) of a directory aleady exists at the path.
 *   F_name (with error bit) on path name error.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_interrupted (with error bit) when program received an interrupt signal, halting create.
 *   F_file_open_max (with error bit) when system-wide max open files is reached.
 *   F_busy (with error bit) if filesystem is too busy to perforrm write.
 *
 * @see f_file_copy()
 * @see f_file_create()
 */
#if !defined(_di_f_file_create_) || !defined(_di_f_file_copy_)
  extern f_return_status private_f_file_create(const f_string path, const mode_t mode, const bool exclusive, const bool dereference) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_file_create_) || !defined(_di_f_file_copy_)

/**
 * Private implementation of f_file_create_at().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param file
 *   The data related to the file being opened.
 *   This will be updated with the file descriptor and file address.
 *   This will be updated with the create flags (ignoring and overriding existing file.flags).
 * @param path
 *   The path file name.
 * @param mode
 *   The file mode to open in.
 * @param exclusive
 *   If TRUE, will fail when file already exists.
 *   If FALSE, will not fail if file already exists.
 * @param dereference
 *   Set to TRUE to dereferenc symlinks (often is what is desired).
 *   Set to FALSE to fail if the path is a symbolic link.
 *   This does not write symbolic links. (@todo add function f_create_link() for creating symbolic links.)
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_access_denied (with error bit) on access denied.
 *   F_loop (with error bit) on loop error.
 *   F_file_found (with error bit) if a file was found while exclusive is TRUE.
 *   F_memory_out (with error bit) if out of memory.
 *   F_prohibited (with error bit) if filesystem does not allow for removing.
 *   F_read_only (with error bit) if file is read-only.
 *   F_failure (with error bit) for any other (mkdir()) error.
 *   F_filesystem_quota_blocks (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   F_filesystem_quota_reached (with error bit) quota reached of filesystem is out of space.
 *   F_file_found (with error bit) of a directory aleady exists at the path.
 *   F_name (with error bit) on path name error.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_interrupted (with error bit) when program received an interrupt signal, halting create.
 *   F_file_open_max (with error bit) when system-wide max open files is reached.
 *   F_busy (with error bit) if filesystem is too busy to perforrm write.
 *
 * @see f_file_copy_at()
 * @see f_file_create_at()
 */
#if !defined(_di_f_file_create_at_) || !defined(_di_f_file_copy_at_)
  extern f_return_status private_f_file_create_at(const int at_id, const f_string path, const mode_t mode, const bool exclusive, const bool dereference) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_file_create_at_) || !defined(_di_f_file_copy_at_)

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
 *
 * @see f_file_copy()
 * @see f_file_link()
 */
#if !defined(_di_f_file_link_) || !defined(_di_f_file_copy_)
  extern f_return_status private_f_file_link(const f_string target, const f_string point) f_gcc_attribute_visibility_internal;
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
 *
 * @see f_file_copy_at()
 * @see f_file_link_at()
 */
#if !defined(_di_f_file_link_at_) || !defined(_di_f_file_copy_at_)
  extern f_return_status private_f_file_link_at(const int at_id, const f_string target, const f_string point) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_file_link_at_) || !defined(_di_f_file_copy_at_)

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
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_file_descriptor (with error bit) if file descriptor is invalid.
 *   F_input_output (with error bit) on I/O error.
 *   F_filesystem_quota_blocks (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   F_space_not (with error bit) if filesystem is out of space (or filesystem quota is reached).
 *   F_unsupported (with error bit) if the file system or file type does not support flushing.
 *   F_failure (with error bit) on any other failure.
 *
 * @see f_file_close()
 * @see f_file_copy()
 * @see f_file_flush()
 */
#if !defined(_di_f_file_flush_) || !defined(_di_f_file_close_) || !defined(_di_f_file_copy_)
  extern f_return_status private_f_file_flush(const int id) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_file_flush_) || !defined(_di_f_file_close_) || !defined(_di_f_file_copy_)

/**
 * Create a link to a file.
 *
 * This will not replace existing files/links.
 *
 * @param target
 *   A path that the link points to.
 * @param point
 *   A path to the link that does the pointing.
 *
 * @return
 *
 * @see f_file_link()
 * @see f_file_copy()
 */
#if !defined(_di_f_file_link_) || !defined(_di_f_file_copy_)
  extern f_return_status private_f_file_link(const f_string target, const f_string point);
#endif // !defined(_di_f_file_link_) || !defined(_di_f_file_copy_)

/**
 * Create a link to a file.
 *
 * This will not replace existing files/links.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param target
 *   A path that the link points to.
 * @param point
 *   A path to the link that does the pointing.
 *
 * @return
 *
 * @see f_file_link_at()
 * @see f_file_copy_at()
 */
#if !defined(_di_f_file_link_at_) || !defined(_di_f_file_copy_at_)
  extern f_return_status private_f_file_link_at(const int at_id, const f_string target, const f_string point);
#endif // !defined(_di_f_file_link_at_) || !defined(_di_f_file_copy_at_)

/**
 * Private implementation of f_file_open().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param path
 *   The path file name.
 * @param mode
 *   The file mode to open in.
 *   Set to 0 to not use.
 * @param file
 *   The data related to the file being opened.
 *   This will be updated with the file descriptor and file address.
 *
 * @return
 *   F_none on success.
 *   F_file_found_not (with error bit) if the file was not found.
 *   F_file_open (with error bit) if the file is already open.
 *   F_file_descriptor (with error bit) if unable to load the file descriptor (the file pointer may still be valid).
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_file_copy()
 * @see f_file_open()
 */
#if !defined(_di_f_file_open_) || !defined(_di_f_file_copy_)
  extern f_return_status private_f_file_open(const f_string path, const mode_t mode, f_file *file) f_gcc_attribute_visibility_internal;
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
 *   Set to 0 to not use.
 * @param file
 *   The data related to the file being opened.
 *   This will be updated with the file descriptor and file address.
 *
 * @return
 *   F_none on success.
 *   F_file_found_not (with error bit) if the file was not found.
 *   F_file_open (with error bit) if the file is already open.
 *   F_file_descriptor (with error bit) if unable to load the file descriptor (the file pointer may still be valid).
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_file_copy_at()
 * @see f_file_open_at()
 */
#if !defined(_di_f_file_open_at_) || !defined(_di_f_file_copy_at_)
  extern f_return_status private_f_file_open_at(const int at_id, const f_string path, const mode_t mode, f_file *file) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_file_open_at_) || !defined(_di_f_file_copy_at_)

/**
 * Private implementation of f_file_close().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param file_name
 *   The name of the file.
 * @param dereference
 *   Set to TRUE to dereference symlinks (often is what is desired).
 *   Set to FALSE to operate on the symlink itself.
 * @param file_stat
 *   The statistics read.
 *
 * @return
 *   F_none on success.
 *   F_name (with error bit) if the name is somehow invalid.
 *   F_memory_out (with error bit) if out of memory.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_directory (with error bit) on invalid directory.
 *   F_file_found_not (with error bit) if the file was not found.
 *   F_access_denied (with error bit) if access to the file was denied.
 *   F_loop (with error bit) if a loop occurred.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_file_copy()
 * @see f_file_stat()
 */
#if !defined(_di_f_file_stat_) || !defined(_di_f_file_copy_)
  extern f_return_status private_f_file_stat(const f_string file_name, const bool dereference, struct stat *file_stat) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_file_stat_) || !defined(_di_f_file_copy_)

/**
 * Private implementation of f_file_close().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param file_name
 *   The name of the file.
 * @param flags
 *   Any valid flag, such as AT_EMPTY_PATH, AT_NO_AUTOMOUNT, or AT_SYMLINK_NO_FOLLOW.
 * @param file_stat
 *   The statistics read.
 *
 *
 * @return
 *   F_none on success.
 *   F_name (with error bit) if the name is somehow invalid.
 *   F_memory_out (with error bit) if out of memory.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_directory (with error bit) on invalid directory.
 *   F_file_found_not (with error bit) if the file was not found.
 *   F_access_denied (with error bit) if access to the file was denied.
 *   F_loop (with error bit) if a loop occurred.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_file_copy_at()
 * @see f_file_stat_at()
 */
#if !defined(_di_f_file_stat_at_) || !defined(_di_f_file_copy_at_)
  extern f_return_status private_f_file_stat_at(const int at_id, const f_string file_name, const int flags, struct stat *file_stat) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_file_stat_at_) || !defined(_di_f_file_copy_at_)

/**
 * Private implementation of f_file_close().
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
 *   F_name (with error bit) if the name is somehow invalid.
 *   F_memory_out (with error bit) if out of memory.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_directory (with error bit) on invalid directory.
 *   F_file_found_not (with error bit) if the file was not found.
 *   F_access_denied (with error bit) if access to the file was denied.
 *   F_loop (with error bit) if a loop occurred.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_file_size_by_id()
 * @see f_file_stat_by_id()
 */
#if !defined(_di_f_file_stat_by_id_) || !defined(_di_f_file_size_by_id_)
  extern f_return_status private_f_file_stat_by_id(const int id, struct stat *file_stat) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_file_stat_by_id_) || !defined(_di_f_file_size_by_id_)

/**
 * Private implementation of private_f_file_write_until().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param file
 *   The file to write to.
 *   The file must already be open.
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
 * @see f_file_write()
 * @see f_file_write_range()
 * @see f_file_write_until()
 */
#if !defined(f_file_write) || !defined(f_file_write_until) || !defined(f_file_write_range)
  extern f_return_status private_f_file_write_until(const f_file file, const f_string string, const f_string_length total, f_string_length *written) f_gcc_attribute_visibility_internal;
#endif // !defined(f_file_write) || !defined(f_file_write_until) || !defined(f_file_write_range)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_file_h
