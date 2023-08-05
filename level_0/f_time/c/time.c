#include "time.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_time_spec_millisecond_
  extern f_status_t f_time_spec_millisecond(const f_number_unsigned_t second, const f_number_unsigned_t millisecond, struct timespec * const time) {
    #ifndef _di_level_0_parameter_checking_
      if (!time) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (((time_t) second) < 0) {
      if ((long) millisecond < 0) {
        time->tv_sec = 0;
        time->tv_nsec = 0;
      }
      else {
        time->tv_sec = (long) millisecond > 1000 ? ((long) millisecond) / 1000 : 0;
        time->tv_nsec = (time->tv_sec ? ((long) millisecond) % 1000 : ((long) millisecond)) * 1000;
      }

      return F_status_set_error(F_number_underflow);
    }

    if ((long) millisecond < 0) {
      time->tv_sec = (time_t) second;
      time->tv_nsec = 0;

      return F_status_set_error(F_number_underflow);
    }

    if (millisecond) {
      time->tv_sec = ((long) millisecond) / 1000;
      time->tv_nsec = (time->tv_sec ? ((long) millisecond) % 1000 : ((long) millisecond)) * 1000;
    }
    else {
      time->tv_sec = 0;
      time->tv_nsec = 0;
    }

    time->tv_sec += (time_t) second;

    return time->tv_sec < (time_t) second ? F_status_set_error(F_number_overflow) : F_none;
  }
#endif // _di_f_time_spec_millisecond_

#ifndef _di_f_time_spec_nanosecond_
  extern f_status_t f_time_spec_nanosecond(const f_number_unsigned_t second, const f_number_unsigned_t nanosecond, struct timespec * const time) {
    #ifndef _di_level_0_parameter_checking_
      if (!time) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (((time_t) second) < 0) {
      time->tv_sec = 0;
      time->tv_nsec = ((long) nanosecond) < 0 ? 0 : (long) nanosecond;

      return F_status_set_error(F_number_underflow);
    }

    time->tv_sec = (time_t) second;

    if ((long) nanosecond < 0) {
      time->tv_nsec = 0;

      return F_status_set_error(F_number_underflow);
    }

    time->tv_nsec = (long) nanosecond;

    // If tv_nsec is 1 second or greater, then increment second.
    if (time->tv_nsec >= 1000000000) {
      ++(time->tv_sec);

      time->tv_nsec -= 1000000000;

      if (time->tv_sec < (time_t) second) return F_status_set_error(F_number_overflow);
    }

    return F_none;
  }
#endif // _di_f_time_spec_nanosecond_

#ifdef __cplusplus
} // extern "C"
#endif
