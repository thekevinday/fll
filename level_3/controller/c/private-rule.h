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
    f_string_length_t line_action;
    f_string_length_t line_item;

    f_string_range_t range_action;
    f_string_range_t range_item;

    f_fss_comments_t comments;
    f_fss_delimits_t delimits;

    f_fss_content_t content_action;
    f_fss_contents_t contents_action;
    f_fss_contents_t contents_items;
    f_fss_objects_t objects_action;
    f_fss_objects_t objects_items;

    f_string_dynamic_t buffer_item;
    f_string_dynamic_t buffer_items;

    f_string_dynamic_t name_action;
    f_string_dynamic_t name_file;
    f_string_dynamic_t name_item;
  } controller_rule_cache_t;

  #define controller_rule_cache_t_initialize \
    { \
      0, \
      0, \
      0, \
      0, \
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

  #define f_macro_controller_rule_name_t_delete_simple(cache) \
    f_macro_fss_comments_t_delete_simple(cache.comments) \
    f_macro_fss_delimits_t_delete_simple(cache.delimits) \
    f_macro_fss_content_t_delete_simple(cache.content_action) \
    f_macro_fss_contents_t_delete_simple(cache.contents_action) \
    f_macro_fss_contents_t_delete_simple(cache.contents_items) \
    f_macro_fss_objects_t_delete_simple(cache.objects_action) \
    f_macro_fss_objects_t_delete_simple(cache.objects_items) \
    f_macro_string_dynamic_t_delete_simple(cache.buffer_item) \
    f_macro_string_dynamic_t_delete_simple(cache.buffer_items) \
    f_macro_string_dynamic_t_delete_simple(cache.name_action) \
    f_macro_string_dynamic_t_delete_simple(cache.name_file) \
    f_macro_string_dynamic_t_delete_simple(cache.name_item)
#endif // _di_controller_rule_cache_t_

/**
 * Read the rule action.
 *
 * The object and content ranges are merged together (in that order) as the action parameters.
 *
 * @param data
 *   The program data.
 * @param buffer
 *   The buffer containing the content.
 * @param object
 *   (optional) The range representing where the object is found within the buffer.
 *   Set pointer address to 0 to disable.
 * @param content
 *   (optional) The ranges representing where the content is found within the buffer.
 *   Set pointer address to 0 to disable.
 * @param action
 *   The processed action.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_fss_count_lines().
 *   Errors (with error bit) from: fl_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: fl_string_dynamics_increase().
 *
 * @see f_fss_count_lines()
 * @see fl_string_dynamic_partial_append_nulless()
 * @see fl_string_dynamics_increase()
 */
#ifndef _di_controller_rule_action_read_
  extern f_return_status controller_rule_action_read(const controller_data_t data, const f_string_static_t buffer, f_fss_object_t *object, f_fss_content_t *content, controller_rule_action_t *action) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_action_read_

/**
 * Increase the size of the rule actions array by the specified amount, but only if necessary.
 *
 * This only increases size if the current used plus amount is greater than the currently allocated size.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param actions
 *   The actions to resize.
 *
 * @return
 *   F_none on success.
 *   F_array_too_large on success, but requested size is too small (resize is smaller than requested length).
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_controller_rule_actions_increase_by_
  extern f_return_status controller_rule_actions_increase_by(const f_array_length_t amount, controller_rule_actions_t *actions) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_actions_increase_by_

/**
 * Read the content within the buffer, extracting all valid actions for the current processed item.
 *
 * @param data
 *   The program data.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param item
 *   The processed item.
 * @param actions
 *   The processed actions.
 * @param range
 *   The current positions within the buffer being operated on.
 *   This is expected to be set to a position immediately after a valid object read.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: controller_rule_action_read().
 *   Errors (with error bit) from: controller_rule_actions_increase_by().
 *   Errors (with error bit) from: f_fss_count_lines().
 *
 * @see controller_rule_action_read()
 * @see controller_rule_actions_increase_by()
 * @see f_fss_count_lines()
 */
#ifndef _di_controller_rule_actions_read_
  extern f_return_status controller_rule_actions_read(const controller_data_t data, controller_rule_cache_t *cache, controller_rule_item_t *item, controller_rule_actions_t *actions, f_string_range_t *range) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_actions_read_

/**
 * Print additional error/warning information in addition to existing error.
 *
 * This is explicitly intended to be used in addition to the error message.
 *
 * @param output
 *   The error or warning output structure.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param item
 *   If TRUE, then this error is associated with an item.
 *   If FALSE, then this error is associated with a rule setting.
 *
 * @see controller_rule_actions_read()
 * @see controller_rule_items_read()
 */
#ifndef _di_controller_rule_error_print_
  void controller_rule_error_print(const fll_error_print_t output, const controller_rule_cache_t cache, const bool item) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_error_print_

/**
 * Read the content within the buffer, extracting all valid items after determining their type for some rule file.
 *
 * This will perform additional FSS read functions as appropriate.
 *
 * @param data
 *   The program data.
 * @param cache
 *   A structure for containing and caching relevant data.
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
 * @see f_fss_count_lines()
 * @see fl_string_dynamic_partial_append_nulless()
 * @see fl_string_dynamic_terminate_after()
 */
#ifndef _di_controller_rule_item_read_
  extern f_return_status controller_rule_item_read(const controller_data_t data, controller_rule_cache_t *cache, controller_rule_item_t *item) f_gcc_attribute_visibility_internal;
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
 *
 * @see f_memory_resize()
 */
#ifndef _di_controller_rule_items_increase_by_
  extern f_return_status controller_rule_items_increase_by(const f_array_length_t amount, controller_rule_items_t *items) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_items_increase_by_

/**
 * Read the content within the buffer, extracting all valid items.
 *
 * @param data
 *   The program data.
 * @param rule_id
 *   The string identifying the rule.
 *   This is constructed from the path parts to the file without the file extension and without the settings directory prefix.
 *   "/etc/controller/setting/rules/boot/my.rule" would have a rule id of "boot/my".
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param rule
 *   The processed rule.
 *   The rule status will be updated by this function.
 *
 * @return
 *   F_true on success.
 *   F_false on failure.
 *
 * @see controller_rule_items_increase_by().
 * @see controller_rule_item_read().
 * @see f_file_stream_open().
 * @see f_file_stream_read().
 * @see f_fss_count_lines().
 * @see fl_fss_apply_delimit().
 * @see fl_string_dynamic_partial_append().
 * @see fl_string_dynamic_partial_append_nulless().
 * @see fl_string_dynamic_terminate_after().
 * @see fll_fss_basic_list_read().
 */
#ifndef _di_controller_rule_read_
  extern f_return_status controller_rule_read(const controller_data_t data, const f_string_static_t rule_id, controller_rule_cache_t *cache, controller_rule_t *rule) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_read_

/**
 * Read the content within the buffer, extracting all valid settings.
 *
 * This will perform additional FSS read functions as appropriate.
 *
 * Errors from this are not considered fatal, therefore errors may be printed but nothing is returned.
 *
 * @param data
 *   The program data.
 * @param cache
 *   A structure for containing and caching relevant data.
 * @param rule
 *   The processed rule.
 *
 * @todo consider making memory failures still critical errors, in which case a status does need to be returned.
 */
#ifndef _di_controller_rule_setting_read_
  extern void controller_rule_setting_read(const controller_data_t data, controller_rule_cache_t *cache, controller_rule_t *rule) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_setting_read_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_rule_h
