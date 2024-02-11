#include "iki_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_main_
  void iki_write_main(iki_write_main_t * const main) {

    if (!main) return;

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & iki_write_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    if ((main->setting.flag & iki_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }

    main->setting.state.status = F_okay;

    if (main->setting.flag & iki_write_main_flag_version_copyright_help_e) {
      if (main->setting.flag & iki_write_main_flag_help_e) {
        iki_write_print_message_help(&main->program.message);
      }
      else if (main->setting.flag & iki_write_main_flag_version_e) {
        fll_program_print_version(&main->program.message, iki_write_program_version_s);
      }
      else if (main->setting.flag & iki_write_main_flag_copyright_e) {
        fll_program_print_copyright(&main->program.message);
      }

      if ((main->setting.flag & iki_write_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    main->setting.escaped.used = 0;

    if (main->setting.flag & iki_write_main_flag_pipe_e) {
      bool object_ended = F_false;

      f_number_unsigned_t previous = 0;
      f_range_t range = f_range_t_initialize;
      f_status_t status = F_okay;
      f_file_t pipe = f_file_t_initialize;

      pipe.id = F_type_descriptor_input_d;
      pipe.size_read = 1;

      main->setting.buffer.used = 0;
      main->setting.object.used = 0;
      main->setting.content.used = 0;

      range.start = 0;

      do {
        if (!((++main->program.signal_check) % iki_write_signal_check_d)) {
          if (fll_program_standard_signal_received(&main->program)) {
            main->setting.state.status = F_status_set_error(F_interrupt);

            object_ended = F_false;

            break;
          }

          main->program.signal_check = 0;
        }

        if (status != F_okay_eof) {
          status = f_file_read(pipe, &main->setting.buffer);

          if (F_status_is_error(status)) {
            main->setting.state.status = F_status_set_error(F_pipe);

            iki_write_print_error_file(&main->program.error, macro_iki_write_f(f_file_read), f_string_ascii_minus_s, f_file_operation_read_s, fll_error_file_type_pipe_e);

            object_ended = F_false;

            break;
          }

          if (!main->setting.buffer.used) {
            main->setting.state.status = F_status_set_error(F_parameter);

            fll_program_print_error_pipe_missing_content(&main->program.error);

            object_ended = F_false;

            break;
          }

          range.stop = main->setting.buffer.used - 1;
        }

        previous = range.start;
        main->setting.state.status = f_string_dynamic_seek_to(main->setting.buffer, f_string_ascii_feed_form_s.string[0], &range);

        if (main->setting.state.status == F_data_not_stop) {
          main->setting.state.status = F_status_set_error(F_parameter);
        }

        if (F_status_is_error(main->setting.state.status)) {
          iki_write_print_error(&main->program.error, macro_iki_write_f(f_string_dynamic_seek_to));

          object_ended = F_false;

          break;
        }

        if (object_ended && previous == range.start) {
          main->setting.state.status = F_status_set_error(F_parameter);

          fll_program_print_error_pipe_invalid_form_feed(&main->program.error);

          object_ended = F_false;

          break;
        }

        range.stop = range.start - 1;
        range.start = previous;

        if (object_ended) {
          main->setting.content.used = 0;

          if (main->setting.buffer.used) {
            main->setting.state.status = f_string_dynamic_partial_append_nulless(main->setting.buffer, range, &main->setting.content);

            if (F_status_is_error(main->setting.state.status)) {
              iki_write_print_error(&main->program.error, macro_iki_write_f(f_string_dynamic_partial_append_nulless));

              object_ended = F_false;

              break;
            }
          }

          iki_write_process(main, main->setting.object, main->setting.content);

          if (F_status_is_error(main->setting.state.status)) {
            object_ended = F_false;

            break;
          }

          fll_print_dynamic_raw(f_string_eol_s, main->program.output.to);

          object_ended = F_false;
        }
        else {
          main->setting.object.used = 0;

          main->setting.state.status = f_string_dynamic_partial_append_nulless(main->setting.buffer, range, &main->setting.object);

          if (F_status_is_error(main->setting.state.status)) {
            iki_write_print_error(&main->program.error, macro_iki_write_f(f_string_dynamic_partial_append_nulless));

            object_ended = F_false;

            break;
          }

          object_ended = F_true;
        }

        // Restore the range, positioned after the new line.
        range.start = range.stop + 2;
        range.stop = main->setting.buffer.used - 1;

        // Only clear the buffer and reset the start when the entire buffer has been processed.
        if (range.start > range.stop) {
          range.start = 0;
          main->setting.buffer.used = 0;
        }

      } while (status != F_okay_eof || main->setting.buffer.used || object_ended);

      if (object_ended) {
        main->setting.state.status = F_status_set_error(F_parameter);

        fll_program_print_error_pipe_object_without_content(&main->program.error);
      }
    }

    if (F_status_is_error_not(main->setting.state.status) && F_status_set_fine(main->setting.state.status) != F_interrupt) {
      for (f_number_unsigned_t i = 0; i < main->setting.objects.used; ++i) {

        if (!((++main->program.signal_check) % iki_write_signal_check_d)) {
          if (fll_program_standard_signal_received(&main->program)) {
            main->setting.state.status = F_status_set_error(F_interrupt);

            break;
          }

          main->program.signal_check = 0;
        }

        iki_write_process(main, main->setting.objects.array[i], main->setting.contents.array[i]);
        if (F_status_is_error(main->setting.state.status)) break;

        fll_print_dynamic_raw(f_string_eol_s, main->program.output.to);
      } // for
    }

    if ((main->setting.flag & iki_write_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }
  }
#endif // _di_iki_write_main_

#ifdef __cplusplus
} // extern "C"
#endif
