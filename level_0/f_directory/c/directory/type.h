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
#ifndef _F_directory_type_h
#define _F_directory_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure representing a listing of paths found within a directory.
 *
 * Each property represents a set of paths grouped by directory entity file type.
 *
 * block:     For S_IFBLK.
 * character: For S_IFCHR.
 * directory: For S_IFDIR.
 * regular:   For S_IFREG.
 * link:      For S_IFLNK.
 * fifo:      For S_IFIFO.
 * socket:    For S_IFSOCK.
 * unknown:   For anything else.
 */
#ifndef _di_f_directory_listing_t_
  typedef struct {
    f_string_dynamics_t block;     // S_IFBLK
    f_string_dynamics_t character; // S_IFCHR
    f_string_dynamics_t directory; // S_IFDIR
    f_string_dynamics_t regular;   // S_IFREG
    f_string_dynamics_t link;      // S_IFLNK
    f_string_dynamics_t fifo;      // S_IFIFO
    f_string_dynamics_t socket;    // S_IFSOCK
    f_string_dynamics_t unknown;
  } f_directory_listing_t;

  #define f_directory_listing_t_initialize { \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
  }

  #define macro_f_directory_listing_t_initialize_1(block, character, directory, regular, link, fifo, socket, unknown) { \
    block, \
    character, \
    directory, \
    regular, \
    link, \
    fifo, \
    socket, \
    unknown, \
  }
#endif // _di_f_directory_listing_t_

/**
 * An association of a path and a status code.
 *
 * The allocation macros apply to the path.
 *
 * step:   The allocation step.
 * status: The status code.
 * path:   The dynamically allocated path associated with the status code.
 */
#ifndef _di_f_directory_status_t_
  typedef struct {
    f_status_t status;
    f_string_dynamic_t path;
  } f_directory_status_t;

  #define f_directory_status_t_initialize { 0, f_string_dynamic_t_initialize }

  #define macro_f_directory_status_t_initialize_1(status, path) { status, path }

  #define macro_f_directory_status_t_clear(directory) \
    directory.status = 0; \
    macro_f_string_dynamic_t_clear(directory.path);
#endif // _di_f_directory_status_t_

/**
 * An array of directory status.
 *
 * array: An array of directory status.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_directory_statuss_t_
  typedef struct {
    f_directory_status_t *array;
    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_directory_statuss_t;

  #define f_directory_statuss_t_initialize { 0, 0, 0 }

  #define macro_f_directory_statuss_t_initialize_1(content, size, used) { array, size, used }
  #define macro_f_directory_statuss_t_initialize_2(array, length) { array, length, length }

  #define macro_f_directory_statuss_t_clear(structures) macro_f_memory_structures_clear(structures)
#endif // _di_f_directory_statuss_t_

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
 *   - recurse: Must be of type f_directory_recurse_do_t and represents this data.
 *   - name:    The name of the file or directory the action is being performed on (does not have the parent directory path) (may be empty at the top level).
 *   - flag:    A flag representing the particular action being performed.
 *
 * The handle() callback provides a callback identical to the handle() except that it is for handling exceptions in place of state.handle().
 * The handle() provides additional information not provided by state.handle() but if it is NULL, then state.handle() is called.
 * The state.handle() and state.interrupt() callbacks internal parameter must be of type f_directory_recurse_do_t.
 *
 * The callbacks must take care to properly modify the structure or they could cause security, integrity, or functionality problems.
 *
 * depth:     A number representing the depth recursed thus far (generally assigned internally).
 * depth_max: The maximum recursion depth to use.
 * flag:      A set of flags used exclusively by the directory recurse process (not to be confused with state.flag).
 * mode:      A file mode flag to use when working on files, such as when copying a file.
 *
 * state:     A pointer to the state information, where state.interrupt() and state.handle() are called appopriately.
 * listing:   A directory listing structure used internally to help reduce repeated memory allocation overhead.
 *
 * path:       A path representing the current directory path being operated on and usually represents the parent path of some file or directory (generally assigned internally).
 * path_cache: A path-related cache made available for the caller to use, such as combining the path and the file name in the action callback.
 * path_top:   A pointer to the top path string, used for error handling and printing (generally assigned internally).
 *
 * action: A callback used for performing some action (this is required to do anything).
 * handle: A callback used for performing error handling during recursion directly relating to a file.
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
 * Delete all arrays within the listing.
 *
 * @param listing
 *   The listing to fully delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamics_resize().
 *
 * @see f_string_dynamics_resize()
 */
#ifndef _di_f_directory_listing_delete_
  extern f_status_t f_directory_listing_delete(f_directory_listing_t * const listing);
#endif // _di_f_directory_listing_delete_

/**
 * Destroy all arrays within the listing.
 *
 * @param listing
 *   The listing to fully destroy.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamics_adjust().
 *
 * @see f_string_dynamics_adjust()
 */
#ifndef _di_f_directory_listing_destroy_
  extern f_status_t f_directory_listing_destroy(f_directory_listing_t * const listing);
#endif // _di_f_directory_listing_destroy_

/**
 * Delete all non-pointer based dynamic arrays within the recurse.
 *
 * @param recurse
 *   The recurse to fully delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_directory_listing_delete().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_directory_listing_delete()
 * @see f_string_dynamic_resize()
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
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_directory_listing_destroy().
 *   Errors (with error bit) from: f_string_dynamic_adjust().
 *
 * @see f_directory_listing_destroy()
 * @see f_string_dynamic_adjust()
 */
#ifndef _di_f_directory_recurse_do_destroy_
  extern f_status_t f_directory_recurse_do_destroy(f_directory_recurse_do_t * const recurse);
#endif // _di_f_directory_recurse_do_destroy_

/**
 * Resize all parts of the directory statuss structure using the same length.
 *
 * @param length
 *   The new size to use.
 * @param statuss
 *   The statuss structure to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 *   @see f_memory_resize()
 *   @see f_string_dynamic_resize()
 */
#ifndef _di_f_directory_statuss_adjust_
  extern f_status_t f_directory_statuss_adjust(const f_number_unsigned_t length, f_directory_statuss_t * const statuss);
#endif // _di_f_directory_statuss_adjust_

/**
 * Resize all parts of the directory statuss structure to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param statuss
 *   The statuss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 *   @see f_memory_resize()
 *   @see f_string_dynamic_resize()
 */
#ifndef _di_f_directory_statuss_decimate_by_
  extern f_status_t f_directory_statuss_decimate_by(const f_number_unsigned_t amount, f_directory_statuss_t * const statuss);
#endif // _di_f_directory_statuss_decimate_by_

/**
 * Resize all parts of the directory statuss structure to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param statuss
 *   The statuss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 *   @see f_memory_resize()
 *   @see f_string_dynamic_resize()
 */
#ifndef _di_f_directory_statuss_decrease_by_
  extern f_status_t f_directory_statuss_decrease_by(const f_number_unsigned_t amount, f_directory_statuss_t * const statuss);
#endif // _di_f_directory_statuss_decrease_by_

/**
 * Increase the size of all parts of the directory statuss structure, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param statuss
 *   The statuss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 *   @see f_memory_resize()
 *   @see f_string_dynamic_resize()
 */
#ifndef _di_f_directory_statuss_increase_
  extern f_status_t f_directory_statuss_increase(const f_number_unsigned_t step, f_directory_statuss_t * const statuss);
#endif // _di_f_directory_statuss_increase_

/**
 * Resize all parts of the directory statuss structure to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param statuss
 *   The statuss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 *   @see f_memory_resize()
 *   @see f_string_dynamic_resize()
 */
#ifndef _di_f_directory_statuss_increase_by_
  extern f_status_t f_directory_statuss_increase_by(const f_number_unsigned_t amount, f_directory_statuss_t * const statuss);
#endif // _di_f_directory_statuss_increase_by_

/**
 * Resize all parts of the directory statuss structure using the same length.
 *
 * @param length
 *   The new size to use.
 * @param statuss
 *   The directory status array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 *   @see f_memory_resize()
 *   @see f_string_dynamic_resize()
 */
#ifndef _di_f_directory_statuss_resize_
  extern f_status_t f_directory_statuss_resize(const f_number_unsigned_t length, f_directory_statuss_t * const statuss);
#endif // _di_f_directory_statuss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_directory_type_h
