#include "fss_embedded_list.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_embedded_list_read_
  f_status_t fll_fss_embedded_list_read(const f_string_static_t buffer, f_string_range_t *range, f_fss_nest_t *nest, f_fss_delimits_t *objects_delimits, f_fss_delimits_t *contents_delimits, f_fss_comments_t *comments) {
    #ifndef _di_level_2_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
      if (!nest) return F_status_set_error(F_parameter);
      if (!objects_delimits) return F_status_set_error(F_parameter);
      if (!comments) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;
    f_status_t status2 = F_none;
    f_array_length_t initial_used = 0;

    bool found_data = F_false;

    if (!nest->used) {
      macro_f_fss_nest_t_resize(status2, (*nest), f_fss_default_allocation_step);
      if (F_status_is_error(status2)) return status2;
    }
    else {
      initial_used = nest->depth[0].used;
    }

    do {
      do {
        if (nest->depth[0].used == nest->depth[0].size) {
          macro_f_fss_items_t_resize(status2, nest->depth[0], nest->depth[0].used + f_fss_default_allocation_step);
          if (F_status_is_error(status)) return status;
        }

        status = fl_fss_embedded_list_object_read(buffer, range, &nest->depth[0].array[nest->depth[0].used].object, objects_delimits);
        if (F_status_is_error(status)) return status;

        if (range->start >= range->stop || range->start >= buffer.used) {
          if (status == FL_fss_found_object || status == FL_fss_found_object_content_not) {

            // extended list requires content closure, so this could be an error.
            return FL_fss_found_object_content_not;
          }

          if (found_data) {
            if (range->start >= buffer.used) {
              return F_none_eos;
            }

            return F_none_stop;
          }
          else {
            if (range->start >= buffer.used) {
              return F_data_not_eos;
            }

            return F_data_not_stop;
          }
        }

        if (status == FL_fss_found_object) {
          found_data = F_true;

          status = fl_fss_embedded_list_content_read(buffer, range, nest, contents_delimits ? contents_delimits : objects_delimits, comments);

          break;
        }
        else if (status == FL_fss_found_object_content_not) {
          found_data = F_true;
          break;
        }
      } while (status == FL_fss_found_object_not);

      if (status == F_none_eos || status == F_none_stop) {
        return status;
      }
      else if (status == F_data_not_eos || status == F_data_not_stop) {

        // If at least some valid object was found, then return F_none equivalents.
        if (nest->depth[0].used > initial_used) {
          if (status == F_data_not_eos) return F_none_eos;
          if (status == F_data_not_stop) return F_none_stop;
        }

        return status;
      }
      else if (status == F_terminated_not_eos || status == F_terminated_not_stop || status == F_terminated_not_nest_eos || status == F_terminated_not_nest_stop) {

        // If at least some valid object was found, then return F_none equivalents.
        if (nest->depth[0].used > initial_used) {
          if (status == F_data_not_eos) return F_none_eos;
          if (status == F_data_not_stop) return F_none_stop;
        }

        return status;
      }
      else if (status != FL_fss_found_object && status != FL_fss_found_content && status != FL_fss_found_content_not && status != FL_fss_found_object_content_not) {
        return status;
      }
      // When content is found, the range->start is incremented, if content is found at range->stop, then range->start will be > range.stop.
      else if (range->start >= range->stop || range->start >= buffer.used) {
        if (range->start >= buffer.used) {
          return F_none_eos;
        }

        return F_none_stop;
      }
    } while (range->start < f_array_length_t_size);

    return F_status_is_error(F_number_overflow);
  }
#endif // _di_fll_fss_embedded_list_read_

#ifndef _di_fll_fss_embedded_list_write_string_
  f_status_t fll_fss_embedded_list_write_string(const f_string_static_t object, const f_string_static_t content, const f_string_static_t *content_prepend, const f_string_ranges_t *ignore, f_string_dynamic_t *destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = 0;
    f_string_range_t range = macro_f_string_range_t_initialize(object.used);

    status = fl_fss_embedded_list_object_write_string(object, f_fss_complete_full, &range, destination);

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

      status = fl_fss_embedded_list_content_write_string(content, f_fss_complete_full, content_prepend, ignore, &range, destination);
    }

    return status;
  }
#endif // _di_fll_fss_embedded_list_write_string_

#ifdef __cplusplus
} // extern "C"
#endif
