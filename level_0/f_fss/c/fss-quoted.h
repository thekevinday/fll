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
#ifndef _di_f_fss_quoted_t_
  typedef uint8_t f_fss_quoted_t;
#endif // _di_f_fss_quoted_t_

/**
 * An array of f_fss_quoted_t.
 *
 * array: the array of fss quoted.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_fss_quoteds_t_
  typedef f_uint8s_t f_fss_quoteds_t;

  #define f_fss_quoteds_t_initialize f_uint8s_t_initialize

  #define f_macro_fss_quoteds_t_clear(quoteds) f_macro_uint8s_t_clear(quoteds)

  #define f_macro_fss_quoteds_t_new(status, quoteds, length) f_macro_uint8s_t_new(status, quoteds, length)

  #define f_macro_fss_quoteds_t_delete(status, quoteds)  f_macro_uint8s_t_delete(status, quoteds)
  #define f_macro_fss_quoteds_t_destroy(status, quoteds) f_macro_uint8s_t_destroy(status, quoteds)

  #define f_macro_fss_quoteds_t_delete_simple(quoteds)  f_macro_uint8s_t_delete_simple(quoteds)
  #define f_macro_fss_quoteds_t_destroy_simple(quoteds) f_macro_uint8s_t_destroy_simple(quoteds)

  #define f_macro_fss_quoteds_t_resize(status, quoteds, new_length) f_macro_uint8s_t_resize(status, quoteds, new_length)
  #define f_macro_fss_quoteds_t_adjust(status, quoteds, new_length) f_macro_uint8s_t_adjust(status, quoteds, new_length)
#endif // _di_f_fss_quoteds_t_

/**
 * An array of f_fss_quoteds_t.
 *
 * array: the array of fss quoteds.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_fss_quotedss_t_
  typedef f_uint8ss_t f_fss_quotedss_t;

  #define f_fss_quotedss_t_initialize f_uint8ss_t_initialize

  #define f_macro_fss_quotedss_t_clear(quotedss) f_macro_uint8ss_t_clear(quotedss)

  #define f_macro_fss_quotedss_t_new(status, quotedss, length) f_macro_uint8ss_t_new(status, quotedss, length)

  #define f_macro_fss_quotedss_t_delete(status, quotedss)  f_macro_uint8ss_t_delete(status, quotedss)
  #define f_macro_fss_quotedss_t_destroy(status, quotedss) f_macro_uint8ss_t_destroy(status, quotedss)

  #define f_macro_fss_quotedss_t_delete_simple(quotedss)  f_macro_uint8ss_t_delete_simple(quotedss)
  #define f_macro_fss_quotedss_t_destroy_simple(quotedss) f_macro_uint8ss_t_destroy_simple(quotedss)

  #define f_macro_fss_quotedss_t_resize(status, quotedss, new_length) f_macro_uint8ss_t_resize(status, quotedss, new_length)
  #define f_macro_fss_quotedss_t_adjust(status, quotedss, new_length) f_macro_uint8ss_t_adjust(status, quotedss, new_length)
#endif // _di_f_fss_quotedss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_quoted_h
