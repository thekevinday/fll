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
 *   - none:   Not a quote.
 *   - double: Quote type is a double quote (U+0022).
 *   - grave:  Quote type is a grave (U+0060).
 *   - single: Quote type is a single quote (U+0027).
 */
#ifndef _di_f_fss_quote_type_e_
  enum {
    f_fss_quote_type_none_e = 0,
    f_fss_quote_type_double_e,
    f_fss_quote_type_grave_e,
    f_fss_quote_type_single_e,
  }; // enum
#endif // _di_f_fss_quote_type_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_quote_h
