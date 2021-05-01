#include "fss_basic_read.h"
#include "private-fss_basic_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_read_depth_process_
  f_status_t fss_basic_read_depth_process(const f_console_arguments_t arguments, const fss_basic_read_data_t data, fss_basic_read_depths_t *depths) {

    f_status_t status = F_none;

    {
      f_array_length_t depth_size = 1;

      if (data.parameters[fss_basic_read_parameter_depth].result == f_console_result_additional) {
        depth_size = data.parameters[fss_basic_read_parameter_depth].values.used;
      }

      fss_basic_read_macro_depths_t_resize(status, (*depths), depth_size);

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

      if (!data.parameters[fss_basic_read_parameter_depth].values.used) {
        position_depth = 0;
      }
      else {
        position_depth = data.parameters[fss_basic_read_parameter_depth].values.array[i];

        const f_string_range_t range = f_macro_string_range_t_initialize(strlen(arguments.argv[position_depth]));

        status = fl_conversion_string_to_number_unsigned(arguments.argv[position_depth], range, &depths->array[i].depth);

        if (F_status_is_error(status)) {
          fll_error_parameter_integer_print(data.error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_basic_read_long_depth, arguments.argv[position_depth]);
          return status;
        }
      }

      if (data.parameters[fss_basic_read_parameter_at].result == f_console_result_additional) {
        for (; position_at < data.parameters[fss_basic_read_parameter_at].values.used; position_at++) {

          if (data.parameters[fss_basic_read_parameter_at].values.array[position_at] < position_depth) {
            continue;
          }

          if (i + 1 < depths->used && data.parameters[fss_basic_read_parameter_at].values.array[position_at] > data.parameters[fss_basic_read_parameter_depth].values.array[i + 1]) {
            break;
          }

          depths->array[i].index_at = data.parameters[fss_basic_read_parameter_at].values.array[position_at];

          const f_string_range_t range = f_macro_string_range_t_initialize(strlen(arguments.argv[depths->array[i].index_at]));

          status = fl_conversion_string_to_number_unsigned(arguments.argv[depths->array[i].index_at], range, &depths->array[i].value_at);

          if (F_status_is_error(status)) {
            fll_error_parameter_integer_print(data.error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_basic_read_long_at, arguments.argv[depths->array[i].index_at]);

            return status;
          }
        } // for
      }

      if (data.parameters[fss_basic_read_parameter_name].result == f_console_result_additional) {
        for (; position_name < data.parameters[fss_basic_read_parameter_name].values.used; position_name++) {

          if (data.parameters[fss_basic_read_parameter_name].values.array[position_name] < position_depth) {
            continue;
          }

          if (i + 1 < depths->used && data.parameters[fss_basic_read_parameter_name].values.array[position_name] > data.parameters[fss_basic_read_parameter_depth].values.array[i + 1]) {
            break;
          }

          depths->array[i].index_name = data.parameters[fss_basic_read_parameter_name].values.array[position_name];

          if (data.parameters[fss_basic_read_parameter_trim].result == f_console_result_found) {
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
            else if (status_code == F_string_too_large) {
              f_color_print(data.error.to.stream, data.context.set.error, "%sUnable to process '", fll_error_print_error);
              f_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_trim);
              f_color_print(data.error.to.stream, data.context.set.error, "' because the maximum buffer size was reached.%c", f_string_eol_s[0]);
            }
            else {
              f_string_t function = "f_string_append";

              if (data.parameters[fss_basic_read_parameter_trim].result == f_console_result_found) {
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
            f_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_name);
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
          f_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_depth);
          f_color_print(data.error.to.stream, data.context.set.error, "'.%c", f_string_eol_s[0]);

          return F_status_set_error(F_parameter);
        }
        else if (depths->array[i].depth > depths->array[j].depth) {
          f_color_print(data.error.to.stream, data.context.set.error, "%sThe parameter '", fll_error_print_error);
          f_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_depth);
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
#endif // _di_fss_basic_read_depth_process_

#ifndef _di_fss_basic_read_file_identify_
  f_string_t fss_basic_read_file_identify(const f_array_length_t at, const fss_basic_read_files_t files) {

    for (f_array_length_t i = 0; i < files.used; ++i) {

      if (at >= files.array[i].range.start && at <= files.array[i].range.stop) {
        return files.array[i].name;
      }
    } // for

    return "";
  }
#endif // _di_fss_basic_read_file_identify_

#ifndef _di_fss_basic_read_load_number_
  f_status_t fss_basic_read_load_number(const f_console_arguments_t arguments, const fss_basic_read_data_t data, const f_array_length_t parameter, const f_string_t name, f_number_unsigned_t *number) {

    if (data.parameters[parameter].result == f_console_result_additional) {
      const f_array_length_t index = data.parameters[parameter].values.array[data.parameters[parameter].values.used - 1];
      const f_string_range_t range = f_macro_string_range_t_initialize(strnlen(arguments.argv[index], f_console_parameter_size));

      const f_status_t status = fl_conversion_string_to_number_unsigned(arguments.argv[index], range, number);

      if (F_status_is_error(status)) {
        fll_error_parameter_integer_print(data.error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, name, arguments.argv[index]);

        return status;
      }
    }

    return F_none;
  }
#endif // _di_fss_basic_read_load_number_

#ifndef _di_fss_basic_read_print_at_
  void fss_basic_read_print_at(const fss_basic_read_data_t data, const f_array_length_t at, const bool include_empty, const f_fss_delimits_t delimits, const uint8_t print_this) {

    if (at >= data.contents.used) {
      return;
    }

    if (data.contents.array[at].used || include_empty) {

      f_status_t (*print_object)(FILE *, const f_string_static_t, const f_string_range_t, const f_array_lengths_t) = &f_print_except_dynamic_partial;

      if (data.parameters[fss_basic_read_parameter_trim].result == f_console_result_found) {
        print_object = &fl_print_trim_except_dynamic_partial;
      }

      const f_array_lengths_t except_none = f_array_lengths_t_initialize;

      if (data.parameters[fss_basic_read_parameter_object].result == f_console_result_found) {
        print_object(data.output.stream, data.buffer, data.objects.array[at], delimits);

        if (print_this & 0x2) {
          fss_basic_read_print_object_end(data);
        }
      }

      if ((print_this & 0x2) && data.contents.array[at].used) {
        f_print_except_dynamic_partial(data.output.stream, data.buffer, data.contents.array[at].array[0], delimits);
      }

      if ((print_this & 0x1) || (print_this & 0x2) && (data.contents.array[at].used || include_empty)) {
        fss_basic_read_print_set_end(data);
      }
    }
  }
#endif // _di_fss_basic_read_print_at_

#ifndef _di_fss_basic_read_print_object_end_
  void fss_basic_read_print_object_end(const fss_basic_read_data_t data) {

    if (data.parameters[fss_basic_read_parameter_pipe].result == f_console_result_found) {
      fprintf(data.output.stream, "%c", fss_basic_read_pipe_content_start);
    }
    else {
      fprintf(data.output.stream, "%c", f_fss_space);
    }
  }
#endif // _di_fss_basic_read_print_object_end_

#ifndef _di_fss_basic_read_print_one_
  void fss_basic_read_print_one(const fss_basic_read_data_t data) {
    fprintf(data.output.stream, "1%c", f_string_eol_s[0]);
  }
#endif // _di_fss_basic_read_print_one_

#ifndef _di_fss_basic_read_print_set_end_
  void fss_basic_read_print_set_end(const fss_basic_read_data_t data) {

    if (data.parameters[fss_basic_read_parameter_pipe].result == f_console_result_found) {
      fprintf(data.output.stream, "%c", fss_basic_read_pipe_content_end);
    }
    else {
      fprintf(data.output.stream, "%c", f_fss_eol);
    }
  }
#endif // _di_fss_basic_read_print_set_end_

#ifndef _di_fss_basic_read_print_zero_
  void fss_basic_read_print_zero(const fss_basic_read_data_t data) {
    fprintf(data.output.stream, "0%c", f_string_eol_s[0]);
  }
#endif // _di_fss_basic_read_print_zero_

#ifndef _di_fss_basic_read_process_
  f_status_t fss_basic_read_process(const f_console_arguments_t arguments, const fss_basic_read_files_t files, const fss_basic_read_depths_t depths, fss_basic_read_data_t *data, f_fss_delimits_t *delimits) {

    f_status_t status = F_none;

    const f_array_lengths_t except_none = f_array_lengths_t_initialize;
    bool delimited = F_true;
    bool include_empty = F_false;
    f_number_unsigned_t select = 0;
    f_number_unsigned_t line = 0;

    // @todo after changes to data, create a private data object for processing and using this and similar.
    // 0x1 = print object, 0x2 = print content.
    uint8_t print_this = data->parameters[fss_basic_read_parameter_object].result == f_console_result_found;

    if (!print_this || data->parameters[fss_basic_read_parameter_content].result == f_console_result_found) {
      print_this |= 0x2;
    }

    if (data->delimit_mode == fss_basic_read_delimit_mode_none || (data->delimit_depth && (data->delimit_mode == fss_basic_read_delimit_mode_depth || data->delimit_mode == fss_basic_read_delimit_mode_depth_greater))) {
      delimited = F_false;
    }

    if (data->parameters[fss_basic_read_parameter_empty].result == f_console_result_found) {
      include_empty = F_true;
    }

    status = fss_basic_read_load_number(arguments, *data, fss_basic_read_parameter_select, fss_basic_read_long_select, &select);
    if (F_status_is_error(status)) return status;

    status = fss_basic_read_load_number(arguments, *data, fss_basic_read_parameter_line, fss_basic_read_long_line, &line);
    if (F_status_is_error(status)) return status;

    if (data->parameters[fss_basic_read_parameter_select].result == f_console_result_additional) {

      // This standard does not support multiple content groups.
      if (select) {
        if (data->parameters[fss_basic_read_parameter_total].result == f_console_result_found) {
          fss_basic_read_print_zero(*data);
        }

        return F_none;
      }
    }

    {
      f_string_range_t input = f_macro_string_range_t_initialize(data->buffer.used);

      delimits->used = 0;

      status = fll_fss_basic_read(data->buffer, &input, &data->objects, &data->contents, 0, delimits, 0);

      if (F_status_is_error(status)) {
        const f_string_t file_name = fss_basic_read_file_identify(input.start, files);

        fll_error_file_print(data->error, F_status_set_fine(status), "fll_fss_basic_read", F_true, file_name ? file_name : "-", "process", fll_error_file_type_file);
      }
      else if (status == F_data_not_stop || status == F_data_not_eos) {
        if (data->parameters[fss_basic_read_parameter_total].result == f_console_result_found) {
          fss_basic_read_print_zero(*data);

          return F_none;
        }

        return F_status_set_warning(status);
      }

      if (F_status_is_error(status)) {
        return status;
      }
    }

    bool names[data->objects.used];

    f_array_length_t i = 0;

    if (depths.array[0].index_name > 0) {
      memset(names, 0, sizeof(bool) * data->objects.used);

      if (data->parameters[fss_basic_read_parameter_trim].result == f_console_result_found) {
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

    if (depths.array[0].index_at) {
      if (depths.array[0].value_at >= data->objects.used) {
        if (names[depths.array[0].value_at] && data->parameters[fss_basic_read_parameter_total].result == f_console_result_found) {
          fss_basic_read_print_zero(*data);
        }

        return F_none;
      }

      if (data->parameters[fss_basic_read_parameter_line].result == f_console_result_additional) {
        if (line > 0) {
          return F_none;
        }
      }

      f_array_length_t at = 0;

      for (; i < data->objects.used; i++) {

        if (!names[i]) continue;

        if (at == depths.array[0].value_at) {
          if (data->parameters[fss_basic_read_parameter_line].result == f_console_result_additional) {

            // This standard only supports one Content per Object so when using "--at", the only valid line is line 0.
            if (data->parameters[fss_basic_read_parameter_total].result == f_console_result_found) {
              if (line) {
                fss_basic_read_print_one(*data);
              }
              else {
                fss_basic_read_print_zero(*data);
              }
            }
            else if (!line) {
              fss_basic_read_print_at(*data, i, include_empty, delimited ? *delimits : except_none, print_this);
            }
          }
          else if (data->parameters[fss_basic_read_parameter_total].result == f_console_result_found) {
            if (!data->contents.array[i].used) {
              fss_basic_read_print_zero(*data);
            }
            else {
              fss_basic_read_print_one(*data);
            }
          }
          else {
            fss_basic_read_print_at(*data, i, include_empty, delimited ? *delimits : except_none, print_this);
          }

          break;
        }

        at++;
      } // for

      return F_none;
    }

    if (data->parameters[fss_basic_read_parameter_total].result == f_console_result_found) {
      f_array_length_t total = 0;

      for (i = 0; i < data->objects.used; i++) {

        if (!names[i]) continue;

        if (!(data->contents.array[i].used || include_empty)) {
          continue;
        }

        total++;
      } // for

      if (data->parameters[fss_basic_read_parameter_line].result == f_console_result_additional) {
        if (line < total) {
          fss_basic_read_print_one(*data);
        }
        else {
          fss_basic_read_print_zero(*data);
        }
      }
      else {
        fprintf(data->output.stream, "%llu%c", total, f_string_eol_s[0]);
      }

      return F_none;
    }

    if (data->parameters[fss_basic_read_parameter_line].result == f_console_result_additional) {
      f_array_length_t line_current = 0;

      for (i = 0; i < data->contents.used; i++) {

        if (!names[i]) continue;

        if (!data->contents.array[i].used) {
          if (include_empty) {
            if (line_current == line) {
              fss_basic_read_print_set_end(*data);
              break;
            }

            line_current++;
          }

          continue;
        }

        if (line_current == line) {
          fss_basic_read_print_at(*data, i, include_empty, delimited ? *delimits : except_none, print_this);

          break;
        }

        line_current++;
      } // for

      return F_none;
    }

    for (i = 0; i < data->contents.used; i++) {

      if (!names[i]) continue;

      fss_basic_read_print_at(*data, i, include_empty, delimited ? *delimits : except_none, print_this);
    } // for

    return F_none;
  }
#endif // _di_fss_basic_read_process_

#ifdef __cplusplus
} // extern "C"
#endif
