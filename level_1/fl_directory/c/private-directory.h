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
 * Private implementation of fl_directory_clone().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source file path.
 *   Must be NULL terminated.
 * @param destination
 *   The destination file path.
 *   Must be NULL terminated.
 * @param role
 *   If TRUE, will copy the owner and group ids.
 *   If FALSE, will not copy the owner and group ids.
 *   (In both cases the file mode is copied.)
 * @param size_block
 *   The default number of chunks to read at a time with each chunk being 1-byte.
 *   Must be greater than 0.
 * @param exclusive
 *   If TRUE, will fail when file already exists.
 *   If FALSE, will not fail if file already exists (existing file will be replaced).
 * @param verbose
 *   Set to 0 to not print copy operation values on successful copy.
 *   Set to a valid file pointer, such as f_type_output (stdout), to print on successful copy.
 * @param failures
 *   A list of paths and their respective status codes for clone failures.
 *   If 0, then this and statuses is ignored.
 *
 * @return
 *   F_none on success.
 *   F_data_not if directory is empty.
 *   F_directory_descriptor (with error bit) on directory file descriptor error.
 *   F_directory_open (with error bit) on directory open error.
 *   F_directory_stream (with error bit) on directory stream error.
 *   F_directory_unsupported (with error bit) on directory file descriptor not supported.
 *   F_file_descriptor_max (with error bit) if max file descriptors was reached.
 *   F_file_open_max (with error bit) too many open files.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the buffer.
 *   F_failure (with error bit) for any other failure, failures might be populated with individual status codes.
 *
 * @see fl_directory_clone()
 */
#if !defined(_di_fl_directory_clone_)
  extern f_return_status private_fl_directory_clone(const f_string_static source, const f_string_static destination, const bool role, const f_number_unsigned size_block, const bool exclusive, FILE *verbose, f_directory_statuss *failures) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_directory_clone_)

/**
 * A special function intended to be used directly by private_fl_directory_clone().
 *
 * Will only clone a single file and record any detected errors.
 *
 * @param file
 *   The name of the file within source to clone into destination.
 *   Must be NULL terminated.
 * @param source
 *   The source file path.
 *   Must be NULL terminated.
 * @param destination
 *   The destination file path.
 *   Must be NULL terminated.
 * @param role
 *   If TRUE, will copy the owner and group ids.
 *   If FALSE, will not copy the owner and group ids.
 *   (In both cases the file mode is copied.)
 * @param size_block
 *   The default number of chunks to read at a time with each chunk being 1-byte.
 *   Must be greater than 0.
 * @param exclusive
 *   If TRUE, will fail when file already exists.
 *   If FALSE, will not fail if file already exists (existing file will be replaced).
 * @param verbose
 *   Set to 0 to not print copy operation values on successful copy.
 *   Set to a valid file pointer, such as f_type_output (stdout), to print on successful copy.
 * @param failures
 *   A list of paths and their respective status codes for clone failures.
 *   If 0, then this and statuses is ignored.
 *
 * @return
 *   F_none on success.
 *   F_data_not if directory is empty.
 *   F_buffer_too_large (with error bit) if a buffer would exceed max length.
 *   F_directory_descriptor (with error bit) on directory file descriptor error.
 *   F_directory_open (with error bit) on directory open error.
 *   F_directory_stream (with error bit) on directory stream error.
 *   F_directory_unsupported (with error bit) on directory file descriptor not supported.
 *   F_file_descriptor_max (with error bit) if max file descriptors was reached.
 *   F_file_open_max (with error bit) too many open files.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the buffer.
 *   F_failure (with error bit) for any other failure, failures might be populated with individual status codes.
 *
 * @see fl_directory_clone()
 */
#if !defined(_di_fl_directory_clone_file_)
  extern f_return_status private_fl_directory_clone_file(const f_string_static file, const f_string_static source, const f_string_static destination, const bool role, const f_number_unsigned size_block, const bool exclusive, FILE *verbose, f_directory_statuss *failures) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_directory_clone_file_)

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
 * @param mode
 *   The mode for each file type.
 * @param size_block
 *   The default number of chunks to read at a time with each chunk being 1-byte.
 *   Must be greater than 0.
 * @param exclusive
 *   If TRUE, will fail when file already exists.
 *   If FALSE, will not fail if file already exists (existing file will be replaced).
 * @param verbose
 *   Set to 0 to not print copy operation values on successful copy.
 *   Set to a valid file pointer, such as f_type_output (stdout), to print on successful copy.
 * @param failures
 *   A list of paths and their respective status codes for copy failures.
 *   If 0, then this and statuses is ignored.
 *
 * @return
 *   F_none on success.
 *   F_data_not if directory is empty.
 *   F_directory_descriptor (with error bit) on directory file descriptor error.
 *   F_directory_open (with error bit) on directory open error.
 *   F_directory_stream (with error bit) on directory stream error.
 *   F_directory_unsupported (with error bit) on directory file descriptor not supported.
 *   F_file_descriptor_max (with error bit) if max file descriptors was reached.
 *   F_file_open_max (with error bit) too many open files.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the buffer.
 *   F_failure (with error bit) for any other failure, failures might be populated with individual status codes.
 *
 * @see fl_directory_copy()
 */
#if !defined(_di_fl_directory_copy_)
  extern f_return_status private_fl_directory_copy(const f_string_static source, const f_string_static destination, const f_mode mode, const f_number_unsigned size_block, const bool exclusive, FILE *verbose, f_directory_statuss *failures) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_directory_copy_)

/**
 * A special function intended to be used directly by private_fl_directory_copy().
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
 * @param size_block
 *   The default number of chunks to read at a time with each chunk being 1-byte.
 *   Must be greater than 0.
 * @param exclusive
 *   If TRUE, will fail when file already exists.
 *   If FALSE, will not fail if file already exists (existing file will be replaced).
 * @param verbose
 *   Set to 0 to not print copy operation values on successful copy.
 *   Set to a valid file pointer, such as f_type_output (stdout), to print on successful copy.
 * @param failures
 *   A list of paths and their respective status codes for copy failures.
 *   If 0, then this and statuses is ignored.
 *
 * @return
 *   F_none on success.
 *   F_data_not if directory is empty.
 *   F_directory_descriptor (with error bit) on directory file descriptor error.
 *   F_directory_open (with error bit) on directory open error.
 *   F_directory_stream (with error bit) on directory stream error.
 *   F_directory_unsupported (with error bit) on directory file descriptor not supported.
 *   F_file_descriptor_max (with error bit) if max file descriptors was reached.
 *   F_file_open_max (with error bit) too many open files.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if appended string length is too large to store in the buffer.
 *   F_failure (with error bit) for any other failure, failures might be populated with individual status codes.
 *
 * @see fl_directory_copy()
 */
#if !defined(_di_fl_directory_copy_file_)
  extern f_return_status private_fl_directory_copy_file(const f_string_static file, const f_string_static source, const f_string_static destination, const f_mode mode, const f_number_unsigned size_block, const bool exclusive, FILE *verbose, f_directory_statuss *failures) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_directory_copy_file_)

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
 * @see fl_directory_list()
 */
#if !defined(_di_fl_directory_list_)
  extern f_return_status private_fl_directory_list(const f_string path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), const bool dereference, f_directory_listing *listing) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_directory_list_)

/**
 * Private implementation of fl_directory_path_push().
 *
 * Intended to be shared to each of the different implementation variations.
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
 *
 * @see fl_directory_path_push()
 * @see fl_directory_path_push_dynamic()
 */
#if !defined(_di_fl_directory_path_push_) || !defined(_di_fl_directory_path_push_dynamic_)
  extern f_return_status private_fl_directory_path_push(const f_string source, const f_string_length length, f_string_dynamic *destination) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_directory_path_push_) || !defined(_di_fl_directory_path_push_dynamic_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_directory_h
