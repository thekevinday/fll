#include "../string.h"
#include "../private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_string_map_multis_append_
  f_status_t f_string_map_multis_append(const f_string_map_multi_t source, f_string_map_multis_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_string_map_multi_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;

      f_string_map_multi_t * const destination_inner = &destination->array[destination->used];

      destination_inner->key.used = 0;
      destination_inner->value.used = 0;

      if (source.key.used) {
        status = private_f_string_append(source.key.string, source.key.used, &destination_inner->key);
        if (F_status_is_error(status)) return status;
      }

      if (source.value.used) {
        status = f_memory_array_increase_by(source.value.used, sizeof(f_string_dynamic_t), (void **) &destination_inner->value.array, &destination_inner->value.used, &destination_inner->value.size);
        if (F_status_is_error(status)) return status;

        for (f_number_unsigned_t j = 0; j < source.value.used; ++j, ++destination_inner->value.used) {

          destination_inner->value.array[destination_inner->value.used].used = 0;

          if (source.value.array[j].used) {
            status = private_f_string_append(source.value.array[j].string, source.value.array[j].used, &destination_inner->value.array[destination_inner->value.used]);
            if (F_status_is_error(status)) return status;
          }
        } // for
      }
    }

    ++destination->used;

    return F_okay;
  }
#endif // _di_f_string_map_multis_append_

#ifndef _di_f_string_map_multis_append_all_
  f_status_t f_string_map_multis_append_all(const f_string_map_multis_t source, f_string_map_multis_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    {
      f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_string_map_multi_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;

      f_string_map_multi_t * destination_inner = 0;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

        destination_inner = &destination->array[destination->used];
        destination_inner->key.used = 0;
        destination_inner->value.used = 0;

        if (source.array[i].key.used) {
          status = private_f_string_append(source.array[i].key.string, source.array[i].key.used, &destination_inner->key);
          if (F_status_is_error(status)) return status;
        }

        if (source.array[i].value.used) {
          status = f_memory_array_increase_by(source.array[i].value.used, sizeof(f_string_dynamic_t), (void **) &destination_inner->value.array, &destination_inner->value.used, &destination_inner->value.size);
          if (F_status_is_error(status)) return status;

          for (j = 0; j < source.array[i].value.used; ++j, ++destination_inner->value.used) {

            destination_inner->value.array[destination_inner->value.used].used = 0;

            if (source.array[i].value.array[j].used) {
              status = private_f_string_append(source.array[i].value.array[j].string, source.array[i].value.array[j].used, &destination_inner->value.array[destination_inner->value.used]);
              if (F_status_is_error(status)) return status;
            }
          } // for
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_string_map_multis_append_all_

#ifndef _di_f_string_map_multis_delete_callback_
  f_status_t f_string_map_multis_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_string_map_multi_t * const array = (f_string_map_multi_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (array[i].key.size && array[i].key.string) {
          status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].key.string, &array[i].key.used, &array[i].key.size);
          if (F_status_is_error(status)) return status;
        }

        if (array[i].value.size && array[i].value.array) {
          for (j = 0; j < array[i].value.size; ++j) {

            if (array[i].value.array[j].size && array[i].value.array[j].string) {
              status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].value.array[j].string, &array[i].value.array[j].used, &array[i].value.array[j].size);
              if (F_status_is_error(status)) return status;
            }
          } // for

          status = f_memory_array_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].value.array, &array[i].value.used, &array[i].value.size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_string_map_multis_delete_callback_

#ifndef _di_f_string_map_multis_destroy_callback_
  f_status_t f_string_map_multis_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_string_map_multi_t * const array = (f_string_map_multi_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (array[i].key.size && array[i].key.string) {
          status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].key.string, &array[i].key.used, &array[i].key.size);
          if (F_status_is_error(status)) return status;
        }

        if (array[i].value.size && array[i].value.array) {
          for (j = 0; j < array[i].value.size; ++j) {

            if (array[i].value.array[j].size && array[i].value.array[j].string) {
              status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].value.array[j].string, &array[i].value.array[j].used, &array[i].value.array[j].size);
              if (F_status_is_error(status)) return status;
            }
          } // for

          status = f_memory_array_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].value.array, &array[i].value.used, &array[i].value.size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_string_map_multis_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
