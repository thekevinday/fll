#include "payload.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_payload_read_
  f_status_t fll_fss_payload_read(const f_string_static_t buffer, f_state_t state, f_string_range_t * const range, f_fss_objects_t * const objects, f_fss_contents_t * const contents, f_fss_delimits_t * const objects_delimits, f_fss_delimits_t * const contents_delimits, f_fss_comments_t * const comments) {
    #ifndef _di_level_2_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!objects) return F_status_set_error(F_parameter);
      if (!contents) return F_status_set_error(F_parameter);
      if (!objects_delimits) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;
    f_status_t status2 = F_none;
    f_array_length_t initial_used = objects->used;

    bool found_data = F_false;

    do {
      status = f_string_ranges_increase(state.step_small, objects);
      if (F_status_is_error(status)) return status;

      status = f_string_rangess_increase(state.step_small, contents);
      if (F_status_is_error(status)) return status;

      do {
        status = fl_fss_basic_list_object_read(buffer, state, range, &objects->array[objects->used], objects_delimits);
        if (F_status_is_error(status)) return status;

        if (range->start >= range->stop || range->start >= buffer.used) {
          if (status == F_fss_found_object || status == F_fss_found_object_content_not) {
            if (fl_string_dynamic_partial_compare_string(f_fss_string_payload_s.string, buffer, f_fss_string_payload_s.used, objects->array[objects->used]) == F_equal_to) {
              status = F_fss_found_object_content_not;
            }
            else {

              // Returning without a "payload" is an error.
              status = F_status_set_error(F_fss_found_object_content_not);
            }

            ++objects->used;

            status2 = f_string_ranges_increase(state.step_small, &contents->array[contents->used]);
            if (F_status_is_error(status2)) return status2;

            ++contents->used;

            return status;
          }

          // Returning without a "payload" is an error.
          if (found_data) {
            if (range->start >= buffer.used) {
              return F_status_set_error(F_none_eos);
            }

            return F_status_set_error(F_none_stop);
          }

          if (range->start >= buffer.used) {
            return F_status_set_error(F_data_not_eos);
          }

          return F_status_set_error(F_data_not_stop);
        }

        if (status == F_fss_found_object) {
          found_data = F_true;

          if (fl_string_dynamic_partial_compare_string(f_fss_string_payload_s.string, buffer, f_fss_string_payload_s.used, objects->array[objects->used]) == F_equal_to) {
            status2 = f_string_ranges_increase(state.step_small, &contents->array[contents->used]);
            if (F_status_is_error(status)) return status;

            contents->array[contents->used].used = 1;
            contents->array[contents->used].array[0].start = range->start;

            if (buffer.used > range->stop) {
              contents->array[contents->used].array[0].stop = range->stop;
              range->start = range->stop + 1;
              status = F_none_stop;
            }
            else {
              contents->array[contents->used].array[0].stop = buffer.used - 1;
              range->start = buffer.used;
              status = F_none_eos;
            }

            ++objects->used;
            ++contents->used;

            return status;
          }

          status = fl_fss_basic_list_content_read(buffer, state, range, &contents->array[contents->used], contents_delimits ? contents_delimits : objects_delimits, comments);
          if (F_status_is_error(status)) return status;

          break;
        }
        else if (status == F_fss_found_object_content_not) {
          found_data = F_true;

          status2 = f_string_ranges_increase(state.step_small, &contents->array[contents->used]);
          if (F_status_is_error(status2)) return status2;

          if (fl_string_dynamic_partial_compare_string(f_fss_string_payload_s.string, buffer, f_fss_string_payload_s.used, objects->array[objects->used]) == F_equal_to) {
            ++objects->used;

            status2 = f_string_ranges_increase(state.step_small, &contents->array[contents->used]);
            if (F_status_is_error(status2)) return status2;

            ++contents->used;

            return F_none;
          }

          break;
        }
      } while (status == F_fss_found_object_not);

      if (status == F_none_eos || status == F_none_stop) {
        ++contents->array[contents->used].used;
        ++objects->used;
        ++contents->used;

        // Returning without a "payload" is an error.
        return F_status_set_error(status);
      }

      if (status == F_data_not_eos || status == F_data_not_stop) {

        // If at least some valid object was found, then return F_none equivalents.
        if (objects->used > initial_used) {

          // Returning without a "payload" is an error.
          if (status == F_data_not_eos) {
            return F_status_set_error(F_none_eos);
          }

          if (status == F_data_not_stop) {
            return F_status_set_error(F_none_stop);
          }
        }

        return F_status_set_error(status);
      }

      if (status != F_fss_found_object && status != F_fss_found_content && status != F_fss_found_content_not && status != F_fss_found_object_content_not) {
        return status;
      }

      if (range->start >= range->stop || range->start >= buffer.used) {

        // When content is found, the range->start is incremented, if content is found at range->stop, then range->start will be > range.stop.
        if (status == F_fss_found_object || status == F_fss_found_content || status == F_fss_found_content_not || status == F_fss_found_object_content_not) {
          ++objects->used;
          ++contents->used;
        }

        // Returning without a "payload" is an error.
        if (range->start >= buffer.used) {
          return F_status_set_error(F_none_eos);
        }

        return F_status_set_error(F_none_stop);
      }

      ++objects->used;
      ++contents->used;

    } while (range->start < F_string_t_size_d);

    return F_status_is_error(F_number_overflow);
  }
#endif // _di_fll_fss_payload_read_

#ifndef _di_fll_fss_payload_write_string_
  f_status_t fll_fss_payload_write_string(const f_string_static_t object, const f_string_static_t content, const bool trim, const f_string_static_t *content_prepend, f_state_t state, f_string_dynamic_t * const destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = 0;
    f_string_range_t range = macro_f_string_range_t_initialize(object.used);

    status = fl_fss_basic_list_object_write(object, trim ? f_fss_complete_full_trim_e : f_fss_complete_full_e, state, &range, destination);

    if (F_status_is_error(status) || status == F_data_not_stop || status == F_data_not_eos) {
      return status;
    }

    if (status == F_none || status == F_none_stop || status == F_none_eos || status == F_none_eol) {
      if (fl_string_dynamic_compare(f_fss_string_payload_s, object) == F_equal_to) {
        status = f_string_dynamic_increase_by(content.used, destination);
        if (F_status_is_error(status)) return status;

        f_array_length_t i = 0;

        // Copy in blocks to allow for interruptability of potentially large data sets.
        for (; i < content.used && i + F_fss_default_block_size_normal_d < content.used; i += F_fss_default_block_size_normal_d) {

          if (state.interrupt) {
            status = state.interrupt((void *) &state, 0);

            if (F_status_set_fine(status) == F_interrupt) {
              return F_status_set_error(F_interrupt);
            }
          }

          memcpy(destination->string + destination->used + i, content.string + i, sizeof(unsigned char) * F_fss_default_block_size_normal_d);
        } // for

        if (i < content.used) {
          memcpy(destination->string + destination->used + i, content.string + i, sizeof(unsigned char) * (content.used - i));
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

        status = fl_fss_basic_list_content_write(content, f_fss_complete_full_e, content_prepend, state, &range, destination);
      }
    }

    return status;
  }
#endif // _di_fll_fss_payload_write_string_

#ifdef __cplusplus
} // extern "C"
#endif
