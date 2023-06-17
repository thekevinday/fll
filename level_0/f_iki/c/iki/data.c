#include "../iki.h"
#include "data.h"
#include "private-data.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_iki_data_delete_
  f_status_t f_iki_data_delete(f_iki_data_t *data) {
    #ifndef _di_level_0_parameter_checking_
      if (!data) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = f_string_ranges_resize(0, &data->content);
    if (F_status_is_error(status)) return status;

    status = f_number_unsigneds_resize(0, &data->delimits);
    if (F_status_is_error(status)) return status;

    status = f_string_ranges_resize(0, &data->variable);
    if (F_status_is_error(status)) return status;

    status = f_string_ranges_resize(0, &data->vocabulary);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_f_iki_data_delete_

#ifndef _di_f_iki_data_destroy_
  f_status_t f_iki_data_destroy(f_iki_data_t *data) {
    #ifndef _di_level_0_parameter_checking_
      if (!data) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = f_string_ranges_adjust(0, &data->content);
    if (F_status_is_error(status)) return status;

    status = f_number_unsigneds_adjust(0, &data->delimits);
    if (F_status_is_error(status)) return status;

    status = f_string_ranges_adjust(0, &data->variable);
    if (F_status_is_error(status)) return status;

    status = f_string_ranges_adjust(0, &data->vocabulary);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_f_iki_data_destroy_

#ifndef _di_f_iki_datas_adjust_
  f_status_t f_iki_datas_adjust(const f_number_unsigned_t length, f_iki_datas_t *datas) {
    #ifndef _di_level_0_parameter_checking_
      if (!datas) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_iki_datas_adjust(length, datas);
  }
#endif // _di_f_iki_datas_adjust_

#ifndef _di_f_iki_datas_append_
  f_status_t f_iki_datas_append(const f_iki_data_t source, f_iki_datas_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_iki_datas_append(source, destination);
  }
#endif // _di_f_iki_datas_append_

#ifndef _di_f_iki_datas_append_all_
  f_status_t f_iki_datas_append_all(const f_iki_datas_t source, f_iki_datas_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_iki_datas_append_all(source, destination);
  }
#endif // _di_f_iki_datas_append_all_

#ifndef _di_f_iki_datas_decimate_by_
  f_status_t f_iki_datas_decimate_by(const f_number_unsigned_t amount, f_iki_datas_t *datas) {
    #ifndef _di_level_0_parameter_checking_
      if (!datas) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (datas->size > amount) {
      return private_f_iki_datas_adjust(datas->size - amount, datas);
    }

    return private_f_iki_datas_adjust(0, datas);
  }
#endif // _di_f_iki_datas_decimate_by_

#ifndef _di_f_iki_datas_decrease_by_
  f_status_t f_iki_datas_decrease_by(const f_number_unsigned_t amount, f_iki_datas_t *datas) {
    #ifndef _di_level_0_parameter_checking_
      if (!datas) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (datas->size > amount) {
      return private_f_iki_datas_resize(datas->size - amount, datas);
    }

    return private_f_iki_datas_resize(0, datas);
  }
#endif // _di_f_iki_datas_decrease_by_

#ifndef _di_f_iki_datas_increase_
  f_status_t f_iki_datas_increase(const f_number_unsigned_t step, f_iki_datas_t *datas) {
    #ifndef _di_level_0_parameter_checking_
      if (!datas) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && datas->used + 1 > datas->size) {
      f_number_unsigned_t size = datas->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (datas->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_iki_datas_resize(size, datas);
    }

    return F_data_not;
  }
#endif // _di_f_iki_datas_increase_

#ifndef _di_f_iki_datas_increase_by_
  f_status_t f_iki_datas_increase_by(const f_number_unsigned_t amount, f_iki_datas_t *datas) {
    #ifndef _di_level_0_parameter_checking_
      if (!datas) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (datas->used + amount > datas->size) {
      if (datas->used + amount > F_number_t_size_unsigned_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_iki_datas_resize(datas->used + amount, datas);
    }

    return F_data_not;
  }
#endif // _di_f_iki_datas_increase_by_

#ifndef _di_f_iki_datas_resize_
  f_status_t f_iki_datas_resize(const f_number_unsigned_t length, f_iki_datas_t *datas) {
    #ifndef _di_level_0_parameter_checking_
      if (!datas) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_iki_datas_resize(length, datas);
  }
#endif // _di_f_iki_datas_resize_

#ifndef _di_f_iki_datass_adjust_
  f_status_t f_iki_datass_adjust(const f_number_unsigned_t length, f_iki_datass_t *datass) {
    #ifndef _di_level_0_parameter_checking_
      if (!datass) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_iki_datass_adjust(length, datass);
  }
#endif // _di_f_iki_datass_adjust_

#ifndef _di_f_iki_datass_append_
  f_status_t f_iki_datass_append(const f_iki_datas_t source, f_iki_datass_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_iki_datass_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    status = private_f_iki_datas_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_iki_datass_append_

#ifndef _di_f_iki_datass_append_all_
  f_status_t f_iki_datass_append_all(const f_iki_datass_t source, f_iki_datass_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_iki_datass_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_iki_datas_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_iki_datass_append_all_

#ifndef _di_f_iki_datass_decimate_by_
  f_status_t f_iki_datass_decimate_by(const f_number_unsigned_t amount, f_iki_datass_t *datass) {
    #ifndef _di_level_0_parameter_checking_
      if (!datass) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (datass->size > amount) {
      return private_f_iki_datass_adjust(datass->size - amount, datass);
    }

    return private_f_iki_datass_adjust(0, datass);
  }
#endif // _di_f_iki_datass_decimate_by_

#ifndef _di_f_iki_datass_decrease_by_
  f_status_t f_iki_datass_decrease_by(const f_number_unsigned_t amount, f_iki_datass_t *datass) {
    #ifndef _di_level_0_parameter_checking_
      if (!datass) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (datass->size > amount) {
      return private_f_iki_datass_resize(datass->size - amount, datass);
    }

    return private_f_iki_datass_resize(0, datass);
  }
#endif // _di_f_iki_datass_decrease_by_

#ifndef _di_f_iki_datass_increase_
  f_status_t f_iki_datass_increase(const f_number_unsigned_t step, f_iki_datass_t *datass) {
    #ifndef _di_level_0_parameter_checking_
      if (!datass) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && datass->used + 1 > datass->size) {
      f_number_unsigned_t size = datass->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (datass->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_iki_datass_resize(size, datass);
    }

    return F_data_not;
  }
#endif // _di_f_iki_datass_increase_

#ifndef _di_f_iki_datass_increase_by_
  f_status_t f_iki_datass_increase_by(const f_number_unsigned_t amount, f_iki_datass_t *datass) {
    #ifndef _di_level_0_parameter_checking_
      if (!datass) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (datass->used + amount > datass->size) {
      if (datass->used + amount > F_number_t_size_unsigned_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_iki_datass_resize(datass->used + amount, datass);
    }

    return F_data_not;
  }
#endif // _di_f_iki_datass_increase_by_

#ifndef _di_f_iki_datass_resize_
  f_status_t f_iki_datass_resize(const f_number_unsigned_t length, f_iki_datass_t *datass) {
    #ifndef _di_level_0_parameter_checking_
      if (!datass) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_iki_datass_resize(length, datass);
  }
#endif // _di_f_iki_datass_resize_

#ifdef __cplusplus
} // extern "C"
#endif
