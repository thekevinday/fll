#include <level_3/bit_dump.h>
#include "private-bit_dump.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_bit_dump_print_help_
  f_return_status bit_dump_print_help(const bit_dump_data data) {
    fll_program_print_help_header(data.context, bit_dump_name_long, bit_dump_version);

    fll_program_print_help_option(data.context, f_console_standard_short_help, f_console_standard_long_help, f_console_symbol_short_enable, f_console_symbol_long_enable, "       Print this help message.");
    fll_program_print_help_option(data.context, f_console_standard_short_light, f_console_standard_long_light, f_console_symbol_short_disable, f_console_symbol_long_disable, "      Output using colors that show up better on light backgrounds");
    fll_program_print_help_option(data.context, f_console_standard_short_dark, f_console_standard_long_dark, f_console_symbol_short_disable, f_console_symbol_long_disable, "       Output using colors that show up better on dark backgrounds");
    fll_program_print_help_option(data.context, f_console_standard_short_no_color, f_console_standard_long_no_color, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Do not output in color.");
    fll_program_print_help_option(data.context, f_console_standard_short_version, f_console_standard_long_version, f_console_symbol_short_disable, f_console_symbol_long_disable, "    Print only the version number.");

    printf("%c", f_string_eol);

    fll_program_print_help_option(data.context, bit_dump_short_binary, bit_dump_long_binary, f_console_symbol_short_enable, f_console_symbol_long_enable, "     Display binary representation.");
    fll_program_print_help_option(data.context, bit_dump_short_decimal, bit_dump_long_decimal, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Display decimal representation.");
    fll_program_print_help_option(data.context, bit_dump_short_hexdecimal, bit_dump_long_hexidecimal, f_console_symbol_short_enable, f_console_symbol_long_enable, "Display hexadecimal representation.");
    fll_program_print_help_option(data.context, bit_dump_short_octal, bit_dump_long_octal, f_console_symbol_short_enable, f_console_symbol_long_enable, "      Display octal representation.");

    fll_program_print_help_usage(data.context, bit_dump_name, "filename(s)");

    printf("When using the ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "--%s", bit_dump_long_text);
    printf(" option, some UTF-8 characters may be replaced by your instance and cause display alignment issues.");

    printf("%c%c", f_string_eol, f_string_eol);

    printf("Special UTF-8 characters and non-spacing UTF-8 characters may be replaced with a space (or a placeholder when the ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "--%s", bit_dump_long_placeholder);
    printf(" option is used).");

    printf("%c%c", f_string_eol, f_string_eol);

    return f_none;
  }
#endif // _di_bit_dump_print_help_

#ifndef _di_bit_dump_main_
  f_return_status bit_dump_main(const f_console_arguments arguments, bit_dump_data *data) {
    f_status status = f_none;

    {
      f_console_parameters parameters = { data->parameters, bit_dump_total_parameters };
      f_console_parameter_ids choices = f_console_parameter_ids_initialize;

      {
        f_console_parameter_id ids[3] = { bit_dump_parameter_no_color, bit_dump_parameter_light, bit_dump_parameter_dark };
        choices.id = ids;
        choices.used = 3;

        status = fll_program_process_parameters(arguments, parameters, choices, &data->remaining, &data->context);

        if (f_status_is_error(status)) {
          bit_dump_delete_data(data);
          return f_status_set_error(status);
        }
      }

      {
        f_console_parameter_id ids[4] = { bit_dump_parameter_hexidecimal, bit_dump_parameter_octal, bit_dump_parameter_binary, bit_dump_parameter_decimal };
        f_console_parameter_id choice = bit_dump_parameter_hexidecimal;
        choices.id = ids;
        choices.used = 4;

        status = fl_console_parameter_prioritize(parameters, choices, &choice);

        if (f_status_is_error(status)) {
          bit_dump_delete_data(data);
          return f_status_set_error(status);
        }


        if (choice == bit_dump_parameter_hexidecimal) {
          data->mode = bit_dump_mode_hexidecimal;
        }
        else if (choice == bit_dump_parameter_octal) {
          data->mode = bit_dump_mode_octal;
        }
        else if (choice == bit_dump_parameter_binary) {
          data->mode = bit_dump_mode_binary;
        }
        else if (choice == bit_dump_parameter_decimal) {
          data->mode = bit_dump_mode_decimal;
        }
      }
    }

    status = f_none;

    // execute parameter results.
    if (data->parameters[bit_dump_parameter_help].result == f_console_result_found) {
      bit_dump_print_help(*data);
    }
    else if (data->parameters[bit_dump_parameter_version].result == f_console_result_found) {
      fll_program_print_version(bit_dump_version);
    }
    else if (data->remaining.used > 0 || data->process_pipe) {
      if (data->parameters[bit_dump_parameter_width].result == f_console_result_found) {
        fl_color_print_line(f_standard_output, data->context.error, data->context.reset, "Width option was specified but no width was given.");

        bit_dump_delete_data(data);
        return f_status_set_error(status);
      }
      else if (data->parameters[bit_dump_parameter_width].result == f_console_result_additional) {
        uint64_t number = atoll(arguments.argv[data->parameters[bit_dump_parameter_width].additional.array[0]]);
        if (number < 1 || number >= 0xfb) {
          fl_color_print_line(f_standard_output, data->context.error, data->context.reset, "Width option can only be a number between 0 and 251.");

          bit_dump_delete_data(data);
          return f_status_set_error(status);
        }

        data->width = (uint8_t) number;
      }

      if (data->parameters[bit_dump_parameter_first].result == f_console_result_found) {
        fl_color_print_line(f_standard_output, data->context.error, data->context.reset, "First option was specified but no number was given.");

        bit_dump_delete_data(data);
        return f_status_set_error(status);
      }
      else if (data->parameters[bit_dump_parameter_first].result == f_console_result_additional) {
        uint64_t number = atoll(arguments.argv[data->parameters[bit_dump_parameter_first].additional.array[0]]);
        if (number < 1 || number >= 0xffffffffffffffff) {
          fl_color_print_line(f_standard_output, data->context.error, data->context.reset, "First option can only be a number between 0 and 18446744073709551615.");

          bit_dump_delete_data(data);
          return f_status_set_error(status);
        }

        data->first = number;
      }

      if (data->parameters[bit_dump_parameter_last].result == f_console_result_found) {
        fl_color_print_line(f_standard_output, data->context.error, data->context.reset, "Last option was specified but no number was given.");

        bit_dump_delete_data(data);
        return f_status_set_error(status);
      }
      else if (data->parameters[bit_dump_parameter_last].result == f_console_result_additional) {
        uint64_t number = atoll(arguments.argv[data->parameters[bit_dump_parameter_last].additional.array[0]]);
        if (number < 1 || number >= 0xffffffffffffffff) {
          fl_color_print_line(f_standard_output, data->context.error, data->context.reset, "Last option can only be a number between 0 and 18446744073709551615.");

          bit_dump_delete_data(data);
          return f_status_set_error(status);
        }

        data->last = number;
      }

      if (data->first > data->last) {
          fl_color_print(f_standard_output, data->context.error, data->context.reset, "First option (");
          fl_color_print(f_standard_output, data->context.notable, data->context.reset, "%d", data->first);
          fl_color_print(f_standard_output, data->context.error, data->context.reset, ") cannot be greater than Last option (");
          fl_color_print(f_standard_output, data->context.notable, data->context.reset, "%d", data->last);
          fl_color_print_line(f_standard_output, data->context.error, data->context.reset, ").");

          bit_dump_delete_data(data);
          return f_status_set_error(status);
      }

      if (data->process_pipe) {
        // TODO: how should this be done?
      }

      if (data->remaining.used > 0) {
        // pre-process remaining arguments to ensure that they all files exist before processing.
        {
          f_status missing_files = f_none;

          for (f_array_length counter = 0; counter < data->remaining.used; counter++) {
            status = f_file_exists(arguments.argv[data->remaining.array[counter]]);
            if (status == f_false || f_status_is_error(status)) {
              if (missing_files == f_none) {
                missing_files = status;
              }

              bit_dump_print_file_error(data->context, status, "f_file_exists", arguments.argv[data->remaining.array[counter]]);
            }
          } // for

          if (missing_files != f_none) {
            status = f_status_set_error(missing_files);

            bit_dump_delete_data(data);
            return status;
          }
        }

        for (f_array_length counter = 0; counter < data->remaining.used; counter++) {
          f_file file = f_file_initialize;

          status = f_file_open(&file, arguments.argv[data->remaining.array[counter]]);
          if (f_status_is_error(status)) {
            bit_dump_print_file_error(data->context, status, "f_file_open", arguments.argv[data->remaining.array[counter]]);
            bit_dump_delete_data(data);
            return status;
          }

          printf("%c", f_string_eol);
          fl_color_print(f_standard_output, data->context.title, data->context.reset, "Byte Dump of: ");
          fl_color_print(f_standard_output, data->context.notable, data->context.reset, "%s", arguments.argv[data->remaining.array[counter]]);
          fl_color_print(f_standard_output, data->context.title, data->context.reset, " (in ");

          if (data->mode == bit_dump_mode_hexidecimal) {
            fl_color_print(f_standard_output, data->context.title, data->context.reset, "Hexidecimal");
          }
          else if (data->mode == bit_dump_mode_octal) {
            fl_color_print(f_standard_output, data->context.title, data->context.reset, "Octal");
          }
          else if (data->mode == bit_dump_mode_binary) {
            fl_color_print(f_standard_output, data->context.title, data->context.reset, "Binary");
          }
          else if (data->mode == bit_dump_mode_decimal) {
            fl_color_print(f_standard_output, data->context.title, data->context.reset, "Decimal");
          }

          fl_color_print_line(f_standard_output, data->context.title, data->context.reset, ")");

          status = bit_dump_file(*data, arguments.argv[data->remaining.array[counter]], file);

          f_file_close(&file);

          if (f_status_is_error(status)) {
            bit_dump_delete_data(data);
            return status;
          }
        } // for
      }
      else {
        status = f_false;
      }
    }
    else {
      fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: you failed to specify an error code.");
      status = f_status_set_error(f_invalid_parameter);
    }

    bit_dump_delete_data(data);
    return status;
  }
#endif // _di_bit_dump_main_

#ifndef _di_bit_dump_delete_data_
  f_return_status bit_dump_delete_data(bit_dump_data *data) {
    f_status status = f_none;

    for (f_string_length i = 0; i < bit_dump_total_parameters; i++) {
      f_macro_string_lengths_delete(status, data->parameters[i].additional);
    } // for

    f_macro_string_lengths_delete(status, data->remaining);
    fl_macro_color_context_delete(status, data->context);

    return f_none;
  }
#endif // _di_bit_dump_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
