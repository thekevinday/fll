#include "extended_list.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_extended_list_read_
  f_status_t fll_fss_extended_list_read(const f_string_static_t buffer, f_state_t state, f_string_range_t * const range, f_fss_objects_t * const objects, f_fss_contents_t * const contents, f_fss_delimits_t * const objects_delimits, f_fss_delimits_t * const contents_delimits, f_fss_comments_t * const comments) {
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

      contents->array[contents->used].used = 0;

      do {
        status = fl_fss_extended_list_object_read(buffer, state, range, &objects->array[objects->used], objects_delimits);
        if (F_status_is_error(status)) return status;

        if (range->start >= range->stop || range->start >= buffer.used) {
          if (status == F_fss_found_object || status == F_fss_found_object_content_not) {
            ++objects->used;

            status2 = f_string_ranges_increase(state.step_small, &contents->array[contents->used]);
            if (F_status_is_error(status2)) return status2;

            contents->array[contents->used++].used = 0;

            return F_fss_found_object_content_not;
          }

          if (found_data) {
            if (range->start >= buffer.used) return F_none_eos;

            return F_none_stop;
          }

          if (range->start >= buffer.used) return F_data_not_eos;

          return F_data_not_stop;
        }

        if (status == F_fss_found_object) {
          found_data = F_true;

          contents->array[contents->used].used = 0;

          status = fl_fss_extended_list_content_read(buffer, state, range, &contents->array[contents->used], contents_delimits ? contents_delimits : objects_delimits, comments);
          if (F_status_is_error(status)) return status;

          break;
        }
        else if (status == F_fss_found_object_content_not) {
          found_data = F_true;

          status2 = f_string_ranges_increase(state.step_small, &contents->array[contents->used]);
          if (F_status_is_error(status2)) return status2;

          break;
        }
      } while (status == F_fss_found_object_not);

      if (status == F_none_eos || status == F_none_stop) {
        ++contents->array[contents->used].used;
        ++objects->used;
        ++contents->used;

        return status;
      }

      if (status == F_data_not_eos || status == F_data_not_stop) {

        // If at least some valid object was found, then return F_none equivalents.
        if (objects->used > initial_used) {
          if (status == F_data_not_eos) return F_none_eos;
          if (status == F_data_not_stop) return F_none_stop;
        }

        return status;
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

        if (range->start >= buffer.used) return F_none_eos;

        return F_none_stop;
      }

      ++objects->used;
      ++contents->used;

    } while (range->start < F_string_t_size_d);

    return F_status_is_error(F_number_overflow);
  }
#endif // _di_fll_fss_extended_list_read_

#ifndef _di_fll_fss_extended_list_write_
  f_status_t fll_fss_extended_list_write(const f_string_static_t object, const f_string_static_t content, const f_string_static_t *content_prepend, const f_string_ranges_t *ignore, f_state_t state, f_string_dynamic_t * const destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = 0;
    f_string_range_t range = macro_f_string_range_t_initialize2(object.used);

    status = fl_fss_extended_list_object_write(object, f_fss_complete_full_e, state, &range, destination);

    if (F_status_is_error(status) || status == F_data_not_stop || status == F_data_not_eos) {
      return status;
    }

    if (status == F_none || status == F_none_stop || status == F_none_eos || status == F_none_eol) {
      if (content.used) {
        range.start = 0;
        range.stop = content.used - 1;
      }
      else {
        range.start = 1;
        range.stop = 0;
      }

      status = fl_fss_extended_list_content_write(content, f_fss_complete_full_e, content_prepend, ignore, state, &range, destination);
    }

    return status;
  }
#endif // _di_fll_fss_extended_list_write_

#ifdef __cplusplus
} // extern "C"
#endif
