#include "fss_embedded_list_write.h"
#include "private-common.h"
#include "private-write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_embedded_list_write_program_version_
  const f_string_static_t fss_embedded_list_write_program_version_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_program_version_s, 0, FSS_EMBEDDED_LIST_WRITE_program_version_s_length);
#endif // _di_fss_embedded_list_write_program_version_

#ifndef _di_fss_embedded_list_write_program_name_
  const f_string_static_t fss_embedded_list_write_program_name_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_program_name_s, 0, FSS_EMBEDDED_LIST_WRITE_program_name_s_length);
  const f_string_static_t fss_embedded_list_write_program_name_long_s = macro_f_string_static_t_initialize(FSS_EMBEDDED_LIST_WRITE_program_name_long_s, 0, FSS_EMBEDDED_LIST_WRITE_program_name_long_s_length);
#endif // _di_fss_embedded_list_write_program_name_

#ifndef _di_fss_embedded_list_write_print_help_
  f_status_t fss_embedded_list_write_print_help(const f_file_t file, const f_color_context_t context) {

    flockfile(file.stream);

    fll_program_print_help_header(file, context, fss_embedded_list_write_program_name_long_s, fss_embedded_list_write_program_version_s);

    fll_program_print_help_option(file, context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print this help message.");
    fll_program_print_help_option(file, context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Do not file in color.");
    fll_program_print_help_option(file, context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity, silencing most output.");
    fll_program_print_help_option(file, context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Set verbosity to normal file.");
    fll_program_print_help_option(file, context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Enable debugging, significantly increasing verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Print only the version number.");

    f_print_dynamic(f_string_eol_s, file.stream);

    fll_program_print_help_option(file, context, fss_embedded_list_write_short_file_s, fss_embedded_list_write_long_file_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Specify a file to send data to.");
    fll_program_print_help_option(file, context, fss_embedded_list_write_short_content_s, fss_embedded_list_write_long_content_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "The Content to file.");
    fll_program_print_help_option(file, context, fss_embedded_list_write_short_double_s, fss_embedded_list_write_long_double_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Use double quotes (default).");
    fll_program_print_help_option(file, context, fss_embedded_list_write_short_ignore_s, fss_embedded_list_write_long_ignore_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Ignore a given range within a Content.");
    fll_program_print_help_option(file, context, fss_embedded_list_write_short_object_s, fss_embedded_list_write_long_object_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " The Object to file.");
    fll_program_print_help_option(file, context, fss_embedded_list_write_short_partial_s, fss_embedded_list_write_long_partial_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Do not file end of Object/Content character.");
    fll_program_print_help_option(file, context, fss_embedded_list_write_short_prepend_s, fss_embedded_list_write_long_prepend_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Prepend the given whitespace characters to the start of each multi-line Content.");
    fll_program_print_help_option(file, context, fss_embedded_list_write_short_single_s, fss_embedded_list_write_long_single_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Use single quotes.");
    fll_program_print_help_option(file, context, fss_embedded_list_write_short_trim_s, fss_embedded_list_write_long_trim_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Trim Object names.");

    fll_program_print_help_usage(file, context, fss_embedded_list_write_program_name_s, f_string_empty_s);

    fl_print_format("  The pipe uses the Backspace character '%[\\b%]' (%[U+0008%]) to designate the start of a Content.%q", file.stream, context.set.notable, context.set.notable, context.set.notable, context.set.notable, f_string_eol_s);
    fl_print_format("  The pipe uses the Form Feed character '%[\\f%]' (%[U+000C%]) to designate the end of the last Content.%q", file.stream, context.set.notable, context.set.notable, context.set.notable, context.set.notable, f_string_eol_s);
    fl_print_format("  The pipe uses the Vertical Line character '%[\\v%]' (%[U+000B%]) is used to ignore a Content range (use this both before and after the range).%q", file.stream, context.set.notable, context.set.notable, context.set.notable, context.set.notable, f_string_eol_s);
    fl_print_format("  For the pipe, an Object is terminated by either a Backspace character '%[\\b%]' (%[U+0008%])", file.stream, context.set.notable, context.set.notable, context.set.notable, context.set.notable);
    fl_print_format(" or a Form Feed character '%[\\f%]' (%[U+000C%]).%q", file.stream, context.set.notable, context.set.notable, context.set.notable, context.set.notable, f_string_eol_s);
    fl_print_format("  The end of the pipe represents the end of any Object or Content.%q%q", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The FSS-0008 (Embedded List) specification does not support quoted names, therefore the parameters '%[%q%s%]'", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_write_long_single_s, context.set.notable);
    fl_print_format(" and '%[%q%s%]' do nothing.%q%q", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_write_long_double_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The parameter '%[%q%s%]' designates to not escape any valid nested Object or Content within some Content.%q", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_write_long_ignore_s, context.set.notable, f_string_eol_s);
    fl_print_format("  This parameter requires two values.%q", file.stream, f_string_eol_s);
    fl_print_format("  This parameter is not used for ignoring anything from the input pipe.%q", file.stream, f_string_eol_s);
    fl_print_format("  This parameter must be specified after a '%[%q%s%]'", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_write_long_content_s, context.set.notable);
    fl_print_format(" parameter and this applies only to the Content represented by that specific '%[%q%s%]' parameter.%q%q", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_embedded_list_write_long_content_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_fss_embedded_list_write_print_help_

#ifndef _di_fss_embedded_list_write_main_
  f_status_t fss_embedded_list_write_main(fss_embedded_list_write_main_t * const main, const f_console_arguments_t *arguments) {

    f_status_t status = F_none;

    f_console_parameter_t parameters[] = fss_embedded_list_write_console_parameter_t_initialize;
    main->parameters.array = parameters;
    main->parameters.used = fss_embedded_list_write_total_parameters_d;

    {
      f_console_parameter_id_t ids[3] = { fss_embedded_list_write_parameter_no_color_e, fss_embedded_list_write_parameter_light_e, fss_embedded_list_write_parameter_dark_e };
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
        fss_embedded_list_write_main_delete(main);

        return F_status_set_error(status);
      }
    }

    // Identify priority of verbosity related parameters.
    {
      f_console_parameter_id_t ids[4] = { fss_embedded_list_write_parameter_verbosity_quiet_e, fss_embedded_list_write_parameter_verbosity_normal_e, fss_embedded_list_write_parameter_verbosity_verbose_e, fss_embedded_list_write_parameter_verbosity_debug_e };
      f_console_parameter_id_t choice = 0;
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        fss_embedded_list_write_main_delete(main);

        return status;
      }

      if (choice == fss_embedded_list_write_parameter_verbosity_quiet_e) {
        main->output.verbosity = f_console_verbosity_quiet_e;
        main->error.verbosity = f_console_verbosity_quiet_e;
        main->warning.verbosity = f_console_verbosity_quiet_e;
      }
      else if (choice == fss_embedded_list_write_parameter_verbosity_normal_e) {
        main->output.verbosity = f_console_verbosity_normal_e;
        main->error.verbosity = f_console_verbosity_normal_e;
        main->warning.verbosity = f_console_verbosity_normal_e;
      }
      else if (choice == fss_embedded_list_write_parameter_verbosity_verbose_e) {
        main->output.verbosity = f_console_verbosity_verbose_e;
        main->error.verbosity = f_console_verbosity_verbose_e;
        main->warning.verbosity = f_console_verbosity_verbose_e;
      }
      else if (choice == fss_embedded_list_write_parameter_verbosity_debug_e) {
        main->output.verbosity = f_console_verbosity_debug_e;
        main->error.verbosity = f_console_verbosity_debug_e;
        main->warning.verbosity = f_console_verbosity_debug_e;
      }
    }

    f_string_static_t * const argv = main->parameters.arguments.array;

    status = F_none;

    if (main->parameters.array[fss_embedded_list_write_parameter_help_e].result == f_console_result_found_e) {
      fss_embedded_list_write_print_help(main->output.to, main->context);

      fss_embedded_list_write_main_delete(main);

      return status;
    }

    if (main->parameters.array[fss_embedded_list_write_parameter_version_e].result == f_console_result_found_e) {
      fll_program_print_version(main->output.to, fss_embedded_list_write_program_version_s);

      fss_embedded_list_write_main_delete(main);

      return status;
    }

    f_file_t output = f_file_t_initialize;

    output.id = F_type_descriptor_output_d;
    output.stream = F_type_output_d;
    output.flag = F_file_flag_create_d | F_file_flag_write_only_d | F_file_flag_append_d;

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_embedded_list_write_parameter_file_e].result == f_console_result_additional_e) {
        if (main->parameters.array[fss_embedded_list_write_parameter_file_e].values.used > 1) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%q%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_write_long_file_s, main->error.notable);
            fl_print_format("%[' may only be specified once.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }

          status = F_status_set_error(F_parameter);
        }
        else {
          const f_array_length_t location = main->parameters.array[fss_embedded_list_write_parameter_file_e].values.array[0];

          output.id = -1;
          output.stream = 0;
          status = f_file_stream_open(arguments->argv[location], 0, &output);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_open", F_true, arguments->argv[location], f_file_operation_open_s, fll_error_file_type_file_e);
          }
        }
      }
      else if (main->parameters.array[fss_embedded_list_write_parameter_file_e].result == f_console_result_found_e) {
        fss_embedded_list_write_error_parameter_value_missing_print(main, f_console_symbol_long_enable_s.string.string, fss_embedded_list_write_long_file_s);
        status = F_status_set_error(F_parameter);
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_embedded_list_write_parameter_object_e].locations.used || main->parameters.array[fss_embedded_list_write_parameter_content_e].locations.used) {
        if (main->parameters.array[fss_embedded_list_write_parameter_object_e].locations.used) {
          if (main->parameters.array[fss_embedded_list_write_parameter_object_e].locations.used != main->parameters.array[fss_embedded_list_write_parameter_object_e].values.used) {
            fss_embedded_list_write_error_parameter_value_missing_print(main, f_console_symbol_long_enable_s, fss_embedded_list_write_long_object_s);
            status = F_status_set_error(F_parameter);
          }
          else if (main->parameters.array[fss_embedded_list_write_parameter_content_e].locations.used != main->parameters.array[fss_embedded_list_write_parameter_content_e].values.used) {
            fss_embedded_list_write_error_parameter_value_missing_print(main, f_console_symbol_long_enable_s, fss_embedded_list_write_long_content_s);
            status = F_status_set_error(F_parameter);
          }
          else if (main->parameters.array[fss_embedded_list_write_parameter_object_e].locations.used != main->parameters.array[fss_embedded_list_write_parameter_content_e].locations.used && main->parameters.array[fss_embedded_list_write_parameter_partial_e].result == f_console_result_none_e) {
            fss_embedded_list_write_error_parameter_same_times_print(main);
            status = F_status_set_error(F_parameter);
          }
          else if (main->parameters.array[fss_embedded_list_write_parameter_content_e].locations.used && main->parameters.array[fss_embedded_list_write_parameter_partial_e].locations.used) {
            if (main->parameters.array[fss_embedded_list_write_parameter_content_e].result == f_console_result_additional_e) {
              if (main->error.verbosity != f_console_verbosity_quiet_e) {
                flockfile(main->error.to.stream);

                fl_print_format("%q%[%QThe '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
                fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_write_long_partial_s, main->error.notable);
                fl_print_format("%[' parameter only allows either the '%]", main->error.to.stream, main->error.context, main->error.context);
                fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_write_long_object_s, main->error.notable);
                fl_print_format("%[' parameter or the '%]", main->error.to.stream, main->error.context, main->error.context);
                fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_write_long_content_s, main->error.notable);
                fl_print_format("%[' parameter, but not both.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

                funlockfile(main->error.to.stream);
              }

              status = F_status_set_error(F_parameter);
            }
          }

          if (F_status_is_error_not(status)) {
            if (main->parameters.array[fss_embedded_list_write_parameter_content_e].result == f_console_result_additional_e) {
              f_array_length_t location_object = 0;
              f_array_length_t location_content = 0;
              f_array_length_t location_sub_object = 0;
              f_array_length_t location_sub_content = 0;

              for (f_array_length_t i = 0; i < main->parameters.array[fss_embedded_list_write_parameter_object_e].locations.used; ++i) {
                location_object = main->parameters.array[fss_embedded_list_write_parameter_object_e].locations.array[i];
                location_content = main->parameters.array[fss_embedded_list_write_parameter_content_e].locations.array[i];
                location_sub_object = main->parameters.array[fss_embedded_list_write_parameter_object_e].locations_sub.array[i];
                location_sub_content = main->parameters.array[fss_embedded_list_write_parameter_content_e].locations_sub.array[i];

                if (location_object > location_content || location_object == location_content && location_sub_object > location_sub_content) {
                  if (main->error.verbosity != f_console_verbosity_quiet_e) {
                    flockfile(main->error.to.stream);

                    fl_print_format("%q%[%QEach '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
                    fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_write_long_object_s, main->error.notable);
                    fl_print_format("%[' parameter must be specified before a '%]", main->error.to.stream, main->error.context, main->error.context);
                    fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_write_long_content_s, main->error.notable);
                    fl_print_format("%[' parameter.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

                    funlockfile(main->error.to.stream);
                  }

                  status = F_status_set_error(F_parameter);

                  break;
                }
              } // for
            }
          }
        }
        else if (main->parameters.array[fss_embedded_list_write_parameter_content_e].locations.used) {
          if (main->parameters.array[fss_embedded_list_write_parameter_content_e].locations.used != main->parameters.array[fss_embedded_list_write_parameter_content_e].values.used) {
            fss_embedded_list_write_error_parameter_value_missing_print(main, f_console_symbol_long_enable_s, fss_embedded_list_write_long_content_s);
            status = F_status_set_error(F_parameter);
          }
          else if (!main->parameters.array[fss_embedded_list_write_parameter_partial_e].locations.used) {
            fss_embedded_list_write_error_parameter_same_times_print(main);
            status = F_status_set_error(F_parameter);
          }
        }
      }
      else if (!main->process_pipe) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%q%[%QThis requires either piped data or the use of the '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_write_long_object_s, main->error.notable);
          fl_print_format("%[' parameter with the '%]", main->error.to.stream, main->error.context, main->error.context);
          fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_write_long_content_s, main->error.notable);
          fl_print_format("%[' parameter.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }

        status = F_status_set_error(F_parameter);
      }

      if (F_status_is_error_not(status) && main->process_pipe) {
        if (main->parameters.array[fss_embedded_list_write_parameter_partial_e].result == f_console_result_found_e) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%q%[%QThis '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_write_long_partial_s, main->error.notable);
            fl_print_format("%[' parameter cannot be used when processing a pipe.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }

          status = F_status_set_error(F_parameter);
        }
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_embedded_list_write_parameter_prepend_e].result == f_console_result_found_e) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%q%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_write_long_prepend_s, main->error.notable);
          fl_print_format("%[' is specified, but no value is given.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters.array[fss_embedded_list_write_parameter_prepend_e].result == f_console_result_additional_e) {
        const f_array_length_t index = main->parameters.array[fss_embedded_list_write_parameter_prepend_e].values.array[main->parameters.array[fss_embedded_list_write_parameter_prepend_e].values.used - 1];
        const f_array_length_t length = strnlen(arguments->argv[index], F_console_parameter_size_d);

        if (length) {
          f_string_range_t range = macro_f_string_range_t_initialize(length);

          main->prepend.string = arguments->argv[index];
          main->prepend.used = length;
          main->prepend.size = length;

          for (; range.start < length; ++range.start) {

            status = f_fss_is_space(main->prepend, range);
            if (F_status_is_error(status)) break;

            if (status == F_false) {
              if (main->error.verbosity != f_console_verbosity_quiet_e) {
                flockfile(main->error.to.stream);

                fl_print_format("%q%[%QThe value for the parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
                fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_write_long_prepend_s, main->error.notable);
                fl_print_format("%[' must only contain whitespace.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

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

            fl_print_format("%q%[%QThe value for the parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_write_long_prepend_s, main->error.notable);
            fl_print_format("%[' must not be an empty string.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }

          status = F_status_set_error(F_parameter);
        }
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_embedded_list_write_parameter_ignore_e].result == f_console_result_found_e) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%q%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_write_long_ignore_s, main->error.notable);
          fl_print_format("%[' was specified, but no values were given.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters.array[fss_embedded_list_write_parameter_ignore_e].result == f_console_result_additional_e) {
        const f_array_length_t total_locations = main->parameters.array[fss_embedded_list_write_parameter_ignore_e].locations.used;
        const f_array_length_t total_arguments = main->parameters.array[fss_embedded_list_write_parameter_ignore_e].values.used;

        if (total_locations * 2 > total_arguments) {
          flockfile(main->error.to.stream);

          fl_print_format("%q%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%q%q%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_write_long_ignore_s, main->error.notable);
          fl_print_format("%[' requires two values.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);

          status = F_status_set_error(F_parameter);
        }
      }
    }

    f_fss_quote_t quote = F_fss_delimit_quote_double_s;

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_embedded_list_write_parameter_double_e].result == f_console_result_found_e) {
        if (main->parameters.array[fss_embedded_list_write_parameter_single_e].result == f_console_result_found_e) {
          if (main->parameters.array[fss_embedded_list_write_parameter_double_e].location < main->parameters.array[fss_embedded_list_write_parameter_single_e].location) {
            quote = F_fss_delimit_quote_single_s;
          }
        }
      }
      else if (main->parameters.array[fss_embedded_list_write_parameter_single_e].result == f_console_result_found_e) {
        quote = F_fss_delimit_quote_single_s;
      }
    }

    f_string_dynamic_t buffer = f_string_dynamic_t_initialize;
    f_string_dynamic_t object = f_string_dynamic_t_initialize;
    f_string_dynamic_t content = f_string_dynamic_t_initialize;

    if (F_status_is_error_not(status)) {
      f_string_dynamic_t escaped = f_string_dynamic_t_initialize;
      f_string_ranges_t ignore = f_string_ranges_t_initialize;

      if (main->process_pipe) {
        status = fss_embedded_list_write_process_pipe(main, output, quote, &buffer, &ignore);

        if (F_status_is_error(status) && F_status_set_fine(status) != F_interrupt) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%q%[%QWhile processing the '%]%[input pipe%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context, main->error.notable, main->error.notable);
            fl_print_format("%['.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }
        }

        ignore.used = 0;
      }

      if (F_status_is_error_not(status)) {
        if (main->parameters.array[fss_embedded_list_write_parameter_partial_e].result == f_console_result_found_e) {

          if (main->parameters.array[fss_embedded_list_write_parameter_object_e].result == f_console_result_additional_e) {
            for (f_array_length_t i = 0; i < main->parameters.array[fss_embedded_list_write_parameter_object_e].values.used; ++i) {

              if (fss_embedded_list_write_signal_received(main)) {
                status = F_status_set_error(F_interrupt);

                break;
              }

              object.string = arguments->argv[main->parameters.array[fss_embedded_list_write_parameter_object_e].values.array[i]];
              object.used = strnlen(object.string, F_console_parameter_size_d);
              object.size = object.used;

              status = fss_embedded_list_write_process(main, output, quote, &object, 0, 0, &buffer);
              if (F_status_is_error(status)) break;
            } // for
          }
          else {
            for (f_array_length_t i = 0; i < main->parameters.array[fss_embedded_list_write_parameter_content_e].values.used; ++i) {

              if (fss_embedded_list_write_signal_received(main)) {
                status = F_status_set_error(F_interrupt);

                break;
              }

              status = fss_embedded_list_write_process_parameter_ignore(main, arguments, main->parameters.array[fss_embedded_list_write_parameter_content_e].locations, i, &ignore);
              if (F_status_is_error(status)) break;

              content.string = arguments->argv[main->parameters.array[fss_embedded_list_write_parameter_content_e].values.array[i]];
              content.used = strnlen(content.string, F_console_parameter_size_d);
              content.size = content.used;

              status = fss_embedded_list_write_process(main, output, quote, 0, &content, &ignore, &buffer);
              if (F_status_is_error(status)) break;
            } // for
          }
        }
        else {
          for (f_array_length_t i = 0; i < main->parameters.array[fss_embedded_list_write_parameter_object_e].values.used; ++i) {

            if (fss_embedded_list_write_signal_received(main)) {
              status = F_status_set_error(F_interrupt);

              break;
            }

            status = fss_embedded_list_write_process_parameter_ignore(main, arguments, main->parameters.array[fss_embedded_list_write_parameter_content_e].locations, i, &ignore);
            if (F_status_is_error(status)) break;

            object.string = arguments->argv[main->parameters.array[fss_embedded_list_write_parameter_object_e].values.array[i]];
            object.used = strnlen(object.string, F_console_parameter_size_d);
            object.size = object.used;

            content.string = arguments->argv[main->parameters.array[fss_embedded_list_write_parameter_content_e].values.array[i]];
            content.used = strnlen(content.string, F_console_parameter_size_d);
            content.size = content.used;

            status = fss_embedded_list_write_process(main, output, quote, &object, &content, &ignore, &buffer);
            if (F_status_is_error(status)) break;
          } // for
        }

        if (F_status_is_error(status)) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%q%[%QWhile processing the '%]%[input arguments%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context, main->error.notable, main->error.notable);
            fl_print_format("%['.%]%q", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }
        }
        else if (main->error.verbosity != f_console_verbosity_quiet_e && main->parameters.array[fss_embedded_list_write_parameter_file_e].result == f_console_result_none_e) {

          // Ensure there is always a newline at the end, unless in quiet mode.
          fll_print_dynamic(f_string_eol_s, main->output.to.stream);
        }
      }

      f_string_dynamic_resize(0, &escaped);
      macro_f_string_ranges_t_delete_simple(ignore);

      // Object and content, though being a "dynamic" type, is being used statically, so clear them up to avoid invalid free().
      object.string = 0;
      object.used = 0;
      object.size = 0;

      content.string = 0;
      content.used = 0;
      content.size = 0;
    }

    if (main->parameters.array[fss_embedded_list_write_parameter_file_e].result == f_console_result_additional_e) {
      if (output.id != -1) {
        f_file_stream_close(F_true, &output);
      }
    }

    // Ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (main->error.verbosity != f_console_verbosity_quiet_e) {
      if (F_status_is_error(status)) {
        fll_print_dynamic(f_string_eol_s, main->error.to.stream);
      }
    }

    f_string_dynamic_resize(0, &buffer);
    f_string_dynamic_resize(0, &object);
    f_string_dynamic_resize(0, &content);
    fss_embedded_list_write_main_delete(main);

    return status;
  }
#endif // _di_fss_embedded_list_write_main_

#ifndef _di_fss_embedded_list_write_main_delete_
  f_status_t fss_embedded_list_write_main_delete(fss_embedded_list_write_main_t * const main) {

    f_console_parameters_delete(&main->parameters);

    f_type_array_lengths_resize(0, &main->remaining);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_fss_embedded_list_write_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif
