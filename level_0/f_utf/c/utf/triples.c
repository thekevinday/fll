#include "../utf.h"
#include "../private-utf.h"
#include "private-string.h"
#include "private-triples.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_string_triples_append_
  f_status_t f_utf_string_triples_append(const f_utf_string_triple_t source, f_utf_string_triples_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_utf_string_triple_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;

      destination->array[destination->used].a.used = 0;
      destination->array[destination->used].b.used = 0;
      destination->array[destination->used].c.used = 0;

      if (source.a.used) {
        status = private_f_utf_string_append(source.a.string, source.a.used, &destination->array[destination->used].a);
        if (F_status_is_error(status)) return status;
      }

      if (source.b.used) {
        status = private_f_utf_string_append(source.b.string, source.b.used, &destination->array[destination->used].b);
        if (F_status_is_error(status)) return status;
      }

      if (source.c.used) {
        status = private_f_utf_string_append(source.c.string, source.c.used, &destination->array[destination->used].c);
        if (F_status_is_error(status)) return status;
      }
    }

    ++destination->used;

    return F_okay;
  }
#endif // _di_f_utf_string_triples_append_

#ifndef _di_f_utf_string_triples_append_all_
  f_status_t f_utf_string_triples_append_all(const f_utf_string_triples_t source, f_utf_string_triples_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    {
      f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_utf_string_triple_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;

      for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

        destination->array[destination->used].a.used = 0;
        destination->array[destination->used].b.used = 0;
        destination->array[destination->used].c.used = 0;

        if (source.array[i].a.used) {
          status = private_f_utf_string_append(source.array[i].a.string, source.array[i].a.used, &destination->array[destination->used].a);
          if (F_status_is_error(status)) return status;
        }

        if (source.array[i].b.used) {
          status = private_f_utf_string_append(source.array[i].b.string, source.array[i].b.used, &destination->array[destination->used].b);
          if (F_status_is_error(status)) return status;
        }

        if (source.array[i].c.used) {
          status = private_f_utf_string_append(source.array[i].c.string, source.array[i].c.used, &destination->array[destination->used].c);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_utf_string_triples_append_all_

#ifndef _di_f_utf_string_triples_delete_callback_
  f_status_t f_utf_string_triples_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_utf_string_triple_t * const array = (f_utf_string_triple_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (array[i].a.size && array[i].a.string) {
          status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].a.string, &array[i].a.used, &array[i].a.size);
          if (F_status_is_error(status)) return status;
        }

        if (array[i].b.size && array[i].b.string) {
          status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].b.string, &array[i].b.used, &array[i].b.size);
          if (F_status_is_error(status)) return status;
        }

        if (array[i].c.size && array[i].c.string) {
          status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].c.string, &array[i].c.used, &array[i].c.size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_utf_string_triples_delete_callback_

#ifndef _di_f_utf_string_triples_destroy_callback_
  f_status_t f_utf_string_triples_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_utf_string_triple_t * const array = (f_utf_string_triple_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (array[i].a.size && array[i].a.string) {
          status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].a.string, &array[i].a.used, &array[i].a.size);
          if (F_status_is_error(status)) return status;
        }

        if (array[i].b.size && array[i].b.string) {
          status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].b.string, &array[i].b.used, &array[i].b.size);
          if (F_status_is_error(status)) return status;
        }

        if (array[i].c.size && array[i].c.string) {
          status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].c.string, &array[i].c.used, &array[i].c.size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_utf_string_triples_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
