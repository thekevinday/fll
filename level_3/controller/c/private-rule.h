/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_rule_h
#define _PRIVATE_rule_h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_rule_cache_t_
  typedef struct {
    f_string_length_t line_item;
    f_string_length_t line_action;

    f_string_range_t range_item;
    f_string_range_t range_action;

    f_string_dynamic_t name_file;
    f_string_dynamic_t name_item;
    f_string_dynamic_t name_action
  } controller_rule_cache_t;

  #define controller_rule_cache_t_initialize \
    { \
      0, \
      0, \
      0, \
      0, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
    }

  #define f_macro_controller_rule_name_t_delete_simple(cache) \
    f_string_dynamic_t_delete_simple(cache.name_file) \
    f_string_dynamic_t_delete_simple(cache.name_item) \
    f_string_dynamic_t_delete_simple(cache.name_action)
#endif // _di_controller_rule_cache_t_

/**
 * Read the content within the buffer, extracting all valid actions for the current processed item.
 *
 * @param data
 *   The program data.
 * @param multiple
 *   If TRUE, then the Object expects multiple lines of Content (which ends up being an extended list).
 *   If FALSE, then the Object expects only a single line of Content (which is either basic or extended).
 * @param buffer
 *   The buffer containing the content.
 * @param cache
 *   A structure for containing and caching the file name, item name, and action name.
 * @param item
 *   The processed item.
 * @param actions
 *   The processed actions.
 *
 * @return
 *   F_none on success.
 *   @todo add response codes.
 *
 *   Errors (with error bit) from: f_fss_count_lines().
 */
#ifndef _di_controller_rule_actions_read_
  f_return_status controller_rule_actions_read(const controller_data_t data, const bool multiple, f_string_static_t *buffer, controller_rule_cache_t *cache, controller_rule_item_t *item, controller_rule_actions_t *actions) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_actions_read_

/**
 * Print additional error/warning information in addition to existing error.
 *
 * This is explicitly intended to be used in addition to the error message.
 *
 * @param output
 *   The error or warning output structure.
 * @param cache
 *   A structure for containing and caching the file name, item name, and action name.
 *
 * @see controller_rule_actions_read()
 * @see controller_rule_items_read()
 * @see controller_rule_settings_read()
 */
#ifndef _di_controller_rule_error_print_
  void controller_rule_error_print(const fll_error_print_t output, const controller_rule_cache_t cache) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_error_print_

/**
 * Read the content within the buffer, extracting all valid items after determining their type for some rule file.
 *
 * This will perform additional FSS read functions as appropriate.
 *
 * @param data
 *   The program data.
 * @param buffer
 *   The buffer containing the content.
 * @param cache
 *   A structure for containing and caching the file name, item name, and action name.
 * @param item
 *   The processed item.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_fss_count_lines().
 *   Errors (with error bit) from: fl_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: fl_string_dynamic_terminate_after().
 *
 * @see controller_rule_actions_read()
 */
#ifndef _di_controller_rule_item_read_
  extern f_return_status controller_rule_item_read(const controller_data_t data, f_string_static_t *buffer, controller_rule_cache_t *cache, controller_rule_item_t *item) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_item_read_

/**
 * Increase the size of the rule items array by the specified amount, but only if necessary.
 *
 * This only increases size if the current used plus amount is greater than the currently allocated size.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param items
 *   The items to resize.
 *
 * @return
 *   F_none on success.
 *   F_array_too_large on success, but requested size is too small (resize is smaller than requested length).
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_controller_rule_items_increase_by_
  extern f_return_status controller_rule_items_increase_by(const f_array_length_t amount, controller_rule_items_t *items) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_items_increase_by_

/**
 * Read the content within the buffer, extracting all valid items.
 *
 * @param data
 *   The program data.
 * @param cache
 *   A structure for containing and caching the file name, item name, and action name.
 * @param items
 *   The processed array of items.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: controller_rule_items_increase_by().
 *   Errors (with error bit) from: controller_rule_item_read().
 *   Errors (with error bit) from: f_file_stream_open().
 *   Errors (with error bit) from: f_file_stream_read().
 *   Errors (with error bit) from: f_fss_count_lines().
 *   Errors (with error bit) from: fl_fss_apply_delimit().
 *   Errors (with error bit) from: fl_string_dynamic_partial_append().
 *   Errors (with error bit) from: fl_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: fl_string_dynamic_terminate_after().
 *   Errors (with error bit) from: fll_fss_basic_list_read().
 *
 * @see controller_rule_item_read()
 */
#ifndef _di_controller_rule_read_
  extern f_return_status controller_rule_read(const controller_data_t data, controller_rule_cache_t *cache, controller_rule_items_t *items) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_read_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_rule_h
