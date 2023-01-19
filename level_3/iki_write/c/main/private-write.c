#include "iki_write.h"
#include "private-common.h"
#include "private-write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_process_
  void iki_write_process(fll_program_data_t * const main, iki_write_setting_t * const setting, const f_string_static_t object, const f_string_static_t content) {

    if (!object.used) {
      setting->status = F_status_set_error(F_failure);

      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        iki_write_print_line_first_locked(setting, main->error);
        fll_program_print_error_missing_variable_not_zero(main->error, iki_write_object_s);
      }

      return;
    }

    setting->status = f_iki_object_is(object);

    if (setting->status == F_false) {
      setting->status = F_status_set_error(F_failure);

      iki_write_print_error_object_not_valid(setting, main->error, object);

      return;
    }

    if (F_status_is_error(setting->status)) {
      iki_write_print_error(setting, main->error, macro_iki_write_f(f_iki_object_is));

      return;
    }

    setting->escaped.used = 0;

    setting->status = fll_iki_content_escape(content, setting->quote, &setting->escaped);

    if (F_status_is_error(setting->status)) {
      iki_write_print_error(setting, main->error, macro_iki_write_f(fll_iki_content_escape));

      return;
    }

    fl_print_format("%Q%r%r%Q%r", main->output.to, object, f_iki_syntax_separator_s, setting->quote, setting->escaped, setting->quote);
  }
#endif // _di_iki_write_process_

#ifdef __cplusplus
} // extern "C"
#endif
