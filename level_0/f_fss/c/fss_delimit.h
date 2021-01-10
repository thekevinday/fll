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
  typedef f_string_length_t f_fss_delimit_t;
#endif // _di_f_fss_delimit_t_

/**
 * An array of f_fss_delimit_t.
 *
 * array: the array of fss quote.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_fss_delimits_t_
  typedef f_string_lengths_t f_fss_delimits_t;

  #define f_fss_delimits_t_initialize f_string_lengths_t_initialize

  #define f_macro_fss_delimits_t_new(status, lengths, length) f_macro_string_lengths_t_new(status, lengths, length);

  #define f_macro_fss_delimits_t_resize(status, lengths, length) f_macro_string_lengths_t_resize(status, lengths, length);
  #define f_macro_fss_delimits_t_adjust(status, lengths, length) f_macro_string_lengths_t_adjust(status, lengths, length);

  #define f_macro_fss_delimits_t_delete(status, lengths)  f_macro_string_lengths_t_delete(status, lengths);
  #define f_macro_fss_delimits_t_destroy(status, lengths) f_macro_string_lengths_t_destroy(status, lengths);

  #define f_macro_fss_delimits_t_delete_simple(lengths)  f_macro_string_lengths_t_delete_simple(lengths);
  #define f_macro_fss_delimits_t_destroy_simple(lengths) f_macro_string_lengths_t_destroy_simple(lengths);

  #define f_macro_fss_delimits_t_increase(status, lengths)            f_macro_string_lengths_t_increase(status, lengths);
  #define f_macro_fss_delimits_t_increase_by(status, lengths, amount) f_macro_string_lengths_t_increase_by(status, lengths, amount);
  #define f_macro_fss_delimits_t_decrease_by(status, lengths, amount) f_macro_string_lengths_t_decrease_by(status, lengths, amount);
  #define f_macro_fss_delimits_t_decimate_by(status, lengths, amount) f_macro_string_lengths_t_decimate_by(status, lengths, amount);
#endif // _di_f_fss_delimits_t_

/**
 * An array of f_fss_delimits_t.
 *
 * array: the array of fss quotes.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_fss_delimitss_t_
  typedef f_string_lengthss_t f_fss_delimitss_t;

  #define f_fss_delimitss_t_initialize f_string_lengthss_t_initialize

  #define f_macro_fss_delimitss_t_clear(delimitss) f_macro_string_lengthss_t_clear(delimitss);

  #define f_macro_fss_delimitss_t_new(status, delimitss, length) f_macro_string_lengthss_t_new(status, delimitss, length);

  #define f_macro_fss_delimitss_t_resize(status, delimitss, length) f_macro_string_lengthss_t_resize(status, delimitss, length);
  #define f_macro_fss_delimitss_t_adjust(status, delimitss, length) f_macro_string_lengthss_t_adjust(status, delimitss, length);

  #define f_macro_fss_delimitss_t_delete(status, delimitss)  f_macro_string_lengthss_t_delete(status, delimitss);
  #define f_macro_fss_delimitss_t_destroy(status, delimitss) f_macro_string_lengthss_t_destroy(status, delimitss);

  #define f_macro_fss_delimitss_t_delete_simple(delimitss)  f_macro_string_lengthss_t_delete_simple(delimitss);
  #define f_macro_fss_delimitss_t_destroy_simple(delimitss) f_macro_string_lengthss_t_destroy_simple(delimitss);

  #define f_macro_fss_delimitss_t_increase(status, lengthss)            f_macro_string_lengthss_t_increase(status, lengthss);
  #define f_macro_fss_delimitss_t_increase_by(status, lengthss, amount) f_macro_string_lengthss_t_increase_by(status, lengthss, amount);
  #define f_macro_fss_delimitss_t_decrease_by(status, lengthss, amount) f_macro_string_lengthss_t_decrease_by(status, lengthss, amount);
  #define f_macro_fss_delimitss_t_decimate_by(status, lengthss, amount) f_macro_string_lengthss_t_decimate_by(status, lengthss, amount);
#endif // _di_f_fss_delimitss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_delimit_h
