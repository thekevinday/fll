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

    {
      f_status_t status = f_string_ranges_resize(0, &data->content);
      if (F_status_is_error(status)) return status;

      status = f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &data->delimits.array, &data->delimits.used, &data->delimits.size);
      if (F_status_is_error(status)) return status;

      status = f_string_ranges_resize(0, &data->variable);
      if (F_status_is_error(status)) return status;

      status = f_string_ranges_resize(0, &data->vocabulary);
      if (F_status_is_error(status)) return status;
    }

    return F_okay;
  }
#endif // _di_f_iki_data_delete_

#ifndef _di_f_iki_data_destroy_
  f_status_t f_iki_data_destroy(f_iki_data_t *data) {
    #ifndef _di_level_0_parameter_checking_
      if (!data) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      f_status_t status = f_string_ranges_adjust(0, &data->content);
      if (F_status_is_error(status)) return status;

      status = f_memory_array_adjust(0, sizeof(f_number_unsigned_t), (void **) &data->delimits.array, &data->delimits.used, &data->delimits.size);
      if (F_status_is_error(status)) return status;

      status = f_string_ranges_adjust(0, &data->variable);
      if (F_status_is_error(status)) return status;

      status = f_string_ranges_adjust(0, &data->vocabulary);
      if (F_status_is_error(status)) return status;
    }

    return F_okay;
  }
#endif // _di_f_iki_data_destroy_

#ifndef _di_f_iki_datas_append_
  f_status_t f_iki_datas_append(const f_iki_data_t source, f_iki_datas_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

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
      for (f_number_unsigned_t i = 0; i < source.delimits.used; ++i) {

        status = f_memory_array_append(source.delimits.array + i, sizeof(f_number_unsigned_t), (void **) &destination->array[destination->used].delimits.array, &destination->array[destination->used].delimits.used, &destination->array[destination->used].delimits.size);
        if (F_status_is_error(status)) return status;
      } // for
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

    return F_okay;
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

#ifndef _di_f_iki_datas_delete_callback_
  f_status_t f_iki_datas_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_iki_data_t * const array = (f_iki_data_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_string_ranges_resize(0, &array[i].content);
        if (F_status_is_error(status)) return status;

        status = f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &array[i].delimits.array, &array[i].delimits.used, &array[i].delimits.size);
        if (F_status_is_error(status)) return status;

        status = f_string_ranges_resize(0, &array[i].variable);
        if (F_status_is_error(status)) return status;

        status = f_string_ranges_resize(0, &array[i].vocabulary);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_okay;
  }
#endif // _di_f_iki_datas_delete_callback_

#ifndef _di_f_iki_datas_destroy_callback_
  f_status_t f_iki_datas_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_iki_data_t * const array = (f_iki_data_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_string_ranges_adjust(0, &array[i].content);
        if (F_status_is_error(status)) return status;

        status = f_memory_array_adjust(0, sizeof(f_number_unsigned_t), (void **) &array[i].delimits.array, &array[i].delimits.used, &array[i].delimits.size);
        if (F_status_is_error(status)) return status;

        status = f_string_ranges_adjust(0, &array[i].variable);
        if (F_status_is_error(status)) return status;

        status = f_string_ranges_adjust(0, &array[i].vocabulary);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_okay;
  }
#endif // _di_f_iki_datas_destroy_callback_

#ifndef _di_f_iki_datass_append_
  f_status_t f_iki_datass_append(const f_iki_datas_t source, f_iki_datass_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_iki_datas_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    status = private_f_iki_datas_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_okay;
  }
#endif // _di_f_iki_datass_append_

#ifndef _di_f_iki_datass_append_all_
  f_status_t f_iki_datass_append_all(const f_iki_datass_t source, f_iki_datass_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_iki_datas_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_iki_datas_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_okay;
  }
#endif // _di_f_iki_datass_append_all_

#ifndef _di_f_iki_datass_delete_callback_
  f_status_t f_iki_datass_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_iki_datas_t * const array = (f_iki_datas_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          status = f_string_ranges_resize(0, &array[i].array[j].content);
          if (F_status_is_error(status)) return status;

          status = f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &array[i].array[j].delimits.array, &array[i].array[j].delimits.used, &array[i].array[j].delimits.size);
          if (F_status_is_error(status)) return status;

          status = f_string_ranges_resize(0, &array[i].array[j].variable);
          if (F_status_is_error(status)) return status;

          status = f_string_ranges_resize(0, &array[i].array[j].vocabulary);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
          status = f_memory_array_resize(0, sizeof(f_iki_data_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_iki_datass_delete_callback_

#ifndef _di_f_iki_datass_destroy_callback_
  f_status_t f_iki_datass_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_iki_datas_t * const array = (f_iki_datas_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          status = f_string_ranges_adjust(0, &array[i].array[j].content);
          if (F_status_is_error(status)) return status;

          status = f_memory_array_adjust(0, sizeof(f_number_unsigned_t), (void **) &array[i].array[j].delimits.array, &array[i].array[j].delimits.used, &array[i].array[j].delimits.size);
          if (F_status_is_error(status)) return status;

          status = f_string_ranges_adjust(0, &array[i].array[j].variable);
          if (F_status_is_error(status)) return status;

          status = f_string_ranges_adjust(0, &array[i].array[j].vocabulary);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
          status = f_memory_array_adjust(0, sizeof(f_iki_data_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_iki_datass_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
