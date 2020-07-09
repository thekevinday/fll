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
 * This holds a named set of fss objects and contents.
 *
 * The objects and contents should each be of the same used and size.
 * Any deviation to this would require implementing custom equivelents to the standard management macros.
 *
 * object: The name representing this set.
 * objects: The array of objects.
 * contents: The array of contents.
 */
#ifndef _di_f_fss_named_
  typedef struct {
    f_fss_object name;

    f_fss_objects objects;
    f_fss_contents contents;
  } f_fss_named;

  #define f_fss_named_initialize { f_fss_object_initialize, f_fss_objects_initialize, f_fss_contents_initialize }

  #define f_macro_fss_named_clear(set) \
    f_macro_fss_object_clear(set.object) \
    f_macro_fss_objects_clear(set.objects) \
    f_macro_fss_contents_clear(set.contents)

  #define f_macro_fss_named_new(status, set, length) \
    f_macro_fss_objects_new(status, set.objects, length) \
    if (F_status_is_fine(status)) { \
      f_macro_fss_contents_new(status, set.contents, length) \
    }

  #define f_macro_fss_named_delete(status, set) \
    f_macro_fss_objects_delete(status, set.objects) \
    if (F_status_is_fine(status)) { \
      f_macro_fss_contents_delete(status, set.contents) \
    }

  #define f_macro_fss_named_destroy(status, set) \
    f_macro_fss_objects_destroy(status, set.objects) \
    if (F_status_is_fine(status)) { \
      f_macro_fss_contents_destroy(status, set.contents) \
    }

  #define f_macro_fss_named_delete_simple(set) \
    f_macro_fss_objects_delete_simple(set.objects) \
    f_macro_fss_contents_delete_simple(set.contents)

  #define f_macro_fss_named_destroy_simple(set) \
    f_macro_fss_objects_destroy_simple(set.objects) \
    f_macro_fss_contents_destroy_simple(set.contents)

  #define f_macro_fss_named_resize(status, set, new_length) \
    f_macro_fss_objects_resize(status, set.objects, new_length) \
    if (F_status_is_fine(status)) { \
      f_macro_fss_contents_resize(status, set.contents, new_length) \
    }

  #define f_macro_fss_named_adjust(status, set, new_length) \
    f_macro_fss_objects_adjust(status, set.objects, new_length) \
    if (F_status_is_fine(status)) { \
      f_macro_fss_contents_adjust(status, set.contents, new_length) \
    }
#endif // _di_f_fss_named_

/**
 * This holds an array of f_fss_named.
 *
 * array: an array of f_fss_named.
 * size: Total amount of allocated space.
 * used: Total number of allocated spaces used.
 */
#ifndef _di_fss_nameds_
  typedef struct {
    f_fss_named *array;

    f_array_length size;
    f_array_length used;
  } f_fss_nameds;

  #define f_fss_nameds_initialize { 0, 0, 0 }

  /**
   * Reset a fss content sets to 0 (clear all values).
   *
   * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
   *
   * sets: the f_fss_nameds structure to operate on.
   */
  #define f_macro_fss_nameds_clear(sets) \
    sets.array = 0; \
    sets.size = 0; \
    sets.used = 0;

  /**
   * Create a new fss content sets.
   *
   * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
   *
   * status:     the status to return.
   * sets:      the f_fss_nameds structure to operate on.
   * new_length: the new size of the array.
   */
  #define f_macro_fss_nameds_new(status, sets, length) \
    sets.array = 0; \
    sets.size = 0; \
    sets.used = 0; \
    status = f_memory_new((void **) & sets.array, sizeof(f_fss_named), length); \
    if (status == F_none) { \
      sets.size = length; \
      sets.used = 0; \
    }

  /**
   * Delete a fss content sets.
   *
   * status: the status to return.
   * sets:  the f_fss_nameds structure to operate on.
   */
  #define f_macro_fss_nameds_delete(status, sets) \
    status = F_none; \
    sets.used = sets.size; \
    while (sets.used > 0) { \
      sets.used--; \
      f_macro_fss_named_delete(status, sets.array[sets.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_delete((void **) & sets.array, sizeof(f_fss_named), sets.size); \
    if (status == F_none) sets.size = 0;

  /**
   * Destroy a fss content sets.
   *
   * status: the status to return.
   * sets:  the f_fss_nameds structure to operate on.
   */
  #define f_macro_fss_nameds_destroy(status, sets) \
    status = F_none; \
    sets.used = sets.size; \
    while (sets.used > 0) { \
      sets.used--; \
      f_macro_fss_named_destroy(status, sets.array[sets.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_destroy((void **) & sets.array, sizeof(f_fss_named), sets.size); \
    if (status == F_none) sets.size = 0;

  /**
   * Delete a fss content sets.
   *
   * sets: the f_fss_nameds structure to operate on.
   */
  #define f_macro_fss_nameds_delete_simple(sets) \
    sets.used = sets.size; \
    while (sets.used > 0) { \
      sets.used--; \
      f_macro_fss_named_delete_simple(sets.array[sets.used]); \
      if (sets.used == 0) { \
        if (f_memory_delete((void **) & sets.array, sizeof(f_fss_named), sets.size)) { \
          sets.size = 0; \
        } \
      } \
    }

  /**
   * Destroy a fss content sets.
   *
   * sets: the f_fss_nameds structure to operate on.
   */
  #define f_macro_fss_nameds_destroy_simple(sets) \
    sets.used = sets.size; \
    while (sets.used > 0) { \
      sets.used--; \
      f_macro_fss_named_destroy_simple(sets.array[sets.used]); \
      if (sets.used == 0) { \
        if (f_memory_destroy((void **) & sets.array, sizeof(f_fss_named), sets.size)) { \
          sets.size = 0; \
        } \
      } \
    }

  /**
   * Resize a fss content sets.
   *
   * status:     the status to return.
   * sets:      the f_fss_nameds structure to operate on.
   * new_length: the new size of the array.
   */
  #define f_macro_fss_nameds_resize(status, sets, new_length) \
    status = F_none; \
    if (new_length < sets.size) { \
      for (f_array_length _macro__i = sets.size - new_length; _macro__i < sets.size; _macro__i++) { \
        f_macro_fss_named_delete(status, sets.array[_macro__i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & sets.array, sizeof(f_fss_named), sets.size, new_length); \
    if (status == F_none) { \
      if (new_length > sets.size) { \
        for (f_array_length _macro__i = sets.size; _macro__i < new_length; _macro__i++) { \
          memset(&sets.array[_macro__i], 0, sizeof(f_fss_named)); \
        } \
      } \
      sets.size = new_length; \
      if (sets.used > sets.size) sets.used = new_length; \
    }

  /**
   * Adjust a fss content sets.
   *
   * status:     the status to return.
   * sets:      the f_fss_nameds structure to operate on.
   * new_length: he new size of the array.
   */
  #define f_macro_fss_nameds_adjust(status, sets, new_length) \
    status = F_none; \
    if (new_length < sets.size) { \
      for (f_array_length _macro__i = sets.size - new_length; _macro__i < sets.size; _macro__i++) { \
        f_macro_fss_named_destroy(status, sets.array[_macro__i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & sets.array, sizeof(f_fss_named), sets.size, new_length); \
    if (status == F_none) { \
      if (new_length > sets.size) { \
        for (f_array_length _macro__i = sets.size; _macro__i < new_length; _macro__i++) { \
          memset(&sets.array[_macro__i], 0, sizeof(f_fss_named)); \
        } \
      } \
      sets.size = new_length; \
      if (sets.used > sets.size) sets.used = new_length; \
    }
#endif // _di_fss_nameds_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_named_h
