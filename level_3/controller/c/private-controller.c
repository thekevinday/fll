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

    f_status_t status = f_string_dynamic_append_nulless(source, destination);
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
  f_status_t controller_file_load(const bool required, const f_string_t path_prefix, const f_string_static_t path_name, const f_string_t path_suffix, const f_array_length_t path_prefix_length, const f_array_length_t path_suffix_length, controller_global_t global, controller_cache_t *cache) {

    f_status_t status = F_none;
    f_file_t file = f_file_t_initialize;

    cache->action.name_file.used = 0;
    cache->buffer_file.used = 0;

    macro_f_time_spec_t_clear(cache->timestamp);

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
      if (global.main->error.verbosity != f_console_verbosity_quiet) {
        controller_error_print(global.main->error, F_status_set_fine(status), "f_string_append", F_true, global.thread);
      }

      return status;
    }

    status = f_string_dynamic_terminate_after(&cache->action.name_file);

    if (F_status_is_error(status)) {
      if (global.main->error.verbosity != f_console_verbosity_quiet) {
        controller_error_print(global.main->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, global.thread);
      }

      return status;
    }

    const f_array_length_t path_length = global.setting->path_setting.used ? global.setting->path_setting.used + f_path_separator_length + cache->action.name_file.used : cache->action.name_file.used;
    char path[path_length + 1];

    if (global.setting->path_setting.used) {
      memcpy(path, global.setting->path_setting.string, global.setting->path_setting.used);
      memcpy(path + global.setting->path_setting.used + f_path_separator_length, cache->action.name_file.string, cache->action.name_file.used);

      path[global.setting->path_setting.used] = f_path_separator_s[0];
    }

    path[path_length] = 0;

    status = f_file_stream_open(path, 0, &file);

    if (F_status_is_error(status)) {
      if (!required && F_status_set_fine(status) == F_file_found_not) {
        f_file_stream_close(F_true, &file);

        return F_file_found_not;
      }

      if (global.main->error.verbosity != f_console_verbosity_quiet) {
        f_thread_mutex_lock(&global.thread->lock.print);

        fll_error_file_print(global.main->error, F_status_set_fine(status), "f_file_stream_open", F_true, path, "open", fll_error_file_type_file);

        controller_print_unlock_flush(global.main->error.to.stream, &global.thread->lock.print);
      }
    }
    else {
      status = f_file_stream_read(file, &cache->buffer_file);

      if (F_status_is_error(status)) {
        if (global.main->error.verbosity != f_console_verbosity_quiet) {
          f_thread_mutex_lock(&global.thread->lock.print);

          fll_error_file_print(global.main->error, F_status_set_fine(status), "f_file_stream_read", F_true, path, "read", fll_error_file_type_file);

          controller_print_unlock_flush(global.main->error.to.stream, &global.thread->lock.print);
        }
      }
    }

    f_file_stream_close(F_true, &file);

    if (F_status_is_error_not(status)) {
      struct stat stat_file;

      status = f_file_stat(path, F_true, &stat_file);

      if (F_status_is_error(status)) {
        if (global.main->error.verbosity != f_console_verbosity_quiet) {
          f_thread_mutex_lock(&global.thread->lock.print);

          fll_error_file_print(global.main->error, F_status_set_fine(status), "f_file_stat", F_true, path, "stat", fll_error_file_type_file);

          controller_print_unlock_flush(global.main->error.to.stream, &global.thread->lock.print);
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
  f_status_t controller_file_pid_create(const pid_t pid, const f_string_static_t path) {

    f_status_t status = F_none;

    // the file exists, do not attempt to overwrite.
    if (f_file_exists(path.string) == F_true) {
      return F_status_set_error(F_file_found);
    }

    {
      f_string_dynamic_t path_directory = f_string_dynamic_t_initialize;

      status = f_file_name_directory(path.string, path.used, &path_directory);

      if (F_status_is_error_not(status)) {
        status = f_directory_exists(path_directory.string);
      }

      macro_f_string_dynamic_t_delete_simple(path_directory)

      if (F_status_is_error(status)) return status;

      // the directory does not exist so do not bother attempting to create a pid file.
      if (status == F_false) {
        return F_status_set_error(F_directory_not);
      }
    }

    f_file_t file = f_file_t_initialize;

    file.flag = f_file_flag_write_only;

    status = f_file_stream_open(path.string, f_file_open_mode_truncate_s, &file);
    if (F_status_is_error(status)) return status;

    fprintf(file.stream, "%d%c", pid, f_string_eol_s[0]);

    f_file_stream_close(F_true, &file);

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_controller_file_pid_create_

#ifndef _di_controller_file_pid_delete_
  f_status_t controller_file_pid_delete(const pid_t pid, const f_string_static_t path) {

    // only delete if the file exists and there is no error while checking.
    if (f_file_exists(path.string) != F_true) {
      return F_none;
    }

    f_status_t status = F_none;
    f_file_t pid_file = f_file_t_initialize;

    status = f_file_stream_open(path.string, f_file_open_mode_read_s, &pid_file);
    if (F_status_is_error(status)) return status;

    f_string_dynamic_t pid_buffer = f_string_dynamic_t_initialize;

    status = f_file_stream_read(pid_file, &pid_buffer);

    if (F_status_is_error_not(status)) {
      status = f_file_stream_close(F_true, &pid_file);
    }

    if (F_status_is_error_not(status)) {
      f_number_unsigned_t number = 0;
      f_string_range_t range = macro_f_string_range_t_initialize(pid_buffer.used);

      for (; range.start < pid_buffer.used; ++range.start) {
        if (!isspace(pid_buffer.string[range.start])) break;
      } // for

      for (; range.stop > 0; --range.stop) {
        if (!isspace(pid_buffer.string[range.stop])) break;
      } // for

      status = fl_conversion_string_to_decimal_unsigned(pid_buffer.string, range, &number);

      if (F_status_is_error_not(status) && number == pid) {
        status = f_file_remove(path.string);
      }
      else {
        status = F_status_set_error(F_number_not);
      }
    }

    macro_f_string_dynamic_t_delete_simple(pid_buffer);

    return status;
  }
#endif // _di_controller_file_pid_delete_

#ifndef _di_controller_file_pid_read_
  f_status_t controller_file_pid_read(const f_string_static_t path, pid_t *pid) {

    *pid = 0;

    f_status_t status = f_file_exists(path.string);
    if (F_status_is_error(status)) return status;

    if (status != F_true) {
      return F_data_not;
    }

    f_file_t pid_file = f_file_t_initialize;

    status = f_file_stream_open(path.string, f_file_open_mode_read_s, &pid_file);
    if (F_status_is_error(status)) return status;

    f_string_dynamic_t pid_buffer = f_string_dynamic_t_initialize;

    status = f_file_stream_read(pid_file, &pid_buffer);

    if (F_status_is_error_not(status)) {
      status = f_file_stream_close(F_true, &pid_file);
    }

    if (F_status_is_error_not(status)) {
      f_number_unsigned_t number = 0;
      f_string_range_t range = macro_f_string_range_t_initialize(pid_buffer.used);

      for (; range.start < pid_buffer.used; ++range.start) {
        if (!isspace(pid_buffer.string[range.start])) break;
      } // for

      for (; range.stop > 0; --range.stop) {
        if (!isspace(pid_buffer.string[range.stop])) break;
      } // for

      status = fl_conversion_string_to_decimal_unsigned(pid_buffer.string, range, &number);

      if (F_status_is_error_not(status)) {
        *pid = (pid_t) number;
      }
    }

    macro_f_string_dynamic_t_delete_simple(pid_buffer);

    return status;
  }
#endif // _di_controller_file_pid_read_

#ifndef _di_controller_find_process_
  f_status_t controller_find_process(const f_array_length_t action, const f_string_static_t alias, const controller_processs_t processs, f_array_length_t *at) {

    if (!alias.used) return F_none;
    if (!processs.used) return F_false;

    for (f_array_length_t i = 0; i < processs.used; ++i) {

      if (processs.array[i] && processs.array[i]->action == action && fl_string_dynamic_compare(alias, processs.array[i]->rule.alias) == F_equal_to) {
        if (at) *at = i;

        return F_true;
      }
    } // for

    return F_false;
  }
#endif // _di_controller_find_process_

#ifndef _di_controller_get_id_user_
  f_status_t controller_get_id_user(const f_string_static_t buffer, const f_string_range_t range, controller_cache_t *cache, uid_t *id) {

    f_number_unsigned_t number = 0;

    f_status_t status = fl_conversion_string_to_number_unsigned(buffer.string, range, &number);

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

    f_status_t status = fl_conversion_string_to_number_unsigned(buffer.string, range, &number);

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
  f_status_t controller_perform_ready(const bool is_entry, controller_global_t global, controller_cache_t *cache) {

    f_status_t status = F_none;

    // only create pid file when not in validate mode.
    if (is_entry && global.main->parameters[controller_parameter_validate].result == f_console_result_none) {

      status = controller_file_pid_create(global.main->pid, global.setting->path_pid);

      // report pid file error but because this could be an "init" program, consider the pid file as optional and continue on.
      if (F_status_is_error(status)) {

        // always return immediately on memory errors.
        if (F_status_set_fine(status) == F_memory_not) {
          if (global.main->error.verbosity != f_console_verbosity_quiet) {
            f_thread_mutex_lock(&global.thread->lock.print);

            fll_error_file_print(global.main->error, F_status_set_fine(status), "controller_file_pid_create", F_true, global.setting->path_pid.string, "create", fll_error_file_type_file);

            controller_entry_error_print_cache(is_entry, global.main->error, cache->action);

            controller_print_unlock_flush(global.main->error.to.stream, &global.thread->lock.print);
          }

          return status;
        }

        if (global.main->warning.verbosity == f_console_verbosity_debug) {
          f_thread_mutex_lock(&global.thread->lock.print);

          fll_error_file_print(global.main->warning, F_status_set_fine(status), "controller_file_pid_create", F_true, global.setting->path_pid.string, "create", fll_error_file_type_file);

          controller_entry_error_print_cache(is_entry, global.main->warning, cache->action);

          controller_print_unlock_flush(global.main->warning.to.stream, &global.thread->lock.print);
        }

        status = F_none;
      }
      else {
        global.setting->pid_created = F_true;
      }
    }

    return status;
  }
#endif // _di_controller_perform_ready_

#ifndef _di_controller_preprocess_entry_
  f_status_t controller_preprocess_entry(const bool is_entry, controller_global_t global, controller_cache_t *cache) {

    f_status_t status = F_none;
    f_status_t status2 = F_none;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_array_length_t at_i = 0;
    f_array_length_t at_j = 1;

    controller_entry_t *entry = is_entry ? &global.setting->entry : &global.setting->exit;
    controller_entry_actions_t *actions = 0;

    uint8_t error_has = F_false;

    // this effectively sets the read for an entry and resets the ready for an exit.
    // @todo should there be a ready_exit instead?
    // @todo the global.setting->ready in this function may need mutex lock protection.
    global.setting->ready = controller_setting_ready_no;

    cache->ats.used = 0;

    cache->action.line_action = 0;
    cache->action.line_item = 0;
    cache->action.name_action.used = 0;
    cache->action.name_item.used = 0;

    macro_f_array_lengths_t_increase_by(status, cache->ats, controller_common_allocation_small)

    if (F_status_is_error(status)) {
      controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status), "macro_f_array_lengths_t_increase_by", F_true, global.thread);

      return status;
    }

    // utilize the ats cache as an item execution stack (at_i is for item index, and at_j (at_i + 1) is for action index).
    cache->ats.array[0] = 0;
    cache->ats.array[1] = 0;
    cache->ats.used = 2;

    cache->action.line_item = entry->items.array[0].line;
    cache->action.name_item.used = 0;

    status = controller_string_dynamic_append_terminated(entry->items.array[0].name, &cache->action.name_item);

    if (F_status_is_error(status)) {
      controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true, global.thread);

      return status;
    }

    while (controller_thread_is_enabled(is_entry, global.thread)) {

      actions = &entry->items.array[cache->ats.array[at_i]].actions;

      for (; cache->ats.array[at_j] < actions->used && controller_thread_is_enabled(is_entry, global.thread); ++cache->ats.array[at_j]) {

        cache->action.line_action = actions->array[cache->ats.array[at_j]].line;
        cache->action.name_action.used = 0;

        status2 = controller_string_dynamic_append_terminated(controller_entry_action_type_name(actions->array[cache->ats.array[at_j]].type), &cache->action.name_action);

        if (F_status_is_error(status2)) {
          controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status2), "controller_string_dynamic_append_terminated", F_true, global.thread);

          return status2;
        }

        if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_ready) {

          if (global.setting->ready == controller_setting_ready_wait) {
            if (global.main->warning.verbosity == f_console_verbosity_debug) {
              f_thread_mutex_lock(&global.thread->lock.print);

              fprintf(global.main->warning.to.stream, "%c", f_string_eol_s[0]);
              fprintf(global.main->warning.to.stream, "%s%sMultiple '", global.main->warning.context.before->string, global.main->warning.prefix ? global.main->warning.prefix : f_string_empty_s);
              fprintf(global.main->warning.to.stream, "%s%s%s%s", global.main->warning.context.after->string, global.main->warning.notable.before->string, controller_string_ready_s, global.main->warning.notable.after->string);
              fprintf(global.main->warning.to.stream, "%s' %s item actions detected; only the first will be used.%s%c", global.main->warning.context.before->string, is_entry ? controller_string_entry_s : controller_string_exit_s, global.main->warning.context.after->string, f_string_eol_s[0]);

              controller_entry_error_print_cache(is_entry, global.main->warning, cache->action);

              controller_print_unlock_flush(global.main->warning.to.stream, &global.thread->lock.print);
            }
          }

          global.setting->ready = controller_setting_ready_wait;
        }
        else if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_item) {
          error_has = F_false;

          // "main" is not allowed to be used for an "item" and "setting" is not an executable "item".
          if (fl_string_dynamic_compare_string(controller_string_main_s, actions->array[cache->ats.array[at_j]].parameters.array[0], controller_string_main_length) == F_equal_to) {
            continue;
          }
          else if (fl_string_dynamic_compare_string(controller_string_setting_s, actions->array[cache->ats.array[at_j]].parameters.array[0], controller_string_setting_length) == F_equal_to) {
            continue;
          }

          // walk though each items and check to see if the item actually exists.
          for (i = 1; i < entry->items.used && controller_thread_is_enabled(is_entry, global.thread); ++i) {

            if (fl_string_dynamic_compare(entry->items.array[i].name, actions->array[cache->ats.array[at_j]].parameters.array[0]) == F_equal_to) {

              // check to see if "i" is already in the stack (to prevent recursion) (skipping main).
              for (j = 2; j < cache->ats.used; j += 2) {

                if (cache->ats.array[j] == i) {
                  if (global.main->error.verbosity != f_console_verbosity_quiet) {
                    f_thread_mutex_lock(&global.thread->lock.print);

                    fprintf(global.main->error.to.stream, "%c", f_string_eol_s[0]);
                    fprintf(global.main->error.to.stream, "%s%sThe %s item named '", global.main->error.context.before->string, global.main->error.prefix ? global.main->error.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s);
                    fprintf(global.main->error.to.stream, "%s%s%s%s", global.main->error.context.after->string, global.main->error.notable.before->string, entry->items.array[i].name.string, global.main->error.notable.after->string);
                    fprintf(global.main->error.to.stream, "%s' cannot be executed because recursion is not allowed.%s%c", global.main->error.context.before->string, global.main->error.context.after->string, f_string_eol_s[0]);

                    controller_entry_error_print_cache(is_entry, global.main->error, cache->action);

                    controller_print_unlock_flush(global.main->error.to.stream, &global.thread->lock.print);
                  }

                  if (F_status_is_error_not(status)) {
                    status = F_status_set_error(F_recurse);
                  }

                  error_has = F_true;
                  break;
                }
              } // for

              if (error_has) break;

              macro_f_array_lengths_t_increase_by(status2, cache->ats, controller_common_allocation_small)

              if (F_status_is_error(status2)) {
                controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status2), "macro_f_array_lengths_t_increase_by", F_true, global.thread);

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
              cache->action.line_item = entry->items.array[i].line;

              status2 = controller_string_dynamic_append_terminated(entry->items.array[i].name, &cache->action.name_item);

              if (F_status_is_error(status2)) {
                controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status2), "controller_string_dynamic_append_terminated", F_true, global.thread);

                return status2;
              }

              break;
            }
          } // for

          if (error_has || i >= entry->items.used) {
            if (i >= entry->items.used) {
              if (global.main->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&global.thread->lock.print);

                fprintf(global.main->error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(global.main->error.to.stream, "%s%sThe %s item named '", global.main->error.context.before->string, global.main->error.prefix ? global.main->error.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s);
                fprintf(global.main->error.to.stream, "%s%s%s%s", global.main->error.context.after->string, global.main->error.notable.before->string, actions->array[cache->ats.array[at_j]].parameters.array[0].string, global.main->error.notable.after->string);
                fprintf(global.main->error.to.stream, "%s' does not exist.%s%c", global.main->error.context.before->string, global.main->error.context.after->string, f_string_eol_s[0]);

                controller_entry_error_print_cache(is_entry, global.main->error, cache->action);

                controller_print_unlock_flush(global.main->error.to.stream, &global.thread->lock.print);
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
        ++cache->ats.array[at_j];

        cache->action.line_item = entry->items.array[cache->ats.array[at_i]].line;
        cache->action.name_item.used = 0;

        status2 = controller_string_dynamic_append_terminated(entry->items.array[cache->ats.array[at_i]].name, &cache->action.name_item);

        if (F_status_is_error(status2)) {
          controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status2), "controller_string_dynamic_append_terminated", F_true, global.thread);

          return status2;
        }
      }
    } // while

    if (!controller_thread_is_enabled(is_entry, global.thread)) {
      return F_signal;
    }

    // if ready was never found in the entry, then default to always ready.
    if (global.setting->ready == controller_setting_ready_no) {
      global.setting->ready = controller_setting_ready_yes;
    }

    return status;
  }
#endif // _di_controller_preprocess_entry_

#ifndef _di_controller_process_entry_
  f_status_t controller_process_entry(const bool failsafe, const bool is_entry, controller_global_t *global, controller_cache_t *cache) {

    f_status_t status = F_none;
    f_status_t status_lock = F_none;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_array_length_t at_i = 0;
    f_array_length_t at_j = 1;

    uint8_t options_force = 0;
    uint8_t options_process = 0;

    controller_entry_t *entry = is_entry ? &global->setting->entry : &global->setting->exit;
    controller_entry_action_t *entry_action = 0;
    controller_entry_actions_t *entry_actions = 0;
    controller_process_t *process = 0;

    // an empty stack is used here because each rule here is the first rule run in the rule's scope.
    const f_array_lengths_t stack = f_array_lengths_t_initialize;

    cache->ats.used = 0;
    cache->stack.used = 0;

    cache->action.line_action = 0;
    cache->action.line_item = 0;
    cache->action.name_action.used = 0;
    cache->action.name_item.used = 0;

    if (global->setting->ready == controller_setting_ready_yes) {
      status = controller_perform_ready(is_entry, *global, cache);
      if (F_status_is_error(status)) return status;
    }

    macro_f_array_lengths_t_increase_by(status, cache->ats, controller_common_allocation_small)

    if (F_status_is_error(status)) {
      controller_entry_error_print(is_entry, global->main->error, cache->action, F_status_set_fine(status), "macro_f_array_lengths_t_increase_by", F_true, global->thread);

      return status;
    }

    // utilize the ats cache as an item execution stack (at_i is for item index, and at_j (at_i + 1) is for action index).
    cache->ats.array[0] = failsafe ? global->setting->failsafe_item_id : 0;
    cache->ats.array[1] = 0;
    cache->ats.used = 2;

    cache->action.line_item = entry->items.array[cache->ats.array[0]].line;
    cache->action.name_item.used = 0;

    status = controller_string_dynamic_append_terminated(entry->items.array[cache->ats.array[0]].name, &cache->action.name_item);

    if (F_status_is_error(status)) {
      controller_entry_error_print(is_entry, global->main->error, cache->action, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true, global->thread);

      return status;
    }

    if (global->main->parameters[controller_parameter_simulate].result == f_console_result_found || global->main->error.verbosity == f_console_verbosity_verbose) {
      if (global->main->error.verbosity != f_console_verbosity_quiet) {
        f_thread_mutex_lock(&global->thread->lock.print);

        fprintf(global->main->output.stream, "%c", f_string_eol_s[0]);
        fprintf(global->main->output.stream, "Processing %s%s item '", (failsafe ? "failsafe " : ""), is_entry ? controller_string_entry_s : controller_string_exit_s);
        fprintf(global->main->output.stream, "%s%s%s", global->main->context.set.title.before->string, cache->action.name_item.string, global->main->context.set.title.after->string);
        fprintf(global->main->output.stream, "'.%c", f_string_eol_s[0]);

        controller_print_unlock_flush(global->main->output.stream, &global->thread->lock.print);
      }
    }

    while (controller_thread_is_enabled(is_entry, global->thread)) {

      entry_actions = &entry->items.array[cache->ats.array[at_i]].actions;

      for (; cache->ats.array[at_j] < entry_actions->used && controller_thread_is_enabled(is_entry, global->thread); ++cache->ats.array[at_j]) {

        entry_action = &entry_actions->array[cache->ats.array[at_j]];

        cache->action.line_action = entry_action->line;
        cache->action.name_action.used = 0;

        status = controller_string_dynamic_append_terminated(controller_entry_action_type_name(entry_action->type), &cache->action.name_action);

        if (F_status_is_error(status)) {
          controller_entry_error_print(is_entry, global->main->error, cache->action, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true, global->thread);

          return status;
        }

        if (F_status_is_error(entry_action->status)) {
          if (controller_entry_action_type_is_rule(entry_action->type)) {
            if (global->main->parameters[controller_parameter_simulate].result == f_console_result_found) {
              if (global->main->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&global->thread->lock.print);

                fprintf(global->main->output.stream, "%c", f_string_eol_s[0]);
                fprintf(global->main->output.stream, "The %s item action '", is_entry ? controller_string_entry_s : controller_string_exit_s);
                fprintf(global->main->output.stream, "%s%s%s", global->main->context.set.title.before->string, cache->action.name_action.string, global->main->context.set.title.after->string);

                if (entry_action->parameters.used) {
                  fprintf(global->main->output.stream, "%s", f_string_space_s);
                  fprintf(global->main->output.stream, "%s", global->main->context.set.notable.before->string);
                  controller_entry_action_parameters_print(global->main->output.stream, entry_actions->array[cache->ats.array[at_j]]);
                  fprintf(global->main->output.stream, "%s", global->main->context.set.notable.after->string);
                }

                fprintf(global->main->output.stream, "' is %s and is in a %sfailed%s state, skipping execution.%c", entry_action->code & controller_entry_rule_code_require ? "required" : "optional", global->main->error.context.before->string, global->main->error.context.after->string, f_string_eol_s[0]);

                controller_print_unlock_flush(global->main->output.stream, &global->thread->lock.print);
              }
            }
            else if (entry_action->code & controller_entry_rule_code_require) {
              if (global->main->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&global->thread->lock.print);

                fprintf(global->main->error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(global->main->error.to.stream, "%s%sThe %s item action '", global->main->error.context.before->string, global->main->error.prefix ? global->main->error.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s);
                fprintf(global->main->error.to.stream, "%s%s%s", global->main->error.context.after->string, global->main->error.notable.before->string, cache->action.name_action.string);

                if (entry_action->parameters.used) {
                  fprintf(global->main->error.to.stream, "%s", f_string_space_s);
                  controller_entry_action_parameters_print(global->main->error.to.stream, entry_actions->array[cache->ats.array[at_j]]);
                }

                fprintf(global->main->error.to.stream, "%s%s' is ", global->main->error.notable.after->string, global->main->error.context.before->string);
                fprintf(global->main->error.to.stream, "%s%srequired%s", global->main->error.context.after->string, global->main->error.notable.before->string, global->main->error.notable.after->string);
                fprintf(global->main->error.to.stream, "%s and is in a ", global->main->error.context.before->string);
                fprintf(global->main->error.to.stream, "%s%sfailed%s", global->main->error.context.after->string, global->main->error.notable.before->string, global->main->error.notable.after->string);
                fprintf(global->main->error.to.stream, "%s state, skipping execution.%s%c", global->main->error.context.before->string, global->main->error.context.after->string, f_string_eol_s[0]);

                controller_entry_error_print_cache(is_entry, global->main->error, cache->action);

                controller_print_unlock_flush(global->main->error.to.stream, &global->thread->lock.print);
              }

              return F_status_is_error(F_require);
            }
            else if (global->main->warning.verbosity == f_console_verbosity_verbose || global->main->warning.verbosity == f_console_verbosity_debug) {
              f_thread_mutex_lock(&global->thread->lock.print);

              fprintf(global->main->warning.to.stream, "%c", f_string_eol_s[0]);
              fprintf(global->main->warning.to.stream, "%s%sThe %s item action '", global->main->warning.context.before->string, global->main->warning.prefix ? global->main->warning.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s);
              fprintf(global->main->warning.to.stream, "%s%s%s", global->main->warning.context.after->string, global->main->warning.notable.before->string, cache->action.name_action.string);

              if (entry_action->parameters.used) {
                fprintf(global->main->warning.to.stream, "%s", f_string_space_s);
                controller_entry_action_parameters_print(global->main->warning.to.stream, entry_actions->array[cache->ats.array[at_j]]);
              }

              fprintf(global->main->warning.to.stream, "%s%s' is ", global->main->warning.notable.after->string, global->main->warning.context.before->string);
              fprintf(global->main->warning.to.stream, "%s%srequired%s", global->main->warning.context.after->string, global->main->warning.notable.before->string, global->main->warning.notable.after->string);
              fprintf(global->main->warning.to.stream, "%s and is in a ", global->main->warning.context.before->string);
              fprintf(global->main->warning.to.stream, "%s%sfailed%s", global->main->warning.context.after->string, global->main->warning.notable.before->string, global->main->warning.notable.after->string);
              fprintf(global->main->warning.to.stream, "%s state, skipping execution.%s%c", global->main->warning.context.before->string, global->main->warning.context.after->string, f_string_eol_s[0]);

              controller_entry_error_print_cache(is_entry, global->main->warning, cache->action);

              controller_print_unlock_flush(global->main->warning.to.stream, &global->thread->lock.print);
            }
          }
          else {
            if (global->main->parameters[controller_parameter_simulate].result == f_console_result_found) {
              if (global->main->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&global->thread->lock.print);

                fprintf(global->main->output.stream, "%c", f_string_eol_s[0]);
                fprintf(global->main->output.stream, "The %s item action '", is_entry ? controller_string_entry_s : controller_string_exit_s);
                fprintf(global->main->output.stream, "%s%s%s", global->main->context.set.title.before->string, cache->action.name_action.string, global->main->context.set.title.after->string);

                if (entry_action->parameters.used) {
                  fprintf(global->main->output.stream, "%s", f_string_space_s);
                  fprintf(global->main->output.stream, "%s", global->main->context.set.notable.before->string);
                  controller_entry_action_parameters_print(global->main->output.stream, entry_actions->array[cache->ats.array[at_j]]);
                  fprintf(global->main->output.stream, "%s", global->main->context.set.notable.after->string);
                }

                fprintf(global->main->output.stream, "' is in a %sfailed%s state, skipping.%c", global->main->error.context.before->string, global->main->error.context.after->string, f_string_eol_s[0]);

                controller_print_unlock_flush(global->main->output.stream, &global->thread->lock.print);
              }
            }
            else if (global->main->warning.verbosity == f_console_verbosity_debug || global->main->error.verbosity == f_console_verbosity_verbose) {
              f_thread_mutex_lock(&global->thread->lock.print);

              fprintf(global->main->warning.to.stream, "%c", f_string_eol_s[0]);
              fprintf(global->main->warning.to.stream, "%s%sThe %s item action '", global->main->warning.context.before->string, global->main->warning.prefix ? global->main->warning.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s);
              fprintf(global->main->warning.to.stream, "%s%s", global->main->warning.notable.before->string, cache->action.name_action.string);

              if (entry_action->parameters.used) {
                fprintf(global->main->warning.to.stream, "%s", f_string_space_s);
                controller_entry_action_parameters_print(global->main->warning.to.stream, entry_actions->array[cache->ats.array[at_j]]);
              }

              fprintf(global->main->warning.to.stream, "%s' is in a ", global->main->warning.notable.after->string);
              fprintf(global->main->warning.to.stream, "%s%sfailed%s", global->main->warning.context.after->string, global->main->warning.notable.before->string, global->main->warning.notable.after->string);
              fprintf(global->main->warning.to.stream, "%s state, skipping.%s%c", global->main->warning.context.before->string, global->main->warning.context.after->string, f_string_eol_s[0]);

              controller_entry_error_print_cache(is_entry, global->main->warning, cache->action);

              controller_print_unlock_flush(global->main->warning.to.stream, &global->thread->lock.print);
            }
          }

          continue;
        }

        if (entry_action->type == controller_entry_action_type_ready) {
          if (entry_action->code & controller_entry_rule_code_wait) {
            if (global->main->parameters[controller_parameter_simulate].result == f_console_result_found || global->main->error.verbosity == f_console_verbosity_verbose) {
              if (global->main->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&global->thread->lock.print);

                fprintf(global->main->output.stream, "%c", f_string_eol_s[0]);
                fprintf(global->main->output.stream, "Waiting before processing %s item action '", is_entry ? controller_string_entry_s : controller_string_exit_s);
                fprintf(global->main->output.stream, "%s%s%s", global->main->context.set.title.before->string, controller_string_ready_s, global->main->context.set.title.after->string);
                fprintf(global->main->output.stream, "'.%c", f_string_eol_s[0]);

                controller_print_unlock_flush(global->main->output.stream, &global->thread->lock.print);
              }
            }

            if (global->main->parameters[controller_parameter_validate].result == f_console_result_none) {
              controller_rule_wait_all(is_entry, *global, F_false, process);
            }
          }

          if (global->setting->ready == controller_setting_ready_wait) {
            if (global->main->parameters[controller_parameter_simulate].result == f_console_result_found || global->main->error.verbosity == f_console_verbosity_verbose) {
              if (global->main->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&global->thread->lock.print);

                fprintf(global->main->output.stream, "%c", f_string_eol_s[0]);
                fprintf(global->main->output.stream, "Processing %s item action '", is_entry ? controller_string_entry_s : controller_string_exit_s);
                fprintf(global->main->output.stream, "%s%s%s", global->main->context.set.title.before->string, controller_string_ready_s, global->main->context.set.title.after->string);
                fprintf(global->main->output.stream, "'.%c", f_string_eol_s[0]);

                controller_print_unlock_flush(global->main->output.stream, &global->thread->lock.print);
              }
            }

            if (global->main->parameters[controller_parameter_simulate].result == f_console_result_none) {
              status = controller_perform_ready(is_entry, *global, cache);

              if (F_status_is_error(status)) return status;
            }

            global->setting->ready = controller_setting_ready_yes;
          }
          else if (global->main->parameters[controller_parameter_simulate].result == f_console_result_found || global->main->error.verbosity == f_console_verbosity_verbose) {
            if (global->main->error.verbosity != f_console_verbosity_quiet) {
              f_thread_mutex_lock(&global->thread->lock.print);

              fprintf(global->main->output.stream, "%c", f_string_eol_s[0]);
              fprintf(global->main->output.stream, "Ignoring %s item action '", is_entry ? controller_string_entry_s : controller_string_exit_s);
              fprintf(global->main->output.stream, "%s%s%s", global->main->context.set.title.before->string, controller_string_ready_s, global->main->context.set.title.after->string);
              fprintf(global->main->output.stream, "', state already is ready.%c", f_string_eol_s[0]);

              controller_print_unlock_flush(global->main->output.stream, &global->thread->lock.print);
            }
          }
        }
        else if (entry_action->type == controller_entry_action_type_item) {
          if (entry_action->number == 0 || entry_action->number >= entry->items.used || failsafe && entry_action->number == global->setting->failsafe_item_id) {

            // This should not happen if the pre-process is working as designed, but in case it doesn't, return a critical error to prevent infinite recursion and similar errors.
            if (global->main->error.verbosity != f_console_verbosity_quiet) {
              f_thread_mutex_lock(&global->thread->lock.print);

              fprintf(global->main->error.to.stream, "%c", f_string_eol_s[0]);
              fprintf(global->main->error.to.stream, "%s%sInvalid %s item index ", global->main->error.context.before->string, global->main->error.prefix ? global->main->error.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s);
              fprintf(global->main->error.to.stream, "%s%s%llu%s", global->main->error.context.after->string, global->main->error.notable.before->string, entry_action->number, global->main->error.notable.after->string);
              fprintf(global->main->error.to.stream, "%s detected.%s%c", global->main->error.context.before->string, global->main->error.context.after->string, f_string_eol_s[0]);

              controller_entry_error_print_cache(is_entry, global->main->error, cache->action);

              controller_print_unlock_flush(global->main->error.to.stream, &global->thread->lock.print);
            }

            return F_status_is_error(F_critical);
          }

          macro_f_array_lengths_t_increase_by(status, cache->ats, controller_common_allocation_small)

          if (F_status_is_error(status)) {
            controller_entry_error_print(is_entry, global->main->error, cache->action, F_status_set_fine(status), "macro_f_array_lengths_t_increase_by", F_true, global->thread);

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
          cache->action.line_item = entry->items.array[cache->ats.array[at_i]].line;

          status = controller_string_dynamic_append_terminated(entry->items.array[cache->ats.array[at_i]].name, &cache->action.name_item);

          if (F_status_is_error(status)) {
            controller_entry_error_print(is_entry, global->main->error, cache->action, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true, global->thread);

            return status;
          }

          if (global->main->parameters[controller_parameter_simulate].result == f_console_result_found || global->main->error.verbosity == f_console_verbosity_verbose) {
            if (global->main->error.verbosity != f_console_verbosity_quiet) {
              f_thread_mutex_lock(&global->thread->lock.print);

              fprintf(global->main->output.stream, "%c", f_string_eol_s[0]);
              fprintf(global->main->output.stream, "Processing %s item '", is_entry ? controller_string_entry_s : controller_string_exit_s);
              fprintf(global->main->output.stream, "%s%s%s", global->main->context.set.title.before->string, cache->action.name_item.string, global->main->context.set.title.after->string);
              fprintf(global->main->output.stream, "'.%c", f_string_eol_s[0]);

              controller_print_unlock_flush(global->main->output.stream, &global->thread->lock.print);
            }
          }

          // exit inner loop to force restarting and start processing the requested item.
          break;
        }
        else if (entry_action->type == controller_entry_action_type_consider || controller_entry_action_type_is_rule(entry_action->type)) {

          status_lock = controller_lock_write(is_entry, global->thread, &global->thread->lock.rule);

          if (status_lock == F_signal || F_status_is_error(status_lock)) {
            controller_lock_error_critical_print(global->main->error, F_status_set_fine(status_lock), F_false, global->thread);
            break;
          }

          status = controller_rules_increase(&global->setting->rules);

          f_thread_unlock(&global->thread->lock.rule);

          if (F_status_is_error(status)) {
            controller_entry_error_print(is_entry, global->main->error, cache->action, F_status_set_fine(status), "controller_rules_increase", F_true, global->thread);

            return status;
          }

          const f_array_length_t id_rule_length = entry_action->parameters.array[0].used + entry_action->parameters.array[1].used + 1;
          char id_rule_name[id_rule_length + 1];
          const f_string_static_t alias_rule = macro_f_string_static_t_initialize(id_rule_name, id_rule_length);

          memcpy(id_rule_name, entry_action->parameters.array[0].string, entry_action->parameters.array[0].used);
          memcpy(id_rule_name + entry_action->parameters.array[0].used + 1, entry_action->parameters.array[1].string, entry_action->parameters.array[1].used);

          id_rule_name[entry_action->parameters.array[0].used] = f_path_separator_s[0];
          id_rule_name[id_rule_length] = 0;

          status_lock = controller_lock_read(is_entry, global->thread, &global->thread->lock.rule);

          if (status_lock == F_signal || F_status_is_error(status_lock)) {
            controller_lock_error_critical_print(global->main->error, F_status_set_fine(status_lock), F_true, global->thread);

            break;
          }

          status = controller_rule_find(alias_rule, global->setting->rules, 0);

          f_thread_unlock(&global->thread->lock.rule);

          if (global->main->parameters[controller_parameter_simulate].result == f_console_result_found || global->main->error.verbosity == f_console_verbosity_verbose) {
            if (global->main->error.verbosity != f_console_verbosity_quiet) {
              f_thread_mutex_lock(&global->thread->lock.print);

              fprintf(global->main->output.stream, "%c", f_string_eol_s[0]);
              fprintf(global->main->output.stream, "%s %s item rule '", entry_action->type == controller_entry_action_type_consider ? "Considering" : "Processing", is_entry ? controller_string_entry_s : controller_string_exit_s);
              fprintf(global->main->output.stream, "%s%s%s", global->main->context.set.title.before->string, alias_rule.string, global->main->context.set.title.after->string);
              fprintf(global->main->output.stream, "'.%c", f_string_eol_s[0]);

              controller_print_unlock_flush(global->main->output.stream, &global->thread->lock.print);
            }
          }

          if (!controller_thread_is_enabled(is_entry, global->thread)) break;

          // the rule is not yet loaded, ensure that it is loaded.
          if (status != F_true) {

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

            status_lock = controller_lock_write(is_entry, global->thread, &global->thread->lock.rule);

            if (!(status_lock == F_signal || F_status_is_error(status_lock))) {
              status = controller_rule_read(is_entry, alias_rule, *global, cache, &global->setting->rules.array[global->setting->rules.used]);
            }

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

            if (status_lock == F_signal || F_status_is_error(status_lock)) {
              controller_lock_error_critical_print(global->main->error, F_status_set_fine(status_lock), F_false, global->thread);

              break;
            }

            if (status == F_signal || !controller_thread_is_enabled(is_entry, global->thread)) {
              f_thread_unlock(&global->thread->lock.rule);

              break;
            }

            if (F_status_is_error(status)) {

              if (global->main->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&global->thread->lock.print);

                controller_entry_error_print_cache(is_entry, global->main->error, cache->action);

                controller_print_unlock_flush(global->main->output.stream, &global->thread->lock.print);
              }

              if (global->main->parameters[controller_parameter_simulate].result == f_console_result_none) {
                f_thread_unlock(&global->thread->lock.rule);

                break;
              }
            }
            else {
              ++global->setting->rules.used;
            }

            f_thread_unlock(&global->thread->lock.rule);
          }

          if (F_status_is_error_not(status)) {
            options_force = 0;
            options_process = 0;

            if (global->main->parameters[controller_parameter_simulate].result == f_console_result_found) {
              options_process |= controller_process_option_simulate;
            }

            if (entry_action->code & controller_entry_rule_code_require) {
              options_process |= controller_process_option_require;
            }

            if (entry_action->code & controller_entry_rule_code_wait) {
              options_process |= controller_process_option_wait;
            }

            if (global->main->parameters[controller_parameter_validate].result == f_console_result_found) {
              options_process |= controller_process_option_validate;
            }

            if (entry_action->code & controller_entry_rule_code_asynchronous) {
              if (global->main->parameters[controller_parameter_validate].result == f_console_result_none) {
                options_force |= controller_process_option_asynchronous;
              }

              options_process |= controller_process_option_asynchronous;
            }

            status = controller_rule_process_begin(options_force, alias_rule, controller_entry_action_type_to_rule_action_type(entry_action->type), options_process, is_entry ? controller_process_type_entry : controller_process_type_exit, stack, *global, *cache);

            if (F_status_set_fine(status) == F_memory_not || status == F_child || status == F_signal) {
              break;
            }

            if (F_status_is_error(status) && global->main->parameters[controller_parameter_simulate].result == f_console_result_none && (entry_action->code & controller_entry_rule_code_require)) {
              return F_status_set_error(F_require);
            }
          }
        }
        else if (entry_action->type == controller_entry_action_type_execute) {
          if (global->main->parameters[controller_parameter_simulate].result == f_console_result_found || global->main->error.verbosity == f_console_verbosity_verbose) {
            if (global->main->error.verbosity != f_console_verbosity_quiet) {
              f_thread_mutex_lock(&global->thread->lock.print);

              fprintf(global->main->output.stream, "%c", f_string_eol_s[0]);
              fprintf(global->main->output.stream, "%s is executing '", is_entry ? controller_string_entry_s : controller_string_exit_s);

              fprintf(global->main->output.stream, "%s", global->main->context.set.title.before->string);
              for (f_array_length_t k = 0; k < entry_action->parameters.used; ++k) {

                fprintf(global->main->output.stream, "%s%s%s", global->main->context.set.title.before->string, entry_action->parameters.array[k].string, global->main->context.set.title.after->string);

                if (k + 1 < entry_action->parameters.used) {
                  fprintf(global->main->output.stream, " ");
                }
              } // for
              fprintf(global->main->output.stream, "%s'.%c", global->main->context.set.title.after->string, f_string_eol_s[0]);

              controller_print_unlock_flush(global->main->output.stream, &global->thread->lock.print);
            }
          }

          if (global->main->parameters[controller_parameter_simulate].result == f_console_result_found) {
            return F_execute;
          }

          controller_thread_process_cancel(is_entry, is_entry ? controller_thread_cancel_execute : controller_thread_cancel_exit_execute, global, process);

          int result = 0;

          status = fll_execute_into(0, entry_action->parameters, fl_execute_parameter_option_path, &result);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_file_found_not) {
              if (global->main->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&global->thread->lock.print);

                fprintf(global->main->error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(global->main->error.to.stream, "%s%sExecution failed, unable to find program or script ", global->main->error.context.before->string, global->main->error.prefix ? global->main->error.prefix : f_string_empty_s);
                fprintf(global->main->error.to.stream, "%s%s%s%s", global->main->error.context.after->string, global->main->error.notable.before->string, entry_action->parameters.array[0].string, global->main->error.notable.after->string);
                fprintf(global->main->error.to.stream, "%s.%s%c", global->main->error.context.before->string, global->main->error.context.after->string, f_string_eol_s[0]);

                controller_entry_error_print_cache(is_entry, global->main->error, cache->action);

                controller_print_unlock_flush(global->main->error.to.stream, &global->thread->lock.print);
              }
            }
            else {
              controller_entry_error_print(is_entry, global->main->error, cache->action, F_status_set_fine(status), "fll_execute_into", F_true, global->thread);
            }

            return F_status_set_error(F_execute);
          }
          else if (result != 0) {
            if (global->main->error.verbosity != f_console_verbosity_quiet) {
              f_thread_mutex_lock(&global->thread->lock.print);

              fprintf(global->main->error.to.stream, "%c", f_string_eol_s[0]);
              fprintf(global->main->error.to.stream, "%s%sExecution failed with return value of ", global->main->error.context.before->string, global->main->error.prefix ? global->main->error.prefix : f_string_empty_s);
              fprintf(global->main->error.to.stream, "%s%s%d%s", global->main->error.context.after->string, global->main->error.notable.before->string, result, global->main->error.notable.after->string);
              fprintf(global->main->error.to.stream, "%s.%s%c", global->main->error.context.before->string, global->main->error.context.after->string, f_string_eol_s[0]);

              controller_entry_error_print_cache(is_entry, global->main->error, cache->action);

              controller_print_unlock_flush(global->main->error.to.stream, &global->thread->lock.print);
            }

            return F_status_set_error(F_execute);
          }

          return F_execute;
        }
        else if (entry_action->type == controller_entry_action_type_timeout) {

          if (global->main->parameters[controller_parameter_simulate].result == f_console_result_found || global->main->error.verbosity == f_console_verbosity_verbose) {
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

            if (global->main->error.verbosity != f_console_verbosity_quiet) {
              f_thread_mutex_lock(&global->thread->lock.print);

              fprintf(global->main->output.stream, "%c", f_string_eol_s[0]);
              fprintf(global->main->output.stream, "Processing %s item action '", is_entry ? controller_string_entry_s : controller_string_exit_s);
              fprintf(global->main->output.stream, "%s%s%s", global->main->context.set.title.before->string, controller_string_timeout_s, global->main->context.set.title.after->string);
              fprintf(global->main->output.stream, "' setting '");
              fprintf(global->main->output.stream, "%s%s%s", global->main->context.set.important.before->string, code, global->main->context.set.important.after->string);
              fprintf(global->main->output.stream, "' to '");
              fprintf(global->main->output.stream, "%s%llu%s", global->main->context.set.important.before->string, entry_action->number, global->main->context.set.important.after->string);
              fprintf(global->main->output.stream, "' MegaTime (milliseconds).%c", f_string_eol_s[0]);

              controller_print_unlock_flush(global->main->output.stream, &global->thread->lock.print);
            }
          }

          if (entry_action->code == controller_entry_timeout_code_kill) {
            global->setting->timeout_kill = entry_action->number;
          }
          else if (entry_action->code == controller_entry_timeout_code_start) {
            global->setting->timeout_start = entry_action->number;
          }
          else if (entry_action->code == controller_entry_timeout_code_stop) {
            global->setting->timeout_stop = entry_action->number;
          }
        }
        else if (entry_action->type == controller_entry_action_type_failsafe) {

          if (failsafe) {
            if (global->main->warning.verbosity == f_console_verbosity_debug) {
              f_thread_mutex_lock(&global->thread->lock.print);

              fprintf(global->main->warning.to.stream, "%c", f_string_eol_s[0]);
              fprintf(global->main->warning.to.stream, "%s%sFailsafe may not be specified when running in failsafe, ignoring.%s%c", global->main->warning.context.before->string, global->main->warning.prefix ? global->main->warning.prefix : f_string_empty_s, global->main->warning.context.after->string, f_string_eol_s[0]);

              controller_entry_error_print_cache(is_entry, global->main->warning, cache->action);

              controller_print_unlock_flush(global->main->warning.to.stream, &global->thread->lock.print);
            }
          }
          else {
            if (entry_action->number == 0 || entry_action->number >= entry->items.used) {

              // This should not happen if the pre-process is working as designed, but in case it doesn't, return a critical error to prevent infinite recursion and similar errors.
              if (global->main->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&global->thread->lock.print);

                fprintf(global->main->error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(global->main->error.to.stream, "%s%sInvalid %s item index ", global->main->error.context.before->string, global->main->error.prefix ? global->main->error.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s);
                fprintf(global->main->error.to.stream, "%s%s%llu%s", global->main->error.context.after->string, global->main->error.notable.before->string, entry_action->number, global->main->error.notable.after->string);
                fprintf(global->main->error.to.stream, "%s detected.%s%c", global->main->error.context.before->string, global->main->error.context.after->string, f_string_eol_s[0]);

                controller_entry_error_print_cache(is_entry, global->main->error, cache->action);

                controller_print_unlock_flush(global->main->error.to.stream, &global->thread->lock.print);
              }

              return F_status_is_error(F_critical);
            }
            else {
              global->setting->failsafe_enabled = F_true;
              global->setting->failsafe_item_id = entry_action->number;

              if (global->main->parameters[controller_parameter_simulate].result == f_console_result_found || global->main->error.verbosity == f_console_verbosity_verbose) {
                if (global->main->error.verbosity != f_console_verbosity_quiet) {
                  f_thread_mutex_lock(&global->thread->lock.print);

                  fprintf(global->main->output.stream, "%c", f_string_eol_s[0]);
                  fprintf(global->main->output.stream, "Processing %s item action '", is_entry ? controller_string_entry_s : controller_string_exit_s);
                  fprintf(global->main->output.stream, "%s%s%s", global->main->context.set.title.before->string, controller_string_failsafe_s, global->main->context.set.title.after->string);
                  fprintf(global->main->output.stream, "' setting value to '");
                  fprintf(global->main->output.stream, "%s%s%s", global->main->context.set.important.before->string, entry->items.array[global->setting->failsafe_item_id].name.string, global->main->context.set.important.after->string);
                  fprintf(global->main->output.stream, "'.%c", f_string_eol_s[0]);

                  controller_print_unlock_flush(global->main->output.stream, &global->thread->lock.print);
                }
              }
            }
          }
        }
      } // for

      if (status == F_child || status == F_signal) break;

      cache->action.line_action = 0;
      cache->action.name_action.used = 0;

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_require) {
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
        ++cache->ats.array[at_j];

        cache->action.line_item = entry->items.array[cache->ats.array[at_i]].line;
        cache->action.name_item.used = 0;

        status = controller_string_dynamic_append_terminated(entry->items.array[cache->ats.array[at_i]].name, &cache->action.name_item);

        if (F_status_is_error(status)) {
          controller_entry_error_print(is_entry, global->main->error, cache->action, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true, global->thread);

          break;
        }
      }
    } // while

    if (!controller_thread_is_enabled(is_entry, global->thread)) {
      return F_signal;
    }

    if (status == F_child) {
      return status;
    }

    if (F_status_is_error(status_lock)) {
      return status_lock;
    }

    // check to see if any required processes failed, but do not do this if already operating in failsafe.
    if (F_status_is_error_not(status) && !failsafe && global->main->parameters[controller_parameter_validate].result == f_console_result_none) {
      const f_status_t status_wait = controller_rule_wait_all(is_entry, *global, F_true, 0);

      if (status_wait == F_signal || F_status_is_error(status_wait)) {
        return status_wait;
      }

      if (F_status_set_fine(status_wait) == F_require) {
        return F_status_set_error(F_require);
      }
    }

    if ((global->main->parameters[controller_parameter_simulate].result == f_console_result_found && global->main->error.verbosity != f_console_verbosity_quiet) || global->main->error.verbosity == f_console_verbosity_verbose) {
      f_thread_mutex_lock(&global->thread->lock.print);

      fprintf(global->main->output.stream, "%c", f_string_eol_s[0]);
      fprintf(global->main->output.stream, "Done processing %s item '", is_entry ? controller_string_entry_s : controller_string_exit_s);
      fprintf(global->main->output.stream, "%s%s%s", global->main->context.set.title.before->string, controller_string_main_s, global->main->context.set.title.after->string);
      fprintf(global->main->output.stream, "'.%c", f_string_eol_s[0]);

      // failsafe should not print the extra newline because the failure exit from controller_main should handle this.
      if (!failsafe) {
        fprintf(global->main->output.stream, "%c", f_string_eol_s[0]);
      }

      controller_print_unlock_flush(global->main->output.stream, &global->thread->lock.print);
    }

    return status;
  }
#endif // _di_controller_process_entry_

#ifndef _di_controller_process_prepare_
  f_status_t controller_process_prepare(const bool is_normal, const uint8_t action, const f_string_static_t alias, const controller_global_t global, f_array_length_t *id) {

    f_status_t status = F_none;

    if (status == F_signal || F_status_is_error(status)) {
      controller_lock_error_critical_print(global.main->error, F_status_set_fine(status), F_true, global.thread);

      return status;
    }

    if (controller_find_process(action, alias, global.thread->processs, id) == F_false) {
      f_thread_unlock(&global.thread->lock.process);

      status = controller_lock_write(is_normal, global.thread, &global.thread->lock.process);

      if (status == F_signal || F_status_is_error(status)) {
        controller_lock_error_critical_print(global.main->error, F_status_set_fine(status), F_false, global.thread);

        const f_status_t status_lock = controller_lock_read(is_normal, global.thread, &global.thread->lock.process);

        if (status_lock == F_signal || F_status_is_error(status_lock)) {
          return F_status_set_error(F_lock);
        }

        return status;
      }

      status = controller_processs_increase(&global.thread->processs);

      if (F_status_is_error_not(status) && global.thread->processs.array[global.thread->processs.used]) {

        controller_process_t *process = global.thread->processs.array[global.thread->processs.used];

        status = controller_lock_write(is_normal, global.thread, &process->lock);

        if (status == F_signal || F_status_is_error(status)) {
          controller_lock_error_critical_print(global.main->error, F_status_set_fine(status), F_false, global.thread);

          f_thread_unlock(&global.thread->lock.process);

          const f_status_t status_lock = controller_lock_read(is_normal, global.thread, &global.thread->lock.process);

          if (status_lock == F_signal || F_status_is_error(status_lock)) {
            return F_status_set_error(F_lock);
          }

          return status;
        }

        process->action = action;
        process->rule.alias.used = 0;

        status = f_string_dynamic_append(alias, &process->rule.alias);

        if (F_status_is_error_not(status)) {
          status = f_string_dynamic_terminate_after(&process->rule.alias);

          if (F_status_is_error_not(status)) {
            process->id = global.thread->processs.used++;
            status = F_none;

            if (id) {
              *id = process->id;
            }
          }
        }

        f_thread_unlock(&process->lock);
      }

      f_thread_unlock(&global.thread->lock.process);

      const f_status_t status_lock = controller_lock_read(is_normal, global.thread, &global.thread->lock.process);

      if (status_lock == F_signal || F_status_is_error(status_lock)) {
        return F_status_set_error(F_lock);
      }
    }
    else {
      status = F_found;
    }

    return status;
  }
#endif // _di_controller_process_prepare_

#ifndef _di_controller_process_prepare_process_type_
  f_status_t controller_process_prepare_process_type(const uint8_t type, const uint8_t action, const f_string_static_t alias, const controller_global_t global, f_array_length_t *id) {

    return controller_process_prepare(type != controller_process_type_exit, action, alias, global, id);
  }
#endif // _di_controller_process_prepare_process_type_

#ifndef _di_controller_status_simplify_error_
  f_status_t controller_status_simplify_error(const f_status_t status) {

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

    if (status == F_valid_not) {
      return F_status_set_error(F_valid_not);
    }

    return F_status_set_error(F_failure);
  }
#endif // _di_controller_status_simplify_error_

#ifndef _di_controller_validate_define_name_
  f_status_t controller_validate_environment_name(const f_string_static_t name) {

    if (!name.used) return F_none;

    f_status_t status = F_none;

    if (name.string[0] != '_') {
      status = f_utf_is_alpha(name.string, name.used);

      if (F_status_is_error(status)) return status;
      if (status == F_false) return F_false;
    }

    for (f_array_length_t i = macro_f_utf_byte_width(name.string[0]); i < name.used; i += macro_f_utf_byte_width(name.string[i])) {

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

    for (f_array_length_t i = 0; i < name.used; i += macro_f_utf_byte_width(name.string[i])) {

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
