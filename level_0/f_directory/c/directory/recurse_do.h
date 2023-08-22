/**
 * FLL - Level 0
 *
 * Project: Directory
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines type-specific data to be used for/by project directory.
 *
 * This is auto-included by directory.h and should not need to be explicitly included.
 */
#ifndef _F_directory_recurse_do_h
#define _F_directory_recurse_do_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure containing directory recursion information.
 *
 * The action() callback provide full access to this f_directory_recurse_do_t structure.
 * The action callback may set any of the following on the state.status to have the following effects:
 *   - Any status (with error bit set): Immediately return as error.
 *   - F_break:                         Break out of the current loop.
 *   - F_continue:                      Skip to the next iteration in the current loop.
 *   - F_done:                          Immedately return as success but do nothing else in this recursion.
 *
 * The action parameters are:
 *   - recurse: Must be of type f_directory_recurse_do_t and represents this data. Must not be NULL.
 *   - name:    The name of the file or directory the action is being performed on (does not have the parent directory path) (may be empty at the top level).
 *   - flag:    A flag representing the particular action being performed.
 *
 * The handle() callback provides a callback identical to the handle() except that it is for handling exceptions in place of state.handle().
 * The handle() provides additional information not provided by state.handle() but if it is NULL, then state.handle() is called.
 * The state.handle() and state.interrupt() callbacks internal parameter must be of type f_directory_recurse_do_t.
 *
 * The callbacks must take care to properly modify the structure or they could cause security, integrity, or functionality problems.
 *
 * Properties:
 *   - depth:     A number representing the depth recursed thus far (generally assigned internally).
 *   - depth_max: The maximum recursion depth to use.
 *   - flag:      A set of flags used exclusively by the directory recurse process (not to be confused with state.flag).
 *   - mode:      A file mode flag to use when working on files, such as when copying a file.
 *
 *   - state:     A pointer to the state information, where state.interrupt() and state.handle() are called appopriately.
 *   - listing:   A directory listing structure used internally to help reduce repeated memory allocation overhead.
 *
 *   - path:       A path representing the current directory path being operated on and usually represents the parent path of some file or directory (generally assigned internally).
 *   - path_cache: A path-related cache made available for the caller to use, such as combining the path and the file name in the action callback.
 *   - path_top:   A pointer to the top path string, used for error handling and printing (generally assigned internally).
 *
 *   - action: A callback used for performing some action (this is required to do anything).
 *   - handle: A callback used for performing error handling during recursion directly relating to a file.
 *
 * The macro_f_directory_recurse_do_t_initialize_1() all arguments.
 * The macro_f_directory_recurse_do_t_initialize_2() all arguments except for internally managed source, destination, mode, and depth.
 */
#ifndef _di_f_directory_recurse_do_t_
  typedef struct {
    f_number_unsigned_t depth;
    f_number_unsigned_t depth_max;
    uint16_t flag;
    f_mode_t mode;

    f_state_t state;
    f_directory_listing_t listing;

    f_string_dynamic_t path;
    f_string_dynamic_t path_cache;
    const f_string_static_t *path_top;

    void (*action)(void * const recurse, const f_string_static_t name, const uint16_t flag);
    void (*handle)(void * const recurse, const f_string_static_t name, const uint16_t flag);
  } f_directory_recurse_do_t;

  #define f_directory_recurse_do_t_initialize { \
    0, \
    F_directory_max_recurse_depth_d, \
    f_directory_recurse_do_flag_none_e, \
    f_mode_t_initialize, \
    f_state_t_initialize, \
    f_directory_listing_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    0, \
    0, \
    0, \
  }

  #define macro_f_directory_recurse_do_t_initialize_1(depth, depth_max, flag, mode, state, listing, path, path_cache, path_top, action, handle) { \
    depth, \
    depth_max, \
    flag, \
    mode, \
    state, \
    listing, \
    path, \
    path_cache, \
    path_top, \
    action, \
    handle, \
  }

  #define macro_f_directory_recurse_do_t_initialize_2(depth, depth_max, flag, mode, state, action, handle) { \
    depth,\
    depth_max \
    flag, \
    mode, \
    state, \
    f_directory_listing_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    0, \
    action, \
    handle, \
  }
#endif // _di_f_directory_recurse_do_t_

/**
 * An array of directory recursion information.
 *
 * Properties:
 *   - array: An array of directory recursion information.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_directory_recurse_dos_t_
  typedef struct {
    f_directory_recurse_do_t *array;
    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_directory_recurse_dos_t;

  #define f_directory_recurse_dos_t_initialize { 0, 0, 0 }

  #define macro_f_directory_recurse_dos_t_initialize_1(content, size, used) { array, size, used }
  #define macro_f_directory_recurse_dos_t_initialize_2(array, length) { array, length, length }

  #define macro_f_directory_recurse_dos_t_clear(structures) macro_f_memory_structures_clear(structures)
#endif // _di_f_directory_recurse_dos_t_

/**
 * An array of an array of directory recursion information.
 *
 * Properties:
 *   - array: An array of directory recursion information.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_directory_recurse_doss_t_
  typedef struct {
    f_directory_recurse_dos_t *array;
    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_directory_recurse_doss_t;

  #define f_directory_recurse_doss_t_initialize { 0, 0, 0 }

  #define macro_f_directory_recurse_doss_t_initialize_1(content, size, used) { array, size, used }
  #define macro_f_directory_recurse_doss_t_initialize_2(array, length) { array, length, length }

  #define macro_f_directory_recurse_doss_t_clear(structures) macro_f_memory_structures_clear(structures)
#endif // _di_f_directory_recurse_doss_t_

/**
 * Delete all non-pointer based dynamic arrays within the recurse.
 *
 * @param recurse
 *   The recurse to fully delete.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_f_directory_recurse_do_delete_
  extern f_status_t f_directory_recurse_do_delete(f_directory_recurse_do_t * const recurse);
#endif // _di_f_directory_recurse_do_delete_

/**
 * Destroy all non-pointer based dynamic arrays within the recurse.
 *
 * @param recurse
 *   The recurse to fully destroy.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *
 * @see f_memory_array_adjust()
 */
#ifndef _di_f_directory_recurse_do_destroy_
  extern f_status_t f_directory_recurse_do_destroy(f_directory_recurse_do_t * const recurse);
#endif // _di_f_directory_recurse_do_destroy_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_directory_recurse_dos_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_f_directory_recurse_dos_delete_callback_
  extern f_status_t f_directory_recurse_dos_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_directory_recurse_dos_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_directory_recurse_dos_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *
 * @see f_memory_array_adjust()
 */
#ifndef _di_f_directory_recurse_dos_destroy_callback_
  extern f_status_t f_directory_recurse_dos_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_directory_recurse_dos_destroy_callback_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_directory_recurse_doss_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_f_directory_recurse_doss_delete_callback_
  extern f_status_t f_directory_recurse_doss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_directory_recurse_doss_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_directory_recurse_doss_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *
 * @see f_memory_array_adjust()
 */
#ifndef _di_f_directory_recurse_doss_destroy_callback_
  extern f_status_t f_directory_recurse_doss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_directory_recurse_doss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_directory_recurse_do_h
