#include "extended_list.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_extended_list_read_
  void fll_fss_extended_list_read(const f_string_static_t buffer, f_string_range_t * const range, f_string_ranges_t * const objects, f_string_rangess_t * const contents, f_number_unsigneds_t * const objects_delimits, f_number_unsigneds_t * const contents_delimits, f_string_ranges_t * const comments, f_state_t * const state) {
    #ifndef _di_level_2_parameter_checking_
      if (!state) return;

      if (!range || !objects || !contents) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_okay;
    f_number_unsigned_t initial_used = objects->used;

    bool found_data = F_false;

    do {
      state->status = f_string_ranges_increase(state->step_small, objects);
      if (F_status_is_error(state->status)) return;

      state->status = f_string_rangess_increase(state->step_small, contents);
      if (F_status_is_error(state->status)) return;

      contents->array[contents->used].used = 0;

      do {
        fl_fss_extended_list_object_read(buffer, range, &objects->array[objects->used], objects_delimits, state);
        if (F_status_is_error(state->status)) return;

        if (range->start >= range->stop || range->start >= buffer.used) {
          if (state->status == F_fss_found_object || state->status == F_fss_found_object_content_not) {
            ++objects->used;

            status = f_string_ranges_increase(state->step_small, &contents->array[contents->used]);
            if (F_status_is_error(state->status)) {
              state->status = status;

              return;
            }

            contents->array[contents->used++].used = 0;
            state->status = F_fss_found_object_content_not;

            return;
          }

          if (state->status == F_data_not) return;

          if (found_data) {
            state->status = (range->start >= buffer.used) ? F_okay_eos : F_okay_stop;
          }
          else {
            state->status = (range->start >= buffer.used) ? F_data_not_eos : F_data_not_stop;
          }

          return;
        }

        if (state->status == F_fss_found_object) {
          found_data = F_true;
          contents->array[contents->used].used = 0;

          fl_fss_extended_list_content_read(buffer, range, &contents->array[contents->used], contents_delimits ? contents_delimits : objects_delimits, comments, state);
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

      if (state->status == F_okay_eos || state->status == F_okay_stop) {
        ++contents->array[contents->used++].used;
        ++objects->used;

        return;
      }

      if (state->status == F_data_not || state->status == F_data_not_eos || state->status == F_data_not_stop) {

        // If at least some valid object was found, then return F_okay equivalents.
        if (objects->used > initial_used) {
          state->status = state->status == F_data_not_eos ? F_okay_eos : F_okay_stop;
        }

        return;
      }

      if (state->status != F_fss_found_object && state->status != F_fss_found_content && state->status != F_fss_found_content_not && state->status != F_fss_found_object_content_not) {
        return;
      }

      if (range->start >= range->stop || range->start >= buffer.used) {

        // When content is found, the range->start is incremented, if content is found at range->stop, then range->start will be > range.stop.
        if (state->status == F_fss_found_object || state->status == F_fss_found_content || state->status == F_fss_found_content_not || state->status == F_fss_found_object_content_not) {

          if (state->status == F_fss_found_object_content_not) {
            contents->array[contents->used].used = 0;
          }

          ++objects->used;
          ++contents->used;
        }

        state->status = (range->start >= buffer.used) ? F_okay_eos : F_okay_stop;

        return;
      }

      if (state->status == F_fss_found_object_content_not) {
        contents->array[contents->used].used = 0;
      }

      ++objects->used;
      ++contents->used;

    } while (range->start < F_string_t_size_d);

    state->status = F_status_is_error(F_number_overflow);
  }
#endif // _di_fll_fss_extended_list_read_

#ifndef _di_fll_fss_extended_list_write_
  void fll_fss_extended_list_write(const f_string_static_t object, const f_string_static_t content, const f_string_static_t *content_prepend, const f_string_ranges_t *ignore, f_string_dynamic_t * const destination, f_state_t * const state) {
    #ifndef _di_level_2_parameter_checking_
      if (!state) return;
    #endif // _di_level_2_parameter_checking_

    f_string_range_t range = macro_f_string_range_t_initialize_2(object.used);

    fl_fss_extended_list_object_write(object, f_fss_complete_full_e, &range, destination, state);

    if (F_status_is_error(state->status) || state->status == F_data_not || state->status == F_data_not_stop || state->status == F_data_not_eos) {
      return;
    }

    if (state->status == F_okay || state->status == F_okay_stop || state->status == F_okay_eos || state->status == F_okay_eol) {
      if (content.used) {
        range.start = 0;
        range.stop = content.used - 1;
      }
      else {
        range.start = 1;
        range.stop = 0;
      }

      fl_fss_extended_list_content_write(content, f_fss_complete_full_e, content_prepend, ignore, &range, destination, state);
    }
  }
#endif // _di_fll_fss_extended_list_write_

#ifdef __cplusplus
} // extern "C"
#endif
