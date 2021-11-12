#include "iki_read.h"
#include "private-common.h"
#include "private-iki_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_process_at_
  f_status_t iki_read_process_at(iki_read_main_t * const main, const f_string_t file_name, f_string_range_t *range) {

    if (main->parameters[iki_read_parameter_line].result != f_console_result_additional) {
      return F_false;
    }

    f_array_length_t line = 0;

    range->start = 0;
    if (main->line > 0) {
      for (; line < main->line && range->start < main->buffer.used; ++range->start) {
        if (main->buffer.string[range->start] == f_string_eol_s[0]) ++line;
      } // for
    }

    if (line == main->line) {
      for (range->stop = range->start; range->stop < main->buffer.used; ++range->stop) {
        if (main->buffer.string[range->stop] == f_string_eol_s[0]) break;
      } // for

      return F_true;
    }

    return F_data_not;
  }
#endif // _di_iki_read_process_at_

#ifndef _di_iki_read_process_buffer_
  f_status_t iki_read_process_buffer(iki_read_main_t * const main, const f_console_arguments_t *arguments, const f_string_t file_name) {

    f_status_t status = F_none;

    f_iki_variable_t variable = f_iki_variable_t_initialize;
    f_iki_vocabulary_t vocabulary = f_iki_vocabulary_t_initialize;
    f_iki_content_t content = f_iki_content_t_initialize;

    if (main->parameters[iki_read_parameter_whole].result == f_console_result_found) {
      f_string_range_t buffer_range = macro_f_string_range_t_initialize(main->buffer.used);

      status = iki_read_process_at(main, file_name, &buffer_range);

      if (status == F_true) {
        if (buffer_range.start > main->buffer.used) {
          return F_data_not;
        }
      }
      else if (status == F_data_not) {
        return F_data_not;
      }

      if (main->mode == iki_read_mode_content) {
        status = iki_read_process_buffer_ranges_whole(main, arguments, file_name, buffer_range, &variable, &vocabulary, &content, &content);
      }
      else if (main->mode == iki_read_mode_literal) {
        status = iki_read_process_buffer_ranges_whole(main, arguments, file_name, buffer_range, &variable, &vocabulary, &content, &variable);
      }
      else if (main->mode == iki_read_mode_object) {
        status = iki_read_process_buffer_ranges_whole(main, arguments, file_name, buffer_range, &variable, &vocabulary, &content, &vocabulary);
      }
    }
    else if (main->mode == iki_read_mode_total) {
      status = iki_read_process_buffer_total(main, arguments, file_name, &variable, &vocabulary, &content);
    }
    else {
      f_string_range_t buffer_range = macro_f_string_range_t_initialize(main->buffer.used);

      status = iki_read_process_at(main, file_name, &buffer_range);

      if (status == F_true) {
        if (buffer_range.start > main->buffer.used) {
          return F_data_not;
        }
      }
      else if (status == F_data_not) {
        return F_data_not;
      }

      if (main->mode == iki_read_mode_content) {
        status = iki_read_process_buffer_ranges(main, arguments, file_name, &buffer_range, &variable, &vocabulary, &content, &content);
      }
      else if (main->mode == iki_read_mode_literal) {
        status = iki_read_process_buffer_ranges(main, arguments, file_name, &buffer_range, &variable, &vocabulary, &content, &variable);
      }
      else if (main->mode == iki_read_mode_object) {
        status = iki_read_process_buffer_ranges(main, arguments, file_name, &buffer_range, &variable, &vocabulary, &content, &vocabulary);
      }
    }

    macro_f_iki_variable_t_delete_simple(variable);
    macro_f_iki_vocabulary_t_delete_simple(vocabulary);
    macro_f_iki_content_t_delete_simple(content);
    return status;
  }
#endif // _di_iki_read_process_buffer_

#ifndef _di_iki_read_process_buffer_ranges_
  f_status_t iki_read_process_buffer_ranges(iki_read_main_t * const main, const f_console_arguments_t *arguments, const f_string_t file_name, f_string_range_t *buffer_range, f_iki_variable_t *variable, f_iki_vocabulary_t *vocabulary, f_iki_content_t *content, f_string_ranges_t *ranges) {

    f_status_t status = F_none;

    bool unmatched = F_true;

    {
      f_state_t state = macro_f_state_t_initialize(iki_read_common_allocation_large_d, iki_read_common_allocation_small_d, 0, 0, 0, 0, 0);

      status = fl_iki_read(state, &main->buffer, buffer_range, variable, vocabulary, content);
    }

    if (F_status_is_error(status)) {
      fll_error_print(main->error, F_status_set_fine(status), "fl_iki_read", F_true);

      return status;
    }

    const bool content_only = main->mode == iki_read_mode_content;

    iki_read_substitutions_t substitutionss[variable->used];

    memset(substitutionss, 0, sizeof(iki_read_substitutions_t) * variable->used);

    if (main->mode == iki_read_mode_literal || main->mode == iki_read_mode_content) {
      status = iki_read_substitutions_identify(main, arguments, file_name, vocabulary, substitutionss);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "iki_read_substitutions_identify", F_true);

        for (f_array_length_t i = 0; i < variable->used; ++i) {
          macro_iki_read_substitutions_t_delete_simple(substitutionss[i]);
        } // for

        return status;
      }
    }

    if (main->parameters[iki_read_parameter_name].result == f_console_result_additional) {
      f_string_dynamic_t name = f_string_dynamic_t_initialize;

      f_array_length_t index = 0;
      f_array_length_t i = 0;
      f_array_length_t j = 0;
      f_array_length_t matches = 0;
      buffer_range->start = 0;

      for (; i < main->parameters[iki_read_parameter_name].values.used; ++i) {

        index = main->parameters[iki_read_parameter_name].values.array[i];
        name.used = 0;

        status = f_string_append_nulless(arguments->argv[index], strlen(arguments->argv[index]), &name);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "f_string_append_nulless", F_true);

          for (f_array_length_t i = 0; i < variable->used; ++i) {
            macro_iki_read_substitutions_t_delete_simple(substitutionss[i]);
          } // for

          macro_f_string_dynamic_t_delete_simple(name);
          return status;
        }

        buffer_range->stop = name.used - 1;

        flockfile(main->output.to.stream);

        for (j = 0; j < vocabulary->used; ++j) {

          status = fl_string_dynamic_partial_compare(name, main->buffer, *buffer_range, vocabulary->array[j]);

          if (status == F_equal_to) {
            unmatched = F_false;

            if (main->parameters[iki_read_parameter_at].result == f_console_result_additional) {
              if (matches++ != main->at) continue;
            }

            if (substitutionss[j].used) {
              iki_read_substitutions_print(main, *variable, *content, *ranges, substitutionss[j], j, content_only);
            }
            else {
              f_print_dynamic_partial(main->buffer, ranges->array[j], main->output.to.stream);
            }

            f_print_character(f_string_eol_s[0], main->output.to.stream);
          }
        } // for

        funlockfile(main->output.to.stream);
      } // for

      macro_f_string_dynamic_t_delete_simple(name);

      if (unmatched) status = F_data_not;
      else status = F_none;
    }
    else if (ranges->used) {
      if (main->parameters[iki_read_parameter_at].result == f_console_result_additional) {
        if (main->at < ranges->used) {
          flockfile(main->output.to.stream);

          if (substitutionss[main->at].used) {
            iki_read_substitutions_print(main, *variable, *content, *ranges, substitutionss[main->at], main->at, content_only);
          }
          else {
            f_print_dynamic_partial(main->buffer, ranges->array[main->at], main->output.to.stream);
          }

          f_print_character(f_string_eol_s[0], main->output.to.stream);

          funlockfile(main->output.to.stream);

          status = F_none;
        }
        else {
          status = F_data_not;
        }
      }
      else {
        flockfile(main->output.to.stream);

        for (f_array_length_t i = 0; i < ranges->used; ++i) {

          if (substitutionss[i].used) {
            iki_read_substitutions_print(main, *variable, *content, *ranges, substitutionss[i], i, content_only);
          }
          else {
            f_print_dynamic_partial(main->buffer, ranges->array[i], main->output.to.stream);
          }

          f_print_character(f_string_eol_s[0], main->output.to.stream);
        } // for

        funlockfile(main->output.to.stream);

        status = F_none;
      }
    }
    else {
      status = F_data_not;
    }

    for (f_array_length_t i = 0; i < variable->used; ++i) {
      macro_iki_read_substitutions_t_delete_simple(substitutionss[i]);
    } // for

    return status;
  }
#endif // _di_iki_read_process_buffer_ranges_

#ifndef _di_iki_read_process_buffer_ranges_whole_
  f_status_t iki_read_process_buffer_ranges_whole(iki_read_main_t * const main, const f_console_arguments_t *arguments, const f_string_t file_name, const f_string_range_t buffer_range, f_iki_variable_t *variable, f_iki_vocabulary_t *vocabulary, f_iki_content_t *content, f_string_ranges_t *ranges) {

    f_status_t status = F_none;
    f_string_range_t range = buffer_range;

    {
      f_state_t state = macro_f_state_t_initialize(iki_read_common_allocation_large_d, iki_read_common_allocation_small_d, 0, 0, 0, 0, 0);

      status = fl_iki_read(state, &main->buffer, &range, variable, vocabulary, content);
    }

    if (F_status_is_error(status)) {
      fll_error_print(main->error, F_status_set_fine(status), "fl_iki_read", F_true);

      return status;
    }

    if (!variable->used) {
      fll_print_dynamic_partial(main->buffer, buffer_range, main->output.to.stream);

      return F_none;
    }

    const bool content_only = main->mode == iki_read_mode_content;

    iki_read_substitutions_t substitutionss[variable->used];

    memset(substitutionss, 0, sizeof(iki_read_substitutions_t) * variable->used);

    if (main->mode == iki_read_mode_literal || main->mode == iki_read_mode_content) {
      status = iki_read_substitutions_identify(main, arguments, file_name, vocabulary, substitutionss);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "iki_read_substitutions_identify", F_true);

        for (f_array_length_t i = 0; i < variable->used; ++i) {
          macro_iki_read_substitutions_t_delete_simple(substitutionss[i]);
        } // for

        return status;
      }
    }

    f_string_dynamics_t names = f_string_dynamics_t_initialize;
    f_string_range_t name_range = f_string_range_t_initialize;
    f_string_range_t substitution_range = f_string_range_t_initialize;

    bool name_missed = F_true;

    substitution_range.start = 0;

    if (main->parameters[iki_read_parameter_name].result == f_console_result_additional) {
      f_array_length_t i = 0;
      f_array_length_t j = 0;
      f_array_length_t length_argument = 0;

      for (f_array_length_t index = 0; i < main->parameters[iki_read_parameter_name].values.used; ++i) {

        index = main->parameters[iki_read_parameter_name].values.array[i];
        length_argument = strnlen(arguments->argv[index], f_console_parameter_size);

        for (j = 0, name_missed = F_true; j < names.used; ++j) {

          status = fl_string_compare(arguments->argv[index], names.array[j].string, length_argument, names.array[j].used);

          if (status == F_equal_to) {
            name_missed = F_false;
            break;
          }
        } // for

        if (name_missed) {
          macro_f_memory_structure_increment(status, names, 1, F_iki_default_allocation_step_d, macro_f_string_dynamics_t_resize, F_array_too_large);

          if (F_status_is_error(status)) {
            fll_error_print(main->error, F_status_set_fine(status), "iki_read_process_buffer_ranges_whole", F_true);
            break;
          }

          status = f_string_append_nulless(arguments->argv[index], length_argument, &names.array[names.used]);

          if (F_status_is_error(status)) {
            fll_error_print(main->error, F_status_set_fine(status), "f_string_append_nulless", F_true);
            break;
          }

          ++names.used;
        }
      } // for

      if (F_status_is_error(status)) {
        for (i = 0; i < variable->used; ++i) {
          macro_iki_read_substitutions_t_delete_simple(substitutionss[i]);
        } // for

        macro_f_string_dynamics_t_delete_simple(names);
        return status;
      }
    }

    {
      f_array_length_t i = buffer_range.start;
      f_array_length_t j = 0;
      f_array_length_t k = 0;
      f_array_length_t stop = variable->used;

      range = buffer_range;
      name_range.start = 0;

      flockfile(main->output.to.stream);

      while (i <= range.stop && j < stop) {

        if (i < variable->array[j].start) {
          range.start = i;
          range.stop = variable->array[j].start - 1;

          f_print_dynamic_partial(main->buffer, range, main->output.to.stream);

          range.start = variable->array[j].stop + 1;
          range.stop = buffer_range.stop;

          i = variable->array[j].start;
        }

        if (names.used) {
          name_missed = F_true;

          for (k = 0; k < names.used; ++k) {
            name_range.stop = names.array[k].used - 1;

            status = fl_string_dynamic_partial_compare(main->buffer, names.array[k], vocabulary->array[j], name_range);

            if (status == F_equal_to) {
              name_missed = F_false;
              break;
            }
          } // for

          if (name_missed) {
            if (substitutionss[j].used) {
              iki_read_substitutions_print(main, *variable, *content, *variable, substitutionss[j], j, F_false);
            }
            else {
              f_print_dynamic_partial(main->buffer, variable->array[j], main->output.to.stream);
            }
          }
          else {
            if (substitutionss[j].used) {
              iki_read_substitutions_print(main, *variable, *content, *ranges, substitutionss[j], j, content_only);
            }
            else {
              f_print_dynamic_partial(main->buffer, ranges->array[j], main->output.to.stream);
            }
          }
        }
        else {
          if (substitutionss[j].used) {
            iki_read_substitutions_print(main, *variable, *content, *ranges, substitutionss[j], j, content_only);
          }
          else {
            f_print_dynamic_partial(main->buffer, ranges->array[j], main->output.to.stream);
          }
        }

        i = variable->array[j].stop + 1;
        ++j;
      } // while

      if (i <= buffer_range.stop) {
        range.start = i;
        f_print_dynamic_partial(main->buffer, range, main->output.to.stream);
      }

      funlockfile(main->output.to.stream);
    }

    for (f_array_length_t i = 0; i < variable->used; ++i) {
      macro_iki_read_substitutions_t_delete_simple(substitutionss[i]);
    } // for

    macro_f_string_dynamics_t_delete_simple(names);
    return F_none;
  }
#endif // _di_iki_read_process_buffer_ranges_whole_

#ifndef _di_iki_read_process_buffer_total_
  f_status_t iki_read_process_buffer_total(iki_read_main_t * const main, const f_console_arguments_t *arguments, const f_string_t file_name, f_iki_variable_t *variable, f_iki_vocabulary_t *vocabulary, f_iki_content_t *content) {

    f_status_t status = F_none;
    f_string_range_t range = macro_f_string_range_t_initialize(main->buffer.used);

    status = iki_read_process_at(main, file_name, &range);

    if (status == F_true) {
      if (range.start > main->buffer.used) {
        fll_print_format("0%c", main->output.to.stream, f_string_eol_s[0]);

        return F_none;
      }
    }
    else if (status == F_data_not) {
      fll_print_format("0%c", main->output.to.stream, f_string_eol_s[0]);

      return F_none;
    }

    {
      f_state_t state = macro_f_state_t_initialize(iki_read_common_allocation_large_d, iki_read_common_allocation_small_d, 0, 0, 0, 0, 0);

      status = fl_iki_read(state, &main->buffer, &range, variable, vocabulary, content);
    }

    if (F_status_is_error(status)) {
      fll_error_print(main->error, F_status_set_fine(status), "fl_iki_read", F_true);

      return status;
    }

    f_array_length_t total = 0;

    if (main->parameters[iki_read_parameter_name].result == f_console_result_additional) {
      f_string_dynamic_t name = f_string_dynamic_t_initialize;

      f_array_length_t index = 0;
      f_array_length_t i = 0;
      f_array_length_t j = 0;

      range.start = 0;

      for (; i < main->parameters[iki_read_parameter_name].values.used; ++i) {

        if (iki_read_signal_received(main)) {
          macro_f_string_dynamic_t_delete_simple(name);

          return F_status_set_error(F_interrupt);
        }

        index = main->parameters[iki_read_parameter_name].values.array[i];
        name.used = 0;

        status = f_string_append_nulless(arguments->argv[index], strlen(arguments->argv[index]), &name);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "f_string_append_nulless", F_true);

          macro_f_string_dynamic_t_delete_simple(name);
          return status;
        }

        range.stop = name.used - 1;

        for (j = 0; j < vocabulary->used; ++j) {

          status = fl_string_dynamic_partial_compare(name, main->buffer, range, vocabulary->array[j]);

          if (status == F_equal_to) ++total;
        } // for
      } // for

      macro_f_string_dynamic_t_delete_simple(name);
    }
    else {
      total = variable->used;
    }

    // if that at position is within the actual total, then the total at the given position is 1, otherwise is 0.
    if (main->parameters[iki_read_parameter_at].result == f_console_result_additional) {
      if (main->at < total) {
        total = 1;
      }
      else {
        total = 0;
      }
    }

    fll_print_format("%ul%c", main->output.to.stream, total, f_string_eol_s[0]);

    return F_none;
  }
#endif // _di_iki_read_process_buffer_total_

#ifndef _di_iki_read_substitutions_identify_
  f_status_t iki_read_substitutions_identify(iki_read_main_t * const main, const f_console_arguments_t *arguments, const f_string_t file_name, f_iki_vocabulary_t *vocabulary, iki_read_substitutions_t *substitutionss) {

    if (main->parameters[iki_read_parameter_substitute].result != f_console_result_additional) {
      return F_none;
    }

    f_status_t status = F_none;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_array_length_t index = 0;
    f_array_length_t index_2 = 0;

    f_array_length_t length = 0;

    f_console_parameter_t *parameter = &main->parameters[iki_read_parameter_substitute];

    for (; i < parameter->values.used; i += 3) {

      index = parameter->values.array[i];
      length = strnlen(arguments->argv[index], f_console_parameter_size);

      for (j = 0; j < vocabulary->used; ++j) {

        status = fl_string_compare(arguments->argv[index], main->buffer.string + vocabulary->array[j].start, length, (vocabulary->array[j].stop - vocabulary->array[j].start) + 1);

        if (status == F_equal_to) {
          macro_f_memory_structure_increment(status, substitutionss[j], 1, F_iki_default_allocation_step_d, macro_iki_read_substitutions_t_resize, F_array_too_large);
          if (F_status_is_error(status)) return status;

          index = parameter->values.array[i + 1];
          index_2 = substitutionss[j].used;
          substitutionss[j].array[index_2].replace.string = arguments->argv[index];
          substitutionss[j].array[index_2].replace.used = strnlen(arguments->argv[index], f_console_parameter_size);
          substitutionss[j].array[index_2].replace.size = substitutionss[j].array[index_2].replace.used;

          index = parameter->values.array[i + 2];
          substitutionss[j].array[index_2].with.string = arguments->argv[index];
          substitutionss[j].array[index_2].with.used = strnlen(arguments->argv[index], f_console_parameter_size);
          substitutionss[j].array[index_2].with.size = substitutionss[j].array[index_2].with.used;

          ++substitutionss[j].used;
        }
      } // for
    } // for

    return F_none;
  }
#endif // _di_iki_read_substitutions_identify_

#ifndef _di_iki_read_substitutions_print_
  void iki_read_substitutions_print(iki_read_main_t * const main, const f_iki_variable_t variable, const f_iki_content_t content, const f_string_ranges_t ranges, const iki_read_substitutions_t substitutions, const f_array_length_t index, const bool content_only) {

    f_status_t status = F_none;

    f_array_length_t i = 0;
    f_string_range_t range = f_string_range_t_initialize;

    range.start = 0;

    for (; i < substitutions.used; ++i) {

      range.stop = substitutions.array[i].replace.used - 1;

      status = fl_string_dynamic_partial_compare(substitutions.array[i].replace, main->buffer, range, content.array[index]);
      if (status == F_equal_to) break;
    } // for

    if (status == F_equal_to) {
      if (content_only) {
        f_print_dynamic(substitutions.array[i].with, main->output.to.stream);
      }
      else {
        range.start = variable.array[index].start;
        range.stop = content.array[index].start - 1;

        f_print_dynamic_partial(main->buffer, range, main->output.to.stream);

        f_print_dynamic(substitutions.array[i].with, main->output.to.stream);

        range.start = content.array[index].stop + 1;
        range.stop = variable.array[index].stop;

        f_print_dynamic_partial(main->buffer, range, main->output.to.stream);
      }
    }
    else {
      f_print_dynamic_partial(main->buffer, ranges.array[index], main->output.to.stream);
    }
  }
#endif // _di_iki_read_substitutions_print_

#ifdef __cplusplus
} // extern "C"
#endif
