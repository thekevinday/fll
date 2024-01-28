#include "payload.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_payload_read_
  void fll_fss_payload_read(const f_string_static_t buffer, f_range_t * const range, f_ranges_t * const objects, f_rangess_t * const contents, f_number_unsigneds_t * const objects_delimits, f_number_unsigneds_t * const contents_delimits, f_ranges_t * const comments, f_state_t * const state) {
    #ifndef _di_level_2_parameter_checking_
      if (!state) return;

      if (!range || !objects || !contents) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_2_parameter_checking_

    if (!buffer.used) {
      state->status = F_data_not;

      return;
    }

    f_status_t status = F_okay;
    f_number_unsigned_t initial_used = objects->used;

    // 0x1 = found data, 0x2 = found payload object.
    uint8_t found_data = 0;

    do {
      state->status = f_memory_array_increase(state->step_small, sizeof(f_range_t), (void **) &objects->array, &objects->used, &objects->size);
      if (F_status_is_error(state->status)) return;

      state->status = f_memory_array_increase(state->step_small, sizeof(f_ranges_t), (void **) &contents->array, &contents->used, &contents->size);
      if (F_status_is_error(state->status)) return;

      contents->array[contents->used].used = 0;

      do {
        fl_fss_basic_list_object_read(buffer, range, &objects->array[objects->used], objects_delimits, state);
        if (F_status_is_error(state->status)) return;

        if (f_compare_dynamic_partial_string(f_fss_payload_s.string, buffer, f_fss_payload_s.used, objects->array[objects->used]) == F_equal_to) {
          found_data |= 0x2;
        }

        if (range->start >= range->stop || range->start >= buffer.used) {
          if (state->status == F_fss_found_object || state->status == F_fss_found_object_content_not) {
            state->status = F_fss_found_object_content_not;

            break;
          }

          if (found_data & 0x1) {
            state->status = F_status_set_error((range->start >= buffer.used) ? F_okay_eos : F_okay_stop);
          }
          else {
            state->status = F_status_set_error((range->start >= buffer.used) ? F_data_not_eos : F_data_not_stop);
          }

          return;
        }

        if (state->status == F_fss_found_object) {
          found_data |= 0x1;
          contents->array[contents->used].used = 0;

          if (f_compare_dynamic_partial_string(f_fss_payload_s.string, buffer, f_fss_payload_s.used, objects->array[objects->used]) == F_equal_to) {
            status = f_memory_array_increase(state->step_small, sizeof(f_range_t), (void **) &contents->array[contents->used].array, &contents->array[contents->used].used, &contents->array[contents->used].size);

            if (F_status_is_error(status)) {
              state->status = status;

              return;
            }

            contents->array[contents->used].used = 1;
            contents->array[contents->used].array[0].start = range->start;

            if (buffer.used > range->stop) {
              contents->array[contents->used].array[0].stop = range->stop;
              range->start = range->stop + 1;
              state->status = F_okay_stop;
            }
            else {
              contents->array[contents->used].array[0].stop = buffer.used - 1;
              range->start = buffer.used;
              state->status = F_okay_eos;
            }

            ++objects->used;
            ++contents->used;

            return;
          }

          fl_fss_basic_list_content_read(buffer, range, &contents->array[contents->used], contents_delimits ? contents_delimits : objects_delimits, comments, state);
          if (F_status_is_error(state->status)) return;

          break;
        }

        if (state->status == F_fss_found_object_content_not) {
          found_data |= 0x1;

          break;
        }
      } while (state->status == F_fss_found_object_not);

      if (state->status == F_okay_eos || state->status == F_okay_stop) {
        ++contents->array[contents->used].used;
        ++objects->used;
        ++contents->used;

        // Returning without a "payload" is an error.
        if (!(found_data & 0x2)) {
          state->status = F_status_set_error(state->status);
        }

        return;
      }

      if (state->status == F_data_not || state->status == F_data_not_eos || state->status == F_data_not_stop) {

        // If at least some valid object was found, then return F_okay equivalents.
        if (objects->used > initial_used) {

          // Returning without a "payload" is an error.
          if (found_data & 0x2) {
            state->status = (state->status == F_data_not_eos) ? F_okay_eos : F_okay_stop;
          }
          else {
            state->status = F_status_set_error((state->status == F_data_not_eos) ? F_okay_eos : F_okay_stop);
          }
        }
        else {
          state->status = F_status_set_error(state->status);
        }

        return;
      }

      if (state->status != F_fss_found_object && state->status != F_fss_found_content && state->status != F_fss_found_content_not && state->status != F_fss_found_object_content_not) {
        return;
      }

      if (state->status == F_fss_found_object_content_not) {
        found_data |= 0x1;

        status = f_memory_array_increase(state->step_small, sizeof(f_range_t), (void **) &contents->array[contents->used].array, &contents->array[contents->used].used, &contents->array[contents->used].size);

        if (F_status_is_error(status)) {
          state->status = status;

          return;
        }

        contents->array[contents->used].used = 0;
      }

      if (range->start >= range->stop || range->start >= buffer.used) {

        // When content is found, the range->start is incremented, if content is found at range->stop, then range->start will be > range.stop.
        if (state->status == F_fss_found_object || state->status == F_fss_found_content || state->status == F_fss_found_content_not || state->status == F_fss_found_object_content_not) {
          ++objects->used;
          ++contents->used;
        }

        // Returning without a "payload" is an error.
        if (found_data & 0x2) {
          state->status = (range->start >= buffer.used) ? F_okay_eos : F_okay_stop;
        }
        else {
          state->status = F_status_set_error((range->start >= buffer.used) ? F_okay_eos : F_okay_stop);
        }

        return;
      }

      ++objects->used;
      ++contents->used;

    } while (range->start < F_string_t_size_d);

    state->status = F_status_is_error(F_number_overflow);
  }
#endif // _di_fll_fss_payload_read_

#ifndef _di_fll_fss_payload_write_
  void fll_fss_payload_write(const f_string_static_t object, const f_string_static_t content, const bool trim, const f_string_static_t * const content_prepend, f_string_dynamic_t * const destination, f_state_t * const state) {
    #ifndef _di_level_2_parameter_checking_
      if (!state) return;

      if (!destination) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_2_parameter_checking_

    f_range_t range = macro_f_range_t_initialize_2(object.used);

    fl_fss_basic_list_object_write(object, trim ? f_fss_complete_full_trim_e : f_fss_complete_full_e, &range, destination, state);

    if (F_status_is_error(state->status) || state->status == F_data_not || state->status == F_data_not_stop || state->status == F_data_not_eos) {
      return;
    }

    if (state->status == F_okay || state->status == F_okay_stop || state->status == F_okay_eos || state->status == F_okay_eol) {
      if (f_compare_dynamic(f_fss_payload_s, object) == F_equal_to) {
        state->status = f_memory_array_increase_by(content.used, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
        if (F_status_is_error(state->status)) return;

        f_number_unsigned_t i = 0;

        // Copy in blocks to allow for interruptability of potentially large data sets.
        for (; i < content.used && i + F_fss_default_block_size_normal_d < content.used; i += F_fss_default_block_size_normal_d) {

          if (state->interrupt) {
            state->interrupt((void *) state, 0);
            if (F_status_set_fine(state->status) == F_interrupt) return;
          }

          memcpy(destination->string + destination->used + i, content.string + i, sizeof(f_char_t) * F_fss_default_block_size_normal_d);
        } // for

        if (i < content.used) {
          memcpy(destination->string + destination->used + i, content.string + i, sizeof(f_char_t) * (content.used - i));
        }

        destination->used += content.used;
      }
      else {
        if (content.used) {
          range.start = 0;
          range.stop = content.used - 1;
        }
        else {
          range.start = 1;
          range.stop = 0;
        }

        fl_fss_basic_list_content_write(content, f_fss_complete_full_e, content_prepend, &range, destination, state);
      }
    }
  }
#endif // _di_fll_fss_payload_write_

#ifdef __cplusplus
} // extern "C"
#endif
