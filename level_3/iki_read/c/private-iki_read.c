#include "iki_read.h"
#include "private-iki_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_process_at_
  f_status_t iki_read_process_at(const f_console_arguments_t arguments, const f_string_t file_name, iki_read_data_t *data, f_string_range_t *range) {
    if (data->parameters[iki_read_parameter_line].result != f_console_result_additional) return F_false;

    f_string_length_t line = 0;

    range->start = 0;
    if (data->line > 0) {
      for (; line < data->line && range->start < data->buffer.used; range->start++) {
        if (data->buffer.string[range->start] == f_string_eol_s[0]) line++;
      } // for
    }

    if (line == data->line) {
      for (range->stop = range->start; range->stop < data->buffer.used; range->stop++) {
        if (data->buffer.string[range->stop] == f_string_eol_s[0]) break;
      } // for

      return F_true;
    }

    return F_data_not;
  }
#endif // _di_iki_read_process_at_

#ifndef _di_iki_read_process_buffer_
  f_status_t iki_read_process_buffer(const f_console_arguments_t arguments, const f_string_t file_name, iki_read_data_t *data) {
    f_status_t status = F_none;

    f_iki_variable_t variable = f_iki_variable_t_initialize;
    f_iki_vocabulary_t vocabulary = f_iki_vocabulary_t_initialize;
    f_iki_content_t content = f_iki_content_t_initialize;

    if (data->parameters[iki_read_parameter_whole].result == f_console_result_found) {
      f_string_range_t buffer_range = f_macro_string_range_t_initialize(data->buffer.used);

      status = iki_read_process_at(arguments, file_name, data, &buffer_range);

      if (status == F_true) {
        if (buffer_range.start > data->buffer.used) {
          return F_data_not;
        }
      }
      else if (status == F_data_not) {
        return F_data_not;
      }

      if (data->mode == iki_read_mode_content) {
        status = iki_read_process_buffer_ranges_whole(arguments, file_name, buffer_range, data, &variable, &vocabulary, &content, &content);
      }
      else if (data->mode == iki_read_mode_literal) {
        status = iki_read_process_buffer_ranges_whole(arguments, file_name, buffer_range, data, &variable, &vocabulary, &content, &variable);
      }
      else if (data->mode == iki_read_mode_object) {
        status = iki_read_process_buffer_ranges_whole(arguments, file_name, buffer_range, data, &variable, &vocabulary, &content, &vocabulary);
      }
    }
    else if (data->mode == iki_read_mode_total) {
      status = iki_read_process_buffer_total(arguments, file_name, data, &variable, &vocabulary, &content);
    }
    else {
      f_string_range_t buffer_range = f_macro_string_range_t_initialize(data->buffer.used);

      status = iki_read_process_at(arguments, file_name, data, &buffer_range);

      if (status == F_true) {
        if (buffer_range.start > data->buffer.used) {
          return F_data_not;
        }
      }
      else if (status == F_data_not) {
        return F_data_not;
      }

      if (data->mode == iki_read_mode_content) {
        status = iki_read_process_buffer_ranges(arguments, file_name, data, &buffer_range, &variable, &vocabulary, &content, &content);
      }
      else if (data->mode == iki_read_mode_literal) {
        status = iki_read_process_buffer_ranges(arguments, file_name, data, &buffer_range, &variable, &vocabulary, &content, &variable);
      }
      else if (data->mode == iki_read_mode_object) {
        status = iki_read_process_buffer_ranges(arguments, file_name, data, &buffer_range, &variable, &vocabulary, &content, &vocabulary);
      }
    }

    f_macro_iki_variable_t_delete_simple(variable);
    f_macro_iki_vocabulary_t_delete_simple(vocabulary);
    f_macro_iki_content_t_delete_simple(content);

    return status;
  }
#endif // _di_iki_read_process_buffer_

#ifndef _di_iki_read_process_buffer_ranges_
  f_status_t iki_read_process_buffer_ranges(const f_console_arguments_t arguments, const f_string_t file_name, iki_read_data_t *data, f_string_range_t *buffer_range, f_iki_variable_t *variable, f_iki_vocabulary_t *vocabulary, f_iki_content_t *content, f_string_ranges_t *ranges) {
    f_status_t status = F_none;

    bool unmatched = F_true;

    status = fl_iki_read(&data->buffer, buffer_range, variable, vocabulary, content);

    if (F_status_is_error(status)) {
      fll_error_print(data->error, F_status_set_fine(status), "fl_iki_read", F_true);
      return status;
    }

    const bool content_only = data->mode == iki_read_mode_content;

    iki_read_substitutions_t substitutionss[variable->used];

    memset(substitutionss, 0, sizeof(iki_read_substitutions_t) * variable->used);

    if (data->mode == iki_read_mode_literal || data->mode == iki_read_mode_content) {
      status = iki_read_substitutions_identify(arguments, file_name, data, vocabulary, substitutionss);

      if (F_status_is_error(status)) {
        fll_error_print(data->error, F_status_set_fine(status), "iki_read_substitutions_identify", F_true);

        for (f_array_length_t i = 0; i < variable->used; i++) {
          iki_read_macro_substitutions_t_delete_simple(substitutionss[i]);
        } // for

        return status;
      }
    }

    if (data->parameters[iki_read_parameter_name].result == f_console_result_additional) {
      f_string_dynamic_t name = f_string_dynamic_t_initialize;

      f_array_length_t index = 0;
      f_array_length_t i = 0;
      f_array_length_t j = 0;
      buffer_range->start = 0;

      for (; i < data->parameters[iki_read_parameter_name].values.used; i++) {

        index = data->parameters[iki_read_parameter_name].values.array[i];
        name.used = 0;

        status = fl_string_append_nulless(arguments.argv[index], strlen(arguments.argv[index]), &name);

        if (F_status_is_error(status)) {
          fll_error_print(data->error, F_status_set_fine(status), "fl_string_append_nulless", F_true);

          for (f_array_length_t i = 0; i < variable->used; i++) {
            iki_read_macro_substitutions_t_delete_simple(substitutionss[i]);
          } // for

          fl_string_dynamic_delete(&name);
          return status;
        }

        buffer_range->stop = name.used - 1;

        for (j = 0; j < vocabulary->used; j++) {

          status = fl_string_dynamic_partial_compare(name, data->buffer, *buffer_range, vocabulary->array[j]);

          if (status == F_equal_to) {
            unmatched = F_false;

            if (substitutionss[j].used) {
              iki_read_substitutions_print(*data, *variable, *content, *ranges, substitutionss[j], j, content_only);
            }
            else {
              f_print_dynamic_partial(data->output.stream, data->buffer, ranges->array[j]);
            }

            printf("%c", f_string_eol_s[0]);
          }
        } // for
      } // for

      fl_string_dynamic_delete(&name);

      if (unmatched) status = F_data_not;
      else status = F_none;
    }
    else if (ranges->used) {
      f_array_length_t i = 0;
      f_string_length_t j = 0;

      for (; i < ranges->used; i++) {

        if (substitutionss[i].used) {
          iki_read_substitutions_print(*data, *variable, *content, *ranges, substitutionss[i], i, content_only);
        }
        else {
          f_print_dynamic_partial(data->output.stream, data->buffer, ranges->array[i]);
        }

        printf("%c", f_string_eol_s[0]);
      } // for

      status = F_none;
    }
    else {
      status = F_data_not;
    }

    for (f_array_length_t i = 0; i < variable->used; i++) {
      iki_read_macro_substitutions_t_delete_simple(substitutionss[i]);
    } // for

    return status;
  }
#endif // _di_iki_read_process_buffer_ranges_

#ifndef _di_iki_read_process_buffer_ranges_whole_
  f_status_t iki_read_process_buffer_ranges_whole(const f_console_arguments_t arguments, const f_string_t file_name, const f_string_range_t buffer_range, iki_read_data_t *data, f_iki_variable_t *variable, f_iki_vocabulary_t *vocabulary, f_iki_content_t *content, f_string_ranges_t *ranges) {
    f_status_t status = F_none;
    f_string_range_t range = buffer_range;

    status = fl_iki_read(&data->buffer, &range, variable, vocabulary, content);

    if (F_status_is_error(status)) {
      fll_error_print(data->error, F_status_set_fine(status), "fl_iki_read", F_true);
      return status;
    }

    if (!variable->used) {
      f_print_dynamic_partial(data->output.stream, data->buffer, buffer_range);
      return F_none;
    }

    const bool content_only = data->mode == iki_read_mode_content;

    iki_read_substitutions_t substitutionss[variable->used];

    memset(substitutionss, 0, sizeof(iki_read_substitutions_t) * variable->used);

    if (data->mode == iki_read_mode_literal || data->mode == iki_read_mode_content) {
      status = iki_read_substitutions_identify(arguments, file_name, data, vocabulary, substitutionss);

      if (F_status_is_error(status)) {
        fll_error_print(data->error, F_status_set_fine(status), "iki_read_substitutions_identify", F_true);

        for (f_array_length_t i = 0; i < variable->used; i++) {
          iki_read_macro_substitutions_t_delete_simple(substitutionss[i]);
        } // for

        return status;
      }
    }

    f_string_dynamics_t names = f_string_dynamics_t_initialize;
    f_string_range_t name_range = f_string_range_t_initialize;
    f_string_range_t substitution_range = f_string_range_t_initialize;

    bool name_missed = F_true;

    substitution_range.start = 0;

    if (data->parameters[iki_read_parameter_name].result == f_console_result_additional) {
      f_array_length_t i = 0;
      f_array_length_t j = 0;
      f_string_length_t length_argument = 0;

      for (f_array_length_t index = 0; i < data->parameters[iki_read_parameter_name].values.used; i++) {

        index = data->parameters[iki_read_parameter_name].values.array[i];
        length_argument = strnlen(arguments.argv[index], f_console_length_size);

        for (j = 0, name_missed = F_true; j < names.used; j++) {

          status = fl_string_compare(arguments.argv[index], names.array[j].string, length_argument, names.array[j].used);

          if (status == F_equal_to) {
            name_missed = F_false;
            break;
          }
        } // for

        if (name_missed) {
          f_macro_memory_structure_macro_increment(status, names, 1, f_iki_default_allocation_step, f_macro_string_dynamics_t_resize, F_array_too_large);

          if (F_status_is_error(status)) {
            fll_error_print(data->error, F_status_set_fine(status), "iki_read_process_buffer_ranges_whole", F_true);
            break;
          }

          status = fl_string_append_nulless(arguments.argv[index], length_argument, &names.array[names.used]);

          if (F_status_is_error(status)) {
            fll_error_print(data->error, F_status_set_fine(status), "fl_string_append_nulless", F_true);
            break;
          }

          names.used++;
        }
      } // for

      if (F_status_is_error(status)) {
        for (i = 0; i < variable->used; i++) {
          iki_read_macro_substitutions_t_delete_simple(substitutionss[i]);
        } // for

        fl_string_dynamics_delete(&names);
        return status;
      }
    }

    {
      f_string_length_t i = buffer_range.start;
      f_array_length_t j = 0;
      f_array_length_t k = 0;

      range = buffer_range;
      name_range.start = 0;

      while (i <= range.stop && j < variable->used) {

        if (i < variable->array[j].start) {
          range.start = i;
          range.stop = variable->array[j].start - 1;

          f_print_dynamic_partial(data->output.stream, data->buffer, range);

          range.start = variable->array[j].stop + 1;
          range.stop = buffer_range.stop;

          i = variable->array[j].start;
        }

        if (names.used) {
          name_missed = F_true;

          for (k = 0; k < names.used; k++) {
            name_range.stop = names.array[k].used - 1;

            status = fl_string_dynamic_partial_compare(data->buffer, names.array[k], vocabulary->array[j], name_range);

            if (status == F_equal_to) {
              name_missed = F_false;
              break;
            }
          } // for

          if (name_missed) {
            if (substitutionss[j].used) {
              iki_read_substitutions_print(*data, *variable, *content, *variable, substitutionss[j], j, F_false);
            }
            else {
              f_print_dynamic_partial(data->output.stream, data->buffer, variable->array[j]);
            }
          }
          else {
            if (substitutionss[j].used) {
              iki_read_substitutions_print(*data, *variable, *content, *ranges, substitutionss[j], j, content_only);
            }
            else {
              f_print_dynamic_partial(data->output.stream, data->buffer, ranges->array[j]);
            }
          }
        }
        else {
          if (substitutionss[j].used) {
            iki_read_substitutions_print(*data, *variable, *content, *ranges, substitutionss[j], j, content_only);
          }
          else {
            f_print_dynamic_partial(data->output.stream, data->buffer, ranges->array[j]);
          }
        }

        i = variable->array[j].stop + 1;
        j++;
      } // while

      if (i <= buffer_range.stop) {
        range.start = i;
        f_print_dynamic_partial(data->output.stream, data->buffer, range);
      }
    }

    for (f_array_length_t i = 0; i < variable->used; i++) {
      iki_read_macro_substitutions_t_delete_simple(substitutionss[i]);
    } // for

    fl_string_dynamics_delete(&names);
    return F_none;
  }
#endif // _di_iki_read_process_buffer_ranges_whole_

#ifndef _di_iki_read_process_buffer_total_
  f_status_t iki_read_process_buffer_total(const f_console_arguments_t arguments, const f_string_t file_name, iki_read_data_t *data, f_iki_variable_t *variable, f_iki_vocabulary_t *vocabulary, f_iki_content_t *content) {
    f_status_t status = F_none;
    f_string_range_t range = f_macro_string_range_t_initialize(data->buffer.used);

    status = iki_read_process_at(arguments, file_name, data, &range);

    if (status == F_true) {
      if (range.start > data->buffer.used) {
        printf("0\n");
        return F_none;
      }
    }
    else if (status == F_data_not) {
      printf("0\n");
      return F_none;
    }

    status = fl_iki_read(&data->buffer, &range, variable, vocabulary, content);

    if (F_status_is_error(status)) {
      fll_error_print(data->error, F_status_set_fine(status), "fl_iki_read", F_true);
      return status;
    }

    f_array_length_t total = 0;

    if (data->parameters[iki_read_parameter_name].result == f_console_result_additional) {
      f_string_dynamic_t name = f_string_dynamic_t_initialize;

      f_array_length_t index = 0;
      f_array_length_t i = 0;
      f_array_length_t j = 0;

      range.start = 0;

      for (; i < data->parameters[iki_read_parameter_name].values.used; i++) {

        index = data->parameters[iki_read_parameter_name].values.array[i];
        name.used = 0;

        status = fl_string_append_nulless(arguments.argv[index], strlen(arguments.argv[index]), &name);

        if (F_status_is_error(status)) {
          fll_error_print(data->error, F_status_set_fine(status), "fl_string_append_nulless", F_true);

          fl_string_dynamic_delete(&name);
          return status;
        }

        range.stop = name.used - 1;

        for (j = 0; j < vocabulary->used; j++) {
          status = fl_string_dynamic_partial_compare(name, data->buffer, range, vocabulary->array[j]);

          if (status == F_equal_to) total++;
        } // for
      } // for

      fl_string_dynamic_delete(&name);
    }
    else {
      total = variable->used;
    }

    printf("%llu\n", total);

    return F_none;
  }
#endif // _di_iki_read_process_buffer_total_

#ifndef _di_iki_read_substitutions_identify_
  f_status_t iki_read_substitutions_identify(const f_console_arguments_t arguments, const f_string_t file_name, iki_read_data_t *data, f_iki_vocabulary_t *vocabulary, iki_read_substitutions_t *substitutionss) {

    if (data->parameters[iki_read_parameter_substitute].result != f_console_result_additional) {
      return F_none;
    }

    f_status_t status = F_none;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_array_length_t index = 0;
    f_array_length_t index_2 = 0;

    f_string_length_t length = 0;

    f_console_parameter_t *parameter = &data->parameters[iki_read_parameter_substitute];

    for (; i < parameter->values.used; i += 3) {

      index = parameter->values.array[i];
      length = strnlen(arguments.argv[index], f_console_length_size);

      for (j = 0; j < vocabulary->used; j++) {

        status = fl_string_compare(arguments.argv[index], data->buffer.string + vocabulary->array[j].start, length, (vocabulary->array[j].stop - vocabulary->array[j].start) + 1);

        if (status == F_equal_to) {
          f_macro_memory_structure_macro_increment(status, substitutionss[j], 1, f_iki_default_allocation_step, iki_read_macro_substitutions_t_resize, F_array_too_large);
          if (F_status_is_error(status)) return status;

          index = parameter->values.array[i + 1];
          index_2 = substitutionss[j].used;
          substitutionss[j].array[index_2].replace.string = arguments.argv[index];
          substitutionss[j].array[index_2].replace.used = strnlen(arguments.argv[index], f_console_length_size);
          substitutionss[j].array[index_2].replace.size = substitutionss[j].array[index_2].replace.used;

          index = parameter->values.array[i + 2];
          substitutionss[j].array[index_2].with.string = arguments.argv[index];
          substitutionss[j].array[index_2].with.used = strnlen(arguments.argv[index], f_console_length_size);
          substitutionss[j].array[index_2].with.size = substitutionss[j].array[index_2].with.used;

          substitutionss[j].used++;
        }
      } // for
    } // for

    return F_none;
  }
#endif // _di_iki_read_substitutions_identify_

#ifndef _di_iki_read_substitutions_print_
  void iki_read_substitutions_print(const iki_read_data_t data, const f_iki_variable_t variable, const f_iki_content_t content, const f_string_ranges_t ranges, const iki_read_substitutions_t substitutions, const f_string_length_t index, const bool content_only) {
    f_status_t status = F_none;

    f_string_length_t i = 0;
    f_string_range_t range = f_string_range_t_initialize;

    range.start = 0;

    for (; i < substitutions.used; i++) {
      range.stop = substitutions.array[i].replace.used - 1;

      status = fl_string_dynamic_partial_compare(substitutions.array[i].replace, data.buffer, range, content.array[index]);
      if (status == F_equal_to) break;
    } // for

    if (status == F_equal_to) {
      if (content_only) {
        f_print_dynamic(data.output.stream, substitutions.array[i].with);
      }
      else {
        range.start = variable.array[index].start;
        range.stop = content.array[index].start - 1;

        f_print_dynamic_partial(data.output.stream, data.buffer, range);

        f_print_dynamic(data.output.stream, substitutions.array[i].with);

        range.start = content.array[index].stop + 1;
        range.stop = variable.array[index].stop;

        f_print_dynamic_partial(data.output.stream, data.buffer, range);
      }
    }
    else {
      f_print_dynamic_partial(data.output.stream, data.buffer, ranges.array[index]);
    }
  }
#endif // _di_iki_read_substitutions_print_

#ifdef __cplusplus
} // extern "C"
#endif
