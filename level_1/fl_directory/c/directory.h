/**
 * FLL - Level 1
 *
 * Project: Directory
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides operations for directory handling.
 */
#ifndef _FL_directory_h
#define _FL_directory_h

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
#include <level_0/file.h>
#include <level_0/directory.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Copy a directory and its contents.
 *
 * The paths must not contain NULL except for the terminating NULL.
 * The paths must be NULL terminated.
 *
 * Symbolic links are not followed, they are copied as the symbolic link itself.
 *
 * @param source
 *   The path to the directory to copy from.
 * @param destination
 *   The path to copy to.
 * @param mode
 *   The file mode assigned to the destination file (based on each file type).
 * @param size_block
 *   The default number of chunks to read at a time with each chunk being 1-byte.
 *   Must be greater than 0.
 * @param exclusive
 *   If TRUE, will fail when parent directory already exists.
 *   If FALSE, will not fail if parent directory already exists (existing directory will be updated).
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
 *   F_filesystem_quota_block (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   F_filesystem_quota_reached (with error bit) quota reached of filesystem is out of space.
 *   F_file_found (with error bit) of a directory aleady exists at the path.
 *   F_name (with error bit) on path name error.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_interrupted (with error bit) when program received an interrupt signal, halting create.
 *   F_file_open_max (with error bit) when system-wide max open files is reached.
 *   F_busy (with error bit) if filesystem is too busy to perforrm write.
 *   F_file_read (with error bit) on file read error.
 *   F_file_write (with error bit) on file write error.

 * @see f_directory_create()
 * @see f_file_copy()
 * @see read()
 */
#ifndef _di_fl_directory_copy_
  extern f_return_status fl_directory_copy(const f_string source, const f_string destination, const f_directory_mode mode, const f_number_unsigned size_block, const bool exclusive);
#endif // _di_fl_directory_copy_

/**
 * Copy a file, as well as its file mode and possibly the owner and group.
 *
 * The paths must not contain NULL except for the terminating NULL.
 * The paths must be NULL terminated.
 *
 * @todo provide a return status for when owner/role cannot be assigned.
 * This will be returned when complete so that caller can decide if this is an error or not.
 *
 * Symbolic links are not followed, they are copied as the symbolic link itself.
 *
 * @param source
 *   The path to the directory to copy from.
 * @param destination
 *   The path to copy to.
 * @param size_block
 *   The default number of chunks to read at a time with each chunk being 1-byte.
 *   Must be greater than 0.
 * @param exclusive
 *   If TRUE, will fail when parent directory already exists.
 *   If FALSE, will not fail if parent directory already exists (existing directory will be updated).
 * @param roles
 *   If TRUE, will copy the owner and group ids.
 *   If FALSE, will not copy the owner and group ids.
 *   (In both cases the file mode is copied.)
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
 *   F_filesystem_quota_block (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   F_filesystem_quota_reached (with error bit) quota reached of filesystem is out of space.
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
 * @see f_directory_create()
 * @see f_file_clone()
 * @see read()
 */
#ifndef _di_fl_directory_clone_
  extern f_return_status fl_directory_clone(const f_string source, const f_string destination, const f_number_unsigned size_block, const bool exclusive, const bool roles);
#endif // _di_fl_directory_clone_

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
 * @param listing
 *   Will be populated with the names of all top-level paths found within the given directory.
 *
 * @return
 *   F_none on success.
 *   F_data_not if directory is empty (@fixme: unlikely due to '.' and '..' probably always being returned.).
 *   F_failure (with error bit) if failed to read directory information.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_directory_open (with error bit) on directory open error.
 *   F_directory_descriptor (with error bit) on directory file descriptor error.
 *   F_directory_stream (with error bit) on directory stream error.
 *   F_directory_unsupported (with error bit) on directory file descriptor not supported.
 *   F_file_descriptor_max (with error bit) if max file descriptors was reached.
 *   F_file_open_max (with error bit) too many open files.
 *
 * @see alphasort()
 * @see opendir()
 * @see scandir()
 * @see versionsort()
 */
#ifndef _di_fl_directory_list_
  extern f_return_status fl_directory_list(const f_string path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), f_directory_listing *listing);
#endif // _di_fl_directory_list_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_directory_h
