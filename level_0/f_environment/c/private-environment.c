#include "environment.h"
#include "private-environment.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_environment_get_) || !defined(_di_f_environment_get_dynamic_)
  f_return_status private_f_environment_get(const f_string name, f_string_dynamic *value) {
    const f_string result = getenv(name);

    if (result == 0) {
      return F_exist_not;
    }

    const f_string_length size = strnlen(result, f_environment_max_length);

    if (size == 0) {
      value->used = 0;
    }
    else {
      if (value->used + size > f_environment_max_length) {
        return F_status_set_error(F_string_too_large);
      }

      if (value->used + size > value->size) {
        f_status status = F_none;

        f_macro_string_dynamic_resize(status, (*value), size);
        if (F_status_is_error(status)) return status;
      }

      memcpy(value->string + value->used, result, value->used + size);
      value->used = size;
    }

    return F_none;
  }
#endif // !defined(_di_f_environment_get_) || !defined(_di_f_environment_get_dynamic_)

#if !defined(_di_f_environment_set_) || !defined(_di_f_environment_set_dynamic_)
  f_return_status private_f_environment_set(const f_string name, const f_string value, const bool replace) {
    if (setenv(name, value, replace) < 0) {
      if (errno == EINVAL) {
        return F_status_set_error(F_invalid);
      }
      else if (errno == ENOMEM) {
        return F_status_set_error(F_memory_out);
      }

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_environment_set_) || !defined(_di_f_environment_set_dynamic_)

#if !defined(_di_f_environment_unset_) || !defined(_di_f_environment_unset_dynamic_)
  f_return_status private_f_environment_unset(const f_string name) {
    if (unsetenv(name) < 0) {
      if (errno == EINVAL) {
        return F_status_set_error(F_invalid);
      }
      else if (errno == ENOMEM) {
        return F_status_set_error(F_memory_out);
      }

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_f_environment_unset_) || !defined(_di_f_environment_unset_dynamic_)

#ifdef __cplusplus
} // extern "C"
#endif
