#include "../fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_fss_set_delete_
  f_status_t f_fss_set_delete(f_fss_set_t * const set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      f_status_t status = F_okay;

      if (set->objects.size && set->objects.array) {
        status = f_memory_array_resize(0, sizeof(f_string_range_t), (void **) &set->objects.array, &set->objects.used, &set->objects.size);
        if (F_status_is_error(status)) return status;
      }

      if (set->contents.size && set->contents.array) {
        status = f_memory_arrays_resize(0, sizeof(f_string_ranges_t), (void **) &set->contents.array, &set->contents.used, &set->contents.size, &f_string_rangess_delete_callback);
        if (F_status_is_error(status)) return status;
      }
    }

    return F_okay;
  }
#endif // _di_f_fss_set_delete_

#ifndef _di_f_fss_set_destroy_
  f_status_t f_fss_set_destroy(f_fss_set_t * const set) {
    #ifndef _di_level_0_parameter_checking_
      if (!set) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      f_status_t status = F_okay;

      if (set->objects.size && set->objects.array) {
        status = f_memory_array_adjust(0, sizeof(f_string_range_t), (void **) &set->objects.array, &set->objects.used, &set->objects.size);
        if (F_status_is_error(status)) return status;
      }

      if (set->contents.size && set->contents.array) {
        status = f_memory_arrays_adjust(0, sizeof(f_string_ranges_t), (void **) &set->contents.array, &set->contents.used, &set->contents.size, &f_string_rangess_destroy_callback);
        if (F_status_is_error(status)) return status;
      }
    }

    return F_okay;
  }
#endif // _di_f_fss_set_destroy_

#ifndef _di_f_fss_sets_delete_callback_
  f_status_t f_fss_sets_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_set_t * const array = (f_fss_set_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (array[i].objects.size && array[i].objects.array) {
          status = f_memory_array_resize(0, sizeof(f_string_range_t), (void **) &array[i].objects.array, &array[i].objects.used, &array[i].objects.size);
          if (F_status_is_error(status)) return status;
        }

        if (array[i].contents.size && array[i].contents.array) {
          status = f_memory_arrays_resize(0, sizeof(f_string_ranges_t), (void **) &array[i].contents.array, &array[i].contents.used, &array[i].contents.size, &f_string_rangess_delete_callback);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_sets_delete_callback_

#ifndef _di_f_fss_sets_destroy_callback_
  f_status_t f_fss_sets_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_set_t * const array = (f_fss_set_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (array[i].objects.size && array[i].objects.array) {
          status = f_memory_array_adjust(0, sizeof(f_string_range_t), (void **) &array[i].objects.array, &array[i].objects.used, &array[i].objects.size);
          if (F_status_is_error(status)) return status;
        }

        if (array[i].contents.size && array[i].contents.array) {
          status = f_memory_arrays_adjust(0, sizeof(f_string_ranges_t), (void **) &array[i].contents.array, &array[i].contents.used, &array[i].contents.size, &f_string_rangess_destroy_callback);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_sets_destroy_callback_

#ifndef _di_f_fss_setss_delete_callback_
  f_status_t f_fss_setss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_sets_t * const array = (f_fss_sets_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          if (array[i].array[j].objects.size && array[i].array[j].objects.array) {
            status = f_memory_array_resize(0, sizeof(f_string_range_t), (void **) &array[i].array[j].objects.array, &array[i].array[j].objects.used, &array[i].array[j].objects.size);
            if (F_status_is_error(status)) return status;
          }

          if (array[i].array[j].contents.size && array[i].array[j].contents.array) {
            status = f_memory_arrays_resize(0, sizeof(f_string_ranges_t), (void **) &array[i].array[j].contents.array, &array[i].array[j].contents.used, &array[i].array[j].contents.size, &f_string_rangess_delete_callback);
            if (F_status_is_error(status)) return status;
          }
        } // for

        if (array[i].size && array[i].array) {
          status = f_memory_array_resize(0, sizeof(f_fss_set_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_setss_delete_callback_

#ifndef _di_f_fss_setss_destroy_callback_
  f_status_t f_fss_setss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_sets_t * const array = (f_fss_sets_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          if (array[i].array[j].objects.size && array[i].array[j].objects.array) {
            status = f_memory_array_adjust(0, sizeof(f_string_range_t), (void **) &array[i].array[j].objects.array, &array[i].array[j].objects.used, &array[i].array[j].objects.size);
            if (F_status_is_error(status)) return status;
          }

          if (array[i].array[j].contents.size && array[i].array[j].contents.array) {
            status = f_memory_arrays_adjust(0, sizeof(f_string_ranges_t), (void **) &array[i].array[j].contents.array, &array[i].array[j].contents.used, &array[i].array[j].contents.size, &f_string_rangess_destroy_callback);
            if (F_status_is_error(status)) return status;
          }
        } // for

        if (array[i].size && array[i].array) {
          status = f_memory_array_adjust(0, sizeof(f_fss_set_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_setss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
