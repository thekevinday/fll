#include "memory.h"
#include "private-memory.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_memory_adjust_) || defined(_f_memory_FORCE_secure_memory_)
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
          memset((void *) (((uint8_t *) *pointer) + length_new), 0, type_size * (length_old - length_new));
        }
      }

      if (length_new) {
        void * const new_pointer = realloc(*pointer, type_size * length_new);

        if (new_pointer) {
          if (length_new > length_old) {

            // uint8_t * is of a data size size of 1, casting it to bool should result in a single-length increment.
            // This is done to avoid problems with (void *) having arithmetic issues.
            memset((void *) (((uint8_t *) new_pointer) + (type_size * length_old)), 0, type_size * (length_new - length_old));
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
#endif // !defined(_di_f_memory_adjust_) || defined(_f_memory_FORCE_secure_memory_)

#if !defined(_di_f_memory_resize_) || defined(_f_memory_FORCE_fast_memory_)
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
            memset((void *) (((uint8_t *) new_pointer) + (type_size * length_old)), 0, type_size * (length_new - length_old));
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
#endif // !!defined(_di_f_memory_resize_) || defined(_f_memory_FORCE_fast_memory_)

#ifdef __cplusplus
} // extern "C"
#endif
