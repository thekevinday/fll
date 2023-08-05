#include "memory.h"
#include "private-memory.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_memory_adjust_
  f_status_t f_memory_adjust(const size_t length_old, const size_t length_new, const size_t size, void ** const pointer) {
    #ifndef _di_level_0_parameter_checking_
      if (!size) return F_status_set_error(F_parameter);
      if (!pointer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    // Prevent double-frees and unnecessary frees.
    if (!*pointer && !length_new || length_old == length_new) return F_data_not;

    #ifdef _f_memory_FORCE_fast_memory_
      return private_f_memory_resize(length_old, length_new, size, pointer);
    #else // _f_memory_FORCE_fast_memory_
      return private_f_memory_adjust(length_old, length_new, size, pointer);
    #endif // _f_memory_FORCE_fast_memory_
  }
#endif // _di_f_memory_adjust_

#ifndef _di_f_memory_delete_
  f_status_t f_memory_delete(const size_t length, const size_t size, void ** const pointer) {
    #ifndef _di_level_0_parameter_checking_
      if (!size) return F_status_set_error(F_parameter);
      if (!pointer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    // Prevent double-frees.
    if (!*pointer) return F_data_not;

    #ifdef _f_memory_FORCE_secure_memory_
      if (!length) {
        memset(*pointer, 0, size * length);
      }
    #endif // _f_memory_FORCE_secure_memory_

    free(*pointer);

    // It has been deallocated, so reset the pointer.
    *pointer = 0;

    return F_none;
  }
#endif // _di_f_memory_delete_

#ifndef _di_f_memory_destroy_
  f_status_t f_memory_destroy(const size_t length, const size_t size, void ** const pointer) {
    #ifndef _di_level_0_parameter_checking_
      if (!size) return F_status_set_error(F_parameter);
      if (!pointer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    // Prevent double-frees.
    if (!*pointer) return F_data_not;

    #ifndef _f_memory_FORCE_fast_memory_
      if (!length) {
        memset(*pointer, 0, size * length);
      }
    #endif // _f_memory_FORCE_fast_memory_

    free(*pointer);

    // It has been deallocated, so reset the pointer.
    *pointer = 0;

    return F_none;
  }
#endif // _di_f_memory_destroy_

#ifndef _di_f_memory_new_
  f_status_t f_memory_new(const size_t length, const size_t size, void ** const pointer) {
    #ifndef _di_level_0_parameter_checking_
      if (!size) return F_status_set_error(F_parameter);
      if (!pointer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    // Prevent double-allocations and unnecessary frees.
    if (*pointer || !length) return F_data_not;

    if ((*pointer = calloc(length, size))) return F_none;

    return F_status_set_error(F_memory_not);
  }
#endif // _di_f_memory_new_


#ifndef _di_f_memory_new_aligned_
  f_status_t f_memory_new_aligned(const size_t length, const size_t alignment, void ** const pointer) {
    #ifndef _di_level_0_parameter_checking_
      if (!alignment) return F_status_set_error(F_parameter);
      if (!pointer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    // Prevent double-allocations and unnecessary frees.
    if (*pointer || !length) return F_data_not;

    #ifdef _f_memory_USE_posix_memalign_
      const int result = posix_memalign(pointer, alignment, length);

      if (result) {
        if (result == EINVAL) return F_status_set_error(F_parameter);

        return F_status_set_error(F_memory_not);
      }
    #else
      void * const result = aligned_alloc(alignment, length);

      if (result) {
        *pointer = result;
      }
      else if (errno == EINVAL) {
        return F_status_set_error(F_parameter);
      }
      else {
        return F_status_set_error(F_memory_not);
      }
    #endif // _f_memory_USE_posix_memalign_

    // uint8_t * is of a data size of 1, casting it to uint8_t should result in a single-length increment.
    // This is done to avoid problems with (void *) having arithmetic issues.
    memset(((uint8_t *) *pointer), 0, length);

    return F_none;
  }
#endif // _di_f_memory_new_aligned_

#ifndef _di_f_memory_resize_
  f_status_t f_memory_resize(const size_t length_old, const size_t length_new, const size_t size, void ** const pointer) {
    #ifndef _di_level_0_parameter_checking_
      if (!size) return F_status_set_error(F_parameter);
      if (!pointer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    // Prevent double-frees and unnecessary frees.
    if (!*pointer && !length_new || length_old == length_new) return F_data_not;

    #ifdef _f_memory_FORCE_secure_memory_
      return private_f_memory_adjust(length_old, length_new, size, pointer);
    #else // _f_memory_FORCE_secure_memory_
      return private_f_memory_resize(length_old, length_new, size, pointer);
    #endif // _f_memory_FORCE_secure_memory_
  }
#endif // _di_f_memory_resize_

#ifdef __cplusplus
} // extern "C"
#endif
