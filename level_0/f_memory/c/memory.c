#include "memory.h"
#include "private-memory.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_memory_adjust_
  f_status_t f_memory_adjust(void **pointer, const size_t size, const size_t old_length, const size_t new_length) {
    #ifndef _di_level_0_parameter_checking_
      if (size <= 0) return F_status_set_error(F_parameter);
      if (old_length < 0) return F_status_set_error(F_parameter);
      if (new_length < 0) return F_status_set_error(F_parameter);
      if (!pointer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    #ifdef _f_memory_FORCE_fast_memory_
      return private_f_memory_resize(old_length, new_length, size, pointer);
    #else // _f_memory_FORCE_fast_memory_
      return private_f_memory_adjust(old_length, new_length, size, pointer);
    #endif // _f_memory_FORCE_fast_memory_
  }
#endif // _di_f_memory_adjust_

#ifndef _di_f_memory_new_aligned_
  f_status_t f_memory_new_aligned(void **pointer, const size_t alignment, const size_t length) {
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

      return F_status_set_error(F_memory_not);
    }

    // uint8_t * is of a data size size of 1, casting it to uint8_t should result in a single-length increment.
    // this is done to avoid problems with (void *) having arithmetic issues.
    memset(((uint8_t *) *pointer), 0, length);

    return F_none;
  }
#endif // _di_f_memory_new_aligned_

#ifndef _di_f_memory_delete_
  f_status_t f_memory_delete(void **pointer, const size_t size, const size_t length) {
    #ifndef _di_level_0_parameter_checking_
      if (!pointer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    // prevent double-frees.
    if (!*pointer || !size || !length) return F_none;

    #ifdef _f_memory_FORCE_secure_memory_
      if (length > 0) {
        memset(*pointer, 0, size * length);
      }
    #endif // _f_memory_FORCE_secure_memory_

    free(*pointer);

    // it has been deallocated, so reset the pointer.
    *pointer = 0;

    return F_none;
  }
#endif // _di_f_memory_delete_

#ifndef _di_f_memory_destroy_
  f_status_t f_memory_destroy(void **pointer, const size_t size, const size_t length) {
    #ifndef _di_level_0_parameter_checking_
      if (length < 0) return F_status_set_error(F_parameter);
      if (size <= 0) return F_status_set_error(F_parameter);
      if (!pointer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    // prevent double-frees.
    if (!*pointer || !length) return F_none;

    #ifndef _f_memory_FORCE_fast_memory_
      if (length > 0) {
        memset(*pointer, 0, size * length);
      }
    #endif // _f_memory_FORCE_fast_memory_

    free(*pointer);

    // it has been deallocated, so reset the pointer.
    *pointer = 0;

    return F_none;
  }
#endif // _di_f_memory_destroy_

#ifndef _di_f_memory_new_
  f_status_t f_memory_new(void **pointer, const size_t size, const size_t length) {
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

    return F_status_set_error(F_memory_not);
  }
#endif // _di_f_memory_new_

#ifndef _di_f_memory_resize_
  f_status_t f_memory_resize(void **pointer, const size_t size, const size_t old_length, const size_t new_length) {
    #ifndef _di_level_0_parameter_checking_
      if (size <= 0) return F_status_set_error(F_parameter);
      if (old_length < 0) return F_status_set_error(F_parameter);
      if (new_length < 0) return F_status_set_error(F_parameter);
      if (!pointer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    #ifdef _f_memory_FORCE_secure_memory_
      return private_f_memory_adjust(old_length, new_length, size, pointer);
    #else // _f_memory_FORCE_secure_memory_
      return private_f_memory_resize(old_length, new_length, size, pointer);
    #endif // _f_memory_FORCE_secure_memory_
  }
#endif // _di_f_memory_resize_

#ifdef __cplusplus
} // extern "C"
#endif
