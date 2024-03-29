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

#ifndef _di_controller_print_copyright_
  f_status_t controller_print_copyright(const f_file_t file, const bool full) {

    flockfile(file.stream);

    fl_print_format("%rCopyright © 2007-2024 Kevin Day.%r", file.stream, f_string_eol_s, f_string_eol_s);

    #ifndef _di_detailed_copyright_
      if (full) {
        fl_print_format("%rThis program comes with ABSOLUTELY NO WARRANTY.%r", file.stream, f_string_eol_s, f_string_eol_s);
        fl_print_format("This is free software, and you are welcome to modify or redistribute in accordance to the license.%r", file.stream, f_string_eol_s);
      }
    #endif // _di_detailed_copyright_

    fl_print_format("%rSource code license lgpl-2.1-or-later.%r", file.stream, f_string_eol_s, f_string_eol_s);
    fl_print_format("Standard and specification license open-standard-license-1.0.%r", file.stream, f_string_eol_s);
    fl_print_format("Documentation license cc-by-sa-4.0.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_controller_print_copyright_

#ifndef _di_controller_print_help_
  f_status_t controller_print_help(controller_main_t * const main) {

    if (!main) return F_output_not;

    controller_lock_print(main->output.to, 0);

    fll_program_print_help_header(main->output.to, main->context, *main->program_name_long, controller_program_version_s);

    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print this help message.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Do not main->output.to in color.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity beyond normal main->output.to.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Set verbosity to normal main->output.to.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Increase verbosity beyond normal main->output.to.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Enable debugging, increasing verbosity beyond normal main->output.to.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Print only the version number.");

    f_print_dynamic_raw(f_string_eol_s, main->output.to.stream);

    fll_program_print_help_option(main->output.to, main->context, controller_short_cgroup_s, controller_long_cgroup_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "         Specify a custom control group file path, such as '" F_control_group_path_system_prefix_s F_control_group_path_system_default_s "'.");
    fll_program_print_help_option(main->output.to, main->context, controller_short_daemon_s, controller_long_daemon_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "         Run in daemon only mode (do not process the entry).");
    fll_program_print_help_option(main->output.to, main->context, controller_short_init_s, controller_long_init_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "           The program will run as an init replacement.");
    fll_program_print_help_option(main->output.to, main->context, controller_short_interruptible_s, controller_long_interruptible_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Designate that this program can be interrupted by a signal.");
    fll_program_print_help_option(main->output.to, main->context, controller_short_pid_s, controller_long_pid_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "            Specify a custom pid file path, such as 'controller/run/default.pid'.");
    fll_program_print_help_option(main->output.to, main->context, controller_short_settings_s, controller_long_settings_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "       Specify a custom settings path, such as 'controller/'.");
    fll_program_print_help_option(main->output.to, main->context, controller_short_simulate_s, controller_long_simulate_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "       Run as a simulation.");
    fll_program_print_help_option(main->output.to, main->context, controller_short_socket_s, controller_long_socket_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "         Specify a custom socket file path, such as 'controller/run/default.socket'.");
    fll_program_print_help_option(main->output.to, main->context, controller_short_uninterruptible_s, controller_long_uninterruptible_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Designate that this program cannot be interrupted by a signal.");
    fll_program_print_help_option(main->output.to, main->context, controller_short_validate_s, controller_long_validate_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "       Validate the settings (entry and rules) without running (does not simulate).");

    fll_program_print_help_usage(main->output.to, main->context, *main->program_name, controller_entry_s);

    fl_print_format("  When both the %[%r%r%] parameter and the", main->output.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, controller_long_simulate_s, main->context.set.notable);
    fl_print_format(" %[%r%r%] parameter are specified, then additional information on each would be executed rule is printed but no simulation is performed.%r%r", main->output.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, controller_long_validate_s, main->context.set.notable, f_string_eol_s, f_string_eol_s);

    const f_string_static_t interruptable = main->as_init ? controller_long_uninterruptible_s : controller_long_interruptible_s;

    fl_print_format("  The default interrupt behavior is to operate as if the %[%r%r%] parameter is passed.%r%r", main->output.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, interruptable, main->context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  Specify an empty string for the %[%r%r%] parameter to disable pid file creation for this program.%r%r", main->output.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, controller_long_pid_s, main->context.set.notable, f_string_eol_s, f_string_eol_s);

    controller_unlock_print_flush(main->output.to, 0);

    return F_none;
  }
#endif // _di_controller_print_help_

#ifndef _di_controller_main_
  f_status_t controller_main(controller_main_t * const main, const f_console_arguments_t *arguments) {

    f_status_t status = F_none;

    {
      f_console_parameter_id_t ids[3] = { controller_parameter_no_color_e, controller_parameter_light_e, controller_parameter_dark_e };
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

      status = fll_program_parameter_process(*arguments, &main->parameters, choices, F_true, &main->context);

      main->output.set = &main->context.set;
      main->error.set = &main->context.set;
      main->warning.set = &main->context.set;

      if (main->context.set.error.before) {
        main->output.context = f_color_set_empty_s;
        main->output.notable = main->context.set.notable;

        main->error.context = main->context.set.error;
        main->error.notable = main->context.set.notable;

        main->warning.context = main->context.set.warning;
        main->warning.notable = main->context.set.notable;
      }
      else {
        f_color_set_t *sets[] = { &main->output.context, &main->output.notable, &main->error.context, &main->error.notable, &main->warning.context, &main->warning.notable, 0 };

        fll_program_parameter_process_empty(&main->context, sets);
      }

      if (F_status_is_error(status)) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process", F_true);
          fll_print_dynamic_raw(f_string_eol_s, main->error.to.stream);
        }

        return F_status_set_error(status);
      }
    }

    // Identify priority of verbosity related parameters.
    {
      f_console_parameter_id_t ids[5] = { controller_parameter_verbosity_quiet_e, controller_parameter_verbosity_error_e, controller_parameter_verbosity_normal_e, controller_parameter_verbosity_verbose_e, controller_parameter_verbosity_debug_e };
      f_console_parameter_id_t choice = 0;
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 5);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

        return status;
      }

      if (choice == controller_parameter_verbosity_quiet_e) {
        main->output.verbosity = f_console_verbosity_quiet_e;
        main->error.verbosity = f_console_verbosity_quiet_e;
        main->warning.verbosity = f_console_verbosity_quiet_e;
      }
      else if (choice == controller_parameter_verbosity_error_e) {
        main->output.verbosity = f_console_verbosity_error_e;
        main->error.verbosity = f_console_verbosity_error_e;
        main->warning.verbosity = f_console_verbosity_error_e;
      }
      else if (choice == controller_parameter_verbosity_normal_e) {
        main->output.verbosity = f_console_verbosity_normal_e;
        main->error.verbosity = f_console_verbosity_normal_e;
        main->warning.verbosity = f_console_verbosity_normal_e;
      }
      else if (choice == controller_parameter_verbosity_verbose_e) {
        main->output.verbosity = f_console_verbosity_verbose_e;
        main->error.verbosity = f_console_verbosity_verbose_e;
        main->warning.verbosity = f_console_verbosity_verbose_e;
      }
      else if (choice == controller_parameter_verbosity_debug_e) {
        main->output.verbosity = f_console_verbosity_debug_e;
        main->error.verbosity = f_console_verbosity_debug_e;
        main->warning.verbosity = f_console_verbosity_debug_e;
      }
    }

    if (main->parameters.array[controller_parameter_help_e].result == f_console_result_found_e) {
      controller_print_help(main);

      return F_none;
    }

    if (main->parameters.array[controller_parameter_version_e].result == f_console_result_found_e) {
      controller_lock_print(main->output.to, 0);

      fll_program_print_version(main->output.to, controller_program_version_s);

      controller_unlock_print_flush(main->output.to, 0);

      return F_none;
    }

    if (main->parameters.array[controller_parameter_copyright_e].result == f_console_result_found_e) {
      controller_print_copyright(main->output.to, main->output.verbosity > f_console_verbosity_error_e);

      return F_none;
    }

    status = F_none;

    f_string_static_t * const argv = main->parameters.arguments.array;

    controller_setting_t setting = controller_setting_t_initialize;

    setting.control.server.address = (struct sockaddr *) &setting.control.address;
    setting.control.server.domain = f_socket_domain_file_d;
    setting.control.server.type = f_socket_type_stream_d;
    setting.control.server.length = sizeof(struct sockaddr_un);

    memset(setting.control.server.address, 0, setting.control.server.length);

    if (main->parameters.remaining.used) {
      status = f_string_dynamic_append(argv[main->parameters.remaining.array[0]], &setting.name_entry);
    }
    else {
      status = f_string_dynamic_append(controller_default_s, &setting.name_entry);
    }

    if (F_status_is_error(status)) {
      fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);

      return status;
    }

    if (main->parameters.array[controller_parameter_init_e].result == f_console_result_found_e) {
      main->as_init = F_true;
    }

    if (main->as_init) {
      setting.mode = controller_setting_mode_service_e;
    }

    status = f_path_current(F_false, &setting.path_current);

    if (F_status_is_error(status)) {
      fll_error_print(main->error, F_status_set_fine(status), "f_path_current", F_true);
    }
    else {
      if (main->parameters.array[controller_parameter_settings_e].result == f_console_result_found_e) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          controller_lock_print(main->error.to, 0);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, controller_long_settings_s, main->context.set.notable);
          fl_print_format("%[' is specified, but no value is given.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          controller_unlock_print_flush(main->error.to, 0);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters.array[controller_parameter_settings_e].locations.used) {
        const f_array_length_t index = main->parameters.array[controller_parameter_settings_e].values.array[main->parameters.array[controller_parameter_settings_e].values.used - 1];

        status = controller_path_canonical_relative(&setting, argv[index], &setting.path_setting);

        if (F_status_is_error(status)) {
          fll_error_file_print(main->error, F_status_set_fine(status), "controller_path_canonical_relative", F_true, argv[index], f_file_operation_verify_s, fll_error_file_type_path_e);
        }
      }
      else {
        setting.path_setting.used = 0;

        if (main->as_init) {
          status = f_string_dynamic_append(*main->default_path_setting_init, &setting.path_setting);
        }
        else {
          status = f_string_dynamic_append(*main->default_path_setting, &setting.path_setting);
        }

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);
        }
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[controller_parameter_pid_e].result == f_console_result_found_e) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          controller_lock_print(main->error.to, 0);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, controller_long_pid_s, main->context.set.notable);
          fl_print_format("%[' is specified, but no value is given.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          controller_unlock_print_flush(main->error.to, 0);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters.array[controller_parameter_pid_e].locations.used) {
        setting.path_pid.used = 0;

        const f_array_length_t index = main->parameters.array[controller_parameter_pid_e].values.array[main->parameters.array[controller_parameter_pid_e].values.used - 1];

        if (argv[index].used) {
          status = controller_path_canonical_relative(&setting, argv[index], &setting.path_pid);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "controller_path_canonical_relative", F_true, argv[index], f_file_operation_verify_s, fll_error_file_type_path_e);
          }
        }
      }
    }

    if (F_status_is_error_not(status) && !setting.path_pid.used && !main->parameters.array[controller_parameter_pid_e].locations.used) {
      if (main->as_init) {
        status = f_string_dynamic_append(*main->default_path_pid_init, &setting.path_pid);
      }
      else {
        status = f_string_dynamic_append(*main->default_path_pid, &setting.path_pid);
      }

      if (F_status_is_error_not(status)) {
        status = f_string_dynamic_append(f_path_separator_s, &setting.path_pid);
      }

      if (F_status_is_error_not(status)) {
        status = f_string_dynamic_append(*main->default_path_pid_prefix, &setting.path_pid);
      }

      if (F_status_is_error_not(status)) {
        status = f_string_dynamic_append(setting.name_entry, &setting.path_pid);
      }

      if (F_status_is_error_not(status)) {
        status = f_string_dynamic_append(*main->default_path_pid_suffix, &setting.path_pid);
      }

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[controller_parameter_cgroup_e].result == f_console_result_found_e) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          controller_lock_print(main->error.to, 0);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, controller_long_cgroup_s, main->context.set.notable);
          fl_print_format("%[' is specified, but no value is given.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          controller_unlock_print_flush(main->error.to, 0);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters.array[controller_parameter_cgroup_e].locations.used) {
        const f_array_length_t index = main->parameters.array[controller_parameter_cgroup_e].values.array[main->parameters.array[controller_parameter_cgroup_e].values.used - 1];

        if (argv[index].used) {
          status = controller_path_canonical_relative(&setting, argv[index], &setting.path_cgroup);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "controller_path_canonical_relative", F_true, argv[index], f_file_operation_verify_s, fll_error_file_type_path_e);
          }
          else {
            status = f_string_append_assure(F_path_separator_s, 1, &setting.path_cgroup);

            if (F_status_is_error(status)) {
              fll_error_print(main->error, F_status_set_fine(status), "f_string_append_assure", F_true);
            }
          }
        }
        else {
          if (main->warning.verbosity == f_console_verbosity_debug_e) {
            controller_lock_print(main->warning.to, 0);

            fl_print_format("%r%[%QThe parameter '%]", main->warning.to.stream, f_string_eol_s, main->warning.context, main->warning.prefix, main->warning.context);
            fl_print_format("%[%r%r%]", main->warning.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, controller_long_cgroup_s, main->context.set.notable);
            fl_print_format("%[' must be a file directory path but instead is an empty string, falling back to the default.%]%r", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s);

            controller_unlock_print_flush(main->warning.to, 0);
          }
        }
      }
    }

    if (F_status_is_error_not(status) && main->parameters.array[controller_parameter_daemon_e].result == f_console_result_found_e) {
      if (main->parameters.array[controller_parameter_validate_e].result == f_console_result_found_e) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          controller_lock_print(main->error.to, 0);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[' must not be specified with the parameter '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, controller_long_daemon_s, main->context.set.notable);
          fl_print_format("%['.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          controller_unlock_print_flush(main->error.to, 0);
        }

        status = F_status_set_error(F_parameter);
      }
    }

    // Handle defaults dependent on the "as init" execution state.
    if (main->as_init) {
      setting.entry.pid = controller_entry_pid_disable_e;
      setting.entry.show = controller_entry_show_init_e;

      if (main->parameters.array[controller_parameter_interruptible_e].result == f_console_result_found_e) {
        setting.flag |= controller_setting_flag_interruptible_e;
      }
      else {
        setting.flag &= ~controller_setting_flag_interruptible_e;
      }
    }
    else {
      if (main->parameters.array[controller_parameter_uninterruptible_e].result == f_console_result_found_e) {
        setting.flag &= ~controller_setting_flag_interruptible_e;
      }
      else {
        setting.flag |= controller_setting_flag_interruptible_e;
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
      if (!setting.path_cgroup.used) {
        status = f_string_append_nulless(F_control_group_path_system_prefix_s, F_control_group_path_system_prefix_s_length, &setting.path_cgroup);

        if (F_status_is_error_not(status)) {
          status = f_string_append_nulless(F_control_group_path_system_default_s, F_control_group_path_system_default_s_length, &setting.path_cgroup);
        }

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "f_string_append_nulless", F_true);
        }
        else {
          status = f_string_append_assure(F_path_separator_s, 1, &setting.path_cgroup);

          if (F_status_is_error(status)) {
            fll_error_print(main->error, F_status_set_fine(status), "f_string_append_assure", F_true);
          }
        }
      }
    }

    if (F_status_is_error_not(status)) {
      status = controller_thread_main(main, &setting);
    }

    // Ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (F_status_is_error(status) && main->output.verbosity != f_console_verbosity_quiet_e) {
      if (F_status_set_fine(status) == F_interrupt) {
        fflush(main->output.to.stream);
      }

      fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
    }

    if (status != F_child && (setting.flag & controller_setting_flag_pid_created_e)) {
      const f_status_t status_delete = controller_file_pid_delete(main->pid, setting.path_pid);

      if (F_status_is_error(status_delete) && main->warning.verbosity == f_console_verbosity_debug_e) {
        if (F_status_set_fine(status_delete) == F_number_not) {
          controller_lock_print(main->warning.to, 0);

          fl_print_format("%r%[%QThe pid file '%]", main->warning.to.stream, f_string_eol_s, main->warning.context, main->warning.prefix, main->warning.context);
          fl_print_format("%[%Q%]", main->warning.to.stream, main->warning.notable, setting.path_pid, main->warning.notable);
          fl_print_format("%[' must not be specified with the parameter '%]", main->warning.to.stream, main->warning.context, main->warning.context);
          fl_print_format("%[%i%]", main->warning.to.stream, main->warning.notable, main->pid, main->warning.notable);
          fl_print_format("%[' doesn't contain the expected number, not deleting file.%]%r", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s);

          controller_unlock_print_flush(main->warning.to, 0);
        }
        else if (F_status_set_fine(status_delete) != F_interrupt) {
          fll_error_file_print(main->warning, F_status_set_fine(status_delete), "controller_file_pid_delete", F_true, setting.path_pid, f_file_operation_delete_s, fll_error_file_type_file_e);
        }
      }
    }

    if (status != F_child && setting.path_control.used) {
      f_socket_disconnect(&setting.control.server, f_socket_close_read_write_e);

      if (!(setting.control.flag & controller_control_flag_readonly_e)) {
        f_file_remove(setting.path_control);
      }
    }

    controller_setting_delete_simple(&setting);

    if (status == F_child) {
      return status;
    }

    return status;
  }
#endif // _di_controller_main_

#ifdef __cplusplus
} // extern "C"
#endif
