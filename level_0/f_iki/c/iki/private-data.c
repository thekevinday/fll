#include "../iki.h"
#include "private-data.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_iki_datas_adjust_) || !defined(_di_f_iki_datas_decimate_by_)
  f_status_t private_f_iki_datas_adjust(const f_number_unsigned_t length, f_iki_datas_t *structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = f_string_ranges_adjust(0, &structure->array[i].content);
      if (F_status_is_error(status)) return status;

      status = f_memory_array_adjust(0, sizeof(f_number_unsigned_t), (void **) &structure->array[i].delimits.array, &structure->array[i].delimits.used, &structure->array[i].delimits.size);
      if (F_status_is_error(status)) return status;

      status = f_string_ranges_adjust(0, &structure->array[i].variable);
      if (F_status_is_error(status)) return status;

      status = f_string_ranges_adjust(0, &structure->array[i].vocabulary);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_iki_data_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_iki_datas_adjust_) || !defined(_di_f_iki_datas_decimate_by_)

#if !defined(_di_f_iki_datas_append_) || !defined(_di_f_iki_datass_append_)
  extern f_status_t private_f_iki_datas_append(const f_iki_data_t source, f_iki_datas_t *destination) {

    f_status_t status = f_memory_array_increase(F_iki_default_allocation_small_d, sizeof(f_iki_data_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

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

    f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_iki_data_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

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
  f_status_t private_f_iki_datas_resize(const f_number_unsigned_t length, f_iki_datas_t *structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = f_string_ranges_resize(0, &structure->array[i].content);
      if (F_status_is_error(status)) return status;

      status = f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &structure->array[i].delimits.array, &structure->array[i].delimits.used, &structure->array[i].delimits.size);
      if (F_status_is_error(status)) return status;

      status = f_string_ranges_resize(0, &structure->array[i].variable);
      if (F_status_is_error(status)) return status;

      status = f_string_ranges_resize(0, &structure->array[i].vocabulary);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_iki_data_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_iki_datas_append_) || !defined(_di_f_iki_datas_decrease_by_) || !defined(_di_f_iki_datas_increase_) || !defined(_di_f_iki_datas_increase_by_) || !defined(_di_f_iki_datas_resize_)

#if !defined(_di_f_iki_datass_adjust_) || !defined(_di_f_iki_datass_decimate_by_)
  f_status_t private_f_iki_datass_adjust(const f_number_unsigned_t length, f_iki_datass_t *structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = private_f_iki_datas_adjust(0, &structure->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_iki_datas_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_iki_datass_adjust_) || !defined(_di_f_iki_datass_decimate_by_)

#if !defined(_di_f_iki_datass_decrease_by_) || !defined(_di_f_iki_datass_increase_) || !defined(_di_f_iki_datass_increase_by_) || !defined(_di_f_iki_datass_resize_)
  f_status_t private_f_iki_datass_resize(const f_number_unsigned_t length, f_iki_datass_t *structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = private_f_iki_datas_resize(0, &structure->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_iki_datas_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_iki_datass_decrease_by_) || !defined(_di_f_iki_datass_increase_) || !defined(_di_f_iki_datass_increase_by_) || !defined(_di_f_iki_datass_resize_)

#ifdef __cplusplus
} // extern "C"
#endif
