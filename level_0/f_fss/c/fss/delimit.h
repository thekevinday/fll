/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines set data to be used for/by project fss.
 *
 * This is auto-included by fss.h and should not need to be explicitly included.
 */
#ifndef _F_fss_delimit_h
#define _F_fss_delimit_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Designate an fss delimit location.
 */
#ifndef _di_f_fss_delimit_t_
  typedef f_array_length_t f_fss_delimit_t;

  #define f_fss_delimit_t_initialize f_array_length_t_initialize

  #define macro_f_fss_delimit_t_initialize(delimit) macro_f_array_length_t_initialize(delimit)
#endif // _di_f_fss_delimit_t_

/**
 * An array of f_fss_delimit_t.
 *
 * array: The array of fss quote.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_delimits_t_
  typedef f_array_lengths_t f_fss_delimits_t;

  #define f_fss_delimits_t_initialize f_array_lengths_t_initialize

  #define macro_f_fss_delimits_t_initialize(array, size, used) macro_f_array_lengths_t_initialize(array, size, used)
  #define macro_f_fss_delimits_t_initialize2(array, length)    macro_f_array_lengths_t_initialize2(array, length)

  #define macro_f_fss_delimits_t_clear(delimits) macro_f_array_lengths_t_clear(delimits)

  #define macro_f_fss_delimits_t_resize(status, delimits, length) macro_f_array_lengths_t_resize(status, delimits, length)
  #define macro_f_fss_delimits_t_adjust(status, delimits, length) macro_f_array_lengths_t_adjust(status, delimits, length)

  #define macro_f_fss_delimits_t_delete_simple(delimits)  macro_f_array_lengths_t_delete_simple(delimits)
  #define macro_f_fss_delimits_t_destroy_simple(delimits) macro_f_array_lengths_t_destroy_simple(delimits)

  #define macro_f_fss_delimits_t_increase(status, step, delimits)      macro_f_array_lengths_t_increase(status, step, delimits)
  #define macro_f_fss_delimits_t_increase_by(status, delimits, amount) macro_f_array_lengths_t_increase_by(status, delimits, amount)
  #define macro_f_fss_delimits_t_decrease_by(status, delimits, amount) macro_f_array_lengths_t_decrease_by(status, delimits, amount)
  #define macro_f_fss_delimits_t_decimate_by(status, delimits, amount) macro_f_array_lengths_t_decimate_by(status, delimits, amount)
#endif // _di_f_fss_delimits_t_

/**
 * An array of f_fss_delimits_t.
 *
 * array: The array of fss quotes.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_delimitss_t_
  typedef f_array_lengthss_t f_fss_delimitss_t;

  #define f_fss_delimitss_t_initialize f_array_lengthss_t_initialize

  #define macro_f_fss_delimitss_t_initialize(array, size, used) macro_f_array_lengthss_t_initialize(array, size, used)
  #define macro_f_fss_delimitss_t_initialize2(array, length)    macro_f_array_lengthss_t_initialize2(array, length)

  #define macro_f_fss_delimitss_t_clear(delimitss) macro_f_array_lengthss_t_clear(delimitss)

  #define macro_f_fss_delimitss_t_resize(status, delimitss, length) macro_f_array_lengthss_t_resize(status, delimitss, length)
  #define macro_f_fss_delimitss_t_adjust(status, delimitss, length) macro_f_array_lengthss_t_adjust(status, delimitss, length)

  #define macro_f_fss_delimitss_t_delete_simple(delimitss)  macro_f_array_lengthss_t_delete_simple(delimitss)
  #define macro_f_fss_delimitss_t_destroy_simple(delimitss) macro_f_array_lengthss_t_destroy_simple(delimitss)

  #define macro_f_fss_delimitss_t_increase(status, step, delimitss)      macro_f_array_lengthss_t_increase(status, step, delimitss)
  #define macro_f_fss_delimitss_t_increase_by(status, delimitss, amount) macro_f_array_lengthss_t_increase_by(status, delimitss, amount)
  #define macro_f_fss_delimitss_t_decrease_by(status, delimitss, amount) macro_f_array_lengthss_t_decrease_by(status, delimitss, amount)
  #define macro_f_fss_delimitss_t_decimate_by(status, delimitss, amount) macro_f_array_lengthss_t_decimate_by(status, delimitss, amount)
#endif // _di_f_fss_delimitss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_delimit_h
