#include <level_0/utf.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_is_big_endian_
  f_return_status f_utf_is_big_endian() {
    uint16_t test_int = (0x01 << 8) | 0x02;
    char test_char[2] = {0x01, 0x02};

    if (!memcmp(&test_int, test_char, 2)) {
      return f_true;
    }

    return f_false;
  }
#endif // _di_f_utf_is_big_endian_

#ifndef _di_f_utf_is_
  f_return_status f_utf_is(const f_string character, const f_u_short max_width) {
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

    return f_true;
  }
#endif // _di_f_utf_is_

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

#ifndef _di_f_utf_is_character_
  f_return_status f_utf_is_character(const f_utf_character character) {
    f_u_short width = f_macro_utf_character_width_is(character);

    if (width == 0) {
      return f_false;
    }
    else if (width == 1) {
      return f_status_is_error(f_invalid_utf);
    }

    return f_true;
  }
#endif // _di_f_utf_is_

#ifndef _di_f_utf_is_graph_
  f_return_status f_utf_is_graph(const f_string character, const f_u_short max_width) {
    #ifndef _di_level_0_parameter_checking_
      if (max_width < 1) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    if (f_macro_utf_byte_width_is(*character) == 0) {
      if (isgraph(*character)) {
        return f_true;
      }

      return f_false;
    }

    // For now, just assume that any non-whitespace, non-substitute UTF-8 character is a graph.
    f_status status = f_utf_is_space(character, max_width);

    if (f_status_is_error(status)) {
      return status;
    }
    else if (status == f_true) {
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
      if (isspace(*character)) {
        return f_true;
      }

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
      // there is no substitute character in ASCII.
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
      if (isspace(*character)) {
        return f_true;
      }

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
    // for now, just assume that any non-whitespace, non-substitute utf-8 character is a graph.
    f_status status = f_utf_is_space_character(character);

    if (f_status_is_error(status)) {
      return status;
    }
    else if (status == f_true) {
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
      char ascii = character >> 24;

      if (isspace(ascii)) {
        return f_true;
      }

      return f_false;
    }
    else if (width == 1) {
      return f_status_is_error(f_invalid_utf);
    }

    f_bool is_big_endian = f_utf_is_big_endian();

    if (width == 2) {
      uint16_t utf = 0;
      if (is_big_endian) {
        utf = (uint16_t) (character >> 16);
      }
      else {
        utf = (f_macro_utf_character_to_char_2(character) << 8) | f_macro_utf_character_to_char_1(character);
      }

      if (!memcmp(&utf, f_utf_space_no_break, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_line_feed_reverse, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_line_next, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_substitute_middle_dot, width)) {
        return f_true;
      }

      return f_false;
    }

    if (width == 3) {
      uint32_t utf = 0;
      if (is_big_endian) {
        utf = character;
      }
      else {
        utf = (f_macro_utf_character_to_char_3(character) << 24) | (f_macro_utf_character_to_char_2(character) << 16) | (f_macro_utf_character_to_char_1(character) << 8);
      }

      if (!memcmp(&utf, f_utf_space_no_break_narrow, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_en, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_en_quad, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_en_quad, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_em, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_em_quad, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_em_per_three, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_em_per_four, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_em_per_six, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_figure, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_punctuation, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_thin, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_hair, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_separator_line, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_separator_paragraph, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_ogham, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_ideographic, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_medium_mathematical, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_substitute_symbol_blank, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_substitute_symbol_space, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_substitute_open_box, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_substitute_open_box_shouldered, width)) {
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
      // there is no substitute character in ASCII.
      return f_false;
    }
    else if (width == 1) {
      return f_status_is_error(f_invalid_utf);
    }

    f_bool is_big_endian = f_utf_is_big_endian();

    if (width == 2) {
      uint16_t utf = 0;
      if (is_big_endian) {
        utf = (uint16_t) (character >> 16);
      }
      else {
        utf = (f_macro_utf_character_to_char_2(character) << 8) | f_macro_utf_character_to_char_1(character);
      }

      if (!memcmp(&utf, f_utf_substitute_middle_dot, width)) {
        return f_true;
      }

      return f_false;
    }

    if (width == 3) {
      uint32_t utf = 0;
      if (is_big_endian) {
        utf = character;
      }
      else {
        utf = (f_macro_utf_character_to_char_3(character) << 24) | (f_macro_utf_character_to_char_2(character) << 16) | (f_macro_utf_character_to_char_1(character) << 8);
      }

      if (!memcmp(&utf, f_utf_substitute_symbol_blank, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_substitute_symbol_space, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_substitute_open_box, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_substitute_open_box_shouldered, width)) {
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
      char ascii = character >> 24;

      if (isspace(ascii)) {
        return f_true;
      }

      return f_false;
    }
    else if (width == 1) {
      return f_status_is_error(f_invalid_utf);
    }

    f_bool is_big_endian = f_utf_is_big_endian();

    if (width == 2) {
      uint16_t utf = 0;
      if (is_big_endian) {
        utf = (uint16_t) (character >> 16);
      }
      else {
        utf = (f_macro_utf_character_to_char_2(character) << 8) | f_macro_utf_character_to_char_1(character);
      }

      if (!memcmp(&utf, f_utf_space_no_break, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_line_feed_reverse, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_line_next, width)) {
        return f_true;
      }

      return f_false;
    }

    if (width == 3) {
      uint32_t utf = 0;
      if (is_big_endian) {
        utf = character;
      }
      else {
        utf = (f_macro_utf_character_to_char_3(character) << 24) | (f_macro_utf_character_to_char_2(character) << 16) | (f_macro_utf_character_to_char_1(character) << 8);
      }

      if (!memcmp(&utf, f_utf_space_no_break_narrow, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_en, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_en_quad, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_en_quad, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_em, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_em_quad, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_em_per_three, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_em_per_four, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_em_per_six, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_figure, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_punctuation, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_thin, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_hair, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_separator_line, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_separator_paragraph, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_ogham, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_ideographic, width)) {
        return f_true;
      }

      if (!memcmp(&utf, f_utf_space_medium_mathematical, width)) {
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
      return f_status_is_error(f_invalid_utf);
    }

    if (width > max_width) {
      return f_status_set_error(f_failure);
    }

    *utf_character = 0;
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

#ifndef _di_f_utf_character_to_char_
  f_return_status f_utf_character_to_char(const f_utf_character utf_character, f_string *character, f_u_short *max_width) {
    #ifndef _di_level_0_parameter_checking_
      if (utf_character == 0) return f_status_set_error(f_invalid_parameter);
      if (max_width == 0 && *character != 0) return f_status_set_error(f_invalid_parameter);
      if (max_width != 0 && *character == 0) return f_status_set_error(f_invalid_parameter);
      if (max_width != 0 && *max_width > 4) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = f_none;

    f_u_short width = f_macro_utf_character_width_is(utf_character);

    if (max_width == 0) {
      f_macro_string_new(status, *character, width);

      if (f_status_is_error(status)) return status;

      width = 1;
      *max_width = 1;
    }
    else if (width == 1) {
      return f_status_is_error(f_invalid_utf);
    }
    else if (width > *max_width) {
      return f_status_set_error(f_failure);
    }

    *max_width = width;

    if (f_utf_is_big_endian()) {
      memcpy(*character, &utf_character, sizeof(char) * width);
    }
    else {
      uint32_t utf = 0;

      if (width == 1) {
        utf = f_macro_utf_character_to_char_1(utf_character) << 24;
      }
      else if (width == 2) {
        utf = (f_macro_utf_character_to_char_2(utf_character) << 24) | (f_macro_utf_character_to_char_1(utf_character) << 16);
      }
      else if (width == 3) {
        utf = (f_macro_utf_character_to_char_3(utf_character) << 24) | (f_macro_utf_character_to_char_2(utf_character) << 16) | (f_macro_utf_character_to_char_1(utf_character) << 8);
      }
      else if (width == 4) {
        utf = (f_macro_utf_character_to_char_4(utf_character) << 24) | (f_macro_utf_character_to_char_3(utf_character) << 16) | (f_macro_utf_character_to_char_2(utf_character) << 8) | f_macro_utf_character_to_char_1(utf_character);
      }

      memcpy(*character, &utf, sizeof(char) * width);
    }

    return f_none;
  }
#endif // _di_f_utf_character_to_char_

#ifdef __cplusplus
} // extern "C"
#endif
