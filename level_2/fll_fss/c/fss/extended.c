#include "extended.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_extended_read_
  void fll_fss_extended_read(const f_string_static_t buffer, f_range_t * const range, f_ranges_t * const objects, f_rangess_t * const contents, f_uint8s_t * const objects_quoted, f_uint8ss_t * const contents_quoted, f_number_unsigneds_t * const objects_delimits, f_number_unsigneds_t * const contents_delimits, f_state_t * const state) {
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

    uint8_t *quoted_object = 0;
    f_uint8s_t *quoted_content = 0;

    do {
      state->status = f_memory_array_increase(state->step_small, sizeof(f_range_t), (void **) &objects->array, &objects->used, &objects->size);
      if (F_status_is_error(state->status)) return;

      state->status = f_memory_array_increase(state->step_small, sizeof(f_ranges_t), (void **) &contents->array, &contents->used, &contents->size);
      if (F_status_is_error(state->status)) return;

      contents->array[contents->used].used = 0;

      if (objects_quoted) {
        state->status = f_memory_array_increase(state->step_small, sizeof(uint8_t), (void **) &objects_quoted->array, &objects_quoted->used, &objects_quoted->size);
        if (F_status_is_error(state->status)) return;
      }

      if (contents_quoted) {
        state->status = f_memory_array_increase(state->step_small, sizeof(f_uint8s_t), (void **) &contents_quoted->array, &contents_quoted->used, &contents_quoted->size);
        if (F_status_is_error(state->status)) return;

        contents_quoted->array[contents_quoted->used].used = 0;
      }

      do {
        if (objects_quoted) {
          quoted_object = &objects_quoted->array[objects_quoted->used];
        }

        fl_fss_extended_object_read(buffer, range, &objects->array[objects->used], quoted_object, objects_delimits, state);
        if (F_status_is_error(state->status)) return;

        if (range->start >= range->stop || range->start >= buffer.used) {
          if (state->status == F_fss_found_object || state->status == F_fss_found_object_content_not) {
            state->status = F_fss_found_object_content_not;

            break;
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

          if (contents_quoted) {
            quoted_content = &contents_quoted->array[contents_quoted->used];
            quoted_content->used = 0;
          }

          fl_fss_extended_content_read(buffer, range, &contents->array[contents->used], quoted_content, contents_delimits ? contents_delimits : objects_delimits, state);
          if (F_status_is_error(state->status)) return;

          break;
        }

        if (state->status == F_fss_found_object_content_not) break;

      } while (state->status == F_fss_found_object_not);

      if (state->status == F_okay_eos || state->status == F_okay_stop) {
        ++contents->array[contents->used++].used;
        ++objects->used;

        if (objects_quoted) {
          ++objects_quoted->used;
        }

        if (contents_quoted) {
          ++contents_quoted->array[contents_quoted->used].used;
          ++contents_quoted->used;
        }

        return;
      }

      if (state->status == F_data_not || state->status == F_data_not_eos || state->status == F_data_not_stop || state->status == F_end_not_group_eos || state->status == F_end_not_group_stop) {

        // If at least some valid object was found, then return F_okay equivelents.
        if (objects->used > initial_used) {
          state->status = (state->status == F_data_not_eos) ? F_okay_eos : F_okay_stop;
        }

        return;
      }

      if (state->status != F_fss_found_object && state->status != F_fss_found_content && state->status != F_fss_found_content_not && state->status != F_fss_found_object_content_not && state->status != F_end_not_group) {
        return;
      }

      if (state->status == F_fss_found_object_content_not) {
        found_data = F_true;
        contents->array[contents->used].used = 0;

        status = f_memory_array_increase(state->step_small, sizeof(f_range_t), (void **) &contents->array[contents->used].array, &contents->array[contents->used].used, &contents->array[contents->used].size);

        if (F_status_is_error(status)) {
          state->status = status;

          return;
        }
      }

      if (range->start >= range->stop || range->start >= buffer.used) {

        // When content is found, the range->start is incremented, if content is found at range->stop, then range->start will be > range.stop.
        if (state->status == F_fss_found_object || state->status == F_fss_found_content || state->status == F_fss_found_content_not || state->status == F_fss_found_object_content_not || state->status == F_end_not_group) {
          ++objects->used;
          ++contents->used;

          if (objects_quoted) {
            ++objects_quoted->used;
          }

          if (contents_quoted) {
            ++contents_quoted->used;
          }
        }

        if (range->start >= buffer.used) {
          state->status = (state->status == F_end_not_group) ? F_end_not_group_eos : F_okay_eos;

          return;
        }

        state->status = (state->status == F_end_not_group) ? F_end_not_group_stop : F_okay_stop;

        return;
      }

      ++objects->used;
      ++contents->used;

      if (objects_quoted) {
        ++objects_quoted->used;
      }

      if (contents_quoted) {
        ++contents_quoted->used;
      }

    } while (range->start < F_string_t_size_d);

    state->status = F_status_is_error(F_number_overflow);
  }
#endif // _di_fll_fss_extended_read_

#ifndef _di_fll_fss_extended_write_
  void fll_fss_extended_write(const f_string_static_t object, const f_string_statics_t contents, const uint8_t quote, f_string_dynamic_t * const destination, f_state_t * const state) {
    #ifndef _di_level_2_parameter_checking_
      if (!state) return;
    #endif // _di_level_2_parameter_checking_

    f_range_t range = macro_f_range_t_initialize_2(object.used);

    fl_fss_extended_object_write(object, quote, f_fss_complete_full_e, &range, destination, state);

    if (F_status_is_error(state->status) || state->status == F_data_not || state->status == F_data_not_stop || state->status == F_data_not_eos) {
      return;
    }

    if (state->status == F_okay || state->status == F_okay_stop || state->status == F_okay_eos || state->status == F_okay_eol) {
      uint8_t complete = f_fss_complete_next_e;

      for (f_number_unsigned_t i = 0; i < contents.used; ++i) {

        if (i + 1 == contents.used) {
          complete = f_fss_complete_end_e;
        }

        if (contents.array[i].used) {
          range.start = 0;
          range.stop = contents.array[i].used - 1;
        }
        else {
          range.start = 1;
          range.stop = 0;
        }

        fl_fss_extended_content_write(contents.array[i], quote, complete, &range, destination, state);
        if (F_status_is_error(state->status)) return;
      } // for
    }
  }
#endif // _di_fll_fss_extended_write_

#ifdef __cplusplus
} // extern "C"
#endif
