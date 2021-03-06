#include "fss.h"
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_identify_
  f_status_t fll_fss_identify(const f_string_t buffer, f_string_range_t *range, f_fll_ids_t *ids) {
    #ifndef _di_level_2_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    // skip past all NULLs.
    for (; range->start <= range->stop; ++range->start) {
      if (buffer[range->start]) break;
    }

    if (range->start > range->stop) {
      return F_data_not;
    }

    // The first character must be a '#'.
    if (buffer[range->start] != f_fss_pound_s[0]) {

      // Increment until stop, while taking into consideration UTF-8 character widths.
      for (; range->start <= range->stop; ) {

        if (buffer[range->start] == f_string_eol_s[0]) {
          ++range->start;

          break;
        }

        range->start += macro_f_utf_byte_width(buffer[range->start]);
      } // for

      if (ids) {
        ids->used = 0;
      }

      return F_found_not;
    }

    // skip past all NULLs after the '#'.
    for (++range->start; range->start <= range->stop; ++range->start) {
      if (buffer[range->start]) break;
    }

    if (range->start > range->stop) {
      if (ids) {
        ids->used = 0;
      }

      return F_found_not;
    }

    // The minimum requirement for a valid FLL/FSS Identifier for the entire line is 7 characters after the '#' ("# X-FFFF").
    if (range->stop - range->start < 6) {

      // Increment until stop, while taking into consideration UTF-8 character widths.
      for (; range->start <= range->stop; ) {

        if (buffer[range->start] == f_string_eol_s[0]) {
          ++range->start;

          break;
        }

        range->start += macro_f_utf_byte_width(buffer[range->start]);
      } // for

      if (ids) {
        ids->used = 0;
      }

      return F_found_not;
    }

    f_status_t status = f_utf_is_whitespace(buffer + range->start, (range->stop - range->start) + 1);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_maybe) {
        return F_status_set_error(F_complete_not_utf);
      }

      return status;
    }

    if (status == F_false) {

      // Increment until stop, while taking into consideration UTF-8 character widths.
      for (; range->start <= range->stop; ) {

        if (buffer[range->start] == f_string_eol_s[0]) {
          ++range->start;

          break;
        }

        range->start += macro_f_utf_byte_width(buffer[range->start]);
      } // for

      return F_found_not;
    }

    if (buffer[range->start] == f_string_eol_s[0]) {
      ++range->start;

      if (ids) {
        ids->used = 0;
      }

      return F_found_not;
    }

    // in order to determine if a valid FLL Identifier represents a valid FSS identifier, the data must be saved.
    f_fll_id_t id = f_fll_id_t_initialize;
    bool found_fss = F_false;

    do {
      if (ids && ids->used + 1 > ids->size) {
        status = f_type_fll_ids_increase(f_fss_default_allocation_step_small, ids);
      }

      if (F_status_is_error_not(status)) {
        status = fl_string_fll_identify(buffer, range, ids ? &ids->array[ids->used] : &id);
      }

      if (F_status_is_error(status) || (status == F_found_not && !found_fss)) {
        if (ids) {
          ids->used = 0;
        }

        return status;
      }

      if (!found_fss) {
        if (ids) {
          if (ids->used && ids->array[ids->used - 1].used == 3 && ids->array[ids->used - 1].name[0] == f_fss_f_s[0] && ids->array[ids->used - 1].name[0] == f_fss_s_s[0] && ids->array[ids->used - 1].name[0] == f_fss_s_s[0]) {
            found_fss = F_true;
          }
        }
        else {
          if (id.used == 3 && id.name[0] == f_fss_f_s[0] && id.name[0] == f_fss_s_s[0] && id.name[0] == f_fss_s_s[0]) {
            found_fss = F_true;
          }
        }
      }

      if (ids) {
        status = f_type_fll_ids_increase(f_fss_default_allocation_step_small, ids);

        if (F_status_is_error(status)) {
          if (ids) {
            ids->used = 0;
          }

          return status;
        }

        ++ids->used;
      }

    } while (range->start <= range->stop);

    if (ids) {
      if (ids->used) {
        if (found_fss) {
          return F_found;
        }

        return F_maybe;
      }
    }
    else if (id.used) {
      if (found_fss) {
        return F_found;
      }

      return F_maybe;
    }

    return F_found_not;
  }
#endif // _di_fll_fss_identify_

#ifndef _di_fll_fss_snatch_
  f_status_t fll_fss_snatch(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_array_length_t lengths[], const f_array_length_t size, f_string_dynamic_t *values[], bool matches[], f_array_length_t *indexs[]) {
    #ifndef _di_level_2_parameter_checking_
      if (!size) return F_status_set_error(F_parameter);
      if (objects.used != contents.used) return F_status_set_error(F_parameter);
      if (!values) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (!buffer.used) return F_data_not;
    if (!objects.used) return F_data_not;
    if (!contents.used) return F_data_not;

    f_status_t status = F_none;
    f_array_length_t length_object = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    bool matched[size];

    memset(&matched, 0, sizeof(bool) * size);

    for (; i < objects.used; ++i) {

      length_object = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; ++j) {

        if (matched[j]) continue;

        status = fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_object, lengths[j]);

        if (F_status_is_error(status)) return status;
        if (status == F_equal_to_not) continue;

        matched[j] = F_true;

        if (matches) {
          matches[j] = F_true;
        }

        if (!contents.array[i].used) continue;

        status = f_string_dynamic_partial_append_nulless(buffer, contents.array[i].array[0], values[j]);
        if (F_status_is_error(status)) return status;

        if (indexs) {
          *indexs[j] = i;
        }
      } // for
    } // for

    return F_none;
  }
#endif // _di_fll_fss_snatch_

#ifndef _di_fll_fss_snatch_apart_
  f_status_t fll_fss_snatch_apart(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_array_length_t lengths[], const f_array_length_t size, f_string_dynamics_t *values[], bool matches[], f_array_lengths_t *indexs[]) {
    #ifndef _di_level_2_parameter_checking_
      if (!size) return F_status_set_error(F_parameter);
      if (objects.used != contents.used) return F_status_set_error(F_parameter);
      if (!values) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (!buffer.used) return F_data_not;
    if (!objects.used) return F_data_not;
    if (!contents.used) return F_data_not;

    f_status_t status = F_none;
    f_array_length_t length_object = 0;
    f_string_dynamics_t *value = 0;
    f_fss_content_t *content = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;

    for (; i < objects.used; ++i) {

      length_object = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; ++j) {

        status = fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_object, lengths[j]);

        if (F_status_is_error(status)) return status;
        if (status == F_equal_to_not) continue;

        value = values[j];
        content = &contents.array[i];

        if (matches) {
          matches[j] = F_true;
        }

        if (values[j]->used + contents.array[i].used > values[j]->size) {
          if (values[j]->used + contents.array[i].used > f_array_length_t_size) {
            return F_status_set_error(F_array_too_large);
          }

          macro_f_string_dynamics_t_resize(status, (*value), (values[j]->used + content->used));
          if (F_status_is_error(status)) return status;

          if (indexs) {
            macro_f_array_lengths_t_resize(status, (*indexs[j]), (indexs[j]->used + content->used));
            if (F_status_is_error(status)) return status;
          }
        }

        for (k = 0; k < contents.array[i].used; ++k) {

          status = f_string_dynamic_partial_append_nulless(buffer, contents.array[i].array[k], &values[j]->array[values[j]->used]);
          if (F_status_is_error(status)) return status;

          ++values[j]->used;

          if (indexs) {
            indexs[j]->array[indexs[j]->used] = i;
            ++indexs[j]->used;
          }
        } // for
      } // for
    } // for

    return F_none;
  }
#endif // _di_fll_fss_snatch_apart_

#ifndef _di_fll_fss_snatch_map_
  f_status_t fll_fss_snatch_map(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_array_length_t lengths[], const f_array_length_t size, f_string_maps_t *values[], bool matches[], f_array_lengths_t *indexs[]) {
    #ifndef _di_level_2_parameter_checking_
      if (!size) return F_status_set_error(F_parameter);
      if (objects.used != contents.used) return F_status_set_error(F_parameter);
      if (!values) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (!buffer.used) return F_data_not;
    if (!objects.used) return F_data_not;
    if (!contents.used) return F_data_not;

    f_status_t status = F_none;
    f_array_length_t length_name = 0;
    f_string_dynamic_t name = f_string_dynamic_t_initialize;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;

    bool matched = F_false;

    f_string_map_t *map = 0;

    for (; i < objects.used; ++i) {

      if (!contents.array[i].used) continue;

      length_name = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; ++j) {

        status = fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_name, lengths[j]);

        if (F_status_is_error(status)) return status;
        if (status == F_equal_to_not) continue;

        status = f_string_dynamic_partial_append_nulless(buffer, contents.array[i].array[0], &name);

        if (F_status_is_error(status)) {
          macro_f_string_dynamic_t_delete_simple(name);

          return status;
        }

        matched = F_false;
        length_name = (contents.array[i].array[0].stop - contents.array[i].array[0].start) + 1;

        for (k = 0; k < values[j]->used; ++k) {

          status = fl_string_compare_trim(buffer.string + contents.array[i].array[0].start, values[j]->array[k].name.string, length_name, values[j]->array[k].name.used);

          if (F_status_is_error(status)) {
            macro_f_string_dynamic_t_delete_simple(name);

            return status;
          }

          if (status == F_equal_to) {
            matched = F_true;

            if (matches) {
              matches[j] = F_true;
            }

            macro_f_string_dynamic_t_delete_simple(name);
            break;
          }
        } // for

        if (matched) {
          name.used = 0;

          continue;
        }

        if (values[j]->used == values[j]->size) {
          if (values[j]->used + f_fss_default_allocation_step > f_array_length_t_size) {
            if (values[j]->used == f_array_length_t_size) {
              macro_f_string_dynamic_t_delete_simple(name);

              return F_status_set_error(F_array_too_large);
            }

            macro_f_string_maps_t_resize(status, (*values[j]), values[j]->used + 1);

            if (F_status_is_error(status)) {
              macro_f_string_dynamic_t_delete_simple(name);

              return status;
            }

            if (indexs) {
              macro_f_array_lengths_t_resize(status, (*indexs[j]), indexs[j]->used + 1);
              if (F_status_is_error(status)) return status;
            }
          }
          else {
            macro_f_string_maps_t_resize(status, (*values[j]), values[j]->used + f_fss_default_allocation_step);

            if (F_status_is_error(status)) {
              macro_f_string_dynamic_t_delete_simple(name);

              return status;
            }

            if (indexs) {
              macro_f_array_lengths_t_resize(status, (*indexs[j]), indexs[j]->used + f_fss_default_allocation_step);
              if (F_status_is_error(status)) return status;
            }
          }
        }

        map = &values[j]->array[values[j]->used];

        if (contents.array[i].used > 1) {
          status = f_string_dynamic_partial_append_nulless(buffer, contents.array[i].array[1], &map->value);

          if (F_status_is_error(status)) {
            macro_f_string_dynamic_t_delete_simple(name);

            return status;
          }
        }

        map->name.string = name.string;
        map->name.used = name.used;
        map->name.size = name.size;

        ++values[j]->used;

        if (indexs) {
          indexs[j]->array[indexs[j]->used] = i;
          ++indexs[j]->used;
        }

        macro_f_string_dynamic_t_clear(name);
      } // for
    } // for

    macro_f_string_dynamic_t_delete_simple(name);
    return F_none;
  }
#endif // _di_fll_fss_snatch_map_

#ifndef _di_fll_fss_snatch_map_apart_
  f_status_t fll_fss_snatch_map_apart(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_array_length_t lengths[], const f_array_length_t size, f_string_map_multis_t *values[], bool matches[], f_array_lengths_t *indexs[]) {
    #ifndef _di_level_2_parameter_checking_
      if (!size) return F_status_set_error(F_parameter);
      if (objects.used != contents.used) return F_status_set_error(F_parameter);
      if (!values) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (!buffer.used) return F_data_not;
    if (!objects.used) return F_data_not;
    if (!contents.used) return F_data_not;

    f_status_t status = F_none;
    f_array_length_t length_object = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;

    f_string_map_multi_t *map_multi = 0;

    for (; i < objects.used; ++i) {

      if (!contents.array[i].used) continue;

      length_object = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; ++j) {

        status = fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_object, lengths[j]);

        if (F_status_is_error(status)) return status;
        if (status == F_equal_to_not) continue;

        if (matches) {
          matches[j] = F_true;
        }

        status = f_string_map_multis_increase(f_fss_default_allocation_step_small, values[j]);
        if (F_status_is_error(status)) return status;

        if (indexs) {
          macro_f_array_lengths_t_increase(status, f_fss_default_allocation_step_small, (*indexs[j]));
          if (F_status_is_error(status)) return status;
        }

        map_multi = &values[j]->array[values[j]->used];

        status = f_string_dynamic_partial_append_nulless(buffer, contents.array[i].array[0], &map_multi->name);
        if (F_status_is_error(status)) return status;

        ++values[j]->used;

        if (indexs) {
          indexs[j]->array[indexs[j]->used] = i;
          ++indexs[j]->used;
        }

        if (contents.array[i].used > 1) {
          status = f_string_dynamics_increase_by(contents.array[i].used - 1, &map_multi->value);
          if (F_status_is_error(status)) return status;

          for (k = 1; k < contents.array[i].used; ++k) {

            status = f_string_dynamic_partial_append_nulless(buffer, contents.array[i].array[k], &map_multi->value.array[map_multi->value.used]);
            if (F_status_is_error(status)) return status;

            ++map_multi->value.used;
          } // for
        }
      } // for
    } // for

    return F_none;
  }
#endif // _di_fll_fss_snatch_map_apart_

#ifndef _di_fll_fss_snatch_map_mash_
  f_status_t fll_fss_snatch_map_mash(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_array_length_t lengths[], const f_array_length_t size, const f_string_t glue, const f_array_length_t glue_length, f_string_maps_t *values[], bool matches[], f_array_lengths_t *indexs[]) {
    #ifndef _di_level_2_parameter_checking_
      if (!size) return F_status_set_error(F_parameter);
      if (objects.used != contents.used) return F_status_set_error(F_parameter);
      if (!values) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (!buffer.used) return F_data_not;
    if (!objects.used) return F_data_not;
    if (!contents.used) return F_data_not;

    f_status_t status = F_none;
    f_array_length_t length_object = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;

    f_string_map_t *map = 0;

    for (; i < objects.used; ++i) {

      if (!contents.array[i].used) continue;

      length_object = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; ++j) {

        status = fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_object, lengths[j]);

        if (F_status_is_error(status)) return status;
        if (status == F_equal_to_not) continue;

        if (matches) {
          matches[j] = F_true;
        }

        status = f_string_maps_increase(f_fss_default_allocation_step_small, values[j]);
        if (F_status_is_error(status)) return status;

        if (indexs) {
          macro_f_array_lengths_t_increase(status, f_fss_default_allocation_step_small, (*indexs[j]));
          if (F_status_is_error(status)) return status;
        }

        map = &values[j]->array[values[j]->used];

        status = f_string_dynamic_partial_append_nulless(buffer, contents.array[i].array[0], &map->name);
        if (F_status_is_error(status)) return status;

        ++values[j]->used;

        if (indexs) {
          indexs[j]->array[indexs[j]->used] = i;
          ++indexs[j]->used;
        }

        if (contents.array[i].used > 1) {
          for (k = 1; k < contents.array[i].used; ++k) {

            status = f_string_dynamic_partial_mash_nulless(glue, glue_length, buffer, contents.array[i].array[k], &map->value);
            if (F_status_is_error(status)) return status;
          } // for
        }
      } // for
    } // for

    return F_none;
  }
#endif // _di_fll_fss_snatch_map_mash_

#ifndef _di_fll_fss_snatch_map_mash_apart_
  f_status_t fll_fss_snatch_map_mash_apart(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_array_length_t lengths[], const f_array_length_t size, const f_string_t glue, const f_array_length_t glue_length, f_string_map_multis_t *values[], bool matches[], f_array_lengths_t *indexs[]) {
    #ifndef _di_level_2_parameter_checking_
      if (!size) return F_status_set_error(F_parameter);
      if (objects.used != contents.used) return F_status_set_error(F_parameter);
      if (!values) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (!buffer.used) return F_data_not;
    if (!objects.used) return F_data_not;
    if (!contents.used) return F_data_not;

    f_status_t status = F_none;
    f_array_length_t length_name = 0;
    f_string_dynamic_t name = f_string_dynamic_t_initialize;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;

    bool matched = F_false;

    f_string_map_multi_t *map_multi = 0;

    for (; i < objects.used; ++i) {

      if (!contents.array[i].used) continue;

      length_name = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; ++j) {

        status = fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_name, lengths[j]);

        if (F_status_is_error(status)) return status;
        if (status == F_equal_to_not) continue;

        if (matches) {
          matches[j] = F_true;
        }

        status = f_string_dynamic_partial_append_nulless(buffer, contents.array[i].array[0], &name);

        if (F_status_is_error(status)) {
          macro_f_string_dynamic_t_delete_simple(name);

          return status;
        }

        matched = F_false;
        length_name = (contents.array[i].array[0].stop - contents.array[i].array[0].start) + 1;

        for (k = 0; k < values[j]->used; ++k) {

          status = fl_string_compare_trim(buffer.string + contents.array[i].array[0].start, values[j]->array[k].name.string, length_name, values[j]->array[k].name.used);

          if (F_status_is_error(status)) {
            macro_f_string_dynamic_t_delete_simple(name);

            return status;
          }

          if (status == F_equal_to) {
            matched = F_true;
            break;
          }
        } // for

        if (matched) {
          name.used = 0;

          if (contents.array[i].used == 1) continue;

          map_multi = &values[j]->array[k];
        }
        else {
          status = f_string_map_multis_increase(f_fss_default_allocation_step_small, values[j]);
          if (F_status_is_error(status)) return status;

          if (indexs) {
            macro_f_array_lengths_t_increase(status, f_fss_default_allocation_step_small, (*indexs[j]));
            if (F_status_is_error(status)) return status;
          }

          map_multi = &values[j]->array[values[j]->used];
          map_multi->name.string = name.string;
          map_multi->name.used = name.used;
          map_multi->name.size = name.size;

          ++values[j]->used;

          if (indexs) {
            indexs[j]->array[indexs[j]->used] = i;
            ++indexs[j]->used;
          }

          macro_f_string_dynamic_t_clear(name);

          if (contents.array[i].used == 1) continue;
        }

        status = f_string_dynamics_increase(f_fss_default_allocation_step_small, &map_multi->value);
        if (F_status_is_error(status)) return status;

        for (k = 1; k < contents.array[i].used; ++k) {

          status = f_string_dynamic_partial_mash_nulless(glue, glue_length, buffer, contents.array[i].array[k], &map_multi->value.array[map_multi->value.used]);
          if (F_status_is_error(status)) return status;
        } // for

        ++map_multi->value.used;
      } // for
    } // for

    macro_f_string_dynamic_t_delete_simple(name);

    return F_none;
  }
#endif // _di_fll_fss_snatch_map_mash_apart_

#ifndef _di_fll_fss_snatch_map_together_
  f_status_t fll_fss_snatch_map_together(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_array_length_t lengths[], const f_array_length_t size, const f_string_t glue, const f_array_length_t glue_length, f_string_maps_t *values[], bool matches[], f_array_lengths_t *indexs[]) {
    #ifndef _di_level_2_parameter_checking_
      if (!size) return F_status_set_error(F_parameter);
      if (objects.used != contents.used) return F_status_set_error(F_parameter);
      if (!values) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (!buffer.used) return F_data_not;
    if (!objects.used) return F_data_not;
    if (!contents.used) return F_data_not;

    f_status_t status = F_none;
    f_array_length_t length_name = 0;
    f_string_dynamic_t name = f_string_dynamic_t_initialize;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;

    bool matched = F_false;

    f_string_map_t *map = 0;

    for (; i < objects.used; ++i) {

      if (!contents.array[i].used) continue;

      length_name = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; ++j) {

        status = fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_name, lengths[j]);

        if (F_status_is_error(status)) return status;
        if (status == F_equal_to_not) continue;

        if (matches) {
          matches[j] = F_true;
        }

        status = f_string_dynamic_partial_append_nulless(buffer, contents.array[i].array[0], &name);

        if (F_status_is_error(status)) {
          macro_f_string_dynamic_t_delete_simple(name);

          return status;
        }

        matched = F_false;
        length_name = (contents.array[i].array[0].stop - contents.array[i].array[0].start) + 1;

        for (k = 0; k < values[j]->used; ++k) {

          status = fl_string_compare_trim(buffer.string + contents.array[i].array[0].start, values[j]->array[k].name.string, length_name, values[j]->array[k].name.used);

          if (F_status_is_error(status)) {
            macro_f_string_dynamic_t_delete_simple(name);

            return status;
          }

          if (status == F_equal_to) {
            matched = F_true;

            macro_f_string_dynamic_t_delete_simple(name);
            break;
          }
        } // for

        if (matched) {
          name.used = 0;

          map = &values[j]->array[k];
        }
        else {
          status = f_string_maps_increase(f_fss_default_allocation_step_small, values[j]);
          if (F_status_is_error(status)) return status;

          if (indexs) {
            macro_f_array_lengths_t_increase(status, f_fss_default_allocation_step_small, (*indexs[j]));
            if (F_status_is_error(status)) return status;
          }

          map = &values[j]->array[values[j]->used];

          map->name.string = name.string;
          map->name.used = name.used;
          map->name.size = name.size;

          ++values[j]->used;

          if (indexs) {
            indexs[j]->array[indexs[j]->used] = i;
            ++indexs[j]->used;
          }

          macro_f_string_dynamic_t_clear(name);
        }

        if (contents.array[i].used > 1) {
          status = f_string_dynamic_partial_mash_nulless(glue, glue_length, buffer, contents.array[i].array[1], &map->value);

          if (F_status_is_error(status)) {
            macro_f_string_dynamic_t_delete_simple(name);

            return status;
          }
        }
      } // for
    } // for

    macro_f_string_dynamic_t_delete_simple(name);

    return F_none;
  }
#endif // _di_fll_fss_snatch_map_together_

#ifndef _di_fll_fss_snatch_mash_
  f_status_t fll_fss_snatch_mash(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_array_length_t lengths[], const f_array_length_t size, const f_string_t glue, const f_array_length_t glue_length, f_string_dynamic_t *values[], bool matches[], f_array_length_t *indexs[]) {
    #ifndef _di_level_2_parameter_checking_
      if (!size) return F_status_set_error(F_parameter);
      if (objects.used != contents.used) return F_status_set_error(F_parameter);
      if (!values) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (!buffer.used) return F_data_not;
    if (!objects.used) return F_data_not;
    if (!contents.used) return F_data_not;

    f_status_t status = F_none;
    f_array_length_t length_object = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;

    bool matched[size];

    memset(&matched, 0, sizeof(bool) * size);

    for (; i < objects.used; ++i) {

      length_object = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; ++j) {

        if (matched[j]) continue;

        status = fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_object, lengths[j]);

        if (F_status_is_error(status)) return status;
        if (status == F_equal_to_not) continue;

        if (matches) {
          matches[j] = F_true;
        }

        matched[j] = F_true;

        for (k = 0; k < contents.array[i].used; ++k) {

          status = f_string_dynamic_partial_mash_nulless(glue, glue_length, buffer, contents.array[i].array[k], values[j]);
          if (F_status_is_error(status)) return status;
        } // for

        if (indexs) {
          *indexs[j] = i;
        }
      } // for
    } // for

    return F_none;
  }
#endif // _di_fll_fss_snatch_mash_

#ifndef _di_fll_fss_snatch_mash_apart_
  f_status_t fll_fss_snatch_mash_apart(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_array_length_t lengths[], const f_array_length_t size, const f_string_t glue, const f_array_length_t glue_length, f_string_dynamics_t *values[], bool matches[], f_array_lengths_t *indexs[]) {
    #ifndef _di_level_2_parameter_checking_
      if (!size) return F_status_set_error(F_parameter);
      if (objects.used != contents.used) return F_status_set_error(F_parameter);
      if (!values) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (!buffer.used) return F_data_not;
    if (!objects.used) return F_data_not;
    if (!contents.used) return F_data_not;

    f_status_t status = F_none;
    f_array_length_t length_object = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;

    for (; i < objects.used; ++i) {

      length_object = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; ++j) {

        status = fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_object, lengths[j]);

        if (F_status_is_error(status)) return status;
        if (status == F_equal_to_not) continue;

        if (matches) {
          matches[j] = F_true;
        }

        status = f_string_dynamics_increase(f_fss_default_allocation_step_small, values[j]);
        if (F_status_is_error(status)) return status;

        if (indexs) {
          macro_f_array_lengths_t_increase(status, f_fss_default_allocation_step_small, (*indexs[j]));
          if (F_status_is_error(status)) return status;
        }

        for (k = 0; k < contents.array[i].used; ++k) {

          status = f_string_dynamic_partial_mash_nulless(glue, glue_length, buffer, contents.array[i].array[k], &values[j]->array[values[j]->used]);
          if (F_status_is_error(status)) return status;
        } // for

        ++values[j]->used;

        if (indexs) {
          indexs[j]->array[indexs[j]->used] = i;
          ++indexs[j]->used;
        }
      } // for
    } // for

    return F_none;
  }
#endif // _di_fll_fss_snatch_mash_apart_

#ifndef _di_fll_fss_snatch_together_
  f_status_t fll_fss_snatch_together(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_array_length_t lengths[], const f_array_length_t size, const f_string_t glue, const f_array_length_t glue_length, f_string_dynamic_t *values[], bool matches[], f_array_length_t *indexs[]) {
    #ifndef _di_level_2_parameter_checking_
      if (!size) return F_status_set_error(F_parameter);
      if (objects.used != contents.used) return F_status_set_error(F_parameter);
      if (!values) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (!buffer.used) return F_data_not;
    if (!objects.used) return F_data_not;
    if (!contents.used) return F_data_not;

    f_status_t status = F_none;
    f_array_length_t length_object = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;

    for (; i < objects.used; ++i) {

      length_object = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; ++j) {

        status = fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_object, lengths[j]);

        if (F_status_is_error(status)) return status;
        if (status == F_equal_to_not) continue;

        if (matches) {
          matches[j] = F_true;
        }

        for (k = 0; k < contents.array[i].used; ++k) {

          status = f_string_dynamic_partial_mash_nulless(glue, glue_length, buffer, contents.array[i].array[k], values[j]);
          if (F_status_is_error(status)) return status;
        } // for

        if (indexs) {
          *indexs[j] = i;
        }
      } // for
    } // for

    return F_none;
  }
#endif // _di_fll_fss_snatch_together_

#ifdef __cplusplus
} // extern "C"
#endif
