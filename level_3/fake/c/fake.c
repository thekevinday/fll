#include "fake.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-clean.h"
#include "private-make.h"
#include "private-print.h"
#include "private-skeleton.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_print_help_
  f_return_status fake_print_help(const fl_color_context_t context) {
    fll_program_print_help_header(context, fake_name_long, fake_version);

    fll_program_print_help_option(context, f_console_standard_short_help, f_console_standard_long_help, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print this help message.");
    fll_program_print_help_option(context, f_console_standard_short_light, f_console_standard_long_light, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(context, f_console_standard_short_dark, f_console_standard_long_dark, f_console_symbol_short_disable, f_console_symbol_long_disable, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(context, f_console_standard_short_no_color, f_console_standard_long_no_color, f_console_symbol_short_disable, f_console_symbol_long_disable, "Do not output in color.");
    fll_program_print_help_option(context, f_console_standard_short_quiet, f_console_standard_long_quiet, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Decrease verbosity beyond normal output.");
    fll_program_print_help_option(context, f_console_standard_short_verbose, f_console_standard_long_verbose, f_console_symbol_short_disable, f_console_symbol_long_disable, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(context, f_console_standard_short_version, f_console_standard_long_version, f_console_symbol_short_disable, f_console_symbol_long_disable, " Print only the version number.");

    printf("%c", f_string_eol[0]);

    fll_program_print_help_option(context, fake_short_define, fake_long_define, f_console_symbol_short_enable, f_console_symbol_long_enable, "  Override defines from settings file with this define.");
    fll_program_print_help_option(context, fake_short_fakefile, fake_long_fakefile, f_console_symbol_short_enable, f_console_symbol_long_enable, "Use this fakefile.");
    fll_program_print_help_option(context, fake_short_mode, fake_long_mode, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Use this mode when processing the build settings.");
    fll_program_print_help_option(context, fake_short_process, fake_long_process, f_console_symbol_short_enable, f_console_symbol_long_enable, " Process name for storing build states.");
    fll_program_print_help_option(context, fake_short_settings, fake_long_settings, f_console_symbol_short_enable, f_console_symbol_long_enable, "Use this settings file.");

    printf("%c", f_string_eol[0]);

    fll_program_print_help_option(context, fake_short_path_build, fake_long_path_build, f_console_symbol_short_enable, f_console_symbol_long_enable, "   Specify a custom build directory.");
    fll_program_print_help_option(context, fake_short_path_data, fake_long_path_data, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Specify a custom path to the data files.");
    fll_program_print_help_option(context, fake_short_path_sources, fake_long_path_sources, f_console_symbol_short_enable, f_console_symbol_long_enable, " Specify a custom path to the source files.");
    fll_program_print_help_option(context, fake_short_path_work, fake_long_path_work, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Use includes/libraries/programs from this directory instead of system.");

    printf("%c%c", f_string_eol[0], f_string_eol[0]);

    fl_color_print(f_type_output, context.important, context.reset, " Special Options: ");

    fll_program_print_help_option_long(context, fake_long_documents_disabled, f_console_symbol_long_enable, "   Forcibly do not build documents files.");
    fll_program_print_help_option_long(context, fake_long_documents_enabled, f_console_symbol_long_enable, "    Forcibly do build documents files.");
    fll_program_print_help_option_long(context, fake_long_shared_disabled, f_console_symbol_long_enable, "Forcibly do not build shared files.");
    fll_program_print_help_option_long(context, fake_long_shared_enabled, f_console_symbol_long_enable, " Forcibly do build shared files.");
    fll_program_print_help_option_long(context, fake_long_static_disabled, f_console_symbol_long_enable, "Forcibly do not build static files.");
    fll_program_print_help_option_long(context, fake_long_static_enabled, f_console_symbol_long_enable, " Forcibly do build static files.");

    printf("%c%c", f_string_eol[0], f_string_eol[0]);

    fl_color_print(f_type_output, context.important, context.reset, " Operations: ");

    fll_program_print_help_option_other(context, fake_other_operation_build, "   Build or compile the code based on build settings file.");
    fll_program_print_help_option_other(context, fake_other_operation_clean, "   Delete all build files.");
    fll_program_print_help_option_other(context, fake_other_operation_make, "    Build or compile the code based on fakefile.");
    fll_program_print_help_option_other(context, fake_other_operation_skeleton, "Build a skeleton directory structure.");

    fll_program_print_help_usage(context, fake_name, "operation");

    printf("  When performing the ");
    fl_color_print(f_type_output, context.notable, context.reset, "%s", fake_other_operation_build);
    printf(" operation, the ");
    fl_color_print(f_type_output, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, fake_long_mode);
    printf(" parameter specifies a name (limited to alpha-numeric, underscore, and dash) to be used in addition to the global.");
    printf("%c", f_string_eol[0]);

    printf("  For example, when a ");
    fl_color_print(f_type_output, context.notable, context.reset, "%s", fake_long_mode);
    printf(" of 'fll_monolithic' is specified, build libaries from both 'build_libraries' and 'build_libraries-fll_monolithic' are used (but not 'build_libraries-fll_level').");

    printf("%c%c", f_string_eol[0], f_string_eol[0]);

    printf("  When specifying the ");
    fl_color_print(f_type_output, context.notable, context.reset, "%s", fake_long_fakefile);
    printf(" or the ");
    fl_color_print(f_type_output, context.notable, context.reset, "%s", fake_long_settings);
    printf(" parameters, the filenames are relative to the data build directory, unless a path is used.");
    printf("%c", f_string_eol[0]);

    printf("  For example, with '");
    fl_color_print(f_type_output, context.notable, context.reset, "%s%s my_fakefile", f_console_symbol_long_enable, fake_long_fakefile);
    printf("' the fakefile at '");
    fl_color_print(f_type_output, context.notable, context.reset, "./%s%smy_fakefile", fake_default_path_data, fake_default_path_build);
    printf(" would be used, however with '");
    fl_color_print(f_type_output, context.notable, context.reset, "%s%s ./my_fakefile", f_console_symbol_long_enable, fake_long_fakefile);
    printf("' the fakefile at '");
    fl_color_print(f_type_output, context.notable, context.reset, "./my_fakefile", fake_default_path_data, fake_default_path_build);
    printf(" would be used.");

    printf("%c%c", f_string_eol[0], f_string_eol[0]);

    return F_none;
  }
#endif // _di_fake_print_help_

#ifndef _di_fake_main_
  f_return_status fake_main(const f_console_arguments_t arguments, fake_data_t *data) {
    f_status_t status = F_none;

    {
      f_console_parameters_t parameters = { data->parameters, fake_total_parameters };

      // Load all parameters and identify priority of color parameters.
      {
        f_console_parameter_id_t ids[3] = { fake_parameter_no_color, fake_parameter_light, fake_parameter_dark };
        f_console_parameter_ids_t choices = f_console_parameter_ids_t_initialize;

        choices.id = ids;
        choices.used = 3;

        status = fll_program_parameter_process(arguments, parameters, choices, F_true, &data->remaining, &data->context);

        if (F_status_is_error(status)) {
          fake_print_error(*data, F_status_set_fine(status), "fll_program_parameter_process", F_true);
          fake_delete_data(data);
          return status;
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[3] = { fake_parameter_quiet, fake_parameter_verbose, fake_parameter_debug };
        f_console_parameter_ids_t choices = f_console_parameter_ids_t_initialize;
        f_console_parameter_id_t choice = 0;

        choices.id = ids;
        choices.used = 3;

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          fake_print_error(*data, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);
          fake_delete_data(data);
          return status;
        }

        if (choice == fake_parameter_quiet) {
          data->verbosity = fake_verbosity_quiet;
        }
        else if (choice == fake_parameter_verbose) {
          data->verbosity = fake_verbosity_verbose;
        }
        else if (choice == fake_parameter_debug) {
          data->verbosity = fake_verbosity_debug;
        }
      }

      status = F_none;
    }

    f_array_length_t operations_length = data->parameters[fake_parameter_operation_build].locations.used;

    operations_length += data->parameters[fake_parameter_operation_clean].locations.used;
    operations_length += data->parameters[fake_parameter_operation_make].locations.used;
    operations_length += data->parameters[fake_parameter_operation_skeleton].locations.used;

    uint8_t operations[operations_length];
    f_string_t operations_name = 0;

    {
      f_array_length_t locations[operations_length];
      f_array_length_t locations_length = 0;
      f_string_length_t i = 0;
      f_string_length_t j = 0;
      f_string_length_t k = 0;

      for (; i < data->parameters[fake_parameter_operation_build].locations.used; i++, locations_length++) {
        operations[locations_length] = fake_operation_build;
        locations[locations_length] = data->parameters[fake_parameter_operation_build].locations.array[i];
      } // for

      for (i = 0; i < data->parameters[fake_parameter_operation_clean].locations.used; i++) {
        for (j = 0; j < locations_length; j++) {
          if (data->parameters[fake_parameter_operation_clean].locations.array[i] < locations[j]) {
            for (k = locations_length; k > j; k--) {
              locations[k] = locations[k - 1];
              operations[k] = operations[k - 1];
            } // for

            break;
          }
        } // for

        locations[j] = data->parameters[fake_parameter_operation_clean].locations.array[i];
        operations[j] = fake_operation_clean;
        locations_length++;
      } // for

      for (i = 0; i < data->parameters[fake_parameter_operation_make].locations.used; i++) {
        for (j = 0; j < locations_length; j++) {
          if (data->parameters[fake_parameter_operation_make].locations.array[i] < locations[j]) {
            for (k = locations_length; k > j; k--) {
              locations[k] = locations[k - 1];
              operations[k] = operations[k - 1];
            } // for

            break;
          }
        } // for

        locations[j] = data->parameters[fake_parameter_operation_make].locations.array[i];
        operations[j] = fake_operation_make;
        locations_length++;
      } // for

      for (i = 0; i < data->parameters[fake_parameter_operation_skeleton].locations.used; i++) {
        for (j = 0; j < locations_length; j++) {
          if (data->parameters[fake_parameter_operation_skeleton].locations.array[i] < locations[j]) {
            for (k = locations_length; k > j; k--) {
              locations[k] = locations[k - 1];
              operations[k] = operations[k - 1];
            } // for

            break;
          }
        } // for

        locations[j] = data->parameters[fake_parameter_operation_skeleton].locations.array[i];
        operations[j] = fake_operation_skeleton;
        locations_length++;
      } // for
    }

    status = F_none;

    if (data->parameters[fake_parameter_help].result == f_console_result_found) {
      fake_print_help(data->context);
    }
    else if (data->parameters[fake_parameter_version].result == f_console_result_found) {
      fll_program_print_version(fake_version);
    }
    else if (operations_length) {
      bool validate_parameter_directories = F_true;

      status = fake_process_console_parameters(arguments, data);

      if (F_status_is_error_not(status)) {
        status = fake_path_generate(data);
      }

      if (F_status_is_error(status)) {
        fake_delete_data(data);
        return F_status_set_error(status);
      }

      for (uint8_t i = 0; i < operations_length; i++) {
        data->operation = operations[i];

        if (data->operation == fake_operation_build) {
          operations_name = fake_other_operation_build;
        }
        else if (data->operation == fake_operation_clean) {
          operations_name = fake_other_operation_clean;
        }
        else if (data->operation == fake_operation_make) {
          operations_name = fake_other_operation_make;
        }
        else if (data->operation == fake_operation_skeleton) {
          operations_name = fake_other_operation_skeleton;
        }

        if (data->operation == fake_operation_build) {
          if (validate_parameter_directories) {
            status = fake_validate_parameter_directories(arguments, *data);
            validate_parameter_directories = F_false;
          }

          if (F_status_is_error_not(status) && status != F_signal) {
            f_string_static_t stub = f_string_static_t_initialize;

            status = fake_build_operate(*data, stub);
          }
        }
        else if (data->operation == fake_operation_clean) {
          if (validate_parameter_directories) {
            status = fake_validate_parameter_directories(arguments, *data);
            validate_parameter_directories = F_false;
          }

          if (F_status_is_error_not(status) && status != F_signal) {
            status = fake_clean_operate(*data);
          }
        }
        else if (data->operation == fake_operation_make) {
          if (validate_parameter_directories) {
            status = fake_validate_parameter_directories(arguments, *data);
            validate_parameter_directories = F_false;
          }

          if (F_status_is_error_not(status) && status != F_signal) {
            status = fake_make_operate(*data);
          }
        }
        else if (data->operation == fake_operation_skeleton) {
          status = fake_skeleton_operate(*data);
        }

        if (status == F_signal || fake_signal_received(*data)) {
          break;
        }
        else if (F_status_is_error(status)) {
          if (data->verbosity != fake_verbosity_quiet) {
            fprintf(f_type_error, "%c", f_string_eol[0]);
            fl_color_print(f_type_error, data->context.error, data->context.reset, "ERROR: The operation '");
            fl_color_print(f_type_error, data->context.notable, data->context.reset, "%s", operations_name);
            fl_color_print_line(f_type_error, data->context.error, data->context.reset, "' failed.");
          }

          break;
        }
      } // for

      // ensure a newline is always put at the end of the program execution, unless in quite mode.
      if (data->verbosity != fake_verbosity_quiet) {
        if (F_status_is_error(status) || status == F_signal) {
          fprintf(f_type_error, "%c", f_string_eol[0]);
        }
        else {
          fprintf(f_type_output, "%cAll operations complete.%c%c", f_string_eol[0], f_string_eol[0], f_string_eol[0]);
        }
      }
    }
    else {
      if (data->verbosity != fake_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print_line(f_type_error, data->context.error, data->context.reset, "ERROR: You failed to specify an operation.");
        fprintf(f_type_error, "%c", f_string_eol[0]);
      }

      status = F_status_set_error(F_parameter);
    }

    fake_delete_data(data);
    return status;
  }
#endif // _di_fake_main_

#ifndef _di_fake_delete_data_
  f_return_status fake_delete_data(fake_data_t *data) {

    for (f_string_length_t i = 0; i < fake_total_parameters; i++) {
      f_macro_string_lengths_t_delete_simple(data->parameters[i].locations);
      f_macro_string_lengths_t_delete_simple(data->parameters[i].additional);
    } // for

    f_macro_string_lengths_t_delete_simple(data->remaining);

    f_macro_string_dynamics_t_delete_simple(data->define);
    f_macro_string_dynamic_t_delete_simple(data->fakefile);
    f_macro_string_dynamics_t_delete_simple(data->mode);
    f_macro_string_dynamic_t_delete_simple(data->process);
    f_macro_string_dynamic_t_delete_simple(data->settings);

    f_macro_string_dynamic_t_delete_simple(data->path_build);
    f_macro_string_dynamic_t_delete_simple(data->path_build_documents);
    f_macro_string_dynamic_t_delete_simple(data->path_build_includes);
    f_macro_string_dynamic_t_delete_simple(data->path_build_libraries);
    f_macro_string_dynamic_t_delete_simple(data->path_build_libraries_script);
    f_macro_string_dynamic_t_delete_simple(data->path_build_libraries_shared);
    f_macro_string_dynamic_t_delete_simple(data->path_build_libraries_static);
    f_macro_string_dynamic_t_delete_simple(data->path_build_objects);
    f_macro_string_dynamic_t_delete_simple(data->path_build_programs);
    f_macro_string_dynamic_t_delete_simple(data->path_build_programs_script);
    f_macro_string_dynamic_t_delete_simple(data->path_build_programs_shared);
    f_macro_string_dynamic_t_delete_simple(data->path_build_programs_static);
    f_macro_string_dynamic_t_delete_simple(data->path_build_settings);
    f_macro_string_dynamic_t_delete_simple(data->path_build_stage);
    f_macro_string_dynamic_t_delete_simple(data->path_work);

    f_macro_string_dynamic_t_delete_simple(data->path_data);
    f_macro_string_dynamic_t_delete_simple(data->path_data_build);

    f_macro_string_dynamic_t_delete_simple(data->path_data_settings);

    f_macro_string_dynamic_t_delete_simple(data->path_documents);

    f_macro_string_dynamic_t_delete_simple(data->path_licenses);

    f_macro_string_dynamic_t_delete_simple(data->path_sources);
    f_macro_string_dynamic_t_delete_simple(data->path_sources_bash);
    f_macro_string_dynamic_t_delete_simple(data->path_sources_c);
    f_macro_string_dynamic_t_delete_simple(data->path_sources_cpp);
    f_macro_string_dynamic_t_delete_simple(data->path_sources_script);

    f_macro_string_dynamic_t_delete_simple(data->path_work);
    f_macro_string_dynamic_t_delete_simple(data->path_work_includes);
    f_macro_string_dynamic_t_delete_simple(data->path_work_libraries);
    f_macro_string_dynamic_t_delete_simple(data->path_work_libraries_script);
    f_macro_string_dynamic_t_delete_simple(data->path_work_libraries_shared);
    f_macro_string_dynamic_t_delete_simple(data->path_work_libraries_static);
    f_macro_string_dynamic_t_delete_simple(data->path_work_programs);
    f_macro_string_dynamic_t_delete_simple(data->path_work_programs_script);
    f_macro_string_dynamic_t_delete_simple(data->path_work_programs_shared);
    f_macro_string_dynamic_t_delete_simple(data->path_work_programs_static);

    f_macro_string_dynamic_t_delete_simple(data->file_data_build_defines);
    f_macro_string_dynamic_t_delete_simple(data->file_data_build_dependencies);
    f_macro_string_dynamic_t_delete_simple(data->file_data_build_fakefile);
    f_macro_string_dynamic_t_delete_simple(data->file_data_build_settings);

    f_macro_string_dynamic_t_delete_simple(data->file_documents_readme);

    fl_macro_color_context_t_delete_simple(data->context);

    return F_none;
  }
#endif // _di_fake_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
