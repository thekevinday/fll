#include <level_0/environment.h>
#include "private-environment.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_environment_clear_
  f_return_status f_environment_clear() {
    if (clearenv() == 0) {
      return F_none;
    }

    return F_status_set_error(F_failure);
  }
#endif // _di_f_environment_clear_

#ifndef _di_f_environment_get_
  f_return_status f_environment_get(const f_string name, f_string_dynamic *value) {
    return private_f_environment_get(name, value);
  }
#endif // _di_f_environment_get_

#ifndef _di_f_environment_get_dynamic_
  f_return_status f_environment_get_dynamic(const f_string_static name, f_string_dynamic *value) {
    #ifndef _di_level_0_parameter_checking_
      if (name.used > name.size) return F_status_set_error(F_parameter);
      if (value->used > value->size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (name.used == 0) return F_data_not;

    if (name.string[name.used - 1] == 0) {
      return private_f_environment_get(name.string, value);
    }

    char variable_name[name.used + 1];

    memcpy(&variable_name, name.string, name.used);
    variable_name[name.used] = 0;

    return private_f_environment_get(variable_name, value);
  }
#endif // _di_f_environment_get_dynamic_

#ifndef _di_f_environment_set_
  f_return_status f_environment_set(const f_string name, const f_string value, const bool replace) {
    return private_f_environment_set(name, value, replace);
  }
#endif // _di_f_environment_set_

#ifndef _di_f_environment_set_dynamic_
  f_return_status f_environment_set_dynamic(const f_string_static name, const f_string_static value, const bool replace) {
    #ifndef _di_level_0_parameter_checking_
      if (name.used > name.size) return F_status_set_error(F_parameter);
      if (value.used > value.size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (name.used == 0) return F_data_not;

    if (name.string[name.used - 1] == 0) {
      if (value.used > 0 && value.string[value.used - 1] == 0) {
        return private_f_environment_set(name.string, value.string, replace);
      }

      char variable_value[value.used + 1];

      if (value.used > 0) {
        memcpy(&variable_value, value.string, value.used);
      }

      variable_value[value.used] = 0;

      return private_f_environment_set(name.string, variable_value, replace);
    }

    char variable_name[name.used + 1];

    memcpy(&variable_name, name.string, name.used);
    variable_name[name.used] = 0;

    if (value.used > 0 && value.string[value.used - 1] == 0) {
      return private_f_environment_set(variable_name, value.string, replace);
    }

    char variable_value[value.used + 1];

    if (value.used > 0) {
      memcpy(&variable_value, value.string, value.used);
    }

    variable_value[value.used] = 0;

    return private_f_environment_set(variable_name, variable_value, replace);
  }
#endif // _di_f_environment_set_dynamic_

#ifndef _di_f_environment_unset_
  f_return_status f_environment_unset(const f_string name) {
    return private_f_environment_unset(name);
  }
#endif // _di_f_environment_unset_

#ifndef _di_f_environment_unset_
  f_return_status f_environment_unset_dynamic(const f_string_static name) {
    #ifndef _di_level_0_parameter_checking_
      if (name.used > name.size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (name.used == 0) return F_data_not;

    if (name.string[name.used - 1] == 0) {
      return private_f_environment_unset(name.string);
    }

    char variable_name[name.used + 1];

    memcpy(&variable_name, name.string, name.used);
    variable_name[name.used] = 0;

    return private_f_environment_unset(variable_name);
  }
#endif // _di_f_environment_unset_

#ifdef __cplusplus
} // extern "C"
#endif
