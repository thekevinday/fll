#include "controller.h"
#include "common/private-common.h"
#include "control/private-control.h"
#include "controller/private-controller.h"
#include "controller/private-controller_print.h"
#include "entry/private-entry.h"
#include "lock/private-lock_print.h"
#include "rule/private-rule.h"
#include "thread/private-thread.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_main_
  void controller_main(controller_main_t * const main) {

    if (F_status_is_error(status)) return;

    if ((main->setting.flag & controller_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }

    main->setting.state.status = F_okay;

    if (main->setting.flag & controller_main_flag_version_copyright_help_e) {
      if (main->setting.flag & controller_main_flag_help_e) {
        controller_print_message_help(&main->program.message);
      }
      else if (main->setting.flag & controller_main_flag_version_e) {
        fll_program_print_version(&main->program.message, controller_program_version_s);
      }
      else if (main->setting.flag & controller_main_flag_copyright_e) {
        fll_program_print_copyright(&main->program.message);
      }

      if ((main->setting.flag & controller_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    if ((main->setting.flag & controller_main_flag_operation_build_e) && (main->setting.flag & controller_main_flag_operation_make_e)) {
      main->setting.state.status = F_status_set_error(F_parameter);

      controller_print_error_parameter_operation_not_with(&main->program.error, controller_other_operation_build_s, controller_other_operation_make_s);

      if ((main->setting.flag & controller_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    f_string_static_t * const argv = main->parameters.arguments.array;

    controller_process_t process = controller_process_t_initialize;

    process.control.server.address = (struct sockaddr *) &process.control.address;
    process.control.server.domain = f_socket_protocol_family_local_e;
    process.control.server.type = f_socket_type_stream_d;
    process.control.server.length = sizeof(struct sockaddr_un);

    memset(process.control.server.address, 0, process.control.server.length);

    if (main->parameters.remaining.used) {
      status = f_string_dynamic_append(argv[main->parameters.remaining.array[0]], &process.name_entry);
    }
    else {
      status = f_string_dynamic_append(controller_default_s, &process.name_entry);
    }

    if (F_status_is_error(status)) {
      fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_append", fll_error_file_flag_fallback_e);

      return status;
    }

    if (main->parameters.array[controller_parameter_init_e].result & f_console_result_found_e) {
      main->as_init = F_true;
    }

    if (main->as_init) {
      process.mode = controller_setting_mode_service_e;
    }

    status = f_path_current(F_false, &process.path_current);

    if (F_status_is_error(status)) {
      fll_error_print(main->error, F_status_set_fine(status), "f_path_current", fll_error_file_flag_fallback_e);
    }
    else {
      if (main->parameters.array[controller_parameter_settings_e].result & f_console_result_found_e) {
        if (main->error.verbosity > f_console_verbosity_quiet_e) {
          controller_lock_print(main->error.to, 0);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format(f_string_format_rr_single_s.string, main->error.to, main->context.set.notable, f_console_symbol_long_normal_s, controller_long_settings_s, main->context.set.notable);
          fl_print_format("%[' is specified, but no value is given.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

          controller_unlock_print_flush(main->error.to, 0);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters.array[controller_parameter_settings_e].locations.used) {
        const f_number_unsigned_t index = main->parameters.array[controller_parameter_settings_e].values.array[main->parameters.array[controller_parameter_settings_e].values.used - 1];

        status = controller_path_canonical_relative(&process, argv[index], &process.path_setting);

        if (F_status_is_error(status)) {
          fll_error_file_print(main->error, F_status_set_fine(status), "controller_path_canonical_relative", fll_error_file_flag_fallback_e, argv[index], f_file_operation_verify_s, fll_error_file_type_path_e);
        }
      }
      else {
        process.path_setting.used = 0;

        if (main->as_init) {
          status = f_string_dynamic_append(*main->default_path_setting_init, &process.path_setting);
        }
        else {
          status = f_string_dynamic_append(*main->default_path_setting, &process.path_setting);
        }

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_append", fll_error_file_flag_fallback_e);
        }
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[controller_parameter_pid_e].result & f_console_result_found_e) {
        if (main->error.verbosity > f_console_verbosity_quiet_e) {
          controller_lock_print(main->error.to, 0);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format(f_string_format_rr_single_s.string, main->error.to, main->context.set.notable, f_console_symbol_long_normal_s, controller_long_pid_s, main->context.set.notable);
          fl_print_format("%[' is specified, but no value is given.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

          controller_unlock_print_flush(main->error.to, 0);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters.array[controller_parameter_pid_e].locations.used) {
        process.path_pid.used = 0;

        const f_number_unsigned_t index = main->parameters.array[controller_parameter_pid_e].values.array[main->parameters.array[controller_parameter_pid_e].values.used - 1];

        if (argv[index].used) {
          status = controller_path_canonical_relative(&process, argv[index], &process.path_pid);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "controller_path_canonical_relative", fll_error_file_flag_fallback_e, argv[index], f_file_operation_verify_s, fll_error_file_type_path_e);
          }
        }
      }
    }

    if (F_status_is_error_not(status) && !process.path_pid.used && !main->parameters.array[controller_parameter_pid_e].locations.used) {
      if (main->as_init) {
        status = f_string_dynamic_append(*main->default_path_pid_init, &process.path_pid);
      }
      else {
        status = f_string_dynamic_append(*main->default_path_pid, &process.path_pid);
      }

      if (F_status_is_error_not(status)) {
        status = f_string_dynamic_append(f_path_separator_s, &process.path_pid);
      }

      if (F_status_is_error_not(status)) {
        status = f_string_dynamic_append(*main->default_path_pid_prefix, &process.path_pid);
      }

      if (F_status_is_error_not(status)) {
        status = f_string_dynamic_append(process.name_entry, &process.path_pid);
      }

      if (F_status_is_error_not(status)) {
        status = f_string_dynamic_append(*main->default_path_pid_suffix, &process.path_pid);
      }

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_append", fll_error_file_flag_fallback_e);
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[controller_parameter_cgroup_e].result & f_console_result_found_e) {
        if (main->error.verbosity > f_console_verbosity_quiet_e) {
          controller_lock_print(main->error.to, 0);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format(f_string_format_rr_single_s.string, main->error.to, main->context.set.notable, f_console_symbol_long_normal_s, controller_long_cgroup_s, main->context.set.notable);
          fl_print_format("%[' is specified, but no value is given.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

          controller_unlock_print_flush(main->error.to, 0);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters.array[controller_parameter_cgroup_e].locations.used) {
        const f_number_unsigned_t index = main->parameters.array[controller_parameter_cgroup_e].values.array[main->parameters.array[controller_parameter_cgroup_e].values.used - 1];

        if (argv[index].used) {
          status = controller_path_canonical_relative(&process, argv[index], &process.path_cgroup);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "controller_path_canonical_relative", fll_error_file_flag_fallback_e, argv[index], f_file_operation_verify_s, fll_error_file_type_path_e);
          }
          else {
            status = f_string_append_assure(F_path_separator_s, 1, &process.path_cgroup);

            if (F_status_is_error(status)) {
              fll_error_print(main->error, F_status_set_fine(status), "f_string_append_assure", fll_error_file_flag_fallback_e);
            }
          }
        }
        else {
          if (main->warning.verbosity == f_console_verbosity_debug_e) {
            controller_lock_print(main->warning.to, 0);

            fl_print_format("%r%[%QThe parameter '%]", main->warning.to, f_string_eol_s, main->warning.context, main->warning.prefix, main->warning.context);
            fl_print_format(f_string_format_rr_single_s.string, main->warning.to, main->context.set.notable, f_console_symbol_long_normal_s, controller_long_cgroup_s, main->context.set.notable);
            fl_print_format("%[' must be a file directory path but instead is an empty string, falling back to the default.%]%r", main->warning.to, main->warning.context, main->warning.context, f_string_eol_s);

            controller_unlock_print_flush(main->warning.to, 0);
          }
        }
      }
    }

    if (F_status_is_error_not(status) && (main->parameters.array[controller_parameter_daemon_e].result & f_console_result_found_e)) {
      if (main->parameters.array[controller_parameter_validate_e].result & f_console_result_found_e) {
        if (main->error.verbosity > f_console_verbosity_quiet_e) {
          controller_lock_print(main->error.to, 0);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[' must not be specified with the parameter '%]", main->error.to, main->error.context, main->error.context);
          fl_print_format(f_string_format_rr_single_s.string, main->error.to, main->context.set.notable, f_console_symbol_long_normal_s, controller_long_daemon_s, main->context.set.notable);
          fl_print_format(f_string_format_sentence_end_quote_s.string, main->error.to, main->error.context, main->error.context, f_string_eol_s);

          controller_unlock_print_flush(main->error.to, 0);
        }

        status = F_status_set_error(F_parameter);
      }
    }

    // Handle defaults dependent on the "as init" execution state.
    if (main->as_init) {
      process.entry.pid = controller_entry_pid_disable_e;
      process.entry.show = controller_entry_show_init_e;

      if (main->parameters.array[controller_parameter_interruptible_e].result & f_console_result_found_e) {
        process.flag |= controller_setting_flag_interruptible_e;
      }
      else {
        process.flag &= ~controller_setting_flag_interruptible_e;
      }
    }
    else {
      if (main->parameters.array[controller_parameter_uninterruptible_e].result & f_console_result_found_e) {
        process.flag &= ~controller_setting_flag_interruptible_e;
      }
      else {
        process.flag |= controller_setting_flag_interruptible_e;
      }
    }

    if (F_status_is_error_not(status)) {
      f_signal_set_fill(&main->signal.set);

      status = f_thread_signal_mask(SIG_BLOCK, &main->signal.set, 0);

      if (F_status_is_error_not(status)) {
        status = f_signal_open(&main->signal);
      }

      // If there is an error opening a signal descriptor, then do not handle signals.
      if (F_status_is_error(status)) {
        f_signal_mask(SIG_UNBLOCK, &main->signal.set, 0);
        f_signal_close(&main->signal);
      }

      // A control file path is required.
      if (!process.path_cgroup.used) {
        status = f_string_append_nulless(F_control_group_path_system_prefix_s, F_control_group_path_system_prefix_s_length, &process.path_cgroup);

        if (F_status_is_error_not(status)) {
          status = f_string_append_nulless(F_control_group_path_system_default_s, F_control_group_path_system_default_s_length, &process.path_cgroup);
        }

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "f_string_append_nulless", fll_error_file_flag_fallback_e);
        }
        else {
          status = f_string_append_assure(F_path_separator_s, 1, &process.path_cgroup);

          if (F_status_is_error(status)) {
            fll_error_print(main->error, F_status_set_fine(status), "f_string_append_assure", fll_error_file_flag_fallback_e);
          }
        }
      }
    }

    if (F_status_is_error_not(status)) {
      status = controller_thread_main(main, &process);
    }

    // Ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (F_status_is_error(status) && main->output.verbosity != f_console_verbosity_quiet_e) {
      if (F_status_set_fine(status) == F_interrupt) {
        f_file_stream_flush(main->output.to);
      }

      fll_print_dynamic_raw(f_string_eol_s, main->output.to);
    }

    if (status != F_child && (process.flag & controller_setting_flag_pid_created_e)) {
      const f_status_t status_delete = controller_file_pid_delete(main->pid, process.path_pid);

      if (F_status_is_error(status_delete) && main->warning.verbosity == f_console_verbosity_debug_e) {
        if (F_status_set_fine(status_delete) == F_number_not) {
          controller_lock_print(main->warning.to, 0);

          fl_print_format("%r%[%QThe pid file '%]", main->warning.to, f_string_eol_s, main->warning.context, main->warning.prefix, main->warning.context);
          fl_print_format(f_string_format_Q_single_s.string, main->warning.to, main->warning.notable, process.path_pid, main->warning.notable);
          fl_print_format("%[' must not be specified with the parameter '%]", main->warning.to, main->warning.context, main->warning.context);
          fl_print_format("%[%i%]", main->warning.to, main->warning.notable, main->pid, main->warning.notable);
          fl_print_format("%[' doesn't contain the expected number, not deleting file.%]%r", main->warning.to, main->warning.context, main->warning.context, f_string_eol_s);

          controller_unlock_print_flush(main->warning.to, 0);
        }
        else if (F_status_set_fine(status_delete) != F_interrupt) {
          fll_error_file_print(main->warning, F_status_set_fine(status_delete), "controller_file_pid_delete", fll_error_file_flag_fallback_e, process.path_pid, f_file_operation_delete_s, fll_error_file_type_file_e);
        }
      }
    }

    if (status != F_child && process.path_control.used) {
      f_socket_disconnect(&process.control.server, f_socket_close_read_write_e);

      if (!(process.control.flag & controller_control_flag_readonly_e)) {
        f_file_remove(process.path_control);
      }
    }

    return status;
  }
#endif // _di_controller_main_

#ifdef __cplusplus
} // extern "C"
#endif
