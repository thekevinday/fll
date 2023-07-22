#include "../type_array.h"
#include "cell.h"
#include "private-cell.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_cells_adjust_
  f_status_t f_cells_adjust(const f_number_unsigned_t length, f_cells_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_adjust(length, sizeof(f_cell_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_cells_adjust_

#ifndef _di_f_cells_append_
  f_status_t f_cells_append(const f_cell_t source, f_cells_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_cells_append(source, destination);
  }
#endif // _di_f_cells_append_

#ifndef _di_f_cells_append_all_
  f_status_t f_cells_append_all(const f_cells_t source, f_cells_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_cells_append_all(source, destination);
  }
#endif // _di_f_cells_append_all_

#ifndef _di_f_cells_decimate_by_
  f_status_t f_cells_decimate_by(const f_number_unsigned_t amount, f_cells_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decimate_by(amount, sizeof(f_cell_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_cells_decimate_by_

#ifndef _di_f_cells_decrease_by_
  f_status_t f_cells_decrease_by(const f_number_unsigned_t amount, f_cells_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decrease_by(amount, sizeof(f_cell_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_cells_decrease_by_

#ifndef _di_f_cells_increase_
  f_status_t f_cells_increase(const f_number_unsigned_t step, f_cells_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(f_cell_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_cells_increase_

#ifndef _di_f_cells_increase_by_
  f_status_t f_cells_increase_by(const f_number_unsigned_t amount, f_cells_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(f_cell_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_cells_increase_by_

#ifndef _di_f_cells_resize_
  f_status_t f_cells_resize(const f_number_unsigned_t length, f_cells_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_resize(length, sizeof(f_cell_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_cells_resize_

#ifndef _di_f_cellss_adjust_
  f_status_t f_cellss_adjust(const f_number_unsigned_t length, f_cellss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_cellss_adjust(length, structure);
  }
#endif // _di_f_cellss_adjust_

#ifndef _di_f_cellss_append_
  f_status_t f_cellss_append(const f_cells_t source, f_cellss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_cells_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    status = private_f_cells_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_cellss_append_

#ifndef _di_f_cellss_append_all_
  f_status_t f_cellss_append_all(const f_cellss_t source, f_cellss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_cells_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_cells_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_cellss_append_all_

#ifndef _di_f_cellss_decimate_by_
  f_status_t f_cellss_decimate_by(const f_number_unsigned_t amount, f_cellss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_cellss_adjust((structure->size - amount > 0) ? structure->size - amount : 0, structure);
  }
#endif // _di_f_cellss_decimate_by_

#ifndef _di_f_cellss_decrease_by_
  f_status_t f_cellss_decrease_by(const f_number_unsigned_t amount, f_cellss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_cellss_resize((structure->size - amount > 0) ? structure->size - amount : 0, structure);
  }
#endif // _di_f_cellss_decrease_by_

#ifndef _di_f_cellss_increase_
  f_status_t f_cellss_increase(const f_number_unsigned_t step, f_cellss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && structure->used + 1 > structure->size) {
      if (structure->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      f_number_unsigned_t length = structure->used + step;

      if (length > F_number_t_size_unsigned_d) {
        if (structure->used + 1 > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        length = F_number_t_size_unsigned_d;
      }

      return private_f_cellss_resize(length, structure);
    }

    return F_data_not;
  }
#endif // _di_f_cellss_increase_

#ifndef _di_f_cellss_increase_by_
  f_status_t f_cellss_increase_by(const f_number_unsigned_t amount, f_cellss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (structure->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = structure->used + amount;

      if (length > structure->size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        return private_f_cellss_resize(structure->used + amount, structure);
      }
    }

    return F_data_not;
  }
#endif // _di_f_cellss_increase_by_

#ifndef _di_f_cellss_resize_
  f_status_t f_cellss_resize(const f_number_unsigned_t length, f_cellss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_cellss_resize(length, structure);
  }
#endif // _di_f_cellss_resize_

#ifdef __cplusplus
} // extern "C"
#endif
