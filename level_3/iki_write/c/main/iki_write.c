#include "iki_write.h"
#include "private-common.h"
#include "private-write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_main_
  void iki_write_main(fll_program_data_t * const main, iki_write_setting_t * const setting) {

    if (!main || !setting) return;

    if (F_status_is_error(setting->status)) {
      iki_write_print_line_last_locked(setting, main->error);

      return;
    }

    setting->status = F_none;

    if (setting->flag & iki_write_main_flag_help_e) {
      iki_write_print_help(setting, main->message);

      return;
    }

    if (setting->flag & iki_write_main_flag_version_e) {
      fll_program_print_version(main->message, (setting->line_first.used ? 0x1 : 0x0) | (setting->line_last.used ? 0x2 : 0x0), iki_write_program_version_s);

      return;
    }

    if (setting->flag & iki_write_main_flag_copyright_e) {
      fll_program_print_copyright(main->message, (setting->line_first.used ? 0x1 : 0x0) | (setting->line_last.used ? 0x2 : 0x0));

      return;
    }

    setting->escaped.used = 0;

    if (main->pipe & fll_program_data_pipe_input_e) {
      bool object_ended = F_false;

      f_array_length_t previous = 0;
      f_string_range_t range = f_string_range_t_initialize;
      f_status_t status = F_none;
      f_file_t pipe = f_file_t_initialize;

      pipe.id = F_type_descriptor_input_d;
      pipe.size_read = 1;

      setting->buffer.used = 0;
      setting->object.used = 0;
      setting->content.used = 0;

      range.start = 0;

      do {
        if (!((++main->signal_check) % iki_write_signal_check_d)) {
          if (fll_program_standard_signal_received(main)) {
            setting->status = F_status_set_error(F_interrupt);

            return;
          }

          main->signal_check = 0;
        }

        if (status != F_none_eof) {
          status = f_file_read(pipe, &setting->buffer);

          if (F_status_is_error(status)) {
            setting->status = F_status_set_error(F_pipe);

            iki_write_print_error_file(setting, main->error, macro_iki_write_f(f_file_read), f_string_ascii_minus_s, f_file_operation_read_s, fll_error_file_type_pipe_e);

            return;
          }

          if (!setting->buffer.used) {
            setting->status = F_status_set_error(F_parameter);

            iki_write_print_line_first_locked(setting, main->error);
            fll_program_print_error_pipe_missing_content(main->error);
            iki_write_print_line_last_locked(setting, main->error);

            return;
          }

          range.stop = setting->buffer.used - 1;
        }

        previous = range.start;
        setting->status = f_string_dynamic_seek_to(setting->buffer, f_string_ascii_feed_form_s.string[0], &range);

        if (setting->status == F_data_not_stop) {
          setting->status = F_status_set_error(F_parameter);
        }

        if (F_status_is_error(setting->status)) {
          iki_write_print_error(setting, main->error, macro_iki_write_f(f_string_dynamic_seek_to));

          return;
        }

        if (object_ended && previous == range.start) {
          setting->status = F_status_set_error(F_parameter);

          iki_write_print_line_first_locked(setting, main->error);
          fll_program_print_error_pipe_invalid_form_feed(main->error);
          iki_write_print_line_last_locked(setting, main->error);

          return;
        }

        range.stop = range.start - 1;
        range.start = previous;

        if (object_ended) {
          setting->content.used = 0;

          if (setting->buffer.used) {
            setting->status = f_string_dynamic_partial_append_nulless(setting->buffer, range, &setting->content);

            if (F_status_is_error(setting->status)) {
              iki_write_print_error(setting, main->error, macro_iki_write_f(f_string_dynamic_partial_append_nulless));

              return;
            }
          }

          iki_write_process(main, setting, setting->object, setting->content);
          if (F_status_is_error(setting->status)) return;

          fll_print_dynamic_raw(f_string_eol_s, main->output.to);

          object_ended = F_false;
        }
        else {
          setting->object.used = 0;

          setting->status = f_string_dynamic_partial_append_nulless(setting->buffer, range, &setting->object);

          if (F_status_is_error(setting->status)) {
            iki_write_print_error(setting, main->error, macro_iki_write_f(f_string_dynamic_partial_append_nulless));

            return;
          }

          object_ended = F_true;
        }

        // Restore the range, positioned after the new line.
        range.start = range.stop + 2;
        range.stop = setting->buffer.used - 1;

        // Only clear the buffer and reset the start when the entire buffer has been processed.
        if (range.start > range.stop) {
          range.start = 0;
          setting->buffer.used = 0;
        }

      } while (status != F_none_eof || setting->buffer.used || object_ended);

      if (object_ended) {
        setting->status = F_status_set_error(F_parameter);

        iki_write_print_line_first_locked(setting, main->error);
        fll_program_print_error_pipe_object_without_content(main->error);
        iki_write_print_line_last_locked(setting, main->error);

        return;
      }
    }

    for (f_array_length_t i = 0; i < setting->objects.used; ++i) {

      if (!((++main->signal_check) % iki_write_signal_check_d)) {
        if (fll_program_standard_signal_received(main)) {
          setting->status = F_status_set_error(F_interrupt);

          break;
        }

        main->signal_check = 0;
      }

      iki_write_process(main, setting, setting->objects.array[i], setting->contents.array[i]);
      if (F_status_is_error(setting->status)) break;

      fll_print_dynamic_raw(f_string_eol_s, main->output.to);
    } // for

    if (F_status_is_error(setting->status)) {
      iki_write_print_line_last_locked(setting, main->error);
    }
    else if (setting->status != F_interrupt) {
      iki_write_print_line_last_locked(setting, main->message);
    }
  }
#endif // _di_iki_write_main_

#ifdef __cplusplus
} // extern "C"
#endif
