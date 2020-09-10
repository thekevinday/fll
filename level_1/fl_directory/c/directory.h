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
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/status_array.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/utf.h>
#include <level_0/directory.h>
#include <level_0/file.h>
#include <level_0/path.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * An association of a path and a status code.
 *
 * The allocation macros apply to the path.
 *
 * depth_max:
 *   The max recursion depth.
 * size_block:
 *   The default number of chunks to read at a time with each chunk being 1-byte.
 *   Must be greater than 0.
 * exclusive:
 *   If TRUE, will fail when file already exists.
 *   If FALSE, will not fail if file already exists (existing file will be replaced).
 * output:
 *   Set to 0 to not print on successful operation.
 *   Set to a valid file pointer to print to on successful operation.
 *   This is passed to the verbose function if that function pointer is not 0.
 * verbose:
 *   Set to 0 to not print on successful operation.
 *   Set to address of a function to be called for printing such that:
 *     - The first parameter represents the file pointer from the output variable.
 *     - The second parameter represents the source string.
 *     - The third parameter represents the destination string.
 * failures:
 *   A list of paths and their respective status codes for clone failures.
 *   If 0, then this and statuses are ignored.
 */
#ifndef _di_fl_directory_recurse_t_
  #define fl_directory_recurse_depth_max 65535

  typedef struct {
    f_number_unsigned_t depth_max;
    f_number_unsigned_t size_block;
    bool exclusive;
    FILE *output;
    void (*verbose)(FILE *, const f_string_t, const f_string_t);
    f_directory_statuss_t *failures;
  } fl_directory_recurse_t;

  #define fl_directory_recurse_t_initialize { fl_directory_recurse_depth_max, f_file_default_read_size, F_false, 0, 0, 0 }
#endif // _di_fl_directory_recurse_t_

/**
 * Copy a directory and its contents, as well as its file mode and possibly the owner and group.
 *
 * The paths must not contain NULL except for the terminating NULL.
 * The paths must be NULL terminated.
 *
 * Symbolic links are not followed, they are copied as the symbolic link itself.
 *
 * This does not copy unknown file types.
 *
 * @param source
 *   The source file path.
 *   Must be NULL terminated.
 * @param destination
 *   The destination file path.
 *   Must be NULL terminated.
 * @param source_length
 *   The length of the source path.
 * @param destination_length
 *   The length of the destination path.
 * @param role
 *   If TRUE, will copy the owner and group ids.
 *   If FALSE, will not copy the owner and group ids.
 *   (In both cases the file mode is copied.)
 * @param recurse
 *   The directory recurse data.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) for any other failure, failures might be populated with individual status codes.
 *
 *   Errors from (with error bit): f_directory_create().
 *   Errors from (with error bit): f_directory_exists().
 *   Errors from (with error bit): f_file_mode_set().
 *   Errors from (with error bit): f_file_role_change().
 *   Errors from (with error bit): f_file_stat().
 *
 * @see f_file_clone()
 */
#ifndef _di_fl_directory_clone_
  extern f_return_status fl_directory_clone(const f_string_t source, const f_string_t destination, const f_string_length_t source_length, const f_string_length_t destination_length, const bool role, const fl_directory_recurse_t recurse);
#endif // _di_fl_directory_clone_

/**
 * Copy a directory contents, as well as its file mode and possibly the owner and group.
 *
 * When cloning the contents of a directory, both the source and the destination paths must already exist and be directories, regardless of exclusive boolean.
 *
 * The paths must not contain NULL except for the terminating NULL.
 * The paths must be NULL terminated.
 *
 * Symbolic links are not followed, they are copied as the symbolic link itself.
 *
 * This does not copy unknown file types.
 *
 * @param source
 *   The source file path.
 *   Must be NULL terminated.
 * @param destination
 *   The destination file path.
 *   Must be NULL terminated.
 * @param source_length
 *   The length of the source path.
 * @param destination_length
 *   The length of the destination path.
 * @param role
 *   If TRUE, will copy the owner and group ids.
 *   If FALSE, will not copy the owner and group ids.
 *   (In both cases the file mode is copied.)
 * @param recurse
 *   The directory recurse data.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) for any other failure, failures might be populated with individual status codes.
 *
 *   Errors from (with error bit): f_directory_exists().
 *
 * @see f_file_clone()
 */
#ifndef _di_fl_directory_clone_content_
  extern f_return_status fl_directory_clone_content(const f_string_t source, const f_string_t destination, const f_string_length_t source_length, const f_string_length_t destination_length, const bool role, const fl_directory_recurse_t recurse);
#endif // _di_fl_directory_clone_content_

/**
 * Copy a directory and its contents.
 *
 * The paths must not contain NULL except for the terminating NULL.
 * The paths must be NULL terminated.
 *
 * Symbolic links are not followed, they are copied as the symbolic link itself.
 *
 * This does not copy unknown file types.
 *
 * @param source
 *   The source file path.
 *   Must be NULL terminated.
 * @param destination
 *   The destination file path.
 *   Must be NULL terminated.
 * @param source_length
 *   The length of the source path.
 * @param destination_length
 *   The length of the destination path.
 * @param mode
 *   The directory modes.
 * @param recurse
 *   The directory recurse data.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) for any other failure, failures might be populated with individual status codes.
 *
 *   Errors from (with error bit): f_directory_create().
 *   Errors from (with error bit): f_directory_exists().
 *   Errors from (with error bit): f_file_mode_set().
 *   Errors from (with error bit): f_file_role_change().
 *   Errors from (with error bit): f_file_stat().
 *
 * @see f_file_copy()
 */
#ifndef _di_fl_directory_copy_
  extern f_return_status fl_directory_copy(const f_string_t source, const f_string_t destination, const f_string_length_t source_length, const f_string_length_t destination_length, const f_mode_t mode, const fl_directory_recurse_t recurse);
#endif // _di_fl_directory_copy_

/**
 * Copy a directory contents.
 *
 * When copying the contents of a directory, both the source and the destination paths must already exist and be directories, regardless of exclusive boolean.
 *
 * The paths must not contain NULL except for the terminating NULL.
 * The paths must be NULL terminated.
 *
 * Symbolic links are not followed, they are copied as the symbolic link itself.
 *
 * This does not copy unknown file types.
 *
 * @param source
 *   The source file path.
 *   Must be NULL terminated.
 * @param destination
 *   The destination file path.
 *   Must be NULL terminated.
 * @param source_length
 *   The length of the source path.
 * @param destination_length
 *   The length of the destination path.
 * @param mode
 *   The directory modes.
 * @param recurse
 *   The directory recurse data.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) for any other failure, failures might be populated with individual status codes.
 *
 *   Errors from (with error bit): f_directory_exists().
 *
 * @see f_file_copy()
 */
#ifndef _di_fl_directory_copy_content_
  extern f_return_status fl_directory_copy_content(const f_string_t source, const f_string_t destination, const f_string_length_t source_length, const f_string_length_t destination_length, const f_mode_t mode, const fl_directory_recurse_t recurse);
#endif // _di_fl_directory_copy_content_

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
 *   F_data_not if directory is empty.
 *   F_directory_descriptor (with error bit) on directory file descriptor error.
 *   F_directory_open (with error bit) on directory open error.
 *   F_directory_stream (with error bit) on directory stream error.
 *   F_directory_unsupported (with error bit) on directory file descriptor not supported.
 *   F_failure (with error bit) if failed to read directory information.
 *   F_file_descriptor_max (with error bit) if max file descriptors was reached.
 *   F_file_open_max (with error bit) too many open files.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the buffer.
 *
 * @see alphasort()
 * @see opendir()
 * @see scandir()
 * @see versionsort()
 */
#ifndef _di_fl_directory_list_
  extern f_return_status fl_directory_list(const f_string_t path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), const bool dereference, f_directory_listing_t *listing);
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
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the buffer.
 */
#ifndef _di_fl_directory_path_pop_
  extern f_return_status fl_directory_path_pop(f_string_static_t *path);
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
 * @param length
 *   The length of the string.
 *   Must not exceed length of source.
 * @param destination
 *   The destination path to push the path part onto.
 *   Any terminating NULLs at the end of the destination string are removed before appending.
 *   This will only be NULL terminated if destination string is already NULL terminated.
 *
 * @return
 *   F_none on success.
 *   F_data_not if length is 0.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the buffer.
 *
 *   Errors from (with error bit): f_utf_is_control().
 */
#ifndef _di_fl_directory_path_push_
  extern f_return_status fl_directory_path_push(const f_string_t source, f_string_length_t length, f_string_dynamic_t *destination);
#endif // _di_fl_directory_path_push_

/**
 * Append a dynamic path string onto the destination path.
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
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the buffer.
 *
 *   Errors from (with error bit): f_utf_is_control().
 */
#ifndef _di_fl_directory_path_push_dynamic_
  extern f_return_status fl_directory_path_push_dynamic(const f_string_static_t source, f_string_dynamic_t *destination);
#endif // _di_fl_directory_path_push_dynamic_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_directory_h
