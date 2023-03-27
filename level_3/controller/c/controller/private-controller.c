#include "../controller.h"
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

      if (buffer.string[result.start] == f_string_ascii_minus_s.string[0] || buffer.string[result.start] == f_string_ascii_plus_s.string[0]) {
        ++result.start;
      }

      break;
    } // for

    return result;
  }
#endif // _di_controller_range_after_number_sign_

#ifndef _di_controller_file_load_
  f_status_t controller_file_load(const controller_global_t global, const bool required, const f_string_static_t path_prefix, const f_string_static_t path_name, const f_string_static_t path_suffix, controller_cache_t * const cache) {

    f_status_t status = F_none;
    f_file_t file = f_file_t_initialize;

    cache->action.name_file.used = 0;
    cache->buffer_file.used = 0;

    macro_f_time_spec_t_clear(cache->timestamp);

    status = f_string_dynamic_append(path_prefix, &cache->action.name_file);

    if (F_status_is_error_not(status)) {
      status = f_string_dynamic_append(f_path_separator_s, &cache->action.name_file);
    }

    if (F_status_is_error_not(status)) {
      status = f_string_dynamic_append(path_name, &cache->action.name_file);
    }

    if (F_status_is_error_not(status)) {
      status = f_string_dynamic_append(f_path_extension_separator_s, &cache->action.name_file);
    }

    if (F_status_is_error_not(status)) {
      status = f_string_dynamic_append(path_suffix, &cache->action.name_file);
    }

    if (F_status_is_error(status)) {
      controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);

      return status;
    }

    f_string_static_t path = f_string_static_t_initialize;

    if (global.setting->path_setting.used) {
      path.used = global.setting->path_setting.used + F_path_separator_s_length + cache->action.name_file.used;
    }
    else {
      path.used = cache->action.name_file.used;
    }

    f_char_t path_string[path.used + 1];
    path.string = path_string;

    if (global.setting->path_setting.used) {
      memcpy(path_string, global.setting->path_setting.string, sizeof(f_char_t) * global.setting->path_setting.used);
      memcpy(path_string + global.setting->path_setting.used + F_path_separator_s_length, cache->action.name_file.string, sizeof(f_char_t) * cache->action.name_file.used);

      path_string[global.setting->path_setting.used] = f_path_separator_s.string[0];
    }
    else {
      memcpy(path_string, cache->action.name_file.string, sizeof(f_char_t) * cache->action.name_file.used);
    }

    path_string[path.used] = 0;


    status = f_file_stream_open(path, f_string_empty_s, &file);

    if (F_status_is_error(status)) {
      if (!required && F_status_set_fine(status) == F_file_found_not) {
        f_file_stream_flush(file);
        f_file_stream_close(&file);

        return F_file_found_not;
      }

      if (global.main->error.verbosity > f_console_verbosity_quiet_e) {
        controller_print_error_file(global.thread, global.main->error, F_status_set_fine(status), "f_file_stream_open", F_true, path, f_file_operation_open_s, fll_error_file_type_file_e);
      }
    }
    else {
      status = f_file_stream_read(file, &cache->buffer_file);

      if (F_status_is_error(status)) {
        if (global.main->error.verbosity > f_console_verbosity_quiet_e) {
          controller_print_error_file(global.thread, global.main->error, F_status_set_fine(status), "f_file_stream_read", F_true, path, f_file_operation_read_s, fll_error_file_type_file_e);
        }
      }
    }

    f_file_stream_flush(file);
    f_file_stream_close(&file);

    if (F_status_is_error_not(status)) {
      struct stat stat_file;

      status = f_file_stat(path, F_true, &stat_file);

      if (F_status_is_error(status)) {
        if (global.main->error.verbosity > f_console_verbosity_quiet_e) {
          controller_print_error_file(global.thread, global.main->error, F_status_set_fine(status), "f_file_stat", F_true, path, f_file_operation_stat_s, fll_error_file_type_file_e);
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

    // The file exists, do not attempt to overwrite.
    if (f_file_exists(path, F_true) == F_true) {
      return F_status_set_error(F_file_found);
    }

    {
      f_string_dynamic_t path_directory = f_string_dynamic_t_initialize;

      status = f_file_name_directory(path, &path_directory);

      if (F_status_is_error_not(status)) {
        status = f_directory_exists(path_directory);
      }

      f_string_dynamic_resize(0, &path_directory);

      if (F_status_is_error(status)) return status;

      // The directory does not exist so do not bother attempting to create a pid file.
      if (status == F_false) {
        return F_status_set_error(F_directory_not);
      }
    }

    f_file_t file = f_file_t_initialize;

    file.flag = F_file_flag_write_only_d;

    status = f_file_stream_open(path, f_file_open_mode_truncate_s, &file);
    if (F_status_is_error(status)) return status;

    fll_print_format("%i%r", file, pid, f_string_eol_s);

    f_file_stream_flush(file);
    f_file_stream_close(&file);

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_controller_file_pid_create_

#ifndef _di_controller_file_pid_delete_
  f_status_t controller_file_pid_delete(const pid_t pid, const f_string_static_t path) {

    // Only delete if the file exists and there is no error while checking.
    if (f_file_exists(path, F_true) != F_true) {
      return F_none;
    }

    f_status_t status = F_none;
    f_file_t pid_file = f_file_t_initialize;

    status = f_file_stream_open(path, f_file_open_mode_read_s, &pid_file);
    if (F_status_is_error(status)) return status;

    f_string_dynamic_t pid_buffer = f_string_dynamic_t_initialize;

    status = f_file_stream_read(pid_file, &pid_buffer);

    if (F_status_is_error_not(status)) {
      status = f_file_stream_flush(pid_file);
    }

    if (F_status_is_error_not(status)) {
      status = f_file_stream_close(&pid_file);
    }

    if (F_status_is_error_not(status)) {
      f_number_unsigned_t number = 0;
      f_string_range_t range = macro_f_string_range_t_initialize2(pid_buffer.used);

      for (; range.start < pid_buffer.used; ++range.start) {
        if (!isspace(pid_buffer.string[range.start])) break;
      } // for

      for (; range.stop > 0; --range.stop) {
        if (!isspace(pid_buffer.string[range.stop])) break;
      } // for

      status = fl_conversion_dynamic_partial_to_unsigned(fl_conversion_data_base_10_c, pid_buffer, range, &number);

      if (F_status_is_error_not(status) && number == pid) {
        status = f_file_remove(path);
      }
      else {
        status = F_status_set_error(F_number_not);
      }
    }

    f_string_dynamic_resize(0, &pid_buffer);

    return status;
  }
#endif // _di_controller_file_pid_delete_

#ifndef _di_controller_file_pid_read_
  f_status_t controller_file_pid_read(const f_string_static_t path, pid_t * const pid) {

    *pid = 0;

    f_status_t status = f_file_exists(path, F_true);
    if (F_status_is_error(status)) return status;

    if (status != F_true) {
      return F_data_not;
    }

    f_file_t pid_file = f_file_t_initialize;

    status = f_file_stream_open(path, f_file_open_mode_read_s, &pid_file);
    if (F_status_is_error(status)) return status;

    f_string_dynamic_t pid_buffer = f_string_dynamic_t_initialize;

    status = f_file_stream_read(pid_file, &pid_buffer);

    if (F_status_is_error_not(status)) {
      status = f_file_stream_flush(pid_file);
    }

    if (F_status_is_error_not(status)) {
      status = f_file_stream_close(&pid_file);
    }

    if (F_status_is_error_not(status)) {
      f_number_unsigned_t number = 0;
      f_string_range_t range = macro_f_string_range_t_initialize2(pid_buffer.used);

      for (; range.start < pid_buffer.used; ++range.start) {
        if (!isspace(pid_buffer.string[range.start])) break;
      } // for

      for (; range.stop > 0; --range.stop) {
        if (!isspace(pid_buffer.string[range.stop])) break;
      } // for

      status = fl_conversion_dynamic_partial_to_unsigned(fl_conversion_data_base_10_c, pid_buffer, range, &number);

      if (F_status_is_error_not(status)) {
        *pid = (pid_t) number;
      }
    }

    f_string_dynamic_resize(0, &pid_buffer);

    return status;
  }
#endif // _di_controller_file_pid_read_

#ifndef _di_controller_get_id_user_
  f_status_t controller_get_id_user(const f_string_static_t buffer, const f_string_range_t range, controller_cache_t * const cache, uid_t * const id) {

    f_number_unsigned_t number = 0;

    f_status_t status = fl_conversion_dynamic_partial_to_unsigned_detect(fl_conversion_data_base_10_c, buffer, range, &number);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_number) {
        cache->action.generic.used = 0;

        status = f_rip_dynamic_partial_nulless(buffer, range, &cache->action.generic);
        if (F_status_is_error(status)) return status;

        status = f_account_id_by_name(cache->action.generic, id);
        if (F_status_is_error(status)) return status;

        if (status == F_exist_not) {
          return F_status_set_error(F_exist_not);
        }

        return F_none;
      }

      return status;
    }

    if (number > F_type_size_32_unsigned_d) {
      return F_status_set_error(F_number_too_large);
    }

    return status;
  }
#endif // _di_controller_get_id_user_

#ifndef _di_controller_get_id_group_
  f_status_t controller_get_id_group(const f_string_static_t buffer, const f_string_range_t range, controller_cache_t * const cache, gid_t * const id) {

    f_number_unsigned_t number = 0;

    f_status_t status = fl_conversion_dynamic_partial_to_unsigned_detect(fl_conversion_data_base_10_c, buffer, range, &number);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_number) {
        cache->action.generic.used = 0;

        status = f_rip_dynamic_partial_nulless(buffer, range, &cache->action.generic);
        if (F_status_is_error(status)) return status;

        status = f_account_group_id_by_name(cache->action.generic, id);
        if (F_status_is_error(status)) return status;

        if (status == F_exist_not) {
          return F_status_set_error(F_exist_not);
        }

        return F_none;
      }

      return status;
    }

    if (number > F_type_size_32_unsigned_d) {
      return F_status_set_error(F_number_too_large);
    }

    return status;
  }
#endif // _di_controller_get_id_group_

#ifndef _di_controller_path_canonical_relative_
  f_status_t controller_path_canonical_relative(const controller_setting_t * const setting, const f_string_static_t source, f_string_dynamic_t * const destination) {

    {
      const f_status_t status = fl_path_canonical(source, destination);
      if (F_status_is_error(status)) return status;
    }

    if (destination->used >= setting->path_current.used) {
      const f_string_range_t range = macro_f_string_range_t_initialize2(setting->path_current.used);

      if (f_compare_dynamic_partial_string(destination->string, setting->path_current, destination->used, range) == F_equal_to) {
        f_array_length_t length = destination->used - setting->path_current.used;

        if (length) {
          f_char_t temporary[--length];
          temporary[length] = 0;

          memcpy(temporary, destination->string + setting->path_current.used + 1, sizeof(f_char_t) * length);
          memcpy(destination->string, temporary, sizeof(f_char_t) * length);

          destination->string[length] = 0;
          destination->used = length;
        }
        else {
          destination->used = 0;
        }
      }
    }

    return F_none;
  }
#endif // _di_controller_path_canonical_relative_

#ifndef _di_controller_perform_ready_
  f_status_t controller_perform_ready(const controller_global_t * const global, controller_cache_t * const cache, const bool is_entry) {

    if (!is_entry) {
      return F_none;
    }

    if (global->main->parameters.array[controller_parameter_validate_e].result & f_console_result_found_e) {
      if ((global->main->parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e) && global->main->output.verbosity == f_console_verbosity_debug_e) {
        controller_lock_print(global->main->output.to, global->thread);

        fl_print_format("%rPID file '", global->main->output.to, f_string_eol_s);
        fl_print_format("%[%Q%]'.%r", global->main->output.to, global->main->context.set.notable, global->setting->path_pid, global->main->context.set.notable, f_string_eol_s);

        if (global->setting->path_control.used) {
          fl_print_format("%rControl socket '", global->main->output.to, f_string_eol_s);
          fl_print_format("%[%Q%]", global->main->output.to, global->main->context.set.notable, global->setting->path_control, global->main->context.set.notable);
          fl_print_format("'.%r", global->main->output.to, f_string_eol_s);
        }

        controller_unlock_print_flush(global->main->output.to, global->thread);
      }

      return F_none;
    }

    f_status_t status = F_none;

    if (global->setting->entry.pid != controller_entry_pid_disable_e && !global->setting->path_pid.used) {
      status = controller_file_pid_create(global->main->pid, global->setting->path_pid);

      // Report pid file error but because this could be an "init" program, consider the pid file as optional and continue on.
      if (F_status_is_error(status)) {

        // Always return immediately on memory errors.
        if (F_status_set_fine(status) == F_memory_not) {
          if (global->main->error.verbosity > f_console_verbosity_quiet_e) {
            controller_lock_print(global->main->error.to, global->thread);

            controller_print_error_file(0, global->main->error, F_status_set_fine(status), "controller_file_pid_create", F_true, global->setting->path_pid, f_file_operation_create_s, fll_error_file_type_file_e);

            f_file_stream_lock(global->main->error.to);

            controller_entry_print_error_cache(is_entry, global->main->error, cache->action);

            controller_unlock_print_flush(global->main->error.to, global->thread);
          }

          return status;
        }

        if (global->main->warning.verbosity == f_console_verbosity_debug_e) {
          controller_lock_print(global->main->warning.to, global->thread);

          if (F_status_set_fine(status) == F_read_only) {
            fl_print_format("%r%[%QThe pid file '%]", global->main->warning.to, f_string_eol_s, global->main->warning.context, global->main->warning.prefix, global->main->warning.context);
            fl_print_format("%[%Q%]", global->main->warning.to, global->main->warning.notable, global->setting->path_pid, global->main->warning.notable);
            fl_print_format("%[' could not be written because the destination is read only.%]%r", global->main->warning.to, global->main->warning.context, global->main->warning.context, f_string_eol_s);
          }
          else {
            controller_print_error_file(0, global->main->warning, F_status_set_fine(status), "controller_file_pid_create", F_true, global->setting->path_pid, f_file_operation_create_s, fll_error_file_type_file_e);
          }

          controller_entry_print_error_cache(is_entry, global->main->warning, cache->action);

          controller_unlock_print_flush(global->main->warning.to, global->thread);
        }

        status = F_none;
      }
      else {
        global->setting->flag |= controller_setting_flag_pid_created_e;

        if (global->main->output.verbosity == f_console_verbosity_debug_e) {
          controller_lock_print(global->main->output.to, global->thread);

          fl_print_format("%rPID file '", global->main->output.to, f_string_eol_s);
          fl_print_format("%[%Q%]' created.%r", global->main->output.to, global->main->context.set.notable, global->setting->path_pid, global->main->context.set.notable, f_string_eol_s);

          controller_unlock_print_flush(global->main->output.to, global->thread);
        }
      }
    }

    // Disabled, all parts are not yet implemented.
    /*if (global->setting->path_control.used) {
      status = controller_perform_ready_socket(global, cache, is_entry);

      // Do not fail on non-memory errors related to creating the control socket.
      if (F_status_is_error(status) && F_status_set_fine(status) != F_memory) {
        status = F_none;
      }
    }*/

    return status;
  }
#endif // _di_controller_perform_ready_

#ifndef _di_controller_perform_ready_socket_
  f_status_t controller_perform_ready_socket(const controller_global_t * const global, controller_cache_t * const cache, const bool is_entry) {

    f_status_t status = F_none;

    if (global->setting->control.flag & controller_control_flag_readonly_e) {
      if (f_file_exists(global->setting->path_control, F_true) != F_true) {
        if (global->main->output.verbosity == f_console_verbosity_debug_e) {
          controller_lock_print(global->main->output.to, global->thread);

          fl_print_format("%r%[%QControl socket '%]", global->main->warning.to, f_string_eol_s, global->main->warning.context, global->main->warning.prefix, global->main->warning.context);
          fl_print_format("%[%Q%]", global->main->output.to, global->main->context.set.notable, global->setting->path_control, global->main->context.set.notable);
          fl_print_format("' .%r", global->main->output.to, f_string_eol_s);
          fl_print_format("%[' cannot be found while read only mode is enabled and so the Control socket is unavailable.%]%r", global->main->output.to, global->main->warning.context, global->main->warning.context, f_string_eol_s);

          controller_unlock_print_flush(global->main->output.to, global->thread);
        }

        return F_data_not;
      }
    }

    status = f_socket_create(&global->setting->control.server);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_memory_not) {
        controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_socket_create", F_true);
      }
      else if (global->main->output.verbosity == f_console_verbosity_debug_e) {
        controller_lock_print(global->main->output.to, global->thread);

        fl_print_format("%r%[%QControl socket '%]", global->main->warning.to, f_string_eol_s, global->main->warning.context, global->main->warning.prefix, global->main->warning.context);
        fl_print_format("%[%Q%]", global->main->output.to, global->main->context.set.notable, global->setting->path_control, global->main->context.set.notable);
        fl_print_format("%[' could not be created, code %]", global->main->output.to, global->main->warning.context, global->main->warning.context);
        fl_print_format("%[%ui%]", global->main->output.to, global->main->context.set.notable, F_status_set_fine(status), global->main->context.set.notable);
        fl_print_format("%[.%]%r", global->main->output.to, global->main->warning.context, global->main->warning.context, f_string_eol_s);

        controller_unlock_print_flush(global->main->output.to, global->thread);
      }

      return status;
    }

    if (!(global->setting->control.flag & controller_control_flag_readonly_e)) {
      status = f_file_remove(global->setting->path_control);

      if (F_status_set_fine(status) == F_memory_not) {
        controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_file_remove", F_true);

        return status;
      }
    }

    global->setting->control.server.name = global->setting->path_control.string;

    status = f_socket_bind_local(&global->setting->control.server);

    if (F_status_is_error(status)) {
      f_socket_disconnect(&global->setting->control.server, f_socket_close_fast_e);

      if (!(global->setting->control.flag & controller_control_flag_readonly_e)) {
        f_file_remove(global->setting->path_control);
      }

      if (F_status_set_fine(status) == F_memory_not) {
        controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_socket_bind_local", F_true);
      }
      else if (global->main->output.verbosity == f_console_verbosity_debug_e) {
        controller_lock_print(global->main->output.to, global->thread);

        fl_print_format("%r%[%QControl socket '%]", global->main->warning.to, f_string_eol_s, global->main->warning.context, global->main->warning.prefix, global->main->warning.context);
        fl_print_format("%[%Q%]", global->main->output.to, global->main->context.set.notable, global->setting->path_control, global->main->context.set.notable);
        fl_print_format("%[' could not be bound, code %]", global->main->output.to, global->main->warning.context, global->main->warning.context);
        fl_print_format("%[%ui%]", global->main->output.to, global->main->context.set.notable, F_status_set_fine(status), global->main->context.set.notable);
        fl_print_format("%[.%]%r", global->main->output.to, global->main->warning.context, global->main->warning.context, f_string_eol_s);

        controller_unlock_print_flush(global->main->output.to, global->thread);
      }

      return status;
    }

    if (global->setting->control.flag & (controller_control_flag_has_user_e | controller_control_flag_has_group_e)) {
      status = f_file_role_change(global->setting->path_control, global->setting->control.user, global->setting->control.group, F_true);

      if (F_status_is_error(status)) {
        f_socket_disconnect(&global->setting->control.server, f_socket_close_fast_e);

        if (!(global->setting->control.flag & controller_control_flag_readonly_e)) {
          f_file_remove(global->setting->path_control);
        }

        if (F_status_set_fine(status) == F_memory_not) {
          controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_file_role_change", F_true);
        }
        else if (global->main->output.verbosity == f_console_verbosity_debug_e) {
          controller_lock_print(global->main->output.to, global->thread);

          fl_print_format("%r%[%QControl socket '%]", global->main->warning.to, f_string_eol_s, global->main->warning.context, global->main->warning.prefix, global->main->warning.context);
          fl_print_format("%[%Q%]", global->main->output.to, global->main->context.set.notable, global->setting->path_control, global->main->context.set.notable);
          fl_print_format("%[' failed to set file roles, code %]", global->main->output.to, global->main->warning.context, global->main->warning.context);
          fl_print_format("%[%ui%]", global->main->output.to, global->main->context.set.notable, F_status_set_fine(status), global->main->context.set.notable);
          fl_print_format("%[.%]%r", global->main->output.to, global->main->warning.context, global->main->warning.context, f_string_eol_s);

          controller_unlock_print_flush(global->main->output.to, global->thread);
        }

        return status;
      }
    }

    if (global->setting->control.flag & controller_control_flag_has_mode_e) {
      status = f_file_mode_set(global->setting->path_control, global->setting->control.mode);

      if (F_status_is_error(status)) {
        f_socket_disconnect(&global->setting->control.server, f_socket_close_fast_e);

        if (!(global->setting->control.flag & controller_control_flag_readonly_e)) {
          f_file_remove(global->setting->path_control);
        }

        if (F_status_set_fine(status) == F_memory_not) {
          controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_file_role_change", F_true);
        }
        else if (global->main->output.verbosity == f_console_verbosity_debug_e) {
          controller_lock_print(global->main->output.to, global->thread);

          fl_print_format("%r%[%QControl socket '%]", global->main->warning.to, f_string_eol_s, global->main->warning.context, global->main->warning.prefix, global->main->warning.context);
          fl_print_format("%[%Q%]", global->main->output.to, global->main->context.set.notable, global->setting->path_control, global->main->context.set.notable);
          fl_print_format("%[' failed to set file mode, code %]", global->main->output.to, global->main->warning.context, global->main->warning.context);
          fl_print_format("%[%ui%]", global->main->output.to, global->main->context.set.notable, F_status_set_fine(status), global->main->context.set.notable);
          fl_print_format("%[.%]%r", global->main->output.to, global->main->warning.context, global->main->warning.context, f_string_eol_s);

          controller_unlock_print_flush(global->main->output.to, global->thread);
        }

        return status;
      }
    }

    if (global->main->output.verbosity == f_console_verbosity_debug_e) {
      controller_lock_print(global->main->output.to, global->thread);

      fl_print_format("%rControl socket '", global->main->output.to, f_string_eol_s);
      fl_print_format("%[%Q%]", global->main->output.to, global->main->context.set.notable, global->setting->path_control, global->main->context.set.notable);
      fl_print_format("' created.%r", global->main->output.to, f_string_eol_s);

      controller_unlock_print_flush(global->main->output.to, global->thread);
    }

    // Disabled, not yet implemented.
    //status = f_thread_create(0, &global->thread->id_control, &controller_thread_control, (void *) global);

    if (status == F_child) {
      return status;
    }

    if (F_status_is_error(status)) {
      f_socket_disconnect(&global->setting->control.server, f_socket_close_fast_e);

      if (!(global->setting->control.flag & controller_control_flag_readonly_e)) {
        f_file_remove(global->setting->path_control);
      }

      if (global->thread->id_control) {
        f_thread_cancel(global->thread->id_control);
        f_thread_join(global->thread->id_control, 0);

        global->thread->id_control = 0;
      }

      if (global->main->error.verbosity > f_console_verbosity_quiet_e) {
        controller_print_error(global->thread, global->main->error, F_status_set_fine(status), "f_thread_create", F_true);
      }
    }

    return F_none;
  }
#endif // _di_controller_perform_ready_socket_

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

    if (status == F_parameter || status == F_found_not || status == F_interrupt || status == F_support_not || status == F_critical) {
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
    if ((setting->flag & controller_setting_flag_interruptible_e) && time.tv_sec) {
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
      status = f_utf_is_alphabetic(name.string, name.used);

      if (F_status_is_error(status)) return status;
      if (status == F_false) return F_false;
    }

    for (f_array_length_t i = macro_f_utf_byte_width(name.string[0]); i < name.used; i += macro_f_utf_byte_width(name.string[i])) {

      if (name.string[i] == '_') continue;

      status = f_utf_is_alphabetic_digit(name.string, name.used, 0);

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
