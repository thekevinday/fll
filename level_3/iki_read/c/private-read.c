#include "iki_read.h"
#include "private-common.h"
#include "private-print.h"
#include "private-read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_process_at_
  f_status_t iki_read_process_at(iki_read_main_t * const main, f_string_range_t *range) {

    if (main->parameters.array[iki_read_parameter_line_e].result != f_console_result_additional_e) {
      return F_false;
    }

    f_array_length_t line = 0;

    range->start = 0;
    if (main->line > 0) {
      for (; line < main->line && range->start < main->buffer.used; ++range->start) {
        if (main->buffer.string[range->start] == f_string_eol_s.string[0]) ++line;
      } // for
    }

    if (line == main->line) {
      for (range->stop = range->start; range->stop < main->buffer.used; ++range->stop) {
        if (main->buffer.string[range->stop] == f_string_eol_s.string[0]) break;
      } // for

      return F_true;
    }

    return F_data_not;
  }
#endif // _di_iki_read_process_at_

#ifndef _di_iki_read_process_buffer_
  f_status_t iki_read_process_buffer(iki_read_main_t * const main) {

    f_status_t status = F_none;
    f_iki_data_t iki_data = f_iki_data_t_initialize;

    if (main->parameters.array[iki_read_parameter_whole_e].result == f_console_result_found_e) {
      f_string_range_t buffer_range = macro_f_string_range_t_initialize(main->buffer.used);

      status = iki_read_process_at(main, &buffer_range);

      if (status == F_true) {
        if (buffer_range.start > main->buffer.used) {
          return F_data_not;
        }
      }
      else if (status == F_data_not) {
        return F_data_not;
      }

      if (main->mode == iki_read_mode_content_e) {
        status = iki_read_process_buffer_ranges_whole(main, buffer_range, &iki_data, &iki_data.content);
      }
      else if (main->mode == iki_read_mode_literal_e) {
        status = iki_read_process_buffer_ranges_whole(main, buffer_range, &iki_data, &iki_data.variable);
      }
      else if (main->mode == iki_read_mode_object_e) {
        status = iki_read_process_buffer_ranges_whole(main, buffer_range, &iki_data, &iki_data.vocabulary);
      }
    }
    else if (main->mode == iki_read_mode_total_e) {
      status = iki_read_process_buffer_total(main, &iki_data);
    }
    else {
      f_string_range_t buffer_range = macro_f_string_range_t_initialize(main->buffer.used);

      status = iki_read_process_at(main, &buffer_range);

      if (status == F_true && buffer_range.start > main->buffer.used || status == F_data_not) {
        f_iki_data_delete(&iki_data);

        return F_data_not;
      }

      if (main->mode == iki_read_mode_content_e) {
        status = iki_read_process_buffer_ranges(main, &buffer_range, &iki_data, &iki_data.content);
      }
      else if (main->mode == iki_read_mode_literal_e) {
        status = iki_read_process_buffer_ranges(main, &buffer_range, &iki_data, &iki_data.variable);
      }
      else if (main->mode == iki_read_mode_object_e) {
        status = iki_read_process_buffer_ranges(main, &buffer_range, &iki_data, &iki_data.vocabulary);
      }
    }

    f_iki_data_delete(&iki_data);

    return status;
  }
#endif // _di_iki_read_process_buffer_

#ifndef _di_iki_read_process_buffer_ranges_
  f_status_t iki_read_process_buffer_ranges(iki_read_main_t * const main, f_string_range_t *buffer_range, f_iki_data_t *iki_data, f_string_ranges_t *ranges) {

    f_status_t status = F_none;

    bool unmatched = F_true;

    {
      f_state_t state = macro_f_state_t_initialize(iki_read_common_allocation_large_d, iki_read_common_allocation_small_d, 0, 0, 0, 0, 0);

      status = fl_iki_read(state, &main->buffer, buffer_range, iki_data);
    }

    if (F_status_is_error(status)) {
      fll_error_print(main->error, F_status_set_fine(status), "fl_iki_read", F_true);

      return status;
    }

    for (f_array_length_t i = 0; i < iki_data->delimits.used; ++i) {
      main->buffer.string[iki_data->delimits.array[i]] = f_iki_syntax_placeholder_s.string[0];
    } // for

    const bool content_only = main->mode == iki_read_mode_content_e;

    iki_read_substitutions_t substitutionss[iki_data->variable.used];

    memset(substitutionss, 0, sizeof(iki_read_substitutions_t) * iki_data->variable.used);

    if (main->mode == iki_read_mode_literal_e || main->mode == iki_read_mode_content_e) {
      status = iki_read_substitutions_identify(main, &iki_data->vocabulary, substitutionss);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "iki_read_substitutions_identify", F_true);

        for (f_array_length_t i = 0; i < iki_data->variable.used; ++i) {
          macro_iki_read_substitutions_t_delete_simple(substitutionss[i]);
        } // for

        return status;
      }
    }

    if (main->parameters.array[iki_read_parameter_name_e].result == f_console_result_additional_e) {
      f_string_dynamic_t name = f_string_dynamic_t_initialize;

      f_array_length_t index = 0;
      f_array_length_t i = 0;
      f_array_length_t j = 0;
      f_array_length_t matches = 0;
      buffer_range->start = 0;

      for (; i < main->parameters.array[iki_read_parameter_name_e].values.used; ++i) {

        index = main->parameters.array[iki_read_parameter_name_e].values.array[i];
        name.used = 0;

        status = f_string_dynamic_append_nulless(main->parameters.arguments.array[index], &name);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);

          for (f_array_length_t i = 0; i < iki_data->variable.used; ++i) {
            macro_iki_read_substitutions_t_delete_simple(substitutionss[i]);
          } // for

          f_string_dynamic_resize(0, &name);
          return status;
        }

        buffer_range->stop = name.used - 1;

        flockfile(main->output.to.stream);

        for (j = 0; j < iki_data->vocabulary.used; ++j) {

          status = fl_string_dynamic_partial_compare(name, main->buffer, *buffer_range, iki_data->vocabulary.array[j]);

          if (status == F_equal_to) {
            unmatched = F_false;

            if (main->parameters.array[iki_read_parameter_at_e].result == f_console_result_additional_e) {
              if (matches++ != main->at) continue;
            }

            if (substitutionss[j].used) {
              iki_read_substitutions_print(main, *iki_data, *ranges, substitutionss[j], j, content_only);
            }
            else {
              f_print_dynamic_partial(main->buffer, ranges->array[j], main->output.to.stream);
            }

            f_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
          }
        } // for

        funlockfile(main->output.to.stream);
      } // for

      f_string_dynamic_resize(0, &name);

      if (unmatched) {
        status = F_data_not;
      }
      else {
        status = F_none;
      }
    }
    else if (ranges->used) {
      if (main->parameters.array[iki_read_parameter_at_e].result == f_console_result_additional_e) {
        if (main->at < ranges->used) {
          flockfile(main->output.to.stream);

          if (substitutionss[main->at].used) {
            iki_read_substitutions_print(main, *iki_data, *ranges, substitutionss[main->at], main->at, content_only);
          }
          else {
            f_print_dynamic_partial(main->buffer, ranges->array[main->at], main->output.to.stream);
          }

          f_print_dynamic_raw(f_string_eol_s, main->output.to.stream);

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
            iki_read_substitutions_print(main, *iki_data, *ranges, substitutionss[i], i, content_only);
          }
          else {
            f_print_dynamic_partial(main->buffer, ranges->array[i], main->output.to.stream);
          }

          f_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
        } // for

        funlockfile(main->output.to.stream);

        status = F_none;
      }
    }
    else {
      status = F_data_not;
    }

    for (f_array_length_t i = 0; i < iki_data->variable.used; ++i) {
      macro_iki_read_substitutions_t_delete_simple(substitutionss[i]);
    } // for

    return status;
  }
#endif // _di_iki_read_process_buffer_ranges_

#ifndef _di_iki_read_process_buffer_ranges_whole_
  f_status_t iki_read_process_buffer_ranges_whole(iki_read_main_t * const main, const f_string_range_t buffer_range, f_iki_data_t *iki_data, f_string_ranges_t *ranges) {

    f_status_t status = F_none;
    f_string_range_t range = buffer_range;

    {
      f_state_t state = macro_f_state_t_initialize(iki_read_common_allocation_large_d, iki_read_common_allocation_small_d, 0, 0, 0, 0, 0);

      status = fl_iki_read(state, &main->buffer, &range, iki_data);
    }

    if (F_status_is_error(status)) {
      fll_error_print(main->error, F_status_set_fine(status), "fl_iki_read", F_true);

      return status;
    }

    for (f_array_length_t i = 0; i < iki_data->delimits.used; ++i) {
      main->buffer.string[iki_data->delimits.array[i]] = f_iki_syntax_placeholder_s.string[0];
    } // for

    if (!iki_data->variable.used) {
      fll_print_dynamic_partial(main->buffer, buffer_range, main->output.to.stream);

      return F_none;
    }

    const bool content_only = main->mode == iki_read_mode_content_e;

    iki_read_substitutions_t substitutionss[iki_data->variable.used];

    memset(substitutionss, 0, sizeof(iki_read_substitutions_t) * iki_data->variable.used);

    if (main->mode == iki_read_mode_literal_e || main->mode == iki_read_mode_content_e) {
      status = iki_read_substitutions_identify(main, &iki_data->vocabulary, substitutionss);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "iki_read_substitutions_identify", F_true);

        for (f_array_length_t i = 0; i < iki_data->variable.used; ++i) {
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

    if (main->parameters.array[iki_read_parameter_name_e].result == f_console_result_additional_e) {
      f_array_length_t i = 0;
      f_array_length_t j = 0;

      for (f_array_length_t index = 0; i < main->parameters.array[iki_read_parameter_name_e].values.used; ++i) {

        index = main->parameters.array[iki_read_parameter_name_e].values.array[i];

        for (j = 0, name_missed = F_true; j < names.used; ++j) {

          if (fl_string_dynamic_compare(main->parameters.arguments.array[index], names.array[j]) == F_equal_to) {
            name_missed = F_false;

            break;
          }
        } // for

        if (name_missed) {
          macro_f_memory_structure_increment(status, names, 1, F_iki_default_allocation_step_d, macro_f_string_dynamics_t_resize, F_array_too_large);

          if (F_status_is_error(status)) {
            fll_error_print(main->error, F_status_set_fine(status), "macro_f_memory_structure_increment", F_true);

            break;
          }

          status = f_string_dynamic_append_nulless(main->parameters.arguments.array[index], &names.array[names.used]);

          if (F_status_is_error(status)) {
            fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);

            break;
          }

          ++names.used;
        }
      } // for

      if (F_status_is_error(status)) {
        for (i = 0; i < iki_data->variable.used; ++i) {
          macro_iki_read_substitutions_t_delete_simple(substitutionss[i]);
        } // for

        f_string_dynamics_resize(0, &names);

        return status;
      }
    }

    {
      f_array_length_t i = buffer_range.start;
      f_array_length_t j = 0;
      f_array_length_t k = 0;
      f_array_length_t stop = iki_data->variable.used;

      range = buffer_range;
      name_range.start = 0;

      flockfile(main->output.to.stream);

      while (i <= range.stop && j < stop) {

        if (i < iki_data->variable.array[j].start) {
          range.start = i;
          range.stop = iki_data->variable.array[j].start - 1;

          f_print_dynamic_partial(main->buffer, range, main->output.to.stream);

          range.start = iki_data->variable.array[j].stop + 1;
          range.stop = buffer_range.stop;

          i = iki_data->variable.array[j].start;
        }

        if (names.used) {
          name_missed = F_true;

          for (k = 0; k < names.used; ++k) {
            name_range.stop = names.array[k].used - 1;

            status = fl_string_dynamic_partial_compare(main->buffer, names.array[k], iki_data->vocabulary.array[j], name_range);

            if (status == F_equal_to) {
              name_missed = F_false;
              break;
            }
          } // for

          if (name_missed) {
            if (substitutionss[j].used) {
              iki_read_substitutions_print(main, *iki_data, iki_data->variable, substitutionss[j], j, F_false);
            }
            else {
              f_print_dynamic_partial(main->buffer, iki_data->variable.array[j], main->output.to.stream);
            }
          }
          else {
            if (substitutionss[j].used) {
              iki_read_substitutions_print(main, *iki_data, *ranges, substitutionss[j], j, content_only);
            }
            else {
              f_print_dynamic_partial(main->buffer, ranges->array[j], main->output.to.stream);
            }
          }
        }
        else {
          if (substitutionss[j].used) {
            iki_read_substitutions_print(main, *iki_data, *ranges, substitutionss[j], j, content_only);
          }
          else {
            f_print_dynamic_partial(main->buffer, ranges->array[j], main->output.to.stream);
          }
        }

        i = iki_data->variable.array[j].stop + 1;
        ++j;
      } // while

      if (i <= buffer_range.stop) {
        range.start = i;
        f_print_dynamic_partial(main->buffer, range, main->output.to.stream);
      }

      funlockfile(main->output.to.stream);
    }

    for (f_array_length_t i = 0; i < iki_data->variable.used; ++i) {
      macro_iki_read_substitutions_t_delete_simple(substitutionss[i]);
    } // for

    f_string_dynamics_resize(0, &names);

    return F_none;
  }
#endif // _di_iki_read_process_buffer_ranges_whole_

#ifndef _di_iki_read_process_buffer_total_
  f_status_t iki_read_process_buffer_total(iki_read_main_t * const main, f_iki_data_t *iki_data) {

    f_status_t status = F_none;
    f_string_range_t range = macro_f_string_range_t_initialize(main->buffer.used);

    status = iki_read_process_at(main, &range);

    if (status == F_true) {
      if (range.start > main->buffer.used) {
        fll_print_format("%r%r", main->output.to.stream, f_string_ascii_0_s, f_string_eol_s);

        return F_none;
      }
    }
    else if (status == F_data_not) {
      fll_print_format("%r%r", main->output.to.stream, f_string_ascii_0_s, f_string_eol_s);

      return F_none;
    }

    {
      f_state_t state = macro_f_state_t_initialize(iki_read_common_allocation_large_d, iki_read_common_allocation_small_d, 0, 0, 0, 0, 0);

      status = fl_iki_read(state, &main->buffer, &range, iki_data);
    }

    if (F_status_is_error(status)) {
      fll_error_print(main->error, F_status_set_fine(status), "fl_iki_read", F_true);

      return status;
    }

    for (f_array_length_t i = 0; i < iki_data->delimits.used; ++i) {
      main->buffer.string[iki_data->delimits.array[i]] = f_iki_syntax_placeholder_s.string[0];
    } // for

    f_array_length_t total = 0;

    if (main->parameters.array[iki_read_parameter_name_e].result == f_console_result_additional_e) {
      f_string_dynamic_t name = f_string_dynamic_t_initialize;

      f_array_length_t index = 0;
      f_array_length_t i = 0;
      f_array_length_t j = 0;

      range.start = 0;

      for (uint16_t signal_check = 0; i < main->parameters.array[iki_read_parameter_name_e].values.used; ++i) {

        if (!((++signal_check) % iki_read_signal_check_d)) {
          if (iki_read_signal_received(main)) {
            f_string_dynamic_resize(0, &name);

            return F_status_set_error(F_interrupt);
          }

          signal_check = 0;
        }

        index = main->parameters.array[iki_read_parameter_name_e].values.array[i];
        name.used = 0;

        status = f_string_dynamic_append_nulless(main->parameters.arguments.array[index], &name);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);

          f_string_dynamic_resize(0, &name);

          return status;
        }

        range.stop = name.used - 1;

        for (j = 0; j < iki_data->vocabulary.used; ++j) {

          status = fl_string_dynamic_partial_compare(name, main->buffer, range, iki_data->vocabulary.array[j]);

          if (status == F_equal_to) ++total;
        } // for
      } // for

      f_string_dynamic_resize(0, &name);
    }
    else {
      total = iki_data->variable.used;
    }

    // if that at position is within the actual total, then the total at the given position is 1, otherwise is 0.
    if (main->parameters.array[iki_read_parameter_at_e].result == f_console_result_additional_e) {
      if (main->at < total) {
        total = 1;
      }
      else {
        total = 0;
      }
    }

    fll_print_format("%ul%r", main->output.to.stream, total, f_string_eol_s);

    return F_none;
  }
#endif // _di_iki_read_process_buffer_total_

#ifndef _di_iki_read_substitutions_identify_
  f_status_t iki_read_substitutions_identify(iki_read_main_t * const main, f_iki_vocabulary_t *vocabulary, iki_read_substitutions_t *substitutionss) {

    if (main->parameters.array[iki_read_parameter_substitute_e].result != f_console_result_additional_e) {
      return F_none;
    }

    f_status_t status = F_none;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_array_length_t index = 0;
    f_array_length_t index_2 = 0;

    f_console_parameter_t *parameter = &main->parameters.array[iki_read_parameter_substitute_e];

    for (; i < parameter->values.used; i += 3) {

      index = parameter->values.array[i];

      for (j = 0; j < vocabulary->used; ++j) {

        if (fl_string_dynamic_partial_compare_string(main->parameters.arguments.array[index].string, main->buffer, main->parameters.arguments.array[index].used, vocabulary->array[j]) == F_equal_to) {
          macro_f_memory_structure_increment(status, substitutionss[j], 1, F_iki_default_allocation_step_d, macro_iki_read_substitutions_t_resize, F_array_too_large);
          if (F_status_is_error(status)) return status;

          index = parameter->values.array[i + 1];
          index_2 = substitutionss[j].used;
          substitutionss[j].array[index_2].replace = main->parameters.arguments.array[index];

          index = parameter->values.array[i + 2];
          substitutionss[j].array[index_2].with = main->parameters.arguments.array[index];

          ++substitutionss[j].used;
        }
      } // for
    } // for

    return F_none;
  }
#endif // _di_iki_read_substitutions_identify_

#ifdef __cplusplus
} // extern "C"
#endif
