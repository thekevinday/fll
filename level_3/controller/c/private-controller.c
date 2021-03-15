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
  f_status_t controller_file_load(const f_string_t path_prefix, const f_string_static_t path_name, const f_string_t path_suffix, const f_array_length_t path_prefix_length, const f_array_length_t path_suffix_length, controller_thread_data_t thread_data, controller_cache_t *cache) {
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
      if (thread_data.data->error.verbosity != f_console_verbosity_quiet) {
        f_thread_mutex_lock(&thread_data.thread->lock.print);

        fll_error_print(thread_data.data->error, F_status_set_fine(status), "f_string_append", F_true);

        f_thread_mutex_unlock(&thread_data.thread->lock.print);
      }

      return status;
    }

    status = f_string_dynamic_terminate_after(&cache->action.name_file);

    if (F_status_is_error(status)) {
      if (thread_data.data->error.verbosity != f_console_verbosity_quiet) {
        f_thread_mutex_lock(&thread_data.thread->lock.print);

        fll_error_print(thread_data.data->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);

        f_thread_mutex_unlock(&thread_data.thread->lock.print);
      }

      return status;
    }

    const f_array_length_t path_length = thread_data.setting->path_setting.used ? thread_data.setting->path_setting.used + f_path_separator_length + cache->action.name_file.used : cache->action.name_file.used;
    char path[path_length + 1];

    if (thread_data.setting->path_setting.used) {
      memcpy(path, thread_data.setting->path_setting.string, thread_data.setting->path_setting.used);
      memcpy(path + thread_data.setting->path_setting.used + f_path_separator_length, cache->action.name_file.string, cache->action.name_file.used);

      path[thread_data.setting->path_setting.used] = f_path_separator_s[0];
    }

    path[path_length] = 0;

    status = f_file_stream_open(path, 0, &file);

    if (F_status_is_error(status)) {
      if (thread_data.data->error.verbosity != f_console_verbosity_quiet) {
        f_thread_mutex_lock(&thread_data.thread->lock.print);

        fll_error_file_print(thread_data.data->error, F_status_set_fine(status), "f_file_stream_open", F_true, path, "open", fll_error_file_type_file);

        f_thread_mutex_unlock(&thread_data.thread->lock.print);
      }
    }
    else {
      status = f_file_stream_read(file, 1, &cache->buffer_file);

      if (F_status_is_error(status)) {
        if (thread_data.data->error.verbosity != f_console_verbosity_quiet) {
          f_thread_mutex_lock(&thread_data.thread->lock.print);

          fll_error_file_print(thread_data.data->error, F_status_set_fine(status), "f_file_stream_read", F_true, path, "read", fll_error_file_type_file);

          f_thread_mutex_unlock(&thread_data.thread->lock.print);
        }
      }
    }

    f_file_stream_close(F_true, &file);

    if (F_status_is_error_not(status)) {
      struct stat stat_file;

      status = f_file_stat(path, F_true, &stat_file);

      if (F_status_is_error(status)) {
        if (thread_data.data->error.verbosity != f_console_verbosity_quiet) {
          f_thread_mutex_lock(&thread_data.thread->lock.print);

          fll_error_file_print(thread_data.data->error, F_status_set_fine(status), "f_file_stat", F_true, path, "stat", fll_error_file_type_file);

          f_thread_mutex_unlock(&thread_data.thread->lock.print);
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
  f_status_t controller_find_process(const f_string_static_t id, const controller_processs_t processs, f_array_length_t *at) {

    if (!id.used) return F_none;
    if (!processs.used) return F_false;

    for (f_array_length_t i = 0; i < processs.used; ++i) {

      if (fl_string_dynamic_compare(id, processs.array[i].id) == F_equal_to) {
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
  f_status_t controller_perform_ready(controller_thread_data_t thread_data, controller_cache_t *cache) {
    f_status_t status = F_none;

    // only create pid file when not in validate mode.
    if (thread_data.data->parameters[controller_parameter_validate].result == f_console_result_none) {

      status = controller_file_pid_create(*thread_data.data, thread_data.setting->path_pid);

      // report pid file error but because this could be an "init" program, consider the pid file as optional and continue on.
      if (F_status_is_error(status)) {

        // always return immediately on memory errors.
        if (F_status_set_fine(status) == F_memory_not) {
          if (thread_data.data->error.verbosity != f_console_verbosity_quiet) {
            f_thread_mutex_lock(&thread_data.thread->lock.print);

            fll_error_file_print(thread_data.data->error, F_status_set_fine(status), "controller_file_pid_create", F_true, thread_data.setting->path_pid.string, "create", fll_error_file_type_file);

            controller_entry_error_print_cache(thread_data.data->error, cache->action);

            f_thread_mutex_unlock(&thread_data.thread->lock.print);
          }

          return status;
        }

        if (thread_data.data->warning.verbosity == f_console_verbosity_debug) {
          f_thread_mutex_lock(&thread_data.thread->lock.print);

          fll_error_file_print(thread_data.data->warning, F_status_set_fine(status), "controller_file_pid_create", F_true, thread_data.setting->path_pid.string, "create", fll_error_file_type_file);

          controller_entry_error_print_cache(thread_data.data->warning, cache->action);

          f_thread_mutex_unlock(&thread_data.thread->lock.print);
        }

        status = F_none;
      }
    }

    return status;
  }
#endif // _di_controller_perform_ready_

#ifndef _di_controller_preprocess_entry_
  f_status_t controller_preprocess_entry(controller_thread_data_t thread_data, controller_cache_t *cache) {
    f_status_t status = F_none;
    f_status_t status2 = F_none;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_array_length_t at_i = 0;
    f_array_length_t at_j = 1;

    controller_entry_actions_t *actions = 0;

    uint8_t error_has = F_false;

    thread_data.setting->ready = controller_setting_ready_no;

    cache->ats.used = 0;

    cache->action.line_action = 0;
    cache->action.line_item = 0;
    cache->action.name_action.used = 0;
    cache->action.name_item.used = 0;

    f_macro_array_lengths_t_increase_by(status, cache->ats, controller_default_allocation_step)

    if (F_status_is_error(status)) {
      controller_entry_error_print(thread_data.data->error, cache->action, F_status_set_fine(status), "f_macro_array_lengths_t_increase_by", F_true, thread_data.thread);
      return status;
    }

    // utilize the ats cache as an item execution stack (at_i is for item index, and at_j (at_i + 1) is for action index).
    cache->ats.array[0] = 0;
    cache->ats.array[1] = 0;
    cache->ats.used = 2;

    cache->action.line_item = thread_data.setting->entry.items.array[0].line;
    cache->action.name_item.used = 0;

    status = controller_string_dynamic_append_terminated(thread_data.setting->entry.items.array[0].name, &cache->action.name_item);

    if (F_status_is_error(status)) {
      controller_entry_error_print(thread_data.data->error, cache->action, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true, thread_data.thread);

      return status;
    }

    for (;;) {

      actions = &thread_data.setting->entry.items.array[cache->ats.array[at_i]].actions;

      for (; cache->ats.array[at_j] < actions->used; ++cache->ats.array[at_j]) {

        if (thread_data.setting->signal) {
          return F_signal;
        }

        cache->action.line_action = actions->array[cache->ats.array[at_j]].line;
        cache->action.name_action.used = 0;

        status2 = controller_string_dynamic_append_terminated(controller_entry_action_type_name(actions->array[cache->ats.array[at_j]].type), &cache->action.name_action);

        if (F_status_is_error(status2)) {
          controller_entry_error_print(thread_data.data->error, cache->action, F_status_set_fine(status2), "controller_string_dynamic_append_terminated", F_true, thread_data.thread);

          return status2;
        }

        if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_ready) {

          if (thread_data.setting->ready == controller_setting_ready_wait) {
            if (thread_data.data->warning.verbosity == f_console_verbosity_debug) {
              f_thread_mutex_lock(&thread_data.thread->lock.print);

              fprintf(thread_data.data->warning.to.stream, "%c", f_string_eol_s[0]);
              fprintf(thread_data.data->warning.to.stream, "%s%sMultiple '", thread_data.data->warning.context.before->string, thread_data.data->warning.prefix ? thread_data.data->warning.prefix : f_string_empty_s);
              fprintf(thread_data.data->warning.to.stream, "%s%s%s%s", thread_data.data->warning.context.after->string, thread_data.data->warning.notable.before->string, controller_string_ready_s, thread_data.data->warning.notable.after->string);
              fprintf(thread_data.data->warning.to.stream, "%s' entry item actions detected; only the first will be used.%s%c", thread_data.data->warning.context.before->string, thread_data.data->warning.context.after->string, f_string_eol_s[0]);

              controller_entry_error_print_cache(thread_data.data->warning, cache->action);

              f_thread_mutex_unlock(&thread_data.thread->lock.print);
            }
          }

          // the pre-process currently only looks for "ready", so once found, pre-process is complete.
          thread_data.setting->ready = controller_setting_ready_wait;
        }
        else if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_item) {
          error_has = F_false;

          if (fl_string_dynamic_compare_string(controller_string_main_s, actions->array[cache->ats.array[at_j]].parameters.array[0], controller_string_main_length) == F_equal_to) {
            continue;
          }

          // walk though each items and check to see if the item actually exists (skipping main).
          for (i = 1; i < thread_data.setting->entry.items.used; ++i) {

            if (fl_string_dynamic_compare(thread_data.setting->entry.items.array[i].name, actions->array[cache->ats.array[at_j]].parameters.array[0]) == F_equal_to) {

              // check to see if "i" is already in the stack (to prevent recursion) (skipping main).
              for (j = 2; j < cache->ats.used; j += 2) {

                if (cache->ats.array[j] == i) {
                  if (thread_data.data->error.verbosity != f_console_verbosity_quiet) {
                    f_thread_mutex_lock(&thread_data.thread->lock.print);

                    fprintf(thread_data.data->error.to.stream, "%c", f_string_eol_s[0]);
                    fprintf(thread_data.data->error.to.stream, "%s%sThe entry item named '", thread_data.data->error.context.before->string, thread_data.data->error.prefix ? thread_data.data->error.prefix : f_string_empty_s);
                    fprintf(thread_data.data->error.to.stream, "%s%s%s%s", thread_data.data->error.context.after->string, thread_data.data->error.notable.before->string, thread_data.setting->entry.items.array[i].name.string, thread_data.data->error.notable.after->string);
                    fprintf(thread_data.data->error.to.stream, "%s' cannot be executed because recursion is not allowed.%s%c", thread_data.data->error.context.before->string, thread_data.data->error.context.after->string, f_string_eol_s[0]);

                    controller_entry_error_print_cache(thread_data.data->error, cache->action);

                    f_thread_mutex_unlock(&thread_data.thread->lock.print);
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
                controller_entry_error_print(thread_data.data->error, cache->action, F_status_set_fine(status2), "f_macro_array_lengths_t_increase_by", F_true, thread_data.thread);

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
              cache->action.line_item = thread_data.setting->entry.items.array[i].line;

              status2 = controller_string_dynamic_append_terminated(thread_data.setting->entry.items.array[i].name, &cache->action.name_item);

              if (F_status_is_error(status2)) {
                controller_entry_error_print(thread_data.data->error, cache->action, F_status_set_fine(status2), "controller_string_dynamic_append_terminated", F_true, thread_data.thread);

                return status2;
              }

              break;
            }
          } // for

          if (error_has || i >= thread_data.setting->entry.items.used) {
            if (i >= thread_data.setting->entry.items.used) {
              if (thread_data.data->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&thread_data.thread->lock.print);

                fprintf(thread_data.data->error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(thread_data.data->error.to.stream, "%s%sThe entry item named '", thread_data.data->error.context.before->string, thread_data.data->error.prefix ? thread_data.data->error.prefix : f_string_empty_s);
                fprintf(thread_data.data->error.to.stream, "%s%s%s%s", thread_data.data->error.context.after->string, thread_data.data->error.notable.before->string, actions->array[cache->ats.array[at_j]].parameters.array[0].string, thread_data.data->error.notable.after->string);
                fprintf(thread_data.data->error.to.stream, "%s' does not exist.%s%c", thread_data.data->error.context.before->string, thread_data.data->error.context.after->string, f_string_eol_s[0]);

                controller_entry_error_print_cache(thread_data.data->error, cache->action);

                f_thread_mutex_unlock(&thread_data.thread->lock.print);
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

        cache->action.line_item = thread_data.setting->entry.items.array[cache->ats.array[at_i]].line;
        cache->action.name_item.used = 0;

        status2 = controller_string_dynamic_append_terminated(thread_data.setting->entry.items.array[cache->ats.array[at_i]].name, &cache->action.name_item);

        if (F_status_is_error(status2)) {
          controller_entry_error_print(thread_data.data->error, cache->action, F_status_set_fine(status2), "controller_string_dynamic_append_terminated", F_true, thread_data.thread);

          return status2;
        }
      }
    } // for

    // if ready was never found in the entry, then default to always ready.
    if (thread_data.setting->ready == controller_setting_ready_no) {
      thread_data.setting->ready = controller_setting_ready_yes;
    }

    return status;
  }
#endif // _di_controller_preprocess_entry_

#ifndef _di_controller_process_entry_
  f_status_t controller_process_entry(controller_thread_data_t thread_data, controller_cache_t *cache) {
    f_status_t status = F_none;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_array_length_t at = 0;
    f_array_length_t at_i = 0;
    f_array_length_t at_j = 1;

    uint8_t rule_options = 0;

    controller_entry_actions_t *actions = 0;

    controller_process_t *process = 0;

    const bool simulate = thread_data.data->parameters[controller_parameter_test].result == f_console_result_found;

    cache->ats.used = 0;
    cache->stack.used = 0;

    cache->action.line_action = 0;
    cache->action.line_item = 0;
    cache->action.name_action.used = 0;
    cache->action.name_item.used = 0;

    if (thread_data.setting->ready == controller_setting_ready_yes) {
      status = controller_perform_ready(thread_data, cache);
      if (F_status_is_error(status)) return status;
    }

    f_macro_array_lengths_t_increase_by(status, cache->ats, controller_default_allocation_step)

    if (F_status_is_error(status)) {
      controller_entry_error_print(thread_data.data->error, cache->action, F_status_set_fine(status), "f_macro_array_lengths_t_increase_by", F_true, thread_data.thread);

      return status;
    }

    // utilize the ats cache as an item execution stack (at_i is for item index, and at_j (at_i + 1) is for action index).
    cache->ats.array[0] = 0;
    cache->ats.array[1] = 0;
    cache->ats.used = 2;

    cache->action.line_item = thread_data.setting->entry.items.array[0].line;
    cache->action.name_item.used = 0;

    status = controller_string_dynamic_append_terminated(thread_data.setting->entry.items.array[0].name, &cache->action.name_item);

    if (F_status_is_error(status)) {
      controller_entry_error_print(thread_data.data->error, cache->action, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true, thread_data.thread);

      return status;
    }

    if (simulate) {
      f_thread_mutex_lock(&thread_data.thread->lock.print);

      fprintf(thread_data.data->output.stream, "%c", f_string_eol_s[0]);
      fprintf(thread_data.data->output.stream, "Processing entry item rule '");
      fprintf(thread_data.data->output.stream, "%s%s%s", thread_data.data->context.set.title.before->string, controller_string_main_s, thread_data.data->context.set.title.after->string);
      fprintf(thread_data.data->output.stream, "'.%c", f_string_eol_s[0]);

      f_thread_mutex_unlock(&thread_data.thread->lock.print);
    }

    // @todo this function should maintain a read lock on "thread_data.thread->lock.rule", but it must immediately release the read lock before it can do a write lock (which is unfortunate).
    //       I would much rather gain the write lock and then release the read lock, but that is likely not possible.
    for (;;) {

      actions = &thread_data.setting->entry.items.array[cache->ats.array[at_i]].actions;

      for (; cache->ats.array[at_j] < actions->used; ++cache->ats.array[at_j]) {

        if (thread_data.setting->signal) {
          status = F_signal;
          break;
        }

        cache->action.line_action = actions->array[cache->ats.array[at_j]].line;
        cache->action.name_action.used = 0;

        status = controller_string_dynamic_append_terminated(controller_entry_action_type_name(actions->array[cache->ats.array[at_j]].type), &cache->action.name_action);

        if (F_status_is_error(status)) {
          controller_entry_error_print(thread_data.data->error, cache->action, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true, thread_data.thread);

          return status;
        }

        if (F_status_is_error(actions->array[cache->ats.array[at_j]].status)) {

          if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_rule) {

            if (simulate) {
              f_thread_mutex_lock(&thread_data.thread->lock.print);

              fprintf(thread_data.data->output.stream, "%c", f_string_eol_s[0]);
              fprintf(thread_data.data->output.stream, "The entry item action '");
              fprintf(thread_data.data->output.stream, "%s%s%s", thread_data.data->context.set.title.before->string, cache->action.name_action.string, thread_data.data->context.set.title.after->string);

              if (actions->array[cache->ats.array[at_j]].parameters.used) {
                fprintf(thread_data.data->output.stream, f_string_space_s);
                fprintf(thread_data.data->output.stream, "%s", thread_data.data->context.set.notable.before->string);
                controller_entry_action_parameters_print(thread_data.data->output.stream, actions->array[cache->ats.array[at_j]]);
                fprintf(thread_data.data->output.stream, "%s", thread_data.data->context.set.notable.after->string);
              }

              fprintf(thread_data.data->output.stream, "' is %s and is in a %sfailed%s state, skipping execution.%c", actions->array[cache->ats.array[at_j]].code & controller_entry_rule_code_require ? "required" : "optional", thread_data.data->error.context.before->string, thread_data.data->error.context.after->string, f_string_eol_s[0]);

              f_thread_mutex_unlock(&thread_data.thread->lock.print);
            }
            else if (actions->array[cache->ats.array[at_j]].code & controller_entry_rule_code_require) {

              if (thread_data.data->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&thread_data.thread->lock.print);

                fprintf(thread_data.data->error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(thread_data.data->error.to.stream, "%s%sThe entry item action '", thread_data.data->error.context.before->string, thread_data.data->error.prefix ? thread_data.data->error.prefix : f_string_empty_s);
                fprintf(thread_data.data->error.to.stream, "%s%s%s", thread_data.data->error.context.after->string, thread_data.data->error.notable.before->string, cache->action.name_action.string);

                if (actions->array[cache->ats.array[at_j]].parameters.used) {
                  fprintf(thread_data.data->error.to.stream, f_string_space_s);
                  controller_entry_action_parameters_print(thread_data.data->error.to.stream, actions->array[cache->ats.array[at_j]]);
                }

                fprintf(thread_data.data->error.to.stream, "%s%s' is ", thread_data.data->error.notable.after->string, thread_data.data->error.context.before->string);
                fprintf(thread_data.data->error.to.stream, "%s%srequired%s", thread_data.data->error.context.after->string, thread_data.data->error.notable.before->string, thread_data.data->error.notable.after->string);
                fprintf(thread_data.data->error.to.stream, "%s and is in a ", thread_data.data->error.context.before->string);
                fprintf(thread_data.data->error.to.stream, "%s%sfailed%s", thread_data.data->error.context.after->string, thread_data.data->error.notable.before->string, thread_data.data->error.notable.after->string);
                fprintf(thread_data.data->error.to.stream, "%s state, skipping execution.%s%c", thread_data.data->error.context.before->string, thread_data.data->error.context.after->string, f_string_eol_s[0]);

                controller_entry_error_print_cache(thread_data.data->error, cache->action);

                f_thread_mutex_unlock(&thread_data.thread->lock.print);
              }

              return F_status_is_error(F_require);
            }
            else if (thread_data.data->warning.verbosity == f_console_verbosity_debug) {
              f_thread_mutex_lock(&thread_data.thread->lock.print);

              fprintf(thread_data.data->warning.to.stream, "%c", f_string_eol_s[0]);
              fprintf(thread_data.data->warning.to.stream, "%s%sThe entry item action '", thread_data.data->warning.context.before->string, thread_data.data->warning.prefix ? thread_data.data->warning.prefix : f_string_empty_s);
              fprintf(thread_data.data->warning.to.stream, "%s%s%s", thread_data.data->warning.context.after->string, thread_data.data->warning.notable.before->string, cache->action.name_action.string);

              if (actions->array[cache->ats.array[at_j]].parameters.used) {
                fprintf(thread_data.data->warning.to.stream, f_string_space_s);
                controller_entry_action_parameters_print(thread_data.data->warning.to.stream, actions->array[cache->ats.array[at_j]]);
              }

              fprintf(thread_data.data->warning.to.stream, "%s%s' is ", thread_data.data->warning.notable.after->string, thread_data.data->warning.context.before->string);
              fprintf(thread_data.data->warning.to.stream, "%s%srequired%s", thread_data.data->warning.context.after->string, thread_data.data->warning.notable.before->string, thread_data.data->warning.notable.after->string);
              fprintf(thread_data.data->warning.to.stream, "%s and is in a ", thread_data.data->warning.context.before->string);
              fprintf(thread_data.data->warning.to.stream, "%s%sfailed%s", thread_data.data->warning.context.after->string, thread_data.data->warning.notable.before->string, thread_data.data->warning.notable.after->string);
              fprintf(thread_data.data->warning.to.stream, "%s state, skipping execution.%s%c", thread_data.data->warning.context.before->string, thread_data.data->warning.context.after->string, f_string_eol_s[0]);

              controller_entry_error_print_cache(thread_data.data->warning, cache->action);

              f_thread_mutex_unlock(&thread_data.thread->lock.print);
            }
          }
          else {
            if (simulate) {
              f_thread_mutex_lock(&thread_data.thread->lock.print);

              fprintf(thread_data.data->output.stream, "%c", f_string_eol_s[0]);
              fprintf(thread_data.data->output.stream, "The entry item action '");
              fprintf(thread_data.data->output.stream, "%s%s%s", thread_data.data->context.set.title.before->string, cache->action.name_action.string, thread_data.data->context.set.title.after->string);

              if (actions->array[cache->ats.array[at_j]].parameters.used) {
                fprintf(thread_data.data->output.stream, f_string_space_s);
                fprintf(thread_data.data->output.stream, "%s", thread_data.data->context.set.notable.before->string);
                controller_entry_action_parameters_print(thread_data.data->output.stream, actions->array[cache->ats.array[at_j]]);
                fprintf(thread_data.data->output.stream, "%s", thread_data.data->context.set.notable.after->string);
              }

              fprintf(thread_data.data->output.stream, "' is in a %sfailed%s state, skipping.%c", thread_data.data->error.context.before->string, thread_data.data->error.context.after->string, f_string_eol_s[0]);

              f_thread_mutex_unlock(&thread_data.thread->lock.print);
            }
            else if (thread_data.data->warning.verbosity == f_console_verbosity_debug) {
              f_thread_mutex_lock(&thread_data.thread->lock.print);

              fprintf(thread_data.data->warning.to.stream, "%c", f_string_eol_s[0]);
              fprintf(thread_data.data->warning.to.stream, "%s%sThe entry item action '", thread_data.data->warning.context.before->string, thread_data.data->warning.prefix ? thread_data.data->warning.prefix : f_string_empty_s);
              fprintf(thread_data.data->warning.to.stream, "%s%s", thread_data.data->warning.notable.before->string, cache->action.name_action.string);

              if (actions->array[cache->ats.array[at_j]].parameters.used) {
                fprintf(thread_data.data->warning.to.stream, f_string_space_s);
                controller_entry_action_parameters_print(thread_data.data->warning.to.stream, actions->array[cache->ats.array[at_j]]);
              }

              fprintf(thread_data.data->warning.to.stream, "%s' is in a ", thread_data.data->warning.notable.after->string);
              fprintf(thread_data.data->warning.to.stream, "%s%sfailed%s", thread_data.data->warning.context.after->string, thread_data.data->warning.notable.before->string, thread_data.data->warning.notable.after->string);
              fprintf(thread_data.data->warning.to.stream, "%s state, skipping.%s%c", thread_data.data->warning.context.before->string, thread_data.data->warning.context.after->string, f_string_eol_s[0]);

              controller_entry_error_print_cache(thread_data.data->warning, cache->action);

              f_thread_mutex_unlock(&thread_data.thread->lock.print);
            }
          }

          continue;
        }

        if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_ready) {

          if (thread_data.setting->ready == controller_setting_ready_wait) {

            if (simulate) {
              f_thread_mutex_lock(&thread_data.thread->lock.print);

              fprintf(thread_data.data->output.stream, "%c", f_string_eol_s[0]);
              fprintf(thread_data.data->output.stream, "Processing entry item action '");
              fprintf(thread_data.data->output.stream, "%s%s%s", thread_data.data->context.set.title.before->string, controller_string_ready_s, thread_data.data->context.set.title.after->string);
              fprintf(thread_data.data->output.stream, "'.%c", f_string_eol_s[0]);

              f_thread_mutex_unlock(&thread_data.thread->lock.print);
            }
            else {
              controller_perform_ready(thread_data, cache);
              if (F_status_is_error(status)) return status;
            }

            thread_data.setting->ready = controller_setting_ready_yes;
          }
          else if (simulate) {
            f_thread_mutex_lock(&thread_data.thread->lock.print);

            fprintf(thread_data.data->output.stream, "%c", f_string_eol_s[0]);
            fprintf(thread_data.data->output.stream, "Ignoring entry item action '");
            fprintf(thread_data.data->output.stream, "%s%s%s", thread_data.data->context.set.title.before->string, controller_string_ready_s, thread_data.data->context.set.title.after->string);
            fprintf(thread_data.data->output.stream, "', state already is ready.%c", f_string_eol_s[0]);

            f_thread_mutex_unlock(&thread_data.thread->lock.print);
          }
        }
        else if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_item) {

          if (actions->array[cache->ats.array[at_j]].number == 0 || actions->array[cache->ats.array[at_j]].number >= thread_data.setting->entry.items.used) {

            // This should not happen if the pre-process is working as designed, but in case it doesn't, return a critical error to prevent infinite recursion and similar errors.
            if (thread_data.data->error.verbosity != f_console_verbosity_quiet) {
              f_thread_mutex_lock(&thread_data.thread->lock.print);

              fprintf(thread_data.data->error.to.stream, "%c", f_string_eol_s[0]);
              fprintf(thread_data.data->error.to.stream, "%s%sInvalid entry item index ", thread_data.data->error.context.before->string, thread_data.data->error.prefix ? thread_data.data->error.prefix : f_string_empty_s);
              fprintf(thread_data.data->error.to.stream, "%s%s%llu%s", thread_data.data->error.context.after->string, thread_data.data->error.notable.before->string, actions->array[cache->ats.array[at_j]].number, thread_data.data->error.notable.after->string);
              fprintf(thread_data.data->error.to.stream, "%s detected.%s%c", thread_data.data->error.context.before->string, thread_data.data->error.context.after->string, f_string_eol_s[0]);

              controller_entry_error_print_cache(thread_data.data->error, cache->action);

              f_thread_mutex_unlock(&thread_data.thread->lock.print);
            }

            return F_status_is_error(F_critical);
          }

          f_macro_array_lengths_t_increase_by(status, cache->ats, controller_default_allocation_step)

          if (F_status_is_error(status)) {
            controller_entry_error_print(thread_data.data->error, cache->action, F_status_set_fine(status), "f_macro_array_lengths_t_increase_by", F_true, thread_data.thread);

            return status;
          }

          // continue into the requested item.
          cache->ats.array[cache->ats.used] = actions->array[cache->ats.array[at_j]].number;
          cache->ats.array[cache->ats.used + 1] = 0;

          at_i = cache->ats.used;
          at_j = cache->ats.used + 1;

          cache->ats.used += 2;

          cache->action.name_action.used = 0;
          cache->action.line_action = 0;

          cache->action.name_item.used = 0;
          cache->action.line_item = thread_data.setting->entry.items.array[cache->ats.array[at_i]].line;

          status = controller_string_dynamic_append_terminated(thread_data.setting->entry.items.array[cache->ats.array[at_i]].name, &cache->action.name_item);

          if (F_status_is_error(status)) {
            controller_entry_error_print(thread_data.data->error, cache->action, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true, thread_data.thread);

            return status;
          }

          if (simulate) {
            f_thread_mutex_lock(&thread_data.thread->lock.print);

            fprintf(thread_data.data->output.stream, "%c", f_string_eol_s[0]);
            fprintf(thread_data.data->output.stream, "Processing entry item '");
            fprintf(thread_data.data->output.stream, "%s%s%s", thread_data.data->context.set.title.before->string, cache->action.name_item.string, thread_data.data->context.set.title.after->string);
            fprintf(thread_data.data->output.stream, "'.%c", f_string_eol_s[0]);

            f_thread_mutex_unlock(&thread_data.thread->lock.print);
          }

          // exit inner loop to force restarting and start processing the requested item.
          break;
        }
        else if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_consider || actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_rule) {

          status = controller_rules_increase(&thread_data.setting->rules);

          if (F_status_is_error(status)) {
            controller_entry_error_print(thread_data.data->error, cache->action, F_status_set_fine(status), "controller_rules_increase", F_true, thread_data.thread);

            return status;
          }

          const f_array_length_t rule_id_length = actions->array[cache->ats.array[at_j]].parameters.array[0].used + actions->array[cache->ats.array[at_j]].parameters.array[1].used + 1;
          char rule_id_name[rule_id_length + 1];
          const f_string_static_t rule_id = f_macro_string_static_t_initialize(rule_id_name, rule_id_length);

          memcpy(rule_id_name, actions->array[cache->ats.array[at_j]].parameters.array[0].string, actions->array[cache->ats.array[at_j]].parameters.array[0].used);
          memcpy(rule_id_name + actions->array[cache->ats.array[at_j]].parameters.array[0].used + 1, actions->array[cache->ats.array[at_j]].parameters.array[1].string, actions->array[cache->ats.array[at_j]].parameters.array[1].used);

          rule_id_name[actions->array[cache->ats.array[at_j]].parameters.array[0].used] = f_path_separator_s[0];
          rule_id_name[rule_id_length] = 0;

          f_thread_lock_read(&thread_data.thread->lock.rule);

          at = controller_rule_find_loaded(rule_id, thread_data);

          const f_array_length_t used = thread_data.setting->rules.used;

          f_thread_unlock(&thread_data.thread->lock.rule);

          if (simulate) {
            f_thread_mutex_lock(&thread_data.thread->lock.print);

            fprintf(thread_data.data->output.stream, "%c", f_string_eol_s[0]);
            fprintf(thread_data.data->output.stream, "%s entry item rule '", actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_rule ? "Processing" : "Considering");
            fprintf(thread_data.data->output.stream, "%s%s%s", thread_data.data->context.set.title.before->string, rule_id.string, thread_data.data->context.set.title.after->string);
            fprintf(thread_data.data->output.stream, "'.%c", f_string_eol_s[0]);

            f_thread_mutex_unlock(&thread_data.thread->lock.print);
          }

          // the rule is not yet loaded, ensure that it is loaded.
          if (at == used) {

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

            f_thread_lock_write(&thread_data.thread->lock.rule);

            status = controller_rule_read(rule_id, thread_data, cache, &thread_data.setting->rules.array[thread_data.setting->rules.used]);

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

              if (thread_data.data->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&thread_data.thread->lock.print);

                controller_entry_error_print_cache(thread_data.data->error, cache->action);

                f_thread_mutex_unlock(&thread_data.thread->lock.print);
              }

              if (!simulate) {
                f_thread_unlock(&thread_data.thread->lock.rule);

                break;
              }
            }
            else {
              thread_data.setting->rules.used++;
            }

            f_thread_unlock(&thread_data.thread->lock.rule);
          }

          if (F_status_is_error_not(status) && actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_rule) {

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

            rule_options = 0;

            if (simulate) {
              rule_options |= controller_rule_option_simulate;
            }

            if (actions->array[cache->ats.array[at_j]].code & controller_entry_rule_code_require) {
              rule_options |= controller_rule_option_require;
            }

            if (actions->array[cache->ats.array[at_j]].code & controller_entry_rule_code_wait) {
              rule_options |= controller_rule_option_wait;
            }

            if (actions->array[cache->ats.array[at_j]].code & controller_entry_rule_code_asynchronous) {
              rule_options |= controller_rule_option_asynchronous;

              // @todo this function will need to do the same process prep work as is done right before controller_rule_process().
              status = controller_rule_process_asynchronous(at, controller_rule_action_type_start, rule_options, thread_data, cache);
            }
            else {

              f_array_length_t at_process = 0;

              f_thread_lock_read(&thread_data.thread->lock.process);

              if (controller_find_process(rule_id, *thread_data.processs, &at_process) == F_false) {
                f_thread_unlock(&thread_data.thread->lock.process);
                f_thread_lock_write(&thread_data.thread->lock.process);

                status = controller_processs_increase(thread_data.processs);

                if (F_status_is_error(status)) {
                  controller_entry_error_print(thread_data.data->error, cache->action, F_status_set_fine(status), "controller_processs_increase", F_true, thread_data.thread);
                }
                else {
                  at_process = thread_data.processs->used;
                }
              }

              f_thread_unlock(&thread_data.thread->lock.process);

              if (F_status_is_error_not(status)) {
                f_thread_lock_write(&thread_data.processs->array[at_process].lock);

                controller_rule_t rule = controller_rule_t_initialize;

                status = controller_rule_copy(thread_data.setting->rules.array[at], &rule);

                f_thread_condition_signal(&thread_data.processs->array[at_process].wait);
                f_thread_unlock(&thread_data.processs->array[at_process].lock);

                status = controller_rule_process(rule, at_process, controller_rule_action_type_start, rule_options, thread_data, cache);

                controller_rule_delete_simple(&rule);
              }
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

            if (status == F_child || status == F_signal) break;
          }

          // @todo this may need to be relocated (currently it may result in multiple error messages due to other messages being printed above.)
          if (F_status_is_error(status)) {
            f_thread_mutex_lock(&thread_data.thread->lock.print);

            controller_entry_error_print_cache(thread_data.data->error, cache->action);

            f_thread_mutex_unlock(&thread_data.thread->lock.print);

            if (!simulate || F_status_set_fine(status) == F_memory_not) {
              break;
            }
          }
        }
        else if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_timeout) {

          if (simulate) {
            f_string_t code = "";

            if (actions->array[cache->ats.array[at_j]].code == controller_entry_timeout_code_kill) {
              code = controller_string_kill_s;
            }
            else if (actions->array[cache->ats.array[at_j]].code == controller_entry_timeout_code_start) {
              code = controller_string_start_s;
            }
            else if (actions->array[cache->ats.array[at_j]].code == controller_entry_timeout_code_stop) {
              code = controller_string_stop_s;
            }

            f_thread_mutex_lock(&thread_data.thread->lock.print);

            fprintf(thread_data.data->output.stream, "%c", f_string_eol_s[0]);
            fprintf(thread_data.data->output.stream, "Processing entry item action '");
            fprintf(thread_data.data->output.stream, "%s%s%s", thread_data.data->context.set.title.before->string, controller_string_timeout_s, thread_data.data->context.set.title.after->string);
            fprintf(thread_data.data->output.stream, "' setting '");
            fprintf(thread_data.data->output.stream, "%s%s%s", thread_data.data->context.set.important.before->string, code, thread_data.data->context.set.important.after->string);
            fprintf(thread_data.data->output.stream, "' to '");
            fprintf(thread_data.data->output.stream, "%s%llu%s", thread_data.data->context.set.important.before->string, actions->array[cache->ats.array[at_j]].number, thread_data.data->context.set.important.after->string);
            fprintf(thread_data.data->output.stream, "' MegaTime (milliseconds).%c", f_string_eol_s[0]);

            f_thread_mutex_unlock(&thread_data.thread->lock.print);
          }

          if (actions->array[cache->ats.array[at_j]].code == controller_entry_timeout_code_kill) {
            thread_data.setting->timeout_kill = actions->array[cache->ats.array[at_j]].number;
          }
          else if (actions->array[cache->ats.array[at_j]].code == controller_entry_timeout_code_start) {
            thread_data.setting->timeout_start = actions->array[cache->ats.array[at_j]].number;
          }
          else if (actions->array[cache->ats.array[at_j]].code == controller_entry_timeout_code_stop) {
            thread_data.setting->timeout_stop = actions->array[cache->ats.array[at_j]].number;
          }
        }
        else if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_failsafe) {

          if (actions->array[cache->ats.array[at_j]].number == 0 || actions->array[cache->ats.array[at_j]].number >= thread_data.setting->entry.items.used) {

            // This should not happen if the pre-process is working as designed, but in case it doesn't, return a critical error to prevent infinite recursion and similar errors.
            if (thread_data.data->error.verbosity != f_console_verbosity_quiet) {
              f_thread_mutex_lock(&thread_data.thread->lock.print);

              fprintf(thread_data.data->error.to.stream, "%c", f_string_eol_s[0]);
              fprintf(thread_data.data->error.to.stream, "%s%sInvalid entry item index ", thread_data.data->error.context.before->string, thread_data.data->error.prefix ? thread_data.data->error.prefix : f_string_empty_s);
              fprintf(thread_data.data->error.to.stream, "%s%s%llu%s", thread_data.data->error.context.after->string, thread_data.data->error.notable.before->string, actions->array[cache->ats.array[at_j]].number, thread_data.data->error.notable.after->string);
              fprintf(thread_data.data->error.to.stream, "%s detected.%s%c", thread_data.data->error.context.before->string, thread_data.data->error.context.after->string, f_string_eol_s[0]);

              controller_entry_error_print_cache(thread_data.data->error, cache->action);

              f_thread_mutex_unlock(&thread_data.thread->lock.print);
            }

            return F_status_is_error(F_critical);
          }
          else {
            thread_data.setting->failsafe_enabled = F_true;
            thread_data.setting->failsafe_rule_id = actions->array[cache->ats.array[at_j]].number;

            if (simulate) {
              f_thread_mutex_lock(&thread_data.thread->lock.print);

              fprintf(thread_data.data->output.stream, "%c", f_string_eol_s[0]);
              fprintf(thread_data.data->output.stream, "Processing entry item action '");
              fprintf(thread_data.data->output.stream, "%s%s%s", thread_data.data->context.set.title.before->string, controller_string_failsafe_s, thread_data.data->context.set.title.after->string);
              fprintf(thread_data.data->output.stream, "' setting value to '");
              fprintf(thread_data.data->output.stream, "%s%s%s", thread_data.data->context.set.important.before->string, thread_data.setting->entry.items.array[thread_data.setting->failsafe_rule_id].name.string, thread_data.data->context.set.important.after->string);
              fprintf(thread_data.data->output.stream, "'.%c", f_string_eol_s[0]);

              f_thread_mutex_unlock(&thread_data.thread->lock.print);
            }
          }
        }
      } // for

      if (thread_data.setting->signal) {
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
      if (cache->ats.array[at_j] == actions->used) {

        // all actions for "main" are processed so there is nothing left to do.
        if (at_i == 0) break;

        at_i -= 2;
        at_j -= 2;

        cache->ats.used -= 2;
        cache->ats.array[at_j]++;

        cache->action.line_item = thread_data.setting->entry.items.array[cache->ats.array[at_i]].line;
        cache->action.name_item.used = 0;

        status = controller_string_dynamic_append_terminated(thread_data.setting->entry.items.array[cache->ats.array[at_i]].name, &cache->action.name_item);

        if (F_status_is_error(status)) {
          controller_entry_error_print(thread_data.data->error, cache->action, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true, thread_data.thread);

          break;
        }
      }
    } // for

    if (status == F_child || status == F_signal) {
      return status;
    }

    if (F_status_is_error_not(status) && simulate) {
      f_thread_mutex_lock(&thread_data.thread->lock.print);

      fprintf(thread_data.data->output.stream, "%c", f_string_eol_s[0]);

      f_thread_mutex_unlock(&thread_data.thread->lock.print);
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

controller_processs_t

#ifdef __cplusplus
} // extern "C"
#endif
