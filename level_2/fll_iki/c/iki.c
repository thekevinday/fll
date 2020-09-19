#include "iki.h"
#include "private-iki.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_iki_content_escape_
  f_return_status fll_iki_content_escape(const f_string_static_t content, const uint8_t quote, f_string_dynamic_t *escaped) {
    #ifndef _di_level_0_parameter_checking_
      if (content.used > content.size) return F_status_set_error(F_parameter);
      if (quote != f_iki_syntax_quote_single && quote != f_iki_syntax_quote_double) return F_status_set_error(F_parameter);
      if (escaped->used > escaped->size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const f_string_range_t range = f_macro_string_range_t_initialize(content.used);

    return private_fll_iki_content_partial_escape(content, range, quote, escaped);
  }
#endif // _di_fll_iki_content_escape_

#ifndef _di_fll_iki_content_partial_escape_
  f_return_status fll_iki_content_partial_escape(const f_string_static_t content, const f_string_range_t range, const uint8_t quote, f_string_dynamic_t *escaped) {
    #ifndef _di_level_0_parameter_checking_
      if (content.used > content.size) return F_status_set_error(F_parameter);
      if (range.start > range.stop) return F_status_set_error(F_parameter);
      if (range.start >= content.used) return F_status_set_error(F_parameter);
      if (quote != f_iki_syntax_quote_single && quote != f_iki_syntax_quote_double) return F_status_set_error(F_parameter);
      if (escaped->used > escaped->size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_fll_iki_content_partial_escape(content, range, quote, escaped);
  }
#endif // _di_fll_iki_content_partial_escape_

#ifndef _di_fll_iki_content_escape_un_
  f_return_status fll_iki_content_escape_un(const f_string_static_t content, const uint8_t quote, f_string_dynamic_t *unescaped) {
    #ifndef _di_level_0_parameter_checking_
      if (content.used > content.size) return F_status_set_error(F_parameter);
      if (quote != f_iki_syntax_quote_single && quote != f_iki_syntax_quote_double) return F_status_set_error(F_parameter);
      if (unescaped->used > unescaped->size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const f_string_range_t range = f_macro_string_range_t_initialize(content.used);

    return private_fll_iki_content_partial_escape_un(content, range, quote, unescaped);
  }
#endif // _di_fll_iki_content_escape_un_

#ifndef _di_fll_iki_content_partial_escape_un_
  f_return_status fll_iki_content_partial_escape_un(const f_string_static_t content, const f_string_range_t range, const uint8_t quote, f_string_dynamic_t *unescaped) {
    #ifndef _di_level_0_parameter_checking_
      if (content.used > content.size) return F_status_set_error(F_parameter);
      if (range.start > range.stop) return F_status_set_error(F_parameter);
      if (range.start >= content.used) return F_status_set_error(F_parameter);
      if (quote != f_iki_syntax_quote_single && quote != f_iki_syntax_quote_double) return F_status_set_error(F_parameter);
      if (unescaped->used > unescaped->size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_fll_iki_content_partial_escape_un(content, range, quote, unescaped);
  }
#endif // _di_fll_iki_content_partial_escape_un_

#ifdef __cplusplus
} // extern "C"
#endif
