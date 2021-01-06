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

  #define f_macro_fss_comments_t_new(status, ranges, length) f_macro_string_ranges_t_new(status, ranges, length);

  #define f_macro_fss_comments_t_resize(status, ranges, length) f_macro_string_ranges_t_resize(status, ranges, length);
  #define f_macro_fss_comments_t_adjust(status, ranges, length) f_macro_string_ranges_t_adjust(status, ranges, length);

  #define f_macro_fss_comments_t_delete(status, ranges)  f_macro_string_ranges_t_delete(status, ranges);
  #define f_macro_fss_comments_t_destroy(status, ranges) f_macro_string_ranges_t_destroy(status, ranges);

  #define f_macro_fss_comments_t_delete_simple(ranges)  f_macro_string_ranges_t_delete_simple(ranges);
  #define f_macro_fss_comments_t_destroy_simple(ranges) f_macro_string_ranges_t_destroy_simple(ranges);

  #define f_macro_fss_comments_t_increase(status, ranges) f_macro_string_ranges_t_increase(status, ranges);
  #define f_macro_fss_comments_t_decrease(status, ranges) f_macro_string_ranges_t_decrease(status, ranges);
  #define f_macro_fss_comments_t_decimate(status, ranges) f_macro_string_ranges_t_decimate(status, ranges);

  #define f_macro_fss_comments_t_increase_by(status, ranges, amount) f_macro_string_ranges_t_increase_by(status, ranges, amount);
  #define f_macro_fss_comments_t_decrease_by(status, ranges, amount) f_macro_string_ranges_t_decrease_by(status, ranges, amount);
  #define f_macro_fss_comments_t_decimate_by(status, ranges, amount) f_macro_string_ranges_t_decimate_by(status, ranges, amount);
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

  #define f_macro_fss_commentss_t_clear(quotess) f_macro_string_rangess_t_clear(quotess);

  #define f_macro_fss_commentss_t_new(status, quotess, length) f_macro_string_rangess_t_new(status, quotess, length);

  #define f_macro_fss_commentss_t_resize(status, quotess, length) f_macro_string_rangess_t_resize(status, quotess, length);
  #define f_macro_fss_commentss_t_adjust(status, quotess, length) f_macro_string_rangess_t_adjust(status, quotess, length);

  #define f_macro_fss_commentss_t_delete(status, quotess)  f_macro_string_rangess_t_delete(status, quotess);
  #define f_macro_fss_commentss_t_destroy(status, quotess) f_macro_string_rangess_t_destroy(status, quotess);

  #define f_macro_fss_commentss_t_delete_simple(quotess)  f_macro_string_rangess_t_delete_simple(quotess);
  #define f_macro_fss_commentss_t_destroy_simple(quotess) f_macro_string_rangess_t_destroy_simple(quotess);
#endif // _di_f_fss_commentss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_comment_h
