#include "environment.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_environment_load_name_
  f_status_t fll_environment_load_name(const f_string_t name, const f_string_length_t length, f_string_maps_t *environment) {
    #ifndef _di_level_2_parameter_checking_
      if (!name) return F_status_set_error(F_parameter);
      if (!environment) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (!length) {
      return F_data_not;
    }

    f_status_t status = f_string_maps_increase(environment);
    if (F_status_is_error(status)) return status;

    environment->array[environment->used].name.used = 0;
    environment->array[environment->used].value.used = 0;

    const f_string_static_t name_string = f_macro_string_static_t_initialize(name, length);

    status = f_string_dynamic_append_nulless(name_string, &environment->array[environment->used].name);
    if (F_status_is_error(status)) return status;

    status = f_environment_get_dynamic(name_string, &environment->array[environment->used].value);

    if (F_status_is_error(status)) {
      environment->array[environment->used].name.used = 0;
      return status;
    }

    if (status == F_data_not || status == F_exist_not) {
      environment->array[environment->used].name.used = 0;
      return status;
    }

    environment->used++;

    return F_none;
  }
#endif // _di_fll_environment_load_name_

#ifndef _di_fll_environment_load_names_
  f_status_t fll_environment_load_names(const f_string_dynamics_t names, f_string_maps_t *environment) {
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

      status = f_environment_get_dynamic(names.array[i], &environment->array[environment->used].value);

      if (F_status_is_error(status)) {
        environment->array[environment->used].name.used = 0;
        return status;
      }

      if (status == F_data_not || status == F_exist_not) {
        environment->array[environment->used].name.used = 0;
        continue;
      }

      environment->used++;
    } // for

    return F_none;
  }
#endif // _di_fll_environment_load_names_

#ifdef __cplusplus
} // extern "C"
#endif
