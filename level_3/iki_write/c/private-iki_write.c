#include "iki_write.h"
#include "private-iki_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_process_
  f_return_status iki_write_process(const iki_write_data_t data, const f_string_static_t object, const f_string_static_t content, const uint8_t quote, const int output, f_string_dynamic_t *escaped) {

    if (!object.used) {
      if (data.error.verbosity != f_console_verbosity_quiet) {
        fprintf(data.error.to.stream, "%c", f_string_eol[0]);
        fl_color_print(data.error.to.stream, data.context.set.error, "%sThe object is missing, it must not have a length of ", fll_error_print_error);
        fl_color_print(data.error.to.stream, data.context.set.notable, "0");
        fl_color_print(data.error.to.stream, data.context.set.error, ".%c", f_string_eol[0]);
      }

      return F_status_set_error(F_failure);
    }

    f_status_t status = f_iki_object_is(object);

    if (status == F_false) {
      if (data.error.verbosity != f_console_verbosity_quiet) {
        fprintf(data.error.to.stream, "%c", f_string_eol[0]);
        fl_color_print(data.error.to.stream, data.context.set.error, "%sThe object '", fll_error_print_error);

        fl_color_print_code(f_type_error, data.context.notable);
        f_print_dynamic(f_type_error, object);
        fl_color_print_code(f_type_error, data.context.reset);

        fl_color_print(data.error.to.stream, data.context.set.error, "' is not a valid IKI object.%c", f_string_eol[0]);
      }

      return F_status_set_error(F_failure);
    }
    else if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "f_iki_object_is", F_true);
      return F_status_set_error(F_failure);
    }

    escaped->used = 0;

    status = fll_iki_content_escape(content, quote, escaped);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fll_iki_content_escape", F_true);

      f_macro_string_dynamic_t_delete_simple((*escaped));
      return F_status_set_error(F_failure);
    }

    dprintf(output, "%s%c%c%s%c", object.string, f_iki_syntax_separator, quote, escaped->string, quote);

    return F_none;
  }
#endif // _di_iki_write_process_

#ifdef __cplusplus
} // extern "C"
#endif
