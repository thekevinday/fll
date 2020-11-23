#include "controller.h"
#include "private-entry.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_entry_lists_increase_by_
  f_return_status controller_entry_lists_increase_by(const f_array_length_t amount, controller_entry_lists_t *lists) {
    f_status_t status = F_none;
    f_string_length_t size = lists->size + amount;

    if (size > f_array_length_t_size) {
      if (lists->size == f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      size = lists->size;
      status = F_array_too_large;
    }

    const f_status_t status_resize = f_memory_resize((void **) & lists->array, sizeof(controller_entry_lists_t), lists->size, size);
    if (F_status_is_error(status_resize)) return status_resize;

    lists->size = size;
    return status;
  }
#endif // _di_controller_entry_lists_increase_by_

#ifndef _di_controller_entry_list_read_
  f_return_status controller_entry_list_read(const controller_data_t data, const controller_setting_t setting, const f_string_static_t entry_name, controller_entry_cache_t *cache, controller_entry_lists_t *lists) {
    f_status_t status = F_none;

    {
      f_file_t file = f_file_t_initialize;

      const f_string_length_t file_path_length = setting.path_setting.used + f_path_separator_length + controller_string_rules_length + f_path_separator_length + entry_name.used + f_path_separator_length;
      char file_path[file_path_length + 1];

      memcpy(file_path, setting.path_setting.string, setting.path_setting.used);
      memcpy(file_path + setting.path_setting.used + f_path_separator_length, controller_string_rules, controller_string_rules_length);
      memcpy(file_path + setting.path_setting.used + f_path_separator_length + controller_string_rules_length + f_path_separator_length, entry_name.string, entry_name.used);

      file_path[setting.path_setting.used] = f_path_separator[0];
      file_path[setting.path_setting.used + f_path_separator_length + controller_string_rules_length] = f_path_separator[0];
      file_path[file_path_length - 1] = f_path_separator[0];
      file_path[file_path_length] = 0;

      status = f_file_stream_open(file_path, 0, &file);

      if (F_status_is_error(status)) {
        fll_error_file_print(data.error, F_status_set_fine(status), "f_file_stream_open", F_true, entry_name.string, "open", fll_error_file_type_file);
      }
      else {
        status = f_file_stream_read(file, 1, &cache->buffer_entry);

        if (F_status_is_error(status)) {
          fll_error_file_print(data.error, F_status_set_fine(status), "f_file_stream_read", F_true, entry_name.string, "read", fll_error_file_type_file);
        }
      }

      f_file_stream_close(F_true, &file);

      if (F_status_is_error(status)) return status;
    }

    if (cache->buffer_entry.used) {
      f_string_range_t range = f_macro_string_range_t_initialize(cache->buffer_entry.used);

      status = fll_fss_basic_list_read(cache->buffer_entry, &range, &cache->objects_list, &cache->contents_list, &cache->delimits, 0, &cache->comments);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fll_fss_basic_list_read", F_true);
      }
      else {
        status = fl_fss_apply_delimit(cache->delimits, &cache->buffer_entry);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true);
        }
      }

      cache->delimits.used = 0;
      cache->comments.used = 0;
    }
    else {
      // @todo: error out that there is no list, because a valid entry is required.
      return F_status_set_error(F_data_not);
    }

    if (F_status_is_error_not(status) && cache->objects_items.used) {
      status = controller_entry_lists_increase_by(cache->objects_list.used, lists);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "controller_entry_lists_increase_by", F_true);
      }
      else {
        for (f_array_length_t i = 0; i < cache->objects_list.used; ++i) {
          // @todo
          // @todo reserve index 0 for "main", checking each list if a "main" exists then assigning it to index 0).
          // @todo be sure to provide an error if "main" does not exist at all, this is a critical failure.
        } // for
      }
    }

    if (F_status_is_error(status)) {
      //@todo someting like: controller_rule_error_print(data.error, *cache, for_item);

      return status;
    }

    return F_none;
  }
#endif // _di_controller_entry_list_read_

#ifdef __cplusplus
} // extern "C"
#endif
