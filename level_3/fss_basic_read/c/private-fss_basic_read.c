#include "fss_basic_read.h"
#include "private-common.h"
#include "private-fss_basic_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_read_depth_process_
  f_status_t fss_basic_read_depth_process(const f_console_arguments_t arguments, const fss_basic_read_main_t main, fss_basic_read_depths_t *depths) {

    f_status_t status = F_none;

    {
      f_array_length_t depth_size = 1;

      if (main.parameters[fss_basic_read_parameter_depth].result == f_console_result_additional) {
        depth_size = main.parameters[fss_basic_read_parameter_depth].values.used;
      }

      if (depth_size > depths->size) {
        status = fss_basic_read_depths_resize(depth_size, depths);

        if (F_status_is_error(status)) {
          fll_error_print(main.error, F_status_set_fine(status), "fss_basic_read_depths_resize", F_true);

          return status;
        }
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

      macro_f_string_dynamic_t_clear(depths->array[i].value_name);

      if (!main.parameters[fss_basic_read_parameter_depth].values.used) {
        position_depth = 0;
      }
      else {
        position_depth = main.parameters[fss_basic_read_parameter_depth].values.array[i];

        const f_string_range_t range = macro_f_string_range_t_initialize(strlen(arguments.argv[position_depth]));

        status = fl_conversion_string_to_number_unsigned(arguments.argv[position_depth], range, &depths->array[i].depth);

        if (F_status_is_error(status)) {
          fll_error_parameter_integer_print(main.error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_basic_read_long_depth, arguments.argv[position_depth]);

          return status;
        }
      }

      if (main.parameters[fss_basic_read_parameter_at].result == f_console_result_additional) {
        for (; position_at < main.parameters[fss_basic_read_parameter_at].values.used; position_at++) {

          if (main.parameters[fss_basic_read_parameter_at].values.array[position_at] < position_depth) {
            continue;
          }

          if (i + 1 < depths->used && main.parameters[fss_basic_read_parameter_at].values.array[position_at] > main.parameters[fss_basic_read_parameter_depth].values.array[i + 1]) {
            break;
          }

          depths->array[i].index_at = main.parameters[fss_basic_read_parameter_at].values.array[position_at];

          const f_string_range_t range = macro_f_string_range_t_initialize(strlen(arguments.argv[depths->array[i].index_at]));

          status = fl_conversion_string_to_number_unsigned(arguments.argv[depths->array[i].index_at], range, &depths->array[i].value_at);

          if (F_status_is_error(status)) {
            fll_error_parameter_integer_print(main.error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_basic_read_long_at, arguments.argv[depths->array[i].index_at]);

            return status;
          }
        } // for
      }

      if (main.parameters[fss_basic_read_parameter_name].result == f_console_result_additional) {
        for (; position_name < main.parameters[fss_basic_read_parameter_name].values.used; position_name++) {

          if (main.parameters[fss_basic_read_parameter_name].values.array[position_name] < position_depth) {
            continue;
          }

          if (i + 1 < depths->used && main.parameters[fss_basic_read_parameter_name].values.array[position_name] > main.parameters[fss_basic_read_parameter_depth].values.array[i + 1]) {
            break;
          }

          depths->array[i].index_name = main.parameters[fss_basic_read_parameter_name].values.array[position_name];

          if (main.parameters[fss_basic_read_parameter_trim].result == f_console_result_found) {
            status = fl_string_rip(arguments.argv[depths->array[i].index_name], strlen(arguments.argv[depths->array[i].index_name]), &depths->array[i].value_name);
          }
          else {
            status = f_string_append(arguments.argv[depths->array[i].index_name], strlen(arguments.argv[depths->array[i].index_name]), &depths->array[i].value_name);
          }

          if (F_status_is_error(status)) {
            fll_error_print(main.error, F_status_set_fine(status), main.parameters[fss_basic_read_parameter_trim].result == f_console_result_found ? "fl_string_rip" : "f_string_append", F_true);

            return status;
          }

          if (!depths->array[i].value_name.used) {
            if (main.error.verbosity != f_console_verbosity_quiet) {
              f_color_print(main.error.to.stream, main.context.set.error, "%sThe '", fll_error_print_error);
              f_color_print(main.error.to.stream, main.context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_name);
              f_color_print(main.error.to.stream, main.context.set.error, "' must not be an empty string.%c", f_string_eol_s[0]);
            }

            return F_status_set_error(F_parameter);
          }
        } // for
      }
    } // for

    for (f_array_length_t i = 0; i < depths->used; i++) {

      for (f_array_length_t j = i + 1; j < depths->used; j++) {

        if (depths->array[i].depth == depths->array[j].depth) {
          if (main.error.verbosity != f_console_verbosity_quiet) {
            f_color_print(main.error.to.stream, main.context.set.error, "%sThe value '", fll_error_print_error);
            f_color_print(main.error.to.stream, main.context.set.notable, "%llu", depths->array[i].depth);
            f_color_print(main.error.to.stream, main.context.set.error, "' may only be specified once for the parameter '");
            f_color_print(main.error.to.stream, main.context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_depth);
            f_color_print(main.error.to.stream, main.context.set.error, "'.%c", f_string_eol_s[0]);
          }

          return F_status_set_error(F_parameter);
        }
        else if (depths->array[i].depth > depths->array[j].depth) {
          if (main.error.verbosity != f_console_verbosity_quiet) {
            f_color_print(main.error.to.stream, main.context.set.error, "%sThe parameter '", fll_error_print_error);
            f_color_print(main.error.to.stream, main.context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_read_long_depth);
            f_color_print(main.error.to.stream, main.context.set.error, "' may not have the value '");
            f_color_print(main.error.to.stream, main.context.set.notable, "%llu", depths->array[i].depth);
            f_color_print(main.error.to.stream, main.context.set.error, "' before the value '");
            f_color_print(main.error.to.stream, main.context.set.notable, "%llu", depths->array[j].depth);
            f_color_print(main.error.to.stream, main.context.set.error, "'.%c", f_string_eol_s[0]);
          }

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
  f_status_t fss_basic_read_load_number(const f_console_arguments_t arguments, const fss_basic_read_main_t main, const f_array_length_t parameter, const f_string_t name, f_number_unsigned_t *number) {

    if (main.parameters[parameter].result == f_console_result_additional) {
      const f_array_length_t index = main.parameters[parameter].values.array[main.parameters[parameter].values.used - 1];
      const f_string_range_t range = macro_f_string_range_t_initialize(strnlen(arguments.argv[index], f_console_parameter_size));

      const f_status_t status = fl_conversion_string_to_number_unsigned(arguments.argv[index], range, number);

      if (F_status_is_error(status)) {
        fll_error_parameter_integer_print(main.error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, name, arguments.argv[index]);

        return status;
      }
    }

    return F_none;
  }
#endif // _di_fss_basic_read_load_number_

#ifndef _di_fss_basic_read_print_at_
  void fss_basic_read_print_at(const fss_basic_read_main_t main, const f_array_length_t at, const bool include_empty, const f_fss_delimits_t delimits, const uint8_t print_this) {

    if (at >= main.contents.used) {
      return;
    }

    if (main.contents.array[at].used || include_empty) {

      f_status_t (*print_object)(FILE *, const f_string_static_t, const f_string_range_t, const f_array_lengths_t) = &f_print_except_dynamic_partial;

      if (main.parameters[fss_basic_read_parameter_trim].result == f_console_result_found) {
        print_object = &fl_print_trim_except_dynamic_partial;
      }

      const f_array_lengths_t except_none = f_array_lengths_t_initialize;

      if (main.parameters[fss_basic_read_parameter_object].result == f_console_result_found) {
        print_object(main.output.stream, main.buffer, main.objects.array[at], delimits);

        if (print_this & 0x2) {
          fss_basic_read_print_object_end(main);
        }
      }

      if ((print_this & 0x2) && main.contents.array[at].used) {
        f_print_except_dynamic_partial(main.output.stream, main.buffer, main.contents.array[at].array[0], delimits);
      }

      if ((print_this & 0x1) || (print_this & 0x2) && (main.contents.array[at].used || include_empty)) {
        fss_basic_read_print_set_end(main);
      }
    }
  }
#endif // _di_fss_basic_read_print_at_

#ifndef _di_fss_basic_read_print_object_end_
  void fss_basic_read_print_object_end(const fss_basic_read_main_t main) {

    if (main.parameters[fss_basic_read_parameter_pipe].result == f_console_result_found) {
      fprintf(main.output.stream, "%c", fss_basic_read_pipe_content_start);
    }
    else {
      fprintf(main.output.stream, "%c", f_fss_space);
    }
  }
#endif // _di_fss_basic_read_print_object_end_

#ifndef _di_fss_basic_read_print_one_
  void fss_basic_read_print_one(const fss_basic_read_main_t main) {
    fprintf(main.output.stream, "1%c", f_string_eol_s[0]);
  }
#endif // _di_fss_basic_read_print_one_

#ifndef _di_fss_basic_read_print_set_end_
  void fss_basic_read_print_set_end(const fss_basic_read_main_t main) {

    if (main.parameters[fss_basic_read_parameter_pipe].result == f_console_result_found) {
      fprintf(main.output.stream, "%c", fss_basic_read_pipe_content_end);
    }
    else {
      fprintf(main.output.stream, "%c", f_fss_eol);
    }
  }
#endif // _di_fss_basic_read_print_set_end_

#ifndef _di_fss_basic_read_print_zero_
  void fss_basic_read_print_zero(const fss_basic_read_main_t main) {
    fprintf(main.output.stream, "0%c", f_string_eol_s[0]);
  }
#endif // _di_fss_basic_read_print_zero_

#ifndef _di_fss_basic_read_process_
  f_status_t fss_basic_read_process(const f_console_arguments_t arguments, const fss_basic_read_files_t files, const fss_basic_read_depths_t depths, fss_basic_read_main_t *main, f_fss_delimits_t *delimits) {

    f_status_t status = F_none;

    const f_array_lengths_t except_none = f_array_lengths_t_initialize;
    bool delimited = F_true;
    bool include_empty = F_false;
    f_number_unsigned_t select = 0;
    f_number_unsigned_t line = 0;

    // @todo after changes to main, create a private main object for processing and using this and similar.
    // 0x1 = print object, 0x2 = print content.
    uint8_t print_this = main->parameters[fss_basic_read_parameter_object].result == f_console_result_found;

    if (!print_this || main->parameters[fss_basic_read_parameter_content].result == f_console_result_found) {
      print_this |= 0x2;
    }

    if (main->delimit_mode == fss_basic_read_delimit_mode_none || (main->delimit_depth && (main->delimit_mode == fss_basic_read_delimit_mode_depth || main->delimit_mode == fss_basic_read_delimit_mode_depth_greater))) {
      delimited = F_false;
    }

    if (main->parameters[fss_basic_read_parameter_empty].result == f_console_result_found) {
      include_empty = F_true;
    }

    status = fss_basic_read_load_number(arguments, *main, fss_basic_read_parameter_select, fss_basic_read_long_select, &select);
    if (F_status_is_error(status)) return status;

    status = fss_basic_read_load_number(arguments, *main, fss_basic_read_parameter_line, fss_basic_read_long_line, &line);
    if (F_status_is_error(status)) return status;

    if (main->parameters[fss_basic_read_parameter_select].result == f_console_result_additional) {

      // This standard does not support multiple content groups.
      if (select) {
        if (main->parameters[fss_basic_read_parameter_total].result == f_console_result_found) {
          fss_basic_read_print_zero(*main);
        }

        return F_none;
      }
    }

    {
      f_string_range_t input = macro_f_string_range_t_initialize(main->buffer.used);

      delimits->used = 0;

      status = fll_fss_basic_read(main->buffer, &input, &main->objects, &main->contents, 0, delimits, 0);

      if (F_status_is_error(status)) {
        const f_string_t file_name = fss_basic_read_file_identify(input.start, files);

        fll_error_file_print(main->error, F_status_set_fine(status), "fll_fss_basic_read", F_true, file_name ? file_name : "-", "process", fll_error_file_type_file);
      }
      else if (status == F_data_not_stop || status == F_data_not_eos) {
        if (main->parameters[fss_basic_read_parameter_total].result == f_console_result_found) {
          fss_basic_read_print_zero(*main);

          return F_none;
        }

        return F_status_set_warning(status);
      }

      if (F_status_is_error(status)) {
        return status;
      }
    }

    bool names[main->objects.used];

    f_array_length_t i = 0;

    if (depths.array[0].index_name > 0) {
      memset(names, 0, sizeof(bool) * main->objects.used);

      if (main->parameters[fss_basic_read_parameter_trim].result == f_console_result_found) {
        for (i = 0; i < main->objects.used; i++) {

          if (fl_string_dynamic_partial_compare_except_trim_dynamic(depths.array[0].value_name, main->buffer, main->objects.array[i], except_none, *delimits) == F_equal_to) {
            names[i] = 1;
          }
        } // for
      }
      else {
        for (i = 0; i < main->objects.used; i++) {

           if (fl_string_dynamic_partial_compare_except_dynamic(depths.array[0].value_name, main->buffer, main->objects.array[i], except_none, *delimits) == F_equal_to) {
            names[i] = 1;
          }
        } // for
      }
    }
    else {
      memset(names, 1, sizeof(bool) * main->objects.used);
    }

    if (depths.array[0].index_at) {
      if (depths.array[0].value_at >= main->objects.used) {
        if (names[depths.array[0].value_at] && main->parameters[fss_basic_read_parameter_total].result == f_console_result_found) {
          fss_basic_read_print_zero(*main);
        }

        return F_none;
      }

      if (main->parameters[fss_basic_read_parameter_line].result == f_console_result_additional) {
        if (line > 0) {
          return F_none;
        }
      }

      f_array_length_t at = 0;

      for (; i < main->objects.used; i++) {

        if (!names[i]) continue;

        if (at == depths.array[0].value_at) {
          if (main->parameters[fss_basic_read_parameter_line].result == f_console_result_additional) {

            // This standard only supports one Content per Object so when using "--at", the only valid line is line 0.
            if (main->parameters[fss_basic_read_parameter_total].result == f_console_result_found) {
              if (line) {
                fss_basic_read_print_one(*main);
              }
              else {
                fss_basic_read_print_zero(*main);
              }
            }
            else if (!line) {
              fss_basic_read_print_at(*main, i, include_empty, delimited ? *delimits : except_none, print_this);
            }
          }
          else if (main->parameters[fss_basic_read_parameter_total].result == f_console_result_found) {
            if (!main->contents.array[i].used) {
              fss_basic_read_print_zero(*main);
            }
            else {
              fss_basic_read_print_one(*main);
            }
          }
          else {
            fss_basic_read_print_at(*main, i, include_empty, delimited ? *delimits : except_none, print_this);
          }

          break;
        }

        at++;
      } // for

      return F_none;
    }

    if (main->parameters[fss_basic_read_parameter_total].result == f_console_result_found) {
      f_array_length_t total = 0;

      for (i = 0; i < main->objects.used; i++) {

        if (!names[i]) continue;

        if (!(main->contents.array[i].used || include_empty)) {
          continue;
        }

        total++;
      } // for

      if (main->parameters[fss_basic_read_parameter_line].result == f_console_result_additional) {
        if (line < total) {
          fss_basic_read_print_one(*main);
        }
        else {
          fss_basic_read_print_zero(*main);
        }
      }
      else {
        fprintf(main->output.stream, "%llu%c", total, f_string_eol_s[0]);
      }

      return F_none;
    }

    if (main->parameters[fss_basic_read_parameter_line].result == f_console_result_additional) {
      f_array_length_t line_current = 0;

      for (i = 0; i < main->contents.used; i++) {

        if (!names[i]) continue;

        if (!main->contents.array[i].used) {
          if (include_empty) {
            if (line_current == line) {
              fss_basic_read_print_set_end(*main);
              break;
            }

            line_current++;
          }

          continue;
        }

        if (line_current == line) {
          fss_basic_read_print_at(*main, i, include_empty, delimited ? *delimits : except_none, print_this);

          break;
        }

        line_current++;
      } // for

      return F_none;
    }

    for (i = 0; i < main->contents.used; i++) {

      if (!names[i]) continue;

      fss_basic_read_print_at(*main, i, include_empty, delimited ? *delimits : except_none, print_this);
    } // for

    return F_none;
  }
#endif // _di_fss_basic_read_process_

#ifdef __cplusplus
} // extern "C"
#endif
