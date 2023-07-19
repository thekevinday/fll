#include "../iki.h"
#include "private-data.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_iki_datas_adjust_) || !defined(_di_f_iki_datas_decimate_by_)
  f_status_t private_f_iki_datas_adjust(const f_number_unsigned_t length, f_iki_datas_t *datas) {

    if (datas->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);
    if (datas->used + length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < datas->size; ++i) {

      status = f_string_ranges_adjust(0, &datas->array[i].content);
      if (F_status_is_error(status)) return status;

      status = f_number_unsigneds_adjust(0, &datas->array[i].delimits);
      if (F_status_is_error(status)) return status;

      status = f_string_ranges_adjust(0, &datas->array[i].variable);
      if (F_status_is_error(status)) return status;

      status = f_string_ranges_adjust(0, &datas->array[i].vocabulary);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_iki_data_t), (void **) &datas->array, &datas->used, &datas->size);
  }
#endif // !defined(_di_f_iki_datas_adjust_) || !defined(_di_f_iki_datas_decimate_by_)

#if !defined(_di_f_iki_datas_append_) || !defined(_di_f_iki_datass_append_)
  extern f_status_t private_f_iki_datas_append(const f_iki_data_t source, f_iki_datas_t *destination) {

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_iki_datas_resize(destination->used + F_iki_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used].content.used = 0;
    destination->array[destination->used].delimits.used = 0;
    destination->array[destination->used].variable.used = 0;
    destination->array[destination->used].vocabulary.used = 0;

    if (source.content.used) {
      status = f_string_ranges_append_all(source.content, &destination->array[destination->used].content);
      if (F_status_is_error(status)) return status;
    }

    if (source.delimits.used) {
      status = f_number_unsigneds_append_all(source.delimits, &destination->array[destination->used].delimits);
      if (F_status_is_error(status)) return status;
    }

    if (source.variable.used) {
      status = f_string_ranges_append_all(source.variable, &destination->array[destination->used].variable);
      if (F_status_is_error(status)) return status;
    }

    if (source.vocabulary.used) {
      status = f_string_ranges_append_all(source.vocabulary, &destination->array[destination->used].vocabulary);
      if (F_status_is_error(status)) return status;
    }

    ++destination->used;

    return F_none;
  }
#endif // !defined(_di_f_iki_datas_append_) || !defined(_di_f_iki_datass_append_)

#if !defined(_di_f_iki_datas_append_) || !defined(_di_f_iki_datas_append_all_) || !defined(_di_f_iki_datass_append_all_)
  extern f_status_t private_f_iki_datas_append_all(const f_iki_datas_t source, f_iki_datas_t *destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_iki_datas_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].content.used = 0;
      destination->array[destination->used].delimits.used = 0;
      destination->array[destination->used].variable.used = 0;
      destination->array[destination->used].vocabulary.used = 0;

      if (source.array[i].content.used) {
        status = f_string_ranges_append_all(source.array[i].content, &destination->array[destination->used].content);
        if (F_status_is_error(status)) return status;
      }

      if (source.array[i].delimits.used) {
        status = f_number_unsigneds_append_all(source.array[i].delimits, &destination->array[destination->used].delimits);
        if (F_status_is_error(status)) return status;
      }

      if (source.array[i].variable.used) {
        status = f_string_ranges_append_all(source.array[i].variable, &destination->array[destination->used].variable);
        if (F_status_is_error(status)) return status;
      }

      if (source.array[i].vocabulary.used) {
        status = f_string_ranges_append_all(source.array[i].vocabulary, &destination->array[destination->used].vocabulary);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_iki_datas_append_) || !defined(_di_f_iki_datas_append_all_) || !defined(_di_f_iki_datass_append_all_)

#if !defined(_di_f_iki_datas_append_) || !defined(_di_f_iki_datas_decrease_by_) || !defined(_di_f_iki_datas_increase_) || !defined(_di_f_iki_datas_increase_by_) || !defined(_di_f_iki_datas_resize_)
  f_status_t private_f_iki_datas_resize(const f_number_unsigned_t length, f_iki_datas_t *datas) {

    if (datas->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);
    if (datas->used + length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < datas->size; ++i) {

      status = f_string_ranges_resize(0, &datas->array[i].content);
      if (F_status_is_error(status)) return status;

      status = f_number_unsigneds_resize(0, &datas->array[i].delimits);
      if (F_status_is_error(status)) return status;

      status = f_string_ranges_resize(0, &datas->array[i].variable);
      if (F_status_is_error(status)) return status;

      status = f_string_ranges_resize(0, &datas->array[i].vocabulary);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_iki_data_t), (void **) &datas->array, &datas->used, &datas->size);
  }
#endif // !defined(_di_f_iki_datas_append_) || !defined(_di_f_iki_datas_decrease_by_) || !defined(_di_f_iki_datas_increase_) || !defined(_di_f_iki_datas_increase_by_) || !defined(_di_f_iki_datas_resize_)

#if !defined(_di_f_iki_datass_adjust_) || !defined(_di_f_iki_datass_decimate_by_)
  f_status_t private_f_iki_datass_adjust(const f_number_unsigned_t length, f_iki_datass_t *datass) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < datass->size; ++i) {

      status = private_f_iki_datas_adjust(0, &datass->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(datass->size, length, sizeof(f_iki_datas_t), (void **) & datass->array);
    if (F_status_is_error(status)) return status;

    datass->size = length;

    if (datass->used > datass->size) {
      datass->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_iki_datass_adjust_) || !defined(_di_f_iki_datass_decimate_by_)

#if !defined(_di_f_iki_datass_decrease_by_) || !defined(_di_f_iki_datass_increase_) || !defined(_di_f_iki_datass_increase_by_) || !defined(_di_f_iki_datass_resize_)
  f_status_t private_f_iki_datass_resize(const f_number_unsigned_t length, f_iki_datass_t *datass) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < datass->size; ++i) {

      status = f_memory_delete(datass->array[i].size, sizeof(f_iki_datas_t), (void **) & datass->array[i].array);
      if (F_status_is_error(status)) return status;

      datass->array[i].size = 0;
      datass->array[i].used = 0;
    } // for

    status = f_memory_resize(datass->size, length, sizeof(f_iki_datas_t), (void **) & datass->array);
    if (F_status_is_error(status)) return status;

    datass->size = length;

    if (datass->used > datass->size) {
      datass->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_iki_datass_decrease_by_) || !defined(_di_f_iki_datass_increase_) || !defined(_di_f_iki_datass_increase_by_) || !defined(_di_f_iki_datass_resize_)

#ifdef __cplusplus
} // extern "C"
#endif
