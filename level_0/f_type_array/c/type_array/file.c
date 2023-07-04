#include "../type_array.h"
#include "../type_array_file.h"
#include "file.h"
#include "private-file.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_files_adjust_
  f_status_t f_files_adjust(const f_number_unsigned_t length, f_files_t * const files) {
    #ifndef _di_level_0_parameter_checking_
      if (!files) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_files_adjust(length, files);
  }
#endif // _di_f_files_adjust_

#ifndef _di_f_files_append_
  f_status_t f_files_append(const f_file_t source, f_files_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_files_append(source, destination);
  }
#endif // _di_f_files_append_

#ifndef _di_f_files_append_all_
  f_status_t f_files_append_all(const f_files_t source, f_files_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_files_append_all(source, destination);
  }
#endif // _di_f_files_append_all_

#ifndef _di_f_files_decimate_by_
  f_status_t f_files_decimate_by(const f_number_unsigned_t amount, f_files_t * const files) {
    #ifndef _di_level_0_parameter_checking_
      if (!files) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (files->size - amount > 0) {
      return private_f_files_adjust(files->size - amount, files);
    }

    return private_f_files_adjust(0, files);
  }
#endif // _di_f_files_decimate_by_

#ifndef _di_f_files_decrease_by_
  f_status_t f_files_decrease_by(const f_number_unsigned_t amount, f_files_t * const files) {
    #ifndef _di_level_0_parameter_checking_
      if (!files) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (files->size - amount > 0) {
      return private_f_files_resize(files->size - amount, files);
    }

    return private_f_files_resize(0, files);
  }
#endif // _di_f_files_decrease_by_

#ifndef _di_f_files_increase_
  f_status_t f_files_increase(const f_number_unsigned_t step, f_files_t * const files) {
    #ifndef _di_level_0_parameter_checking_
      if (!files) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && files->used + 1 > files->size) {
      f_number_unsigned_t size = files->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (files->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_files_resize(size, files);
    }

    return F_data_not;
  }
#endif // _di_f_files_increase_

#ifndef _di_f_files_increase_by_
  f_status_t f_files_increase_by(const f_number_unsigned_t amount, f_files_t * const files) {
    #ifndef _di_level_0_parameter_checking_
      if (!files) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (files->used + amount > files->size) {
      if (files->used + amount > F_number_t_size_unsigned_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_files_resize(files->used + amount, files);
    }

    return F_data_not;
  }
#endif // _di_f_files_increase_by_

#ifndef _di_f_files_resize_
  f_status_t f_files_resize(const f_number_unsigned_t length, f_files_t * const files) {
    #ifndef _di_level_0_parameter_checking_
      if (!files) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_files_resize(length, files);
  }
#endif // _di_f_files_resize_

#ifndef _di_f_filess_adjust_
  f_status_t f_filess_adjust(const f_number_unsigned_t length, f_filess_t * const filess) {
    #ifndef _di_level_0_parameter_checking_
      if (!filess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_filess_adjust(length, filess);
  }
#endif // _di_f_filess_adjust_

#ifndef _di_f_filess_append_
  f_status_t f_filess_append(const f_files_t source, f_filess_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_filess_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    status = private_f_files_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_filess_append_

#ifndef _di_f_filess_append_all_
  f_status_t f_filess_append_all(const f_filess_t source, f_filess_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_filess_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_files_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_filess_append_all_

#ifndef _di_f_filess_decimate_by_
  f_status_t f_filess_decimate_by(const f_number_unsigned_t amount, f_filess_t * const filess) {
    #ifndef _di_level_0_parameter_checking_
      if (!filess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (filess->size - amount > 0) {
      return private_f_filess_adjust(filess->size - amount, filess);
    }

    return private_f_filess_adjust(0, filess);
  }
#endif // _di_f_filess_decimate_by_

#ifndef _di_f_filess_decrease_by_
  f_status_t f_filess_decrease_by(const f_number_unsigned_t amount, f_filess_t * const filess) {
    #ifndef _di_level_0_parameter_checking_
      if (!filess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (filess->size - amount > 0) {
      return private_f_filess_resize(filess->size - amount, filess);
    }

    return private_f_filess_resize(0, filess);
  }
#endif // _di_f_filess_decrease_by_

#ifndef _di_f_filess_increase_
  f_status_t f_filess_increase(const f_number_unsigned_t step, f_filess_t * const filess) {
    #ifndef _di_level_0_parameter_checking_
      if (!filess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && filess->used + 1 > filess->size) {
      f_number_unsigned_t size = filess->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (filess->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_filess_resize(size, filess);
    }

    return F_data_not;
  }
#endif // _di_f_filess_increase_

#ifndef _di_f_filess_increase_by_
  f_status_t f_filess_increase_by(const f_number_unsigned_t amount, f_filess_t * const filess) {
    #ifndef _di_level_0_parameter_checking_
      if (!filess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (filess->used + amount > filess->size) {
      if (filess->used + amount > F_number_t_size_unsigned_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_filess_resize(filess->used + amount, filess);
    }

    return F_data_not;
  }
#endif // _di_f_filess_increase_by_

#ifndef _di_f_filess_resize_
  f_status_t f_filess_resize(const f_number_unsigned_t length, f_filess_t * const filess) {
    #ifndef _di_level_0_parameter_checking_
      if (!filess) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_filess_resize(length, filess);
  }
#endif // _di_f_filess_resize_

#ifdef __cplusplus
} // extern "C"
#endif
