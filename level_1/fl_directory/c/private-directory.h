/**
 * FLL - Level 1
 *
 * Project: Directory
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides operations for directory handling.
 */
#ifndef _PRIVATE_FL_directory_h
#define _PRIVATE_FL_directory_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of fl_directory_copy().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source file path.
 *   Must be NULL terminated.
 * @param destination
 *   The destination file path.
 *   Must be NULL terminated.
 * @param recurse
 *   The directory recurse data.
 * @param depth
 *   The current depth.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) for any other failure, failures might be populated with individual status codes.
 *
 * @see fl_directory_copy()
 */
#if !defined(_di_fl_directory_copy_)
  extern void private_fl_directory_copy_recurse(f_directory_recurse_t * const recurse) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_directory_copy_)

/**
 * A special function intended to be used directly by private_fl_directory_copy_recurse().
 *
 * Will only copy a single file and record any detected errors.
 *
 * @param file
 *   The name of the file within source to copy into destination.
 *   Must be NULL terminated.
 * @param source
 *   The source file path.
 *   Must be NULL terminated.
 * @param destination
 *   The destination file path.
 *   Must be NULL terminated.
 * @param mode
 *   The mode for each file type.
 * @param recurse
 *   The directory recurse data.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if a buffer would exceed max length.
 *   F_failure (with error bit) for any other failure, failures might be populated with individual status codes.
 *
 * @see fl_directory_copy()
 */
#if !defined(_di_fl_directory_copy_)
  extern void private_fl_directory_copy_recurse_file(const f_string_static_t file, f_directory_recurse_t * const recurse) F_attribute_visibility_internal_d;
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
 * @param dereference
 *   Set to TRUE to dereferenc symlinks (often is what is desired).
 *   Set to FALSE to operate on the symlink itself.
 * @param listing
 *   Will be populated with the names of all top-level paths found within the given directory.
 *
 * @return
 *   F_none on success.
 *   F_data_not if directory is empty.
 *
 *   F_directory_descriptor (with error bit) on directory file descriptor error.
 *   F_directory_open (with error bit) on directory open error.
 *   F_directory_stream (with error bit) on directory stream error.
 *   F_directory_supported_not (with error bit) on directory file descriptor not supported.
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
 * @see f_file_stat_at()
 * @see f_string_dynamics_increase_by()
 *
 * @see fl_directory_copy()
 * @see fl_directory_list()
 */
#if !defined(_di_fl_directory_copy_) || !defined(_di_fl_directory_list_)
  extern f_status_t private_fl_directory_list(const f_string_static_t path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), const bool dereference, f_directory_listing_t * const listing) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_directory_copy_) || !defined(_di_fl_directory_list_)

/**
 * Private implementation of fl_directory_path_push().
 *
 * Intended to be shared to each of the different implementation variations.
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
 *   F_data_not if length is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the buffer.
 *
 *   Errors (with error bit) from: f_utf_is_control().
 *
 * @see fl_directory_path_push()
 * @see fl_directory_path_push_dynamic()
 */
#if !defined(_di_fl_directory_path_push_) || !defined(_di_fl_directory_path_push_dynamic_)
  extern f_status_t private_fl_directory_path_push(const f_string_static_t source, f_string_dynamic_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_directory_path_push_) || !defined(_di_fl_directory_path_push_dynamic_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_directory_h
