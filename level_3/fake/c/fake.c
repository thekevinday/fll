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

#ifndef _di_fake_print_copyright_
  f_status_t fake_print_copyright(const f_file_t file, const bool full) {

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
#endif // _di_fake_print_copyright_

#ifndef _di_fake_print_help_
  f_status_t fake_print_help(const f_file_t file, const f_color_context_t context) {

    flockfile(file.stream);

    fll_program_print_help_header(file, context, fake_program_name_long_s, fake_program_version_s);

    fll_program_print_help_option(file, context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Print this help message.");
    fll_program_print_help_option(file, context, f_console_standard_short_copyright_s, f_console_standard_long_copyright_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Print the copyright.");
    fll_program_print_help_option(file, context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "     Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Do not print using color.");
    fll_program_print_help_option(file, context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Decrease verbosity, silencing most output.");
    fll_program_print_help_option(file, context, f_console_standard_short_error_s, f_console_standard_long_error_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Decrease verbosity, using only error output.");
    fll_program_print_help_option(file, context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Set verbosity to normal.");
    fll_program_print_help_option(file, context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Increase verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Enable debugging, significantly increasing verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Print only the version number.");

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
    fll_program_print_help_option(file, context, fake_short_path_under_s, fake_long_path_under_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Specify a custom path the data build files are under.");
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
    fll_program_print_help_option_other(file, context, fake_other_operation_make_s, "    Build or compile the code based on fakefile (default).");
    fll_program_print_help_option_other(file, context, fake_other_operation_skeleton_s, "Build a skeleton directory structure.");

    fll_program_print_help_usage(file, context, fake_program_name_s, fake_program_help_parameters_s);

    fl_print_format("  When performing the %[%r%] operation, the", file.stream, context.set.notable, fake_other_operation_build_s, context.set.notable);
    fl_print_format(" %[%r%r%] parameter specifies a name (limited to alpha-numeric, underscore, and dash) to be used in addition to the global.%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, fake_long_mode_s, context.set.notable, f_string_eol_s);

    fl_print_format("  For example, when a %[%r%]", file.stream, context.set.notable, fake_make_parameter_variable_mode_s, context.set.notable);
    fl_print_format(" of 'fll_monolithic' is specified, build libraries from both 'build_libraries' and 'build_libraries-fll_monolithic' are used (but not 'build_libraries-fll_level').%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When specifying the %[%r%] or the %[%r%]", file.stream, context.set.notable, fake_make_parameter_variable_fakefile_s, context.set.notable, context.set.notable, fake_make_parameter_variable_settings_s, context.set.notable);
    fl_print_format(" parameters, the project root is seached first and then the build data director is searched when the given file does not contain a directory separator.%r", file.stream, f_string_eol_s);

    fl_print_format("  For example, with '%[%r%r my_fakefile%]' the fakefile at", file.stream, context.set.notable, f_console_symbol_long_enable_s, fake_long_fakefile_s, context.set.notable);
    fl_print_format(" '%[./my_fakefile%]' is used if found, but if it is not found then", file.stream, context.set.notable, context.set.notable);
    fl_print_format(" '%[./%r%rmy_fakefile%]' is used if found.%r", file.stream, context.set.notable, fake_default_path_data_s, fake_default_path_build_s, context.set.notable, f_string_eol_s);
    fl_print_format("  For example, with '%[%r%r ./my_fakefile%]' the fakefile at", file.stream, context.set.notable, f_console_symbol_long_enable_s, fake_long_fakefile_s, context.set.notable);
    fl_print_format(" '%[./my_fakefile%]' is used if found, but if it is not found then no other paths are attempted.%r%r", file.stream, context.set.notable, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When piping data to this program, the piped data is treated as if it were prepended to the %[%r%]", file.stream, context.set.notable, fake_make_parameter_variable_fakefile_s, context.set.notable);
    fl_print_format(" or the %[%r%], depending on the operation.%r%r", file.stream, context.set.notable, fake_make_parameter_variable_settings_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  A section name from the fakefile that does not conflict with an operation name may be specified when performing the %[%r%] operation.%r%r", file.stream, context.set.notable, fake_other_operation_make_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_fake_print_help_

#ifndef _di_fake_main_
  f_status_t fake_main(fll_program_data_t * const main, const f_console_arguments_t *arguments) {

    f_status_t status = F_none;

    // Load all parameters and identify priority of color parameters.
    {
      f_console_parameter_id_t ids[3] = { fake_parameter_no_color_e, fake_parameter_light_e, fake_parameter_dark_e };
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
        fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process", F_true);

        return status;
      }
    }

    // Identify priority of verbosity related parameters.
    {
      f_console_parameter_id_t ids[5] = { fake_parameter_verbosity_quiet_e, fake_parameter_verbosity_error_e, fake_parameter_verbosity_normal_e, fake_parameter_verbosity_verbose_e, fake_parameter_verbosity_debug_e };
      f_console_parameter_id_t choice = 0;
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 5);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

        return status;
      }

      if (choice == fake_parameter_verbosity_quiet_e) {
        main->output.verbosity = f_console_verbosity_quiet_e;
        main->error.verbosity = f_console_verbosity_quiet_e;
        main->warning.verbosity = f_console_verbosity_quiet_e;
      }
      else if (choice == fake_parameter_verbosity_error_e) {
        main->output.verbosity = f_console_verbosity_error_e;
        main->error.verbosity = f_console_verbosity_error_e;
        main->warning.verbosity = f_console_verbosity_error_e;
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

    if (main->parameters.array[fake_parameter_help_e].result == f_console_result_found_e) {
      fake_print_help(main->output.to, main->context);

      return F_none;
    }

    if (main->parameters.array[fake_parameter_version_e].result == f_console_result_found_e) {
      fll_program_print_version(main->output.to, fake_program_version_s);

      return F_none;
    }

    if (main->parameters.array[fake_parameter_copyright_e].result == f_console_result_found_e) {
      fake_print_copyright(main->output.to, main->output.verbosity > f_console_verbosity_error_e);

      return F_none;
    }

    status = F_none;

    fake_data_t data = fake_data_t_initialize;
    data.main = main;
    data.argv = main->parameters.arguments.array;

    f_array_length_t operations_length = main->parameters.array[fake_parameter_operation_build_e].locations.used;

    operations_length += main->parameters.array[fake_parameter_operation_clean_e].locations.used;
    operations_length += main->parameters.array[fake_parameter_operation_make_e].locations.used;
    operations_length += main->parameters.array[fake_parameter_operation_skeleton_e].locations.used;

    // Ensure the default operation always exists.
    if (operations_length) {
      data.flag |= fake_data_flag_has_operation_e;
    }
    else {
      operations_length = 1;
    }

    uint8_t operations[operations_length];
    f_string_static_t operations_name = f_string_static_t_initialize;

    if (data.flag & fake_data_flag_has_operation_e) {
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
    else {
      operations[0] = fake_operation_make_e;
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fake_parameter_operation_build_e].locations.used && main->parameters.array[fake_parameter_operation_make_e].locations.used) {
        status = F_status_set_error(F_parameter);

        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%r%[%QThe operation '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%]", main->error.to.stream, main->error.notable, fake_other_operation_build_s, main->error.notable);
          fl_print_format("%[' cannot be specified with the operation '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%r%]", main->error.to.stream, main->error.notable, fake_other_operation_make_s, main->error.notable);
          fl_print_format("%['.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }
      }
    }

    if (F_status_is_error_not(status)) {
      bool validate_parameter_paths = F_true;

      status = fake_process_console_parameters(&data);

      if (F_status_is_error_not(status)) {
        status = fake_path_generate(&data);
      }

      if (F_status_is_error(status)) {
        fake_data_delete(&data);

        return F_status_set_error(status);
      }

      {
        uint8_t i = 0;

        if (main->process_pipe && !(data.flag & fake_data_flag_has_operation_e)) {
          data.file_data_build_fakefile.used = 0;

          status = f_string_dynamic_append(f_string_ascii_minus_s, &data.file_data_build_fakefile);

          if (F_status_is_error_not(status)) {
            data.fakefile.used = 0;

            status = f_string_dynamic_append(f_string_ascii_minus_s, &data.fakefile);
          }

          if (F_status_is_error(status)) {
            fll_error_print(data.main->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);
          }
        }

        // Pre-process and perform validation when "clean" is before a "build" or "make" command as a safety check.
        if (operations_length) {
          for (uint8_t has_clean = F_false; i < operations_length; ++i) {

            if (operations[i] == fake_operation_clean_e) {
              has_clean = F_true;
            }
            else if (operations[i] == fake_operation_build_e || operations[i] == fake_operation_make_e) {

              // If the first operation is clean and a make or build operation exists, then the clean operation requires the appropriate settings file or fakefile file.
              if (has_clean) {
                operations_name = fake_other_operation_clean_s;
                data.operation = operations[i];

                status = fake_validate_parameter_paths(&data);

                if (F_status_is_error_not(status) && !main->process_pipe) {
                  f_string_static_t *path = 0;

                  if (operations[i] == fake_operation_build_e) {
                    path = &data.file_data_build_settings;
                  }
                  else {
                    path = &data.file_data_build_fakefile;
                  }

                  status = f_file_is(*path, F_file_type_regular_d, F_false);

                  if (status == F_false) {
                    status = F_status_set_error(F_file_not);
                  }

                  if (F_status_is_error(status)) {
                    fll_error_file_print(data.main->error, F_status_set_fine(status), "f_file_is", F_true, *path, fake_common_file_path_access_s, fll_error_file_type_file_e);
                  }
                }
              }

              break;
            }
          } // for
        }

        if (F_status_is_error_not(status)) {
          for (i = 0; i < operations_length; ++i) {

            data.operation = operations[i];

            if (data.operation == fake_operation_build_e) {
              operations_name = fake_other_operation_build_s;
            }
            else if (data.operation == fake_operation_clean_e) {
              operations_name = fake_other_operation_clean_s;
            }
            else if (data.operation == fake_operation_make_e) {
              operations_name = fake_other_operation_make_s;
            }
            else if (data.operation == fake_operation_skeleton_e) {
              operations_name = fake_other_operation_skeleton_s;
            }

            if (data.operation == fake_operation_build_e) {
              if (validate_parameter_paths) {
                status = fake_validate_parameter_paths(&data);
                validate_parameter_paths = F_false;
              }

              if (F_status_is_error_not(status)) {
                status = fake_build_operate(&data, 0, main->process_pipe);
              }
            }
            else if (data.operation == fake_operation_clean_e) {
              status = fake_clean_operate(&data);

              // Reset in case next operation needs files.
              validate_parameter_paths = F_true;
            }
            else if (data.operation == fake_operation_make_e) {
              if (validate_parameter_paths) {
                status = fake_validate_parameter_paths(&data);
                validate_parameter_paths = F_false;
              }

              if (F_status_is_error_not(status)) {
                status = fake_make_operate(&data);
                if (status == F_child) break;
              }
            }
            else if (data.operation == fake_operation_skeleton_e) {
              status = fake_skeleton_operate(&data);

              // Skeleton is supposed to guarantee these.
              validate_parameter_paths = F_false;
            }

            if (status == F_child) break;

            if (F_status_set_fine(status) == F_interrupt || !(i % fake_signal_check_short_d)) {
              if (fll_program_standard_signal_received(main)) {
                fake_print_signal_received(&data);

                status = F_status_set_error(F_interrupt);

                break;
              }

              main->signal_check = 0;
            }

            if (F_status_is_error(status)) break;
          } // for
        }

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_interrupt) {
            flockfile(main->output.to.stream);

            fl_print_format("%rThe operation '%[%r%]", main->output.to.stream, f_string_eol_s, main->output.notable, operations_name, main->output.notable);
            fl_print_format("' is cancelled.%r", main->output.to.stream, f_string_eol_s);

            funlockfile(main->output.to.stream);
          }
          else if (main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%r%[%QThe operation '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%r%]", main->error.to.stream, main->error.notable, operations_name, main->error.notable);
            fl_print_format("%[' failed.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }
        }
      }

      if (main->error.verbosity != f_console_verbosity_quiet_e && main->error.verbosity != f_console_verbosity_error_e) {
        if (F_status_is_error_not(status) && status != F_child) {
          fll_print_format("%rAll operations complete.%r%r", main->output.to.stream, f_string_eol_s, f_string_eol_s, f_string_eol_s);
        }
      }
    }

    if (F_status_is_error(status) && main->error.verbosity != f_console_verbosity_quiet_e) {
      if (F_status_set_fine(status) == F_interrupt) {
        fflush(main->output.to.stream);
      }

      fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
    }

    fake_data_delete(&data);

    return status;
  }
#endif // _di_fake_main_

#ifdef __cplusplus
} // extern "C"
#endif
