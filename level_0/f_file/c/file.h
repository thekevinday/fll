/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides structures and data types for a file I/O.
 * Provides operations for opening/closing files.
 *
 * @fixme Currently this uses makedev(3) to create devices, which is non-standad.
 *        The documentation for mknod(2) isn't clear on how to make major/minor based block and character devices.
 *        Find out how to implement this and elliminate the use of the non-standard makedev(3) call.
 */
#ifndef _F_file_h
#define _F_file_h

// Libc includes.
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <libgen.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// Non-standard libc includes.
#include <sys/sysmacros.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>

// FLL-0 file includes.
#include <fll/level_0/file/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Check if a file can be accessed.
 *
 * @param path
 *   The path file name.
 *
 * @return
 *   F_true if file exists.
 *   F_false if file does not exist.
 *   F_data_not if path.used is 0.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_directory (with error bit) on invalid directory.
 *   F_false (with error bit) on unknown/unhandled errors.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see access()
 */
#ifndef _di_f_file_access_
  extern f_status_t f_file_access(const f_string_static_t path);
#endif // _di_f_file_access_

/**
 * Copy a file, as well as its file mode and possibly the owner and group.
 *
 * The paths must not contain NULL except for the terminating NULL.
 * The paths must be NULL terminated.
 *
 * For directory file types, this will only copy the directory itself and not its contents.
 *
 * This does not copy unknown file types.
 *
 * @param source
 *   The path to the file to copy from.
 * @param destination
 *   The path to copy to.
 * @param role
 *   If TRUE, will copy the owner and group ids.
 *   If FALSE, will not copy the owner and group ids.
 *   (In both cases the file mode is copied.)
 * @param size_block
 *   The default number of chunks to read at a time with each chunk being 1-byte.
 *   Set to 0 to use default block read size.
 * @param exclusive
 *   If TRUE, will fail when file already exists.
 *   If FALSE, will not fail if file already exists (existing file will be replaced).
 *
 * @return
 *   F_none on success.
 *   F_data_not if source.used or destination.used is 0.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_access_group (with error bit) if the current user does not have access to assign the specified group.
 *   F_access_mode (with error bit) if the current user does not have access to assign the file mode.
 *   F_access_owner (with error bit) if the current user does not have access to assign the specified owner.
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
 */
#ifndef _di_f_file_clone_
  extern f_status_t f_file_clone(const f_string_static_t source, const f_string_static_t destination, const bool role, const f_number_unsigned_t size_block, const bool exclusive);
#endif // _di_f_file_clone_

/**
 * Close an open file.
 *
 * Will not flush before closing.
 *
 * @param id
 *   The file descriptor.
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
 *   F_space_not (with error bit) if file system is out of space (or file system quota is reached).
 *
 * @see fclose()
 */
#ifndef _di_f_file_close_
  extern f_status_t f_file_close(int * const id);
#endif // _di_f_file_close_

/**
 * Close an open file.
 *
 * Will flush before closing.
 *
 * @param id
 *   The file descriptor.
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
 *   F_space_not (with error bit) if file system is out of space (or file system quota is reached).
 *
 * @see fclose()
 */
#ifndef _di_f_file_close_flush_
  extern f_status_t f_file_close_flush(int * const id);
#endif // _di_f_file_close_flush_

/**
 * Copy a file.
 *
 * The paths must not contain NULL except for the terminating NULL.
 * The paths must be NULL terminated.
 *
 * For directory file types, this will only copy the directory itself and not its contents.
 *
 * This does not copy unknown file types.
 *
 * This does not set mode based on umask(), be sure to apply umask if so desired.
 * (such as: mode & ~mask).
 *
 * @param source
 *   The path to the file to copy from.
 * @param destination
 *   The path to copy to.
 * @param mode
 *   The file mode assigned to the destination file, based on the file type.
 * @param size_block
 *   The default number of chunks to read at a time with each chunk being 1-byte.
 *   Set to 0 to use default block read size.
 * @param exclusive
 *   If TRUE, will fail when file already exists.
 *   If FALSE, will not fail if file already exists (existing file will be replaced).
 *
 * @return
 *   F_none on success.
 *   F_data_not if source.used or destination.used is 0.
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
 */
#ifndef _di_f_file_copy_
  extern f_status_t f_file_copy(const f_string_static_t source, const f_string_static_t destination, const f_mode_t mode, const f_number_unsigned_t size_block, const bool exclusive);
#endif // _di_f_file_copy_

/**
 * Create a (regular) file based on the given path and file mode.
 *
 * The file will not be open after calling this.
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
 *   F_data_not if path.used is 0.
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
 */
#ifndef _di_f_file_create_
  extern f_status_t f_file_create(const f_string_static_t path, const mode_t mode, const bool exclusive);
#endif // _di_f_file_create_

/**
 * Create a (regular) file based on the given path and file mode.
 *
 * The file will not be open after calling this.
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
 *   F_data_not if path.used is 0.
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
 */
#ifndef _di_f_file_create_at_
  extern f_status_t f_file_create_at(const int at_id, const f_string_static_t path, const mode_t mode, const bool exclusive);
#endif // _di_f_file_create_at_

/**
 * Create a device node based on the given path and file mode.
 *
 * Warning: Due to the current status of POSIX and LINUX in regards to major and minor devices, this utilizes the non-POSI makedev() function.
 *
 * @param path
 *   The path file name.
 * @param mode
 *   The file mode to assign.
 * @param major
 *   The major device number for character and block file types.
 *   Is ignored by pipe file types.
 * @param minor
 *   The minor device number for character and block file types.
 *   Is ignored by pipe file types.
 *
 * @return
 *   F_none on success.
 *   F_data_not if path.used is 0.
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
 * @see makedev()
 * @see mknod()
 */
#ifndef _di_f_file_create_device_
  extern f_status_t f_file_create_device(const f_string_static_t path, const mode_t mode, const unsigned int major, const unsigned int minor);
#endif // _di_f_file_create_device_

/**
 * Create a device node based on the given path and file mode.
 *
 * Warning: Due to the current status of POSIX and LINUX in regards to major and minor devices, this utilizes the non-POSI makedev() function.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param mode
 *   The file mode to assign.
 * @param major
 *   The major device number for character and block file types.
 *   Is ignored by pipe file types.
 * @param minor
 *   The minor device number for character and block file types.
 *   Is ignored by pipe file types.
 *
 * @return
 *   F_none on success.
 *   F_data_not if path.used is 0.
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
 *   F_supported_not (with error bit) for unsupported file types.
 *   F_failure (with error bit) for any other error.
 *
 * @see makedev()
 * @see mknodat()
 */
#ifndef _di_f_file_create_device_at_
  extern f_status_t f_file_create_device_at(const int at_id, const f_string_static_t path, const mode_t mode, const unsigned int major, const unsigned int minor);
#endif // _di_f_file_create_device_at_

/**
 * Create a fifo based on the given path and file mode.
 *
 * @param path
 *   The path file name.
 * @param mode
 *   The file mode to assign.
 *
 * @return
 *   F_none on success.
 *   F_data_not if path.used is 0.
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
 */
#ifndef _di_f_file_create_fifo_
  extern f_status_t f_file_create_fifo(const f_string_static_t path, const mode_t mode);
#endif // _di_f_file_create_fifo_

/**
 * Create a fifo based on the given path and file mode.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param mode
 *   The file mode to assign.
 *
 * @return
 *   F_none on success.
 *   F_data_not if path.used is 0.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_directory_descriptor (with error bit) for bad directory descriptor for at_id.
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
 * @see mkfifoat()
 */
#ifndef _di_f_file_create_fifo_at_
  extern f_status_t f_file_create_fifo_at(const int at_id, const f_string_static_t path, const mode_t mode);
#endif // _di_f_file_create_fifo_at_

/**
 * Create a node based on the given path and file mode.
 *
 * @param path
 *   The path file name.
 * @param mode
 *   The file mode to assign.
 * @param device
 *   The device number for character and block file types.
 *   Is ignored by pipe file types.
 *
 * @return
 *   F_none on success.
 *   F_data_not if path.used is 0.
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
 */
#ifndef _di_f_file_create_node_
  extern f_status_t f_file_create_node(const f_string_static_t path, const mode_t mode, const dev_t device);
#endif // _di_f_file_create_node_

/**
 * Create a node based on the given path and file mode.
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
 *
 * @return
 *   F_none on success.
 *   F_data_not if path.used is 0.
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
 */
#ifndef _di_f_file_create_node_at_
  extern f_status_t f_file_create_node_at(const int at_id, const f_string_static_t path, const mode_t mode, const dev_t device);
#endif // _di_f_file_create_node_at_

/**
 * Identify the file descriptor of a valid file stream.
 *
 * @param file
 *   The file stream to get descriptor of.
 *
 * @return
 *   F_none is returned on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_file (with error bit) if file is not a valid stream.
 *
 * @see fileno()
 */
#ifndef _di_f_file_descriptor_
  extern f_status_t f_file_descriptor(f_file_t * const file);
#endif // _di_f_file_descriptor_

/**
 * Identify whether or not a file exists at the given path.
 *
 * This does not require access on the file itself.
 * This only requires access via the parent directories in the path.
 *
 * @param path
 *   The path file name.
 *
 * @return
 *   F_true if path was found.
 *   F_false if path was not found.
 *   F_data_not if path.used is 0.
 *
 *   F_access_denied (with error bit) if access to the file was denied.
 *   F_directory (with error bit) on invalid directory.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see stat()
 */
#ifndef _di_f_file_exists_
  extern f_status_t f_file_exists(const f_string_static_t path);
#endif // _di_f_file_exists_

/**
 * Identify whether or not a file exists at the given path.
 *
 * This does not require access on the file itself.
 * This only requires access via the parent directories in the path.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param flag
 *   Any valid flag, such as F_file_at_path_empty_d, F_file_at_automount_no_d, or F_file_at_symlink_follow_no_d.
 *
 * @return
 *   F_true if file exists.
 *   F_false if file does not exist.
 *   F_data_not if path.used is 0.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_directory (with error bit) on invalid directory.
 *   F_false (with error bit) on unknown/unhandled errors.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fstatat()
 */
#ifndef _di_f_file_exists_at_
  extern f_status_t f_file_exists_at(const int at_id, const f_string_static_t path, const int flag);
#endif // _di_f_file_exists_at_

/**
 * Flush the file.
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
 *   F_failure (with error bit) on any other failure.
 *
 * @see fsync()
 */
#ifndef _di_f_file_flush_
  extern f_status_t f_file_flush(const int id);
#endif // _di_f_file_flush_

/**
 * Get the current group of a file.
 *
 * @param path
 *   The path file name.
 * @param group
 *   The id of the file's group.
 *
 * @return
 *   F_none on success.
 *   F_data_not if path.used is 0.
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
 */
#ifndef _di_f_file_group_read_
  extern f_status_t f_file_group_read(const f_string_static_t path, uid_t * const group);
#endif // _di_f_file_group_read_

/**
 * Identify whether or not a file exists at the given path and if that file is a specific type.
 *
 * This does not require access on the file itself.
 * This only requires access via the parent directories in the path.
 *
 * @param path
 *   The path file name.
 * @param type
 *   The type of the file.
 * @param dereference
 *   Set to TRUE to dereference symlinks (often is what is desired).
 *   Set to FALSE to operate on the symlink itself.
 *
 * @return
 *   F_true if path was found and path is type.
 *   F_false if path was found and path is not type.
 *   F_file_found_not if the path was not found.
 *   F_data_not if path.used is 0.
 *
 *   F_access_denied (with error bit) if access to the file was denied.
 *   F_directory (with error bit) on invalid directory.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see stat()
 */
#ifndef _di_f_file_is_
  extern f_status_t f_file_is(const f_string_static_t path, const int type, const bool dereference);
#endif // _di_f_file_is_

/**
 * Identify whether or not a file exists at the given path within the parent directory and if that file is a specific type.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param type
 *   The type of the file.
 * @param flag
 *   Any valid flag, such as F_file_at_path_empty_d, F_file_at_automount_no_d, or F_file_at_symlink_follow_no_d.
 *
 * @return
 *   F_true if path was found and path is type.
 *   F_false if path was found and path is not type.
 *   F_file_found_not if the path was not found.
 *   F_data_not if path.used is 0.
 *
 *   F_access_denied (with error bit) if access to the file was denied.
 *   F_directory (with error bit) on invalid directory.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fstatat()
 */
#ifndef _di_f_file_is_at_
  extern f_status_t f_file_is_at(const int at_id, const f_string_static_t path, const int type, const int flag);
#endif // _di_f_file_is_at_

/**
 * Create a symbolic link to a file.
 *
 * This will not replace existing files/links.
 * This does not validate the existence of target.
 *
 * @param target
 *   A path that the link points to.
 * @param point
 *   A path to the link that does the pointing.
 *
 * @return
 *   F_none on success.
 *   F_data_not if target.used or point.used is 0.
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
 */
#ifndef _di_f_file_link_
  extern f_status_t f_file_link(const f_string_static_t target, const f_string_static_t point);
#endif // _di_f_file_link_

/**
 * Create a symbolic link to a file.
 *
 * This will not replace existing files/links.
 * This does not validate the existence of target.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which point path is relative to.
 * @param target
 *   A path that the link points to.
 * @param point
 *   A path to the link that does the pointing.
 *
 * @return
 *   F_none on success.
 *   F_data_not if target.used or point.used is 0.
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
 */
#ifndef _di_f_file_link_at_
  extern f_status_t f_file_link_at(const int at_id, const f_string_static_t target, const f_string_static_t point);
#endif // _di_f_file_link_at_

/**
 * Create a hard link to a file.
 *
 * This will not replace existing files/links.
 *
 * @param target
 *   A path that the link points to.
 * @param point
 *   A path to the link that does the pointing.
 *
 * @return
 *   F_none on success.
 *   F_data_not if target.used or point.used is 0.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_busy (with error bit) if file system is too busy to perform write.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
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
 * @see link()
 */
#ifndef _di_f_file_link_hard_
  extern f_status_t f_file_link_hard(const f_string_static_t target, const f_string_static_t point);
#endif // _di_f_file_link_hard_

/**
 * Create a hard link to a file.
 *
 * This will not replace existing files/links.
 *
 * @param at_id_target
 *   The parent directory, as an open directory file descriptor, in which target path is relative to.
 * @param at_id_point
 *   The parent directory, as an open directory file descriptor, in which point path is relative to.
 * @param target
 *   A path that the link points to.
 * @param point
 *   A path to the link that does the pointing.
 * @param flag
 *   Any valid flag, such as F_file_at_path_empty_d, F_file_at_automount_no_d, or F_file_at_symlink_follow_no_d.
 *
 * @return
 *   F_none on success.
 *   F_data_not if target.used or point.used is 0.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_busy (with error bit) if file system is too busy to perform write.
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
 * @see linkat()
 */
#ifndef _di_f_file_link_hard_at_
  extern f_status_t f_file_link_hard_at(const int at_id_target, const int at_id_point, const f_string_static_t target, const f_string_static_t point, const int flag);
#endif // _di_f_file_link_hard_at_

/**
 * Get the target a given link points to.
 *
 * This does not require access on the file itself.
 * This only requires access via the parent directories in the path.
 *
 * @param path
 *   The path file name.
 * @param link_stat
 *   The link file statistics.
 * @param target
 *   Will be replaced with the path in which the link points to.
 *   Will be NULL terminated with the NULL at target.string[target.used];
 *
 * @return
 *   F_none on success.
 *   F_data_not if path.used is 0.
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
 */
#ifndef _di_f_file_link_read_
  extern f_status_t f_file_link_read(const f_string_static_t path, const struct stat link_stat, f_string_dynamic_t * const target);
#endif // _di_f_file_link_read_

/**
 * Get the target a given link points to.
 *
 * This does not require access on the file itself.
 * This only requires access via the parent directories in the path.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param link_stat
 *   The link file statistics.
 * @param target
 *   Will be replaced with the path in which the link points to.
 *   Will be NULL terminated with the NULL at target.string[target.used];
 *
 * @return
 *   F_none on success.
 *   F_data_not if path.used is 0.
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
 */
#ifndef _di_f_file_link_read_at_
  extern f_status_t f_file_link_read_at(const int at_id, const f_string_static_t path, const struct stat link_stat, f_string_dynamic_t * const target);
#endif // _di_f_file_link_read_at_

/**
 * Determine how the mode should be applied based on different file properties and the given mode properties.
 *
 * This does not set mode based on umask(), which is already applied if f_file_mode_from_string() was used to create mode_change.
 *
 * @fixme apparently "u+g" is valid such that the mode from the group (g) is applied to the user (u) mode.
 *
 * @param mode_file
 *   The mode_t value representing the file's current mode.
 *   This is expected to be populated from (struct stat).st_mode.
 * @param mode_change
 *   The file mode values to change.
 * @param mode_replace
 *   The modes designated to be replaced instead of simply changed.
 * @param directory_is
 *   Set to TRUE if the file is a directory, FALSE otherwise.
 * @param mode
 *   The determined mode.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_file_mode_from_string()
 */
#ifndef _di_f_file_mode_determine_
  extern f_status_t f_file_mode_determine(const mode_t mode_file, const f_file_mode_t mode_change, const uint8_t mode_replace, const bool directory_is, mode_t * const mode);
#endif // _di_f_file_mode_determine_

/**
 * Get the file mode id from a string syntax.
 *
 * The string syntax is defined as follows:
 *   '([ugoa]*[-+=]{0,1}([rwxXst]|[ugo])+([,][ugoa]*[-+=]{0,1}([rwxXst]|[ugo])+)*)|([-+=]{0,1}0*[0-7]{1,4})'.
 *
 * Such that:
 *   'u' = apply to user.
 *   'g' = apply to group.
 *   'o' = apply to other/world.
 *   'a' = apply to all (user, group, and other/world).
 *   '-' = remove the specified modes.
 *   '+' = add the specified modes.
 *   '=' = overwrite all existing modes with this set.
 *   'r' = read mode.
 *   'w' = write mode.
 *   'x' = execute mode.
 *   'X' = execute mode, only if already executable directory or is file with owner already has executable bit.
 *   's' = set-gid/set-uid mode.
 *   't' = sticky-bit mode.
 *   '0' = no mode.
 *   '1' = execute mode.
 *   '2' = write mode.
 *   '3' = execute and write mode.
 *   '4' = read mode.
 *   '5' = execute and read mode.
 *   '6' = read and write mode.
 *   '7' = execute, read, and write mode.
 *
 * When there are 4 digits with a non-zero leading digit (such as 2000 or 002000):
 *   '1' = sticky-bit mode.
 *   '2' = set-gid mode.
 *   '3' = sticky-bit and set-gid mode.
 *   '4' = set-uid mode.
 *   '5' = sticky-bit and set-uid mode.
 *   '6' = set-uid and set-gid mode.
 *   '7' = sticky-bit, set-uid, and set-gid mode.
 *
 * When using digits, each set of 0-7 represents the following:
 *   [0]+  = set all bits to 0.
 *   [0-7] = apply to other/world.
 *   [0-7][0-7] = first ([1-7]) to group and second ([0-7]) to other/world.
 *   [0-7][0-7][0-7] = first ([1-7]) to owner, second ([0-7]) to group, and third ([0-7]) to other/world.
 *   [0-7][0-7][0-7][0-7] = first ([1-7]) to stick/set-uid/set-gid, second ([0-7]) to owner, third ([0-7]) to owner, and fourth ([0-7]) to other/world.
 *
 * When using digits, the umask is always ignored.
 * When there is a leading '0' or '=' when using digits, then the special bits should be replaced.
 * Otherwise, the current special bits are intended to be respected (designated by F_file_mode_t_replace_directory_d).
 *
 * When using non-digits and '+', '-', or '=' are specified without a leading 'a', 'u', 'g', or 'o', then the mode operations should be performed against the current umask.
 * These are designated with the umask hows, such as f_file_mode_how_umask_replace.
 *
 * There are problems with the chmod documentation (as of GNU coreutils 8.30):
 * 1) "The operator + causes the selected file mode bits to be added to the existing file mode bits of each file; - causes them to be removed; and = causes them to be added and causes unmentioned bits to be re‐moved except that a directory's unmentioned set user and group ID bits are not affected."
 *   - This means that "chmod =1 some_directory" would not change the setuid/setgid/sticky bits, however, in practice it does change it!
 * 2) "For directories chmod preserves set-user-ID and set-group-ID bits unless you explicitly specify other‐wise. You can set or clear the bits with symbolic modes like u+s and g-s. To clear these bits for directories with a numeric mode requires an additional leading zero, or leading = like 00755, or =755"
 *   - This directly contradicts quote "1" above, which effectively states "=755" would preserve the bits while quote "2" states that it clears the bits.
 *   - This means that "chmod 1 some_directory" would not change the setuid/setgid/sticky bits, however, in practice it does change it!
 *
 * Considering the behavior, assume that when "=" or a leading "0" is provided, this will change the setuid/setgid/sticky bits, otherwise it preserves those bits for directories.
 *
 * @fixme the possibilities are a bit extensive and this needs additional review; remove this fixme when this review is completed.
 *
 * @fixme apparently "u+g" is valid such that the mode from the group (g) is applied to the user (u) mode.
 *
 * @param code
 *   A NULL terminated string designating the desired mode, following the above string syntax.
 * @param umask
 *   The umask to be applied to the file mode, when applicable.
 * @param mode
 *   The determined mode.
 *   This uses bitwise data.
 * @param replace
 *   The determined modes that are to be replaced, such as: F_file_mode_t_replace_owner_d.
 *   This uses bitwise data.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_syntax (with error bit) if the string fails to follow the syntax rules.
 *
 *   The parameters how, mode_normal, and mode_executable are all set to 0 on error.
 *
 * @see private_f_file_mode_determine()
 */
#ifndef _di_f_file_mode_from_string_
  extern f_status_t f_file_mode_from_string(const f_string_static_t code, const mode_t umask, f_file_mode_t * const mode, uint8_t * const replace);
#endif // _di_f_file_mode_from_string_

/**
 * Get the current file mode as an f_file_mode_t.
 *
 * @param path
 *   The path file name.
 * @param mode
 *   The read file mode.
 *
 * @return
 *   F_none on success.
 *   F_data_not if path.used is 0.
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
 */
#ifndef _di_f_file_mode_read_
  extern f_status_t f_file_mode_read(const f_string_static_t path, mode_t * const mode);
#endif // _di_f_file_mode_read_

/**
 * Get the current file mode as an f_file_mode_t.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param mode
 *   The read file mode.
 *
 * @return
 *   F_none on success.
 *   F_data_not if path.used is 0.
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
 */
#ifndef _di_f_file_mode_read_at_
  extern f_status_t f_file_mode_read_at(const int at_id, const f_string_static_t path, mode_t * const mode);
#endif // _di_f_file_mode_read_at_

/**
 * Change mode of a given file at the specified path.
 *
 * This does not set mode based on umask(), be sure to apply umask if so desired.
 * (such as: mode & ~mask).
 *
 * @param path
 *   The path file name.
 * @param mode
 *   The new mode to use.
 *
 * @return
 *   F_none on success.
 *   F_data_not if path.used is 0.
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
 */
#ifndef _di_f_file_mode_set_
  extern f_status_t f_file_mode_set(const f_string_static_t path, const mode_t mode);
#endif // _di_f_file_mode_set_

/**
 * Change mode of a given file at the specified path.
 *
 * This does not set mode based on umask(), be sure to apply umask if so desired.
 * (such as: mode & ~mask).
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param mode
 *   The new mode to use.
 *
 * @return
 *   F_none on success.
 *   F_data_not if path.used is 0.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_access_mode (with error bit) if the current user does not have access to assign the file mode.
 *   F_file_found_not (with error bit) if file at path was not found.
 *   F_directory (with error bit) on invalid directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_read_only (with error bit) if file is read-only.
 *   F_failure (with error bit) for any other error.
 *
 * @see fchmodat()
 */
#ifndef _di_f_file_mode_set_at_
  extern f_status_t f_file_mode_set_at(const int at_id, const f_string_static_t path, const mode_t mode);
#endif // _di_f_file_mode_set_at_

/**
 * Convert an f_file_mode_t type to a mode_t type.
 *
 * This essentially converts all "add" codes from an f_file_mode_t to a mode_t, ignoring the "subtract" codes.
 *
 * @param from
 *   The file mode to convert from.
 * @param to
 *   The determined mode.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_file_mode_from_string()
 */
#ifndef _di_f_file_mode_to_mode_
  extern f_status_t f_file_mode_to_mode(const f_file_mode_t from, mode_t * const to);
#endif // _di_f_file_mode_to_mode_

/**
 * Get the base name of a file path.
 *
 * @param path
 *   The path file name.
 *   Need not be NULL terminated.
 * @param name_base
 *   The resulting base name as per basename().
 *   The base name is appended onto this.
 *   This is NULL terminated after the name_directory.used.
 *
 * @return
 *   F_none on success.
 *   F_data_not if path.used is 0.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if string is too large to store in the buffer.
 *
 *   Errors (with error bit) from: f_string_dynamic_increase_by().
 *
 * @see basename()
 *
 * @see f_string_dynamic_increase_by()
 */
#ifndef _di_f_file_name_base_
  extern f_status_t f_file_name_base(const f_string_static_t path, f_string_dynamic_t * const name_base);
#endif // _di_f_file_name_base_

/**
 * Get the directory name of a file path.
 *
 * @param path
 *   The path file name.
 *   Need not be NULL terminated.
 * @param name_directory
 *   The resulting base name as per dirname().
 *   The directory name is appended onto this.
 *   This is NULL terminated after the name_directory.used.
 *
 * @return
 *   F_none on success.
 *   F_data_not if path.used is 0.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if string is too large to store in the buffer.
 *
 *   Errors (with error bit) from: f_string_dynamic_increase_by().
 *
 * @see dirname()
 *
 * @see f_string_dynamic_increase_by()
 */
#ifndef _di_f_file_name_directory_
  extern f_status_t f_file_name_directory(const f_string_static_t path, f_string_dynamic_t * const name_directory);
#endif // _di_f_file_name_directory_

/**
 * Open a particular file and save its stream.
 *
 * This will open the file as a file descriptor.
 * This does not open a file stream.
 *
 * @param path
 *   The path file name.
 * @param mode
 *   The file mode to open in.
 *   Set to 0 to not use.
 * @param file
 *   The data related to the file being opened.
 *   This will be updated with the file descriptor.
 *
 * @return
 *   F_none is returned on success.
 *   F_data_not if path.used is 0.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_busy (with error bit) if file system is too busy to perform write.
 *   F_file_found_not (with error bit) if the file was not found.
 *   F_file_open_max (with error bit) when system-wide max open files is reached.
 *   F_file_type_not_directory (with error bit) if F_NOTIFY was specified and file.id is not a directory.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name is too long.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for making changes.
 *   F_read_only (with error bit) if file is read-only.
 *   F_supported_not (with error bit) fo unsupported file types.
 *   F_failure (with error bit) for any other error.
 *
 * @see open()
 */
#ifndef _di_f_file_open_
  extern f_status_t f_file_open(const f_string_static_t path, const mode_t mode, f_file_t * const file);
#endif // _di_f_file_open_

/**
 * Open a particular file and save its stream.
 *
 * This will open the file as a file descriptor.
 * This does not open a file stream.
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
 *   This will be updated with the file descriptor.
 *
 * @return
 *   F_none on success.
 *   F_data_not if path.used is 0.
 *
 *   F_directory_descriptor (with error bit) for bad directory descriptor for at_id.
 *   F_file_found_not (with error bit) if the file was not found.
 *   F_file_open (with error bit) if the file is already open.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see openat()
 */
#ifndef _di_f_file_open_at_
  extern f_status_t f_file_open_at(const int at_id, const f_string_static_t path, const mode_t mode, f_file_t * const file);
#endif // _di_f_file_open_at_

/**
 * Get the current owner of a file.
 *
 * @param path
 *   The path file name.
 * @param owner
 *   The id of the file's owner.
 *
 * @return
 *   F_none on success.
 *   F_data_not if path.used is 0.
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
 */
#ifndef _di_f_file_owner_read_
  extern f_status_t f_file_owner_read(const f_string_static_t path, uid_t * const owner);
#endif // _di_f_file_owner_read_

/**
 * Read until EOF is reached.
 *
 * To determine how much was read into the buffer, record buffer->used before execution and compare to buffer->used after execution.
 *
 * @param file
 *   The file to read.
 *   The file must already be open.
 * @param buffer
 *   The buffer the file is being read into.
 *   The contents of the file is appended into this buffer.
 *
 * @return
 *   F_none_eof on success and EOF was reached.
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the read would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_increase_by().
 *
 * @see read()
 *
 * @see f_string_dynamic_increase_by()
 */
#ifndef _di_f_file_read_
  extern f_status_t f_file_read(const f_file_t file, f_string_dynamic_t * const buffer);
#endif // _di_f_file_read_

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
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the read would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see read()
 */
#ifndef _di_f_file_read_block_
  extern f_status_t f_file_read_block(const f_file_t file, f_string_dynamic_t * const buffer);
#endif // _di_f_file_read_block_

/**
 * Read until a given number or EOF is reached, storing it in the buffer.
 *
 * To determine how much was read into the buffer, record buffer->used before execution and compare to buffer->used after execution.
 *
 * This is different from simply using the file.size_read.
 * The file.size_read represents the amount to process at a given time.
 * The total represents the maximum number of file.size_read to process.
 * For example, if file.size_read is 16 and total is 128, then this function would need to be called 8 times until total is reached.
 *
 * @param file
 *   The file to read.
 *   The file must already be open.
 * @param total
 *   The total bytes to read, unless EOF is reached first.
 * @param buffer
 *   The buffer the file is being read into.
 *
 * @return
 *   F_none_eof on success and EOF was reached.
 *   F_none_stop on success and total was reached.
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the read would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see read()
 */
#ifndef _di_f_file_read_until_
  extern f_status_t f_file_read_until(const f_file_t file, const f_array_length_t total, f_string_dynamic_t * const buffer);
#endif // _di_f_file_read_until_

/**
 * Remove a file.
 *
 * @param path
 *   The path file name.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_busy (with error bit) if file is busy.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_file_found_not (with error bit) if file not found.
 *   F_file_type_directory (with error bit) file is a directory (directories cannot be removed via this function).
 *   F_input_output (with error bit) if an I/O error occurred.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for making changes.
 *   F_read_only (with error bit) if file is read-only.
 *   F_failure (with error bit) for any other error.
 *
 * @see unlink()
 */
#ifndef _di_f_file_remove_
  extern f_status_t f_file_remove(const f_string_static_t path);
#endif // _di_f_file_remove_

/**
 * Remove a file.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param flag
 *   Any valid flag, such as F_file_at_path_empty_d, F_file_at_automount_no_d, or F_file_at_symlink_follow_no_d.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_busy (with error bit) if file is busy.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_file_found_not (with error bit) if file not found.
 *   F_file_type_directory (with error bit) file is a directory (directories cannot be removed via this function).
 *   F_input_output (with error bit) if an I/O error occurred.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for making changes.
 *   F_read_only (with error bit) if file is read-only.
 *   F_failure (with error bit) for any other error.
 *
 * @see unlinkat()
 */
#ifndef _di_f_file_remove_at_
  extern f_status_t f_file_remove_at(const int at_id, const f_string_static_t path, const int flag);
#endif // _di_f_file_remove_at_

/**
 * Rename a file.
 *
 * The paths must not contain NULL except for the terminating NULL.
 * The paths must be NULL terminated.
 *
 * This essentially renames a file but can also change the file's path, which is identical to a move.
 * However, renames only work within a file system and cannot be moved to another file system.
 *
 * If destination already exists, then according to rename(), destination will be atomically replaced.
 * Which, if destination is a directory, then that directory must either not exist or be empty.
 *
 * @param source
 *   The path to the file to copy from.
 * @param destination
 *   The path to copy to.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_busy (with error bit) if file system is too busy to perform write.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_directory_empty_not (with error bit) if the destination is a non-empty directory.
 *   F_file_found_not (with error bit) if file at path was not found.
 *   F_file_type_directory (with error bit) if destination is a directory but source is not.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_link (with error bit) if source or destination has the maxiumum associated links.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_mount (with error bit) if source and destination are not within the same mounted filesystems.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for making changes.
 *   F_read_only (with error bit) if file is read-only.
 *   F_space_not (with error bit) if file system is out of space (or file system quota is reached).
 *   F_failure (with error bit) for any other error.
 *
 * @see rename()
 */
#ifndef _di_f_file_rename_
  extern f_status_t f_file_rename(const f_string_static_t source, const f_string_static_t destination);
#endif // _di_f_file_rename_

/**
 * Rename a file.
 *
 * The paths must not contain NULL except for the terminating NULL.
 * The paths must be NULL terminated.
 *
 * This essentially renames a file but can also change the file's path, which is identical to a move.
 * However, renames only work within a file system and cannot be moved to another file system.
 *
 * If destination already exists, then according to rename(), destination will be atomically replaced.
 * Which, if destination is a directory, then that directory must either not exist or be empty.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which the source is relative to.
 * @param to_id
 *   The parent directory, as an open directory file descriptor, in which the destination is relative to.
 * @param source
 *   The path to the file to copy from.
 * @param destination
 *   The path to copy to.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_busy (with error bit) if file system is too busy to perform write.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_directory_descriptor (with error bit) for bad directory descriptor for at_id or to_id.
 *   F_directory_empty_not (with error bit) if the destination is a non-empty directory.
 *   F_file_found_not (with error bit) if file at path was not found.
 *   F_file_type_directory (with error bit) if destination is a directory but source is not.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_link (with error bit) if source or destination has the maxiumum associated links.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_mount (with error bit) if source and destination are not within the same mounted filesystems.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for making changes.
 *   F_read_only (with error bit) if file is read-only.
 *   F_space_not (with error bit) if file system is out of space (or file system quota is reached).
 *   F_failure (with error bit) for any other error.
 *
 * @see renameat()
 */
#ifndef _di_f_file_rename_at_
  extern f_status_t f_file_rename_at(const int at_id, const int to_id, const f_string_static_t source, const f_string_static_t destination);
#endif // _di_f_file_rename_at_

/**
 * Change owner and/or group of a given file at the specified path.
 *
 * At least one of uid or gid must not be -1.
 *
 * @param path
 *   The path file name.
 * @param uid
 *   The new user id to use.
 *   Set to -1 to not change.
 * @param gid
 *   The new group id to use.
 *   Set to -1 to not change.
 * @param dereference
 *   Set to TRUE to dereferenc symlinks (often is what is desired).
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
 */
#ifndef _di_f_file_role_change_
  extern f_status_t f_file_role_change(const f_string_static_t path, const uid_t uid, const gid_t gid, const bool dereference);
#endif // _di_f_file_role_change_

/**
 * Change owner and/or group of a given file at the specified path.
 *
 * At least one of uid or gid must not be -1.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param uid
 *   The new user id to use.
 *   Set to -1 to not change.
 * @param gid
 *   The new group id to use.
 *   Set to -1 to not change.
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
 */
#ifndef _di_f_file_role_change_at_
  extern f_status_t f_file_role_change_at(const int at_id, const f_string_static_t path, const uid_t uid, const gid_t gid, const int flag);
#endif // _di_f_file_role_change_at_

/**
 * Given an open file descriptor, seek to a given location.
 *
 * @param id
 *   The file descriptor.
 * @param whence
 *   One of: SEEK_SET, SEEK_CUR, SEEK_END, SEEK_DATA, SEEK_HOLE.
 * @param offset
 *   The offset to use, based off of whence.
 * @param seeked
 *   This gets update to represent the total amount seeked.
 *   To be compared against offset.
 *
 * @return
 *   F_none on success.
 *
 *   F_bound_not (with error bit) if SEEK_DATA or SEEK_HOLE is specified as whence and offset is beyond the end of file.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_pipe (with error bit) if file descriptor represents a pipe, socket, or FIFO.
 *   F_number_overflow (with error bit) on overflow for offset.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) on any other error.
 *
 * @see lseek
 */
#ifndef _di_f_file_seek_
  extern f_status_t f_file_seek(const int id, const int whence, const f_array_length_t offset, f_array_length_t * const seeked);
#endif // _di_f_file_seek_

/**
 * Read the size of file.
 *
 * @param path
 *   The path to the file.
 * @param dereference
 *   Set to TRUE to dereferenc symlinks (often is what is desired).
 *   Set to FALSE to operate on the symlink itself.
 * @param size
 *   This gets set to the size of the file.
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
 * @see f_file_stat()
 */
#ifndef _di_f_file_size_
  extern f_status_t f_file_size(const f_string_static_t path, const bool dereference, f_array_length_t * const size);
#endif // _di_f_file_size_

/**
 * Read the size of file.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path to the file.
 * @param dereference
 *   Set to TRUE to dereferenc symlinks (often is what is desired).
 *   Set to FALSE to operate on the symlink itself.
 * @param size
 *   This gets set to the size of the file.
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
 * @see f_file_stat_at()
 */
#ifndef _di_f_file_size_at_
  extern f_status_t f_file_size_at(const int at_id, const f_string_static_t path, const bool dereference, f_array_length_t * const size);
#endif // _di_f_file_size_at_

/**
 * Read size of a file relative to the path represented by the file descriptor id.
 *
 * @param id
 *   The file descriptor.
 * @param size
 *   This gets set to the size of the file.
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
 * @see f_file_stat_by_id()
 */
#ifndef _di_f_file_size_by_id_
  extern f_status_t f_file_size_by_id(const int id, f_array_length_t * const size);
#endif // _di_f_file_size_by_id_

/**
 * Read statistics of a file.
 *
 * @param path
 *   The path to the file.
 * @param dereference
 *   Set to TRUE to dereferenc symlinks (often is what is desired).
 *   Set to FALSE to operate on the symlink itself.
 * @param stat_file
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
 * @see stat()
 */
#ifndef _di_f_file_stat_
  extern f_status_t f_file_stat(const f_string_static_t path, const bool dereference, struct stat * const stat_file);
#endif // _di_f_file_stat_

/**
 * Read statistics of a file relative to the path represented by the file descriptor id.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path to the file.
 * @param flag
 *   Any valid flag, such as F_file_at_path_empty_d, F_file_at_automount_no_d, or F_file_at_symlink_follow_no_d.
 * @param stat_file
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
 */
#ifndef _di_f_file_stat_at_
  extern f_status_t f_file_stat_at(const int at_id, const f_string_static_t path, const int flag, struct stat * const stat_file);
#endif // _di_f_file_stat_at_

/**
 * Read statistics of a file using a file descriptor id.
 *
 * @param id
 *   The file descriptor.
 * @param stat_file
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
 */
#ifndef _di_f_file_stat_by_id_
  extern f_status_t f_file_stat_by_id(const int id, struct stat * const stat_file);
#endif // _di_f_file_stat_by_id_

/**
 * Close an open file stream.
 *
 * @param complete
 *   If TRUE, will close the file descriptor as well, setting file.id is reset to -1, on success.
 *   If FALSE, will do nothing in regards to the file descriptor.
 * @param file
 *   The file information.
 *   The file.stream is set to 0, on success.
 *
 * @return
 *   F_none is returned on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_block (with error bit) if the action would block and non-blocking is set on the stream.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_deadlock (with error bit) if operation would cause a deadlock.
 *   F_file_close (with error bit) if fclose() failed for any other reason.
 *   F_file_descriptor (with error bit) if file descriptor is invalid.
 *   F_file_descriptor_max (with error bit) if max file descriptors is reached.
 *   F_file_overflow (with error bit) if the write exceeds some implementation defined maximum file size.
 *   F_file_synchronize (with error bit) on flush failure.
 *   F_file_type_not_directory (with error bit) if F_NOTIFY was specified and file.id is not a directory.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_lock (with error bit) if failed to lock, such as lock table is full or too many open segments.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_pipe_not (with error bit) if the stream is a pipe or a socket but the pipe or socket is already closed.
 *   F_prohibited (with error bit) if file system does not allow for making changes.
 *   F_space_not (with error bit) if file system is out of space (or file system quota is reached).
 *   F_socket_not (with error bit) if the datagram socket in which a peer has not been set (for socket related streams).
 *
 * @see close()
 * @see fclose()
 */
#ifndef _di_f_file_stream_close_
  extern f_status_t f_file_stream_close(const bool complete, f_file_t * const file);
#endif // _di_f_file_stream_close_

/**
 * Open a file stream from a file descriptor.
 *
 * @param mode
 *   The file modes do use when opening.
 *   Set mode.used to 0 to determine mode from file.flags (falling back to read only as a failsafe).
 *   If neither truncate nor append are not specified in write only mode, then the failsafe is to append.
 *   This should match the modes used to open the file descriptor as it relates to the stream modes.
 * @param file
 *   The file with a valid file descriptor (file.id).
 *   THe file stream (file.stream) is updated on success, but may be set to NULL on error.
 *
 * @return
 *   F_none is returned on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_deadlock (with error bit) if operation would cause a deadlock.
 *   F_file_descriptor (with error bit) if file descriptor is invalid.
 *   F_file_descriptor_max (with error bit) if max file descriptors is reached.
 *   F_file_type_not_directory (with error bit) if F_NOTIFY was specified and file.id is not a directory.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_lock (with error bit) if failed to lock, such as lock table is full or too many open segments.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for making changes.
 *
 * @see fdopen()
 */
#ifndef _di_f_file_stream_descriptor_
  extern f_status_t f_file_stream_descriptor(const f_string_static_t mode, f_file_t * const file);
#endif // _di_f_file_stream_descriptor_

/**
 * Open a file stream.
 *
 * The file descriptor is retrieved on success, if necessary and able.
 *
 * @param path
 *   The file path
 * @param mode
 *   The file modes do use when opening, as an fopen() file mode string.
 *   Set mode.used to 0 to determine mode from file.flags (falling back to read only as a failsafe).
 *   If neither truncate nor append are not specified in write only mode, then the failsafe is to append.
 *
 *   File Modes (fopen() file modes vs open file modes):
 *     - "r":  O_RDONLY.
 *     - "w":  O_WRONLY | O_CREAT | O_TRUNC.
 *     - "a":  O_WRONLY | O_CREAT | O_APPEND.
 *     - "r+": O_RDWR.
 *     - "w+": O_RDWR | O_CREAT | O_TRUNC.
 *     - "a+": O_RDWR | O_CREAT | O_APPEND.
 * @param file
 *   The file information.
 *   The file.stream is updated if necessary.
 *   The file.id is updated with the file descriptor, if necessary and able.
 *
 * @return
 *   F_none is returned on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_busy (with error bit) if file system is too busy to perform write.
 *   F_file_descriptor (with error bit) if unable to load the file descriptor.
 *   F_file_found_not (with error bit) if the file was not found.
 *   F_file_open_max (with error bit) when system-wide max open files is reached.
 *   F_file_type_not_directory (with error bit) if F_NOTIFY was specified and file.id is not a directory.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name is too long.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for making changes.
 *   F_read_only (with error bit) if file is read-only.
 *   F_supported_not (with error bit) fo unsupported file types.
 *   F_failure (with error bit) for any other error.
 *
 * @see fileno()
 * @see fopen()
 */
#ifndef _di_f_file_stream_open_
  extern f_status_t f_file_stream_open(const f_string_static_t path, const f_string_static_t mode, f_file_t * const file);
#endif // _di_f_file_stream_open_

/**
 * Read until EOF is reached.
 *
 * To check how much was read into the buffer, record buffer->used before execution and compare to buffer->used after execution.
 *
 * @param file
 *   The file to read.
 *   The file must already be open.
 *   The file.size_read represents the amount to process at a given time.
 * @param buffer
 *   The buffer the file is being read into.
 *   The contents of the file is appended into this buffer.
 *
 * @return
 *   F_none_eof on success and EOF was reached.
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the read would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see flockfile()
 * @see fread_unlocked()
 * @see funlockfile()
 */
#ifndef _di_f_file_stream_read_
  extern f_status_t f_file_stream_read(const f_file_t file, f_string_dynamic_t * const buffer);
#endif // _di_f_file_stream_read_

/**
 * Read until a single block is filled or EOF is reached.
 *
 * To determine how much was read into the buffer, record buffer->used before execution and compare to buffer->used after execution.
 *
 * @param file
 *   The file to read.
 *   The file must already be open.
 *   The file.size_read represents the amount to process at a given time.
 * @param buffer
 *   The buffer the file is being read into.
 *   The contents of the file is appended into this buffer.
 *
 * @return
 *   F_none on success.
 *   F_none_eof on success and EOF was reached.
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the read would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fread()
 */
#ifndef _di_f_file_stream_read_block_
  extern f_status_t f_file_stream_read_block(const f_file_t file, f_string_dynamic_t * const buffer);
#endif // _di_f_file_stream_read_block_

/**
 * Read until a given number or EOF is reached, storing it in the buffer.
 *
 * To check how much was read into the buffer, record buffer->used before execution and compare to buffer->used after execution.
 *
 * This is different from simply using the file.size_read.
 * The file.size_read represents the amount to process at a given time.
 * The total represents the maximum number of file.size_read to process.
 * For example, if file.size_read is 16 and total is 128, then this function would need to be called 8 times until total is reached.
 *
 * @param file
 *   The file to read.
 *   The file must already be open.
 *   The file.size_read represents the amount to process at a given time.
 * @param total
 *   The total bytes to read, unless EOF is reached first.
 * @param buffer
 *   The buffer the file is being read into.
 *
 * @return
 *   F_none_eof on success and EOF was reached.
 *   F_none_stop on success and total was reached.
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the read would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_increase_by().
 *
 * @see flockfile()
 * @see fread_unlocked()
 * @see funlockfile()
 *
 * @see f_string_dynamic_increase_by()
 */
#ifndef _di_f_file_stream_read_until_
  extern f_status_t f_file_stream_read_until(const f_file_t file, const f_array_length_t total, f_string_dynamic_t * const buffer);
#endif // _di_f_file_stream_read_until_

/**
 * Re-open a file stream.
 *
 * This allows for re-using an existing file stream and possibly file-descriptor.
 *
 * The file descriptor is retrieved on success, if necessary and able.
 *
 * @param path
 *   The file path
 * @param mode
 *   The file modes do use when opening.
 *   Set to 0 to determine mode from file.flags (falling back to read only as a failsafe).
 *   If neither truncate nor append are not specified in write only mode, then the failsafe is to append.
 * @param file
 *   The file information.
 *   The file.stream is updated, if necessary.
 *   The file.id is updated with the file descriptor, if necessary and able.
 *
 * @return
 *   F_none is returned on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_busy (with error bit) if file system is too busy to perform write.
 *   F_file_descriptor (with error bit) if unable to load the file descriptor.
 *   F_file_found_not (with error bit) if the file was not found.
 *   F_file_open_max (with error bit) when system-wide max open files is reached.
 *   F_file_type_not_directory (with error bit) if F_NOTIFY was specified and file.id is not a directory.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name is too long.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for making changes.
 *   F_read_only (with error bit) if file is read-only.
 *   F_supported_not (with error bit) fo unsupported file types.
 *   F_failure (with error bit) for any other error.
 *
 * @see fileno()
 * @see freopen()
 */
#ifndef _di_f_file_stream_reopen_
  extern f_status_t f_file_stream_reopen(const f_string_static_t path, const f_string_static_t mode, f_file_t * const file);
#endif // _di_f_file_stream_reopen_

/**
 * Write until entire buffer is written.
 *
 * @param file
 *   The file to write to.
 *   The file must already be open.
 *   The file.size_write represents the amount to process at a given time.
 * @param buffer
 *   The buffer to write to the file.
 * @param written
 *   The total bytes written.
 *   Set pointer to 0 to not use.
 *
 * @return
 *   F_none on success.
 *   F_none_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite()
 */
#ifndef _di_f_file_stream_write_
  extern f_status_t f_file_stream_write(const f_file_t file, const f_string_static_t buffer, f_array_length_t * const written);
#endif // _di_f_file_stream_write_

/**
 * Write until a single block is filled or entire buffer is written.
 *
 * To check how much was write into the buffer, record buffer->used before execution and compare to buffer->used after execution.
 *
 * @param file
 *   The file to write to.
 *   The file must already be open.
 *   The file.size_write represents the amount to process at a given time.
 * @param buffer
 *   The buffer to write to the file.
 * @param written
 *   The total bytes written.
 *   Set pointer to 0 to not use.
 *
 * @return
 *   F_none on success.
 *   F_none_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite()
 */
#ifndef _di_f_file_stream_write_block_
  extern f_status_t f_file_stream_write_block(const f_file_t file, const f_string_static_t buffer, f_array_length_t * const written);
#endif // _di_f_file_stream_write_block_

/**
 * Write until a given number or entire buffer is written.
 *
 * @param file
 *   The file to write to.
 *   The file must already be open.
 *   The file.size_write represents the amount to process at a given time.
 * @param buffer
 *   The buffer to write to the file.
 * @param total
 *   The total bytes to write, unless end of buffer is reached first.
 * @param written
 *   The total bytes written.
 *   Set pointer to 0 to not use.
 *
 * @return
 *   F_none on success.
 *   F_none_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *   F_none_eos on success but range.stop exceeded buffer.used (only wrote up to buffer.used).
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite()
 */
#ifndef _di_f_file_stream_write_until_
  extern f_status_t f_file_stream_write_until(const f_file_t file, const f_string_static_t buffer, const f_array_length_t total, f_array_length_t * const written);
#endif // _di_f_file_stream_write_until_

/**
 * Write a given range within the buffer.
 *
 * @param file
 *   The file to write to.
 *   The file must already be open.
 *   The file.size_write represents the amount to process at a given time.
 * @param buffer
 *   The buffer to write to the file.
 * @param range
 *   An inclusive start an stop range within the buffer to read.
 * @param written
 *   The total bytes written.
 *   Set pointer to 0 to not use.
 *
 * @return
 *   F_none on success.
 *   F_none_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *   F_none_eos on success but range.stop exceeded buffer.used (only wrote up to buffer.used).
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fwrite()
 */
#ifndef _di_f_file_stream_write_range_
  extern f_status_t f_file_stream_write_range(const f_file_t file, const f_string_static_t buffer, const f_string_range_t range, f_array_length_t * const written);
#endif // _di_f_file_stream_write_range_


/**
 * Update the files access and modification timestamp, creating the file if it does not already exist.
 *
 * When the file is created, it is created as a regular file.
 *
 * @param path
 *   The path file name.
 * @param mode
 *   The file mode to use when (regular) file is created.
 * @param dereference
 *   Set to TRUE to dereference symlinks (often is what is desired).
 *   Set to FALSE to operate on the symlink itself.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_busy (with error bit) if file system is too busy to perform write.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_directory_descriptor (with error bit) for bad directory descriptor for at_id.
 *   F_file_found (with error bit) if a file aleady exists at the path.
 *   F_file_open_max (with error bit) when system-wide max open files is reached.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_filesystem_quota_reached (with error bit) quota reached of file system is out of space.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for creating or linking.
 *   F_read_only (with error bit) if file system is read-only.
 *   F_search (with error bit) if search permission is denied for one of the paths to the file.
 *   F_failure (with error bit) for any other error.
 *
 * @see utimensat()
 */
#ifndef _di_f_file_touch_
  extern f_status_t f_file_touch(const f_string_static_t path, const mode_t mode, const bool dereference);
#endif // _di_f_file_touch_

/**
 * Update the files access and modification timestamp, creating the file if it does not already exist.
 *
 * When the file is created, it is created as a regular file.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param mode
 *   The file mode to use when (regular) file is created.
 * @param flag
 *   Any valid flag, such as F_file_at_path_empty_d, F_file_at_automount_no_d, or F_file_at_symlink_follow_no_d.
 *
 * @return
 *   F_none on success.
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *
 *   F_busy (with error bit) if file system is too busy to perform write.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_directory_descriptor (with error bit) for bad directory descriptor for at_id.
 *   F_file_found (with error bit) if a file aleady exists at the path (when calling utimensat()).
 *   F_file_open_max (with error bit) when system-wide max open files is reached.
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_filesystem_quota_reached (with error bit) quota reached of file system is out of space.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for creating or linking.
 *   F_read_only (with error bit) if file system is read-only.
 *   F_search (with error bit) if search permission is denied for one of the paths to the file.
 *   F_failure (with error bit) for any other error.
 *
 * @see utimensat()
 */
#ifndef _di_f_file_touch_at_
  extern f_status_t f_file_touch_at(const int at_id, const f_string_static_t path, const mode_t mode, const int flag);
#endif // _di_f_file_touch_at_

/**
 * Get the file type for the file at the given path.
 *
 * This does not require access on the file itself.
 * This only requires access via the parent directories in the path.
 *
 * @param path
 *   The path file name.
 * @param type
 *   The type of the file.
 *
 * @return
 *   F_none if path was found and and the type was loaded in the type parameter.
 *   F_file_found_not if the path was not found.
 *
 *   F_access_denied (with error bit) if access to the file was denied.
 *   F_directory (with error bit) on invalid directory.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see stat()
 */
#ifndef _di_f_file_type_
  extern f_status_t f_file_type(const f_string_static_t path, int * const type);
#endif //  _di_f_file_type_

/**
 * Get the file type for the file at the given path within the parent directory.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param flag
 *   Any valid flag, such as F_file_at_path_empty_d, F_file_at_automount_no_d, or F_file_at_symlink_follow_no_d.
 * @param type
 *   The type of the file.
 *
 * @return
 *   F_none if path was found and and the type was loaded in the type parameter.
 *   F_file_found_not if the path was not found.
 *
 *   F_access_denied (with error bit) if access to the file was denied.
 *   F_directory (with error bit) on invalid directory.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fstatat()
 */
#ifndef _di_f_file_type_at_
  extern f_status_t f_file_type_at(const int at_id, const f_string_static_t path, const int flag, int * const type);
#endif // _di_f_file_type_at_

/**
 * Get the umask.
 *
 * This sets the umask after getting the umask.
 * This is necessary because the umask() is poorly designed such that it requires changing the umask to get the current umask.
 *
 * @param mask
 *   The umask value.
 *   (The name "mask" is used avoid a naming conflict with the umask() function.)
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_f_file_umask_get_
  extern f_status_t f_file_umask_get(mode_t * const mask);
#endif // _di_f_file_umask_get_

/**
 * Set the umask.
 *
 * @param mask
 *   The umask value to assigned.
 *   (The name "mask" is used avoid a naming conflict with the umask() function.)
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_f_file_umask_set_
  extern f_status_t f_file_umask_set(const mode_t mask);
#endif // _di_f_file_umask_set_

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
 *   Set pointer to 0 to not use.
 *
 * @return
 *   F_none on success.
 *   F_none_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *   F_data_not if buffer.used is 0.
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_file_write_
  extern f_status_t f_file_write(const f_file_t file, const f_string_static_t buffer, f_array_length_t * const written);
#endif // _di_f_file_write_

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
 *   Set pointer to 0 to not use.
 *
 * @return
 *   F_none on success.
 *   F_none_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *   F_data_not if buffer.used is 0.
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_file_write_block_
  extern f_status_t f_file_write_block(const f_file_t file, const f_string_static_t buffer, f_array_length_t * const written);
#endif // _di_f_file_write_block_

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
 *   Set pointer to 0 to not use.
 *
 * @return
 *   F_none on success.
 *   F_none_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *   F_none_eos on success but range.stop exceeded buffer.used (only wrote up to buffer.used).
 *   F_data_not if buffer.used is 0 or total is 0.
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_closed (with error bit) if file is not open.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_file_write_until_
  extern f_status_t f_file_write_until(const f_file_t file, const f_string_static_t buffer, const f_array_length_t total, f_array_length_t * const written);
#endif // _di_f_file_write_until_

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
 *   Set pointer to 0 to not use.
 *
 * @return
 *   F_none on success.
 *   F_none_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *   F_none_eos on success but range.stop exceeded buffer.used (only wrote up to buffer.used).
 *   F_data_not if buffer.used is 0 or range.start > range.stop.
 *
 *   F_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_file_descriptor (with error bit) if the file descriptor is invalid.
 *   F_file_type_directory (with error bit) if file descriptor represents a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see write()
 */
#ifndef _di_f_file_write_range_
  extern f_status_t f_file_write_range(const f_file_t file, const f_string_static_t buffer, const f_string_range_t range, f_array_length_t * const written);
#endif // _di_f_file_write_range_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_file_h
