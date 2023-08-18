#include "../fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_fss_item_delete_
  f_status_t f_fss_item_delete(f_fss_item_t * const item) {
    #ifndef _di_level_0_parameter_checking_
      if (!item) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_string_ranges_resize(0, &item->content);
  }
#endif // _di_f_fss_item_delete_

#ifndef _di_f_fss_item_destroy_
  f_status_t f_fss_item_destroy(f_fss_item_t * const item) {
    #ifndef _di_level_0_parameter_checking_
      if (!item) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    item->object.start = 1;
    item->object.stop = 0;
    item->parent = 0;

    return f_string_ranges_adjust(0, &item->content);
  }
#endif // _di_f_fss_item_destroy_

#ifndef _di_f_fss_items_delete_callback_
  f_status_t f_fss_items_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_item_t * const array = (f_fss_item_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_string_ranges_resize(0, &array[i].content);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_items_delete_callback_

#ifndef _di_f_fss_items_destroy_callback_
  f_status_t f_fss_items_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_item_t * const array = (f_fss_item_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        array[i].object.start = 1;
        array[i].object.stop = 0;
        array[i].parent = 0;

        status = f_string_ranges_adjust(0, &array[i].content);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_items_destroy_callback_

#ifndef _di_f_fss_itemss_delete_callback_
  f_status_t f_fss_itemss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_items_t * const array = (f_fss_items_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          status = f_string_ranges_resize(0, &array[i].array[j].content);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
          status = f_memory_array_resize(0, sizeof(f_fss_item_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_itemss_delete_callback_

#ifndef _di_f_fss_itemss_destroy_callback_
  f_status_t f_fss_itemss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_items_t * const array = (f_fss_items_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          array[i].array[j].object.start = 1;
          array[i].array[j].object.stop = 0;
          array[i].array[j].parent = 0;

          status = f_string_ranges_adjust(0, &array[i].array[j].content);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
          status = f_memory_array_adjust(0, sizeof(f_fss_item_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_itemss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
