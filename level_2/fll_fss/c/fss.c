#include "fss.h"
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_identify_
  f_return_status fll_fss_identify(const f_string_static_t buffer, f_fss_header_t *header) {
    #ifndef _di_level_2_parameter_checking_
      if (header == 0) return F_status_set_error(F_parameter);
      if (buffer.used == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    return private_fll_fss_identify(buffer, header);
  }
#endif // _di_fll_fss_identify_

#ifndef _di_fll_fss_identify_file_
  f_return_status fll_fss_identify_file(f_file_t *file, f_fss_header_t *header) {
    #ifndef _di_level_2_parameter_checking_
      if (file == 0) return F_status_set_error(F_parameter);
      if (header == 0) return F_status_set_error(F_parameter);
      if (file->id == 0) return F_status_set_error(F_file_closed);
      if (file->id < 0) return F_status_set_error(F_file);
    #endif // _di_level_2_parameter_checking_

    {
      f_string_length_t seeked = 0;
      if (F_status_is_error(f_file_seek(file->id, SEEK_SET, 0, &seeked))) {
        return F_status_set_error(F_file_seek);
      }
    }

    f_status_t status = F_none;
    f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

    f_macro_string_dynamic_t_resize(status, buffer, f_fss_max_header_length + 1);
    if (F_status_is_error(status)) return status;

    status = f_file_read_until(*file, f_fss_max_header_length + 1, &buffer);
    if (F_status_is_error(status)) return status;

    return private_fll_fss_identify(buffer, header);
  }
#endif // _di_fll_fss_identify_file_

#ifndef _di_fll_fss_snatch_
  f_return_status fll_fss_snatch(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_string_length_t lengths[], const f_string_length_t size, f_string_dynamic_t *values[], f_array_length_t *indexs[]) {
    #ifndef _di_level_2_parameter_checking_
      if (size == 0) return F_status_set_error(F_parameter);
      if (objects.used != contents.used) return F_status_set_error(F_parameter);
      if (values == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (buffer.used == 0) return F_data_not;
    if (objects.used == 0) return F_data_not;
    if (contents.used == 0) return F_data_not;

    f_status_t status = F_none;
    f_string_length_t length_object = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;

    bool matched[size];

    memset(&matched, 0, sizeof(bool) * size);

    for (; i < objects.used; i++) {

      length_object = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; j++) {
        if (matched[j]) continue;

        status = fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_object, lengths[j]);

        if (F_status_is_error(status)) return status;
        if (status == F_equal_to_not) continue;

        matched[j] = F_true;

        if (!contents.array[i].used) continue;

        status = fl_string_dynamic_partial_append_nulless(buffer, contents.array[i].array[0], values[j]);
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
  f_return_status fll_fss_snatch_apart(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_string_length_t lengths[], const f_string_length_t size, f_string_dynamics_t *values[], f_array_lengths_t *indexs[]) {
    #ifndef _di_level_2_parameter_checking_
      if (size == 0) return F_status_set_error(F_parameter);
      if (objects.used != contents.used) return F_status_set_error(F_parameter);
      if (values == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (buffer.used == 0) return F_data_not;
    if (objects.used == 0) return F_data_not;
    if (contents.used == 0) return F_data_not;

    f_status_t status = F_none;
    f_string_length_t length_object = 0;
    f_string_dynamics_t *value = 0;
    f_fss_content_t *content = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;

    for (; i < objects.used; i++) {

      length_object = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; j++) {

        status = fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_object, lengths[j]);

        if (F_status_is_error(status)) return status;
        if (status == F_equal_to_not) continue;

        value = values[j];
        content = &contents.array[i];

        if (values[j]->used + contents.array[i].used > values[j]->size) {
          if (values[j]->used + contents.array[i].used > f_array_length_t_size) {
            return F_status_set_error(F_buffer_too_large);
          }

          f_macro_string_dynamics_resize(status, (*value), (values[j]->used + content->used));
          if (F_status_is_error(status)) return status;

          if (indexs) {
            f_macro_array_lengths_t_resize(status, (*indexs[j]), (indexs[j]->used + content->used));
            if (F_status_is_error(status)) return status;
          }
        }

        for (k = 0; k < contents.array[i].used; k++) {

          status = fl_string_dynamic_partial_append_nulless(buffer, contents.array[i].array[k], &values[j]->array[values[j]->used]);
          if (F_status_is_error(status)) return status;

          values[j]->used++;

          if (indexs) {
            indexs[j]->array[indexs[j]->used] = i;
            indexs[j]->used++;
          }
        } // for
      } // for
    } // for

    return F_none;
  }
#endif // _di_fll_fss_snatch_apart_

#ifndef _di_fll_fss_snatch_map_
  f_return_status fll_fss_snatch_map(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_string_length_t lengths[], const f_string_length_t size, f_string_maps_t *values[], f_array_lengths_t *indexs[]) {
    #ifndef _di_level_2_parameter_checking_
      if (size == 0) return F_status_set_error(F_parameter);
      if (objects.used != contents.used) return F_status_set_error(F_parameter);
      if (values == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (buffer.used == 0) return F_data_not;
    if (objects.used == 0) return F_data_not;
    if (contents.used == 0) return F_data_not;

    f_status_t status = F_none;
    f_string_length_t length_name = 0;
    f_string_dynamic_t name = f_string_dynamic_t_initialize;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;

    bool matched = F_false;

    f_string_map_t *map = 0;

    for (; i < objects.used; i++) {
      if (!contents.array[i].used) continue;

      length_name = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; j++) {

        status = fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_name, lengths[j]);

        if (F_status_is_error(status)) return status;
        if (status == F_equal_to_not) continue;

        status = fl_string_dynamic_partial_append_nulless(buffer, contents.array[i].array[0], &name);

        if (F_status_is_error(status)) {
          f_macro_string_dynamic_t_delete_simple(name);
          return status;
        }

        matched = F_false;
        length_name = (contents.array[i].array[0].stop - contents.array[i].array[0].start) + 1;

        for (k = 0; k < values[j]->used; k++) {

          status = fl_string_compare_trim(buffer.string + contents.array[i].array[0].start, values[j]->array[k].name.string, length_name, values[j]->array[k].name.used);

          if (F_status_is_error(status)) {
            f_macro_string_dynamic_t_delete_simple(name);
            return status;
          }

          if (status == F_equal_to) {
            matched = F_true;

            f_macro_string_dynamic_t_delete_simple(name);
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
              f_macro_string_dynamic_t_delete_simple(name);
              return F_status_set_error(F_buffer_too_large);
            }

            f_macro_string_maps_t_resize(status, (*values[j]), values[j]->used + 1);

            if (F_status_is_error(status)) {
              f_macro_string_dynamic_t_delete_simple(name);
              return status;
            }

            if (indexs) {
              f_macro_array_lengths_t_resize(status, (*indexs[j]), indexs[j]->used + 1);
              if (F_status_is_error(status)) return status;
            }
          }
          else {
            f_macro_string_maps_t_resize(status, (*values[j]), values[j]->used + f_fss_default_allocation_step);

            if (F_status_is_error(status)) {
              f_macro_string_dynamic_t_delete_simple(name);
              return status;
            }

            if (indexs) {
              f_macro_array_lengths_t_resize(status, (*indexs[j]), indexs[j]->used + f_fss_default_allocation_step);
              if (F_status_is_error(status)) return status;
            }
          }
        }

        map = &values[j]->array[values[j]->used];

        if (contents.array[i].used > 1) {
          status = fl_string_dynamic_partial_append_nulless(buffer, contents.array[i].array[1], &map->value);

          if (F_status_is_error(status)) {
            f_macro_string_dynamic_t_delete_simple(name);
            return status;
          }
        }

        map->name.string = name.string;
        map->name.used = name.used;
        map->name.size = name.size;

        values[j]->used++;

        if (indexs) {
          indexs[j]->array[indexs[j]->used] = i;
          indexs[j]->used++;
        }

        f_macro_string_dynamic_t_clear(name);
      } // for
    } // for

    f_macro_string_dynamic_t_delete_simple(name);
    return F_none;
  }
#endif // _di_fll_fss_snatch_map_

#ifndef _di_fll_fss_snatch_map_apart_
  f_return_status fll_fss_snatch_map_apart(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_string_length_t lengths[], const f_string_length_t size, f_string_map_multis_t *values[], f_array_lengths_t *indexs[]) {
    #ifndef _di_level_2_parameter_checking_
      if (size == 0) return F_status_set_error(F_parameter);
      if (objects.used != contents.used) return F_status_set_error(F_parameter);
      if (values == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (buffer.used == 0) return F_data_not;
    if (objects.used == 0) return F_data_not;
    if (contents.used == 0) return F_data_not;

    f_status_t status = F_none;
    f_string_length_t length_object = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;

    f_string_map_multi_t *map_multi = 0;

    for (; i < objects.used; i++) {
      if (!contents.array[i].used) continue;

      length_object = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; j++) {

        status = fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_object, lengths[j]);

        if (F_status_is_error(status)) return status;
        if (status == F_equal_to_not) continue;

        if (values[j]->used == values[j]->size) {
          if (values[j]->used + f_fss_default_allocation_step > f_array_length_t_size) {
            if (values[j]->used == f_array_length_t_size) {
              return F_status_set_error(F_buffer_too_large);
            }

            f_macro_string_map_multis_t_resize(status, (*values[j]), values[j]->used + 1);
            if (F_status_is_error(status)) return status;

            if (indexs) {
              f_macro_array_lengths_t_resize(status, (*indexs[j]), indexs[j]->used + 1);
              if (F_status_is_error(status)) return status;
            }
          }
          else {
            f_macro_string_map_multis_t_resize(status, (*values[j]), values[j]->used + f_fss_default_allocation_step);
            if (F_status_is_error(status)) return status;

            if (indexs) {
              f_macro_array_lengths_t_resize(status, (*indexs[j]), indexs[j]->used + f_fss_default_allocation_step);
              if (F_status_is_error(status)) return status;
            }
          }
        }

        map_multi = &values[j]->array[values[j]->used];

        status = fl_string_dynamic_partial_append_nulless(buffer, contents.array[i].array[0], &map_multi->name);
        if (F_status_is_error(status)) return status;

        values[j]->used++;

        if (indexs) {
          indexs[j]->array[indexs[j]->used] = i;
          indexs[j]->used++;
        }

        if (contents.array[i].used > 1) {
          if (map_multi->value.used + contents.array[i].used - 1 > map_multi->value.size) {
            if (map_multi->value.used + contents.array[i].used - 1 > f_array_length_t_size) return F_status_set_error(F_buffer_too_large);

            f_macro_string_dynamics_resize(status, map_multi->value, map_multi->value.used + contents.array[i].used - 1);
            if (F_status_is_error(status)) return status;
          }

          for (k = 1; k < contents.array[i].used; k++) {

            status = fl_string_dynamic_partial_append_nulless(buffer, contents.array[i].array[k], &map_multi->value.array[map_multi->value.used]);
            if (F_status_is_error(status)) return status;

            map_multi->value.used++;
          } // for
        }
      } // for
    } // for

    return F_none;
  }
#endif // _di_fll_fss_snatch_map_apart_

#ifndef _di_fll_fss_snatch_map_mash_
  f_return_status fll_fss_snatch_map_mash(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_string_length_t lengths[], const f_string_length_t size, const f_string_t glue, const f_string_length_t glue_length, f_string_maps_t *values[], f_array_lengths_t *indexs[]) {
    #ifndef _di_level_2_parameter_checking_
      if (size == 0) return F_status_set_error(F_parameter);
      if (objects.used != contents.used) return F_status_set_error(F_parameter);
      if (values == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (buffer.used == 0) return F_data_not;
    if (objects.used == 0) return F_data_not;
    if (contents.used == 0) return F_data_not;

    f_status_t status = F_none;
    f_string_length_t length_object = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;

    f_string_map_t *map = 0;

    for (; i < objects.used; i++) {
      if (!contents.array[i].used) continue;

      length_object = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; j++) {

        status = fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_object, lengths[j]);

        if (F_status_is_error(status)) return status;
        if (status == F_equal_to_not) continue;

        if (values[j]->used == values[j]->size) {
          if (values[j]->used + f_fss_default_allocation_step > f_array_length_t_size) {
            if (values[j]->used == f_array_length_t_size) {
              return F_status_set_error(F_buffer_too_large);
            }

            f_macro_string_maps_t_resize(status, (*values[j]), values[j]->used + 1);
            if (F_status_is_error(status)) return status;

            if (indexs) {
              f_macro_array_lengths_t_resize(status, (*indexs[j]), indexs[j]->used + 1);
              if (F_status_is_error(status)) return status;
            }
          }
          else {
            f_macro_string_maps_t_resize(status, (*values[j]), values[j]->used + f_fss_default_allocation_step);
            if (F_status_is_error(status)) return status;

            if (indexs) {
              f_macro_array_lengths_t_resize(status, (*indexs[j]), indexs[j]->used + f_fss_default_allocation_step);
              if (F_status_is_error(status)) return status;
            }
          }
        }

        map = &values[j]->array[values[j]->used];

        status = fl_string_dynamic_partial_append_nulless(buffer, contents.array[i].array[0], &map->name);
        if (F_status_is_error(status)) return status;

        values[j]->used++;

        if (indexs) {
          indexs[j]->array[indexs[j]->used] = i;
          indexs[j]->used++;
        }

        if (contents.array[i].used > 1) {
          for (k = 1; k < contents.array[i].used; k++) {

            status = fl_string_dynamic_partial_mash_nulless(glue, glue_length, buffer, contents.array[i].array[k], &map->value);
            if (F_status_is_error(status)) return status;
          } // for
        }
      } // for
    } // for

    return F_none;
  }
#endif // _di_fll_fss_snatch_map_mash_

#ifndef _di_fll_fss_snatch_map_mash_apart_
  f_return_status fll_fss_snatch_map_mash_apart(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_string_length_t lengths[], const f_string_length_t size, const f_string_t glue, const f_string_length_t glue_length, f_string_map_multis_t *values[], f_array_lengths_t *indexs[]) {
    #ifndef _di_level_2_parameter_checking_
      if (size == 0) return F_status_set_error(F_parameter);
      if (objects.used != contents.used) return F_status_set_error(F_parameter);
      if (values == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (buffer.used == 0) return F_data_not;
    if (objects.used == 0) return F_data_not;
    if (contents.used == 0) return F_data_not;

    f_status_t status = F_none;
    f_string_length_t length_name = 0;
    f_string_dynamic_t name = f_string_dynamic_t_initialize;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;

    bool matched = F_false;

    f_string_map_multi_t *map_multi = 0;

    for (; i < objects.used; i++) {
      if (!contents.array[i].used) continue;

      length_name = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; j++) {
        status = fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_name, lengths[j]);

        if (F_status_is_error(status)) return status;
        if (status == F_equal_to_not) continue;

        status = fl_string_dynamic_partial_append_nulless(buffer, contents.array[i].array[0], &name);

        if (F_status_is_error(status)) {
          f_macro_string_dynamic_t_delete_simple(name);
          return status;
        }

        matched = F_false;
        length_name = (contents.array[i].array[0].stop - contents.array[i].array[0].start) + 1;

        for (k = 0; k < values[j]->used; k++) {

          status = fl_string_compare_trim(buffer.string + contents.array[i].array[0].start, values[j]->array[k].name.string, length_name, values[j]->array[k].name.used);

          if (F_status_is_error(status)) {
            f_macro_string_dynamic_t_delete_simple(name);
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
          if (values[j]->used == values[j]->size) {
            if (values[j]->used + f_fss_default_allocation_step > f_array_length_t_size) {
              if (values[j]->used == f_array_length_t_size) {
                return F_status_set_error(F_buffer_too_large);
              }

              f_macro_string_map_multis_t_resize(status, (*values[j]), values[j]->used + 1);
              if (F_status_is_error(status)) return status;

              if (indexs) {
                f_macro_array_lengths_t_resize(status, (*indexs[j]), indexs[j]->used + 1);
                if (F_status_is_error(status)) return status;
              }
            }
            else {
              f_macro_string_map_multis_t_resize(status, (*values[j]), values[j]->used + f_fss_default_allocation_step);
              if (F_status_is_error(status)) return status;

              if (indexs) {
                f_macro_array_lengths_t_resize(status, (*indexs[j]), indexs[j]->used + f_fss_default_allocation_step);
                if (F_status_is_error(status)) return status;
              }
            }
          }

          map_multi = &values[j]->array[values[j]->used];
          map_multi->name.string = name.string;
          map_multi->name.used = name.used;
          map_multi->name.size = name.size;

          values[j]->used++;

          if (indexs) {
            indexs[j]->array[indexs[j]->used] = i;
            indexs[j]->used++;
          }

          f_macro_string_dynamic_t_clear(name);

          if (contents.array[i].used == 1) continue;
        }

        if (map_multi->value.used == map_multi->value.size) {
          if (map_multi->value.used == f_array_length_t_size) {
            return F_status_set_error(F_buffer_too_large);
          }

          f_macro_string_dynamics_resize(status, map_multi->value, map_multi->value.used + 1);
          if (F_status_is_error(status)) return status;
        }

        for (k = 1; k < contents.array[i].used; k++) {

          status = fl_string_dynamic_partial_mash_nulless(glue, glue_length, buffer, contents.array[i].array[k], &map_multi->value.array[map_multi->value.used]);
          if (F_status_is_error(status)) return status;
        } // for

        map_multi->value.used++;
      } // for
    } // for

    f_macro_string_dynamic_t_delete_simple(name);
    return F_none;
  }
#endif // _di_fll_fss_snatch_map_mash_apart_

#ifndef _di_fll_fss_snatch_map_together_
  f_return_status fll_fss_snatch_map_together(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_string_length_t lengths[], const f_string_length_t size, const f_string_t glue, const f_string_length_t glue_length, f_string_maps_t *values[], f_array_lengths_t *indexs[]) {
    #ifndef _di_level_2_parameter_checking_
      if (size == 0) return F_status_set_error(F_parameter);
      if (objects.used != contents.used) return F_status_set_error(F_parameter);
      if (values == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (buffer.used == 0) return F_data_not;
    if (objects.used == 0) return F_data_not;
    if (contents.used == 0) return F_data_not;

    f_status_t status = F_none;
    f_string_length_t length_name = 0;
    f_string_dynamic_t name = f_string_dynamic_t_initialize;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;

    bool matched = F_false;

    f_string_map_t *map = 0;

    for (; i < objects.used; i++) {
      if (!contents.array[i].used) continue;

      length_name = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; j++) {

        status = fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_name, lengths[j]);

        if (F_status_is_error(status)) return status;
        if (status == F_equal_to_not) continue;

        status = fl_string_dynamic_partial_append_nulless(buffer, contents.array[i].array[0], &name);

        if (F_status_is_error(status)) {
          f_macro_string_dynamic_t_delete_simple(name);
          return status;
        }

        matched = F_false;
        length_name = (contents.array[i].array[0].stop - contents.array[i].array[0].start) + 1;

        for (k = 0; k < values[j]->used; k++) {

          status = fl_string_compare_trim(buffer.string + contents.array[i].array[0].start, values[j]->array[k].name.string, length_name, values[j]->array[k].name.used);

          if (F_status_is_error(status)) {
            f_macro_string_dynamic_t_delete_simple(name);
            return status;
          }

          if (status == F_equal_to) {
            matched = F_true;

            f_macro_string_dynamic_t_delete_simple(name);
            break;
          }
        } // for

        if (matched) {
          name.used = 0;

          map = &values[j]->array[k];
        }
        else {
          if (values[j]->used == values[j]->size) {
            if (values[j]->used + f_fss_default_allocation_step > f_array_length_t_size) {
              if (values[j]->used == f_array_length_t_size) {
                f_macro_string_dynamic_t_delete_simple(name);
                return F_status_set_error(F_buffer_too_large);
              }

              f_macro_string_maps_t_resize(status, (*values[j]), values[j]->used + 1);

              if (F_status_is_error(status)) {
                f_macro_string_dynamic_t_delete_simple(name);
                return status;
              }

              if (indexs) {
                f_macro_array_lengths_t_resize(status, (*indexs[j]), indexs[j]->used + 1);
                if (F_status_is_error(status)) return status;
              }
            }
            else {
              f_macro_string_maps_t_resize(status, (*values[j]), values[j]->used + f_fss_default_allocation_step);

              if (F_status_is_error(status)) {
                f_macro_string_dynamic_t_delete_simple(name);
                return status;
              }

              if (indexs) {
                f_macro_array_lengths_t_resize(status, (*indexs[j]), indexs[j]->used + f_fss_default_allocation_step);
                if (F_status_is_error(status)) return status;
              }
            }
          }

          map = &values[j]->array[values[j]->used];

          map->name.string = name.string;
          map->name.used = name.used;
          map->name.size = name.size;

          values[j]->used++;

          if (indexs) {
            indexs[j]->array[indexs[j]->used] = i;
            indexs[j]->used++;
          }

          f_macro_string_dynamic_t_clear(name);
        }

        if (contents.array[i].used > 1) {
          status = fl_string_dynamic_partial_mash_nulless(glue, glue_length, buffer, contents.array[i].array[1], &map->value);

          if (F_status_is_error(status)) {
            f_macro_string_dynamic_t_delete_simple(name);
            return status;
          }
        }
      } // for
    } // for

    f_macro_string_dynamic_t_delete_simple(name);
    return F_none;
  }
#endif // _di_fll_fss_snatch_map_together_

#ifndef _di_fll_fss_snatch_mash_
  f_return_status fll_fss_snatch_mash(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_string_length_t lengths[], const f_string_length_t size, const f_string_t glue, const f_string_length_t glue_length, f_string_dynamic_t *values[], f_array_length_t *indexs[]) {
    #ifndef _di_level_2_parameter_checking_
      if (size == 0) return F_status_set_error(F_parameter);
      if (objects.used != contents.used) return F_status_set_error(F_parameter);
      if (values == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (buffer.used == 0) return F_data_not;
    if (objects.used == 0) return F_data_not;
    if (contents.used == 0) return F_data_not;

    f_status_t status = F_none;
    f_string_length_t length_object = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;

    bool matched[size];

    memset(&matched, 0, sizeof(bool) * size);

    for (; i < objects.used; i++) {

      length_object = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; j++) {
        if (matched[j]) continue;

        status = fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_object, lengths[j]);

        if (F_status_is_error(status)) return status;
        if (status == F_equal_to_not) continue;

        matched[j] = F_true;

        for (k = 0; k < contents.array[i].used; k++) {

          status = fl_string_dynamic_partial_mash_nulless(glue, glue_length, buffer, contents.array[i].array[k], values[j]);
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
  f_return_status fll_fss_snatch_mash_apart(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_string_length_t lengths[], const f_string_length_t size, const f_string_t glue, const f_string_length_t glue_length, f_string_dynamics_t *values[], f_array_lengths_t *indexs[]) {
    #ifndef _di_level_2_parameter_checking_
      if (size == 0) return F_status_set_error(F_parameter);
      if (objects.used != contents.used) return F_status_set_error(F_parameter);
      if (values == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (buffer.used == 0) return F_data_not;
    if (objects.used == 0) return F_data_not;
    if (contents.used == 0) return F_data_not;

    f_status_t status = F_none;
    f_string_length_t length_object = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;

    for (; i < objects.used; i++) {

      length_object = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; j++) {

        status = fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_object, lengths[j]);

        if (F_status_is_error(status)) return status;
        if (status == F_equal_to_not) continue;

        if (values[j]->used == values[j]->size) {
          if (values[j]->used + f_fss_default_allocation_step > f_array_length_t_size) {
            if (values[j]->used == f_array_length_t_size) {
              return F_status_set_error(F_buffer_too_large);
            }

            f_macro_string_dynamics_resize(status, (*values[j]), values[j]->used + 1);
            if (F_status_is_error(status)) return status;

            if (indexs) {
              f_macro_array_lengths_t_resize(status, (*indexs[j]), indexs[j]->used + 1);
              if (F_status_is_error(status)) return status;
            }
          }
          else {
            f_macro_string_dynamics_resize(status, (*values[j]), values[j]->used + f_fss_default_allocation_step);
            if (F_status_is_error(status)) return status;

            if (indexs) {
              f_macro_array_lengths_t_resize(status, (*indexs[j]), indexs[j]->used + f_fss_default_allocation_step);
              if (F_status_is_error(status)) return status;
            }
          }
        }

        for (k = 0; k < contents.array[i].used; k++) {

          status = fl_string_dynamic_partial_mash_nulless(glue, glue_length, buffer, contents.array[i].array[k], &values[j]->array[values[j]->used]);
          if (F_status_is_error(status)) return status;
        } // for

        values[j]->used++;

        if (indexs) {
          indexs[j]->array[indexs[j]->used] = i;
          indexs[j]->used++;
        }
      } // for
    } // for

    return F_none;
  }
#endif // _di_fll_fss_snatch_mash_apart_

#ifndef _di_fll_fss_snatch_together_
  f_return_status fll_fss_snatch_together(const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, const f_string_t names[], const f_string_length_t lengths[], const f_string_length_t size, const f_string_t glue, const f_string_length_t glue_length, f_string_dynamic_t *values[], f_array_length_t *indexs[]) {
    #ifndef _di_level_2_parameter_checking_
      if (size == 0) return F_status_set_error(F_parameter);
      if (objects.used != contents.used) return F_status_set_error(F_parameter);
      if (values == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (buffer.used == 0) return F_data_not;
    if (objects.used == 0) return F_data_not;
    if (contents.used == 0) return F_data_not;

    f_status_t status = F_none;
    f_string_length_t length_object = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;

    for (; i < objects.used; i++) {

      length_object = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; j++) {

        status = fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_object, lengths[j]);

        if (F_status_is_error(status)) return status;
        if (status == F_equal_to_not) continue;

        for (k = 0; k < contents.array[i].used; k++) {

          status = fl_string_dynamic_partial_mash_nulless(glue, glue_length, buffer, contents.array[i].array[k], values[j]);
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
