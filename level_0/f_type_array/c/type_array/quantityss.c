#include "../type_array.h"
#include "quantityss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_quantityss_append_
  f_status_t f_quantityss_append(const f_quantitys_t source, f_quantityss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    {
      f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_quantitys_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;

      f_quantitys_t * const destination_inner = &destination->array[destination->used];
      destination_inner->used = 0;

      if (source.used) {
        status = f_memory_array_increase_by(source.used, sizeof(f_quantity_t), (void **) &destination_inner->array, &destination_inner->used, &destination_inner->size);
        if (F_status_is_error(status)) return status;

        for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination_inner->used) {

          destination_inner->array[destination_inner->used].start = source.array[i].start;
          destination_inner->array[destination_inner->used].total = source.array[i].total;
        } // for
      }
    }

    ++destination->used;

    return F_okay;
  }
#endif // _di_f_quantityss_append_

#ifndef _di_f_quantityss_append_all_
  f_status_t f_quantityss_append_all(const f_quantityss_t source, f_quantityss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    {
      f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_quantitys_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;

      f_quantitys_t * destination_inner = 0;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

        destination_inner = &destination->array[destination->used];
        destination_inner->used = 0;

        if (source.array[i].used) {
          status = f_memory_array_increase_by(source.array[i].used, sizeof(f_quantity_t), (void **) &destination->array[destination->used].array, &destination->array[destination->used].used, &destination->array[destination->used].size);
          if (F_status_is_error(status)) return status;

          for (j = 0; j < source.array[i].used; ++j, ++destination_inner->used) {

            destination_inner->array[destination_inner->used].start = source.array[i].array[j].start;
            destination_inner->array[destination_inner->used].total = source.array[i].array[j].total;
          } // for
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_quantityss_append_all_

#ifndef _di_f_quantityss_delete_callback_
  f_status_t f_quantityss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_quantitys_t * const array = (f_quantitys_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (array[i].size && array[i].array) {
          status = f_memory_array_resize(0, sizeof(f_quantity_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_quantityss_delete_callback_

#ifndef _di_f_quantityss_destroy_callback_
  f_status_t f_quantityss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_quantitys_t * const array = (f_quantitys_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (array[i].size && array[i].array) {
          status = f_memory_array_adjust(0, sizeof(f_quantity_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_quantityss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif