#include "../string.h"
#include "../private-string.h"
#include "private-quantitys.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_string_quantitys_adjust_
  f_status_t f_string_quantitys_adjust(const f_number_unsigned_t length, f_string_quantitys_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_adjust(length, sizeof(f_string_quantity_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_string_quantitys_adjust_

#ifndef _di_f_string_quantitys_append_
  f_status_t f_string_quantitys_append(const f_string_quantity_t source, f_string_quantitys_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (destination->used + 1 > destination->size) {
      const f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_string_quantity_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used].start = source.start;
    destination->array[destination->used++].total = source.total;

    return F_none;
  }
#endif // _di_f_string_quantitys_append_

#ifndef _di_f_string_quantitys_append_all_
  f_status_t f_string_quantitys_append_all(const f_string_quantitys_t source, f_string_quantitys_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_string_quantitys_append_all(source, destination);
  }
#endif // _di_f_string_quantitys_append_all_

#ifndef _di_f_string_quantitys_decimate_by_
  f_status_t f_string_quantitys_decimate_by(const f_number_unsigned_t amount, f_string_quantitys_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decimate_by(amount, sizeof(f_string_quantity_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_string_quantitys_decimate_by_

#ifndef _di_f_string_quantitys_decrease_by_
  f_status_t f_string_quantitys_decrease_by(const f_number_unsigned_t amount, f_string_quantitys_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_


    return f_memory_array_decrease_by(amount, sizeof(f_string_quantity_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_string_quantitys_decrease_by_

#ifndef _di_f_string_quantitys_increase_
  f_status_t f_string_quantitys_increase(const f_number_unsigned_t step, f_string_quantitys_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(f_string_quantity_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_string_quantitys_increase_

#ifndef _di_f_string_quantitys_increase_by_
  f_status_t f_string_quantitys_increase_by(const f_number_unsigned_t amount, f_string_quantitys_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(f_string_quantity_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_string_quantitys_increase_by_

#ifndef _di_f_string_quantitys_resize_
  f_status_t f_string_quantitys_resize(const f_number_unsigned_t length, f_string_quantitys_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_resize(length, sizeof(f_string_quantity_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_string_quantitys_resize_

#ifdef __cplusplus
} // extern "C"
#endif
