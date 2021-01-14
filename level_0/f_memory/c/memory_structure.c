#include "memory.h"
#include "private-memory.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_memory_structure_adjust_
  f_status_t f_memory_structure_adjust(const size_t length_new, const size_t type_size, void **structure, f_array_length_t *used, f_array_length_t *size) {
    #ifndef _di_level_0_parameter_checking_
      if (!type_size) return F_status_set_error(F_parameter);
      if (!structure) return F_status_set_error(F_parameter);
      if (!used) return F_status_set_error(F_parameter);
      if (!size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_memory_structure_adjust(length_new, type_size, structure, used, size);
  }
#endif // _di_f_memory_structure_adjust_

#ifndef _di_f_memory_structure_decimate_by_
  f_status_t f_memory_structure_decimate_by(const f_array_length_t amount, const size_t type_size, void **structure, f_array_length_t *used, f_array_length_t *size) {
    #ifndef _di_level_0_parameter_checking_
      if (!type_size) return F_status_set_error(F_parameter);
      if (!structure) return F_status_set_error(F_parameter);
      if (!used) return F_status_set_error(F_parameter);
      if (!size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount && *size) {
      return private_f_memory_structure_adjust(amount <= *size ? *size - amount : 0, type_size, structure, used, size);
    }

    return F_data_not;
  }
#endif // _di_f_memory_structure_decimate_by_

#ifndef _di_f_memory_structure_decrease_by_
  f_status_t f_memory_structure_decrease_by(const f_array_length_t amount, const size_t type_size, void **structure, f_array_length_t *used, f_array_length_t *size) {
    #ifndef _di_level_0_parameter_checking_
      if (!type_size) return F_status_set_error(F_parameter);
      if (!structure) return F_status_set_error(F_parameter);
      if (!used) return F_status_set_error(F_parameter);
      if (!size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount && *size) {
      return private_f_memory_structure_resize(amount <= *size ? *size - amount : 0, type_size, structure, used, size);
    }

    return F_data_not;
  }
#endif // _di_f_memory_structure_decrease_by_

#ifndef _di_f_memory_structure_increase_
  f_status_t f_memory_structure_increase(const size_t type_size, void **structure, f_array_length_t *used, f_array_length_t *size) {
    #ifndef _di_level_0_parameter_checking_
      if (!type_size) return F_status_set_error(F_parameter);
      if (!structure) return F_status_set_error(F_parameter);
      if (!used) return F_status_set_error(F_parameter);
      if (!size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (*used + 1 > *size) {
      f_array_length_t length_new = *used + f_memory_default_allocation_step;

      if (length_new > f_array_length_t_size) {
        if (*used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        length_new = f_array_length_t_size;
      }

      return private_f_memory_structure_resize(length_new, type_size, structure, used, size);
    }

    return F_data_not;
  }
#endif // _di_f_memory_structure_increase_

#ifndef _di_f_memory_structure_increase_by_
  f_status_t f_memory_structure_increase_by(const f_array_length_t amount, const size_t type_size, void **structure, f_array_length_t *used, f_array_length_t *size) {
    #ifndef _di_level_0_parameter_checking_
      if (!type_size) return F_status_set_error(F_parameter);
      if (!structure) return F_status_set_error(F_parameter);
      if (!used) return F_status_set_error(F_parameter);
      if (!size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (*used + amount > *size) {
      if (*used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_memory_structure_resize(*used + amount, type_size, structure, used, size);
    }

    return F_data_not;
  }
#endif // _di_f_memory_structure_increase_by_

#ifndef _di_f_memory_structure_resize_
  f_status_t f_memory_structure_resize(const size_t length_new, const size_t type_size, void **structure, f_array_length_t *used, f_array_length_t *size) {
    #ifndef _di_level_0_parameter_checking_
      if (!type_size) return F_status_set_error(F_parameter);
      if (!structure) return F_status_set_error(F_parameter);
      if (!used) return F_status_set_error(F_parameter);
      if (!size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_memory_structure_resize(length_new, type_size, structure, used, size);
  }
#endif // _di_f_memory_structure_resize_

#ifdef __cplusplus
} // extern "C"
#endif
