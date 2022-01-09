#include "fss_basic_read.h"
#include "private-common.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_read_print_at_
  void fss_basic_read_print_at(fss_basic_read_main_t * const main, const f_array_length_t at, const f_fss_delimits_t delimits_object, const f_fss_delimits_t delimits_content, fss_basic_read_data_t * const data) {

    if (at >= data->contents.used) {
      return;
    }

    if ((data->option & fss_basic_read_data_option_object_d) || (data->option & fss_basic_read_data_option_content_d) && (data->contents.array[at].used || (data->option & fss_basic_read_data_option_empty_d))) {
      flockfile(main->output.to.stream);

      if (data->option & fss_basic_read_data_option_object_d) {
        if (data->option & fss_basic_read_data_option_trim_d) {
          if (data->option & fss_basic_read_data_option_raw_d) {
            if (data->quotes.array[at]) {
              f_print_character_safely(data->quotes.array[at] == f_fss_quote_type_single_e ? f_fss_quote_single_s[0] : f_fss_quote_double_s[0], main->output.to.stream);
            }

            fl_print_trim_dynamic_partial(data->buffer, data->objects.array[at], main->output.to.stream);

            if (data->quotes.array[at]) {
              f_print_character_safely(data->quotes.array[at] == f_fss_quote_type_single_e ? f_fss_quote_single_s[0] : f_fss_quote_double_s[0], main->output.to.stream);
            }
          }
          else {
            fl_print_trim_except_dynamic_partial(data->buffer, data->objects.array[at], delimits_object, main->output.to.stream);
          }
        }
        else {
          if (data->option & fss_basic_read_data_option_raw_d) {
            if (data->quotes.array[at]) {
              f_print_character_safely(data->quotes.array[at] == f_fss_quote_type_single_e ? f_fss_quote_single_s[0] : f_fss_quote_double_s[0], main->output.to.stream);
            }

            f_print_dynamic_partial(data->buffer, data->objects.array[at], main->output.to.stream);

            if (data->quotes.array[at]) {
              f_print_character_safely(data->quotes.array[at] == f_fss_quote_type_single_e ? f_fss_quote_single_s[0] : f_fss_quote_double_s[0], main->output.to.stream);
            }
          }
          else {
            f_print_except_dynamic_partial(data->buffer, data->objects.array[at], delimits_object, main->output.to.stream);
          }
        }

        if (data->option & fss_basic_read_data_option_content_d) {
          fss_basic_read_print_object_end(main);
        }
      }

      if ((data->option & fss_basic_read_data_option_content_d) && data->contents.array[at].used) {
        if (data->option & fss_basic_read_data_option_raw_d) {
          f_print_dynamic_partial(data->buffer, data->contents.array[at].array[0], main->output.to.stream);
        }
        else {
          f_print_except_dynamic_partial(data->buffer, data->contents.array[at].array[0], delimits_content, main->output.to.stream);
        }
      }

      fss_basic_read_print_set_end(main);

      funlockfile(main->output.to.stream);
    }
  }
#endif // _di_fss_basic_read_print_at_

#ifndef _di_fss_basic_read_print_object_end_
  void fss_basic_read_print_object_end(fss_basic_read_main_t * const main) {

    if (main->parameters[fss_basic_read_parameter_pipe_e].result == f_console_result_found_e) {
      f_print_character(fss_basic_read_pipe_content_start_s, main->output.to.stream);
    }
    else {
      f_print_character(F_fss_space_s[0], main->output.to.stream);
    }
  }
#endif // _di_fss_basic_read_print_object_end_

#ifndef _di_fss_basic_read_print_one_
  void fss_basic_read_print_one(fss_basic_read_main_t * const main) {

    f_print_character(f_string_ascii_1_s[0], main->output.to.stream);
    f_print_character(f_string_eol_s[0], main->output.to.stream);
  }
#endif // _di_fss_basic_read_print_one_

#ifndef _di_fss_basic_read_print_set_end_
  void fss_basic_read_print_set_end(fss_basic_read_main_t * const main) {

    if (main->parameters[fss_basic_read_parameter_pipe_e].result == f_console_result_found_e) {
      f_print_character(fss_basic_read_pipe_content_end_s, main->output.to.stream);
    }
    else {
      f_print_character(f_string_eol_s[0], main->output.to.stream);
    }
  }
#endif // _di_fss_basic_read_print_set_end_

#ifndef _di_fss_basic_read_print_zero_
  void fss_basic_read_print_zero(fss_basic_read_main_t * const main) {

    f_print_character(f_string_ascii_0_s[0], main->output.to.stream);
    f_print_character(f_string_eol_s[0], main->output.to.stream);
  }
#endif // _di_fss_basic_read_print_zero_

#ifdef __cplusplus
} // extern "C"
#endif
