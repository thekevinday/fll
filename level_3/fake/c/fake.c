#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-fake-path_generate.h"
#include "private-build.h"
#include "private-clean.h"
#include "private-make.h"
#include "private-make-operate.h"
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

    f_print_dynamic_raw(f_string_eol_s, file.stream);

    fll_program_print_help_option(file, context, fake_short_define_s, fake_long_define_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Append an additional define after defines from settings file.");
    fll_program_print_help_option(file, context, fake_short_fakefile_s, fake_long_fakefile_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Use this fakefile.");
    fll_program_print_help_option(file, context, fake_short_mode_s, fake_long_mode_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Use this mode when processing the build settings.");
    fll_program_print_help_option(file, context, fake_short_process_s, fake_long_process_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Process name for storing build states.");
    fll_program_print_help_option(file, context, fake_short_settings_s, fake_long_settings_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Use this settings file.");

    f_print_dynamic_raw(f_string_eol_s, file.stream);

    fll_program_print_help_option(file, context, fake_short_path_build_s, fake_long_path_build_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Specify a custom build directory.");
    fll_program_print_help_option(file, context, fake_short_path_data_s, fake_long_path_data_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Specify a custom path to the data files.");
    fll_program_print_help_option(file, context, fake_short_path_sources_s, fake_long_path_sources_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Specify a custom path to the source files.");
    fll_program_print_help_option(file, context, fake_short_path_work_s, fake_long_path_work_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Use includes/libraries/programs from this directory instead of system.");

    fl_print_format("%r%r %[Special Options:%] ", file.stream, f_string_eol_s, f_string_eol_s, context.set.important, context.set.important);

    fll_program_print_help_option_long(file, context, fake_long_documents_disabled_s, f_console_symbol_long_enable_s, "   Forcibly do not build documents files.");
    fll_program_print_help_option_long(file, context, fake_long_documents_enabled_s, f_console_symbol_long_enable_s, "    Forcibly do build documents files.");
    fll_program_print_help_option_long(file, context, fake_long_shared_disabled_s, f_console_symbol_long_enable_s, "Forcibly do not build shared files.");
    fll_program_print_help_option_long(file, context, fake_long_shared_enabled_s, f_console_symbol_long_enable_s, " Forcibly do build shared files.");
    fll_program_print_help_option_long(file, context, fake_long_static_disabled_s, f_console_symbol_long_enable_s, "Forcibly do not build static files.");
    fll_program_print_help_option_long(file, context, fake_long_static_enabled_s, f_console_symbol_long_enable_s, " Forcibly do build static files.");

    fl_print_format("%r%r %[Operations:%] ", file.stream, f_string_eol_s, f_string_eol_s, context.set.important, context.set.important);

    fll_program_print_help_option_other(file, context, fake_other_operation_build_s, "   Build or compile the code based on build settings file.");
    fll_program_print_help_option_other(file, context, fake_other_operation_clean_s, "   Delete all build files.");
    fll_program_print_help_option_other(file, context, fake_other_operation_make_s, "    Build or compile the code based on fakefile.");
    fll_program_print_help_option_other(file, context, fake_other_operation_skeleton_s, "Build a skeleton directory structure.");

    fll_program_print_help_usage(file, context, fake_program_name_s, fake_program_help_parameters_s);

    fl_print_format("  When performing the %[%r%] operation, the", file.stream, context.set.notable, fake_other_operation_build_s, context.set.notable);
    fl_print_format(" %[%r%r%] parameter specifies a name (limited to alpha-numeric, underscore, and dash) to be used in addition to the global.%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, fake_long_mode_s, context.set.notable, f_string_eol_s);

    fl_print_format("  For example, when a %[%r%]", file.stream, context.set.notable, fake_make_parameter_variable_mode_s, context.set.notable);
    fl_print_format(" of 'fll_monolithic' is specified, build libraries from both 'build_libraries' and 'build_libraries-fll_monolithic' are used (but not 'build_libraries-fll_level').%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When specifying the %[%r%]  or the %[%r%]", file.stream, context.set.notable, fake_make_parameter_variable_fakefile_s, context.set.notable, context.set.notable, fake_make_parameter_variable_settings_s, context.set.notable);
    fl_print_format(" parameters, the filenames are relative to the data build directory, unless a path is used.%r", file.stream, f_string_eol_s);

    fl_print_format("  For example, with '%[%r%r my_fakefile%]' the fakefile at", file.stream, context.set.notable, f_console_symbol_long_enable_s, fake_long_fakefile_s, context.set.notable);
    fl_print_format(" '%[./%r%rmy_fakefile%]' would be used, however with", file.stream, context.set.notable, fake_default_path_data_s, fake_default_path_build_s, context.set.notable);
    fl_print_format(" '%[%r%r ./my_fakefile%]' the fakefile at", file.stream, context.set.notable, f_console_symbol_long_enable_s, fake_long_fakefile_s, context.set.notable);
    fl_print_format(" '%[./my_fakefile%]' would be used.%r%r", file.stream, context.set.notable, context.set.notable, f_string_eol_s, f_string_eol_s);

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_fake_print_help_

#ifndef _di_fake_main_
  f_status_t fake_main(fake_main_t * const main, const f_console_arguments_t *arguments) {

    f_status_t status = F_none;

    f_console_parameter_t parameters[] = fake_console_parameter_t_initialize;
    main->parameters.array = parameters;
    main->parameters.used = fake_total_parameters_d;

    // Load all parameters and identify priority of color parameters.
    {
      f_console_parameter_id_t ids[3] = { fake_parameter_no_color_e, fake_parameter_light_e, fake_parameter_dark_e };
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

      status = fll_program_parameter_process(*arguments, &main->parameters, choices, F_true, &main->remaining, &main->context);

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
      f_console_parameter_id_t ids[4] = { fake_parameter_verbosity_quiet_e, fake_parameter_verbosity_normal_e, fake_parameter_verbosity_verbose_e, fake_parameter_verbosity_debug_e };
      f_console_parameter_id_t choice = 0;
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

        fake_main_delete(main);
        return status;
      }

      if (choice == fake_parameter_verbosity_quiet_e) {
        main->output.verbosity = f_console_verbosity_quiet_e;
        main->error.verbosity = f_console_verbosity_quiet_e;
        main->warning.verbosity = f_console_verbosity_quiet_e;
      }
      else if (choice == fake_parameter_verbosity_normal_e) {
        main->output.verbosity = f_console_verbosity_normal_e;
        main->error.verbosity = f_console_verbosity_normal_e;
        main->warning.verbosity = f_console_verbosity_normal_e;
      }
      else if (choice == fake_parameter_verbosity_verbose_e) {
        main->output.verbosity = f_console_verbosity_verbose_e;
        main->error.verbosity = f_console_verbosity_verbose_e;
        main->warning.verbosity = f_console_verbosity_verbose_e;
      }
      else if (choice == fake_parameter_verbosity_debug_e) {
        main->output.verbosity = f_console_verbosity_debug_e;
        main->error.verbosity = f_console_verbosity_debug_e;
        main->warning.verbosity = f_console_verbosity_debug_e;
      }
    }

    status = F_none;

    f_array_length_t operations_length = main->parameters.array[fake_parameter_operation_build_e].locations.used;

    operations_length += main->parameters.array[fake_parameter_operation_clean_e].locations.used;
    operations_length += main->parameters.array[fake_parameter_operation_make_e].locations.used;
    operations_length += main->parameters.array[fake_parameter_operation_skeleton_e].locations.used;

    uint8_t operations[operations_length];
    f_string_static_t operations_name = f_string_static_t_initialize;

    {
      f_array_length_t locations[operations_length];
      f_array_length_t locations_length = 0;
      f_array_length_t i = 0;
      f_array_length_t j = 0;
      f_array_length_t k = 0;

      for (; i < main->parameters.array[fake_parameter_operation_build_e].locations.used; ++i, ++locations_length) {

        operations[locations_length] = fake_operation_build_e;
        locations[locations_length] = main->parameters.array[fake_parameter_operation_build_e].locations.array[i];
      } // for

      for (i = 0; i < main->parameters.array[fake_parameter_operation_clean_e].locations.used; ++i) {

        for (j = 0; j < locations_length; ++j) {

          if (main->parameters.array[fake_parameter_operation_clean_e].locations.array[i] < locations[j]) {
            for (k = locations_length; k > j; --k) {
              locations[k] = locations[k - 1];
              operations[k] = operations[k - 1];
            } // for

            break;
          }
        } // for

        locations[j] = main->parameters.array[fake_parameter_operation_clean_e].locations.array[i];
        operations[j] = fake_operation_clean_e;
        ++locations_length;
      } // for

      for (i = 0; i < main->parameters.array[fake_parameter_operation_make_e].locations.used; ++i) {

        for (j = 0; j < locations_length; ++j) {

          if (main->parameters.array[fake_parameter_operation_make_e].locations.array[i] < locations[j]) {
            for (k = locations_length; k > j; --k) {
              locations[k] = locations[k - 1];
              operations[k] = operations[k - 1];
            } // for

            break;
          }
        } // for

        locations[j] = main->parameters.array[fake_parameter_operation_make_e].locations.array[i];
        operations[j] = fake_operation_make_e;
        ++locations_length;
      } // for

      for (i = 0; i < main->parameters.array[fake_parameter_operation_skeleton_e].locations.used; ++i) {

        for (j = 0; j < locations_length; ++j) {

          if (main->parameters.array[fake_parameter_operation_skeleton_e].locations.array[i] < locations[j]) {
            for (k = locations_length; k > j; --k) {

              locations[k] = locations[k - 1];
              operations[k] = operations[k - 1];
            } // for

            break;
          }
        } // for

        locations[j] = main->parameters.array[fake_parameter_operation_skeleton_e].locations.array[i];
        operations[j] = fake_operation_skeleton_e;
        ++locations_length;
      } // for
    }

    status = F_none;

    if (main->parameters.array[fake_parameter_help_e].result == f_console_result_found_e) {
      fake_print_help(main->output.to, main->context);

      fake_main_delete(main);

      return F_none;
    }

    if (main->parameters.array[fake_parameter_version_e].result == f_console_result_found_e) {
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

        if (main->operation == fake_operation_build_e) {
          operations_name = fake_other_operation_build_s;
        }
        else if (main->operation == fake_operation_clean_e) {
          operations_name = fake_other_operation_clean_s;
        }
        else if (main->operation == fake_operation_make_e) {
          operations_name = fake_other_operation_make_s;
        }
        else if (main->operation == fake_operation_skeleton_e) {
          operations_name = fake_other_operation_skeleton_s;
        }

        if (main->operation == fake_operation_build_e) {
          if (validate_parameter_directories) {
            status = fake_validate_parameter_directories(arguments, main);
            validate_parameter_directories = F_false;
          }

          if (F_status_is_error_not(status)) {
            status = fake_build_operate(f_string_empty_s, main);
          }
        }
        else if (main->operation == fake_operation_clean_e) {
          if (validate_parameter_directories) {
            status = fake_validate_parameter_directories(arguments, main);
            validate_parameter_directories = F_false;
          }

          if (F_status_is_error_not(status)) {
            status = fake_clean_operate(main);
          }
        }
        else if (main->operation == fake_operation_make_e) {
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
        else if (main->operation == fake_operation_skeleton_e) {
          status = fake_skeleton_operate(main);
        }

        if (status == F_child) {
          break;
        }

        if (F_status_set_fine(status) == F_interrupt || !(i % fake_signal_check_short_d) && fake_signal_received(main)) {
          status = F_status_set_error(F_interrupt);

          break;
        }

        if (F_status_is_error(status)) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%r%[%QThe operation '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%r%]", main->error.to.stream, main->error.notable, operations_name, main->error.notable);
            fl_print_format("%[' failed.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }

          break;
        }
      } // for

      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_interrupt) {
            fflush(main->output.to.stream);
          }

          fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
        }
        else if (status != F_child) {
          fll_print_format("%rAll operations complete.%r%r", main->output.to.stream, f_string_eol_s, f_string_eol_s, f_string_eol_s);
        }
      }
    }
    else {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        fll_print_format("%r%[%QYou failed to specify an operation.%]%r%r", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context, f_string_eol_s, f_string_eol_s);
      }

      status = F_status_set_error(F_parameter);
    }

    fake_main_delete(main);

    return status;
  }
#endif // _di_fake_main_

#ifdef __cplusplus
} // extern "C"
#endif
