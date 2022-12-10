#include "fss_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_write_main_
  void fss_write_main(fll_program_data_t * const main, fss_write_setting_t * const setting) {

    if (!main || !setting || F_status_is_error(setting->status)) return;

    setting->status = F_none;

    if (setting->flag & fss_write_flag_help_e) {
      setting->process_help(main, (void *) setting);

      return;
    }

    if (setting->flag & fss_write_flag_version_e) {
      fll_program_print_version(main->message, fss_write_program_version_s);

      return;
    }

    setting->escaped.used = 0;

    if (main->pipe & fll_program_data_pipe_input_e) {
      setting->process_pipe(main, setting);
      if (F_status_is_error(setting->status)) return;
    }

    if (setting->flag & (fss_write_flag_object_e | fss_write_flag_content_e)) {
      setting->process_normal(main, setting);
      if (F_status_is_error(setting->status)) return;
    }

    // Ensure a new line is always put at the end of the program execution.
    fss_write_print_line_last_locked(setting, main->message);
  }
#endif // _di_fss_write_main_

#ifndef _di_fss_write_process_normal_
  void fss_write_process_normal(fll_program_data_t * const main, void * const setting) {

    fss_write_process_normal_data(
      main,
      macro_fss_write_setting(setting),
      (macro_fss_write_setting(setting)->flag & fss_write_flag_object_e)
        ? macro_fss_write_setting(setting)->objects.used
        : macro_fss_write_setting(setting)->contentss.used
    );
  }
#endif // _di_fss_write_process_normal_

#ifndef _di_fss_write_process_normal_data_
  void fss_write_process_normal_data(fll_program_data_t * const main, fss_write_setting_t * const setting, const f_array_length_t length) {

    setting->ignores = 0;
    setting->object = 0;
    setting->content = 0;
    setting->contents = 0;

    for (f_array_length_t i = 0; i < length; ++i) {

      // @todo replace all signal checks with forked main process that independently checks and assigns main->signal_received.
      if (!((++main->signal_check) % fss_write_signal_check_d)) {
        if (fll_program_standard_signal_received(main)) {
          setting->status = F_status_set_error(F_interrupt);

          return;
        }

        main->signal_check = 0;
      }

      if (setting->objects.used) {
        setting->object = &setting->objects.array[i];
      }

      if (setting->contentss.used) {
        setting->contents = &setting->contentss.array[i];
      }

      if (setting->ignoress.used) {
        setting->ignores = &setting->ignoress.array[i];
      }

      setting->process_set(main, setting);
      if (F_status_is_error(setting->status)) break;
    } // for
  }
#endif // _di_fss_write_process_normal_data_

#ifndef _di_fss_write_process_pipe_
  void fss_write_process_pipe(fll_program_data_t * const main, void * const void_setting) {

    fss_write_setting_t * const setting = macro_fss_write_setting(void_setting);

    f_status_t status_pipe = F_none;
    f_file_t input = f_file_t_initialize;
    input.id = F_type_descriptor_input_d;
    input.size_read = setting->state.step_large;

    f_array_length_t total = 0;
    f_array_length_t length = 0;
    f_array_length_t ignore = 0;
    f_string_range_t range = f_string_range_t_initialize;

    const f_array_length_t used_objects = setting->objects.used;
    const f_array_length_t used_contentss = setting->contentss.used;
    const f_array_length_t used_ignoress = setting->ignoress.used;

    setting->object = &setting->objects.array[used_objects];
    setting->contents = &setting->contentss.array[used_contentss];
    setting->ignores = &setting->ignoress.array[used_ignoress];

    // 0x0 = nothing printed, 0x1 = something printed, 0x2 = ignore enabled, 0x4 = added Content for Object.
    uint8_t flag = 0;

    // 0x0 = start new object/content set, 0x1 = processing object, 0x2 = processing content, 0x3 = end object/content set.
    uint8_t state = 0;

    // This is processed in a single set, so there is only ever one Object added.
    setting->status = f_string_dynamics_increase(setting->state.step_small, &setting->objects);

    if (F_status_is_error(setting->status)) {
      fss_write_print_error(setting, main->error, "f_string_dynamics_increase");

      return;
    }

    // This is processed in a single set, so there is only ever one Content added.
    setting->status = f_string_dynamicss_increase(setting->state.step_small, &setting->contentss);

    if (F_status_is_error(setting->status)) {
      fss_write_print_error(setting, main->error, "f_string_dynamicss_increase");

      return;
    }

    setting->status = f_string_dynamics_increase(setting->state.step_small, setting->contents);

    if (F_status_is_error(setting->status)) {
      fss_write_print_error(setting, main->error, "f_string_dynamics_increase");

      return;
    }

    // This is processed in a single set, so there is only ever one Ignores added.
    setting->status = f_string_rangess_increase(setting->state.step_small, &setting->ignoress);

    if (F_status_is_error(setting->status)) {
      fss_write_print_error(setting, main->error, "f_string_rangess_increase");

      return;
    }

    // Reset all of the used data before starting the loop.
    setting->object->used = 0;
    setting->contents->used = 0;
    setting->ignores->used = 0;

    for (;;) {

      if (!((++main->signal_check) % fss_write_signal_check_d)) {
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
          fss_write_print_error(setting, main->error, "f_file_read_block");

          status_pipe = F_status_set_error(F_pipe);

          break;
        }

        if (!setting->block.used) break;

        range.start = 0;
        range.stop = setting->block.used - 1;
      }

      // Start Object.
      if (!state || state == 0x1) {
        if (!state) {
          setting->object->used = 0;

          state = 0x1;
        }

        // Reset the "has Content for Object" flag and associated contents array used length.
        flag -= flag | 0x4;
        setting->contents->used = 0;

        setting->status = f_string_dynamic_increase_by(setting->block.used, setting->object);

        if (F_status_is_error(setting->status)) {
          fss_write_print_error(setting, main->error, "f_string_dynamic_increase_by");

          break;
        }

        for (; range.start <= range.stop; ++range.start) {

          // Do not handle start/end while inside an ignore set.
          if (!(flag & 0x2)) {
            if (setting->block.string[range.start] == fss_write_pipe_content_start_s.string[0]) {
              state = 0x2;
              ++range.start;

              break;
            }

            if (setting->block.string[range.start] == fss_write_pipe_content_end_s.string[0]) {
              state = 0x3;
              ++range.start;

              break;
            }
          }

          // There currently is no support for "ignore" in Objects, but the Ignore should still be processed.
          if (setting->block.string[range.start] == fss_write_pipe_content_ignore_s.string[0]) {

            // Ignore is enabled.
            if (flag & 0x2) {
              flag -= 0x2;
            }
            else {
              flag |= 0x2;
            }

            continue;
          }

          setting->object->string[setting->object->used++] = setting->block.string[range.start];
        } // for

        if (F_status_is_error(setting->status)) break;

        // If the start of Content is not found, then fetch the next block.
        if (state == 0x1) continue;

        // If the end of the current block is reached, fetch the next block.
        if (range.start > range.stop) continue;
      }

      // Start Content.
      if (state == 0x2) {

        // Check to see if the Content supports multiple Content per Object.
        if (flag & 0x4) {
          if (!(setting->flag & fss_write_flag_content_multiple_e)) {
            setting->status = F_status_set_error(F_support_not);

            fss_write_print_error_one_content_only(setting, main->error);

            break;
          }

          setting->status = f_string_dynamics_increase(setting->state.step_small, setting->contents);

          if (F_status_is_error(setting->status)) {
            fss_write_print_error(setting, main->error, "f_string_dynamics_increase");

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
          setting->status = f_string_dynamic_increase_by(total, &setting->contents->array[setting->contents->used]);

          if (F_status_is_error(setting->status)) {
            fss_write_print_error(setting, main->error, "f_string_dynamic_increase_by");

            break;
          }

          for (; range.start <= range.stop; ++range.start) {

            // Do not handle start/end while inside an ignore set.
            if (!(flag & 0x2)) {
              if (setting->block.string[range.start] == fss_write_pipe_content_start_s.string[0]) {
                if (!(setting->flag & fss_write_flag_content_multiple_e)) {
                  setting->status = F_status_set_error(F_support_not);

                  fss_write_print_error_one_content_only(setting, main->error);

                  break;
                }
              }

              if (setting->block.string[range.start] == fss_write_pipe_content_end_s.string[0]) {
                state = 0x3;
                ++range.start;

                break;
              }
            }

            if (setting->block.string[range.start] == fss_write_pipe_content_ignore_s.string[0]) {

              // Ignore is enabled.
              if (flag & 0x2) {
                setting->status = f_string_ranges_increase(setting->state.step_small, setting->ignores);

                if (F_status_is_error(setting->status)) {
                  fss_write_print_error(setting, main->error, "f_string_ranges_increase");

                  break;
                }

                setting->ignores->array[setting->ignores->used].start = setting->contents->array[setting->contents->used].used;
                setting->ignores->array[setting->ignores->used].stop = range.start;

                flag -= 0x2;
              }
              else {
                ignore = setting->contents->array[setting->contents->used].used;

                flag |= 0x2;
              }

              continue;
            }

            setting->contents->array[setting->contents->used].string[setting->contents->array[setting->contents->used].used++] = setting->block.string[range.start];
          } // for

          if (F_status_is_error(setting->status)) break;

          ++setting->contents->used;
          flag |= 0x4;
        }
        else {
          state = 0x3;
        }
      }

      // End Object or Content set.
      if (state == 0x3) {
        setting->process_set(main, void_setting);
        if (F_status_is_error(setting->status)) break;

        state = 0;
        flag |= 0x1;

        // Reset all of the used data for next set.
        setting->object->used = 0;
        setting->contents->used = 0;
        setting->ignores->used = 0;

        continue;
      }
    } // for

    // If the pipe ended before finishing, then attempt to wrap up.
    if (F_status_is_error_not(setting->status) && status_pipe == F_none_eof && state) {
      setting->process_set(main, void_setting);

      flag |= 0x1;
    }

    setting->block.used = 0;
    setting->buffer.used = 0;
    setting->object->used = 0;
    setting->contents->used = 0;
    setting->ignores->used = 0;
    setting->ignoress.used = used_ignoress;
    setting->objects.used = used_objects;
    setting->contentss.used = used_contentss;

    if (F_status_is_error_not(setting->status)) {
      setting->status = (flag & 0x1) ? F_none : F_data_not;
    }
  }
#endif // _di_fss_write_process_pipe_

#ifndef _di_fss_write_process_set_
  void fss_write_process_set(fll_program_data_t * const main, void * const void_setting) {

    fss_write_setting_t * const setting = macro_fss_write_setting(void_setting);

    setting->buffer.used = 0;

    if ((!(setting->flag & fss_write_flag_partial_e) || (setting->flag & fss_write_flag_partial_e) && (setting->flag & fss_write_flag_object_e)) && setting->object) {
      if (setting->object->used) {
        setting->range.start = 0;
        setting->range.stop = setting->object->used - 1;
      }
      else {
        setting->range.start = 1;
        setting->range.stop = 0;
      }

      setting->process_object(main, void_setting);
      if (F_status_is_error(setting->status)) return;
    }

    if ((!(setting->flag & fss_write_flag_partial_e) || (setting->flag & fss_write_flag_partial_e) && (setting->flag & fss_write_flag_content_e)) && setting->contents) {
      for (f_array_length_t i = 0; i < setting->contents->used; ++i) {

        if (setting->contents->array[i].used) {
          setting->range.start = 0;
          setting->range.stop = setting->contents->array[i].used - 1;
        }
        else {
          setting->range.start = 1;
          setting->range.stop = 0;
        }

        setting->content = &setting->contents->array[i];

        setting->process_content(main, void_setting, i + 1 == setting->contents->used);
        if (F_status_is_error(setting->status)) return;
      } // for
    }

    if (setting->buffer.used) {
      fll_print_dynamic(setting->buffer, main->output.to);
    }
  }
#endif // _di_fss_write_process_set_

#ifdef __cplusplus
} // extern "C"
#endif
