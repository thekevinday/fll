#include "fss_payload_write.h"
#include "private-common.h"
#include "private-write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_payload_write_main_
  void fss_payload_write_main(fll_program_data_t * const main, fss_payload_write_setting_t * const setting) {

    if (!main || !setting || F_status_is_error(setting->status)) return;

    setting->status = F_none;

    if (setting->flag & fss_payload_write_main_flag_help_e) {
      fss_payload_write_print_help(setting, main->message);

      return;
    }

    if (setting->flag & fss_payload_write_main_flag_version_e) {
      fll_program_print_version(main->message, fss_payload_write_program_version_s);

      return;
    }

    setting->escaped.used = 0;

    if (main->pipe & fll_program_data_pipe_input_e) {
      fss_payload_write_process_pipe(main, setting);
      if (F_status_is_error(setting->status)) return;

      // Print newline character to separate data printed from pipe.
      if (setting->status == F_none) {
        if ((setting->flag & fss_payload_write_main_flag_partial_e) && setting->objects.used) {
          fll_print_dynamic(f_string_eol_s, main->output.to);
        }
        else if (setting->contents.used) {
          fll_print_dynamic(f_fss_payload_header_close_s, main->output.to);
        }
      }
    }

    if (setting->flag & (fss_payload_write_main_flag_object_e | fss_payload_write_main_flag_content_e)) {
      f_string_statics_t *objects = &setting->objects;
      f_string_statics_t *contents = &setting->contents;
      f_string_statics_t *data = &setting->objects;

      if (setting->flag & fss_payload_write_main_flag_partial_e) {
        if (setting->flag & fss_payload_write_main_flag_content_e) {
          data = &setting->contents;
          objects = 0;
        }
        else {
          contents = 0;
        }
      }

      for (f_array_length_t i = 0; i < data->used; ++i) {

        if (!((++main->signal_check) % fss_payload_write_signal_check_d)) {
          if (fll_program_standard_signal_received(main)) {
            setting->status = F_status_set_error(F_interrupt);

            return;
          }

          main->signal_check = 0;
        }

        fss_payload_write_process(main, setting, objects ? &objects->array[i] : 0, contents ? &contents->array[i] : 0);
        if (F_status_is_error(setting->status)) return;
      } // for
    }

    // Ensure a new line is always put at the end of the program execution, unless in quiet mode.
    fss_payload_write_print_line_last_locked(setting, main->message);
  }
#endif // _di_fss_payload_write_main_

#ifdef __cplusplus
} // extern "C"
#endif
