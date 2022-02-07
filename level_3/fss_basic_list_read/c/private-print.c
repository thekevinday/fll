#include "fss_basic_list_read.h"
#include "private-common.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_list_read_print_at_
  void fss_basic_list_read_print_at(fll_program_data_t * const main, const f_array_length_t at, const f_fss_delimits_t delimits_object, const f_fss_delimits_t delimits_content, fss_basic_list_read_data_t * const data) {

    if (at >= data->contents.used) {
      return;
    }

    if ((data->option & fss_basic_list_read_data_option_object_d) || (data->option & fss_basic_list_read_data_option_content_d) && (data->contents.array[at].used || (data->option & fss_basic_list_read_data_option_empty_d))) {
      flockfile(main->output.to.stream);

      if (data->option & fss_basic_list_read_data_option_object_d) {
        if (data->option & fss_basic_list_read_data_option_trim_d) {
          fl_print_trim_except_in_dynamic_partial(data->buffer, data->objects.array[at], delimits_object, data->comments, main->output.to.stream);
        }
        else {
          f_print_except_in_dynamic_partial(data->buffer, data->objects.array[at], delimits_object, data->comments, main->output.to.stream);
        }

        fss_basic_list_read_print_object_end(main);
      }

      if (data->option & fss_basic_list_read_data_option_content_d) {
        if (data->contents.array[at].used) {
          fss_basic_list_read_print_content_ignore(main);

          f_print_except_in_dynamic_partial(data->buffer, data->contents.array[at].array[0], delimits_content, data->comments, main->output.to.stream);

          fss_basic_list_read_print_content_ignore(main);
        }
      }

      fss_basic_list_read_print_set_end(main);

      funlockfile(main->output.to.stream);
    }
  }
#endif // _di_fss_basic_list_read_print_at_

#ifndef _di_fss_basic_list_read_print_at_object_
  void fss_basic_list_read_print_at_object(fll_program_data_t * const main, fss_basic_list_read_data_t * const data, const f_array_length_t at, const f_fss_delimits_t delimits_object) {

    if (at >= data->objects.used) {
      return;
    }

    if (data->option & fss_basic_list_read_data_option_trim_d) {
      fl_print_trim_except_dynamic_partial(data->buffer, data->objects.array[at], delimits_object, main->output.to.stream);
    }
    else {
      f_print_except_dynamic_partial(data->buffer, data->objects.array[at], delimits_object, main->output.to.stream);
    }

    fss_basic_list_read_print_object_end(main);
  }
#endif // _di_fss_basic_list_read_print_at_object_

#ifndef _di_fss_basic_list_read_print_content_ignore_
  void fss_basic_list_read_print_content_ignore(fll_program_data_t * const main) {

    if (main->parameters.array[fss_basic_list_read_parameter_pipe_e].result == f_console_result_found_e) {
      f_print_dynamic_raw(fss_basic_list_read_pipe_content_ignore_s, main->output.to.stream);
    }
  }
#endif // _di_fss_basic_list_read_print_content_ignore_

#ifndef _di_fss_basic_list_read_print_object_end_
  void fss_basic_list_read_print_object_end(fll_program_data_t * const main) {

    if (main->parameters.array[fss_basic_list_read_parameter_pipe_e].result == f_console_result_found_e) {
      f_print_dynamic_raw(fss_basic_list_read_pipe_content_start_s, main->output.to.stream);
    }
    else {
      if (main->parameters.array[fss_basic_list_read_parameter_content_e].result == f_console_result_found_e) {
        f_print_dynamic_raw(f_fss_basic_list_open_s, main->output.to.stream);
        f_print_dynamic_raw(f_fss_basic_list_open_end_s, main->output.to.stream);
      }
      else {
        f_print_dynamic_raw(f_fss_eol_s, main->output.to.stream);
      }
    }
  }
#endif // _di_fss_basic_list_read_print_object_end_

#ifndef _di_fss_basic_list_read_print_set_end_
  void fss_basic_list_read_print_set_end(fll_program_data_t * const main) {

    if (main->parameters.array[fss_basic_list_read_parameter_pipe_e].result == f_console_result_found_e) {
      f_print_dynamic_raw(fss_basic_list_read_pipe_content_end_s, main->output.to.stream);
    }
  }
#endif // _di_fss_basic_list_read_print_set_end_

#ifndef _di_fss_basic_list_read_print_one_
  void fss_basic_list_read_print_one(fll_program_data_t * const main) {

    f_print_dynamic_raw(f_string_ascii_1_s, main->output.to.stream);
    f_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
  }
#endif // _di_fss_basic_list_read_print_one_

#ifndef _di_fss_basic_list_read_print_zero_
  void fss_basic_list_read_print_zero(fll_program_data_t * const main) {

    f_print_dynamic_raw(f_string_ascii_0_s, main->output.to.stream);
    f_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
  }
#endif // _di_fss_basic_list_read_print_zero_

#ifdef __cplusplus
} // extern "C"
#endif
