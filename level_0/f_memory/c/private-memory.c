#include "memory.h"
#include "private-memory.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_memory_adjust_) || !defined(_di_f_memory_structure_adjust_) || !defined(_di_f_memory_structure_decimate_by_)
  f_status_t private_f_memory_adjust(const size_t length_old, const size_t length_new, const size_t type_size, void ** const pointer) {

    // When old length is 0 and the pointer is not NULL, then consider this pointer stale and reset it to NULL.
    if (!length_old && *pointer) {
      *pointer = 0;
    }

    if (*pointer) {
      if (length_old) {
        if (length_new < length_old) {

          // uint8_t * is of a data size size of 1, casting it to uint8_t should result in a single-length increment.
          // This is done to avoid problems with (void *) having arithmetic issues.
          memset(((uint8_t *) *pointer) + length_new, 0, type_size * (length_old - length_new));
        }
      }

      if (length_new) {
        void * const new_pointer = realloc(*pointer, type_size * length_new);

        if (new_pointer) {
          if (length_new > length_old) {

            // uint8_t * is of a data size size of 1, casting it to bool should result in a single-length increment.
            // This is done to avoid problems with (void *) having arithmetic issues.
            memset(((uint8_t *) new_pointer) + (type_size * length_old), 0, type_size * (length_new - length_old));
          }

          *pointer = new_pointer;

          return F_none;
        }
      }
      else {
        free(*pointer);

        // Assure that the pointer is always 0 after deallocation.
        *pointer = 0;

        return F_none;
      }
    }
    else if (length_new) {
      *pointer = calloc(type_size, length_new);
      if (*pointer) return F_none;
    }
    else {
      return F_data_not;
    }

    return F_status_set_error(F_memory_not);
  }
#endif // !defined(_di_f_memory_adjust_) || !defined(_di_f_memory_structure_adjust_) || !defined(_di_f_memory_structure_decimate_by_)

#if !defined(_di_f_memory_resize_) || !defined(_di_memory_structure_decrease_by_) || !defined(_di_memory_structure_increase_) || !defined(_di_memory_structure_increase_by_) || !defined(_di_f_memory_structure_resize_)
  f_status_t private_f_memory_resize(const size_t length_old, const size_t length_new, const size_t type_size, void ** const pointer) {

    // When old length is 0 and the pointer is not NULL, then consider this pointer stale and reset it to NULL.
    if (!length_old && *pointer) {
      *pointer = 0;
    }

    if (*pointer) {
      if (length_new) {
        void * const new_pointer = realloc(*pointer, type_size * length_new);

        if (new_pointer) {
          if (length_new > length_old) {

            // uint8_t * is of a data size size of 1, casting it to bool should result in a single-length increment.
            // This is done to avoid problems with (void *) having arithmetic issues.
            memset(((uint8_t *) new_pointer) + (type_size * length_old), 0, type_size * (length_new - length_old));
          }

          *pointer = new_pointer;

          return F_none;
        }
      }
      else {
        free(*pointer);

        // Assure that the pointer is always 0 after deallocation.
        *pointer = 0;

        return F_none;
      }
    }
    else if (length_new) {
      *pointer = calloc(type_size, length_new);
      if (*pointer) return F_none;
    }
    else {
      return F_data_not;
    }

    return F_status_set_error(F_memory_not);
  }
#endif // !defined(_di_f_memory_resize_) || !defined(_di_memory_structure_decrease_by_) || !defined(_di_memory_structure_increase_) || !defined(_di_memory_structure_increase_by_) || !defined(_di_f_memory_structure_resize_)

#if !defined(_di_f_memory_structure_adjust_) || !defined(_di_f_memory_structure_decimate_by_)
  f_status_t private_f_memory_structure_adjust(const size_t length_new, const size_t type_size, void ** const structure, f_number_unsigned_t * const used, f_number_unsigned_t * const size) {

    const f_status_t status = private_f_memory_adjust(*size, length_new, type_size, structure);

    if (F_status_is_error_not(status)) {
      *size = length_new;

      if (*used > *size) {
        *used = *size;
      }
    }

    return status;
  }
#endif // !defined(_di_f_memory_structure_adjust_) || !defined(_di_f_memory_structure_decimate_by_)

#if !defined(_di_memory_structure_decrease_by_) || !defined(_di_memory_structure_increase_) || !defined(_di_memory_structure_increase_by_) || !defined(_di_f_memory_structure_resize_)
  f_status_t private_f_memory_structure_resize(const size_t length_new, const size_t type_size, void ** const structure, f_number_unsigned_t * const used, f_number_unsigned_t * const size) {

    const f_status_t status = private_f_memory_resize(*size, length_new, type_size, structure);

    if (F_status_is_error_not(status)) {
      *size = length_new;

      if (*used > *size) {
        *used = *size;
      }
    }

    return status;
  }
#endif // !defined(_di_memory_structure_decrease_by_) || !defined(_di_memory_structure_increase_) || !defined(_di_memory_structure_increase_by_) || !defined(_di_f_memory_structure_resize_)

#ifdef __cplusplus
} // extern "C"
#endif
