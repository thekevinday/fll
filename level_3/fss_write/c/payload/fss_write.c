#include "fss_write.h"
#include "../main/fss_write.h"
#include "private-common.h"
#include "private-write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_write_payload_process_help_
  void fss_write_payload_process_help(fll_program_data_t * const main, void * const setting) {

    fss_write_payload_print_help(macro_fss_write_setting(setting), main->message);
  }
#endif // _di_fss_write_payload_process_help_

#ifndef _di_fss_write_payload_process_normal_
  void fss_write_payload_process_normal(fll_program_data_t * const main, void * const setting) {

    f_string_statics_t * const data = (macro_fss_write_setting(setting)->flag & fss_write_flag_object_e) ? &macro_fss_write_setting(setting)->objects : &macro_fss_write_setting(setting)->contents;

    for (f_array_length_t i = 0; i < data->used; ++i) {

      // @todo replace all signal checks with forked main process that independently checks and assigns main->signal_received.
      if (!((++main->signal_check) % fss_write_signal_check_d)) {
        if (fll_program_standard_signal_received(main)) {
          macro_fss_write_setting(setting)->status = F_status_set_error(F_interrupt);

          return;
        }

        main->signal_check = 0;
      }

      fss_write_payload_process_set(
        main,
        macro_fss_write_setting(setting),
        (macro_fss_write_setting(setting)->flag & fss_write_flag_object_e) ? &macro_fss_write_setting(setting)->objects.array[i] : 0,
        (macro_fss_write_setting(setting)->flag & fss_write_flag_content_e) ? &macro_fss_write_setting(setting)->contents.array[i] : 0
      );

      if (F_status_is_error(macro_fss_write_setting(setting)->status)) break;
    } // for
  }
#endif // _di_fss_write_payload_process_normal_

#ifndef _di_fss_write_payload_process_pipe_
  void fss_write_payload_process_pipe(fll_program_data_t * const main, void * const setting) {

    f_status_t status_pipe = F_none;
    f_file_t input = f_file_t_initialize;
    input.id = F_type_descriptor_input_d;
    input.size_read = fss_write_common_allocation_large_d;

    f_array_length_t total = 0;
    f_array_length_t length = 0;
    f_string_range_t range = f_string_range_t_initialize;

    // 0x0 = nothing printed, 0x1 = something printed, 0x2 = "payload" matched.
    uint8_t printed = 0;

    // 0x0 = start new object/content set, 0x1 = processing object, 0x2 = processing content, 0x3 = end object/content set, 0x4 = processing payload content.
    uint8_t state = 0;

    for (;;) {

      if (!((++main->signal_check) % fss_write_signal_check_d)) {
        if (fll_program_standard_signal_received(main)) {
          fll_program_print_signal_received(main->warning, macro_fss_write_setting(setting)->line_first, main->signal_received);

          macro_fss_write_setting(setting)->status = F_status_set_error(F_interrupt);

          break;
        }

        main->signal_check = 0;
      }

      if (range.start > range.stop) {
        if (status_pipe == F_none_eof) break;

        macro_fss_write_setting(setting)->block.used = 0;

        status_pipe = f_file_read_block(input, &macro_fss_write_setting(setting)->block);

        if (F_status_is_error(status_pipe)) {
          fss_write_print_error(macro_fss_write_setting(setting), main->error, "f_file_read_block");

          status_pipe = F_status_set_error(F_pipe);

          break;
        }

        if (!macro_fss_write_setting(setting)->block.used) break;

        range.start = 0;
        range.stop = macro_fss_write_setting(setting)->block.used - 1;
      }

      if (!state || state == 0x1) {
        if (!state) {
          macro_fss_write_setting(setting)->object.used = 0;
          macro_fss_write_setting(setting)->content.used = 0;

          state = 0x1;
        }

        if (macro_fss_write_setting(setting)->object.used + macro_fss_write_setting(setting)->block.used > macro_fss_write_setting(setting)->object.size) {
          macro_fss_write_setting(setting)->status = f_string_dynamic_increase_by(macro_fss_write_setting(setting)->block.used, &macro_fss_write_setting(setting)->object);

          if (F_status_is_error(macro_fss_write_setting(setting)->status)) {
            fss_write_print_error(macro_fss_write_setting(setting), main->error, "f_string_dynamic_increase_by");

            break;
          }
        }

        for (; range.start <= range.stop; ++range.start) {

          if (macro_fss_write_setting(setting)->block.string[range.start] == fss_write_pipe_content_start_s.string[0]) {
            state = 0x2;
            ++range.start;

            break;
          }

          if (macro_fss_write_setting(setting)->block.string[range.start] == fss_write_pipe_content_end_s.string[0]) {
            state = 0x3;
            ++range.start;

            break;
          }

          if (macro_fss_write_setting(setting)->block.string[range.start] == fss_write_pipe_content_ignore_s.string[0]) {

            // This is not used by objects.
            continue;
          }

          macro_fss_write_setting(setting)->object.string[macro_fss_write_setting(setting)->object.used++] = macro_fss_write_setting(setting)->block.string[range.start];
        } // for

        if (F_status_is_error(macro_fss_write_setting(setting)->status)) break;

        // If the start of content was not found, then fetch the next block.
        if (state == 0x1) continue;

        // If the end of the current block is reached, fetch the next block.
        if (range.start > range.stop) continue;
      }

      if (state == 0x2) {
        if (range.start <= range.stop) {
          total = (range.stop - range.start) + 1;
        }
        else {
          total = 0;
        }

        // When payload is provided, all data at this point is part of the payload until the end of the pipe.
        if (fl_string_dynamic_compare(f_fss_string_payload_s, macro_fss_write_setting(setting)->object) == F_equal_to) {
          if (total > 1) {
            macro_fss_write_setting(setting)->status = f_string_dynamic_increase_by(total, &macro_fss_write_setting(setting)->content);

            if (F_status_is_error(macro_fss_write_setting(setting)->status)) {
              fss_write_print_error(macro_fss_write_setting(setting), main->error, "f_string_dynamic_increase_by");

              break;
            }

            memcpy(macro_fss_write_setting(setting)->content.string, macro_fss_write_setting(setting)->block.string + range.start, sizeof(f_char_t) * total);

            macro_fss_write_setting(setting)->content.used += total;
          }

          state = 0x4;
          printed |= 0x2;

          // Designate to read next block from pipe.
          range.start = 1; // fss_write_payload_process_set ??
          range.stop = 0;

          continue;
        }

        if (total) {
          macro_fss_write_setting(setting)->status = f_string_dynamic_increase_by(total, &macro_fss_write_setting(setting)->content);

          if (F_status_is_error(macro_fss_write_setting(setting)->status)) {
            fss_write_print_error(macro_fss_write_setting(setting), main->error, "f_string_dynamic_increase_by");

            break;
          }

          for (; range.start <= range.stop; ++range.start) {

            if (macro_fss_write_setting(setting)->block.string[range.start] == fss_write_pipe_content_start_s.string[0]) {
              macro_fss_write_setting(setting)->status = F_status_set_error(F_supported_not);

              if (main->error.verbosity > f_console_verbosity_quiet_e) {
                fss_write_print_line_first_locked(macro_fss_write_setting(setting), main->error);
                fss_write_print_error_one_content_only(macro_fss_write_setting(setting), main->error, fss_write_payload_standard_s);
                fss_write_print_line_last_locked(macro_fss_write_setting(setting), main->error);
              }

              break;
            }

            if (macro_fss_write_setting(setting)->block.string[range.start] == fss_write_pipe_content_end_s.string[0]) {
              state = 0x3;
              ++range.start;

              break;
            }

            if (macro_fss_write_setting(setting)->block.string[range.start] == fss_write_pipe_content_ignore_s.string[0]) {

              // This is not used by this program.
              continue;
            }

            macro_fss_write_setting(setting)->content.string[macro_fss_write_setting(setting)->content.used++] = macro_fss_write_setting(setting)->block.string[range.start];
          } // for

          if (F_status_is_error(macro_fss_write_setting(setting)->status)) break;
        }
        else {
          state = 0x3;
        }
      }

      if (state == 0x3) {
        if (macro_fss_write_setting(setting)->flag & fss_write_flag_partial_e) {
          if (macro_fss_write_setting(setting)->flag & fss_write_flag_content_e) {
            fss_write_payload_process_set(main, macro_fss_write_setting(setting), 0, &macro_fss_write_setting(setting)->content);
          }
          else {
            fss_write_payload_process_set(main, macro_fss_write_setting(setting), &macro_fss_write_setting(setting)->object, 0);
          }
        }
        else {
          fss_write_payload_process_set(main, macro_fss_write_setting(setting), &macro_fss_write_setting(setting)->object, &macro_fss_write_setting(setting)->content);
        }

        if (F_status_is_error(macro_fss_write_setting(setting)->status)) break;

        state = 0;
        printed |= 0x1;

        continue;
      }

      if (state == 0x4) {
        if (macro_fss_write_setting(setting)->block.used && range.start <= range.stop) {
          length = (range.stop - range.start) + 1;

          macro_fss_write_setting(setting)->status = f_string_dynamic_increase_by(length + 1, &macro_fss_write_setting(setting)->content);

          if (F_status_is_error(macro_fss_write_setting(setting)->status)) {
            fss_write_print_error(macro_fss_write_setting(setting), main->error, "f_string_dynamic_increase_by");

            break;
          }

          memcpy(macro_fss_write_setting(setting)->content.string + range.start, macro_fss_write_setting(setting)->block.string, sizeof(f_char_t) * length);

          macro_fss_write_setting(setting)->content.used += length;
        }

        // Designate to read next block from pipe.
        range.start = 1;
        range.stop = 0;
      }
    } // for

    // If the pipe ended before finishing, then attempt to wrap up.
    if (F_status_is_error_not(macro_fss_write_setting(setting)->status) && status_pipe == F_none_eof && state) {
      if (macro_fss_write_setting(setting)->flag & fss_write_flag_partial_e) {
        if (macro_fss_write_setting(setting)->flag & fss_write_flag_content_e) {
          fss_write_payload_process_set(main, macro_fss_write_setting(setting), 0, &macro_fss_write_setting(setting)->content);
        }
        else {
          fss_write_payload_process_set(main, macro_fss_write_setting(setting), &macro_fss_write_setting(setting)->object, 0);
        }
      }
      else {
        fss_write_payload_process_set(main, macro_fss_write_setting(setting), &macro_fss_write_setting(setting)->object, &macro_fss_write_setting(setting)->content);
      }

      printed |= 0x1;
    }

    macro_fss_write_setting(setting)->block.used = 0;
    macro_fss_write_setting(setting)->object.used = 0;
    macro_fss_write_setting(setting)->content.used = 0;
    macro_fss_write_setting(setting)->buffer.used = 0;

    if (F_status_is_error_not(macro_fss_write_setting(setting)->status)) {
      if (printed & 0x1) {
        if (printed & 0x2) {
          macro_fss_write_setting(setting)->status = F_payload;
        }
        else {
          macro_fss_write_setting(setting)->status = F_none;
        }
      }
      else {
        macro_fss_write_setting(setting)->status = F_data_not;
      }

      // Print newline character to separate data printed from pipe.
      if ((macro_fss_write_setting(setting)->flag & fss_write_flag_partial_e) && macro_fss_write_setting(setting)->objects.used) {
        fll_print_dynamic(f_string_eol_s, main->output.to);
      }
      else if (macro_fss_write_setting(setting)->contents.used) {
        fll_print_dynamic(f_fss_payload_header_close_s, main->output.to);
      }
    }
  }
#endif // _di_fss_write_payload_process_pipe_

#ifndef _di_fss_write_payload_process_set_
  void fss_write_payload_process_set(fll_program_data_t * const main, fss_write_setting_t * const setting, const f_string_static_t *object, const f_string_static_t *content) {

    if (object) {
      if (content) {
        if (object->used) {
          setting->range.start = 0;
          setting->range.stop = object->used - 1;
        }
        else {
          setting->range.start = 1;
          setting->range.stop = 0;
        }

        setting->status = fll_fss_payload_write(*object, *content, setting->flag & fss_write_flag_trim_e, setting->flag & fss_write_flag_prepend_e ? &setting->prepend : 0, setting->state, &setting->buffer);

        if (F_status_set_fine(setting->status) == F_none_eol) {
          setting->status = F_status_set_error(F_supported_not);

          fss_write_print_line_first_locked(setting, main->error);
          fss_write_print_error_unsupported_eol(setting, main->error, fss_write_payload_standard_s);
          fss_write_print_line_last_locked(setting, main->error);

          return;
        }

        if (F_status_is_error(setting->status)) {
          fss_write_print_error(setting, main->error, "fll_fss_payload_write");

          return;
        }
      }
      else {
        bool complete = f_fss_complete_none_e;

        if (object->used) {
          setting->range.start = 0;
          setting->range.stop = object->used - 1;
        }
        else {
          setting->range.start = 1;
          setting->range.stop = 0;
        }

        if (content) {
          if (main->parameters.array[fss_write_parameter_trim_e].result & f_console_result_found_e) {
            complete = f_fss_complete_full_trim_e;
          }
          else {
            complete = f_fss_complete_full_e;
          }
        }

        setting->status = fl_fss_basic_list_object_write(*object, complete, setting->state, &setting->range, &setting->buffer);

        if (F_status_set_fine(setting->status) == F_none_eol) {
          setting->status = F_status_set_error(F_supported_not);

          fss_write_print_line_first_locked(setting, main->error);
          fss_write_print_error_unsupported_eol(setting, main->error, fss_write_payload_standard_s);
          fss_write_print_line_last_locked(setting, main->error);

          return;
        }

        if (F_status_is_error(setting->status)) {
          fss_write_print_error(setting, main->error, "fl_fss_basic_list_object_write");

          return;
        }
      }
    }
    else if (content && content->used) {
      setting->range.start = 0;
      setting->range.stop = content->used - 1;

      const f_string_static_t *prepend = 0;

      if (setting->flag & fss_write_flag_prepend_e) {
        const f_array_length_t index = main->parameters.array[fss_write_parameter_prepend_e].values.array[main->parameters.array[fss_write_parameter_prepend_e].values.used - 1];

        prepend = &main->parameters.arguments.array[index];
      }

      setting->status = fl_fss_basic_list_content_write(*content, object ? f_fss_complete_full_e : f_fss_complete_none_e, prepend, setting->state, &setting->range, &setting->buffer);

      if (F_status_is_error(setting->status)) {
        fss_write_print_error(setting, main->error, "fl_fss_payload_content_write");

        return;
      }
    }

    if (!object || !content) {
      setting->status = f_string_dynamic_append(f_string_eol_s, &setting->buffer);

      if (F_status_is_error(setting->status)) {
        fss_write_print_error(setting, main->error, "f_string_dynamic_append");

        return;
      }
    }

    fll_print_dynamic(setting->buffer, main->output.to);

    setting->buffer.used = 0;
    setting->status = F_none;
  }
#endif // _di_fss_write_payload_process_set_

#ifndef _di_fss_write_payload_setting_load_
  void fss_write_payload_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, fss_write_setting_t * const setting) {

    if (!main || !setting) return;

    f_array_lengths_t * const values = &main->parameters.array[fss_write_parameter_object_e].values;
    f_string_static_t * const argv = main->parameters.arguments.array;

    if ((main->parameters.array[fss_write_parameter_object_e].result & f_console_result_value_e) && values->used) {

      for (f_array_length_t i = 0; i < values->used; ++i) {

        if (fl_string_dynamic_compare(argv[values->array[i]], fss_write_payload_s) == F_equal_to && i + 1 < values->used) {
          setting->status = F_status_set_error(F_parameter);

          fss_write_payload_print_error_payload_not_last(setting, main->error);

          return;
        }
      } // for
    }
  }
#endif // _di_fss_write_payload_setting_load_

#ifdef __cplusplus
} // extern "C"
#endif
