#include "fake.h"
#include "private-common.h"
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
  f_status_t fake_print_help(const f_file_t output, const f_color_context_t context) {

    flockfile(output.stream);

    fll_program_print_help_header(output, context, fake_name_long, fake_version);

    fll_program_print_help_option(output, context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print this help message.");
    fll_program_print_help_option(output, context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(output, context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Do not output in color.");
    fll_program_print_help_option(output, context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Set verbosity to normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Enable debugging, inceasing verbosity beyond normal output.");
    fll_program_print_help_option(output, context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Print only the version number.");

    f_print_character(f_string_eol_s[0], output.stream);

    fll_program_print_help_option(output, context, fake_short_define, fake_long_define, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Append an additional define after defines from settings file.");
    fll_program_print_help_option(output, context, fake_short_fakefile, fake_long_fakefile, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Use this fakefile.");
    fll_program_print_help_option(output, context, fake_short_mode, fake_long_mode, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Use this mode when processing the build settings.");
    fll_program_print_help_option(output, context, fake_short_process, fake_long_process, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Process name for storing build states.");
    fll_program_print_help_option(output, context, fake_short_settings, fake_long_settings, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Use this settings file.");

    f_print_character(f_string_eol_s[0], output.stream);

    fll_program_print_help_option(output, context, fake_short_path_build, fake_long_path_build, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Specify a custom build directory.");
    fll_program_print_help_option(output, context, fake_short_path_data, fake_long_path_data, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Specify a custom path to the data files.");
    fll_program_print_help_option(output, context, fake_short_path_sources, fake_long_path_sources, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Specify a custom path to the source files.");
    fll_program_print_help_option(output, context, fake_short_path_work, fake_long_path_work, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Use includes/libraries/programs from this directory instead of system.");

    fl_print_format("%c%c %[Special Options:%] ", output.stream, f_string_eol_s[0], f_string_eol_s[0], context.set.important, context.set.important);

    fll_program_print_help_option_long(output, context, fake_long_documents_disabled, f_console_symbol_long_enable_s, "   Forcibly do not build documents files.");
    fll_program_print_help_option_long(output, context, fake_long_documents_enabled, f_console_symbol_long_enable_s, "    Forcibly do build documents files.");
    fll_program_print_help_option_long(output, context, fake_long_shared_disabled, f_console_symbol_long_enable_s, "Forcibly do not build shared files.");
    fll_program_print_help_option_long(output, context, fake_long_shared_enabled, f_console_symbol_long_enable_s, " Forcibly do build shared files.");
    fll_program_print_help_option_long(output, context, fake_long_static_disabled, f_console_symbol_long_enable_s, "Forcibly do not build static files.");
    fll_program_print_help_option_long(output, context, fake_long_static_enabled, f_console_symbol_long_enable_s, " Forcibly do build static files.");

    fl_print_format("%c%c %[Operations:%] ", output.stream, f_string_eol_s[0], f_string_eol_s[0], context.set.important, context.set.important);

    fll_program_print_help_option_other(output, context, fake_other_operation_build, "   Build or compile the code based on build settings file.");
    fll_program_print_help_option_other(output, context, fake_other_operation_clean, "   Delete all build files.");
    fll_program_print_help_option_other(output, context, fake_other_operation_make, "    Build or compile the code based on fakefile.");
    fll_program_print_help_option_other(output, context, fake_other_operation_skeleton, "Build a skeleton directory structure.");

    fll_program_print_help_usage(output, context, fake_name, "operation");

    f_print_terminated("  When performing the ", output.stream);
    fl_print_format("%[%s%]", output.stream, context.set.notable, fake_other_operation_build, context.set.notable);
    f_print_terminated("  operation, the ", output.stream);
    fl_print_format("%[%s%s%]", output.stream, context.set.notable, f_console_symbol_long_enable_s, fake_long_mode, context.set.notable);
    fl_print_format(" parameter specifies a name (limited to alpha-numeric, underscore, and dash) to be used in addition to the global.%c", output.stream, f_string_eol_s[0]);

    f_print_terminated("  For example, when a ", output.stream);
    fl_print_format("%[%s%]", output.stream, context.set.notable, fake_make_parameter_variable_mode, context.set.notable);
    fl_print_format(" of 'fll_monolithic' is specified, build libraries from both 'build_libraries' and 'build_libraries-fll_monolithic' are used (but not 'build_libraries-fll_level').%c%c", output.stream, f_string_eol_s[0], f_string_eol_s[0]);

    f_print_terminated("  When specifying the ", output.stream);
    fl_print_format("%[%s%]", output.stream, context.set.notable, fake_make_parameter_variable_fakefile, context.set.notable);
    f_print_terminated("  or the ", output.stream);
    fl_print_format("%[%s%]", output.stream, context.set.notable, fake_make_parameter_variable_settings, context.set.notable);
    fl_print_format(" parameters, the filenames are relative to the data build directory, unless a path is used.%c", output.stream, f_string_eol_s[0]);

    f_print_terminated("  For example, with '", output.stream);
    fl_print_format("%[%s%s my_fakefile%]", output.stream, context.set.notable, f_console_symbol_long_enable_s, fake_long_fakefile, context.set.notable);
    f_print_terminated("' the fakefile at '", output.stream);
    fl_print_format("%[./%s%smy_fakefile%]", output.stream, context.set.notable, fake_default_path_data, fake_default_path_build, context.set.notable);
    f_print_terminated("' would be used, however with '", output.stream);
    fl_print_format("%[%s%s ./my_fakefile%]", output.stream, context.set.notable, f_console_symbol_long_enable_s, fake_long_fakefile, context.set.notable);
    f_print_terminated("' the fakefile at '", output.stream);
    fl_print_format("%[./my_fakefile%]", output.stream, context.set.notable, context.set.notable);
    fl_print_format("' would be used.%c%c", output.stream, f_string_eol_s[0], f_string_eol_s[0]);

    funlockfile(output.stream);

    return F_none;
  }
#endif // _di_fake_print_help_

#ifndef _di_fake_main_
  f_status_t fake_main(const f_console_arguments_t arguments, fake_main_t *main) {

    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(main->parameters, fake_total_parameters);

      // Load all parameters and identify priority of color parameters.
      {
        f_console_parameter_id_t ids[3] = { fake_parameter_no_color, fake_parameter_light, fake_parameter_dark };
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(arguments, parameters, choices, F_true, &main->remaining, &main->context);

        if (main->context.set.error.before) {
          main->error.context = main->context.set.error;
          main->error.notable = main->context.set.notable;

          main->warning.context = main->context.set.warning;
          main->warning.notable = main->context.set.notable;
        }
        else {
          f_color_set_t *sets[] = { &main->error.context, &main->error.notable, &main->warning.context, &main->warning.notable, 0 };

          fll_program_parameter_process_empty(&main->context, sets);
        }

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process", F_true);

          fake_main_delete(main);
          return status;
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { fake_parameter_verbosity_quiet, fake_parameter_verbosity_normal, fake_parameter_verbosity_verbose, fake_parameter_verbosity_debug };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

          fake_main_delete(main);
          return status;
        }

        if (choice == fake_parameter_verbosity_quiet) {
          main->error.verbosity = f_console_verbosity_quiet;
          main->warning.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == fake_parameter_verbosity_normal) {
          main->error.verbosity = f_console_verbosity_normal;
          main->warning.verbosity = f_console_verbosity_normal;
        }
        else if (choice == fake_parameter_verbosity_verbose) {
          main->error.verbosity = f_console_verbosity_verbose;
          main->warning.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == fake_parameter_verbosity_debug) {
          main->error.verbosity = f_console_verbosity_debug;
          main->warning.verbosity = f_console_verbosity_debug;
        }
      }

      status = F_none;
    }

    f_array_length_t operations_length = main->parameters[fake_parameter_operation_build].locations.used;

    operations_length += main->parameters[fake_parameter_operation_clean].locations.used;
    operations_length += main->parameters[fake_parameter_operation_make].locations.used;
    operations_length += main->parameters[fake_parameter_operation_skeleton].locations.used;

    uint8_t operations[operations_length];
    f_string_t operations_name = 0;

    {
      f_array_length_t locations[operations_length];
      f_array_length_t locations_length = 0;
      f_array_length_t i = 0;
      f_array_length_t j = 0;
      f_array_length_t k = 0;

      for (; i < main->parameters[fake_parameter_operation_build].locations.used; ++i, ++locations_length) {

        operations[locations_length] = fake_operation_build;
        locations[locations_length] = main->parameters[fake_parameter_operation_build].locations.array[i];
      } // for

      for (i = 0; i < main->parameters[fake_parameter_operation_clean].locations.used; ++i) {

        for (j = 0; j < locations_length; ++j) {

          if (main->parameters[fake_parameter_operation_clean].locations.array[i] < locations[j]) {
            for (k = locations_length; k > j; --k) {
              locations[k] = locations[k - 1];
              operations[k] = operations[k - 1];
            } // for

            break;
          }
        } // for

        locations[j] = main->parameters[fake_parameter_operation_clean].locations.array[i];
        operations[j] = fake_operation_clean;
        ++locations_length;
      } // for

      for (i = 0; i < main->parameters[fake_parameter_operation_make].locations.used; ++i) {

        for (j = 0; j < locations_length; ++j) {

          if (main->parameters[fake_parameter_operation_make].locations.array[i] < locations[j]) {
            for (k = locations_length; k > j; --k) {
              locations[k] = locations[k - 1];
              operations[k] = operations[k - 1];
            } // for

            break;
          }
        } // for

        locations[j] = main->parameters[fake_parameter_operation_make].locations.array[i];
        operations[j] = fake_operation_make;
        ++locations_length;
      } // for

      for (i = 0; i < main->parameters[fake_parameter_operation_skeleton].locations.used; ++i) {

        for (j = 0; j < locations_length; ++j) {

          if (main->parameters[fake_parameter_operation_skeleton].locations.array[i] < locations[j]) {
            for (k = locations_length; k > j; --k) {

              locations[k] = locations[k - 1];
              operations[k] = operations[k - 1];
            } // for

            break;
          }
        } // for

        locations[j] = main->parameters[fake_parameter_operation_skeleton].locations.array[i];
        operations[j] = fake_operation_skeleton;
        ++locations_length;
      } // for
    }

    status = F_none;

    if (main->parameters[fake_parameter_help].result == f_console_result_found) {
      fake_print_help(main->output, main->context);

      fake_main_delete(main);
      return F_none;
    }

    if (main->parameters[fake_parameter_version].result == f_console_result_found) {
      fll_program_print_version(main->output, fake_version);

      fake_main_delete(main);
      return F_none;
    }

    if (operations_length) {
      bool validate_parameter_directories = F_true;

      status = fake_process_console_parameters(arguments, main);

      if (F_status_is_error_not(status)) {
        status = fake_path_generate(main);
      }

      if (F_status_is_error(status)) {
        fake_main_delete(main);

        return F_status_set_error(status);
      }

      for (uint8_t i = 0; i < operations_length; ++i) {

        main->operation = operations[i];

        if (main->operation == fake_operation_build) {
          operations_name = fake_other_operation_build;
        }
        else if (main->operation == fake_operation_clean) {
          operations_name = fake_other_operation_clean;
        }
        else if (main->operation == fake_operation_make) {
          operations_name = fake_other_operation_make;
        }
        else if (main->operation == fake_operation_skeleton) {
          operations_name = fake_other_operation_skeleton;
        }

        if (main->operation == fake_operation_build) {
          if (validate_parameter_directories) {
            status = fake_validate_parameter_directories(arguments, *main);
            validate_parameter_directories = F_false;
          }

          if (F_status_is_error_not(status) && status != F_signal) {
            f_string_static_t stub = f_string_static_t_initialize;

            status = fake_build_operate(stub, main);
          }
        }
        else if (main->operation == fake_operation_clean) {
          if (validate_parameter_directories) {
            status = fake_validate_parameter_directories(arguments, *main);
            validate_parameter_directories = F_false;
          }

          if (F_status_is_error_not(status) && status != F_signal) {
            status = fake_clean_operate(*main);
          }
        }
        else if (main->operation == fake_operation_make) {
          if (validate_parameter_directories) {
            status = fake_validate_parameter_directories(arguments, *main);
            validate_parameter_directories = F_false;
          }

          if (F_status_is_error_not(status) && status != F_signal) {
            status = fake_make_operate(main);

            if (status == F_child) {
              break;
            }
          }
        }
        else if (main->operation == fake_operation_skeleton) {
          status = fake_skeleton_operate(*main);
        }

        if (status == F_signal || status == F_child || fake_signal_received(*main)) {
          break;
        }
        else if (F_status_is_error(status)) {
          if (main->error.verbosity != f_console_verbosity_quiet) {
            flockfile(main->error.to.stream);

            fl_print_format("%c%[%SThe operation '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%s%]", main->error.to.stream, main->error.notable, operations_name, main->error.notable);
            fl_print_format("%[' failed.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

            funlockfile(main->error.to.stream);
          }

          break;
        }
      } // for

      // ensure a newline is always put at the end of the program execution, unless in quiet mode.
      if (main->error.verbosity != f_console_verbosity_quiet) {
        if (F_status_is_error(status) || status == F_signal) {
          fll_print_character(f_string_eol_s[0], main->error.to.stream);
        }
        else if (status != F_child) {
          fll_print_format("%cAll operations complete.%c%c", main->output.stream, f_string_eol_s[0], f_string_eol_s[0], f_string_eol_s[0]);
        }
      }
    }
    else {
      if (main->error.verbosity != f_console_verbosity_quiet) {
        fll_print_format("%c%[%SYou failed to specify an operation.%]%c%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context, f_string_eol_s[0], f_string_eol_s[0]);
      }

      status = F_status_set_error(F_parameter);
    }

    fake_main_delete(main);
    return status;
  }
#endif // _di_fake_main_

#ifndef _di_fake_main_delete_
  f_status_t fake_main_delete(fake_main_t *main) {

    for (f_array_length_t i = 0; i < fake_total_parameters; ++i) {
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations_sub);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].values);
    } // for

    macro_f_array_lengths_t_delete_simple(main->remaining);

    macro_f_string_dynamics_t_delete_simple(main->define);
    macro_f_string_dynamic_t_delete_simple(main->fakefile);
    macro_f_string_dynamics_t_delete_simple(main->mode);
    macro_f_string_dynamic_t_delete_simple(main->process);
    macro_f_string_dynamic_t_delete_simple(main->settings);

    macro_f_string_dynamic_t_delete_simple(main->path_build);
    macro_f_string_dynamic_t_delete_simple(main->path_build_documents);
    macro_f_string_dynamic_t_delete_simple(main->path_build_includes);
    macro_f_string_dynamic_t_delete_simple(main->path_build_libraries);
    macro_f_string_dynamic_t_delete_simple(main->path_build_libraries_script);
    macro_f_string_dynamic_t_delete_simple(main->path_build_libraries_shared);
    macro_f_string_dynamic_t_delete_simple(main->path_build_libraries_static);
    macro_f_string_dynamic_t_delete_simple(main->path_build_objects);
    macro_f_string_dynamic_t_delete_simple(main->path_build_programs);
    macro_f_string_dynamic_t_delete_simple(main->path_build_programs_script);
    macro_f_string_dynamic_t_delete_simple(main->path_build_programs_shared);
    macro_f_string_dynamic_t_delete_simple(main->path_build_programs_static);
    macro_f_string_dynamic_t_delete_simple(main->path_build_settings);
    macro_f_string_dynamic_t_delete_simple(main->path_build_stage);
    macro_f_string_dynamic_t_delete_simple(main->path_work);

    macro_f_string_dynamic_t_delete_simple(main->path_data);
    macro_f_string_dynamic_t_delete_simple(main->path_data_build);

    macro_f_string_dynamic_t_delete_simple(main->path_data_settings);

    macro_f_string_dynamic_t_delete_simple(main->path_documents);

    macro_f_string_dynamic_t_delete_simple(main->path_licenses);

    macro_f_string_dynamic_t_delete_simple(main->path_sources);
    macro_f_string_dynamic_t_delete_simple(main->path_sources_bash);
    macro_f_string_dynamic_t_delete_simple(main->path_sources_c);
    macro_f_string_dynamic_t_delete_simple(main->path_sources_cpp);
    macro_f_string_dynamic_t_delete_simple(main->path_sources_script);

    macro_f_string_dynamic_t_delete_simple(main->path_work);
    macro_f_string_dynamic_t_delete_simple(main->path_work_includes);
    macro_f_string_dynamic_t_delete_simple(main->path_work_libraries);
    macro_f_string_dynamic_t_delete_simple(main->path_work_libraries_script);
    macro_f_string_dynamic_t_delete_simple(main->path_work_libraries_shared);
    macro_f_string_dynamic_t_delete_simple(main->path_work_libraries_static);
    macro_f_string_dynamic_t_delete_simple(main->path_work_programs);
    macro_f_string_dynamic_t_delete_simple(main->path_work_programs_script);
    macro_f_string_dynamic_t_delete_simple(main->path_work_programs_shared);
    macro_f_string_dynamic_t_delete_simple(main->path_work_programs_static);

    macro_f_string_dynamic_t_delete_simple(main->file_data_build_defines);
    macro_f_string_dynamic_t_delete_simple(main->file_data_build_dependencies);
    macro_f_string_dynamic_t_delete_simple(main->file_data_build_fakefile);
    macro_f_string_dynamic_t_delete_simple(main->file_data_build_settings);

    macro_f_string_dynamic_t_delete_simple(main->file_documents_readme);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_fake_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif
