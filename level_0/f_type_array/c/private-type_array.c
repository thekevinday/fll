#include "type_array.h"
#include "private-type_array.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_type_statuss_adjust_) || !defined(_di_f_type_statuss_decimate_by_)
  f_status_t private_f_type_statuss_adjust(const f_array_length_t length, f_statuss_t *statuss) {

    const f_status_t status = f_memory_adjust(statuss->size, length, sizeof(f_statuss_t), (void **) & statuss->array);

    if (F_status_is_error_not(status)) {
      statuss->size = length;

      if (statuss->used > statuss->size) {
        statuss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_statuss_adjust_) || !defined(_di_f_type_statuss_decimate_by_)

#if !defined(_di_f_type_statuss_append_) || !defined(_di_f_type_statusss_append_)
  extern f_status_t private_f_type_statuss_append(const f_statuss_t source, f_statuss_t *destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_statuss_adjust(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      destination->array[destination->used] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_type_statuss_append_) || !defined(_di_f_type_statusss_append_)

#if !defined(_di_f_type_statuss_resize_) || !defined(_di_f_type_statuss_append_) || !defined(_di_f_type_statuss_decimate_by_) || !defined(_di_f_type_statusss_append_)
  f_status_t private_f_type_statuss_resize(const f_array_length_t length, f_statuss_t *statuss) {

    const f_status_t status = f_memory_resize(statuss->size, length, sizeof(f_statuss_t), (void **) & statuss->array);

    if (F_status_is_error_not(status)) {
      statuss->size = length;

      if (statuss->used > statuss->size) {
        statuss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_statuss_resize_) || !defined(_di_f_type_statuss_append_) || !defined(_di_f_type_statuss_decimate_by_) || !defined(_di_f_type_statusss_append_)

#if !defined(_di_f_type_statusss_adjust_) || !defined(_di_f_type_statusss_decimate_by_)
  f_status_t private_f_type_statusss_adjust(const f_array_length_t length, f_statusss_t *statusss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < statusss->size; ++i) {

      status = f_memory_destroy(statusss->array[i].size, sizeof(f_statuss_t), (void **) & statusss->array[i].array);
      if (F_status_is_error(status)) return status;

      statusss->array[i].size = 0;
      statusss->array[i].used = 0;
    } // for

    status = f_memory_adjust(statusss->size, length, sizeof(f_statuss_t), (void **) & statusss->array);

    if (F_status_is_error_not(status)) {
      statusss->size = length;

      if (statusss->used > statusss->size) {
        statusss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_statusss_adjust_) || !defined(_di_f_type_statusss_decimate_by_)

#if !defined(_di_f_type_statusss_decrease_by_) || !defined(_di_f_type_statusss_increase_) || !defined(_di_f_type_statusss_increase_by_) || !defined(_di_f_type_statusss_resize_)
  f_status_t private_f_type_statusss_resize(const f_array_length_t length, f_statusss_t *statusss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < statusss->size; ++i) {

      status = f_memory_delete(statusss->array[i].size, sizeof(f_statuss_t), (void **) & statusss->array[i].array);
      if (F_status_is_error(status)) return status;

      statusss->array[i].size = 0;
      statusss->array[i].used = 0;
    } // for

    status = f_memory_resize(statusss->size, length, sizeof(f_statuss_t), (void **) & statusss->array);

    if (F_status_is_error_not(status)) {
      statusss->size = length;

      if (statusss->used > statusss->size) {
        statusss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_statusss_decrease_by_) || !defined(_di_f_type_statusss_increase_) || !defined(_di_f_type_statusss_increase_by_) || !defined(_di_f_type_statusss_resize_)

#if !defined(_di_f_type_states_adjust_) || !defined(_di_f_type_states_decimate_by_)
  f_status_t private_f_type_states_adjust(const f_array_length_t length, f_states_t *states) {

    const f_status_t status = f_memory_adjust(states->size, length, sizeof(f_states_t), (void **) & states->array);

    if (F_status_is_error_not(status)) {
      states->size = length;

      if (states->used > states->size) {
        states->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_states_adjust_) || !defined(_di_f_type_states_decimate_by_)

#if !defined(_di_f_type_states_append_) || !defined(_di_f_type_statess_append_)
  extern f_status_t private_f_type_states_append(const f_states_t source, f_states_t *destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_states_adjust(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      destination->array[destination->used] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_type_states_append_) || !defined(_di_f_type_statess_append_)

#if !defined(_di_f_type_states_resize_) || !defined(_di_f_type_states_append_) || !defined(_di_f_type_states_decimate_by_) || !defined(_di_f_type_statess_append_)
  f_status_t private_f_type_states_resize(const f_array_length_t length, f_states_t *states) {

    const f_status_t status = f_memory_resize(states->size, length, sizeof(f_states_t), (void **) & states->array);

    if (F_status_is_error_not(status)) {
      states->size = length;

      if (states->used > states->size) {
        states->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_states_resize_) || !defined(_di_f_type_states_append_) || !defined(_di_f_type_states_decimate_by_) || !defined(_di_f_type_statess_append_)

#if !defined(_di_f_type_statess_adjust_) || !defined(_di_f_type_statess_decimate_by_)
  f_status_t private_f_type_statess_adjust(const f_array_length_t length, f_statess_t *statess) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < statess->size; ++i) {

      status = f_memory_destroy(statess->array[i].size, sizeof(f_states_t), (void **) & statess->array[i].array);
      if (F_status_is_error(status)) return status;

      statess->array[i].size = 0;
      statess->array[i].used = 0;
    } // for

    status = f_memory_adjust(statess->size, length, sizeof(f_states_t), (void **) & statess->array);

    if (F_status_is_error_not(status)) {
      statess->size = length;

      if (statess->used > statess->size) {
        statess->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_statess_adjust_) || !defined(_di_f_type_statess_decimate_by_)

#if !defined(_di_f_type_statess_decrease_by_) || !defined(_di_f_type_statess_increase_) || !defined(_di_f_type_statess_increase_by_) || !defined(_di_f_type_statess_resize_)
  f_status_t private_f_type_statess_resize(const f_array_length_t length, f_statess_t *statess) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < statess->size; ++i) {

      status = f_memory_delete(statess->array[i].size, sizeof(f_states_t), (void **) & statess->array[i].array);
      if (F_status_is_error(status)) return status;

      statess->array[i].size = 0;
      statess->array[i].used = 0;
    } // for

    status = f_memory_resize(statess->size, length, sizeof(f_states_t), (void **) & statess->array);

    if (F_status_is_error_not(status)) {
      statess->size = length;

      if (statess->used > statess->size) {
        statess->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_statess_decrease_by_) || !defined(_di_f_type_statess_increase_) || !defined(_di_f_type_statess_increase_by_) || !defined(_di_f_type_statess_resize_)

#if !defined(_di_f_type_cells_adjust_) || !defined(_di_f_type_cells_decimate_by_)
  f_status_t private_f_type_cells_adjust(const f_array_length_t length, f_cells_t *cells) {

    const f_status_t status = f_memory_adjust(cells->size, length, sizeof(f_cells_t), (void **) & cells->array);

    if (F_status_is_error_not(status)) {
      cells->size = length;

      if (cells->used > cells->size) {
        cells->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_cells_adjust_) || !defined(_di_f_type_cells_decimate_by_)

#if !defined(_di_f_type_cells_append_) || !defined(_di_f_type_cellss_append_)
  extern f_status_t private_f_type_cells_append(const f_cells_t source, f_cells_t *destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_cells_adjust(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      destination->array[destination->used] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_type_cells_append_) || !defined(_di_f_type_cellss_append_)

#if !defined(_di_f_type_cells_resize_) || !defined(_di_f_type_cells_append_) || !defined(_di_f_type_cells_decimate_by_) || !defined(_di_f_type_cellss_append_)
  f_status_t private_f_type_cells_resize(const f_array_length_t length, f_cells_t *cells) {

    const f_status_t status = f_memory_resize(cells->size, length, sizeof(f_cells_t), (void **) & cells->array);

    if (F_status_is_error_not(status)) {
      cells->size = length;

      if (cells->used > cells->size) {
        cells->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_cells_resize_) || !defined(_di_f_type_cells_append_) || !defined(_di_f_type_cells_decimate_by_) || !defined(_di_f_type_cellss_append_)

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

#if !defined(_di_f_type_cellss_decrease_by_) || !defined(_di_f_type_cellss_increase_) || !defined(_di_f_type_cellss_increase_by_) || !defined(_di_f_type_cellss_resize_)
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
#endif // !defined(_di_f_type_cellss_decrease_by_) || !defined(_di_f_type_cellss_increase_) || !defined(_di_f_type_cellss_increase_by_) || !defined(_di_f_type_cellss_resize_)

#if !defined(_di_f_type_fll_ids_adjust_) || !defined(_di_f_type_fll_ids_decimate_by_)
  f_status_t private_f_type_fll_ids_adjust(const f_array_length_t length, f_fll_ids_t *ids) {

    const f_status_t status = f_memory_adjust(ids->size, length, sizeof(f_fll_ids_t), (void **) & ids->array);

    if (F_status_is_error_not(status)) {
      ids->size = length;

      if (ids->used > ids->size) {
        ids->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_fll_ids_adjust_) || !defined(_di_f_type_fll_ids_decimate_by_)

#if !defined(_di_f_type_fll_ids_append_) || !defined(_di_f_type_fll_idss_append_)
  extern f_status_t private_f_type_fll_ids_append(const f_fll_ids_t source, f_fll_ids_t *destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_fll_ids_adjust(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      destination->array[destination->used] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_type_fll_ids_append_) || !defined(_di_f_type_fll_idss_append_)

#if !defined(_di_f_type_fll_ids_resize_) || !defined(_di_f_type_fll_ids_append_) || !defined(_di_f_type_fll_ids_decimate_by_) || !defined(_di_f_type_fll_idss_append_)
  f_status_t private_f_type_fll_ids_resize(const f_array_length_t length, f_fll_ids_t *ids) {

    const f_status_t status = f_memory_resize(ids->size, length, sizeof(f_fll_ids_t), (void **) & ids->array);

    if (F_status_is_error_not(status)) {
      ids->size = length;

      if (ids->used > ids->size) {
        ids->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_fll_ids_resize_) || !defined(_di_f_type_fll_ids_append_) || !defined(_di_f_type_fll_ids_decimate_by_) || !defined(_di_f_type_fll_idss_append_)

#if !defined(_di_f_type_fll_idss_adjust_) || !defined(_di_f_type_fll_idss_decimate_by_)
  f_status_t private_f_type_fll_idss_adjust(const f_array_length_t length, f_fll_idss_t *idss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < idss->size; ++i) {

      status = f_memory_destroy(idss->array[i].size, sizeof(f_fll_ids_t), (void **) & idss->array[i].array);
      if (F_status_is_error(status)) return status;

      idss->array[i].size = 0;
      idss->array[i].used = 0;
    } // for

    status = f_memory_adjust(idss->size, length, sizeof(f_fll_ids_t), (void **) & idss->array);

    if (F_status_is_error_not(status)) {
      idss->size = length;

      if (idss->used > idss->size) {
        idss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_fll_idss_adjust_) || !defined(_di_f_type_fll_idss_decimate_by_)

#if !defined(_di_f_type_fll_idss_decrease_by_) || !defined(_di_f_type_fll_idss_increase_) || !defined(_di_f_type_fll_idss_increase_by_) || !defined(_di_f_type_fll_idss_resize_)
  f_status_t private_f_type_fll_idss_resize(const f_array_length_t length, f_fll_idss_t *idss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < idss->size; ++i) {

      status = f_memory_delete(idss->array[i].size, sizeof(f_fll_ids_t), (void **) & idss->array[i].array);
      if (F_status_is_error(status)) return status;

      idss->array[i].size = 0;
      idss->array[i].used = 0;
    } // for

    status = f_memory_resize(idss->size, length, sizeof(f_fll_ids_t), (void **) & idss->array);

    if (F_status_is_error_not(status)) {
      idss->size = length;

      if (idss->used > idss->size) {
        idss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_fll_idss_decrease_by_) || !defined(_di_f_type_fll_idss_increase_) || !defined(_di_f_type_fll_idss_increase_by_) || !defined(_di_f_type_fll_idss_resize_)

#if !defined(_di_f_type_array_lengths_adjust_) || !defined(_di_f_type_array_lengths_decimate_by_)
  f_status_t private_f_type_array_lengths_adjust(const f_array_length_t length, f_array_lengths_t *array_lengths) {

    const f_status_t status = f_memory_adjust(array_lengths->size, length, sizeof(f_array_lengths_t), (void **) & array_lengths->array);

    if (F_status_is_error_not(status)) {
      array_lengths->size = length;

      if (array_lengths->used > array_lengths->size) {
        array_lengths->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_array_lengths_adjust_) || !defined(_di_f_type_array_lengths_decimate_by_)

#if !defined(_di_f_type_array_lengths_append_) || !defined(_di_f_type_array_lengthss_append_)
  extern f_status_t private_f_type_array_lengths_append(const f_array_lengths_t source, f_array_lengths_t *destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_array_lengths_adjust(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      destination->array[destination->used] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_type_array_lengths_append_) || !defined(_di_f_type_array_lengthss_append_)

#if !defined(_di_f_type_array_lengths_resize_) || !defined(_di_f_type_array_lengths_append_) || !defined(_di_f_type_array_lengths_decimate_by_) || !defined(_di_f_type_array_lengthss_append_)
  f_status_t private_f_type_array_lengths_resize(const f_array_length_t length, f_array_lengths_t *lengths) {

    const f_status_t status = f_memory_resize(lengths->size, length, sizeof(f_array_lengths_t), (void **) & lengths->array);

    if (F_status_is_error_not(status)) {
      lengths->size = length;

      if (lengths->used > lengths->size) {
        lengths->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_array_lengths_resize_) || !defined(_di_f_type_array_lengths_append_) || !defined(_di_f_type_array_lengths_decimate_by_) || !defined(_di_f_type_array_lengthss_append_)

#if !defined(_di_f_type_array_lengthss_adjust_) || !defined(_di_f_type_array_lengthss_decimate_by_)
  f_status_t private_f_type_array_lengthss_adjust(const f_array_length_t length, f_array_lengthss_t *lengthss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < lengthss->size; ++i) {

      status = f_memory_destroy(lengthss->array[i].size, sizeof(f_array_lengths_t), (void **) & lengthss->array[i].array);
      if (F_status_is_error(status)) return status;

      lengthss->array[i].size = 0;
      lengthss->array[i].used = 0;
    } // for

    status = f_memory_adjust(lengthss->size, length, sizeof(f_array_lengths_t), (void **) & lengthss->array);

    if (F_status_is_error_not(status)) {
      lengthss->size = length;

      if (lengthss->used > lengthss->size) {
        lengthss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_array_lengthss_adjust_) || !defined(_di_f_type_array_lengthss_decimate_by_)

#if !defined(_di_f_type_array_lengthss_decrease_by_) || !defined(_di_f_type_array_lengthss_increase_) || !defined(_di_f_type_array_lengthss_increase_by_) || !defined(_di_f_type_array_lengthss_resize_)
  f_status_t private_f_type_array_lengthss_resize(const f_array_length_t length, f_array_lengthss_t *lengthss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < lengthss->size; ++i) {

      status = f_memory_delete(lengthss->array[i].size, sizeof(f_array_lengths_t), (void **) & lengthss->array[i].array);
      if (F_status_is_error(status)) return status;

      lengthss->array[i].size = 0;
      lengthss->array[i].used = 0;
    } // for

    status = f_memory_resize(lengthss->size, length, sizeof(f_array_lengths_t), (void **) & lengthss->array);

    if (F_status_is_error_not(status)) {
      lengthss->size = length;

      if (lengthss->used > lengthss->size) {
        lengthss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_array_lengthss_decrease_by_) || !defined(_di_f_type_array_lengthss_increase_) || !defined(_di_f_type_array_lengthss_increase_by_) || !defined(_di_f_type_array_lengthss_resize_)

#if !defined(_di_f_type_int8s_adjust_) || !defined(_di_f_type_int8s_decimate_by_)
  f_status_t private_f_type_int8s_adjust(const f_array_length_t length, f_int8s_t *int8s) {

    const f_status_t status = f_memory_adjust(int8s->size, length, sizeof(f_int8s_t), (void **) & int8s->array);

    if (F_status_is_error_not(status)) {
      int8s->size = length;

      if (int8s->used > int8s->size) {
        int8s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_int8s_adjust_) || !defined(_di_f_type_int8s_decimate_by_)

#if !defined(_di_f_type_int8s_append_) || !defined(_di_f_type_int8ss_append_)
  extern f_status_t private_f_type_int8s_append(const f_int8s_t source, f_int8s_t *destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_int8s_adjust(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      destination->array[destination->used] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_type_int8s_append_) || !defined(_di_f_type_int8ss_append_)

#if !defined(_di_f_type_int8s_resize_) || !defined(_di_f_type_int8s_append_) || !defined(_di_f_type_int8s_decimate_by_) || !defined(_di_f_type_int8ss_append_)
  f_status_t private_f_type_int8s_resize(const f_array_length_t length, f_int8s_t *int8s) {

    const f_status_t status = f_memory_resize(int8s->size, length, sizeof(f_int8s_t), (void **) & int8s->array);

    if (F_status_is_error_not(status)) {
      int8s->size = length;

      if (int8s->used > int8s->size) {
        int8s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_int8s_resize_) || !defined(_di_f_type_int8s_append_) || !defined(_di_f_type_int8s_decimate_by_) || !defined(_di_f_type_int8ss_append_)

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

#if !defined(_di_f_type_int8ss_decrease_by_) || !defined(_di_f_type_int8ss_increase_) || !defined(_di_f_type_int8ss_increase_by_) || !defined(_di_f_type_int8ss_resize_)
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
#endif // !defined(_di_f_type_int8ss_decrease_by_) || !defined(_di_f_type_int8ss_increase_) || !defined(_di_f_type_int8ss_increase_by_) || !defined(_di_f_type_int8ss_resize_)

#if !defined(_di_f_type_uint8s_adjust_) || !defined(_di_f_type_uint8s_decimate_by_)
  f_status_t private_f_type_uint8s_adjust(const f_array_length_t length, f_uint8s_t *uint8s) {

    const f_status_t status = f_memory_adjust(uint8s->size, length, sizeof(f_uint8s_t), (void **) & uint8s->array);

    if (F_status_is_error_not(status)) {
      uint8s->size = length;

      if (uint8s->used > uint8s->size) {
        uint8s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_uint8s_adjust_) || !defined(_di_f_type_uint8s_decimate_by_)

#if !defined(_di_f_type_uint8s_append_) || !defined(_di_f_type_uint8ss_append_)
  extern f_status_t private_f_type_uint8s_append(const f_uint8s_t source, f_uint8s_t *destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_uint8s_adjust(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      destination->array[destination->used] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_type_uint8s_append_) || !defined(_di_f_type_uint8ss_append_)

#if !defined(_di_f_type_uint8s_resize_) || !defined(_di_f_type_uint8s_append_) || !defined(_di_f_type_uint8s_decimate_by_) || !defined(_di_f_type_uint8ss_append_)
  f_status_t private_f_type_uint8s_resize(const f_array_length_t length, f_uint8s_t *uint8s) {

    const f_status_t status = f_memory_resize(uint8s->size, length, sizeof(f_uint8s_t), (void **) & uint8s->array);

    if (F_status_is_error_not(status)) {
      uint8s->size = length;

      if (uint8s->used > uint8s->size) {
        uint8s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_uint8s_resize_) || !defined(_di_f_type_uint8s_append_) || !defined(_di_f_type_uint8s_decimate_by_) || !defined(_di_f_type_uint8ss_append_)

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

#if !defined(_di_f_type_uint8ss_decrease_by_) || !defined(_di_f_type_uint8ss_increase_) || !defined(_di_f_type_uint8ss_increase_by_) || !defined(_di_f_type_uint8ss_resize_)
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
#endif // !defined(_di_f_type_uint8ss_decrease_by_) || !defined(_di_f_type_uint8ss_increase_) || !defined(_di_f_type_uint8ss_increase_by_) || !defined(_di_f_type_uint8ss_resize_)

#if !defined(_di_f_type_int16s_adjust_) || !defined(_di_f_type_int16s_decimate_by_)
  f_status_t private_f_type_int16s_adjust(const f_array_length_t length, f_int16s_t *int16s) {

    const f_status_t status = f_memory_adjust(int16s->size, length, sizeof(f_int16s_t), (void **) & int16s->array);

    if (F_status_is_error_not(status)) {
      int16s->size = length;

      if (int16s->used > int16s->size) {
        int16s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_int16s_adjust_) || !defined(_di_f_type_int16s_decimate_by_)

#if !defined(_di_f_type_int16s_append_) || !defined(_di_f_type_int16ss_append_)
  extern f_status_t private_f_type_int16s_append(const f_int16s_t source, f_int16s_t *destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_int16s_adjust(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      destination->array[destination->used] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_type_int16s_append_) || !defined(_di_f_type_int16ss_append_)

#if !defined(_di_f_type_int16s_resize_) || !defined(_di_f_type_int16s_append_) || !defined(_di_f_type_int16s_decimate_by_) || !defined(_di_f_type_int16ss_append_)
  f_status_t private_f_type_int16s_resize(const f_array_length_t length, f_int16s_t *int16s) {

    const f_status_t status = f_memory_resize(int16s->size, length, sizeof(f_int16s_t), (void **) & int16s->array);

    if (F_status_is_error_not(status)) {
      int16s->size = length;

      if (int16s->used > int16s->size) {
        int16s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_int16s_resize_) || !defined(_di_f_type_int16s_append_) || !defined(_di_f_type_int16s_decimate_by_) || !defined(_di_f_type_int16ss_append_)

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

#if !defined(_di_f_type_int16ss_decrease_by_) || !defined(_di_f_type_int16ss_increase_) || !defined(_di_f_type_int16ss_increase_by_) || !defined(_di_f_type_int16ss_resize_)
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
#endif // !defined(_di_f_type_int16ss_decrease_by_) || !defined(_di_f_type_int16ss_increase_) || !defined(_di_f_type_int16ss_increase_by_) || !defined(_di_f_type_int16ss_resize_)

#if !defined(_di_f_type_uint16s_adjust_) || !defined(_di_f_type_uint16s_decimate_by_)
  f_status_t private_f_type_uint16s_adjust(const f_array_length_t length, f_uint16s_t *uint16s) {

    const f_status_t status = f_memory_adjust(uint16s->size, length, sizeof(f_uint16s_t), (void **) & uint16s->array);

    if (F_status_is_error_not(status)) {
      uint16s->size = length;

      if (uint16s->used > uint16s->size) {
        uint16s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_uint16s_adjust_) || !defined(_di_f_type_uint16s_decimate_by_)

#if !defined(_di_f_type_uint16s_append_) || !defined(_di_f_type_uint16ss_append_)
  extern f_status_t private_f_type_uint16s_append(const f_uint16s_t source, f_uint16s_t *destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_uint16s_adjust(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      destination->array[destination->used] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_type_uint16s_append_) || !defined(_di_f_type_uint16ss_append_)

#if !defined(_di_f_type_uint16s_resize_) || !defined(_di_f_type_uint16s_append_) || !defined(_di_f_type_uint16s_decimate_by_) || !defined(_di_f_type_uint16ss_append_)
  f_status_t private_f_type_uint16s_resize(const f_array_length_t length, f_uint16s_t *uint16s) {

    const f_status_t status = f_memory_resize(uint16s->size, length, sizeof(f_uint16s_t), (void **) & uint16s->array);

    if (F_status_is_error_not(status)) {
      uint16s->size = length;

      if (uint16s->used > uint16s->size) {
        uint16s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_uint16s_resize_) || !defined(_di_f_type_uint16s_append_) || !defined(_di_f_type_uint16s_decimate_by_) || !defined(_di_f_type_uint16ss_append_)

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

#if !defined(_di_f_type_uint16ss_decrease_by_) || !defined(_di_f_type_uint16ss_increase_) || !defined(_di_f_type_uint16ss_increase_by_) || !defined(_di_f_type_uint16ss_resize_)
  f_status_t private_f_type_uint16ss_resize(const f_array_length_t length, f_uint16ss_t *uint16ss) {

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < uint16ss->size; ++i) {

      status = f_memory_delete(uint16ss->array[i].size, sizeof(f_uint16s_t), (void **) & uint16ss->array[i].array);
      if (F_status_is_error(status)) return status;

      uint16ss->array[i].size = 0;
      uint16ss->array[i].used = 0;
    } // for

    status = f_memory_resize(uint16ss->size, length, sizeof(f_uint16s_t), (void **) & uint16ss->array);

    if (F_status_is_error_not(status)) {
      uint16ss->size = length;

      if (uint16ss->used > uint16ss->size) {
        uint16ss->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_uint16ss_decrease_by_) || !defined(_di_f_type_uint16ss_increase_) || !defined(_di_f_type_uint16ss_increase_by_) || !defined(_di_f_type_uint16ss_resize_)

#if !defined(_di_f_type_int32s_adjust_) || !defined(_di_f_type_int32s_decimate_by_)
  f_status_t private_f_type_int32s_adjust(const f_array_length_t length, f_int32s_t *int32s) {

    const f_status_t status = f_memory_adjust(int32s->size, length, sizeof(f_int32s_t), (void **) & int32s->array);

    if (F_status_is_error_not(status)) {
      int32s->size = length;

      if (int32s->used > int32s->size) {
        int32s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_int32s_adjust_) || !defined(_di_f_type_int32s_decimate_by_)

#if !defined(_di_f_type_int32s_append_) || !defined(_di_f_type_int32ss_append_)
  extern f_status_t private_f_type_int32s_append(const f_int32s_t source, f_int32s_t *destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_int32s_adjust(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      destination->array[destination->used] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_type_int32s_append_) || !defined(_di_f_type_int32ss_append_)

#if !defined(_di_f_type_int32s_resize_) || !defined(_di_f_type_int32s_append_) || !defined(_di_f_type_int32s_decimate_by_) || !defined(_di_f_type_int32ss_append_)
  f_status_t private_f_type_int32s_resize(const f_array_length_t length, f_int32s_t *int32s) {

    const f_status_t status = f_memory_resize(int32s->size, length, sizeof(f_int32s_t), (void **) & int32s->array);

    if (F_status_is_error_not(status)) {
      int32s->size = length;

      if (int32s->used > int32s->size) {
        int32s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_int32s_resize_) || !defined(_di_f_type_int32s_append_) || !defined(_di_f_type_int32s_decimate_by_) || !defined(_di_f_type_int32ss_append_)

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

#if !defined(_di_f_type_int32ss_decrease_by_) || !defined(_di_f_type_int32ss_increase_) || !defined(_di_f_type_int32ss_increase_by_) || !defined(_di_f_type_int32ss_resize_)
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
#endif // !defined(_di_f_type_int32ss_decrease_by_) || !defined(_di_f_type_int32ss_increase_) || !defined(_di_f_type_int32ss_increase_by_) || !defined(_di_f_type_int32ss_resize_)

#if !defined(_di_f_type_uint32s_adjust_) || !defined(_di_f_type_uint32s_decimate_by_)
  f_status_t private_f_type_uint32s_adjust(const f_array_length_t length, f_uint32s_t *uint32s) {

    const f_status_t status = f_memory_adjust(uint32s->size, length, sizeof(f_uint32s_t), (void **) & uint32s->array);

    if (F_status_is_error_not(status)) {
      uint32s->size = length;

      if (uint32s->used > uint32s->size) {
        uint32s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_uint32s_adjust_) || !defined(_di_f_type_uint32s_decimate_by_)

#if !defined(_di_f_type_uint32s_append_) || !defined(_di_f_type_uint32ss_append_)
  extern f_status_t private_f_type_uint32s_append(const f_uint32s_t source, f_uint32s_t *destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_uint32s_adjust(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      destination->array[destination->used] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_type_uint32s_append_) || !defined(_di_f_type_uint32ss_append_)

#if !defined(_di_f_type_uint32s_resize_) || !defined(_di_f_type_uint32s_append_) || !defined(_di_f_type_uint32s_decimate_by_) || !defined(_di_f_type_uint32ss_append_)
  f_status_t private_f_type_uint32s_resize(const f_array_length_t length, f_uint32s_t *uint32s) {

    const f_status_t status = f_memory_resize(uint32s->size, length, sizeof(f_uint32s_t), (void **) & uint32s->array);

    if (F_status_is_error_not(status)) {
      uint32s->size = length;

      if (uint32s->used > uint32s->size) {
        uint32s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_uint32s_resize_) || !defined(_di_f_type_uint32s_append_) || !defined(_di_f_type_uint32s_decimate_by_) || !defined(_di_f_type_uint32ss_append_)

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

#if !defined(_di_f_type_uint32ss_decrease_by_) || !defined(_di_f_type_uint32ss_increase_) || !defined(_di_f_type_uint32ss_increase_by_) || !defined(_di_f_type_uint32ss_resize_)
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
#endif // !defined(_di_f_type_uint32ss_decrease_by_) || !defined(_di_f_type_uint32ss_increase_) || !defined(_di_f_type_uint32ss_increase_by_) || !defined(_di_f_type_uint32ss_resize_)

#if !defined(_di_f_type_int64s_adjust_) || !defined(_di_f_type_int64s_decimate_by_)
  f_status_t private_f_type_int64s_adjust(const f_array_length_t length, f_int64s_t *int64s) {

    const f_status_t status = f_memory_adjust(int64s->size, length, sizeof(f_int64s_t), (void **) & int64s->array);

    if (F_status_is_error_not(status)) {
      int64s->size = length;

      if (int64s->used > int64s->size) {
        int64s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_int64s_adjust_) || !defined(_di_f_type_int64s_decimate_by_)

#if !defined(_di_f_type_int64s_append_) || !defined(_di_f_type_int64ss_append_)
  extern f_status_t private_f_type_int64s_append(const f_int64s_t source, f_int64s_t *destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_int64s_adjust(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      destination->array[destination->used] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_type_int64s_append_) || !defined(_di_f_type_int64ss_append_)

#if !defined(_di_f_type_int64s_resize_) || !defined(_di_f_type_int64s_append_) || !defined(_di_f_type_int64s_decimate_by_) || !defined(_di_f_type_int64ss_append_)
  f_status_t private_f_type_int64s_resize(const f_array_length_t length, f_int64s_t *int64s) {

    const f_status_t status = f_memory_resize(int64s->size, length, sizeof(f_int64s_t), (void **) & int64s->array);

    if (F_status_is_error_not(status)) {
      int64s->size = length;

      if (int64s->used > int64s->size) {
        int64s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_int64s_resize_) || !defined(_di_f_type_int64s_append_) || !defined(_di_f_type_int64s_decimate_by_) || !defined(_di_f_type_int64ss_append_)

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

#if !defined(_di_f_type_int64ss_decrease_by_) || !defined(_di_f_type_int64ss_increase_) || !defined(_di_f_type_int64ss_increase_by_) || !defined(_di_f_type_int64ss_resize_)
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
#endif // !defined(_di_f_type_int64ss_decrease_by_) || !defined(_di_f_type_int64ss_increase_) || !defined(_di_f_type_int64ss_increase_by_) || !defined(_di_f_type_int64ss_resize_)

#if !defined(_di_f_type_uint64s_adjust_) || !defined(_di_f_type_uint64s_decimate_by_)
  f_status_t private_f_type_uint64s_adjust(const f_array_length_t length, f_uint64s_t *uint64s) {

    const f_status_t status = f_memory_adjust(uint64s->size, length, sizeof(f_uint64s_t), (void **) & uint64s->array);

    if (F_status_is_error_not(status)) {
      uint64s->size = length;

      if (uint64s->used > uint64s->size) {
        uint64s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_uint64s_adjust_) || !defined(_di_f_type_uint64s_decimate_by_)

#if !defined(_di_f_type_uint64s_append_) || !defined(_di_f_type_uint64ss_append_)
  extern f_status_t private_f_type_uint64s_append(const f_uint64s_t source, f_uint64s_t *destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_uint64s_adjust(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      destination->array[destination->used] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_type_uint64s_append_) || !defined(_di_f_type_uint64ss_append_)

#if !defined(_di_f_type_uint64s_resize_) || !defined(_di_f_type_uint64s_append_) || !defined(_di_f_type_uint64s_decimate_by_) || !defined(_di_f_type_uint64ss_append_)
  f_status_t private_f_type_uint64s_resize(const f_array_length_t length, f_uint64s_t *uint64s) {

    const f_status_t status = f_memory_resize(uint64s->size, length, sizeof(f_uint64s_t), (void **) & uint64s->array);

    if (F_status_is_error_not(status)) {
      uint64s->size = length;

      if (uint64s->used > uint64s->size) {
        uint64s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_uint64s_resize_) || !defined(_di_f_type_uint64s_append_) || !defined(_di_f_type_uint64s_decimate_by_) || !defined(_di_f_type_uint64ss_append_)

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

#if !defined(_di_f_type_uint64ss_decrease_by_) || !defined(_di_f_type_uint64ss_increase_) || !defined(_di_f_type_uint64ss_increase_by_) || !defined(_di_f_type_uint64ss_resize_)
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
#endif // !defined(_di_f_type_uint64ss_decrease_by_) || !defined(_di_f_type_uint64ss_increase_) || !defined(_di_f_type_uint64ss_increase_by_) || !defined(_di_f_type_uint64ss_resize_)

#if !defined(_di_f_type_int128s_adjust_) || !defined(_di_f_type_int128s_decimate_by_)
  f_status_t private_f_type_int128s_adjust(const f_array_length_t length, f_int128s_t *int128s) {

    const f_status_t status = f_memory_adjust(int128s->size, length, sizeof(f_int128s_t), (void **) & int128s->array);

    if (F_status_is_error_not(status)) {
      int128s->size = length;

      if (int128s->used > int128s->size) {
        int128s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_int128s_adjust_) || !defined(_di_f_type_int128s_decimate_by_)

#if !defined(_di_f_type_int128s_append_) || !defined(_di_f_type_int128ss_append_)
  extern f_status_t private_f_type_int128s_append(const f_int128s_t source, f_int128s_t *destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_int128s_adjust(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      destination->array[destination->used] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_type_int128s_append_) || !defined(_di_f_type_int128ss_append_)

#if !defined(_di_f_type_int128s_resize_) || !defined(_di_f_type_int128s_append_) || !defined(_di_f_type_int128s_decimate_by_) || !defined(_di_f_type_int128ss_append_)
  f_status_t private_f_type_int128s_resize(const f_array_length_t length, f_int128s_t *int128s) {

    const f_status_t status = f_memory_resize(int128s->size, length, sizeof(f_int128s_t), (void **) & int128s->array);

    if (F_status_is_error_not(status)) {
      int128s->size = length;

      if (int128s->used > int128s->size) {
        int128s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_int128s_resize_) || !defined(_di_f_type_int128s_append_) || !defined(_di_f_type_int128s_decimate_by_) || !defined(_di_f_type_int128ss_append_)

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

#if !defined(_di_f_type_int128ss_decrease_by_) || !defined(_di_f_type_int128ss_increase_) || !defined(_di_f_type_int128ss_increase_by_) || !defined(_di_f_type_int128ss_resize_)
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
#endif // !defined(_di_f_type_int128ss_decrease_by_) || !defined(_di_f_type_int128ss_increase_) || !defined(_di_f_type_int128ss_increase_by_) || !defined(_di_f_type_int128ss_resize_)

#if !defined(_di_f_type_uint128s_adjust_) || !defined(_di_f_type_uint128s_decimate_by_)
  f_status_t private_f_type_uint128s_adjust(const f_array_length_t length, f_uint128s_t *uint128s) {

    const f_status_t status = f_memory_adjust(uint128s->size, length, sizeof(f_uint128s_t), (void **) & uint128s->array);

    if (F_status_is_error_not(status)) {
      uint128s->size = length;

      if (uint128s->used > uint128s->size) {
        uint128s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_uint128s_adjust_) || !defined(_di_f_type_uint128s_decimate_by_)

#if !defined(_di_f_type_uint128s_append_) || !defined(_di_f_type_uint128ss_append_)
  extern f_status_t private_f_type_uint128s_append(const f_uint128s_t source, f_uint128s_t *destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_type_uint128s_adjust(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {
      destination->array[destination->used] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_type_uint128s_append_) || !defined(_di_f_type_uint128ss_append_)

#if !defined(_di_f_type_uint128s_resize_) || !defined(_di_f_type_uint128s_append_) || !defined(_di_f_type_uint128s_decimate_by_) || !defined(_di_f_type_uint128ss_append_)
  f_status_t private_f_type_uint128s_resize(const f_array_length_t length, f_uint128s_t *uint128s) {

    const f_status_t status = f_memory_resize(uint128s->size, length, sizeof(f_uint128s_t), (void **) & uint128s->array);

    if (F_status_is_error_not(status)) {
      uint128s->size = length;

      if (uint128s->used > uint128s->size) {
        uint128s->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_type_uint128s_resize_) || !defined(_di_f_type_uint128s_append_) || !defined(_di_f_type_uint128s_decimate_by_) || !defined(_di_f_type_uint128ss_append_)

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

#if !defined(_di_f_type_uint128ss_decrease_by_) || !defined(_di_f_type_uint128ss_increase_) || !defined(_di_f_type_uint128ss_increase_by_) || !defined(_di_f_type_uint128ss_resize_)
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
#endif // !defined(_di_f_type_uint128ss_decrease_by_) || !defined(_di_f_type_uint128ss_increase_) || !defined(_di_f_type_uint128ss_increase_by_) || !defined(_di_f_type_uint128ss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif
