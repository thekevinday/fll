#include "../utf.h"
#include "../private-utf.h"
#include "private-triples.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_string_triples_append_all_) || !defined(_di_f_utf_string_tripless_append_) || !defined(_di_f_utf_string_tripless_append_all_)
  f_status_t private_f_utf_string_triples_append_all(const f_utf_string_triples_t source, f_utf_string_triples_t * const destination) {

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
#endif // !defined(_di_f_utf_string_triples_append_all_) || !defined(_di_f_utf_string_tripless_append_) || !defined(_di_f_utf_string_tripless_append_all_)

#ifdef __cplusplus
} // extern "C"
#endif
