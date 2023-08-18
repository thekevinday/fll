#include "environment.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_environment_load_name_
  f_status_t fl_environment_load_name(const f_string_static_t name, f_string_maps_t * const environment) {
    #ifndef _di_level_1_parameter_checking_
      if (!environment) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!name.used) {
      return F_data_not;
    }

    f_status_t status = f_string_maps_increase(F_memory_default_allocation_small_d, environment);
    if (F_status_is_error(status)) return status;

    environment->array[environment->used].name.used = 0;
    environment->array[environment->used].value.used = 0;

    status = f_string_dynamic_append_nulless(name, &environment->array[environment->used].name);

    if (F_status_is_error_not(status)) {
      status = f_environment_get(name, &environment->array[environment->used].value);
    }

    if (F_status_is_error(status) || status == F_data_not || status == F_exist_not) {
      environment->array[environment->used].name.used = 0;
      environment->array[environment->used].value.used = 0;

      return status;
    }

    ++environment->used;

    return F_okay;
  }
#endif // _di_fl_environment_load_name_

#ifndef _di_fl_environment_load_names_
  f_status_t fl_environment_load_names(const f_string_statics_t names, f_string_maps_t * const environment) {
    #ifndef _di_level_1_parameter_checking_
      if (!environment) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!names.used) {
      return F_data_not;
    }

    f_status_t status = f_string_maps_increase_by(names.used, environment);
    if (F_status_is_error(status)) return status;

    for (f_number_unsigned_t i = 0; i < names.used; ++i) {

      environment->array[environment->used].name.used = 0;
      environment->array[environment->used].value.used = 0;

      status = f_string_dynamic_append_nulless(names.array[i], &environment->array[environment->used].name);

      if (F_status_is_error_not(status)) {
        status = f_environment_get(names.array[i], &environment->array[environment->used].value);
      }
      else {
        environment->array[environment->used].name.used = 0;
        environment->array[environment->used].value.used = 0;

        return status;
      }

      if (status == F_data_not || status == F_exist_not) continue;

      ++environment->used;
    } // for

    return F_okay;
  }
#endif // _di_fl_environment_load_names_

#ifndef _di_fl_environment_path_explode_
  f_status_t fl_environment_path_explode(const f_string_static_t path, f_string_dynamics_t * const paths) {
    #ifndef _di_level_1_parameter_checking_
      if (!paths) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_okay;

    if (!path.used) {

      // When PATH is "", this is actually a valid search path for PWD.
      // Therefore append an equivalent representation of PWD (string used length is 0).
      status = f_string_dynamics_increase(F_memory_default_allocation_small_d, paths);
      if (F_status_is_error(status)) return status;

      paths->array[paths->used++].used = 0;

      return F_okay;
    }

    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;
    f_number_unsigned_t k = 0;
    f_number_unsigned_t first = 0;
    f_number_unsigned_t total = 0;

    // Do a quick pre-process of PATH to approximate the amount of parts needed, reducing the number of allocations.
    for (; i <= path.used; ++i) {
      if (path.string[i] == f_path_separator_variable_s.string[0]) ++total;
    } // for

    #ifdef _en_kevux_path_architecture_bits_
      total *= 3;
    #endif // _en_kevux_path_architecture_bits_

    if (total) {
      status = f_string_dynamics_increase_by(total, paths);
      if (F_status_is_error(status)) return status;

      total = 0;
    }

    #ifdef _en_kevux_path_architecture_bits_
      f_string_dynamic_t architecture_bits = f_string_dynamic_t_initialize;

      if (f_path_architecture_bits_s.used) {
        status = f_environment_get(f_path_architecture_bits_s, &architecture_bits);
        if (F_status_is_error(status)) return status;
      }

      if (architecture_bits.used) {
        status = f_string_dynamic_append_assure(f_path_separator_s, &architecture_bits);

        if (F_status_is_error(status)) {
          f_string_dynamic_resize(0, &architecture_bits);

          return status;
        }
      } else if (!architecture_bits.used && f_path_architecture_bits_default_s.used) {
        architecture_bits.string = f_path_architecture_bits_default_s.string;
        architecture_bits.used = f_path_architecture_bits_default_s.used;
        architecture_bits.size = f_path_architecture_bits_default_s.size;
      }
    #endif // _en_kevux_path_architecture_bits_

    for (i = 0; i <= path.used; ++i) {

      if (i == path.used || path.string[i] == f_path_separator_variable_s.string[0]) {
        #ifdef _en_kevux_path_architecture_bits_
          if (paths->used + 3 > paths->size) {
            status = f_string_dynamics_increase(F_memory_default_allocation_small_d + 2, paths);
          }
        #else
          status = f_string_dynamics_increase(F_memory_default_allocation_small_d, paths);
        #endif // _en_kevux_path_architecture_bits_

        if (F_status_is_error(status)) {
          #ifdef _en_kevux_path_architecture_bits_
            f_string_dynamic_resize(0, &architecture_bits);
          #endif // _en_kevux_path_architecture_bits_

          return status;
        }

        if (!i) {
          paths->array[paths->used++].used = 0;

          first = 1;

          continue;
        }

        total = i - first;
        paths->array[paths->used].used = 0;

        if (total) {
          char buffer[total + 1];

          for (j = first, k = 0; j < i; ++j) {

            if (!path.string[j]) continue;

            buffer[k++] = (char) path.string[j];
          } // for

          // Guarantee a trailing directory separator.
          if (buffer[k - 1] != f_path_separator_s.string[0]) {
            buffer[k++] = f_path_separator_s.string[0];
          }

          #ifdef _en_kevux_path_architecture_bits_
            if (f_path_architecture_bits_s.used) {
              status = f_string_dynamic_increase_by(k + f_path_architecture_bits_s.used, &paths->array[paths->used]);

              if (F_status_is_error(status)) {
                #ifdef _en_kevux_path_architecture_bits_
                  f_string_dynamic_resize(0, &architecture_bits);
                #endif // _en_kevux_path_architecture_bits_

                return status;
              }

              memcpy(paths->array[paths->used].string, buffer, sizeof(f_char_t) * k);
              memcpy(paths->array[paths->used].string + k, architecture_bits.string, sizeof(f_char_t) * architecture_bits.used);

              paths->array[paths->used++].used = k + architecture_bits.used;
            }

            if (f_path_architecture_bits_scripts_s.used) {
              status = f_string_dynamic_increase_by(k + f_path_architecture_bits_scripts_s.used, &paths->array[paths->used]);

              if (F_status_is_error(status)) {
                #ifdef _en_kevux_path_architecture_bits_
                  f_string_dynamic_resize(0, &architecture_bits);
                #endif // _en_kevux_path_architecture_bits_

                return status;
              }

              memcpy(paths->array[paths->used].string, buffer, sizeof(f_char_t) * k);
              memcpy(paths->array[paths->used].string + k, f_path_architecture_bits_scripts_s.string, sizeof(f_char_t) * f_path_architecture_bits_scripts_s.used);

              paths->array[paths->used++].used = k + f_path_architecture_bits_scripts_s.used;
            }
          #endif // _en_kevux_path_architecture_bits_

          status = f_string_dynamic_increase_by(k, &paths->array[paths->used]);

          if (F_status_is_error(status)) {
            #ifdef _en_kevux_path_architecture_bits_
              f_string_dynamic_resize(0, &architecture_bits);
            #endif // _en_kevux_path_architecture_bits_

            return status;
          }

          memcpy(paths->array[paths->used].string, buffer, sizeof(f_char_t) * k);

          paths->array[paths->used++].used = k;
        }
        else {
          ++paths->used;
        }

        first = i + 1;
      }
    } // for

    #ifdef _en_kevux_path_architecture_bits_
      f_string_dynamic_resize(0, &architecture_bits);
    #endif // _en_kevux_path_architecture_bits_

    return F_okay;
  }
#endif // _di_fl_environment_path_explode_

#ifndef _di_fl_environment_path_explode_reverse_
  f_status_t fl_environment_path_explode_reverse(const f_string_static_t path, f_string_dynamics_t * const paths) {
    #ifndef _di_level_1_parameter_checking_
      if (!paths) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_okay;

    if (!path.used) {

      // When PATH is "", this is actually a valid search path for PWD.
      // Therefore append an equivalent representation of PWD (string used length is 0).
      status = f_string_dynamics_increase(F_memory_default_allocation_small_d, paths);
      if (F_status_is_error(status)) return status;

      paths->array[paths->used++].used = 0;

      return F_okay;
    }

    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;
    f_number_unsigned_t k = 0;
    f_number_unsigned_t r = path.used;
    f_number_unsigned_t last = path.used;
    f_number_unsigned_t total = 0;

    // Do a quick pre-process of PATH to approximate the amount of parts needed, reducing the number of allocations.
    for (; i <= path.used; ++i) {
      if (path.string[i] == f_path_separator_variable_s.string[0]) ++total;
    } // for

    #ifdef _en_kevux_path_architecture_bits_
      total *= 3;
    #endif // _en_kevux_path_architecture_bits_

    if (total) {
      status = f_string_dynamics_increase_by(total, paths);
      if (F_status_is_error(status)) return status;

      total = 0;
    }

    #ifdef _en_kevux_path_architecture_bits_
      f_string_dynamic_t architecture_bits = f_string_dynamic_t_initialize;

      if (f_path_architecture_bits_s.used) {
        status = f_environment_get(f_path_architecture_bits_s, &architecture_bits);
        if (F_status_is_error(status)) return status;
      }

      if (architecture_bits.used) {
        status = f_string_dynamic_append_assure(f_path_separator_s, &architecture_bits);

        if (F_status_is_error(status)) {
          f_string_dynamic_resize(0, &architecture_bits);

          return status;
        }
      } else if (!architecture_bits.used && f_path_architecture_bits_default_s.used) {
        architecture_bits.string = f_path_architecture_bits_default_s.string;
        architecture_bits.used = f_path_architecture_bits_default_s.used;
        architecture_bits.size = f_path_architecture_bits_default_s.size;
      }
    #endif // _en_kevux_path_architecture_bits_

    for (; i <= path.used; ++i, --r) {

      if (i == path.used || path.string[r] == f_path_separator_variable_s.string[0]) {
        #ifdef _en_kevux_path_architecture_bits_
          if (paths->used + 3 > paths->size) {
            status = f_string_dynamics_increase(F_memory_default_allocation_small_d + 2, paths);
          }
        #else
          status = f_string_dynamics_increase(F_memory_default_allocation_small_d, paths);
        #endif // _en_kevux_path_architecture_bits_

        if (F_status_is_error(status)) {
          #ifdef _en_kevux_path_architecture_bits_
            f_string_dynamic_resize(0, &architecture_bits);
          #endif // _en_kevux_path_architecture_bits_

          return status;
        }

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

            buffer[k++] = (char) path.string[r + j + 1];
          } // for

          // Guarantee a trailing directory separator.
          if (buffer[k - 1] != f_path_separator_s.string[0]) {
            buffer[k++] = f_path_separator_s.string[0];
          }

          #ifdef _en_kevux_path_architecture_bits_
            if (f_path_architecture_bits_s.used) {
              status = f_string_dynamic_increase_by(k + f_path_architecture_bits_s.used, &paths->array[paths->used]);

              if (F_status_is_error(status)) {
                #ifdef _en_kevux_path_architecture_bits_
                  f_string_dynamic_resize(0, &architecture_bits);
                #endif // _en_kevux_path_architecture_bits_

                return status;
              }

              memcpy(paths->array[paths->used].string, buffer, sizeof(f_char_t) * k);
              memcpy(paths->array[paths->used].string + k, architecture_bits.string, sizeof(f_char_t) * architecture_bits.used);

              paths->array[paths->used++].used = k + architecture_bits.used;
            }

            if (f_path_architecture_bits_scripts_s.used) {
              status = f_string_dynamic_increase_by(k + f_path_architecture_bits_scripts_s.used, &paths->array[paths->used]);

              if (F_status_is_error(status)) {
                #ifdef _en_kevux_path_architecture_bits_
                  f_string_dynamic_resize(0, &architecture_bits);
                #endif // _en_kevux_path_architecture_bits_

                return status;
              }

              memcpy(paths->array[paths->used].string, buffer, sizeof(f_char_t) * k);
              memcpy(paths->array[paths->used].string + k, f_path_architecture_bits_scripts_s.string, sizeof(f_char_t) * f_path_architecture_bits_scripts_s.used);

              paths->array[paths->used++].used = k + f_path_architecture_bits_scripts_s.used;
            }
          #endif // _en_kevux_path_architecture_bits_

          status = f_string_dynamic_increase_by(k, &paths->array[paths->used]);

          if (F_status_is_error(status)) {
            #ifdef _en_kevux_path_architecture_bits_
              f_string_dynamic_resize(0, &architecture_bits);
            #endif // _en_kevux_path_architecture_bits_

            return status;
          }

          memcpy(paths->array[paths->used].string, buffer, sizeof(f_char_t) * k);

          paths->array[paths->used++].used = k;
        }
        else {
          ++paths->used;
        }

        last = r - 1;
      }
    } // for

    #ifdef _en_kevux_path_architecture_bits_
      f_string_dynamic_resize(0, &architecture_bits);
    #endif // _en_kevux_path_architecture_bits_

    return F_okay;
  }
#endif // _di_fl_environment_path_explode_reverse_

#ifdef __cplusplus
} // extern "C"
#endif
