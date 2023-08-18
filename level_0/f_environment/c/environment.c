#include "environment.h"

#ifdef __cplusplus
extern "C" {
#endif

// for loading all current environment variables.
extern char **environ;

#ifndef _di_f_environment_clear_
  f_status_t f_environment_clear(void) {

    if (!clearenv()) {
      return F_okay;
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

    const char *result = getenv(name.string);

    if (!result) {
      return F_exist_not;
    }

    const f_number_unsigned_t size = strnlen(result, f_environment_max_length_d);

    if (size) {
      const f_status_t status = f_string_dynamic_increase_by(size + 1, value);
      if (F_status_is_error(status)) return status;

      memcpy(value->string + value->used, result, sizeof(char) * size);

      value->used += size;
      value->string[value->used] = 0;
    }
    else {
      const f_status_t status = f_string_dynamic_increase_by(1, value);
      if (F_status_is_error(status)) return status;

      value->string[0] = 0;
      value->used = 0;
    }

    return F_okay;
  }
#endif // _di_f_environment_get_

#ifndef _di_f_environment_get_all_
  f_status_t f_environment_get_all(f_string_maps_t * const environment) {
    #ifndef _di_level_0_parameter_checking_
      if (!environment) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_okay;
    char *at = 0;
    f_string_map_t map = f_string_map_t_initialize;

    // Copy all environment variables over when a custom define is used.
    for (char **string = environ; *string; string++) {

      map.name.string = 0;
      map.value.string = 0;

      map.name.used = 0;
      map.value.used = 0;

      at = index(*string, f_string_ascii_equal_s.string[0]);
      if (!at || at == *string) continue;

      map.name.string = *string;
      map.name.used = at - *string;

      map.value.string = at + 1;
      map.value.used = strlen(at + 1);

      status = f_string_maps_append(map, environment);
      if (F_status_is_error(status)) return status;
    } // for

    return F_okay;
  }
#endif // _di_f_environment_get_all_

#ifndef _di_f_environment_secure_is_
  f_status_t f_environment_secure_is(void) {

    if (geteuid() == getuid() && getegid() == getgid()) {
      return F_true;
    }

    #ifndef _di_libcap_
      cap_t capability = cap_get_proc();

      if (!capability) {
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EPERM) return F_status_set_error(F_prohibited);
        if (errno == ENOMEM) return F_status_set_error(F_memory_not);

        return F_status_set_error(F_failure);
      }

      cap_flag_value_t value;

      memset(&value, 0, sizeof(cap_flag_value_t));

      if (cap_get_flag(capability, CAP_SETUID, CAP_EFFECTIVE, &value) == -1) {
        cap_free(capability);

        if (errno == EINVAL) return F_status_set_error(F_parameter);

        return F_status_set_error(F_failure);
      }

      cap_free(capability);

      if (value == CAP_SET) {
        return F_true;
      }
    #endif // _di_libcap_

    return F_false;
  }
#endif // _di_f_environment_secure_is_

#ifndef _di_f_environment_set_
  f_status_t f_environment_set(const f_string_static_t name, const f_string_static_t value, const bool replace) {

    if (!name.used) {
      return F_data_not;
    }

    if (setenv(name.string, value.used ? value.string : "", replace) < 0) {
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }

    return F_okay;
  }
#endif // _di_f_environment_set_

#ifndef _di_f_environment_unset_
  f_status_t f_environment_unset(const f_string_static_t name) {

    if (!name.used) {
      return F_data_not;
    }

    if (unsetenv(name.string) < 0) {
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }

    return F_okay;
  }
#endif // _di_f_environment_unset_

#ifdef __cplusplus
} // extern "C"
#endif
