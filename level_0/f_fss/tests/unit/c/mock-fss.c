#include "mock-fss.h"

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

f_status_t __wrap_f_memory_arrays_adjust(const f_number_unsigned_t length, const size_t width, void ** const array, f_number_unsigned_t * const used, f_number_unsigned_t * const size, f_status_t (*callback)(const f_number_unsigned_t start, const f_number_unsigned_t size, void * const array)) {

  if (mock_unwrap_f_memory) {
    return __real_f_memory_arrays_resize(length, width, array, used, size, callback);
  }

  if (!array || !used || !size || !callback) return F_status_set_error(F_parameter_not);

  const bool failure = mock_type(bool);

  if (failure) return mock_type(f_status_t);

  *size = length;

  return mock_type(f_status_t);
}

f_status_t __wrap_f_memory_arrays_resize(const f_number_unsigned_t length, const size_t width, void ** const array, f_number_unsigned_t * const used, f_number_unsigned_t * const size, f_status_t (*callback)(const f_number_unsigned_t start, const f_number_unsigned_t size, void * const array)) {

  if (mock_unwrap_f_memory) {
    return __real_f_memory_arrays_resize(length, width, array, used, size, callback);
  }

  if (!array || !used || !size || !callback) return F_status_set_error(F_parameter_not);

  const bool failure = mock_type(bool);

  if (failure) return mock_type(f_status_t);

  *size = length;

  return mock_type(f_status_t);
}

f_status_t __wrap_f_string_dynamic_adjust(const f_number_unsigned_t length, f_string_dynamic_t * const structure) {

  if (mock_unwrap) {
    return __real_f_string_dynamic_adjust(length, structure);
  }

  if (!structure) return F_status_set_error(F_parameter_not);

  const bool failure = mock_type(bool);

  if (failure) return mock_type(f_status_t);

  structure->size = length;

  return mock_type(f_status_t);
}

f_status_t __wrap_f_string_dynamic_resize(const f_number_unsigned_t length, f_string_dynamic_t * const structure) {

  if (mock_unwrap) {
    return __real_f_string_dynamic_resize(length, structure);
  }

  if (!structure) return F_status_set_error(F_parameter_not);

  const bool failure = mock_type(bool);

  if (failure) return mock_type(f_status_t);

  structure->size = length;

  return mock_type(f_status_t);
}

f_status_t __wrap_f_string_ranges_adjust(const f_number_unsigned_t length, f_string_ranges_t * const structure) {

  if (mock_unwrap) {
    return __real_f_string_ranges_adjust(length, structure);
  }

  if (!structure) return F_status_set_error(F_parameter_not);

  const bool failure = mock_type(bool);

  if (failure) return mock_type(f_status_t);

  structure->size = length;

  return mock_type(f_status_t);
}

f_status_t __wrap_f_string_ranges_resize(const f_number_unsigned_t length, f_string_ranges_t * const structure) {

  if (mock_unwrap) {
    return __real_f_string_ranges_resize(length, structure);
  }

  if (!structure) return F_status_set_error(F_parameter_not);

  const bool failure = mock_type(bool);

  if (failure) return mock_type(f_status_t);

  structure->size = length;

  return mock_type(f_status_t);
}

f_status_t __wrap_f_string_rangess_adjust(const f_number_unsigned_t length, f_string_ranges_t * const structure) {

  if (mock_unwrap) {
    return __real_f_string_rangess_adjust(length, structure);
  }

  if (!structure) return F_status_set_error(F_parameter_not);

  const bool failure = mock_type(bool);

  if (failure) return mock_type(f_status_t);

  structure->size = length;

  return mock_type(f_status_t);
}

f_status_t __wrap_f_string_rangess_resize(const f_number_unsigned_t length, f_string_ranges_t * const structure) {

  if (mock_unwrap) {
    return __real_f_string_rangess_resize(length, structure);
  }

  if (!structure) return F_status_set_error(F_parameter_not);

  const bool failure = mock_type(bool);

  if (failure) return mock_type(f_status_t);

  structure->size = length;

  return mock_type(f_status_t);
}

#ifdef __cplusplus
} // extern "C"
#endif
