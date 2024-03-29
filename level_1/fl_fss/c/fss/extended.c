#include "extended.h"
#include "../private-fss.h"
#include "macro.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_extended_content_read_
  f_status_t fl_fss_extended_content_read(const f_string_static_t buffer, f_state_t state, f_string_range_t * const range, f_fss_content_t * const found, f_fss_quotes_t * const quotes, f_fss_delimits_t * const delimits) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!found) return F_status_set_error(F_parameter);
      if (!delimits) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;
    f_status_t status_allocate = F_none;

    status = f_fss_skip_past_space(state, buffer, range);
    if (F_status_is_error(status)) return status;

    if (status == F_none_eol) {
      ++range->start;

      return F_fss_found_content_not;
    }

    if (status == F_none_eos) return F_data_not_eos;
    if (status == F_none_stop) return F_data_not_stop;

    const f_array_length_t delimits_used = delimits->used;
    const f_array_length_t quotes_used = quotes ? quotes->used : 0;

    uint8_t content_found = 0;
    f_fss_quote_t quote = f_fss_quote_type_none_e;

    while (range->start <= range->stop && range->start < buffer.used) {

      f_string_range_t content_partial = f_string_range_t_initialize;

      status = private_fl_fss_basic_or_extended_read(buffer, (state.flag & f_fss_state_quote_not_e) ? 0x2 : 0x0, state, range, &content_partial, &quote, delimits);

      // Quote is unterminated, retry with quotes disabled as per-specification (this error should not be reported when quotes are disabled).
      if (status == F_status_set_error(F_fss_found_object_content_not)) {
        content_partial.start = 1;
        content_partial.stop = 0;

        status = private_fl_fss_basic_or_extended_read(buffer, 0x2, state, range, &content_partial, &quote, delimits);
      }

      if (status == F_fss_found_object || status == F_fss_found_object_content_not) {
        status_allocate = f_string_ranges_increase(state.step_small, found);

        // The private function sets the error bit on unterminated quoted Object.
        if (status == F_status_set_error(F_fss_found_object_content_not)) {
          status = F_fss_found_object_content_not;
        }

        if (F_status_is_error_not(status_allocate) && quotes) {
          status_allocate = f_uint8s_increase(state.step_small, quotes);
        }

        if (F_status_is_error(status_allocate)) {
          delimits->used = delimits_used;

          if (quotes) {
            quotes->used = quotes_used;
          }

          return status_allocate;
        }

        found->array[found->used++] = content_partial;

        if (quotes) {
          quotes->array[quotes->used++] = quote;
        }

        content_found = 1;

        if (status == F_fss_found_object_content_not) break;
      }
      else if (status == F_fss_found_object_not) {
        break;
      }
      else if (status == F_data_not_eos) {
        if (content_found) {
          status = F_none_eos;
        }

        content_found = 2;

        break;
      }
      else if (status == F_data_not_stop) {
        if (content_found) {
          status = F_none_stop;
        }

        content_found = 2;

        break;
      }
      else if (status == F_end_not_group_eos || status == F_end_not_group_eos) {
        if (content_found) {
          content_found = 2;
        }

        break;
      }
      else if (F_status_is_error(status)) {
        delimits->used = delimits_used;

        if (quotes) {
          quotes->used = quotes_used;
        }

        return status;
      }
    } // while

    if (content_found) {
      if (content_found == 2) return status;

      return F_fss_found_content;
    }

    return F_fss_found_content_not;
  }
#endif // _di_fl_fss_extended_content_read_

#ifndef _di_fl_fss_extended_content_write_
  f_status_t fl_fss_extended_content_write(const f_string_static_t content, const f_fss_quote_t quote, const uint8_t complete, f_state_t state, f_string_range_t * const range, f_string_dynamic_t * const destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    const f_array_length_t destination_used = destination->used;

    // This operates exactly like an object, syntax-wise.
    const f_status_t status = private_fl_fss_basic_write(F_false, content, quote ? quote : f_fss_delimit_quote_double_s.string[0], state, range, destination);

    if (F_status_is_error(status)) {
      destination->used = destination_used;

      return status;
    }

    if (status == F_data_not_stop || status == F_data_not_eos) {

      // Content that is empty must be represented by a quote empty string.
      {
        const f_status_t status_allocation = f_string_dynamic_increase_by(state.step_small + 4, destination);
        if (F_status_is_error(status_allocation)) return status_allocation;
      }

      destination->string[destination->used++] = quote ? quote : f_fss_delimit_quote_double_s.string[0];
      destination->string[destination->used++] = quote ? quote : f_fss_delimit_quote_double_s.string[0];

      // Content should be terminated, even if empty.
      if (complete == f_fss_complete_partial_e || complete == f_fss_complete_partial_trim_e || complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e || complete == f_fss_complete_next_e) {
        destination->string[destination->used++] = f_fss_extended_next_s.string[0];
      }

      if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e || complete == f_fss_complete_end_e) {
        destination->string[destination->used++] = f_fss_extended_close_s.string[0];
      }

      if (status == F_data_not_stop) return F_none_stop;

      return F_none_eos;
    }

    // Ensure that there is room, including the slash delimit and possibly the end of content characters.
    {
      const f_status_t status_allocation = f_string_dynamic_increase_by(state.step_small + 2, destination);
      if (F_status_is_error(status_allocation)) return status_allocation;
    }

    if (complete == f_fss_complete_partial_e || complete == f_fss_complete_partial_trim_e || complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e || complete == f_fss_complete_next_e) {
      destination->string[destination->used++] = f_fss_extended_next_s.string[0];
    }

    if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e || complete == f_fss_complete_end_e) {
      destination->string[destination->used++] = f_fss_extended_close_s.string[0];
    }

    return status;
  }
#endif // _di_fl_fss_extended_content_write_

#ifndef _di_fl_fss_extended_object_read_
  f_status_t fl_fss_extended_object_read(const f_string_static_t buffer, f_state_t state, f_string_range_t * const range, f_fss_object_t * const found, f_fss_quote_t * const quote, f_fss_delimits_t * const delimits) {
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
#endif // _di_fl_fss_extended_object_read_

#ifndef _di_fl_fss_extended_object_write_
f_status_t fl_fss_extended_object_write(const f_string_static_t object, const f_fss_quote_t quote, const uint8_t complete, f_state_t state, f_string_range_t * const range, f_string_dynamic_t * const destination) {
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

        destination->string[destination->used++] = f_fss_extended_open_s.string[0];
      }
    }

    return status;
  }
#endif // _di_fl_fss_extended_object_write_

#ifdef __cplusplus
} // extern "C"
#endif
