/**
 * FLL - Level 1
 *
 * Project: Directory
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides operations for directory handling.
 */
#ifndef _FL_directory_h
#define _FL_directory_h

// Libc includes.
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// Work-around for systems that require __USE_XOPEN_EXTENDED defined to properly include ftw.h.
#ifndef __USE_XOPEN_EXTENDED
  #define __USE_XOPEN_EXTENDED
  #include <ftw.h>
  #undef __USE_XOPEN_EXTENDED
#else
  #include <ftw.h>
#endif // __USE_XOPEN_EXTENDED

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/type_array.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/directory.h>
#include <fll/level_0/file.h>
#include <fll/level_0/path.h>

// FLL-1 directory includes.
#include <fll/level_1/directory/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create all directories at the given path.
 *
 * The paths must not contain NULL except for the terminating NULL.
 * The paths must be NULL terminated.
 *
 * @param path
 *   The file path to the directory.
 * @param mode
 *   The directory mode to use when creating.
 *   This is applied to all created directories.
 *
 * @return
 *   F_none on success.
 *   F_data_not if path.used is 0.
 *   F_directory_found on success, but the directory already exists.
 *
 *   F_access_denied (with error bit) on access denied.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_directory_link_max (with error bit) max links limit reached or exceeded.
 *   F_file_found (with error bit) of a directory aleady exists at the path.
 *   F_file_found_not (with error bit) if a file within the path is not found (such as a broken symbolic link).
 *   F_filesystem_quota_block (with error bit) if file system's disk blocks or inodes are exhausted.
 *   F_loop (with error bit) on loop error.
 *   F_memory_not (with error bit) if out of memory.
 *   F_name (with error bit) on path name error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if file system does not allow for removing.
 *   F_read_only (with error bit) if file is read-only.
 *   F_space_not (with error bit) if file system is out of space (or file system quota is reached).
 *   F_failure (with error bit) for any other error.
 *
 * @see f_directory_create()
 */
#ifndef _di_fl_directory_create_
  extern f_status_t fl_directory_create(const f_string_static_t path, const mode_t mode);
#endif // _di_fl_directory_create_

/**
 * Perform a recursive action on some directory.
 *
 * This is intended to be used as an alternative to functions like fl_directory_list(), giving more control over the recursion process.
 *
 * When recursing the directory, except for the top directory, handle() with the before and after flags set is called after the recurse.path is updated.
 * For the top directory, handle() is called with the before and after flags set when the path is not updated (that is, the path should be
 *
 * This function is designed and intended to be used on directories.
 * If depth is 0, the operations callacks are still called but done at the top level.
 *
 * The action callback must set the error bit to ensure that the handle callbacks are called or not set the error bit to prevent this behavior.
 *
 * This exists on error if, after the handle callback is called, that the recurse.state.status still has the error bit set.
 * This allows for the caller to inform this function to effectively ignore any errors.
 *
 * @param path
 *   The directory file path.
 *   Must be NULL terminated.
 * @param recurse
 *   The directory recurse data.
 *   This must not be NULL.
 *
 *   This alters recurse.state.status:
 *     F_none on success.
 *     F_data_not if source.used or destination.used is 0.
 *
 *     F_directory_descriptor (with error bit) on directory file descriptor error.
 *     F_directory_not (with error bit) if the directory does not exist.
 *     F_directory_open (with error bit) on directory open error.
 *     F_directory_stream (with error bit) on directory stream error.
 *     F_directory_support_not (with error bit) on directory file descriptor not supported.
 *     F_failure (with error bit) if failed to read directory information.
 *     F_file_descriptor_max (with error bit) if max file descriptors is reached.
 *     F_file_open_max (with error bit) too many open files.
 *     F_interrupt (with error bit) if stopping due to an interrupt.
 *     F_memory_not (with error bit) on out of memory.
 *     F_parameter (with error bit) if a parameter is invalid.
 *     F_string_too_large (with error bit) if appended string length is too large to store in the buffer.
 *
 *     Errors (with error bit) from: f_directory_create().
 *     Errors (with error bit) from: f_directory_exists().
 *     Errors (with error bit) from: f_file_mode_set().
 *     Errors (with error bit) from: f_file_role_change().
 *     Errors (with error bit) from: f_file_stat().
 *     Errors (with error bit) from: f_file_stat_at().
 *     Errors (with error bit) from: f_string_dynamic_append_assure().
 *     Errors (with error bit) from: f_string_dynamic_append_nulless().
 *     Errors (with error bit) from: f_string_dynamic_increase_by().
 *     Errors (with error bit) from: f_string_dynamic_resize().
 *     Errors (with error bit) from: f_string_dynamics_increase_by().
 *     Errors (with error bit) from: f_string_dynamics_resize().
 *
 *     Errors (with error bit) from: recurse.action().
 *     Errors (with error bit) from: recurse.handle().
 *
 * @see alphasort()
 * @see opendir()
 * @see scandir()
 * @see versionsort()
 *
 * @see f_directory_create()
 * @see f_directory_exists()
 * @see f_file_mode_set()
 * @see f_file_role_change()
 * @see f_file_stat()
 * @see f_file_stat_at()
 * @see f_string_dynamic_append_assure()
 * @see f_string_dynamic_append_nulless()
 * @see f_string_dynamic_increase_by()
 * @see f_string_dynamic_resize()
 * @see f_string_dynamics_increase_by()
 * @see f_string_dynamics_resize()
 *
 * @see recurse.action()
 * @see recurse.handle()
 */
#ifndef _di_fl_directory_do_
  extern void fl_directory_do(const f_string_static_t path, f_directory_recurse_do_t * const recurse);
#endif // _di_fl_directory_do_

/**
 * For some given path, print the names of each file and/or directory inside the directory, stored as a directory listing.
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
 * @param dereference
 *   Set to TRUE to dereferenc symlinks (often is what is desired).
 *   Set to FALSE to operate on the symlink itself.
 * @param listing
 *   Will be populated with the names of all top-level paths found within the given directory.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source.used or destination.used is 0.
 *   F_directory_empty if directory is empty.
 *
 *   F_directory_descriptor (with error bit) on directory file descriptor error.
 *   F_directory_open (with error bit) on directory open error.
 *   F_directory_stream (with error bit) on directory stream error.
 *   F_directory_support_not (with error bit) on directory file descriptor not supported.
 *   F_failure (with error bit) if failed to read directory information.
 *   F_file_descriptor_max (with error bit) if max file descriptors is reached.
 *   F_file_open_max (with error bit) too many open files.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the buffer.
 *
 *   Errors (with error bit) from: f_file_stat_at().
 *   Errors (with error bit) from: f_string_dynamics_increase_by().
 *
 * @see alphasort()
 * @see opendir()
 * @see scandir()
 * @see versionsort()
 *
 * @see f_file_stat_at()
 * @see f_string_dynamics_increase_by()
 */
#ifndef _di_fl_directory_list_
  extern f_status_t fl_directory_list(const f_string_static_t path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), const bool dereference, f_directory_listing_t * const listing);
#endif // _di_fl_directory_list_

/**
 * Append a path string onto the destination path.
 *
 * This ensures that there is a trailing '/' after pop.
 * This ignores control characters.
 * This does not dynamically reallocate the string.
 *
 * @param path
 *   The path to remove a single directory.
 *   This will only be NULL terminated if path string is already NULL terminated.
 *
 * @return
 *   F_none on success.
 *   F_data_not if path.used is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the buffer.
 *
 *   Errors (with error bit) from: f_utf_is_control().
 */
#ifndef _di_fl_directory_path_pop_
  extern f_status_t fl_directory_path_pop(f_string_static_t * const path);
#endif // _di_fl_directory_path_pop_

/**
 * Append a path string onto the destination path.
 *
 * This ensures that there is a leading and trailing '/' from source.
 * This ignores control characters.
 *
 * @param source
 *   The path to append onto the destination.
 *   This need not be NULL terminated.
 * @param destination
 *   The destination path to push the path part onto.
 *   Any terminating NULLs at the end of the destination string are removed before appending.
 *   This will only be NULL terminated if destination string is already NULL terminated.
 *
 * @return
 *   F_none on success.
 *   F_data_not if source.used is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the buffer.
 *
 *   Errors (with error bit) from: f_utf_is_control().
 */
#ifndef _di_fl_directory_path_push_
  extern f_status_t fl_directory_path_push(const f_string_static_t source, f_string_dynamic_t * const destination);
#endif // _di_fl_directory_path_push_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_directory_h
