#include "iki_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_process_line_
  void iki_read_process_line(iki_read_main_t * const main, f_string_range_t *range) {

    if (!(main->setting.flag & iki_read_main_flag_line_e)) {
      main->setting.state.status = F_false;

      return;
    }

    f_array_length_t line = 0;

    range->start = 0;
    if (main->setting.line) {
      for (; line < main->setting.line && range->start < main->setting.buffer.used; ++range->start) {
        if (main->setting.buffer.string[range->start] == f_string_eol_s.string[0]) ++line;
      } // for
    }

    if (line == main->setting.line) {

      // Find where the found line ends and set that as the range stop.
      for (range->stop = range->start; range->stop < main->setting.buffer.used; ++range->stop) {
        if (main->setting.buffer.string[range->stop] == f_string_eol_s.string[0]) break;
      } // for

      main->setting.state.status = F_true;
    }
    else {
      main->setting.state.status = F_data_not;
    }
  }
#endif // _di_iki_read_process_line_

#ifndef _di_iki_read_process_buffer_
  void iki_read_process_buffer(iki_read_main_t * const main) {

    if (main->setting.flag & iki_read_main_flag_total_e) {
      iki_read_process_buffer_total(main);

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = F_none;
      }

      return;
    }

    f_string_range_t buffer_range = macro_f_string_range_t_initialize2(main->setting.buffer.used);

    iki_read_process_line(main, &buffer_range);

    if (main->setting.state.status == F_true) {
      if (buffer_range.start > main->setting.buffer.used) {
        main->setting.state.status = F_data_not;

        return;
      }
    }
    else if (main->setting.state.status == F_data_not) {
      main->setting.state.status = F_data_not;

      return;
    }

    if (main->setting.flag & iki_read_main_flag_whole_e) {
      iki_read_process_buffer_ranges_whole(main, buffer_range);
    }
    else {
      iki_read_process_buffer_ranges(main, &buffer_range);
    }

    if (F_status_is_error_not(main->setting.state.status)) {
      main->setting.state.status = F_none;
    }
  }
#endif // _di_iki_read_process_buffer_

#ifndef _di_iki_read_process_buffer_ranges_
  void iki_read_process_buffer_ranges(iki_read_main_t * const main, f_string_range_t *buffer_range) {

    fl_iki_read(&main->setting.buffer, buffer_range, &main->setting.data, &main->setting.state);

    if (F_status_is_error(main->setting.state.status)) {
      iki_read_print_error(&main->program.error, macro_iki_read_f(fl_iki_read));

      return;
    }

    f_array_length_t i = 0;
    f_array_length_t replaces[main->setting.data.vocabulary.used];
    f_array_length_t wraps[main->setting.data.vocabulary.used];

    memset(replaces, 0, sizeof(f_array_length_t) * main->setting.data.vocabulary.used);
    memset(wraps, 0, sizeof(f_array_length_t) * main->setting.data.vocabulary.used);

    main->setting.map_replaces = replaces;
    main->setting.map_wraps = wraps;

    for (; i < main->setting.data.delimits.used; ++i) {
      main->setting.buffer.string[main->setting.data.delimits.array[i]] = f_iki_syntax_placeholder_s.string[0];
    } // for

    iki_read_identify_alteration(main);

    if (main->setting.flag & iki_read_main_flag_name_e) {
      f_array_length_t j = 0;
      f_array_length_t matches = 0;
      bool unmatched = F_true;

      f_file_stream_lock(main->program.output.to);

      for (i = 0; i < main->setting.data.vocabulary.used; ++i) {

        for (j = 0; j < main->setting.names.used; ++j) {

          if (fl_string_dynamic_partial_compare_string(main->setting.names.array[j].string, main->setting.buffer, main->setting.names.array[j].used, main->setting.data.vocabulary.array[i]) == F_equal_to) {
            unmatched = F_false;

            if (main->setting.flag & iki_read_main_flag_at_e) {
              if (matches < main->setting.at) {
                matches++;

                continue;
              }

              if (matches++ > main->setting.at) break;
            }

            iki_read_print_data(&main->program.output, i);

            f_print_dynamic_raw(f_string_eol_s, main->program.output.to);
          }
        } // for
      } // for

      f_file_stream_unlock(main->program.output.to);

      if (unmatched) {
        main->setting.state.status = F_data_not;
      }
      else {
        main->setting.state.status = F_none;
      }
    }
    else {
      if (main->setting.data.variable.used) {
        if (main->setting.flag & iki_read_main_flag_at_e) {
          if (main->setting.at < main->setting.data.variable.used) {
            f_file_stream_lock(main->program.output.to);

            iki_read_print_data(&main->program.output, main->setting.at);

            f_print_dynamic_raw(f_string_eol_s, main->program.output.to);

            f_file_stream_unlock(main->program.output.to);

            main->setting.state.status = F_none;
          }
          else {
            main->setting.state.status = F_data_not;
          }
        }
        else {
          f_file_stream_lock(main->program.output.to);

          for (i = 0; i < main->setting.data.variable.used; ++i) {

            iki_read_print_data(&main->program.output, i);

            f_print_dynamic_raw(f_string_eol_s, main->program.output.to);
          } // for

          f_file_stream_unlock(main->program.output.to);

          main->setting.state.status = F_none;
        }
      }
      else {
        main->setting.state.status = F_data_not;
      }
    }
  }
#endif // _di_iki_read_process_buffer_ranges_

#ifndef _di_iki_read_process_buffer_ranges_whole_
  void iki_read_process_buffer_ranges_whole(iki_read_main_t * const main, const f_string_range_t buffer_range) {

    f_string_range_t range = buffer_range;

    fl_iki_read(&main->setting.buffer, &range, &main->setting.data, &main->setting.state);

    if (F_status_is_error(main->setting.state.status)) {
      iki_read_print_error(&main->program.error, macro_iki_read_f(fl_iki_read));

      return;
    }

    f_array_length_t i = 0;

    for (; i < main->setting.data.delimits.used; ++i) {
      main->setting.buffer.string[main->setting.data.delimits.array[i]] = f_iki_syntax_placeholder_s.string[0];
    } // for

    if (!main->setting.data.variable.used) {
      fll_print_dynamic_partial(main->setting.buffer, buffer_range, main->program.output.to);

      main->setting.state.status = F_none;

      return;
    }

    f_array_length_t replaces[main->setting.data.vocabulary.used];
    f_array_length_t wraps[main->setting.data.vocabulary.used];

    memset(replaces, 0, sizeof(f_array_length_t) * main->setting.data.vocabulary.used);
    memset(wraps, 0, sizeof(f_array_length_t) * main->setting.data.vocabulary.used);

    main->setting.map_replaces = replaces;
    main->setting.map_wraps = wraps;

    iki_read_identify_alteration(main);

    {
      f_array_length_t j = 0;
      f_array_length_t k = 0;
      f_array_length_t stop = main->setting.data.variable.used;

      i = buffer_range.start;
      range = buffer_range;

      f_file_stream_lock(main->program.output.to);

      while (i <= range.stop && j < stop) {

        if (i < main->setting.data.variable.array[j].start) {
          range.start = i;
          range.stop = main->setting.data.variable.array[j].start - 1;

          f_print_dynamic_partial(main->setting.buffer, range, main->program.output.to);

          range.start = main->setting.data.variable.array[j].stop + 1;
          range.stop = buffer_range.stop;

          i = main->setting.data.variable.array[j].start;
        }

        if (main->setting.names.used) {
          for (k = 0; k < main->setting.names.used; ++k) {
            if (fl_string_dynamic_partial_compare_string(main->setting.names.array[k].string, main->setting.buffer, main->setting.names.array[k].used, main->setting.data.vocabulary.array[j]) == F_equal_to) break;
          } // for

          if (k < main->setting.names.used) {
            iki_read_print_data(&main->program.output, j);
          }
        }
        else {
          iki_read_print_data(&main->program.output, j);
        }

        i = main->setting.data.variable.array[j].stop + 1;
        ++j;
      } // while

      if (i <= buffer_range.stop) {
        range.start = i;
        f_print_dynamic_partial(main->setting.buffer, range, main->program.output.to);
      }

      f_file_stream_unlock(main->program.output.to);
    }

    main->setting.state.status = F_none;
  }
#endif // _di_iki_read_process_buffer_ranges_whole_

#ifndef _di_iki_read_process_buffer_total_
  void iki_read_process_buffer_total(iki_read_main_t * const main) {

    f_string_range_t range = macro_f_string_range_t_initialize2(main->setting.buffer.used);

    iki_read_process_line(main, &range);

    if (main->setting.state.status == F_true) {
      if (range.start > main->setting.buffer.used) {
        fll_print_format("%r%r", main->program.output.to, f_string_ascii_0_s, f_string_eol_s);

        main->setting.state.status = F_none;

        return;
      }
    }
    else if (main->setting.state.status == F_data_not) {
      fll_print_format("%r%r", main->program.output.to, f_string_ascii_0_s, f_string_eol_s);

      main->setting.state.status = F_none;

      return;
    }

    fl_iki_read(&main->setting.buffer, &range, &main->setting.data, &main->setting.state);

    if (F_status_is_error(main->setting.state.status)) {
      iki_read_print_error(&main->program.error, macro_iki_read_f(fl_iki_read));

      return;
    }

    f_array_length_t i = 0;
    f_array_length_t total = 0;

    for (; i < main->setting.data.delimits.used; ++i) {
      main->setting.buffer.string[main->setting.data.delimits.array[i]] = f_iki_syntax_placeholder_s.string[0];
    } // for

    if (main->program.parameters.array[iki_read_parameter_name_e].result & f_console_result_value_e) {
      f_string_dynamic_t name = f_string_dynamic_t_initialize;

      f_array_length_t index = 0;
      f_array_length_t j = 0;

      range.start = 0;

      for (i = 0; i < main->program.parameters.array[iki_read_parameter_name_e].values.used; ++i) {

        if (!((++main->program.signal_check) % iki_read_signal_check_d)) {
          if (fll_program_standard_signal_received(&main->program)) {
            fll_program_print_signal_received(&main->program.warning, main->program.signal_received);

            f_string_dynamic_resize(0, &name);

            main->setting.state.status = F_status_set_error(F_interrupt);

            return;
          }

          main->program.signal_check = 0;
        }

        index = main->program.parameters.array[iki_read_parameter_name_e].values.array[i];
        name.used = 0;

        main->setting.state.status = f_string_dynamic_append_nulless(main->program.parameters.arguments.array[index], &name);

        if (F_status_is_error(main->setting.state.status)) {
          iki_read_print_error(&main->program.error, macro_iki_read_f(f_string_dynamic_append_nulless));

          f_string_dynamic_resize(0, &name);

          return;
        }

        range.stop = name.used - 1;

        for (j = 0; j < main->setting.data.vocabulary.used; ++j) {

          main->setting.state.status = fl_string_dynamic_partial_compare(name, main->setting.buffer, range, main->setting.data.vocabulary.array[j]);

          if (main->setting.state.status == F_equal_to) ++total;
        } // for
      } // for

      f_string_dynamic_resize(0, &name);
    }
    else {
      total = main->setting.data.variable.used;
    }

    // If the "at" position is within the actual total, then the total at the given position is 1, otherwise is 0.
    if (main->program.parameters.array[iki_read_parameter_at_e].result & f_console_result_value_e) {
      if (main->setting.at < total) {
        total = 1;
      }
      else {
        total = 0;
      }
    }

    fll_print_format("%ul%r", main->program.output.to, total, f_string_eol_s);

    main->setting.state.status = F_none;
  }
#endif // _di_iki_read_process_buffer_total_

#ifdef __cplusplus
} // extern "C"
#endif
