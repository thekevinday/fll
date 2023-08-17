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
#ifndef _F_directory_status_h
#define _F_directory_status_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * An association of a path and a status code.
 *
 * The allocation macros apply to the path.
 *
 * Properties:
 *   - step:   The allocation step.
 *   - status: The status code.
 *   - path:   The dynamically allocated path associated with the status code.
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
 * Properties:
 *   - array: An array of directory status.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
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
 * An array of an array of directory status.
 *
 * Properties:
 *   - array: An array of an array of directory status.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_directory_statusss_t_
  typedef struct {
    f_directory_statuss_t *array;
    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_directory_statusss_t;

  #define f_directory_statusss_t_initialize { 0, 0, 0 }

  #define macro_f_directory_statusss_t_initialize_1(content, size, used) { array, size, used }
  #define macro_f_directory_statusss_t_initialize_2(array, length) { array, length, length }

  #define macro_f_directory_statusss_t_clear(structures) macro_f_memory_structures_clear(structures)
#endif // _di_f_directory_statusss_t_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_directory_statuss_t structure.
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
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_string_dynamic_resize()
 */
#ifndef _di_f_directory_statuss_delete_callback_
  extern f_status_t f_directory_statuss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_directory_statuss_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_directory_statuss_t structure.
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
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_adjust().
 *
 * @see f_string_dynamic_adjust()
 */
#ifndef _di_f_directory_statuss_destroy_callback_
  extern f_status_t f_directory_statuss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_directory_statuss_destroy_callback_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_directory_statusss_t structure.
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
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_string_dynamic_resize()
 */
#ifndef _di_f_directory_statusss_delete_callback_
  extern f_status_t f_directory_statusss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_directory_statusss_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_directory_statusss_t structure.
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
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_adjust().
 *
 * @see f_string_dynamic_adjust()
 */
#ifndef _di_f_directory_statusss_destroy_callback_
  extern f_status_t f_directory_statusss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_directory_statusss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_directory_status_h
