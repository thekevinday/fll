#include "fss_extended_write.h"
#include "private-common.h"
#include "private-write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_write_print_copyright_
  f_status_t fss_extended_write_print_copyright(const f_file_t file, const bool full) {

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
#endif // _di_fss_extended_write_print_copyright_

#ifndef _di_fss_extended_write_print_help_
  f_status_t fss_extended_write_print_help(const f_file_t file, const f_color_context_t context) {

    flockfile(file.stream);

    fll_program_print_help_header(file, context, fss_extended_write_program_name_long_s, fss_extended_write_program_version_s);

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

    fll_program_print_help_option(file, context, fss_extended_write_short_content_s, fss_extended_write_long_content_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "The Content to write.");
    fll_program_print_help_option(file, context, fss_extended_write_short_double_s, fss_extended_write_long_double_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Use double quotes (default).");
    fll_program_print_help_option(file, context, fss_extended_write_short_file_s, fss_extended_write_long_file_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Specify a file to send data to.");
    fll_program_print_help_option(file, context, fss_extended_write_short_ignore_s, fss_extended_write_long_ignore_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Ignore a given range within a Content.");
    fll_program_print_help_option(file, context, fss_extended_write_short_object_s, fss_extended_write_long_object_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " The Object to write.");
    fll_program_print_help_option(file, context, fss_extended_write_short_partial_s, fss_extended_write_long_partial_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Do not write a complete Object and Content set.");
    fll_program_print_help_option(file, context, fss_extended_write_short_prepend_s, fss_extended_write_long_prepend_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Prepend the given white space characters to the start of each multi-line Content.");
    fll_program_print_help_option(file, context, fss_extended_write_short_single_s, fss_extended_write_long_single_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Use single quotes.");
    fll_program_print_help_option(file, context, fss_extended_write_short_trim_s, fss_extended_write_long_trim_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Trim Object names.");

    fll_program_print_help_usage(file, context, fss_extended_write_program_name_s, f_string_empty_s);

    fl_print_format("  The pipe uses the Backspace character '%[\\b%]' (%[U+0008%]) to designate the start of a Content.%r", file.stream, context.set.notable, context.set.notable, context.set.notable, context.set.notable, f_string_eol_s);
    fl_print_format("  The pipe uses the Form Feed character '%[\\f%]' (%[U+000C%]) to designate the end of the last Content.%r", file.stream, context.set.notable, context.set.notable, context.set.notable, context.set.notable, f_string_eol_s);
    fl_print_format("  The pipe uses the Vertical Line character '%[\\v%]' (%[U+000B%]) is used to ignore a Content range, which does nothing in this program.%r", file.stream, context.set.notable, context.set.notable, context.set.notable, context.set.notable, f_string_eol_s);
    fl_print_format("  For the pipe, an Object is terminated by either a Backspace character '%[\\b%]' (%[U+0008%])", file.stream, context.set.notable, context.set.notable, context.set.notable, context.set.notable);
    fl_print_format(" or a Form Feed character '%[\\f%]' (%[U+000C%]).%r", file.stream, context.set.notable, context.set.notable, context.set.notable, context.set.notable, f_string_eol_s);
    fl_print_format("  The end of the pipe represents the end of any Object or Content.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The FSS-0001 (Extended) specification does not support multi-line Content, therefore the parameter '%[%r%r%]'", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_extended_write_long_prepend_s, context.set.notable);
    fl_print_format(" does nothing.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  This program does not use the parameter '%[%r%r%]', which therefore does nothing.%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_extended_write_long_ignore_s, context.set.notable, f_string_eol_s);
    fl_print_format("  This parameter requires two values.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_fss_extended_write_print_help_

#ifndef _di_fss_extended_write_main_
  f_status_t fss_extended_write_main(fll_program_data_t * const main, const f_console_arguments_t *arguments) {

    f_status_t status = F_none;

    {
      f_console_parameter_id_t ids[3] = { fss_extended_write_parameter_no_color_e, fss_extended_write_parameter_light_e, fss_extended_write_parameter_dark_e };
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

      if (F_status_is_error(status)) return status;
    }

    // Identify priority of verbosity related parameters.
    {
      f_console_parameter_id_t ids[5] = { fss_extended_write_parameter_verbosity_quiet_e, fss_extended_write_parameter_verbosity_error_e, fss_extended_write_parameter_verbosity_normal_e, fss_extended_write_parameter_verbosity_verbose_e, fss_extended_write_parameter_verbosity_debug_e };
      f_console_parameter_id_t choice = 0;
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 5);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

        return status;
      }

      if (choice == fss_extended_write_parameter_verbosity_quiet_e) {
        main->output.verbosity = f_console_verbosity_quiet_e;
        main->error.verbosity = f_console_verbosity_quiet_e;
        main->warning.verbosity = f_console_verbosity_quiet_e;
      }
      else if (choice == fss_extended_write_parameter_verbosity_error_e) {
        main->output.verbosity = f_console_verbosity_error_e;
        main->error.verbosity = f_console_verbosity_error_e;
        main->warning.verbosity = f_console_verbosity_error_e;
      }
      else if (choice == fss_extended_write_parameter_verbosity_normal_e) {
        main->output.verbosity = f_console_verbosity_normal_e;
        main->error.verbosity = f_console_verbosity_normal_e;
        main->warning.verbosity = f_console_verbosity_normal_e;
      }
      else if (choice == fss_extended_write_parameter_verbosity_verbose_e) {
        main->output.verbosity = f_console_verbosity_verbose_e;
        main->error.verbosity = f_console_verbosity_verbose_e;
        main->warning.verbosity = f_console_verbosity_verbose_e;
      }
      else if (choice == fss_extended_write_parameter_verbosity_debug_e) {
        main->output.verbosity = f_console_verbosity_debug_e;
        main->error.verbosity = f_console_verbosity_debug_e;
        main->warning.verbosity = f_console_verbosity_debug_e;
      }
    }

    if (main->parameters.array[fss_extended_write_parameter_help_e].result == f_console_result_found_e) {
      fss_extended_write_print_help(main->output.to, main->context);

      return F_none;
    }

    if (main->parameters.array[fss_extended_write_parameter_version_e].result == f_console_result_found_e) {
      fll_program_print_version(main->output.to, fss_extended_write_program_version_s);

      return F_none;
    }

    if (main->parameters.array[fss_extended_write_parameter_copyright_e].result == f_console_result_found_e) {
      fss_extended_write_print_copyright(main->output.to, main->output.verbosity > f_console_verbosity_error_e);

      return F_none;
    }

    status = F_none;

    f_string_static_t * const argv = main->parameters.arguments.array;

    f_file_t output = f_file_t_initialize;

    output.id = F_type_descriptor_output_d;
    output.stream = F_type_output_d;
    output.flag = F_file_flag_create_d | F_file_flag_write_only_d | F_file_flag_append_d;

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_extended_write_parameter_file_e].result == f_console_result_additional_e) {
        if (main->parameters.array[fss_extended_write_parameter_file_e].values.used > 1) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_extended_write_long_file_s, main->error.notable);
            fl_print_format("%[' may only be specified once.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }

          status = F_status_set_error(F_parameter);
        }
        else {
          const f_array_length_t index = main->parameters.array[fss_extended_write_parameter_file_e].values.array[0];

          output.id = -1;
          output.stream = 0;
          status = f_file_stream_open(argv[index], f_string_empty_s, &output);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_open", F_true, argv[index], f_file_operation_open_s, fll_error_file_type_file_e);
          }
        }
      }
      else if (main->parameters.array[fss_extended_write_parameter_file_e].result == f_console_result_found_e) {
        fss_extended_write_error_parameter_value_missing_print(main, f_console_symbol_long_enable_s, fss_extended_write_long_file_s);
        status = F_status_set_error(F_parameter);
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_extended_write_parameter_object_e].locations.used || main->parameters.array[fss_extended_write_parameter_content_e].locations.used) {
        if (main->parameters.array[fss_extended_write_parameter_object_e].locations.used) {
          if (main->parameters.array[fss_extended_write_parameter_object_e].locations_sub.used > main->parameters.array[fss_extended_write_parameter_content_e].locations_sub.used && main->parameters.array[fss_extended_write_parameter_partial_e].result == f_console_result_none_e) {
            fss_extended_write_error_parameter_same_times_at_least_print(main);
            status = F_status_set_error(F_parameter);
          }
          else if (main->parameters.array[fss_extended_write_parameter_content_e].locations.used && main->parameters.array[fss_extended_write_parameter_partial_e].locations.used) {
            if (main->parameters.array[fss_extended_write_parameter_content_e].result == f_console_result_additional_e) {
              if (main->error.verbosity != f_console_verbosity_quiet_e) {
                flockfile(main->error.to.stream);

                fl_print_format("%r%[%QThe '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
                fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_extended_write_long_partial_s, main->error.notable);
                fl_print_format("%[' parameter only allows either the '%]", main->error.to.stream, main->error.context, main->error.context);
                fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_extended_write_long_object_s, main->error.notable);
                fl_print_format("%[' parameter or the '%]", main->error.to.stream, main->error.context, main->error.context);
                fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_extended_write_long_content_s, main->error.notable);
                fl_print_format("%[' parameter, but not both.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

                funlockfile(main->error.to.stream);
              }

              status = F_status_set_error(F_parameter);
            }
          }

          if (F_status_is_error_not(status)) {
            if (main->parameters.array[fss_extended_write_parameter_content_e].result == f_console_result_additional_e) {
              f_array_length_t location_object = main->parameters.array[fss_extended_write_parameter_object_e].locations.array[0];
              f_array_length_t location_content = main->parameters.array[fss_extended_write_parameter_content_e].locations.array[0];
              f_array_length_t location_sub_object = main->parameters.array[fss_extended_write_parameter_object_e].locations_sub.array[0];
              f_array_length_t location_sub_content = main->parameters.array[fss_extended_write_parameter_content_e].locations_sub.array[0];

              if (location_object > location_content || location_object == location_content && location_sub_object > location_sub_content) {
                if (main->error.verbosity != f_console_verbosity_quiet_e) {
                  flockfile(main->error.to.stream);

                  fl_print_format("%r%[%QEach '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
                  fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_extended_write_long_object_s, main->error.notable);
                  fl_print_format("%[' parameter must be specified before a '%]", main->error.to.stream, main->error.context, main->error.context);
                  fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_extended_write_long_content_s, main->error.notable);
                  fl_print_format("%[' parameter.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

                  funlockfile(main->error.to.stream);
                }

                status = F_status_set_error(F_parameter);
              }
              else {
                location_object = main->parameters.array[fss_extended_write_parameter_object_e].locations.array[main->parameters.array[fss_extended_write_parameter_object_e].locations.used - 1];
                location_content = main->parameters.array[fss_extended_write_parameter_content_e].locations.array[main->parameters.array[fss_extended_write_parameter_content_e].locations.used - 1];
                location_sub_object = main->parameters.array[fss_extended_write_parameter_object_e].locations_sub.array[main->parameters.array[fss_extended_write_parameter_object_e].locations_sub.used - 1];
                location_sub_content = main->parameters.array[fss_extended_write_parameter_content_e].locations_sub.array[main->parameters.array[fss_extended_write_parameter_content_e].locations_sub.used - 1];

                if (location_object > location_content || location_object == location_content && location_sub_object > location_sub_content) {
                  if (main->error.verbosity != f_console_verbosity_quiet_e) {
                    flockfile(main->error.to.stream);

                    fl_print_format("%r%[%QEach '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
                    fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_extended_write_long_object_s, main->error.notable);
                    fl_print_format("%[' parameter must have at least one '%]", main->error.to.stream, main->error.context, main->error.context);
                    fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_extended_write_long_content_s, main->error.notable);
                    fl_print_format("%[' parameter.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

                    funlockfile(main->error.to.stream);
                  }

                  status = F_status_set_error(F_parameter);
                }
              }
            }
          }
        }
        else if (main->parameters.array[fss_extended_write_parameter_content_e].locations.used) {
          if (!main->parameters.array[fss_extended_write_parameter_partial_e].locations.used) {
            fss_extended_write_error_parameter_same_times_at_least_print(main);
            status = F_status_set_error(F_parameter);
          }
        }
      }
      else if (!main->process_pipe) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%r%[%QThis requires either piped data or the use of the '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_extended_write_long_object_s, main->error.notable);
          fl_print_format("%[' parameter with the '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_extended_write_long_content_s, main->error.notable);
          fl_print_format("%[' parameter.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && main->process_pipe) {
        if (main->parameters.array[fss_extended_write_parameter_partial_e].result == f_console_result_found_e) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%r%[%QThis '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_extended_write_long_partial_s, main->error.notable);
            fl_print_format("%[' parameter cannot be used when processing a pipe.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }

          status = F_status_set_error(F_parameter);
        }
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_extended_write_parameter_prepend_e].result == f_console_result_found_e) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_extended_write_long_prepend_s, main->error.notable);
          fl_print_format("%[' is specified, but no value is given.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters.array[fss_extended_write_parameter_prepend_e].result == f_console_result_additional_e) {
        const f_array_length_t index = main->parameters.array[fss_extended_write_parameter_prepend_e].values.array[main->parameters.array[fss_extended_write_parameter_prepend_e].values.used - 1];

        // Even though this standard does not utilize this parameter, provide the validation for consistency.
        if (argv[index].used) {
          f_string_range_t range = macro_f_string_range_t_initialize2(argv[index].used);
          f_state_t state = f_state_t_initialize;

          for (; range.start < argv[index].used; ++range.start) {

            status = f_fss_is_space(state, argv[index], range);
            if (F_status_is_error(status)) break;

            if (status == F_false) {
              if (main->error.verbosity != f_console_verbosity_quiet_e) {
                flockfile(main->error.to.stream);

                fl_print_format("%r%[%QThe value for the parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
                fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_extended_write_long_prepend_s, main->error.notable);
                fl_print_format("%[' must only contain white space.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

                funlockfile(main->error.to.stream);
              }

              status = F_status_set_error(F_parameter);

              break;
            }
          } // for
        }
        else {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%r%[%QThe value for the parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_extended_write_long_prepend_s, main->error.notable);
            fl_print_format("%[' must not be an empty string.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }

          status = F_status_set_error(F_parameter);
        }
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_extended_write_parameter_ignore_e].result == f_console_result_found_e) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_extended_write_long_ignore_s, main->error.notable);
          fl_print_format("%[' was specified, but no values were given.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters.array[fss_extended_write_parameter_ignore_e].result == f_console_result_additional_e) {
        const f_array_length_t total_locations = main->parameters.array[fss_extended_write_parameter_ignore_e].locations.used;
        const f_array_length_t total_arguments = main->parameters.array[fss_extended_write_parameter_ignore_e].values.used;

        if (total_locations * 2 > total_arguments) {
          flockfile(main->error.to.stream);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_extended_write_long_ignore_s, main->error.notable);
          fl_print_format("%[' requires two values.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);

          status = F_status_set_error(F_parameter);
        }
      }
    }

    f_fss_quote_t quote = f_fss_quote_type_double_e;

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_extended_write_parameter_double_e].result == f_console_result_found_e) {
        if (main->parameters.array[fss_extended_write_parameter_single_e].result == f_console_result_found_e) {
          if (main->parameters.array[fss_extended_write_parameter_double_e].location < main->parameters.array[fss_extended_write_parameter_single_e].location) {
            quote = f_fss_quote_type_single_e;
          }
        }
      }
      else if (main->parameters.array[fss_extended_write_parameter_single_e].result == f_console_result_found_e) {
        quote = f_fss_quote_type_single_e;
      }
    }

    f_string_dynamic_t buffer = f_string_dynamic_t_initialize;
    f_string_dynamics_t contents = f_string_dynamics_t_initialize;

    if (F_status_is_error_not(status)) {
      f_string_dynamic_t escaped = f_string_dynamic_t_initialize;

      if (main->process_pipe) {
        status = fss_extended_write_process_pipe(main, output, quote, &buffer);

        if (F_status_is_error(status)) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%r%[%QWhile processing the '%]%[input pipe%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context, main->error.notable, main->error.notable);
            fl_print_format("%['.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }
        }
      }

      if (F_status_is_error_not(status)) {
        if (main->parameters.array[fss_extended_write_parameter_partial_e].result == f_console_result_found_e) {
          if (main->parameters.array[fss_extended_write_parameter_object_e].result == f_console_result_additional_e) {
            contents.used = 0;

            for (f_array_length_t i = 0; i < main->parameters.array[fss_extended_write_parameter_object_e].values.used; ++i) {

              if (!((++main->signal_check) % fss_extended_write_signal_check_d)) {
                if (fll_program_standard_signal_received(main)) {
                  fss_extended_write_print_signal_received(main);

                  status = F_status_set_error(F_interrupt);

                  break;
                }

                main->signal_check = 0;
              }

              status = fss_extended_write_process(main, output, quote, &argv[main->parameters.array[fss_extended_write_parameter_object_e].values.array[i]], 0, &buffer);
              if (F_status_is_error(status)) break;
            } // for
          }
          else {
            status = f_string_dynamics_increase_by(main->parameters.array[fss_extended_write_parameter_content_e].values.used, &contents);

            if (status == F_array_too_large) {
              status = F_status_set_error(status);
            }

            if (F_status_is_error(status)) {
              fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamics_increase_by", F_true);
            }
            else {
              f_array_length_t i = 0;

              for (; i < main->parameters.array[fss_extended_write_parameter_content_e].values.used; ++i) {

                contents.array[contents.used++] = argv[main->parameters.array[fss_extended_write_parameter_content_e].values.array[i]];
              } // for

              status = fss_extended_write_process(main, output, quote, 0, &contents, &buffer);
            }
          }
        }
        else {
          f_array_length_t i = 0;
          f_array_length_t j = 0;
          f_array_length_t object_current = 0;
          f_array_length_t object_next = 0;
          f_array_length_t content_current = 0;

          for (; i < main->parameters.array[fss_extended_write_parameter_object_e].values.used; ++i) {

            if (!((++main->signal_check) % fss_extended_write_signal_check_d)) {
              if (fll_program_standard_signal_received(main)) {
                fss_extended_write_print_signal_received(main);

                status = F_status_set_error(F_interrupt);

                break;
              }

              main->signal_check = 0;
            }

            object_current = main->parameters.array[fss_extended_write_parameter_object_e].locations.array[i];

            if (i + 1 < main->parameters.array[fss_extended_write_parameter_object_e].values.used) {
              object_next = main->parameters.array[fss_extended_write_parameter_object_e].locations.array[i + 1];
            }

            contents.used = 0;

            for (; j < main->parameters.array[fss_extended_write_parameter_content_e].values.used; ++j) {

              content_current = main->parameters.array[fss_extended_write_parameter_content_e].locations.array[j];

              if (i + 1 < main->parameters.array[fss_extended_write_parameter_object_e].values.used) {
                if (content_current < object_current || content_current >= object_next) break;
              }

              status = f_string_dynamics_increase_by(F_fss_default_allocation_step_d, &contents);

              if (F_status_is_error(status)) {
                fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamics_increase_by", F_true);

                break;
              }

              if (contents.array[contents.used].used) {
                contents.array[contents.used].used = 0;
              }

              status = f_string_dynamic_append(argv[main->parameters.array[fss_extended_write_parameter_content_e].values.array[j]], &contents.array[contents.used]);

              if (F_status_is_error(status)) {
                fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);

                break;
              }

              ++contents.used;
            } // for

            if (F_status_is_error(status)) break;

            status = fss_extended_write_process(main, output, quote, &argv[main->parameters.array[fss_extended_write_parameter_object_e].values.array[i]], &contents, &buffer);
            if (F_status_is_error(status)) break;
          } // for
        }

        if (F_status_is_error(status)) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%r%[%QWhile processing the '%]%[input arguments%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context, main->error.notable, main->error.notable);
            fl_print_format("%['.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }
        }
        else if (main->error.verbosity != f_console_verbosity_quiet_e && main->error.verbosity != f_console_verbosity_error_e && main->parameters.array[fss_extended_write_parameter_file_e].result == f_console_result_none_e) {

          // Ensure there is always a newline at the end, unless in quiet mode.
          fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
        }
      }

      f_string_dynamic_resize(0, &escaped);
    }

    if (main->parameters.array[fss_extended_write_parameter_file_e].result == f_console_result_additional_e) {
      if (output.id != -1) {
        f_file_stream_close(F_true, &output);
      }
    }

    // Ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (main->error.verbosity != f_console_verbosity_quiet_e) {
      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_interrupt) {
          fflush(main->output.to.stream);
        }

        fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
      }
    }

    f_string_dynamic_resize(0, &buffer);
    f_string_dynamics_resize(0, &contents);

    return status;
  }
#endif // _di_fss_extended_write_main_

#ifdef __cplusplus
} // extern "C"
#endif
