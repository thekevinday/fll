#include "fss_payload_write.h"
#include "private-common.h"
#include "private-write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_payload_write_process_
  void fss_payload_write_process(fll_program_data_t * const main, fss_payload_write_setting_t * const setting, const f_string_static_t *object, const f_string_static_t *content) {

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

        setting->status = fll_fss_payload_write(*object, *content, setting->flag & fss_payload_write_main_flag_trim_e, setting->flag & fss_payload_write_main_flag_prepend_e ? &setting->prepend : 0, setting->state, &setting->buffer);

        if (F_status_set_fine(setting->status) == F_none_eol) {
          setting->status = F_status_set_error(F_supported_not);

          fss_payload_write_print_line_first_locked(setting, main->error);
          fss_payload_write_print_error_unsupported_eol(setting, main->error);
          fss_payload_write_print_line_last_locked(setting, main->error);

          return;
        }

        if (F_status_is_error(setting->status)) {
          fss_payload_write_print_error(setting, main->error, "fll_fss_payload_write");

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
          if (main->parameters.array[fss_payload_write_parameter_trim_e].result == f_console_result_found_e) {
            complete = f_fss_complete_full_trim_e;
          }
          else {
            complete = f_fss_complete_full_e;
          }
        }

        setting->status = fl_fss_basic_list_object_write(*object, complete, setting->state, &setting->range, &setting->buffer);

        if (F_status_set_fine(setting->status) == F_none_eol) {
          setting->status = F_status_set_error(F_supported_not);

          fss_payload_write_print_line_first_locked(setting, main->error);
          fss_payload_write_print_error_unsupported_eol(setting, main->error);
          fss_payload_write_print_line_last_locked(setting, main->error);

          return;
        }

        if (F_status_is_error(setting->status)) {
          fss_payload_write_print_error(setting, main->error, "fl_fss_basic_list_object_write");

          return;
        }
      }
    }
    else if (content && content->used) {
      setting->range.start = 0;
      setting->range.stop = content->used - 1;

      const f_string_static_t *prepend = 0;

      if (setting->flag & fss_payload_write_main_flag_prepend_e) {
        const f_array_length_t index = main->parameters.array[fss_payload_write_parameter_prepend_e].values.array[main->parameters.array[fss_payload_write_parameter_prepend_e].values.used - 1];

        prepend = &main->parameters.arguments.array[index];
      }

      setting->status = fl_fss_basic_list_content_write(*content, object ? f_fss_complete_full_e : f_fss_complete_none_e, prepend, setting->state, &setting->range, &setting->buffer);

      if (F_status_is_error(setting->status)) {
        fss_payload_write_print_error(setting, main->error, "fl_fss_payload_content_write");

        return;
      }
    }

    if (!object || !content) {
      setting->status = f_string_dynamic_append(f_string_eol_s, &setting->buffer);

      if (F_status_is_error(setting->status)) {
        fss_payload_write_print_error(setting, main->error, "f_string_dynamic_append");

        return;
      }
    }

    fll_print_dynamic(setting->buffer, main->output.to);

    setting->buffer.used = 0;
    setting->status = F_none;
  }
#endif // _di_fss_payload_write_process_

#ifndef _di_fss_payload_write_process_pipe_
  void fss_payload_write_process_pipe(fll_program_data_t * const main, fss_payload_write_setting_t * const setting) {

    f_status_t status_pipe = F_none;
    f_file_t input = f_file_t_initialize;
    input.id = F_type_descriptor_input_d;
    input.size_read = fss_payload_write_common_allocation_large_d;

    f_array_length_t total = 0;
    f_array_length_t length = 0;
    f_string_range_t range = f_string_range_t_initialize;

    // 0x0 = nothing printed, 0x1 = something printed, 0x2 = "payload" matched.
    uint8_t printed = 0;

    // 0x0 = start new object/content set, 0x1 = processing object, 0x2 = processing content, 0x3 = end object/content set, 0x4 = processing payload content.
    uint8_t state = 0;

    for (;;) {

      if (!((++main->signal_check) % fss_payload_write_signal_check_d)) {
        if (fll_program_standard_signal_received(main)) {
          fll_program_print_signal_received(main->warning, setting->line_first, main->signal_received);

          setting->status = F_status_set_error(F_interrupt);

          break;
        }

        main->signal_check = 0;
      }

      if (range.start > range.stop) {
        if (status_pipe == F_none_eof) break;

        setting->block.used = 0;

        status_pipe = f_file_read_block(input, &setting->block);

        if (F_status_is_error(status_pipe)) {
          fss_payload_write_print_error(setting, main->error, "f_file_read_block");

          status_pipe = F_status_set_error(F_pipe);

          break;
        }

        if (!setting->block.used) break;

        range.start = 0;
        range.stop = setting->block.used - 1;
      }

      if (!state || state == 0x1) {
        if (!state) {
          setting->object.used = 0;
          setting->content.used = 0;

          state = 0x1;
        }

        if (setting->object.used + setting->block.used > setting->object.size) {
          setting->status = f_string_dynamic_increase_by(setting->block.used, &setting->object);

          if (F_status_is_error(setting->status)) {
            fss_payload_write_print_error(setting, main->error, "f_string_dynamic_increase_by");

            break;
          }
        }

        for (; range.start <= range.stop; ++range.start) {

          if (setting->block.string[range.start] == fss_payload_write_pipe_content_start_s.string[0]) {
            state = 0x2;
            ++range.start;

            break;
          }

          if (setting->block.string[range.start] == fss_payload_write_pipe_content_end_s.string[0]) {
            state = 0x3;
            ++range.start;

            break;
          }

          if (setting->block.string[range.start] == fss_payload_write_pipe_content_ignore_s.string[0]) {

            // This is not used by objects.
            continue;
          }

          setting->object.string[setting->object.used++] = setting->block.string[range.start];
        } // for

        if (F_status_is_error(setting->status)) break;

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
        if (fl_string_dynamic_compare(f_fss_string_payload_s, setting->object) == F_equal_to) {
          if (total > 1) {
            setting->status = f_string_dynamic_increase_by(total, &setting->content);

            if (F_status_is_error(setting->status)) {
              fss_payload_write_print_error(setting, main->error, "f_string_dynamic_increase_by");

              break;
            }

            memcpy(setting->content.string, setting->block.string + range.start, sizeof(f_char_t) * total);

            setting->content.used += total;
          }

          state = 0x4;
          printed |= 0x2;

          // Designate to read next block from pipe.
          range.start = 1;
          range.stop = 0;

          continue;
        }

        if (total) {
          setting->status = f_string_dynamic_increase_by(total, &setting->content);

          if (F_status_is_error(setting->status)) {
            fss_payload_write_print_error(setting, main->error, "f_string_dynamic_increase_by");

            break;
          }

          for (; range.start <= range.stop; ++range.start) {

            if (setting->block.string[range.start] == fss_payload_write_pipe_content_start_s.string[0]) {
              setting->status = F_status_set_error(F_supported_not);

              if (main->error.verbosity > f_console_verbosity_quiet_e) {
                fss_payload_write_print_line_first_locked(setting, main->error);
                fss_payload_write_print_error_one_content_only(setting, main->error);
                fss_payload_write_print_line_last_locked(setting, main->error);
              }

              break;
            }

            if (setting->block.string[range.start] == fss_payload_write_pipe_content_end_s.string[0]) {
              state = 0x3;
              ++range.start;

              break;
            }

            if (setting->block.string[range.start] == fss_payload_write_pipe_content_ignore_s.string[0]) {

              // This is not used by this program.
              continue;
            }

            setting->content.string[setting->content.used++] = setting->block.string[range.start];
          } // for

          if (F_status_is_error(setting->status)) break;
        }
        else {
          state = 0x3;
        }
      }

      if (state == 0x3) {
        if (setting->flag & fss_payload_write_main_flag_partial_e) {
          if (setting->flag & fss_payload_write_main_flag_content_e) {
            fss_payload_write_process(main, setting, 0, &setting->content);
          }
          else {
            fss_payload_write_process(main, setting, &setting->object, 0);
          }
        }
        else {
          fss_payload_write_process(main, setting, &setting->object, &setting->content);
        }

        if (F_status_is_error(setting->status)) break;

        state = 0;
        printed |= 0x1;

        continue;
      }

      if (state == 0x4) {
        if (setting->block.used && range.start <= range.stop) {
          length = (range.stop - range.start) + 1;

          setting->status = f_string_dynamic_increase_by(length + 1, &setting->content);

          if (F_status_is_error(setting->status)) {
            fss_payload_write_print_error(setting, main->error, "f_string_dynamic_increase_by");

            break;
          }

          memcpy(setting->content.string + range.start, setting->block.string, sizeof(f_char_t) * length);

          setting->content.used += length;
        }

        // Designate to read next block from pipe.
        range.start = 1;
        range.stop = 0;
      }
    } // for

    // If the pipe ended before finishing, then attempt to wrap up.
    if (F_status_is_error_not(setting->status) && status_pipe == F_none_eof && state) {
      if (setting->flag & fss_payload_write_main_flag_partial_e) {
        if (setting->flag & fss_payload_write_main_flag_content_e) {
          fss_payload_write_process(main, setting, 0, &setting->content);
        }
        else {
          fss_payload_write_process(main, setting, &setting->object, 0);
        }
      }
      else {
        fss_payload_write_process(main, setting, &setting->object, &setting->content);
      }

      printed |= 0x1;
    }

    setting->block.used = 0;
    setting->object.used = 0;
    setting->content.used = 0;
    setting->buffer.used = 0;

    if (F_status_is_error_not(setting->status)) {
      if (printed & 0x1) {
        if (printed & 0x2) {
          setting->status = F_payload;
        }
        else {
          setting->status = F_none;
        }
      }
      else {
        setting->status = F_data_not;
      }
    }
  }
#endif // _di_fss_payload_write_process_pipe_

#ifdef __cplusplus
} // extern "C"
#endif
