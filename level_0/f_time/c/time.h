/**
 * FLL - Level 0
 *
 * Project: Time
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides time related functionality.
 */
#ifndef _F_time_h
#define _F_time_h

// Libc includes.
#include <time.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>

// FLL-0 time includes.

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create a timespec representing the given seconds and milliseconds.
 *
 * This is intended to work with "struct timespec" and is not intended to work with "f_time_spec_t".
 * The "struct timespec" may have different lengths and so this function provides overflow and underflow protection.
 * The "f_time_spec_t" should not need this as "f_time_spec_t" is intended to always be uint64_t.
 *
 * @param second
 *   The number of seconds.
 * @param millisecond
 *   The number of milliseconds.
 * @param time
 *   The time spec representing the given seconds and milliseconds.
 *
 *   This is still updated on F_number_overflow, and the result of the overflow is still assigned to seconds.
 *   This is still updated on F_number_underflow, but the underflow value is set to 0.
 *
 * @return
 *   F_okay on success.
 *
 *   F_number_overflow (with error bit) if the summation of seconds and milliseconds results in an overflow when cast to appropriate integer type.
 *   F_number_underflow (with error bit) if the seconds or milliseconds is less than 0 when cast to appropriate integer type.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_time_spec_millisecond_
  extern f_status_t f_time_spec_millisecond(const f_number_unsigned_t second, const f_number_unsigned_t millisecond, struct timespec * const time);
#endif // _di_f_time_spec_millisecond_

/**
 * Create a timespec representing the given seconds and nanoseconds.
 *
 * This is intended to work with "struct timespec" and is not intended to work with "f_time_spec_t".
 * The "struct timespec" may have different lengths and so this function provides overflow and underflow protection.
 * The "f_time_spec_t" should not need this as "f_time_spec_t" is intended to always be uint64_t.
 *
 * @param second
 *   The number of seconds.
 * @param nanosecond
 *   The number of nanoseconds.
 * @param time
 *   The time spec representing the given seconds and nanoseconds.
 *
 *   This is still updated on F_number_overflow, and the result of the overflow is still assigned to second.
 *   This is still updated on F_number_underflow, but the underflow value is set to 0.
 *
 * @return
 *   F_okay on success.
 *
 *   F_number_overflow (with error bit) if the summation of seconds and nanoseconds results in an overflow when cast to appropriate integer type.
 *   F_number_underflow (with error bit) if the second or nanoseconds is less than 0 when cast to appropriate integer type.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_time_spec_nanosecond_
  extern f_status_t f_time_spec_nanosecond(const f_number_unsigned_t second, const f_number_unsigned_t nanosecond, struct timespec * const time);
#endif // _di_f_time_spec_nanosecond_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_time_h
