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
  f_status_t fake_print_help(const f_file_t file, const f_color_context_t context) {

    flockfile(file.stream);

    fll_program_print_help_header(file, context, fake_program_name_long_s, fake_program_version_s);

    fll_program_print_help_option(file, context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print this help message.");
    fll_program_print_help_option(file, context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Do not file in color.");
    fll_program_print_help_option(file, context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity, silencing most output.");
    fll_program_print_help_option(file, context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Set verbosity to normal file.");
    fll_program_print_help_option(file, context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Enable debugging, significantly increasing verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Print only the version number.");

    f_print_character(f_string_eol_s[0], file.stream);

    fll_program_print_help_option(file, context, fake_short_define_s, fake_long_define_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Append an additional define after defines from settings file.");
    fll_program_print_help_option(file, context, fake_short_fakefile_s, fake_long_fakefile_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Use this fakefile.");
    fll_program_print_help_option(file, context, fake_short_mode_s, fake_long_mode_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Use this mode when processing the build settings.");
    fll_program_print_help_option(file, context, fake_short_process_s, fake_long_process_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Process name for storing build states.");
    fll_program_print_help_option(file, context, fake_short_settings_s, fake_long_settings_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Use this settings file.");

    f_print_character(f_string_eol_s[0], file.stream);

    fll_program_print_help_option(file, context, fake_short_path_build_s, fake_long_path_build_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Specify a custom build directory.");
    fll_program_print_help_option(file, context, fake_short_path_data_s, fake_long_path_data_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Specify a custom path to the data files.");
    fll_program_print_help_option(file, context, fake_short_path_sources_s, fake_long_path_sources_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Specify a custom path to the source files.");
    fll_program_print_help_option(file, context, fake_short_path_work_s, fake_long_path_work_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Use includes/libraries/programs from this directory instead of system.");

    fl_print_format("%c%c %[Special Options:%] ", file.stream, f_string_eol_s[0], f_string_eol_s[0], context.set.important, context.set.important);

    fll_program_print_help_option_long(file, context, fake_long_documents_disabled_s, f_console_symbol_long_enable_s, "   Forcibly do not build documents files.");
    fll_program_print_help_option_long(file, context, fake_long_documents_enabled_s, f_console_symbol_long_enable_s, "    Forcibly do build documents files.");
    fll_program_print_help_option_long(file, context, fake_long_shared_disabled_s, f_console_symbol_long_enable_s, "Forcibly do not build shared files.");
    fll_program_print_help_option_long(file, context, fake_long_shared_enabled_s, f_console_symbol_long_enable_s, " Forcibly do build shared files.");
    fll_program_print_help_option_long(file, context, fake_long_static_disabled_s, f_console_symbol_long_enable_s, "Forcibly do not build static files.");
    fll_program_print_help_option_long(file, context, fake_long_static_enabled_s, f_console_symbol_long_enable_s, " Forcibly do build static files.");

    fl_print_format("%c%c %[Operations:%] ", file.stream, f_string_eol_s[0], f_string_eol_s[0], context.set.important, context.set.important);

    fll_program_print_help_option_other(file, context, fake_other_operation_build_s, "   Build or compile the code based on build settings file.");
    fll_program_print_help_option_other(file, context, fake_other_operation_clean_s, "   Delete all build files.");
    fll_program_print_help_option_other(file, context, fake_other_operation_make_s, "    Build or compile the code based on fakefile.");
    fll_program_print_help_option_other(file, context, fake_other_operation_skeleton_s, "Build a skeleton directory structure.");

    fll_program_print_help_usage(file, context, fake_program_name_s, "operation");

    fl_print_format("  When performing the %[%s%] operation, the", file.stream, context.set.notable, fake_other_operation_build_s, context.set.notable);
    fl_print_format(" %[%s%s%] parameter specifies a name (limited to alpha-numeric, underscore, and dash) to be used in addition to the global.%c", file.stream, context.set.notable, f_console_symbol_long_enable_s, fake_long_mode_s, context.set.notable, f_string_eol_s[0]);

    fl_print_format("  For example, when a %[%s%]", file.stream, context.set.notable, fake_make_parameter_variable_mode_s, context.set.notable);
    fl_print_format(" of 'fll_monolithic' is specified, build libraries from both 'build_libraries' and 'build_libraries-fll_monolithic' are used (but not 'build_libraries-fll_level').%c%c", file.stream, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  When specifying the %[%s%]  or the %[%s%]", file.stream, context.set.notable, fake_make_parameter_variable_fakefile_s, context.set.notable, context.set.notable, fake_make_parameter_variable_settings_s, context.set.notable);
    fl_print_format(" parameters, the filenames are relative to the data build directory, unless a path is used.%c", file.stream, f_string_eol_s[0]);

    fl_print_format("  For example, with '%[%s%s my_fakefile%]' the fakefile at", file.stream, context.set.notable, f_console_symbol_long_enable_s, fake_long_fakefile_s, context.set.notable);
    fl_print_format(" '%[./%s%smy_fakefile%]' would be used, however with", file.stream, context.set.notable, fake_default_path_data_s, fake_default_path_build_s, context.set.notable);
    fl_print_format(" '%[%s%s ./my_fakefile%]' the fakefile at", file.stream, context.set.notable, f_console_symbol_long_enable_s, fake_long_fakefile_s, context.set.notable);
    fl_print_format(" '%[./my_fakefile%]' would be used.%c%c", file.stream, context.set.notable, context.set.notable, f_string_eol_s[0], f_string_eol_s[0]);

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_fake_print_help_

#ifndef _di_fake_main_
  f_status_t fake_main(fake_main_t * const main, const f_console_arguments_t *arguments) {

    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(main->parameters, fake_total_parameters_d);

      // Load all parameters and identify priority of color parameters.
      {
        f_console_parameter_id_t ids[3] = { fake_parameter_no_color, fake_parameter_light, fake_parameter_dark };
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
          main->output.verbosity = f_console_verbosity_quiet;
          main->error.verbosity = f_console_verbosity_quiet;
          main->warning.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == fake_parameter_verbosity_normal) {
          main->output.verbosity = f_console_verbosity_normal;
          main->error.verbosity = f_console_verbosity_normal;
          main->warning.verbosity = f_console_verbosity_normal;
        }
        else if (choice == fake_parameter_verbosity_verbose) {
          main->output.verbosity = f_console_verbosity_verbose;
          main->error.verbosity = f_console_verbosity_verbose;
          main->warning.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == fake_parameter_verbosity_debug) {
          main->output.verbosity = f_console_verbosity_debug;
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
      fake_print_help(main->output.to, main->context);

      fake_main_delete(main);

      return F_none;
    }

    if (main->parameters[fake_parameter_version].result == f_console_result_found) {
      fll_program_print_version(main->output.to, fake_program_version_s);

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
          operations_name = fake_other_operation_build_s;
        }
        else if (main->operation == fake_operation_clean) {
          operations_name = fake_other_operation_clean_s;
        }
        else if (main->operation == fake_operation_make) {
          operations_name = fake_other_operation_make_s;
        }
        else if (main->operation == fake_operation_skeleton) {
          operations_name = fake_other_operation_skeleton_s;
        }

        if (main->operation == fake_operation_build) {
          if (validate_parameter_directories) {
            status = fake_validate_parameter_directories(arguments, main);
            validate_parameter_directories = F_false;
          }

          if (F_status_is_error_not(status)) {
            f_string_static_t stub = f_string_static_t_initialize;

            status = fake_build_operate(stub, main);
          }
        }
        else if (main->operation == fake_operation_clean) {
          if (validate_parameter_directories) {
            status = fake_validate_parameter_directories(arguments, main);
            validate_parameter_directories = F_false;
          }

          if (F_status_is_error_not(status)) {
            status = fake_clean_operate(main);
          }
        }
        else if (main->operation == fake_operation_make) {
          if (validate_parameter_directories) {
            status = fake_validate_parameter_directories(arguments, main);
            validate_parameter_directories = F_false;
          }

          if (F_status_is_error_not(status)) {
            status = fake_make_operate(main);

            if (status == F_child) {
              break;
            }
          }
        }
        else if (main->operation == fake_operation_skeleton) {
          status = fake_skeleton_operate(main);
        }

        if (status == F_child) {
          break;
        }
        else if (F_status_set_fine(status) == F_interrupt || !(i % fake_signal_check_short_d) && fake_signal_received(main)) {
          status = F_status_set_error(F_interrupt);
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

      if (main->error.verbosity != f_console_verbosity_quiet) {
        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_interrupt) {
            fflush(main->output.to.stream);
          }

          fll_print_terminated(f_string_eol_s, main->output.to.stream);
        }
        else if (status != F_child) {
          fll_print_format("%cAll operations complete.%c%c", main->output.to.stream, f_string_eol_s[0], f_string_eol_s[0], f_string_eol_s[0]);
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
  f_status_t fake_main_delete(fake_main_t * const main) {

    for (f_array_length_t i = 0; i < fake_total_parameters_d; ++i) {

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
