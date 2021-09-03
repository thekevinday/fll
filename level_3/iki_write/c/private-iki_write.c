#include "iki_write.h"
#include "private-common.h"
#include "private-iki_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_process_
  f_status_t iki_write_process(const iki_write_main_t main, const f_file_t output, const f_string_static_t object, const f_string_static_t content, const uint8_t quote, f_string_dynamic_t *escaped) {

    if (!object.used) {
      if (main.error.verbosity != f_console_verbosity_quiet) {
        flockfile(main.error.to.stream);

        fl_print_format("%c%[%sThe object is missing, it must not have a length of %]", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.prefix, main.error.context);
        fl_print_format("%[0%]", main.error.to.stream, main.error.notable, main.error.notable);
        fl_print_format("%[.%]%c", main.error.to.stream, main.error.context, main.error.context, f_string_eol_s[0]);

        funlockfile(main.error.to.stream);
      }

      return F_status_set_error(F_failure);
    }

    f_status_t status = f_iki_object_is(object);

    if (status == F_false) {
      if (main.error.verbosity != f_console_verbosity_quiet) {
        flockfile(main.error.to.stream);

        fl_print_format("%c%[%sThe object '%]", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.prefix, main.error.context);
        fl_print_format("%[%Q%]", main.error.to.stream, main.error.notable, object, main.error.notable);
        fl_print_format("%[' is not a valid IKI object.%]%c", main.error.to.stream, main.error.context, main.error.context, f_string_eol_s[0]);

        funlockfile(main.error.to.stream);
      }

      return F_status_set_error(F_failure);
    }
    else if (F_status_is_error(status)) {
      fll_error_print(main.error, F_status_set_fine(status), "f_iki_object_is", F_true);
      return F_status_set_error(F_failure);
    }

    escaped->used = 0;

    status = fll_iki_content_escape(content, quote, escaped);

    if (F_status_is_error(status)) {
      fll_error_print(main.error, F_status_set_fine(status), "fll_iki_content_escape", F_true);

      macro_f_string_dynamic_t_delete_simple((*escaped));
      return F_status_set_error(F_failure);
    }

    fl_print_format("%Q%c%c%Q%c", output.stream, object, f_iki_syntax_separator, quote, *escaped, quote);

    return F_none;
  }
#endif // _di_iki_write_process_

#ifdef __cplusplus
} // extern "C"
#endif
