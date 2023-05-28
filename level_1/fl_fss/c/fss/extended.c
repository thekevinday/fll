#include "extended.h"
#include "../private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_extended_content_read_
  void fl_fss_extended_content_read(const f_string_static_t buffer, f_string_range_t * const range, f_fss_content_t * const found, f_uint8s_t * const quotes, f_fss_delimits_t * const delimits, f_state_t * const state) {
    #ifndef _di_level_1_parameter_checking_
      if (!state) return;

      if (!range || !found || !delimits) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_1_parameter_checking_

    f_fss_skip_past_space(buffer, range, state);
    if (F_status_is_error(state->status)) return;
    if (state->status == F_data_not) return;

    if (state->status == F_none_eol) {
      ++range->start;
      state->status = F_fss_found_content_not;

      return;
    }

    if (state->status == F_none_eos) {
      state->status = F_data_not_eos;

      return;
    }

    if (state->status == F_none_stop) {
      state->status = F_data_not_stop;

      return;
    }

    const f_array_length_t delimits_used = delimits->used;
    const f_array_length_t quotes_used = quotes ? quotes->used : 0;

    uint8_t content_found = 0;
    uint8_t quote = 0;

    f_status_t status = F_none;

    while (range->start <= range->stop && range->start < buffer.used) {

      f_string_range_t content_partial = f_string_range_t_initialize;

      quote = 0;

      private_fl_fss_basic_read(buffer, F_false, range, &content_partial, &quote, delimits, state);

      if (state->status == F_fss_found_object || F_status_set_fine(state->status) == F_fss_found_object_content_not) {
        status = f_string_ranges_increase(state->step_small, found);

        if (F_status_is_error_not(status) && quotes) {
          status = f_uint8s_increase(state->step_small, quotes);
        }

        // The private function sets the error bit on unterminated quoted Object.
        if (state->status == F_status_set_error(F_fss_found_object_content_not)) {
          state->status = F_fss_found_object_content_not;
        }

        if (F_status_is_error(status)) {
          delimits->used = delimits_used;
          state->status = status;

          if (quotes) {
            quotes->used = quotes_used;
          }

          return;
        }

        found->array[found->used++] = content_partial;

        if (quotes) {
          if (quote == f_fss_quote_type_double_e) {
            quotes->array[quotes->used] = f_fss_quote_double_s.string[0];
          }
          else if (quote == f_fss_quote_type_single_e) {
            quotes->array[quotes->used] = f_fss_quote_single_s.string[0];
          }
          else if (quote == f_fss_quote_type_backtick_e) {
            quotes->array[quotes->used] = f_fss_quote_backtick_s.string[0];
          }
          else {
            quotes->array[quotes->used] = 0;
          }

          quotes->used = found->used;
        }

        content_found = 1;

        if (state->status == F_fss_found_object_content_not) break;
      }
      else if (state->status == F_fss_found_object_not) {
        break;
      }
      else if (state->status == F_data_not_eos) {
        if (content_found) {
          state->status = F_none_eos;
        }

        content_found = 2;

        break;
      }
      else if (state->status == F_data_not_stop) {
        if (content_found) {
          state->status = F_none_stop;
        }

        content_found = 2;

        break;
      }
      else if (state->status == F_end_not_group_eos || state->status == F_end_not_group_eos) {
        if (content_found) {
          content_found = 2;
        }

        break;
      }
      else if (F_status_is_error(state->status)) {
        delimits->used = delimits_used;

        return;
      }
    } // while

    if (content_found) {
      if (content_found == 2) return;

      state->status = F_fss_found_content;
    }
    else {
      state->status = F_fss_found_content_not;
    }
  }
#endif // _di_fl_fss_extended_content_read_

#ifndef _di_fl_fss_extended_content_write_
  void fl_fss_extended_content_write(const f_string_static_t content, const uint8_t quote, const uint8_t complete, f_string_range_t * const range, f_string_dynamic_t * const destination, f_state_t * const state) {
    #ifndef _di_level_1_parameter_checking_
      if (!state) return;

      if (!range || !destination) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_1_parameter_checking_

    const f_array_length_t destination_used = destination->used;

    // This operates exactly like an object, syntax-wise.
    private_fl_fss_basic_write(F_false, content, quote ? quote : f_fss_quote_double_s.string[0], range, destination, state);

    if (F_status_is_error(state->status)) {
      destination->used = destination_used;

      return;
    }

    f_status_t status = F_none;

    if (state->status == F_data_not_stop || state->status == F_data_not_eos) {

      // Content that is empty must be represented by a quote empty string.
      status = f_string_dynamic_increase_by(state->step_small + 4, destination);

      if (F_status_is_error(status)) {
        state->status = status;
      };

      destination->string[destination->used++] = quote ? quote : f_fss_quote_double_s.string[0];
      destination->string[destination->used++] = quote ? quote : f_fss_quote_double_s.string[0];

      // Content should be terminated, even if empty.
      if (complete == f_fss_complete_partial_e || complete == f_fss_complete_partial_trim_e || complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e || complete == f_fss_complete_next_e) {
        destination->string[destination->used++] = f_fss_extended_next_s.string[0];
      }

      if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e || complete == f_fss_complete_end_e) {
        destination->string[destination->used++] = f_fss_extended_close_s.string[0];
      }

      state->status = (state->status == F_data_not_stop) ? F_none_stop : F_none_eos;

      return;
    }

    // Ensure that there is room, including the slash delimit and possibly the end of content characters.
    status = f_string_dynamic_increase_by(state->step_small + 2, destination);

    if (F_status_is_error(status)) {
      state->status = status;

      return;
    }

    if (complete == f_fss_complete_partial_e || complete == f_fss_complete_partial_trim_e || complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e || complete == f_fss_complete_next_e) {
      destination->string[destination->used++] = f_fss_extended_next_s.string[0];
    }

    if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e || complete == f_fss_complete_end_e) {
      destination->string[destination->used++] = f_fss_extended_close_s.string[0];
    }
  }
#endif // _di_fl_fss_extended_content_write_

#ifndef _di_fl_fss_extended_object_read_
  void fl_fss_extended_object_read(const f_string_static_t buffer, f_string_range_t * const range, f_fss_object_t * const found, uint8_t * const quote, f_fss_delimits_t * const delimits, f_state_t * const state) {
    #ifndef _di_level_1_parameter_checking_
      if (!state) return;

      if (!range || !found || !delimits) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_1_parameter_checking_

    const f_array_length_t delimits_used = delimits->used;

    private_fl_fss_basic_read(buffer, F_true, range, found, quote, delimits, state);

    if (state->status == F_status_set_error(F_fss_found_object_content_not)) {

      // The private function sets the error bit on unterminated quoted Object.
      state->status = F_fss_found_object_content_not;
    }
    else if (F_status_is_error(state->status) || state->status == F_fss_found_object_not || state->status == F_data_not || state->status == F_data_not_eos || state->status == F_data_not_stop) {
      delimits->used = delimits_used;
    }

    return;
  }
#endif // _di_fl_fss_extended_object_read_

#ifndef _di_fl_fss_extended_object_write_
void fl_fss_extended_object_write(const f_string_static_t object, const uint8_t quote, const uint8_t complete, f_string_range_t * const range, f_string_dynamic_t * const destination, f_state_t * const state) {
    #ifndef _di_level_1_parameter_checking_
      if (!state) return;

      if (!range || !destination) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_1_parameter_checking_

    const f_array_length_t destination_used = destination->used;

    private_fl_fss_basic_write(F_true, object, quote ? quote : f_fss_quote_double_s.string[0], range, destination, state);

    if (F_status_is_error(state->status)) {
      destination->used = destination_used;

      return;
    }

    f_status_t status = F_none;

    if (state->status == F_data_not_stop || state->status == F_data_not_eos) {

      // Objects cannot be empty, so write a quote empty string.
      status = f_string_dynamic_increase_by(state->step_small + 2, destination);

      if (F_status_is_error(status)) {
        destination->used = destination_used;
        state->status = status;

        return;
      }

      destination->string[destination->used++] = quote ? quote : f_fss_quote_double_s.string[0];
      destination->string[destination->used++] = quote ? quote : f_fss_quote_double_s.string[0];
    }

    if (complete == f_fss_complete_partial_e || complete == f_fss_complete_partial_trim_e || complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e || complete == f_fss_complete_trim_e) {
      if (state->status == F_none_stop || state->status == F_none_eos || state->status == F_data_not_stop || state->status == F_data_not_eos) {
        status = F_none;

        if (complete == f_fss_complete_full_trim_e || complete == f_fss_complete_trim_e) {
          private_fl_fss_basic_write_object_trim(quote ? quote : f_fss_quote_double_s.string[0], destination_used, destination, state);

          if (F_status_is_error(state->status)) {
            destination->used = destination_used;
            state->status = status;

            return;
          }
        }

        if (complete != f_fss_complete_trim_e) {
          status = f_string_dynamic_increase(state->step_large, destination);

          if (F_status_is_error(status)) {
            destination->used = destination_used;
            state->status = status;

            return;
          }

          destination->string[destination->used++] = f_fss_extended_open_s.string[0];
        }
      }
    }
  }
#endif // _di_fl_fss_extended_object_write_

#ifdef __cplusplus
} // extern "C"
#endif
