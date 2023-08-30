#include "../utf.h"
#include "../private-utf.h"
#include "private-string.h"
#include "private-triples.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_string_tripless_append_
  f_status_t f_utf_string_tripless_append(const f_utf_string_triples_t source, f_utf_string_tripless_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    {
      f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_utf_string_triples_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;

      destination->array[destination->used].used = 0;

      if (source.used) {
        status = private_f_utf_string_triples_append_all(source, &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    }

    ++destination->used;

    return F_okay;
  }
#endif // _di_f_utf_string_tripless_append_

#ifndef _di_f_utf_string_tripless_append_all_
  f_status_t f_utf_string_tripless_append_all(const f_utf_string_tripless_t source, f_utf_string_tripless_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    {
      f_status_t status = F_okay;

      {
        status = f_memory_array_increase_by(source.used, sizeof(f_utf_string_triples_t), (void **) &destination->array, &destination->used, &destination->size);
        if (F_status_is_error(status)) return status;
      }

      for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

        destination->array[destination->used].used = 0;

        if (source.array[i].used) {
          status = private_f_utf_string_triples_append_all(source.array[i], &destination->array[destination->used]);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_utf_string_tripless_append_all_

#ifndef _di_f_utf_string_tripless_delete_callback_
  f_status_t f_utf_string_tripless_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_utf_string_triples_t * const array = (f_utf_string_triples_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (array[i].size && array[i].array) {
          for (j = 0; j < array[i].size; ++j) {

            if (array[i].array[j].a.size && array[i].array[j].a.string) {
              status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].array[j].a.string, &array[i].array[j].a.used, &array[i].array[j].a.size);
              if (F_status_is_error(status)) return status;
            }

            if (array[i].array[j].b.size && array[i].array[j].b.string) {
              status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].array[j].b.string, &array[i].array[j].b.used, &array[i].array[j].b.size);
              if (F_status_is_error(status)) return status;
            }

            if (array[i].array[j].c.size && array[i].array[j].c.string) {
              status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].array[j].c.string, &array[i].array[j].c.used, &array[i].array[j].c.size);
              if (F_status_is_error(status)) return status;
            }
          } // for

          status = f_memory_array_resize(0, sizeof(f_utf_string_triple_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_utf_string_tripless_delete_callback_

#ifndef _di_f_utf_string_tripless_destroy_callback_
  f_status_t f_utf_string_tripless_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_utf_string_triples_t * const array = (f_utf_string_triples_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (array[i].size && array[i].array) {
          for (j = 0; j < array[i].size; ++j) {

            if (array[i].array[j].a.size && array[i].array[j].a.string) {
              status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].array[j].a.string, &array[i].array[j].a.used, &array[i].array[j].a.size);
              if (F_status_is_error(status)) return status;
            }

            if (array[i].array[j].b.size && array[i].array[j].b.string) {
              status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].array[j].b.string, &array[i].array[j].b.used, &array[i].array[j].b.size);
              if (F_status_is_error(status)) return status;
            }

            if (array[i].array[j].c.size && array[i].array[j].c.string) {
              status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].array[j].c.string, &array[i].array[j].c.used, &array[i].array[j].c.size);
              if (F_status_is_error(status)) return status;
            }
          } // for

          status = f_memory_array_adjust(0, sizeof(f_utf_string_triple_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_utf_string_tripless_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
