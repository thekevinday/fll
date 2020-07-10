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
#ifndef _F_fss_quoted_h
#define _F_fss_quoted_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Types for FSS quoted.
 */
#ifndef _di_f_fss_quoted_type_
  enum {
    f_fss_quoted_type_single = 1,
    f_fss_quoted_type_double,
  };
#endif // _di_f_fss_quoted_type_

/**
 * Designate an fss quoted.
 */
#ifndef _di_f_fss_quoted_
  typedef uint8_t f_fss_quoted;
#endif // _di_f_fss_quoted_

/**
 * An array of f_fss_quoted.
 *
 * array: the array of fss quoted.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_fss_quoteds_
  typedef f_uint8_ts f_fss_quoteds;

  #define f_fss_quoteds_initialize f_uint8_ts_initialize

  #define f_macro_fss_quoteds_clear(quoteds) f_macro_uint8_ts_clear(quoteds)

  #define f_macro_fss_quoteds_new(status, quoteds, length) f_macro_uint8_ts_new(status, quoteds, length)

  #define f_macro_fss_quoteds_delete(status, quoteds)  f_macro_uint8_ts_delete(status, quoteds)
  #define f_macro_fss_quoteds_destroy(status, quoteds) f_macro_uint8_ts_destroy(status, quoteds)

  #define f_macro_fss_quoteds_delete_simple(quoteds)  f_macro_uint8_ts_delete_simple(quoteds)
  #define f_macro_fss_quoteds_destroy_simple(quoteds) f_macro_uint8_ts_destroy_simple(quoteds)

  #define f_macro_fss_quoteds_resize(status, quoteds, new_length) f_macro_uint8_ts_resize(status, quoteds, new_length)
  #define f_macro_fss_quoteds_adjust(status, quoteds, new_length) f_macro_uint8_ts_adjust(status, quoteds, new_length)
#endif // _di_f_fss_quoteds_

/**
 * An array of f_fss_quoteds.
 *
 * array: the array of fss quoteds.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_fss_quotedss_
  typedef f_uint8_tss f_fss_quotedss;

  #define f_fss_quotedss_initialize f_uint8_tss_initialize

  #define f_macro_fss_quotedss_clear(quotedss) f_macro_uint8_tss_clear(quotedss)

  #define f_macro_fss_quotedss_new(status, quotedss, length) f_macro_uint8_tss_new(status, quotedss, length)

  #define f_macro_fss_quotedss_delete(status, quotedss)  f_macro_uint8_tss_delete(status, quotedss)
  #define f_macro_fss_quotedss_destroy(status, quotedss) f_macro_uint8_tss_destroy(status, quotedss)

  #define f_macro_fss_quotedss_delete_simple(quotedss)  f_macro_uint8_tss_delete_simple(quotedss)
  #define f_macro_fss_quotedss_destroy_simple(quotedss) f_macro_uint8_tss_destroy_simple(quotedss)

  #define f_macro_fss_quotedss_resize(status, quotedss, new_length) f_macro_uint8_tss_resize(status, quotedss, new_length)
  #define f_macro_fss_quotedss_adjust(status, quotedss, new_length) f_macro_uint8_tss_adjust(status, quotedss, new_length)
#endif // _di_f_fss_quotedss_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_quoted_h
