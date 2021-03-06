/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
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
#endif // _di_f_fss_delimit_t_

/**
 * An array of f_fss_delimit_t.
 *
 * array: the array of fss quote.
 * size:  total amount of allocated space.
 * used:  total number of allocated spaces used.
 */
#ifndef _di_f_fss_delimits_t_
  typedef f_array_lengths_t f_fss_delimits_t;

  #define f_fss_delimits_t_initialize f_array_lengths_t_initialize

  #define f_macro_fss_delimits_t_clear(delimits) f_macro_array_lengths_t_clear(delimits)

  #define f_macro_fss_delimits_t_resize(status, delimits, length) f_macro_array_lengths_t_resize(status, delimits, length)
  #define f_macro_fss_delimits_t_adjust(status, delimits, length) f_macro_array_lengths_t_adjust(status, delimits, length)

  #define f_macro_fss_delimits_t_delete_simple(delimits)  f_macro_array_lengths_t_delete_simple(delimits)
  #define f_macro_fss_delimits_t_destroy_simple(delimits) f_macro_array_lengths_t_destroy_simple(delimits)

  #define f_macro_fss_delimits_t_increase(status, delimits)            f_macro_array_lengths_t_increase(status, delimits)
  #define f_macro_fss_delimits_t_increase_by(status, delimits, amount) f_macro_array_lengths_t_increase_by(status, delimits, amount)
  #define f_macro_fss_delimits_t_decrease_by(status, delimits, amount) f_macro_array_lengths_t_decrease_by(status, delimits, amount)
  #define f_macro_fss_delimits_t_decimate_by(status, delimits, amount) f_macro_array_lengths_t_decimate_by(status, delimits, amount)
#endif // _di_f_fss_delimits_t_

/**
 * An array of f_fss_delimits_t.
 *
 * array: the array of fss quotes.
 * size:  total amount of allocated space.
 * used:  total number of allocated spaces used.
 */
#ifndef _di_f_fss_delimitss_t_
  typedef f_array_lengthss_t f_fss_delimitss_t;

  #define f_fss_delimitss_t_initialize f_array_lengthss_t_initialize

  #define f_macro_fss_delimitss_t_clear(delimitss) f_macro_array_lengthss_t_clear(delimitss)

  #define f_macro_fss_delimitss_t_resize(status, delimitss, length) f_macro_array_lengthss_t_resize(status, delimitss, length)
  #define f_macro_fss_delimitss_t_adjust(status, delimitss, length) f_macro_array_lengthss_t_adjust(status, delimitss, length)

  #define f_macro_fss_delimitss_t_delete_simple(delimitss)  f_macro_array_lengthss_t_delete_simple(delimitss)
  #define f_macro_fss_delimitss_t_destroy_simple(delimitss) f_macro_array_lengthss_t_destroy_simple(delimitss)

  #define f_macro_fss_delimitss_t_increase(status, delimitss)            f_macro_array_lengthss_t_increase(status, delimitss)
  #define f_macro_fss_delimitss_t_increase_by(status, delimitss, amount) f_macro_array_lengthss_t_increase_by(status, delimitss, amount)
  #define f_macro_fss_delimitss_t_decrease_by(status, delimitss, amount) f_macro_array_lengthss_t_decrease_by(status, delimitss, amount)
  #define f_macro_fss_delimitss_t_decimate_by(status, delimitss, amount) f_macro_array_lengthss_t_decimate_by(status, delimitss, amount)
#endif // _di_f_fss_delimitss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_delimit_h
