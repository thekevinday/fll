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

    if (F_status_is_error(main->setting.state.status)) return;

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

    f_string_static_t * const argv = main->program.parameters.arguments.array;

    main->setting.state.status = f_path_current(F_false, &main->process->path_current);

    if (F_status_is_error(main->setting.state.status)) {
      fll_error_print(&main->program.error, F_status_set_fine(main->setting.state.status), "f_path_current", fll_error_file_flag_fallback_e);
    }
    else {
      if (main->program.parameters.array[controller_parameter_settings_e].result & f_console_result_found_e) {
        if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
          controller_lock_print(main->program.error.to, 0);

          fl_print_format("%r%[%QThe parameter '%]", main->program.error.to, f_string_eol_s, main->program.error.context, main->program.error.prefix, main->program.error.context);
          fl_print_format(f_string_format_rr_single_s.string, main->program.error.to, main->program.context.set.notable, f_console_symbol_long_normal_s, controller_long_settings_s, main->program.context.set.notable);
          fl_print_format("%[' is specified, but no value is given.%]%r", main->program.error.to, main->program.error.context, main->program.error.context, f_string_eol_s);

          controller_unlock_print_flush(main->program.error.to, 0);
        }

        main->setting.state.status = F_status_set_error(F_parameter);
      }
      else if (main->program.parameters.array[controller_parameter_settings_e].locations.used) {
        const f_number_unsigned_t index = main->program.parameters.array[controller_parameter_settings_e].values.array[main->program.parameters.array[controller_parameter_settings_e].values.used - 1];

        main->setting.state.status = controller_path_canonical_relative(main->process, argv[index], &main->process->path_setting);

        if (F_status_is_error(main->setting.state.status)) {
          fll_error_file_print(&main->program.error, F_status_set_fine(main->setting.state.status), "controller_path_canonical_relative", fll_error_file_flag_fallback_e, argv[index], f_file_operation_verify_s, fll_error_file_type_path_e);
        }
      }
      else {
        main->process->path_setting.used = 0;

        if (main->setting.flag & controller_main_flag_init_e) {
          main->setting.state.status = f_string_dynamic_append(*main->setting.default_path_setting_init, &main->process->path_setting);
        }
        else {
          main->setting.state.status = f_string_dynamic_append(*main->setting.default_path_setting, &main->process->path_setting);
        }

        if (F_status_is_error(main->setting.state.status)) {
          fll_error_print(&main->program.error, F_status_set_fine(main->setting.state.status), "f_string_dynamic_append", fll_error_file_flag_fallback_e);
        }
      }
    }

    if (F_status_is_error_not(main->setting.state.status)) {
      if (main->program.parameters.array[controller_parameter_pid_e].result & f_console_result_found_e) {
        if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
          controller_lock_print(main->program.error.to, 0);

          fl_print_format("%r%[%QThe parameter '%]", main->program.error.to, f_string_eol_s, main->program.error.context, main->program.error.prefix, main->program.error.context);
          fl_print_format(f_string_format_rr_single_s.string, main->program.error.to, main->program.context.set.notable, f_console_symbol_long_normal_s, controller_long_pid_s, main->program.context.set.notable);
          fl_print_format("%[' is specified, but no value is given.%]%r", main->program.error.to, main->program.error.context, main->program.error.context, f_string_eol_s);

          controller_unlock_print_flush(main->program.error.to, 0);
        }

        main->setting.state.status = F_status_set_error(F_parameter);
      }
      else if (main->program.parameters.array[controller_parameter_pid_e].locations.used) {
        main->process->path_pid.used = 0;

        const f_number_unsigned_t index = main->program.parameters.array[controller_parameter_pid_e].values.array[main->program.parameters.array[controller_parameter_pid_e].values.used - 1];

        if (argv[index].used) {
          main->setting.state.status = controller_path_canonical_relative(main->process, argv[index], &main->process->path_pid);

          if (F_status_is_error(main->setting.state.status)) {
            fll_error_file_print(&main->program.error, F_status_set_fine(main->setting.state.status), "controller_path_canonical_relative", fll_error_file_flag_fallback_e, argv[index], f_file_operation_verify_s, fll_error_file_type_path_e);
          }
        }
      }
    }

    if (F_status_is_error_not(main->setting.state.status) && !main->process->path_pid.used && !main->program.parameters.array[controller_parameter_pid_e].locations.used) {
      if (main->setting.flag & controller_main_flag_init_e) {
        main->setting.state.status = f_string_dynamic_append(*main->setting.default_path_pid_init, &main->process->path_pid);
      }
      else {
        main->setting.state.status = f_string_dynamic_append(*main->setting.default_path_pid, &main->process->path_pid);
      }

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_string_dynamic_append(f_path_separator_s, &main->process->path_pid);
      }

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_string_dynamic_append(*main->setting.default_path_pid_prefix, &main->process->path_pid);
      }

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_string_dynamic_append(main->process->name_entry, &main->process->path_pid);
      }

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_string_dynamic_append(*main->setting.default_path_pid_suffix, &main->process->path_pid);
      }

      if (F_status_is_error(main->setting.state.status)) {
        fll_error_print(&main->program.error, F_status_set_fine(main->setting.state.status), "f_string_dynamic_append", fll_error_file_flag_fallback_e);
      }
    }

    if (F_status_is_error_not(main->setting.state.status)) {
      if (main->program.parameters.array[controller_parameter_cgroup_e].result & f_console_result_found_e) {
        if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
          controller_lock_print(main->program.error.to, 0);

          fl_print_format("%r%[%QThe parameter '%]", main->program.error.to, f_string_eol_s, main->program.error.context, main->program.error.prefix, main->program.error.context);
          fl_print_format(f_string_format_rr_single_s.string, main->program.error.to, main->program.context.set.notable, f_console_symbol_long_normal_s, controller_long_cgroup_s, main->program.context.set.notable);
          fl_print_format("%[' is specified, but no value is given.%]%r", main->program.error.to, main->program.error.context, main->program.error.context, f_string_eol_s);

          controller_unlock_print_flush(main->program.error.to, 0);
        }

        main->setting.state.status = F_status_set_error(F_parameter);
      }
      else if (main->program.parameters.array[controller_parameter_cgroup_e].locations.used) {
        const f_number_unsigned_t index = main->program.parameters.array[controller_parameter_cgroup_e].values.array[main->program.parameters.array[controller_parameter_cgroup_e].values.used - 1];

        if (argv[index].used) {
          main->setting.state.status = controller_path_canonical_relative(main->process, argv[index], &main->process->path_cgroup);

          if (F_status_is_error(main->setting.state.status)) {
            fll_error_file_print(&main->program.error, F_status_set_fine(main->setting.state.status), "controller_path_canonical_relative", fll_error_file_flag_fallback_e, argv[index], f_file_operation_verify_s, fll_error_file_type_path_e);
          }
          else {
            main->setting.state.status = f_string_append_assure(F_path_separator_s, 1, &main->process->path_cgroup);

            if (F_status_is_error(main->setting.state.status)) {
              fll_error_print(&main->program.error, F_status_set_fine(main->setting.state.status), "f_string_append_assure", fll_error_file_flag_fallback_e);
            }
          }
        }
        else {
          if (main->program.warning.verbosity == f_console_verbosity_debug_e) {
            controller_lock_print(main->program.warning.to, 0);

            fl_print_format("%r%[%QThe parameter '%]", main->program.warning.to, f_string_eol_s, main->program.warning.context, main->program.warning.prefix, main->program.warning.context);
            fl_print_format(f_string_format_rr_single_s.string, main->program.warning.to, main->program.context.set.notable, f_console_symbol_long_normal_s, controller_long_cgroup_s, main->program.context.set.notable);
            fl_print_format("%[' must be a file directory path but instead is an empty string, falling back to the default.%]%r", main->program.warning.to, main->program.warning.context, main->program.warning.context, f_string_eol_s);

            controller_unlock_print_flush(main->program.warning.to, 0);
          }
        }
      }
    }

    if (F_status_is_error_not(main->setting.state.status) && (main->program.parameters.array[controller_parameter_daemon_e].result & f_console_result_found_e)) {
      if (main->program.parameters.array[controller_parameter_validate_e].result & f_console_result_found_e) {
        if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
          controller_lock_print(main->program.error.to, 0);

          fl_print_format("%r%[%QThe parameter '%]", main->program.error.to, f_string_eol_s, main->program.error.context, main->program.error.prefix, main->program.error.context);
          fl_print_format("%[' must not be specified with the parameter '%]", main->program.error.to, main->program.error.context, main->program.error.context);
          fl_print_format(f_string_format_rr_single_s.string, main->program.error.to, main->program.context.set.notable, f_console_symbol_long_normal_s, controller_long_daemon_s, main->program.context.set.notable);
          fl_print_format(f_string_format_sentence_end_quote_s.string, main->program.error.to, main->program.error.context, main->program.error.context, f_string_eol_s);

          controller_unlock_print_flush(main->program.error.to, 0);
        }

        main->setting.state.status = F_status_set_error(F_parameter);
      }
    }

    // Handle defaults dependent on the "as init" execution state.
    if (main->setting.flag & controller_main_flag_init_e) {
      main->process->entry.pid = controller_entry_pid_disable_e;
      main->process->entry.show = controller_entry_show_init_e;

      if (main->program.parameters.array[controller_parameter_interruptible_e].result & f_console_result_found_e) {
        main->process->flag |= controller_setting_flag_interruptible_e;
      }
      else {
        main->process->flag &= ~controller_setting_flag_interruptible_e;
      }
    }
    else {
      if (main->program.parameters.array[controller_parameter_uninterruptible_e].result & f_console_result_found_e) {
        main->process->flag &= ~controller_setting_flag_interruptible_e;
      }
      else {
        main->process->flag |= controller_setting_flag_interruptible_e;
      }
    }

    if (F_status_is_error_not(main->setting.state.status)) {
      f_signal_set_fill(&main->program.signal.set);

      main->setting.state.status = f_thread_signal_mask(SIG_BLOCK, &main->program.signal.set, 0);

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_signal_open(&main->program.signal);
      }

      // If there is an error opening a signal descriptor, then do not handle signals.
      if (F_status_is_error(main->setting.state.status)) {
        f_signal_mask(SIG_UNBLOCK, &main->program.signal.set, 0);
        f_signal_close(&main->program.signal);
      }

      // A control file path is required.
      if (!main->process->path_cgroup.used) {
        main->setting.state.status = f_string_append_nulless(F_control_group_path_system_prefix_s, F_control_group_path_system_prefix_s_length, &main->process->path_cgroup);

        if (F_status_is_error_not(main->setting.state.status)) {
          main->setting.state.status = f_string_append_nulless(F_control_group_path_system_default_s, F_control_group_path_system_default_s_length, &main->process->path_cgroup);
        }

        if (F_status_is_error(main->setting.state.status)) {
          fll_error_print(&main->program.error, F_status_set_fine(main->setting.state.status), "f_string_append_nulless", fll_error_file_flag_fallback_e);
        }
        else {
          main->setting.state.status = f_string_append_assure(F_path_separator_s, 1, &main->process->path_cgroup);

          if (F_status_is_error(main->setting.state.status)) {
            fll_error_print(&main->program.error, F_status_set_fine(main->setting.state.status), "f_string_append_assure", fll_error_file_flag_fallback_e);
          }
        }
      }
    }

    if (F_status_is_error_not(main->setting.state.status)) {
      main->setting.state.status = controller_thread_main(main, main->process);
    }

    // Ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (F_status_is_error(main->setting.state.status) && main->program.output.verbosity != f_console_verbosity_quiet_e) {
      if (F_status_set_fine(main->setting.state.status) == F_interrupt) {
        f_file_stream_flush(main->program.output.to);
      }

      fll_print_dynamic_raw(f_string_eol_s, main->program.output.to);
    }

    if (main->setting.state.status != F_child && (main->process->flag & controller_setting_flag_pid_created_e)) {
      const f_status_t status_delete = controller_file_pid_delete(main->program.pid, main->process->path_pid);

      if (F_status_is_error(status_delete) && main->program.warning.verbosity == f_console_verbosity_debug_e) {
        if (F_status_set_fine(status_delete) == F_number_not) {
          controller_lock_print(main->program.warning.to, 0);

          fl_print_format("%r%[%QThe pid file '%]", main->program.warning.to, f_string_eol_s, main->program.warning.context, main->program.warning.prefix, main->program.warning.context);
          fl_print_format(f_string_format_Q_single_s.string, main->program.warning.to, main->program.warning.notable, main->process->path_pid, main->program.warning.notable);
          fl_print_format("%[' must not be specified with the parameter '%]", main->program.warning.to, main->program.warning.context, main->program.warning.context);
          fl_print_format("%[%i%]", main->program.warning.to, main->program.warning.notable, main->program.pid, main->program.warning.notable);
          fl_print_format("%[' doesn't contain the expected number, not deleting file.%]%r", main->program.warning.to, main->program.warning.context, main->program.warning.context, f_string_eol_s);

          controller_unlock_print_flush(main->program.warning.to, 0);
        }
        else if (F_status_set_fine(status_delete) != F_interrupt) {
          fll_error_file_print(&main->program.warning, F_status_set_fine(status_delete), "controller_file_pid_delete", fll_error_file_flag_fallback_e, main->process->path_pid, f_file_operation_delete_s, fll_error_file_type_file_e);
        }
      }
    }

    if (main->setting.state.status != F_child && main->process->path_control.used) {
      f_socket_disconnect(&main->process->control.server, f_socket_close_read_write_e);

      if (!(main->process->control.flag & controller_control_flag_readonly_e)) {
        f_file_remove(main->process->path_control);
      }
    }
  }
#endif // _di_controller_main_

#ifdef __cplusplus
} // extern "C"
#endif
