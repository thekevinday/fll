#include "fss_identify.h"
#include "private-common.h"
#include "private-fss_identify.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_identify_print_help_
  f_status_t fss_identify_print_help(const f_file_t file, const f_color_context_t context) {

    flockfile(file.stream);

    fll_program_print_help_header(file, context, fss_identify_program_name_long_s, fss_identify_program_version);

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

    fll_program_print_help_option(file, context, fss_identify_short_content_s, fss_identify_long_content_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Print the Identifier content (the 4-digit hexidecimal type code).");
    fll_program_print_help_option(file, context, fss_identify_short_object_s, fss_identify_long_object_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Print the Identifier object (the name).");

    f_print_character(f_string_eol_s[0], file.stream);

    fll_program_print_help_option(file, context, fss_identify_short_line_s, fss_identify_long_line_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Print only the Identifier at the given line.");
    fll_program_print_help_option(file, context, fss_identify_short_name_s, fss_identify_long_name_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Select Object with this name.");
    fll_program_print_help_option(file, context, fss_identify_short_total_s, fss_identify_long_total_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Print the total Identifiers found.");

    fll_program_print_help_usage(file, context, fss_identify_program_name_s, "filename(s)");

    fl_print_format("  The %[%s%s%] parameter refers to the file lines and not the lines in a given file.%c%c", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_identify_long_line_s, context.set.notable, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  If neither the %[%s%s%] nor", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_identify_long_object_s, context.set.notable);
    fl_print_format(" %[%s%s%] are specified, then the default behavior is to print both.%c%c", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_identify_long_content_s, context.set.notable, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  When specifying the %[%s%s%] parameter, neither the", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_identify_long_total_s, context.set.notable);
    fl_print_format(" %[%s%s%] nor the", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_identify_long_object_s, context.set.notable);
    fl_print_format(" %[%s%s%] parameter may be specified.%c%c", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_identify_long_content_s, context.set.notable, f_string_eol_s[0], f_string_eol_s[0]);

    fl_print_format("  An FSS file is identified by the following format: '%[# Object-Content%]'", file.stream, context.set.notable, context.set.notable);
    fl_print_format(" where the Object, is a machine-name representing the name and may only consist of \"word\" characters and the Content is a 4-digit hexidecimal number representing a particular variant of the Object.%c", file.stream, f_string_eol_s[0]);
    fl_print_format("  This identifier, if provided, must exist on the first line in a file and must begin with the pound character: '#'.%c", file.stream, f_string_eol_s[0]);
    fl_print_format("  Whitespace must follow this pound character.%c", file.stream, f_string_eol_s[0]);
    fl_print_format("  There may be multiple Object and Content pairs, separated by whitspace, such as: \"# fss-0002 fss-0000 iki-0002\".%c%c", file.stream, f_string_eol_s[0], f_string_eol_s[0]);

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_fss_identify_print_help_

#ifndef _di_fss_identify_main_
  f_status_t fss_identify_main(const f_console_arguments_t arguments, fss_identify_main_t *main) {
    f_status_t status = F_none;

    {
      const f_console_parameters_t parameters = macro_f_console_parameters_t_initialize(main->parameters, fss_identify_total_parameters_d);

      {
        f_console_parameter_id_t ids[3] = { fss_identify_parameter_no_color, fss_identify_parameter_light, fss_identify_parameter_dark };
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

        status = fll_program_parameter_process(arguments, parameters, choices, F_true, &main->remaining, &main->context);

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
          if (main->error.verbosity != f_console_verbosity_quiet) {
            fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process", F_true);
            fll_print_character(f_string_eol_s[0], main->error.to.stream);
          }

          fss_identify_main_delete(main);

          return F_status_set_error(status);
        }
      }

      // Identify priority of verbosity related parameters.
      {
        f_console_parameter_id_t ids[4] = { fss_identify_parameter_verbosity_quiet, fss_identify_parameter_verbosity_normal, fss_identify_parameter_verbosity_verbose, fss_identify_parameter_verbosity_debug };
        f_console_parameter_id_t choice = 0;
        const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);

        status = f_console_parameter_prioritize_right(parameters, choices, &choice);

        if (F_status_is_error(status)) {
          fss_identify_main_delete(main);

          return status;
        }

        if (choice == fss_identify_parameter_verbosity_quiet) {
          main->output.verbosity = f_console_verbosity_quiet;
          main->error.verbosity = f_console_verbosity_quiet;
          main->warning.verbosity = f_console_verbosity_quiet;
        }
        else if (choice == fss_identify_parameter_verbosity_normal) {
          main->output.verbosity = f_console_verbosity_normal;
          main->error.verbosity = f_console_verbosity_normal;
          main->warning.verbosity = f_console_verbosity_normal;
        }
        else if (choice == fss_identify_parameter_verbosity_verbose) {
          main->output.verbosity = f_console_verbosity_verbose;
          main->error.verbosity = f_console_verbosity_verbose;
          main->warning.verbosity = f_console_verbosity_verbose;
        }
        else if (choice == fss_identify_parameter_verbosity_debug) {
          main->output.verbosity = f_console_verbosity_debug;
          main->error.verbosity = f_console_verbosity_debug;
          main->warning.verbosity = f_console_verbosity_debug;
        }
      }

      status = F_none;
    }

    if (main->parameters[fss_identify_parameter_help].result == f_console_result_found) {
      fss_identify_print_help(main->output.to, main->context);

      fss_identify_main_delete(main);

      return F_none;
    }

    if (main->parameters[fss_identify_parameter_version].result == f_console_result_found) {
      fll_program_print_version(main->output.to, fss_identify_program_version);

      fss_identify_main_delete(main);

      return F_none;
    }

    fss_identify_data_t data = fss_identify_data_t_initialize;

    if (F_status_is_error_not(status)) {
      if (main->parameters[fss_identify_parameter_line].result == f_console_result_found) {
        flockfile(main->error.to.stream);

        fl_print_format("%c%[%sThe parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_identify_long_line_s, main->error.notable);
        fl_print_format("%[' requires a positive number.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

        funlockfile(main->error.to.stream);

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters[fss_identify_parameter_line].result == f_console_result_additional) {
        const f_array_length_t index = main->parameters[fss_identify_parameter_line].values.array[main->parameters[fss_identify_parameter_line].values.used - 1];
        const f_string_range_t range = macro_f_string_range_t_initialize(strnlen(arguments.argv[index], f_console_parameter_size));

        status = fl_conversion_string_to_number_unsigned(arguments.argv[index], range, &data.line);

        if (F_status_is_error(status)) {
          fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_identify_long_line_s, arguments.argv[index]);
        }
      }
    }

    if (F_status_is_error_not(status) && main->parameters[fss_identify_parameter_total].result == f_console_result_found) {
      if (main->parameters[fss_identify_parameter_object].result == f_console_result_found) {
        flockfile(main->error.to.stream);

        fl_print_format("%c%[%sCannot specify the '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_identify_long_object_s, main->error.notable);
        fl_print_format("%[' parameter with the '%]", main->error.to.stream, main->error.context, main->error.context);
        fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_identify_long_total_s, main->error.notable);
        fl_print_format("%[' parameter.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

        funlockfile(main->error.to.stream);

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters[fss_identify_parameter_content].result == f_console_result_found) {
        flockfile(main->error.to.stream);

        fl_print_format("%c%[%sCannot specify the '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_identify_long_content_s, main->error.notable);
        fl_print_format("%[' parameter with the '%]", main->error.to.stream, main->error.context, main->error.context);
        fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_identify_long_total_s, main->error.notable);
        fl_print_format("%[' parameter.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

        funlockfile(main->error.to.stream);

        status = F_status_set_error(F_parameter);
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters[fss_identify_parameter_name].result == f_console_result_found) {
        flockfile(main->error.to.stream);

        fl_print_format("%c%[%sThe parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_identify_long_name_s, main->error.notable);
        fl_print_format("%[' requires a string.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

        funlockfile(main->error.to.stream);

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters[fss_identify_parameter_name].result == f_console_result_additional) {
        const f_array_length_t index = main->parameters[fss_identify_parameter_name].values.array[main->parameters[fss_identify_parameter_name].values.used - 1];
        const f_array_length_t length = strnlen(arguments.argv[index], f_console_parameter_size);
        const f_string_range_t range = macro_f_string_range_t_initialize(length);

        if (length == 0) {
          flockfile(main->error.to.stream);

          fl_print_format("%c%[%sThe parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_identify_long_name_s, main->error.notable);
          fl_print_format("%[' does not allow zero length strings.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

          funlockfile(main->error.to.stream);

          status = F_status_set_error(F_parameter);
        }
        else {
          status = f_string_dynamic_resize(length, &data.name);

          if (F_status_is_error(status)) {
            fll_error_print(main->error, F_status_set_fine(status), "f_utf_is_word", F_true);
          }
        }

        if (F_status_is_error_not(status)) {

          for (f_array_length_t i = range.start; i <= range.stop; ++i) {

            status = f_utf_is_word(arguments.argv[index] + i, length, F_true);

            if (F_status_is_error(status)) {
              fll_error_print(main->error, F_status_set_fine(status), "f_utf_is_word", F_true);

              break;
            }
            else if (status == F_false) {
              flockfile(main->error.to.stream);

              fl_print_format("%c%[%sThe value '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
              fl_print_format("%[%S%]", main->error.to.stream, main->error.notable, arguments.argv[index], main->error.notable);
              fl_print_format("%[' for the parameter '%]", main->error.to.stream, main->error.context, main->error.context);
              fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_identify_long_name_s, main->error.notable);
              fl_print_format("%[' may only contain word characters.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

              funlockfile(main->error.to.stream);

              status = F_status_set_error(F_parameter);

              break;
            }

            data.name.string[data.name.used++] = arguments.argv[index][i];
          } // for
        }
      }
    }

    f_string_range_t range = f_string_range_t_initialize;
    f_string_dynamic_t buffer = f_string_dynamic_t_initialize;
    f_file_t file = f_file_t_initialize;

    if (F_status_is_error_not(status) && main->process_pipe) {
      file.id = F_type_descriptor_input_d;
      file.stream = F_type_input_d;
      file.size_read = 512;

      status = fss_identify_load_line(*main, file, "-", &buffer, &range);

      if (F_status_is_error_not(status)) {
        status = fss_identify_process(*main, "-", buffer, &range, &data);
      }
    }

    if (F_status_is_error_not(status)) {

      for (f_array_length_t i = 0; i < main->remaining.used; ++i) {

        if (main->parameters[fss_identify_parameter_line].result == f_console_result_additional) {
          if (data.current > data.line) break;
        }

        macro_f_file_t_reset(file);

        file.size_read = 512;

        status = f_file_stream_open(arguments.argv[main->remaining.array[i]], 0, &file);

        if (F_status_is_error(status)) {
          fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_open", F_true, arguments.argv[main->remaining.array[i]], "open", fll_error_file_type_file);
        }
        else {
          status = fss_identify_load_line(*main, file, arguments.argv[main->remaining.array[i]], &buffer, &range);

          if (F_status_is_error_not(status)) {
            status = fss_identify_process(*main, arguments.argv[main->remaining.array[i]], buffer, &range, &data);
          }
        }

        f_file_stream_close(F_true, &file);

        if (F_status_is_error(status)) break;
      } // for
    }

    f_string_dynamic_resize(0, &buffer);

    if (F_status_is_error_not(status)) {
      if (main->parameters[fss_identify_parameter_total].result == f_console_result_found) {
        fll_print_format("%ul%c", main->output.to.stream, data.total, f_string_eol_s[0]);
      }
    }

    // ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (main->error.verbosity != f_console_verbosity_quiet) {
      if (F_status_is_error(status)) {
        fll_print_character(f_string_eol_s[0], main->error.to.stream);
      }
    }

    fss_identify_data_delete(&data);
    fss_identify_main_delete(main);

    return status;
  }
#endif // _di_fss_identify_main_

#ifndef _di_fss_identify_main_delete_
  f_status_t fss_identify_main_delete(fss_identify_main_t *main) {

    for (f_array_length_t i = 0; i < fss_identify_total_parameters_d; ++i) {

      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].locations_sub);
      macro_f_array_lengths_t_delete_simple(main->parameters[i].values);
    } // for

    macro_f_array_lengths_t_delete_simple(main->remaining);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_fss_identify_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif
