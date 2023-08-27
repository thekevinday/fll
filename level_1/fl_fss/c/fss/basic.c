#include "basic.h"
#include "../private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_basic_content_read_
  void fl_fss_basic_content_read(const f_string_static_t buffer, f_string_range_t * const range, f_string_ranges_t * const found, f_number_unsigneds_t * const delimits, f_state_t * const state) {
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

    if (state->status == F_okay_eol) {
      ++range->start;
      state->status = F_fss_found_content_not;

      return;
    }

    if (state->status == F_okay_eos) {
      state->status = F_data_not_eos;

      return;
    }

    if (state->status == F_okay_stop) {
      state->status = F_data_not_stop;

      return;
    }

    state->status = f_memory_array_increase(state->step_small, sizeof(f_string_range_t), (void **) &found->array, &found->used, &found->size);
    if (F_status_is_error(state->status)) return;

    found->array[found->used].start = range->start;

    for (;; ++range->start) {

      if (state->interrupt) {
        state->interrupt((void *) state, 0);
        if (F_status_set_fine(state->status) == F_interrupt) break;
      }

      f_fss_skip_past_delimit(buffer, range, state);
      if (F_status_is_error(state->status)) break;

      if (state->status == F_okay_eos || state->status == F_okay_stop) return;
      if (buffer.string[range->start] == f_fss_basic_close_s.string[0]) break;
    } // for

    if (F_status_is_error(state->status)) return;

    found->array[found->used++].stop = range->start - 1;

    state->status = f_utf_buffer_increment(buffer, range, 1);
    if (F_status_is_error(state->status)) return;

    state->status = F_fss_found_content;
  }
#endif // _di_fl_fss_basic_content_read_

#ifndef _di_fl_fss_basic_content_write_
  void fl_fss_basic_content_write(const f_string_static_t content, const uint8_t complete, f_string_range_t * const range, f_string_dynamic_t * const destination, f_state_t * const state) {
    #ifndef _di_level_1_parameter_checking_
      if (!state) return;

      if (!range || !destination) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_1_parameter_checking_

    state->status = F_okay;

    f_fss_skip_past_delimit(content, range, state);
    if (F_status_is_error(state->status)) return;
    if (state->status == F_data_not) return;

    if (range->start > range->stop || range->start >= content.used) {

      // Content should be terminated, even if empty.
      if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e || complete == f_fss_complete_end_e) {
        state->status = f_memory_array_increase(state->step_large, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
        if (F_status_is_error(state->status)) return;

        destination->string[destination->used++] = f_fss_basic_close_s.string[0];
      }

      state->status = range->start > range->stop ? F_data_not_stop : F_data_not_eos;

      return;
    }

    const f_number_unsigned_t destination_used = destination->used;

    for (; range->start <= range->stop && range->start < content.used; ++range->start) {

      if (state->interrupt) {
        state->interrupt((void *) state, 0);
        if (F_status_set_fine(state->status) == F_interrupt) return;
      }

      if (content.string[range->start] == f_fss_eol_s.string[0]) {
        destination->used = destination_used;
        state->status = F_status_set_error(F_okay_eol);

        return;
      }

      if (content.string[range->start] == f_fss_placeholder_s.string[0]) continue;

      state->status = f_memory_array_increase(state->step_large, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);

      if (F_status_is_error(state->status)) {
        destination->used = destination_used;

        return;
      }

      destination->string[destination->used++] = content.string[range->start];
    } // for

    if (complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e || complete == f_fss_complete_end_e) {
      state->status = f_memory_array_increase(state->step_large, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);

      if (F_status_is_error(state->status)) {
        destination->used = destination_used;

        return;
      }

      destination->string[destination->used++] = f_fss_basic_close_s.string[0];
    }

    if (range->start > range->stop) state->status = F_okay_stop;
    else state->status = F_okay_eos;
  }
#endif // _di_fl_fss_basic_content_write_

#ifndef _di_fl_fss_basic_object_read_
  void fl_fss_basic_object_read(const f_string_static_t buffer, f_string_range_t * const range, f_string_range_t * const found, uint8_t * const quote, f_number_unsigneds_t * const delimits, f_state_t * const state) {
    #ifndef _di_level_1_parameter_checking_
      if (!state) return;

      if (!range || !found || !delimits) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_1_parameter_checking_

    const f_number_unsigned_t delimits_used = delimits->used;

    private_fl_fss_basic_read(buffer, F_true, range, found, quote, delimits, state);

    if (state->status == F_status_set_error(F_fss_found_object_content_not)) {

      // The private function sets the error bit on unterminated quoted Object.
      state->status = F_fss_found_object_content_not;
    }
    else if (F_status_is_error(state->status) || state->status == F_fss_found_object_not || state->status == F_data_not || state->status == F_data_not_eos || state->status == F_data_not_stop) {
      delimits->used = delimits_used;
    }
  }
#endif // _di_fl_fss_basic_object_read_

#ifndef _di_fl_fss_basic_object_write_
  void fl_fss_basic_object_write(const f_string_static_t object, const uint8_t quote, const uint8_t complete, f_string_range_t * const range, f_string_dynamic_t * const destination, f_state_t * const state) {
    #ifndef _di_level_1_parameter_checking_
      if (!state) return;

      if (!range || !destination) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_1_parameter_checking_

    const f_number_unsigned_t destination_used = destination->used;

    private_fl_fss_basic_write(F_true, object, quote ? quote : f_fss_quote_double_s.string[0], range, destination, state);

    if (F_status_is_error(state->status)) {
      destination->used = destination_used;

      return;
    }

    if (state->status == F_data_not_stop || state->status == F_data_not_eos) {

      // Objects cannot be empty, so write a quote empty string.
      {
        const f_status_t status = f_memory_array_increase_by(state->step_small + 2, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);

        if (F_status_is_error(status)) {
          destination->used = destination_used;
          state->status = status;

          return;
        }
      }

      destination->string[destination->used++] = quote ? quote : f_fss_quote_double_s.string[0];
      destination->string[destination->used++] = quote ? quote : f_fss_quote_double_s.string[0];
    }

    if (complete == f_fss_complete_partial_e || complete == f_fss_complete_partial_trim_e || complete == f_fss_complete_full_e || complete == f_fss_complete_full_trim_e || complete == f_fss_complete_trim_e) {
      if (state->status == F_okay_stop || state->status == F_okay_eos || state->status == F_data_not_stop || state->status == F_data_not_eos) {
        const f_status_t status_original = state->status;

        if (complete == f_fss_complete_full_trim_e || complete == f_fss_complete_trim_e) {
          private_fl_fss_basic_write_object_trim(quote ? quote : f_fss_quote_double_s.string[0], destination_used, destination, state);

          if (F_status_is_error(state->status)) {
            destination->used = destination_used;

            return;
          }
        }

        if (complete != f_fss_complete_trim_e) {
          state->status = f_memory_array_increase(state->step_large, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);

          if (F_status_is_error(state->status)) {
            destination->used = destination_used;

            return;
          }

          destination->string[destination->used++] = f_fss_basic_open_s.string[0];
        }

        state->status = status_original;
      }
    }

    if (F_status_is_error(state->status)) {
      destination->used = destination_used;
    }
  }
#endif // _di_fl_fss_basic_object_write_

#ifdef __cplusplus
} // extern "C"
#endif
