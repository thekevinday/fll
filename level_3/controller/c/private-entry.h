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
    f_string_length_t line_action;
    f_string_length_t line_list;

    f_string_range_t range_list;

    f_fss_comments_t comments;
    f_fss_delimits_t delimits;

    f_fss_content_t content_action;
    f_fss_contents_t content_actions;
    f_fss_contents_t content_items;
    f_fss_objects_t object_actions;
    f_fss_objects_t object_items;

    f_string_dynamic_t buffer_file;
    f_string_dynamic_t buffer_item;

    f_string_dynamic_t name_action;
    f_string_dynamic_t name_file;
    f_string_dynamic_t name_item;
  } controller_entry_cache_t;

  #define controller_entry_cache_t_initialize \
    { \
      0, \
      0, \
      f_string_range_t_initialize, \
      f_fss_comments_t_initialize, \
      f_fss_delimits_t_initialize, \
      f_fss_content_t_initialize, \
      f_fss_contents_t_initialize, \
      f_fss_contents_t_initialize, \
      f_fss_objects_t_initialize, \
      f_fss_objects_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
    }

  #define macro_controller_entry_cache_t_delete_simple(cache) \
    f_macro_fss_comments_t_delete_simple(cache.comments) \
    f_macro_fss_delimits_t_delete_simple(cache.delimits) \
    f_macro_fss_content_t_delete_simple(cache.content_action) \
    f_macro_fss_contents_t_delete_simple(cache.content_actions) \
    f_macro_fss_contents_t_delete_simple(cache.content_items) \
    f_macro_fss_objects_t_delete_simple(cache.object_actions) \
    f_macro_fss_objects_t_delete_simple(cache.object_items) \
    f_macro_string_dynamic_t_delete_simple(cache.buffer_file) \
    f_macro_string_dynamic_t_delete_simple(cache.buffer_item) \
    f_macro_string_dynamic_t_delete_simple(cache.name_action) \
    f_macro_string_dynamic_t_delete_simple(cache.name_file) \
    f_macro_string_dynamic_t_delete_simple(cache.name_item)
#endif // _di_controller_entry_cache_t_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Increase the size of the entry item actions array by the specified amount, but only if necessary.
 *
 * This only increases size if the current used plus amount is greater than the currently allocated size.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param actions
 *   The entry item actions to resize.
 *
 * @return
 *   F_none on success.
 *   F_array_too_large on success, but requested size is too small (resize is smaller than requested length).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 */
#ifndef _di_controller_entry_actions_increase_by_
  extern f_return_status controller_entry_actions_increase_by(const f_array_length_t amount, controller_entry_actions_t *actions) f_gcc_attribute_visibility_internal;
#endif // _di_controller_entry_actions_increase_by_

/**
 * Read the entry list, extracting all items and values.
 *
 * @param data
 *   The program data.
 * @param setting
 *   The controller settings data.
 * @param content_range
 *   The range in the list buffer representing the content.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param list
 *   The processed list.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_controller_entry_actions_read_
  extern f_return_status controller_entry_actions_read(const controller_data_t data, const controller_setting_t setting, const f_string_range_t content_range, controller_entry_cache_t *cache, controller_entry_actions_t *items) f_gcc_attribute_visibility_internal;
#endif // _di_controller_entry_actions_read_

/**
 * Print additional error/warning information in addition to existing error.
 *
 * This is explicitly intended to be used in addition to the error message.
 *
 * @param output
 *   The error or warning output structure.
 * @param cache
 *   A structure for containing and caching relevant data.
 *
 * @see controller_entry_actions_read()
 * @see controller_entry_read()
 */
#ifndef _di_controller_entry_error_print_
  extern void controller_entry_error_print(const fll_error_print_t output, const controller_entry_cache_t cache) f_gcc_attribute_visibility_internal;
#endif // _di_controller_entry_error_print_

/**
 * Increase the size of the entry items array by the specified amount, but only if necessary.
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
#ifndef _di_controller_entry_items_increase_by_
  extern f_return_status controller_entry_items_increase_by(const f_array_length_t amount, controller_entry_items_t *lists) f_gcc_attribute_visibility_internal;
#endif // _di_controller_entry_items_increase_by_

/**
 * Read the entry, extracting all lists.
 *
 * @param data
 *   The program data.
 * @param setting
 *   The controller settings data.
 * @param entry_name
 *   The string identifying the entry.
 *   This is constructed from the path parts to the file without the file extension and without the settings directory prefix.
 *   "/etc/controller/entries/example/my.entry" would have a rule id of "example/my".
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param entry
 *   The processed entry.
 *
 * @return
 *   F_true on success.
 *   F_false on failure.
 */
#ifndef _di_controller_entry_read_
  extern f_return_status controller_entry_read(const controller_data_t data, const controller_setting_t setting, const f_string_static_t entry_name, controller_entry_cache_t *cache, controller_entry_t *entry) f_gcc_attribute_visibility_internal;
#endif // _di_controller_entry_read_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_entry_h
