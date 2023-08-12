#include "../memory.h"
#include "../private-memory.h"
#include "private-array.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_memory_array_adjust_) || !defined(_di_f_memory_array_decimate_by_)
  f_status_t private_f_memory_array_adjust(const f_number_unsigned_t length, const size_t width, void ** const array, f_number_unsigned_t * const used, f_number_unsigned_t * const size) {

    {
      const f_status_t status = private_f_memory_adjust(*size, length, width, array);
      if (F_status_is_error(status)) return status;
    }

    *size = length;

    if (*used > *size) {
      *used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_memory_array_adjust_) || !defined(_di_f_memory_array_decimate_by_)

#if !defined(_di_f_memory_array_append_) || !defined(_di_f_memory_array_append_all_) || !defined(_di_f_memory_array_decrease_by_) || !defined(_di_f_memory_array_increase_) || !defined(_di_f_memory_array_increase_by_) || !defined(_di_f_memory_array_resize_)
  f_status_t private_f_memory_array_resize(const f_number_unsigned_t length, const size_t width, void ** const array, f_number_unsigned_t * const used, f_number_unsigned_t * const size) {

    {
      const f_status_t status = private_f_memory_resize(*size, length, width, array);
      if (F_status_is_error(status)) return status;
    }

    *size = length;

    if (*used > *size) {
      *used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_memory_array_append_) || !defined(_di_f_memory_array_append_all_) || !defined(_di_f_memory_array_decrease_by_) || !defined(_di_f_memory_array_increase_) || !defined(_di_f_memory_array_increase_by_) || !defined(_di_f_memory_array_resize_)

#ifdef __cplusplus
} // extern "C"
#endif
