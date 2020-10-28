#include "fss_extended_list_read.h"
#include "private-fss_extended_list_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_list_read_main_preprocess_depth_
  f_return_status fss_extended_list_read_main_preprocess_depth(const f_console_arguments_t arguments, const fss_extended_list_read_data_t data, fss_extended_list_read_depths_t *depths) {
    f_status_t status = F_none;

    const f_array_length_t values_total = data.parameters[fss_extended_list_read_parameter_depth].values.used + data.parameters[fss_extended_list_read_parameter_at].values.used + data.parameters[fss_extended_list_read_parameter_name].values.used;

    f_array_length_t values_order[values_total];
    f_array_length_t values_type[values_total];

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    // determine the linear order in which all of the three parameter values are to be applied.
    if (values_total) {
      memset(values_order, 0, values_total);

      f_array_length_t k = 0;
      f_array_length_t l = 0;

      for (; j < data.parameters[fss_extended_list_read_parameter_depth].values.used; ++j) {

        values_order[i] = data.parameters[fss_extended_list_read_parameter_depth].values.array[j];
        values_type[i++] = fss_extended_list_read_parameter_depth;
      } // for

      if (i) {
        for (j = 0; j < data.parameters[fss_extended_list_read_parameter_at].values.used; ++j) {

          for (k = 0; k < j; ++k) {

            if (values_order[k] > data.parameters[fss_extended_list_read_parameter_at].values.array[j]) {
              for (l = j; l > k; --l) {
                values_order[l] = values_order[l - 1];
              } // for

              values_order[i] = data.parameters[fss_extended_list_read_parameter_at].values.array[j];
              values_type[i++] = fss_extended_list_read_parameter_at;
              break;
            }
          } // for

          if (j == k) {
              values_order[i] = data.parameters[fss_extended_list_read_parameter_at].values.array[j];
              values_type[i++] = fss_extended_list_read_parameter_at;
          }
        } // for
      }
      else {
        for (; j < data.parameters[fss_extended_list_read_parameter_at].values.used; ++j) {

          values_order[i] = data.parameters[fss_extended_list_read_parameter_at].values.array[j];
          values_type[i++] = fss_extended_list_read_parameter_at;
        } // for
      }

      if (i) {
        for (j = 0; j < data.parameters[fss_extended_list_read_parameter_name].values.used; ++j) {

          for (k = 0; k < j; ++k) {

            if (values_order[k] > data.parameters[fss_extended_list_read_parameter_name].values.array[j]) {
              for (l = j; l > k; --l) {
                values_order[l] = values_order[l - 1];
              } // for

              values_order[i] = data.parameters[fss_extended_list_read_parameter_name].values.array[j];
              values_type[i++] = fss_extended_list_read_parameter_name;
              break;
            }
          } // for

          if (j == k) {
              values_order[i] = data.parameters[fss_extended_list_read_parameter_name].values.array[j];
              values_type[i++] = fss_extended_list_read_parameter_name;
          }
        } // for
      }
      else {
        for (; j < data.parameters[fss_extended_list_read_parameter_name].values.used; ++j) {

          values_order[i] = data.parameters[fss_extended_list_read_parameter_name].values.array[j];
          values_type[i++] = fss_extended_list_read_parameter_name;
        } // for
      }
    }

    {
      i = 1;

      if (data.parameters[fss_extended_list_read_parameter_depth].result == f_console_result_additional) {
        i = data.parameters[fss_extended_list_read_parameter_depth].values.used + 1;
      }

      macro_fss_extended_list_read_depths_t_new(status, (*depths), i);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fss_extended_list_read_main_preprocess_depth", F_true);
        return status;
      }

      depths->used = 0;
    }

    // provide default level-0 depth values.
    depths->array[0].depth = 0;
    depths->array[0].index_at = 0;
    depths->array[0].index_name = 0;
    depths->array[0].value_at = 0;

    {
      f_number_unsigned_t number = 0;
      bool first_depth = F_true;

      for (i = 0; i < values_total; ++i) {

        if (values_type[i] == fss_extended_list_read_parameter_depth || values_type[i] == fss_extended_list_read_parameter_at) {
          const f_string_range_t range = f_macro_string_range_t_initialize(strlen(arguments.argv[values_order[i]]));

          status = fl_conversion_string_to_number_unsigned(arguments.argv[values_order[i]], &number, range);

          if (F_status_is_error(status)) {
            fll_error_parameter_integer_print(data.error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_extended_list_read_long_depth, arguments.argv[values_order[i]]);
            return status;
          }
        }

        if (values_type[i] == fss_extended_list_read_parameter_depth) {
          if (first_depth) {
            if (i) {
              depths->array[++depths->used].index_at = 0;
              depths->array[depths->used].index_name = 0;
              depths->array[depths->used].value_at = 0;
            }

            first_depth = F_false;
            depths->array[depths->used].depth = number;
          }
          else {
            depths->array[++depths->used].depth = number;
            depths->array[depths->used].index_at = 0;
            depths->array[depths->used].index_name = 0;
            depths->array[depths->used].value_at = 0;
          }
        }
        else if (values_type[i] == fss_extended_list_read_parameter_at) {
          depths->array[depths->used].index_at = values_order[i];
          depths->array[depths->used].value_at = number;
        }
        else if (values_type[i] == fss_extended_list_read_parameter_name) {
          depths->array[depths->used].index_name = values_order[i];
          depths->array[depths->used].value_name.used = 0;

          if (data.parameters[fss_extended_list_read_parameter_trim].result == f_console_result_found) {
            status = fl_string_rip(arguments.argv[values_order[i]], strnlen(arguments.argv[values_order[i]], f_console_length_size), &depths->array[depths->used].value_name);

            if (F_status_is_error(status)) {
              fll_error_print(data.error, F_status_set_fine(status), "fl_string_rip", F_true);
              return status;
            }
          }
          else {
            status = fl_string_append(arguments.argv[values_order[i]], strnlen(arguments.argv[values_order[i]], f_console_length_size), &depths->array[depths->used].value_name);

            if (F_status_is_error(status)) {
              fll_error_print(data.error, F_status_set_fine(status), "fl_string_append", F_true);
              return status;
            }
          }

          if (!depths->array[depths->used].value_name.used) {
            fprintf(data.error.to.stream, "%c", f_string_eol[0]);
            fl_color_print(data.error.to.stream, data.context.set.error, "%sThe '", fll_error_print_error);
            fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_name);
            fl_color_print(data.error.to.stream, data.context.set.error, "' must not be an empty string.%c", f_string_eol[0]);

            return F_status_set_error(F_parameter);
          }
        }
      } // for
    }

    if (!depths->used) {
      depths->used++;
    }

    for (i = 0; i < depths->used; i++) {

      for (j = i + 1; j < depths->used; j++) {

        if (depths->array[i].depth == depths->array[j].depth) {
          fprintf(data.error.to.stream, "%c", f_string_eol[0]);
          fl_color_print(data.error.to.stream, data.context.set.error, "%sThe value '", fll_error_print_error);
          fl_color_print(data.error.to.stream, data.context.set.notable, "%llu", depths->array[i].depth);
          fl_color_print(data.error.to.stream, data.context.set.error, "' may only be specified once for the parameter '");
          fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_list_read_long_depth);
          fl_color_print(data.error.to.stream, data.context.set.error, "'.%c", f_string_eol[0]);

          return F_status_set_error(F_parameter);
        }
        else if (depths->array[i].depth > depths->array[j].depth) {
          fprintf(data.error.to.stream, "%c", f_string_eol[0]);
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
        const f_string_length_t index = data->parameters[fss_extended_list_read_parameter_select].values.array[data->parameters[fss_extended_list_read_parameter_select].values.used - 1];
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
      const f_array_length_t index = data->parameters[fss_extended_list_read_parameter_line].values.array[data->parameters[fss_extended_list_read_parameter_line].values.used - 1];
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
    bool skip[items->used];

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    const f_string_lengths_t except_none = f_string_lengths_t_initialize;

    if (depth_setting.index_name || depth_setting.index_at) {
      memset(skip, F_true, sizeof(skip) * items->used);

      if (!depth_setting.index_name || (depth_setting.index_at && depth_setting.index_at < depth_setting.index_name)) {

        if (depth_setting.value_at < items->used) {
          if (depth_setting.index_name) {
            if (data->parameters[fss_extended_list_read_parameter_trim].result == f_console_result_found) {

              if (fl_string_dynamic_partial_compare_except_trim_dynamic(depth_setting.value_name, data->buffer, items->array[depth_setting.value_at].object, except_none, *objects_delimits) == F_equal_to) {
                skip[depth_setting.value_at] = F_false;
              }
            }
            else {

              if (fl_string_dynamic_partial_compare_except_dynamic(depth_setting.value_name, data->buffer, items->array[depth_setting.value_at].object, except_none, *objects_delimits) == F_equal_to) {
                skip[depth_setting.value_at] = F_false;
              }
            }
          }
          else {
            skip[depth_setting.value_at] = F_false;
          }
        }
      }
      else {

        if (data->parameters[fss_extended_list_read_parameter_trim].result == f_console_result_found) {

          for (i = 0; i < items->used; ++i) {

            if (fl_string_dynamic_partial_compare_except_trim_dynamic(depth_setting.value_name, data->buffer, items->array[i].object, except_none, *objects_delimits) == F_equal_to) {
              skip[i] = F_false;
            }
          } // for
        }
        else {

          for (i = 0; i < items->used; ++i) {

            if (fl_string_dynamic_partial_compare_except_dynamic(depth_setting.value_name, data->buffer, items->array[i].object, except_none, *objects_delimits) == F_equal_to) {
              skip[i] = F_false;
            }
          } // for
        }

        if (depth_setting.index_at) {

          for (i = 0, j = 0; i < items->used; ++i) {

            if (!skip[i] && j != depth_setting.value_at) {
              skip[i] = F_true;
              ++j;
            }
          } // for
        }
      }
    }
    else {
      memset(skip, F_false, sizeof(skip) * items->used);
    }

    // process objects.

    if (data->parameters[fss_extended_list_read_parameter_object].result == f_console_result_found) {
      if (data->parameters[fss_extended_list_read_parameter_total].result == f_console_result_found) {
        f_array_length_t total = 0;

        for (i = 0; i < items->used; i++) {
          if (skip[i]) continue;

          total++;
        } // for

        fprintf(data->output.stream, "%llu%c", total, f_string_eol[0]);

        return F_none;
      }

      f_return_status (*print_object)(FILE *, const f_string_static_t, const f_string_range_t, const f_string_lengths_t) = &f_print_except_dynamic_partial;

      if (data->parameters[fss_extended_list_read_parameter_trim].result == f_console_result_found) {
        print_object = &fl_print_trim_except_dynamic_partial;
      }

      for (i = 0; i < items->used; i++) {

        if (skip[i]) continue;

        print_object(data->output.stream, data->buffer, items->array[i].object, *objects_delimits);

        if (data->parameters[fss_extended_list_read_parameter_content].result == f_console_result_found) {
          fss_extended_list_read_print_object_end(*data);

          if (items->array[i].content.used) {
            f_print_except_dynamic_partial(data->output.stream, data->buffer, items->array[i].content.array[0], *contents_delimits);
          }
        }

        fss_extended_list_read_print_set_end(*data);
      } // for

      return F_none;
    }

    // process contents.
    bool include_empty = 0;

    if (data->parameters[fss_extended_list_read_parameter_empty].result == f_console_result_found) {
      include_empty = 1;
    }

    if (data->parameters[fss_extended_list_read_parameter_total].result == f_console_result_found) {
      f_array_length_t total = 0;

      for (i = 0; i < items->used; ++i) {

        if (skip[i]) continue;

        if (!items->array[i].content.used) {
          if (include_empty) {
            total++;
          }

          continue;
        }

        for (j = items->array[i].content.array[0].start; j <= items->array[i].content.array[0].stop; ++j) {

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

      for (; i < items->used; ++i) {

        if (skip[i]) continue;

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
          for (; j <= items->array[i].content.array[0].stop; ++j) {

            if (data->buffer.string[j] == f_string_eol[0]) {
              line_current++;

              if (line_current == line) {
                ++j;
                break;
              }
            }
          } // for
        }

        if (line_current == line) {
          if (j > items->array[i].content.array[0].stop) continue;

          for (; j <= items->array[i].content.array[0].stop; ++j) {

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

      if (skip[i]) continue;

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
