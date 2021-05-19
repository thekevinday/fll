/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines named set data to be used for/by project fss.
 *
 * This is auto-included by fss.h and should not need to be explicitly included.
 */
#ifndef _F_fss_named_h
#define _F_fss_named_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This holds a named set of fss objects, contents, and quotess.
 *
 * The objects, contents, and quotess should each be of the same used and size.
 * Any deviation to this would require implementing custom equivelents to the standard management macros.
 *
 * name:     The name representing this set.
 * objects:  The array of objects.
 * contents: The array of contents.
 * quotess:  The array of quote for each content.
 */
#ifndef _di_f_fss_named_t_
  typedef struct {
    f_fss_object_t name;

    f_fss_objects_t objects;
    f_fss_contents_t contents;
    f_fss_quotess_t quotess;
  } f_fss_named_t;

  #define f_fss_named_t_initialize { f_fss_object_t_initialize, f_fss_objects_t_initialize, f_fss_contents_t_initialize, f_fss_quotess_t_initialize }

  #define macro_f_fss_named_t_clear(named) \
    macro_f_fss_object_t_clear(named.name) \
    macro_f_fss_objects_t_clear(named.objects) \
    macro_f_fss_contents_t_clear(named.contents) \
    macro_f_fss_quotess_t_clear(named.quotess)

  #define macro_f_fss_named_t_resize(status, named, length) status = f_fss_named_resize(length, &named);
  #define macro_f_fss_named_t_adjust(status, named, length) status = f_fss_named_adjust(length, &named);

  #define macro_f_fss_named_t_delete_simple(named)  f_fss_named_resize(0, &named);
  #define macro_f_fss_named_t_destroy_simple(named) f_fss_named_adjust(0, &named);

  #define macro_f_fss_named_t_increase(status, step, named)            status = f_fss_named_increase(step, &named);
  #define macro_f_fss_named_t_increase_by(status, named, amount) status = f_fss_named_increase_by(amount, &named);
  #define macro_f_fss_named_t_decrease_by(status, named, amount) status = f_fss_named_decrease_by(amount, &named);
  #define macro_f_fss_named_t_decimate_by(status, named, amount) status = f_fss_named_decimate_by(amount, &named);
#endif // _di_f_fss_named_t_

/**
 * This holds an array of f_fss_named_t.
 *
 * array: An array of f_fss_named_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_fss_nameds_t_
  typedef struct {
    f_fss_named_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_fss_nameds_t;

  #define f_fss_nameds_t_initialize { 0, 0, 0 }

  #define macro_f_fss_nameds_t_clear(nameds) macro_f_memory_structure_clear(nameds);

  #define macro_f_fss_nameds_t_resize(status, nameds, length) status = f_fss_nameds_resize(length, &nameds);
  #define macro_f_fss_nameds_t_adjust(status, nameds, length) status = f_fss_nameds_adjust(length, &nameds);

  #define macro_f_fss_nameds_t_delete_simple(nameds)  f_fss_nameds_resize(0, &nameds);
  #define macro_f_fss_nameds_t_destroy_simple(nameds) f_fss_nameds_adjust(0, &nameds);

  #define macro_f_fss_nameds_t_increase(status, step, nameds)      status = f_fss_nameds_increase(step, &nameds);
  #define macro_f_fss_nameds_t_increase_by(status, nameds, amount) status = f_fss_nameds_increase_by(amount, &nameds);
  #define macro_f_fss_nameds_t_decrease_by(status, nameds, amount) status = f_fss_nameds_decrease_by(amount, &nameds);
  #define macro_f_fss_nameds_t_decimate_by(status, nameds, amount) status = f_fss_nameds_decimate_by(amount, &nameds);
#endif // _di_fss_nameds_t_

/**
 * Resize all parts of the named structure using the same length.
 *
 * @param length
 *   The new size to use.
 * @param named
 *   The named structure to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_named_adjust_
  extern f_status_t f_fss_named_adjust(const f_array_length_t length, f_fss_named_t *named);
#endif // _di_f_fss_named_adjust_

/**
 * Resize all parts of the named structure to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param named
 *   The named array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_named_decimate_by_
  extern f_status_t f_fss_named_decimate_by(const f_array_length_t amount, f_fss_named_t *named);
#endif // _di_f_fss_named_decimate_by_

/**
 * Resize all parts of the named structure to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param named
 *   The named array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_named_decrease_by_
  extern f_status_t f_fss_named_decrease_by(const f_array_length_t amount, f_fss_named_t *named);
#endif // _di_f_fss_named_decrease_by_

/**
 * Increase the size of all parts of the named structure, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param named
 *   The named array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_named_increase_
  extern f_status_t f_fss_named_increase(const uint16_t step, f_fss_named_t *named);
#endif // _di_f_fss_named_increase_

/**
 * Resize all parts of the named structure to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param named
 *   The named array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_f_fss_named_increase_by_
  extern f_status_t f_fss_named_increase_by(const f_array_length_t amount, f_fss_named_t *named);
#endif // _di_f_fss_named_increase_by_

/**
 * Resize all parts of the named structure using the same length.
 *
 * @param length
 *   The new size to use.
 * @param named
 *   The named structure to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_named_resize_
  extern f_status_t f_fss_named_resize(const f_array_length_t length, f_fss_named_t *named);
#endif // _di_f_fss_named_resize_

/**
 * Resize the named array.
 *
 * @param length
 *   The new size to use.
 * @param nameds
 *   The nameds array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nameds_adjust_
  extern f_status_t f_fss_nameds_adjust(const f_array_length_t length, f_fss_nameds_t *nameds);
#endif // _di_f_fss_nameds_adjust_

/**
 * Resize the named array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param nameds
 *   The nameds array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nameds_decimate_by_
  extern f_status_t f_fss_nameds_decimate_by(const f_array_length_t amount, f_fss_nameds_t *nameds);
#endif // _di_f_fss_nameds_decimate_by_

/**
 * Resize the named array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param nameds
 *   The nameds array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nameds_decrease_by_
  extern f_status_t f_fss_nameds_decrease_by(const f_array_length_t amount, f_fss_nameds_t *nameds);
#endif // _di_f_fss_nameds_decrease_by_

/**
 * Increase the size of the nameds array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param nameds
 *   The nameds array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nameds_increase_
  extern f_status_t f_fss_nameds_increase(const uint16_t step, f_fss_nameds_t *nameds);
#endif // _di_f_fss_nameds_increase_

/**
 * Resize the nameds array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param nameds
 *   The nameds array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_array_too_large (with error bit) if the new array length is too large.
 */
#ifndef _di_f_fss_nameds_increase_by_
  extern f_status_t f_fss_nameds_increase_by(const f_array_length_t amount, f_fss_nameds_t *nameds);
#endif // _di_f_fss_nameds_increase_by_

/**
 * Resize the nameds array.
 *
 * @param length
 *   The new size to use.
 * @param nameds
 *   The nameds array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_fss_nameds_resize_
  extern f_status_t f_fss_nameds_resize(const f_array_length_t length, f_fss_nameds_t *nameds);
#endif // _di_f_fss_nameds_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_named_h
