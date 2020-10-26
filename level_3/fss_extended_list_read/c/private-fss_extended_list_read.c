#include "fss_extended_list_read.h"
#include "private-fss_extended_list_read.h"

#ifdef __cplusplus
extern "C" {
#endif

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
        fl_color_print(data.error.to.stream, data.context.set.error, "%sUnable to allocate memory.%c", fll_error_print_error, f_string_eol[0]);
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
          fll_error_parameter_integer_print(data.error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_extended_list_read_long_depth, arguments.argv[position_depth]);
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
            fll_error_parameter_integer_print(data.error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_extended_list_read_long_at, arguments.argv[depths->array[i].index_at]);
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
              fl_color_print(data.error.to.stream, data.context.set.error, "%sUnable to allocate memory.%c", fll_error_print_error, f_string_eol[0]);
            }
            else if (status_code == f_string_length_t_size) {
              fl_color_print(data.error.to.stream, data.context.set.error, "%sUnable to process '", fll_error_print_error);
              fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_trim);
              fl_color_print(data.error.to.stream, data.context.set.error, "' because the maximum buffer size was reached.%c", f_string_eol[0]);
            }
            else {
              f_string_t function = "fl_string_append";

              if (data.parameters[fss_extended_list_read_parameter_trim].result == f_console_result_found) {
                function = "fl_string_rip";
              }

              fl_color_print(data.error.to.stream, data.context.set.error, "%sAn unhandled error (", fll_error_print_error);
              fl_color_print(data.error.to.stream, data.context.set.notable, "%u", status_code);
              fl_color_print(data.error.to.stream, data.context.set.error, ") has occurred while calling ");
              fl_color_print(data.error.to.stream, data.context.set.notable, "%s()", function);
              fl_color_print(data.error.to.stream, data.context.set.error, ".%c", f_string_eol[0]);
            }

            return status;
          }

          if (!depths->array[i].value_name.used) {
            fl_color_print(data.error.to.stream, data.context.set.error, "%sThe '", fll_error_print_error);
            fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_name);
            fl_color_print(data.error.to.stream, data.context.set.error, "' must not be an empty string.%c", f_string_eol[0]);

            return F_status_set_error(F_parameter);
          }
        } // for
      }
    } // for

    for (f_array_length_t i = 0; i < depths->used; i++) {

      for (f_array_length_t j = i + 1; j < depths->used; j++) {

        if (depths->array[i].depth == depths->array[j].depth) {
          fl_color_print(data.error.to.stream, data.context.set.error, "%sThe value '", fll_error_print_error);
          fl_color_print(data.error.to.stream, data.context.set.notable, "%llu", depths->array[i].depth);
          fl_color_print(data.error.to.stream, data.context.set.error, "' may only be specified once for the parameter '");
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_depth);
          fl_color_print(data.error.to.stream, data.context.set.error, "'.%c", f_string_eol[0]);

          return F_status_set_error(F_parameter);
        }
        else if (depths->array[i].depth > depths->array[j].depth) {
          fl_color_print(data.error.to.stream, data.context.set.error, "%sThe parameter '", fll_error_print_error);
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_depth);
          fl_color_print(data.error.to.stream, data.context.set.error, "' may not have the value '");
          fl_color_print(data.error.to.stream, data.context.set.notable, "%llu", depths->array[i].depth);
          fl_color_print(data.error.to.stream, data.context.set.error, "' before the value '");
          fl_color_print(data.error.to.stream, data.context.set.notable, "%llu", depths->array[j].depth);
          fl_color_print(data.error.to.stream, data.context.set.error, "'.%c", f_string_eol[0]);

          return F_status_set_error(F_parameter);
        }
      } // for
    } // for

    return F_none;
  }
#endif // _di_fss_extended_list_read_main_preprocess_depth_

#ifndef _di_fss_extended_list_read_main_process_file_
  f_return_status fss_extended_list_read_main_process_file(const f_console_arguments_t arguments, fss_extended_list_read_data_t *data, const f_string_t filename, const fss_extended_list_read_depths_t depths, f_fss_delimits_t *objects_delimits, f_fss_delimits_t *contents_delimits, f_fss_comments_t *comments) {
    f_status_t status = F_none;

    {
      f_string_range_t input = f_macro_string_range_t_initialize(data->buffer.used);

      objects_delimits->used = 0;
      contents_delimits->used = 0;
      comments->used = 0;

      status = fll_fss_extended_list_read(&data->buffer, &input, &data->nest, objects_delimits, contents_delimits, comments);

      if (F_status_is_error(status)) {
        // @todo: detect and replace fll_error_file_type_file with fll_error_file_type_pipe as appropriate.
        fll_error_file_print(data->error, F_status_set_fine(status), "fll_fss_extended_list_read", F_true, filename, "process", fll_error_file_type_file);
      }
      else if (status == F_data_not_stop || status == F_data_not_eos) {
        f_macro_fss_nest_t_delete_simple(data->nest);
        f_macro_string_dynamic_t_delete_simple(data->buffer);

        if (data->parameters[fss_extended_list_read_parameter_total].result == f_console_result_found) {
          fprintf(data->output.stream, "0%c", f_string_eol[0]);
          return F_none;
        }

        return F_status_set_warning(status);
      }

      if (F_status_is_error(status)) {
        f_macro_fss_nest_t_delete_simple(data->nest);
        f_macro_string_dynamic_t_delete_simple(data->buffer);

        return status;
      }

      f_array_length_t i = 0;
      f_array_length_t j = 0;

      // comments are not to be part of the file, so remove them.
      for (; i < comments->used; ++i) {
        for (j = comments->array[i].start; j <= comments->array[i].stop; ++j) {
          data->buffer.string[j] = f_fss_delimit_placeholder;
        } // for
      } // for
    }

    // Requested depths cannot be greater than contents depth.
    if (depths.used > data->nest.used) {
      if (data->parameters[fss_extended_list_read_parameter_total].result == f_console_result_found) {
        fprintf(data->output.stream, "0%c", f_string_eol[0]);
        return F_none;
      }

      return F_none;
    }

    {
      f_number_unsigned_t select = 0;

      if (data->parameters[fss_extended_list_read_parameter_select].result == f_console_result_additional) {
        const f_string_length_t index = data->parameters[fss_extended_list_read_parameter_select].additional.array[data->parameters[fss_extended_list_read_parameter_select].additional.used - 1];
        const f_string_range_t range = f_macro_string_range_t_initialize(strlen(arguments.argv[index]));

        status = fl_conversion_string_to_number_unsigned(arguments.argv[index], &select, range);

        if (F_status_is_error(status)) {
          fll_error_parameter_integer_print(data->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_extended_list_read_long_select, arguments.argv[index]);
          return status;
        }

        // This standard does not support multiple content groups.
        if (select > 0) {
          return F_none;
        }
      }
    }

    f_array_length_t line = 0;

    if (data->parameters[fss_extended_list_read_parameter_line].result == f_console_result_additional) {
      const f_array_length_t index = data->parameters[fss_extended_list_read_parameter_line].additional.array[data->parameters[fss_extended_list_read_parameter_line].additional.used - 1];
      const f_string_range_t range = f_macro_string_range_t_initialize(strlen(arguments.argv[index]));

      status = fl_conversion_string_to_number_unsigned(arguments.argv[index], &line, range);

      if (F_status_is_error(status)) {
        fll_error_parameter_integer_print(data->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_extended_list_read_long_line, arguments.argv[index]);
        return status;
      }
    }

    if (data->parameters[fss_extended_list_read_parameter_depth].result == f_console_result_none || (data->parameters[fss_extended_list_read_parameter_depth].result == f_console_result_additional && depths.used == 1)) {

      fss_extended_list_read_process_delimits(*data, objects_delimits, contents_delimits);

      return fss_extended_list_read_main_process_for_depth(arguments, data, filename, depths.array[0], line, objects_delimits, contents_delimits);
    }

    return F_none;
  }
#endif // _di_fss_extended_list_read_main_process_file_

#ifndef _di_fss_extended_list_read_main_process_for_depth_
  f_return_status fss_extended_list_read_main_process_for_depth(const f_console_arguments_t arguments, fss_extended_list_read_data_t *data, const f_string_t filename, const fss_extended_list_read_depth_t depth_setting, const f_array_length_t line, f_fss_delimits_t *objects_delimits, f_fss_delimits_t *contents_delimits) {
    f_status_t status = F_none;

    f_fss_items_t *items = &data->nest.depth[depth_setting.depth];
    bool names[items->used];

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    const f_string_lengths_t except_none = f_string_lengths_t_initialize;

    if (depth_setting.index_name > 0) {
      memset(names, 0, sizeof(bool) * items->used);

      if (data->parameters[fss_extended_list_read_parameter_trim].result == f_console_result_found) {
        for (i = 0; i < items->used; i++) {

          if (fl_string_dynamic_partial_compare_except_trim_dynamic(depth_setting.value_name, data->buffer, items->array[i].object, except_none, *objects_delimits) == F_equal_to) {
            names[i] = 1;
          }
        } // for
      }
      else {
        for (i = 0; i < items->used; i++) {

          if (fl_string_dynamic_partial_compare_except_dynamic(depth_setting.value_name, data->buffer, items->array[i].object, except_none, *objects_delimits) == F_equal_to) {
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
            fprintf(data->output.stream, "1%c", f_string_eol[0]);
          }
          else {
            fprintf(data->output.stream, "0%c", f_string_eol[0]);
          }

          return F_none;
        }
        else if (depth_setting.index_name > 0) {
          f_array_length_t total = 0;

          for (i = 0; i < items->used; i++) {
            if (!names[i]) continue;

            total++;
          } // for

          fprintf(data->output.stream, "%llu%c", total, f_string_eol[0]);

          return F_none;
        }

        fprintf(data->output.stream, "%llu%c", items->used, f_string_eol[0]);

        return F_none;
      }

      f_return_status (*print_object)(FILE *, const f_string_static_t, const f_string_range_t, const f_string_lengths_t) = &f_print_except_dynamic_partial;

      if (data->parameters[fss_extended_list_read_parameter_trim].result == f_console_result_found) {
        print_object = &fl_print_trim_except_dynamic_partial;
      }

      if (depth_setting.index_at > 0) {
        if (depth_setting.value_at < items->used && names[depth_setting.value_at]) {
          print_object(data->output.stream, data->buffer, items->array[depth_setting.value_at].object, *objects_delimits);

          if (data->parameters[fss_extended_list_read_parameter_content].result == f_console_result_found) {
            fss_extended_list_read_print_object_end(*data);

            if (items->array[depth_setting.value_at].content.used) {
              f_print_except_dynamic_partial(data->output.stream, data->buffer, items->array[depth_setting.value_at].content.array[0], *contents_delimits);
            }
          }

          fss_extended_list_read_print_set_end(*data);
        }

        return F_none;
      }

      for (i = 0; i < items->used; i++) {

        if (names[i]) {
          print_object(data->output.stream, data->buffer, items->array[i].object, *objects_delimits);

          if (data->parameters[fss_extended_list_read_parameter_content].result == f_console_result_found) {
            fss_extended_list_read_print_object_end(*data);

            if (items->array[i].content.used) {
              f_print_except_dynamic_partial(data->output.stream, data->buffer, items->array[i].content.array[0], *contents_delimits);
            }
          }

          fss_extended_list_read_print_set_end(*data);
        }
      } // for

      return F_none;
    }

    if (depth_setting.index_at > 0) {
      if (depth_setting.value_at >= items->used) {
        if (data->parameters[fss_extended_list_read_parameter_total].result == f_console_result_found) {
          fprintf(data->output.stream, "0%c", f_string_eol[0]);
        }

        return F_none;
      }

      f_array_length_t at = 0;

      for (; i < items->used; i++) {

        if (names[i]) {
          if (at == depth_setting.value_at) {
            if (data->parameters[fss_extended_list_read_parameter_total].result == f_console_result_found) {
              if (!items->array[i].content.used) {
                fprintf(data->output.stream, "0%c", f_string_eol[0]);
              }
              else {
                f_array_length_t total = 1;

                for (j = items->array[i].content.array[0].start; j <= items->array[i].content.array[0].stop; j++) {
                  if (!data->buffer.string[j]) continue;

                  if (data->buffer.string[j] == f_string_eol[0]) {
                    total++;
                  }
                } // for

                fprintf(data->output.stream, "%llu%c", total, f_string_eol[0]);
              }

              return F_none;
            }

            if (data->parameters[fss_extended_list_read_parameter_line].result == f_console_result_additional) {
              if (!items->array[i].content.used) {
                if (include_empty && !line) {
                  fss_extended_list_read_print_set_end(*data);
                }
              }
              else {
                i = items->array[i].content.array[0].start;

                if (!line) {
                  for (; i <= items->array[i].content.array[0].stop; i++) {
                    if (!data->buffer.string[i]) continue;

                    if (data->buffer.string[i] == f_string_eol[0]) {
                      fprintf(data->output.stream, "%c", f_string_eol[0]);
                      break;
                    }

                    fprintf(data->output.stream, "%c", data->buffer.string[i]);
                  } // for
                }
                else {
                  f_array_length_t line_current = 0;

                  for (; i <= items->array[i].content.array[0].stop; i++) {
                    if (!data->buffer.string[i]) continue;

                    if (data->buffer.string[i] == f_string_eol[0]) {
                      line_current++;

                      if (line_current == line) {
                        i++;

                        for (; i <= items->array[i].content.array[0].stop; i++) {
                          if (!data->buffer.string[i]) continue;

                          if (data->buffer.string[i] == f_string_eol[0]) {
                            fprintf(data->output.stream, "%c", f_string_eol[0]);
                            break;
                          }

                          fprintf(data->output.stream, "%c", data->buffer.string[i]);
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
              f_print_except_dynamic_partial(data->output.stream, data->buffer, items->array[i].content.array[0], *contents_delimits);
              fss_extended_list_read_print_content_end(*data);
            }
            else if (include_empty) {
              fss_extended_list_read_print_set_end(*data);
            }

            break;
          }

          at++;
        }
      } // for

      return F_none;
    }

    if (data->parameters[fss_extended_list_read_parameter_total].result == f_console_result_found) {
      f_array_length_t total = 0;

      for (i = 0; i < items->used; i++) {
        if (!names[i]) continue;

        if (!items->array[i].content.used) {
          if (include_empty) {
            total++;
          }

          continue;
        }

        for (j = items->array[i].content.array[0].start; j <= items->array[i].content.array[0].stop; j++) {
          if (!data->buffer.string[j]) continue;

          if (data->buffer.string[j] == f_string_eol[0]) {
            total++;
          }
        } // for
      } // for

      fprintf(data->output.stream, "%llu%c", total, f_string_eol[0]);
      return F_none;
    }

    if (data->parameters[fss_extended_list_read_parameter_line].result == f_console_result_additional) {
      f_array_length_t line_current = 0;

      for (; i < items->used; i++) {
        if (!names[i]) continue;

        if (!items->array[i].content.used) {
          if (include_empty) {
            if (line_current == line) {
              fss_extended_list_read_print_set_end(*data);
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
              fprintf(data->output.stream, "%c", f_string_eol[0]);
              break;
            }

            fprintf(data->output.stream, "%c", data->buffer.string[j]);
          } // for

          break;
        }
      } // for

      return F_none;
    }

    for (i = 0; i < items->used; i++) {
      if (!names[i]) continue;

      if (!items->array[i].content.used) {
        if (include_empty) {
          fss_extended_list_read_print_set_end(*data);
        }

        continue;
      }

      f_print_except_dynamic_partial(data->output.stream, data->buffer, items->array[i].content.array[0], *contents_delimits);

      if (data->parameters[fss_extended_list_read_parameter_pipe].result == f_console_result_found) {
        fprintf(data->output.stream, "%c", fss_extended_list_read_pipe_content_end);
      }
    } // for

    return F_none;
  }
#endif // _di_fss_extended_list_read_main_process_for_depth_

#ifndef _di_fss_extended_list_read_print_object_end_
  void fss_extended_list_read_print_object_end(const fss_extended_list_read_data_t data) {

    if (data.parameters[fss_extended_list_read_parameter_pipe].result == f_console_result_found) {
      fprintf(data.output.stream, "%c", fss_extended_list_read_pipe_content_start);
    }
    else {
      if (data.parameters[fss_extended_list_read_parameter_object].result == f_console_result_found && data.parameters[fss_extended_list_read_parameter_content].result == f_console_result_found) {
        fprintf(data.output.stream, "%c%c", f_fss_extended_list_open, f_fss_extended_list_open_end);
      }
      else {
        fprintf(data.output.stream, "%c", f_fss_eol);
      }
    }
  }
#endif // _di_fss_extended_list_read_print_object_end_

#ifndef _di_fss_extended_list_read_print_content_end_
  void fss_extended_list_read_print_content_end(const fss_extended_list_read_data_t data) {

    if (data.parameters[fss_extended_list_read_parameter_pipe].result == f_console_result_found) {
      fprintf(data.output.stream, "%c", fss_extended_list_read_pipe_content_start);
    }
    else {
      if (data.parameters[fss_extended_list_read_parameter_object].result == f_console_result_found && data.parameters[fss_extended_list_read_parameter_content].result == f_console_result_found) {
        fprintf(data.output.stream, "%c%c", f_fss_extended_list_close, f_fss_extended_list_close_end);
      }
      else {
        fprintf(data.output.stream, "%c", f_fss_eol);
      }
    }
  }
#endif // _di_fss_extended_list_read_print_content_end_

#ifndef _di_fss_extended_list_read_print_content_ignore_
  void fss_extended_list_read_print_content_ignore(const fss_extended_list_read_data_t data) {

    if (data.parameters[fss_extended_list_read_parameter_pipe].result == f_console_result_found) {
      fprintf(data.output.stream, "%c", fss_extended_list_read_pipe_content_ignore);
    }
  }
#endif // _di_fss_extended_list_read_print_content_ignore_

#ifndef _di_fss_extended_list_read_print_set_end_
  void fss_extended_list_read_print_set_end(const fss_extended_list_read_data_t data) {

    if (data.parameters[fss_extended_list_read_parameter_pipe].result == f_console_result_found) {
      fprintf(data.output.stream, "%c", fss_extended_list_read_pipe_content_end);
    }
    else {
      if (data.parameters[fss_extended_list_read_parameter_object].result == f_console_result_found && data.parameters[fss_extended_list_read_parameter_content].result == f_console_result_found) {
        fprintf(data.output.stream, "%c%c", f_fss_extended_list_close, f_fss_extended_list_close_end);
      }
      else {
        fprintf(data.output.stream, "%c", f_fss_eol);
      }
    }
  }
#endif // _di_fss_extended_list_read_print_set_end_

#ifndef _di_fss_extended_list_read_process_delimits_
  void fss_extended_list_read_process_delimits(const fss_extended_list_read_data_t data, f_fss_delimits_t *objects_delimits, f_fss_delimits_t *contents_delimits) {

    if (!data.nest.used) return;

    if ((!objects_delimits->used && !contents_delimits->used) || data.delimit_mode == fss_extended_list_read_delimit_mode_all) return;

    if (data.delimit_mode == fss_extended_list_read_delimit_mode_depth_lesser && data.nest.used < data.delimit_depth) return;
    if (data.delimit_mode == fss_extended_list_read_delimit_mode_depth_greater && data.delimit_depth == 0) return;

    if (data.delimit_mode == fss_extended_list_read_delimit_mode_none) {
      objects_delimits->used = 0;
      contents_delimits->used = 0;
      return;
    }

    if (data.delimit_mode == fss_extended_list_read_delimit_mode_depth || data.delimit_mode == fss_extended_list_read_delimit_mode_depth_greater) {
      if (data.delimit_depth >= data.nest.used) {
        objects_delimits->used = 0;
        contents_delimits->used = 0;
        return;
      }
    }

    const f_string_length_t original_objects_used = objects_delimits->used;
    const f_string_length_t original_contents_used = contents_delimits->used;

    f_string_length_t original_objects_delimits[original_objects_used];
    f_string_length_t original_contents_delimits[original_contents_used];

    memcpy(&original_objects_delimits, objects_delimits->array, original_objects_used * sizeof(f_string_length_t));
    memcpy(&original_contents_delimits, contents_delimits->array, original_contents_used * sizeof(f_string_length_t));

    objects_delimits->used = 0;
    contents_delimits->used = 0;

    if (data.delimit_mode == fss_extended_list_read_delimit_mode_depth) {

      // only depth 0 objects are stored in objects_delimits.
      if (data.delimit_depth) {
        fss_extended_list_read_process_delimits_objects(data, data.delimit_depth, original_contents_delimits, original_contents_used, contents_delimits);
      }
      else {
        fss_extended_list_read_process_delimits_objects(data, data.delimit_depth, original_objects_delimits, original_objects_used, objects_delimits);
      }

      fss_extended_list_read_process_delimits_contents(data, data.delimit_depth, original_contents_delimits, original_contents_used, contents_delimits);
    }
    else {

      if (data.delimit_mode == fss_extended_list_read_delimit_mode_depth_lesser) {

        // only depth 0 objects are stored in objects_delimits.
        fss_extended_list_read_process_delimits_objects(data, 0, original_objects_delimits, original_objects_used, objects_delimits);
        fss_extended_list_read_process_delimits_contents(data, 0, original_contents_delimits, original_contents_used, contents_delimits);

        for (f_array_length_t i = 1; i <= data.delimit_depth && i < data.nest.used; ++i) {

          fss_extended_list_read_process_delimits_objects(data, i, original_contents_delimits, original_contents_used, contents_delimits);
          fss_extended_list_read_process_delimits_contents(data, i, original_contents_delimits, original_contents_used, contents_delimits);
        } // for
      }
      else if (data.delimit_mode == fss_extended_list_read_delimit_mode_depth_greater) {
        for (f_array_length_t i = data.delimit_depth; i < data.nest.used; ++i) {

          fss_extended_list_read_process_delimits_objects(data, i, original_contents_delimits, original_contents_used, contents_delimits);
          fss_extended_list_read_process_delimits_contents(data, i, original_contents_delimits, original_contents_used, contents_delimits);
        } // for
      }
    }
  }
#endif // _di_fss_extended_list_read_process_delimits_

#ifndef _di_fss_extended_list_read_process_delimits_contents_
  void fss_extended_list_read_process_delimits_contents(const fss_extended_list_read_data_t data, const f_string_length_t depth, const f_string_length_t original_delimits[], const f_string_length_t original_used, f_fss_delimits_t *delimits) {

    if (!original_used) return;

    f_fss_items_t *items = &data.nest.depth[depth];

    if (!items->used) return;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;
    f_array_length_t l = 0;
    f_array_length_t m = 0;

    for (i = 0; i < items->used; ++i) {

      for (j = 0; j < original_used; ++j) {

        for (k = 0; k < items->array[i].content.used; ++k) {

          if (original_delimits[j] >= items->array[i].content.array[k].start && original_delimits[j] <= items->array[i].content.array[k].stop) {

            // preserve linear order when adding back delimits.
            if (delimits->used) {
              for (l = 0; l < delimits->used; ++l) {

                if (original_delimits[j] > delimits->array[l]) continue;
                if (original_delimits[j] == delimits->array[l]) break;

                for (m = delimits->used; m > l; --m) {
                  delimits->array[m] = delimits->array[m - 1];
                } // for

                if (fss_extended_list_read_process_delimits_within_greater(data, depth, original_delimits[j]) == F_false) {
                  delimits->array[l] = original_delimits[j];
                  delimits->used++;
                }

                break;
              } // for
            }
            else if (fss_extended_list_read_process_delimits_within_greater(data, depth, original_delimits[j]) == F_false) {
              delimits->array[0] = original_delimits[j];
              delimits->used = 1;
            }
          }
        }
      } // for
    } // for
  }
#endif // _di_fss_extended_list_read_process_delimits_contents_

#ifndef _di_fss_extended_list_read_process_delimits_objects_
  void fss_extended_list_read_process_delimits_objects(const fss_extended_list_read_data_t data, const f_string_length_t depth, const f_string_length_t original_delimits[], const f_string_length_t original_used, f_fss_delimits_t *delimits) {

    if (!original_used) return;

    f_fss_items_t *items = &data.nest.depth[depth];

    if (!items->used) return;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;
    f_array_length_t l = 0;

    for (i = 0; i < items->used; ++i) {

      for (j = 0; j < original_used; ++j) {

        if (original_delimits[j] >= items->array[i].object.start && original_delimits[j] <= items->array[i].object.stop) {

          // preserve linear order when adding back delimits.
          if (delimits->used) {
            for (k = 0; k < delimits->used; ++k) {

              if (original_delimits[j] > delimits->array[k]) continue;
              if (original_delimits[j] == delimits->array[k]) break;

              for (l = delimits->used; l > k; --l) {
                delimits->array[l] = delimits->array[l - 1];
              } // for

              if (fss_extended_list_read_process_delimits_within_greater(data, depth, original_delimits[j]) == F_false) {
                delimits->array[k] = original_delimits[j];
                delimits->used++;
              }

              break;
            } // for
          }
          else if (fss_extended_list_read_process_delimits_within_greater(data, depth, original_delimits[j]) == F_false) {
            delimits->array[0] = original_delimits[j];
            delimits->used = 1;
          }
        }
      } // for
    } // for
  }
#endif // _di_fss_extended_list_read_process_delimits_objects_

#ifndef _di_fss_extended_list_read_process_delimits_within_greater_
  f_return_status fss_extended_list_read_process_delimits_within_greater(const fss_extended_list_read_data_t data, const f_string_length_t depth, const f_string_length_t location) {

    if (depth + 1 >= data.nest.used) return F_false;

    f_fss_items_t *items = 0;

    f_string_length_t i = 0;
    f_string_length_t j = 0;

    for (f_string_length_t d = depth + 1; d < data.nest.used; ++d) {
      items = &data.nest.depth[d];

      for (i = 0; i < items->used; ++i) {

        for (j = 0; j < items->array[i].content.used; ++j) {

          if (location >= items->array[i].content.array[j].start && location <= items->array[i].content.array[j].stop) {
            return F_true;
          }
        } // for
      } // for
    } // for

    return F_false;
  }
#endif // _di_fss_extended_list_read_process_delimits_within_greater_

#ifdef __cplusplus
} // extern "C"
#endif
