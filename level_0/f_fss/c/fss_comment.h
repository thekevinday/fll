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
 * size:  total amount of allocated space.
 * used:  total number of allocated spaces used.
 */
#ifndef _di_f_fss_comments_t_
  typedef f_string_ranges_t f_fss_comments_t;

  #define f_fss_comments_t_initialize f_string_ranges_t_initialize

  #define f_fss_comments_t_clear(comments) f_macro_string_ranges_t_clear(comments)

  #define f_macro_fss_comments_t_resize(status, comments, length) f_macro_string_ranges_t_resize(status, comments, length)
  #define f_macro_fss_comments_t_adjust(status, comments, length) f_macro_string_ranges_t_adjust(status, comments, length)

  #define f_macro_fss_comments_t_delete_simple(comments)  f_macro_string_ranges_t_delete_simple(comments)
  #define f_macro_fss_comments_t_destroy_simple(comments) f_macro_string_ranges_t_destroy_simple(comments)

  #define f_macro_fss_comments_t_increase(status, comments)            f_macro_string_ranges_t_increase(status, comments)
  #define f_macro_fss_comments_t_increase_by(status, comments, amount) f_macro_string_ranges_t_increase_by(status, comments, amount)
  #define f_macro_fss_comments_t_decrease_by(status, comments, amount) f_macro_string_ranges_t_decrease_by(status, comments, amount)
  #define f_macro_fss_comments_t_decimate_by(status, comments, amount) f_macro_string_ranges_t_decimate_by(status, comments, amount)
#endif // _di_f_fss_comments_t_

/**
 * An array of f_fss_comments_t.
 *
 * array: the array of fss quotes.
 * size:  total amount of allocated space.
 * used:  total number of allocated spaces used.
 */
#ifndef _di_f_fss_commentss_t_
  typedef f_string_rangess_t f_fss_commentss_t;

  #define f_fss_commentss_t_initialize f_string_rangess_t_initialize

  #define f_macro_fss_commentss_t_clear(commentss) f_macro_string_rangess_t_clear(commentss)

  #define f_macro_fss_commentss_t_resize(status, commentss, length) f_macro_string_rangess_t_resize(status, commentss, length)
  #define f_macro_fss_commentss_t_adjust(status, commentss, length) f_macro_string_rangess_t_adjust(status, commentss, length)

  #define f_macro_fss_commentss_t_delete_simple(commentss)  f_macro_string_rangess_t_delete_simple(commentss)
  #define f_macro_fss_commentss_t_destroy_simple(commentss) f_macro_string_rangess_t_destroy_simple(commentss)

  #define f_macro_fss_commentss_t_increase(status, commentss)            f_macro_string_rangess_t_increase(status, commentss)
  #define f_macro_fss_commentss_t_increase_by(status, commentss, amount) f_macro_string_rangess_t_increase_by(status, commentss, amount)
  #define f_macro_fss_commentss_t_decrease_by(status, commentss, amount) f_macro_string_rangess_t_decrease_by(status, commentss, amount)
  #define f_macro_fss_commentss_t_decimate_by(status, commentss, amount) f_macro_string_rangess_t_decimate_by(status, commentss, amount)
#endif // _di_f_fss_commentss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_comment_h
