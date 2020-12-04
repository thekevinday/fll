#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_cells_increase_
  f_return_status fl_cells_increase(f_cells_t *cells) {

    if (cells->used + 1 > cells->size) {
      f_array_length_t size = cells->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (cells->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_cells_t_resize(status, (*cells), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_cells_increase_

#ifndef _di_fl_cells_increase_by_
  f_return_status fl_cells_increase_by(const f_array_length_t amount, f_cells_t *cells) {

    if (cells->used + amount > cells->size) {
      if (cells->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_cells_t_resize(status, (*cells), cells->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_cells_increase_by_

#ifndef _di_fl_cellss_increase_
  f_return_status fl_cellss_increase(f_cellss_t *cellss) {

    if (cellss->used + 1 > cellss->size) {
      f_array_length_t size = cellss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (cellss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_cellss_t_resize(status, (*cellss), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_cellss_increase_

#ifndef _di_fl_cellss_increase_by_
  f_return_status fl_cellss_increase_by(const f_array_length_t amount, f_cellss_t *cellss) {

    if (cellss->used + amount > cellss->size) {
      if (cellss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_cellss_t_resize(status, (*cellss), cellss->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_cellss_increase_by_

#ifndef _di_fl_array_lengths_increase_
  f_return_status fl_array_lengths_increase(f_array_lengths_t *lengths) {

    if (lengths->used + 1 > lengths->size) {
      f_array_length_t size = lengths->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (lengths->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_array_lengths_t_resize(status, (*lengths), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_array_lengths_increase_

#ifndef _di_fl_array_lengths_increase_by_
  f_return_status fl_array_lengths_increase_by(const f_array_length_t amount, f_array_lengths_t *lengths) {

    if (lengths->used + amount > lengths->size) {
      if (lengths->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_array_lengths_t_resize(status, (*lengths), lengths->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_array_lengths_increase_by_

#ifndef _di_fl_array_lengthss_increase_
  f_return_status fl_array_lengthss_increase(f_array_lengthss_t *lengthss) {

    if (lengthss->used + 1 > lengthss->size) {
      f_array_length_t size = lengthss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (lengthss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_array_lengthss_t_resize(status, (*lengthss), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_array_lengthss_increase_

#ifndef _di_fl_array_lengthss_increase_by_
  f_return_status fl_array_lengthss_increase_by(const f_array_length_t amount, f_array_lengthss_t *lengthss) {

    if (lengthss->used + amount > lengthss->size) {
      if (lengthss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_array_lengthss_t_resize(status, (*lengthss), lengthss->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_array_lengthss_increase_by_

#ifndef _di_fl_int8s_increase_
  f_return_status fl_int8s_increase(f_int8s_t *int8s) {

    if (int8s->used + 1 > int8s->size) {
      f_array_length_t size = int8s->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int8s->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_int8s_t_resize(status, (*int8s), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_int8s_increase_

#ifndef _di_fl_int8s_increase_by_
  f_return_status fl_int8s_increase_by(const f_array_length_t amount, f_int8s_t *int8s) {

    if (int8s->used + amount > int8s->size) {
      if (int8s->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_int8s_t_resize(status, (*int8s), int8s->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_int8s_increase_by_

#ifndef _di_fl_int8ss_increase_
  f_return_status fl_int8ss_increase(f_int8ss_t *int8ss) {

    if (int8ss->used + 1 > int8ss->size) {
      f_array_length_t size = int8ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int8ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_int8ss_t_resize(status, (*int8ss), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_int8ss_increase_

#ifndef _di_fl_int8ss_increase_by_
  f_return_status fl_int8ss_increase_by(const f_array_length_t amount, f_int8ss_t *int8ss) {

    if (int8ss->used + amount > int8ss->size) {
      if (int8ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_int8ss_t_resize(status, (*int8ss), int8ss->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_int8ss_increase_by_

#ifndef _di_fl_uint8s_increase_
  f_return_status fl_uint8s_increase(f_uint8s_t *uint8s) {

    if (uint8s->used + 1 > uint8s->size) {
      f_array_length_t size = uint8s->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint8s->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_uint8s_t_resize(status, (*uint8s), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_uint8s_increase_

#ifndef _di_fl_uint8s_increase_by_
  f_return_status fl_uint8s_increase_by(const f_array_length_t amount, f_uint8s_t *uint8s) {

    if (uint8s->used + amount > uint8s->size) {
      if (uint8s->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_uint8s_t_resize(status, (*uint8s), uint8s->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_uint8s_increase_by_

#ifndef _di_fl_uint8ss_increase_
  f_return_status fl_uint8ss_increase(f_uint8ss_t *uint8ss) {

    if (uint8ss->used + 1 > uint8ss->size) {
      f_array_length_t size = uint8ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint8ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_uint8ss_t_resize(status, (*uint8ss), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_uint8ss_increase_

#ifndef _di_fl_uint8ss_increase_by_
  f_return_status fl_uint8ss_increase_by(const f_array_length_t amount, f_uint8ss_t *uint8ss) {

    if (uint8ss->used + amount > uint8ss->size) {
      if (uint8ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_uint8ss_t_resize(status, (*uint8ss), uint8ss->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_uint8ss_increase_by_

#ifndef _di_fl_int16s_increase_
  f_return_status fl_int16s_increase(f_int16s_t *int16s) {

    if (int16s->used + 1 > int16s->size) {
      f_array_length_t size = int16s->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int16s->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_int16s_t_resize(status, (*int16s), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_int16s_increase_

#ifndef _di_fl_int16s_increase_by_
  f_return_status fl_int16s_increase_by(const f_array_length_t amount, f_int16s_t *int16s) {

    if (int16s->used + amount > int16s->size) {
      if (int16s->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_int16s_t_resize(status, (*int16s), int16s->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_int16s_increase_by_

#ifndef _di_fl_int16ss_increase_
  f_return_status fl_int16ss_increase(f_int16ss_t *int16ss) {

    if (int16ss->used + 1 > int16ss->size) {
      f_array_length_t size = int16ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int16ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_int16ss_t_resize(status, (*int16ss), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_int16ss_increase_

#ifndef _di_fl_int16ss_increase_by_
  f_return_status fl_int16ss_increase_by(const f_array_length_t amount, f_int16ss_t *int16ss) {

    if (int16ss->used + amount > int16ss->size) {
      if (int16ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_int16ss_t_resize(status, (*int16ss), int16ss->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_int16ss_increase_by_

#ifndef _di_fl_uint16s_increase_
  f_return_status fl_uint16s_increase(f_uint16s_t *uint16s) {

    if (uint16s->used + 1 > uint16s->size) {
      f_array_length_t size = uint16s->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint16s->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_uint16s_t_resize(status, (*uint16s), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_uint16s_increase_

#ifndef _di_fl_uint16s_increase_by_
  f_return_status fl_uint16s_increase_by(const f_array_length_t amount, f_uint16s_t *uint16s) {

    if (uint16s->used + amount > uint16s->size) {
      if (uint16s->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_uint16s_t_resize(status, (*uint16s), uint16s->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_uint16s_increase_by_

#ifndef _di_fl_uint16ss_increase_
  f_return_status fl_uint16ss_increase(f_uint16ss_t *uint16ss) {

    if (uint16ss->used + 1 > uint16ss->size) {
      f_array_length_t size = uint16ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint16ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_uint16ss_t_resize(status, (*uint16ss), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_uint16ss_increase_

#ifndef _di_fl_uint16ss_increase_by_
  f_return_status fl_uint16ss_increase_by(const f_array_length_t amount, f_uint16ss_t *uint16ss) {

    if (uint16ss->used + amount > uint16ss->size) {
      if (uint16ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_uint16ss_t_resize(status, (*uint16ss), uint16ss->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_uint16ss_increase_by_

#ifndef _di_fl_int32s_increase_
  f_return_status fl_int32s_increase(f_int32s_t *int32s) {

    if (int32s->used + 1 > int32s->size) {
      f_array_length_t size = int32s->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int32s->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_int32s_t_resize(status, (*int32s), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_int32s_increase_

#ifndef _di_fl_int32s_increase_by_
  f_return_status fl_int32s_increase_by(const f_array_length_t amount, f_int32s_t *int32s) {

    if (int32s->used + amount > int32s->size) {
      if (int32s->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_int32s_t_resize(status, (*int32s), int32s->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_int32s_increase_by_

#ifndef _di_fl_int32ss_increase_
  f_return_status fl_int32ss_increase(f_int32ss_t *int32ss) {

    if (int32ss->used + 1 > int32ss->size) {
      f_array_length_t size = int32ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int32ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_int32ss_t_resize(status, (*int32ss), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_int32ss_increase_

#ifndef _di_fl_int32ss_increase_by_
  f_return_status fl_int32ss_increase_by(const f_array_length_t amount, f_int32ss_t *int32ss) {

    if (int32ss->used + amount > int32ss->size) {
      if (int32ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_int32ss_t_resize(status, (*int32ss), int32ss->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_int32ss_increase_by_

#ifndef _di_fl_uint32s_increase_
  f_return_status fl_uint32s_increase(f_uint32s_t *uint32s) {

    if (uint32s->used + 1 > uint32s->size) {
      f_array_length_t size = uint32s->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint32s->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_uint32s_t_resize(status, (*uint32s), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_uint32s_increase_

#ifndef _di_fl_uint32s_increase_by_
  f_return_status fl_uint32s_increase_by(const f_array_length_t amount, f_uint32s_t *uint32s) {

    if (uint32s->used + amount > uint32s->size) {
      if (uint32s->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_uint32s_t_resize(status, (*uint32s), uint32s->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_uint32s_increase_by_

#ifndef _di_fl_uint32ss_increase_
  f_return_status fl_uint32ss_increase(f_uint32ss_t *uint32ss) {

    if (uint32ss->used + 1 > uint32ss->size) {
      f_array_length_t size = uint32ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint32ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_uint32ss_t_resize(status, (*uint32ss), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_uint32ss_increase_

#ifndef _di_fl_uint32ss_increase_by_
  f_return_status fl_uint32ss_increase_by(const f_array_length_t amount, f_uint32ss_t *uint32ss) {

    if (uint32ss->used + amount > uint32ss->size) {
      if (uint32ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_uint32ss_t_resize(status, (*uint32ss), uint32ss->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_uint32ss_increase_by_

#ifndef _di_fl_int64s_increase_
  f_return_status fl_int64s_increase(f_int64s_t *int64s) {

    if (int64s->used + 1 > int64s->size) {
      f_array_length_t size = int64s->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int64s->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_int64s_t_resize(status, (*int64s), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_int64s_increase_

#ifndef _di_fl_int64s_increase_by_
  f_return_status fl_int64s_increase_by(const f_array_length_t amount, f_int64s_t *int64s) {

    if (int64s->used + amount > int64s->size) {
      if (int64s->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_int64s_t_resize(status, (*int64s), int64s->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_int64s_increase_by_

#ifndef _di_fl_int64ss_increase_
  f_return_status fl_int64ss_increase(f_int64ss_t *int64ss) {

    if (int64ss->used + 1 > int64ss->size) {
      f_array_length_t size = int64ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int64ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_int64ss_t_resize(status, (*int64ss), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_int64ss_increase_

#ifndef _di_fl_int64ss_increase_by_
  f_return_status fl_int64ss_increase_by(const f_array_length_t amount, f_int64ss_t *int64ss) {

    if (int64ss->used + amount > int64ss->size) {
      if (int64ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_int64ss_t_resize(status, (*int64ss), int64ss->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_int64ss_increase_by_

#ifndef _di_fl_uint64s_increase_
  f_return_status fl_uint64s_increase(f_uint64s_t *uint64s) {

    if (uint64s->used + 1 > uint64s->size) {
      f_array_length_t size = uint64s->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint64s->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_uint64s_t_resize(status, (*uint64s), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_uint64s_increase_

#ifndef _di_fl_uint64s_increase_by_
  f_return_status fl_uint64s_increase_by(const f_array_length_t amount, f_uint64s_t *uint64s) {

    if (uint64s->used + amount > uint64s->size) {
      if (uint64s->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_uint64s_t_resize(status, (*uint64s), uint64s->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_uint64s_increase_by_

#ifndef _di_fl_uint64ss_increase_
  f_return_status fl_uint64ss_increase(f_uint64ss_t *uint64ss) {

    if (uint64ss->used + 1 > uint64ss->size) {
      f_array_length_t size = uint64ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint64ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_uint64ss_t_resize(status, (*uint64ss), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_uint64ss_increase_

#ifndef _di_fl_uint64ss_increase_by_
  f_return_status fl_uint64ss_increase_by(const f_array_length_t amount, f_uint64ss_t *uint64ss) {

    if (uint64ss->used + amount > uint64ss->size) {
      if (uint64ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_uint64ss_t_resize(status, (*uint64ss), uint64ss->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_uint64ss_increase_by_

#ifndef _di_fl_int128s_increase_
  f_return_status fl_int128s_increase(f_int128s_t *int128s) {

    if (int128s->used + 1 > int128s->size) {
      f_array_length_t size = int128s->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int128s->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_int128s_t_resize(status, (*int128s), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_int128s_increase_

#ifndef _di_fl_int128s_increase_by_
  f_return_status fl_int128s_increase_by(const f_array_length_t amount, f_int128s_t *int128s) {

    if (int128s->used + amount > int128s->size) {
      if (int128s->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_int128s_t_resize(status, (*int128s), int128s->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_int128s_increase_by_

#ifndef _di_fl_int128ss_increase_
  f_return_status fl_int128ss_increase(f_int128ss_t *int128ss) {

    if (int128ss->used + 1 > int128ss->size) {
      f_array_length_t size = int128ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (int128ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_int128ss_t_resize(status, (*int128ss), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_int128ss_increase_

#ifndef _di_fl_int128ss_increase_by_
  f_return_status fl_int128ss_increase_by(const f_array_length_t amount, f_int128ss_t *int128ss) {

    if (int128ss->used + amount > int128ss->size) {
      if (int128ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_int128ss_t_resize(status, (*int128ss), int128ss->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_int128ss_increase_by_

#ifndef _di_fl_uint128s_increase_
  f_return_status fl_uint128s_increase(f_uint128s_t *uint128s) {

    if (uint128s->used + 1 > uint128s->size) {
      f_array_length_t size = uint128s->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint128s->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_uint128s_t_resize(status, (*uint128s), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_uint128s_increase_

#ifndef _di_fl_uint128s_increase_by_
  f_return_status fl_uint128s_increase_by(const f_array_length_t amount, f_uint128s_t *uint128s) {

    if (uint128s->used + amount > uint128s->size) {
      if (uint128s->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_uint128s_t_resize(status, (*uint128s), uint128s->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_uint128s_increase_by_

#ifndef _di_fl_uint128ss_increase_
  f_return_status fl_uint128ss_increase(f_uint128ss_t *uint128ss) {

    if (uint128ss->used + 1 > uint128ss->size) {
      f_array_length_t size = uint128ss->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (uint128ss->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      f_status_t status = F_none;

      f_macro_uint128ss_t_resize(status, (*uint128ss), size);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_uint128ss_increase_

#ifndef _di_fl_uint128ss_increase_by_
  f_return_status fl_uint128ss_increase_by(const f_array_length_t amount, f_uint128ss_t *uint128ss) {

    if (uint128ss->used + amount > uint128ss->size) {
      if (uint128ss->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      f_status_t status = F_none;

      f_macro_uint128ss_t_resize(status, (*uint128ss), uint128ss->used + amount);

      return status;
    }

    return F_none;
  }
#endif // _di_fl_uint128ss_increase_by_

#ifdef __cplusplus
} // extern "C"
#endif
