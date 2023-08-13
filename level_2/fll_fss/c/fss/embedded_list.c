#include "embedded_list.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_embedded_list_read_
  void fll_fss_embedded_list_read(const f_string_static_t buffer, f_string_range_t * const range, f_fss_nest_t * const nest, f_number_unsigneds_t * const objects_delimits, f_number_unsigneds_t * const contents_delimits, f_string_ranges_t * const comments, f_state_t * const state) {
    #ifndef _di_level_2_parameter_checking_
      if (!state) return;

      if (!range || !nest) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_2_parameter_checking_

    f_number_unsigned_t initial_used = 0;

    bool found_data = F_false;

    if (!nest->used) {
      state->status = f_memory_array_increase(state->step_small, sizeof(f_fss_nest_t), (void **) &nest->depth, &nest->used, &nest->size);
      if (F_status_is_error(state->status)) return;
    }
    else {
      initial_used = nest->depth[0].used;
    }

    do {
      do {
        state->status = f_memory_array_increase(state->step_small, sizeof(f_fss_item_t), (void **) &nest->depth[0].array, &nest->depth[0].used, &nest->depth[0].size);
        if (F_status_is_error(state->status)) return;

        nest->depth[nest->used].used = 0;

        fl_fss_embedded_list_object_read(buffer, range, &nest->depth[0].array[nest->depth[0].used].object, objects_delimits, state);
        if (F_status_is_error(state->status)) return;

        if (range->start >= range->stop || range->start >= buffer.used) {
          if (state->status == F_fss_found_object || state->status == F_fss_found_object_content_not) {

            // Extended list requires content closure, so this could be an error.
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

          fl_fss_embedded_list_content_read(buffer, range, nest, contents_delimits ? contents_delimits : objects_delimits, comments, state);

          break;
        }

        if (state->status == F_fss_found_object_content_not) {
          found_data = F_true;

          break;
        }

      } while (state->status == F_fss_found_object_not);

      if (state->status == F_none_eos || state->status == F_none_stop) return;

      if (state->status == F_data_not || state->status == F_data_not_eos || state->status == F_data_not_stop) {

        // If at least some valid object was found, then return F_none equivalents.
        if (nest->depth[0].used > initial_used) {
          state->status = (state->status == F_data_not_eos) ? F_none_eos : F_none_stop;
        }

        return;
      }

      if (state->status == F_end_not_eos || state->status == F_end_not_stop || state->status == F_end_not_nest_eos || state->status == F_end_not_nest_stop) {

        // If at least some valid object was found, then return F_none equivalents.
        if (nest->depth[0].used > initial_used) {
          state->status = (state->status == F_data_not_eos) ? F_none_eos : F_data_not_stop;
        }

        return;
      }

      if (state->status != F_fss_found_object && state->status != F_fss_found_content && state->status != F_fss_found_content_not && state->status != F_fss_found_object_content_not) {
        return;
      }

      if (range->start >= range->stop || range->start >= buffer.used) {

        // When content is found, the range->start is incremented, if content is found at range->stop, then range->start will be > range.stop.
        state->status = (range->start >= buffer.used) ? F_none_eos : F_none_stop;

        return;
      }

    } while (range->start < F_string_t_size_d);

    state->status = F_status_is_error(F_number_overflow);
  }
#endif // _di_fll_fss_embedded_list_read_

#ifndef _di_fll_fss_embedded_list_write_
  void fll_fss_embedded_list_write(const f_string_static_t object, const f_string_static_t content, const f_string_static_t *content_prepend, const f_string_ranges_t *ignore, f_string_dynamic_t * const destination, f_state_t * const state) {
    #ifndef _di_level_2_parameter_checking_
      if (!state) return;
    #endif // _di_level_2_parameter_checking_

    f_string_range_t range = macro_f_string_range_t_initialize_2(object.used);

    fl_fss_embedded_list_object_write(object, f_fss_complete_full_e, &range, destination, state);

    if (F_status_is_error(state->status) || state->status == F_data_not || state->status == F_data_not_stop || state->status == F_data_not_eos) {
      return;
    }

    if (state->status == F_none || state->status == F_none_stop || state->status == F_none_eos || state->status == F_none_eol) {
      if (content.used) {
        range.start = 0;
        range.stop = content.used - 1;
      }
      else {
        range.start = 1;
        range.stop = 0;
      }

      fl_fss_embedded_list_content_write(content, f_fss_complete_full_e, content_prepend, ignore, &range, destination, state);
    }
  }
#endif // _di_fll_fss_embedded_list_write_

#ifdef __cplusplus
} // extern "C"
#endif
