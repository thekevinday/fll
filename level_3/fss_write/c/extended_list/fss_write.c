#include "fss_write.h"
#include "../main/fss_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_write_extended_list_process_content_
  void fss_write_extended_list_process_content(fll_program_data_t * const main, void * const void_setting, const bool last) {

    fss_write_setting_t * const setting = macro_fss_write_setting(void_setting);

    setting->status = fl_fss_extended_list_content_write(
      *setting->content,
      (setting->flag & fss_write_flag_partial_e)
        ? last
          ? f_fss_complete_none_e
          : f_fss_complete_partial_e
        : f_fss_complete_full_e,
      &setting->prepend,
      setting->ignores,
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
      fss_write_print_error(setting, main->error, "fl_fss_extended_list_content_write");

      return;
    }
  }
#endif // _di_fss_write_extended_list_process_content_

#ifndef _di_fss_write_extended_list_process_help_
  void fss_write_extended_list_process_help(fll_program_data_t * const main, void * const setting) {

    fss_write_extended_list_print_help(macro_fss_write_setting(setting), main->message);
  }
#endif // _di_fss_write_extended_list_process_help_

#ifndef _di_fss_write_extended_list_process_object_
  void fss_write_extended_list_process_object(fll_program_data_t * const main, void * const void_setting) {

    fss_write_setting_t * const setting = macro_fss_write_setting(void_setting);

    setting->status = fl_fss_extended_list_object_write(
      *setting->object,
      (setting->flag & fss_write_flag_partial_e)
        ? (setting->flag & fss_write_flag_trim_e)
          ? f_fss_complete_partial_trim_e
          : f_fss_complete_partial_e
        : (setting->flag & fss_write_flag_trim_e)
          ? f_fss_complete_full_trim_e
          : f_fss_complete_full_e,
      setting->state,
      &setting->range,
      &setting->buffer
    );

    if (F_status_set_fine(macro_fss_write_setting(setting)->status) == F_none_eol) {
      macro_fss_write_setting(setting)->status = F_status_set_error(F_support_not);

      fss_write_print_line_first_locked(macro_fss_write_setting(setting), main->error);
      fss_write_print_error_unsupported_eol(macro_fss_write_setting(setting), main->error);
      fss_write_print_line_last_locked(macro_fss_write_setting(setting), main->error);

      return;
    }

    if (F_status_is_error(macro_fss_write_setting(setting)->status)) {
      fss_write_print_error(macro_fss_write_setting(setting), main->error, "fl_fss_extended_list_object_write");
    }
  }
#endif // _di_fss_write_extended_list_process_object_

#ifdef __cplusplus
} // extern "C"
#endif
