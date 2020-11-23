/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_entry_h
#define _PRIVATE_entry_h

#include "private-controller.h"

#ifndef _di_controller_entry_cache_t_
  typedef struct {
    f_string_length_t line_item;
    f_string_length_t line_list;

    f_string_range_t range_item;
    f_string_range_t range_list;

    f_fss_comments_t comments;
    f_fss_delimits_t delimits;

    f_fss_content_t content_item;
    f_fss_contents_t contents_items;
    f_fss_contents_t contents_list;
    f_fss_objects_t objects_items;
    f_fss_objects_t objects_list;

    f_string_dynamic_t buffer_entry;

    f_string_static_t name_entry;
    f_string_dynamic_t name_item;
    f_string_dynamic_t name_list;
  } controller_entry_cache_t;

  #define controller_entry_cache_t_initialize \
    { \
      0, \
      0, \
      f_string_range_t_initialize, \
      f_string_range_t_initialize, \
      f_fss_comments_t_initialize, \
      f_fss_delimits_t_initialize, \
      f_fss_content_t_initialize, \
      f_fss_contents_t_initialize, \
      f_fss_contents_t_initialize, \
      f_fss_objects_t_initialize, \
      f_fss_objects_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_static_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
    }

  #define macro_controller_entry_cache_t_delete_simple(cache) \
    f_macro_fss_comments_t_delete_simple(cache.comments) \
    f_macro_fss_delimits_t_delete_simple(cache.delimits) \
    f_macro_fss_content_t_delete_simple(cache.content_action) \
    f_macro_fss_contents_t_delete_simple(cache.contents_action) \
    f_macro_fss_contents_t_delete_simple(cache.contents_items) \
    f_macro_fss_objects_t_delete_simple(cache.objects_action) \
    f_macro_fss_objects_t_delete_simple(cache.objects_items) \
    f_macro_string_dynamic_t_delete_simple(cache.buffer_entry) \
    f_macro_string_dynamic_t_delete_simple(cache.name_item) \
    f_macro_string_dynamic_t_delete_simple(cache.name_list)
#endif // _di_controller_entry_cache_t_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Increase the size of the entry lists array by the specified amount, but only if necessary.
 *
 * This only increases size if the current used plus amount is greater than the currently allocated size.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param lists
 *   The entry lists to resize.
 *
 * @return
 *   F_none on success.
 *   F_array_too_large on success, but requested size is too small (resize is smaller than requested length).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 */
#ifndef _di_controller_entry_lists_increase_by_
  extern f_return_status controller_entry_lists_increase_by(const f_array_length_t amount, controller_entry_lists_t *lists) f_gcc_attribute_visibility_internal;
#endif // _di_controller_entry_lists_increase_by_

/**
 * Read the entry file, extracting all valid entry lists.
 *
 * @param data
 *   The program data.
 * @param setting
 *   The controller settings data.
 * @param entry_name
 *   The string identifying the entry.
 *   This is constructed from the path parts to the file without the file extension and without the settings directory prefix.
 *   "/etc/controller/entries/my.entry" would have a entry name of "my".
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param lists
 *   The processed list.
 *
 * @return
 *   F_none on success.
 *   @todo determine how the error management will be done for both entry and rule (ideally the "controller" should avoid failing if possible given that it is the defacto "init" program).
 */
#ifndef _di_controller_entry_list_read_
  extern f_return_status controller_entry_list_read(const controller_data_t data, const controller_setting_t setting, const f_string_static_t entry_name, controller_entry_cache_t *cache, controller_entry_lists_t *lists) f_gcc_attribute_visibility_internal;
#endif // _di_controller_entry_list_read_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_entry_h
