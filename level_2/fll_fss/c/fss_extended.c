#include "fss_extended.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_extended_read_
  f_status_t fll_fss_extended_read(const f_string_static_t buffer, f_state_t state, f_string_range_t *range, f_fss_objects_t *objects, f_fss_contents_t *contents, f_fss_quotes_t *objects_quoted, f_fss_quotess_t *contents_quoted, f_fss_delimits_t *objects_delimits, f_fss_delimits_t *contents_delimits) {
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

    f_fss_quote_t *quoted_object = 0;
    f_fss_quotes_t *quoted_content = 0;

    do {
      if (objects->used == objects->size) {
        macro_f_fss_objects_t_increase(status2, f_fss_default_allocation_step_small, (*objects));
        if (F_status_is_error(status2)) return status2;

        macro_f_fss_contents_t_increase(status2, f_fss_default_allocation_step_small, (*contents));
        if (F_status_is_error(status2)) return status2;

        if (objects_quoted) {
          macro_f_fss_quotes_t_increase(status2, f_fss_default_allocation_step_small, (*objects_quoted));
          if (F_status_is_error(status2)) return status2;
        }

        if (contents_quoted) {
          macro_f_fss_quotess_t_increase(status2, f_fss_default_allocation_step_small, (*contents_quoted));
          if (F_status_is_error(status2)) return status2;
        }
      }

      do {
        if (objects_quoted) {
          quoted_object = &objects_quoted->array[objects_quoted->used];
        }

        status = fl_fss_extended_object_read(buffer, state, range, &objects->array[objects->used], quoted_object, objects_delimits);
        if (F_status_is_error(status)) return status;

        if (range->start >= range->stop || range->start >= buffer.used) {
          if (status == FL_fss_found_object || status == FL_fss_found_object_content_not) {
            ++objects->used;

            if (objects_quoted) {
              ++objects_quoted->used;
            }

            macro_f_fss_content_t_increase(status2, f_fss_default_allocation_step_small, contents->array[contents->used])
            if (F_status_is_error(status2)) return status2;

            ++contents->used;

            if (contents_quoted) {
              macro_f_fss_quotes_t_increase(status2, f_fss_default_allocation_step_small, contents_quoted->array[contents_quoted->used])
              if (F_status_is_error(status2)) return status2;

              ++contents_quoted->used;
            }

            return FL_fss_found_object_content_not;
          }

          if (found_data) {
            if (range->start >= buffer.used) {
               return F_none_eos;
            }

            return F_none_stop;
          }

          if (range->start >= buffer.used) {
             return F_data_not_eos;
          }

          return F_data_not_stop;
        }

        if (status == FL_fss_found_object) {
          found_data = F_true;

          if (contents_quoted) {
            macro_f_fss_quotes_t_increase(status2, f_fss_default_allocation_step_small, contents_quoted->array[contents_quoted->used])
            if (F_status_is_error(status2)) return status2;

            quoted_content = &contents_quoted->array[contents_quoted->used];
          }

          status = fl_fss_extended_content_read(buffer, state, range, &contents->array[contents->used], quoted_content, contents_delimits ? contents_delimits : objects_delimits);
          if (F_status_is_error(status)) return status;

          break;
        }
        else if (status == FL_fss_found_object_content_not) {
          found_data = F_true;
          break;
        }

      } while (status == FL_fss_found_object_not);

      if (status == F_none_eos || status == F_none_stop) {
        contents->array[contents->used].used++;

        ++objects->used;
        ++contents->used;

        if (objects_quoted) {
          ++objects_quoted->used;
        }

        if (contents_quoted) {
          ++contents_quoted->array[contents_quoted->used].used;
          ++contents_quoted->used;
        }

        return status;
      }
      else if (status == F_data_not_eos || status == F_data_not_stop || status == F_terminated_not_group_eos || status == F_terminated_not_group_stop) {

        // If at least some valid object was found, then return F_none equivelents.
        if (objects->used > initial_used) {
          if (status == F_data_not_eos) {
            return F_none_eos;
          }

          if (status == F_data_not_stop) {
            return F_none_stop;
          }
        }

        return status;
      }
      else if (status != FL_fss_found_object && status != FL_fss_found_content && status != FL_fss_found_content_not && status != FL_fss_found_object_content_not && status != F_terminated_not_group) {
        return status;
      }
      else if (range->start >= range->stop || range->start >= buffer.used) {

        // When content is found, the range->start is incremented, if content is found at range->stop, then range->start will be > range.stop.
        if (status == FL_fss_found_object || status == FL_fss_found_content || status == FL_fss_found_content_not || status == FL_fss_found_object_content_not || status == F_terminated_not_group) {
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
          if (status == F_terminated_not_group) {
            return F_terminated_not_group_eos;
          }

          return F_none_eos;
        }

        if (status == F_terminated_not_group) {
          return F_terminated_not_group_stop;
        }

        return F_none_stop;
      }

      ++objects->used;
      ++contents->used;

      if (objects_quoted) {
        ++objects_quoted->used;
      }

      if (contents_quoted) {
        ++contents_quoted->used;
      }

    } while (range->start < f_string_t_size);

    return F_status_is_error(F_number_overflow);
  }
#endif // _di_fll_fss_extended_read_

#ifndef _di_fll_fss_extended_write_string_
  f_status_t fll_fss_extended_write_string(const f_string_static_t object, const f_string_statics_t contents, const f_fss_quote_t quote, f_state_t state, f_string_dynamic_t *destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = 0;
    f_string_range_t range = macro_f_string_range_t_initialize(object.used);

    status = fl_fss_extended_object_write_string(object, quote, f_fss_complete_full, state, &range, destination);

    if (F_status_is_error(status) || status == F_data_not_stop || status == F_data_not_eos) {
      return status;
    }

    if (status == F_none || status == F_none_stop || status == F_none_eos || status == F_none_eol) {
      uint8_t complete = f_fss_complete_next;

      for (f_array_length_t i = 0; i < contents.used; ++i) {

        if (i + 1 == contents.used) {
          complete = f_fss_complete_end;
        }

        if (contents.array[i].used) {
          range.start = 0;
          range.stop = contents.array[i].used - 1;
        }
        else {
          range.start = 1;
          range.stop = 0;
        }

        status = fl_fss_extended_content_write_string(contents.array[i], quote, complete, state, &range, destination);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return status;
  }
#endif // _di_fll_fss_extended_write_string_

#ifdef __cplusplus
} // extern "C"
#endif
