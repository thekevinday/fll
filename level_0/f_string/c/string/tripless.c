#include "../string.h"
#include "../private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_string_tripless_append_
  f_status_t f_string_tripless_append(const f_string_triples_t source, f_string_tripless_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    {
      f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_string_ranges_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;

      f_string_triples_t * const destination_inner = &destination->array[destination->used];
      destination_inner->used = 0;

      if (source.used) {
        status = f_memory_array_increase_by(source.used, sizeof(f_string_triple_t), (void **) &destination_inner->array, &destination_inner->used, &destination_inner->size);
        if (F_status_is_error(status)) return status;

        for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination_inner->used) {

          destination_inner->array[destination_inner->used].a.used = 0;
          destination_inner->array[destination_inner->used].b.used = 0;
          destination_inner->array[destination_inner->used].c.used = 0;

          if (source.array[i].a.used) {
            status = private_f_string_append(source.array[i].a.string, source.array[i].a.used, &destination_inner->array[destination_inner->used].a);
            if (F_status_is_error(status)) return status;
          }

          if (source.array[i].b.used) {
            status = private_f_string_append(source.array[i].b.string, source.array[i].b.used, &destination_inner->array[destination_inner->used].b);
            if (F_status_is_error(status)) return status;
          }

          if (source.array[i].c.used) {
            status = private_f_string_append(source.array[i].c.string, source.array[i].c.used, &destination_inner->array[destination_inner->used].c);
            if (F_status_is_error(status)) return status;
          }
        } // for
      }
    }

    ++destination->used;

    return F_okay;
  }
#endif // _di_f_string_tripless_append_

#ifndef _di_f_string_tripless_append_all_
  f_status_t f_string_tripless_append_all(const f_string_tripless_t source, f_string_tripless_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    {
      f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_string_triples_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;

      f_string_triples_t * destination_inner = 0;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

        destination_inner = &destination->array[destination->used];
        destination_inner->used = 0;

        if (source.array[i].used) {
          status = f_memory_array_increase_by(source.array[i].used, sizeof(f_string_triple_t), (void **) &destination_inner->array, &destination_inner->used, &destination_inner->size);
          if (F_status_is_error(status)) return status;

          for (j = 0; j < source.array[i].used; ++j, ++destination_inner->used) {

            destination_inner->array[destination_inner->used].a.used = 0;
            destination_inner->array[destination_inner->used].b.used = 0;
            destination_inner->array[destination_inner->used].c.used = 0;

            if (source.array[i].array[j].a.used) {
              status = private_f_string_append(source.array[i].array[j].a.string, source.array[i].array[j].a.used, &destination_inner->array[destination_inner->used].a);
              if (F_status_is_error(status)) return status;
            }

            if (source.array[i].array[j].b.used) {
              status = private_f_string_append(source.array[i].array[j].b.string, source.array[i].array[j].b.used, &destination_inner->array[destination_inner->used].b);
              if (F_status_is_error(status)) return status;
            }

            if (source.array[i].array[j].c.used) {
              status = private_f_string_append(source.array[i].array[j].c.string, source.array[i].array[j].c.used, &destination_inner->array[destination_inner->used].c);
              if (F_status_is_error(status)) return status;
            }
          } // for
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_string_tripless_append_all_

#ifndef _di_f_string_tripless_delete_callback_
  f_status_t f_string_tripless_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_string_triples_t * const array = (f_string_triples_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (array[i].size) {
          for (j = 0; j < array[i].size; ++j) {

            if (array[i].array[j].a.size) {
              status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].array[j].a.string, &array[i].array[j].a.used, &array[i].array[j].a.size);
              if (F_status_is_error(status)) return status;
            }

            if (array[i].array[j].b.size) {
              status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].array[j].b.string, &array[i].array[j].b.used, &array[i].array[j].b.size);
              if (F_status_is_error(status)) return status;
            }

            if (array[i].array[j].c.size) {
              status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].array[j].c.string, &array[i].array[j].c.used, &array[i].array[j].c.size);
              if (F_status_is_error(status)) return status;
            }
          } // for

          status = f_memory_array_resize(0, sizeof(f_string_triple_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_string_tripless_delete_callback_

#ifndef _di_f_string_tripless_destroy_callback_
  f_status_t f_string_tripless_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_string_triples_t * const array = (f_string_triples_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        if (array[i].size) {
          for (j = 0; j < array[i].size; ++j) {

            if (array[i].array[j].a.size) {
              status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].array[j].a.string, &array[i].array[j].a.used, &array[i].array[j].a.size);
              if (F_status_is_error(status)) return status;
            }

            if (array[i].array[j].b.size) {
              status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].array[j].b.string, &array[i].array[j].b.used, &array[i].array[j].b.size);
              if (F_status_is_error(status)) return status;
            }

            if (array[i].array[j].c.size) {
              status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].array[j].c.string, &array[i].array[j].c.used, &array[i].array[j].c.size);
              if (F_status_is_error(status)) return status;
            }
          } // for

          status = f_memory_array_adjust(0, sizeof(f_string_triple_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_string_tripless_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
