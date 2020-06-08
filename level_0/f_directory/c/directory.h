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
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/type.h>
#include <level_0/directory_type.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Directory AT_* define related functionality.
 */
#ifndef _di_f_directory_at_
  #define f_directory_at_current_working    -100
  #define f_directory_at_symlink_follow     0x400
  #define f_directory_at_symlink_follow_no  0x100
  #define f_directory_at_remove_directory   0x200
  #define f_directory_at_automount_no       0x800
  #define f_directory_at_path_empty         0x1000
  #define f_directory_at_statx_sync_type    0x6000
  #define f_directory_at_statx_sync_as_stat 0x0000
  #define f_directory_at_statx_sync_force   0x2000
  #define f_directory_at_statx_sync_no      0x4000
#endif // _di_f_directory_at_

/**
 * Directory flag related functionality.
 */
#ifndef _di_f_directory_flag_

  // directory open flags
  #define f_directory_flag_append             O_APPEND
  #define f_directory_flag_asynchronous       O_ASYNC
  #define f_directory_flag_create             O_CREAT
  #define f_directory_flag_close_execute      O_CLOEXEC
  #define f_directory_flag_direct             O_DIRECT
  #define f_directory_flag_directory          O_DIRECTORY
  #define f_directory_flag_exclusive          O_EXCL
  #define f_directory_flag_large_file         O_LARGEFILE
  #define f_directory_flag_no_access_time     O_NOATIME
  #define f_directory_flag_no_follow          O_NOFOLLOW
  #define f_directory_flag_no_tty             O_NOCTTY
  #define f_directory_flag_non_blocking       O_NONBLOCK
  #define f_directory_flag_path               010000000
  #define f_directory_flag_read_only          O_RDONLY
  #define f_directory_flag_read_write         O_RDWR
  #define f_directory_flag_synchronous        O_SYNC
  #define f_directory_flag_synchronous_direct O_DSYNC
  #define f_directory_flag_temporary          O_TMPFILE
  #define f_directory_flag_truncate           O_TRUNC
  #define f_directory_flag_write_only         O_WRONLY
#endif // _di_f_directory_flag_

/**
 * Provide limitations and related defines.
 *
 * The directory max descriptors is more of a default than a rule.
 * This is generally used for nftw() recursive operations to reduce the number of open file descriptors during recursion.
 */
#ifndef _di_f_directory_limitations_
  #define f_directory_default_allocation_step f_memory_default_allocation_step

  #define f_directory_name_max        NAME_MAX
  #define f_directory_descriptors_max 255
#endif // _di_f_directory_limitations_

/**
 * Create a directory at the given path.
 *
 * @param path
 *   The path file name.
 * @param mode
 *   The directory mode to use when creating.
 *
 * @return
 *   F_none on success.
 *   F_access_denied (with error bit) on access denied.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_directory_link_max (with error bit) max links limit reached or exceeded.
 *   F_file_found (with error bit) of a directory aleady exists at the path.
 *   F_file_found_not (with error bit) if a file within the path is not found (such as a broken symbolic link).
 *   F_filesystem_quota_block (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   F_loop (with error bit) on loop error.
 *   F_memory_out (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if filesystem does not allow for removing.
 *   F_read_only (with error bit) if file is read-only.
 *   F_space_not (with error bit) if filesystem is out of space (or filesystem quota is reached).
 *   F_failure (with error bit) for any other (mkdir()) error.
 *
 * @see mkdir()
 */
#ifndef _di_f_directory_create_
  extern f_return_status f_directory_create(const f_string path, const mode_t mode);
#endif // _di_f_directory_create_

/**
 * Create a directory at the given path within the directories specified by the file descriptor.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param mode
 *   The directory mode to use when creating.
 *
 * @return
 *   F_none on success.
 *   F_access_denied (with error bit) on access denied.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_directory_descriptor (with error bit) for bad directory descriptor for at_id.
 *   F_directory_link_max (with error bit) max links limit reached or exceeded.
 *   F_file_found (with error bit) of a directory aleady exists at the path.
 *   F_file_found_not (with error bit) if a file within the path is not found (such as a broken symbolic link).
 *   F_filesystem_quota_block (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   F_loop (with error bit) on loop error.
 *   F_memory_out (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if filesystem does not allow for removing.
 *   F_read_only (with error bit) if file is read-only.
 *   F_space_not (with error bit) if filesystem is out of space (or filesystem quota is reached).
 *   F_failure (with error bit) for any other (mkdirat()) error.
 *
 * @see mkdirat()
 */
#ifndef _di_f_directory_create_at_
  extern f_return_status f_directory_create_at(const int at_id, const f_string path, const mode_t mode);
#endif // _di_f_directory_create_at_

/**
 * Identify whether or not a file exists at the given path and if that file is a directory or a symlink to a directory.
 *
 * @param path
 *   The path file name.
 *
 * @return
 *   F_false if path was found and path is not a directory.
 *   F_file_found_not if the path was not found.
 *   F_true if path was found and path is a directory (or a symlink to a directory).
 *   F_access_denied (with error bit) if access to the file was denied.
 *   F_loop (with error bit) if a loop occurred.
 *   F_memory_out (with error bit) if out of memory.
 *   F_name (with error bit) if the name is somehow invalid.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see stat()
 */
#ifndef _di_f_directory_exists_
  extern f_return_status f_directory_exists(const f_string path);
#endif // _di_f_directory_exists_

/**
 * Identify whether or not a file exists at the given path and if that file is a directory or a symlink to a directory.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param flag
 *   Any valid flag, such as f_directory_at_path_empty, f_directory_at_automount_no, or f_directory_at_symlink_follow_no.
 *
 * @return
 *   F_false if path was found and path is not a directory.
 *   F_file_found_not if the path was not found.
 *   F_true if path was found and path is a directory (or a symlink to a directory).
 *   F_access_denied (with error bit) if access to the file was denied.
 *   F_directory_descriptor (with error bit) for bad directory descriptor for at_id.
 *   F_loop (with error bit) if a loop occurred.
 *   F_memory_out (with error bit) if out of memory.
 *   F_name (with error bit) if the name is somehow invalid.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fstatat()
 */
#ifndef _di_f_directory_exists_at_
  extern f_return_status f_directory_exists_at(const int at_id, const f_string path, const int flag);
#endif // _di_f_directory_exists_at_

/**
 * Identify whether or not a file exists at the given path and if that file is a directory.
 *
 * @param path
 *   The path file name.
 *
 * @return
 *   F_false if path was found and path is not a directory (this includes symlinks).
 *   F_file_found_not if the path was not found.
 *   F_true if path was found and path is a directory.
 *   F_access_denied (with error bit) if access to the file was denied.
 *   F_loop (with error bit) if a loop occurred.
 *   F_memory_out (with error bit) if out of memory.
 *   F_name (with error bit) if the name is somehow invalid.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see stat()
 */
#ifndef _di_f_directory_is_
  extern f_return_status f_directory_is(const f_string path);
#endif // _di_f_directory_is_

/**
 * Identify whether or not a file exists at the given path within the parent directory and if that file is a directory.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param flag
 *   Any valid flag, such as f_directory_at_path_empty, f_directory_at_automount_no, or f_directory_at_symlink_follow_no.
 *
 * @return
 *   F_false if path was found and path is not a directory.
 *   F_file_found_not if the path was not found.
 *   F_true if path was found and path is a directory.
 *   F_access_denied (with error bit) if access to the file was denied.
 *   F_directory_descriptor (with error bit) for bad directory descriptor for at_id.
 *   F_loop (with error bit) if a loop occurred.
 *   F_memory_out (with error bit) if out of memory.
 *   F_name (with error bit) if the name is somehow invalid.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fstatat()
 */
#ifndef _di_f_directory_is_at_
  extern f_return_status f_directory_is_at(const int at_id, const f_string path, const int flag);
#endif // _di_f_directory_is_at_

/**
 * For some given path, print the names of each file and/or directory inside the directory.
 *
 * Allows specifying a custom filter and custom sort.
 *
 * @param path
 *   Filesystem path to the directory.
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
 *   F_failure (with error bit) if failed to read directory information.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see alphasort()
 * @see scandir()
 * @see versionsort()
 */
#ifndef _di_f_directory_list_
  extern f_return_status f_directory_list(const f_string path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), f_string_dynamics *names);
#endif // _di_f_directory_list_

/**
 * Open the directory specified by path.
 *
 * This opens with O_PATH and O_CLOEXEC.
 *
 * @param path
 *   The path file name.
 * @param dereference
 *   Set to TRUE to dereferenc symlinks (often is what is desired).
 *   Set to FALSE to operate on the symlink itself.
 * @param id
 *   The file descriptor.
 *   This is updated with the result of open() or openat().
 *
 * @return
 *   F_none on success.
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_directory_found_not (with error bit) if directory was not found.
 *   F_failure (with error bit) if failed to read directory information.
 *   F_file_open_max (with error bit) too many open files.
 *   F_file_type_directory_not (with error bit) file is not a directory.
 *   F_interrupted (with error bit) when program received an interrupt signal, halting operation.
 *   F_loop (with error bit) on loop error.
 *   F_memory_out (with error bit) if out of memory.
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
  extern f_return_status f_directory_open(const f_string path, const bool dereference, int *id) f_gcc_attribute_visibility_internal;
#endif // _di_f_directory_open_

/**
 * Open the directory specified by path.
 *
 * This opens with O_PATH and O_CLOEXEC.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param dereference
 *   Set to TRUE to dereferenc symlinks (often is what is desired).
 *   Set to FALSE to operate on the symlink itself.
 * @param id
 *   The file descriptor.
 *   This is updated with the result of open() or openat().
 *
 * @return
 *   F_none on success.
 *   F_access_denied (with error bit) on access denied.
 *   F_buffer (with error bit) if the buffer is invalid.
 *   F_directory_found_not (with error bit) if directory was not found.
 *   F_directory_descriptor (with error bit) for bad directory descriptor for at_id.
 *   F_failure (with error bit) if failed to read directory information.
 *   F_file_open_max (with error bit) too many open files.
 *   F_file_type_directory_not (with error bit) file is not a directory.
 *   F_interrupted (with error bit) when program received an interrupt signal, halting operation.
 *   F_loop (with error bit) on loop error.
 *   F_memory_out (with error bit) if out of memory.
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
  extern f_return_status f_directory_open_at(const int at_id, const f_string path, const bool dereference, int *id) f_gcc_attribute_visibility_internal;
#endif // _di_f_directory_open_at_

/**
 * Remove a directory and possibly its contents.
 *
 * @param path
 *   The path file name.
 * @param recursion_max
 *   Represents the max recursion depth, set to 0 to disable recursive delete.
 * @param preserve
 *   When recursion_max > 0, this designates whether or not to preserve the directory at path.
 *   If TRUE, then only the content within the directory is deleted.
 *   If FALSE, then the directory at path and its content are deleted.
 *   When recursion_max is 0, then this should only be FALSE (setting this to TRUE would be a no-op).
 *
 * @return
 *   F_none on success.
 *   F_access_denied (with error bit) on access denied.
 *   F_busy (with error bit) if file is busy.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_file_descriptor_max (with error bit) if max file descriptors was reached.
 *   F_file_found_not (with error bit) if file not found.
 *   F_file_open_max (with error bit) too many open files.
 *   F_file_type_directory (with error bit) file is a directory (directories cannot be removed via this function).
 *   F_input_output (with error bit) if an I/O error occurred.
 *   F_loop (with error bit) on loop error.
 *   F_memory_out (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if filesystem does not allow for removing.
 *   F_read_only (with error bit) if file is read-only.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_failure (with error bit) for any other (remove()) error.
 *
 * @see nftw()
 * @see remove()
 */
#ifndef _di_f_directory_remove_
  extern f_return_status f_directory_remove(const f_string path, const int recursion_max, const bool preserve);
#endif // _di_f_directory_remove_

/**
 * Remove a directory and possibly its contents.
 *
 * @param path
 *   The path file name.
 * @param recursion_max
 *   Represents the max recursion depth, set to 0 to disable recursive delete.
 * @param preserve
 *   When recursion_max > 0, this designates whether or not to preserve the directory at path.
 *   If TRUE, then only the content within the directory is deleted.
 *   If FALSE, then the directory at path and its content are deleted.
 *   When recursion_max is 0, then this should only be FALSE (setting this to TRUE would be a no-op).
 * @param custom
 *   A custom function to pass to nftw() instead of using the internal one.
 *   Such as a custom function for verbose printing of removed files.
 *
 * @return
 *   F_none on success.
 *   F_access_denied (with error bit) on access denied.
 *   F_busy (with error bit) if file is busy.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_file_found_not (with error bit) if file not found.
 *   F_file_type_directory (with error bit) file is a directory (directories cannot be removed via this function).
 *   F_input_output (with error bit) if an I/O error occurred.
 *   F_loop (with error bit) on loop error.
 *   F_memory_out (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if filesystem does not allow for removing.
 *   F_read_only (with error bit) if file is read-only.
 *   F_failure (with error bit) for any other (remove()) error.
 *
 * @see nftw()
 * @see remove()
 */
#ifndef _di_f_directory_remove_custom_
  extern f_return_status f_directory_remove_custom(const f_string path, const int recursion_max, const bool preserve, int (*custom) (const char *, const struct stat *, int, struct FTW *));
#endif // _di_f_directory_remove_custom_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_directory_h
