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

  #define f_macro_fss_delimits_t_adjust(status, delimits, length) f_macro_memory_structure_t_adjust(status, delimits, f_fss_delimit_t, length)

  #define f_macro_fss_delimits_t_clear(delimits) f_macro_memory_structure_t_clear(delimits)

  #define f_macro_fss_delimits_t_decimate(status, delimits)            f_macro_memory_structure_decimate(status, delimits, f_fss_delimit_t);
  #define f_macro_fss_delimits_t_decimate_by(status, delimits, amount) f_macro_memory_structure_decimate_by(status, delimits, f_fss_delimit_t, amount);

  #define f_macro_fss_delimits_t_decrease(status, delimits)            f_macro_memory_structure_decrease(status, delimits, f_fss_delimit_t);
  #define f_macro_fss_delimits_t_decrease_by(status, delimits, amount) f_macro_memory_structure_decrease_by(status, delimits, f_fss_delimit_t, amount);

  #define f_macro_fss_delimits_t_delete(status, delimits) f_macro_memory_structure_t_delete(status, delimits, f_fss_delimit_t)
  #define f_macro_fss_delimits_t_delete_simple(delimits)  f_macro_memory_structure_t_delete_simple(delimits, f_fss_delimit_t)

  #define f_macro_fss_delimits_t_destroy(status, delimits) f_macro_memory_structure_t_destroy(status, delimits, f_fss_delimit_t)
  #define f_macro_fss_delimits_t_destroy_simple(delimits)  f_macro_memory_structure_t_destroy_simple(delimits, f_fss_delimit_t)

  #define f_macro_fss_delimits_t_increase(status, delimits)            f_macro_memory_structure_increase(status, delimits, f_fss_delimit_t);
  #define f_macro_fss_delimits_t_increase_by(status, delimits, amount) f_macro_memory_structure_increase_by(status, delimits, f_fss_delimit_t, amount);

  #define f_macro_fss_delimits_t_new(status, delimits, length) f_macro_memory_structure_t_new(status, delimits, f_fss_delimit_t, length)

  #define f_macro_fss_delimits_t_resize(status, delimits, new_length) f_macro_memory_structure_t_resize(status, delimits, f_fss_delimit_t, new_length)
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

  #define f_macro_fss_delimitss_t_clear(quotess) f_macro_string_lengthss_t_clear(quotess)

  #define f_macro_fss_delimitss_t_new(status, quotess, length) f_macro_string_lengthss_t_new(status, quotess, length)

  #define f_macro_fss_delimitss_t_delete(status, quotess)  f_macro_string_lengthss_t_delete(status, quotess)
  #define f_macro_fss_delimitss_t_destroy(status, quotess) f_macro_string_lengthss_t_destroy(status, quotess)

  #define f_macro_fss_delimitss_t_delete_simple(quotess)  f_macro_string_lengthss_t_delete_simple(quotess)
  #define f_macro_fss_delimitss_t_destroy_simple(quotess) f_macro_string_lengthss_t_destroy_simple(quotess)

  #define f_macro_fss_delimitss_t_resize(status, quotess, new_length) f_macro_string_lengthss_t_resize(status, quotess, new_length)
  #define f_macro_fss_delimitss_t_adjust(status, quotess, new_length) f_macro_string_lengthss_t_adjust(status, quotess, new_length)
#endif // _di_f_fss_delimitss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_delimit_h
