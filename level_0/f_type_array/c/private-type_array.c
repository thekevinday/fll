#include "type_array.h"
#include "private-type_array.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_type_cellss_adjust_) || !defined(_di_f_type_cellss_decimate_by_)
  f_status_t private_f_type_cellss_adjust(const f_array_length_t length, f_cellss_t *cellss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < cellss->size; ++i) {

      status = f_memory_destroy(cellss->array[i].size, sizeof(f_cells_t), (void **) & cellss->array[i].array);
      if (F_status_is_error(status)) return status;

      cellss->array[i].size = 0;
      cellss->array[i].used = 0;
    } // for

    status = f_memory_adjust(cellss->size, length, sizeof(f_cells_t), (void **) & cellss->array);

    if (F_status_is_error_not(status)) {
      cellss->size = length;

      if (cellss->used > cellss->size) {
        cellss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_cellss_adjust_) || !defined(_di_f_type_cellss_decimate_by_)

#if !defined(_di_f_type_cellss_decrease_by_) || !defined(_di_f_type_cellss_increase_) || !defined(_di_f_type_cellss_increase_by_)
  f_status_t private_f_type_cellss_resize(const f_array_length_t length, f_cellss_t *cellss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < cellss->size; ++i) {

      status = f_memory_delete(cellss->array[i].size, sizeof(f_cells_t), (void **) & cellss->array[i].array);
      if (F_status_is_error(status)) return status;

      cellss->array[i].size = 0;
      cellss->array[i].used = 0;
    } // for

    status = f_memory_resize(cellss->size, length, sizeof(f_cells_t), (void **) & cellss->array);

    if (F_status_is_error_not(status)) {
      cellss->size = length;

      if (cellss->used > cellss->size) {
        cellss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_cellss_decrease_by_) || !defined(_di_f_type_cellss_increase_) || !defined(_di_f_type_cellss_increase_by_)

#if !defined(_di_f_type_array_lengthss_adjust_) || !defined(_di_f_type_array_lengthss_decimate_by_)
  f_status_t private_f_type_array_lengthss_adjust(const f_array_length_t length, f_array_lengthss_t *array_lengthss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < array_lengthss->size; ++i) {

      status = f_memory_destroy(array_lengthss->array[i].size, sizeof(f_array_lengths_t), (void **) & array_lengthss->array[i].array);
      if (F_status_is_error(status)) return status;

      array_lengthss->array[i].size = 0;
      array_lengthss->array[i].used = 0;
    } // for

    status = f_memory_adjust(array_lengthss->size, length, sizeof(f_array_lengths_t), (void **) & array_lengthss->array);

    if (F_status_is_error_not(status)) {
      array_lengthss->size = length;

      if (array_lengthss->used > array_lengthss->size) {
        array_lengthss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_array_lengthss_adjust_) || !defined(_di_f_type_array_lengthss_decimate_by_)

#if !defined(_di_f_type_array_lengthss_decrease_by_) || !defined(_di_f_type_array_lengthss_increase_) || !defined(_di_f_type_array_lengthss_increase_by_)
  f_status_t private_f_type_array_lengthss_resize(const f_array_length_t length, f_array_lengthss_t *array_lengthss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < array_lengthss->size; ++i) {

      status = f_memory_delete(array_lengthss->array[i].size, sizeof(f_array_lengths_t), (void **) & array_lengthss->array[i].array);
      if (F_status_is_error(status)) return status;

      array_lengthss->array[i].size = 0;
      array_lengthss->array[i].used = 0;
    } // for

    status = f_memory_resize(array_lengthss->size, length, sizeof(f_array_lengths_t), (void **) & array_lengthss->array);

    if (F_status_is_error_not(status)) {
      array_lengthss->size = length;

      if (array_lengthss->used > array_lengthss->size) {
        array_lengthss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_array_lengthss_decrease_by_) || !defined(_di_f_type_array_lengthss_increase_) || !defined(_di_f_type_array_lengthss_increase_by_)

#if !defined(_di_f_type_int8ss_adjust_) || !defined(_di_f_type_int8ss_decimate_by_)
  f_status_t private_f_type_int8ss_adjust(const f_array_length_t length, f_int8ss_t *int8ss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < int8ss->size; ++i) {

      status = f_memory_destroy(int8ss->array[i].size, sizeof(f_int8s_t), (void **) & int8ss->array[i].array);
      if (F_status_is_error(status)) return status;

      int8ss->array[i].size = 0;
      int8ss->array[i].used = 0;
    } // for

    status = f_memory_adjust(int8ss->size, length, sizeof(f_int8s_t), (void **) & int8ss->array);

    if (F_status_is_error_not(status)) {
      int8ss->size = length;

      if (int8ss->used > int8ss->size) {
        int8ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_int8ss_adjust_) || !defined(_di_f_type_int8ss_decimate_by_)

#if !defined(_di_f_type_int8ss_decrease_by_) || !defined(_di_f_type_int8ss_increase_) || !defined(_di_f_type_int8ss_increase_by_)
  f_status_t private_f_type_int8ss_resize(const f_array_length_t length, f_int8ss_t *int8ss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < int8ss->size; ++i) {

      status = f_memory_delete(int8ss->array[i].size, sizeof(f_int8s_t), (void **) & int8ss->array[i].array);
      if (F_status_is_error(status)) return status;

      int8ss->array[i].size = 0;
      int8ss->array[i].used = 0;
    } // for

    status = f_memory_resize(int8ss->size, length, sizeof(f_int8s_t), (void **) & int8ss->array);

    if (F_status_is_error_not(status)) {
      int8ss->size = length;

      if (int8ss->used > int8ss->size) {
        int8ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_int8ss_decrease_by_) || !defined(_di_f_type_int8ss_increase_) || !defined(_di_f_type_int8ss_increase_by_)

#if !defined(_di_f_type_uint8ss_adjust_) || !defined(_di_f_type_uint8ss_decimate_by_)
  f_status_t private_f_type_uint8ss_adjust(const f_array_length_t length, f_uint8ss_t *uint8ss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < uint8ss->size; ++i) {

      status = f_memory_destroy(uint8ss->array[i].size, sizeof(f_uint8s_t), (void **) & uint8ss->array[i].array);
      if (F_status_is_error(status)) return status;

      uint8ss->array[i].size = 0;
      uint8ss->array[i].used = 0;
    } // for

    status = f_memory_adjust(uint8ss->size, length, sizeof(f_uint8s_t), (void **) & uint8ss->array);

    if (F_status_is_error_not(status)) {
      uint8ss->size = length;

      if (uint8ss->used > uint8ss->size) {
        uint8ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_uint8ss_adjust_) || !defined(_di_f_type_uint8ss_decimate_by_)

#if !defined(_di_f_type_uint8ss_decrease_by_) || !defined(_di_f_type_uint8ss_increase_) || !defined(_di_f_type_uint8ss_increase_by_)
  f_status_t private_f_type_uint8ss_resize(const f_array_length_t length, f_uint8ss_t *uint8ss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < uint8ss->size; ++i) {

      status = f_memory_delete(uint8ss->array[i].size, sizeof(f_uint8s_t), (void **) & uint8ss->array[i].array);
      if (F_status_is_error(status)) return status;

      uint8ss->array[i].size = 0;
      uint8ss->array[i].used = 0;
    } // for

    status = f_memory_resize(uint8ss->size, length, sizeof(f_uint8s_t), (void **) & uint8ss->array);

    if (F_status_is_error_not(status)) {
      uint8ss->size = length;

      if (uint8ss->used > uint8ss->size) {
        uint8ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_uint8ss_decrease_by_) || !defined(_di_f_type_uint8ss_increase_) || !defined(_di_f_type_uint8ss_increase_by_)

#if !defined(_di_f_type_int16ss_adjust_) || !defined(_di_f_type_int16ss_decimate_by_)
  f_status_t private_f_type_int16ss_adjust(const f_array_length_t length, f_int16ss_t *int16ss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < int16ss->size; ++i) {

      status = f_memory_destroy(int16ss->array[i].size, sizeof(f_int16s_t), (void **) & int16ss->array[i].array);
      if (F_status_is_error(status)) return status;

      int16ss->array[i].size = 0;
      int16ss->array[i].used = 0;
    } // for

    status = f_memory_adjust(int16ss->size, length, sizeof(f_int16s_t), (void **) & int16ss->array);

    if (F_status_is_error_not(status)) {
      int16ss->size = length;

      if (int16ss->used > int16ss->size) {
        int16ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_int16ss_adjust_) || !defined(_di_f_type_int16ss_decimate_by_)

#if !defined(_di_f_type_int16ss_decrease_by_) || !defined(_di_f_type_int16ss_increase_) || !defined(_di_f_type_int16ss_increase_by_)
  f_status_t private_f_type_int16ss_resize(const f_array_length_t length, f_int16ss_t *int16ss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < int16ss->size; ++i) {

      status = f_memory_delete(int16ss->array[i].size, sizeof(f_int16s_t), (void **) & int16ss->array[i].array);
      if (F_status_is_error(status)) return status;

      int16ss->array[i].size = 0;
      int16ss->array[i].used = 0;
    } // for

    status = f_memory_resize(int16ss->size, length, sizeof(f_int16s_t), (void **) & int16ss->array);

    if (F_status_is_error_not(status)) {
      int16ss->size = length;

      if (int16ss->used > int16ss->size) {
        int16ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_int16ss_decrease_by_) || !defined(_di_f_type_int16ss_increase_) || !defined(_di_f_type_int16ss_increase_by_)

#if !defined(_di_f_type_uint16ss_adjust_) || !defined(_di_f_type_uint16ss_decimate_by_)
  f_status_t private_f_type_uint16ss_adjust(const f_array_length_t length, f_uint16ss_t *uint16ss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < uint16ss->size; ++i) {

      status = f_memory_destroy(uint16ss->array[i].size, sizeof(f_uint16s_t), (void **) & uint16ss->array[i].array);
      if (F_status_is_error(status)) return status;

      uint16ss->array[i].size = 0;
      uint16ss->array[i].used = 0;
    } // for

    status = f_memory_adjust(uint16ss->size, length, sizeof(f_uint16s_t), (void **) & uint16ss->array);

    if (F_status_is_error_not(status)) {
      uint16ss->size = length;

      if (uint16ss->used > uint16ss->size) {
        uint16ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_uint16ss_adjust_) || !defined(_di_f_type_uint16ss_decimate_by_)

#if !defined(_di_f_type_uint16ss_decrease_by_) || !defined(_di_f_type_uint16ss_increase_) || !defined(_di_f_type_uint16ss_increase_by_)
  f_status_t private_f_type_uint16ss_resize(const f_array_length_t length, f_uint16ss_t *uint16ss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < uint16ss->size; ++i) {

      status = f_memory_delete(uint16ss->array[i].size, sizeof(f_uint8s_t), (void **) & uint16ss->array[i].array);
      if (F_status_is_error(status)) return status;

      uint16ss->array[i].size = 0;
      uint16ss->array[i].used = 0;
    } // for

    status = f_memory_resize(uint16ss->size, length, sizeof(f_uint8s_t), (void **) & uint16ss->array);

    if (F_status_is_error_not(status)) {
      uint16ss->size = length;

      if (uint16ss->used > uint16ss->size) {
        uint16ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_uint16ss_decrease_by_) || !defined(_di_f_type_uint16ss_increase_) || !defined(_di_f_type_uint16ss_increase_by_)

#if !defined(_di_f_type_int32ss_adjust_) || !defined(_di_f_type_int32ss_decimate_by_)
  f_status_t private_f_type_int32ss_adjust(const f_array_length_t length, f_int32ss_t *int32ss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < int32ss->size; ++i) {

      status = f_memory_destroy(int32ss->array[i].size, sizeof(f_int32s_t), (void **) & int32ss->array[i].array);
      if (F_status_is_error(status)) return status;

      int32ss->array[i].size = 0;
      int32ss->array[i].used = 0;
    } // for

    status = f_memory_adjust(int32ss->size, length, sizeof(f_int32s_t), (void **) & int32ss->array);

    if (F_status_is_error_not(status)) {
      int32ss->size = length;

      if (int32ss->used > int32ss->size) {
        int32ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_int32ss_adjust_) || !defined(_di_f_type_int32ss_decimate_by_)

#if !defined(_di_f_type_int32ss_decrease_by_) || !defined(_di_f_type_int32ss_increase_) || !defined(_di_f_type_int32ss_increase_by_)
  f_status_t private_f_type_int32ss_resize(const f_array_length_t length, f_int32ss_t *int32ss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < int32ss->size; ++i) {

      status = f_memory_delete(int32ss->array[i].size, sizeof(f_int32s_t), (void **) & int32ss->array[i].array);
      if (F_status_is_error(status)) return status;

      int32ss->array[i].size = 0;
      int32ss->array[i].used = 0;
    } // for

    status = f_memory_resize(int32ss->size, length, sizeof(f_int32s_t), (void **) & int32ss->array);

    if (F_status_is_error_not(status)) {
      int32ss->size = length;

      if (int32ss->used > int32ss->size) {
        int32ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_int32ss_decrease_by_) || !defined(_di_f_type_int32ss_increase_) || !defined(_di_f_type_int32ss_increase_by_)

#if !defined(_di_f_type_uint32ss_adjust_) || !defined(_di_f_type_uint32ss_decimate_by_)
  f_status_t private_f_type_uint32ss_adjust(const f_array_length_t length, f_uint32ss_t *uint32ss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < uint32ss->size; ++i) {

      status = f_memory_destroy(uint32ss->array[i].size, sizeof(f_uint32s_t), (void **) & uint32ss->array[i].array);
      if (F_status_is_error(status)) return status;

      uint32ss->array[i].size = 0;
      uint32ss->array[i].used = 0;
    } // for

    status = f_memory_adjust(uint32ss->size, length, sizeof(f_uint32s_t), (void **) & uint32ss->array);

    if (F_status_is_error_not(status)) {
      uint32ss->size = length;

      if (uint32ss->used > uint32ss->size) {
        uint32ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_uint32ss_adjust_) || !defined(_di_f_type_uint32ss_decimate_by_)

#if !defined(_di_f_type_uint32ss_decrease_by_) || !defined(_di_f_type_uint32ss_increase_) || !defined(_di_f_type_uint32ss_increase_by_)
  f_status_t private_f_type_uint32ss_resize(const f_array_length_t length, f_uint32ss_t *uint32ss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < uint32ss->size; ++i) {

      status = f_memory_delete(uint32ss->array[i].size, sizeof(f_uint32s_t), (void **) & uint32ss->array[i].array);
      if (F_status_is_error(status)) return status;

      uint32ss->array[i].size = 0;
      uint32ss->array[i].used = 0;
    } // for

    status = f_memory_resize(uint32ss->size, length, sizeof(f_uint32s_t), (void **) & uint32ss->array);

    if (F_status_is_error_not(status)) {
      uint32ss->size = length;

      if (uint32ss->used > uint32ss->size) {
        uint32ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_uint32ss_decrease_by_) || !defined(_di_f_type_uint32ss_increase_) || !defined(_di_f_type_uint32ss_increase_by_)

#if !defined(_di_f_type_int64ss_adjust_) || !defined(_di_f_type_int64ss_decimate_by_)
  f_status_t private_f_type_int64ss_adjust(const f_array_length_t length, f_int64ss_t *int64ss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < int64ss->size; ++i) {

      status = f_memory_destroy(int64ss->array[i].size, sizeof(f_int64s_t), (void **) & int64ss->array[i].array);
      if (F_status_is_error(status)) return status;

      int64ss->array[i].size = 0;
      int64ss->array[i].used = 0;
    } // for

    status = f_memory_adjust(int64ss->size, length, sizeof(f_int64s_t), (void **) & int64ss->array);

    if (F_status_is_error_not(status)) {
      int64ss->size = length;

      if (int64ss->used > int64ss->size) {
        int64ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_int64ss_adjust_) || !defined(_di_f_type_int64ss_decimate_by_)

#if !defined(_di_f_type_int64ss_decrease_by_) || !defined(_di_f_type_int64ss_increase_) || !defined(_di_f_type_int64ss_increase_by_)
  f_status_t private_f_type_int64ss_resize(const f_array_length_t length, f_int64ss_t *int64ss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < int64ss->size; ++i) {

      status = f_memory_delete(int64ss->array[i].size, sizeof(f_int64s_t), (void **) & int64ss->array[i].array);
      if (F_status_is_error(status)) return status;

      int64ss->array[i].size = 0;
      int64ss->array[i].used = 0;
    } // for

    status = f_memory_resize(int64ss->size, length, sizeof(f_int64s_t), (void **) & int64ss->array);

    if (F_status_is_error_not(status)) {
      int64ss->size = length;

      if (int64ss->used > int64ss->size) {
        int64ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_int64ss_decrease_by_) || !defined(_di_f_type_int64ss_increase_) || !defined(_di_f_type_int64ss_increase_by_)

#if !defined(_di_f_type_uint64ss_adjust_) || !defined(_di_f_type_uint64ss_decimate_by_)
  f_status_t private_f_type_uint64ss_adjust(const f_array_length_t length, f_uint64ss_t *uint64ss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < uint64ss->size; ++i) {

      status = f_memory_destroy(uint64ss->array[i].size, sizeof(f_uint64s_t), (void **) & uint64ss->array[i].array);
      if (F_status_is_error(status)) return status;

      uint64ss->array[i].size = 0;
      uint64ss->array[i].used = 0;
    } // for

    status = f_memory_adjust(uint64ss->size, length, sizeof(f_uint64s_t), (void **) & uint64ss->array);

    if (F_status_is_error_not(status)) {
      uint64ss->size = length;

      if (uint64ss->used > uint64ss->size) {
        uint64ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_uint64ss_adjust_) || !defined(_di_f_type_uint64ss_decimate_by_)

#if !defined(_di_f_type_uint64ss_decrease_by_) || !defined(_di_f_type_uint64ss_increase_) || !defined(_di_f_type_uint64ss_increase_by_)
  f_status_t private_f_type_uint64ss_resize(const f_array_length_t length, f_uint64ss_t *uint64ss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < uint64ss->size; ++i) {

      status = f_memory_delete(uint64ss->array[i].size, sizeof(f_uint64s_t), (void **) & uint64ss->array[i].array);
      if (F_status_is_error(status)) return status;

      uint64ss->array[i].size = 0;
      uint64ss->array[i].used = 0;
    } // for

    status = f_memory_resize(uint64ss->size, length, sizeof(f_uint64s_t), (void **) & uint64ss->array);

    if (F_status_is_error_not(status)) {
      uint64ss->size = length;

      if (uint64ss->used > uint64ss->size) {
        uint64ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_uint64ss_decrease_by_) || !defined(_di_f_type_uint64ss_increase_) || !defined(_di_f_type_uint64ss_increase_by_)

#if !defined(_di_f_type_int128ss_adjust_) || !defined(_di_f_type_int128ss_decimate_by_)
  f_status_t private_f_type_int128ss_adjust(const f_array_length_t length, f_int128ss_t *int128ss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < int128ss->size; ++i) {

      status = f_memory_destroy(int128ss->array[i].size, sizeof(f_int128s_t), (void **) & int128ss->array[i].array);
      if (F_status_is_error(status)) return status;

      int128ss->array[i].size = 0;
      int128ss->array[i].used = 0;
    } // for

    status = f_memory_adjust(int128ss->size, length, sizeof(f_int128s_t), (void **) & int128ss->array);

    if (F_status_is_error_not(status)) {
      int128ss->size = length;

      if (int128ss->used > int128ss->size) {
        int128ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_int128ss_adjust_) || !defined(_di_f_type_int128ss_decimate_by_)

#if !defined(_di_f_type_int128ss_decrease_by_) || !defined(_di_f_type_int128ss_increase_) || !defined(_di_f_type_int128ss_increase_by_)
  f_status_t private_f_type_int128ss_resize(const f_array_length_t length, f_int128ss_t *int128ss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < int128ss->size; ++i) {

      status = f_memory_delete(int128ss->array[i].size, sizeof(f_int128s_t), (void **) & int128ss->array[i].array);
      if (F_status_is_error(status)) return status;

      int128ss->array[i].size = 0;
      int128ss->array[i].used = 0;
    } // for

    status = f_memory_resize(int128ss->size, length, sizeof(f_int128s_t), (void **) & int128ss->array);

    if (F_status_is_error_not(status)) {
      int128ss->size = length;

      if (int128ss->used > int128ss->size) {
        int128ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_int128ss_decrease_by_) || !defined(_di_f_type_int128ss_increase_) || !defined(_di_f_type_int128ss_increase_by_)

#if !defined(_di_f_type_uint128ss_adjust_) || !defined(_di_f_type_uint128ss_decimate_by_)
  f_status_t private_f_type_uint128ss_adjust(const f_array_length_t length, f_uint128ss_t *uint128ss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < uint128ss->size; ++i) {

      status = f_memory_destroy(uint128ss->array[i].size, sizeof(f_uint128s_t), (void **) & uint128ss->array[i].array);
      if (F_status_is_error(status)) return status;

      uint128ss->array[i].size = 0;
      uint128ss->array[i].used = 0;
    } // for

    status = f_memory_adjust(uint128ss->size, length, sizeof(f_uint128s_t), (void **) & uint128ss->array);

    if (F_status_is_error_not(status)) {
      uint128ss->size = length;

      if (uint128ss->used > uint128ss->size) {
        uint128ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_uint128ss_adjust_) || !defined(_di_f_type_uint128ss_decimate_by_)

#if !defined(_di_f_type_uint128ss_decrease_by_) || !defined(_di_f_type_uint128ss_increase_) || !defined(_di_f_type_uint128ss_increase_by_)
  f_status_t private_f_type_uint128ss_resize(const f_array_length_t length, f_uint128ss_t *uint128ss) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < uint128ss->size; ++i) {

      status = f_memory_delete(uint128ss->array[i].size, sizeof(f_uint128s_t), (void **) & uint128ss->array[i].array);
      if (F_status_is_error(status)) return status;

      uint128ss->array[i].size = 0;
      uint128ss->array[i].used = 0;
    } // for

    status = f_memory_resize(uint128ss->size, length, sizeof(f_uint128s_t), (void **) & uint128ss->array);

    if (F_status_is_error_not(status)) {
      uint128ss->size = length;

      if (uint128ss->used > uint128ss->size) {
        uint128ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_uint128ss_decrease_by_) || !defined(_di_f_type_uint128ss_increase_) || !defined(_di_f_type_uint128ss_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif
