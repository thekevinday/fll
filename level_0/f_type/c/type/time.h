/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines time type data.
 *
 * This is auto-included by type.h and should not need to be explicitly included.
 */
#ifndef _F_type_time_h
#define _F_type_time_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Hold a unit of Time.
 *
 * This is intended to be utilized for the unit of measurement called a "Time", represented with uppercase "T".
 * For comparison, a unit of Time is equivalent to a nanosecond, or 10^-9 seconds.
 *
 * A unit of Time is intended to represent some unit of Time such that a single 64-bit integer may hold all units of Time for a single calendar year.
 * This unit of Time does not and must not include Years (unlike Unixtime).
 *
 * A MegaTime (MT) is therefore equivalent to a millisecond such that a millisecond is 10^-3 seconds.
 *
 * To convert from Time to Unixtime, one must have a year (which could be assumed to be the current year) and then calculate all of those calendar od
 *
 * A unit of Time by default is assumed to be in UTC.
 * 1 (Earth) year ~= 31536000000000000 Time or 31536000 GT (GigaTime).
 * 1 (Earth) day = 86400000000000 Time or 86400 GT (GigaTime).
 * 1 (Earth) hour = 3600000000000 Time or 3600 GT (GigaTime).
 * 1 (Earth) minute = 60000000000 Time or 60 GT (GigaTime).
 * 1 (Earth) second = 1000000000 Time or 1 GT (GigaTime).
 *
 * Consequentially, 1 day in units of Time is easily represented as 86.4 TT (TeraTime).
 *
 * This is not time_t, which is a different structure that may not be uint64_t and is often signed.
 */
#ifndef _di_f_time_t_
  typedef uint64_t f_time_t;

  #define f_time_t_initialize 0
#endif // _di_f_time_t_

/**
 * A non-kernel dependent alternative version of "struct timespec".
 *
 * This is may not compatible with struct timespec because seconds is time_t and that may not be a uint64_t.
 * In many cases of "struct timespec", seconds is signed because time_t is signed.
 *
 * Properties:
 *   - seconds:      The total number of seconds.
 *   - seconds_nano: The total number of nanoseconds.
 */
#ifndef _di_f_time_spec_t_
  typedef struct {
    f_time_t seconds;
    f_time_t seconds_nano;
  } f_time_spec_t;

  #define f_time_spec_t_initialize { f_time_t_initialize, f_time_t_initialize }

  #define macro_f_time_spec_t_clear(spec) \
    spec.seconds = 0; \
    spec.seconds_nano = 0;
#endif // _di_f_time_spec_t_

/**
 * Hold a unit of Time along with a year to represent a date.
 *
 * This implementation of a date using the unit of Time is limited on the size of the year.
 * The value for year is expected to be a signed number.
 * For anything that needs a larger (or smaller) year, create a new type or use the "year string format" of Time.
 *
 * In "year string format" of Time, a Year may be prepended to the Time followed by a single colon ':' to associate a year with the Time.
 * This Year has no minimum or maximum but may not have decimals.
 *
 * For example, "2020:86400000000000" would represent: January 02, 2020 0:00 UTC.
 * For example, "2020:86.4 TT" would represent: January 02, 2020 0:00 UTC.
 *
 * Properties:
 *   - year: A number representing the year.
 *   - time: A number representing the time.
 */
#ifndef _di_f_date_t_
  typedef struct {
    f_number_signed_t year;
    f_time_t time;
  } f_date_t;

  #define f_date_t_initialize { 0, 0 }

  #define macro_f_date_t_clear(date) \
    date.year = 0; \
    date.time = 0;
#endif // _di_f_date_t_

/**
 * A variation of f_date_t that using f_time_spec_t rather than f_time_t.
 *
 * This can is a more precise alternative to f_date_t because it stores nanoseconds.
 *
 * The f_time_spec_t.time.seconds can be directly cast to the f_date_t.time.
 *
 * Properties:
 *   - year: A number representing the year.
 *   - time: A number representing the time with seconds and nanoseconds.
 */
#ifndef _di_f_date_spec_t_
  typedef struct {
    f_time_t year;
    f_time_spec_t time;
  } f_date_spec_t;

  #define f_date_spec_t_initialize { f_time_t_initialize, macro_f_time_spec_t_clear }

  #define macro_f_date_spec_t_clear(date) \
    date.year = 0; \
    macro_f_time_spec_t_clear(date.time);
#endif // _di_f_date_spec_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_time_h
