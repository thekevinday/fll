#include "type_array.h"
#include "private-type_array.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_type_cellss_adjust_
  f_status_t f_type_cellss_adjust(const f_array_length_t length, f_cellss_t *cellss) {
    #ifndef _di_level_0_parameter_checking_
      if (!cellss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_cellss_adjust(length, cellss);
  }
#endif // _di_f_type_cellss_adjust_

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

#ifndef _di_f_type_array_lengthssss_adjust_
  f_status_t f_type_array_lengthssss_adjust(const f_array_length_t length, f_array_lengthss_t *array_lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!array_lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_array_lengthss_adjust(length, array_lengthss);
  }
#endif // _di_f_type_array_lengthss_adjust_

#ifndef _di_f_type_array_lengthss_decimate_by_
  f_status_t f_type_array_lengthss_decimate_by(const f_array_length_t amount, f_array_lengthss_t *array_lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!array_lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (array_lengthss->size - amount > 0) {
      return private_f_type_array_lengthss_adjust(array_lengthss->size - amount, array_lengthss);
    }

    return private_f_type_array_lengthss_adjust(0, array_lengthss);
  }
#endif // _di_f_type_array_lengthss_decimate_by_

#ifndef _di_f_type_array_lengthss_decrease_by_
  f_status_t f_type_array_lengthss_decrease_by(const f_array_length_t amount, f_array_lengthss_t *array_lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!array_lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (array_lengthss->size - amount > 0) {
      return private_f_type_array_lengthss_resize(array_lengthss->size - amount, array_lengthss);
    }

    return private_f_type_array_lengthss_resize(0, array_lengthss);
  }
#endif // _di_f_type_array_lengthss_decrease_by_

#ifndef _di_f_type_array_lengthss_increase_
  f_status_t f_type_array_lengthss_increase(f_array_lengthss_t *array_lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!array_lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (array_lengthss->used + 1 > array_lengthss->size) {
      f_array_length_t size = array_lengthss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (array_lengthss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_type_array_lengthss_resize(size, array_lengthss);
    }

    return F_data_not;
  }
#endif // _di_f_type_array_lengthss_increase_

#ifndef _di_f_type_array_lengthss_increase_by_
  f_status_t f_type_array_lengthss_increase_by(const f_array_length_t amount, f_array_lengthss_t *array_lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!array_lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (array_lengthss->used + amount > array_lengthss->size) {
      if (array_lengthss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_type_array_lengthss_resize(array_lengthss->used + amount, array_lengthss);
    }

    return F_data_not;
  }
#endif // _di_f_type_array_lengthss_increase_by_

#ifndef _di_f_type_array_lengthss_resize_
  f_status_t f_type_array_lengthss_resize(const f_array_length_t length, f_array_lengthss_t *array_lengthss) {
    #ifndef _di_level_0_parameter_checking_
      if (!array_lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_array_lengthss_resize(length, array_lengthss);
  }
#endif // _di_f_type_array_lengthss_resize_

#ifndef _di_f_type_int8ss_adjust_
  f_status_t f_type_int8ss_adjust(const f_array_length_t length, f_int8ss_t *int8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int8ss_adjust(length, int8ss);
  }
#endif // _di_f_type_int8ss_adjust_

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

#ifndef _di_f_type_uint8ss_adjust_
  f_status_t f_type_uint8ss_adjust(const f_array_length_t length, f_uint8ss_t *uint8ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint8ss_adjust(length, uint8ss);
  }
#endif // _di_f_type_uint8ss_adjust_

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

#ifndef _di_f_type_int16ss_adjust_
  f_status_t f_type_int16ss_adjust(const f_array_length_t length, f_int16ss_t *int16ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int16ss_adjust(length, int16ss);
  }
#endif // _di_f_type_int16ss_adjust_

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

#ifndef _di_f_type_int32ss_adjust_
  f_status_t f_type_int32ss_adjust(const f_array_length_t length, f_int32ss_t *int32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int32ss_adjust(length, int32ss);
  }
#endif // _di_f_type_int32ss_adjust_

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

#ifndef _di_f_type_uint32ss_adjust_
  f_status_t f_type_uint32ss_adjust(const f_array_length_t length, f_uint32ss_t *uint32ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint32ss_adjust(length, uint32ss);
  }
#endif // _di_f_type_uint32ss_adjust_

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

#ifndef _di_f_type_int64ss_adjust_
  f_status_t f_type_int64ss_adjust(const f_array_length_t length, f_int64ss_t *int64ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int64ss_adjust(length, int64ss);
  }
#endif // _di_f_type_int64ss_adjust_

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

#ifndef _di_f_type_uint64ss_adjust_
  f_status_t f_type_uint64ss_adjust(const f_array_length_t length, f_uint64ss_t *uint64ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint64ss_adjust(length, uint64ss);
  }
#endif // _di_f_type_uint64ss_adjust_

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

#ifndef _di_f_type_int128ss_adjust_
  f_status_t f_type_int128ss_adjust(const f_array_length_t length, f_int128ss_t *int128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!int128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_int128ss_adjust(length, int128ss);
  }
#endif // _di_f_type_int128ss_adjust_

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

#ifndef _di_f_type_uint128ss_adjust_
  f_status_t f_type_uint128ss_adjust(const f_array_length_t length, f_uint128ss_t *uint128ss) {
    #ifndef _di_level_0_parameter_checking_
      if (!uint128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_type_uint128ss_adjust(length, uint128ss);
  }
#endif // _di_f_type_uint128ss_adjust_

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
