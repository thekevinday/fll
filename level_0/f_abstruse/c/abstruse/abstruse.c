#include "../abstruse.h"
#include "private-abstruse.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_abstruses_delete_callback_
  f_status_t f_abstruses_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_abstruse_t * const array = (f_abstruse_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = private_f_abstruses_delete_switch(&array[i]);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_okay;
  }
#endif // _di_f_abstruses_delete_callback_

#ifndef _di_f_abstruses_destroy_callback_
  f_status_t f_abstruses_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_abstruse_t * const array = (f_abstruse_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = private_f_abstruses_destroy_switch(&array[i]);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_okay;
  }
#endif // _di_f_abstruses_destroy_callback_

#ifndef _di_f_abstrusess_delete_callback_
  f_status_t f_abstrusess_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_abstruses_t * const array = (f_abstruses_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t i = start;
      f_number_unsigned_t j = 0;

      for (; i < stop; ++i) {

        if (array[i].size) {
          for (j = 0; j < array[i].size; ++j) {

            status = private_f_abstruses_delete_switch(&array[i].array[j]);
            if (F_status_is_error(status)) return status;
          } // for

          status = f_memory_array_resize(0, sizeof(f_abstruse_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_abstrusess_delete_callback_

#ifndef _di_f_abstrusess_destroy_callback_
  f_status_t f_abstrusess_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_abstruses_t * const array = (f_abstruses_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t i = start;
      f_number_unsigned_t j = 0;

      for (; i < stop; ++i) {

        if (array[i].size) {
          for (j = 0; j < array[i].size; ++j) {

            status = private_f_abstruses_destroy_switch(&array[i].array[j]);
            if (F_status_is_error(status)) return status;
          } // for

          status = f_memory_array_adjust(0, sizeof(f_abstruse_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_abstrusess_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
