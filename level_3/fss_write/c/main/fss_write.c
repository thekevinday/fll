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

    if (setting->flag & fss_write_main_flag_help_e) {
      fss_write_print_help(setting, main->message);

      return;
    }

    if (setting->flag & fss_write_main_flag_version_e) {
      fll_program_print_version(main->message, fss_write_program_version_s);

      return;
    }

    setting->escaped.used = 0;

    if (main->pipe & fll_program_data_pipe_input_e) {
      setting->process_pipe(main, setting);
      if (F_status_is_error(setting->status)) return;
    }

    if (setting->flag & (fss_write_main_flag_object_e | fss_write_main_flag_content_e)) {
      setting->process_normal(main, setting);
      if (F_status_is_error(setting->status)) return;
    }

    // Ensure a new line is always put at the end of the program execution, unless in quiet mode.
    fss_write_print_line_last_locked(setting, main->message);
  }
#endif // _di_fss_write_main_

#ifdef __cplusplus
} // extern "C"
#endif
