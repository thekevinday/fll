#include "controller.h"
#include "private-common.h"
#include "private-control.h"
#include "private-entry.h"
#include "private-rule.h"
#include "private-thread.h"
#include "private-controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_string_dynamic_rip_nulless_terminated_
  f_status_t controller_string_dynamic_rip_nulless_terminated(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {

    f_status_t status = fl_string_dynamic_rip_nulless(source, range, destination);
    if (F_status_is_error(status)) return status;

    return f_string_dynamic_terminate_after(destination);
  }
#endif // _di_controller_string_dynamic_rip_nulless_terminated_

#ifndef _di_controller_string_dynamic_append_terminated_
  f_status_t controller_string_dynamic_append_terminated(const f_string_static_t source, f_string_dynamic_t *destination) {

    f_status_t status = f_string_dynamic_append(source, destination);
    if (F_status_is_error(status)) return status;

    return f_string_dynamic_terminate_after(destination);
  }
#endif // _di_controller_string_dynamic_append_terminated_

#ifndef _di_controller_string_dynamic_partial_append_terminated_
  f_status_t controller_string_dynamic_partial_append_terminated(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {

    f_status_t status = f_string_dynamic_partial_append(source, range, destination);
    if (F_status_is_error(status)) return status;

    return f_string_dynamic_terminate_after(destination);
  }
#endif // _di_controller_string_dynamic_partial_append_terminated_

#ifndef _di_controller_file_load_
  f_status_t controller_file_load(const f_string_t path_prefix, const f_string_static_t path_name, const f_string_t path_suffix, const f_array_length_t path_prefix_length, const f_array_length_t path_suffix_length, controller_main_t main, controller_cache_t *cache) {
    f_status_t status = F_none;
    f_file_t file = f_file_t_initialize;

    cache->action.name_file.used = 0;
    cache->buffer_file.used = 0;

    f_macro_time_spec_t_clear(cache->timestamp);

    status = f_string_append(path_prefix, path_prefix_length, &cache->action.name_file);

    if (F_status_is_error_not(status)) {
      status = f_string_append(f_path_separator_s, f_path_separator_length, &cache->action.name_file);
    }

    if (F_status_is_error_not(status)) {
      status = f_string_append(path_name.string, path_name.used, &cache->action.name_file);
    }

    if (F_status_is_error_not(status)) {
      status = f_string_append(f_path_extension_separator, f_path_extension_separator_length, &cache->action.name_file);
    }

    if (F_status_is_error_not(status)) {
      status = f_string_append(path_suffix, path_suffix_length, &cache->action.name_file);
    }

    if (F_status_is_error(status)) {
      if (main.data->error.verbosity != f_console_verbosity_quiet) {
        f_thread_mutex_lock(&main.thread->lock.print);

        fll_error_print(main.data->error, F_status_set_fine(status), "f_string_append", F_true);

        f_thread_mutex_unlock(&main.thread->lock.print);
      }

      return status;
    }

    status = f_string_dynamic_terminate_after(&cache->action.name_file);

    if (F_status_is_error(status)) {
      if (main.data->error.verbosity != f_console_verbosity_quiet) {
        f_thread_mutex_lock(&main.thread->lock.print);

        fll_error_print(main.data->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);

        f_thread_mutex_unlock(&main.thread->lock.print);
      }

      return status;
    }

    const f_array_length_t path_length = main.setting->path_setting.used ? main.setting->path_setting.used + f_path_separator_length + cache->action.name_file.used : cache->action.name_file.used;
    char path[path_length + 1];

    if (main.setting->path_setting.used) {
      memcpy(path, main.setting->path_setting.string, main.setting->path_setting.used);
      memcpy(path + main.setting->path_setting.used + f_path_separator_length, cache->action.name_file.string, cache->action.name_file.used);

      path[main.setting->path_setting.used] = f_path_separator_s[0];
    }

    path[path_length] = 0;

    status = f_file_stream_open(path, 0, &file);

    if (F_status_is_error(status)) {
      if (main.data->error.verbosity != f_console_verbosity_quiet) {
        f_thread_mutex_lock(&main.thread->lock.print);

        fll_error_file_print(main.data->error, F_status_set_fine(status), "f_file_stream_open", F_true, path, "open", fll_error_file_type_file);

        f_thread_mutex_unlock(&main.thread->lock.print);
      }
    }
    else {
      status = f_file_stream_read(file, 1, &cache->buffer_file);

      if (F_status_is_error(status)) {
        if (main.data->error.verbosity != f_console_verbosity_quiet) {
          f_thread_mutex_lock(&main.thread->lock.print);

          fll_error_file_print(main.data->error, F_status_set_fine(status), "f_file_stream_read", F_true, path, "read", fll_error_file_type_file);

          f_thread_mutex_unlock(&main.thread->lock.print);
        }
      }
    }

    f_file_stream_close(F_true, &file);

    if (F_status_is_error_not(status)) {
      struct stat stat_file;

      status = f_file_stat(path, F_true, &stat_file);

      if (F_status_is_error(status)) {
        if (main.data->error.verbosity != f_console_verbosity_quiet) {
          f_thread_mutex_lock(&main.thread->lock.print);

          fll_error_file_print(main.data->error, F_status_set_fine(status), "f_file_stat", F_true, path, "stat", fll_error_file_type_file);

          f_thread_mutex_unlock(&main.thread->lock.print);
        }
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
  f_status_t controller_file_pid_create(const controller_data_t data, const f_string_static_t path_pid) {
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

      f_macro_string_dynamic_t_delete_simple(path_directory)

      if (F_status_is_error(status)) return status;

      // the directory does not exist so do not bother attempting to create a pid file.
      if (status == F_false) {
        return F_status_set_error(F_directory_not);
      }
    }

    f_file_t file = f_file_t_initialize;

    file.flag = f_file_flag_write_only;

    status = f_file_stream_open(path_pid.string, f_file_open_mode_truncate_s, &file);
    if (F_status_is_error(status)) return status;

    fprintf(file.stream, "%llu%c", data.pid, f_string_eol_s[0]);

    f_file_stream_close(F_true, &file);

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_controller_file_pid_create_

#ifndef _di_controller_file_pid_delete_
  void controller_file_pid_delete(const controller_data_t data, const f_string_static_t path_pid) {

    // only delete if the file exists and there is no error while checking.
    if (f_file_exists(path_pid.string) != F_true) {
      return;
    }

    f_status_t status = F_none;
    f_file_t pid_file = f_file_t_initialize;

    status = f_file_stream_open(path_pid.string, f_file_open_mode_read_s, &pid_file);
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

#ifndef _di_controller_find_process_
  f_status_t controller_find_process(const f_string_static_t alias, const controller_processs_t processs, f_array_length_t *at) {

    if (!alias.used) return F_none;
    if (!processs.used) return F_false;

    for (f_array_length_t i = 0; i < processs.used; ++i) {

      if (fl_string_dynamic_compare(alias, processs.array[i].alias_rule) == F_equal_to) {
        *at = i;
        return F_true;
      }
    } // for

    return F_false;
  }
#endif // _di_controller_find_process_

#ifndef _di_controller_get_id_user_
  f_status_t controller_get_id_user(const f_string_static_t buffer, const f_string_range_t range, controller_cache_t *cache, uid_t *id) {
    f_number_unsigned_t number = 0;

    // @todo fix argument ordering in fl_conversion_string_to_number_unsigned().
    f_status_t status = fl_conversion_string_to_number_unsigned(buffer.string, &number, range);

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_number) {
        cache->action.generic.used = 0;

        status = f_string_dynamic_partial_append_nulless(buffer, range, &cache->action.generic);

        if (F_status_is_error(status)) {
          return F_status_set_error(status);
        }

        status = f_account_id_user_by_name(cache->action.generic.string, id);

        if (F_status_is_error(status)) {
          return F_status_set_error(status);
        }
        else if (status == F_exist_not) {
          return F_status_set_error(F_exist_not);
        }

        return F_none;
      }

      return F_status_set_error(status);
    }
    else if (number > f_type_size_32_unsigned) {
      return F_status_set_error(F_number_too_large);
    }

    *id = (uid_t) number;
    return status;
  }
#endif // _di_controller_get_id_user_

#ifndef _di_controller_get_id_group_
  f_status_t controller_get_id_group(const f_string_static_t buffer, const f_string_range_t range, controller_cache_t *cache, gid_t *id) {
    f_number_unsigned_t number = 0;

    // @todo fix argument ordering in fl_conversion_string_to_number_unsigned().
    f_status_t status = fl_conversion_string_to_number_unsigned(buffer.string, &number, range);

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_number) {
        cache->action.generic.used = 0;

        status = f_string_dynamic_partial_append_nulless(buffer, range, &cache->action.generic);

        if (F_status_is_error(status)) {
          return F_status_set_error(status);
        }

        status = f_account_id_group_by_name(cache->action.generic.string, id);

        if (F_status_is_error(status)) {
          return F_status_set_error(status);
        }
        else if (status == F_exist_not) {
          return F_status_set_error(F_exist_not);
        }

        return F_none;
      }

      return F_status_set_error(status);
    }
    else if (number > f_type_size_32_unsigned) {
      return F_status_set_error(F_number_too_large);
    }

    *id = (gid_t) number;
    return status;
  }
#endif // _di_controller_get_id_group_

#ifndef _di_controller_perform_ready_
  f_status_t controller_perform_ready(controller_main_t main, controller_cache_t *cache) {
    f_status_t status = F_none;

    // only create pid file when not in validate mode.
    if (main.data->parameters[controller_parameter_validate].result == f_console_result_none) {

      status = controller_file_pid_create(*main.data, main.setting->path_pid);

      // report pid file error but because this could be an "init" program, consider the pid file as optional and continue on.
      if (F_status_is_error(status)) {

        // always return immediately on memory errors.
        if (F_status_set_fine(status) == F_memory_not) {
          if (main.data->error.verbosity != f_console_verbosity_quiet) {
            f_thread_mutex_lock(&main.thread->lock.print);

            fll_error_file_print(main.data->error, F_status_set_fine(status), "controller_file_pid_create", F_true, main.setting->path_pid.string, "create", fll_error_file_type_file);

            controller_entry_error_print_cache(main.data->error, cache->action);

            f_thread_mutex_unlock(&main.thread->lock.print);
          }

          return status;
        }

        if (main.data->warning.verbosity == f_console_verbosity_debug) {
          f_thread_mutex_lock(&main.thread->lock.print);

          fll_error_file_print(main.data->warning, F_status_set_fine(status), "controller_file_pid_create", F_true, main.setting->path_pid.string, "create", fll_error_file_type_file);

          controller_entry_error_print_cache(main.data->warning, cache->action);

          f_thread_mutex_unlock(&main.thread->lock.print);
        }

        status = F_none;
      }
    }

    return status;
  }
#endif // _di_controller_perform_ready_

#ifndef _di_controller_preprocess_entry_
  f_status_t controller_preprocess_entry(controller_main_t main, controller_cache_t *cache) {
    f_status_t status = F_none;
    f_status_t status2 = F_none;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_array_length_t at_i = 0;
    f_array_length_t at_j = 1;

    controller_entry_actions_t *actions = 0;

    uint8_t error_has = F_false;

    main.setting->ready = controller_setting_ready_no;

    cache->ats.used = 0;

    cache->action.line_action = 0;
    cache->action.line_item = 0;
    cache->action.name_action.used = 0;
    cache->action.name_item.used = 0;

    f_macro_array_lengths_t_increase_by(status, cache->ats, controller_default_allocation_step)

    if (F_status_is_error(status)) {
      controller_entry_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_macro_array_lengths_t_increase_by", F_true, main.thread);
      return status;
    }

    // utilize the ats cache as an item execution stack (at_i is for item index, and at_j (at_i + 1) is for action index).
    cache->ats.array[0] = 0;
    cache->ats.array[1] = 0;
    cache->ats.used = 2;

    cache->action.line_item = main.setting->entry.items.array[0].line;
    cache->action.name_item.used = 0;

    status = controller_string_dynamic_append_terminated(main.setting->entry.items.array[0].name, &cache->action.name_item);

    if (F_status_is_error(status)) {
      controller_entry_error_print(main.data->error, cache->action, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true, main.thread);

      return status;
    }

    for (;;) {

      actions = &main.setting->entry.items.array[cache->ats.array[at_i]].actions;

      for (; cache->ats.array[at_j] < actions->used; ++cache->ats.array[at_j]) {

        if (main.thread->signal) {
          return F_signal;
        }

        cache->action.line_action = actions->array[cache->ats.array[at_j]].line;
        cache->action.name_action.used = 0;

        status2 = controller_string_dynamic_append_terminated(controller_entry_action_type_name(actions->array[cache->ats.array[at_j]].type), &cache->action.name_action);

        if (F_status_is_error(status2)) {
          controller_entry_error_print(main.data->error, cache->action, F_status_set_fine(status2), "controller_string_dynamic_append_terminated", F_true, main.thread);

          return status2;
        }

        if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_ready) {

          if (main.setting->ready == controller_setting_ready_wait) {
            if (main.data->warning.verbosity == f_console_verbosity_debug) {
              f_thread_mutex_lock(&main.thread->lock.print);

              fprintf(main.data->warning.to.stream, "%c", f_string_eol_s[0]);
              fprintf(main.data->warning.to.stream, "%s%sMultiple '", main.data->warning.context.before->string, main.data->warning.prefix ? main.data->warning.prefix : f_string_empty_s);
              fprintf(main.data->warning.to.stream, "%s%s%s%s", main.data->warning.context.after->string, main.data->warning.notable.before->string, controller_string_ready_s, main.data->warning.notable.after->string);
              fprintf(main.data->warning.to.stream, "%s' entry item actions detected; only the first will be used.%s%c", main.data->warning.context.before->string, main.data->warning.context.after->string, f_string_eol_s[0]);

              controller_entry_error_print_cache(main.data->warning, cache->action);

              f_thread_mutex_unlock(&main.thread->lock.print);
            }
          }

          // the pre-process currently only looks for "ready", so once found, pre-process is complete.
          main.setting->ready = controller_setting_ready_wait;
        }
        else if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_item) {
          error_has = F_false;

          if (fl_string_dynamic_compare_string(controller_string_main_s, actions->array[cache->ats.array[at_j]].parameters.array[0], controller_string_main_length) == F_equal_to) {
            continue;
          }

          // walk though each items and check to see if the item actually exists (skipping main).
          for (i = 1; i < main.setting->entry.items.used; ++i) {

            if (fl_string_dynamic_compare(main.setting->entry.items.array[i].name, actions->array[cache->ats.array[at_j]].parameters.array[0]) == F_equal_to) {

              // check to see if "i" is already in the stack (to prevent recursion) (skipping main).
              for (j = 2; j < cache->ats.used; j += 2) {

                if (cache->ats.array[j] == i) {
                  if (main.data->error.verbosity != f_console_verbosity_quiet) {
                    f_thread_mutex_lock(&main.thread->lock.print);

                    fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                    fprintf(main.data->error.to.stream, "%s%sThe entry item named '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
                    fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, main.setting->entry.items.array[i].name.string, main.data->error.notable.after->string);
                    fprintf(main.data->error.to.stream, "%s' cannot be executed because recursion is not allowed.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

                    controller_entry_error_print_cache(main.data->error, cache->action);

                    f_thread_mutex_unlock(&main.thread->lock.print);
                  }

                  if (F_status_is_error_not(status)) {
                    status = F_status_set_error(F_recurse);
                  }

                  error_has = F_true;
                  break;
                }
              } // for

              if (error_has) break;

              f_macro_array_lengths_t_increase_by(status2, cache->ats, controller_default_allocation_step)

              if (F_status_is_error(status2)) {
                controller_entry_error_print(main.data->error, cache->action, F_status_set_fine(status2), "f_macro_array_lengths_t_increase_by", F_true, main.thread);

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

              cache->action.name_action.used = 0;
              cache->action.line_action = 0;

              cache->action.name_item.used = 0;
              cache->action.line_item = main.setting->entry.items.array[i].line;

              status2 = controller_string_dynamic_append_terminated(main.setting->entry.items.array[i].name, &cache->action.name_item);

              if (F_status_is_error(status2)) {
                controller_entry_error_print(main.data->error, cache->action, F_status_set_fine(status2), "controller_string_dynamic_append_terminated", F_true, main.thread);

                return status2;
              }

              break;
            }
          } // for

          if (error_has || i >= main.setting->entry.items.used) {
            if (i >= main.setting->entry.items.used) {
              if (main.data->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&main.thread->lock.print);

                fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(main.data->error.to.stream, "%s%sThe entry item named '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
                fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, actions->array[cache->ats.array[at_j]].parameters.array[0].string, main.data->error.notable.after->string);
                fprintf(main.data->error.to.stream, "%s' does not exist.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

                controller_entry_error_print_cache(main.data->error, cache->action);

                f_thread_mutex_unlock(&main.thread->lock.print);
              }

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

      cache->action.line_action = 0;
      cache->action.name_action.used = 0;

      // end of actions found, so drop to previous loop in stack.
      if (cache->ats.array[at_j] == actions->used) {

        // all actions for "main" are processed so there is nothing left to do.
        if (at_i == 0) break;

        at_i -= 2;
        at_j -= 2;

        cache->ats.used -= 2;
        cache->ats.array[at_j]++;

        cache->action.line_item = main.setting->entry.items.array[cache->ats.array[at_i]].line;
        cache->action.name_item.used = 0;

        status2 = controller_string_dynamic_append_terminated(main.setting->entry.items.array[cache->ats.array[at_i]].name, &cache->action.name_item);

        if (F_status_is_error(status2)) {
          controller_entry_error_print(main.data->error, cache->action, F_status_set_fine(status2), "controller_string_dynamic_append_terminated", F_true, main.thread);

          return status2;
        }
      }
    } // for

    // if ready was never found in the entry, then default to always ready.
    if (main.setting->ready == controller_setting_ready_no) {
      main.setting->ready = controller_setting_ready_yes;
    }

    return status;
  }
#endif // _di_controller_preprocess_entry_

#ifndef _di_controller_process_entry_
  f_status_t controller_process_entry(controller_main_t main, controller_cache_t *cache) {
    f_status_t status = F_none;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_array_length_t at = 0;
    f_array_length_t at_i = 0;
    f_array_length_t at_j = 1;

    uint8_t rule_options = 0;

    controller_entry_action_t *entry_action = 0;
    controller_entry_actions_t *entry_actions = 0;
    controller_process_t *process = 0;

    // an empty stack is used here because each rule here is the first rule run in the rule's scope.
    const f_array_lengths_t stack = f_array_lengths_t_initialize;

    const bool simulate = main.data->parameters[controller_parameter_test].result == f_console_result_found;

    cache->ats.used = 0;
    cache->stack.used = 0;

    cache->action.line_action = 0;
    cache->action.line_item = 0;
    cache->action.name_action.used = 0;
    cache->action.name_item.used = 0;

    if (main.setting->ready == controller_setting_ready_yes) {
      status = controller_perform_ready(main, cache);
      if (F_status_is_error(status)) return status;
    }

    f_macro_array_lengths_t_increase_by(status, cache->ats, controller_default_allocation_step)

    if (F_status_is_error(status)) {
      controller_entry_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_macro_array_lengths_t_increase_by", F_true, main.thread);

      return status;
    }

    // utilize the ats cache as an item execution stack (at_i is for item index, and at_j (at_i + 1) is for action index).
    cache->ats.array[0] = 0;
    cache->ats.array[1] = 0;
    cache->ats.used = 2;

    cache->action.line_item = main.setting->entry.items.array[0].line;
    cache->action.name_item.used = 0;

    status = controller_string_dynamic_append_terminated(main.setting->entry.items.array[0].name, &cache->action.name_item);

    if (F_status_is_error(status)) {
      controller_entry_error_print(main.data->error, cache->action, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true, main.thread);

      return status;
    }

    if (simulate) {
      f_thread_mutex_lock(&main.thread->lock.print);

      fprintf(main.data->output.stream, "%c", f_string_eol_s[0]);
      fprintf(main.data->output.stream, "Processing entry item rule '");
      fprintf(main.data->output.stream, "%s%s%s", main.data->context.set.title.before->string, controller_string_main_s, main.data->context.set.title.after->string);
      fprintf(main.data->output.stream, "'.%c", f_string_eol_s[0]);

      f_thread_mutex_unlock(&main.thread->lock.print);
    }

    f_thread_lock_read(&main.thread->lock.entry);

    for (;;) {

      entry_actions = &main.setting->entry.items.array[cache->ats.array[at_i]].actions;

      for (; cache->ats.array[at_j] < entry_actions->used; ++cache->ats.array[at_j]) {

        if (main.thread->signal) {
          status = F_signal;
          break;
        }

        entry_action = &entry_actions->array[cache->ats.array[at_j]];

        cache->action.line_action = entry_action->line;
        cache->action.name_action.used = 0;

        status = controller_string_dynamic_append_terminated(controller_entry_action_type_name(entry_action->type), &cache->action.name_action);

        if (F_status_is_error(status)) {
          controller_entry_error_print(main.data->error, cache->action, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true, main.thread);

          f_thread_unlock(&main.thread->lock.entry);

          return status;
        }

        if (F_status_is_error(entry_action->status)) {

          if (entry_action->type == controller_entry_action_type_rule) {

            if (simulate) {
              f_thread_mutex_lock(&main.thread->lock.print);

              fprintf(main.data->output.stream, "%c", f_string_eol_s[0]);
              fprintf(main.data->output.stream, "The entry item action '");
              fprintf(main.data->output.stream, "%s%s%s", main.data->context.set.title.before->string, cache->action.name_action.string, main.data->context.set.title.after->string);

              if (entry_action->parameters.used) {
                fprintf(main.data->output.stream, f_string_space_s);
                fprintf(main.data->output.stream, "%s", main.data->context.set.notable.before->string);
                controller_entry_action_parameters_print(main.data->output.stream, entry_actions->array[cache->ats.array[at_j]]);
                fprintf(main.data->output.stream, "%s", main.data->context.set.notable.after->string);
              }

              fprintf(main.data->output.stream, "' is %s and is in a %sfailed%s state, skipping execution.%c", entry_action->code & controller_entry_rule_code_require ? "required" : "optional", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

              f_thread_mutex_unlock(&main.thread->lock.print);
            }
            else if (entry_action->code & controller_entry_rule_code_require) {

              if (main.data->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&main.thread->lock.print);

                fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(main.data->error.to.stream, "%s%sThe entry item action '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
                fprintf(main.data->error.to.stream, "%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, cache->action.name_action.string);

                if (entry_action->parameters.used) {
                  fprintf(main.data->error.to.stream, f_string_space_s);
                  controller_entry_action_parameters_print(main.data->error.to.stream, entry_actions->array[cache->ats.array[at_j]]);
                }

                fprintf(main.data->error.to.stream, "%s%s' is ", main.data->error.notable.after->string, main.data->error.context.before->string);
                fprintf(main.data->error.to.stream, "%s%srequired%s", main.data->error.context.after->string, main.data->error.notable.before->string, main.data->error.notable.after->string);
                fprintf(main.data->error.to.stream, "%s and is in a ", main.data->error.context.before->string);
                fprintf(main.data->error.to.stream, "%s%sfailed%s", main.data->error.context.after->string, main.data->error.notable.before->string, main.data->error.notable.after->string);
                fprintf(main.data->error.to.stream, "%s state, skipping execution.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

                controller_entry_error_print_cache(main.data->error, cache->action);

                f_thread_mutex_unlock(&main.thread->lock.print);
              }

              f_thread_unlock(&main.thread->lock.entry);

              return F_status_is_error(F_require);
            }
            else if (main.data->warning.verbosity == f_console_verbosity_debug) {
              f_thread_mutex_lock(&main.thread->lock.print);

              fprintf(main.data->warning.to.stream, "%c", f_string_eol_s[0]);
              fprintf(main.data->warning.to.stream, "%s%sThe entry item action '", main.data->warning.context.before->string, main.data->warning.prefix ? main.data->warning.prefix : f_string_empty_s);
              fprintf(main.data->warning.to.stream, "%s%s%s", main.data->warning.context.after->string, main.data->warning.notable.before->string, cache->action.name_action.string);

              if (entry_action->parameters.used) {
                fprintf(main.data->warning.to.stream, f_string_space_s);
                controller_entry_action_parameters_print(main.data->warning.to.stream, entry_actions->array[cache->ats.array[at_j]]);
              }

              fprintf(main.data->warning.to.stream, "%s%s' is ", main.data->warning.notable.after->string, main.data->warning.context.before->string);
              fprintf(main.data->warning.to.stream, "%s%srequired%s", main.data->warning.context.after->string, main.data->warning.notable.before->string, main.data->warning.notable.after->string);
              fprintf(main.data->warning.to.stream, "%s and is in a ", main.data->warning.context.before->string);
              fprintf(main.data->warning.to.stream, "%s%sfailed%s", main.data->warning.context.after->string, main.data->warning.notable.before->string, main.data->warning.notable.after->string);
              fprintf(main.data->warning.to.stream, "%s state, skipping execution.%s%c", main.data->warning.context.before->string, main.data->warning.context.after->string, f_string_eol_s[0]);

              controller_entry_error_print_cache(main.data->warning, cache->action);

              f_thread_mutex_unlock(&main.thread->lock.print);
            }
          }
          else {
            if (simulate) {
              f_thread_mutex_lock(&main.thread->lock.print);

              fprintf(main.data->output.stream, "%c", f_string_eol_s[0]);
              fprintf(main.data->output.stream, "The entry item action '");
              fprintf(main.data->output.stream, "%s%s%s", main.data->context.set.title.before->string, cache->action.name_action.string, main.data->context.set.title.after->string);

              if (entry_action->parameters.used) {
                fprintf(main.data->output.stream, f_string_space_s);
                fprintf(main.data->output.stream, "%s", main.data->context.set.notable.before->string);
                controller_entry_action_parameters_print(main.data->output.stream, entry_actions->array[cache->ats.array[at_j]]);
                fprintf(main.data->output.stream, "%s", main.data->context.set.notable.after->string);
              }

              fprintf(main.data->output.stream, "' is in a %sfailed%s state, skipping.%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

              f_thread_mutex_unlock(&main.thread->lock.print);
            }
            else if (main.data->warning.verbosity == f_console_verbosity_debug) {
              f_thread_mutex_lock(&main.thread->lock.print);

              fprintf(main.data->warning.to.stream, "%c", f_string_eol_s[0]);
              fprintf(main.data->warning.to.stream, "%s%sThe entry item action '", main.data->warning.context.before->string, main.data->warning.prefix ? main.data->warning.prefix : f_string_empty_s);
              fprintf(main.data->warning.to.stream, "%s%s", main.data->warning.notable.before->string, cache->action.name_action.string);

              if (entry_action->parameters.used) {
                fprintf(main.data->warning.to.stream, f_string_space_s);
                controller_entry_action_parameters_print(main.data->warning.to.stream, entry_actions->array[cache->ats.array[at_j]]);
              }

              fprintf(main.data->warning.to.stream, "%s' is in a ", main.data->warning.notable.after->string);
              fprintf(main.data->warning.to.stream, "%s%sfailed%s", main.data->warning.context.after->string, main.data->warning.notable.before->string, main.data->warning.notable.after->string);
              fprintf(main.data->warning.to.stream, "%s state, skipping.%s%c", main.data->warning.context.before->string, main.data->warning.context.after->string, f_string_eol_s[0]);

              controller_entry_error_print_cache(main.data->warning, cache->action);

              f_thread_mutex_unlock(&main.thread->lock.print);
            }
          }

          continue;
        }

        if (entry_action->type == controller_entry_action_type_ready) {

          if (main.setting->ready == controller_setting_ready_wait) {

            if (simulate) {
              f_thread_mutex_lock(&main.thread->lock.print);

              fprintf(main.data->output.stream, "%c", f_string_eol_s[0]);
              fprintf(main.data->output.stream, "Processing entry item action '");
              fprintf(main.data->output.stream, "%s%s%s", main.data->context.set.title.before->string, controller_string_ready_s, main.data->context.set.title.after->string);
              fprintf(main.data->output.stream, "'.%c", f_string_eol_s[0]);

              f_thread_mutex_unlock(&main.thread->lock.print);
            }
            else {
              controller_perform_ready(main, cache);

              if (F_status_is_error(status)) {
                f_thread_unlock(&main.thread->lock.entry);

                return status;
              }
            }

            main.setting->ready = controller_setting_ready_yes;
          }
          else if (simulate) {
            f_thread_mutex_lock(&main.thread->lock.print);

            fprintf(main.data->output.stream, "%c", f_string_eol_s[0]);
            fprintf(main.data->output.stream, "Ignoring entry item action '");
            fprintf(main.data->output.stream, "%s%s%s", main.data->context.set.title.before->string, controller_string_ready_s, main.data->context.set.title.after->string);
            fprintf(main.data->output.stream, "', state already is ready.%c", f_string_eol_s[0]);

            f_thread_mutex_unlock(&main.thread->lock.print);
          }
        }
        else if (entry_action->type == controller_entry_action_type_item) {

          if (entry_action->number == 0 || entry_action->number >= main.setting->entry.items.used) {

            // This should not happen if the pre-process is working as designed, but in case it doesn't, return a critical error to prevent infinite recursion and similar errors.
            if (main.data->error.verbosity != f_console_verbosity_quiet) {
              f_thread_mutex_lock(&main.thread->lock.print);

              fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
              fprintf(main.data->error.to.stream, "%s%sInvalid entry item index ", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
              fprintf(main.data->error.to.stream, "%s%s%llu%s", main.data->error.context.after->string, main.data->error.notable.before->string, entry_action->number, main.data->error.notable.after->string);
              fprintf(main.data->error.to.stream, "%s detected.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

              controller_entry_error_print_cache(main.data->error, cache->action);

              f_thread_mutex_unlock(&main.thread->lock.print);
            }

            f_thread_unlock(&main.thread->lock.entry);

            return F_status_is_error(F_critical);
          }

          f_macro_array_lengths_t_increase_by(status, cache->ats, controller_default_allocation_step)

          if (F_status_is_error(status)) {
            controller_entry_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_macro_array_lengths_t_increase_by", F_true, main.thread);

            f_thread_unlock(&main.thread->lock.entry);

            return status;
          }

          // continue into the requested item.
          cache->ats.array[cache->ats.used] = entry_action->number;
          cache->ats.array[cache->ats.used + 1] = 0;

          at_i = cache->ats.used;
          at_j = cache->ats.used + 1;

          cache->ats.used += 2;

          cache->action.name_action.used = 0;
          cache->action.line_action = 0;

          cache->action.name_item.used = 0;
          cache->action.line_item = main.setting->entry.items.array[cache->ats.array[at_i]].line;

          status = controller_string_dynamic_append_terminated(main.setting->entry.items.array[cache->ats.array[at_i]].name, &cache->action.name_item);

          if (F_status_is_error(status)) {
            controller_entry_error_print(main.data->error, cache->action, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true, main.thread);

            f_thread_unlock(&main.thread->lock.entry);

            return status;
          }

          if (simulate) {
            f_thread_mutex_lock(&main.thread->lock.print);

            fprintf(main.data->output.stream, "%c", f_string_eol_s[0]);
            fprintf(main.data->output.stream, "Processing entry item '");
            fprintf(main.data->output.stream, "%s%s%s", main.data->context.set.title.before->string, cache->action.name_item.string, main.data->context.set.title.after->string);
            fprintf(main.data->output.stream, "'.%c", f_string_eol_s[0]);

            f_thread_mutex_unlock(&main.thread->lock.print);
          }

          // exit inner loop to force restarting and start processing the requested item.
          break;
        }
        else if (entry_action->type == controller_entry_action_type_consider || entry_action->type == controller_entry_action_type_rule) {

          f_thread_lock_write(&main.thread->lock.rule);

          status = controller_rules_increase(&main.setting->rules);

          f_thread_unlock(&main.thread->lock.rule);

          if (F_status_is_error(status)) {
            controller_entry_error_print(main.data->error, cache->action, F_status_set_fine(status), "controller_rules_increase", F_true, main.thread);

            f_thread_unlock(&main.thread->lock.entry);

            return status;
          }

          const f_array_length_t id_rule_length = entry_action->parameters.array[0].used + entry_action->parameters.array[1].used + 1;
          char id_rule_name[id_rule_length + 1];
          const f_string_static_t alias_rule = f_macro_string_static_t_initialize(id_rule_name, id_rule_length);

          memcpy(id_rule_name, entry_action->parameters.array[0].string, entry_action->parameters.array[0].used);
          memcpy(id_rule_name + entry_action->parameters.array[0].used + 1, entry_action->parameters.array[1].string, entry_action->parameters.array[1].used);

          id_rule_name[entry_action->parameters.array[0].used] = f_path_separator_s[0];
          id_rule_name[id_rule_length] = 0;

          f_thread_lock_read(&main.thread->lock.rule);

          at = controller_rule_find_loaded(alias_rule, main);

          if (simulate) {
            f_thread_mutex_lock(&main.thread->lock.print);

            fprintf(main.data->output.stream, "%c", f_string_eol_s[0]);
            fprintf(main.data->output.stream, "%s entry item rule '", entry_action->type == controller_entry_action_type_rule ? "Processing" : "Considering");
            fprintf(main.data->output.stream, "%s%s%s", main.data->context.set.title.before->string, alias_rule.string, main.data->context.set.title.after->string);
            fprintf(main.data->output.stream, "'.%c", f_string_eol_s[0]);

            f_thread_mutex_unlock(&main.thread->lock.print);
          }

          // the rule is not yet loaded, ensure that it is loaded.
          if (at == main.setting->rules.used) {

            f_thread_unlock(&main.thread->lock.rule);

            // rule execution will re-use the existing cache, so save the current cache.
            const f_array_length_t cache_line_action = cache->action.line_action;
            const f_array_length_t cache_line_item = cache->action.line_item;

            const f_array_length_t cache_name_action_used = cache->action.name_action.used;
            const f_array_length_t cache_name_item_used = cache->action.name_item.used;
            const f_array_length_t cache_name_file_used = cache->action.name_file.used;

            char cache_name_action[cache_name_action_used];
            char cache_name_item[cache_name_item_used];
            char cache_name_file[cache_name_file_used];

            memcpy(cache_name_action, cache->action.name_action.string, cache->action.name_action.used);
            memcpy(cache_name_item, cache->action.name_item.string, cache->action.name_item.used);
            memcpy(cache_name_file, cache->action.name_file.string, cache->action.name_file.used);

            f_thread_lock_write(&main.thread->lock.rule);

            status = controller_rule_read(alias_rule, main, cache, &main.setting->rules.array[main.setting->rules.used]);

            // restore cache.
            memcpy(cache->action.name_action.string, cache_name_action, cache_name_action_used);
            memcpy(cache->action.name_item.string, cache_name_item, cache_name_item_used);
            memcpy(cache->action.name_file.string, cache_name_file, cache_name_file_used);

            cache->action.name_action.string[cache_name_action_used] = 0;
            cache->action.name_item.string[cache_name_item_used] = 0;
            cache->action.name_file.string[cache_name_file_used] = 0;

            cache->action.name_action.used = cache_name_action_used;
            cache->action.name_item.used = cache_name_item_used;
            cache->action.name_file.used = cache_name_file_used;

            cache->action.line_action = cache_line_action;
            cache->action.line_item = cache_line_item;

            if (F_status_is_error(status)) {

              if (main.data->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&main.thread->lock.print);

                controller_entry_error_print_cache(main.data->error, cache->action);

                f_thread_mutex_unlock(&main.thread->lock.print);
              }

              if (!simulate) {
                f_thread_unlock(&main.thread->lock.rule);

                break;
              }
            }
            else {
              main.setting->rules.used++;
            }

            f_thread_unlock(&main.thread->lock.rule);
          }
          else {
            f_thread_unlock(&main.thread->lock.rule);
          }

          if (F_status_is_error_not(status) && entry_action->type == controller_entry_action_type_rule) {
            rule_options = 0;

            if (simulate) {
              rule_options |= controller_rule_option_simulate;
            }

            if (entry_action->code & controller_entry_rule_code_require) {
              rule_options |= controller_rule_option_require;
            }

            if (entry_action->code & controller_entry_rule_code_wait) {
              rule_options |= controller_rule_option_wait;
            }

            if (entry_action->code & controller_entry_rule_code_asynchronous) {
              rule_options |= controller_rule_option_asynchronous;
            }

            status = controller_rule_process_begin(entry_action->code & controller_entry_rule_code_asynchronous, alias_rule, controller_rule_action_type_start, rule_options, stack, main, cache);

            if (!simulate || F_status_set_fine(status) == F_memory_not || status == F_child || status == F_signal) {
              break;
            }
          }
        }
        else if (entry_action->type == controller_entry_action_type_timeout) {

          if (simulate) {
            f_string_t code = "";

            if (entry_action->code == controller_entry_timeout_code_kill) {
              code = controller_string_kill_s;
            }
            else if (entry_action->code == controller_entry_timeout_code_start) {
              code = controller_string_start_s;
            }
            else if (entry_action->code == controller_entry_timeout_code_stop) {
              code = controller_string_stop_s;
            }

            f_thread_mutex_lock(&main.thread->lock.print);

            fprintf(main.data->output.stream, "%c", f_string_eol_s[0]);
            fprintf(main.data->output.stream, "Processing entry item action '");
            fprintf(main.data->output.stream, "%s%s%s", main.data->context.set.title.before->string, controller_string_timeout_s, main.data->context.set.title.after->string);
            fprintf(main.data->output.stream, "' setting '");
            fprintf(main.data->output.stream, "%s%s%s", main.data->context.set.important.before->string, code, main.data->context.set.important.after->string);
            fprintf(main.data->output.stream, "' to '");
            fprintf(main.data->output.stream, "%s%llu%s", main.data->context.set.important.before->string, entry_action->number, main.data->context.set.important.after->string);
            fprintf(main.data->output.stream, "' MegaTime (milliseconds).%c", f_string_eol_s[0]);

            f_thread_mutex_unlock(&main.thread->lock.print);
          }

          if (entry_action->code == controller_entry_timeout_code_kill) {
            main.setting->timeout_kill = entry_action->number;
          }
          else if (entry_action->code == controller_entry_timeout_code_start) {
            main.setting->timeout_start = entry_action->number;
          }
          else if (entry_action->code == controller_entry_timeout_code_stop) {
            main.setting->timeout_stop = entry_action->number;
          }
        }
        else if (entry_action->type == controller_entry_action_type_failsafe) {

          if (entry_action->number == 0 || entry_action->number >= main.setting->entry.items.used) {

            // This should not happen if the pre-process is working as designed, but in case it doesn't, return a critical error to prevent infinite recursion and similar errors.
            if (main.data->error.verbosity != f_console_verbosity_quiet) {
              f_thread_mutex_lock(&main.thread->lock.print);

              fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
              fprintf(main.data->error.to.stream, "%s%sInvalid entry item index ", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
              fprintf(main.data->error.to.stream, "%s%s%llu%s", main.data->error.context.after->string, main.data->error.notable.before->string, entry_action->number, main.data->error.notable.after->string);
              fprintf(main.data->error.to.stream, "%s detected.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

              controller_entry_error_print_cache(main.data->error, cache->action);

              f_thread_mutex_unlock(&main.thread->lock.print);
            }

            f_thread_unlock(&main.thread->lock.entry);

            return F_status_is_error(F_critical);
          }
          else {
            main.setting->failsafe_enabled = F_true;
            main.setting->failsafe_rule_id = entry_action->number;

            if (simulate) {
              f_thread_mutex_lock(&main.thread->lock.print);

              fprintf(main.data->output.stream, "%c", f_string_eol_s[0]);
              fprintf(main.data->output.stream, "Processing entry item action '");
              fprintf(main.data->output.stream, "%s%s%s", main.data->context.set.title.before->string, controller_string_failsafe_s, main.data->context.set.title.after->string);
              fprintf(main.data->output.stream, "' setting value to '");
              fprintf(main.data->output.stream, "%s%s%s", main.data->context.set.important.before->string, main.setting->entry.items.array[main.setting->failsafe_rule_id].name.string, main.data->context.set.important.after->string);
              fprintf(main.data->output.stream, "'.%c", f_string_eol_s[0]);

              f_thread_mutex_unlock(&main.thread->lock.print);
            }
          }
        }
      } // for

      if (main.thread->signal) {
        status = F_signal;
      }

      if (status == F_child || status == F_signal) break;

      cache->action.line_action = 0;
      cache->action.name_action.used = 0;

      if (F_status_is_error(status)) {
        if (!simulate || F_status_set_fine(status) == F_memory_not) {
          break;
        }
      }

      // end of actions found, so drop to previous loop in stack.
      if (cache->ats.array[at_j] == entry_actions->used) {

        // all actions for "main" are processed so there is nothing left to do.
        if (at_i == 0) break;

        at_i -= 2;
        at_j -= 2;

        cache->ats.used -= 2;
        cache->ats.array[at_j]++;

        cache->action.line_item = main.setting->entry.items.array[cache->ats.array[at_i]].line;
        cache->action.name_item.used = 0;

        status = controller_string_dynamic_append_terminated(main.setting->entry.items.array[cache->ats.array[at_i]].name, &cache->action.name_item);

        if (F_status_is_error(status)) {
          controller_entry_error_print(main.data->error, cache->action, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true, main.thread);

          break;
        }
      }
    } // for

    f_thread_unlock(&main.thread->lock.entry);

    if (status == F_child || status == F_signal) {
      return status;
    }

    if (F_status_is_error_not(status) && simulate) {
      f_thread_mutex_lock(&main.thread->lock.print);

      fprintf(main.data->output.stream, "%c", f_string_eol_s[0]);

      f_thread_mutex_unlock(&main.thread->lock.print);
    }

    return status;
  }
#endif // _di_controller_process_entry_

#ifndef _di_controller_status_simplify_
  f_status_t controller_status_simplify(const f_status_t status) {

    if (status == F_memory_not) {
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
  f_status_t controller_validate_environment_name(const f_string_static_t name) {

    if (!name.used) return F_none;

    f_status_t status = F_none;

    if (name.string[0] != '_') {
      status = f_utf_is_alpha(name.string, name.used);

      if (F_status_is_error(status)) return status;
      if (status == F_false) return F_false;
    }

    for (f_array_length_t i = f_macro_utf_byte_width(name.string[0]); i < name.used; i += f_macro_utf_byte_width(name.string[i])) {

      if (name.string[i] == '_') continue;

      status = f_utf_is_alpha_digit(name.string, name.used);

      if (F_status_is_error(status)) return status;
      if (status == F_false) return F_false;
    } // for

    return F_true;
  }
#endif // _di_controller_validate_define_name_

#ifndef _di_controller_validate_has_graph_
  f_status_t controller_validate_has_graph(const f_string_static_t name) {

    if (!name.used) return F_none;

    f_status_t status = F_none;

    for (f_array_length_t i = 0; i < name.used; i += f_macro_utf_byte_width(name.string[i])) {

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
