#include "../iki.h"
#include "private-data.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_iki_datas_append_) || !defined(_di_f_iki_datas_append_all_) || !defined(_di_f_iki_datass_append_all_)
  extern f_status_t private_f_iki_datas_append_all(const f_iki_datas_t source, f_iki_datas_t *destination) {

    f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_iki_data_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    {
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

        destination->array[destination->used].content.used = 0;
        destination->array[destination->used].delimits.used = 0;
        destination->array[destination->used].variable.used = 0;
        destination->array[destination->used].vocabulary.used = 0;

        if (source.array[i].content.used) {
          status = f_string_ranges_append_all(source.array[i].content, &destination->array[destination->used].content);
          if (F_status_is_error(status)) return status;
        }

        for (j = 0; j < source.array[i].delimits.used; ++j) {

          status = f_memory_array_append(source.array[i].delimits.array + j, sizeof(f_number_unsigned_t), (void **) &destination->array[destination->used].delimits.array, &destination->array[destination->used].delimits.used, &destination->array[destination->used].delimits.size);
          if (F_status_is_error(status)) return status;
        } // for

        if (source.array[i].variable.used) {
          status = f_string_ranges_append_all(source.array[i].variable, &destination->array[destination->used].variable);
          if (F_status_is_error(status)) return status;
        }

        if (source.array[i].vocabulary.used) {
          status = f_string_ranges_append_all(source.array[i].vocabulary, &destination->array[destination->used].vocabulary);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // !defined(_di_f_iki_datas_append_) || !defined(_di_f_iki_datas_append_all_) || !defined(_di_f_iki_datass_append_all_)

#ifdef __cplusplus
} // extern "C"
#endif
