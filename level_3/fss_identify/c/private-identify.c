#include "fss_identify.h"
#include "private-common.h"
#include "private-identify.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_identify_load_line_
  f_status_t fss_identify_load_line(fll_program_data_t * const main, const f_file_t file, const f_string_static_t file_name, f_string_static_t *buffer, f_string_range_t *range) {

    f_status_t status = F_none;

    buffer->used = 0;

    range->start = 0;
    range->stop = 0;

    do {
      if (!((++main->signal_check) % fss_identify_signal_check_d)) {
        if (fll_program_standard_signal_received(main)) {
          fss_identify_print_signal_received(main);

          status = F_status_set_error(F_interrupt);

          break;
        }

        main->signal_check = 0;
      }

      if (buffer->used + file.size_read > buffer->size) {
        status = f_string_dynamic_resize(buffer->size + file.size_read, buffer);

        if (F_status_is_error(status)) {
          fll_error_file_print(main->error, F_status_set_fine(status), "f_string_dynamic_resize", F_true, file_name.used ? file_name : f_string_ascii_minus_s, f_file_operation_read_s, file_name.used ? fll_error_file_type_file_e : fll_error_file_type_pipe_e);

          return status;
        }
      }

      status = f_file_stream_read_block(file, buffer);

      if (F_status_is_error(status)) {
        fll_error_file_print(main->error, F_status_set_fine(status), "f_file_stream_read_block", F_true, file_name.used ? file_name : f_string_ascii_minus_s, f_file_operation_read_s, file_name.used ? fll_error_file_type_file_e : fll_error_file_type_pipe_e);

        return status;
      }

      for (; range->start < buffer->used; ++range->start) {
        if (buffer->string[range->start] == f_string_eol_s.string[0]) break;
      } // for

      range->stop = range->start;

      if (buffer->string[range->start] == f_string_eol_s.string[0]) break;

    } while (F_status_is_error_not(status) && status != F_none_eof);

    // Reset the start point to prepare the buffer for processing.
    range->start = 0;

    return status;
  }
#endif // _di_fss_identify_load_line_

#ifndef _di_fss_identify_process_
  f_status_t fss_identify_process(fll_program_data_t * const main, fss_identify_data_t * const data, const f_string_static_t file_name, const f_string_static_t buffer, f_string_range_t *range) {

    f_status_t status = F_none;
    f_fll_ids_t ids = f_fll_ids_t_initialize;

    status = fll_fss_identify(buffer, range, &ids);

    if (F_status_is_error(status)) {
      fll_error_file_print(main->error, F_status_set_fine(status), "fll_fss_identify", F_true, file_name.used ? file_name : f_string_ascii_pipe_s, f_file_operation_read_s, file_name.used ? fll_error_file_type_file_e : fll_error_file_type_pipe_e);

      f_fll_ids_resize(0, &ids);

      return status;
    }

    // 0 = is name, 1 = is type, 2 = is full.
    uint8_t modes[data->names.used];
    f_array_length_t i = 0;

    if (data->names.used) {
      for (f_array_length_t j = 0; i < data->names.used; ++i) {

        modes[i] = 1;

        for (j = 0; j < data->names.array[i].used; ++j) {

          if (data->names.array[i].string[j] == f_string_ascii_minus_s.string[0]) {
            modes[i] = 2;

            break;
          }

          if (f_utf_is_digit(data->names.array[i].string + j, data->names.array[i].used - j, 0) != F_true) {
            modes[i] = 0;
          }
        } // for
      } // for
    }

    if (main->parameters.array[fss_identify_parameter_line_e].result == f_console_result_additional_e) {
      for (i = 0; i < ids.used; ++i, ++data->current) {

        if (data->current == data->line) {
          if (data->names.used) {
            if (fss_identify_process_name_compare(data, ids.array[i], modes) != F_equal_to) continue;
          }

          if (main->parameters.array[fss_identify_parameter_total_e].result == f_console_result_found_e) {
            ++data->total;
          }
          else {
            fss_identify_print(main, ids.array[i]);
          }

          ++data->current;

          break;
        }
      } // for
    }
    else if (main->parameters.array[fss_identify_parameter_total_e].result == f_console_result_found_e) {
      if (data->names.used) {

        for (i = 0; i < ids.used; ++i, ++data->current) {

          if (fss_identify_process_name_compare(data, ids.array[i], modes) == F_equal_to) {
            ++data->total;
          }
        } // for
      }
      else {
        data->total += ids.used;
      }
    }
    else if (status == F_found || status == F_maybe) {
      for (i = 0; i < ids.used; ++i) {

        if (data->names.used) {
          if (fss_identify_process_name_compare(data, ids.array[i], modes) != F_equal_to) continue;
        }

        fss_identify_print(main, ids.array[i]);
      } // for
    }

    f_fll_ids_resize(0, &ids);

    return F_none;
  }
#endif // _di_fss_identify_process_

#ifndef _di_fss_identify_process_name_compare_
  f_status_t fss_identify_process_name_compare(fss_identify_data_t * const data, const f_fll_id_t id, const uint8_t modes[]) {

    f_status_t status = F_none;
    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t number = 0;
    f_string_range_t range = f_string_range_t_initialize;

    for (status = F_equal_to_not; i < data->names.used && status == F_equal_to_not; ++i) {

      if (modes[i]) {
        if (data->names.array[i].used) {
          range.start = 0;
          range.stop = data->names.array[i].used - 1;
        }
        else {
          range.start = 1;
          range.stop = 0;
        }

        for (j = 0; j < data->names.array[i].used; ++j) {

          if (data->names.array[i].string[j] == f_string_ascii_minus_s.string[0] && j + 1 < data->names.array[i].used) {
            range.start = j + 1;

            break;
          }
        } // for

        {
          status = fl_conversion_dynamic_partial_to_unsigned(fl_conversion_data_base_16_c, data->names.array[i], range, &number);
          if (F_status_is_error(status)) return F_equal_to_not;
        }

        if (id.type != number) {
          status = F_equal_to_not;

          continue;
        }

        if (modes[i] == 1) return F_equal_to;

        if (range.start) {
          range.stop = range.start - 2;
          range.start = 0;
        }

        status = fl_string_dynamic_partial_compare_string((const f_string_t) id.name, data->names.array[i], id.used, range);
      }
      else {
        status = fl_string_dynamic_compare_string((const f_string_t) id.name, data->names.array[i], id.used);
      }
    } // for

    return status == F_equal_to ? F_equal_to : F_equal_to_not;
  }
#endif // _di_fss_identify_process_name_compare_

#ifdef __cplusplus
} // extern "C"
#endif
