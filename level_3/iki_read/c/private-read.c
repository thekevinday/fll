#include "iki_read.h"
#include "private-common.h"
#include "private-print.h"
#include "private-read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_process_at_
  f_status_t iki_read_process_at(iki_read_data_t * const data, f_string_range_t *range) {

    if (data->main->parameters.array[iki_read_parameter_line_e].result != f_console_result_additional_e) {
      return F_false;
    }

    f_array_length_t line = 0;

    range->start = 0;
    if (data->line > 0) {
      for (; line < data->line && range->start < data->buffer.used; ++range->start) {
        if (data->buffer.string[range->start] == f_string_eol_s.string[0]) ++line;
      } // for
    }

    if (line == data->line) {
      for (range->stop = range->start; range->stop < data->buffer.used; ++range->stop) {
        if (data->buffer.string[range->stop] == f_string_eol_s.string[0]) break;
      } // for

      return F_true;
    }

    return F_data_not;
  }
#endif // _di_iki_read_process_at_

#ifndef _di_iki_read_process_buffer_
  f_status_t iki_read_process_buffer(iki_read_data_t * const data) {

    f_status_t status = F_none;
    f_iki_data_t iki_data = f_iki_data_t_initialize;

    if (data->main->parameters.array[iki_read_parameter_whole_e].result == f_console_result_found_e) {
      f_string_range_t buffer_range = macro_f_string_range_t_initialize2(data->buffer.used);

      status = iki_read_process_at(data, &buffer_range);

      if (status == F_true) {
        if (buffer_range.start > data->buffer.used) {
          return F_data_not;
        }
      }
      else if (status == F_data_not) {
        return F_data_not;
      }

      if (data->mode == iki_read_mode_content_e) {
        status = iki_read_process_buffer_ranges_whole(data, buffer_range, &iki_data, &iki_data.content);
      }
      else if (data->mode == iki_read_mode_literal_e) {
        status = iki_read_process_buffer_ranges_whole(data, buffer_range, &iki_data, &iki_data.variable);
      }
      else if (data->mode == iki_read_mode_object_e) {
        status = iki_read_process_buffer_ranges_whole(data, buffer_range, &iki_data, &iki_data.vocabulary);
      }
    }
    else if (data->mode == iki_read_mode_total_e) {
      status = iki_read_process_buffer_total(data, &iki_data);
    }
    else {
      f_string_range_t buffer_range = macro_f_string_range_t_initialize2(data->buffer.used);

      status = iki_read_process_at(data, &buffer_range);

      if ((status == F_true && buffer_range.start > data->buffer.used) || status == F_data_not) {
        f_iki_data_delete(&iki_data);

        return F_data_not;
      }

      if (data->mode == iki_read_mode_content_e) {
        status = iki_read_process_buffer_ranges(data, &buffer_range, &iki_data, &iki_data.content);
      }
      else if (data->mode == iki_read_mode_literal_e) {
        status = iki_read_process_buffer_ranges(data, &buffer_range, &iki_data, &iki_data.variable);
      }
      else if (data->mode == iki_read_mode_object_e) {
        status = iki_read_process_buffer_ranges(data, &buffer_range, &iki_data, &iki_data.vocabulary);
      }
    }

    f_iki_data_delete(&iki_data);

    return status;
  }
#endif // _di_iki_read_process_buffer_

#ifndef _di_iki_read_process_buffer_ranges_
  f_status_t iki_read_process_buffer_ranges(iki_read_data_t * const data, f_string_range_t *buffer_range, f_iki_data_t *iki_data, f_string_ranges_t *ranges) {

    f_status_t status = F_none;

    bool unmatched = F_true;

    {
      f_state_t state = macro_f_state_t_initialize(iki_read_common_allocation_large_d, iki_read_common_allocation_small_d, 0, 0, &fll_program_standard_signal_state, 0, (void *) data->main, 0);

      status = fl_iki_read(state, &data->buffer, buffer_range, iki_data);
    }

    if (F_status_is_error(status)) {
      fll_error_print(data->main->error, F_status_set_fine(status), "fl_iki_read", F_true);

      return status;
    }

    for (f_array_length_t i = 0; i < iki_data->delimits.used; ++i) {
      data->buffer.string[iki_data->delimits.array[i]] = f_iki_syntax_placeholder_s.string[0];
    } // for

    const bool content_only = data->mode == iki_read_mode_content_e;

    iki_read_substitution_t replacements[iki_data->variable.used];
    iki_read_substitution_t wraps[iki_data->variable.used];
    iki_read_substitutions_t substitutionss[iki_data->variable.used];

    memset(replacements, 0, sizeof(iki_read_substitution_t) * iki_data->variable.used);
    memset(wraps, 0, sizeof(iki_read_substitution_t) * iki_data->variable.used);
    memset(substitutionss, 0, sizeof(iki_read_substitutions_t) * iki_data->variable.used);

    if (data->mode == iki_read_mode_literal_e || data->mode == iki_read_mode_content_e) {
      status = iki_read_replacements_identify(data, &iki_data->vocabulary, replacements);

      if (F_status_is_error(status)) {
        fll_error_print(data->main->error, F_status_set_fine(status), "iki_read_replacements_identify", F_true);

        return status;
      }

      status = iki_read_wraps_identify(data, &iki_data->vocabulary, wraps);

      if (F_status_is_error(status)) {
        fll_error_print(data->main->error, F_status_set_fine(status), "iki_read_wraps_identify", F_true);

        return status;
      }

      status = iki_read_substitutions_identify(data, &iki_data->vocabulary, substitutionss);

      if (F_status_is_error(status)) {
        fll_error_print(data->main->error, F_status_set_fine(status), "iki_read_substitutions_identify", F_true);

        for (f_array_length_t i = 0; i < iki_data->variable.used; ++i) {
          macro_iki_read_substitutions_t_delete_simple(substitutionss[i]);
        } // for

        return status;
      }
    }

    if (data->main->parameters.array[iki_read_parameter_name_e].result == f_console_result_additional_e) {
      f_string_dynamic_t name = f_string_dynamic_t_initialize;

      f_array_length_t index = 0;
      f_array_length_t i = 0;
      f_array_length_t j = 0;
      f_array_length_t matches = 0;
      buffer_range->start = 0;

      for (; i < data->main->parameters.array[iki_read_parameter_name_e].values.used; ++i) {

        index = data->main->parameters.array[iki_read_parameter_name_e].values.array[i];
        name.used = 0;

        status = f_string_dynamic_append_nulless(data->argv[index], &name);

        if (F_status_is_error(status)) {
          fll_error_print(data->main->error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);

          for (f_array_length_t i = 0; i < iki_data->variable.used; ++i) {
            macro_iki_read_substitutions_t_delete_simple(substitutionss[i]);
          } // for

          f_string_dynamic_resize(0, &name);
          return status;
        }

        buffer_range->stop = name.used - 1;

        flockfile(data->main->output.to.stream);

        for (j = 0; j < iki_data->vocabulary.used; ++j) {

          status = fl_string_dynamic_partial_compare(name, data->buffer, *buffer_range, iki_data->vocabulary.array[j]);

          if (status == F_equal_to) {
            unmatched = F_false;

            if (data->main->parameters.array[iki_read_parameter_at_e].result == f_console_result_additional_e) {
              if (matches++ != data->at) continue;
            }

            if (replacements[j].replace.used || wraps[j].replace.used || wraps[j].with.used || substitutionss[j].used) {
              iki_read_substitutions_print(data, *iki_data, *ranges, replacements[j], wraps[j], substitutionss[j], j, content_only);
            }
            else {
              f_print_dynamic_partial(data->buffer, ranges->array[j], data->main->output.to.stream);
            }

            f_print_dynamic_raw(f_string_eol_s, data->main->output.to.stream);
          }
        } // for

        funlockfile(data->main->output.to.stream);
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
      if (data->main->parameters.array[iki_read_parameter_at_e].result == f_console_result_additional_e) {
        if (data->at < ranges->used) {
          flockfile(data->main->output.to.stream);

          if (replacements[data->at].replace.used || wraps[data->at].replace.used || wraps[data->at].with.used || substitutionss[data->at].used) {
            iki_read_substitutions_print(data, *iki_data, *ranges, replacements[data->at], wraps[data->at], substitutionss[data->at], data->at, content_only);
          }
          else {
            f_print_dynamic_partial(data->buffer, ranges->array[data->at], data->main->output.to.stream);
          }

          f_print_dynamic_raw(f_string_eol_s, data->main->output.to.stream);

          funlockfile(data->main->output.to.stream);

          status = F_none;
        }
        else {
          status = F_data_not;
        }
      }
      else {
        flockfile(data->main->output.to.stream);

        for (f_array_length_t i = 0; i < ranges->used; ++i) {

          if (replacements[i].replace.used || wraps[i].replace.used || wraps[i].with.used || substitutionss[i].used) {
            iki_read_substitutions_print(data, *iki_data, *ranges, replacements[i], wraps[i], substitutionss[i], i, content_only);
          }
          else {
            f_print_dynamic_partial(data->buffer, ranges->array[i], data->main->output.to.stream);
          }

          f_print_dynamic_raw(f_string_eol_s, data->main->output.to.stream);
        } // for

        funlockfile(data->main->output.to.stream);

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
  f_status_t iki_read_process_buffer_ranges_whole(iki_read_data_t * const data, const f_string_range_t buffer_range, f_iki_data_t *iki_data, f_string_ranges_t *ranges) {

    f_status_t status = F_none;
    f_string_range_t range = buffer_range;

    {
      f_state_t state = macro_f_state_t_initialize(iki_read_common_allocation_large_d, iki_read_common_allocation_small_d, 0, 0, &fll_program_standard_signal_state, 0, (void *) data->main, 0);

      status = fl_iki_read(state, &data->buffer, &range, iki_data);
    }

    if (F_status_is_error(status)) {
      fll_error_print(data->main->error, F_status_set_fine(status), "fl_iki_read", F_true);

      return status;
    }

    for (f_array_length_t i = 0; i < iki_data->delimits.used; ++i) {
      data->buffer.string[iki_data->delimits.array[i]] = f_iki_syntax_placeholder_s.string[0];
    } // for

    if (!iki_data->variable.used) {
      fll_print_dynamic_partial(data->buffer, buffer_range, data->main->output.to.stream);

      return F_none;
    }

    const bool content_only = data->mode == iki_read_mode_content_e;

    iki_read_substitution_t replacements[iki_data->variable.used];
    iki_read_substitution_t wraps[iki_data->variable.used];
    iki_read_substitutions_t substitutionss[iki_data->variable.used];

    memset(replacements, 0, sizeof(iki_read_substitution_t) * iki_data->variable.used);
    memset(wraps, 0, sizeof(iki_read_substitution_t) * iki_data->variable.used);
    memset(substitutionss, 0, sizeof(iki_read_substitutions_t) * iki_data->variable.used);

    if (data->mode == iki_read_mode_literal_e || data->mode == iki_read_mode_content_e) {
      status = iki_read_replacements_identify(data, &iki_data->vocabulary, replacements);

      if (F_status_is_error(status)) {
        fll_error_print(data->main->error, F_status_set_fine(status), "iki_read_replacements_identify", F_true);

        return status;
      }

      status = iki_read_wraps_identify(data, &iki_data->vocabulary, wraps);

      if (F_status_is_error(status)) {
        fll_error_print(data->main->error, F_status_set_fine(status), "iki_read_wraps_identify", F_true);

        return status;
      }

      status = iki_read_substitutions_identify(data, &iki_data->vocabulary, substitutionss);

      if (F_status_is_error(status)) {
        fll_error_print(data->main->error, F_status_set_fine(status), "iki_read_substitutions_identify", F_true);

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

    if (data->main->parameters.array[iki_read_parameter_name_e].result == f_console_result_additional_e) {
      f_array_length_t i = 0;
      f_array_length_t j = 0;

      for (f_array_length_t index = 0; i < data->main->parameters.array[iki_read_parameter_name_e].values.used; ++i) {

        index = data->main->parameters.array[iki_read_parameter_name_e].values.array[i];

        for (j = 0, name_missed = F_true; j < names.used; ++j) {

          if (fl_string_dynamic_compare(data->argv[index], names.array[j]) == F_equal_to) {
            name_missed = F_false;

            break;
          }
        } // for

        if (name_missed) {
          macro_f_memory_structure_increment(status, names, 1, F_iki_default_allocation_small_d, macro_f_string_dynamics_t_resize, F_array_too_large);

          if (F_status_is_error(status)) {
            fll_error_print(data->main->error, F_status_set_fine(status), "macro_f_memory_structure_increment", F_true);

            break;
          }

          status = f_string_dynamic_append_nulless(data->argv[index], &names.array[names.used]);

          if (F_status_is_error(status)) {
            fll_error_print(data->main->error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);

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

      flockfile(data->main->output.to.stream);

      while (i <= range.stop && j < stop) {

        if (i < iki_data->variable.array[j].start) {
          range.start = i;
          range.stop = iki_data->variable.array[j].start - 1;

          f_print_dynamic_partial(data->buffer, range, data->main->output.to.stream);

          range.start = iki_data->variable.array[j].stop + 1;
          range.stop = buffer_range.stop;

          i = iki_data->variable.array[j].start;
        }

        if (names.used) {
          name_missed = F_true;

          for (k = 0; k < names.used; ++k) {
            name_range.stop = names.array[k].used - 1;

            status = fl_string_dynamic_partial_compare(data->buffer, names.array[k], iki_data->vocabulary.array[j], name_range);

            if (status == F_equal_to) {
              name_missed = F_false;
              break;
            }
          } // for

          if (name_missed) {
            if (replacements[j].replace.used || wraps[j].replace.used || wraps[j].with.used || substitutionss[j].used) {
              iki_read_substitutions_print(data, *iki_data, iki_data->variable, replacements[j], wraps[j], substitutionss[j], j, F_false);
            }
            else {
              f_print_dynamic_partial(data->buffer, iki_data->variable.array[j], data->main->output.to.stream);
            }
          }
          else {
            if (replacements[j].replace.used || wraps[j].replace.used || wraps[j].with.used || substitutionss[j].used) {
              iki_read_substitutions_print(data, *iki_data, *ranges, replacements[j], wraps[j], substitutionss[j], j, content_only);
            }
            else {
              f_print_dynamic_partial(data->buffer, ranges->array[j], data->main->output.to.stream);
            }
          }
        }
        else {
          if (replacements[j].replace.used || wraps[j].replace.used || wraps[j].with.used || substitutionss[j].used) {
            iki_read_substitutions_print(data, *iki_data, *ranges, replacements[j], wraps[j], substitutionss[j], j, content_only);
          }
          else {
            f_print_dynamic_partial(data->buffer, ranges->array[j], data->main->output.to.stream);
          }
        }

        i = iki_data->variable.array[j].stop + 1;
        ++j;
      } // while

      if (i <= buffer_range.stop) {
        range.start = i;
        f_print_dynamic_partial(data->buffer, range, data->main->output.to.stream);
      }

      funlockfile(data->main->output.to.stream);
    }

    for (f_array_length_t i = 0; i < iki_data->variable.used; ++i) {
      macro_iki_read_substitutions_t_delete_simple(substitutionss[i]);
    } // for

    f_string_dynamics_resize(0, &names);

    return F_none;
  }
#endif // _di_iki_read_process_buffer_ranges_whole_

#ifndef _di_iki_read_process_buffer_total_
  f_status_t iki_read_process_buffer_total(iki_read_data_t * const data, f_iki_data_t *iki_data) {

    f_status_t status = F_none;
    f_string_range_t range = macro_f_string_range_t_initialize2(data->buffer.used);

    status = iki_read_process_at(data, &range);

    if (status == F_true) {
      if (range.start > data->buffer.used) {
        fll_print_format("%r%r", data->main->output.to.stream, f_string_ascii_0_s, f_string_eol_s);

        return F_none;
      }
    }
    else if (status == F_data_not) {
      fll_print_format("%r%r", data->main->output.to.stream, f_string_ascii_0_s, f_string_eol_s);

      return F_none;
    }

    {
      f_state_t state = macro_f_state_t_initialize(iki_read_common_allocation_large_d, iki_read_common_allocation_small_d, 0, 0, &fll_program_standard_signal_state, 0, (void *) data->main, 0);

      status = fl_iki_read(state, &data->buffer, &range, iki_data);
    }

    if (F_status_is_error(status)) {
      fll_error_print(data->main->error, F_status_set_fine(status), "fl_iki_read", F_true);

      return status;
    }

    for (f_array_length_t i = 0; i < iki_data->delimits.used; ++i) {
      data->buffer.string[iki_data->delimits.array[i]] = f_iki_syntax_placeholder_s.string[0];
    } // for

    f_array_length_t total = 0;

    if (data->main->parameters.array[iki_read_parameter_name_e].result == f_console_result_additional_e) {
      f_string_dynamic_t name = f_string_dynamic_t_initialize;

      f_array_length_t index = 0;
      f_array_length_t i = 0;
      f_array_length_t j = 0;

      range.start = 0;

      for (; i < data->main->parameters.array[iki_read_parameter_name_e].values.used; ++i) {

        if (!((++data->main->signal_check) % iki_read_signal_check_d)) {
          if (fll_program_standard_signal_received(data->main)) {
            iki_read_print_signal_received(data);

            f_string_dynamic_resize(0, &name);

            return F_status_set_error(F_interrupt);
          }

          data->main->signal_check = 0;
        }

        index = data->main->parameters.array[iki_read_parameter_name_e].values.array[i];
        name.used = 0;

        status = f_string_dynamic_append_nulless(data->argv[index], &name);

        if (F_status_is_error(status)) {
          fll_error_print(data->main->error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);

          f_string_dynamic_resize(0, &name);

          return status;
        }

        range.stop = name.used - 1;

        for (j = 0; j < iki_data->vocabulary.used; ++j) {

          status = fl_string_dynamic_partial_compare(name, data->buffer, range, iki_data->vocabulary.array[j]);

          if (status == F_equal_to) ++total;
        } // for
      } // for

      f_string_dynamic_resize(0, &name);
    }
    else {
      total = iki_data->variable.used;
    }

    // if that at position is within the actual total, then the total at the given position is 1, otherwise is 0.
    if (data->main->parameters.array[iki_read_parameter_at_e].result == f_console_result_additional_e) {
      if (data->at < total) {
        total = 1;
      }
      else {
        total = 0;
      }
    }

    fll_print_format("%ul%r", data->main->output.to.stream, total, f_string_eol_s);

    return F_none;
  }
#endif // _di_iki_read_process_buffer_total_

#ifndef _di_iki_read_replacements_identify_
  f_status_t iki_read_replacements_identify(iki_read_data_t * const data, f_iki_vocabulary_t *vocabulary, iki_read_substitution_t *replacements) {

    if (data->main->parameters.array[iki_read_parameter_replace_e].result != f_console_result_additional_e) {
      return F_none;
    }

    f_status_t status = F_none;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_array_length_t index = 0;
    f_array_length_t index2 = 0;

    f_console_parameter_t *parameter = &data->main->parameters.array[iki_read_parameter_replace_e];

    for (; i < parameter->values.used; i += 2) {

      index = parameter->values.array[i];

      for (j = 0; j < vocabulary->used; ++j) {

        if (fl_string_dynamic_partial_compare_string(data->argv[index].string, data->buffer, data->argv[index].used, vocabulary->array[j]) == F_equal_to) {
          replacements[j].replace.used = F_true;

          index2 = parameter->values.array[i + 1];
          replacements[j].with = data->argv[index2];
        }
      } // for
    } // for

    return F_none;
  }
#endif // _di_iki_read_replacements_identify_

#ifndef _di_iki_read_substitutions_identify_
  f_status_t iki_read_substitutions_identify(iki_read_data_t * const data, f_iki_vocabulary_t *vocabulary, iki_read_substitutions_t *substitutionss) {

    if (data->main->parameters.array[iki_read_parameter_substitute_e].result != f_console_result_additional_e) {
      return F_none;
    }

    f_status_t status = F_none;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_array_length_t index = 0;
    f_array_length_t index2 = 0;

    f_console_parameter_t *parameter = &data->main->parameters.array[iki_read_parameter_substitute_e];

    for (; i < parameter->values.used; i += 3) {

      index = parameter->values.array[i];

      for (j = 0; j < vocabulary->used; ++j) {

        if (fl_string_dynamic_partial_compare_string(data->argv[index].string, data->buffer, data->argv[index].used, vocabulary->array[j]) == F_equal_to) {
          macro_f_memory_structure_increment(status, substitutionss[j], 1, F_iki_default_allocation_small_d, macro_iki_read_substitutions_t_resize, F_array_too_large);
          if (F_status_is_error(status)) return status;

          index2 = parameter->values.array[i + 1];
          substitutionss[j].array[substitutionss[j].used].replace = data->argv[index2];

          index2 = parameter->values.array[i + 2];
          substitutionss[j].array[substitutionss[j].used].with = data->argv[index2];

          ++substitutionss[j].used;
        }
      } // for
    } // for

    return F_none;
  }
#endif // _di_iki_read_substitutions_identify_

#ifndef _di_iki_read_wraps_identify_
  f_status_t iki_read_wraps_identify(iki_read_data_t * const data, f_iki_vocabulary_t *vocabulary, iki_read_substitution_t *wraps) {

    if (data->main->parameters.array[iki_read_parameter_wrap_e].result != f_console_result_additional_e) {
      return F_none;
    }

    f_status_t status = F_none;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_array_length_t index = 0;
    f_array_length_t index2 = 0;

    f_console_parameter_t *parameter = &data->main->parameters.array[iki_read_parameter_wrap_e];

    for (; i < parameter->values.used; i += 3) {

      index = parameter->values.array[i];

      for (j = 0; j < vocabulary->used; ++j) {

        if (fl_string_dynamic_partial_compare_string(data->argv[index].string, data->buffer, data->argv[index].used, vocabulary->array[j]) == F_equal_to) {
          index2 = parameter->values.array[i + 1];
          wraps[j].replace = data->argv[index2];

          index2 = parameter->values.array[i + 2];
          wraps[j].with = data->argv[index2];
        }
      } // for
    } // for

    return F_none;
  }
#endif // _di_iki_read_wraps_identify_

#ifdef __cplusplus
} // extern "C"
#endif
