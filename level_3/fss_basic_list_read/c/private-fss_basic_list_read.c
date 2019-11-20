#include <level_3/fss_basic_list_read.h>
#include "private-fss_basic_list_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_list_read_print_file_error_
  void fss_basic_list_read_print_file_error(const fl_color_context context, const f_string function_name, const f_string file_name, const f_status status) {

    if (status == f_invalid_parameter) {
      fl_color_print(f_standard_error, context.error, context.reset, "INTERNAL ERROR: Invalid parameter when calling ");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s()", function_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, ".");
    }
    else if (status == f_number_overflow) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Integer overflow while trying to buffer the file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
    }
    else if (status == f_file_not_open) {
      fl_color_print(f_standard_error, context.error, context.reset, "INTERNAL ERROR: The file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "' is no longer open.");
    }
    else if (status == f_file_error_seek) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: A seek error occurred while accessing the file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
    }
    else if (status == f_file_error_read) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: A read error occurred while accessing the file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
    }
    else if (status == f_file_not_found) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Unable to find the file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
    }
    else if (status == f_file_error_open) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Unable to open the file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
    }
    else if (status == f_file_error_descriptor) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: File descriptor error while trying to open the file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
    }
    else if (status == f_number_overflow) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Integer overflow while trying to buffer the file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
    }
    else if (status == f_error_allocation || status == f_error_reallocation) {
      fl_color_print_line(f_standard_error, context.error, context.reset, "CRITICAL ERROR: Unable to allocate memory.");
    }
    else {
      fl_color_print(f_standard_error, context.error, context.reset, "INTERNAL ERROR: An unhandled error (");
      fl_color_print(f_standard_error, context.notable, context.reset, "%u", status);
      fl_color_print(f_standard_error, context.error, context.reset, ") has occured while calling ");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s()", function_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, ".");
    }
  }
#endif // _di_fss_basic_list_read_print_file_error_

#ifndef _di_fss_basic_list_read_print_number_argument_error_
  void fss_basic_list_read_print_number_argument_error(const fl_color_context context, const f_string function_name, const f_string parameter_name, const f_string argument, const f_status status) {

    if (status == f_invalid_parameter) {
      fl_color_print(f_standard_error, context.error, context.reset, "INTERNAL ERROR: Invalid parameter when calling ");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s()", function_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, ".");
    }
    else if (status == f_number_invalid) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: The argument '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", argument);
      fl_color_print(f_standard_error, context.error, context.reset, "' is not a valid number for the parameter '");
      fl_color_print(f_standard_error, context.notable, context.reset, "--%s", parameter_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
    }
    else if (status == f_number_underflow) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: The argument '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", argument);
      fl_color_print(f_standard_error, context.error, context.reset, "' is too small for the parameter '");
      fl_color_print(f_standard_error, context.notable, context.reset, "--%s", parameter_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
    }
    else if (status == f_number_overflow) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: The argument '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", argument);
      fl_color_print(f_standard_error, context.error, context.reset, "' is too large for the parameter '");
      fl_color_print(f_standard_error, context.notable, context.reset, "--%s", parameter_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
    }
    else if (status == f_number_negative) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: The argument '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", argument);
      fl_color_print(f_standard_error, context.error, context.reset, "' is negative, which is not allowed for the parameter '");
      fl_color_print(f_standard_error, context.notable, context.reset, "--%s", parameter_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
    }
    else if (status == f_number_positive) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: The argument '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", argument);
      fl_color_print(f_standard_error, context.error, context.reset, "' contains a '");
      fl_color_print(f_standard_error, context.notable, context.reset, "+");
      fl_color_print(f_standard_error, context.error, context.reset, "', which is not allowed for the parameter '");
      fl_color_print(f_standard_error, context.notable, context.reset, "--%s", parameter_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
    }
    else if (status == f_no_data) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: The parameter '");
      fl_color_print(f_standard_error, context.notable, context.reset, "--%s", parameter_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "' must not be an empty string.");
    }
    else {
      fl_color_print(f_standard_error, context.error, context.reset, "INTERNAL ERROR: An unhandled error (");
      fl_color_print(f_standard_error, context.notable, context.reset, "%u", status);
      fl_color_print(f_standard_error, context.error, context.reset, ") has occured while calling ");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s()", function_name);
      fl_color_print(f_standard_error, context.error, context.reset, "' for the parameter '");
      fl_color_print(f_standard_error, context.notable, context.reset, "--%s", parameter_name);
      fl_color_print(f_standard_error, context.error, context.reset, "' with the value '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", argument);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
    }
  }
#endif // _di_fss_basic_list_read_print_number_argument_error_

#ifndef _di_fss_basic_list_read_main_preprocess_depth_
  f_return_status fss_basic_list_read_main_preprocess_depth(const f_console_arguments arguments, const fss_basic_list_read_data data, fss_basic_list_read_depths *depths) {
    f_status status = f_none;

    {
      f_array_length depth_size = 1;

      if (data.parameters[fss_basic_list_read_parameter_depth].result == f_console_result_additional) {
        depth_size = data.parameters[fss_basic_list_read_parameter_depth].additional.used;
      }

      macro_fss_basic_list_read_depths_new(status, (*depths), depth_size);
      if (f_status_is_error(status)) {
        fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "CRITICAL ERROR: Unable to allocate memory.");
        return status;
      }

      depths->used = depth_size;
    }

    f_array_length position_depth = 0;
    f_array_length position_at = 0;
    f_array_length position_name = 0;

    for (f_array_length i = 0; i < depths->used; i++) {
      depths->array[i].depth = 0;
      depths->array[i].index_at = 0;
      depths->array[i].index_name = 0;
      depths->array[i].value_at = 0;
      depths->array[i].value_name = f_string_eos;

      if (data.parameters[fss_basic_list_read_parameter_depth].additional.used == 0) {
        position_depth = 0;
      }
      else {
        position_depth = data.parameters[fss_basic_list_read_parameter_depth].additional.array[i];

        status = fl_console_parameter_to_number_unsigned(arguments.argv[position_depth], &depths->array[i].depth);

        if (f_status_is_error(status)) {
          fss_basic_list_read_print_number_argument_error(data.context, "fl_console_parameter_to_number_unsigned", fss_basic_list_read_long_depth, arguments.argv[position_depth], f_status_set_fine(status));
          return status;
        }
      }

      if (data.parameters[fss_basic_list_read_parameter_at].result == f_console_result_additional) {
        for (; position_at < data.parameters[fss_basic_list_read_parameter_at].additional.used; position_at++) {
          if (data.parameters[fss_basic_list_read_parameter_at].additional.array[position_at] < position_depth) {
            continue;
          }

          if (i + 1 < depths->used && data.parameters[fss_basic_list_read_parameter_at].additional.array[position_at] > data.parameters[fss_basic_list_read_parameter_depth].additional.array[i + 1]) {
            break;
          }

          depths->array[i].index_at = data.parameters[fss_basic_list_read_parameter_at].additional.array[position_at];

          status = fl_console_parameter_to_number_unsigned(arguments.argv[depths->array[i].index_at], &depths->array[i].value_at);

          if (f_status_is_error(status)) {
            fss_basic_list_read_print_number_argument_error(data.context, "fl_console_parameter_to_number_unsigned", fss_basic_list_read_long_at, arguments.argv[depths->array[i].index_at], f_status_set_fine(status));
            return status;
          }
        } // for
      }

      if (data.parameters[fss_basic_list_read_parameter_name].result == f_console_result_additional) {
        for (; position_name < data.parameters[fss_basic_list_read_parameter_name].additional.used; position_name++) {
          if (data.parameters[fss_basic_list_read_parameter_name].additional.array[position_name] < position_depth) {
            continue;
          }

          if (i + 1 < depths->used && data.parameters[fss_basic_list_read_parameter_name].additional.array[position_name] > data.parameters[fss_basic_list_read_parameter_depth].additional.array[i + 1]) {
            break;
          }

          depths->array[i].index_name = data.parameters[fss_basic_list_read_parameter_name].additional.array[position_name];
          depths->array[i].value_name = arguments.argv[depths->array[i].index_name];

          if (depths->array[i].value_name[0] == '\0') {
            fl_color_print(f_standard_error, data.context.error, data.context.reset, "ERROR: The '");
            fl_color_print(f_standard_error, data.context.notable, data.context.reset, "--%s", fss_basic_list_read_long_name);
            fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "' must not be an empty string.");

            return f_status_set_error(f_invalid_parameter);
          }
        } // for
      }
    } // for

    for (f_array_length i = 0; i < depths->used; i++) {
      for (f_array_length j = i + 1; j < depths->used; j++) {
        if (depths->array[i].depth == depths->array[j].depth) {
          fl_color_print(f_standard_error, data.context.error, data.context.reset, "ERROR: The value '");
          fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%llu", depths->array[i].depth);
          fl_color_print(f_standard_error, data.context.error, data.context.reset, "' may only be specified once for the parameter '");
          fl_color_print(f_standard_error, data.context.notable, data.context.reset, "--%s", fss_basic_list_read_long_depth);
          fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "'.");

          return f_status_set_error(f_invalid_parameter);
        }
        else if (depths->array[i].depth > depths->array[j].depth) {
          fl_color_print(f_standard_error, data.context.error, data.context.reset, "ERROR: The parameter '");
          fl_color_print(f_standard_error, data.context.notable, data.context.reset, "--%s", fss_basic_list_read_long_depth);
          fl_color_print(f_standard_error, data.context.error, data.context.reset, "' may not have the value '");
          fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%llu", depths->array[i].depth);
          fl_color_print(f_standard_error, data.context.error, data.context.reset, "' before the value '");
          fl_color_print(f_standard_error, data.context.notable, data.context.reset, "%llu", depths->array[j].depth);
          fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "'.");

          return f_status_set_error(f_invalid_parameter);
        }
      } // for
    } // for

    return f_none;
  }
#endif // _di_fss_basic_list_read_main_preprocess_depth_

#ifndef _di_fss_basic_list_read_main_process_file_
  f_return_status fss_basic_list_read_main_process_file(const f_console_arguments arguments, fss_basic_list_read_data *data, const f_string filename, const fss_basic_list_read_depths depths) {
    f_status status = f_none;
    f_status status2 = f_none;

    {
      f_string_location input = f_string_location_initialize;

      input.start = 0;
      input.stop = data->buffer.used - 1;

      status = fll_fss_basic_list_read(&data->buffer, &input, &data->objects, &data->contents);

      if (f_status_is_error(status)) {
        status = f_status_set_fine(status);

        if (status == f_invalid_parameter) {
          fl_color_print(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling ");
          fl_color_print(f_standard_error, data->context.notable, data->context.reset, "fll_fss_basic_list_read()");
          fl_color_print(f_standard_error, data->context.error, data->context.reset, " for the file '");
          fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s", filename);
          fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "'.");
        }
        else if (status == f_error_allocation || status == f_error_reallocation) {
          fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: Unable to allocate memory");
        }
        else if (status == f_incomplete_utf_on_stop) {
          fl_color_print(f_standard_error, data->context.error, data->context.reset, "ENCODING ERROR: error occured on invalid UTF-8 character at stop position (at ");
          fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%d", input.start);
          fl_color_print_line(f_standard_error, data->context.error, data->context.reset, ").");
        }
        else if (status == f_incomplete_utf_on_eos) {
          fl_color_print(f_standard_error, data->context.error, data->context.reset, "ENCODING ERROR: error occured on invalid UTF-8 character at end of string (at ");
          fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%d", input.start);
          fl_color_print_line(f_standard_error, data->context.error, data->context.reset, ").");
        }
        else {
          fl_color_print(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (");
          fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%u", status);
          fl_color_print(f_standard_error, data->context.error, data->context.reset, ") has occured while calling ");
          fl_color_print(f_standard_error, data->context.notable, data->context.reset, "fll_fss_basic_list_read()");
          fl_color_print(f_standard_error, data->context.error, data->context.reset, " for the file '");
          fl_color_print(f_standard_error, data->context.notable, data->context.reset, "%s", filename);
          fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "'.");
        }

        return f_status_set_error(status);
      }
      else if (status == f_no_data_on_stop || status == f_no_data_on_eos) {
        // Clear buffers, then attempt the next file.
        f_macro_fss_contents_delete(status2, data->contents);
        f_macro_fss_objects_delete(status2, data->objects);
        f_macro_string_dynamic_delete(status2, data->buffer);

        return f_status_set_warning(status);
      }
    }

    f_string_length select = 0;

    if (data->parameters[fss_basic_list_read_parameter_select].result == f_console_result_additional) {
      status = fl_console_parameter_to_number_unsigned(arguments.argv[data->parameters[fss_basic_list_read_parameter_select].additional.array[data->parameters[fss_basic_list_read_parameter_select].additional.used - 1]], &select);

      if (f_status_is_error(status)) {
        fss_basic_list_read_print_number_argument_error(data->context, "fl_console_parameter_to_number_unsigned", fss_basic_list_read_long_select, arguments.argv[data->parameters[fss_basic_list_read_parameter_select].additional.array[0]], f_status_set_fine(status));
        return status;
      }

      // This standard does not support multiple content groups.
      if (select > 0) {
        return f_none;
      }
    }

    f_string_length line = 0;

    if (data->parameters[fss_basic_list_read_parameter_line].result == f_console_result_additional) {
      status = fl_console_parameter_to_number_unsigned(arguments.argv[data->parameters[fss_basic_list_read_parameter_line].additional.array[data->parameters[fss_basic_list_read_parameter_line].additional.used - 1]], &line);

      if (f_status_is_error(status)) {
        fss_basic_list_read_print_number_argument_error(data->context, "fl_console_parameter_to_number_unsigned", fss_basic_list_read_long_line, arguments.argv[data->parameters[fss_basic_list_read_parameter_line].additional.array[0]], f_status_set_fine(status));
        return status;
      }
    }

    bool names[data->objects.used];

    if (depths.array[0].index_name > 0) {
      memset(names, 0, sizeof(bool) * data->objects.used);

      f_string_length argv_length = strlen(depths.array[0].value_name);
      f_string_length name_length = 0;

      for (f_string_length i = 0; i < data->objects.used; i++) {
        name_length = data->objects.array[i].stop - data->objects.array[i].start + 1;

        if (name_length == argv_length) {
          if (fl_string_compare(data->buffer.string + data->objects.array[i].start, depths.array[0].value_name, name_length, argv_length) == f_equal_to) {
            names[i] = 1;
          }
        }
      } // for
    }
    else {
      memset(names, 1, sizeof(bool) * data->objects.used);
    }

    bool include_empty = 0;

    if (data->parameters[fss_basic_list_read_parameter_empty].result == f_console_result_found) {
      include_empty = 1;
    }

    if (data->parameters[fss_basic_list_read_parameter_object].result == f_console_result_found) {
      if (data->parameters[fss_basic_list_read_parameter_total].result == f_console_result_found) {
        if (depths.array[0].index_at > 0) {
          if (depths.array[0].value_at < data->objects.used && names[depths.array[0].value_at]) {
            fprintf(f_standard_output, "1%c", f_string_eol);
          }
          else {
            fprintf(f_standard_output, "0%c", f_string_eol);
          }
        }
        else if (depths.array[0].index_name > 0) {
          f_string_length total = 0;

          for (f_string_length i = 0; i < data->objects.used; i++) {
            if (names[i] == 0) continue;

            total++;
          } // for

          fprintf(f_standard_output, "%llu%c", total, f_string_eol);
        }
        else {
          fprintf(f_standard_output, "%llu%c", data->objects.used, f_string_eol);
        }

        return f_none;
      }

      if (depths.array[0].index_at > 0) {
        f_array_length at = 0;
        f_array_length i = 0;

        for (; i < data->objects.used; i++) {
          if (names[i]) {
            if (at == depths.array[0].value_at) {
              f_print_string_dynamic_partial(f_standard_output, data->buffer, data->objects.array[i]);
              fprintf(f_standard_output, "%c", f_string_eol);
              break;
            }

            at++;
          }
        } // for

        return f_none;
      }

      for (f_string_length i = 0; i < data->objects.used; i++) {
        if (names[i] == 0) continue;

        f_print_string_dynamic_partial(f_standard_output, data->buffer, data->objects.array[i]);
        fprintf(f_standard_output, "%c", f_string_eol);
      } // for

      return f_none;
    }

    if (depths.array[0].index_at > 0) {
      if (depths.array[0].value_at >= data->objects.used) {
        if (names[depths.array[0].value_at] && data->parameters[fss_basic_list_read_parameter_total].result == f_console_result_found) {
          fprintf(f_standard_output, "0%c", f_string_eol);
        }

        return f_none;
      }

      f_array_length at = 0;
      f_array_length i = 0;

      for (; i < data->objects.used; i++) {
        if (names[i]) {
          if (at == depths.array[0].value_at) {
            if (data->parameters[fss_basic_list_read_parameter_total].result == f_console_result_found) {
              if (data->contents.array[i].used == 0) {
                fprintf(f_standard_output, "0%c", f_string_eol);
              }
              else {
                f_string_length total = 1;

                for (f_string_length j = data->contents.array[i].array[0].start; j <= data->contents.array[i].array[0].stop; j++) {
                  if (data->buffer.string[j] == f_string_eos) continue;

                  if (data->buffer.string[j] == f_string_eol) {
                    total++;
                  }
                } // for

                fprintf(f_standard_output, "%llu%c", total, f_string_eol);
              }

              return f_none;
            }

            if (data->parameters[fss_basic_list_read_parameter_line].result == f_console_result_additional) {
              if (data->contents.array[i].used == 0) {
                if (include_empty && line == 0) {
                  fprintf(f_standard_output, "%c", f_string_eol);
                }
              }
              else {
                f_string_length i = data->contents.array[i].array[0].start;

                if (line == 0) {
                  for (; i <= data->contents.array[i].array[0].stop; i++) {
                    if (data->buffer.string[i] == f_string_eos) continue;
                    if (data->buffer.string[i] == f_string_eol) {
                      fprintf(f_standard_output, "%c", f_string_eol);
                      break;
                    }

                    fprintf(f_standard_output, "%c", data->buffer.string[i]);
                  } // for
                }
                else {
                  f_string_length line_current = 0;

                  for (; i <= data->contents.array[i].array[0].stop; i++) {
                    if (data->buffer.string[i] == f_string_eos) continue;

                    if (data->buffer.string[i] == f_string_eol) {
                      line_current++;

                      if (line_current == line) {
                        i++;

                        for (; i <= data->contents.array[i].array[0].stop; i++) {
                          if (data->buffer.string[i] == f_string_eos) continue;
                          if (data->buffer.string[i] == f_string_eol) {
                            fprintf(f_standard_output, "%c", f_string_eol);
                            break;
                          }

                          fprintf(f_standard_output, "%c", data->buffer.string[i]);
                        } // for

                        break;
                      }
                    }
                  } // for
                }
              }

              return f_none;
            }

            if (data->contents.array[i].used > 0) {
              f_print_string_dynamic_partial(f_standard_output, data->buffer, data->contents.array[i].array[0]);
            }
            else if (include_empty) {
              fprintf(f_standard_output, "%c", f_string_eol);
            }

            break;
          }

          at++;
        }
      } // for

      return f_none;
    }

    if (data->parameters[fss_basic_list_read_parameter_total].result == f_console_result_found) {
      f_string_length total = 0;

      for (f_string_length i = 0; i < data->objects.used; i++) {
        if (!names[i]) continue;

        if (data->contents.array[i].used == 0) {
          if (include_empty) {
            total++;
          }

          continue;
        }

        for (f_string_length j = data->contents.array[i].array[0].start; j <= data->contents.array[i].array[0].stop; j++) {
          if (data->buffer.string[j] == f_string_eos) continue;

          if (data->buffer.string[j] == f_string_eol) {
            total++;
          }
        } // for
      } // for

      fprintf(f_standard_output, "%llu%c", total, f_string_eol);
      return f_none;
    }

    if (data->parameters[fss_basic_list_read_parameter_line].result == f_console_result_additional) {
      f_string_length line_current = 0;
      f_string_length i = 0;
      f_string_length j = 0;

      for (; i < data->contents.used; i++) {
        if (!names[i]) {
          continue;
        }

        if (data->contents.array[i].used == 0) {
          if (include_empty) {
            if (line_current == line) {
              fprintf(f_standard_output, "%c", f_string_eol);
              break;
            }

            line_current++;
          }

          continue;
        }

        j = data->contents.array[i].array[0].start;

        if (line_current != line) {
          for (; j <= data->contents.array[i].array[0].stop; j++) {
            if (data->buffer.string[j] == f_string_eol) {
              line_current++;

              if (line_current == line) {
                j++;
                break;
              }
            }
          } // for
        }

        if (line_current == line) {
          if (j > data->contents.array[i].array[0].stop) continue;

          for (; j <= data->contents.array[i].array[0].stop; j++) {
            if (data->buffer.string[j] == f_string_eos) continue;

            if (data->buffer.string[j] == f_string_eol) {
              fprintf(f_standard_output, "%c", f_string_eol);
              break;
            }

            fprintf(f_standard_output, "%c", data->buffer.string[j]);
          } // for

          break;
        }
      } // for

      return f_none;
    }

    for (f_string_length i = 0; i < data->contents.used; i++) {
      if (!names[i]) {
        continue;
      }

      if (data->contents.array[i].used == 0) {
        if (include_empty) {
          fprintf(f_standard_output, "%c", f_string_eol);
        }

        continue;
      }

      f_print_string_dynamic_partial(f_standard_output, data->buffer, data->contents.array[i].array[0]);
    } // for

    return f_none;
  }
#endif // _di_fss_basic_list_read_main_process_file_

#ifdef __cplusplus
} // extern "C"
#endif
