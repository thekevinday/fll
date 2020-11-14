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
 * @param file_name
 *   The file name string.
 * @param items
 *   An array of items associated with the rule.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: controller_rule_items_increase_by().
 *   Errors (with error bit) from: controller_rule_read_content().
 *   Errors (with error bit) from: f_file_stream_open().
 *   Errors (with error bit) from: f_file_stream_read().
 *   Errors (with error bit) from: f_fss_count_lines().
 *   Errors (with error bit) from: fl_fss_apply_delimit().
 *   Errors (with error bit) from: fl_string_dynamic_partial_append().
 *   Errors (with error bit) from: fl_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: fl_string_dynamic_terminate_after().
 *   Errors (with error bit) from: fll_fss_basic_list_read().
 */
#ifndef _di_controller_rule_read_
  extern f_return_status controller_rule_read(const controller_data_t data, const f_string_static_t file_name, controller_rule_items_t *items) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_read_

/**
 * Read the content within the buffer, extracting all valid items after determining their type for some rule file.
 *
 * This will perform additional FSS read functions as appropriate.
 *
 * @param data
 *   The program data.
 * @param file_name
 *   The file name string.
 * @param line
 *   The line number where the content begins.
 * @param content
 *   The buffer containing the content.
 * @param items
 *   An array of items associated with the rule.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_fss_count_lines().
 *   Errors (with error bit) from: fl_string_dynamic_partial_append_nulless().
 *   Errors (with error bit) from: fl_string_dynamic_terminate_after().
 */
#ifndef _di_controller_rule_read_content_
  extern f_return_status controller_rule_read_content(const controller_data_t data, const f_string_static_t file_name, const f_string_length_t line, f_string_static_t *content, controller_rule_items_t *items) f_gcc_attribute_visibility_internal;
#endif // _di_controller_rule_read_content_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_rule_h
