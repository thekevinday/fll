#include "fss_identify.h"
#include "private-common.h"
#include "private-identify.h"

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

    f_print_dynamic_raw(f_string_eol_s, file.stream);

    fll_program_print_help_option(file, context, fss_identify_short_content_s, fss_identify_long_content_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Print the Identifier content (the 4-digit hexidecimal type code).");
    fll_program_print_help_option(file, context, fss_identify_short_object_s, fss_identify_long_object_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Print the Identifier object (the name).");

    f_print_dynamic_raw(f_string_eol_s, file.stream);

    fll_program_print_help_option(file, context, fss_identify_short_line_s, fss_identify_long_line_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Print only the Identifier at the given line.");
    fll_program_print_help_option(file, context, fss_identify_short_name_s, fss_identify_long_name_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Select Object with this name.");
    fll_program_print_help_option(file, context, fss_identify_short_total_s, fss_identify_long_total_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Print the total Identifiers found.");

    fll_program_print_help_usage(file, context, fss_identify_program_name_s, fll_program_parameter_filenames_s);

    fl_print_format("  The %[%r%r%] parameter refers to the file lines and not the lines in a given file.%r%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_identify_long_line_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  If neither the %[%r%r%] nor", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_identify_long_object_s, context.set.notable);
    fl_print_format(" %[%r%r%] are specified, then the default behavior is to print both.%r%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_identify_long_content_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When specifying the %[%r%r%] parameter, neither the", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_identify_long_total_s, context.set.notable);
    fl_print_format(" %[%r%r%] nor the", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_identify_long_object_s, context.set.notable);
    fl_print_format(" %[%r%r%] parameter may be specified.%r%r", file.stream, context.set.notable, f_console_symbol_long_enable_s, fss_identify_long_content_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  An FSS file is identified by the following format: '%[# Object-Content%]'", file.stream, context.set.notable, context.set.notable);
    fl_print_format(" where the Object, is a machine-name representing the name and may only consist of \"word\" characters and the Content is a 4-digit hexidecimal number representing a particular variant of the Object.%r", file.stream, f_string_eol_s);
    fl_print_format("  This identifier, if provided, must exist on the first line in a file and must begin with the pound character: '#'.%r", file.stream, f_string_eol_s);
    fl_print_format("  Whitespace must follow this pound character.%r", file.stream, f_string_eol_s);
    fl_print_format("  There may be multiple Object and Content pairs, separated by whitspace, such as: \"# fss-0002 fss-0000 iki-0002\".%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_fss_identify_print_help_

#ifndef _di_fss_identify_main_
  f_status_t fss_identify_main(fll_program_data_t * const main, const f_console_arguments_t *arguments) {

    f_status_t status = F_none;

    f_console_parameter_t parameters[] = fss_identify_console_parameter_t_initialize;
    main->parameters.array = parameters;
    main->parameters.used = fss_identify_total_parameters_d;

    {
      f_console_parameter_id_t ids[3] = { fss_identify_parameter_no_color_e, fss_identify_parameter_light_e, fss_identify_parameter_dark_e };
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
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          fll_error_print(main->error, F_status_set_fine(status), "fll_program_parameter_process", F_true);
          fll_print_dynamic_raw(f_string_eol_s, main->error.to.stream);
        }

        fss_identify_main_delete(main);

        return F_status_set_error(status);
      }
    }

    // Identify priority of verbosity related parameters.
    {
      f_console_parameter_id_t ids[4] = { fss_identify_parameter_verbosity_quiet_e, fss_identify_parameter_verbosity_normal_e, fss_identify_parameter_verbosity_verbose_e, fss_identify_parameter_verbosity_debug_e };
      f_console_parameter_id_t choice = 0;
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        fss_identify_main_delete(main);

        return status;
      }

      if (choice == fss_identify_parameter_verbosity_quiet_e) {
        main->output.verbosity = f_console_verbosity_quiet_e;
        main->error.verbosity = f_console_verbosity_quiet_e;
        main->warning.verbosity = f_console_verbosity_quiet_e;
      }
      else if (choice == fss_identify_parameter_verbosity_normal_e) {
        main->output.verbosity = f_console_verbosity_normal_e;
        main->error.verbosity = f_console_verbosity_normal_e;
        main->warning.verbosity = f_console_verbosity_normal_e;
      }
      else if (choice == fss_identify_parameter_verbosity_verbose_e) {
        main->output.verbosity = f_console_verbosity_verbose_e;
        main->error.verbosity = f_console_verbosity_verbose_e;
        main->warning.verbosity = f_console_verbosity_verbose_e;
      }
      else if (choice == fss_identify_parameter_verbosity_debug_e) {
        main->output.verbosity = f_console_verbosity_debug_e;
        main->error.verbosity = f_console_verbosity_debug_e;
        main->warning.verbosity = f_console_verbosity_debug_e;
      }
    }

    f_string_static_t * const argv = main->parameters.arguments.array;

    status = F_none;

    if (main->parameters.array[fss_identify_parameter_help_e].result == f_console_result_found_e) {
      fss_identify_print_help(main->output.to, main->context);

      fss_identify_main_delete(main);

      return F_none;
    }

    if (main->parameters.array[fss_identify_parameter_version_e].result == f_console_result_found_e) {
      fll_program_print_version(main->output.to, fss_identify_program_version);

      fss_identify_main_delete(main);

      return F_none;
    }

    fss_identify_data_t data = fss_identify_data_t_initialize;

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_identify_parameter_line_e].result == f_console_result_found_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_identify_long_line_s, main->error.notable);
        fl_print_format("%[' requires a positive number.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters.array[fss_identify_parameter_line_e].result == f_console_result_additional_e) {
        const f_array_length_t index = main->parameters.array[fss_identify_parameter_line_e].values.array[main->parameters.array[fss_identify_parameter_line_e].values.used - 1];
        const f_string_range_t range = macro_f_string_range_t_initialize(argv[index].used);

        status = fl_conversion_string_to_number_unsigned(argv[index].string, range, &data.line);

        if (F_status_is_error(status)) {
          fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_identify_long_line_s, argv[index]);
        }
      }
    }

    if (F_status_is_error_not(status) && main->parameters.array[fss_identify_parameter_total_e].result == f_console_result_found_e) {
      if (main->parameters.array[fss_identify_parameter_object_e].result == f_console_result_found_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%r%[%QCannot specify the '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_identify_long_object_s, main->error.notable);
        fl_print_format("%[' parameter with the '%]", main->error.to.stream, main->error.context, main->error.context);
        fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_identify_long_total_s, main->error.notable);
        fl_print_format("%[' parameter.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters.array[fss_identify_parameter_content_e].result == f_console_result_found_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%r%[%QCannot specify the '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_identify_long_content_s, main->error.notable);
        fl_print_format("%[' parameter with the '%]", main->error.to.stream, main->error.context, main->error.context);
        fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_identify_long_total_s, main->error.notable);
        fl_print_format("%[' parameter.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);

        status = F_status_set_error(F_parameter);
      }
    }

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_identify_parameter_name_e].result == f_console_result_found_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_identify_long_name_s, main->error.notable);
        fl_print_format("%[' requires a string.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters.array[fss_identify_parameter_name_e].result == f_console_result_additional_e) {
        const f_array_length_t index = main->parameters.array[fss_identify_parameter_name_e].values.array[main->parameters.array[fss_identify_parameter_name_e].values.used - 1];
        const f_array_length_t length = argv[index].used;
        const f_string_range_t range = macro_f_string_range_t_initialize(length);

        if (length == 0) {
          flockfile(main->error.to.stream);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_identify_long_name_s, main->error.notable);
          fl_print_format("%[' does not allow zero length strings.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

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

            status = f_utf_is_word(argv[index].string + i, length, F_true);

            if (F_status_is_error(status)) {
              fll_error_print(main->error, F_status_set_fine(status), "f_utf_is_word", F_true);

              break;
            }
            else if (status == F_false) {
              flockfile(main->error.to.stream);

              fl_print_format("%r%[%QThe value '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
              fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, argv[index], main->error.notable);
              fl_print_format("%[' for the parameter '%]", main->error.to.stream, main->error.context, main->error.context);
              fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_identify_long_name_s, main->error.notable);
              fl_print_format("%[' may only contain word characters.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

              funlockfile(main->error.to.stream);

              status = F_status_set_error(F_parameter);

              break;
            }

            data.name.string[data.name.used++] = argv[index].string[i];
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

      status = fss_identify_load_line(main, file, "-", &buffer, &range);

      if (F_status_is_error_not(status)) {
        status = fss_identify_process(main, "-", buffer, &range, &data);
      }
    }

    if (F_status_is_error_not(status)) {
      uint16_t signal_check = 0;

      for (f_array_length_t i = 0; i < main->parameters.remaining.used; ++i) {

        if (!((++signal_check) % fss_identify_signal_check_d)) {
          if (fss_identify_signal_received(main)) {
            status = F_status_set_error(F_interrupt);
            break;
          }

          signal_check = 0;
        }

        if (main->parameters.array[fss_identify_parameter_line_e].result == f_console_result_additional_e) {
          if (data.current > data.line) break;
        }

        macro_f_file_t_reset(file);

        file.size_read = 512;

        status = f_file_stream_open(argv[main->parameters.remaining.array[i]], f_string_empty_s, &file);

        if (F_status_is_error(status)) {
          fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_open", F_true, argv[main->parameters.remaining.array[i]], f_file_operation_open_s, fll_error_file_type_file_e);
        }
        else {
          status = fss_identify_load_line(main, file, argv[main->parameters.remaining.array[i]], &buffer, &range);

          if (F_status_is_error_not(status)) {
            status = fss_identify_process(main, argv[main->parameters.remaining.array[i]], buffer, &range, &data);
          }
        }

        f_file_stream_close(F_true, &file);

        if (F_status_is_error(status)) break;
      } // for
    }

    f_string_dynamic_resize(0, &buffer);

    if (F_status_is_error_not(status)) {
      if (main->parameters.array[fss_identify_parameter_total_e].result == f_console_result_found_e) {
        fll_print_format("%ul%r", main->output.to.stream, data.total, f_string_eol_s);
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

    fss_identify_data_delete(&data);
    fss_identify_main_delete(main);

    return status;
  }
#endif // _di_fss_identify_main_

#ifdef __cplusplus
} // extern "C"
#endif
