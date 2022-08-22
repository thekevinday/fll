#include "iki_write.h"
#include "private-common.h"
#include "private-write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_process_
  f_status_t iki_write_process(fll_program_data_t * const main, status_code_setting_t * const setting, iki_write_data_t * const data, const f_file_t output, const f_string_static_t object, const f_string_static_t content, f_string_dynamic_t *escaped) {

    if (!object.used) {
      if (data->main->error.verbosity != f_console_verbosity_quiet_e) {
        flockfile(data->main->error.to.stream);

        fl_print_format("%r%[%QThe object is missing, it must not have a length of %]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
        fl_print_format("%[0%]", data->main->error.to.stream, data->main->error.notable, data->main->error.notable);
        fl_print_format("%[.%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

        funlockfile(data->main->error.to.stream);
      }

      return F_status_set_error(F_failure);
    }

    f_status_t status = f_iki_object_is(object);

    if (status == F_false) {
      if (data->main->error.verbosity != f_console_verbosity_quiet_e) {
        flockfile(data->main->error.to.stream);

        fl_print_format("%r%[%QThe object '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
        fl_print_format("%[%Q%]", data->main->error.to.stream, data->main->error.notable, object, data->main->error.notable);
        fl_print_format("%[' is not a valid IKI object.%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

        funlockfile(data->main->error.to.stream);
      }

      return F_status_set_error(F_failure);
    }
    else if (F_status_is_error(status)) {
      fll_error_print(data->main->error, F_status_set_fine(status), "f_iki_object_is", F_true);

      return F_status_set_error(F_failure);
    }

    escaped->used = 0;

    status = fll_iki_content_escape(content, data->quote, escaped);

    if (F_status_is_error(status)) {
      fll_error_print(data->main->error, F_status_set_fine(status), "fll_iki_content_escape", F_true);

      return F_status_set_error(F_failure);
    }

    fl_print_format("%Q%r%r%Q%r", output, object, f_iki_syntax_separator_s, data->quote, *escaped, data->quote);

    return F_none;
  }
#endif // _di_iki_write_process_

#ifdef __cplusplus
} // extern "C"
#endif
