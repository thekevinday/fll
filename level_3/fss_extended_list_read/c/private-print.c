#include "fss_extended_list_read.h"
#include "private-common.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_list_read_print_at_
  void fss_extended_list_read_print_at(fss_extended_list_read_main_t * const main, const f_array_length_t at, const f_fss_delimits_t delimits_object, const f_fss_delimits_t delimits_content, fss_extended_list_read_data_t * const data) {

    if (at >= data->contents.used) {
      return;
    }

    if ((data->option & fss_extended_list_read_data_option_object_d) || ((data->option & fss_extended_list_read_data_option_content_d) && (data->contents.array[at].used && data->contents.array[at].array[0].start <= data->contents.array[at].array[0].stop || (data->option & fss_extended_list_read_data_option_empty_d)))) {
      flockfile(main->output.to.stream);

      if (data->option & fss_extended_list_read_data_option_object_d) {
        if (data->option & fss_extended_list_read_data_option_trim_d) {
          fl_print_trim_except_dynamic_partial(data->buffer, data->objects.array[at], delimits_object, main->output.to.stream);
        }
        else {
          f_print_except_dynamic_partial(data->buffer, data->objects.array[at], delimits_object, main->output.to.stream);
        }

        fss_extended_list_read_print_object_end(main, data);
      }

      if (data->option & fss_extended_list_read_data_option_content_d) {
        if (data->contents.array[at].used && data->contents.array[at].array[0].start <= data->contents.array[at].array[0].stop) {
          if (data->contents.array[at].used && data->contents.array[at].array[0].start <= data->contents.array[at].array[0].stop) {
            fss_extended_list_read_print_content_ignore(main);

            f_print_except_in_dynamic_partial(data->buffer, data->contents.array[at].array[0], delimits_content, data->comments, main->output.to.stream);

            fss_extended_list_read_print_content_ignore(main);
          }
        }
      }

      fss_extended_list_read_print_set_end(main, data);

      funlockfile(main->output.to.stream);
    }
  }
#endif // _di_fss_extended_list_read_print_at_

#ifndef _di_fss_extended_list_read_print_at_object_
  void fss_extended_list_read_print_at_object(fss_extended_list_read_main_t * const main, fss_extended_list_read_data_t * const data, const f_array_length_t at, const f_fss_delimits_t delimits_object) {

    if (at >= data->objects.used) {
      return;
    }

    if (data->option & fss_extended_list_read_data_option_trim_d) {
      fl_print_trim_except_dynamic_partial(data->buffer, data->objects.array[at], delimits_object, main->output.to.stream);
    }
    else {
      f_print_except_dynamic_partial(data->buffer, data->objects.array[at], delimits_object, main->output.to.stream);
    }

    fss_extended_list_read_print_object_end(main, data);
  }
#endif // _di_fss_extended_list_read_print_at_object_

#ifndef _di_fss_extended_list_read_print_content_ignore_
  void fss_extended_list_read_print_content_ignore(fss_extended_list_read_main_t * const main) {

    if (main->parameters[fss_extended_list_read_parameter_pipe_e].result == f_console_result_found_e) {
      f_print_character(fss_extended_list_read_pipe_content_ignore, main->output.to.stream);
    }
  }
#endif // _di_fss_extended_list_read_print_content_ignore_

#ifndef _di_fss_extended_list_read_print_object_end_
  void fss_extended_list_read_print_object_end(fss_extended_list_read_main_t * const main, fss_extended_list_read_data_t * const data) {

    if (main->parameters[fss_extended_list_read_parameter_pipe_e].result == f_console_result_found_e) {
      f_print_character(fss_extended_list_read_pipe_content_start, main->output.to.stream);
    }
    else {
      if ((data->option & fss_extended_list_read_data_option_object_d) && (data->option & fss_extended_list_read_data_option_content_d)) {
        f_print_character(f_fss_extended_list_open_s[0], main->output.to.stream);
        f_print_character(f_fss_extended_list_open_end_s[0], main->output.to.stream);
      }
    }
  }
#endif // _di_fss_extended_list_read_print_object_end_

#ifndef _di_fss_extended_list_read_print_set_end_
  void fss_extended_list_read_print_set_end(fss_extended_list_read_main_t * const main, fss_extended_list_read_data_t * const data) {

    if (main->parameters[fss_extended_list_read_parameter_pipe_e].result == f_console_result_found_e) {
      f_print_character(fss_extended_list_read_pipe_content_end, main->output.to.stream);
    }
    else {
      if (data->option & fss_extended_list_read_data_option_object_d) {
        if (data->option & fss_extended_list_read_data_option_content_d) {
          f_print_character(f_fss_extended_list_close_s[0], main->output.to.stream);
          f_print_character(f_fss_extended_list_close_end_s[0], main->output.to.stream);
        }
        else if (!(data->option & fss_extended_list_read_data_option_content_d)) {
          f_print_character(f_fss_eol_s[0], main->output.to.stream);
        }
      }
    }
  }
#endif // _di_fss_extended_list_read_print_set_end_

#ifndef _di_fss_extended_list_read_print_one_
  void fss_extended_list_read_print_one(fss_extended_list_read_main_t * const main) {

    f_print_character(f_string_ascii_1_s[0], main->output.to.stream);
    f_print_character(f_string_eol_s[0], main->output.to.stream);
  }
#endif // _di_fss_extended_list_read_print_one_

#ifndef _di_fss_extended_list_read_print_zero_
  void fss_extended_list_read_print_zero(fss_extended_list_read_main_t * const main) {

    f_print_character(f_string_ascii_0_s[0], main->output.to.stream);
    f_print_character(f_string_eol_s[0], main->output.to.stream);
  }
#endif // _di_fss_extended_list_read_print_zero_

#ifdef __cplusplus
} // extern "C"
#endif