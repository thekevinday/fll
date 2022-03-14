#include "../type_array.h"
#include "private-cell.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_cells_adjust_) || !defined(_di_f_cells_decimate_by_)
  f_status_t private_f_cells_adjust(const f_array_length_t length, f_cells_t *cells) {

    const f_status_t status = f_memory_adjust(cells->size, length, sizeof(f_cell_t), (void **) & cells->array);
    if (F_status_is_error(status)) return status;

    cells->size = length;

    if (cells->used > cells->size) {
      cells->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_cells_adjust_) || !defined(_di_f_cells_decimate_by_)

#if !defined(_di_f_cells_append_) || !defined(_di_f_cellss_append_)
  extern f_status_t private_f_cells_append(const f_cell_t source, f_cells_t *destination) {

    if (destination->used + 1 > destination->size) {
      const f_status_t status = private_f_cells_adjust(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used].row = source.row;
    destination->array[destination->used++].column = source.column;

    return F_none;
  }
#endif // !defined(_di_f_cells_append_) || !defined(_di_f_cellss_append_)

#if !defined(_di_f_cells_append_) || !defined(_di_f_cells_append_all_) || !defined(_di_f_cellss_append_all_)
  extern f_status_t private_f_cells_append_all(const f_cells_t source, f_cells_t *destination) {

    if (destination->used + source.used > destination->size) {
      const f_status_t status = private_f_cells_adjust(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i) {

      destination->array[destination->used].row = source.array[i].row;
      destination->array[destination->used++].column = source.array[i].column;
    } // for

    return F_none;
  }
#endif // !defined(_di_f_cells_append_) || !defined(_di_f_cells_append_all_) || !defined(_di_f_cellss_append_all_)

#if !defined(_di_f_cells_resize_) || !defined(_di_f_cells_append_) || !defined(_di_f_cells_decimate_by_) || !defined(_di_f_cellss_append_)
  f_status_t private_f_cells_resize(const f_array_length_t length, f_cells_t *cells) {

    const f_status_t status = f_memory_resize(cells->size, length, sizeof(f_cell_t), (void **) & cells->array);
    if (F_status_is_error(status)) return status;

    cells->size = length;

    if (cells->used > cells->size) {
      cells->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_cells_resize_) || !defined(_di_f_cells_append_) || !defined(_di_f_cells_decimate_by_) || !defined(_di_f_cellss_append_)

#if !defined(_di_f_cellss_adjust_) || !defined(_di_f_cellss_decimate_by_)
  f_status_t private_f_cellss_adjust(const f_array_length_t length, f_cellss_t *cellss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < cellss->size; ++i) {

      status = f_memory_destroy(cellss->array[i].size, sizeof(f_cells_t), (void **) & cellss->array[i].array);
      if (F_status_is_error(status)) return status;

      cellss->array[i].size = 0;
      cellss->array[i].used = 0;
    } // for

    status = f_memory_adjust(cellss->size, length, sizeof(f_cells_t), (void **) & cellss->array);
    if (F_status_is_error(status)) return status;

    cellss->size = length;

    if (cellss->used > cellss->size) {
      cellss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_cellss_adjust_) || !defined(_di_f_cellss_decimate_by_)

#if !defined(_di_f_cellss_decrease_by_) || !defined(_di_f_cellss_increase_) || !defined(_di_f_cellss_increase_by_) || !defined(_di_f_cellss_resize_)
  f_status_t private_f_cellss_resize(const f_array_length_t length, f_cellss_t *cellss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < cellss->size; ++i) {

      status = f_memory_delete(cellss->array[i].size, sizeof(f_cells_t), (void **) & cellss->array[i].array);
      if (F_status_is_error(status)) return status;

      cellss->array[i].size = 0;
      cellss->array[i].used = 0;
    } // for

    status = f_memory_resize(cellss->size, length, sizeof(f_cells_t), (void **) & cellss->array);
    if (F_status_is_error(status)) return status;

    cellss->size = length;

    if (cellss->used > cellss->size) {
      cellss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_cellss_decrease_by_) || !defined(_di_f_cellss_increase_) || !defined(_di_f_cellss_increase_by_) || !defined(_di_f_cellss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif
