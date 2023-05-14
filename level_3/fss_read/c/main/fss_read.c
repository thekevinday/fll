#include "fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_main_
  void fss_read_main(void * const void_main) {

    if (!void_main) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & fss_read_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }

    main->setting.state.status = F_none;

    if (main->setting.flag & (fss_read_main_flag_help_e | fss_read_main_flag_version_e | fss_read_main_flag_copyright_e)) {
      if (main->setting.flag & fss_read_main_flag_help_e) {
        if (main->setting.process_help) {
          main->setting.process_help(void_main);
        }
        else {
          fss_read_print_message_help(&main->program.message);
        }
      }
      else if (main->setting.flag & fss_read_main_flag_version_e) {
        fll_program_print_version(&main->program.message, fss_read_program_version_s);
      }
      else if (main->setting.flag & fss_read_main_flag_copyright_e) {
        fll_program_print_copyright(&main->program.message);
      }

      if ((main->setting.flag & fss_read_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    main->setting.escaped.used = 0;

    if (main->program.pipe & fll_program_data_pipe_input_e) {
      if (main->setting.process_pipe) {
        main->setting.process_pipe(void_main);
      }
    }

    if (F_status_is_error_not(main->setting.state.status)) {
      if (main->setting.flag & (fss_read_main_flag_object_e | fss_read_main_flag_content_e | fss_read_main_flag_object_open_e | fss_read_main_flag_content_next_e | fss_read_main_flag_content_end_e)) {
        if (main->setting.process_normal) {
          main->setting.process_normal(void_main);
        }
      }
    }

    if ((main->setting.flag & fss_read_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }
  }
#endif // _di_fss_read_main_

#ifndef _di_fss_read_process_at_line_
  f_status_t fss_read_process_at_line(fss_read_main_t * const main, const f_array_length_t at, const f_array_lengths_t delimits_object, const f_array_lengths_t delimits_content, f_array_length_t * const line) {

    if (!main || !line) return;

    if (main->setting.flag & fss_read_main_flag_object_e) {
      if (*line == main->setting.line) {
        f_file_stream_lock(main->program.output.to);

        if (main->setting.flag & fss_read_main_flag_total_e) {
          fss_read_print_number(&main->program.output, 1);
        }
        else {
          fss_read_print_object_at(&main->program.output, at, delimits_object);
        }

        f_file_stream_unlock(main->program.output.to);

        main->setting.state.status = F_success;

        return;
      }

      ++(*line);
    }

    // There is only a single Content column for this standard.
    if (main->setting.flag & fss_read_main_flag_content_e) {
      if (!main->setting.contents.array[at].used) {
        main->setting.state.status = F_none;

        return;
      }

      f_string_range_t range = main->setting.contents.array[at].array[0];

      // This content has no data, do not even check "include empty" because it cannot be counted as a line.
      if (range.start > range.stop) {
        main->setting.state.status = F_none;

        return;
      }

      for (f_array_length_t i = range.start; i <= range.stop; ++i) {

        if (fss_read_signal_check(main)) return;

        if (main->setting.buffer.string[i] == f_string_eol_s.string[0]) {
          if (*line == main->setting.line) {
            range.stop = i;

            f_file_stream_lock(main->program.output.to);

            if (main->setting.flag & fss_read_main_flag_total_e) {
              fss_read_print_number(&main->program.output, 1);
            }
            else {
              fss_read_print_content(&main->program.output, range, delimits_content);
            }

            f_file_stream_unlock(main->program.output.to);

            main->setting.state.status = F_success;

            return;
          }

          range.start = i + 1;

          if (i <= range.stop) {
            ++(*line);
          }
        }
      } // for

      // If Content does not end with a newline, it still must be treated as the last line.
      if (main->setting.buffer.string[range.stop] != f_string_eol_s.string[0]) {
        ++(*line);

        if (*line == main->setting.line) {
          f_file_stream_lock(main->program.output.to);

          if (main->setting.flag & fss_read_main_flag_total_e) {
            fss_read_print_number(&main->program.output, 1);
          }
          else {
            range.stop = main->setting.contents.array[at].array[0].stop;

            fss_read_print_content(&main->program.output, range, delimits_content);
            f_print_dynamic_raw(f_string_eol_s, main->program.output.to);
          }

          f_file_stream_unlock(main->program.output.to);

          main->setting.state.status = F_success;

          return;
        }
      }
    }

    main->setting.state.status = F_none;
  }
#endif // _di_fss_read_process_at_line_

#ifndef _di_fss_read_process_last_line_
  void fss_read_process_last_line(void * const void_main) {

    if (!void_main) return;

    fss_read_main_t * const main = (fss_read_main_t *) void_main;

    main->setting.state.status = f_string_dynamic_append_assure(f_string_eol_s, &main->setting.buffer);

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & fss_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fll_error_file_print(&main->error, F_status_set_fine(main->setting.state.status), macro_fss_read_f(f_string_dynamic_append_assure), fll_error_file_flag_fallback_e, f_string_ascii_minus_s, f_file_operation_read_s, fll_error_file_type_pipe_e);
    }
  }
#endif // _di_fss_read_process_last_line_

#ifdef __cplusplus
} // extern "C"
#endif
