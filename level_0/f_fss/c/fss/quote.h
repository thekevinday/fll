/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
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
 *   - backtick: Quote type is a backtick.
 *   - double:   Quote type is a double quote.
 *   - single:   Quote type is a single quote.
 */
#ifndef _di_f_fss_quote_type_
  enum {
    f_fss_quote_type_none_e = 0,
    f_fss_quote_type_backtick_e,
    f_fss_quote_type_double_e,
    f_fss_quote_type_single_e,
  };
#endif // _di_f_fss_quote_type_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_quote_h
