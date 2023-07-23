#include "../string.h"
#include "../private-string.h"
#include "private-dynamic.h"
#include "private-triples.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_string_triples_adjust_) || !defined(_di_f_string_triples_decimate_by_)
  f_status_t private_f_string_triples_adjust(const f_number_unsigned_t length, f_string_triples_t * const structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = f_memory_array_adjust(0, sizeof(f_string_triple_t), (void **) &structure->array[i].a.string, &structure->array[i].a.used, &structure->array[i].a.size);
      if (F_status_is_error(status)) return status;

      status = f_memory_array_adjust(0, sizeof(f_string_triple_t), (void **) &structure->array[i].b.string, &structure->array[i].b.used, &structure->array[i].b.size);
      if (F_status_is_error(status)) return status;

      status = f_memory_array_adjust(0, sizeof(f_string_triple_t), (void **) &structure->array[i].c.string, &structure->array[i].c.used, &structure->array[i].c.size);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_string_triple_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_string_triples_adjust_) || !defined(_di_f_string_triples_decimate_by_)

#if !defined(_di_f_string_triples_append_all_) || !defined(_di_f_string_tripless_append_) || !defined(_di_f_string_tripless_append_all_)
  f_status_t private_f_string_triples_append_all(const f_string_triples_t source, f_string_triples_t * const destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_string_triples_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].a.used = 0;
      destination->array[destination->used].b.used = 0;
      destination->array[destination->used].c.used = 0;

      if (source.array[i].a.used) {
        status = private_f_string_append(source.array[i].a.string, source.array[i].a.used, &destination->array[destination->used].a);
        if (F_status_is_error(status)) return status;
      }

      if (source.array[i].b.used) {
        status = private_f_string_append(source.array[i].b.string, source.array[i].b.used, &destination->array[destination->used].b);
        if (F_status_is_error(status)) return status;
      }

      if (source.array[i].c.used) {
        status = private_f_string_append(source.array[i].c.string, source.array[i].c.used, &destination->array[destination->used].c);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_string_triples_append_all_) || !defined(_di_f_string_tripless_append_) || !defined(_di_f_string_tripless_append_all_)

#if !defined(_di_f_string_triples_decrease_by_) || !defined(_di_f_string_triples_increase_) || !defined(_di_f_string_triples_increase_by_)
  f_status_t private_f_string_triples_resize(const f_number_unsigned_t length, f_string_triples_t * const structure) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = f_memory_array_resize(0, sizeof(f_string_triple_t), (void **) &structure->array[i].a.string, &structure->array[i].a.used, &structure->array[i].a.size);
      if (F_status_is_error(status)) return status;

      status = f_memory_array_resize(0, sizeof(f_string_triple_t), (void **) &structure->array[i].b.string, &structure->array[i].b.used, &structure->array[i].b.size);
      if (F_status_is_error(status)) return status;

      status = f_memory_array_resize(0, sizeof(f_string_triple_t), (void **) &structure->array[i].c.string, &structure->array[i].c.used, &structure->array[i].c.size);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_string_triple_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // !defined(_di_f_string_triples_decrease_by_) || !defined(_di_f_string_triples_increase_) || !defined(_di_f_string_triples_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif
