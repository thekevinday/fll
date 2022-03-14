#include "../type_array.h"
#include "cell.h"
#include "private-cell.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_cells_adjust_
  f_status_t f_cells_adjust(const f_array_length_t length, f_cells_t *cells) {
    #ifndef _di_level_0_parameter_checking_
      if (!cells) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_cells_adjust(length, cells);
  }
#endif // _di_f_cells_adjust_

#ifndef _di_f_cells_append_
  f_status_t f_cells_append(const f_cell_t source, f_cells_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_cells_append(source, destination);
  }
#endif // _di_f_cells_append_

#ifndef _di_f_cells_append_all_
  f_status_t f_cells_append_all(const f_cells_t source, f_cells_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_cells_append_all(source, destination);
  }
#endif // _di_f_cells_append_all_

#ifndef _di_f_cells_decimate_by_
  f_status_t f_cells_decimate_by(const f_array_length_t amount, f_cells_t *cells) {
    #ifndef _di_level_0_parameter_checking_
      if (!cells) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (cells->size - amount > 0) {
      return private_f_cells_adjust(cells->size - amount, cells);
    }

    return private_f_cells_adjust(0, cells);
  }
#endif // _di_f_cells_decimate_by_

#ifndef _di_f_cells_decrease_by_
  f_status_t f_cells_decrease_by(const f_array_length_t amount, f_cells_t *cells) {
    #ifndef _di_level_0_parameter_checking_
      if (!cells) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (cells->size - amount > 0) {
      return private_f_cells_resize(cells->size - amount, cells);
    }

    return private_f_cells_resize(0, cells);
  }
#endif // _di_f_cells_decrease_by_

#ifndef _di_f_cells_increase_
  f_status_t f_cells_increase(const f_array_length_t step, f_cells_t *cells) {
    #ifndef _di_level_0_parameter_checking_
      if (!cells) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && cells->used + 1 > cells->size) {
      f_array_length_t size = cells->used + step;

      if (size > F_array_length_t_size_d) {
        if (cells->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_cells_resize(size, cells);
    }

    return F_data_not;
  }
#endif // _di_f_cells_increase_

#ifndef _di_f_cells_increase_by_
  f_status_t f_cells_increase_by(const f_array_length_t amount, f_cells_t *cells) {
    #ifndef _di_level_0_parameter_checking_
      if (!cells) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (cells->used + amount > cells->size) {
      if (cells->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_cells_resize(cells->used + amount, cells);
    }

    return F_data_not;
  }
#endif // _di_f_cells_increase_by_

#ifndef _di_f_cells_resize_
  f_status_t f_cells_resize(const f_array_length_t length, f_cells_t *cells) {
    #ifndef _di_level_0_parameter_checking_
      if (!cells) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_cells_resize(length, cells);
  }
#endif // _di_f_cells_resize_

#ifndef _di_f_cellss_adjust_
  f_status_t f_cellss_adjust(const f_array_length_t length, f_cellss_t *cellss) {
    #ifndef _di_level_0_parameter_checking_
      if (!cellss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_cellss_adjust(length, cellss);
  }
#endif // _di_f_cellss_adjust_

#ifndef _di_f_cellss_append_
  f_status_t f_cellss_append(const f_cells_t source, f_cellss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_cellss_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    status = private_f_cells_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_cellss_append_

#ifndef _di_f_cellss_append_all_
  f_status_t f_cellss_append_all(const f_cellss_t source, f_cellss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_cellss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {

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
  f_status_t f_cellss_decimate_by(const f_array_length_t amount, f_cellss_t *cellss) {
    #ifndef _di_level_0_parameter_checking_
      if (!cellss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (cellss->size - amount > 0) {
      return private_f_cellss_adjust(cellss->size - amount, cellss);
    }

    return private_f_cellss_adjust(0, cellss);
  }
#endif // _di_f_cellss_decimate_by_

#ifndef _di_f_cellss_decrease_by_
  f_status_t f_cellss_decrease_by(const f_array_length_t amount, f_cellss_t *cellss) {
    #ifndef _di_level_0_parameter_checking_
      if (!cellss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (cellss->size - amount > 0) {
      return private_f_cellss_resize(cellss->size - amount, cellss);
    }

    return private_f_cellss_resize(0, cellss);
  }
#endif // _di_f_cellss_decrease_by_

#ifndef _di_f_cellss_increase_
  f_status_t f_cellss_increase(const f_array_length_t step, f_cellss_t *cellss) {
    #ifndef _di_level_0_parameter_checking_
      if (!cellss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && cellss->used + 1 > cellss->size) {
      f_array_length_t size = cellss->used + step;

      if (size > F_array_length_t_size_d) {
        if (cellss->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_cellss_resize(size, cellss);
    }

    return F_data_not;
  }
#endif // _di_f_cellss_increase_

#ifndef _di_f_cellss_increase_by_
  f_status_t f_cellss_increase_by(const f_array_length_t amount, f_cellss_t *cellss) {
    #ifndef _di_level_0_parameter_checking_
      if (!cellss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) {
      return F_data_not;
    }

    if (cellss->used + amount > cellss->size) {
      if (cellss->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_cellss_resize(cellss->used + amount, cellss);
    }

    return F_data_not;
  }
#endif // _di_f_cellss_increase_by_

#ifndef _di_f_cellss_resize_
  f_status_t f_cellss_resize(const f_array_length_t length, f_cellss_t *cellss) {
    #ifndef _di_level_0_parameter_checking_
      if (!cellss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_cellss_resize(length, cellss);
  }
#endif // _di_f_cellss_resize_

#ifdef __cplusplus
} // extern "C"
#endif
