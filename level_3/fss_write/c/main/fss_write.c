#include "fss_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_write_main_
  void fss_write_main(void * const void_main) {

    if (!void_main) return;

    fss_write_main_t * const main = (fss_write_main_t *) void_main;

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & fss_write_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }

    main->setting.state.status = F_okay;

    if (main->setting.flag & fss_write_main_flag_version_copyright_help_e) {
      if (main->setting.flag & fss_write_main_flag_help_e) {
        if (main->callback.process_help) {
          main->callback.process_help(void_main);
        }
        else {
          fss_write_print_message_help(&main->program.message);
        }
      }
      else if (main->setting.flag & fss_write_main_flag_version_e) {
        fll_program_print_version(&main->program.message, fss_write_program_version_s);
      }
      else if (main->setting.flag & fss_write_main_flag_copyright_e) {
        fll_program_print_copyright(&main->program.message);
      }

      if ((main->setting.flag & fss_write_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    if (main->setting.flag & fss_write_main_flag_pipe_e) {
      if (main->callback.process_pipe) {
        main->callback.process_pipe(void_main);
      }
    }

    if (F_status_is_error_not(main->setting.state.status)) {
      if (main->setting.flag & (fss_write_main_flag_object_e | fss_write_main_flag_content_e | fss_write_main_flag_object_open_e | fss_write_main_flag_content_next_e | fss_write_main_flag_content_end_e)) {
        if (main->callback.process_normal) {
          main->callback.process_normal(void_main);
        }
      }
    }

    if ((main->setting.flag & fss_write_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }
  }
#endif // _di_fss_write_main_

#ifndef _di_fss_write_process_normal_
  void fss_write_process_normal(void * const void_main) {

    if (!void_main) return;

    fss_write_process_normal_data(
      (fss_write_main_t *) void_main,
      (((fss_write_main_t *) void_main)->setting.flag & fss_write_main_flag_object_e)
        ? ((fss_write_main_t *) void_main)->setting.objects.used
        : ((fss_write_main_t *) void_main)->setting.contentss.used
    );
  }
#endif // _di_fss_write_process_normal_

#ifndef _di_fss_write_process_normal_data_
  void fss_write_process_normal_data(void * const void_main, const f_number_unsigned_t length) {

    if (!void_main) return;

    fss_write_main_t * const main = (fss_write_main_t *) void_main;

    main->setting.ignores = 0;
    main->setting.object = 0;
    main->setting.content = 0;
    main->setting.contents = 0;

    if (length) {
      for (f_number_unsigned_t i = 0; i < length; ++i) {

        // @todo replace all signal checks with forked main process that independently checks and assigns main->program.signal_received.
        if (!((++main->program.signal_check) % fss_write_signal_check_d)) {
          if (fll_program_standard_signal_received(&main->program)) {
            main->setting.state.status = F_status_set_error(F_interrupt);

            return;
          }

          main->program.signal_check = 0;
        }

        if (main->setting.objects.used) {
          main->setting.object = &main->setting.objects.array[i];
        }

        if (main->setting.contentss.used) {
          main->setting.contents = &main->setting.contentss.array[i];
        }

        if (main->setting.ignoress.used) {
          main->setting.ignores = &main->setting.ignoress.array[i];
        }

        main->callback.process_set(void_main);
        if (F_status_is_error(main->setting.state.status)) break;
      } // for
    }
    else {
      if (main->setting.flag & (fss_write_main_flag_object_open_e | fss_write_main_flag_content_next_e | fss_write_main_flag_content_end_e)) {
        main->setting.object = 0;
        main->setting.contents = 0;
        main->setting.ignores = 0;

        main->callback.process_set(void_main);
      }
    }
  }
#endif // _di_fss_write_process_normal_data_

#ifndef _di_fss_write_process_pipe_
  void fss_write_process_pipe(void * const void_main) {

    if (!void_main) return;

    fss_write_main_t * const main = (fss_write_main_t *) void_main;

    if (!main->callback.process_set) return;

    if (main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }

    const f_number_unsigned_t used_objects = main->setting.objects.used;
    const f_number_unsigned_t used_contentss = main->setting.contentss.used;
    const f_number_unsigned_t used_ignoress = main->setting.ignoress.used;

    main->setting.object = &main->setting.objects.array[used_objects];
    main->setting.contents = &main->setting.contentss.array[used_contentss];
    main->setting.ignores = &main->setting.ignoress.array[used_ignoress];

    // 0x0 = nothing printed, 0x1 = something printed, 0x2 = ignore enabled, 0x4 = added Content for Object.
    uint8_t flag = 0;

    // 0x0 = start new object/content set, 0x1 = processing object, 0x2 = processing content, 0x3 = end object/content set.
    uint8_t state = 0;

    // This is processed in a single set, so there is only ever one Object added.
    main->setting.state.status = f_memory_array_increase(main->setting.state.step_small, sizeof(f_string_dynamic_t), (void **) &main->setting.objects.array, &main->setting.objects.used, &main->setting.objects.size);

    if (F_status_is_error(main->setting.state.status)) {
      fss_write_print_error(&main->program.error, macro_fss_write_f(f_memory_array_increase));

      return;
    }

    // This is processed in a single set, so there is only ever one Content added.
    main->setting.state.status = f_memory_array_increase(main->setting.state.step_small, sizeof(f_string_dynamics_t), (void **) &main->setting.contentss.array, &main->setting.contentss.used, &main->setting.contentss.size);

    if (F_status_is_error(main->setting.state.status)) {
      fss_write_print_error(&main->program.error, macro_fss_write_f(f_memory_array_increase));

      return;
    }

    main->setting.state.status = f_memory_array_increase(main->setting.state.step_small, sizeof(f_string_dynamic_t), (void **) &main->setting.contents->array, &main->setting.contents->used, &main->setting.contents->size);

    if (F_status_is_error(main->setting.state.status)) {
      fss_write_print_error(&main->program.error, macro_fss_write_f(f_memory_array_increase));

      return;
    }

    // This is processed in a single set, so there is only ever one Ignores added.
    main->setting.state.status = f_memory_array_increase(main->setting.state.step_small, sizeof(f_ranges_t), (void **) &main->setting.ignoress.array, &main->setting.ignoress.used, &main->setting.ignoress.size);

    if (F_status_is_error(main->setting.state.status)) {
      fss_write_print_error(&main->program.error, macro_fss_write_f(f_memory_array_increase));

      return;
    }

    f_status_t status_pipe = F_okay;

    f_file_t input = f_file_t_initialize;
    input.id = F_type_descriptor_input_d;
    input.size_read = main->setting.state.step_large;

    f_number_unsigned_t total = 0;
    f_range_t range = f_range_t_initialize;

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
        if (status_pipe == F_okay_eof) break;

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
      }

      // Start Object.
      if (!state || state == 0x1) {
        if (!state) {
          main->setting.object->used = 0;

          state = 0x1;
        }

        // Reset the "has Content for Object" flag and associated contents array used length.
        flag &= ~0x4;
        main->setting.contents->used = 0;

        main->setting.state.status = f_memory_array_increase_by(main->setting.block.used, sizeof(f_char_t), (void **) &main->setting.object->string, &main->setting.object->used, &main->setting.object->size);

        if (F_status_is_error(main->setting.state.status)) {
          fss_write_print_error(&main->program.error, macro_fss_write_f(f_memory_array_increase_by));

          break;
        }

        for (; range.start <= range.stop; ++range.start) {

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

        // If the start of Content is not found, then fetch the next block.
        if (state == 0x1) continue;

        // If the end of the current block is reached, fetch the next block.
        if (range.start > range.stop) continue;
      }

      // Start Content.
      if (state == 0x2) {

        // Check to see if the Content supports multiple Content per Object.
        if (flag & 0x4) {
          if (!(main->setting.flag & fss_write_main_flag_content_multiple_e)) {
            main->setting.state.status = F_status_set_error(F_support_not);

            fss_write_print_error_one_content_only(&main->program.error);

            break;
          }

          main->setting.state.status = f_memory_array_increase(main->setting.state.step_small, sizeof(f_string_dynamic_t), (void **) &main->setting.contents->array, &main->setting.contents->used, &main->setting.contents->size);

          if (F_status_is_error(main->setting.state.status)) {
            fss_write_print_error(&main->program.error, macro_fss_write_f(f_memory_array_increase));

            break;
          }
        }

        if (range.start <= range.stop) {
          total = (range.stop - range.start) + 1;
        }
        else {
          total = 0;
        }

        if (total) {
          main->setting.state.status = f_memory_array_increase_by(total, sizeof(f_char_t), (void **) &main->setting.contents->array[main->setting.contents->used].string, &main->setting.contents->array[main->setting.contents->used].used, &main->setting.contents->array[main->setting.contents->used].size);

          if (F_status_is_error(main->setting.state.status)) {
            fss_write_print_error(&main->program.error, macro_fss_write_f(f_memory_array_increase_by));

            break;
          }

          for (; range.start <= range.stop; ++range.start) {

            // Do not handle start/end while inside an ignore set.
            if (!(flag & 0x2)) {
              if (main->setting.block.string[range.start] == fss_write_pipe_content_start_s.string[0]) {
                if (!(main->setting.flag & fss_write_main_flag_content_multiple_e)) {
                  main->setting.state.status = F_status_set_error(F_support_not);

                  fss_write_print_error_one_content_only(&main->program.error);

                  break;
                }
              }

              if (main->setting.block.string[range.start] == fss_write_pipe_content_end_s.string[0]) {
                state = 0x3;
                ++range.start;

                break;
              }
            }

            if (main->setting.block.string[range.start] == fss_write_pipe_content_ignore_s.string[0]) {

              // Ignore is enabled.
              if (flag & 0x2) {
                main->setting.state.status = f_memory_array_increase(main->setting.state.step_small, sizeof(f_range_t), (void **) &main->setting.ignores->array, &main->setting.ignores->used, &main->setting.ignores->size);

                if (F_status_is_error(main->setting.state.status)) {
                  fss_write_print_error(&main->program.error, macro_fss_write_f(f_memory_array_increase));

                  break;
                }

                main->setting.ignores->array[main->setting.ignores->used].start = main->setting.contents->array[main->setting.contents->used].used;
                main->setting.ignores->array[main->setting.ignores->used].stop = range.start;

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
        main->callback.process_set(void_main);
        if (F_status_is_error(main->setting.state.status)) break;

        state = 0;
        flag |= 0x1;

        // Reset all of the used data for next set.
        main->setting.object->used = 0;
        main->setting.contents->used = 0;
        main->setting.ignores->used = 0;

        continue;
      }
    } // for

    // If the pipe ended before finishing, then attempt to wrap up.
    if (F_status_is_error_not(main->setting.state.status) && status_pipe == F_okay_eof && state) {
      main->callback.process_set(void_main);

      flag |= 0x1;
    }

    main->setting.block.used = 0;
    main->setting.buffer.used = 0;
    main->setting.object->used = 0;
    main->setting.contents->used = 0;
    main->setting.ignores->used = 0;
    main->setting.ignoress.used = used_ignoress;
    main->setting.objects.used = used_objects;
    main->setting.contentss.used = used_contentss;

    if (F_status_is_error_not(main->setting.state.status)) {
      main->setting.state.status = (flag & 0x1) ? F_okay : F_data_not;
    }
  }
#endif // _di_fss_write_process_pipe_

#ifndef _di_fss_write_process_set_
  void fss_write_process_set(void * const void_main) {

    if (!void_main) return;

    fss_write_main_t * const main = (fss_write_main_t *) void_main;

    main->setting.buffer.used = 0;

    if ((!(main->setting.flag & fss_write_main_flag_partial_e) || (main->setting.flag & fss_write_main_flag_partial_e) && (main->setting.flag & fss_write_main_flag_object_e)) && main->setting.object || (main->setting.flag & fss_write_main_flag_object_open_e)) {

      if (main->setting.object) {
        if (main->setting.object->used) {
          main->setting.range.start = 0;
          main->setting.range.stop = main->setting.object->used - 1;
        }
        else {
          main->setting.range.start = 1;
          main->setting.range.stop = 0;
        }
      }

      if (main->callback.process_object) {
        main->callback.process_object(void_main);
        if (F_status_is_error(main->setting.state.status)) return;
      }
    }

    if ((!(main->setting.flag & fss_write_main_flag_partial_e) || (main->setting.flag & fss_write_main_flag_partial_e) && (main->setting.flag & fss_write_main_flag_content_e)) && main->setting.contents || (main->setting.flag & (fss_write_main_flag_content_next_e | fss_write_main_flag_content_end_e))) {

      if (main->callback.process_content) {
        if (main->setting.contents && main->setting.contents->used) {
          for (f_number_unsigned_t i = 0; i < main->setting.contents->used; ++i) {

            if (main->setting.contents->array[i].used) {
              main->setting.range.start = 0;
              main->setting.range.stop = main->setting.contents->array[i].used - 1;
            }
            else {
              main->setting.range.start = 1;
              main->setting.range.stop = 0;
            }

            main->setting.content = &main->setting.contents->array[i];

            main->callback.process_content(void_main, i + 1 == main->setting.contents->used);
            if (F_status_is_error(main->setting.state.status)) return;
          } // for
        }
        else {
          main->setting.content = 0;

          main->callback.process_content(void_main, F_true);
          if (F_status_is_error(main->setting.state.status)) return;
        }
      }
    }

    if (main->setting.buffer.used) {
      fll_print_dynamic(main->setting.buffer, main->program.output.to);
    }
  }
#endif // _di_fss_write_process_set_

#ifdef __cplusplus
} // extern "C"
#endif
