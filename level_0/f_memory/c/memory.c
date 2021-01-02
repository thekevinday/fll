#include "memory.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_memory_new_
  f_return_status f_memory_new(void **pointer, const size_t size, const size_t length) {
    #ifndef _di_level_0_parameter_checking_
      if (size <= 0) return F_status_set_error(F_parameter);
      if (length <= 0) return F_status_set_error(F_parameter);
      if (!pointer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    // prevent double-allocations.
    if (*pointer || length == 0) return F_none;

    // Some people use malloc(size * length) to produce the same results.
    // This has been observed to sometimes causes an increase in L1/L2 cache misses (0.02% L1 increase, 0.01% L2 increase).
    *pointer = calloc(length, size);

    if (*pointer) {

      // uint8_t * is of a data size size of 1, casting it to uint8_t should result in a single-length increment.
      // this is done to avoid problems with (void *) having arithmetic issues.
      memset(((uint8_t *) *pointer), 0, size * length);

      return F_none;
    }

    return F_status_set_error(F_memory_allocation);
  }
#endif // _di_f_memory_new_

#ifndef _di_f_memory_new_aligned_
  f_return_status f_memory_new_aligned(void **pointer, const size_t alignment, const size_t length) {
    #ifndef _di_level_0_parameter_checking_
      if (alignment <= 0) return F_status_set_error(F_parameter);
      if (length <= 0) return F_status_set_error(F_parameter);
      if (!pointer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    // prevent double-allocations.
    if (*pointer || length == 0) return F_none;

    const int result = posix_memalign(pointer, alignment, length);

    if (result) {
      if (result == EINVAL) return F_status_set_error(F_parameter);

      return F_status_set_error(F_memory_allocation);
    }

    // uint8_t * is of a data size size of 1, casting it to uint8_t should result in a single-length increment.
    // this is done to avoid problems with (void *) having arithmetic issues.
    memset(((uint8_t *) *pointer), 0, length);

    return F_none;
  }
#endif // _di_f_memory_new_aligned_

#if !(defined(_di_f_memory_delete_) || defined(_f_memory_FORCE_secure_memory_))
  f_return_status f_memory_delete(void **pointer, const size_t size, const size_t length) {
    #ifndef _di_level_0_parameter_checking_
      if (!pointer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    // prevent double-frees.
    if (!*pointer || !size || !length) return F_none;

    free(*pointer);

    // it has been deallocated, so reset the pointer.
    *pointer = 0;

    return F_none;
  }
#endif // !(defined(_di_f_memory_delete_) || defined(_f_memory_FORCE_secure_memory_))

#if !(defined(_di_f_memory_destroy_) || defined(_f_memory_FORCE_fast_memory_))
  f_return_status f_memory_destroy(void **pointer, const size_t size, const size_t length) {
    #ifndef _di_level_0_parameter_checking_
      if (length < 0) return F_status_set_error(F_parameter);
      if (size <= 0) return F_status_set_error(F_parameter);
      if (!pointer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    // prevent double-frees.
    if (!*pointer || !length) return F_none;

    if (length > 0) {
      memset(*pointer, 0, size * length);
    }

    free(*pointer);

    // it has been deallocated, so reset the pointer.
    *pointer = 0;

    return F_none;
  }
#endif // !(defined(_di_f_memory_destroy_) || defined(_f_memory_FORCE_fast_memory_))

#if !(defined(_di_f_memory_resize_) || defined(_f_memory_FORCE_secure_memory_))
  f_return_status f_memory_resize(void **pointer, const size_t size, const size_t old_length, const size_t new_length) {
    #ifndef _di_level_0_parameter_checking_
      if (size <= 0) return F_status_set_error(F_parameter);
      if (old_length < 0) return F_status_set_error(F_parameter);
      if (new_length < 0) return F_status_set_error(F_parameter);
      if (!pointer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    // don't be wasteful.
    if (old_length == new_length) return F_none;

    if (*pointer) {
      void *new_pointer = 0;

      // allocate new space
      if (new_length > 0) {
        new_pointer = realloc(*pointer, size * new_length);
      }
      else {
        free(*pointer);

        // it has been deallocated, so reset the pointer
        *pointer = 0;

        return F_none;
      }

      if (new_pointer) {
        if (new_pointer != *pointer) {
          if (new_length > old_length) {
            // uint8_t * is of a data size size of 1, casting it to uint8_t should result in a single-length increment.
            // this is done to avoid problems with (void *) having arithmetic issues.
            memset(((uint8_t *) new_pointer) + (size * old_length), 0, size * (new_length - old_length));
          }

          *pointer = new_pointer;
        }

        return F_none;
      }
    }
    else if (new_length > 0) {
      *pointer = calloc(size, new_length);

      if (*pointer) {
        return F_none;
      }
    }
    else {
      return F_none;
    }

    return F_status_set_error(F_memory_reallocation);
  }
#endif // !(defined(_di_f_memory_resize_) || defined(_f_memory_FORCE_secure_memory_))

#if !(defined(_di_f_memory_adjust_) || defined(_f_memory_FORCE_fast_memory_))
  f_return_status f_memory_adjust(void **pointer, const size_t size, const size_t old_length, const size_t new_length) {
    #ifndef _di_level_0_parameter_checking_
      if (size <= 0) return F_status_set_error(F_parameter);
      if (old_length < 0) return F_status_set_error(F_parameter);
      if (new_length < 0) return F_status_set_error(F_parameter);
      if (!pointer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    // don't be wasteful
    if (old_length == new_length) return F_none;

    if (*pointer) {
      void *new_pointer = 0;

      if (old_length > 0) {
        if (new_length < old_length) {
          // uint8_t * is of a data size size of 1, casting it to uint8_t should result in a single-length increment.
          // this is done to avoid problems with (void *) having arithmetic issues.
          memset(((uint8_t *) *pointer) + new_length, 0, size * (old_length - new_length));
        }
      }

      // allocate new space.
      if (new_length > 0) {
        new_pointer = realloc(*pointer, size * new_length);
      }
      else {
        free(*pointer);

        // it has been deallocated, so reset the pointer
        *pointer = 0;

        return F_none;
      }

      if (new_pointer) {
        if (new_pointer != *pointer) {
          if (new_length > old_length) {
            // uint8_t * is of a data size size of 1, casting it to bool should result in a single-length increment.
            // this is done to avoid problems with (void *) having arithmetic issues.
            memset(((uint8_t *) new_pointer) + (size * old_length), 0, size * (new_length - old_length));
          }

          *pointer = new_pointer;
        }

        return F_none;
      }
    }
    else if (new_length > 0) {
      *pointer = calloc(size, new_length);

      if (*pointer) {
        return F_none;
      }
    }
    else {
      return F_none;
    }

    return F_status_set_error(F_memory_reallocation);
  }
#endif // !(defined(_di_f_memory_adjust_) || defined(_f_memory_FORCE_fast_memory_))

#ifdef __cplusplus
} // extern "C"
#endif
