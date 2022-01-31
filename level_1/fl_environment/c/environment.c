#include "environment.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_environment_load_name_
  f_status_t fl_environment_load_name(const f_string_static_t name, f_string_maps_t *environment) {
    #ifndef _di_level_2_parameter_checking_
      if (!environment) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (!name.used) {
      return F_data_not;
    }

    f_status_t status = f_string_maps_increase(F_memory_default_allocation_small_d, environment);
    if (F_status_is_error(status)) return status;

    environment->array[environment->used].name.used = 0;
    environment->array[environment->used].value.used = 0;

    status = f_string_dynamic_append_nulless(name, &environment->array[environment->used].name);
    if (F_status_is_error(status)) return status;

    status = f_environment_get(name, &environment->array[environment->used].value);

    if (F_status_is_error(status) || status == F_data_not || status == F_exist_not) {
      environment->array[environment->used].name.used = 0;

      return status;
    }

    ++environment->used;

    return F_none;
  }
#endif // _di_fl_environment_load_name_

#ifndef _di_fl_environment_load_names_
  f_status_t fl_environment_load_names(const f_string_statics_t names, f_string_maps_t *environment) {
    #ifndef _di_level_2_parameter_checking_
      if (!environment) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (!names.used) {
      return F_data_not;
    }

    f_status_t status = f_string_maps_increase_by(names.used, environment);
    if (F_status_is_error(status)) return status;

    for (f_array_length_t i = 0; i < names.used; ++i) {

      environment->array[environment->used].name.used = 0;
      environment->array[environment->used].value.used = 0;

      status = f_string_dynamic_append_nulless(names.array[i], &environment->array[environment->used].name);
      if (F_status_is_error(status)) return status;

      status = f_environment_get(names.array[i], &environment->array[environment->used].value);

      if (F_status_is_error(status)) {
        environment->array[environment->used].name.used = 0;

        return status;
      }

      if (status == F_data_not || status == F_exist_not) {
        environment->array[environment->used].name.used = 0;

        continue;
      }

      ++environment->used;
    } // for

    return F_none;
  }
#endif // _di_fl_environment_load_names_

#ifndef _di_fl_environment_path_explode_
  f_status_t fl_environment_path_explode(const f_string_static_t path, f_string_dynamics_t *paths) {
    #ifndef _di_level_0_parameter_checking_
      if (!paths) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;

    if (!path.used) {

      // When PATH is "", this is actually a valid search path for PWD.
      // Therefore append an equivalent representation of PWD (string used length is 0).
      status = f_string_dynamics_increase(F_memory_default_allocation_small_d, paths);
      if (F_status_is_error(status)) return status;

      paths->array[paths->used++].used = 0;

      return F_none;
    }

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;
    f_array_length_t first = 0;
    f_array_length_t total = 0;

    for (; i <= path.used; ++i) {

      if (i == path.used || path.string[i] == f_path_separator_variable_s.string[0]) {
        status = f_string_dynamics_increase(F_memory_default_allocation_small_d, paths);
        if (F_status_is_error(status)) return status;

        if (!i) {
          paths->array[paths->used++].used = 0;

          first = 1;

          continue;
        }

        total = i - first;
        paths->array[paths->used].used = 0;

        if (total) {
          char buffer[total];

          for (j = 0, k = 0; j < total; ++j) {

            if (!path.string[first + j]) continue;

            buffer[k++] = path.string[first + j];
          } // for

          buffer[k++] = f_path_separator_s.string[0];

          status = f_string_dynamic_increase_by(k, &paths->array[paths->used]);
          if (F_status_is_error(status)) return status;

          memcpy(paths->array[paths->used].string, buffer, k);

          paths->array[paths->used++].used = k;
        }
        else {
          ++paths->used;
        }

        first = i + 1;
      }
    } // for

    return F_none;
  }
#endif // _di_fl_environment_path_explode_

#ifndef _di_fl_environment_path_explode_reverse_
  f_status_t fl_environment_path_explode_reverse(const f_string_static_t path, f_string_dynamics_t *paths) {
    #ifndef _di_level_0_parameter_checking_
      if (!paths) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;

    if (!path.used) {

      // When PATH is "", this is actually a valid search path for PWD.
      // Therefore append an equivalent representation of PWD (string used length is 0).
      status = f_string_dynamics_increase(F_memory_default_allocation_small_d, paths);
      if (F_status_is_error(status)) return status;

      paths->array[paths->used++].used = 0;

      return F_none;
    }

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;
    f_array_length_t r = path.used;
    f_array_length_t last = path.used;
    f_array_length_t total = 0;

    for (; i <= path.used; ++i, --r) {

      if (i == path.used || path.string[r] == f_path_separator_variable_s.string[0]) {
        status = f_string_dynamics_increase(F_memory_default_allocation_small_d, paths);
        if (F_status_is_error(status)) return status;

        if (!i) {
          paths->array[paths->used++].used = 0;

          last = r - 1;

          continue;
        }

        total = last - r;
        paths->array[paths->used].used = 0;

        if (total) {
          char buffer[total];

          for (j = 0, k = 0; j < total; ++j) {

            if (!path.string[r + j + 1]) continue;

            buffer[k++] = path.string[r + j + 1];
          } // for

          buffer[k++] = f_path_separator_s.string[0];

          status = f_string_dynamic_increase_by(k, &paths->array[paths->used]);
          if (F_status_is_error(status)) return status;

          memcpy(paths->array[paths->used].string, buffer, k);

          paths->array[paths->used++].used = k;
        }
        else {
          ++paths->used;
        }

        last = r - 1;
      }
    } // for

    return F_none;
  }
#endif // _di_fl_environment_path_explode_reverse_

#ifdef __cplusplus
} // extern "C"
#endif
