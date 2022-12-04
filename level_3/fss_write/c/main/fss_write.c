#include "fss_write.h"
#include "private-common.h"
#include "private-write.h"

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

#ifndef _di_fss_write_process_set_
  void fss_write_process_set(fll_program_data_t * const main, fss_write_setting_t * const setting, const f_string_static_t * const object, const f_string_static_t * const content) {

    setting->buffer.used = 0;

    if (object) {
      if (object->used) {
        setting->range.start = 0;
        setting->range.stop = object->used - 1;
      }
      else {
        setting->range.start = 1;
        setting->range.stop = 0;
      }

      setting->process_object(main, (void *) setting, object);
      if (F_status_is_error(setting->status)) return;
    }

    if (content) {
      if (content->used) {
        setting->range.start = 0;
        setting->range.stop = content->used - 1;
      }
      else {
        setting->range.start = 1;
        setting->range.stop = 0;
      }

      setting->process_content(main, (void *) setting, content);
      if (F_status_is_error(setting->status)) return;
    }

    if (setting->buffer.used) {
      fss_write_print_line_first_locked(setting, main->message);

      f_file_stream_lock(main->output.to);

      f_print_dynamic(setting->buffer, main->output.to);
      f_print_dynamic_raw(f_string_eol_s, main->output.to);

      f_file_stream_unlock(main->output.to);
    }
  }
#endif // _di_fss_write_process_set_

#ifdef __cplusplus
} // extern "C"
#endif
