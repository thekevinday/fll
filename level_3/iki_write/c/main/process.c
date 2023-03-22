#include "iki_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_process_
  void iki_write_process(fll_program_data_t * const main, iki_write_setting_t * const setting, const f_string_static_t object, const f_string_static_t content) {

    if (!object.used) {
      setting->state.status = F_status_set_error(F_failure);

      fll_program_print_error_missing_variable_not_zero(&main->error, iki_write_object_s);

      return;
    }

    setting->state.status = f_iki_object_is(object);

    if (setting->state.status == F_false) {
      setting->state.status = F_status_set_error(F_failure);

      iki_write_print_error_object_not_valid(setting, main->error, object);

      return;
    }

    if (F_status_is_error(setting->state.status)) {
      iki_write_print_error(setting, main->error, macro_iki_write_f(f_iki_object_is));

      return;
    }

    setting->escaped.used = 0;

    setting->state.status = fll_iki_content_escape(content, setting->quote, &setting->escaped);

    if (F_status_is_error(setting->state.status)) {
      iki_write_print_error(setting, main->error, macro_iki_write_f(fll_iki_content_escape));

      return;
    }

    if (setting->flag & iki_write_main_flag_wrap_e) {
      fl_print_format("%r%Q%r%r%r%Q%r", main->output.to, f_iki_syntax_wrap_open_s, object, f_iki_syntax_wrap_close_s, f_iki_syntax_separator_s, setting->quote, setting->escaped, setting->quote);
    }
    else {
      fl_print_format("%Q%r%r%Q%r", main->output.to, object, f_iki_syntax_separator_s, setting->quote, setting->escaped, setting->quote);
    }
  }
#endif // _di_iki_write_process_

#ifdef __cplusplus
} // extern "C"
#endif
