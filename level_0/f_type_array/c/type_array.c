#include "type_array.h"
#include "private-type_array.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef _di_f_type_cells_adjust_
  f_status_t f_type_cells_adjust(const f_array_length_t length, f_cells_t *cells) {
    #ifndef _di_level_0_parameter_checking_
      if (!cells) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_cells_adjust(length, cells);
  }
#endif // _di_f_type_cells_adjust_

#ifndef _di_f_type_cells_append_
  f_status_t f_type_cells_append(const f_cells_t source, f_cells_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_cells_append(source, destination);
  }
#endif // _di_f_type_cells_append_

#ifndef _di_f_type_cells_decimate_by_
  f_status_t f_type_cells_decimate_by(const f_array_length_t amount, f_cells_t *cells) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!cells) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (cells->size - amount > 0) {
      return private_f_type_cells_adjust(cells->size - amount, cells);
    }

    return private_f_type_cells_adjust(0, cells);
  }
#endif // _di_f_type_cells_decimate_by_

#ifndef _di_f_type_cells_decrease_by_
  f_status_t f_type_cells_decrease_by(const f_array_length_t amount, f_cells_t *cells) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!cells) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (cells->size - amount > 0) {
      return private_f_type_cells_resize(cells->size - amount, cells);
    }

    return private_f_type_cells_resize(0, cells);
  }
#endif // _di_f_type_cells_decrease_by_

#ifndef _di_f_type_cells_increase_
  f_status_t f_type_cells_increase(f_cells_t *cells) {
    #ifndef _di_level_0_parameter_checking_
      if (!cells) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (cells->used + 1 > cells->size) {
      f_array_length_t size = cells->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (cells->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_cells_resize(size, cells);
    }

    return F_data_not;
  }
#endif // _di_f_type_cells_increase_

#ifndef _di_f_type_cells_increase_by_
  f_status_t f_type_cells_increase_by(const f_array_length_t amount, f_cells_t *cells) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!cells) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (cells->used + amount > cells->size) {
      if (cells->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_cells_resize(cells->used + amount, cells);
    }

    return F_data_not;
  }
#endif // _di_f_type_cells_increase_by_

#ifndef _di_f_type_cells_resize_
  f_status_t f_type_cells_resize(const f_array_length_t length, f_cells_t *cells) {
    #ifndef _di_level_0_parameter_checking_
      if (!cells) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_cells_resize(length, cells);
  }
#endif // _di_f_type_cells_resize_

#ifndef _di_f_type_cellss_adjust_
  f_status_t f_type_cellss_adjust(const f_array_length_t length, f_cellss_t *cellss) {
    #ifndef _di_level_0_parameter_checking_
      if (!cellss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_cellss_adjust(length, cellss);
  }
#endif // _di_f_type_cellss_adjust_

#ifndef _di_f_type_cellss_append_
  f_status_t f_type_cellss_append(const f_cellss_t source, f_cellss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_cellss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      status = private_f_type_cells_append(source.array[i], &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    } // for

    return F_none;
  }
#endif // _di_f_type_cellss_append_

#ifndef _di_f_type_cellss_decimate_by_
  f_status_t f_type_cellss_decimate_by(const f_array_length_t amount, f_cellss_t *cellss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!cellss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (cellss->size - amount > 0) {
      return private_f_type_cellss_adjust(cellss->size - amount, cellss);
    }

    return private_f_type_cellss_adjust(0, cellss);
  }
#endif // _di_f_type_cellss_decimate_by_

#ifndef _di_f_type_cellss_decrease_by_
  f_status_t f_type_cellss_decrease_by(const f_array_length_t amount, f_cellss_t *cellss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!cellss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (cellss->size - amount > 0) {
      return private_f_type_cellss_resize(cellss->size - amount, cellss);
    }

    return private_f_type_cellss_resize(0, cellss);
  }
#endif // _di_f_type_cellss_decrease_by_

#ifndef _di_f_type_cellss_increase_
  f_status_t f_type_cellss_increase(f_cellss_t *cellss) {
    #ifndef _di_level_0_parameter_checking_
      if (!cellss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (cellss->used + 1 > cellss->size) {
      f_array_length_t size = cellss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (cellss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_cellss_resize(size, cellss);
    }

    return F_data_not;
  }
#endif // _di_f_type_cellss_increase_

#ifndef _di_f_type_cellss_increase_by_
  f_status_t f_type_cellss_increase_by(const f_array_length_t amount, f_cellss_t *cellss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!cellss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (cellss->used + amount > cellss->size) {
      if (cellss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_cellss_resize(cellss->used + amount, cellss);
    }

    return F_data_not;
  }
#endif // _di_f_type_cellss_increase_by_

#ifndef _di_f_type_cellss_resize_
  f_status_t f_type_cellss_resize(const f_array_length_t length, f_cellss_t *cellss) {
    #ifndef _di_level_0_parameter_checking_
      if (!cellss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_cellss_resize(length, cellss);
  }
#endif // _di_f_type_cellss_resize_

#ifndef _di_f_type_array_lengths_adjust_
  f_status_t f_type_array_lengths_adjust(const f_array_length_t length, f_array_lengths_t *lengths) {
    #ifndef _di_level_0_parameter_checking_
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_array_lengths_adjust(length, lengths);
  }
#endif // _di_f_type_array_lengths_adjust_

#ifndef _di_f_type_array_lengths_append_
  f_status_t f_type_array_lengths_append(const f_array_lengths_t source, f_array_lengths_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_array_lengths_append(source, destination);
  }
#endif // _di_f_type_array_lengths_append_

#ifndef _di_f_type_array_lengths_decimate_by_
  f_status_t f_type_array_lengths_decimate_by(const f_array_length_t amount, f_array_lengths_t *lengths) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (lengths->size - amount > 0) {
      return private_f_type_array_lengths_adjust(lengths->size - amount, lengths);
    }

    return private_f_type_array_lengths_adjust(0, lengths);
  }
#endif // _di_f_type_array_lengths_decimate_by_

#ifndef _di_f_type_array_lengths_decrease_by_
  f_status_t f_type_array_lengths_decrease_by(const f_array_length_t amount, f_array_lengths_t *lengths) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (lengths->size - amount > 0) {
      return private_f_type_array_lengths_resize(lengths->size - amount, lengths);
    }

    return private_f_type_array_lengths_resize(0, lengths);
  }
#endif // _di_f_type_array_lengths_decrease_by_

#ifndef _di_f_type_array_lengths_increase_
  f_status_t f_type_array_lengths_increase(f_array_lengths_t *lengths) {
    #ifndef _di_level_0_parameter_checking_
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (lengths->used + 1 > lengths->size) {
      f_array_length_t size = lengths->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (lengths->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_array_lengths_resize(size, lengths);
    }

    return F_data_not;
  }
#endif // _di_f_type_array_lengths_increase_

#ifndef _di_f_type_array_lengths_increase_by_
  f_status_t f_type_array_lengths_increase_by(const f_array_length_t amount, f_array_lengths_t *lengths) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (lengths->used + amount > lengths->size) {
      if (lengths->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_array_lengths_resize(lengths->used + amount, lengths);
    }

    return F_data_not;
  }
#endif // _di_f_type_array_lengths_increase_by_

#ifndef _di_f_type_array_lengths_resize_
  f_status_t f_type_array_lengths_resize(const f_array_length_t length, f_array_lengths_t *lengths) {
    #ifndef _di_level_0_parameter_checking_
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_array_lengths_resize(length, lengths);
  }
#endif // _di_f_type_array_lengths_resize_

#ifndef _di_f_type_array_lengthss_adjust_
  f_status_t f_type_array_lengthss_adjust(const f_array_length_t length, f_array_lengthss_t *lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_array_lengthss_adjust(length, lengthss);
  }
#endif // _di_f_type_array_lengthss_adjust_

#ifndef _di_f_type_array_lengthss_append_
  f_status_t f_type_array_lengthss_append(const f_array_lengthss_t source, f_array_lengthss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_array_lengthss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      status = private_f_type_array_lengths_append(source.array[i], &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    } // for

    return F_none;
  }
#endif // _di_f_type_array_lengthss_append_

#ifndef _di_f_type_array_lengthss_decimate_by_
  f_status_t f_type_array_lengthss_decimate_by(const f_array_length_t amount, f_array_lengthss_t *lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (lengthss->size - amount > 0) {
      return private_f_type_array_lengthss_adjust(lengthss->size - amount, lengthss);
    }

    return private_f_type_array_lengthss_adjust(0, lengthss);
  }
#endif // _di_f_type_array_lengthss_decimate_by_

#ifndef _di_f_type_array_lengthss_decrease_by_
  f_status_t f_type_array_lengthss_decrease_by(const f_array_length_t amount, f_array_lengthss_t *lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (lengthss->size - amount > 0) {
      return private_f_type_array_lengthss_resize(lengthss->size - amount, lengthss);
    }

    return private_f_type_array_lengthss_resize(0, lengthss);
  }
#endif // _di_f_type_array_lengthss_decrease_by_

#ifndef _di_f_type_array_lengthss_increase_
  f_status_t f_type_array_lengthss_increase(f_array_lengthss_t *lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (lengthss->used + 1 > lengthss->size) {
      f_array_length_t size = lengthss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (lengthss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_array_lengthss_resize(size, lengthss);
    }

    return F_data_not;
  }
#endif // _di_f_type_array_lengthss_increase_

#ifndef _di_f_type_array_lengthss_increase_by_
  f_status_t f_type_array_lengthss_increase_by(const f_array_length_t amount, f_array_lengthss_t *lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (lengthss->used + amount > lengthss->size) {
      if (lengthss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_array_lengthss_resize(lengthss->used + amount, lengthss);
    }

    return F_data_not;
  }
#endif // _di_f_type_array_lengthss_increase_by_

#ifndef _di_f_type_array_lengthss_resize_
  f_status_t f_type_array_lengthss_resize(const f_array_length_t length, f_array_lengthss_t *lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_array_lengthss_resize(length, lengthss);
  }
#endif // _di_f_type_array_lengthss_resize_

#ifndef _di_f_type_int8s_adjust_
  f_status_t f_type_int8s_adjust(const f_array_length_t length, f_int8s_t *int8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int8s_adjust(length, int8s);
  }
#endif // _di_f_type_int8s_adjust_

#ifndef _di_f_type_int8s_append_
  f_status_t f_type_int8s_append(const f_int8s_t source, f_int8s_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int8s_append(source, destination);
  }
#endif // _di_f_type_int8s_append_

#ifndef _di_f_type_int8s_decimate_by_
  f_status_t f_type_int8s_decimate_by(const f_array_length_t amount, f_int8s_t *int8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int8s->size - amount > 0) {
      return private_f_type_int8s_adjust(int8s->size - amount, int8s);
    }

    return private_f_type_int8s_adjust(0, int8s);
  }
#endif // _di_f_type_int8s_decimate_by_

#ifndef _di_f_type_int8s_decrease_by_
  f_status_t f_type_int8s_decrease_by(const f_array_length_t amount, f_int8s_t *int8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int8s->size - amount > 0) {
      return private_f_type_int8s_resize(int8s->size - amount, int8s);
    }

    return private_f_type_int8s_resize(0, int8s);
  }
#endif // _di_f_type_int8s_decrease_by_

#ifndef _di_f_type_int8s_increase_
  f_status_t f_type_int8s_increase(f_int8s_t *int8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int8s->used + 1 > int8s->size) {
      f_array_length_t size = int8s->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int8s->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_int8s_resize(size, int8s);
    }

    return F_data_not;
  }
#endif // _di_f_type_int8s_increase_

#ifndef _di_f_type_int8s_increase_by_
  f_status_t f_type_int8s_increase_by(const f_array_length_t amount, f_int8s_t *int8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int8s->used + amount > int8s->size) {
      if (int8s->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_int8s_resize(int8s->used + amount, int8s);
    }

    return F_data_not;
  }
#endif // _di_f_type_int8s_increase_by_

#ifndef _di_f_type_int8s_resize_
  f_status_t f_type_int8s_resize(const f_array_length_t length, f_int8s_t *int8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int8s_resize(length, int8s);
  }
#endif // _di_f_type_int8s_resize_

#ifndef _di_f_type_int8ss_adjust_
  f_status_t f_type_int8ss_adjust(const f_array_length_t length, f_int8ss_t *int8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int8ss_adjust(length, int8ss);
  }
#endif // _di_f_type_int8ss_adjust_

#ifndef _di_f_type_int8ss_append_
  f_status_t f_type_int8ss_append(const f_int8ss_t source, f_int8ss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_int8ss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      status = private_f_type_int8s_append(source.array[i], &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    } // for

    return F_none;
  }
#endif // _di_f_type_int8ss_append_

#ifndef _di_f_type_int8ss_decimate_by_
  f_status_t f_type_int8ss_decimate_by(const f_array_length_t amount, f_int8ss_t *int8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int8ss->size - amount > 0) {
      return private_f_type_int8ss_adjust(int8ss->size - amount, int8ss);
    }

    return private_f_type_int8ss_adjust(0, int8ss);
  }
#endif // _di_f_type_int8ss_decimate_by_

#ifndef _di_f_type_int8ss_decrease_by_
  f_status_t f_type_int8ss_decrease_by(const f_array_length_t amount, f_int8ss_t *int8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int8ss->size - amount > 0) {
      return private_f_type_int8ss_resize(int8ss->size - amount, int8ss);
    }

    return private_f_type_int8ss_resize(0, int8ss);
  }
#endif // _di_f_type_int8ss_decrease_by_

#ifndef _di_f_type_int8ss_increase_
  f_status_t f_type_int8ss_increase(f_int8ss_t *int8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int8ss->used + 1 > int8ss->size) {
      f_array_length_t size = int8ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int8ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_int8ss_resize(size, int8ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_int8ss_increase_

#ifndef _di_f_type_int8ss_increase_by_
  f_status_t f_type_int8ss_increase_by(const f_array_length_t amount, f_int8ss_t *int8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int8ss->used + amount > int8ss->size) {
      if (int8ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_int8ss_resize(int8ss->used + amount, int8ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_int8ss_increase_by_

#ifndef _di_f_type_int8ss_resize_
  f_status_t f_type_int8ss_resize(const f_array_length_t length, f_int8ss_t *int8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int8ss_resize(length, int8ss);
  }
#endif // _di_f_type_int8ss_resize_

#ifndef _di_f_type_uint8s_adjust_
  f_status_t f_type_uint8s_adjust(const f_array_length_t length, f_uint8s_t *uint8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint8s_adjust(length, uint8s);
  }
#endif // _di_f_type_uint8s_adjust_

#ifndef _di_f_type_uint8s_append_
  f_status_t f_type_uint8s_append(const f_uint8s_t source, f_uint8s_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint8s_append(source, destination);
  }
#endif // _di_f_type_uint8s_append_

#ifndef _di_f_type_uint8s_decimate_by_
  f_status_t f_type_uint8s_decimate_by(const f_array_length_t amount, f_uint8s_t *uint8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint8s->size - amount > 0) {
      return private_f_type_uint8s_adjust(uint8s->size - amount, uint8s);
    }

    return private_f_type_uint8s_adjust(0, uint8s);
  }
#endif // _di_f_type_uint8s_decimate_by_

#ifndef _di_f_type_uint8s_decrease_by_
  f_status_t f_type_uint8s_decrease_by(const f_array_length_t amount, f_uint8s_t *uint8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint8s->size - amount > 0) {
      return private_f_type_uint8s_resize(uint8s->size - amount, uint8s);
    }

    return private_f_type_uint8s_resize(0, uint8s);
  }
#endif // _di_f_type_uint8s_decrease_by_

#ifndef _di_f_type_uint8s_increase_
  f_status_t f_type_uint8s_increase(f_uint8s_t *uint8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint8s->used + 1 > uint8s->size) {
      f_array_length_t size = uint8s->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint8s->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_uint8s_resize(size, uint8s);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint8s_increase_

#ifndef _di_f_type_uint8s_increase_by_
  f_status_t f_type_uint8s_increase_by(const f_array_length_t amount, f_uint8s_t *uint8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint8s->used + amount > uint8s->size) {
      if (uint8s->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_uint8s_resize(uint8s->used + amount, uint8s);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint8s_increase_by_

#ifndef _di_f_type_uint8s_resize_
  f_status_t f_type_uint8s_resize(const f_array_length_t length, f_uint8s_t *uint8s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint8s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint8s_resize(length, uint8s);
  }
#endif // _di_f_type_uint8s_resize_

#ifndef _di_f_type_uint8ss_adjust_
  f_status_t f_type_uint8ss_adjust(const f_array_length_t length, f_uint8ss_t *uint8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint8ss_adjust(length, uint8ss);
  }
#endif // _di_f_type_uint8ss_adjust_

#ifndef _di_f_type_uint8ss_append_
  f_status_t f_type_uint8ss_append(const f_uint8ss_t source, f_uint8ss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_uint8ss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      status = private_f_type_uint8s_append(source.array[i], &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    } // for

    return F_none;
  }
#endif // _di_f_type_uint8ss_append_

#ifndef _di_f_type_uint8ss_decimate_by_
  f_status_t f_type_uint8ss_decimate_by(const f_array_length_t amount, f_uint8ss_t *uint8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint8ss->size - amount > 0) {
      return private_f_type_uint8ss_adjust(uint8ss->size - amount, uint8ss);
    }

    return private_f_type_uint8ss_adjust(0, uint8ss);
  }
#endif // _di_f_type_uint8ss_decimate_by_

#ifndef _di_f_type_uint8ss_decrease_by_
  f_status_t f_type_uint8ss_decrease_by(const f_array_length_t amount, f_uint8ss_t *uint8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint8ss->size - amount > 0) {
      return private_f_type_uint8ss_resize(uint8ss->size - amount, uint8ss);
    }

    return private_f_type_uint8ss_resize(0, uint8ss);
  }
#endif // _di_f_type_uint8ss_decrease_by_

#ifndef _di_f_type_uint8ss_increase_
  f_status_t f_type_uint8ss_increase(f_uint8ss_t *uint8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint8ss->used + 1 > uint8ss->size) {
      f_array_length_t size = uint8ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint8ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_uint8ss_resize(size, uint8ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint8ss_increase_

#ifndef _di_f_type_uint8ss_increase_by_
  f_status_t f_type_uint8ss_increase_by(const f_array_length_t amount, f_uint8ss_t *uint8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint8ss->used + amount > uint8ss->size) {
      if (uint8ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_uint8ss_resize(uint8ss->used + amount, uint8ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint8ss_increase_by_

#ifndef _di_f_type_uint8ss_resize_
  f_status_t f_type_uint8ss_resize(const f_array_length_t length, f_uint8ss_t *uint8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint8ss_resize(length, uint8ss);
  }
#endif // _di_f_type_uint8ss_resize_

#ifndef _di_f_type_int16s_adjust_
  f_status_t f_type_int16s_adjust(const f_array_length_t length, f_int16s_t *int16s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int16s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int16s_adjust(length, int16s);
  }
#endif // _di_f_type_int16s_adjust_

#ifndef _di_f_type_int16s_append_
  f_status_t f_type_int16s_append(const f_int16s_t source, f_int16s_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int16s_append(source, destination);
  }
#endif // _di_f_type_int16s_append_

#ifndef _di_f_type_int16s_decimate_by_
  f_status_t f_type_int16s_decimate_by(const f_array_length_t amount, f_int16s_t *int16s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int16s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int16s->size - amount > 0) {
      return private_f_type_int16s_adjust(int16s->size - amount, int16s);
    }

    return private_f_type_int16s_adjust(0, int16s);
  }
#endif // _di_f_type_int16s_decimate_by_

#ifndef _di_f_type_int16s_decrease_by_
  f_status_t f_type_int16s_decrease_by(const f_array_length_t amount, f_int16s_t *int16s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int16s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int16s->size - amount > 0) {
      return private_f_type_int16s_resize(int16s->size - amount, int16s);
    }

    return private_f_type_int16s_resize(0, int16s);
  }
#endif // _di_f_type_int16s_decrease_by_

#ifndef _di_f_type_int16s_increase_
  f_status_t f_type_int16s_increase(f_int16s_t *int16s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int16s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int16s->used + 1 > int16s->size) {
      f_array_length_t size = int16s->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int16s->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_int16s_resize(size, int16s);
    }

    return F_data_not;
  }
#endif // _di_f_type_int16s_increase_

#ifndef _di_f_type_int16s_increase_by_
  f_status_t f_type_int16s_increase_by(const f_array_length_t amount, f_int16s_t *int16s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int16s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int16s->used + amount > int16s->size) {
      if (int16s->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_int16s_resize(int16s->used + amount, int16s);
    }

    return F_data_not;
  }
#endif // _di_f_type_int16s_increase_by_

#ifndef _di_f_type_int16s_resize_
  f_status_t f_type_int16s_resize(const f_array_length_t length, f_int16s_t *int16s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int16s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int16s_resize(length, int16s);
  }
#endif // _di_f_type_int16s_resize_

#ifndef _di_f_type_int16ss_adjust_
  f_status_t f_type_int16ss_adjust(const f_array_length_t length, f_int16ss_t *int16ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int16ss_adjust(length, int16ss);
  }
#endif // _di_f_type_int16ss_adjust_

#ifndef _di_f_type_int16ss_append_
  f_status_t f_type_int16ss_append(const f_int16ss_t source, f_int16ss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_int16ss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      status = private_f_type_int16s_append(source.array[i], &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    } // for

    return F_none;
  }
#endif // _di_f_type_int16ss_append_

#ifndef _di_f_type_int16ss_decimate_by_
  f_status_t f_type_int16ss_decimate_by(const f_array_length_t amount, f_int16ss_t *int16ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int16ss->size - amount > 0) {
      return private_f_type_int16ss_adjust(int16ss->size - amount, int16ss);
    }

    return private_f_type_int16ss_adjust(0, int16ss);
  }
#endif // _di_f_type_int16ss_decimate_by_

#ifndef _di_f_type_int16ss_decrease_by_
  f_status_t f_type_int16ss_decrease_by(const f_array_length_t amount, f_int16ss_t *int16ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int16ss->size - amount > 0) {
      return private_f_type_int16ss_resize(int16ss->size - amount, int16ss);
    }

    return private_f_type_int16ss_resize(0, int16ss);
  }
#endif // _di_f_type_int16ss_decrease_by_

#ifndef _di_f_type_int16ss_increase_
  f_status_t f_type_int16ss_increase(f_int16ss_t *int16ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int16ss->used + 1 > int16ss->size) {
      f_array_length_t size = int16ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int16ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_int16ss_resize(size, int16ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_int16ss_increase_

#ifndef _di_f_type_int16ss_increase_by_
  f_status_t f_type_int16ss_increase_by(const f_array_length_t amount, f_int16ss_t *int16ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int16ss->used + amount > int16ss->size) {
      if (int16ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_int16ss_resize(int16ss->used + amount, int16ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_int16ss_increase_by_

#ifndef _di_f_type_int16ss_resize_
  f_status_t f_type_int16ss_resize(const f_array_length_t length, f_int16ss_t *int16ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int16ss_resize(length, int16ss);
  }
#endif // _di_f_type_int16ss_resize_

#ifndef _di_f_type_uint16s_adjust_
  f_status_t f_type_uint16s_adjust(const f_array_length_t length, f_uint16s_t *uint16s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint16s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint16s_adjust(length, uint16s);
  }
#endif // _di_f_type_uint16s_adjust_

#ifndef _di_f_type_uint16s_append_
  f_status_t f_type_uint16s_append(const f_uint16s_t source, f_uint16s_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint16s_append(source, destination);
  }
#endif // _di_f_type_uint16s_append_

#ifndef _di_f_type_uint16s_decimate_by_
  f_status_t f_type_uint16s_decimate_by(const f_array_length_t amount, f_uint16s_t *uint16s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint16s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint16s->size - amount > 0) {
      return private_f_type_uint16s_adjust(uint16s->size - amount, uint16s);
    }

    return private_f_type_uint16s_adjust(0, uint16s);
  }
#endif // _di_f_type_uint16s_decimate_by_

#ifndef _di_f_type_uint16s_decrease_by_
  f_status_t f_type_uint16s_decrease_by(const f_array_length_t amount, f_uint16s_t *uint16s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint16s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint16s->size - amount > 0) {
      return private_f_type_uint16s_resize(uint16s->size - amount, uint16s);
    }

    return private_f_type_uint16s_resize(0, uint16s);
  }
#endif // _di_f_type_uint16s_decrease_by_

#ifndef _di_f_type_uint16s_increase_
  f_status_t f_type_uint16s_increase(f_uint16s_t *uint16s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint16s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint16s->used + 1 > uint16s->size) {
      f_array_length_t size = uint16s->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint16s->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_uint16s_resize(size, uint16s);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint16s_increase_

#ifndef _di_f_type_uint16s_increase_by_
  f_status_t f_type_uint16s_increase_by(const f_array_length_t amount, f_uint16s_t *uint16s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint16s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint16s->used + amount > uint16s->size) {
      if (uint16s->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_uint16s_resize(uint16s->used + amount, uint16s);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint16s_increase_by_

#ifndef _di_f_type_uint16s_resize_
  f_status_t f_type_uint16s_resize(const f_array_length_t length, f_uint16s_t *uint16s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint16s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint16s_resize(length, uint16s);
  }
#endif // _di_f_type_uint16s_resize_

#ifndef _di_f_type_uint16ss_adjust_
  f_status_t f_type_uint16ss_adjust(const f_array_length_t length, f_uint16ss_t *uint16ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint16ss_adjust(length, uint16ss);
  }
#endif // _di_f_type_uint16ss_adjust_

#ifndef _di_f_type_uint16ss_append_
  f_status_t f_type_uint16ss_append(const f_uint16ss_t source, f_uint16ss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_uint16ss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      status = private_f_type_uint16s_append(source.array[i], &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    } // for

    return F_none;
  }
#endif // _di_f_type_uint16ss_append_

#ifndef _di_f_type_uint16ss_decimate_by_
  f_status_t f_type_uint16ss_decimate_by(const f_array_length_t amount, f_uint16ss_t *uint16ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint16ss->size - amount > 0) {
      return private_f_type_uint16ss_adjust(uint16ss->size - amount, uint16ss);
    }

    return private_f_type_uint16ss_adjust(0, uint16ss);
  }
#endif // _di_f_type_uint16ss_decimate_by_

#ifndef _di_f_type_uint16ss_decrease_by_
  f_status_t f_type_uint16ss_decrease_by(const f_array_length_t amount, f_uint16ss_t *uint16ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint16ss->size - amount > 0) {
      return private_f_type_uint16ss_resize(uint16ss->size - amount, uint16ss);
    }

    return private_f_type_uint16ss_resize(0, uint16ss);
  }
#endif // _di_f_type_uint16ss_decrease_by_

#ifndef _di_f_type_uint16ss_increase_
  f_status_t f_type_uint16ss_increase(f_uint16ss_t *uint16ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint16ss->used + 1 > uint16ss->size) {
      f_array_length_t size = uint16ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint16ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_uint16ss_resize(size, uint16ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint16ss_increase_

#ifndef _di_f_type_uint16ss_increase_by_
  f_status_t f_type_uint16ss_increase_by(const f_array_length_t amount, f_uint16ss_t *uint16ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint16ss->used + amount > uint16ss->size) {
      if (uint16ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_uint16ss_resize(uint16ss->used + amount, uint16ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint16ss_increase_by_

#ifndef _di_f_type_uint16ss_resize_
  f_status_t f_type_uint16ss_resize(const f_array_length_t length, f_uint16ss_t *uint16ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint16ss_resize(length, uint16ss);
  }
#endif // _di_f_type_uint16ss_resize_

#ifndef _di_f_type_int32s_adjust_
  f_status_t f_type_int32s_adjust(const f_array_length_t length, f_int32s_t *int32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int32s_adjust(length, int32s);
  }
#endif // _di_f_type_int32s_adjust_

#ifndef _di_f_type_int32s_append_
  f_status_t f_type_int32s_append(const f_int32s_t source, f_int32s_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int32s_append(source, destination);
  }
#endif // _di_f_type_int32s_append_

#ifndef _di_f_type_int32s_decimate_by_
  f_status_t f_type_int32s_decimate_by(const f_array_length_t amount, f_int32s_t *int32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int32s->size - amount > 0) {
      return private_f_type_int32s_adjust(int32s->size - amount, int32s);
    }

    return private_f_type_int32s_adjust(0, int32s);
  }
#endif // _di_f_type_int32s_decimate_by_

#ifndef _di_f_type_int32s_decrease_by_
  f_status_t f_type_int32s_decrease_by(const f_array_length_t amount, f_int32s_t *int32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int32s->size - amount > 0) {
      return private_f_type_int32s_resize(int32s->size - amount, int32s);
    }

    return private_f_type_int32s_resize(0, int32s);
  }
#endif // _di_f_type_int32s_decrease_by_

#ifndef _di_f_type_int32s_increase_
  f_status_t f_type_int32s_increase(f_int32s_t *int32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int32s->used + 1 > int32s->size) {
      f_array_length_t size = int32s->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int32s->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_int32s_resize(size, int32s);
    }

    return F_data_not;
  }
#endif // _di_f_type_int32s_increase_

#ifndef _di_f_type_int32s_increase_by_
  f_status_t f_type_int32s_increase_by(const f_array_length_t amount, f_int32s_t *int32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int32s->used + amount > int32s->size) {
      if (int32s->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_int32s_resize(int32s->used + amount, int32s);
    }

    return F_data_not;
  }
#endif // _di_f_type_int32s_increase_by_

#ifndef _di_f_type_int32s_resize_
  f_status_t f_type_int32s_resize(const f_array_length_t length, f_int32s_t *int32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int32s_resize(length, int32s);
  }
#endif // _di_f_type_int32s_resize_

#ifndef _di_f_type_int32ss_adjust_
  f_status_t f_type_int32ss_adjust(const f_array_length_t length, f_int32ss_t *int32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int32ss_adjust(length, int32ss);
  }
#endif // _di_f_type_int32ss_adjust_

#ifndef _di_f_type_int32ss_append_
  f_status_t f_type_int32ss_append(const f_int32ss_t source, f_int32ss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_int32ss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      status = private_f_type_int32s_append(source.array[i], &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    } // for

    return F_none;
  }
#endif // _di_f_type_int32ss_append_

#ifndef _di_f_type_int32ss_decimate_by_
  f_status_t f_type_int32ss_decimate_by(const f_array_length_t amount, f_int32ss_t *int32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int32ss->size - amount > 0) {
      return private_f_type_int32ss_adjust(int32ss->size - amount, int32ss);
    }

    return private_f_type_int32ss_adjust(0, int32ss);
  }
#endif // _di_f_type_int32ss_decimate_by_

#ifndef _di_f_type_int32ss_decrease_by_
  f_status_t f_type_int32ss_decrease_by(const f_array_length_t amount, f_int32ss_t *int32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int32ss->size - amount > 0) {
      return private_f_type_int32ss_resize(int32ss->size - amount, int32ss);
    }

    return private_f_type_int32ss_resize(0, int32ss);
  }
#endif // _di_f_type_int32ss_decrease_by_

#ifndef _di_f_type_int32ss_increase_
  f_status_t f_type_int32ss_increase(f_int32ss_t *int32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int32ss->used + 1 > int32ss->size) {
      f_array_length_t size = int32ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int32ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_int32ss_resize(size, int32ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_int32ss_increase_

#ifndef _di_f_type_int32ss_increase_by_
  f_status_t f_type_int32ss_increase_by(const f_array_length_t amount, f_int32ss_t *int32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int32ss->used + amount > int32ss->size) {
      if (int32ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_int32ss_resize(int32ss->used + amount, int32ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_int32ss_increase_by_

#ifndef _di_f_type_int32ss_resize_
  f_status_t f_type_int32ss_resize(const f_array_length_t length, f_int32ss_t *int32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int32ss_resize(length, int32ss);
  }
#endif // _di_f_type_int32ss_resize_

#ifndef _di_f_type_uint32s_adjust_
  f_status_t f_type_uint32s_adjust(const f_array_length_t length, f_uint32s_t *uint32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint32s_adjust(length, uint32s);
  }
#endif // _di_f_type_uint32s_adjust_

#ifndef _di_f_type_uint32s_append_
  f_status_t f_type_uint32s_append(const f_uint32s_t source, f_uint32s_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint32s_append(source, destination);
  }
#endif // _di_f_type_uint32s_append_

#ifndef _di_f_type_uint32s_decimate_by_
  f_status_t f_type_uint32s_decimate_by(const f_array_length_t amount, f_uint32s_t *uint32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint32s->size - amount > 0) {
      return private_f_type_uint32s_adjust(uint32s->size - amount, uint32s);
    }

    return private_f_type_uint32s_adjust(0, uint32s);
  }
#endif // _di_f_type_uint32s_decimate_by_

#ifndef _di_f_type_uint32s_decrease_by_
  f_status_t f_type_uint32s_decrease_by(const f_array_length_t amount, f_uint32s_t *uint32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint32s->size - amount > 0) {
      return private_f_type_uint32s_resize(uint32s->size - amount, uint32s);
    }

    return private_f_type_uint32s_resize(0, uint32s);
  }
#endif // _di_f_type_uint32s_decrease_by_

#ifndef _di_f_type_uint32s_increase_
  f_status_t f_type_uint32s_increase(f_uint32s_t *uint32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint32s->used + 1 > uint32s->size) {
      f_array_length_t size = uint32s->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint32s->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_uint32s_resize(size, uint32s);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint32s_increase_

#ifndef _di_f_type_uint32s_increase_by_
  f_status_t f_type_uint32s_increase_by(const f_array_length_t amount, f_uint32s_t *uint32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint32s->used + amount > uint32s->size) {
      if (uint32s->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_uint32s_resize(uint32s->used + amount, uint32s);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint32s_increase_by_

#ifndef _di_f_type_uint32s_resize_
  f_status_t f_type_uint32s_resize(const f_array_length_t length, f_uint32s_t *uint32s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint32s_resize(length, uint32s);
  }
#endif // _di_f_type_uint32s_resize_

#ifndef _di_f_type_uint32ss_adjust_
  f_status_t f_type_uint32ss_adjust(const f_array_length_t length, f_uint32ss_t *uint32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint32ss_adjust(length, uint32ss);
  }
#endif // _di_f_type_uint32ss_adjust_

#ifndef _di_f_type_uint32ss_append_
  f_status_t f_type_uint32ss_append(const f_uint32ss_t source, f_uint32ss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_uint32ss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      status = private_f_type_uint32s_append(source.array[i], &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    } // for

    return F_none;
  }
#endif // _di_f_type_uint32ss_append_

#ifndef _di_f_type_uint32ss_decimate_by_
  f_status_t f_type_uint32ss_decimate_by(const f_array_length_t amount, f_uint32ss_t *uint32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint32ss->size - amount > 0) {
      return private_f_type_uint32ss_adjust(uint32ss->size - amount, uint32ss);
    }

    return private_f_type_uint32ss_adjust(0, uint32ss);
  }
#endif // _di_f_type_uint32ss_decimate_by_

#ifndef _di_f_type_uint32ss_decrease_by_
  f_status_t f_type_uint32ss_decrease_by(const f_array_length_t amount, f_uint32ss_t *uint32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint32ss->size - amount > 0) {
      return private_f_type_uint32ss_resize(uint32ss->size - amount, uint32ss);
    }

    return private_f_type_uint32ss_resize(0, uint32ss);
  }
#endif // _di_f_type_uint32ss_decrease_by_

#ifndef _di_f_type_uint32ss_increase_
  f_status_t f_type_uint32ss_increase(f_uint32ss_t *uint32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint32ss->used + 1 > uint32ss->size) {
      f_array_length_t size = uint32ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint32ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_uint32ss_resize(size, uint32ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint32ss_increase_

#ifndef _di_f_type_uint32ss_increase_by_
  f_status_t f_type_uint32ss_increase_by(const f_array_length_t amount, f_uint32ss_t *uint32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint32ss->used + amount > uint32ss->size) {
      if (uint32ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_uint32ss_resize(uint32ss->used + amount, uint32ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint32ss_increase_by_

#ifndef _di_f_type_uint32ss_resize_
  f_status_t f_type_uint32ss_resize(const f_array_length_t length, f_uint32ss_t *uint32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint32ss_resize(length, uint32ss);
  }
#endif // _di_f_type_uint32ss_resize_

#ifndef _di_f_type_int64s_adjust_
  f_status_t f_type_int64s_adjust(const f_array_length_t length, f_int64s_t *int64s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int64s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int64s_adjust(length, int64s);
  }
#endif // _di_f_type_int64s_adjust_

#ifndef _di_f_type_int64s_append_
  f_status_t f_type_int64s_append(const f_int64s_t source, f_int64s_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int64s_append(source, destination);
  }
#endif // _di_f_type_int64s_append_

#ifndef _di_f_type_int64s_decimate_by_
  f_status_t f_type_int64s_decimate_by(const f_array_length_t amount, f_int64s_t *int64s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int64s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int64s->size - amount > 0) {
      return private_f_type_int64s_adjust(int64s->size - amount, int64s);
    }

    return private_f_type_int64s_adjust(0, int64s);
  }
#endif // _di_f_type_int64s_decimate_by_

#ifndef _di_f_type_int64s_decrease_by_
  f_status_t f_type_int64s_decrease_by(const f_array_length_t amount, f_int64s_t *int64s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int64s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int64s->size - amount > 0) {
      return private_f_type_int64s_resize(int64s->size - amount, int64s);
    }

    return private_f_type_int64s_resize(0, int64s);
  }
#endif // _di_f_type_int64s_decrease_by_

#ifndef _di_f_type_int64s_increase_
  f_status_t f_type_int64s_increase(f_int64s_t *int64s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int64s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int64s->used + 1 > int64s->size) {
      f_array_length_t size = int64s->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int64s->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_int64s_resize(size, int64s);
    }

    return F_data_not;
  }
#endif // _di_f_type_int64s_increase_

#ifndef _di_f_type_int64s_increase_by_
  f_status_t f_type_int64s_increase_by(const f_array_length_t amount, f_int64s_t *int64s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int64s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int64s->used + amount > int64s->size) {
      if (int64s->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_int64s_resize(int64s->used + amount, int64s);
    }

    return F_data_not;
  }
#endif // _di_f_type_int64s_increase_by_

#ifndef _di_f_type_int64s_resize_
  f_status_t f_type_int64s_resize(const f_array_length_t length, f_int64s_t *int64s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int64s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int64s_resize(length, int64s);
  }
#endif // _di_f_type_int64s_resize_

#ifndef _di_f_type_int64ss_adjust_
  f_status_t f_type_int64ss_adjust(const f_array_length_t length, f_int64ss_t *int64ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int64ss_adjust(length, int64ss);
  }
#endif // _di_f_type_int64ss_adjust_

#ifndef _di_f_type_int64ss_append_
  f_status_t f_type_int64ss_append(const f_int64ss_t source, f_int64ss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_int64ss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      status = private_f_type_int64s_append(source.array[i], &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    } // for

    return F_none;
  }
#endif // _di_f_type_int64ss_append_

#ifndef _di_f_type_int64ss_decimate_by_
  f_status_t f_type_int64ss_decimate_by(const f_array_length_t amount, f_int64ss_t *int64ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int64ss->size - amount > 0) {
      return private_f_type_int64ss_adjust(int64ss->size - amount, int64ss);
    }

    return private_f_type_int64ss_adjust(0, int64ss);
  }
#endif // _di_f_type_int64ss_decimate_by_

#ifndef _di_f_type_int64ss_decrease_by_
  f_status_t f_type_int64ss_decrease_by(const f_array_length_t amount, f_int64ss_t *int64ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int64ss->size - amount > 0) {
      return private_f_type_int64ss_resize(int64ss->size - amount, int64ss);
    }

    return private_f_type_int64ss_resize(0, int64ss);
  }
#endif // _di_f_type_int64ss_decrease_by_

#ifndef _di_f_type_int64ss_increase_
  f_status_t f_type_int64ss_increase(f_int64ss_t *int64ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int64ss->used + 1 > int64ss->size) {
      f_array_length_t size = int64ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int64ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_int64ss_resize(size, int64ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_int64ss_increase_

#ifndef _di_f_type_int64ss_increase_by_
  f_status_t f_type_int64ss_increase_by(const f_array_length_t amount, f_int64ss_t *int64ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int64ss->used + amount > int64ss->size) {
      if (int64ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_int64ss_resize(int64ss->used + amount, int64ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_int64ss_increase_by_

#ifndef _di_f_type_int64ss_resize_
  f_status_t f_type_int64ss_resize(const f_array_length_t length, f_int64ss_t *int64ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int64ss_resize(length, int64ss);
  }
#endif // _di_f_type_int64ss_resize_

#ifndef _di_f_type_uint64s_adjust_
  f_status_t f_type_uint64s_adjust(const f_array_length_t length, f_uint64s_t *uint64s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint64s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint64s_adjust(length, uint64s);
  }
#endif // _di_f_type_uint64s_adjust_

#ifndef _di_f_type_uint64s_append_
  f_status_t f_type_uint64s_append(const f_uint64s_t source, f_uint64s_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint64s_append(source, destination);
  }
#endif // _di_f_type_uint64s_append_

#ifndef _di_f_type_uint64s_decimate_by_
  f_status_t f_type_uint64s_decimate_by(const f_array_length_t amount, f_uint64s_t *uint64s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint64s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint64s->size - amount > 0) {
      return private_f_type_uint64s_adjust(uint64s->size - amount, uint64s);
    }

    return private_f_type_uint64s_adjust(0, uint64s);
  }
#endif // _di_f_type_uint64s_decimate_by_

#ifndef _di_f_type_uint64s_decrease_by_
  f_status_t f_type_uint64s_decrease_by(const f_array_length_t amount, f_uint64s_t *uint64s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint64s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint64s->size - amount > 0) {
      return private_f_type_uint64s_resize(uint64s->size - amount, uint64s);
    }

    return private_f_type_uint64s_resize(0, uint64s);
  }
#endif // _di_f_type_uint64s_decrease_by_

#ifndef _di_f_type_uint64s_increase_
  f_status_t f_type_uint64s_increase(f_uint64s_t *uint64s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint64s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint64s->used + 1 > uint64s->size) {
      f_array_length_t size = uint64s->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint64s->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_uint64s_resize(size, uint64s);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint64s_increase_

#ifndef _di_f_type_uint64s_increase_by_
  f_status_t f_type_uint64s_increase_by(const f_array_length_t amount, f_uint64s_t *uint64s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint64s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint64s->used + amount > uint64s->size) {
      if (uint64s->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_uint64s_resize(uint64s->used + amount, uint64s);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint64s_increase_by_

#ifndef _di_f_type_uint64s_resize_
  f_status_t f_type_uint64s_resize(const f_array_length_t length, f_uint64s_t *uint64s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint64s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint64s_resize(length, uint64s);
  }
#endif // _di_f_type_uint64s_resize_

#ifndef _di_f_type_uint64ss_adjust_
  f_status_t f_type_uint64ss_adjust(const f_array_length_t length, f_uint64ss_t *uint64ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint64ss_adjust(length, uint64ss);
  }
#endif // _di_f_type_uint64ss_adjust_

#ifndef _di_f_type_uint64ss_append_
  f_status_t f_type_uint64ss_append(const f_uint64ss_t source, f_uint64ss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_uint64ss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      status = private_f_type_uint64s_append(source.array[i], &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    } // for

    return F_none;
  }
#endif // _di_f_type_uint64ss_append_

#ifndef _di_f_type_uint64ss_decimate_by_
  f_status_t f_type_uint64ss_decimate_by(const f_array_length_t amount, f_uint64ss_t *uint64ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint64ss->size - amount > 0) {
      return private_f_type_uint64ss_adjust(uint64ss->size - amount, uint64ss);
    }

    return private_f_type_uint64ss_adjust(0, uint64ss);
  }
#endif // _di_f_type_uint64ss_decimate_by_

#ifndef _di_f_type_uint64ss_decrease_by_
  f_status_t f_type_uint64ss_decrease_by(const f_array_length_t amount, f_uint64ss_t *uint64ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint64ss->size - amount > 0) {
      return private_f_type_uint64ss_resize(uint64ss->size - amount, uint64ss);
    }

    return private_f_type_uint64ss_resize(0, uint64ss);
  }
#endif // _di_f_type_uint64ss_decrease_by_

#ifndef _di_f_type_uint64ss_increase_
  f_status_t f_type_uint64ss_increase(f_uint64ss_t *uint64ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint64ss->used + 1 > uint64ss->size) {
      f_array_length_t size = uint64ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint64ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_uint64ss_resize(size, uint64ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint64ss_increase_

#ifndef _di_f_type_uint64ss_increase_by_
  f_status_t f_type_uint64ss_increase_by(const f_array_length_t amount, f_uint64ss_t *uint64ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint64ss->used + amount > uint64ss->size) {
      if (uint64ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_uint64ss_resize(uint64ss->used + amount, uint64ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint64ss_increase_by_

#ifndef _di_f_type_uint64ss_resize_
  f_status_t f_type_uint64ss_resize(const f_array_length_t length, f_uint64ss_t *uint64ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint64ss_resize(length, uint64ss);
  }
#endif // _di_f_type_uint64ss_resize_

#ifndef _di_f_type_int128s_adjust_
  f_status_t f_type_int128s_adjust(const f_array_length_t length, f_int128s_t *int128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int128s_adjust(length, int128s);
  }
#endif // _di_f_type_int128s_adjust_

#ifndef _di_f_type_int128s_append_
  f_status_t f_type_int128s_append(const f_int128s_t source, f_int128s_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int128s_append(source, destination);
  }
#endif // _di_f_type_int128s_append_

#ifndef _di_f_type_int128s_decimate_by_
  f_status_t f_type_int128s_decimate_by(const f_array_length_t amount, f_int128s_t *int128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int128s->size - amount > 0) {
      return private_f_type_int128s_adjust(int128s->size - amount, int128s);
    }

    return private_f_type_int128s_adjust(0, int128s);
  }
#endif // _di_f_type_int128s_decimate_by_

#ifndef _di_f_type_int128s_decrease_by_
  f_status_t f_type_int128s_decrease_by(const f_array_length_t amount, f_int128s_t *int128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int128s->size - amount > 0) {
      return private_f_type_int128s_resize(int128s->size - amount, int128s);
    }

    return private_f_type_int128s_resize(0, int128s);
  }
#endif // _di_f_type_int128s_decrease_by_

#ifndef _di_f_type_int128s_increase_
  f_status_t f_type_int128s_increase(f_int128s_t *int128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int128s->used + 1 > int128s->size) {
      f_array_length_t size = int128s->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int128s->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_int128s_resize(size, int128s);
    }

    return F_data_not;
  }
#endif // _di_f_type_int128s_increase_

#ifndef _di_f_type_int128s_increase_by_
  f_status_t f_type_int128s_increase_by(const f_array_length_t amount, f_int128s_t *int128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int128s->used + amount > int128s->size) {
      if (int128s->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_int128s_resize(int128s->used + amount, int128s);
    }

    return F_data_not;
  }
#endif // _di_f_type_int128s_increase_by_

#ifndef _di_f_type_int128s_resize_
  f_status_t f_type_int128s_resize(const f_array_length_t length, f_int128s_t *int128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!int128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int128s_resize(length, int128s);
  }
#endif // _di_f_type_int128s_resize_

#ifndef _di_f_type_int128ss_adjust_
  f_status_t f_type_int128ss_adjust(const f_array_length_t length, f_int128ss_t *int128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int128ss_adjust(length, int128ss);
  }
#endif // _di_f_type_int128ss_adjust_

#ifndef _di_f_type_int128ss_append_
  f_status_t f_type_int128ss_append(const f_int128ss_t source, f_int128ss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_int128ss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      status = private_f_type_int128s_append(source.array[i], &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    } // for

    return F_none;
  }
#endif // _di_f_type_int128ss_append_

#ifndef _di_f_type_int128ss_decimate_by_
  f_status_t f_type_int128ss_decimate_by(const f_array_length_t amount, f_int128ss_t *int128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int128ss->size - amount > 0) {
      return private_f_type_int128ss_adjust(int128ss->size - amount, int128ss);
    }

    return private_f_type_int128ss_adjust(0, int128ss);
  }
#endif // _di_f_type_int128ss_decimate_by_

#ifndef _di_f_type_int128ss_decrease_by_
  f_status_t f_type_int128ss_decrease_by(const f_array_length_t amount, f_int128ss_t *int128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int128ss->size - amount > 0) {
      return private_f_type_int128ss_resize(int128ss->size - amount, int128ss);
    }

    return private_f_type_int128ss_resize(0, int128ss);
  }
#endif // _di_f_type_int128ss_decrease_by_

#ifndef _di_f_type_int128ss_increase_
  f_status_t f_type_int128ss_increase(f_int128ss_t *int128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int128ss->used + 1 > int128ss->size) {
      f_array_length_t size = int128ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int128ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_int128ss_resize(size, int128ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_int128ss_increase_

#ifndef _di_f_type_int128ss_increase_by_
  f_status_t f_type_int128ss_increase_by(const f_array_length_t amount, f_int128ss_t *int128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!int128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (int128ss->used + amount > int128ss->size) {
      if (int128ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_int128ss_resize(int128ss->used + amount, int128ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_int128ss_increase_by_

#ifndef _di_f_type_int128ss_resize_
  f_status_t f_type_int128ss_resize(const f_array_length_t length, f_int128ss_t *int128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int128ss_resize(length, int128ss);
  }
#endif // _di_f_type_int128ss_resize_

#ifndef _di_f_type_uint128s_adjust_
  f_status_t f_type_uint128s_adjust(const f_array_length_t length, f_uint128s_t *uint128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint128s_adjust(length, uint128s);
  }
#endif // _di_f_type_uint128s_adjust_

#ifndef _di_f_type_uint128s_append_
  f_status_t f_type_uint128s_append(const f_uint128s_t source, f_uint128s_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint128s_append(source, destination);
  }
#endif // _di_f_type_uint128s_append_

#ifndef _di_f_type_uint128s_decimate_by_
  f_status_t f_type_uint128s_decimate_by(const f_array_length_t amount, f_uint128s_t *uint128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint128s->size - amount > 0) {
      return private_f_type_uint128s_adjust(uint128s->size - amount, uint128s);
    }

    return private_f_type_uint128s_adjust(0, uint128s);
  }
#endif // _di_f_type_uint128s_decimate_by_

#ifndef _di_f_type_uint128s_decrease_by_
  f_status_t f_type_uint128s_decrease_by(const f_array_length_t amount, f_uint128s_t *uint128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint128s->size - amount > 0) {
      return private_f_type_uint128s_resize(uint128s->size - amount, uint128s);
    }

    return private_f_type_uint128s_resize(0, uint128s);
  }
#endif // _di_f_type_uint128s_decrease_by_

#ifndef _di_f_type_uint128s_increase_
  f_status_t f_type_uint128s_increase(f_uint128s_t *uint128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint128s->used + 1 > uint128s->size) {
      f_array_length_t size = uint128s->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint128s->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_uint128s_resize(size, uint128s);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint128s_increase_

#ifndef _di_f_type_uint128s_increase_by_
  f_status_t f_type_uint128s_increase_by(const f_array_length_t amount, f_uint128s_t *uint128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint128s->used + amount > uint128s->size) {
      if (uint128s->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_uint128s_resize(uint128s->used + amount, uint128s);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint128s_increase_by_

#ifndef _di_f_type_uint128s_resize_
  f_status_t f_type_uint128s_resize(const f_array_length_t length, f_uint128s_t *uint128s) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint128s) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint128s_resize(length, uint128s);
  }
#endif // _di_f_type_uint128s_resize_

#ifndef _di_f_type_uint128ss_adjust_
  f_status_t f_type_uint128ss_adjust(const f_array_length_t length, f_uint128ss_t *uint128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint128ss_adjust(length, uint128ss);
  }
#endif // _di_f_type_uint128ss_adjust_

#ifndef _di_f_type_uint128ss_append_
  f_status_t f_type_uint128ss_append(const f_uint128ss_t source, f_uint128ss_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_uint128ss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      status = private_f_type_uint128s_append(source.array[i], &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    } // for

    return F_none;
  }
#endif // _di_f_type_uint128ss_append_

#ifndef _di_f_type_uint128ss_decimate_by_
  f_status_t f_type_uint128ss_decimate_by(const f_array_length_t amount, f_uint128ss_t *uint128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint128ss->size - amount > 0) {
      return private_f_type_uint128ss_adjust(uint128ss->size - amount, uint128ss);
    }

    return private_f_type_uint128ss_adjust(0, uint128ss);
  }
#endif // _di_f_type_uint128ss_decimate_by_

#ifndef _di_f_type_uint128ss_decrease_by_
  f_status_t f_type_uint128ss_decrease_by(const f_array_length_t amount, f_uint128ss_t *uint128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint128ss->size - amount > 0) {
      return private_f_type_uint128ss_resize(uint128ss->size - amount, uint128ss);
    }

    return private_f_type_uint128ss_resize(0, uint128ss);
  }
#endif // _di_f_type_uint128ss_decrease_by_

#ifndef _di_f_type_uint128ss_increase_
  f_status_t f_type_uint128ss_increase(f_uint128ss_t *uint128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint128ss->used + 1 > uint128ss->size) {
      f_array_length_t size = uint128ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint128ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_uint128ss_resize(size, uint128ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint128ss_increase_

#ifndef _di_f_type_uint128ss_increase_by_
  f_status_t f_type_uint128ss_increase_by(const f_array_length_t amount, f_uint128ss_t *uint128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!uint128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (uint128ss->used + amount > uint128ss->size) {
      if (uint128ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_uint128ss_resize(uint128ss->used + amount, uint128ss);
    }

    return F_data_not;
  }
#endif // _di_f_type_uint128ss_increase_by_

#ifndef _di_f_type_uint128ss_resize_
  f_status_t f_type_uint128ss_resize(const f_array_length_t length, f_uint128ss_t *uint128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint128ss_resize(length, uint128ss);
  }
#endif // _di_f_type_uint128ss_resize_

#ifdef __cplusplus
} // extern "C"
#endif
