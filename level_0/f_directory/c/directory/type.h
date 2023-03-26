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

  #define macro_f_directory_listing_t_initialize(block, character, directory, regular, link, fifo, socket, unknown) { \
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
    f_array_length_t size;
    f_array_length_t used;
  } f_directory_statuss_t;

  #define f_directory_statuss_t_initialize { 0, 0, 0 }

  #define macro_f_directory_statuss_t_initialize_1(content, size, used) { array, size, used }
  #define macro_f_directory_statuss_t_initialize_2(array, length) { array, length, length }

  #define macro_f_directory_statuss_t_clear(structures) macro_f_memory_structures_clear(structures)
#endif // _di_f_directory_statuss_t_

/**
 * A structure containing directory recursion information for copy or clone operations.
 *
 * The flag is processed as follows (using f_file_stat_flags_*_e):
 *   - f_file_stat_flag_exclusive_e:
 *     - If set, fail when file already exists.
 *     - If not set, do not fail if file already exists (existing file will be replaced).
 *   - f_file_stat_flag_reference_e:
 *     - If set, operate directly on a link rather than what it references.
 *     - If not set, dereference any links.
 *
 * For clone operations:
 *   - f_file_stat_flag_group_e:
 *     - If set, copy the group ids.
 *     - If not set, do not copy the group ids.
 *   - f_file_stat_flag_owner_e:
 *     - If set, copy the owner ids.
 *     - If not set, do not copy the owner ids.
 *
 *   (For a clone operation, the file mode is always copied.)
 *
 * The verbose() callbacks provide full access to this f_directory_recurse_copy_t structure.
 * These callbacks must take care to properly modify the structure or they could cause security, integrity, or functionality problems.
 *
 * flag:            A set of flags used exclusively by the directory recurse process (not to be confused with state.flag).
 * max_depth:       The maximum recursion depth to use.
 * size_block:      The default number of chunks to read at a time with each chunk being 1-byte (Must be greater than 0).
 * depth:           A number representing the depth recursed thus far (generally assigned internally).
 * mode:            A pointer to the mode, used for error handling and printing (generally assigned internally).
 * state:           A pointer to the state information.
 * listing:         A directory listing structure used internally to help reduce repeated memory allocation overhead.
 * source:          A pointer to the source string, used for error handling and printing (generally assigned internally).
 * source_top:      A pointer to the top source string, used for error handling and printing (generally assigned internally).
 * destination:     A pointer to the destination string, used for error handling and printing (generally assigned internally).
 * destination_top: A pointer to the top destination string, used for error handling and printing (generally assigned internally).
 * verbose:         A callback used for printing verbose messages (Set to NULL to not use).
 *
 * The macro_f_directory_recurse_copy_t_initialize_1() all arguments.
 * The macro_f_directory_recurse_copy_t_initialize_2() all arguments except for internally managed source, destination, mode, and depth.
 */
#ifndef _di_f_directory_recurse_copy_t_
  typedef struct {
    f_number_unsigned_t max_depth;
    f_number_unsigned_t size_block;
    uint8_t flag;
    f_array_length_t depth;

    f_mode_t mode;
    f_state_t state;
    f_directory_listing_t listing;

    const f_string_static_t *source;
    const f_string_static_t *source_top;
    const f_string_static_t *destination;
    const f_string_static_t *destination_top;

    void (*verbose)(const f_string_static_t source, const f_string_static_t destination, void * const recurse);
  } f_directory_recurse_copy_t;

  #define f_directory_recurse_copy_t_initialize { \
    F_directory_max_recurse_depth_d, \
    F_file_default_read_size_d, \
    F_file_flag_write_only_d, \
    0, \
    f_mode_t_initialize, \
    f_state_t_initialize, \
    f_directory_listing_t_initialize, \
    0, \
    0, \
    0, \
    0, \
    0, \
  }

  #define macro_f_directory_recurse_copy_t_initialize_1(max_depth, size_block, flag, depth, mode, state, listing, source, source_top, destination, destination_top, verbose) { \
    max_depth, \
    size_block, \
    flag, \
    depth, \
    mode, \
    state, \
    listing, \
    source, \
    source_top, \
    destination, \
    destination_top, \
    verbose, \
  }

  #define macro_f_directory_recurse_copy_t_initialize_2(max_depth, size_block, flag, depth, mode, state, verbose) { \
    max_depth, \
    size_block, \
    flag, \
    depth,\
    mode, \
    state, \
    f_directory_listing_t_initialize, \
    0, \
    0, \
    0, \
    0, \
    verbose, \
  }
#endif // _di_f_directory_recurse_copy_t_

/**
 * A structure containing directory recursion information.
 *
 * The action() callbacks provide full access to this f_directory_recurse_do_t structure.
 * The callback must take care to properly modify the structure or they could cause security, integrity, or functionality problems.
 * The action callback may set any of the following on the state.status to have the following effects:
 *   - Any status (with error bit set): Immediately return as error.
 *   - F_break: Break out of the current loop.
 *   - F_continue: Skip to the next iteration in the current loop.
 *   - F_done: immedately return as success but do nothing else in this recursion.
 *
 * max_depth: The maximum recursion depth to use.
 * depth:     A number representing the depth recursed thus far (generally assigned internally).
 * flag:      A set of flags used exclusively by the directory recurse process (not to be confused with state.flag).
 * state:     A pointer to the state information.
 * listing:   A directory listing structure used internally to help reduce repeated memory allocation overhead.
 * path:      A pointer to the current path string, used for error handling and printing (generally assigned internally).
 * path_top:  A pointer to the top path string, used for error handling and printing (generally assigned internally).
 * action:    A callback used for performing some action (this is required to do anything).
 *
 * The macro_f_directory_recurse_do_t_initialize_1() all arguments.
 * The macro_f_directory_recurse_do_t_initialize_2() all arguments except for internally managed source, destination, mode, and depth.
 */
#ifndef _di_f_directory_recurse_do_t_
  typedef struct {
    f_number_unsigned_t max_depth;
    f_array_length_t depth;
    uint8_t flag;

    f_state_t state;
    f_directory_listing_t listing;

    const f_string_static_t *path;
    const f_string_static_t *path_top;

    void (*action)(void * const recurse, const uint16_t flag);
  } f_directory_recurse_do_t;

  #define f_directory_recurse_do_t_initialize { \
    F_directory_max_recurse_depth_d, \
    0, \
    f_directory_recurse_do_flag_none_e, \
    f_state_t_initialize, \
    f_directory_listing_t_initialize, \
    0, \
    0, \
    0, \
  }

  #define macro_f_directory_recurse_do_t_initialize_1(max_depth, depth, flag, state, listing, path, path_top, action) { \
    max_depth, \
    depth, \
    flag, \
    state, \
    listing, \
    path, \
    path_top, \
    action, \
  }

  #define macro_f_directory_recurse_do_t_initialize_2(max_depth, depth, flag, state, action) { \
    max_depth, \
    depth,\
    flag, \
    state, \
    f_directory_listing_t_initialize, \
    0, \
    0, \
    action, \
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
 *   Errors (with error bit) from: f_string_dynamics_resize().
 *
 * @see f_string_dynamics_resize()
 */
#ifndef _di_f_directory_recurse_copy_delete_
  extern f_status_t f_directory_recurse_copy_delete(f_directory_recurse_copy_t * const recurse);
#endif // _di_f_directory_recurse_copy_delete_

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
 *   Errors (with error bit) from: f_string_dynamics_adjust().
 *
 * @see f_string_dynamics_adjust()
 */
#ifndef _di_f_directory_recurse_copy_destroy_
  extern f_status_t f_directory_recurse_copy_destroy(f_directory_recurse_copy_t * const recurse);
#endif // _di_f_directory_recurse_copy_destroy_

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
 *   Errors (with error bit) from: f_string_dynamics_resize().
 *
 * @see f_string_dynamics_resize()
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
 *   Errors (with error bit) from: f_string_dynamics_adjust().
 *
 * @see f_string_dynamics_adjust()
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_directory_statuss_adjust_
  extern f_status_t f_directory_statuss_adjust(const f_array_length_t length, f_directory_statuss_t * const statuss);
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_directory_statuss_decimate_by_
  extern f_status_t f_directory_statuss_decimate_by(const f_array_length_t amount, f_directory_statuss_t * const statuss);
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_directory_statuss_decrease_by_
  extern f_status_t f_directory_statuss_decrease_by(const f_array_length_t amount, f_directory_statuss_t * const statuss);
#endif // _di_f_directory_statuss_decrease_by_

/**
 * Increase the size of all parts of the directory statuss structure, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
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
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_directory_statuss_increase_
  extern f_status_t f_directory_statuss_increase(const f_array_length_t step, f_directory_statuss_t * const statuss);
#endif // _di_f_directory_statuss_increase_

/**
 * Resize all parts of the directory statuss structure to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_f_directory_statuss_increase_by_
  extern f_status_t f_directory_statuss_increase_by(const f_array_length_t amount, f_directory_statuss_t * const statuss);
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
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_directory_statuss_resize_
  extern f_status_t f_directory_statuss_resize(const f_array_length_t length, f_directory_statuss_t * const statuss);
#endif // _di_f_directory_statuss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_directory_type_h
