#include "fss_basic_read.h"
#include "private-common.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_read_print_at_
  void fss_basic_read_print_at(fll_program_data_t * const main, const f_array_length_t at, const f_fss_delimits_t delimits_object, const f_fss_delimits_t delimits_content, fss_basic_read_data_t * const data) {

    if (at >= data->contents.used) {
      return;
    }

    if ((data->option & fss_basic_read_data_option_object_d) || (data->option & fss_basic_read_data_option_content_d) && (data->contents.array[at].used || (data->option & fss_basic_read_data_option_empty_d))) {
      f_file_stream_lock(main->output.to);

      if (data->option & fss_basic_read_data_option_object_d) {
        if (data->option & fss_basic_read_data_option_trim_d) {
          if (data->option & fss_basic_read_data_option_original_d) {
            if (data->quotes.array[at]) {
              f_print_dynamic_raw(data->quotes.array[at] == f_fss_quote_type_single_e ? f_fss_quote_single_s : f_fss_quote_double_s, main->output.to);
            }

            fl_print_trim_dynamic_partial(data->buffer, data->objects.array[at], main->output.to);

            if (data->quotes.array[at]) {
              f_print_dynamic_raw(data->quotes.array[at] == f_fss_quote_type_single_e ? f_fss_quote_single_s : f_fss_quote_double_s, main->output.to);
            }
          }
          else {
            fl_print_trim_except_dynamic_partial(data->buffer, data->objects.array[at], delimits_object, main->output.to);
          }
        }
        else {
          if (data->option & fss_basic_read_data_option_original_d) {
            if (data->quotes.array[at]) {
              f_print_dynamic_raw(data->quotes.array[at] == f_fss_quote_type_single_e ? f_fss_quote_single_s : f_fss_quote_double_s, main->output.to);
            }

            f_print_dynamic_partial(data->buffer, data->objects.array[at], main->output.to);

            if (data->quotes.array[at]) {
              f_print_dynamic_raw(data->quotes.array[at] == f_fss_quote_type_single_e ? f_fss_quote_single_s : f_fss_quote_double_s, main->output.to);
            }
          }
          else {
            f_print_except_dynamic_partial(data->buffer, data->objects.array[at], delimits_object, main->output.to);
          }
        }

        if (data->option & fss_basic_read_data_option_content_d) {
          fss_basic_read_print_object_end(main);
        }
      }

      if ((data->option & fss_basic_read_data_option_content_d) && data->contents.array[at].used) {
        if (data->option & fss_basic_read_data_option_original_d) {
          f_print_dynamic_partial(data->buffer, data->contents.array[at].array[0], main->output.to);
        }
        else {
          f_print_except_dynamic_partial(data->buffer, data->contents.array[at].array[0], delimits_content, main->output.to);
        }
      }

      fss_basic_read_print_set_end(main);

      f_file_stream_unlock(main->output.to);
    }
  }
#endif // _di_fss_basic_read_print_at_

#ifndef _di_fss_basic_read_print_object_end_
  void fss_basic_read_print_object_end(fll_program_data_t * const main) {

    if (main->parameters.array[fss_basic_read_parameter_pipe_e].result == f_console_result_found_e) {
      f_print_dynamic_raw(fss_basic_read_pipe_content_start_s, main->output.to);
    }
    else {
      f_print_dynamic_raw(f_fss_space_s, main->output.to);
    }
  }
#endif // _di_fss_basic_read_print_object_end_

#ifndef _di_fss_basic_read_print_one_
  void fss_basic_read_print_one(fll_program_data_t * const main) {

    f_print_dynamic_raw(f_string_ascii_1_s, main->output.to);
    f_print_dynamic_raw(f_string_eol_s, main->output.to);
  }
#endif // _di_fss_basic_read_print_one_

#ifndef _di_fss_basic_read_print_set_end_
  void fss_basic_read_print_set_end(fll_program_data_t * const main) {

    if (main->parameters.array[fss_basic_read_parameter_pipe_e].result == f_console_result_found_e) {
      f_print_dynamic_raw(fss_basic_read_pipe_content_end_s, main->output.to);
    }
    else {
      f_print_dynamic_raw(f_string_eol_s, main->output.to);
    }
  }
#endif // _di_fss_basic_read_print_set_end_

#ifndef _di_fss_basic_read_print_zero_
  void fss_basic_read_print_zero(fll_program_data_t * const main) {

    f_print_dynamic_raw(f_string_ascii_0_s, main->output.to);
    f_print_dynamic_raw(f_string_eol_s, main->output.to);
  }
#endif // _di_fss_basic_read_print_zero_

#ifdef __cplusplus
} // extern "C"
#endif
