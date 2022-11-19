#include "fss_embedded_list_read.h"
#include "private-common.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_embedded_list_read_print_object_end_
  void fss_embedded_list_read_print_object_end(fss_embedded_list_read_data_t * const data) {

    if (data->main->parameters.array[fss_embedded_list_read_parameter_pipe_e].result & f_console_result_found_e) {
      f_print_dynamic_raw(fss_embedded_list_read_pipe_content_start_s, data->main->output.to);
    }
    else {
      if (data->main->parameters.array[fss_embedded_list_read_parameter_object_e].result & f_console_result_found_e && (data->main->parameters.array[fss_embedded_list_read_parameter_content_e].result & f_console_result_found_e)) {
        f_print_dynamic_raw(f_fss_embedded_list_open_s, data->main->output.to);
        f_print_dynamic_raw(f_fss_embedded_list_open_end_s, data->main->output.to);
      }
      else {
        f_print_dynamic_raw(f_fss_eol_s, data->main->output.to);
      }
    }
  }
#endif // _di_fss_embedded_list_read_print_object_end_

#ifndef _di_fss_embedded_list_read_print_content_ignore_
  void fss_embedded_list_read_print_content_ignore(fss_embedded_list_read_data_t * const data) {

    if (data->main->parameters.array[fss_embedded_list_read_parameter_pipe_e].result & f_console_result_found_e) {
      f_print_dynamic_raw(fss_embedded_list_read_pipe_content_ignore_s, data->main->output.to);
    }
  }
#endif // _di_fss_embedded_list_read_print_content_ignore_

#ifndef _di_fss_embedded_list_read_print_set_end_
  void fss_embedded_list_read_print_set_end(fss_embedded_list_read_data_t * const data) {

    if (data->main->parameters.array[fss_embedded_list_read_parameter_pipe_e].result & f_console_result_found_e) {
      f_print_dynamic_raw(fss_embedded_list_read_pipe_content_end_s, data->main->output.to);
    }
    else {
      if ((data->main->parameters.array[fss_embedded_list_read_parameter_object_e].result & f_console_result_found_e) && (data->main->parameters.array[fss_embedded_list_read_parameter_content_e].result & f_console_result_found_e)) {
        f_print_dynamic_raw(f_fss_embedded_list_close_s, data->main->output.to);
        f_print_dynamic_raw(f_fss_embedded_list_close_end_s, data->main->output.to);
      }
      else {
        f_print_dynamic_raw(f_fss_eol_s, data->main->output.to);
      }
    }
  }
#endif // _di_fss_embedded_list_read_print_set_end_

#ifdef __cplusplus
} // extern "C"
#endif
