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

  #define f_fss_comment_t_initialize f_string_range_t_initialize

  #define macro_f_fss_comment_t_initialize(length) macro_f_string_range_t_initialize2(length)

  #define macro_f_fss_comment_t_clear(comment) macro_f_string_range_t_clear(comment)
#endif // _di_f_fss_comment_t_

/**
 * An array of f_fss_comment_t.
 *
 * array: The array of fss quote.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_comments_t_
  typedef f_string_ranges_t f_fss_comments_t;

  #define f_fss_comments_t_initialize f_string_ranges_t_initialize

  #define macro_f_fss_comments_t_initialize(array, size, used) macro_f_string_ranges_t_initialize(array, size, used)
  #define macro_f_fss_comments_t_initialize2(array, length)    macro_f_string_ranges_t_initialize2(array, length)

  #define f_fss_comments_t_clear(comments) macro_f_string_ranges_t_clear(comments)

  #define macro_f_fss_comments_t_resize(status, comments, length) macro_f_string_ranges_t_resize(status, comments, length)
  #define macro_f_fss_comments_t_adjust(status, comments, length) macro_f_string_ranges_t_adjust(status, comments, length)

  #define macro_f_fss_comments_t_delete_simple(comments)  macro_f_string_ranges_t_delete_simple(comments)
  #define macro_f_fss_comments_t_destroy_simple(comments) macro_f_string_ranges_t_destroy_simple(comments)

  #define macro_f_fss_comments_t_increase(status, step, comments)      macro_f_string_ranges_t_increase(status, step, comments)
  #define macro_f_fss_comments_t_increase_by(status, comments, amount) macro_f_string_ranges_t_increase_by(status, comments, amount)
  #define macro_f_fss_comments_t_decrease_by(status, comments, amount) macro_f_string_ranges_t_decrease_by(status, comments, amount)
  #define macro_f_fss_comments_t_decimate_by(status, comments, amount) macro_f_string_ranges_t_decimate_by(status, comments, amount)
#endif // _di_f_fss_comments_t_

/**
 * An array of f_fss_comments_t.
 *
 * array: The array of fss quotes.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_commentss_t_
  typedef f_string_rangess_t f_fss_commentss_t;

  #define f_fss_commentss_t_initialize f_string_rangess_t_initialize

  #define macro_f_fss_commentss_t_initialize(array, size, used) macro_f_string_rangess_t_initialize(array, size, used)
  #define macro_f_fss_commentss_t_initialize2(array, length)    macro_f_string_rangess_t_initialize2(array, length)

  #define macro_f_fss_commentss_t_clear(commentss) macro_f_string_rangess_t_clear(commentss)

  #define macro_f_fss_commentss_t_resize(status, commentss, length) macro_f_string_rangess_t_resize(status, commentss, length)
  #define macro_f_fss_commentss_t_adjust(status, commentss, length) macro_f_string_rangess_t_adjust(status, commentss, length)

  #define macro_f_fss_commentss_t_delete_simple(commentss)  macro_f_string_rangess_t_delete_simple(commentss)
  #define macro_f_fss_commentss_t_destroy_simple(commentss) macro_f_string_rangess_t_destroy_simple(commentss)

  #define macro_f_fss_commentss_t_increase(status, step, commentss)      macro_f_string_rangess_t_increase(status, step, commentss)
  #define macro_f_fss_commentss_t_increase_by(status, commentss, amount) macro_f_string_rangess_t_increase_by(status, commentss, amount)
  #define macro_f_fss_commentss_t_decrease_by(status, commentss, amount) macro_f_string_rangess_t_decrease_by(status, commentss, amount)
  #define macro_f_fss_commentss_t_decimate_by(status, commentss, amount) macro_f_string_rangess_t_decimate_by(status, commentss, amount)
#endif // _di_f_fss_commentss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_comment_h
