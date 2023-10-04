#include "../abstruse.h"
#include "private-abstruse.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_abstruse_maps_delete_callback_
  f_status_t f_abstruse_maps_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_abstruse_map_t * const array = (f_abstruse_map_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].key.string, &array[i].key.used, &array[i].key.size);
        if (F_status_is_error(status)) return status;

        status = private_f_abstruses_delete_switch(&array[i].value);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_okay;
  }
#endif // _di_f_abstruse_maps_delete_callback_

#ifndef _di_f_abstruse_maps_destroy_callback_
  f_status_t f_abstruse_maps_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_abstruse_map_t * const array = (f_abstruse_map_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].key.string, &array[i].key.used, &array[i].key.size);
        if (F_status_is_error(status)) return status;

        status = private_f_abstruses_destroy_switch(&array[i].value);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_okay;
  }
#endif // _di_f_abstruse_maps_destroy_callback_

#ifndef _di_f_abstruse_mapss_delete_callback_
  f_status_t f_abstruse_mapss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_abstruse_maps_t * const array = (f_abstruse_maps_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t i = start;
      f_number_unsigned_t j = 0;

      for (; i < stop; ++i) {

        if (array[i].size) {
          for (j = 0; j < array[i].size; ++j) {

            status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].array[j].key.string, &array[i].array[j].key.used, &array[i].array[j].key.size);
            if (F_status_is_error(status)) return status;

            status = private_f_abstruses_delete_switch(&array[i].array[j].value);
            if (F_status_is_error(status)) return status;
          } // for

          status = f_memory_array_resize(0, sizeof(f_abstruse_map_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_abstruse_mapss_delete_callback_

#ifndef _di_f_abstruse_mapss_destroy_callback_
  f_status_t f_abstruse_mapss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_abstruse_maps_t * const array = (f_abstruse_maps_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t i = start;
      f_number_unsigned_t j = 0;

      for (; i < stop; ++i) {

        if (array[i].size) {
          for (j = 0; j < array[i].size; ++j) {

            status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].array[j].key.string, &array[i].array[j].key.used, &array[i].array[j].key.size);
            if (F_status_is_error(status)) return status;

            status = private_f_abstruses_destroy_switch(&array[i].array[j].value);
            if (F_status_is_error(status)) return status;
          } // for

          status = f_memory_array_adjust(0, sizeof(f_abstruse_map_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_abstruse_mapss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
