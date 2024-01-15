#include "iki.h"
#include "private-iki.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_iki_content_escape_
  f_status_t fll_iki_content_escape(const f_string_static_t content, const f_string_static_t quote, f_string_dynamic_t * const escaped) {
    #ifndef _di_level_2_parameter_checking_
      if (!quote.used) return F_status_set_error(F_parameter);
      if (quote.string[0] != f_iki_syntax_quote_single_s.string[0] && quote.string[0] != f_iki_syntax_quote_double_s.string[0] && quote.string[0] != f_iki_syntax_quote_grave_s.string[0]) return F_status_set_error(F_parameter);
      if (escaped->used > escaped->size) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    const f_range_t range = macro_f_range_t_initialize_2(content.used);

    return private_fll_iki_content_partial_escape(content, range, quote.string[0], escaped);
  }
#endif // _di_fll_iki_content_escape_

#ifndef _di_fll_iki_content_partial_escape_
  f_status_t fll_iki_content_partial_escape(const f_string_static_t content, const f_range_t range, const f_string_static_t quote, f_string_dynamic_t * const escaped) {
    #ifndef _di_level_2_parameter_checking_
      if (range.start > range.stop) return F_status_set_error(F_parameter);
      if (range.start >= content.used) return F_status_set_error(F_parameter);
      if (!quote.used) return F_status_set_error(F_parameter);
      if (quote.string[0] != f_iki_syntax_quote_single_s.string[0] && quote.string[0] != f_iki_syntax_quote_double_s.string[0] && quote.string[0] != f_iki_syntax_quote_grave_s.string[0]) return F_status_set_error(F_parameter);
      if (escaped->used > escaped->size) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    return private_fll_iki_content_partial_escape(content, range, quote.string[0], escaped);
  }
#endif // _di_fll_iki_content_partial_escape_

#ifndef _di_fll_iki_content_partial_unescape_
  f_status_t fll_iki_content_partial_unescape(const f_string_static_t content, const f_range_t range, const f_string_static_t quote, f_string_dynamic_t * const unescaped) {
    #ifndef _di_level_2_parameter_checking_
      if (range.start > range.stop) return F_status_set_error(F_parameter);
      if (range.start >= content.used) return F_status_set_error(F_parameter);
      if (!quote.used) return F_status_set_error(F_parameter);
      if (quote.string[0] != f_iki_syntax_quote_single_s.string[0] && quote.string[0] != f_iki_syntax_quote_double_s.string[0] && quote.string[0] != f_iki_syntax_quote_grave_s.string[0]) return F_status_set_error(F_parameter);
      if (unescaped->used > unescaped->size) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    return private_fll_iki_content_partial_unescape(content, range, quote.string[0], unescaped);
  }
#endif // _di_fll_iki_content_partial_unescape_

#ifndef _di_fll_iki_content_unescape_
  f_status_t fll_iki_content_unescape(const f_string_static_t content, const f_string_static_t quote, f_string_dynamic_t * const unescaped) {
    #ifndef _di_level_2_parameter_checking_
      if (!quote.used) return F_status_set_error(F_parameter);
      if (quote.string[0] != f_iki_syntax_quote_single_s.string[0] && quote.string[0] != f_iki_syntax_quote_double_s.string[0] && quote.string[0] != f_iki_syntax_quote_grave_s.string[0]) return F_status_set_error(F_parameter);
      if (unescaped->used > unescaped->size) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    const f_range_t range = macro_f_range_t_initialize_2(content.used);

    return private_fll_iki_content_partial_unescape(content, range, quote.string[0], unescaped);
  }
#endif // _di_fll_iki_content_unescape_

#ifdef __cplusplus
} // extern "C"
#endif
