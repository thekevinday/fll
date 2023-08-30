#include "../utf.h"
#include "../private-utf.h"
#include "private-maps.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_string_maps_append_
  f_status_t f_utf_string_maps_append(const f_utf_string_map_t source, f_utf_string_maps_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_utf_string_map_t), (void **) &destination->array, &destination->used, &destination->size);

      destination->array[destination->used].name.used = 0;
      destination->array[destination->used].value.used = 0;

      if (source.name.used) {
        status = private_f_utf_string_append(source.name.string, source.name.used, &destination->array[destination->used].name);
        if (F_status_is_error(status)) return status;
      }

      if (source.value.used) {
        status = private_f_utf_string_append(source.value.string, source.value.used, &destination->array[destination->used].value);
        if (F_status_is_error(status)) return status;
      }
    }

    ++destination->used;

    return F_okay;
  }
#endif // _di_f_utf_string_maps_append_

#ifndef _di_f_utf_string_maps_append_all_
  f_status_t f_utf_string_maps_append_all(const f_utf_string_maps_t source, f_utf_string_maps_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_utf_string_maps_append_all(source, destination);
  }
#endif // _di_f_utf_string_maps_append_all_

#ifndef _di_f_utf_string_maps_delete_callback_
  f_status_t f_utf_string_maps_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_utf_string_map_t * const array = (f_utf_string_map_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (array[i].name.size && array[i].name.string) {
          status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].name.string, &array[i].name.used, &array[i].name.size);
          if (F_status_is_error(status)) return status;
        }

        if (array[i].value.size && array[i].value.string) {
          status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].value.string, &array[i].value.used, &array[i].value.size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_utf_string_maps_delete_callback_

#ifndef _di_f_utf_string_maps_destroy_callback_
  f_status_t f_utf_string_maps_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_utf_string_map_t * const array = (f_utf_string_map_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (array[i].name.size && array[i].name.string) {
          status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].name.string, &array[i].name.used, &array[i].name.size);
          if (F_status_is_error(status)) return status;
        }

        if (array[i].value.size && array[i].value.string) {
          status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].value.string, &array[i].value.used, &array[i].value.size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_utf_string_maps_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
