#include "fss_identify.h"
#include "private-common.h"
#include "private-fss_identify.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_identify_load_line_
  f_status_t fss_identify_load_line(const fss_identify_main_t main, const f_file_t file, const f_string_t name, f_string_static_t *buffer, f_string_range_t *range) {

    f_status_t status = F_none;

    buffer->used = 0;

    range->start = 0;
    range->stop = 0;

    do {
      if (buffer->used + file.size_read > buffer->size) {
        status = f_string_dynamic_resize(buffer->size + file.size_read, buffer);

        if (F_status_is_error(status)) {
          fll_error_file_print(main.error, F_status_set_fine(status), "f_string_dynamic_resize", F_true, name ? name : "-", "read", name ? fll_error_file_type_file : fll_error_file_type_pipe);

          return status;
        }
      }

      status = f_file_stream_read_block(file, buffer);

      if (F_status_is_error(status)) {
        fll_error_file_print(main.error, F_status_set_fine(status), "f_file_stream_read_block", F_true, name ? name : "-", "read", name ? fll_error_file_type_file : fll_error_file_type_pipe);

        return status;
      }

      for (; range->start < buffer->used; ++range->start) {
        if (buffer->string[range->start] == f_string_eol_s[0]) break;
      } // for

      range->stop = range->start;

      if (buffer->string[range->start] == f_string_eol_s[0]) break;

    } while (F_status_is_error_not(status) && status != F_none_eof);

    // reset the start point to prepare the buffer for processing.
    range->start = 0;

    return status;
  }
#endif // _di_fss_identify_load_line_

#ifndef _di_fss_identify_print_
  void fss_identify_print(const fss_identify_main_t main, f_fll_id_t id) {

    flockfile(main.output.stream);

    if (main.parameters[fss_identify_parameter_object].result == f_console_result_found || main.parameters[fss_identify_parameter_content].result != f_console_result_found) {
      f_print(id.name, id.used, main.output.stream);

      if (main.parameters[fss_identify_parameter_object].result != f_console_result_found || main.parameters[fss_identify_parameter_content].result == f_console_result_found) {
        f_print_character(f_fss_type_header_part5, main.output.stream);
      }
    }

    if (main.parameters[fss_identify_parameter_object].result != f_console_result_found || main.parameters[fss_identify_parameter_content].result == f_console_result_found) {
      fl_print_format("%04_ui", main.output.stream, id.type);
    }

    f_print_character(f_string_eol_s[0], main.output.stream);

    funlockfile(main.output.stream);
  }
#endif // _di_fss_identify_print_

#ifndef _di_fss_identify_process_
  f_status_t fss_identify_process(const fss_identify_main_t main, const f_string_t name, const f_string_static_t buffer, f_string_range_t *range, fss_identify_data_t *data) {

    f_status_t status = F_none;
    f_fll_ids_t ids = f_fll_ids_t_initialize;

    status = fll_fss_identify(buffer.string, range, &ids);

    if (F_status_is_error(status)) {
      fll_error_file_print(main.error, F_status_set_fine(status), "fll_fss_identify", F_true, name ? name : "-", "read", name ? fll_error_file_type_file : fll_error_file_type_pipe);

      f_type_fll_ids_resize(0, &ids);

      return status;
    }

    if (main.parameters[fss_identify_parameter_line].result == f_console_result_additional) {

      for (f_array_length_t i = 0; i < ids.used; ++i, ++data->current) {

        if (data->current == data->line) {
          if (data->name.used) {
            if (fl_string_dynamic_compare_string(ids.array[i].name, data->name, ids.array[i].used) != F_equal_to) {
              continue;
            }
          }

          if (main.parameters[fss_identify_parameter_total].result == f_console_result_found) {
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
    else if (main.parameters[fss_identify_parameter_total].result == f_console_result_found) {
      if (data->name.used) {

        for (f_array_length_t i = 0; i < ids.used; ++i, ++data->current) {

          if (fl_string_dynamic_compare_string(ids.array[i].name, data->name, ids.array[i].used) == F_equal_to) {
            ++data->total;
          }
        } // for
      }
      else {
        data->total += ids.used;
      }
    }
    else if (status == F_found || status == F_maybe) {

      for (f_array_length_t i = 0; i < ids.used; ++i) {

        if (data->name.used) {
          if (fl_string_dynamic_compare_string(ids.array[i].name, data->name, ids.array[i].used) != F_equal_to) {
            continue;
          }
        }

        fss_identify_print(main, ids.array[i]);
      } // for
    }

    f_type_fll_ids_resize(0, &ids);

    return F_none;
  }
#endif // _di_fss_identify_process_

#ifdef __cplusplus
} // extern "C"
#endif
