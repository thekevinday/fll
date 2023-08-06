#include "basic.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_basic_read_
  void fll_fss_basic_read(const f_string_static_t buffer, f_string_range_t * const range, f_string_ranges_t * const objects, f_string_rangess_t * const contents, f_uint8s_t * const objects_quoted, f_number_unsigneds_t * const objects_delimits, f_number_unsigneds_t * const contents_delimits, f_state_t * const state) {
    #ifndef _di_level_2_parameter_checking_
      if (!state) return;

      if (!range || !objects || !contents) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;
    f_number_unsigned_t initial_used = objects->used;

    bool found_data = F_false;

    uint8_t *quoted_object = 0;

    do {
      state->status = f_string_ranges_increase(state->step_small, objects);
      if (F_status_is_error(state->status)) return;

      state->status = f_string_rangess_increase(state->step_small, contents);
      if (F_status_is_error(state->status)) return;

      contents->array[contents->used].used = 0;

      if (objects_quoted) {
        state->status = f_memory_array_increase(state->step_small, sizeof(uint8_t), (void **) &objects_quoted->array, &objects_quoted->used, &objects_quoted->size);
        if (F_status_is_error(state->status)) return;
      }

      do {
        if (objects_quoted) {
          quoted_object = &objects_quoted->array[objects_quoted->used];
        }

        fl_fss_basic_object_read(buffer, range, &objects->array[objects->used], quoted_object, objects_delimits, state);
        if (F_status_is_error(state->status)) return;

        if (range->start >= range->stop || range->start >= buffer.used) {
          if (state->status == F_fss_found_object || state->status == F_fss_found_object_content_not) {
            ++objects->used;

            if (objects_quoted) {
              ++objects_quoted->used;
            }

            status = f_string_ranges_increase(state->step_small, &contents->array[contents->used]);
            if (F_status_is_error(status)) {
              state->status = status;

              return;
            }

            contents->array[contents->used++].used = 0;
            state->status = F_fss_found_object_content_not;

            return;
          }

          if (state->status == F_data_not) return;

          if (found_data) {
            state->status = (range->start >= buffer.used) ? F_none_eos : F_none_stop;

            return;
          }

          state->status = (range->start >= buffer.used) ? F_data_not_eos : F_data_not_stop;

          return;
        }

        if (state->status == F_fss_found_object) {
          found_data = F_true;
          contents->array[contents->used].used = 0;

          fl_fss_basic_content_read(buffer, range, &contents->array[contents->used], contents_delimits ? contents_delimits : objects_delimits, state);
          if (F_status_is_error(state->status)) return;

          break;
        }

        if (state->status == F_fss_found_object_content_not) {
          found_data = F_true;

          status = f_string_ranges_increase(state->step_small, &contents->array[contents->used]);

          if (F_status_is_error(status)) {
            state->status = status;

            return;
          }

          break;
        }

      } while (state->status == F_fss_found_object_not);

      if (state->status == F_none_eos || state->status == F_none_stop) {
        ++contents->array[contents->used++].used;
        ++objects->used;

        if (objects_quoted) {
          ++objects_quoted->used;
        }

        return;
      }

      if (state->status == F_data_not || state->status == F_data_not_eos || state->status == F_data_not_stop) {

        // If at least some valid object was found, then return F_none equivelents.
        if (objects->used > initial_used) {
          state->status = (state->status == F_data_not_eos) ? F_none_eos : F_none_stop;
        }

        return;
      }

      if (state->status != F_fss_found_object && state->status != F_fss_found_content && state->status != F_fss_found_content_not && state->status != F_fss_found_object_content_not) {
        return;
      }

      // When content is found, the range->start is incremented, if content is found at range->stop, then range->start will be > range.stop.
      if (range->start >= range->stop || range->start >= buffer.used) {
        if (state->status == F_fss_found_object || state->status == F_fss_found_content || state->status == F_fss_found_content_not || state->status == F_fss_found_object_content_not) {

          if (state->status == F_fss_found_object_content_not) {
            contents->array[contents->used].used = 0;
          }

          ++objects->used;
          ++contents->used;

          if (objects_quoted) {
            ++objects_quoted->used;
          }
        }

        state->status = (range->start >= buffer.used) ? F_none_eos : F_none_stop;

        return;
      }

      if (state->status == F_fss_found_object_content_not) {
        contents->array[contents->used].used = 0;
      }

      ++objects->used;
      ++contents->used;

      if (objects_quoted) {
        ++objects_quoted->used;
      }

    } while (range->start < F_string_t_size_d);

    state->status = F_status_is_error(F_number_overflow);
  }
#endif // _di_fll_fss_basic_read_

#ifndef _di_fll_fss_basic_write_
  void fll_fss_basic_write(const f_string_static_t object, const f_string_static_t content, const uint8_t quote, f_string_dynamic_t * const destination, f_state_t * const state) {
    #ifndef _di_level_2_parameter_checking_
      if (!state) return;

      if (!destination) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_2_parameter_checking_

    f_string_range_t range = macro_f_string_range_t_initialize_2(object.used);

    fl_fss_basic_object_write(object, quote, f_fss_complete_full_e, &range, destination, state);

    if (F_status_is_error(state->status) || state->status == F_data_not || state->status == F_data_not_stop || state->status == F_data_not_eos) {
      return;
    }

    if (state->status == F_none || state->status == F_none_stop || state->status == F_none_eos || state->status == F_none_eol) {
      if (content.used) {
        range.start = 0;
        range.stop = content.used - 1;

        fl_fss_basic_content_write(content, f_fss_complete_full_e, &range, destination, state);
        if (F_status_is_error(state->status)) return;
      }
      else {
        state->status = f_string_dynamic_increase(state->step_small, destination);
        if (F_status_is_error(state->status)) return;

        destination->string[destination->used++] = f_string_eol_s.string[0];
      }
    }
  }
#endif // _di_fll_fss_basic_write_

#ifdef __cplusplus
} // extern "C"
#endif
