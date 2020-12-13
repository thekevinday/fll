#include "controller.h"
#include "private-common.h"
#include "private-control.h"
#include "private-entry.h"
#include "private-rule.h"
#include "private-controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_print_help_
  f_return_status controller_print_help(const f_file_t output, const f_color_context_t context) {

    fll_program_print_help_header(output, context, controller_name_long, controller_version);

    fll_program_print_help_option(output, context, f_console_standard_short_help, f_console_standard_long_help, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print this help message.");
    fll_program_print_help_option(output, context, f_console_standard_short_dark, f_console_standard_long_dark, f_console_symbol_short_disable, f_console_symbol_long_disable, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_light, f_console_standard_long_light, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_no_color, f_console_standard_long_no_color, f_console_symbol_short_disable, f_console_symbol_long_disable, "Do not output in color.");
    fll_program_print_help_option(output, context, f_console_standard_short_quiet, f_console_standard_long_quiet, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Decrease verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_normal, f_console_standard_long_normal, f_console_symbol_short_disable, f_console_symbol_long_disable, "  Set verbosity to normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_verbose, f_console_standard_long_verbose, f_console_symbol_short_disable, f_console_symbol_long_disable, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_debug, f_console_standard_long_debug, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Enable debugging, inceasing verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_version, f_console_standard_long_version, f_console_symbol_short_disable, f_console_symbol_long_disable, " Print only the version number.");

    fprintf(output.stream, "%c", f_string_eol_s[0]);

    fll_program_print_help_option(output, context, controller_short_daemon, controller_long_daemon, f_console_symbol_short_enable, f_console_symbol_long_enable, "       Run in daemon only mode (do not process the entry).");
    fll_program_print_help_option(output, context, controller_short_interruptable, controller_long_interruptable, f_console_symbol_short_enable, f_console_symbol_long_enable, "Designate that this program can be interrupted.");
    fll_program_print_help_option(output, context, controller_short_pid, controller_long_pid, f_console_symbol_short_enable, f_console_symbol_long_enable, "          Specify a custom pid file path, such as '" controller_path_pid controller_string_default controller_path_suffix "'.");
    fll_program_print_help_option(output, context, controller_short_settings, controller_long_settings, f_console_symbol_short_enable, f_console_symbol_long_enable, "     Specify a custom settings path, such as '" controller_path_settings "'.");
    fll_program_print_help_option(output, context, controller_short_test, controller_long_test, f_console_symbol_short_enable, f_console_symbol_long_enable, "         Run in test mode, where nothing is actually run but is instead simulated.");
    fll_program_print_help_option(output, context, controller_short_validate, controller_long_validate, f_console_symbol_short_enable, f_console_symbol_long_enable, "     Validate the settings (entry and rules) without running (does not simulate).");

    fll_program_print_help_usage(output, context, controller_name, "entry");

    fprintf(output.stream, "  When both the ");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, controller_long_test);
    fprintf(output.stream, " operation and the ");
    fl_color_print(output.stream, context.set.notable, "%s%s", f_console_symbol_long_enable, controller_long_validate);
    fprintf(output.stream, " operation are specified, then additional information on each would be executed rule is printed.");
    fprintf(output.stream, "%c", f_string_eol[0]);

    return F_none;
  }
#endif // _di_controller_print_help_

#ifndef _di_controller_main_
  f_return_status controller_main(const f_console_arguments_t arguments, controller_data_t *data) {
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
          data->context.set.warning.before = &f_color_set_string_null_s;
          data->context.set.warning.after = &f_color_set_string_null_s;
          data->context.set.error.before = &f_color_set_string_null_s;
          data->context.set.error.after = &f_color_set_string_null_s;
          data->context.set.title.before = &f_color_set_string_null_s;
          data->context.set.title.after = &f_color_set_string_null_s;
          data->context.set.notable.before = &f_color_set_string_null_s;
          data->context.set.notable.after = &f_color_set_string_null_s;
          data->context.set.important.before = &f_color_set_string_null_s;
          data->context.set.important.after = &f_color_set_string_null_s;
          data->context.set.standout.before = &f_color_set_string_null_s;
          data->context.set.standout.after = &f_color_set_string_null_s;
          data->context.set.normal.before = &f_color_set_string_null_s;
          data->context.set.normal.after = &f_color_set_string_null_s;
          data->context.set.normal_reset.before = &f_color_set_string_null_s;
          data->context.set.normal_reset.after = &f_color_set_string_null_s;

          data->error.context.before = &f_color_set_string_null_s;
          data->error.context.after = &f_color_set_string_null_s;
          data->error.notable.before = &f_color_set_string_null_s;
          data->error.notable.after = &f_color_set_string_null_s;

          data->warning.context.before = &f_color_set_string_null_s;
          data->warning.context.after = &f_color_set_string_null_s;
          data->warning.notable.before = &f_color_set_string_null_s;
          data->warning.notable.after = &f_color_set_string_null_s;
        }

        if (F_status_is_error(status)) {
          if (data->error.verbosity != f_console_verbosity_quiet) {
            fll_error_print(data->error, F_status_set_fine(status), "fll_program_parameter_process", F_true);
            fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
          }

          controller_delete_data(data);
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
          controller_delete_data(data);
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

      controller_delete_data(data);
      return F_none;
    }

    if (data->parameters[controller_parameter_version].result == f_console_result_found) {
      fll_program_print_version(data->output, controller_version);

      controller_delete_data(data);
      return F_none;
    }

    controller_setting_t setting = controller_setting_t_initialize;
    controller_cache_t cache = controller_cache_t_initialize;

    f_string_static_t entry_name = f_string_static_t_initialize;

    if (data->remaining.used) {
      entry_name.string = arguments.argv[data->remaining.array[0]];
      entry_name.used = strnlen(entry_name.string, f_console_length_size);
      entry_name.size = entry_name.used;
    }
    else {
      entry_name.string = controller_string_default;
      entry_name.used = controller_string_default_length;
      entry_name.size = entry_name.used;
    }

    if (data->parameters[controller_parameter_settings].result == f_console_result_found) {
      if (data->error.verbosity != f_console_verbosity_quiet) {
        fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
        fprintf(data->error.to.stream, "%s%sThe parameter '", data->error.context.before->string, data->error.prefix ? data->error.prefix : f_string_empty_s);
        fprintf(data->error.to.stream, "%s%s%s%s", data->error.context.after->string, data->error.notable.before->string, f_console_symbol_long_enable, controller_long_settings, data->error.notable.after->string);
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
      status = fl_string_append(controller_path_settings, controller_path_settings_length, &setting.path_setting);

      if (F_status_is_error(status)) {
        if (data->error.verbosity != f_console_verbosity_quiet) {
          fll_error_print(data->error, F_status_set_fine(status), "fl_string_append", F_true);
        }
      }
    }

    if (data->parameters[controller_parameter_pid].result == f_console_result_found) {
      if (data->error.verbosity != f_console_verbosity_quiet) {
        fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
        fprintf(data->error.to.stream, "%s%sThe parameter '", data->error.context.before->string, data->error.prefix ? data->error.prefix : f_string_empty_s);
        fprintf(data->error.to.stream, "%s%s%s%s%s", data->error.context.after->string, data->error.notable.before->string, f_console_symbol_long_enable, controller_long_pid, data->error.notable.after->string);
        fprintf(data->error.to.stream, "%s' was specified, but no value was given.%s%c", data->error.context.before->string, data->error.context.after->string, f_string_eol_s[0]);
      }

      status = F_status_set_error(F_parameter);
    }
    else if (data->parameters[controller_parameter_pid].locations.used) {
      const f_array_length_t location = data->parameters[controller_parameter_pid].values.array[data->parameters[controller_parameter_pid].values.used - 1];

      if (strnlen(arguments.argv[location], f_console_length_size)) {
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
          fprintf(data->warning.to.stream, "%s%s%s%s%s", data->warning.context.after->string, data->warning.notable.before->string, f_console_symbol_long_enable, controller_long_pid, data->warning.notable.after->string);
          fprintf(data->warning.to.stream, "%s' must be a file path but instead is an empty string, falling back to the default.%s%c", data->warning.context.before->string, data->warning.context.after->string, f_string_eol_s[0]);
        }
      }
    }

    // a pid file path is required.
    if (!setting.path_pid.used) {
      status = fl_string_append(controller_path_pid, controller_path_pid_length, &setting.path_pid);

      if (F_status_is_error_not(status)) {
        status = fl_string_append(entry_name.string, entry_name.used, &setting.path_pid);
      }

      if (F_status_is_error_not(status)) {
        status = fl_string_append(controller_path_suffix, controller_path_suffix_length, &setting.path_pid);
      }

      if (F_status_is_error(status)) {
        if (data->error.verbosity != f_console_verbosity_quiet) {
          fll_error_print(data->error, F_status_set_fine(status), "fl_string_append", F_true);
        }
      }
    }

    if (data->parameters[controller_parameter_daemon].result == f_console_result_found) {

      if (data->parameters[controller_parameter_validate].result == f_console_result_found) {
        if (data->error.verbosity != f_console_verbosity_quiet) {
          fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
          fprintf(data->error.to.stream, "%s%sThe parameter '", data->error.context.before->string, data->error.prefix ? data->error.prefix : f_string_empty_s);
          fprintf(data->error.to.stream, "%s%s%s%s%s", data->error.context.after->string, data->error.notable.before->string, f_console_symbol_long_enable, controller_long_validate, data->error.notable.after->string);
          fprintf(data->error.to.stream, "%s' must not be specified with the parameter '", data->error.context.before->string);
          fprintf(data->error.to.stream, "%s%s%s%s%s", data->error.context.after->string, data->error.notable.before->string, f_console_symbol_long_enable, controller_long_daemon, data->error.notable.after->string);
          fprintf(data->error.to.stream, "%s'.%s%c", data->error.context.before->string, data->error.context.after->string, f_string_eol_s[0]);
        }

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status)) {
        setting.ready = controller_setting_ready_done;

        if (f_file_exists(setting.path_pid.string) == F_true) {
          if (data->error.verbosity != f_console_verbosity_quiet) {
            fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(data->error.to.stream, "%s%sThe pid file must not already exist.%s%c", data->error.context.before->string, data->error.prefix ? data->error.prefix : f_string_empty_s, data->error.context.after->string, f_string_eol_s[0]);
          }

          status = F_status_set_error(F_available_not);
          setting.ready = controller_setting_ready_abort;
        }

        // @todo wait here until told to quit, listening for "control" commands (and listening for signals).
        // @todo clear cache periodically while waiting.
        // controller_macro_cache_t_delete_simple(cache);
      }
    }
    else {

      if (F_status_is_error_not(status)) {
        status = controller_entry_read(*data, setting, entry_name, &cache, &setting.entry);
      }

      if (F_status_is_error(status)) {
        setting.ready = controller_setting_ready_fail;
      }
      else {
        status = controller_preprocess_entry(*data, &setting, &cache);

        if (data->parameters[controller_parameter_validate].result == f_console_result_none || data->parameters[controller_parameter_test].result == f_console_result_found) {

          if (f_file_exists(setting.path_pid.string) == F_true) {
            if (data->error.verbosity != f_console_verbosity_quiet) {
              fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
              fprintf(data->error.to.stream, "%s%sThe pid file must not already exist.%s%c", data->error.context.before->string, data->error.prefix ? data->error.prefix : f_string_empty_s, data->error.context.after->string, f_string_eol_s[0]);
            }

            status = F_status_set_error(F_available_not);
            setting.ready = controller_setting_ready_abort;
          }

          if (F_status_is_error_not(status)) {
            status = controller_process_entry(*data, &setting, &cache);
          }

          if (F_status_is_error(status)) {
            setting.ready = controller_setting_ready_fail;
          }
          else {
            setting.ready = controller_setting_ready_done;

            // @todo wait here until told to quit, listening for "control" commands (and listening for signals).
            // @todo clear cache periodically while waiting.
            // controller_macro_cache_t_delete_simple(cache);
          }
        }
      }
    }

    // ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (data->error.verbosity != f_console_verbosity_quiet) {
      if (F_status_is_error(status)) {
        fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
      }
    }

    controller_file_pid_delete(*data, setting.path_pid);

    controller_macro_setting_t_delete_simple(setting);
    controller_macro_cache_t_delete_simple(cache);

    controller_delete_data(data);

    if (setting.ready == controller_setting_ready_fail) {
      // @todo trigger failsafe/fallback execution, if defined.
    }

    return status;
  }
#endif // _di_controller_main_

#ifndef _di_controller_delete_data_
  f_return_status controller_delete_data(controller_data_t *data) {

    for (f_string_length_t i = 0; i < controller_total_parameters; i++) {
      f_macro_string_lengths_t_delete_simple(data->parameters[i].locations);
      f_macro_string_lengths_t_delete_simple(data->parameters[i].locations_sub);
      f_macro_string_lengths_t_delete_simple(data->parameters[i].values);
    } // for

    f_macro_string_lengths_t_delete_simple(data->remaining);
    f_macro_color_context_t_delete_simple(data->context);

    return F_none;
  }
#endif // _di_controller_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
