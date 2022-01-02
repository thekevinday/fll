#include "controller.h"
#include "private-common.h"
#include "private-control.h"
#include "private-controller.h"
#include "private-controller_print.h"
#include "private-entry.h"
#include "private-lock_print.h"
#include "private-rule.h"
#include "private-thread.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_help_
  f_status_t controller_print_help(controller_main_t * const main) {

    controller_lock_print(main->output.to, 0);

    fll_program_print_help_header(main->output.to, main->context, main->program_name_long, controller_program_version_s);

    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print this help message.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Do not main->output.to in color.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity beyond normal main->output.to.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Set verbosity to normal main->output.to.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Increase verbosity beyond normal main->output.to.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Enable debugging, inceasing verbosity beyond normal main->output.to.");
    fll_program_print_help_option(main->output.to, main->context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Print only the version number.");

    f_print_character(f_string_eol_s[0], main->output.to.stream);

    fll_program_print_help_option(main->output.to, main->context, controller_short_cgroup_s, controller_long_cgroup_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "         Specify a custom control group file path, such as '" F_control_group_path_system_prefix_s F_control_group_path_system_default_s "'.");
    fll_program_print_help_option(main->output.to, main->context, controller_short_daemon_s, controller_long_daemon_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "         Run in daemon only mode (do not process the entry).");
    fll_program_print_help_option(main->output.to, main->context, controller_short_init_s, controller_long_init_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "           The program will run as an init replacement.");
    fll_program_print_help_option(main->output.to, main->context, controller_short_interruptible_s, controller_long_interruptible_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Designate that this program can be interrupted by a signal.");
    fll_program_print_help_option(main->output.to, main->context, controller_short_pid_s, controller_long_pid_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "            Specify a custom pid file path, such as '" controller_path_pid_s CONTROLLER_default_s controller_path_suffix_s "'.");
    fll_program_print_help_option(main->output.to, main->context, controller_short_settings_s, controller_long_settings_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "       Specify a custom settings path, such as '" controller_path_settings_s "'.");
    fll_program_print_help_option(main->output.to, main->context, controller_short_simulate_s, controller_long_simulate_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "       Run as a simulation.");
    fll_program_print_help_option(main->output.to, main->context, controller_short_uninterruptible_s, controller_long_uninterruptible_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Designate that this program cannot be interrupted by a signal.");
    fll_program_print_help_option(main->output.to, main->context, controller_short_validate_s, controller_long_validate_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "       Validate the settings (entry and rules) without running (does not simulate).");

    fll_program_print_help_usage(main->output.to, main->context, main->program_name, "entry");

    fl_print_format("  When both the %[%s%s%] parameter and the", main->output.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, controller_long_simulate_s, main->context.set.notable);
    fl_print_format(" %[%s%s%] parameter are specified, then additional information on each would be executed rule is printed but no simulation is performed.%c%c", main->output.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, controller_long_validate_s, main->context.set.notable, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format(" The default interrupt behavior is to operate as if the %[%s%s%] parameter is passed.%c%c", main->output.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, main->setting_default.used ? controller_long_uninterruptible_s : controller_long_interruptible_s, main->context.set.notable, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format(" Specify an empty string for the %[%s%s%] parameter to disable pid file creation for this program.%c%c", main->output.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, controller_long_pid_s, main->context.set.notable, f_string_eol_s[0], f_string_eol_s[0]);

    controller_unlock_print_flush(main->output.to, 0);

    return F_none;
  }
#endif // _di_controller_print_help_

#ifndef _di_controller_main_
  f_status_t controller_main(controller_main_t * const main, const f_console_arguments_t *arguments) {

    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(main->parameters, controller_total_parameters_d);

      {
        f_console_parameter_id_t ids[3] = { controller_parameter_no_color_e, controller_parameter_light_e, controller_parameter_dark_e };
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(*arguments, parameters, choices, F_true, &main->remaining, &main->context);

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
            fll_print_terminated(f_string_eol_s, main->error.to.stream);
          }

          controller_main_delete(main);

          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { controller_parameter_verbosity_quiet_e, controller_parameter_verbosity_normal_e, controller_parameter_verbosity_verbose_e, controller_parameter_verbosity_debug_e };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          controller_main_delete(main);

          return status;
        }

        if (choice == controller_parameter_verbosity_quiet_e) {
          main->output.verbosity = f_console_verbosity_quiet_e;
          main->error.verbosity = f_console_verbosity_quiet_e;
          main->warning.verbosity = f_console_verbosity_quiet_e;
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

      status = F_none;
    }

    if (main->parameters[controller_parameter_help_e].result == f_console_result_found_e) {
      controller_print_help(main);

      controller_main_delete(main);

      return F_none;
    }

    if (main->parameters[controller_parameter_version_e].result == f_console_result_found_e) {
      controller_lock_print(main->output.to, 0);

      fll_program_print_version(main->output.to, controller_program_version_s);

      controller_unlock_print_flush(main->output.to, 0);

      controller_main_delete(main);

      return F_none;
    }

    controller_setting_t setting = controller_setting_t_initialize;

    struct sockaddr_un address;
    setting.control_socket.address = (struct sockaddr *) &address;
    setting.control_socket.domain = f_socket_domain_file_d;
    setting.control_socket.type = f_socket_type_stream_d;
    setting.control_socket.length = sizeof(struct sockaddr_un);

    memset(&address, 0, setting.control_socket.length);

    if (main->remaining.used) {
      status = f_string_append_nulless(arguments->argv[main->remaining.array[0]], strnlen(arguments->argv[main->remaining.array[0]], f_console_parameter_size), &setting.name_entry);
    }
    else {
      status = f_string_append_nulless(controller_default_s, controller_default_s_length, &setting.name_entry);
    }

    if (F_status_is_error(status)) {
      fll_error_print(main->error, F_status_set_fine(status), "f_string_append_nulless", F_true);

      controller_main_delete(main);

      return status;
    }

    status = f_string_dynamic_terminate_after(&setting.name_entry);

    if (F_status_is_error(status)) {
      fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);

      controller_main_delete(main);

      return status;
    }

    if (main->parameters[controller_parameter_init_e].result == f_console_result_found_e) {
      main->as_init = F_true;
    }

    if (main->as_init) {
      setting.mode = controller_setting_mode_service_e;
    }

    if (main->parameters[controller_parameter_settings_e].result == f_console_result_found_e) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        controller_lock_print(main->error.to, 0);

        fl_print_format("%c%[%SThe parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix ? main->error.prefix : f_string_empty_s, main->error.context);
        fl_print_format("%[%s%s%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, controller_long_settings_s, main->context.set.notable);
        fl_print_format("%[' is specified, but no value is given.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

        controller_unlock_print_flush(main->error.to, 0);
      }

      status = F_status_set_error(F_parameter);
    }
    else if (main->parameters[controller_parameter_settings_e].locations.used) {
      const f_array_length_t location = main->parameters[controller_parameter_settings_e].values.array[main->parameters[controller_parameter_settings_e].values.used - 1];

      status = fll_path_canonical(arguments->argv[location], &setting.path_setting);

      if (F_status_is_error(status)) {
        fll_error_file_print(main->error, F_status_set_fine(status), "fll_path_canonical", F_true, arguments->argv[location], "verify", fll_error_file_type_path_e);
      }
    }
    else {
      if (main->parameters[controller_parameter_init_e].result == f_console_result_found_e && !main->as_init) {
        status = f_string_append(controller_path_settings_init_s, controller_path_settings_init_s_length, &setting.path_setting);
      }
      else if (main->setting_default.used) {
        status = f_string_append(main->setting_default.string, main->setting_default.used, &setting.path_setting);
      }
      else {
        status = f_string_append(controller_path_settings_s, controller_path_settings_s_length, &setting.path_setting);
      }

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_string_append", F_true);
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters[controller_parameter_pid_e].result == f_console_result_found_e) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          controller_lock_print(main->error.to, 0);

          fl_print_format("%c%[%SThe parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix ? main->error.prefix : f_string_empty_s, main->error.context);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, controller_long_pid_s, main->context.set.notable);
          fl_print_format("%[' is specified, but no value is given.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

          controller_unlock_print_flush(main->error.to, 0);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters[controller_parameter_pid_e].locations.used) {
        const f_array_length_t location = main->parameters[controller_parameter_pid_e].values.array[main->parameters[controller_parameter_pid_e].values.used - 1];

        if (strnlen(arguments->argv[location], f_console_parameter_size)) {
          status = fll_path_canonical(arguments->argv[location], &setting.path_pid);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "fll_path_canonical", F_true, arguments->argv[location], "verify", fll_error_file_type_path_e);
          }
        }
        else {
          setting.path_pid.used = 0;
        }
      }
    }

    if (F_status_is_error_not(status) && !setting.path_pid.used && !main->parameters[controller_parameter_pid_e].locations.used) {
      if (main->parameters[controller_parameter_init_e].result == f_console_result_found_e) {
        status = f_string_append(controller_path_pid_init_s, controller_path_pid_init_s_length, &setting.path_pid);
      }
      else {
        status = f_string_append(main->path_pid.string, main->path_pid.used, &setting.path_pid);
      }

      if (F_status_is_error_not(status)) {
        status = f_string_append(setting.name_entry.string, setting.name_entry.used, &setting.path_pid);
      }

      if (F_status_is_error_not(status)) {
        status = f_string_append(controller_path_suffix_s, controller_path_suffix_s_length, &setting.path_pid);
      }

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_string_append", F_true);
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters[controller_parameter_cgroup_e].result == f_console_result_found_e) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          controller_lock_print(main->error.to, 0);

          fl_print_format("%c%[%SThe parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix ? main->error.prefix : f_string_empty_s, main->error.context);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, controller_long_cgroup_s, main->context.set.notable);
          fl_print_format("%[' is specified, but no value is given.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

          controller_unlock_print_flush(main->error.to, 0);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters[controller_parameter_cgroup_e].locations.used) {
        const f_array_length_t location = main->parameters[controller_parameter_cgroup_e].values.array[main->parameters[controller_parameter_cgroup_e].values.used - 1];

        if (strnlen(arguments->argv[location], f_console_parameter_size)) {
          status = fll_path_canonical(arguments->argv[location], &setting.path_cgroup);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "fll_path_canonical", F_true, arguments->argv[location], "verify", fll_error_file_type_path_e);
          }
          else {
            status = f_string_append_assure(F_path_separator_s, 1, &setting.path_cgroup);

            if (F_status_is_error(status)) {
              fll_error_print(main->error, F_status_set_fine(status), "f_string_append_assure", F_true);
            }
            else {
              status = f_string_dynamic_terminate_after(&setting.path_cgroup);

              if (F_status_is_error(status)) {
                fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
              }
            }
          }
        }
        else {
          if (main->warning.verbosity == f_console_verbosity_debug_e) {
            controller_lock_print(main->warning.to, 0);

            fl_print_format("%c%[%SThe parameter '%]", main->warning.to.stream, f_string_eol_s[0], main->warning.context, main->warning.prefix ? main->warning.prefix : f_string_empty_s, main->warning.context);
            fl_print_format("%[%s%s%]", main->warning.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, controller_long_cgroup_s, main->context.set.notable);
            fl_print_format("%[' must be a file directory path but instead is an empty string, falling back to the default.%]%c", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s[0]);

            controller_unlock_print_flush(main->warning.to, 0);
          }
        }
      }
    }

    if (F_status_is_error_not(status) && main->parameters[controller_parameter_daemon_e].result == f_console_result_found_e) {
      if (main->parameters[controller_parameter_validate_e].result == f_console_result_found_e) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          controller_lock_print(main->error.to, 0);

          fl_print_format("%c%[%SThe parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix ? main->error.prefix : f_string_empty_s, main->error.context);
          fl_print_format("%[' must not be specified with the parameter '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->context.set.notable, f_console_symbol_long_enable_s, controller_long_daemon_s, main->context.set.notable);
          fl_print_format("%['.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

          controller_unlock_print_flush(main->error.to, 0);
        }

        status = F_status_set_error(F_parameter);
      }
    }

    // Handle defaults dependent on the "as init" execution state.
    if (main->as_init) {
      setting.entry.pid = controller_entry_pid_disable_e;
      setting.entry.show = controller_entry_show_init_e;

      if (main->parameters[controller_parameter_interruptible_e].result == f_console_result_found_e) {
        setting.interruptible = F_true;
      }
      else {
        setting.interruptible = F_false;
      }
    }
    else {
      if (main->parameters[controller_parameter_uninterruptible_e].result == f_console_result_found_e) {
        setting.interruptible = F_false;
      }
      else {
        setting.interruptible = F_true;
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
          else {
            status = f_string_dynamic_terminate_after(&setting.path_cgroup);

            if (F_status_is_error(status)) {
              fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
            }
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

      fll_print_terminated(f_string_eol_s, main->output.to.stream);
    }

    if (status != F_child && setting.pid_created) {
      const f_status_t status_delete = controller_file_pid_delete(main->pid, setting.path_pid);

      if (F_status_is_error(status_delete) && main->warning.verbosity == f_console_verbosity_debug_e) {
        if (F_status_set_fine(status_delete) == F_number_not) {
          controller_lock_print(main->warning.to, 0);

          fl_print_format("%c%[%SThe pid file '%]", main->warning.to.stream, f_string_eol_s[0], main->warning.context, main->warning.prefix ? main->warning.prefix : f_string_empty_s, main->warning.context);
          fl_print_format("%[%Q%]", main->warning.to.stream, main->warning.notable, setting.path_pid, main->warning.notable);
          fl_print_format("%[' must not be specified with the parameter '%]", main->warning.to.stream, main->warning.context, main->warning.context);
          fl_print_format("%[%i%]", main->warning.to.stream, main->warning.notable, main->pid, main->warning.notable);
          fl_print_format("%[' doesn't contain the expected number, not deleting file.%]%c", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s[0]);

          controller_unlock_print_flush(main->warning.to, 0);
        }
        else if (F_status_set_fine(status_delete) != F_interrupt) {
          fll_error_file_print(main->warning, F_status_set_fine(status_delete), "controller_file_pid_delete", F_true, setting.path_pid.string, "delete", fll_error_file_type_file_e);
        }
      }
    }

    if (status != F_child && setting.path_control.used) {
      f_socket_disconnect(&setting.control_socket, f_socket_close_read_write_e);

      if (!setting.control_readonly) {
        f_file_remove(setting.path_control.string);
      }
    }

    controller_setting_delete_simple(&setting);
    controller_main_delete(main);

    if (status == F_child) {
      return status;
    }

    return status;
  }
#endif // _di_controller_main_

#ifndef _di_controller_main_delete_
  f_status_t controller_main_delete(controller_main_t * const main) {

    for (f_array_length_t i = 0; i < controller_total_parameters_d; ++i) {

      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations_sub);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].values);
    } // for

    macro_f_array_lengths_t_delete_simple(main->remaining);
    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_controller_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif
