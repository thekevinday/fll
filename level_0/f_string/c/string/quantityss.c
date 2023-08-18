#include "../string.h"
#include "../private-string.h"
#include "private-quantitys.h"
#include "private-quantityss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_string_quantityss_adjust_
  f_status_t f_string_quantityss_adjust(const f_number_unsigned_t length, f_string_quantityss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_quantityss_adjust(length, structure);
  }
#endif // _di_f_string_quantityss_adjust_

#ifndef _di_f_string_quantityss_append_
  f_status_t f_string_quantityss_append(const f_string_quantitys_t source, f_string_quantityss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_okay;

    if (destination->used + 1 > destination->size) {
      status = private_f_string_quantityss_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used].used = 0;

    if (source.used) {
      status = private_f_string_quantitys_append_all(source, &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    }

    ++destination->used;

    return F_okay;
  }
#endif // _di_f_string_quantityss_append_

#ifndef _di_f_string_quantityss_append_all_
  f_status_t f_string_quantityss_append_all(const f_string_quantityss_t source, f_string_quantityss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_okay;

    if (destination->used + source.used > destination->size) {
      status = private_f_string_quantityss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_string_quantitys_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_okay;
  }
#endif // _di_f_string_quantityss_append_all_

#ifndef _di_f_string_quantityss_decimate_by_
  f_status_t f_string_quantityss_decimate_by(const f_number_unsigned_t amount, f_string_quantityss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_string_quantityss_adjust((structure->size > amount) ? structure->size - amount : 0, structure);
  }
#endif // _di_f_string_quantityss_decimate_by_

#ifndef _di_f_string_quantityss_decrease_by_
  f_status_t f_string_quantityss_decrease_by(const f_number_unsigned_t amount, f_string_quantityss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_string_quantityss_resize((structure->size > amount) ? structure->size - amount : 0, structure);
  }
#endif // _di_f_string_quantityss_decrease_by_

#ifndef _di_f_string_quantityss_increase_
  f_status_t f_string_quantityss_increase(const f_number_unsigned_t step, f_string_quantityss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && structure->used + 1 > structure->size) {
      f_number_unsigned_t length = structure->used + step;

      if (length > F_number_t_size_unsigned_d) {
        if (structure->used + 1 > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        length = F_number_t_size_unsigned_d;
      }

      return private_f_string_quantityss_resize(length, structure);
    }

    return F_data_not;
  }
#endif // _di_f_string_quantityss_increase_

#ifndef _di_f_string_quantityss_increase_by_
  f_status_t f_string_quantityss_increase_by(const f_number_unsigned_t amount, f_string_quantityss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (structure->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = structure->used + amount;

      if (length > structure->size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        return private_f_string_quantityss_resize(length, structure);
      }
    }

    return F_data_not;
  }
#endif // _di_f_string_quantityss_increase_by_

#ifndef _di_f_string_quantityss_resize_
  f_status_t f_string_quantityss_resize(const f_number_unsigned_t length, f_string_quantityss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_quantityss_resize(length, structure);
  }
#endif // _di_f_string_quantityss_resize_

#ifdef __cplusplus
} // extern "C"
#endif
