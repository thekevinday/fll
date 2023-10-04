#include "mock-abstruse.h"

#ifdef __cplusplus
extern "C" {
#endif

int mock_unwrap = 0;
int mock_unwrap_f_memory = 1;

f_status_t __wrap_f_memory_array_adjust(const f_number_unsigned_t length, const size_t width, void ** const array, f_number_unsigned_t * const used, f_number_unsigned_t * const size) {

  if (mock_unwrap_f_memory) {
    return __real_f_memory_array_adjust(length, width, array, used, size);
  }

  if (!array || !used || !size) return F_status_set_error(F_parameter_not);

  const bool failure = mock_type(bool);

  if (failure) return mock_type(f_status_t);

  *size = length;

  return mock_type(f_status_t);
}

f_status_t __wrap_f_memory_array_resize(const f_number_unsigned_t length, const size_t width, void ** const array, f_number_unsigned_t * const used, f_number_unsigned_t * const size) {

  if (mock_unwrap_f_memory) {
    return __real_f_memory_array_resize(length, width, array, used, size);
  }

  if (!array || !used || !size) return F_status_set_error(F_parameter_not);

  const bool failure = mock_type(bool);

  if (failure) return mock_type(f_status_t);

  *size = length;

  return mock_type(f_status_t);
}

#ifdef __cplusplus
} // extern "C"
#endif
