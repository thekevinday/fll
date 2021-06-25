#include "iki.h"
#include "private-iki.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fll_iki_content_escape_) || !defined(_di_fll_iki_content_partial_escape_)
  f_status_t private_fll_iki_content_partial_escape(const f_string_static_t content, const f_string_range_t range, const uint8_t quote, f_string_dynamic_t *escaped) {
    f_status_t status = F_none;

    // ensure escaped is at least the same size as content.
    if (content.used > escaped->size) {
      macro_f_string_dynamic_t_resize(status, (*escaped), content.used);
      if (F_status_is_error(status)) return status;
    }

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t delimits = 0;

    for (; i < content.used; ++i) {

      if (content.string[i] == quote) {
        if (escaped->used + delimits + 2 > escaped->size) {
          status = f_string_dynamic_increase_by(delimits + 2, escaped);
          if (F_status_is_error(status)) return status;
        }

        for (j = 0; j < delimits; ++j) {
          escaped->string[escaped->used++] = f_iki_syntax_slash;
        } // for

        escaped->string[escaped->used++] = f_iki_syntax_slash;
        escaped->string[escaped->used++] = quote;

        delimits = 0;
      }
      else if (content.string[i]) {
        if (escaped->used + 1 > escaped->size) {
          status = f_string_dynamic_increase_by(f_memory_default_allocation_small, escaped);
          if (F_status_is_error(status)) return status;
        }

        if (content.string[i] == f_iki_syntax_slash) {
          ++delimits;
        }
        else {
          delimits = 0;
        }

        escaped->string[escaped->used++] = content.string[i];
      }
    } // for

    // delimits found at the end must be escaped to prevent escaping the end quote.
    if (delimits) {
      if (escaped->used + delimits > escaped->size) {
        status = f_string_dynamic_increase_by(delimits, escaped);
        if (F_status_is_error(status)) return status;
      }

      for (j = 0; j < delimits; ++j) {
        escaped->string[escaped->used++] = f_iki_syntax_slash;
      } // for
    }

    return F_none;
  }
#endif // !defined(_di_fll_iki_content_escape_) || !defined(_di_fll_iki_content_partial_escape_)

#if !defined(_di_fll_iki_content_unescape_) || !defined(_di_fll_iki_content_partial_unescape_)
  f_status_t private_fll_iki_content_partial_unescape(const f_string_static_t content, const f_string_range_t range, const uint8_t quote, f_string_dynamic_t *unescaped) {
    f_status_t status = F_none;

    // ensure escaped is at least the same size as content.
    if (content.used > unescaped->size) {
      macro_f_string_dynamic_t_resize(status, (*unescaped), content.used);
      if (F_status_is_error(status)) return status;
    }

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t delimits = 0;

    const f_array_length_t used = unescaped->used;

    for (; i < content.used; ++i) {

      if (content.string[i] == quote) {

        // reset the used array on failure.
        unescaped->used = used;

        return F_status_set_error(F_syntax);
      }
      else if (content.string[i] == f_iki_syntax_slash) {
        delimits = 1;

        if (i + 1 < content.used) {
          for (j = i + 1; j < content.used; ++j) {

            if (content.string[j] == quote) {
              if (delimits % 2 == 0) {

                // reset the used array on failure.
                unescaped->used = used;

                return F_status_set_error(F_syntax);
              }

              i = j;
              delimits /= 2;

              if (unescaped->used + delimits + 1 > unescaped->size) {
                status = f_string_dynamic_increase_by(delimits + 1, unescaped);
                if (F_status_is_error(status)) return status;
              }

              for (j = 0; j < delimits; ++j) {
                unescaped->string[unescaped->used++] = f_iki_syntax_slash;
              } // for

              delimits = 0;
              unescaped->string[unescaped->used++] = quote;
              break;
            }
            else if (content.string[j] == f_iki_syntax_slash) {
              ++delimits;
            }
            else if (content.string[j]) {
              if (unescaped->used + (j - i) + 1 > unescaped->size) {
                status = f_string_dynamic_increase_by((j - i) + 1, unescaped);
                if (F_status_is_error(status)) return status;
              }

              for (; i <= j; ++i) {
                unescaped->string[unescaped->used++] = content.string[i];
              } // for

              delimits = 0;
              --i;
              break;
            }
          } // for
        }

        // at this point if delimits > 0, then this should be the end of the string.
        if (delimits) {

          // delimits at the end must be even to prevent escaping the closing quote.
          if (delimits % 2) {

            // reset the used array on failure.
            unescaped->used = used;

            return F_status_set_error(F_syntax);
          }

          delimits /= 2;

          if (unescaped->used + delimits > unescaped->size) {
            status = f_string_dynamic_increase_by(delimits, unescaped);
            if (F_status_is_error(status)) return status;
          }

          for (j = 0; j < delimits; ++j) {
            unescaped->string[unescaped->used++] = f_iki_syntax_slash;
          } // for

          break;
        }
      }
      else if (content.string[i]) {
        if (unescaped->used + 1 > unescaped->size) {
          status = f_string_dynamic_increase_by(f_memory_default_allocation_small, unescaped);
          if (F_status_is_error(status)) return status;
        }

        unescaped->string[unescaped->used++] = content.string[i];
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_fll_iki_content_unescape_) || !defined(_di_fll_iki_content_partial_unescape_)

#ifdef __cplusplus
} // extern "C"
#endif
