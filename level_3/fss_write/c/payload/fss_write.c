#include "fss_write.h"
#include "../main/fss_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_write_payload_process_help_
  void fss_write_payload_process_help(void * const void_main) {

    if (!void_main) return;

    fss_write_payload_print_help(&((fss_write_main_t *) void_main)->program.message);
  }
#endif // _di_fss_write_payload_process_help_

#ifndef _di_fss_write_payload_process_pipe_
  void fss_write_payload_process_pipe(void * const void_main) {

    if (!void_main) return;

    fss_write_main_t * const main = (fss_write_main_t *) void_main;

    f_status_t status_pipe = F_none;
    f_file_t input = f_file_t_initialize;
    input.id = F_type_descriptor_input_d;
    input.size_read = fss_write_allocation_large_d;

    f_array_length_t total = 0;
    f_array_length_t length = 0;
    f_string_range_t range = f_string_range_t_initialize;

    const f_array_length_t used_objects = main->setting.objects.used;
    const f_array_length_t used_contentss = main->setting.contentss.used;
    const f_array_length_t used_ignoress = main->setting.ignoress.used;

    main->setting.object = &main->setting.objects.array[used_objects];
    main->setting.contents = &main->setting.contentss.array[used_contentss];
    main->setting.ignores = &main->setting.ignoress.array[used_ignoress];

    // 0x0 = nothing printed, 0x1 = something printed, 0x2 = ignore enabled, 0x4 = added Content for Object, 0x8 = "payload" matched.
    uint8_t flag = 0;

    // 0x0 = start new object/content set, 0x1 = processing object, 0x2 = processing content, 0x3 = end object/content set, 0x4 = processing payload content.
    uint8_t state = 0;

    // This is processed in a single set, so there is only ever one Object added.
    main->setting.state.status = f_string_dynamics_increase(main->setting.state.step_small, &main->setting.objects);

    if (F_status_is_error(main->setting.state.status)) {
      fss_write_print_error(&main->program.error, macro_fss_write_f(f_string_dynamics_increase));

      return;
    }

    // This is processed in a single set, so there is only ever one Content added.
    main->setting.state.status = f_string_dynamicss_increase(main->setting.state.step_small, &main->setting.contentss);

    if (F_status_is_error(main->setting.state.status)) {
      fss_write_print_error(&main->program.error, macro_fss_write_f(f_string_dynamicss_increase));

      return;
    }

    main->setting.state.status = f_string_dynamics_increase(main->setting.state.step_small, main->setting.contents);

    if (F_status_is_error(main->setting.state.status)) {
      fss_write_print_error(&main->program.error, macro_fss_write_f(f_string_dynamics_increase));

      return;
    }

    // This is processed in a single set, so there is only ever one Ignores added.
    main->setting.state.status = f_string_rangess_increase(main->setting.state.step_small, &main->setting.ignoress);

    if (F_status_is_error(main->setting.state.status)) {
      fss_write_print_error(&main->program.error, macro_fss_write_f(f_string_rangess_increase));

      return;
    }

    // Reset all of the used data before starting the loop.
    main->setting.object->used = 0;
    main->setting.contents->used = 0;
    main->setting.ignores->used = 0;

    for (;;) {

      if (!((++main->program.signal_check) % fss_write_signal_check_d)) {
        if (fll_program_standard_signal_received(&main->program)) {
          fll_program_print_signal_received(&main->program.warning, main->program.signal_received);

          main->setting.state.status = F_status_set_error(F_interrupt);

          break;
        }

        main->program.signal_check = 0;
      }

      if (range.start > range.stop) {
        if (status_pipe == F_none_eof) break;

        main->setting.block.used = 0;

        status_pipe = f_file_read_block(input, &main->setting.block);

        if (F_status_is_error(status_pipe)) {
          fss_write_print_error(&main->program.error, macro_fss_write_f(f_file_read_block));

          status_pipe = F_status_set_error(F_pipe);

          break;
        }

        if (!main->setting.block.used) break;

        range.start = 0;
        range.stop = main->setting.block.used - 1;
        status_pipe = F_none;
      }

      // Start Object.
      if (!state || state == 0x1) {
        if (!state) {
          main->setting.object->used = 0;

          state = 0x1;
        }

        // Reset the "has Content for Object" flag and associated contents array used length.
        flag -= flag | 0x4;
        main->setting.contents->used = 0;

        main->setting.state.status = f_string_dynamic_increase_by(main->setting.block.used, main->setting.object);

        if (F_status_is_error(main->setting.state.status)) {
          fss_write_print_error(&main->program.error, macro_fss_write_f(f_string_dynamic_increase_by));

          break;
        }

        for (; range.start <= range.stop && range.start < main->setting.block.used; ++range.start) {

          // Do not handle start/end while inside an ignore set.
          if (!(flag & 0x2)) {
            if (main->setting.block.string[range.start] == fss_write_pipe_content_start_s.string[0]) {
              state = 0x2;
              ++range.start;

              break;
            }

            if (main->setting.block.string[range.start] == fss_write_pipe_content_end_s.string[0]) {
              state = 0x3;
              ++range.start;

              break;
            }
          }

          // There currently is no support for "ignore" in Objects, but the Ignore should still be processed.
          if (main->setting.block.string[range.start] == fss_write_pipe_content_ignore_s.string[0]) {

            // Ignore is enabled.
            if (flag & 0x2) {
              flag -= 0x2;
            }
            else {
              flag |= 0x2;
            }

            continue;
          }

          main->setting.object->string[main->setting.object->used++] = main->setting.block.string[range.start];
        } // for

        if (F_status_is_error(main->setting.state.status)) break;

        // If the start of Content was not found, then fetch the next block.
        if (state == 0x1) continue;

        // If the end of the current block is reached, fetch the next block.
        if (range.start > range.stop) continue;
      }

      // Begin Content.
      if (state == 0x2) {

        // Check to see if the Content supports multiple Content per Object.
        if (flag & 0x4) {
          if (!(main->setting.flag & fss_write_main_flag_content_multiple_e)) {
            main->setting.state.status = F_status_set_error(F_support_not);

            fss_write_print_error_one_content_only(&main->program.error);

            break;
          }

          main->setting.state.status = f_string_dynamics_increase(main->setting.state.step_small, main->setting.contents);

          if (F_status_is_error(main->setting.state.status)) {
            fss_write_print_error(&main->program.error, macro_fss_write_f(f_string_dynamics_increase));

            break;
          }
        }

        if (range.start <= range.stop) {
          total = (range.stop - range.start) + 1;
        }
        else {
          total = 0;
        }

        // When payload is provided, all data at this point is part of the payload until the end of the pipe.
        if (fl_string_dynamic_compare(f_fss_payload_s, *main->setting.object) == F_equal_to) {
          if (total > 1) {
            main->setting.state.status = f_string_dynamic_increase_by(total, &main->setting.contents->array[main->setting.contents->used]);

            if (F_status_is_error(main->setting.state.status)) {
              fss_write_print_error(&main->program.error, macro_fss_write_f(f_string_dynamic_increase_by));

              break;
            }

            memcpy(main->setting.contents->array[main->setting.contents->used].string, main->setting.block.string + range.start, sizeof(f_char_t) * total);

            main->setting.contents->array[main->setting.contents->used].used += total;
          }

          state = 0x4;
          flag |= 0x8;

          // Designate to read next block from pipe.
          range.start = 1;
          range.stop = 0;

          continue;
        }

        if (total) {
          main->setting.state.status = f_string_dynamic_increase_by(total, &main->setting.contents->array[main->setting.contents->used]);

          if (F_status_is_error(main->setting.state.status)) {
            fss_write_print_error(&main->program.error, macro_fss_write_f(f_string_dynamic_increase_by));

            break;
          }

          for (; range.start <= range.stop && range.start < main->setting.block.used; ++range.start) {

            // Do not handle start/end while inside an ignore set.
            if (!(flag & 0x2)) {
              if (main->setting.block.string[range.start] == fss_write_pipe_content_start_s.string[0]) {
                main->setting.state.status = F_status_set_error(F_support_not);

                fss_write_print_error_one_content_only(&main->program.error);

                break;
              }

              if (main->setting.block.string[range.start] == fss_write_pipe_content_end_s.string[0]) {
                state = 0x3;
                ++range.start;

                break;
              }
            }

            // There currently is no support for "ignore" in Contents, but the Ignore should still be processed.
            if (main->setting.block.string[range.start] == fss_write_pipe_content_ignore_s.string[0]) {

              // Ignore is enabled.
              if (flag & 0x2) {
                flag -= 0x2;
              }
              else {
                flag |= 0x2;
              }

              continue;
            }

            main->setting.contents->array[main->setting.contents->used].string[main->setting.contents->array[main->setting.contents->used].used++] = main->setting.block.string[range.start];
          } // for

          if (F_status_is_error(main->setting.state.status)) break;

          ++main->setting.contents->used;
          flag |= 0x4;
        }
        else {
          state = 0x3;
        }
      }

      // End Object or Content set.
      if (state == 0x3) {
        fss_write_payload_process_set(void_main);
        if (F_status_is_error(main->setting.state.status)) break;

        state = 0;
        flag |= 0x1;

        // Reset all of the used data for next set.
        main->setting.object->used = 0;
        main->setting.contents->used = 0;
        main->setting.ignores->used = 0;

        continue;
      }

      // Payload Object.
      if (state == 0x4) {
        if (main->setting.block.used && range.start <= range.stop) {
          length = (range.stop - range.start) + 1;

          main->setting.state.status = f_string_dynamic_increase_by(length + 1, &main->setting.contents->array[main->setting.contents->used]);

          if (F_status_is_error(main->setting.state.status)) {
            fss_write_print_error(&main->program.error, macro_fss_write_f(f_string_dynamic_increase_by));

            break;
          }

          memcpy(main->setting.contents->array[main->setting.contents->used].string + range.start, main->setting.block.string, sizeof(f_char_t) * length);

          main->setting.contents->array[main->setting.contents->used].used += length;
        }

        // Designate to read next block from pipe.
        range.start = 1;
        range.stop = 0;

        // Reset all of the used data for next set.
        main->setting.object->used = 0;
        main->setting.contents->used = 0;
        main->setting.ignores->used = 0;
      }
    } // for

    // If the pipe ended before finishing, then attempt to wrap up.
    if (F_status_is_error_not(main->setting.state.status) && status_pipe == F_none_eof && state) {
      fss_write_payload_process_set(void_main);

      flag |= 0x1;
    }

    main->setting.block.used = 0;
    main->setting.buffer.used = 0;
    main->setting.object->used = 0;
    main->setting.contents->used = 0;
    main->setting.ignores->used = 0;
    main->setting.objects.used = used_objects;
    main->setting.contentss.used = used_contentss;
    main->setting.ignoress.used = used_ignoress;

    if (F_status_is_error_not(main->setting.state.status)) {
      if (flag & 0x1) {
        if (flag & 0x8) {
          main->setting.state.status = F_payload;
        }
        else {
          main->setting.state.status = F_none;
        }
      }
      else {
        main->setting.state.status = F_data_not;
      }

      // Payload.
      if (main->setting.contentss.used && (flag & 0x8)) {
        fll_print_dynamic(f_fss_payload_header_close_s, main->program.output.to);
      }
    }
  }
#endif // _di_fss_write_payload_process_pipe_

#ifndef _di_fss_write_payload_process_set_
  void fss_write_payload_process_set(void * const void_main) {

    if (!void_main) return;

    fss_write_main_t * const main = (fss_write_main_t *) void_main;

    if ((!(main->setting.flag & fss_write_main_flag_partial_e) || (main->setting.flag & fss_write_main_flag_partial_e) && (main->setting.flag & fss_write_main_flag_object_e))) {
      if (main->setting.object && !(main->setting.flag & fss_write_main_flag_partial_e) && main->setting.contents && main->setting.contents->used) {
        if (main->setting.object->used) {
          main->setting.range.start = 0;
          main->setting.range.stop = main->setting.object->used - 1;
        }
        else {
          main->setting.range.start = 1;
          main->setting.range.stop = 0;
        }

        fll_fss_payload_write(
          *main->setting.object,
          main->setting.contents->array[0],
          (main->setting.flag & fss_write_main_flag_trim_e),
          (main->setting.flag & fss_write_main_flag_prepend_e)
            ? &main->setting.prepend
            : 0,
          &main->setting.buffer,
          &main->setting.state
        );

        if (F_status_set_fine(main->setting.state.status) == F_none_eol) {
          main->setting.state.status = F_status_set_error(F_support_not);

          fss_write_print_error_unsupported_eol(&main->program.error);

          return;
        }

        if (F_status_is_error(main->setting.state.status)) {
          fss_write_print_error(&main->program.error, macro_fss_write_f(fll_fss_payload_write));

          return;
        }
      }
      else {
        if (main->setting.object) {
          if (main->setting.object->used) {
            main->setting.range.start = 0;
            main->setting.range.stop = main->setting.object->used - 1;
          }
          else {
            main->setting.range.start = 1;
            main->setting.range.stop = 0;
          }

          fl_fss_basic_list_object_write(
            *main->setting.object,
            (main->setting.flag & fss_write_main_flag_partial_e)
              ? (main->setting.flag & fss_write_main_flag_trim_e)
                ? f_fss_complete_trim_e
                : f_fss_complete_none_e
              : (main->setting.flag & fss_write_main_flag_trim_e)
                ? f_fss_complete_full_trim_e
                : f_fss_complete_full_e,
            &main->setting.range,
            &main->setting.buffer,
            &main->setting.state
          );

          if (F_status_set_fine(main->setting.state.status) == F_none_eol) {
            main->setting.state.status = F_status_set_error(F_support_not);

            fss_write_print_error_unsupported_eol(&main->program.error);

            return;
          }

          if (F_status_is_error(main->setting.state.status)) {
            fss_write_print_error(&main->program.error, macro_fss_write_f(fl_fss_basic_list_object_write));

            return;
          }
        }

        if ((main->setting.flag & fss_write_main_flag_partial_e) && !(main->setting.flag & fss_write_main_flag_content_e) || !(main->setting.flag & (fss_write_main_flag_object_e | fss_write_main_flag_content_e))) {
          if (main->setting.flag & fss_write_main_flag_object_open_e) {
            main->setting.state.status = f_string_dynamic_append(f_fss_basic_list_open_s, &main->setting.buffer);

            if (F_status_is_error_not(main->setting.state.status)) {
              main->setting.state.status = f_string_dynamic_append(f_fss_basic_list_open_end_s, &main->setting.buffer);
            }

            if (F_status_is_error(main->setting.state.status)) {
              fss_write_print_error(&main->program.error, macro_fss_write_f(f_string_dynamic_append));

              return;
            }
          }
        }
      }
    }
    else {
      if (main->setting.contents && main->setting.contents->used && main->setting.contents->array[0].used) {
        main->setting.range.start = 0;
        main->setting.range.stop = main->setting.contents->array[0].used - 1;

        const f_string_static_t *prepend = 0;

        if (main->setting.flag & fss_write_main_flag_prepend_e) {
          const f_array_length_t index = main->program.parameters.array[fss_write_parameter_prepend_e].values.array[main->program.parameters.array[fss_write_parameter_prepend_e].values.used - 1];

          prepend = &main->program.parameters.arguments.array[index];
        }

        fl_fss_basic_list_content_write(
          main->setting.contents->array[0],
          main->setting.object
            ? f_fss_complete_full_e
            : f_fss_complete_none_e,
          prepend,
          &main->setting.range,
          &main->setting.buffer,
          &main->setting.state
        );

        if (F_status_is_error(main->setting.state.status)) {
          fss_write_print_error(&main->program.error, macro_fss_write_f(fl_fss_payload_content_write));

          return;
        }
      }

      if ((main->setting.flag & fss_write_main_flag_partial_e) && !(main->setting.flag & fss_write_main_flag_object_e) || !(main->setting.flag & (fss_write_main_flag_object_e | fss_write_main_flag_content_e))) {
        if (main->setting.flag & fss_write_main_flag_content_end_e) {
          main->setting.state.status = f_string_dynamic_append(f_fss_basic_list_close_s, &main->setting.buffer);

          if (F_status_is_error(main->setting.state.status)) {
            fss_write_print_error(&main->program.error, macro_fss_write_f(f_string_dynamic_append));

            return;
          }
        }
      }
    }

    if (!main->setting.object || !(main->setting.contents && main->setting.contents->used)) {
      main->setting.state.status = f_string_dynamic_append(f_string_eol_s, &main->setting.buffer);

      if (F_status_is_error(main->setting.state.status)) {
        fss_write_print_error(&main->program.error, macro_fss_write_f(f_string_dynamic_append));

        return;
      }
    }

    fll_print_dynamic(main->setting.buffer, main->program.output.to);

    main->setting.buffer.used = 0;
    main->setting.state.status = F_none;
  }
#endif // _di_fss_write_payload_process_set_

#ifndef _di_fss_write_payload_setting_load_
  void fss_write_payload_setting_load(const f_console_arguments_t arguments, fss_write_main_t * const main) {

    if (!main) return;

    f_array_lengths_t * const values = &main->program.parameters.array[fss_write_parameter_object_e].values;
    f_string_static_t * const argv = main->program.parameters.arguments.array;

    if ((main->program.parameters.array[fss_write_parameter_object_e].result & f_console_result_value_e) && values->used) {

      for (f_array_length_t i = 0; i < values->used; ++i) {

        if (fl_string_dynamic_compare(argv[values->array[i]], fss_write_payload_s) == F_equal_to && i + 1 < values->used) {
          main->setting.state.status = F_status_set_error(F_parameter);

          fss_write_payload_print_error_payload_not_last(&main->program.error);

          return;
        }
      } // for
    }
  }
#endif // _di_fss_write_payload_setting_load_

#ifdef __cplusplus
} // extern "C"
#endif
