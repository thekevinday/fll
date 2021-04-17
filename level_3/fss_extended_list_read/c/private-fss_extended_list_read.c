#include "fss_extended_list_read.h"
#include "private-fss_extended_list_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_list_read_main_preprocess_depth_
  f_status_t fss_extended_list_read_main_preprocess_depth(const f_console_arguments_t arguments, const fss_extended_list_read_data_t data, fss_extended_list_read_depths_t *depths) {
    f_status_t status = F_none;

    {
      f_array_length_t depth_size = 1;

      if (data.parameters[fss_extended_list_read_parameter_depth].result == f_console_result_additional) {
        depth_size = data.parameters[fss_extended_list_read_parameter_depth].values.used;
      }

      fss_extended_list_read_macro_depths_t_resize(status, (*depths), depth_size);

      if (F_status_is_error(status)) {
        f_color_print(data.error.to.stream, data.context.set.error, "%sUnable to allocate memory.%c", fll_error_print_error, f_string_eol_s[0]);
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

      if (!data.parameters[fss_extended_list_read_parameter_depth].values.used) {
        position_depth = 0;
      }
      else {
        position_depth = data.parameters[fss_extended_list_read_parameter_depth].values.array[i];

        const f_string_range_t range = f_macro_string_range_t_initialize(strlen(arguments.argv[position_depth]));

        status = fl_conversion_string_to_number_unsigned(arguments.argv[position_depth], range, &depths->array[i].depth);

        if (F_status_is_error(status)) {
          fll_error_parameter_integer_print(data.error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_extended_list_read_long_depth, arguments.argv[position_depth]);
          return status;
        }
      }

      if (data.parameters[fss_extended_list_read_parameter_at].result == f_console_result_additional) {
        for (; position_at < data.parameters[fss_extended_list_read_parameter_at].values.used; position_at++) {

          if (data.parameters[fss_extended_list_read_parameter_at].values.array[position_at] < position_depth) {
            continue;
          }

          if (i + 1 < depths->used && data.parameters[fss_extended_list_read_parameter_at].values.array[position_at] > data.parameters[fss_extended_list_read_parameter_depth].values.array[i + 1]) {
            break;
          }

          depths->array[i].index_at = data.parameters[fss_extended_list_read_parameter_at].values.array[position_at];

          const f_string_range_t range = f_macro_string_range_t_initialize(strlen(arguments.argv[depths->array[i].index_at]));

          status = fl_conversion_string_to_number_unsigned(arguments.argv[depths->array[i].index_at], range, &depths->array[i].value_at);

          if (F_status_is_error(status)) {
            fll_error_parameter_integer_print(data.error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_extended_list_read_long_at, arguments.argv[depths->array[i].index_at]);
            return status;
          }
        } // for
      }

      if (data.parameters[fss_extended_list_read_parameter_name].result == f_console_result_additional) {
        for (; position_name < data.parameters[fss_extended_list_read_parameter_name].values.used; position_name++) {

          if (data.parameters[fss_extended_list_read_parameter_name].values.array[position_name] < position_depth) {
            continue;
          }

          if (i + 1 < depths->used && data.parameters[fss_extended_list_read_parameter_name].values.array[position_name] > data.parameters[fss_extended_list_read_parameter_depth].values.array[i + 1]) {
            break;
          }

          depths->array[i].index_name = data.parameters[fss_extended_list_read_parameter_name].values.array[position_name];

          if (data.parameters[fss_extended_list_read_parameter_trim].result == f_console_result_found) {
            status = fl_string_rip(arguments.argv[depths->array[i].index_name], strlen(arguments.argv[depths->array[i].index_name]), &depths->array[i].value_name);
          }
          else {
            status = f_string_append(arguments.argv[depths->array[i].index_name], strlen(arguments.argv[depths->array[i].index_name]), &depths->array[i].value_name);
          }

          if (F_status_is_error(status)) {
            f_status_t status_code = F_status_set_fine(status);

            // @todo: move error printing into common function.
            if (status_code == F_memory_not) {
              f_color_print(data.error.to.stream, data.context.set.error, "%sUnable to allocate memory.%c", fll_error_print_error, f_string_eol_s[0]);
            }
            else if (status_code == f_array_length_t_size) {
              f_color_print(data.error.to.stream, data.context.set.error, "%sUnable to process '", fll_error_print_error);
              f_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_list_read_long_trim);
              f_color_print(data.error.to.stream, data.context.set.error, "' because the maximum buffer size was reached.%c", f_string_eol_s[0]);
            }
            else {
              f_string_t function = "f_string_append";

              if (data.parameters[fss_extended_list_read_parameter_trim].result == f_console_result_found) {
                function = "fl_string_rip";
              }

              f_color_print(data.error.to.stream, data.context.set.error, "%sAn unhandled error (", fll_error_print_error);
              f_color_print(data.error.to.stream, data.context.set.notable, "%u", status_code);
              f_color_print(data.error.to.stream, data.context.set.error, ") has occurred while calling ");
              f_color_print(data.error.to.stream, data.context.set.notable, "%s()", function);
              f_color_print(data.error.to.stream, data.context.set.error, ".%c", f_string_eol_s[0]);
            }

            return status;
          }

          if (!depths->array[i].value_name.used) {
            f_color_print(data.error.to.stream, data.context.set.error, "%sThe '", fll_error_print_error);
            f_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_list_read_long_name);
            f_color_print(data.error.to.stream, data.context.set.error, "' must not be an empty string.%c", f_string_eol_s[0]);

            return F_status_set_error(F_parameter);
          }
        } // for
      }
    } // for

    for (f_array_length_t i = 0; i < depths->used; i++) {

      for (f_array_length_t j = i + 1; j < depths->used; j++) {

        if (depths->array[i].depth == depths->array[j].depth) {
          f_color_print(data.error.to.stream, data.context.set.error, "%sThe value '", fll_error_print_error);
          f_color_print(data.error.to.stream, data.context.set.notable, "%llu", depths->array[i].depth);
          f_color_print(data.error.to.stream, data.context.set.error, "' may only be specified once for the parameter '");
          f_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_list_read_long_depth);
          f_color_print(data.error.to.stream, data.context.set.error, "'.%c", f_string_eol_s[0]);

          return F_status_set_error(F_parameter);
        }
        else if (depths->array[i].depth > depths->array[j].depth) {
          f_color_print(data.error.to.stream, data.context.set.error, "%sThe parameter '", fll_error_print_error);
          f_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_extended_list_read_long_depth);
          f_color_print(data.error.to.stream, data.context.set.error, "' may not have the value '");
          f_color_print(data.error.to.stream, data.context.set.notable, "%llu", depths->array[i].depth);
          f_color_print(data.error.to.stream, data.context.set.error, "' before the value '");
          f_color_print(data.error.to.stream, data.context.set.notable, "%llu", depths->array[j].depth);
          f_color_print(data.error.to.stream, data.context.set.error, "'.%c", f_string_eol_s[0]);

          return F_status_set_error(F_parameter);
        }
      } // for
    } // for

    return F_none;
  }
#endif // _di_fss_extended_list_read_main_preprocess_depth_

#ifndef _di_fss_extended_list_read_main_process_file_
  f_status_t fss_extended_list_read_main_process_file(const f_console_arguments_t arguments, fss_extended_list_read_data_t *data, const f_string_t filename, const fss_extended_list_read_depths_t depths, f_fss_delimits_t *delimits, f_fss_comments_t *comments) {
    f_status_t status = F_none;

    const f_array_lengths_t except_none = f_array_lengths_t_initialize;
    bool delimited = F_true;

    // for this standard, delimits would always be applied, except for when delimit_depth is greater than 0.
    if (data->delimit_mode == fss_extended_list_read_delimit_mode_none || (data->delimit_depth && (data->delimit_mode == fss_extended_list_read_delimit_mode_depth || data->delimit_mode == fss_extended_list_read_delimit_mode_depth_greater))) {
      delimited = F_false;
    }

    {
      f_string_range_t input = f_macro_string_range_t_initialize(data->buffer.used);

      delimits->used = 0;
      comments->used = 0;

      status = fll_fss_extended_list_read(data->buffer, &input, &data->objects, &data->contents, delimits, 0, comments);

      if (F_status_is_error(status)) {
        // @todo: detect and replace fll_error_file_type_file with fll_error_file_type_pipe as appropriate.
        fll_error_file_print(data->error, F_status_set_fine(status), "fll_fss_extended_list_read", F_true, filename, "process", fll_error_file_type_file);
      }
      else if (status == F_data_not_stop || status == F_data_not_eos) {
        f_macro_fss_contents_t_delete_simple(data->contents);
        f_macro_fss_objects_t_delete_simple(data->objects);
        f_macro_string_dynamic_t_delete_simple(data->buffer);

        if (data->parameters[fss_extended_list_read_parameter_total].result == f_console_result_found) {
          fprintf(data->output.stream, "0%c", f_string_eol_s[0]);
          return F_none;
        }

        return F_status_set_warning(status);
      }

      if (F_status_is_error(status)) {
        f_macro_fss_contents_t_delete_simple(data->contents);
        f_macro_fss_objects_t_delete_simple(data->objects);
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

    f_number_unsigned_t select = 0;

    if (data->parameters[fss_extended_list_read_parameter_select].result == f_console_result_additional) {
      const f_array_length_t index = data->parameters[fss_extended_list_read_parameter_select].values.array[data->parameters[fss_extended_list_read_parameter_select].values.used - 1];
      const f_string_range_t range = f_macro_string_range_t_initialize(strlen(arguments.argv[index]));

      status = fl_conversion_string_to_number_unsigned(arguments.argv[index], range, &select);

      if (F_status_is_error(status)) {
        fll_error_parameter_integer_print(data->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_extended_list_read_long_select, arguments.argv[index]);
        return status;
      }

      // This standard does not support multiple content groups.
      if (select > 0) {
        return F_none;
      }
    }

    f_array_length_t line = 0;

    if (data->parameters[fss_extended_list_read_parameter_line].result == f_console_result_additional) {
      const f_array_length_t index = data->parameters[fss_extended_list_read_parameter_line].values.array[data->parameters[fss_extended_list_read_parameter_line].values.used - 1];
      const f_string_range_t range = f_macro_string_range_t_initialize(strlen(arguments.argv[index]));

      status = fl_conversion_string_to_number_unsigned(arguments.argv[index], range, &line);

      if (F_status_is_error(status)) {
        fll_error_parameter_integer_print(data->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_extended_list_read_long_line, arguments.argv[index]);
        return status;
      }
    }

    bool names[data->objects.used];

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    if (depths.array[0].index_name > 0) {
      memset(names, 0, sizeof(bool) * data->objects.used);

      if (data->parameters[fss_extended_list_read_parameter_trim].result == f_console_result_found) {
        for (i = 0; i < data->objects.used; i++) {

          if (fl_string_dynamic_partial_compare_except_trim_dynamic(depths.array[0].value_name, data->buffer, data->objects.array[i], except_none, *delimits) == F_equal_to) {
            names[i] = 1;
          }
        } // for
      }
      else {
        for (i = 0; i < data->objects.used; i++) {
          if (fl_string_dynamic_partial_compare_except_dynamic(depths.array[0].value_name, data->buffer, data->objects.array[i], except_none, *delimits) == F_equal_to) {
            names[i] = 1;
          }
        } // for
      }
    }
    else {
      memset(names, 1, sizeof(bool) * data->objects.used);
    }

    bool include_empty = 0;

    if (data->parameters[fss_extended_list_read_parameter_empty].result == f_console_result_found) {
      include_empty = 1;
    }

    if (data->parameters[fss_extended_list_read_parameter_object].result == f_console_result_found) {
      if (data->parameters[fss_extended_list_read_parameter_total].result == f_console_result_found) {
        if (depths.array[0].index_at > 0) {
          if (depths.array[0].value_at < data->objects.used && names[depths.array[0].value_at]) {
            fprintf(data->output.stream, "1%c", f_string_eol_s[0]);
          }
          else {
            fprintf(data->output.stream, "0%c", f_string_eol_s[0]);
          }
        }
        else if (depths.array[0].index_name > 0) {
          f_array_length_t total = 0;

          for (i = 0; i < data->objects.used; i++) {
            if (!names[i]) continue;

            total++;
          } // for

          fprintf(data->output.stream, "%llu%c", total, f_string_eol_s[0]);
        }
        else {
          fprintf(data->output.stream, "%llu%c", data->objects.used, f_string_eol_s[0]);
        }

        return F_none;
      }

      f_status_t (*print_object)(FILE *, const f_string_static_t, const f_string_range_t, const f_array_lengths_t) = &f_print_except_dynamic_partial;

      if (data->parameters[fss_extended_list_read_parameter_trim].result == f_console_result_found) {
        print_object = &fl_print_trim_except_dynamic_partial;
      }

      if (depths.array[0].index_at > 0) {
        f_array_length_t at = 0;
        f_array_length_t i = 0;

        for (; i < data->objects.used; i++) {

          if (names[i]) {
            if (at == depths.array[0].value_at) {
              print_object(data->output.stream, data->buffer, data->objects.array[i], delimited ? *delimits : except_none);

              fss_extended_list_read_print_object_end(*data);

              if (data->parameters[fss_extended_list_read_parameter_content].result == f_console_result_found) {
                if (data->contents.array[i].used) {
                  fss_extended_list_read_print_content_ignore(*data);
                  f_print_except_dynamic_partial(data->output.stream, data->buffer, data->contents.array[i].array[0], delimited ? *delimits : except_none);
                  fss_extended_list_read_print_content_ignore(*data);
                }
              }

              fss_extended_list_read_print_set_end(*data);
              break;
            }

            at++;
          }
        } // for

        return F_none;
      }

      for (i = 0; i < data->objects.used; i++) {

        if (!names[i]) continue;

        print_object(data->output.stream, data->buffer, data->objects.array[i], delimited ? *delimits : except_none);

        fss_extended_list_read_print_object_end(*data);

        if (data->parameters[fss_extended_list_read_parameter_content].result == f_console_result_found) {
          if (data->contents.array[i].used) {
            fss_extended_list_read_print_content_ignore(*data);
            f_print_except_dynamic_partial(data->output.stream, data->buffer, data->contents.array[i].array[0], delimited ? *delimits : except_none);
            fss_extended_list_read_print_content_ignore(*data);
          }
        }

        fss_extended_list_read_print_set_end(*data);
      } // for

      return F_none;
    }

    if (depths.array[0].index_at > 0) {
      if (depths.array[0].value_at >= data->objects.used) {
        if (names[depths.array[0].value_at] && data->parameters[fss_extended_list_read_parameter_total].result == f_console_result_found) {
          fprintf(data->output.stream, "0%c", f_string_eol_s[0]);
        }

        return F_none;
      }

      f_array_length_t at = 0;
      f_array_length_t total = 0;
      f_array_length_t line_current = 0;

      for (; i < data->objects.used; i++) {

        if (names[i]) {
          if (at == depths.array[0].value_at) {
            if (data->parameters[fss_extended_list_read_parameter_total].result == f_console_result_found) {
              if (!data->contents.array[i].used) {
                fprintf(data->output.stream, "0%c", f_string_eol_s[0]);
              }
              else {
                total = 1;

                for (j = data->contents.array[i].array[0].start; j <= data->contents.array[i].array[0].stop; j++) {
                  if (!data->buffer.string[j]) continue;

                  if (data->buffer.string[j] == f_string_eol_s[0]) {
                    total++;
                  }
                } // for

                fprintf(data->output.stream, "%llu%c", total, f_string_eol_s[0]);
              }

              return F_none;
            }

            if (data->parameters[fss_extended_list_read_parameter_line].result == f_console_result_additional) {
              if (!data->contents.array[i].used) {
                if (include_empty && !line) {
                  fprintf(data->output.stream, "%c", f_string_eol_s[0]);
                  fss_extended_list_read_print_set_end(*data);
                }
              }
              else {
                i = data->contents.array[i].array[0].start;

                if (!line) {
                  for (; i <= data->contents.array[i].array[0].stop; i++) {
                    if (!data->buffer.string[i]) continue;
                    if (data->buffer.string[i] == f_string_eol_s[0]) {
                      fprintf(data->output.stream, "%c", f_string_eol_s[0]);
                      break;
                    }

                    fprintf(data->output.stream, "%c", data->buffer.string[i]);
                  } // for
                }
                else {
                  line_current = 0;

                  for (; i <= data->contents.array[i].array[0].stop; i++) {
                    if (!data->buffer.string[i]) continue;

                    if (data->buffer.string[i] == f_string_eol_s[0]) {
                      line_current++;

                      if (line_current == line) {
                        i++;

                        for (; i <= data->contents.array[i].array[0].stop; i++) {
                          if (!data->buffer.string[i]) continue;

                          if (data->buffer.string[i] == f_string_eol_s[0]) {
                            fprintf(data->output.stream, "%c", f_string_eol_s[0]);
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

            if (data->contents.array[i].used > 0) {
              fss_extended_list_read_print_content_ignore(*data);
              f_print_except_dynamic_partial(data->output.stream, data->buffer, data->contents.array[i].array[0], delimited ? *delimits : except_none);
              fss_extended_list_read_print_content_ignore(*data);

              fss_extended_list_read_print_set_end(*data);
            }
            else if (include_empty) {
              fprintf(data->output.stream, "%c", f_string_eol_s[0]);
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

      for (i = 0; i < data->objects.used; i++) {
        if (!names[i]) continue;

        if (!data->contents.array[i].used) {
          if (include_empty) {
            total++;
          }

          continue;
        }

        for (j = data->contents.array[i].array[0].start; j <= data->contents.array[i].array[0].stop; j++) {
          if (!data->buffer.string[j]) continue;

          if (data->buffer.string[j] == f_string_eol_s[0]) {
            total++;
          }
        } // for
      } // for

      fprintf(data->output.stream, "%llu%c", total, f_string_eol_s[0]);
      return F_none;
    }

    if (data->parameters[fss_extended_list_read_parameter_line].result == f_console_result_additional) {
      for (f_array_length_t line_current = 0; i < data->contents.used; i++) {
        if (!names[i]) continue;

        if (!data->contents.array[i].used) {
          if (include_empty) {
            if (line_current == line) {
              fprintf(data->output.stream, "%c", f_string_eol_s[0]);
              fss_extended_list_read_print_set_end(*data);
              break;
            }

            line_current++;
          }

          continue;
        }

        j = data->contents.array[i].array[0].start;

        if (line_current != line) {
          for (; j <= data->contents.array[i].array[0].stop; j++) {

            if (data->buffer.string[j] == f_string_eol_s[0]) {
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
            if (!data->buffer.string[j]) continue;

            if (data->buffer.string[j] == f_string_eol_s[0]) {
              fprintf(data->output.stream, "%c", f_string_eol_s[0]);
              break;
            }

            fprintf(data->output.stream, "%c", data->buffer.string[j]);
          } // for

          break;
        }
      } // for

      return F_none;
    }

    for (i = 0; i < data->contents.used; i++) {
      if (!names[i]) continue;

      if (!data->contents.array[i].used) {
        if (include_empty) {
          fprintf(data->output.stream, "%c", f_string_eol_s[0]);
          fss_extended_list_read_print_set_end(*data);
        }

        continue;
      }

      fss_extended_list_read_print_content_ignore(*data);
      f_print_except_dynamic_partial(data->output.stream, data->buffer, data->contents.array[i].array[0], delimited ? *delimits : except_none);
      fss_extended_list_read_print_content_ignore(*data);

      fss_extended_list_read_print_set_end(*data);
    } // for

    return F_none;
  }
#endif // _di_fss_extended_list_read_main_process_file_

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
      else if (data.parameters[fss_extended_list_read_parameter_content].result == f_console_result_found) {
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
      else if (data.parameters[fss_extended_list_read_parameter_content].result == f_console_result_found) {
        fprintf(data.output.stream, "%c", f_fss_eol);
      }
    }
  }
#endif // _di_fss_extended_list_read_print_set_end_

#ifdef __cplusplus
} // extern "C"
#endif
