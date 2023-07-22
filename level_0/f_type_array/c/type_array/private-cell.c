#include "../type_array.h"
#include "private-cell.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_cells_append_) || !defined(_di_f_cellss_append_)
  extern f_status_t private_f_cells_append(const f_cell_t source, f_cells_t * const destination) {

    {
      const f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_cell_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used++] = source;

    return F_none;
  }
#endif // !defined(_di_f_cells_append_) || !defined(_di_f_cellss_append_)

#if !defined(_di_f_cells_append_) || !defined(_di_f_cells_append_all_) || !defined(_di_f_cellss_append_all_)
  extern f_status_t private_f_cells_append_all(const f_cells_t source, f_cells_t * const destination) {

    {
      const f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_cell_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {

      destination->array[destination->used].row = source.array[i].row;
      destination->array[destination->used++].column = source.array[i].column;
    } // for

    return F_none;
  }
#endif // !defined(_di_f_cells_append_) || !defined(_di_f_cells_append_all_) || !defined(_di_f_cellss_append_all_)

#if !defined(_di_f_cellss_adjust_) || !defined(_di_f_cellss_decimate_by_)
  f_status_t private_f_cellss_adjust(const f_number_unsigned_t length, f_cellss_t * const structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = f_memory_array_adjust(0, sizeof(f_cell_t), (void **) &structure->array[i].array, &structure->array[i].used, &structure->array[i].size);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_cells_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_cellss_adjust_) || !defined(_di_f_cellss_decimate_by_)

#if !defined(_di_f_cellss_decrease_by_) || !defined(_di_f_cellss_increase_) || !defined(_di_f_cellss_increase_by_) || !defined(_di_f_cellss_resize_)
  f_status_t private_f_cellss_resize(const f_number_unsigned_t length, f_cellss_t * const structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = f_memory_array_resize(0, sizeof(f_cell_t), (void **) &structure->array[i].array, &structure->array[i].used, &structure->array[i].size);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_cells_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_cellss_decrease_by_) || !defined(_di_f_cellss_increase_) || !defined(_di_f_cellss_increase_by_) || !defined(_di_f_cellss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif
