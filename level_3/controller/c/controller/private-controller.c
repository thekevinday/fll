#include "controller.h"
#include "../common/private-common.h"
#include "private-controller.h"
#include "private-controller_print.h"
#include "../entry/private-entry_print.h"
#include "../lock/private-lock_print.h"
#include "../thread/private-thread_control.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_range_after_number_sign_
  f_string_range_t controller_range_after_number_sign(const f_string_static_t buffer, const f_string_range_t range) {

    f_string_range_t result = range;

    for (; result.start <= result.stop; ++result.start) {

      if (!buffer.string[result.start]) continue;

      if (buffer.string[result.start] == '-' || buffer.string[result.start] == '+') {
        ++result.start;
      }

      break;
    } // while

    return result;
  }
#endif // _di_controller_range_after_number_sign_

#ifndef _di_controller_string_dynamic_rip_nulless_terminated_
  f_status_t controller_dynamic_rip_nulless_terminated(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {

    f_status_t status = fl_string_dynamic_rip_nulless(source, range, destination);
    if (F_status_is_error(status)) return status;

    return f_string_dynamic_terminate_after(destination);
  }
#endif // _di_controller_string_dynamic_rip_nulless_terminated_

#ifndef _di_controller_string_dynamic_append_terminated_
  f_status_t controller_dynamic_append_terminated(const f_string_static_t source, f_string_dynamic_t *destination) {

    f_status_t status = f_string_dynamic_append_nulless(source, destination);
    if (F_status_is_error(status)) return status;

    return f_string_dynamic_terminate_after(destination);
  }
#endif // _di_controller_string_dynamic_append_terminated_

#ifndef _di_controller_string_dynamic_partial_append_terminated_
  f_status_t controller_dynamic_partial_append_terminated(const f_string_static_t source, const f_string_range_t range, f_string_dynamic_t *destination) {

    f_status_t status = f_string_dynamic_partial_append(source, range, destination);
    if (F_status_is_error(status)) return status;

    return f_string_dynamic_terminate_after(destination);
  }
#endif // _di_controller_string_dynamic_partial_append_terminated_

#ifndef _di_controller_file_load_
  f_status_t controller_file_load(const controller_global_t global, const bool required, const f_string_t path_prefix, const f_string_static_t path_name, const f_string_t path_suffix, const f_array_length_t path_prefix_length, const f_array_length_t path_suffix_length, controller_cache_t * const cache) {

    f_status_t status = F_none;
    f_file_t file = f_file_t_initialize;

    cache->action.name_file.used = 0;
    cache->buffer_file.used = 0;

    macro_f_time_spec_t_clear(cache->timestamp);

    status = f_string_append(path_prefix, path_prefix_length, &cache->action.name_file);

    if (F_status_is_error_not(status)) {
      status = f_string_append(f_path_separator_s, F_path_separator_s_length, &cache->action.name_file);
    }

    if (F_status_is_error_not(status)) {
      status = f_string_append(path_name.string, path_name.used, &cache->action.name_file);
    }

    if (F_status_is_error_not(status)) {
      status = f_string_append(F_path_extension_separator_s, F_path_extension_separator_s_length, &cache->action.name_file);
    }

    if (F_status_is_error_not(status)) {
      status = f_string_append(path_suffix, path_suffix_length, &cache->action.name_file);
    }

    if (F_status_is_error(status)) {
      if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
        controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_append", F_true);
      }

      return status;
    }

    status = f_string_dynamic_terminate_after(&cache->action.name_file);

    if (F_status_is_error(status)) {
      if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
        controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
      }

      return status;
    }

    const f_array_length_t path_length = global.setting->path_setting.used ? global.setting->path_setting.used + F_path_separator_s_length + cache->action.name_file.used : cache->action.name_file.used;
    char path[path_length + 1];

    if (global.setting->path_setting.used) {
      memcpy(path, global.setting->path_setting.string, global.setting->path_setting.used);
      memcpy(path + global.setting->path_setting.used + F_path_separator_s_length, cache->action.name_file.string, cache->action.name_file.used);

      path[global.setting->path_setting.used] = f_path_separator_s[0];
    }

    path[path_length] = 0;

    status = f_file_stream_open(path, 0, &file);

    if (F_status_is_error(status)) {
      if (!required && F_status_set_fine(status) == F_file_found_not) {
        f_file_stream_close(F_true, &file);

        return F_file_found_not;
      }

      if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
        controller_print_error_file(global.thread, global.main->error, F_status_set_fine(status), "f_file_stream_open", F_true, path, "open", fll_error_file_type_file_e);
      }
    }
    else {
      status = f_file_stream_read(file, &cache->buffer_file);

      if (F_status_is_error(status)) {
        if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
          controller_print_error_file(global.thread, global.main->error, F_status_set_fine(status), "f_file_stream_read", F_true, path, "read", fll_error_file_type_file_e);
        }
      }
    }

    f_file_stream_close(F_true, &file);

    if (F_status_is_error_not(status)) {
      struct stat stat_file;

      status = f_file_stat(path, F_true, &stat_file);

      if (F_status_is_error(status)) {
        if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
          controller_print_error_file(global.thread, global.main->error, F_status_set_fine(status), "f_file_stat", F_true, path, "stat", fll_error_file_type_file_e);
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

    file.flag = F_file_flag_write_only_d;

    status = f_file_stream_open(path.string, f_file_open_mode_truncate_s, &file);
    if (F_status_is_error(status)) return status;

    fll_print_format("%i%c", file.stream, pid, f_string_eol_s[0]);

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
  f_status_t controller_file_pid_read(const f_string_static_t path, pid_t * const pid) {

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

#ifndef _di_controller_get_id_user_
  f_status_t controller_get_id_user(const f_string_static_t buffer, const f_string_range_t range, controller_cache_t * const cache, uid_t * const id) {

    f_number_unsigned_t number = 0;

    f_status_t status = fl_conversion_string_to_number_unsigned(buffer.string, range, &number);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_number) {
        cache->action.generic.used = 0;

        status = controller_dynamic_rip_nulless_terminated(buffer, range, &cache->action.generic);
        if (F_status_is_error(status)) return status;

        status = f_account_id_by_name(cache->action.generic.string, id);
        if (F_status_is_error(status)) return status;

        if (status == F_exist_not) {
          return F_status_set_error(F_exist_not);
        }

        return F_none;
      }

      return status;
    }
    else if (number > F_type_size_32_unsigned_d) {
      return F_status_set_error(F_number_too_large);
    }

    return status;
  }
#endif // _di_controller_get_id_user_

#ifndef _di_controller_get_id_group_
  f_status_t controller_get_id_group(const f_string_static_t buffer, const f_string_range_t range, controller_cache_t * const cache, gid_t * const id) {

    f_number_unsigned_t number = 0;

    f_status_t status = fl_conversion_string_to_number_unsigned(buffer.string, range, &number);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_number) {
        cache->action.generic.used = 0;

        status = controller_dynamic_rip_nulless_terminated(buffer, range, &cache->action.generic);
        if (F_status_is_error(status)) return status;

        status = f_account_group_id_by_name(cache->action.generic.string, id);
        if (F_status_is_error(status)) return status;

        if (status == F_exist_not) {
          return F_status_set_error(F_exist_not);
        }

        return F_none;
      }

      return status;
    }
    else if (number > F_type_size_32_unsigned_d) {
      return F_status_set_error(F_number_too_large);
    }

    return status;
  }
#endif // _di_controller_get_id_group_

#ifndef _di_controller_perform_ready_
  f_status_t controller_perform_ready(const controller_global_t *global, controller_cache_t * const cache, const bool is_entry) {

    if (!is_entry) {
      return F_none;
    }

    f_status_t status = F_none;

    if (global->setting->entry.pid != controller_entry_pid_disable_e && !global->setting->path_pid.used) {
      if (global->main->parameters[controller_parameter_validate_e].result == f_console_result_additional_e) {
        status = controller_file_pid_create(global->main->pid, global->setting->path_pid);
      }

      // Report pid file error but because this could be an "init" program, consider the pid file as optional and continue on.
      if (F_status_is_error(status)) {

        // Always return immediately on memory errors.
        if (F_status_set_fine(status) == F_memory_not) {
          if (global->main->error.verbosity != f_console_verbosity_quiet_e) {
            controller_lock_print(global->main->error.to, global->thread);

            controller_print_error_file(0, global->main->error, F_status_set_fine(status), "controller_file_pid_create", F_true, global->setting->path_pid.string, "create", fll_error_file_type_file_e);

            flockfile(global->main->error.to.stream);

            controller_entry_print_error_cache(is_entry, global->main->error, cache->action);

            controller_unlock_print_flush(global->main->error.to, global->thread);
          }

          return status;
        }

        if (global->main->warning.verbosity == f_console_verbosity_debug_e) {
          controller_lock_print(global->main->warning.to, global->thread);

          if (F_status_set_fine(status) == F_read_only) {
            fl_print_format("%c%[%SThe pid file '%]", global->main->warning.to.stream, f_string_eol_s[0], global->main->warning.context, global->main->warning.prefix, global->main->warning.context);
            fl_print_format("%[%Q%]", global->main->warning.to.stream, global->main->warning.notable, global->setting->path_pid, global->main->warning.notable);
            fl_print_format("%[' could not be written because the destination is read only.%]%c", global->main->warning.to.stream, global->main->warning.context, global->main->warning.context, f_string_eol_s[0]);
          }
          else {
            controller_print_error_file(0, global->main->warning, F_status_set_fine(status), "controller_file_pid_create", F_true, global->setting->path_pid.string, "create", fll_error_file_type_file_e);
          }

          controller_entry_print_error_cache(is_entry, global->main->warning, cache->action);

          controller_unlock_print_flush(global->main->warning.to, global->thread);
        }

        status = F_none;
      }
      else {
        global->setting->pid_created = F_true;

        if (global->main->output.verbosity == f_console_verbosity_debug_e) {
          controller_lock_print(global->main->output.to, global->thread);

          fl_print_format("%cPID file '", global->main->output.to.stream, f_string_eol_s[0]);
          fl_print_format("%[%Q%]", global->main->output.to.stream, global->main->context.set.notable, global->setting->path_pid, global->main->context.set.notable);

          if (global->main->parameters[controller_parameter_validate_e].result == f_console_result_none_e) {
            fl_print_format("' created.%c", global->main->output.to.stream, f_string_eol_s[0]);
          }
          else {
            fl_print_format("'.%c", global->main->output.to.stream, f_string_eol_s[0]);
          }

          controller_unlock_print_flush(global->main->output.to, global->thread);
        }
      }
    }

    if (global->setting->path_control.used) {
      if (global->setting->control_readonly) {
        if (f_file_exists(global->setting->path_control.string) != F_true) {
          if (global->main->output.verbosity == f_console_verbosity_debug_e) {
            controller_lock_print(global->main->output.to, global->thread);

            fl_print_format("%c%[%SControl socket '%]", global->main->warning.to.stream, f_string_eol_s[0], global->main->warning.context, global->main->warning.prefix, global->main->warning.context);
            fl_print_format("%[%Q%]", global->main->output.to.stream, global->main->context.set.notable, global->setting->path_control, global->main->context.set.notable);
            fl_print_format("' .%c", global->main->output.to.stream, f_string_eol_s[0]);
            fl_print_format("%[' cannot be found while read only mode is enabled and so the Control socket is unavailable.%]%c", global->main->output.to.stream, global->main->warning.context, global->main->warning.context, f_string_eol_s[0]);

            controller_unlock_print_flush(global->main->output.to, global->thread);
          }

          return status;
        }
      }
      else {
        status = f_socket_create(&global->setting->control_socket);

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_memory_not) {
            controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_socket_create", F_true);

            return status;
          }

          if (global->main->output.verbosity == f_console_verbosity_debug_e) {
            controller_lock_print(global->main->output.to, global->thread);

            fl_print_format("%c%[%SControl socket '%]", global->main->warning.to.stream, f_string_eol_s[0], global->main->warning.context, global->main->warning.prefix, global->main->warning.context);
            fl_print_format("%[%Q%]", global->main->output.to.stream, global->main->context.set.notable, global->setting->path_control, global->main->context.set.notable);
            fl_print_format("%[' could not be created, code %]", global->main->output.to.stream, global->main->warning.context, global->main->warning.context);
            fl_print_format("%[%ui%]", global->main->output.to.stream, global->main->context.set.notable, F_status_set_fine(status), global->main->context.set.notable);
            fl_print_format("%[.%]%c", global->main->output.to.stream, global->main->warning.context, global->main->warning.context, f_string_eol_s[0]);

            controller_unlock_print_flush(global->main->output.to, global->thread);
          }
        }
        else {
          status = f_file_remove(global->setting->path_control.string);

          if (F_status_set_fine(status) == F_memory_not) {
            controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_file_remove", F_true);

            return status;
          }

          global->setting->control_socket.name = global->setting->path_control.string;

          status = f_socket_bind_file(global->setting->control_socket);

          if (F_status_is_error(status)) {
            f_socket_disconnect(&global->setting->control_socket, f_socket_close_fast_e);

            if (F_status_set_fine(status) == F_memory_not) {
              controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_socket_bind_file", F_true);

              return status;
            }

            if (global->main->output.verbosity == f_console_verbosity_debug_e) {
              controller_lock_print(global->main->output.to, global->thread);

              fl_print_format("%c%[%SControl socket '%]", global->main->warning.to.stream, f_string_eol_s[0], global->main->warning.context, global->main->warning.prefix, global->main->warning.context);
              fl_print_format("%[%Q%]", global->main->output.to.stream, global->main->context.set.notable, global->setting->path_control, global->main->context.set.notable);
              fl_print_format("%[' could not be bound, code %]", global->main->output.to.stream, global->main->warning.context, global->main->warning.context);
              fl_print_format("%[%ui%]", global->main->output.to.stream, global->main->context.set.notable, F_status_set_fine(status), global->main->context.set.notable);
              fl_print_format("%[.%]%c", global->main->output.to.stream, global->main->warning.context, global->main->warning.context, f_string_eol_s[0]);

              controller_unlock_print_flush(global->main->output.to, global->thread);
            }
          }
          else {
            status = f_file_role_change(global->setting->path_control.string, global->setting->control_user, global->setting->control_group, F_true);

            if (F_status_is_error(status)) {
              f_socket_disconnect(&global->setting->control_socket, f_socket_close_fast_e);

              if (F_status_set_fine(status) == F_memory_not) {
                controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_file_role_change", F_true);

                return status;
              }

              if (global->main->output.verbosity == f_console_verbosity_debug_e) {
                controller_lock_print(global->main->output.to, global->thread);

                fl_print_format("%c%[%SControl socket '%]", global->main->warning.to.stream, f_string_eol_s[0], global->main->warning.context, global->main->warning.prefix, global->main->warning.context);
                fl_print_format("%[%Q%]", global->main->output.to.stream, global->main->context.set.notable, global->setting->path_control, global->main->context.set.notable);
                fl_print_format("%[' failed to set file roles, code %]", global->main->output.to.stream, global->main->warning.context, global->main->warning.context);
                fl_print_format("%[%ui%]", global->main->output.to.stream, global->main->context.set.notable, F_status_set_fine(status), global->main->context.set.notable);
                fl_print_format("%[.%]%c", global->main->output.to.stream, global->main->warning.context, global->main->warning.context, f_string_eol_s[0]);

                controller_unlock_print_flush(global->main->output.to, global->thread);
              }
            }
            else {
              status = f_file_mode_set(global->setting->path_control.string, global->setting->control_mode);

              if (F_status_is_error(status)) {
                f_socket_disconnect(&global->setting->control_socket, f_socket_close_fast_e);

                if (F_status_set_fine(status) == F_memory_not) {
                  controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_file_role_change", F_true);

                  return status;
                }

                if (global->main->output.verbosity == f_console_verbosity_debug_e) {
                  controller_lock_print(global->main->output.to, global->thread);

                  fl_print_format("%c%[%SControl socket '%]", global->main->warning.to.stream, f_string_eol_s[0], global->main->warning.context, global->main->warning.prefix, global->main->warning.context);
                  fl_print_format("%[%Q%]", global->main->output.to.stream, global->main->context.set.notable, global->setting->path_control, global->main->context.set.notable);
                  fl_print_format("%[' failed to set file mode, code %]", global->main->output.to.stream, global->main->warning.context, global->main->warning.context);
                  fl_print_format("%[%ui%]", global->main->output.to.stream, global->main->context.set.notable, F_status_set_fine(status), global->main->context.set.notable);
                  fl_print_format("%[.%]%c", global->main->output.to.stream, global->main->warning.context, global->main->warning.context, f_string_eol_s[0]);

                  controller_unlock_print_flush(global->main->output.to, global->thread);
                }
              }
              else {
                if (global->main->output.verbosity == f_console_verbosity_debug_e) {
                  controller_lock_print(global->main->output.to, global->thread);

                  fl_print_format("%cControl socket '", global->main->output.to.stream, f_string_eol_s[0]);
                  fl_print_format("%[%Q%]", global->main->output.to.stream, global->main->context.set.notable, global->setting->path_control, global->main->context.set.notable);

                  if (global->main->parameters[controller_parameter_validate_e].result == f_console_result_none_e) {
                    fl_print_format("' created.%c", global->main->output.to.stream, f_string_eol_s[0]);
                  }
                  else {
                    fl_print_format("'.%c", global->main->output.to.stream, f_string_eol_s[0]);
                  }

                  controller_unlock_print_flush(global->main->output.to, global->thread);
                }

                status = f_thread_create(0, &global->thread->id_listen, &controller_thread_control_listen, (void *) global);

                if (status == F_child) {
                  return status;
                }

                if (F_status_is_error_not(status)) {
                  status = f_thread_create(0, &global->thread->id_control, &controller_thread_control, (void *) global);

                  if (status == F_child) {
                    return status;
                  }
                }

                if (F_status_is_error(status)) {
                  if (global->thread->id_listen) {
                    f_thread_cancel(global->thread->id_listen);
                    f_thread_join(global->thread->id_listen, 0);

                    global->thread->id_listen = 0;
                  }

                  global->thread->id_control = 0;

                  if (global->main->error.verbosity != f_console_verbosity_quiet_e) {
                    controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_thread_create", F_true);
                  }
                }
              }
            }
          }
        }

        // Don't fail if unable to create socket file.
        status = F_none;
      }
    }

    return status;
  }
#endif // _di_controller_perform_ready_

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

#ifndef _di_controller_time_
  void controller_time(const time_t seconds, const long nanoseconds, struct timespec *time) {

    struct timeval now;

    gettimeofday(&now, 0);

    time->tv_sec = now.tv_sec + seconds;
    time->tv_nsec = (now.tv_usec * 1000) + nanoseconds;

    // If tv_nsec is 1 second or greater, then increment seconds.
    if (time->tv_nsec >= 1000000000) {
      ++(time->tv_sec);

      time->tv_nsec -= 1000000000;
    }
  }
#endif // _di_controller_time_

#ifndef _di_controller_time_milliseconds_
  struct timespec controller_time_milliseconds(const f_number_unsigned_t milliseconds) {

    struct timespec time;
    time.tv_sec = milliseconds > 1000 ? milliseconds / 1000 : 0;
    time.tv_nsec = (time.tv_sec ? milliseconds - time.tv_sec : milliseconds) * 1000;

    return time;
  }
#endif // _di_controller_time_milliseconds_

#ifndef _di_controller_time_seconds_
  struct timespec controller_time_seconds(const f_number_unsigned_t seconds) {

    struct timespec time;
    time.tv_sec = seconds;
    time.tv_nsec = 0;

    return time;
  }
#endif // _di_controller_time_seconds_

#ifndef _di_controller_time_sleep_nanoseconds_
  int controller_time_sleep_nanoseconds(controller_main_t * const main, controller_setting_t * const setting, struct timespec time) {

    // When sleep is a second or more, instead wait for terminating signals if interruptible.
    if (setting->interruptible && time.tv_sec) {
      siginfo_t information;
      f_signal_t signal = f_signal_t_initialize;

      memset(&information, 0, sizeof(siginfo_t));

      f_signal_set_empty(&signal.set);
      f_signal_set_add(F_signal_abort, &signal.set);
      f_signal_set_add(F_signal_interrupt, &signal.set);
      f_signal_set_add(F_signal_quit, &signal.set);
      f_signal_set_add(F_signal_termination, &signal.set);

      if (F_status_is_error(f_signal_wait_until(&signal.set, &time, &information))) {
        return -1;
      }

      return 0;
    }

    return nanosleep(&time, 0);
  }
#endif // _di_controller_time_sleep_nanoseconds_

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
