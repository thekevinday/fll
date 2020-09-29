#include "fss_basic_write.h"
#include "private-fss_basic_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_write_error_parameter_same_times_print_
  void fss_basic_write_error_parameter_same_times_print(const fss_basic_write_data_t data) {

    if (data.error.verbosity == f_console_verbosity_quiet) {
      return;
    }

    fl_color_print(data.error.to.stream, data.context.set.error, "%sMust specify both the '", fll_error_print_error);
    fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_write_long_object);
    fl_color_print(data.error.to.stream, data.context.set.error, "' parameter and the '");
    fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_write_long_content);
    fl_color_print(data.error.to.stream, data.context.set.error, "' parameter the same number of times when not specifying the ");
    fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_write_long_partial);
    fl_color_print(data.error.to.stream, data.context.set.error, "' parameter.%c", f_string_eol[0]);
  }
#endif // _di_fss_basic_write_error_parameter_same_times_print_

#ifndef _di_fss_basic_write_error_parameter_value_missing_print_
  void fss_basic_write_error_parameter_value_missing_print(const fss_basic_write_data_t data, const f_string_t symbol, const f_string_t parameter) {

    if (data.error.verbosity == f_console_verbosity_quiet) {
      return;
    }

    fl_color_print(data.error.to.stream, data.context.set.error, "%sThe parameter '", fll_error_print_error);
    fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", symbol, parameter);
    fl_color_print(data.error.to.stream, data.context.set.error, "' was specified, but no value was given.%c", f_string_eol[0]);
  }
#endif // _di_fss_basic_write_error_parameter_value_missing_print_

#ifndef _di_fss_basic_write_process_
  f_return_status fss_basic_write_process(const fss_basic_write_data_t data, const f_file_t output, const f_string_static_t object, const f_string_static_t content, const f_fss_quoted_t quoted, f_string_dynamic_t *buffer) {
    f_status_t status = F_none;

    f_string_range_t range = f_macro_string_range_t_initialize(object.used);

    buffer->used = 0;

    if (data.parameters[fss_basic_write_parameter_object].result == f_console_result_found) {

      status = fl_fss_basic_object_write(object, quoted, &range, buffer);

      if (F_status_is_error(status) || status == F_data_not_stop || status == F_data_not_eos) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_fss_basic_object_write", F_true);
        return F_status_set_error(status);
      }
    }

    if (data.parameters[fss_basic_write_parameter_content].result == f_console_result_found) {
      if (content.used) {
        range.start = 0;
        range.stop = content.used;
      }
      else {
        range.start = 1;
        range.stop = 0;
      }

      status = fl_fss_basic_content_write(content, &range, buffer);

      if (F_status_is_error(status) || data.parameters[fss_basic_write_parameter_content].result == f_console_result_found) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_fss_basic_content_write", F_true);
        return F_status_set_error(status);
      }
    }

    status = fl_string_dynamic_terminate(buffer);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate", F_true);
      return F_status_set_error(status);
    }

    f_print_dynamic(output.stream, *buffer);

    return status;
  }
#endif // _di_fss_basic_write_process_

#ifdef __cplusplus
} // extern "C"
#endif
