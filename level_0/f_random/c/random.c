#include "random.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_random_get_
  f_status_t f_random_get(long * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    *destination = random();

    return F_okay;
  }
#endif // _di_f_random_get_

#ifndef _di_f_random_read_
  f_status_t f_random_read(const unsigned int flag, const f_number_unsigned_t length, f_string_t * const destination, ssize_t * const total) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const ssize_t result = getrandom((void *) (*destination), length, flag);

    if (result == -1) {
      if (errno == EAGAIN) return F_status_set_error(F_again);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENOSYS) return F_status_set_error(F_support_not);

      return F_status_set_error(F_failure);
    }

    if (total) {
      *total = result;
    }

    return F_okay;
  }
#endif // _di_f_random_read_

#ifndef _di_f_random_seed_
  f_status_t f_random_seed(const unsigned int flag) {

    char raw[4] = { 0 };

    if (getrandom((void *) raw, sizeof(char) * 4, flag) == -1) {
      if (errno == EAGAIN) return F_status_set_error(F_again);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENOSYS) return F_status_set_error(F_support_not);

      return F_status_set_error(F_failure);
    }

    uint32_t entropy_digit = (uint32_t) ((uint8_t) raw[0]);
    entropy_digit += ((uint32_t) ((uint8_t) raw[1])) << 8;
    entropy_digit += ((uint32_t) ((uint8_t) raw[2])) << 16;
    entropy_digit += ((uint32_t) ((uint8_t) raw[3])) << 24;

    srandom(entropy_digit);

    // Clear the memory before de-allocating to reduce chances of the seed being in free memory.
    memset(&entropy_digit, 0, sizeof(uint32_t));
    memset(raw, 0, sizeof(char) * 4);

    return F_okay;
  }
#endif // _di_f_random_seed_

#ifndef _di_f_random_seed_set_
  f_status_t f_random_seed_set(unsigned int seed) {

    srandom(seed);

    return F_okay;
  }
#endif // _di_f_random_seed_set_

#ifdef __cplusplus
} // extern "C"
#endif
