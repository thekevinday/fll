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
#ifndef _F_fss_quote_h
#define _F_fss_quote_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Types for FSS quote.
 */
#ifndef _di_f_fss_quote_type_
  enum {
    f_fss_quote_type_single = 1,
    f_fss_quote_type_double,
  };
#endif // _di_f_fss_quote_type_

/**
 * Designate an fss quote.
 */
#ifndef _di_f_fss_quote_t_
  typedef uint8_t f_fss_quote_t;
#endif // _di_f_fss_quote_t_

/**
 * An array of f_fss_quote_t.
 *
 * array: the array of fss quote.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_fss_quotes_t_
  typedef f_uint8s_t f_fss_quotes_t;

  #define f_fss_quotes_t_initialize f_uint8s_t_initialize

  #define f_macro_fss_quotes_t_clear(quotes) f_macro_uint8s_t_clear(quotes)

  #define f_macro_fss_quotes_t_new(status, quotes, length) f_macro_uint8s_t_new(status, quotes, length)

  #define f_macro_fss_quotes_t_delete(status, quotes)  f_macro_uint8s_t_delete(status, quotes)
  #define f_macro_fss_quotes_t_destroy(status, quotes) f_macro_uint8s_t_destroy(status, quotes)

  #define f_macro_fss_quotes_t_delete_simple(quotes)  f_macro_uint8s_t_delete_simple(quotes)
  #define f_macro_fss_quotes_t_destroy_simple(quotes) f_macro_uint8s_t_destroy_simple(quotes)

  #define f_macro_fss_quotes_t_resize(status, quotes, new_length) f_macro_uint8s_t_resize(status, quotes, new_length)
  #define f_macro_fss_quotes_t_adjust(status, quotes, new_length) f_macro_uint8s_t_adjust(status, quotes, new_length)
#endif // _di_f_fss_quotes_t_

/**
 * An array of f_fss_quotes_t.
 *
 * array: the array of fss quotes.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_fss_quotess_t_
  typedef f_uint8ss_t f_fss_quotess_t;

  #define f_fss_quotess_t_initialize f_uint8ss_t_initialize

  #define f_macro_fss_quotess_t_clear(quotess) f_macro_uint8ss_t_clear(quotess)

  #define f_macro_fss_quotess_t_new(status, quotess, length) f_macro_uint8ss_t_new(status, quotess, length)

  #define f_macro_fss_quotess_t_delete(status, quotess)  f_macro_uint8ss_t_delete(status, quotess)
  #define f_macro_fss_quotess_t_destroy(status, quotess) f_macro_uint8ss_t_destroy(status, quotess)

  #define f_macro_fss_quotess_t_delete_simple(quotess)  f_macro_uint8ss_t_delete_simple(quotess)
  #define f_macro_fss_quotess_t_destroy_simple(quotess) f_macro_uint8ss_t_destroy_simple(quotess)

  #define f_macro_fss_quotess_t_resize(status, quotess, new_length) f_macro_uint8ss_t_resize(status, quotess, new_length)
  #define f_macro_fss_quotess_t_adjust(status, quotess, new_length) f_macro_uint8ss_t_adjust(status, quotess, new_length)
#endif // _di_f_fss_quotess_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_quote_h
