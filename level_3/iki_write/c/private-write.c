#include "iki_write.h"
#include "private-common.h"
#include "private-write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_process_
  f_status_t iki_write_process(fll_program_data_t * const main, iki_write_setting_t * const setting, const f_string_static_t object, const f_string_static_t content) {

    if (!object.used) {
      fll_program_print_error_missing_variable_not_zero(main->error, iki_write_object_s);

      return F_status_set_error(F_failure);
    }

    f_status_t status = f_iki_object_is(object);

    if (status == F_false) {
      iki_write_print_error_object_not_valid(setting, main->error, object);

      return F_status_set_error(F_failure);
    }

    if (F_status_is_error(status)) {
      fll_error_print(main->error, F_status_set_fine(status), "f_iki_object_is", F_true);

      return F_status_set_error(F_failure);
    }

    setting->escaped.used = 0;

    status = fll_iki_content_escape(content, setting->quote, &setting->escaped);

    if (F_status_is_error(status)) {
      fll_error_print(main->error, F_status_set_fine(status), "fll_iki_content_escape", F_true);

      return F_status_set_error(F_failure);
    }

    fl_print_format("%Q%r%r%Q%r", main->output.to, object, f_iki_syntax_separator_s, setting->quote, setting->escaped, setting->quote);

    return F_none;
  }
#endif // _di_iki_write_process_

#ifdef __cplusplus
} // extern "C"
#endif
