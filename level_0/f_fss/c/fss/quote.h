/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Defines set data to be used for/by project fss.
 *
 * This is auto-included by fss.h and should not need to be explicitly included.
 */
#ifndef _F_fss_quote_h
#define _F_fss_quote_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Types for FSS quote.
 *
 * f_fss_quote_type_*:
 *   - none:     Not a quote.
 *   - single:   Quote type is a single quote.
 *   - double:   Quote type is a double quote.
 *   - backtick: Quote type is a backtick.
 */
#ifndef _di_f_fss_quote_type_
  enum {
    f_fss_quote_type_none_e = 0,
    f_fss_quote_type_single_e,
    f_fss_quote_type_double_e,
    f_fss_quote_type_backtick_e,
  };
#endif // _di_f_fss_quote_type_

/**
 * A number representing a quote type fom the FSS quote type enumeration.
 */
#ifndef _di_f_fss_quote_t_
  typedef uint8_t f_fss_quote_t;

  #define macro_f_fss_quote_t_initialize(quote) quote
#endif // _di_f_fss_quote_t_

/**
 * An array of f_fss_quote_t.
 *
 * array: The array of fss quote.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_quotes_t_
  typedef f_uint8s_t f_fss_quotes_t;

  #define f_fss_quotes_t_initialize f_uint8s_t_initialize

  #define macro_f_fss_quotes_t_initialize(array, size, used) { array, size, used }
  #define macro_f_fss_quotes_t_initialize2(array, length) { array, length, length }

  #define macro_f_fss_quotes_t_clear(quotes) macro_f_uint8s_t_clear(quotes)

  #define macro_f_fss_quotes_t_resize(status, quotes, length) macro_f_uint8s_t_resize(status, quotes, length)
  #define macro_f_fss_quotes_t_adjust(status, quotes, length) macro_f_uint8s_t_adjust(status, quotes, length)

  #define macro_f_fss_quotes_t_delete_simple(quotes)  macro_f_uint8s_t_delete_simple(quotes)
  #define macro_f_fss_quotes_t_destroy_simple(quotes) macro_f_uint8s_t_destroy_simple(quotes)

  #define macro_f_fss_quotes_t_increase(status, step, quotes)      macro_f_uint8s_t_increase(status, step, quotes)
  #define macro_f_fss_quotes_t_increase_by(status, quotes, amount) macro_f_uint8s_t_increase_by(status, quotes, amount)
  #define macro_f_fss_quotes_t_decrease_by(status, quotes, amount) macro_f_uint8s_t_decrease_by(status, quotes, amount)
  #define macro_f_fss_quotes_t_decimate_by(status, quotes, amount) macro_f_uint8s_t_decimate_by(status, quotes, amount)
#endif // _di_f_fss_quotes_t_

/**
 * An array of f_fss_quotes_t.
 *
 * array: The array of an array of fss quote.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_quotess_t_
  typedef f_uint8ss_t f_fss_quotess_t;

  #define f_fss_quotess_t_initialize f_uint8ss_t_initialize

  #define macro_f_fss_quotess_t_initialize(array, size, used) { array, size, used }
  #define macro_f_fss_quotess_t_initialize2(array, length) { array, length, length }

  #define macro_f_fss_quotess_t_clear(quotess) macro_f_uint8ss_t_clear(quotess)

  #define macro_f_fss_quotess_t_resize(status, quotess, length) macro_f_uint8ss_t_resize(status, quotess, length)
  #define macro_f_fss_quotess_t_adjust(status, quotess, length) macro_f_uint8ss_t_adjust(status, quotess, length)

  #define macro_f_fss_quotess_t_delete_simple(quotess)  macro_f_uint8ss_t_delete_simple(quotess)
  #define macro_f_fss_quotess_t_destroy_simple(quotess) macro_f_uint8ss_t_destroy_simple(quotess)

  #define macro_f_fss_quotess_t_increase(status, step, quotess)      macro_f_uint8ss_t_increase(status, step, quotess)
  #define macro_f_fss_quotess_t_increase_by(status, quotess, amount) macro_f_uint8ss_t_increase_by(status, quotess, amount)
  #define macro_f_fss_quotess_t_decrease_by(status, quotess, amount) macro_f_uint8ss_t_decrease_by(status, quotess, amount)
  #define macro_f_fss_quotess_t_decimate_by(status, quotess, amount) macro_f_uint8ss_t_decimate_by(status, quotess, amount)
#endif // _di_f_fss_quotess_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_quote_h
