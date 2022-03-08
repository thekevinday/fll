#include "environment.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_environment_clear_
  f_status_t f_environment_clear(void) {

    if (!clearenv()) {
      return F_none;
    }

    return F_status_set_error(F_failure);
  }
#endif // _di_f_environment_clear_

#ifndef _di_f_environment_exists_
  f_status_t f_environment_exists(const f_string_static_t name) {

    if (!name.used) {
      return F_data_not;
    }

    if (getenv(name.string)) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_environment_exists_

#ifndef _di_f_environment_get_
  f_status_t f_environment_get(const f_string_static_t name, f_string_dynamic_t * const value) {
    #ifndef _di_level_0_parameter_checking_
      if (!value) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!name.used) {
      return F_data_not;
    }

    const f_string_t result = getenv(name.string);

    if (!result) {
      return F_exist_not;
    }

    const f_array_length_t size = strnlen(result, f_environment_max_length);

    if (size) {
      const f_status_t status = f_string_dynamic_increase_by(size + 1, value);
      if (F_status_is_error(status)) return status;

      memcpy(value->string + value->used, result, sizeof(unsigned char) * size);

      value->used += size;
      value->string[value->used] = 0;
    }
    else {
      const f_status_t status = f_string_dynamic_increase_by(1, value);
      if (F_status_is_error(status)) return status;

      value->string[0] = 0;
      value->used = 0;
    }

    return F_none;
  }
#endif // _di_f_environment_get_

#ifndef _di_f_environment_set_
  f_status_t f_environment_set(const f_string_static_t name, const f_string_static_t value, const bool replace) {

    if (!name.used) {
      return F_data_not;
    }

    if (setenv(name.string, value.string, replace) < 0) {
      if (errno == EINVAL) return F_status_set_error(F_valid_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_environment_set_

#ifndef _di_f_environment_unset_
  f_status_t f_environment_unset(const f_string_static_t name) {

    if (!name.used) {
      return F_data_not;
    }

    if (unsetenv(name.string) < 0) {
      if (errno == EINVAL) return F_status_set_error(F_valid_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_environment_unset_

#ifdef __cplusplus
} // extern "C"
#endif
