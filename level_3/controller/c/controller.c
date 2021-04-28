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

#ifndef _di_controller_print_help_
  f_status_t controller_print_help(const f_file_t output, const f_color_context_t context) {

    fll_program_print_help_header(output, context, controller_name_long, controller_version);

    fll_program_print_help_option(output, context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print this help message.");
    fll_program_print_help_option(output, context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Do not output in color.");
    fll_program_print_help_option(output, context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Set verbosity to normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Enable debugging, inceasing verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Print only the version number.");

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fll_program_print_help_option(output, context, controller_short_control, controller_long_control, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "      Specify a custom control group file path, such as '" f_control_group_path_system_prefix f_control_group_path_system_default "'.");
    fll_program_print_help_option(output, context, controller_short_daemon, controller_long_daemon, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "       Run in daemon only mode (do not process the entry).");
    fll_program_print_help_option(output, context, controller_short_interruptable, controller_long_interruptable, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Designate that this program can be interrupted.");
    fll_program_print_help_option(output, context, controller_short_pid, controller_long_pid, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "          Specify a custom pid file path, such as '" controller_path_pid controller_string_default controller_path_suffix "'.");
    fll_program_print_help_option(output, context, controller_short_settings, controller_long_settings, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Specify a custom settings path, such as '" controller_path_settings "'.");
    fll_program_print_help_option(output, context, controller_short_simulate, controller_long_simulate, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Run as a simulation.");
    fll_program_print_help_option(output, context, controller_short_validate, controller_long_validate, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Validate the settings (entry and rules) without running (does not simulate).");

    fll_program_print_help_usage(output, context, controller_name, "entry");

    fprintf(output.stream, "  When both the ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, controller_long_simulate);
    fprintf(output.stream, " parameter and the ");
    f_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable_s, controller_long_validate);
    fprintf(output.stream, " parameter are specified, then additional information on each would be executed rule is printed but no simulation is performed.");
    fprintf(output.stream, "%c", f_string_eol_s[0]);

    return F_none;
  }
#endif // _di_controller_print_help_

#ifndef _di_controller_main_
  f_status_t controller_main(const f_console_arguments_t arguments, controller_data_t *data) {
    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = f_macro_console_parameters_t_initialize(data->parameters, controller_total_parameters);

      {
        f_console_parameter_id_t ids[3] = { controller_parameter_no_color, controller_parameter_light, controller_parameter_dark };
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(arguments, parameters, choices, F_true, &data->remaining, &data->context);

        if (data->context.set.error.before) {
          data->error.context = data->context.set.error;
          data->error.notable = data->context.set.notable;

          data->warning.context = data->context.set.warning;
          data->warning.notable = data->context.set.notable;
        }
        else {
          data->context.set.warning = f_color_set_empty_s;
          data->context.set.error = f_color_set_empty_s;
          data->context.set.title = f_color_set_empty_s;
          data->context.set.notable = f_color_set_empty_s;
          data->context.set.important = f_color_set_empty_s;
          data->context.set.standout = f_color_set_empty_s;
          data->context.set.normal = f_color_set_empty_s;
          data->context.set.normal_reset = f_color_set_empty_s;

          data->error.context = f_color_set_empty_s;
          data->error.notable = f_color_set_empty_s;

          data->warning.context = f_color_set_empty_s;
          data->warning.notable = f_color_set_empty_s;
        }

        if (F_status_is_error(status)) {
          if (data->error.verbosity != f_console_verbosity_quiet) {
            fll_error_print(data->error, F_status_set_fine(status), "fll_program_parameter_process", F_true);
            fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
          }

          controller_data_delete(data);
          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { controller_parameter_verbosity_quiet, controller_parameter_verbosity_normal, controller_parameter_verbosity_verbose, controller_parameter_verbosity_debug };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = f_macro_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          controller_data_delete(data);
          return status;
        }

        if (choice == controller_parameter_verbosity_quiet) {
          data->error.verbosity = f_console_verbosity_quiet;
          data->warning.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == controller_parameter_verbosity_normal) {
          data->error.verbosity = f_console_verbosity_normal;
          data->warning.verbosity = f_console_verbosity_normal;
        }
        else if (choice == controller_parameter_verbosity_verbose) {
          data->error.verbosity = f_console_verbosity_verbose;
          data->warning.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == controller_parameter_verbosity_debug) {
          data->error.verbosity = f_console_verbosity_debug;
          data->warning.verbosity = f_console_verbosity_debug;
        }
      }

      status = F_none;
    }

    if (data->parameters[controller_parameter_help].result == f_console_result_found) {
      controller_print_help(data->output, data->context);

      controller_data_delete(data);
      return F_none;
    }

    if (data->parameters[controller_parameter_version].result == f_console_result_found) {
      fll_program_print_version(data->output, controller_version);

      controller_data_delete(data);
      return F_none;
    }

    controller_setting_t setting = controller_setting_t_initialize;

    if (data->remaining.used) {
      status = f_string_append_nulless(arguments.argv[data->remaining.array[0]], strnlen(arguments.argv[data->remaining.array[0]], f_console_parameter_size), &setting.name_entry);
    }
    else {
      status = f_string_append_nulless(controller_string_default_s, controller_string_default_length, &setting.name_entry);
    }

    if (F_status_is_error(status)) {
      fll_error_print(data->error, F_status_set_fine(status), "f_string_append_nulless", F_true);

      controller_data_delete(data);
      return status;
    }

    status = f_string_dynamic_terminate_after(&setting.name_entry);

    if (F_status_is_error(status)) {
      fll_error_print(data->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);

      controller_data_delete(data);
      return status;
    }

    if (data->parameters[controller_parameter_settings].result == f_console_result_found) {
      if (data->error.verbosity != f_console_verbosity_quiet) {
        fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
        fprintf(data->error.to.stream, "%s%sThe parameter '", data->error.context.before->string, data->error.prefix ? data->error.prefix : f_string_empty_s);
        fprintf(data->error.to.stream, "%s%s%s%s%s", data->error.context.after->string, data->error.notable.before->string, f_console_symbol_long_enable_s, controller_long_settings, data->error.notable.after->string);
        fprintf(data->error.to.stream, "%s' was specified, but no value was given.%s%c", data->error.context.before->string, data->error.context.after->string, f_string_eol_s[0]);
      }

      status = F_status_set_error(F_parameter);
    }
    else if (data->parameters[controller_parameter_settings].locations.used) {
      const f_array_length_t location = data->parameters[controller_parameter_settings].values.array[data->parameters[controller_parameter_settings].values.used - 1];

      status = fll_path_canonical(arguments.argv[location], &setting.path_setting);

      if (F_status_is_error(status)) {
        if (data->error.verbosity != f_console_verbosity_quiet) {
          fll_error_print(data->error, F_status_set_fine(status), "fll_path_canonical", F_true);
        }
      }
    }
    else {
      status = f_string_append(controller_path_settings, controller_path_settings_length, &setting.path_setting);

      if (F_status_is_error(status)) {
        if (data->error.verbosity != f_console_verbosity_quiet) {
          fll_error_print(data->error, F_status_set_fine(status), "f_string_append", F_true);
        }
      }
    }

    if (data->parameters[controller_parameter_pid].result == f_console_result_found) {
      if (data->error.verbosity != f_console_verbosity_quiet) {
        fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
        fprintf(data->error.to.stream, "%s%sThe parameter '", data->error.context.before->string, data->error.prefix ? data->error.prefix : f_string_empty_s);
        fprintf(data->error.to.stream, "%s%s%s%s%s", data->error.context.after->string, data->error.notable.before->string, f_console_symbol_long_enable_s, controller_long_pid, data->error.notable.after->string);
        fprintf(data->error.to.stream, "%s' was specified, but no value was given.%s%c", data->error.context.before->string, data->error.context.after->string, f_string_eol_s[0]);
      }

      status = F_status_set_error(F_parameter);
    }
    else if (data->parameters[controller_parameter_pid].locations.used) {
      const f_array_length_t location = data->parameters[controller_parameter_pid].values.array[data->parameters[controller_parameter_pid].values.used - 1];

      if (strnlen(arguments.argv[location], f_console_parameter_size)) {
        status = fll_path_canonical(arguments.argv[location], &setting.path_pid);

        if (F_status_is_error(status)) {
          if (data->error.verbosity != f_console_verbosity_quiet) {
            fll_error_print(data->error, F_status_set_fine(status), "fll_path_canonical", F_true);
          }
        }
      }
      else {
        if (data->warning.verbosity == f_console_verbosity_debug) {
          fprintf(data->warning.to.stream, "%c", f_string_eol_s[0]);
          fprintf(data->warning.to.stream, "%s%sThe parameter '", data->warning.context.before->string, data->warning.prefix ? data->warning.prefix : f_string_empty_s);
          fprintf(data->warning.to.stream, "%s%s%s%s%s", data->warning.context.after->string, data->warning.notable.before->string, f_console_symbol_long_enable_s, controller_long_pid, data->warning.notable.after->string);
          fprintf(data->warning.to.stream, "%s' must be a file path but instead is an empty string, falling back to the default.%s%c", data->warning.context.before->string, data->warning.context.after->string, f_string_eol_s[0]);
        }
      }
    }

    // a pid file path is required.
    if (!setting.path_pid.used) {
      status = f_string_append(controller_path_pid, controller_path_pid_length, &setting.path_pid);

      if (F_status_is_error_not(status)) {
        status = f_string_append(setting.name_entry.string, setting.name_entry.used, &setting.path_pid);
      }

      if (F_status_is_error_not(status)) {
        status = f_string_append(controller_path_suffix, controller_path_suffix_length, &setting.path_pid);
      }

      if (F_status_is_error(status)) {
        if (data->error.verbosity != f_console_verbosity_quiet) {
          fll_error_print(data->error, F_status_set_fine(status), "f_string_append", F_true);
        }
      }
    }

    if (data->parameters[controller_parameter_control].result == f_console_result_found) {
      if (data->error.verbosity != f_console_verbosity_quiet) {
        fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
        fprintf(data->error.to.stream, "%s%sThe parameter '", data->error.context.before->string, data->error.prefix ? data->error.prefix : f_string_empty_s);
        fprintf(data->error.to.stream, "%s%s%s%s%s", data->error.context.after->string, data->error.notable.before->string, f_console_symbol_long_enable_s, controller_long_control, data->error.notable.after->string);
        fprintf(data->error.to.stream, "%s' was specified, but no value was given.%s%c", data->error.context.before->string, data->error.context.after->string, f_string_eol_s[0]);
      }

      status = F_status_set_error(F_parameter);
    }
    else if (data->parameters[controller_parameter_control].locations.used) {
      const f_array_length_t location = data->parameters[controller_parameter_control].values.array[data->parameters[controller_parameter_control].values.used - 1];

      if (strnlen(arguments.argv[location], f_console_parameter_size)) {
        status = fll_path_canonical(arguments.argv[location], &setting.path_control);

        if (F_status_is_error(status)) {
          if (data->error.verbosity != f_console_verbosity_quiet) {
            fll_error_print(data->error, F_status_set_fine(status), "fll_path_canonical", F_true);
          }
        }
        else {
          status = f_string_append_assure(f_path_separator, 1, &setting.path_control);

          if (F_status_is_error(status)) {
            if (data->error.verbosity != f_console_verbosity_quiet) {
              fll_error_print(data->error, F_status_set_fine(status), "f_string_append_assure", F_true);
            }
          }
          else {
            status = f_string_dynamic_terminate_after(&setting.path_control);

            if (F_status_is_error(status)) {
              if (data->error.verbosity != f_console_verbosity_quiet) {
                fll_error_print(data->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
              }
            }
          }
        }
      }
      else {
        if (data->warning.verbosity == f_console_verbosity_debug) {
          fprintf(data->warning.to.stream, "%c", f_string_eol_s[0]);
          fprintf(data->warning.to.stream, "%s%sThe parameter '", data->warning.context.before->string, data->warning.prefix ? data->warning.prefix : f_string_empty_s);
          fprintf(data->warning.to.stream, "%s%s%s%s%s", data->warning.context.after->string, data->warning.notable.before->string, f_console_symbol_long_enable_s, controller_long_control, data->warning.notable.after->string);
          fprintf(data->warning.to.stream, "%s' must be a file directory path but instead is an empty string, falling back to the default.%s%c", data->warning.context.before->string, data->warning.context.after->string, f_string_eol_s[0]);
        }
      }
    }

    if (data->parameters[controller_parameter_daemon].result == f_console_result_found) {
      if (data->parameters[controller_parameter_validate].result == f_console_result_found) {
        if (data->error.verbosity != f_console_verbosity_quiet) {
          fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
          fprintf(data->error.to.stream, "%s%sThe parameter '", data->error.context.before->string, data->error.prefix ? data->error.prefix : f_string_empty_s);
          fprintf(data->error.to.stream, "%s%s%s%s%s", data->error.context.after->string, data->error.notable.before->string, f_console_symbol_long_enable_s, controller_long_validate, data->error.notable.after->string);
          fprintf(data->error.to.stream, "%s' must not be specified with the parameter '", data->error.context.before->string);
          fprintf(data->error.to.stream, "%s%s%s%s%s", data->error.context.after->string, data->error.notable.before->string, f_console_symbol_long_enable_s, controller_long_daemon, data->error.notable.after->string);
          fprintf(data->error.to.stream, "%s'.%s%c", data->error.context.before->string, data->error.context.after->string, f_string_eol_s[0]);
        }

        status = F_status_set_error(F_parameter);
      }
    }

    if (F_status_is_error_not(status)) {
      f_signal_set_fill(&data->signal.set);

      status = f_thread_signal_mask(SIG_BLOCK, &data->signal.set, 0);

      if (F_status_is_error_not(status)) {
        status = f_signal_open(&data->signal);
      }

      // if there is an error opening a signal descriptor, then do not handle signals.
      if (F_status_is_error(status)) {
        f_signal_mask(SIG_UNBLOCK, &data->signal.set, 0);
        f_signal_close(&data->signal);
      }

      // a control file path is required.
      if (!setting.path_control.used) {
        status = f_string_append_nulless(f_control_group_path_system_prefix, f_control_group_path_system_prefix_length, &setting.path_control);

        if (F_status_is_error_not(status)) {
          status = f_string_append_nulless(f_control_group_path_system_default, f_control_group_path_system_default_length, &setting.path_control);
        }

        if (F_status_is_error(status)) {
          if (data->error.verbosity != f_console_verbosity_quiet) {
            fll_error_print(data->error, F_status_set_fine(status), "f_string_append_nulless", F_true);
          }
        }
        else {
          status = f_string_append_assure(f_path_separator, 1, &setting.path_control);

          if (F_status_is_error(status)) {
            if (data->error.verbosity != f_console_verbosity_quiet) {
              fll_error_print(data->error, F_status_set_fine(status), "f_string_append_assure", F_true);
            }
          }
          else {
            status = f_string_dynamic_terminate_after(&setting.path_control);

            if (F_status_is_error(status)) {
              if (data->error.verbosity != f_console_verbosity_quiet) {
                fll_error_print(data->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
              }
            }
          }
        }
      }
    }

    if (F_status_is_error_not(status)) {
      status = controller_thread_main(data, &setting);
    }

    // ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (!(status == F_child || status == F_signal)) {
      if (F_status_is_error(status) && data->error.verbosity != f_console_verbosity_quiet) {
        fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
      }
    }

    f_signal_close(&data->signal);

    if (status != F_child && setting.pid_created) {
      f_status_t status_delete = controller_file_pid_delete(data->pid, setting.path_pid);

      if (F_status_is_error(status_delete) && data->warning.verbosity == f_console_verbosity_debug) {
        if (F_status_set_fine(status_delete) == F_number_not) {
          controller_error_pid_bad_match_print(data->warning, setting.path_pid.string, 0);
        }
        else {
          fll_error_file_print(data->warning, F_status_set_fine(status_delete), "controller_file_pid_delete", F_true, setting.path_pid.string, "delete", fll_error_file_type_file);
        }
      }
    }

    controller_setting_delete_simple(&setting);
    controller_data_delete(data);

    if (status == F_child || status == F_signal) {
      return status;
    }

    return status;
  }
#endif // _di_controller_main_

#ifndef _di_controller_data_delete_
  f_status_t controller_data_delete(controller_data_t *data) {

    for (f_array_length_t i = 0; i < controller_total_parameters; i++) {
      f_macro_array_lengths_t_delete_simple(data->parameters[i].locations);
      f_macro_array_lengths_t_delete_simple(data->parameters[i].locations_sub);
      f_macro_array_lengths_t_delete_simple(data->parameters[i].values);
    } // for

    f_macro_array_lengths_t_delete_simple(data->remaining);
    f_macro_color_context_t_delete_simple(data->context);

    return F_none;
  }
#endif // _di_controller_data_delete_

#ifdef __cplusplus
} // extern "C"
#endif
