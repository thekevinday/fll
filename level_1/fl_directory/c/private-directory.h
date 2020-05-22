/**
 * FLL - Level 1
 *
 * Project: Directory
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides operations for directory handling.
 */
#ifndef _PRIVATE_FL_directory_h
#define _PRIVATE_FL_directory_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A special function intended to be used directly by fl_directory_copy()
 *
 * @param path
 *   The file path.
 * @param file_stat
 *   The file stat.
 * @param type
 *   The file type.
 * @param entity
 *   The FTW entity.
 *
 * @return
 *   0 on success.
 *   -1 on failure.
 *   Check errno for details.
 *
 * @see fl_directory_copy()
 */
#if !defined(_di_fl_directory_copy_)
  f_return_status private_fl_directory_copy(const f_string source, const f_string destination, const f_directory_mode mode, const f_number_unsigned size_block, const bool exclusive) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_directory_copy_)


/**
 * A special function intended to be used directly by fl_directory_list().
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
 * @see fl_directory_list()
 */
#if !defined(_di_fl_directory_list_)
  extern f_return_status private_fl_directory_list(const f_string path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), f_directory_listing *listing) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_directory_list_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_directory_h
