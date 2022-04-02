#include "iki_read.h"
#include "private-common.h"
#include "private-read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_print_help_
  f_status_t iki_read_print_help(const f_file_t file, const f_color_context_t context) {

    flockfile(file.stream);

    fll_program_print_help_header(file, context, iki_read_program_name_long_s, iki_read_program_version_s);

    fll_program_print_help_option(file, context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print this help message.");
    fll_program_print_help_option(file, context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(file, context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Do not file in color.");
    fll_program_print_help_option(file, context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity, silencing most output.");
    fll_program_print_help_option(file, context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Set verbosity to normal.");
    fll_program_print_help_option(file, context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Enable debugging, significantly increasing verbosity beyond normal output.");
    fll_program_print_help_option(file, context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Print only the version number.");

    f_print_dynamic_raw(f_string_eol_s, file.stream);

    fll_program_print_help_option(file, context, iki_read_short_at_s, iki_read_long_at_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Select variable at this numeric index.");
    fll_program_print_help_option(file, context, iki_read_short_line_s, iki_read_long_line_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Print only the variables at the given line within the file.");
    fll_program_print_help_option(file, context, iki_read_short_name_s, iki_read_long_name_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Select variables with this name.");
    fll_program_print_help_option(file, context, iki_read_short_whole_s, iki_read_long_whole_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Print all of the data instead of just the IKI variable data.");

    f_print_dynamic_raw(f_string_eol_s, file.stream);

    fll_program_print_help_option(file, context, iki_read_short_content_s, iki_read_long_content_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Print the variable content (default).");
    fll_program_print_help_option(file, context, iki_read_short_literal_s, iki_read_long_literal_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Print the entire variable (aka: object, content, and syntax).");
    fll_program_print_help_option(file, context, iki_read_short_object_s, iki_read_long_object_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Print the variable name (aka: object).");
    fll_program_print_help_option(file, context, iki_read_short_total_s, iki_read_long_total_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Print the total number of variables.");

    f_print_dynamic_raw(f_string_eol_s, file.stream);

    fll_program_print_help_option(file, context, iki_read_short_substitute_s, iki_read_long_substitute_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Substitute the entire variable for the given name and content value with the given string.");

    fll_program_print_help_usage(file, context, iki_read_program_name_s, fll_program_parameter_filenames_s);

    fl_print_format(" %[Notes:%]%r", file.stream, context.set.important, context.set.important, f_string_eol_s);
    fl_print_format("  This program will find and print variables, vocabularies, or content following the IKI standard, without focusing on any particular vocabulary specification.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  This %[%r%r%] option, requires 3 additional parameters:", file.stream, context.set.notable, f_console_symbol_long_enable_s, iki_read_long_substitute_s, context.set.notable);
    fl_print_format(" %[<%]%r%[>%]", file.stream, context.set.notable, context.set.notable, iki_read_substitution_vocabulary_s, context.set.notable, context.set.notable);
    fl_print_format(" %[<%]%r%[>%]", file.stream, context.set.notable, context.set.notable, iki_read_substitution_replace_s, context.set.notable, context.set.notable);
    fl_print_format(" %[<%]%r%[>%].%r", file.stream, context.set.notable, context.set.notable, iki_read_substitution_with_s, context.set.notable, context.set.notable, f_string_eol_s);

    fl_print_format("    %[%r%]: The name of the vocabulary whose content is to be substituted.%r", file.stream, context.set.notable, iki_read_substitution_vocabulary_s, context.set.notable, f_string_eol_s);
    fl_print_format("    %[%r%]: The content matching this exact string will be substituted.%r", file.stream, context.set.notable, iki_read_substitution_replace_s, context.set.notable, f_string_eol_s);
    fl_print_format("    %[%r%]: The new string to use as the substitute.%r%r", file.stream, context.set.notable, iki_read_substitution_with_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The vocabulary and replacement are case-sensitive and must exactly match.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The default behavior is to only display content portion of the IKI variable.%r%r", file.stream, f_string_eol_s, f_string_eol_s);

    funlockfile(file.stream);

    return F_none;
  }
#endif // _di_iki_read_print_help_

#ifndef _di_iki_read_main_
  f_status_t iki_read_main(fll_program_data_t * const main, const f_console_arguments_t *arguments) {

    f_status_t status = F_none;

    {
      f_console_parameter_id_t ids[3] = { iki_read_parameter_no_color_e, iki_read_parameter_light_e, iki_read_parameter_dark_e };
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

        if (main->error.verbosity == f_console_verbosity_verbose_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->error.to.stream);
        }

        return F_status_set_error(status);
      }
    }

    // Identify priority of verbosity related parameters.
    {
      f_console_parameter_id_t ids[4] = { iki_read_parameter_verbosity_quiet_e, iki_read_parameter_verbosity_normal_e, iki_read_parameter_verbosity_verbose_e, iki_read_parameter_verbosity_debug_e };
      f_console_parameter_id_t choice = 0;
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 4);

      status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_console_parameter_prioritize_right", F_true);

        return status;
      }

      if (choice == iki_read_parameter_verbosity_quiet_e) {
        main->output.verbosity = f_console_verbosity_quiet_e;
        main->error.verbosity = f_console_verbosity_quiet_e;
        main->warning.verbosity = f_console_verbosity_quiet_e;
      }
      else if (choice == iki_read_parameter_verbosity_normal_e) {
        main->output.verbosity = f_console_verbosity_normal_e;
        main->error.verbosity = f_console_verbosity_normal_e;
        main->warning.verbosity = f_console_verbosity_normal_e;
      }
      else if (choice == iki_read_parameter_verbosity_verbose_e) {
        main->output.verbosity = f_console_verbosity_verbose_e;
        main->error.verbosity = f_console_verbosity_verbose_e;
        main->warning.verbosity = f_console_verbosity_verbose_e;
      }
      else if (choice == iki_read_parameter_verbosity_debug_e) {
        main->output.verbosity = f_console_verbosity_debug_e;
        main->error.verbosity = f_console_verbosity_debug_e;
        main->warning.verbosity = f_console_verbosity_debug_e;
      }
    }

    iki_read_data_t data = iki_read_data_t_initialize;
    data.main = main;
    data.argv = main->parameters.arguments.array;

    status = F_none;

    if (main->parameters.array[iki_read_parameter_help_e].result == f_console_result_found_e) {
      iki_read_print_help(main->output.to, main->context);

      iki_read_data_delete(&data);

      return F_none;
    }

    if (main->parameters.array[iki_read_parameter_version_e].result == f_console_result_found_e) {
      fll_program_print_version(main->output.to, iki_read_program_version_s);

      iki_read_data_delete(&data);

      return F_none;
    }

    if (main->parameters.remaining.used > 0 || main->process_pipe) {
      if (main->parameters.array[iki_read_parameter_at_e].result == f_console_result_found_e) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_at_s, main->error.notable);
          fl_print_format("%[' requires a positive number.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters.array[iki_read_parameter_at_e].result == f_console_result_additional_e) {
        const f_array_length_t index = main->parameters.array[iki_read_parameter_at_e].values.array[main->parameters.array[iki_read_parameter_at_e].values.used - 1];

        f_number_unsigned_t number = 0;

        status = fl_conversion_dynamic_to_number_unsigned(data.argv[index], &number);

        if (F_status_is_error(status)) {
          fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_dynamic_to_number_unsigned", F_true, iki_read_long_at_s, data.argv[index]);

          status = F_status_set_error(F_parameter);
        }

        data.at = number;

        if (main->parameters.array[iki_read_parameter_whole_e].result == f_console_result_found_e) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            fll_program_parameter_long_print_cannot_use_with(main->error, iki_read_long_at_s, iki_read_long_whole_s);
          }

          status = F_status_set_error(F_parameter);
        }
      }

      if (main->parameters.array[iki_read_parameter_line_e].result == f_console_result_found_e) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_line_s, main->error.notable);
          fl_print_format("%[' requires a positive number.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }

        status = F_status_set_error(F_parameter);
      }
      else if (main->parameters.array[iki_read_parameter_line_e].result == f_console_result_additional_e) {
        const f_array_length_t index = main->parameters.array[iki_read_parameter_line_e].values.array[main->parameters.array[iki_read_parameter_line_e].values.used - 1];

        f_number_unsigned_t number = 0;

        status = fl_conversion_dynamic_to_number_unsigned(data.argv[index], &number);

        if (F_status_is_error(status)) {
          fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_dynamic_to_number_unsigned", F_true, iki_read_long_line_s, data.argv[index]);

          status = F_status_set_error(F_parameter);
        }

        data.line = number;
      }

      if (main->parameters.array[iki_read_parameter_name_e].result == f_console_result_found_e) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          flockfile(main->error.to.stream);

          fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_name_s, main->error.notable);
          fl_print_format("%[' requires a string.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }

        status = F_status_set_error(F_parameter);
      }

      if (main->parameters.array[iki_read_parameter_substitute_e].result != f_console_result_none_e) {
        if (main->parameters.array[iki_read_parameter_substitute_e].result == f_console_result_found_e || main->parameters.array[iki_read_parameter_substitute_e].values.used % 3 != 0) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, iki_read_long_substitute_s, main->error.notable);
            fl_print_format("%[' requires 3 strings.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }

          status = F_status_set_error(F_parameter);
        }

        if (main->parameters.array[iki_read_parameter_total_e].result == f_console_result_found_e) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            fll_program_parameter_long_print_cannot_use_with(main->error, iki_read_long_substitute_s, iki_read_long_total_s);
          }

          status = F_status_set_error(F_parameter);
        }
      }

      if (main->parameters.array[iki_read_parameter_literal_e].result == f_console_result_found_e) {
        if (main->parameters.array[iki_read_parameter_object_e].result == f_console_result_found_e) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            fll_program_parameter_long_print_cannot_use_with(main->error, iki_read_long_literal_s, iki_read_long_object_s);
          }

          status = F_status_set_error(F_parameter);
        }

        if (main->parameters.array[iki_read_parameter_content_e].result == f_console_result_found_e) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            fll_program_parameter_long_print_cannot_use_with(main->error, iki_read_long_literal_s, iki_read_long_content_s);
          }

          status = F_status_set_error(F_parameter);
        }

        if (main->parameters.array[iki_read_parameter_total_e].result == f_console_result_found_e) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            fll_program_parameter_long_print_cannot_use_with(main->error, iki_read_long_literal_s, iki_read_long_total_s);
          }

          status = F_status_set_error(F_parameter);
        }

        data.mode = iki_read_mode_literal_e;
      }
      else if (main->parameters.array[iki_read_parameter_object_e].result == f_console_result_found_e) {
        if (main->parameters.array[iki_read_parameter_content_e].result == f_console_result_found_e) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            fll_program_parameter_long_print_cannot_use_with(main->error, iki_read_long_object_s, iki_read_long_content_s);
          }

          status = F_status_set_error(F_parameter);
        }

        if (main->parameters.array[iki_read_parameter_total_e].result == f_console_result_found_e) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            fll_program_parameter_long_print_cannot_use_with(main->error, iki_read_long_object_s, iki_read_long_total_s);
          }

          status = F_status_set_error(F_parameter);
        }

        data.mode = iki_read_mode_object_e;
      }
      else if (main->parameters.array[iki_read_parameter_total_e].result == f_console_result_found_e) {
        data.mode = iki_read_mode_total_e;
      }
      else {

        // This is the default behavior, so there is no reason to check for the -c/--content parameter.
        data.mode = iki_read_mode_content_e;
      }

      if (main->parameters.array[iki_read_parameter_whole_e].result == f_console_result_found_e) {
        if (main->parameters.array[iki_read_parameter_total_e].result == f_console_result_found_e) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            fll_program_parameter_long_print_cannot_use_with(main->error, iki_read_long_whole_s, iki_read_long_total_s);
          }

          status = F_status_set_error(F_parameter);
        }
      }

      if (F_status_is_error(status)) {
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->error.to.stream);
        }

        iki_read_data_delete(&data);

        return F_status_set_error(F_parameter);
      }

      if (main->process_pipe) {
        f_file_t file = f_file_t_initialize;

        file.id = F_type_descriptor_input_d;

        status = f_file_read(file, &data.buffer);

        if (F_status_is_error(status)) {
          fll_error_file_print(main->error, F_status_set_fine(status), "f_file_read", F_true, f_string_ascii_minus_s, f_file_operation_process_s, fll_error_file_type_file_e);
        }
        else {
          status = iki_read_process_buffer(&data);
        }

        // Clear buffers before continuing.
        f_string_dynamic_resize(0, &data.buffer);
      }

      if (F_status_is_fine(status) && main->parameters.remaining.used > 0) {
        f_file_t file = f_file_t_initialize;

        for (f_array_length_t i = 0; i < main->parameters.remaining.used; ++i) {

          if (!((++main->signal_check) % iki_read_signal_check_d)) {
            if (fll_program_standard_signal_received(main)) {
              iki_read_print_signal_received(&data);

              status = F_status_set_error(F_interrupt);

              break;
            }

            main->signal_check = 0;
          }

          macro_f_file_t_reset(file);
          file.size_read = 0;

          status = f_file_open(data.argv[main->parameters.remaining.array[i]], 0, &file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_open", F_true, data.argv[main->parameters.remaining.array[i]], f_file_operation_process_s, fll_error_file_type_file_e);

            break;
          }

          status = f_file_size_by_id(file.id, &file.size_read);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_size_by_id", F_true, data.argv[main->parameters.remaining.array[i]], f_file_operation_process_s, fll_error_file_type_file_e);

            f_file_stream_close(F_true, &file);

            break;
          }

          // Skip past empty files.
          if (!file.size_read) {
            f_file_stream_close(F_true, &file);

            continue;
          }

          ++file.size_read;

          status = f_file_read(file, &data.buffer);

          f_file_stream_close(F_true, &file);

          if (F_status_is_error(status)) {
            fll_error_file_print(main->error, F_status_set_fine(status), "f_file_read", F_true, data.argv[main->parameters.remaining.array[i]], f_file_operation_process_s, fll_error_file_type_file_e);

            break;
          }

          status = iki_read_process_buffer(&data);
          if (F_status_is_error(status)) break;

          // Clear buffers before repeating the loop.
          f_string_dynamic_resize(0, &data.buffer);
        } // for
      }
    }
    else {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        fll_print_format("%r%[%QYou failed to specify one or more files.%]%r", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context, f_string_eol_s);
      }

      status = F_status_set_error(F_parameter);
    }

    // ensure a newline is always put at the end of the program execution, unless in quiet mode.
    if (main->error.verbosity != f_console_verbosity_quiet_e) {
      if (F_status_is_error(status) || !data.mode) {
        if (F_status_set_fine(status) == F_interrupt) {
          fflush(main->output.to.stream);
        }

        fll_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
      }
    }

    iki_read_data_delete(&data);

    return status;
  }
#endif // _di_iki_read_main_

#ifdef __cplusplus
} // extern "C"
#endif
