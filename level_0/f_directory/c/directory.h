/**
 * FLL - Level 0
 *
 * Project: Directory
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides operations for directory handling.
 */
#ifndef _F_directory_h
#define _F_directory_h

// libc includes
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// work-around for out-dated systems.
#ifndef __USE_XOPEN_EXTENDED
  #define __USE_XOPEN_EXTENDED
  #include <ftw.h>
  #undef __USE_XOPEN_EXTENDED
#else
  #include <ftw.h>
#endif // __USE_XOPEN_EXTENDED

// fll-0 includes
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/directory_type.h>

// fll-0 directory includes
#include <fll/level_0/directory-common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create a directory at the given path.
 *
 * @param path
 *   The file path to the directory.
 * @param mode
 *   The directory mode to use when creating.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_directory_link_max (with error bit) max links limit reached or exceeded.
 *   F_file_found (with error bit) of a directory aleady exists at the path.
 *   F_file_found_not (with error bit) if a file within the path is not found (such as a broken symbolic link).
 *   F_filesystem_quota_block (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if filesystem does not allow for removing.
 *   F_read_only (with error bit) if file is read-only.
 *   F_space_not (with error bit) if filesystem is out of space (or filesystem quota is reached).
 *   F_failure (with error bit) for any other error.
 *
 * @see mkdir()
 */
#ifndef _di_f_directory_create_
  extern f_status_t f_directory_create(const f_string_t path, const mode_t mode);
#endif // _di_f_directory_create_

/**
 * Create a directory at the given path within the directories specified by the file descriptor.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The file path to the directory.
 * @param mode
 *   The directory mode to use when creating.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_directory_descriptor (with error bit) for bad directory descriptor for at_id.
 *   F_directory_link_max (with error bit) max links limit reached or exceeded.
 *   F_file_found (with error bit) of a directory aleady exists at the path.
 *   F_file_found_not (with error bit) if a file within the path is not found (such as a broken symbolic link).
 *   F_filesystem_quota_block (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if filesystem does not allow for removing.
 *   F_read_only (with error bit) if file is read-only.
 *   F_space_not (with error bit) if filesystem is out of space (or filesystem quota is reached).
 *   F_failure (with error bit) for any other error.
 *
 * @see mkdirat()
 */
#ifndef _di_f_directory_create_at_
  extern f_status_t f_directory_create_at(const int at_id, const f_string_t path, const mode_t mode);
#endif // _di_f_directory_create_at_

/**
 * Identify whether or not a file exists at the given path and if that file is a directory or a symlink to a directory.
 *
 * @param path
 *   The file path to the directory.
 *
 * @return
 *   F_true if path was found and path is a directory (or a symlink to a directory).
 *   F_false if path was found and path is not a directory.
 *   F_file_found_not if the path was not found.
 *
 *   F_access_denied (with error bit) if access to the file was denied.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see stat()
 */
#ifndef _di_f_directory_exists_
  extern f_status_t f_directory_exists(const f_string_t path);
#endif // _di_f_directory_exists_

/**
 * Identify whether or not a file exists at the given path and if that file is a directory or a symlink to a directory.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The file path to the directory.
 * @param flag
 *   Any valid flag, such as f_directory_at_path_empty, f_directory_at_automount_no, or f_directory_at_symlink_follow_no.
 *
 * @return
 *   F_true if path was found and path is a directory (or a symlink to a directory).
 *   F_false if path was found and path is not a directory.
 *   F_file_found_not if the path was not found.
 *
 *   F_access_denied (with error bit) if access to the file was denied.
 *   F_directory_descriptor (with error bit) for bad directory descriptor for at_id.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fstatat()
 */
#ifndef _di_f_directory_exists_at_
  extern f_status_t f_directory_exists_at(const int at_id, const f_string_t path, const int flag);
#endif // _di_f_directory_exists_at_

/**
 * Identify whether or not a file exists at the given path and if that file is a directory.
 *
 * @param path
 *   The file path to the directory.
 *
 * @return
 *   F_true if path was found and path is a directory.
 *   F_false if path was found and path is not a directory (this includes symlinks).
 *   F_file_found_not if the path was not found.
 *
 *   F_access_denied (with error bit) if access to the file was denied.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see stat()
 */
#ifndef _di_f_directory_is_
  extern f_status_t f_directory_is(const f_string_t path);
#endif // _di_f_directory_is_

/**
 * Identify whether or not a file exists at the given path within the parent directory and if that file is a directory.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The file path to the directory.
 * @param flag
 *   Any valid flag, such as f_directory_at_path_empty, f_directory_at_automount_no, or f_directory_at_symlink_follow_no.
 *
 * @return
 *   F_true if path was found and path is a directory.
 *   F_false if path was found and path is not a directory.
 *   F_file_found_not if the path was not found.
 *
 *   F_access_denied (with error bit) if access to the file was denied.
 *   F_directory_descriptor (with error bit) for bad directory descriptor for at_id.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fstatat()
 */
#ifndef _di_f_directory_is_at_
  extern f_status_t f_directory_is_at(const int at_id, const f_string_t path, const int flag);
#endif // _di_f_directory_is_at_

/**
 * For some given path, print the names of each file and/or directory inside the directory.
 *
 * Allows specifying a custom filter and custom sort.
 *
 * @param path
 *   The file path to the directory.
 * @param filter
 *   A filter function of the form: int xxx(const struct direct *).
 *   Set to 0 to not use (NULL).
 * @param sort
 *   A sort function of the form: int xxx(const struct direct *, const struct direct *).
 *   Set to 0 to not use (NULL).
 *   There are two pre-made libc functions available for this: alphasort() and versionsort().
 * @param names
 *   Will be populated with the names of each file and/or directory inside path.
 *
 * @return
 *   F_none on success.
 *   F_data_not if directory is empty.
 *
 *   F_array_too_large (with error bit) if the directory buffer max length would be exceeded.
 *   F_failure (with error bit) if failed to read directory information.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see alphasort()
 * @see scandir()
 * @see versionsort()
 */
#ifndef _di_f_directory_list_
  extern f_status_t f_directory_list(const f_string_t path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), f_string_dynamics_t *names);
#endif // _di_f_directory_list_

/**
 * Open the directory specified by path.
 *
 * This opens with O_PATH and O_CLOEXEC.
 *
 * @param path
 *   The file path to the directory.
 * @param dereference
 *   Set to TRUE to dereferenc symlinks (often is what is desired).
 *   Set to FALSE to operate on the symlink itself.
 * @param id
 *   The file descriptor.
 *   This is updated with the result of open() or openat().
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_directory_found_not (with error bit) if directory was not found.
 *   F_failure (with error bit) if failed to read directory information.
 *   F_file_open_max (with error bit) too many open files.
 *   F_file_type_directory_not (with error bit) file is not a directory.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if filesystem does not allow for removing.
 *   F_read_only (with error bit) if file is read-only.
 *   F_space_not (with error bit) if filesystem is out of space (or filesystem quota is reached).
 *
 * @see open()
 */
#ifndef _di_f_directory_open_
  extern f_status_t f_directory_open(const f_string_t path, const bool dereference, int *id);
#endif // _di_f_directory_open_

/**
 * Open the directory specified by path.
 *
 * This opens with O_PATH and O_CLOEXEC.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The file path to the directory.
 * @param dereference
 *   Set to TRUE to dereferenc symlinks (often is what is desired).
 *   Set to FALSE to operate on the symlink itself.
 * @param id
 *   The file descriptor.
 *   This is updated with the result of open() or openat().
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_directory_found_not (with error bit) if directory was not found.
 *   F_directory_descriptor (with error bit) for bad directory descriptor for at_id.
 *   F_failure (with error bit) if failed to read directory information.
 *   F_file_open_max (with error bit) too many open files.
 *   F_file_type_directory_not (with error bit) file is not a directory.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if filesystem does not allow for removing.
 *   F_read_only (with error bit) if file is read-only.
 *   F_space_not (with error bit) if filesystem is out of space (or filesystem quota is reached).
 *
 * @see openat()
 */
#ifndef _di_f_directory_open_at_
  extern f_status_t f_directory_open_at(const int at_id, const f_string_t path, const bool dereference, int *id);
#endif // _di_f_directory_open_at_

/**
 * Remove a directory and possibly its contents.
 *
 * @param path
 *   The file path to the directory.
 * @param depth_max
 *   Represents the max recursion depth, set to 0 to disable recursive delete.
 * @param preserve
 *   When depth_max > 0, this designates whether or not to preserve the directory at path.
 *   If TRUE, then only the content within the directory is deleted.
 *   If FALSE, then the directory at path and its content are deleted.
 *   When depth_max is 0, then this should only be FALSE (setting this to TRUE would be a no-op).
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_busy (with error bit) if file is busy.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_directory_empty_not (with error bit) if the directory is not empty.
 *   F_file_descriptor_max (with error bit) if max file descriptors was reached.
 *   F_file_found_not (with error bit) if file not found.
 *   F_file_open_max (with error bit) too many open files.
 *   F_file_type_directory (with error bit) file is a directory (directories cannot be removed via this function).
 *   F_input_output (with error bit) if an I/O error occurred.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if filesystem does not allow for removing.
 *   F_read_only (with error bit) if file is read-only.
 *   F_failure (with error bit) for any other error.
 *
 * @see nftw()
 * @see remove()
 */
#ifndef _di_f_directory_remove_
  extern f_status_t f_directory_remove(const f_string_t path, const int depth_max, const bool preserve);
#endif // _di_f_directory_remove_

/**
 * Remove a directory and possibly its contents.
 *
 * @param path
 *   The file path to the directory.
 * @param depth_max
 *   Represents the max recursion depth, set to 0 to disable recursive delete.
 * @param preserve
 *   When depth_max > 0, this designates whether or not to preserve the directory at path.
 *   If TRUE, then only the content within the directory is deleted.
 *   If FALSE, then the directory at path and its content are deleted.
 *   When depth_max is 0, then this should only be FALSE (setting this to TRUE would be a no-op).
 * @param custom
 *   A custom function to pass to nftw() instead of using the internal one.
 *   Such as a custom function for verbose printing of removed files.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_busy (with error bit) if file is busy.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_directory_empty_not (with error bit) if the directory is not empty.
 *   F_file_descriptor_max (with error bit) if max file descriptors was reached.
 *   F_file_found_not (with error bit) if file not found.
 *   F_file_open_max (with error bit) too many open files.
 *   F_file_type_directory (with error bit) file is a directory (directories cannot be removed via this function).
 *   F_input_output (with error bit) if an I/O error occurred.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if filesystem does not allow for removing.
 *   F_read_only (with error bit) if file is read-only.
 *   F_failure (with error bit) for any other error.
 *
 * @see nftw()
 * @see remove()
 */
#ifndef _di_f_directory_remove_custom_
  extern f_status_t f_directory_remove_custom(const f_string_t path, const int depth_max, const bool preserve, int (*custom) (const char *, const struct stat *, int, struct FTW *));
#endif // _di_f_directory_remove_custom_

/**
 * Update the files access and modification timestamp, creating the directory if it does not already exist.
 *
 * When the file is created, it is created as a directory file.
 *
 * @param path
 *   The path file name.
 * @param mode
 *   The file mode to use when (directory) file is created.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_busy (with error bit) if filesystem is too busy to perform write.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_directory_descriptor (with error bit) for bad directory descriptor for at_id.
 *   F_file_found (with error bit) if a file aleady exists at the path.
 *   F_file_open_max (with error bit) when system-wide max open files is reached.
 *   F_filesystem_quota_block (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   F_filesystem_quota_reached (with error bit) quota reached of filesystem is out of space.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if filesystem does not allow for creating or linking.
 *   F_read_only (with error bit) if filesystem is read-only.
 *   F_search (with error bit) if search permission is denied for one of the paths to the file.
 *   F_failure (with error bit) for any other error.
 *
 * @see utimensat()
 */
#ifndef _di_f_directory_touch_
  extern f_status_t f_directory_touch(const f_string_t path, const mode_t mode);
#endif // _di_f_directory_touch_

/**
 * Update the files access and modification timestamp, creating the file if it does not already exist.
 *
 * When the file is created, it is created as a directory file.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param mode
 *   The file mode to use when (directory) file is created.
 * @param flag
 *   Any valid flag, such as f_file_at_path_empty, f_file_at_automount_no, or f_file_at_symlink_follow_no.
 *
 * @return
 *   F_none on success.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_busy (with error bit) if filesystem is too busy to perform write.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_directory_descriptor (with error bit) for bad directory descriptor for at_id.
 *   F_file_found (with error bit) if a file aleady exists at the path (when calling utimensat()).
 *   F_file_open_max (with error bit) when system-wide max open files is reached.
 *   F_filesystem_quota_block (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   F_filesystem_quota_reached (with error bit) quota reached of filesystem is out of space.
 *   F_interrupt (with error bit) when program received an interrupt signal, halting operation.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if filesystem does not allow for creating or linking.
 *   F_read_only (with error bit) if filesystem is read-only.
 *   F_search (with error bit) if search permission is denied for one of the paths to the file.
 *   F_failure (with error bit) for any other error.
 *
 * @see utimensat()
 */
#ifndef _di_f_directory_touch_at_
  extern f_status_t f_directory_touch_at(const int at_id, const f_string_t path, const mode_t mode, const int flag);
#endif // _di_f_directory_touch_at_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_directory_h
