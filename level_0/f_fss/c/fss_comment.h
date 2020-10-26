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
#ifndef _F_fss_comment_h
#define _F_fss_comment_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Designate an fss comment location.
 */
#ifndef _di_f_fss_comment_t_
  typedef f_string_range_t f_fss_comment_t;
#endif // _di_f_fss_comment_t_

/**
 * An array of f_fss_comment_t.
 *
 * array: the array of fss quote.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_fss_comments_t_
  typedef f_string_ranges_t f_fss_comments_t;

  #define f_fss_comments_t_initialize f_string_ranges_t_initialize

  #define f_macro_fss_comments_t_clear(delimits) f_macro_string_ranges_t_clear(delimits)

  #define f_macro_fss_comments_t_new(status, delimits, length) f_macro_string_ranges_t_new(status, delimits, length)

  #define f_macro_fss_comments_t_delete(status, delimits)  f_macro_string_ranges_t_delete(status, delimits)
  #define f_macro_fss_comments_t_destroy(status, delimits) f_macro_string_ranges_t_destroy(status, delimits)

  #define f_macro_fss_comments_t_delete_simple(delimits)  f_macro_string_ranges_t_delete_simple(delimits)
  #define f_macro_fss_comments_t_destroy_simple(delimits) f_macro_string_ranges_t_destroy_simple(delimits)

  #define f_macro_fss_comments_t_resize(status, delimits, new_length) f_macro_string_ranges_t_resize(status, delimits, new_length)
  #define f_macro_fss_comments_t_adjust(status, delimits, new_length) f_macro_string_ranges_t_adjust(status, delimits, new_length)
#endif // _di_f_fss_comments_t_

/**
 * An array of f_fss_comments_t.
 *
 * array: the array of fss quotes.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_fss_commentss_t_
  typedef f_string_rangess_t f_fss_commentss_t;

  #define f_fss_commentss_t_initialize f_string_rangess_t_initialize

  #define f_macro_fss_commentss_t_clear(quotess) f_macro_string_rangess_t_clear(quotess)

  #define f_macro_fss_commentss_t_new(status, quotess, length) f_macro_string_rangess_t_new(status, quotess, length)

  #define f_macro_fss_commentss_t_delete(status, quotess)  f_macro_string_rangess_t_delete(status, quotess)
  #define f_macro_fss_commentss_t_destroy(status, quotess) f_macro_string_rangess_t_destroy(status, quotess)

  #define f_macro_fss_commentss_t_delete_simple(quotess)  f_macro_string_rangess_t_delete_simple(quotess)
  #define f_macro_fss_commentss_t_destroy_simple(quotess) f_macro_string_rangess_t_destroy_simple(quotess)

  #define f_macro_fss_commentss_t_resize(status, quotess, new_length) f_macro_string_rangess_t_resize(status, quotess, new_length)
  #define f_macro_fss_commentss_t_adjust(status, quotess, new_length) f_macro_string_rangess_t_adjust(status, quotess, new_length)
#endif // _di_f_fss_commentss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_comment_h
