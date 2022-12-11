#include "iki_read.h"
#include "private-common.h"
#include "private-print.h"
#include "private-read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_identify_alteration_
  void iki_read_identify_alteration(iki_read_setting_t * const setting) {

    if (!(setting->replace.used || setting->wrap.used)) return;

    f_array_length_t i = 0;

    if (setting->flag & (iki_read_main_flag_content_e | iki_read_main_flag_literal_e)) {
      f_array_length_t j = 0;

      for (i = 0; i < setting->data.vocabulary.used; ++i) {

        if (setting->replace.used) {
          setting->map_replaces[i] = setting->replace.used;

          j = setting->replace.used - 1;

          do {
            if (fl_string_dynamic_partial_compare_string(setting->replace.array[j].name.string, setting->buffer, setting->replace.array[j].name.used, setting->data.vocabulary.array[i]) == F_equal_to) {
              setting->map_replaces[i] = j;

              break;
            }

          } while (j--);
        }

        if (setting->wrap.used) {
          setting->map_wraps[i] = setting->wrap.used;

          j = setting->wrap.used - 1;

          do {
            if (fl_string_dynamic_partial_compare_string(setting->wrap.array[j].a.string, setting->buffer, setting->wrap.array[j].a.used, setting->data.vocabulary.array[i]) == F_equal_to) {
              setting->map_wraps[i] = j;

              break;
            }

          } while (j--);
        }
      } // for
    }
    else {
      for (i = 0; i < setting->data.vocabulary.used; ++i) {

        if (setting->replace.used) {
          setting->map_replaces[i] = setting->replace.used;
        }

        if (setting->wrap.used) {
          setting->map_wraps[i] = setting->wrap.used;
        }
      } // for
    }
  }
#endif // _di_iki_read_identify_alteration_

#ifndef _di_iki_read_identify_substitution_
  f_array_length_t iki_read_identify_substitution(iki_read_setting_t * const setting, const f_string_range_t name, const f_string_range_t value, f_string_triples_t *triple) {

    f_array_length_t i = triple->used - 1;

    do {
      if (fl_string_dynamic_partial_compare_string(triple->array[i].a.string, setting->buffer, triple->array[i].a.used, name) == F_equal_to) {
        if (fl_string_dynamic_partial_compare_string(triple->array[i].b.string, setting->buffer, triple->array[i].b.used, value) == F_equal_to) {
          return i;
        }
      }

    } while (i--);

    return triple->used;
  }
#endif // _di_iki_read_identify_substitution_

#ifndef _di_iki_read_process_line_
  void iki_read_process_line(fll_program_data_t * const main, iki_read_setting_t * const setting, f_string_range_t *range) {

    if (!(setting->flag & iki_read_main_flag_line_e)) {
      setting->status = F_false;

      return;
    }

    f_array_length_t line = 0;

    range->start = 0;
    if (setting->line) {
      for (; line < setting->line && range->start < setting->buffer.used; ++range->start) {
        if (setting->buffer.string[range->start] == f_string_eol_s.string[0]) ++line;
      } // for
    }

    if (line == setting->line) {

      // Find where the found line ends and set that as the range stop.
      for (range->stop = range->start; range->stop < setting->buffer.used; ++range->stop) {
        if (setting->buffer.string[range->stop] == f_string_eol_s.string[0]) break;
      } // for

      setting->status = F_true;
    }
    else {
      setting->status = F_data_not;
    }
  }
#endif // _di_iki_read_process_line_

#ifndef _di_iki_read_process_buffer_
  void iki_read_process_buffer(fll_program_data_t * const main, iki_read_setting_t * const setting) {

    if (setting->flag & iki_read_main_flag_total_e) {
      iki_read_process_buffer_total(main, setting);

      if (F_status_is_error_not(setting->status)) {
        setting->status = F_none;
      }

      return;
    }

    f_string_range_t buffer_range = macro_f_string_range_t_initialize2(setting->buffer.used);

    iki_read_process_line(main, setting, &buffer_range);

    if (setting->status == F_true) {
      if (buffer_range.start > setting->buffer.used) {
        setting->status = F_data_not;

        return;
      }
    }
    else if (setting->status == F_data_not) {
      setting->status = F_data_not;

      return;
    }

    if (setting->flag & iki_read_main_flag_whole_e) {
      iki_read_process_buffer_ranges_whole(main, setting, buffer_range);
    }
    else {
      iki_read_process_buffer_ranges(main, setting, &buffer_range);
    }

    if (F_status_is_error_not(setting->status)) {
      setting->status = F_none;
    }
  }
#endif // _di_iki_read_process_buffer_

#ifndef _di_iki_read_process_buffer_ranges_
  void iki_read_process_buffer_ranges(fll_program_data_t * const main, iki_read_setting_t * const setting, f_string_range_t *buffer_range) {

    {
      const f_state_t state = macro_f_state_t_initialize(iki_read_common_allocation_large_d, iki_read_common_allocation_small_d, 0, 0, &fll_program_standard_signal_state, 0, (void *) main, 0);

      setting->status = fl_iki_read(state, &setting->buffer, buffer_range, &setting->data);
    }

    if (F_status_is_error(setting->status)) {
      iki_read_print_error(setting, main->error, macro_iki_read_f(fl_iki_read));

      return;
    }

    f_array_length_t i = 0;
    f_array_length_t replaces[setting->data.vocabulary.used];
    f_array_length_t wraps[setting->data.vocabulary.used];

    memset(replaces, 0, sizeof(f_array_length_t) * setting->data.vocabulary.used);
    memset(wraps, 0, sizeof(f_array_length_t) * setting->data.vocabulary.used);

    setting->map_replaces = replaces;
    setting->map_wraps = wraps;

    for (; i < setting->data.delimits.used; ++i) {
      setting->buffer.string[setting->data.delimits.array[i]] = f_iki_syntax_placeholder_s.string[0];
    } // for

    iki_read_identify_alteration(setting);

    if (setting->flag & iki_read_main_flag_name_e) {
      f_array_length_t j = 0;
      f_array_length_t matches = 0;
      bool unmatched = F_true;

      f_file_stream_lock(main->output.to);

      for (i = 0; i < setting->data.vocabulary.used; ++i) {

        for (j = 0; j < setting->names.used; ++j) {

          if (fl_string_dynamic_partial_compare_string(setting->names.array[j].string, setting->buffer, setting->names.array[j].used, setting->data.vocabulary.array[i]) == F_equal_to) {
            unmatched = F_false;

            if (setting->flag & iki_read_main_flag_at_e) {
              if (matches < setting->at) {
                matches++;

                continue;
              }

              if (matches++ > setting->at) break;
            }

            iki_read_print(main, setting, i);

            f_print_dynamic_raw(f_string_eol_s, main->output.to);
          }
        } // for
      } // for

      f_file_stream_unlock(main->output.to);

      if (unmatched) {
        setting->status = F_data_not;
      }
      else {
        setting->status = F_none;
      }
    }
    else {
      if (setting->data.variable.used) {
        if (setting->flag & iki_read_main_flag_at_e) {
          if (setting->at < setting->data.variable.used) {
            f_file_stream_lock(main->output.to);

            iki_read_print(main, setting, setting->at);

            f_print_dynamic_raw(f_string_eol_s, main->output.to);

            f_file_stream_unlock(main->output.to);

            setting->status = F_none;
          }
          else {
            setting->status = F_data_not;
          }
        }
        else {
          f_file_stream_lock(main->output.to);

          for (i = 0; i < setting->data.variable.used; ++i) {

            iki_read_print(main, setting, i);

            f_print_dynamic_raw(f_string_eol_s, main->output.to);
          } // for

          f_file_stream_unlock(main->output.to);

          setting->status = F_none;
        }
      }
      else {
        setting->status = F_data_not;
      }
    }
  }
#endif // _di_iki_read_process_buffer_ranges_

#ifndef _di_iki_read_process_buffer_ranges_whole_
  void iki_read_process_buffer_ranges_whole(fll_program_data_t * const main, iki_read_setting_t * const setting, const f_string_range_t buffer_range) {

    f_string_range_t range = buffer_range;

    {
      const f_state_t state = macro_f_state_t_initialize(iki_read_common_allocation_large_d, iki_read_common_allocation_small_d, 0, 0, &fll_program_standard_signal_state, 0, (void *) main, 0);

      setting->status = fl_iki_read(state, &setting->buffer, &range, &setting->data);
    }

    if (F_status_is_error(setting->status)) {
      iki_read_print_error(setting, main->error, macro_iki_read_f(fl_iki_read));

      return;
    }

    f_array_length_t i = 0;

    for (; i < setting->data.delimits.used; ++i) {
      setting->buffer.string[setting->data.delimits.array[i]] = f_iki_syntax_placeholder_s.string[0];
    } // for

    if (!setting->data.variable.used) {
      fll_print_dynamic_partial(setting->buffer, buffer_range, main->output.to);

      setting->status = F_none;

      return;
    }

    f_array_length_t replaces[setting->data.vocabulary.used];
    f_array_length_t wraps[setting->data.vocabulary.used];

    memset(replaces, 0, sizeof(f_array_length_t) * setting->data.vocabulary.used);
    memset(wraps, 0, sizeof(f_array_length_t) * setting->data.vocabulary.used);

    setting->map_replaces = replaces;
    setting->map_wraps = wraps;

    iki_read_identify_alteration(setting);

    {
      f_array_length_t j = 0;
      f_array_length_t k = 0;
      f_array_length_t stop = setting->data.variable.used;

      i = buffer_range.start;
      range = buffer_range;

      f_file_stream_lock(main->output.to);

      while (i <= range.stop && j < stop) {

        if (i < setting->data.variable.array[j].start) {
          range.start = i;
          range.stop = setting->data.variable.array[j].start - 1;

          f_print_dynamic_partial(setting->buffer, range, main->output.to);

          range.start = setting->data.variable.array[j].stop + 1;
          range.stop = buffer_range.stop;

          i = setting->data.variable.array[j].start;
        }

        if (setting->names.used) {
          for (k = 0; k < setting->names.used; ++k) {
            if (fl_string_dynamic_partial_compare_string(setting->names.array[k].string, setting->buffer, setting->names.array[k].used, setting->data.vocabulary.array[j]) == F_equal_to) break;
          } // for

          if (k < setting->names.used) {
            iki_read_print(main, setting, j);
          }
        }
        else {
          iki_read_print(main, setting, j);
        }

        i = setting->data.variable.array[j].stop + 1;
        ++j;
      } // while

      if (i <= buffer_range.stop) {
        range.start = i;
        f_print_dynamic_partial(setting->buffer, range, main->output.to);
      }

      f_file_stream_unlock(main->output.to);
    }

    setting->status = F_none;
  }
#endif // _di_iki_read_process_buffer_ranges_whole_

#ifndef _di_iki_read_process_buffer_total_
  void iki_read_process_buffer_total(fll_program_data_t * const main, iki_read_setting_t * const setting) {

    f_string_range_t range = macro_f_string_range_t_initialize2(setting->buffer.used);

    iki_read_process_line(main, setting, &range);

    if (setting->status == F_true) {
      if (range.start > setting->buffer.used) {
        fll_print_format("%r%r", main->output.to, f_string_ascii_0_s, f_string_eol_s);

        setting->status = F_none;

        return;
      }
    }
    else if (setting->status == F_data_not) {
      fll_print_format("%r%r", main->output.to, f_string_ascii_0_s, f_string_eol_s);

      setting->status = F_none;

      return;
    }

    {
      f_state_t state = macro_f_state_t_initialize(iki_read_common_allocation_large_d, iki_read_common_allocation_small_d, 0, 0, &fll_program_standard_signal_state, 0, (void *) main, 0);

      setting->status = fl_iki_read(state, &setting->buffer, &range, &setting->data);
    }

    if (F_status_is_error(setting->status)) {
      iki_read_print_error(setting, main->error, macro_iki_read_f(fl_iki_read));

      return;
    }

    f_array_length_t i = 0;
    f_array_length_t total = 0;

    for (; i < setting->data.delimits.used; ++i) {
      setting->buffer.string[setting->data.delimits.array[i]] = f_iki_syntax_placeholder_s.string[0];
    } // for

    if (main->parameters.array[iki_read_parameter_name_e].result & f_console_result_value_e) {
      f_string_dynamic_t name = f_string_dynamic_t_initialize;

      f_array_length_t index = 0;
      f_array_length_t j = 0;

      range.start = 0;

      for (i = 0; i < main->parameters.array[iki_read_parameter_name_e].values.used; ++i) {

        if (!((++main->signal_check) % iki_read_signal_check_d)) {
          if (fll_program_standard_signal_received(main)) {
            fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

            f_string_dynamic_resize(0, &name);

            setting->status = F_status_set_error(F_interrupt);

            return;
          }

          main->signal_check = 0;
        }

        index = main->parameters.array[iki_read_parameter_name_e].values.array[i];
        name.used = 0;

        setting->status = f_string_dynamic_append_nulless(main->parameters.arguments.array[index], &name);

        if (F_status_is_error(setting->status)) {
          iki_read_print_error(setting, main->error, macro_iki_read_f(f_string_dynamic_append_nulless));

          f_string_dynamic_resize(0, &name);

          return;
        }

        range.stop = name.used - 1;

        for (j = 0; j < setting->data.vocabulary.used; ++j) {

          setting->status = fl_string_dynamic_partial_compare(name, setting->buffer, range, setting->data.vocabulary.array[j]);

          if (setting->status == F_equal_to) ++total;
        } // for
      } // for

      f_string_dynamic_resize(0, &name);
    }
    else {
      total = setting->data.variable.used;
    }

    // If the "at" position is within the actual total, then the total at the given position is 1, otherwise is 0.
    if (main->parameters.array[iki_read_parameter_at_e].result & f_console_result_value_e) {
      if (setting->at < total) {
        total = 1;
      }
      else {
        total = 0;
      }
    }

    fll_print_format("%ul%r", main->output.to, total, f_string_eol_s);

    setting->status = F_none;
  }
#endif // _di_iki_read_process_buffer_total_

#ifdef __cplusplus
} // extern "C"
#endif
