/**
 * FLL - Level 2
 *
 * Project: Directory
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides operations for directory handling.
 */
#ifndef _FLL_directory_h
#define _FLL_directory_h

// libc includes
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/type.h>
#include <level_0/directory.h>
#include <level_0/file.h>

// fll-1 includes
#include <level_1/string.h>

#ifdef __cplusplus
extern "C" {
#endif

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
 *   f_none on success.
 *   f_no_data if directory is empty (@fixme: unlikely due to '.' and '..' probably always being returned.).
 *   f_failure (with error bit) if failed to read directory information.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_reallocation (with error bit) on memory reallocation error.
 *   f_directory_error_open (with error bit) on directory open error.
 *   f_directory_error_descriptor (with error bit) on directory file descriptor error.
 *   f_directory_error_stream (with error bit) on directory stream error.
 *   f_directory_error_unsupported (with error bit) on directory file descriptor not supported.
 *   f_file_max_descriptors (with error bit) if max file descriptors was reached.
 *   f_file_max_open (with error bit) too many open files.
 *
 * @see alphasort()
 * @see scandir()
 * @see versionsort()
 */
#ifndef _di_fll_directory_list_
  extern f_return_status fll_directory_list(const f_string path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), f_directory_listing *listing);
#endif // _di_fll_directory_list_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_directory_h
