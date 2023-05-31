#include "fss_payload_read.h"
#include "private-common.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_payload_read_print_at_
  void fss_payload_read_print_at(fll_program_data_t * const main, const bool is_payload, const f_array_length_t at, const f_fss_delimits_t delimits_object, const f_fss_delimits_t delimits_content, fss_payload_read_data_t * const data) {

    if (at >= data->contents.used) {
      return;
    }

    if ((data->option & fss_payload_read_data_option_object_d) || (data->option & fss_payload_read_data_option_content_d) && (data->contents.array[at].used || (data->option & fss_payload_read_data_option_empty_d))) {
      flockfile(main->output.to.stream);

      if (data->option & fss_payload_read_data_option_object_d) {
        if (data->option & fss_payload_read_data_option_trim_d) {
          fl_print_trim_except_in_dynamic_partial(data->buffer, data->objects.array[at], delimits_object, data->comments, main->output.to.stream);
        }
        else {
          f_print_except_in_dynamic_partial(data->buffer, data->objects.array[at], delimits_object, data->comments, main->output.to.stream);
        }

        fss_payload_read_print_object_end(main);
      }

      if (data->option & fss_payload_read_data_option_content_d) {
        if (data->contents.array[at].used) {
          if (!is_payload) {
            fss_payload_read_print_content_ignore(main);
          }

          if (is_payload) {
            f_print_dynamic_partial_raw(data->buffer, data->contents.array[at].array[0], main->output.to.stream);
          }
          else {
            f_print_except_in_dynamic_partial(data->buffer, data->contents.array[at].array[0], delimits_content, data->comments, main->output.to.stream);
          }

          if (!is_payload) {
            fss_payload_read_print_content_ignore(main);
          }
        }
      }

      if (!is_payload) {
        fss_payload_read_print_set_end(main);
      }

      funlockfile(main->output.to.stream);
    }
  }
#endif // _di_fss_payload_read_print_at_

#ifndef _di_fss_payload_read_print_at_extended_
  void fss_payload_read_print_at_extended(fll_program_data_t * const main, const f_array_length_t at, const f_fss_delimits_t delimits_object, const f_fss_delimits_t delimits_content, fss_payload_read_data_t * const data) {

    if (at >= data->contents_header.used) {
      return;
    }

    flockfile(main->output.to.stream);

    if ((data->option & fss_payload_read_data_option_object_d) || (data->option & fss_payload_read_data_option_content_d) && (data->contents_header.array[at].used || (data->option & fss_payload_read_data_option_empty_d))) {
      if (data->option & fss_payload_read_data_option_object_d) {
        if (data->option & fss_payload_read_data_option_trim_d) {
          if ((data->option & fss_payload_read_data_option_original_d) && data->quotes_object_header.array[at]) {
            f_print_dynamic_raw(
              data->quotes_object_header.array[at] == f_fss_quote_type_single_e
                ? f_fss_quote_single_s
                : data->quotes_object_header.array[at] == f_fss_quote_type_double_e
                  ? f_fss_quote_double_s
                  : f_fss_quote_backtick_s,
              main->output.to.stream
            );
          }

          fl_print_trim_except_dynamic_partial(data->buffer, data->objects_header.array[at], delimits_object, main->output.to.stream);

          if ((data->option & fss_payload_read_data_option_original_d) && data->quotes_object_header.array[at]) {
            f_print_dynamic_raw(
              data->quotes_object_header.array[at] == f_fss_quote_type_single_e
                ? f_fss_quote_single_s
                : data->quotes_object_header.array[at] == f_fss_quote_type_double_e
                  ? f_fss_quote_double_s
                  : f_fss_quote_backtick_s,
              main->output.to.stream
            );
          }
        }
        else {
          if ((data->option & fss_payload_read_data_option_original_d) && data->quotes_object_header.array[at]) {
            f_print_dynamic_raw(
              data->quotes_object_header.array[at] == f_fss_quote_type_single_e
                ? f_fss_quote_single_s
                : data->quotes_object_header.array[at] == f_fss_quote_type_double_e
                  ? f_fss_quote_double_s
                  : f_fss_quote_backtick_s,
              main->output.to.stream
            );
          }

          f_print_except_dynamic_partial(data->buffer, data->objects_header.array[at], delimits_object, main->output.to.stream);

          if ((data->option & fss_payload_read_data_option_original_d) && data->quotes_object_header.array[at]) {
            f_print_dynamic_raw(
              data->quotes_object_header.array[at] == f_fss_quote_type_single_e
                ? f_fss_quote_single_s
                : data->quotes_object_header.array[at] == f_fss_quote_type_double_e
                  ? f_fss_quote_double_s
                  : f_fss_quote_backtick_s,
              main->output.to.stream
            );
          }
        }

        if (data->option & fss_payload_read_data_option_content_d) {
          fss_payload_read_print_object_end_extended(main);
        }
      }

      bool content_printed = F_false;

      if ((data->option & fss_payload_read_data_option_content_d) && data->contents_header.array[at].used) {
        if (data->option & fss_payload_read_data_option_select_d) {
          if (data->select < data->contents_header.array[at].used) {
            content_printed = F_true;

            if ((data->option & fss_payload_read_data_option_original_d) && data->quotes_content_header.array[at].array[data->select]) {
              f_print_dynamic_raw(
                data->quotes_content_header.array[at].array[data->select] == f_fss_quote_type_single_e
                  ? f_fss_quote_single_s
                  : data->quotes_content_header.array[at].array[data->select] == f_fss_quote_type_double_e
                    ? f_fss_quote_double_s
                    : f_fss_quote_backtick_s,
                main->output.to.stream
              );
            }

            f_print_except_dynamic_partial(data->buffer, data->contents_header.array[at].array[data->select], delimits_content, main->output.to.stream);

            if ((data->option & fss_payload_read_data_option_original_d) && data->quotes_content_header.array[at].array[data->select]) {
              f_print_dynamic_raw(
                data->quotes_content_header.array[at].array[data->select] == f_fss_quote_type_single_e
                  ? f_fss_quote_single_s
                  : data->quotes_content_header.array[at].array[data->select] == f_fss_quote_type_double_e
                    ? f_fss_quote_double_s
                    : f_fss_quote_backtick_s,
                main->output.to.stream
              );
            }
          }
        }
        else {
          for (f_array_length_t i = 0; i < data->contents_header.array[at].used; ++i) {

            if (data->contents_header.array[at].array[i].start > data->contents_header.array[at].array[i].stop) {
              continue;
            }

            content_printed = F_true;

            if ((data->option & fss_payload_read_data_option_original_d) && data->quotes_content_header.array[at].array[i]) {
              f_print_dynamic_raw(
                data->quotes_content_header.array[at].array[i] == f_fss_quote_type_single_e
                  ? f_fss_quote_single_s
                  : data->quotes_content_header.array[at].array[i] == f_fss_quote_type_double_e
                    ? f_fss_quote_double_s
                    : f_fss_quote_backtick_s,
                main->output.to.stream
              );
            }

            f_print_except_dynamic_partial(data->buffer, data->contents_header.array[at].array[i], delimits_content, main->output.to.stream);

            if ((data->option & fss_payload_read_data_option_original_d) && data->quotes_content_header.array[at].array[i]) {
              f_print_dynamic_raw(
                data->quotes_content_header.array[at].array[i] == f_fss_quote_type_single_e
                  ? f_fss_quote_single_s
                  : data->quotes_content_header.array[at].array[i] == f_fss_quote_type_double_e
                    ? f_fss_quote_double_s
                    : f_fss_quote_backtick_s,
                main->output.to.stream
              );
            }

            if (i + 1 < data->contents_header.array[at].used && data->contents_header.array[at].array[i + 1].start <= data->contents_header.array[at].array[i + 1].stop) {
              fss_payload_read_print_content_end_extended(main);
            }
          } // for
        }
      }

      if ((data->option & fss_payload_read_data_option_object_d) || (data->option & fss_payload_read_data_option_content_d) && (content_printed || (data->option & fss_payload_read_data_option_empty_d))) {
        fss_payload_read_print_set_end_extended(main);
      }

      funlockfile(main->output.to.stream);
    }
  }
#endif // _di_fss_payload_read_print_at_extended_

#ifndef _di_fss_payload_read_print_at_object_
  void fss_payload_read_print_at_object(fll_program_data_t * const main, fss_payload_read_data_t * const data, const f_array_length_t at, const f_fss_delimits_t delimits_object) {

    if (at >= data->objects.used) {
      return;
    }

    if (data->option & fss_payload_read_data_option_trim_d) {
      fl_print_trim_except_dynamic_partial(data->buffer, data->objects.array[at], delimits_object, main->output.to.stream);
    }
    else {
      f_print_except_dynamic_partial(data->buffer, data->objects.array[at], delimits_object, main->output.to.stream);
    }

    fss_payload_read_print_object_end(main);
  }
#endif // _di_fss_payload_read_print_at_object_

#ifndef _di_fss_payload_read_print_at_total_exteded_
  f_status_t fss_payload_read_print_at_total_extended(fll_program_data_t * const main, const f_array_length_t at, fss_payload_read_data_t *data) {

    if (data->option & fss_payload_read_data_option_select_d) {
      if (data->option & fss_payload_read_data_option_object_d) {
        flockfile(main->output.to.stream);

        fss_payload_read_print_one(main);

        funlockfile(main->output.to.stream);

        return F_success;
      }

      if (data->select < data->contents_header.array[at].used) {
        if (data->contents_header.array[at].array[data->select].start <= data->contents_header.array[at].array[data->select].stop || (data->option & fss_payload_read_data_option_empty_d)) {
          flockfile(main->output.to.stream);

          fss_payload_read_print_one(main);

          funlockfile(main->output.to.stream);

          return F_success;
        }
      }
    }
    else if ((data->option & fss_payload_read_data_option_object_d) || (data->option & fss_payload_read_data_option_empty_d)) {
      flockfile(main->output.to.stream);

      fss_payload_read_print_one(main);

      funlockfile(main->output.to.stream);

      return F_success;
    }
    else if (data->contents_header.array[at].used) {
      for (f_array_length_t j = 0; j < data->contents_header.array[at].used; ++j) {

        if (data->contents_header.array[at].array[j].start <= data->contents_header.array[at].array[j].stop) {
          flockfile(main->output.to.stream);

          fss_payload_read_print_one(main);

          funlockfile(main->output.to.stream);

          return F_success;
        }
      } // for
    }

    return F_none;
  }
#endif // _di_fss_payload_read_print_at_total_extended_

#ifndef _di_fss_payload_read_print_content_end_extended_
  void fss_payload_read_print_content_end_extended(fll_program_data_t * const main) {

    if (main->parameters.array[fss_payload_read_parameter_pipe_e].result == f_console_result_found_e) {
      f_print_dynamic_raw(fss_payload_read_pipe_content_start_s, main->output.to.stream);
    }
    else {
      f_print_dynamic_raw(f_fss_space_s, main->output.to.stream);
    }
  }
#endif // _di_fss_payload_read_print_content_end_extended_

#ifndef _di_fss_payload_read_print_content_ignore_
  void fss_payload_read_print_content_ignore(fll_program_data_t * const main) {

    if (main->parameters.array[fss_payload_read_parameter_pipe_e].result == f_console_result_found_e) {
      f_print_dynamic_raw(fss_payload_read_pipe_content_ignore_s, main->output.to.stream);
    }
  }
#endif // _di_fss_payload_read_print_content_ignore_

#ifndef _di_fss_payload_read_print_object_end_
  void fss_payload_read_print_object_end(fll_program_data_t * const main) {

    if (main->parameters.array[fss_payload_read_parameter_pipe_e].result == f_console_result_found_e) {
      f_print_dynamic_raw(fss_payload_read_pipe_content_start_s, main->output.to.stream);
    }
    else {
      if (main->parameters.array[fss_payload_read_parameter_content_e].result == f_console_result_found_e) {
        f_print_dynamic_raw(f_fss_basic_list_open_s, main->output.to.stream);
        f_print_dynamic_raw(f_fss_basic_list_open_end_s, main->output.to.stream);
      }
      else {
        f_print_dynamic_raw(f_fss_eol_s, main->output.to.stream);
      }
    }
  }
#endif // _di_fss_payload_read_print_object_end_

#ifndef _di_fss_payload_read_print_object_end_extended_
  void fss_payload_read_print_object_end_extended(fll_program_data_t * const main) {

    if (main->parameters.array[fss_payload_read_parameter_pipe_e].result == f_console_result_found_e) {
      f_print_dynamic_raw(fss_payload_read_pipe_content_end_s, main->output.to.stream);
    }
    else {
      f_print_dynamic_raw(f_fss_space_s, main->output.to.stream);
    }
  }
#endif // _di_fss_payload_read_print_object_end_extended_

#ifndef _di_fss_payload_read_print_set_end_
  void fss_payload_read_print_set_end(fll_program_data_t * const main) {

    if (main->parameters.array[fss_payload_read_parameter_pipe_e].result == f_console_result_found_e) {
      f_print_dynamic_raw(fss_payload_read_pipe_content_end_s, main->output.to.stream);
    }
  }
#endif // _di_fss_payload_read_print_set_end_

#ifndef _di_fss_payload_read_print_set_end_extended_
  void fss_payload_read_print_set_end_extended(fll_program_data_t * const main) {

    if (main->parameters.array[fss_payload_read_parameter_pipe_e].result == f_console_result_found_e) {
      f_print_dynamic_raw(fss_payload_read_pipe_content_end_s, main->output.to.stream);
    }
    else {
      f_print_dynamic_raw(f_fss_eol_s, main->output.to.stream);
    }
  }
#endif // _di_fss_payload_read_print_set_end_extended_

#ifndef _di_fss_payload_read_print_one_
  void fss_payload_read_print_one(fll_program_data_t * const main) {

    f_print_dynamic_raw(f_string_ascii_1_s, main->output.to.stream);
    f_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
  }
#endif // _di_fss_payload_read_print_one_

#ifndef _di_fss_payload_read_print_zero_
  void fss_payload_read_print_zero(fll_program_data_t * const main) {

    f_print_dynamic_raw(f_string_ascii_0_s, main->output.to.stream);
    f_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
  }
#endif // _di_fss_payload_read_print_zero_

#ifdef __cplusplus
} // extern "C"
#endif
