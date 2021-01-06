#include "environment.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_environment_path_explode_
  f_status_t fl_environment_path_explode(const f_string_t path, f_string_dynamics_t *paths) {
    #ifndef _di_level_0_parameter_checking_
      if (!paths) return F_status_set_error(F_parameter);
      if (paths->used > paths->size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;
    const f_string_length_t length = strnlen(path, PATH_MAX);

    if (!length) {

      // When PATH is "", this is actually a valid search path for PWD.
      // Append an equivalent representation of PWD (string used length is 0).
      f_macro_memory_structure_macro_increment(status, (*paths), 1, f_memory_default_allocation_step, f_macro_string_dynamics_t_resize, F_array_too_large);
      if (F_status_is_error(status)) return status;

      f_macro_string_dynamic_t_clear(paths->array[paths->used]);
      paths->used++;

      return F_none;
    }

    f_string_length_t i = length;
    f_string_length_t first = 0;
    f_string_length_t total = 0;

    for (i = 0; i <= length; i++) {

      if (i == length || path[i] == f_path_separator_variable_s[0]) {
        f_macro_memory_structure_macro_increment(status, (*paths), 1, f_memory_default_allocation_step, f_macro_string_dynamics_t_resize, F_array_too_large);
        if (F_status_is_error(status)) return status;

        if (!i) {
          f_macro_string_dynamic_t_clear(paths->array[paths->used]);
          paths->used++;

          first = 1;
          continue;
        }

        f_string_dynamic_t part = f_string_dynamic_t_initialize;

        total = i - first;

        if (total > 0) {
          if (path[i - 1] == f_path_separator_s[0]) {
            f_macro_string_dynamic_t_new(status, part, total);
            if (F_status_is_error(status)) return status;

            part.used = total;
          }
          else {
            f_macro_string_dynamic_t_new(status, part, total + 1);
            if (F_status_is_error(status)) return status;

            part.string[total] = f_path_separator_s[0];
            part.used = total + 1;
          }

          memcpy(part.string, path + first, total);
        }

        paths->array[paths->used].string = part.string;
        paths->array[paths->used].used = part.used;
        paths->array[paths->used].size = part.size;
        paths->used++;

        first = i + 1;
      }
    } // for

    return F_none;
  }
#endif // _di_fl_environment_path_explode_

#ifndef _di_fl_environment_path_explode_dynamic_
  f_status_t fl_environment_path_explode_dynamic(const f_string_static_t path, f_string_dynamics_t *paths) {
    #ifndef _di_level_0_parameter_checking_
      if (path.used > path.size) return F_status_set_error(F_parameter);
      if (!paths) return F_status_set_error(F_parameter);
      if (paths->used > paths->size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;

    if (!path.used) {

      // When PATH is "", this is actually a valid search path for PWD.
      // Therefore append an equivalent representation of PWD (string used length is 0).
      f_macro_memory_structure_macro_increment(status, (*paths), 1, f_memory_default_allocation_step, f_macro_string_dynamics_t_resize, F_array_too_large);
      if (F_status_is_error(status)) return status;

      f_macro_string_dynamic_t_clear(paths->array[paths->used]);
      paths->used++;

      return F_none;
    }

    f_string_length_t i = 0;
    f_string_length_t j = 0;
    f_string_length_t first = 0;
    f_string_length_t total = 0;

    f_string_dynamic_t part = f_string_dynamic_t_initialize;

    for (i = 0; i <= path.used; i++) {

      if (i == path.used || path.string[i] == f_path_separator_variable_s[0]) {
        f_macro_memory_structure_macro_increment(status, (*paths), 1, f_memory_default_allocation_step, f_macro_string_dynamics_t_resize, F_array_too_large);
        if (F_status_is_error(status)) return status;

        if (!i) {
          f_macro_string_dynamic_t_clear(paths->array[paths->used]);
          paths->used++;

          first = 1;
          continue;
        }

        total = i - first;

        if (total > 0) {
          f_macro_string_dynamic_t_new(status, part, total);
          if (F_status_is_error(status)) return status;

          for (j = 0; j < total; j++) {
            if (!path.string[first + j]) continue;

            part.string[part.used] = path.string[first + j];
            part.used++;
          } // for

          if (part.string[part.used - 1] != f_path_separator_s[0]) {
            f_macro_string_dynamic_t_resize(status, part, total + 1);
            if (F_status_is_error(status)) return status;

            part.string[part.used] = f_path_separator_s[0];
            part.used++;
          }
        }

        paths->array[paths->used].string = part.string;
        paths->array[paths->used].used = part.used;
        paths->array[paths->used].size = part.size;
        paths->used++;

        first = i + 1;
      }
    } // for

    return F_none;
  }
#endif // _di_fl_environment_path_explode_dynamic_

#ifndef _di_fl_environment_path_explode_reverse_
  f_status_t fl_environment_path_explode_reverse(const f_string_t path, f_string_dynamics_t *paths) {
    #ifndef _di_level_0_parameter_checking_
      if (!paths) return F_status_set_error(F_parameter);
      if (paths->used > paths->size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;
    const f_string_length_t length = strnlen(path, PATH_MAX);

    if (!length) {

      // When PATH is "", this is actually a valid search path for PWD.
      // Therefore append an equivalent representation of PWD (string used length is 0).
      f_macro_memory_structure_macro_increment(status, (*paths), 1, f_memory_default_allocation_step, f_macro_string_dynamics_t_resize, F_array_too_large);
      if (F_status_is_error(status)) return status;

      paths->array[paths->used].string = 0;
      paths->array[paths->used].used = 0;
      paths->array[paths->used].size = 0;
      paths->used++;

      return F_none;
    }

    f_string_length_t i = length;
    f_string_length_t j = length;
    f_string_length_t last = length;
    f_string_length_t total = 0;

    f_string_dynamic_t part = f_string_dynamic_t_initialize;

    for (; i > 0; i--) {
      j--;

      if (!j || path[j] == f_path_separator_variable_s[0]) {
        f_macro_memory_structure_macro_increment(status, (*paths), 1, f_memory_default_allocation_step, f_macro_string_dynamics_t_resize, F_array_too_large);
        if (F_status_is_error(status)) return status;

        if (path[j] == f_path_separator_variable_s[0]) {
          total = last - i;

          if (total > 0) {
            if (path[j + total] == f_path_separator_s[0]) {
              f_macro_string_dynamic_t_new(status, part, total);
              if (F_status_is_error(status)) return status;

              part.used = total;
            }
            else {
              f_macro_string_dynamic_t_new(status, part, total + 1);
              if (F_status_is_error(status)) return status;

              part.string[total] = f_path_separator_s[0];
              part.used = total + 1;
            }

            memcpy(part.string, path + i, total);
          }

          last = j;
        }
        else if (!j) {

          // when j = 0, the total is actually the entire length to max.
          total = last - j;

          if (total > 0) {
            if (path[last - 1] == f_path_separator_s[0]) {
              f_macro_string_dynamic_t_new(status, part, total);
              if (F_status_is_error(status)) return status;

              part.used = total;
            }
            else {
              f_macro_string_dynamic_t_new(status, part, total + 1);
              if (F_status_is_error(status)) return status;

              part.used = total + 1;
              part.string[total] = f_path_separator_s[0];
            }

            memcpy(part.string, path, total);
          }
        }

        paths->array[paths->used].string = part.string;
        paths->array[paths->used].used = part.used;
        paths->array[paths->used].size = part.size;
        paths->used++;
      }
    } // for

    return F_none;
  }
#endif // _di_fl_environment_path_explode_reverse_

#ifndef _di_fl_environment_path_explode_reverse_dynamic_
  f_status_t fl_environment_path_explode_reverse_dynamic(const f_string_static_t path, f_string_dynamics_t *paths) {
    #ifndef _di_level_0_parameter_checking_
      if (path.used > path.size) return F_status_set_error(F_parameter);
      if (!paths) return F_status_set_error(F_parameter);
      if (paths->used > paths->size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;

    if (!path.used) {
      // When PATH is "", this is actually a valid search path for PWD.
      // Therefore append an equivalent representation of PWD (string used length is 0).
      f_macro_memory_structure_macro_increment(status, (*paths), 1, f_memory_default_allocation_step, f_macro_string_dynamics_t_resize, F_array_too_large);
      if (F_status_is_error(status)) return status;

      f_macro_string_dynamic_t_clear(paths->array[paths->used]);
      paths->used++;

      return F_none;
    }

    f_string_length_t i = path.used;
    f_string_length_t j = path.used;
    f_string_length_t k = 0;
    f_string_length_t last = path.used;
    f_string_length_t total = 0;

    f_string_dynamic_t part = f_string_dynamic_t_initialize;

    for (; i > 0; i--) {
      j--;

      if (!j || path.string[j] == f_path_separator_variable_s[0]) {
        f_macro_memory_structure_macro_increment(status, (*paths), 1, f_memory_default_allocation_step, f_macro_string_dynamics_t_resize, F_array_too_large);
        if (F_status_is_error(status)) return status;

        if (path.string[j] == f_path_separator_variable_s[0]) {
          total = last - i;

          if (total > 0) {
            f_macro_string_dynamic_t_new(status, part, total);
            if (F_status_is_error(status)) return status;

            for (k = 0; k < total; k++) {
              if (!path.string[i + k]) continue;

              part.string[part.used] = path.string[i + k];
              part.used++;
            } // for

            if (part.string[part.used - 1] != f_path_separator_s[0]) {
              f_macro_string_dynamic_t_resize(status, part, total + 1);
              if (F_status_is_error(status)) return status;

              part.string[part.used] = f_path_separator_s[0];
              part.used++;
            }
          }

          last = j;
        }
        else if (!j) {
          // when j = 0, the total is actually the entire length to max.
          total = last - j;

          f_macro_string_dynamic_t_new(status, part, total);
          if (F_status_is_error(status)) return status;

          for (k = 0; k < total; k++) {
            if (!path.string[i + k]) continue;

            part.string[part.used] = path.string[i + k];
            part.used++;
          } // for

          if (part.string[part.used - 1] != f_path_separator_s[0]) {
            f_macro_string_dynamic_t_resize(status, part, total + 1);
            if (F_status_is_error(status)) return status;

            part.string[part.used - 1] = f_path_separator_s[0];
            part.used++;
          }
        }

        paths->array[paths->used].string = part.string;
        paths->array[paths->used].used = part.used;
        paths->array[paths->used].size = part.size;
        paths->used++;
      }
    } // for

    return F_none;
  }
#endif // _di_fl_environment_path_explode_reverse_dynamic_

#ifdef __cplusplus
} // extern "C"
#endif
