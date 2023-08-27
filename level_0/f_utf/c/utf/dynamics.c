#include "../utf.h"
#include "../private-utf.h"
#include "static.h"
#include "private-dynamics.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_string_dynamics_append_
  f_status_t f_utf_string_dynamics_append(const f_utf_string_dynamic_t source, f_utf_string_dynamics_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_utf_string_dynamics_append(source, destination);
  }
#endif // _di_f_utf_string_dynamics_append_

#ifndef _di_f_utf_string_dynamics_append_all_
  f_status_t f_utf_string_dynamics_append_all(const f_utf_string_dynamics_t source, f_utf_string_dynamics_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_utf_string_dynamics_append_all(source, destination);
  }
#endif // _di_f_utf_string_dynamics_append_all_

#ifndef _di_f_utf_string_dynamics_delete_callback_
  f_status_t f_utf_string_dynamics_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_utf_string_dynamic_t * const array = (f_utf_string_dynamic_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (array[i].size) {
          status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].string, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_utf_string_dynamics_delete_callback_

#ifndef _di_f_utf_string_dynamics_destroy_callback_
  f_status_t f_utf_string_dynamics_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_utf_string_dynamic_t * const array = (f_utf_string_dynamic_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (array[i].size) {
          status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].string, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_utf_string_dynamics_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
