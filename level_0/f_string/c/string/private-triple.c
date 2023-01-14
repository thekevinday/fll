#include "../string.h"
#include "../private-string.h"
#include "private-dynamic.h"
#include "private-triple.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_string_triples_adjust_) || !defined(_di_f_string_triples_decimate_by_)
  f_status_t private_f_string_triples_adjust(const f_array_length_t length, f_string_triples_t * const triples) {

    if (triples->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < triples->size; ++i) {

      status = private_f_string_dynamic_adjust(0, &triples->array[i].a);
      if (F_status_is_error(status)) return status;

      status = private_f_string_dynamic_adjust(0, &triples->array[i].b);
      if (F_status_is_error(status)) return status;

      status = private_f_string_dynamic_adjust(0, &triples->array[i].c);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(triples->size, length, sizeof(f_string_triple_t), (void **) & triples->array);
    if (F_status_is_error(status)) return status;

    triples->size = length;

    if (triples->used > triples->size) {
      triples->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_triples_adjust_) || !defined(_di_f_string_triples_decimate_by_)

#if !defined(_di_f_string_triples_append_all_) || !defined(_di_f_string_tripless_append_) || !defined(_di_f_string_tripless_append_all_)
  f_status_t private_f_string_triples_append_all(const f_string_triples_t source, f_string_triples_t * const destination) {

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_string_triples_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {

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
  f_status_t private_f_string_triples_resize(const f_array_length_t length, f_string_triples_t * const triples) {

    if (triples->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < triples->size; ++i) {

      status = private_f_string_dynamic_resize(0, &triples->array[i].a);
      if (F_status_is_error(status)) return status;

      status = private_f_string_dynamic_resize(0, &triples->array[i].b);
      if (F_status_is_error(status)) return status;

      status = private_f_string_dynamic_resize(0, &triples->array[i].c);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(triples->size, length, sizeof(f_string_triple_t), (void **) & triples->array);
    if (F_status_is_error(status)) return status;

    triples->size = length;

    if (triples->used > triples->size) {
      triples->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_triples_decrease_by_) || !defined(_di_f_string_triples_increase_) || !defined(_di_f_string_triples_increase_by_)

#if !defined(_di_f_string_tripless_adjust_) || !defined(_di_f_string_tripless_decimate_by_)
  f_status_t private_f_string_tripless_adjust(const f_array_length_t length, f_string_tripless_t * const tripless) {

    if (tripless->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < tripless->size; ++i) {

      status = private_f_string_triples_adjust(0, &tripless->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust(tripless->size, length, sizeof(f_string_triples_t), (void **) & tripless->array);
    if (F_status_is_error(status)) return status;

    tripless->size = length;

    if (tripless->used > tripless->size) {
      tripless->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_tripless_adjust_) || !defined(_di_f_string_tripless_decimate_by_)

#if !defined(_di_f_string_tripless_decrease_by_) || !defined(_di_f_string_tripless_increase_) || !defined(_di_f_string_tripless_increase_by_)
  f_status_t private_f_string_tripless_resize(const f_array_length_t length, f_string_tripless_t * const tripless) {

    if (tripless->used + length > F_array_length_t_size_d) {
      return F_status_set_error(F_array_too_large);
    }

    f_status_t status = F_none;

    for (f_array_length_t i = length; i < tripless->size; ++i) {

      status = private_f_string_triples_resize(0, &tripless->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize(tripless->size, length, sizeof(f_string_triples_t), (void **) & tripless->array);
    if (F_status_is_error(status)) return status;

    tripless->size = length;

    if (tripless->used > tripless->size) {
      tripless->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_tripless_decrease_by_) || !defined(_di_f_string_tripless_increase_) || !defined(_di_f_string_tripless_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif
