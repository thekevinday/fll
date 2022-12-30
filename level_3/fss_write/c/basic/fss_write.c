#include "fss_write.h"
#include "../main/fss_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_write_basic_process_content_
  void fss_write_basic_process_content(fll_program_data_t * const main, void * const void_setting, const bool last) {

    if (!main || !void_setting) return;

    fss_write_setting_t * const setting = macro_fss_write_setting(void_setting);

    if (setting->content) {
      setting->status = fl_fss_basic_content_write(
        *setting->content,
        (setting->flag & fss_write_flag_partial_e)
          ? f_fss_complete_partial_e
          : f_fss_complete_full_e,
        setting->state,
        &setting->range,
        &setting->buffer
      );

      if (F_status_set_fine(setting->status) == F_none_eol) {
        setting->status = F_status_set_error(F_support_not);

        fss_write_print_line_first_locked(setting, main->error);
        fss_write_print_error_unsupported_eol(setting, main->error);
        fss_write_print_line_last_locked(setting, main->error);

        return;
      }

      if (F_status_is_error(setting->status)) {
        fss_write_print_error(setting, main->error, macro_fss_write_f(fl_fss_basic_content_write));

        return;
      }
    }

    if ((setting->flag & fss_write_flag_partial_e) && !(setting->flag & fss_write_flag_object_e) || !(setting->flag & (fss_write_flag_object_e | fss_write_flag_content_e))) {
      if (setting->flag & fss_write_flag_content_end_e) {
        setting->status = f_string_dynamic_append(f_fss_basic_close_s, &setting->buffer);

        if (F_status_is_error(setting->status)) {
          fss_write_print_error(setting, main->error, macro_fss_write_f(f_string_dynamic_append));
        }
      }
    }
  }
#endif // _di_fss_write_basic_process_content_

#ifndef _di_fss_write_basic_process_help_
  void fss_write_basic_process_help(fll_program_data_t * const main, void * const void_setting) {

    if (!main || !void_setting) return;

    fss_write_basic_print_help(void_setting, main->message);
  }
#endif // _di_fss_write_basic_process_help_

#ifndef _di_fss_write_basic_process_object_
  void fss_write_basic_process_object(fll_program_data_t * const main, void * const void_setting) {

    if (!main || !void_setting) return;

    fss_write_setting_t * const setting = macro_fss_write_setting(void_setting);

    if (setting->object) {
      setting->status = fl_fss_basic_object_write(
        *setting->object,
        setting->quote.used
          ? setting->quote.string[0]
          : f_fss_quote_double_s.string[0],
        (setting->flag & fss_write_flag_partial_e)
          ? (setting->flag & fss_write_flag_trim_e)
            ? f_fss_complete_trim_e
            : f_fss_complete_none_e
          : (setting->flag & fss_write_flag_trim_e)
            ? f_fss_complete_full_trim_e
            : f_fss_complete_full_e,
        setting->state,
        &setting->range,
        &setting->buffer
      );

      if (F_status_set_fine(setting->status) == F_none_eol) {
        setting->status = F_status_set_error(F_support_not);

        fss_write_print_line_first_locked(setting, main->error);
        fss_write_print_error_unsupported_eol(setting, main->error);
        fss_write_print_line_last_locked(setting, main->error);

        return;
      }

      if (F_status_is_error(setting->status)) {
        fss_write_print_error(setting, main->error, macro_fss_write_f(fl_fss_basic_object_write));

        return;
      }
    }

    if ((setting->flag & fss_write_flag_partial_e) && !(setting->flag & fss_write_flag_content_e) || !(setting->flag & (fss_write_flag_object_e | fss_write_flag_content_e))) {
      if (setting->flag & fss_write_flag_object_open_e) {
        setting->status = f_string_dynamic_append(f_fss_basic_open_s, &setting->buffer);

        if (F_status_is_error(setting->status)) {
          fss_write_print_error(setting, main->error, macro_fss_write_f(f_string_dynamic_append));
        }
      }
    }
  }
#endif // _di_fss_write_basic_process_object_

#ifdef __cplusplus
} // extern "C"
#endif