/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines set data to be used for/by project fss.
 *
 * This is auto-included by fss.h and should not need to be explicitly included.
 */
#ifndef _F_fss_set_h
#define _F_fss_set_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This holds an fss object with a set of fss content.
 *
 * The objects and contents should each be of the same used and size.
 * Any deviation to this would require implementing custom equivelents to the standard management macros.
 *
 * objects:  the array of objects.
 * contents: the array of contents.
 */
#ifndef _di_f_fss_set_t_
  typedef struct {
    f_fss_objects_t objects;
    f_fss_contents_t contents;
  } f_fss_set_t;

  #define f_fss_set_t_initialize { f_fss_objects_t_initialize, f_fss_contents_t_initialize }

  #define f_macro_fss_set_t_clear(set) \
    f_macro_fss_objects_t_clear(set.objects) \
    f_macro_fss_contents_t_clear(set.contents)

  #define f_macro_fss_set_t_new(status, set, length) \
    f_macro_fss_objects_t_new(status, set.objects, length) \
    if (F_status_is_fine(status)) { \
      f_macro_fss_contents_t_new(status, set.contents, length) \
    }

  #define f_macro_fss_set_t_delete(status, set) \
    f_macro_fss_objects_t_delete(status, set.objects) \
    if (F_status_is_fine(status)) { \
      f_macro_fss_contents_t_delete(status, set.contents) \
    }

  #define f_macro_fss_set_t_destroy(status, set) \
    f_macro_fss_objects_t_destroy(status, set.objects) \
    if (F_status_is_fine(status)) { \
      f_macro_fss_contents_t_destroy(status, set.contents) \
    }

  #define f_macro_fss_set_t_delete_simple(set) \
    f_macro_fss_objects_t_delete_simple(set.objects) \
    f_macro_fss_contents_t_delete_simple(set.contents)

  #define f_macro_fss_set_t_destroy_simple(set) \
    f_macro_fss_objects_t_destroy_simple(set.objects) \
    f_macro_fss_contents_t_destroy_simple(set.contents)

  #define f_macro_fss_set_t_resize(status, set, new_length) \
    f_macro_fss_objects_t_resize(status, set.objects, new_length) \
    if (F_status_is_fine(status)) { \
      f_macro_fss_contents_t_resize(status, set.contents, new_length) \
    }

  #define f_macro_fss_set_t_adjust(status, set, new_length) \
    f_macro_fss_objects_t_resize(status, set.objects, new_length) \
    if (F_status_is_fine(status)) { \
      f_macro_fss_contents_t_resize(status, set.contents, new_length) \
    }
#endif // _di_f_fss_set_t_

/**
 * This holds an array of f_fss_set_t.
 *
 * array: an array of f_fss_set_t.
 * size:  total amount of allocated space.
 * used:  total number of allocated spaces used.
 */
#ifndef _di_f_fss_sets_t_
  typedef struct {
    f_fss_set_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_fss_sets_t;

  #define f_fss_sets_t_initialize { 0, 0, 0 }

  /**
   * Reset a fss content sets to 0 (clear all values).
   *
   * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
   *
   * sets: the f_fss_sets_t structure to operate on.
   */
  #define f_macro_fss_sets_t_clear(sets) \
    sets.array = 0; \
    sets.size = 0; \
    sets.used = 0;

  /**
   * Create a new fss content sets.
   *
   * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
   *
   * status:     the status to return.
   * sets:       the f_fss_sets_t structure to operate on.
   * new_length: the new size of the array.
   */
  #define f_macro_fss_sets_t_new(status, sets, length) \
    sets.array = 0; \
    sets.size = 0; \
    sets.used = 0; \
    status = f_memory_new((void **) & sets.array, sizeof(f_fss_set_t), length); \
    if (status == F_none) { \
      sets.size = length; \
      sets.used = 0; \
    }

  /**
   * Delete a fss content sets.
   *
   * status: the status to return.
   * sets:   the f_fss_sets_t structure to operate on.
   */
  #define f_macro_fss_sets_t_delete(status, sets) \
    status = F_none; \
    sets.used = sets.size; \
    while (sets.used > 0) { \
      sets.used--; \
      f_macro_fss_set_t_delete(status, sets.array[sets.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_delete((void **) & sets.array, sizeof(f_fss_set_t), sets.size); \
    if (status == F_none) sets.size = 0;

  /**
   * Destroy a fss content sets.
   *
   * status: the status to return.
   * sets:   the f_fss_sets_t structure to operate on.
   */
  #define f_macro_fss_sets_t_destroy(status, sets) \
    status = F_none; \
    sets.used = sets.size; \
    while (sets.used > 0) { \
      sets.used--; \
      f_macro_fss_set_t_destroy(status, sets.array[sets.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_destroy((void **) & sets.array, sizeof(f_fss_set_t), sets.size); \
    if (status == F_none) sets.size = 0;

  /**
   * Delete a fss content sets.
   *
   * sets: the f_fss_sets_t structure to operate on.
   */
  #define f_macro_fss_sets_t_delete_simple(sets) \
    sets.used = sets.size; \
    while (sets.used > 0) { \
      sets.used--; \
      f_macro_fss_set_t_delete_simple(sets.array[sets.used]); \
      if (!sets.used) { \
        if (f_memory_delete((void **) & sets.array, sizeof(f_fss_set_t), sets.size)) { \
          sets.size = 0; \
        } \
      } \
    }

  /**
   * Destroy a fss content sets.
   *
   * sets: the f_fss_sets_t structure to operate on.
   */
  #define f_macro_fss_sets_t_destroy_simple(sets) \
    sets.used = sets.size; \
    while (sets.used > 0) { \
      sets.used--; \
      f_macro_fss_set_t_destroy_simple(sets.array[sets.used]); \
      if (!sets.used) { \
        if (f_memory_destroy((void **) & sets.array, sizeof(f_fss_set_t), sets.size)) { \
          sets.size = 0; \
        } \
      } \
    }

  /**
   * Resize a fss content sets.
   *
   * status:     the status to return.
   * sets:       the f_fss_sets_t structure to operate on.
   * new_length: the new size of the array.
   */
  #define f_macro_fss_sets_t_resize(status, sets, new_length) \
    status = F_none; \
    if (new_length < sets.size) { \
      for (f_array_length_t _macro__i = sets.size - new_length; _macro__i < sets.size; _macro__i++) { \
        f_macro_fss_set_t_delete(status, sets.array[_macro__i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & sets.array, sizeof(f_fss_set_t), sets.size, new_length); \
    if (status == F_none) { \
      if (new_length > sets.size) { \
        for (f_array_length_t _macro__i = sets.size; _macro__i < new_length; _macro__i++) { \
          memset(&sets.array[_macro__i], 0, sizeof(f_fss_set_t)); \
        } \
      } \
      sets.size = new_length; \
      if (sets.used > sets.size) sets.used = new_length; \
    }

  /**
   * Adjust a fss content sets.
   *
   * status:     the status to return.
   * sets:       the f_fss_sets_t structure to operate on.
   * new_length: he new size of the array.
   */
  #define f_macro_fss_sets_t_adjust(status, sets, new_length) \
    status = F_none; \
    if (new_length < sets.size) { \
      for (f_array_length_t _macro__i = sets.size - new_length; _macro__i < sets.size; _macro__i++) { \
        f_macro_fss_set_t_destroy(status, sets.array[_macro__i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & sets.array, sizeof(f_fss_set_t), sets.size, new_length); \
    if (status == F_none) { \
      if (new_length > sets.size) { \
        for (f_array_length_t _macro__i = sets.size; _macro__i < new_length; _macro__i++) { \
          memset(&sets.array[_macro__i], 0, sizeof(f_fss_set_t)); \
        } \
      } \
      sets.size = new_length; \
      if (sets.used > sets.size) sets.used = new_length; \
    }
#endif // _di_f_fss_sets_t_

/**
 * This holds an fss object with a set of fss content, along with their quoted types.
 *
 * The objects, contents, and quoteds should each be of the same used and size.
 * Any deviation to this would require implementing custom equivelents to the standard management macros.
 *
 * objects:         the array of objects.
 * contents:        the array of contents.
 * objects_quoted:  the array of objects quoted types.
 * contents_quoted: the array of contents quoted types.
 */
#ifndef _di_f_fss_set_quoted_t_
  typedef struct {
    f_fss_objects_t objects;
    f_fss_contents_t contents;

    f_fss_quoteds_t objects_quoted;
    f_fss_quotedss_t contents_quoted;
  } f_fss_set_quoted_t;

  #define f_fss_set_quoted_t_initialize { f_fss_objects_t_initialize, f_fss_contents_t_initialize, f_fss_quoteds_t_initialize, f_fss_quotedss_t_initialize }

  #define f_macro_fss_set_quoted_t_clear(set) \
    f_macro_fss_objects_t_clear(set.objects) \
    f_macro_fss_contents_t_clear(set.contents) \
    f_macro_fss_quoteds_t_clear(set.objects_quoted) \
    f_macro_fss_quotedss_t_clear(set.contents_quoted)

  #define f_macro_fss_set_quoted_t_new(status, set, length) \
    f_macro_fss_objects_t_new(status, set.objects, length) \
    if (F_status_is_fine(status)) { \
      f_macro_fss_contents_t_new(status, set.contents, length) \
    } \
    if (F_status_is_fine(status)) { \
      f_macro_fss_quoteds_t_new(status, set.objects_quoted, length) \
    } \
    if (F_status_is_fine(status)) { \
      f_macro_fss_quotedss_t_new(status, set.contents_quoted, length) \
    }

  #define f_macro_fss_set_quoted_t_delete(status, set) \
    f_macro_fss_objects_t_delete(status, set.objects) \
    if (F_status_is_fine(status)) { \
      f_macro_fss_contents_t_delete(status, set.contents) \
    } \
    if (F_status_is_fine(status)) { \
      f_macro_fss_quoteds_t_delete(status, set.objects_quoted) \
    } \
    if (F_status_is_fine(status)) { \
      f_macro_fss_quotedss_t_delete(status, set.contents_quoted) \
    }

  #define f_macro_fss_set_quoted_t_destroy(status, set) \
    f_macro_fss_objects_t_destroy(status, set.objects) \
    if (F_status_is_fine(status)) { \
      f_macro_fss_contents_t_destroy(status, set.contents) \
    } \
    if (F_status_is_fine(status)) { \
      f_macro_fss_quoteds_t_destroy(status, set.objects_quoted) \
    } \
    if (F_status_is_fine(status)) { \
      f_macro_fss_quotedss_t_destroy(status, set.contents_quoted) \
    }

  #define f_macro_fss_set_quoted_t_delete_simple(set) \
    f_macro_fss_objects_t_delete_simple(set.objects) \
    f_macro_fss_contents_t_delete_simple(set.contents) \
    f_macro_fss_quoteds_t_delete_simple(set.objects_quoted) \
    f_macro_fss_quotedss_t_delete_simple(set.contents_quoted)

  #define f_macro_fss_set_quoted_t_destroy_simple(set) \
    f_macro_fss_objects_t_destroy_simple(set.objects) \
    f_macro_fss_contents_t_destroy_simple(set.contents) \
    f_macro_fss_quoteds_t_destroy_simple(set.objects_quoted) \
    f_macro_fss_quotedss_t_destroy_simple(set.contents_quoted)

  #define f_macro_fss_set_quoted_t_resize(status, set, new_length) \
    f_macro_fss_objects_t_resize(status, set.objects, new_length) \
    if (F_status_is_fine(status)) { \
      f_macro_fss_contents_t_resize(status, set.contents, new_length) \
    } \
    if (F_status_is_fine(status)) { \
      f_macro_fss_quoteds_t_resize(status, set.objects_quoted, new_length) \
    } \
    if (F_status_is_fine(status)) { \
      f_macro_fss_quotedss_t_resize(status, set.contents_quoted, new_length) \
    }

  #define f_macro_fss_set_quoted_t_adjust(status, set, new_length) \
    f_macro_fss_objects_t_adjust(status, set.objects, new_length) \
    if (F_status_is_fine(status)) { \
      f_macro_fss_contents_t_adjust(status, set.contents, new_length) \
    } \
    if (F_status_is_fine(status)) { \
      f_macro_fss_quoteds_t_adjust(status, set.objects_quoted, new_length) \
    } \
    if (F_status_is_fine(status)) { \
      f_macro_fss_quotedss_t_adjust(status, set.contents_quoted, new_length) \
    }
#endif // _di_f_fss_set_quoted_t_

/**
 * This holds an array of f_fss_set_quoted_t.
 *
 * array: an array of f_fss_set_quoted_t.
 * size:  total amount of allocated space.
 * used:  total number of allocated spaces used.
 */
#ifndef _di_fss_set_quoteds_t_
  typedef struct {
    f_fss_set_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_fss_set_quoteds_t;

  #define f_fss_set_quoteds_t_initialize { 0, 0, 0 }

  /**
   * Reset a fss content sets to 0 (clear all values).
   *
   * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
   *
   * sets: the f_fss_set_quoteds_t structure to operate on.
   */
  #define f_macro_fss_set_quoteds_t_clear(sets) \
    sets.array = 0; \
    sets.size = 0; \
    sets.used = 0;

  /**
   * Create a new fss content sets.
   *
   * This does not deallocate memory, be certain that memory is not allocated before calling this to avoid potential memory leaks.
   *
   * status:     the status to return.
   * sets:       the f_fss_set_quoteds_t structure to operate on.
   * new_length: the new size of the array.
   */
  #define f_macro_fss_set_quoteds_t_new(status, sets, length) \
    sets.array = 0; \
    sets.size = 0; \
    sets.used = 0; \
    status = f_memory_new((void **) & sets.array, sizeof(f_fss_set_quoted_t), length); \
    if (status == F_none) { \
      sets.size = length; \
      sets.used = 0; \
    }

  /**
   * Delete a fss content sets.
   *
   * status: the status to return.
   * sets:   the f_fss_set_quoteds_t structure to operate on.
   */
  #define f_macro_fss_set_quoteds_t_delete(status, sets) \
    status = F_none; \
    sets.used = sets.size; \
    while (sets.used > 0) { \
      sets.used--; \
      f_macro_fss_set_quoted_t_delete(status, sets.array[sets.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_delete((void **) & sets.array, sizeof(f_fss_set_quoted_t), sets.size); \
    if (status == F_none) sets.size = 0;

  /**
   * Destroy a fss content sets.
   *
   * status: the status to return.
   * sets:   the f_fss_set_quoteds_t structure to operate on.
   */
  #define f_macro_fss_set_quoteds_t_destroy(status, sets) \
    status = F_none; \
    sets.used = sets.size; \
    while (sets.used > 0) { \
      sets.used--; \
      f_macro_fss_set_quoted_t_destroy(status, sets.array[sets.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) status = f_memory_destroy((void **) & sets.array, sizeof(f_fss_set_quoted_t), sets.size); \
    if (status == F_none) sets.size = 0;

  /**
   * Delete a fss content sets.
   *
   * sets: the f_fss_set_quoteds_t structure to operate on.
   */
  #define f_macro_fss_set_quoteds_t_delete_simple(sets) \
    sets.used = sets.size; \
    while (sets.used > 0) { \
      sets.used--; \
      f_macro_fss_set_quoted_t_delete_simple(sets.array[sets.used]); \
      if (!sets.used) { \
        if (f_memory_delete((void **) & sets.array, sizeof(f_fss_set_quoted_t), sets.size)) { \
          sets.size = 0; \
        } \
      } \
    }

  /**
   * Destroy a fss content sets.
   *
   * sets: the f_fss_set_quoteds_t structure to operate on.
   */
  #define f_macro_fss_set_quoteds_t_destroy_simple(sets) \
    sets.used = sets.size; \
    while (sets.used > 0) { \
      sets.used--; \
      f_macro_fss_set_quoted_t_destroy_simple(sets.array[sets.used]); \
      if (!sets.used) { \
        if (f_memory_destroy((void **) & sets.array, sizeof(f_fss_set_quoted_t), sets.size)) { \
          sets.size = 0; \
        } \
      } \
    }

  /**
   * Resize a fss content sets.
   *
   * status:     the status to return.
   * sets:       the f_fss_set_quoteds_t structure to operate on.
   * new_length: the new size of the array.
   */
  #define f_macro_fss_set_quoteds_t_resize(status, sets, new_length) \
    status = F_none; \
    if (new_length < sets.size) { \
      for (f_array_length_t _macro__i = sets.size - new_length; _macro__i < sets.size; _macro__i++) { \
        f_macro_fss_set_quoted_t_delete(status, sets.array[_macro__i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & sets.array, sizeof(f_fss_set_quoted_t), sets.size, new_length); \
    if (status == F_none) { \
      if (new_length > sets.size) { \
        for (f_array_length_t _macro__i = sets.size; _macro__i < new_length; _macro__i++) { \
          memset(&sets.array[_macro__i], 0, sizeof(f_fss_set_quoted_t)); \
        } \
      } \
      sets.size = new_length; \
      if (sets.used > sets.size) sets.used = new_length; \
    }

  /**
   * Adjust a fss content sets.
   *
   * status:     the status to return.
   * sets:       the f_fss_set_quoteds_t structure to operate on.
   * new_length: he new size of the array.
   */
  #define f_macro_fss_set_quoteds_t_adjust(status, sets, new_length) \
    status = F_none; \
    if (new_length < sets.size) { \
      for (f_array_length_t _macro__i = sets.size - new_length; _macro__i < sets.size; _macro__i++) { \
        f_macro_fss_set_quoted_t_destroy(status, sets.array[_macro__i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & sets.array, sizeof(f_fss_set_quoted_t), sets.size, new_length); \
    if (status == F_none) { \
      if (new_length > sets.size) { \
        for (f_array_length_t _macro__i = sets.size; _macro__i < new_length; _macro__i++) { \
          memset(&sets.array[_macro__i], 0, sizeof(f_fss_set_quoted_t)); \
        } \
      } \
      sets.size = new_length; \
      if (sets.used > sets.size) sets.used = new_length; \
    }
#endif // _di_fss_set_quoteds_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_set_h
