#include "fss_extended_list_read.h"
#include "private-fss_extended_list_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_list_read_print_file_error_
  void fss_extended_list_read_print_file_error(const f_color_context_t context, const f_string_t function_name, const f_string_t file_name, const f_status_t status) {

    if (fll_file_error_print(f_type_error, context, function_name, file_name, status) == F_false) {
      fl_color_print(f_type_error, context.set.error, "INTERNAL ERROR: An unhandled error (");
      fl_color_print(f_type_error, context.set.notable, "%llu", status);
      fl_color_print(f_type_error, context.set.error, ") has occurred while calling ");
      fl_color_print(f_type_error, context.set.notable, "%s()", function_name);
      fl_color_print_line(f_type_error, context.set.error, ".");
    }
  }
#endif // _di_fss_extended_list_read_print_file_error_

#ifndef _di_fss_extended_list_read_print_number_argument_error_
  void fss_extended_list_read_print_number_argument_error(const f_color_context_t context, const f_string_t function_name, const f_string_t parameter_name, const f_string_t argument, const f_status_t status) {

    if (status == F_parameter) {
      fl_color_print(f_type_error, context.set.error, "INTERNAL ERROR: Invalid parameter when calling ");
      fl_color_print(f_type_error, context.set.notable, "%s()", function_name);
      fl_color_print_line(f_type_error, context.set.error, ".");
    }
    else if (status == F_number) {
      fl_color_print(f_type_error, context.set.error, "ERROR: The argument '");
      fl_color_print(f_type_error, context.set.notable, "%s", argument);
      fl_color_print(f_type_error, context.set.error, "' is not a valid number for the parameter '");
      fl_color_print(f_type_error, context.set.notable, "%s%s", f_console_symbol_long_enable, parameter_name);
      fl_color_print_line(f_type_error, context.set.error, "'.");
    }
    else if (status == F_number_underflow) {
      fl_color_print(f_type_error, context.set.error, "ERROR: The argument '");
      fl_color_print(f_type_error, context.set.notable, "%s", argument);
      fl_color_print(f_type_error, context.set.error, "' is too small for the parameter '");
      fl_color_print(f_type_error, context.set.notable, "%s%s", f_console_symbol_long_enable, parameter_name);
      fl_color_print_line(f_type_error, context.set.error, "'.");
    }
    else if (status == F_number_overflow) {
      fl_color_print(f_type_error, context.set.error, "ERROR: The argument '");
      fl_color_print(f_type_error, context.set.notable, "%s", argument);
      fl_color_print(f_type_error, context.set.error, "' is too large for the parameter '");
      fl_color_print(f_type_error, context.set.notable, "%s%s", f_console_symbol_long_enable, parameter_name);
      fl_color_print_line(f_type_error, context.set.error, "'.");
    }
    else if (status == F_number_negative) {
      fl_color_print(f_type_error, context.set.error, "ERROR: The argument '");
      fl_color_print(f_type_error, context.set.notable, "%s", argument);
      fl_color_print(f_type_error, context.set.error, "' is negative, which is not allowed for the parameter '");
      fl_color_print(f_type_error, context.set.notable, "%s%s", f_console_symbol_long_enable, parameter_name);
      fl_color_print_line(f_type_error, context.set.error, "'.");
    }
    else if (status == F_number_positive) {
      fl_color_print(f_type_error, context.set.error, "ERROR: The argument '");
      fl_color_print(f_type_error, context.set.notable, "%s", argument);
      fl_color_print(f_type_error, context.set.error, "' contains a '");
      fl_color_print(f_type_error, context.set.notable, "+");
      fl_color_print(f_type_error, context.set.error, "', which is not allowed for the parameter '");
      fl_color_print(f_type_error, context.set.notable, "%s%s", f_console_symbol_long_enable, parameter_name);
      fl_color_print_line(f_type_error, context.set.error, "'.");
    }
    else if (status == F_data_not) {
      fl_color_print(f_type_error, context.set.error, "ERROR: The parameter '");
      fl_color_print(f_type_error, context.set.notable, "%s%s", f_console_symbol_long_enable, parameter_name);
      fl_color_print_line(f_type_error, context.set.error, "' must not be an empty string.");
    }
    else {
      fl_color_print(f_type_error, context.set.error, "INTERNAL ERROR: An unhandled error (");
      fl_color_print(f_type_error, context.set.notable, "%llu", status);
      fl_color_print(f_type_error, context.set.error, ") has occurred while calling ");
      fl_color_print(f_type_error, context.set.notable, "%s()", function_name);
      fl_color_print(f_type_error, context.set.error, "' for the parameter '");
      fl_color_print(f_type_error, context.set.notable, "%s%s", f_console_symbol_long_enable, parameter_name);
      fl_color_print(f_type_error, context.set.error, "' with the value '");
      fl_color_print(f_type_error, context.set.notable, "%s", argument);
      fl_color_print_line(f_type_error, context.set.error, "'.");
    }
  }
#endif // _di_fss_extended_list_read_print_number_argument_error_

#ifndef _di_fss_extended_list_read_main_preprocess_depth_
  f_return_status fss_extended_list_read_main_preprocess_depth(const f_console_arguments_t arguments, const fss_extended_list_read_data_t data, fss_extended_list_read_depths_t *depths) {
    f_status_t status = F_none;

    {
      f_array_length_t depth_size = 1;

      if (data.parameters[fss_extended_list_read_parameter_depth].result == f_console_result_additional) {
        depth_size = data.parameters[fss_extended_list_read_parameter_depth].additional.used;
      }

      macro_fss_extended_list_read_depths_t_new(status, (*depths), depth_size);

      if (F_status_is_error(status)) {
        fl_color_print_line(f_type_error, data.context.set.error, "CRITICAL ERROR: Unable to allocate memory.");
        return status;
      }

      depths->used = depth_size;
    }

    f_array_length_t position_depth = 0;
    f_array_length_t position_at = 0;
    f_array_length_t position_name = 0;

    for (f_array_length_t i = 0; i < depths->used; i++) {
      depths->array[i].depth = 0;
      depths->array[i].index_at = 0;
      depths->array[i].index_name = 0;
      depths->array[i].value_at = 0;

      f_macro_string_dynamic_t_clear(depths->array[i].value_name);

      if (!data.parameters[fss_extended_list_read_parameter_depth].additional.used) {
        position_depth = 0;
      }
      else {
        position_depth = data.parameters[fss_extended_list_read_parameter_depth].additional.array[i];

        const f_string_range_t range = f_macro_string_range_t_initialize(strlen(arguments.argv[position_depth]));

        status = fl_conversion_string_to_number_unsigned(arguments.argv[position_depth], &depths->array[i].depth, range);

        if (F_status_is_error(status)) {
          fss_extended_list_read_print_number_argument_error(data.context, "fl_conversion_string_to_number_unsigned", fss_extended_list_read_long_depth, arguments.argv[position_depth], F_status_set_fine(status));
          return status;
        }
      }

      if (data.parameters[fss_extended_list_read_parameter_at].result == f_console_result_additional) {
        for (; position_at < data.parameters[fss_extended_list_read_parameter_at].additional.used; position_at++) {

          if (data.parameters[fss_extended_list_read_parameter_at].additional.array[position_at] < position_depth) {
            continue;
          }

          if (i + 1 < depths->used && data.parameters[fss_extended_list_read_parameter_at].additional.array[position_at] > data.parameters[fss_extended_list_read_parameter_depth].additional.array[i + 1]) {
            break;
          }

          depths->array[i].index_at = data.parameters[fss_extended_list_read_parameter_at].additional.array[position_at];

          const f_string_range_t range = f_macro_string_range_t_initialize(strlen(arguments.argv[depths->array[i].index_at]));

          status = fl_conversion_string_to_number_unsigned(arguments.argv[depths->array[i].index_at], &depths->array[i].value_at, range);

          if (F_status_is_error(status)) {
            fss_extended_list_read_print_number_argument_error(data.context, "fl_conversion_string_to_number_unsigned", fss_extended_list_read_long_at, arguments.argv[depths->array[i].index_at], F_status_set_fine(status));
            return status;
          }
        } // for
      }

      if (data.parameters[fss_extended_list_read_parameter_name].result == f_console_result_additional) {
        for (; position_name < data.parameters[fss_extended_list_read_parameter_name].additional.used; position_name++) {

          if (data.parameters[fss_extended_list_read_parameter_name].additional.array[position_name] < position_depth) {
            continue;
          }

          if (i + 1 < depths->used && data.parameters[fss_extended_list_read_parameter_name].additional.array[position_name] > data.parameters[fss_extended_list_read_parameter_depth].additional.array[i + 1]) {
            break;
          }

          depths->array[i].index_name = data.parameters[fss_extended_list_read_parameter_name].additional.array[position_name];

          if (data.parameters[fss_extended_list_read_parameter_trim].result == f_console_result_found) {
            status = fl_string_rip(arguments.argv[depths->array[i].index_name], strlen(arguments.argv[depths->array[i].index_name]), &depths->array[i].value_name);
          }
          else {
            status = fl_string_append(arguments.argv[depths->array[i].index_name], strlen(arguments.argv[depths->array[i].index_name]), &depths->array[i].value_name);
          }

          if (F_status_is_error(status)) {
            f_status_t status_code = F_status_set_fine(status);

            // @todo: move error printing into common function.
            if (status_code == F_memory_allocation || status_code == F_memory_reallocation) {
              fl_color_print_line(f_type_error, data.context.set.error, "CRITICAL ERROR: Unable to allocate memory.");
            }
            else if (status_code == f_string_length_t_size) {
              fl_color_print(f_type_error, data.context.set.error, "ERROR: Unable to process '");
              fl_color_print(f_type_error, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_trim);
              fl_color_print_line(f_type_error, data.context.set.error, "' because the maximum buffer size was reached.");
            }
            else {
              f_string_t function = "fl_string_append";

              if (data.parameters[fss_extended_list_read_parameter_trim].result == f_console_result_found) {
                function = "fl_string_rip";
              }

              fl_color_print(f_type_error, data.context.set.error, "INTERNAL ERROR: An unhandled error (");
              fl_color_print(f_type_error, data.context.set.notable, "%u", status_code);
              fl_color_print(f_type_error, data.context.set.error, ") has occurred while calling ");
              fl_color_print(f_type_error, data.context.set.notable, "%s()", function);
              fl_color_print_line(f_type_error, data.context.set.error, ".");
            }

            return status;
          }

          if (!depths->array[i].value_name.used) {
            fl_color_print(f_type_error, data.context.set.error, "ERROR: The '");
            fl_color_print(f_type_error, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_name);
            fl_color_print_line(f_type_error, data.context.set.error, "' must not be an empty string.");

            return F_status_set_error(F_parameter);
          }
        } // for
      }
    } // for

    for (f_array_length_t i = 0; i < depths->used; i++) {

      for (f_array_length_t j = i + 1; j < depths->used; j++) {

        if (depths->array[i].depth == depths->array[j].depth) {
          fl_color_print(f_type_error, data.context.set.error, "ERROR: The value '");
          fl_color_print(f_type_error, data.context.set.notable, "%llu", depths->array[i].depth);
          fl_color_print(f_type_error, data.context.set.error, "' may only be specified once for the parameter '");
          fl_color_print(f_type_error, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_depth);
          fl_color_print_line(f_type_error, data.context.set.error, "'.");

          return F_status_set_error(F_parameter);
        }
        else if (depths->array[i].depth > depths->array[j].depth) {
          fl_color_print(f_type_error, data.context.set.error, "ERROR: The parameter '");
          fl_color_print(f_type_error, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_depth);
          fl_color_print(f_type_error, data.context.set.error, "' may not have the value '");
          fl_color_print(f_type_error, data.context.set.notable, "%llu", depths->array[i].depth);
          fl_color_print(f_type_error, data.context.set.error, "' before the value '");
          fl_color_print(f_type_error, data.context.set.notable, "%llu", depths->array[j].depth);
          fl_color_print_line(f_type_error, data.context.set.error, "'.");

          return F_status_set_error(F_parameter);
        }
      } // for
    } // for

    return F_none;
  }
#endif // _di_fss_extended_list_read_main_preprocess_depth_

#ifndef _di_fss_extended_list_read_main_process_file_
  f_return_status fss_extended_list_read_main_process_file(const f_console_arguments_t arguments, fss_extended_list_read_data_t *data, const f_string_t filename, const fss_extended_list_read_depths_t depths) {
    f_status_t status = F_none;

    {
      f_string_range_t input = f_string_range_t_initialize;

      input.start = 0;
      input.stop = data->buffer.used - 1;

      status = fll_fss_extended_list_read(&data->buffer, &input, &data->nest);

      if (F_status_is_error(status)) {
        status = F_status_set_fine(status);

        if (status == F_parameter) {
          fl_color_print(f_type_error, data->context.set.error, "INTERNAL ERROR: Invalid parameter when calling ");
          fl_color_print(f_type_error, data->context.set.notable, "fll_fss_extended_list_read()");
          fl_color_print(f_type_error, data->context.set.error, " for the file '");
          fl_color_print(f_type_error, data->context.set.notable, "%s", filename);
          fl_color_print_line(f_type_error, data->context.set.error, "'.");
        }
        else if (status == F_memory_allocation || status == F_memory_reallocation) {
          fl_color_print_line(f_type_error, data->context.set.error, "CRITICAL ERROR: Unable to allocate memory.");
        }
        else if (status == F_incomplete_utf_stop) {
          fl_color_print(f_type_error, data->context.set.error, "ENCODING ERROR: Error occurred on invalid UTF-8 character at stop position (at ");
          fl_color_print(f_type_error, data->context.set.notable, "%d", input.start);
          fl_color_print_line(f_type_error, data->context.set.error, ").");
        }
        else if (status == F_incomplete_utf_eos) {
          fl_color_print(f_type_error, data->context.set.error, "ENCODING ERROR: Error occurred on invalid UTF-8 character at end of string (at ");
          fl_color_print(f_type_error, data->context.set.notable, "%d", input.start);
          fl_color_print_line(f_type_error, data->context.set.error, ").");
        }
        else {
          fl_color_print(f_type_error, data->context.set.error, "INTERNAL ERROR: An unhandled error (");
          fl_color_print(f_type_error, data->context.set.notable, "%u", status);
          fl_color_print(f_type_error, data->context.set.error, ") has occurred while calling ");
          fl_color_print(f_type_error, data->context.set.notable, "fll_fss_extended_list_read()");
          fl_color_print(f_type_error, data->context.set.error, " for the file '");
          fl_color_print(f_type_error, data->context.set.notable, "%s", filename);
          fl_color_print_line(f_type_error, data->context.set.error, "'.");
        }

        return F_status_set_error(status);
      }
      else if (status == F_data_not_stop || status == F_data_not_eos) {
        // Clear buffers, then attempt the next file.
        f_macro_fss_nest_t_delete_simple(data->nest);
        f_macro_string_dynamic_t_delete_simple(data->buffer);

        return F_status_set_warning(status);
      }
    }

    // Requested depths cannot be greater than contents depth.
    if (depths.used > data->nest.used) {
      if (data->parameters[fss_extended_list_read_parameter_total].result == f_console_result_found) {
        fprintf(f_type_output, "0%c", f_string_eol[0]);
        return F_none;
      }

      return F_none;
    }

    {
      f_string_length_t select = 0;

      if (data->parameters[fss_extended_list_read_parameter_select].result == f_console_result_additional) {
        const f_string_length_t index = data->parameters[fss_extended_list_read_parameter_select].additional.array[data->parameters[fss_extended_list_read_parameter_select].additional.used - 1];
        const f_string_range_t range = f_macro_string_range_t_initialize(strlen(arguments.argv[index]));

        status = fl_conversion_string_to_number_unsigned(arguments.argv[index], &select, range);

        if (F_status_is_error(status)) {
          fss_extended_list_read_print_number_argument_error(data->context, "fl_conversion_string_to_number_unsigned", fss_extended_list_read_long_select, arguments.argv[index], F_status_set_fine(status));
          return status;
        }

        // This standard does not support multiple content groups.
        if (select > 0) {
          return F_none;
        }
      }
    }

    f_string_length_t line = 0;

    if (data->parameters[fss_extended_list_read_parameter_line].result == f_console_result_additional) {
      const f_string_length_t index = data->parameters[fss_extended_list_read_parameter_line].additional.array[data->parameters[fss_extended_list_read_parameter_line].additional.used - 1];
      const f_string_range_t range = f_macro_string_range_t_initialize(strlen(arguments.argv[index]));

      f_number_unsigned_t number = 0;

      status = fl_conversion_string_to_number_unsigned(arguments.argv[index], &number, range);

      if (F_status_is_error(status)) {
        fss_extended_list_read_print_number_argument_error(data->context, "fl_conversion_string_to_number_unsigned", fss_extended_list_read_long_line, arguments.argv[index], F_status_set_fine(status));
        return status;
      }
    }

    if (data->parameters[fss_extended_list_read_parameter_depth].result == f_console_result_none || (data->parameters[fss_extended_list_read_parameter_depth].result == f_console_result_additional && depths.used == 1)) {
      return fss_extended_list_read_main_process_for_depth(arguments, data, filename, depths.array[0], line);
    }

    // @todo: handle recursive situations, possibly calling the above block as a separate private function.

    return F_none;
  }
#endif // _di_fss_extended_list_read_main_process_file_

#ifndef _di_fss_extended_list_read_main_process_for_depth_
  f_return_status fss_extended_list_read_main_process_for_depth(const f_console_arguments_t arguments, fss_extended_list_read_data_t *data, const f_string_t filename, const fss_extended_list_read_depth_t depth_setting, const f_string_length_t line) {
    f_status_t status = F_none;

    f_fss_items_t *items = &data->nest.depth[depth_setting.depth];
    bool names[items->used];

    if (depth_setting.index_name > 0) {
      memset(names, 0, sizeof(bool) * items->used);

      f_string_range_t value_range = f_string_range_t_initialize;
      value_range.stop = depth_setting.value_name.used - 1;

      if (data->parameters[fss_extended_list_read_parameter_trim].result == f_console_result_found) {
        for (f_string_length_t i = 0; i < items->used; i++) {
          if (fl_string_dynamic_partial_compare_trim(data->buffer, depth_setting.value_name, items->array[i].object, value_range) == F_equal_to) {
            names[i] = 1;
          }
        } // for
      }
      else {
        for (f_string_length_t i = 0; i < items->used; i++) {
          if (fl_string_dynamic_partial_compare(data->buffer, depth_setting.value_name, items->array[i].object, value_range) == F_equal_to) {
            names[i] = 1;
          }
        } // for
      }
    }
    else {
      memset(names, 1, sizeof(bool) * items->used);
    }

    bool include_empty = 0;

    if (data->parameters[fss_extended_list_read_parameter_empty].result == f_console_result_found) {
      include_empty = 1;
    }

    if (data->parameters[fss_extended_list_read_parameter_object].result == f_console_result_found) {
      if (data->parameters[fss_extended_list_read_parameter_total].result == f_console_result_found) {

        if (depth_setting.index_at > 0) {
          if (depth_setting.value_at < items->used && names[depth_setting.value_at]) {
            fprintf(f_type_output, "1%c", f_string_eol[0]);
          }
          else {
            fprintf(f_type_output, "0%c", f_string_eol[0]);
          }

          return F_none;
        }
        else if (depth_setting.index_name > 0) {
          f_string_length_t total = 0;

          for (f_string_length_t i = 0; i < items->used; i++) {
            if (!names[i]) continue;

            total++;
          } // for

          fprintf(f_type_output, "%llu%c", total, f_string_eol[0]);

          return F_none;
        }

        fprintf(f_type_output, "%llu%c", items->used, f_string_eol[0]);

        return F_none;
      }

      f_return_status (*print_object)(FILE *, const f_string_static_t, const f_string_range_t) = &f_print_dynamic_partial;

      if (data->parameters[fss_extended_list_read_parameter_trim].result == f_console_result_found) {
        print_object = &fl_print_trim_string_dynamic_partial;
      }

      if (depth_setting.index_at > 0) {
        if (depth_setting.value_at < items->used && names[depth_setting.value_at]) {
          print_object(f_type_output, data->buffer, items->array[depth_setting.value_at].object);
          fprintf(f_type_output, "%c", f_string_eol[0]);
        }

        return F_none;
      }

      for (f_array_length_t i = 0; i < items->used; i++) {

        if (names[i]) {
          print_object(f_type_output, data->buffer, items->array[i].object);
          fprintf(f_type_output, "%c", f_string_eol[0]);
        }
      } // for

      return F_none;
    }

    if (depth_setting.index_at > 0) {
      if (depth_setting.value_at >= items->used) {
        if (names[depth_setting.value_at] && data->parameters[fss_extended_list_read_parameter_total].result == f_console_result_found) {
          fprintf(f_type_output, "0%c", f_string_eol[0]);
        }

        return F_none;
      }

      f_array_length_t at = 0;
      f_array_length_t i = 0;

      for (; i < items->used; i++) {

        if (names[i]) {
          if (at == depth_setting.value_at) {
            if (data->parameters[fss_extended_list_read_parameter_total].result == f_console_result_found) {
              if (!items->array[i].content.used) {
                fprintf(f_type_output, "0%c", f_string_eol[0]);
              }
              else {
                f_string_length_t total = 1;

                for (f_string_length_t j = items->array[i].content.array[0].start; j <= items->array[i].content.array[0].stop; j++) {
                  if (!data->buffer.string[j]) continue;

                  if (data->buffer.string[j] == f_string_eol[0]) {
                    total++;
                  }
                } // for

                fprintf(f_type_output, "%llu%c", total, f_string_eol[0]);
              }

              return F_none;
            }

            if (data->parameters[fss_extended_list_read_parameter_line].result == f_console_result_additional) {
              if (!items->array[i].content.used) {
                if (include_empty && !line) {
                  fprintf(f_type_output, "%c", f_string_eol[0]);
                }
              }
              else {
                f_string_length_t i = items->array[i].content.array[0].start;

                if (!line) {
                  for (; i <= items->array[i].content.array[0].stop; i++) {
                    if (!data->buffer.string[i]) continue;

                    if (data->buffer.string[i] == f_string_eol[0]) {
                      fprintf(f_type_output, "%c", f_string_eol[0]);
                      break;
                    }

                    fprintf(f_type_output, "%c", data->buffer.string[i]);
                  } // for
                }
                else {
                  f_string_length_t line_current = 0;

                  for (; i <= items->array[i].content.array[0].stop; i++) {
                    if (!data->buffer.string[i]) continue;

                    if (data->buffer.string[i] == f_string_eol[0]) {
                      line_current++;

                      if (line_current == line) {
                        i++;

                        for (; i <= items->array[i].content.array[0].stop; i++) {
                          if (!data->buffer.string[i]) continue;

                          if (data->buffer.string[i] == f_string_eol[0]) {
                            fprintf(f_type_output, "%c", f_string_eol[0]);
                            break;
                          }

                          fprintf(f_type_output, "%c", data->buffer.string[i]);
                        } // for

                        break;
                      }
                    }
                  } // for
                }
              }

              return F_none;
            }

            if (items->array[i].content.used > 0) {
              f_print_dynamic_partial(f_type_output, data->buffer, items->array[i].content.array[0]);
            }
            else if (include_empty) {
              fprintf(f_type_output, "%c", f_string_eol[0]);
            }

            break;
          }

          at++;
        }
      } // for

      return F_none;
    }

    if (data->parameters[fss_extended_list_read_parameter_total].result == f_console_result_found) {
      f_string_length_t total = 0;

      for (f_string_length_t i = 0; i < items->used; i++) {
        if (!names[i]) continue;

        if (!items->array[i].content.used) {
          if (include_empty) {
            total++;
          }

          continue;
        }

        for (f_string_length_t j = items->array[i].content.array[0].start; j <= items->array[i].content.array[0].stop; j++) {
          if (!data->buffer.string[j]) continue;

          if (data->buffer.string[j] == f_string_eol[0]) {
            total++;
          }
        } // for
      } // for

      fprintf(f_type_output, "%llu%c", total, f_string_eol[0]);
      return F_none;
    }

    if (data->parameters[fss_extended_list_read_parameter_line].result == f_console_result_additional) {
      f_string_length_t line_current = 0;
      f_string_length_t i = 0;
      f_string_length_t j = 0;

      for (; i < items->used; i++) {
        if (!names[i]) continue;

        if (!items->array[i].content.used) {
          if (include_empty) {
            if (line_current == line) {
              fprintf(f_type_output, "%c", f_string_eol[0]);
              break;
            }

            line_current++;
          }

          continue;
        }

        j = items->array[i].content.array[0].start;

        if (line_current != line) {
          for (; j <= items->array[i].content.array[0].stop; j++) {
            if (data->buffer.string[j] == f_string_eol[0]) {
              line_current++;

              if (line_current == line) {
                j++;
                break;
              }
            }
          } // for
        }

        if (line_current == line) {
          if (j > items->array[i].content.array[0].stop) continue;

          for (; j <= items->array[i].content.array[0].stop; j++) {
            if (!data->buffer.string[j]) continue;

            if (data->buffer.string[j] == f_string_eol[0]) {
              fprintf(f_type_output, "%c", f_string_eol[0]);
              break;
            }

            fprintf(f_type_output, "%c", data->buffer.string[j]);
          } // for

          break;
        }
      } // for

      return F_none;
    }

    for (f_string_length_t i = 0; i < items->used; i++) {
      if (!names[i]) continue;

      if (!items->array[i].content.used) {
        if (include_empty) {
          fprintf(f_type_output, "%c", f_string_eol[0]);
        }

        continue;
      }

      f_print_dynamic_partial(f_type_output, data->buffer, items->array[i].content.array[0]);
    } // for

    return F_none;
  }
#endif // _di_fss_extended_list_read_main_process_for_depth_

#ifdef __cplusplus
} // extern "C"
#endif
