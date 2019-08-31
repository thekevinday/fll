#include <level_0/utf.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_is_bom_
  f_return_status f_utf_is_bom(const f_string character, const f_u_short max_width) {
    #ifndef _di_level_0_parameter_checking_
      if (max_width < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_u_short width = f_macro_utf_byte_width_is(*character);

    if (width == 0) {
      return f_false;
    }
    else if (width == 1) {
      return f_status_is_error(f_incomplete_utf);
    }

    if (width > max_width) {
      return f_status_set_error(f_maybe);
    }

    if (width == 3) {
      if (!memcmp(character, f_utf_bom, width)) {
        return f_true;
      }
    }

    return f_false;
  }
#endif // _di_f_utf_is_bom_

#ifndef _di_f_utf_is_graph_
  f_return_status f_utf_is_graph(const f_string character, const f_u_short max_width) {
    #ifndef _di_level_0_parameter_checking_
      if (max_width < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_u_short width = f_macro_utf_byte_width_is(*character);

    if (width == 0) {
      return f_false;
    }
    else if (width == 1) {
      return f_status_is_error(f_incomplete_utf);
    }

    // Do not operate on UTF-8 fragments that are not the first byte of the character.
    if (width == 1) {
      return f_status_set_error(f_incomplete_utf);
    }

    if (width > max_width) {
      return f_status_set_error(f_maybe);
    }

    // for now, just assume that any non-whitespace, non-substitute utf-8 character is a graph.

    if (f_utf_is_space(character, max_width) == f_true) {
      return f_false;
    }

    if (f_utf_is_bom(character, max_width) == f_true) {
      return f_false;
    }

    return f_true;
  }
#endif // _di_f_utf_is_graph_

#ifndef _di_f_utf_is_space_
  f_return_status f_utf_is_space(const f_string character, const f_u_short max_width) {
    #ifndef _di_level_0_parameter_checking_
      if (max_width < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_u_short width = f_macro_utf_byte_width_is(*character);

    if (width == 0) {
      return f_false;
    }
    else if (width == 1) {
      return f_status_is_error(f_incomplete_utf);
    }

    if (width > max_width) {
      return f_status_set_error(f_maybe);
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

      return f_false;
    }

    return f_false;
  }
#endif // _di_f_utf_is_space_

#ifndef _di_f_utf_is_substitute_
  f_return_status f_utf_is_substitute(const f_string character, const f_u_short max_width) {
    #ifndef _di_level_0_parameter_checking_
      if (max_width < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_u_short width = f_macro_utf_byte_width_is(*character);

    if (width == 0) {
      return f_false;
    }
    else if (width == 1) {
      return f_status_is_error(f_incomplete_utf);
    }

    if (width > max_width) {
      return f_status_set_error(f_maybe);
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
  f_return_status f_utf_is_whitespace(const f_string character, const f_u_short max_width) {
    #ifndef _di_level_0_parameter_checking_
      if (max_width < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_u_short width = f_macro_utf_byte_width_is(*character);

    if (width == 0) {
      return f_false;
    }
    else if (width == 1) {
      return f_status_is_error(f_incomplete_utf);
    }

    if (width > max_width) {
      return f_status_set_error(f_maybe);
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

#ifndef _di_f_utf_is_bom_character_
  f_return_status f_utf_is_bom_character(const f_utf_character character) {
    if (character == f_utf_character_mask_bom) {
      return f_true;
    }

    return f_false;
  }
#endif // _di_f_utf_is_bom_character_

#ifndef _di_f_utf_is_graph_character_
  f_return_status f_utf_is_graph_character(const f_utf_character character) {
    f_u_short width = f_macro_utf_character_width_is(character);

    if (width == 0) {
      return f_false;
    }
    else if (width == 1) {
      return f_status_is_error(f_incomplete_utf);
    }

    // for now, just assume that any non-whitespace, non-substitute utf-8 character is a graph.

    if (f_utf_is_space_character(character) == f_true) {
      return f_false;
    }

    if (f_utf_is_bom_character(character) == f_true) {
      return f_false;
    }

    return f_true;
  }
#endif // _di_f_utf_is_graph_character_

#ifndef _di_f_utf_is_space_character_
  f_return_status f_utf_is_space_character(const f_utf_character character) {
    f_u_short width = f_macro_utf_character_width_is(character);

    if (width == 0) {
      return f_false;
    }
    else if (width == 1) {
      return f_status_is_error(f_incomplete_utf);
    }

    if (width == 2) {
      char utf[2] = { f_macro_utf_character_to_char_1(character), f_macro_utf_character_to_char_2(character) };

      if (utf[0] == f_utf_space_no_break[0] && utf[1] == f_utf_space_no_break[1]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_line_feed_reverse[0] && utf[1] == f_utf_space_line_feed_reverse[1]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_line_next[0] && utf[1] == f_utf_space_line_next[1]) {
        return f_true;
      }

      if (utf[0] == f_utf_substitute_middle_dot[0] && utf[1] == f_utf_substitute_middle_dot[1]) {
        return f_true;
      }

      return f_false;
    }

    if (width == 3) {
      char utf[3] = { f_macro_utf_character_to_char_1(character), f_macro_utf_character_to_char_2(character), f_macro_utf_character_to_char_3(character) };

      if (utf[0] == f_utf_space_no_break_narrow[0] && utf[1] == f_utf_space_no_break_narrow[1] && utf[2] == f_utf_space_no_break_narrow[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_en[0] && utf[1] == f_utf_space_en[1] && utf[2] == f_utf_space_en[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_en_quad[0] && utf[1] == f_utf_space_en_quad[1] && utf[2] == f_utf_space_en_quad[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_en_quad[0] && utf[1] == f_utf_space_en_quad[1] && utf[2] == f_utf_space_en_quad[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_em[0] && utf[1] == f_utf_space_em[1] && utf[2] == f_utf_space_em[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_em_quad[0] && utf[1] == f_utf_space_em_quad[1] && utf[2] == f_utf_space_em_quad[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_em_per_three[0] && utf[1] == f_utf_space_em_per_three[1] && utf[2] == f_utf_space_em_per_three[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_em_per_four[0] && utf[1] == f_utf_space_em_per_four[1] && utf[2] == f_utf_space_em_per_four[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_em_per_six[0] && utf[1] == f_utf_space_em_per_six[1] && utf[2] == f_utf_space_em_per_six[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_figure[0] && utf[1] == f_utf_space_figure[1] && utf[2] == f_utf_space_figure[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_punctuation[0] && utf[1] == f_utf_space_punctuation[1] && utf[2] == f_utf_space_punctuation[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_thin[0] && utf[1] == f_utf_space_thin[1] && utf[2] == f_utf_space_thin[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_hair[0] && utf[1] == f_utf_space_hair[1] && utf[2] == f_utf_space_hair[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_separator_line[0] && utf[1] == f_utf_space_separator_line[1] && utf[2] == f_utf_space_separator_line[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_separator_paragraph[0] && utf[1] == f_utf_space_separator_paragraph[1] && utf[2] == f_utf_space_separator_paragraph[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_ogham[0] && utf[1] == f_utf_space_ogham[1] && utf[2] == f_utf_space_ogham[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_ideographic[0] && utf[1] == f_utf_space_ideographic[1] && utf[2] == f_utf_space_ideographic[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_medium_mathematical[0] && utf[1] == f_utf_space_medium_mathematical[1] && utf[2] == f_utf_space_medium_mathematical[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_substitute_symbol_blank[0] && utf[1] == f_utf_substitute_symbol_blank[1] && utf[2] == f_utf_substitute_symbol_blank[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_substitute_symbol_space[0] && utf[1] == f_utf_substitute_symbol_space[1] && utf[2] == f_utf_substitute_symbol_space[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_substitute_open_box[0] && utf[1] == f_utf_substitute_open_box[1] && utf[2] == f_utf_substitute_open_box[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_substitute_open_box_shouldered[0] && utf[1] == f_utf_substitute_open_box_shouldered[1] && utf[2] == f_utf_substitute_open_box_shouldered[2]) {
        return f_true;
      }

      return f_false;
    }

    return f_false;
  }
#endif // _di_f_utf_is_space_character_

#ifndef _di_f_utf_is_substitute_character_
  f_return_status f_utf_is_substitute_character(const f_utf_character character) {
    f_u_short width = f_macro_utf_character_width_is(character);

    if (width == 0) {
      return f_false;
    }
    else if (width == 1) {
      return f_status_is_error(f_incomplete_utf);
    }

    if (width == 2) {
      char utf[2] = { f_macro_utf_character_to_char_1(character), f_macro_utf_character_to_char_2(character) };

      if (utf[0] == f_utf_substitute_middle_dot[0] && utf[1] == f_utf_substitute_middle_dot[1]) {
        return f_true;
      }

      return f_false;
    }

    if (width == 3) {
      char utf[3] = { f_macro_utf_character_to_char_1(character), f_macro_utf_character_to_char_2(character), f_macro_utf_character_to_char_3(character) };

      if (utf[0] == f_utf_substitute_symbol_blank[0] && utf[1] == f_utf_substitute_symbol_blank[1] && utf[2] == f_utf_substitute_symbol_blank[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_substitute_symbol_space[0] && utf[1] == f_utf_substitute_symbol_space[1] && utf[2] == f_utf_substitute_symbol_space[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_substitute_open_box[0] && utf[1] == f_utf_substitute_open_box[1] && utf[2] == f_utf_substitute_open_box[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_substitute_open_box_shouldered[0] && utf[1] == f_utf_substitute_open_box_shouldered[1] && utf[2] == f_utf_substitute_open_box_shouldered[2]) {
        return f_true;
      }

      return f_false;
    }

    return f_false;
  }
#endif // _di_f_utf_is_substitute_character_

#ifndef _di_f_utf_is_whitespace_character_
  f_return_status f_utf_is_whitespace_character(const f_utf_character character) {
    f_u_short width = f_macro_utf_character_width_is(character);

    if (width == 0) {
      return f_false;
    }
    else if (width == 1) {
      return f_status_is_error(f_incomplete_utf);
    }

    // Do not operate on UTF-8 fragments that are not the first byte of the character.
    if (width == 1) {
      return f_status_set_error(f_incomplete_utf);
    }

    if (width == 2) {
      char utf[2] = { f_macro_utf_character_to_char_1(character), f_macro_utf_character_to_char_2(character) };

      if (utf[0] == f_utf_space_no_break[0] && utf[1] == f_utf_space_no_break[1]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_line_feed_reverse[0] && utf[1] == f_utf_space_line_feed_reverse[1]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_line_next[0] && utf[1] == f_utf_space_line_next[1]) {
        return f_true;
      }

      return f_false;
    }

    if (width == 3) {
      char utf[3] = { f_macro_utf_character_to_char_1(character), f_macro_utf_character_to_char_2(character), f_macro_utf_character_to_char_3(character) };

      if (utf[0] == f_utf_space_no_break_narrow[0] && utf[1] == f_utf_space_no_break_narrow[1] && utf[2] == f_utf_space_no_break_narrow[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_en[0] && utf[1] == f_utf_space_en[1] && utf[2] == f_utf_space_en[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_en_quad[0] && utf[1] == f_utf_space_en_quad[1] && utf[2] == f_utf_space_en_quad[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_en_quad[0] && utf[1] == f_utf_space_en_quad[1] && utf[2] == f_utf_space_en_quad[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_em[0] && utf[1] == f_utf_space_em[1] && utf[2] == f_utf_space_em[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_em_quad[0] && utf[1] == f_utf_space_em_quad[1] && utf[2] == f_utf_space_em_quad[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_em_per_three[0] && utf[1] == f_utf_space_em_per_three[1] && utf[2] == f_utf_space_em_per_three[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_em_per_four[0] && utf[1] == f_utf_space_em_per_four[1] && utf[2] == f_utf_space_em_per_four[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_em_per_six[0] && utf[1] == f_utf_space_em_per_six[1] && utf[2] == f_utf_space_em_per_six[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_figure[0] && utf[1] == f_utf_space_figure[1] && utf[2] == f_utf_space_figure[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_punctuation[0] && utf[1] == f_utf_space_punctuation[1] && utf[2] == f_utf_space_punctuation[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_thin[0] && utf[1] == f_utf_space_thin[1] && utf[2] == f_utf_space_thin[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_hair[0] && utf[1] == f_utf_space_hair[1] && utf[2] == f_utf_space_hair[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_separator_line[0] && utf[1] == f_utf_space_separator_line[1] && utf[2] == f_utf_space_separator_line[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_separator_paragraph[0] && utf[1] == f_utf_space_separator_paragraph[1] && utf[2] == f_utf_space_separator_paragraph[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_ogham[0] && utf[1] == f_utf_space_ogham[1] && utf[2] == f_utf_space_ogham[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_ideographic[0] && utf[1] == f_utf_space_ideographic[1] && utf[2] == f_utf_space_ideographic[2]) {
        return f_true;
      }

      if (utf[0] == f_utf_space_medium_mathematical[0] && utf[1] == f_utf_space_medium_mathematical[1] && utf[2] == f_utf_space_medium_mathematical[2]) {
        return f_true;
      }

      return f_false;
    }

    return f_false;
  }
#endif // _di_f_utf_is_whitespace_character_

#ifndef _di_f_utf_char_to_character_
  f_return_status f_utf_char_to_character(const f_string character, const f_u_short max_width, f_utf_character *utf_character) {
    #ifndef _di_level_0_parameter_checking_
      if (max_width < 1) return f_status_set_error(f_invalid_parameter);
      if (utf_character == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_u_short width = f_macro_utf_byte_width_is(*character);

    if (width == 0) {
      *utf_character = f_macro_utf_character_from_char_1(character[0]);
      return f_none;
    }
    else if (width == 1) {
      return f_status_is_error(f_incomplete_utf);
    }

    if (width > max_width) {
      return f_status_set_error(f_failure);
    }

    memset(utf_character, 0, sizeof(f_utf_character));

    *utf_character |= f_macro_utf_character_to_char_1(character[0]);

    if (width < 2) {
      return f_none;
    }

    *utf_character |= f_macro_utf_character_to_char_2(character[1]);

    if (width == 2) {
      return f_none;
    }

    *utf_character |= f_macro_utf_character_to_char_3(character[2]);

    if (width == 3) {
      return f_none;
    }

    *utf_character |= f_macro_utf_character_to_char_4(character[3]);

    return f_none;
  }
#endif // _di_f_utf_char_to_character_

#ifdef __cplusplus
} // extern "C"
#endif
