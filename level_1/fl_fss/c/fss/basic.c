#include "basic.h"
#include "../private-fss.h"
#include "macro.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_basic_content_read_
  f_status_t fl_fss_basic_content_read(const f_string_static_t buffer, f_state_t state, f_string_range_t * const range, f_fss_content_t * const found, f_fss_delimits_t * const delimits) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!found) return F_status_set_error(F_parameter);
      if (!delimits) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = f_fss_skip_past_space(state, buffer, range);
    if (F_status_is_error(status)) return status;

    if (status == F_none_eol) {
      ++range->start;

      return F_fss_found_content_not;
    }

    if (status == F_none_eos) return F_data_not_eos;
    if (status == F_none_stop) return F_data_not_stop;

    status = f_string_ranges_increase(state.step_small, found);
    if (F_status_is_error(status)) return status;

    const f_number_unsigned_t begin = range->start;
    found->array[found->used].start = range->start;

    for (;; ++range->start) {

      if (state.interrupt) {
        status = state.interrupt((void *) &state, 0);

        if (F_status_set_fine(status) == F_interrupt) {
          status = F_status_set_error(F_interrupt);

          break;
        }
      }

      status = f_fss_skip_past_delimit(state, buffer, range);
      if (F_status_is_error(status)) break;

      if (status == F_none_eos || status == F_none_stop) return status;
      if (buffer.string[range->start] == f_fss_basic_close_s.string[0]) break;
    } // for

    if (F_status_is_error(status)) return status;

    if (range->start > begin) {
      found->array[found->used++].stop = range->start - 1;
    }
    else {
      found->array[found->used].start = 1;
      found->array[found->used++].stop = 0;
    }

    status = f_utf_buffer_increment(buffer, range, 1);
    if (F_status_is_error(status)) return status;

    return F_fss_found_content;
  }
#endif // _di_fl_fss_basic_content_read_

#ifndef _di_fl_fss_basic_content_write_
  f_status_t fl_fss_basic_content_write(const f_string_static_t content, const uint8_t complete, f_state_t state, f_string_range_t * const range, f_string_dynamic_t * const destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    status = f_fss_skip_past_delimit(state, content, range);
    if (F_status_is_error(status)) return status;

    if (range->start > range->stop || range->start >= content.used) {

      // Content should be terminated, even if empty.
      if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e || complete == f_fss_complete_end_e) {
        status = f_string_dynamic_increase(state.step_large, destination);
        if (F_status_is_error(status)) return status;

        destination->string[destination->used++] = f_fss_basic_close_s.string[0];
      }

      if (range->start > range->stop) return F_data_not_stop;

      return F_data_not_eos;
    }

    const f_array_length_t destination_used = destination->used;

    for (; range->start <= range->stop && range->start < content.used; ++range->start) {

      if (state.interrupt) {
        status = state.interrupt((void *) &state, 0);

        if (F_status_set_fine(status) == F_interrupt) return F_status_set_error(F_interrupt);
      }

      if (content.string[range->start] == f_fss_eol_s.string[0]) {
        destination->used = destination_used;

        return F_status_set_error(F_none_eol);
      }

      if (content.string[range->start] == f_fss_delimit_placeholder_s.string[0]) continue;

      status = f_string_dynamic_increase(state.step_large, destination);

      if (F_status_is_error(status)) {
        destination->used = destination_used;

        return status;
      }

      destination->string[destination->used++] = content.string[range->start];
    } // for

    if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e || complete == f_fss_complete_end_e) {
      status = f_string_dynamic_increase(state.step_large, destination);

      if (F_status_is_error(status)) {
        destination->used = destination_used;

        return status;
      }

      destination->string[destination->used++] = f_fss_basic_close_s.string[0];
    }

    if (range->start > range->stop) return F_none_stop;

    return F_none_eos;
  }
#endif // _di_fl_fss_basic_content_write_

#ifndef _di_fl_fss_basic_object_read_
  f_status_t fl_fss_basic_object_read(const f_string_static_t buffer, f_state_t state, f_string_range_t * const range, f_fss_object_t * const found, f_fss_quote_t * const quote, f_fss_delimits_t * const delimits) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!found) return F_status_set_error(F_parameter);
      if (!delimits) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    const f_array_length_t delimits_used = delimits->used;

    const f_status_t status = private_fl_fss_basic_or_extended_read(buffer, 0x1, state, range, found, quote, delimits);

    // The private function sets the error bit on unterminated quoted Object.
    if (status == F_status_set_error(F_fss_found_object_content_not)) {
      return F_fss_found_object_content_not;
    }

    if (F_status_is_error(status) || status == F_fss_found_object_not || status == F_data_not || status == F_data_not_eos || status == F_data_not_stop) {
      delimits->used = delimits_used;
    }

    return status;
  }
#endif // _di_fl_fss_basic_object_read_

#ifndef _di_fl_fss_basic_object_write_
  f_status_t fl_fss_basic_object_write(const f_string_static_t object, const f_fss_quote_t quote, const uint8_t complete, f_state_t state, f_string_range_t * const range, f_string_dynamic_t * const destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    const f_array_length_t destination_used = destination->used;

    f_status_t status = private_fl_fss_basic_write(F_true, object, quote ? quote : f_fss_delimit_quote_double_s.string[0], state, range, destination);

    if (F_status_is_error(status)) {
      destination->used = destination_used;

      return status;
    }

    if (status == F_data_not_stop || status == F_data_not_eos) {

      // Objects cannot be empty, so write a quote empty string.
      {
        const f_status_t status_allocation = f_string_dynamic_increase_by(state.step_small + 2, destination);

        if (F_status_is_error(status_allocation)) {
          destination->used = destination_used;

          return status_allocation;
        }
      }

      destination->string[destination->used++] = quote ? quote : f_fss_delimit_quote_double_s.string[0];
      destination->string[destination->used++] = quote ? quote : f_fss_delimit_quote_double_s.string[0];
    }

    if (complete == f_fss_complete_partial_e || complete == f_fss_complete_partial_trim_e || complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e) {
      if (status == F_none_stop || status == F_none_eos || status == F_data_not_stop || status == F_data_not_eos) {
        f_status_t status2 = F_none;

        if (complete == f_fss_complete_full_trim_e) {
          status2 = private_fl_fss_basic_write_object_trim(quote ? quote : f_fss_delimit_quote_double_s.string[0], destination_used, state, destination);

          if (F_status_is_error(status2)) {
            destination->used = destination_used;

            return status2;
          }
        }

        status2 = f_string_dynamic_increase(state.step_large, destination);

        if (F_status_is_error(status2)) {
          destination->used = destination_used;

          return status2;
        }

        destination->string[destination->used++] = f_fss_basic_open_s.string[0];
      }
    }

    if (F_status_is_error(status)) {
      destination->used = destination_used;
    }

    return status;
  }
#endif // _di_fl_fss_basic_object_write_

#ifdef __cplusplus
} // extern "C"
#endif
