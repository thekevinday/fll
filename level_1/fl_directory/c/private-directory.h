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
 * Private implementation of fl_directory_do().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param recurse
 *   The directory recurse data.
 *
 *   This alters recurse.state.status:
 *     F_okay on success.
 *     F_done on success and instructed to end recursion.
 *
 *     F_interrupt (with error bit) if stopping due to an interrupt.
 *
 *     Errors (with error bit) from: f_memory_array_increase_by().
 *     Errors (with error bit) from: f_string_dynamic_append_assure().
 *     Errors (with error bit) from: f_string_dynamic_append_nulless().
 *     Errors (with error bit) from: fl_directory_list().
 *
 *     Errors (with error bit) from: private_fl_directory_list().
 *     Errors (with error bit) from: private_inline_fl_directory_do_handle().
 *
 *     Errors (with error bit) from: recurse.action().
 *     Errors (with error bit) from: recurse.handle().
 *
 * @see f_memory_array_increase_by()
 * @see f_string_dynamic_append_assure()
 * @see f_string_dynamic_append_nulless()
 * @see fl_directory_do()
 *
 * @see private_fl_directory_list()
 * @see private_inline_fl_directory_do_handle()
 *
 * @see recurse.action()
 * @see recurse.handle()
 */
#if !defined(_di_fl_directory_do_)
  extern void private_fl_directory_do_recurse(f_directory_recurse_do_t * const recurse) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_directory_do_)

/**
 * Private inline function for use by fl_directory_do().
 *
 * Intended to simplify code similar to using a macro function.
 *
 * This calls the handle callback as is appropriate.
 *
 * @param recurse
 *   The directory recurse data.
 *
 * @return
 *   F_okay on success.
 *
 *   F_failure (with error bit) for any other failure, failures might be populated with individual status codes.
 *
 * @see fl_directory_do()
 */
#if !defined(_di_fl_directory_do_)
  static inline void private_inline_fl_directory_do_handle(f_directory_recurse_do_t * const recurse, const f_string_static_t path, const uint16_t flag) {
    if (recurse->handle) {
      recurse->handle((void *) recurse, path, flag);
    }
    else if (recurse->state.handle) {
      recurse->state.handle(&recurse->state, (void *) recurse);
    }
  }
#endif // !defined(_di_fl_directory_do_)

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
 *   F_okay on success.
 *   F_data_not if directory is empty.
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
 *   Errors (with error bit) from: f_memory_array_increase_by().
 *
 * @see f_file_stat_at()
 * @see f_memory_array_increase_by()
 *
 * @see fl_directory_do()
 * @see fl_directory_list()
 */
#if !defined(_di_fl_directory_do_) || !defined(_di_fl_directory_list_)
  extern f_status_t private_fl_directory_list(const f_string_static_t path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), const bool dereference, f_directory_listing_t * const listing) F_attribute_visibility_internal_d;
#endif // !defined(_di_fl_directory_do_) || !defined(_di_fl_directory_list_)

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
 *   F_okay on success.
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
