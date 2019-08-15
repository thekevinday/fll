#include <level_0/utf.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_is_bom_
  f_return_status f_utf_is_bom(const f_string character, const f_u_short maxWidth) {
    #ifndef _di_level_0_parameter_checking_
      if (maxWidth < 1) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_u_short width = f_macro_utf_byte_width(*character);

    if (width == 1) {
      return f_false;
    }

    if (width > maxWidth) {
      return f_error_set_error(f_maybe);
    }

    if (width == 3) {
      if (!memcmp(character, f_utf_bom, width)) {
        return f_true;
      }
    }

    return f_false;
  }
#endif // _di_f_utf_is_bom_

#ifndef _di_f_utf_is_space_
  f_return_status f_utf_is_space(const f_string character, const f_u_short maxWidth) {
    #ifndef _di_level_0_parameter_checking_
      if (maxWidth < 1) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_u_short width = f_macro_utf_byte_width(*character);

    if (width == 1) {
      return f_false;
    }

    if (width > maxWidth) {
      return f_error_set_error(f_maybe);
    }

    if (width == 2) {
      if (!memcmp(character, f_utf_space_no_break, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_line_feed_reverse, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_line_next, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_substitute_middle_dot, width)) {
        return f_true;
      }

      return f_false;
    }

    if (width == 3) {
      if (!memcmp(character, f_utf_space_no_break_narrow, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_en, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_en_quad, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_en_quad, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_em, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_em_quad, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_em_per_three, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_em_per_four, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_em_per_six, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_figure, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_punctuation, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_thin, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_hair, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_separator_line, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_separator_paragraph, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_ogham, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_ideographic, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_medium_mathematical, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_substitute_symbol_blank, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_substitute_symbol_space, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_substitute_open_box, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_substitute_open_box_shouldered, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_bom, width)) {
        return f_true;
      }

      return f_false;
    }

    return f_false;
  }
#endif // _di_f_utf_is_space_

#ifndef _di_f_utf_is_substitute_
  f_return_status f_utf_is_substitute(const f_string character, const f_u_short maxWidth) {
    #ifndef _di_level_0_parameter_checking_
      if (maxWidth < 1) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_u_short width = f_macro_utf_byte_width(*character);

    if (width == 1) {
      return f_false;
    }

    if (width > maxWidth) {
      return f_error_set_error(f_maybe);
    }

    if (width == 2) {
      if (!memcmp(character, f_utf_substitute_middle_dot, width)) {
        return f_true;
      }

      return f_false;
    }

    if (width == 3) {
      if (!memcmp(character, f_utf_substitute_symbol_blank, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_substitute_symbol_space, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_substitute_open_box, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_substitute_open_box_shouldered, width)) {
        return f_true;
      }

      return f_false;
    }

    return f_false;
  }
#endif // _di_f_utf_is_substitute_

#ifndef _di_f_utf_is_whitespace_
  f_return_status f_utf_is_whitespace(const f_string character, const f_u_short maxWidth) {
    #ifndef _di_level_0_parameter_checking_
      if (maxWidth < 1) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_u_short width = f_macro_utf_byte_width(*character);

    if (width == 1) {
      return f_false;
    }

    if (width > maxWidth) {
      return f_error_set_error(f_maybe);
    }

    if (width == 2) {
      if (!memcmp(character, f_utf_space_no_break, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_line_feed_reverse, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_line_next, width)) {
        return f_true;
      }

      return f_false;
    }

    if (width == 3) {
      if (!memcmp(character, f_utf_space_no_break_narrow, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_en, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_en_quad, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_en_quad, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_em, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_em_quad, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_em_per_three, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_em_per_four, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_em_per_six, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_figure, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_punctuation, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_thin, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_hair, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_separator_line, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_separator_paragraph, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_ogham, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_ideographic, width)) {
        return f_true;
      }

      if (!memcmp(character, f_utf_space_medium_mathematical, width)) {
        return f_true;
      }

      return f_false;
    }

    return f_false;
  }
#endif // _di_f_utf_is_whitespace_

#ifdef __cplusplus
} // extern "C"
#endif
