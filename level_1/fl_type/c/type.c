#include "type.h"
#include "private-type.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_type_cells_delete_
  f_status_t fl_type_cells_delete(f_cells_t *cells) {
    #ifndef _di_level_1_parameter_checking_
      if (!cells) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_cells_t_delete(status, (*cells));

    return status;
  }
#endif // _di_fl_type_cells_delete_

#ifndef _di_fl_type_cells_increase_
  f_status_t fl_type_cells_increase(f_cells_t *cells) {
    #ifndef _di_level_1_parameter_checking_
      if (!cells) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_cells_t_increase(status, (*cells));

    return status;
  }
#endif // _di_fl_type_cells_increase_

#ifndef _di_fl_type_cells_increase_by_
  f_status_t fl_type_cells_increase_by(const f_array_length_t amount, f_cells_t *cells) {
    #ifndef _di_level_1_parameter_checking_
      if (!cells) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_cells_t_increase_by(status, (*cells), amount);

    return status;
  }
#endif // _di_fl_type_cells_increase_by_

#ifndef _di_fl_type_cellss_delete_
  f_status_t fl_type_cellss_delete(f_cellss_t *cellss) {
    #ifndef _di_level_1_parameter_checking_
      if (!cellss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    private_fl_type_cellss_delete(cellss);

    return F_none;
  }
#endif // _di_fl_type_cellss_delete_

#ifndef _di_fl_type_cellss_increase_
  f_status_t fl_type_cellss_increase(f_cellss_t *cellss) {
    #ifndef _di_level_1_parameter_checking_
      if (!cellss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (cellss->used + 1 > cellss->size) {
      f_array_length_t size = cellss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (cellss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      private_fl_type_cellss_resize(size, cellss);
    }

    return F_none;
  }
#endif // _di_fl_type_cellss_increase_

#ifndef _di_fl_type_cellss_increase_by_
  f_status_t fl_type_cellss_increase_by(const f_array_length_t amount, f_cellss_t *cellss) {
    #ifndef _di_level_1_parameter_checking_
      if (!cellss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (cellss->used + amount > cellss->size) {
      if (cellss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      private_fl_type_cellss_resize(cellss->used + amount, cellss);
    }

    return F_none;
  }
#endif // _di_fl_type_cellss_increase_by_

#ifndef _di_fl_type_array_lengths_delete_
  f_status_t fl_type_array_lengths_delete(f_array_lengths_t *lengths) {
    #ifndef _di_level_1_parameter_checking_
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_array_lengths_t_delete(status, (*lengths));

    return status;
  }
#endif // _di_fl_type_array_lengths_delete_

#ifndef _di_fl_type_array_lengths_increase_
  f_status_t fl_type_array_lengths_increase(f_array_lengths_t *lengths) {
    #ifndef _di_level_1_parameter_checking_
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_array_lengths_t_increase(status, (*lengths));

    return status;
  }
#endif // _di_fl_type_array_lengths_increase_

#ifndef _di_fl_type_array_lengths_increase_by_
  f_status_t fl_type_array_lengths_increase_by(const f_array_length_t amount, f_array_lengths_t *lengths) {
    #ifndef _di_level_1_parameter_checking_
      if (!lengths) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_array_lengths_t_increase_by(status, (*lengths), amount);

    return status;
  }
#endif // _di_fl_type_array_lengths_increase_by_

#ifndef _di_fl_type_array_lengthss_delete_
  f_status_t fl_type_array_lengthss_delete(f_array_lengthss_t *lengthss) {
    #ifndef _di_level_1_parameter_checking_
      if (!lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    private_fl_type_array_lengthss_delete(lengthss);

    return F_none;
  }
#endif // _di_fl_type_array_lengthss_delete_

#ifndef _di_fl_type_array_lengthss_increase_
  f_status_t fl_type_array_lengthss_increase(f_array_lengthss_t *lengthss) {
    #ifndef _di_level_1_parameter_checking_
      if (!lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (lengthss->used + 1 > lengthss->size) {
      f_array_length_t size = lengthss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (lengthss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      private_fl_type_array_lengthss_resize(size, lengthss);
    }

    return F_none;
  }
#endif // _di_fl_type_array_lengthss_increase_

#ifndef _di_fl_type_array_lengthss_increase_by_
  f_status_t fl_type_array_lengthss_increase_by(const f_array_length_t amount, f_array_lengthss_t *lengthss) {
    #ifndef _di_level_1_parameter_checking_
      if (!lengthss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (lengthss->used + amount > lengthss->size) {
      if (lengthss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      private_fl_type_array_lengthss_resize(lengthss->used + amount, lengthss);
    }

    return F_none;
  }
#endif // _di_fl_type_array_lengthss_increase_by_

#ifndef _di_fl_type_int8s_delete_
  f_status_t fl_type_int8s_delete(f_int8s_t *int8s) {
    #ifndef _di_level_1_parameter_checking_
      if (!int8s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_int8s_t_delete(status, (*int8s));

    return status;
  }
#endif // _di_fl_type_int8s_delete_

#ifndef _di_fl_type_int8s_increase_
  f_status_t fl_type_int8s_increase(f_int8s_t *int8s) {
    #ifndef _di_level_1_parameter_checking_
      if (!int8s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_int8s_t_increase(status, (*int8s));

    return status;
  }
#endif // _di_fl_type_int8s_increase_

#ifndef _di_fl_type_int8s_increase_by_
  f_status_t fl_type_int8s_increase_by(const f_array_length_t amount, f_int8s_t *int8s) {
    #ifndef _di_level_1_parameter_checking_
      if (!int8s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_int8s_t_increase_by(status, (*int8s), amount);

    return status;
  }
#endif // _di_fl_type_int8s_increase_by_

#ifndef _di_fl_type_int8ss_delete_
  f_status_t fl_type_int8ss_delete(f_int8ss_t *int8ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!int8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    private_fl_type_int8ss_delete(int8ss);

    return F_none;
  }
#endif // _di_fl_type_int8ss_delete_

#ifndef _di_fl_type_int8ss_increase_
  f_status_t fl_type_int8ss_increase(f_int8ss_t *int8ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!int8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (int8ss->used + 1 > int8ss->size) {
      f_array_length_t size = int8ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int8ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      private_fl_type_int8ss_resize(size, int8ss);
    }

    return F_none;
  }
#endif // _di_fl_type_int8ss_increase_

#ifndef _di_fl_type_int8ss_increase_by_
  f_status_t fl_type_int8ss_increase_by(const f_array_length_t amount, f_int8ss_t *int8ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!int8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (int8ss->used + amount > int8ss->size) {
      if (int8ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      private_fl_type_int8ss_resize(int8ss->used + amount, int8ss);
    }

    return F_none;
  }
#endif // _di_fl_type_int8ss_increase_by_

#ifndef _di_fl_type_uint8s_delete_
  f_status_t fl_type_uint8s_delete(f_uint8s_t *uint8s) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint8s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_uint8s_t_delete(status, (*uint8s));

    return status;
  }
#endif // _di_fl_type_uint8s_delete_

#ifndef _di_fl_type_uint8s_increase_
  f_status_t fl_type_uint8s_increase(f_uint8s_t *uint8s) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint8s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_uint8s_t_increase(status, (*uint8s));

    return status;
  }
#endif // _di_fl_type_uint8s_increase_

#ifndef _di_fl_type_uint8s_increase_by_
  f_status_t fl_type_uint8s_increase_by(const f_array_length_t amount, f_uint8s_t *uint8s) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint8s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_uint8s_t_increase_by(status, (*uint8s), amount);

    return status;
  }
#endif // _di_fl_type_uint8s_increase_by_

#ifndef _di_fl_type_uint8ss_delete_
  f_status_t fl_type_uint8ss_delete(f_uint8ss_t *uint8ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    private_fl_type_uint8ss_delete(uint8ss);

    return F_none;
  }
#endif // _di_fl_type_uint8ss_delete_

#ifndef _di_fl_type_uint8ss_increase_
  f_status_t fl_type_uint8ss_increase(f_uint8ss_t *uint8ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (uint8ss->used + 1 > uint8ss->size) {
      f_array_length_t size = uint8ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint8ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      private_fl_type_uint8ss_resize(size, uint8ss);
    }

    return F_none;
  }
#endif // _di_fl_type_uint8ss_increase_

#ifndef _di_fl_type_uint8ss_increase_by_
  f_status_t fl_type_uint8ss_increase_by(const f_array_length_t amount, f_uint8ss_t *uint8ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint8ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (uint8ss->used + amount > uint8ss->size) {
      if (uint8ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      private_fl_type_uint8ss_resize(uint8ss->used + amount, uint8ss);
    }

    return F_none;
  }
#endif // _di_fl_type_uint8ss_increase_by_

#ifndef _di_fl_type_int16s_delete_
  f_status_t fl_type_int16s_delete(f_int16s_t *int16s) {
    #ifndef _di_level_1_parameter_checking_
      if (!int16s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_int16s_t_delete(status, (*int16s));

    return status;
  }
#endif // _di_fl_type_int16s_delete_

#ifndef _di_fl_type_int16s_increase_
  f_status_t fl_type_int16s_increase(f_int16s_t *int16s) {
    #ifndef _di_level_1_parameter_checking_
      if (!int16s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_int16s_t_increase(status, (*int16s));

    return status;
  }
#endif // _di_fl_type_int16s_increase_

#ifndef _di_fl_type_int16s_increase_by_
  f_status_t fl_type_int16s_increase_by(const f_array_length_t amount, f_int16s_t *int16s) {
    #ifndef _di_level_1_parameter_checking_
      if (!int16s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_int16s_t_increase_by(status, (*int16s), amount);

    return status;
  }
#endif // _di_fl_type_int16s_increase_by_

#ifndef _di_fl_type_int16ss_delete_
  f_status_t fl_type_int16ss_delete(f_int16ss_t *int16ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!int16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    private_fl_type_int16ss_delete(int16ss);

    return F_none;
  }
#endif // _di_fl_type_int16ss_delete_

#ifndef _di_fl_type_int16ss_increase_
  f_status_t fl_type_int16ss_increase(f_int16ss_t *int16ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!int16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (int16ss->used + 1 > int16ss->size) {
      f_array_length_t size = int16ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int16ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      private_fl_type_int16ss_resize(size, int16ss);
    }

    return F_none;
  }
#endif // _di_fl_type_int16ss_increase_

#ifndef _di_fl_type_int16ss_increase_by_
  f_status_t fl_type_int16ss_increase_by(const f_array_length_t amount, f_int16ss_t *int16ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!int16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (int16ss->used + amount > int16ss->size) {
      if (int16ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      private_fl_type_int16ss_resize(int16ss->used + amount, int16ss);
    }

    return F_none;
  }
#endif // _di_fl_type_int16ss_increase_by_

#ifndef _di_fl_type_uint16s_delete_
  f_status_t fl_type_uint16s_delete(f_uint16s_t *uint16s) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint16s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_uint16s_t_delete(status, (*uint16s));

    return status;
  }
#endif // _di_fl_type_uint16s_delete_

#ifndef _di_fl_type_uint16s_increase_
  f_status_t fl_type_uint16s_increase(f_uint16s_t *uint16s) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint16s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_uint16s_t_increase(status, (*uint16s));

    return status;
  }
#endif // _di_fl_type_uint16s_increase_

#ifndef _di_fl_type_uint16s_increase_by_
  f_status_t fl_type_uint16s_increase_by(const f_array_length_t amount, f_uint16s_t *uint16s) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint16s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_uint16s_t_increase_by(status, (*uint16s), amount);

    return status;
  }
#endif // _di_fl_type_uint16s_increase_by_

#ifndef _di_fl_type_uint16ss_delete_
  f_status_t fl_type_uint16ss_delete(f_uint16ss_t *uint16ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    private_fl_type_uint16ss_delete(uint16ss);

    return F_none;
  }
#endif // _di_fl_type_uint16ss_delete_

#ifndef _di_fl_type_uint16ss_increase_
  f_status_t fl_type_uint16ss_increase(f_uint16ss_t *uint16ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (uint16ss->used + 1 > uint16ss->size) {
      f_array_length_t size = uint16ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint16ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      private_fl_type_uint16ss_resize(size, uint16ss);
    }

    return F_none;
  }
#endif // _di_fl_type_uint16ss_increase_

#ifndef _di_fl_type_uint16ss_increase_by_
  f_status_t fl_type_uint16ss_increase_by(const f_array_length_t amount, f_uint16ss_t *uint16ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint16ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (uint16ss->used + amount > uint16ss->size) {
      if (uint16ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      private_fl_type_uint16ss_resize(uint16ss->used + amount, uint16ss);
    }

    return F_none;
  }
#endif // _di_fl_type_uint16ss_increase_by_

#ifndef _di_fl_type_int32s_delete_
  f_status_t fl_type_int32s_delete(f_int32s_t *int32s) {
    #ifndef _di_level_1_parameter_checking_
      if (!int32s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_int32s_t_delete(status, (*int32s));

    return status;
  }
#endif // _di_fl_type_int32s_delete_

#ifndef _di_fl_type_int32s_increase_
  f_status_t fl_type_int32s_increase(f_int32s_t *int32s) {
    #ifndef _di_level_1_parameter_checking_
      if (!int32s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_int32s_t_increase(status, (*int32s));

    return status;
  }
#endif // _di_fl_type_int32s_increase_

#ifndef _di_fl_type_int32s_increase_by_
  f_status_t fl_type_int32s_increase_by(const f_array_length_t amount, f_int32s_t *int32s) {
    #ifndef _di_level_1_parameter_checking_
      if (!int32s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_int32s_t_increase_by(status, (*int32s), amount);

    return status;
  }
#endif // _di_fl_type_int32s_increase_by_

#ifndef _di_fl_type_int32ss_delete_
  f_status_t fl_type_int32ss_delete(f_int32ss_t *int32ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!int32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    private_fl_type_int32ss_delete(int32ss);

    return F_none;
  }
#endif // _di_fl_type_int32ss_delete_

#ifndef _di_fl_type_int32ss_increase_
  f_status_t fl_type_int32ss_increase(f_int32ss_t *int32ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!int32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (int32ss->used + 1 > int32ss->size) {
      f_array_length_t size = int32ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int32ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      private_fl_type_int32ss_resize(size, int32ss);
    }

    return F_none;
  }
#endif // _di_fl_type_int32ss_increase_

#ifndef _di_fl_type_int32ss_increase_by_
  f_status_t fl_type_int32ss_increase_by(const f_array_length_t amount, f_int32ss_t *int32ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!int32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (int32ss->used + amount > int32ss->size) {
      if (int32ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      private_fl_type_int32ss_resize(int32ss->used + amount, int32ss);
    }

    return F_none;
  }
#endif // _di_fl_type_int32ss_increase_by_

#ifndef _di_fl_type_uint32s_delete_
  f_status_t fl_type_uint32s_delete(f_uint32s_t *uint32s) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint32s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_uint32s_t_delete(status, (*uint32s));

    return status;
  }
#endif // _di_fl_type_uint32s_delete_

#ifndef _di_fl_type_uint32s_increase_
  f_status_t fl_type_uint32s_increase(f_uint32s_t *uint32s) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint32s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_uint32s_t_increase(status, (*uint32s));

    return status;
  }
#endif // _di_fl_type_uint32s_increase_

#ifndef _di_fl_type_uint32s_increase_by_
  f_status_t fl_type_uint32s_increase_by(const f_array_length_t amount, f_uint32s_t *uint32s) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint32s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_uint32s_t_increase_by(status, (*uint32s), amount);

    return status;
  }
#endif // _di_fl_type_uint32s_increase_by_

#ifndef _di_fl_type_uint32ss_delete_
  f_status_t fl_type_uint32ss_delete(f_uint32ss_t *uint32ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    private_fl_type_uint32ss_delete(uint32ss);

    return F_none;
  }
#endif // _di_fl_type_uint32ss_delete_

#ifndef _di_fl_type_uint32ss_increase_
  f_status_t fl_type_uint32ss_increase(f_uint32ss_t *uint32ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (uint32ss->used + 1 > uint32ss->size) {
      f_array_length_t size = uint32ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint32ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      private_fl_type_uint32ss_resize(size, uint32ss);
    }

    return F_none;
  }
#endif // _di_fl_type_uint32ss_increase_

#ifndef _di_fl_type_uint32ss_increase_by_
  f_status_t fl_type_uint32ss_increase_by(const f_array_length_t amount, f_uint32ss_t *uint32ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint32ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (uint32ss->used + amount > uint32ss->size) {
      if (uint32ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      private_fl_type_uint32ss_resize(uint32ss->used + amount, uint32ss);
    }

    return F_none;
  }
#endif // _di_fl_type_uint32ss_increase_by_

#ifndef _di_fl_type_int64s_delete_
  f_status_t fl_type_int64s_delete(f_int64s_t *int64s) {
    #ifndef _di_level_1_parameter_checking_
      if (!int64s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_int64s_t_delete(status, (*int64s));

    return status;
  }
#endif // _di_fl_type_int64s_delete_

#ifndef _di_fl_int64s_increase_
  f_status_t fl_int64s_increase(f_int64s_t *int64s) {
    #ifndef _di_level_1_parameter_checking_
      if (!int64s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_int64s_t_increase(status, (*int64s));

    return status;
  }
#endif // _di_fl_int64s_increase_

#ifndef _di_fl_int64s_increase_by_
  f_status_t fl_int64s_increase_by(const f_array_length_t amount, f_int64s_t *int64s) {
    #ifndef _di_level_1_parameter_checking_
      if (!int64s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_int64s_t_increase_by(status, (*int64s), amount);

    return status;
  }
#endif // _di_fl_int64s_increase_by_

#ifndef _di_fl_type_int64ss_delete_
  f_status_t fl_type_int64ss_delete(f_int64ss_t *int64ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!int64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    private_fl_type_int64ss_delete(int64ss);

    return F_none;
  }
#endif // _di_fl_type_int64ss_delete_

#ifndef _di_fl_int64ss_increase_
  f_status_t fl_int64ss_increase(f_int64ss_t *int64ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!int64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (int64ss->used + 1 > int64ss->size) {
      f_array_length_t size = int64ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int64ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      private_fl_type_int64ss_resize(size, int64ss);
    }

    return F_none;
  }
#endif // _di_fl_int64ss_increase_

#ifndef _di_fl_int64ss_increase_by_
  f_status_t fl_int64ss_increase_by(const f_array_length_t amount, f_int64ss_t *int64ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!int64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (int64ss->used + amount > int64ss->size) {
      if (int64ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      private_fl_type_int64ss_resize(int64ss->used + amount, int64ss);
    }

    return F_none;
  }
#endif // _di_fl_int64ss_increase_by_

#ifndef _di_fl_type_uint64s_delete_
  f_status_t fl_type_uint64s_delete(f_uint64s_t *uint64s) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint64s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_uint64s_t_delete(status, (*uint64s));

    return status;
  }
#endif // _di_fl_type_uint64s_delete_

#ifndef _di_fl_uint64s_increase_
  f_status_t fl_uint64s_increase(f_uint64s_t *uint64s) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint64s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_uint64s_t_increase(status, (*uint64s));

    return status;
  }
#endif // _di_fl_uint64s_increase_

#ifndef _di_fl_uint64s_increase_by_
  f_status_t fl_uint64s_increase_by(const f_array_length_t amount, f_uint64s_t *uint64s) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint64s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_uint64s_t_increase_by(status, (*uint64s), amount);

    return status;
  }
#endif // _di_fl_uint64s_increase_by_

#ifndef _di_fl_type_uint64ss_delete_
  f_status_t fl_type_uint64ss_delete(f_uint64ss_t *uint64ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    private_fl_type_uint64ss_delete(uint64ss);

    return F_none;
  }
#endif // _di_fl_type_uint64ss_delete_

#ifndef _di_fl_uint64ss_increase_
  f_status_t fl_uint64ss_increase(f_uint64ss_t *uint64ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (uint64ss->used + 1 > uint64ss->size) {
      f_array_length_t size = uint64ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint64ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      private_fl_type_uint64ss_resize(size, uint64ss);
    }

    return F_none;
  }
#endif // _di_fl_uint64ss_increase_

#ifndef _di_fl_uint64ss_increase_by_
  f_status_t fl_uint64ss_increase_by(const f_array_length_t amount, f_uint64ss_t *uint64ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint64ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (uint64ss->used + amount > uint64ss->size) {
      if (uint64ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      private_fl_type_uint64ss_resize(uint64ss->used + amount, uint64ss);
    }

    return F_none;
  }
#endif // _di_fl_uint64ss_increase_by_

#ifndef _di_fl_type_int128s_delete_
  f_status_t fl_type_int128s_delete(f_int128s_t *int128s) {
    #ifndef _di_level_1_parameter_checking_
      if (!int128s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_int128s_t_delete(status, (*int128s));

    return status;
  }
#endif // _di_fl_type_int128s_delete_

#ifndef _di_fl_type_int128s_increase_
  f_status_t fl_type_int128s_increase(f_int128s_t *int128s) {
    #ifndef _di_level_1_parameter_checking_
      if (!int128s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_int128s_t_increase(status, (*int128s));

    return status;
  }
#endif // _di_fl_type_int128s_increase_

#ifndef _di_fl_type_int128s_increase_by_
  f_status_t fl_type_int128s_increase_by(const f_array_length_t amount, f_int128s_t *int128s) {
    #ifndef _di_level_1_parameter_checking_
      if (!int128s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_int128s_t_increase_by(status, (*int128s), amount);

    return status;
  }
#endif // _di_fl_type_int128s_increase_by_

#ifndef _di_fl_type_int128ss_delete_
  f_status_t fl_type_int128ss_delete(f_int128ss_t *int128ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!int128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    private_fl_type_int128ss_delete(int128ss);

    return F_none;
  }
#endif // _di_fl_type_int128ss_delete_

#ifndef _di_fl_type_int128ss_increase_
  f_status_t fl_type_int128ss_increase(f_int128ss_t *int128ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!int128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (int128ss->used + 1 > int128ss->size) {
      f_array_length_t size = int128ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int128ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      private_fl_type_int128ss_resize(size, int128ss);
    }

    return F_none;
  }
#endif // _di_fl_type_int128ss_increase_

#ifndef _di_fl_type_int128ss_increase_by_
  f_status_t fl_type_int128ss_increase_by(const f_array_length_t amount, f_int128ss_t *int128ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!int128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (int128ss->used + amount > int128ss->size) {
      if (int128ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      private_fl_type_int128ss_resize(int128ss->used + amount, int128ss);
    }

    return F_none;
  }
#endif // _di_fl_type_int128ss_increase_by_

#ifndef _di_fl_type_uint128s_delete_
  f_status_t fl_type_uint128s_delete(f_uint128s_t *uint128s) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint128s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_uint128s_t_delete(status, (*uint128s));

    return status;
  }
#endif // _di_fl_type_uint128s_delete_

#ifndef _di_fl_type_uint128s_increase_
  f_status_t fl_type_uint128s_increase(f_uint128s_t *uint128s) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint128s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_uint128s_t_increase(status, (*uint128s));

    return status;
  }
#endif // _di_fl_type_uint128s_increase_

#ifndef _di_fl_type_uint128s_increase_by_
  f_status_t fl_type_uint128s_increase_by(const f_array_length_t amount, f_uint128s_t *uint128s) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint128s) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    f_macro_uint128s_t_increase_by(status, (*uint128s), amount);

    return status;
  }
#endif // _di_fl_type_uint128s_increase_by_

#ifndef _di_fl_type_uint128ss_delete_
  f_status_t fl_type_uint128ss_delete(f_uint128ss_t *uint128ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    private_fl_type_uint128ss_delete(uint128ss);

    return F_none;
  }
#endif // _di_fl_type_uint128ss_delete_

#ifndef _di_fl_type_uint128ss_increase_
  f_status_t fl_type_uint128ss_increase(f_uint128ss_t *uint128ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (uint128ss->used + 1 > uint128ss->size) {
      f_array_length_t size = uint128ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint128ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      private_fl_type_uint128ss_resize(size, uint128ss);
    }

    return F_none;
  }
#endif // _di_fl_type_uint128ss_increase_

#ifndef _di_fl_type_uint128ss_increase_by_
  f_status_t fl_type_uint128ss_increase_by(const f_array_length_t amount, f_uint128ss_t *uint128ss) {
    #ifndef _di_level_1_parameter_checking_
      if (!uint128ss) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (uint128ss->used + amount > uint128ss->size) {
      if (uint128ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      private_fl_type_uint128ss_resize(uint128ss->used + amount, uint128ss);
    }

    return F_none;
  }
#endif // _di_fl_type_uint128ss_increase_by_

#ifdef __cplusplus
} // extern "C"
#endif
