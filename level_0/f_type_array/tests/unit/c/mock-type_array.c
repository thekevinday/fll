#include "mock-type_array.h"

#ifdef __cplusplus
extern "C" {
#endif

int __wrap_poll(f_poll_t *fds, nfds_t nfds, int timeout) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  fds->revents = mock_type(short);

  return mock_type(int);
}

f_status_t __wrap_f_memory_array_adjust(const f_number_unsigned_t length, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size) {

  if (!array || !used || !size) return F_status_set_error(F_parameter_not);

  const bool failure = mock_type(bool);

  if (failure) return mock_type(f_status_t);

  *size = length;

  return mock_type(f_status_t);
}

f_status_t __wrap_f_memory_array_resize(const f_number_unsigned_t length, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size) {

  if (!array || !used || !size) return F_status_set_error(F_parameter_not);

  const bool failure = mock_type(bool);

  if (failure) return mock_type(f_status_t);

  *size = length;

  return mock_type(f_status_t);
}

#ifdef __cplusplus
} // extern "C"
#endif
