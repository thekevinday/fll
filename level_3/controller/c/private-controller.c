#include "controller.h"
#include "private-common.h"
#include "private-control.h"
#include "private-entry.h"
#include "private-rule.h"
#include "private-controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_entry_action_type_name_
  f_string_static_t controller_entry_action_type_name(const uint8_t type) {

    f_string_static_t buffer = f_string_static_t_initialize;

    switch (type) {
      case controller_entry_action_type_consider:
        buffer.string = controller_string_consider;
        buffer.used = controller_string_consider_length;
        break;

      case controller_entry_action_type_failsafe:
        buffer.string = controller_string_failsafe;
        buffer.used = controller_string_failsafe_length;
        break;

      case controller_entry_action_type_item:
        buffer.string = controller_string_item;
        buffer.used = controller_string_item_length;
        break;

      case controller_entry_action_type_ready:
        buffer.string = controller_string_ready;
        buffer.used = controller_string_ready_length;
        break;

      case controller_entry_action_type_rule:
        buffer.string = controller_string_rule;
        buffer.used = controller_string_rule_length;
        break;

      case controller_entry_action_type_timeout:
        buffer.string = controller_string_timeout;
        buffer.used = controller_string_timeout_length;
        break;
    }

    buffer.size = buffer.used;

    return buffer;
  }
#endif // _di_controller_entry_action_type_name_

#ifndef _di_controller_string_dynamic_append_terminated_
  f_return_status controller_string_dynamic_append_terminated(const f_string_static_t source, f_string_dynamic_t *destination) {

    f_status_t status = fl_string_dynamic_append(source, destination);

    if (F_status_is_error(status)) return status;

    status = fl_string_dynamic_terminate_after(destination);

    return status;
  }
#endif // _di_controller_string_dynamic_append_terminated_

#ifndef _di_controller_string_dynamic_partial_append_terminated_
  f_return_status controller_string_dynamic_partial_append_terminated(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {

    f_status_t status = fl_string_dynamic_partial_append(source, range, destination);

    if (F_status_is_error(status)) return status;

    status = fl_string_dynamic_terminate_after(destination);

    return status;
  }
#endif // _di_controller_string_dynamic_partial_append_terminated_

#ifndef _di_controller_file_load_
  f_return_status controller_file_load(const controller_data_t data, const controller_setting_t setting, const f_string_t path_prefix, const f_string_static_t path_name, const f_string_t path_suffix, const f_string_length_t path_prefix_length, const f_string_length_t path_suffix_length, controller_cache_t *cache) {
    f_status_t status = F_none;
    f_file_t file = f_file_t_initialize;

    cache->name_file.used = 0;
    cache->buffer_file.used = 0;

    f_macro_time_spec_t_clear(cache->timestamp);

    status = fl_string_append(path_prefix, path_prefix_length, &cache->name_file);

    if (F_status_is_error_not(status)) {
      status = fl_string_append(f_path_separator, f_path_separator_length, &cache->name_file);
    }

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fl_string_append", F_true);
      return status;
    }

    status = fl_string_dynamic_append(path_name, &cache->name_file);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_append", F_true);
      return status;
    }

    status = fl_string_append(f_path_extension_separator, f_path_extension_separator_length, &cache->name_file);

    if (F_status_is_error_not(status)) {
      status = fl_string_append(path_suffix, path_suffix_length, &cache->name_file);
    }

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fl_string_append", F_true);
      return status;
    }

    status = fl_string_dynamic_terminate_after(&cache->name_file);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
      return status;
    }

    const f_string_length_t path_length = setting.path_setting.used ? setting.path_setting.used + f_path_separator_length + cache->name_file.used : cache->name_file.used;
    char path[path_length + 1];

    if (setting.path_setting.used) {
      memcpy(path, setting.path_setting.string, setting.path_setting.used);
      memcpy(path + setting.path_setting.used + f_path_separator_length, cache->name_file.string, cache->name_file.used);

      path[setting.path_setting.used] = f_path_separator[0];
    }

    path[path_length] = 0;

    status = f_file_stream_open(path, 0, &file);

    if (F_status_is_error(status)) {
      fll_error_file_print(data.error, F_status_set_fine(status), "f_file_stream_open", F_true, path, "open", fll_error_file_type_file);
    }
    else {
      status = f_file_stream_read(file, 1, &cache->buffer_file);

      if (F_status_is_error(status)) {
        fll_error_file_print(data.error, F_status_set_fine(status), "f_file_stream_read", F_true, path, "read", fll_error_file_type_file);
      }
    }

    f_file_stream_close(F_true, &file);

    if (F_status_is_error_not(status)) {
      struct stat stat_file;

      status = f_file_stat(path, F_true, &stat_file);

      if (F_status_is_error(status)) {
        fll_error_file_print(data.error, F_status_set_fine(status), "f_file_stat", F_true, path, "stat", fll_error_file_type_file);
      }
      else {
        cache->timestamp.seconds = stat_file.st_ctim.tv_sec;
        cache->timestamp.nanoseconds = stat_file.st_ctim.tv_nsec;
      }
    }

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_controller_file_load_

#ifndef _di_controller_file_pid_create_
  f_return_status controller_file_pid_create(const controller_data_t data, const f_string_static_t path_pid) {
    f_status_t status = F_none;

    // the file exists, do not attempt to overwrite.
    if (f_file_exists(path_pid.string) == F_true) {
      return F_status_set_error(F_file_found);
    }

    {
      f_string_dynamic_t path_directory = f_string_dynamic_t_initialize;

      status = f_file_name_directory(path_pid.string, path_pid.used, &path_directory);

      if (F_status_is_error_not(status)) {
        status = f_directory_exists(path_directory.string);
      }

      f_macro_string_dynamic_t_delete_simple(path_directory);

      if (F_status_is_error(status)) return status;

      // the directory does not exist so do not bother attempting to create a pid file.
      if (status == F_false) {
        return F_status_set_error(F_directory_not);
      }
    }

    f_file_t file = f_file_t_initialize;

    file.flag = f_file_flag_write_only;

    status = f_file_stream_open(path_pid.string, f_macro_file_open_mode_truncate, &file);
    if (F_status_is_error(status)) return status;

    fprintf(file.stream, "%llu\n", data.pid);

    f_file_stream_close(F_true, &file);

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_controller_file_pid_create_

#ifndef _di_controller_file_pid_delete_
  void controller_file_pid_delete(const controller_data_t data, const f_string_static_t path_pid) {

    if (f_file_exists(path_pid.string) != F_true) {
      return;
    }

    f_status_t status = F_none;
    f_file_t pid_file = f_file_t_initialize;

    status = f_file_stream_open(path_pid.string, f_macro_file_open_mode_read, &pid_file);
    if (F_status_is_error(status)) return;

    f_string_dynamic_t pid_buffer = f_string_dynamic_t_initialize;

    status = f_file_stream_read(pid_file, 1, &pid_buffer);

    f_file_stream_close(F_true, &pid_file);

    if (F_status_is_error_not(status)) {
      f_number_unsigned_t number = 0;
      f_string_range_t range = f_macro_string_range_t_initialize(pid_buffer.used);

      for (; range.start < pid_buffer.used; ++range.start) {
        if (!isspace(pid_buffer.string[range.start])) break;
      } // for

      for (; range.stop > 0; --range.stop) {
        if (!isspace(pid_buffer.string[range.stop])) break;
      } // for

      status = fl_conversion_string_to_decimal_unsigned(pid_buffer.string, &number, range);

      if (F_status_is_error_not(status) && number == data.pid) {
        status = f_file_remove(path_pid.string);

        if (F_status_is_error(status) && data.warning.verbosity == f_console_verbosity_debug) {
          fll_error_file_print(data.warning, F_status_set_fine(status), "f_file_remove", F_true, path_pid.string, "delete", fll_error_file_type_file);
        }
      }
    }

    f_macro_string_dynamic_t_delete_simple(pid_buffer);
  }
#endif // _di_controller_file_pid_delete_

#ifndef _di_controller_perform_ready_
  f_return_status controller_perform_ready(const controller_data_t data, controller_setting_t *setting, controller_cache_t *cache) {
    f_status_t status = F_none;

    // only create pid file when not in validate mode.
    if (data.parameters[controller_parameter_validate].result == f_console_result_none) {

      status = controller_file_pid_create(data, setting->path_pid);

      // report pid file error but because this could be an "init" program, consider the pid file as optional and continue on.
      if (F_status_is_error(status)) {
        fll_error_file_print(data.error, F_status_set_fine(status), "controller_file_pid_create", F_true, setting->path_pid.string, "create", fll_error_file_type_file);

        controller_entry_error_print(data.error, *cache);

        // always return immediately on memory errors.
        if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {
          return status;
        }

        status = F_none;
      }
    }

    return status;
  }
#endif // _di_controller_perform_ready_

#ifndef _di_controller_preprocess_entry_
  f_return_status controller_preprocess_entry(const controller_data_t data, controller_setting_t *setting, controller_cache_t *cache) {
    f_status_t status = F_none;
    f_status_t status2 = F_none;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_array_length_t at_i = 0;
    f_array_length_t at_j = 1;

    controller_entry_actions_t *actions = 0;

    uint8_t error_has = F_false;

    setting->ready = controller_setting_ready_no;

    cache->ats.used = 0;
    cache->line_action = 0;
    cache->line_item = 0;
    cache->name_action.used = 0;
    cache->name_item.used = 0;

    status = fl_type_array_lengths_increase_by(controller_default_allocation_step, &cache->ats);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fl_type_array_lengths_increase_by", F_true);
      return status;
    }

    cache->ats.array[0] = 0;
    cache->ats.array[1] = 0;
    cache->ats.used = 2;

    cache->line_item = setting->entry.items.array[0].line;
    cache->name_item.used = 0;

    status = controller_string_dynamic_append_terminated(setting->entry.items.array[0].name, &cache->name_item);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true);
      controller_entry_error_print(data.error, *cache);

      return status;
    }

    for (;;) {

      actions = &setting->entry.items.array[cache->ats.array[at_i]].actions;

      for (; cache->ats.array[at_j] < actions->used; ++cache->ats.array[at_j]) {

        cache->line_action = actions->array[cache->ats.array[at_j]].line;
        cache->name_action.used = 0;

        status2 = controller_string_dynamic_append_terminated(controller_entry_action_type_name(actions->array[cache->ats.array[at_j]].type), &cache->name_action);

        if (F_status_is_error(status2)) {
          fll_error_print(data.error, F_status_set_fine(status2), "controller_string_dynamic_append_terminated", F_true);
          controller_entry_error_print(data.error, *cache);

          return status2;
        }

        if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_ready) {

          if (setting->ready == controller_setting_ready_wait) {
            if (data.warning.verbosity == f_console_verbosity_debug) {
              fprintf(data.warning.to.stream, "%c", f_string_eol[0]);
              fprintf(data.warning.to.stream, "%s%sMultiple '", data.warning.context.before->string, data.warning.prefix ? data.warning.prefix : "");
              fprintf(data.warning.to.stream, "%s%s%s%s", data.warning.context.after->string, data.warning.notable.before->string, controller_string_ready, data.warning.notable.after->string);
              fprintf(data.warning.to.stream, "%s' entry item actions detected; only the first will be used.%s%c", data.warning.context.before->string, data.warning.context.after->string, f_string_eol[0]);

              controller_entry_error_print(data.warning, *cache);
            }
          }

          // the pre-process currently only looks for "ready", so once found, pre-process is complete.
          setting->ready = controller_setting_ready_wait;
        }
        else if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_item) {
          error_has = F_false;

          if (fl_string_dynamic_compare_string(controller_string_main, actions->array[cache->ats.array[at_j]].parameters.array[0], controller_string_main_length) == F_equal_to) {
            continue;
          }

          // walk though each items and check to see if the item actually exists (skipping main).
          for (i = 1; i < setting->entry.items.used; ++i) {

            if (fl_string_dynamic_compare(setting->entry.items.array[i].name, actions->array[cache->ats.array[at_j]].parameters.array[0]) == F_equal_to) {

              // check to see if "i" is already in the stack (to prevent recursion) (skipping main).
              for (j = 2; j < cache->ats.used; j += 2) {

                if (cache->ats.array[j] == i) {
                  if (data.error.verbosity != f_console_verbosity_quiet) {
                    fprintf(data.error.to.stream, "%c", f_string_eol[0]);
                    fprintf(data.error.to.stream, "%s%sThe entry item named '", data.error.context.before->string, data.error.prefix ? data.error.prefix : "");
                    fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, setting->entry.items.array[i].name.string, data.error.notable.after->string);
                    fprintf(data.error.to.stream, "%s' cannot be executed because recursion is not allowed.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol[0]);
                  }

                  controller_entry_error_print(data.error, *cache);

                  if (F_status_is_error_not(status)) {
                    status = F_status_set_error(F_recurse);
                  }

                  error_has = F_true;
                  break;
                }
              } // for

              if (error_has) break;

              status2 = fl_type_array_lengths_increase_by(controller_default_allocation_step, &cache->ats);

              if (F_status_is_error(status2)) {
                fll_error_print(data.error, F_status_set_fine(status2), "fl_type_array_lengths_increase_by", F_true);
                controller_entry_error_print(data.error, *cache);

                return status2;
              }

              // save the value so to avoid string comparison during normal operation.
              actions->array[cache->ats.array[at_j]].number = i;

              // continue into the requested item.
              at_i = cache->ats.used;
              at_j = cache->ats.used + 1;

              cache->ats.array[at_i] = i;
              cache->ats.array[at_j] = 0;
              cache->ats.used += 2;

              cache->name_action.used = 0;
              cache->line_action = 0;

              cache->name_item.used = 0;
              cache->line_item = setting->entry.items.array[i].line;

              status2 = controller_string_dynamic_append_terminated(setting->entry.items.array[i].name, &cache->name_item);

              if (F_status_is_error(status2)) {
                fll_error_print(data.error, F_status_set_fine(status2), "controller_string_dynamic_append_terminated", F_true);
                controller_entry_error_print(data.error, *cache);

                return status2;
              }

              break;
            }
          } // for

          if (error_has || i >= setting->entry.items.used) {
            if (i >= setting->entry.items.used) {
              if (data.error.verbosity != f_console_verbosity_quiet) {
                fprintf(data.error.to.stream, "%c", f_string_eol[0]);
                fprintf(data.error.to.stream, "%s%sThe entry item named '", data.error.context.before->string, data.error.prefix ? data.error.prefix : "");
                fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, actions->array[cache->ats.array[at_j]].parameters.array[0].string, data.error.notable.after->string);
                fprintf(data.error.to.stream, "%s' does not exist.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol[0]);
              }

              controller_entry_error_print(data.error, *cache);

              if (F_status_is_error_not(status)) {
                status = F_status_set_error(F_valid_not);
              }
            }
          }
          else {
            break;
          }
        }
      } // for

      cache->line_action = 0;
      cache->name_action.used = 0;

      // end of actions found, so drop to previous loop in stack.
      if (cache->ats.array[at_j] == actions->used) {

        // all actions for "main" are processed so there is nothing left to do.
        if (at_i == 0) break;

        at_i -= 2;
        at_j -= 2;

        cache->ats.used -= 2;
        cache->ats.array[at_j]++;

        cache->line_item = setting->entry.items.array[cache->ats.array[at_i]].line;
        cache->name_item.used = 0;

        status2 = controller_string_dynamic_append_terminated(setting->entry.items.array[cache->ats.array[at_i]].name, &cache->name_item);

        if (F_status_is_error(status2)) {
          fll_error_print(data.error, F_status_set_fine(status2), "controller_string_dynamic_append_terminated", F_true);
          controller_entry_error_print(data.error, *cache);

          return status2;
        }
      }
    } // for

    // if ready was never found in the entry, then default to always ready.
    if (setting->ready == controller_setting_ready_no) {
      setting->ready = controller_setting_ready_yes;
    }

    return status;
  }
#endif // _di_controller_preprocess_entry_

#ifndef _di_controller_process_entry_
  f_return_status controller_process_entry(const controller_data_t data, controller_setting_t *setting, controller_cache_t *cache) {
    f_status_t status = F_none;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_array_length_t at = 0;
    f_array_length_t at_i = 0;
    f_array_length_t at_j = 1;

    controller_entry_actions_t *actions = 0;

    const bool simulate = data.parameters[controller_parameter_test].result == f_console_result_found;

    cache->ats.used = 0;
    cache->line_action = 0;
    cache->line_item = 0;
    cache->name_action.used = 0;
    cache->name_item.used = 0;

    if (setting->ready == controller_setting_ready_yes) {
      status = controller_perform_ready(data, setting, cache);
      if (F_status_is_error(status)) return status;
    }

    status = fl_type_array_lengths_increase_by(controller_default_allocation_step, &cache->ats);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fl_type_array_lengths_increase_by", F_true);
      controller_entry_error_print(data.error, *cache);

      return status;
    }

    cache->ats.array[0] = 0;
    cache->ats.array[1] = 0;
    cache->ats.used = 2;

    cache->line_item = setting->entry.items.array[0].line;
    cache->name_item.used = 0;

    status = controller_string_dynamic_append_terminated(setting->entry.items.array[0].name, &cache->name_item);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true);
      controller_entry_error_print(data.error, *cache);

      return status;
    }

    for (;;) {

      actions = &setting->entry.items.array[cache->ats.array[at_i]].actions;

      for (; cache->ats.array[at_j] < actions->used; ++cache->ats.array[at_j]) {

        cache->line_action = actions->array[cache->ats.array[at_j]].line;
        cache->name_action.used = 0;

        status = controller_string_dynamic_append_terminated(controller_entry_action_type_name(actions->array[cache->ats.array[at_j]].type), &cache->name_action);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true);
          controller_entry_error_print(data.error, *cache);

          return status;
        }

        if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_ready) {

          if (setting->ready == controller_setting_ready_wait) {
            setting->ready = controller_setting_ready_yes;

            controller_perform_ready(data, setting, cache);
            if (F_status_is_error(status)) return status;
          }
        }
        else if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_item) {

          if (actions->array[cache->ats.array[at_j]].number == 0 || actions->array[cache->ats.array[at_j]].number >= setting->entry.items.used) {

            // This should not happen if the pre-process is working as designed, but in case it doesn't, return a critical error to prevent infinite recursion and similar errors.
            if (data.error.verbosity != f_console_verbosity_quiet) {
              fprintf(data.error.to.stream, "%c", f_string_eol[0]);
              fprintf(data.error.to.stream, "%s%sInvalid entry item index ", data.error.context.before->string, data.error.prefix ? data.error.prefix : "");
              fprintf(data.error.to.stream, "%s%s%llu%s", data.error.context.after->string, data.error.notable.before->string, actions->array[cache->ats.array[at_j]].number, data.error.notable.after->string);
              fprintf(data.error.to.stream, "%s detected.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol[0]);
            }

            controller_entry_error_print(data.error, *cache);

            return F_status_is_error(F_critical);
          }

          status = fl_type_array_lengths_increase_by(controller_default_allocation_step, &cache->ats);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_type_array_lengths_increase_by", F_true);
            controller_entry_error_print(data.error, *cache);

            return status;
          }

          // continue into the requested item.
          at_i = cache->ats.used;
          at_j = cache->ats.used + 1;

          cache->ats.array[at_i] = actions->array[cache->ats.array[at_j]].number;
          cache->ats.array[at_j] = 0;
          cache->ats.used += 2;

          cache->name_action.used = 0;
          cache->line_action = 0;

          cache->name_item.used = 0;
          cache->line_item = setting->entry.items.array[actions->array[cache->ats.array[at_j]].number].line;

          status = controller_string_dynamic_append_terminated(setting->entry.items.array[actions->array[cache->ats.array[at_j]].number].name, &cache->name_item);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true);
            controller_entry_error_print(data.error, *cache);

            return status;
          }

          break;
        }
        else if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_consider || actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_rule) {

          status = controller_rules_increase_by(controller_default_allocation_step, &setting->rules);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "controller_rules_increase_by", F_true);
            controller_entry_error_print(data.error, *cache);

            return status;
          }
          else {

            // rule execution will re-use the existing cache, so save the current cache.
            const f_array_length_t cache_line_action = cache->line_action;
            const f_array_length_t cache_line_item = cache->line_item;

            const f_string_length_t cache_name_action_used = cache->name_action.used;
            const f_string_length_t cache_name_item_used = cache->name_item.used;

            char cache_name_item[cache_name_action_used];
            char cache_name_action[cache_name_item_used];

            memcpy(cache_name_item, cache->name_item.string, cache->name_item.used);
            memcpy(cache_name_action, cache->name_action.string, cache->name_action.used);

            const f_string_length_t rule_id_length = actions->array[cache->ats.array[at_j]].parameters.array[0].used + actions->array[cache->ats.array[at_j]].parameters.array[1].used + 1;
            char rule_id_name[rule_id_length + 1];
            const f_string_static_t rule_id = f_macro_string_static_t_initialize(rule_id_name, rule_id_length);

            memcpy(rule_id_name, actions->array[cache->ats.array[at_j]].parameters.array[0].string, actions->array[cache->ats.array[at_j]].parameters.array[0].used);
            memcpy(rule_id_name + actions->array[cache->ats.array[at_j]].parameters.array[0].used + 1, actions->array[cache->ats.array[at_j]].parameters.array[1].string, actions->array[cache->ats.array[at_j]].parameters.array[1].used);

            rule_id_name[actions->array[cache->ats.array[at_j]].parameters.array[0].used] = f_path_separator[0];
            rule_id_name[rule_id_length] = 0;

            at = controller_rule_find_loaded(data, *setting, rule_id);

            if (at == setting->rules.used) {
              status = controller_rule_read(data, *setting, rule_id, cache, &setting->rules.array[setting->rules.used]);

              if (F_status_is_error(status)) {
                controller_entry_error_print(data.error, *cache);

                if (!simulate) break;
              }
              else {
                setting->rules.used++;
              }
            }

            if (F_status_is_error_not(status) && actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_rule) {
              if (similate) {
                // @todo print message about how this would execute the rule.
              }
              else {
                //status = controller_rule_process();
              }
            }

            // restore cache.
            memcpy(cache->name_action.string, cache_name_action, cache_name_action_used);
            memcpy(cache->name_item.string, cache_name_item, cache_name_item_used);

            cache->name_action.string[cache_name_action_used] = 0;
            cache->name_item.string[cache_name_item_used] = 0;

            cache->name_action.used = cache_name_action_used;
            cache->name_item.used = cache_name_item_used;

            cache->line_action = cache_line_action;
            cache->line_item = cache_line_item;

            if (F_status_is_error(status)) {
              controller_entry_error_print(data.error, *cache);

              if (!simulate) break;
            }
          }
        }
        else if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_timeout) {
          // @todo
        }
        else if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_failsafe) {
          // @todo
        }

      } // for

      cache->line_action = 0;
      cache->name_action.used = 0;

      // end of actions found, so drop to previous loop in stack.
      if (cache->ats.array[at_j] == actions->used) {

        // all actions for "main" are processed so there is nothing left to do.
        if (at_i == 0) break;

        at_i -= 2;
        at_j -= 2;

        cache->ats.used -= 2;
        cache->ats.array[at_j]++;

        cache->line_item = setting->entry.items.array[cache->ats.array[at_i]].line;
        cache->name_item.used = 0;

        status = controller_string_dynamic_append_terminated(setting->entry.items.array[cache->ats.array[at_i]].name, &cache->name_item);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true);
          controller_entry_error_print(data.error, *cache);

          return status;
        }
      }
    } // for

    return status;
  }
#endif // _di_controller_process_entry_

#ifndef _di_controller_status_simplify_
  f_return_status controller_status_simplify(const f_status_t status) {

    if (status == F_memory_not || status == F_memory_allocation || status == F_memory_reallocation) {
      return F_status_set_error(F_memory);
    }

    if (status == F_file_open_max || status == F_space_not || status == F_busy) {
      return F_status_set_error(F_resource);
    }

    if (status == F_access_denied || status == F_filesystem_quota_block || status == F_prohibited || status == F_input_output) {
      return F_status_set_error(F_access);
    }

    if (status == F_complete_not_utf || status == F_complete_not_utf_block || status == F_complete_not_utf_eof || status == F_complete_not_utf_eol || status == F_complete_not_utf_eos || status == F_complete_not_utf_stop) {
      return F_status_set_error(F_encoding);
    }

    if (status == F_number || status == F_number_negative || status == F_number_positive || status == F_number_overflow) {
      return F_status_set_error(F_number);
    }

    if (status == F_parameter || status == F_found_not || status == F_interrupt || status == F_supported_not || status == F_critical) {
      return F_status_set_error(status);
    }

    return F_status_set_error(F_valid_not);
  }
#endif // _di_controller_status_simplify_

#ifndef _di_controller_validate_define_name_
  f_return_status controller_validate_environment_name(const f_string_static_t name) {

    if (!name.used) return F_none;

    f_status_t status = F_none;

    if (name.string[0] != '_') {
      status = f_utf_is_alpha(name.string, name.used);

      if (F_status_is_error(status)) return status;
      if (status == F_false) return F_false;
    }

    for (f_string_length_t i = f_macro_utf_byte_width(name.string[0]); i < name.used; i += f_macro_utf_byte_width(name.string[i])) {

      if (name.string[i] == '_') continue;

      status = f_utf_is_alpha_digit(name.string, name.used);

      if (F_status_is_error(status)) return status;
      if (status == F_false) return F_false;
    } // for

    return F_true;
  }
#endif // _di_controller_validate_define_name_

#ifndef _di_controller_validate_has_graph_
  f_return_status controller_validate_has_graph(const f_string_static_t name) {

    if (!name.used) return F_none;

    f_status_t status = F_none;

    for (f_string_length_t i = 0; i < name.used; i += f_macro_utf_byte_width(name.string[i])) {

      status = f_utf_is_graph(name.string, name.used);

      if (F_status_is_error(status)) return status;
      if (status == F_true) return F_true;
    } // for

    return F_false;
  }
#endif // _di_controller_validate_has_graph_

#ifdef __cplusplus
} // extern "C"
#endif
