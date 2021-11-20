#include "utf.h"
#include "private-utf.h"
#include "private-utf_string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_space_
  const uint8_t f_utf_space_em_s[F_utf_space_em_s_length]                     = { 0xe2, 0x80, 0x83 };
  const uint8_t f_utf_space_em_quad_s[F_utf_space_em_quad_s_length]           = { 0xe2, 0x80, 0x81 };
  const uint8_t f_utf_space_em_per_three_s[F_utf_space_em_per_three_s_length] = { 0xe2, 0x80, 0x84 };
  const uint8_t f_utf_space_em_per_four_s[F_utf_space_em_per_four_s_length]   = { 0xe2, 0x80, 0x85 };
  const uint8_t f_utf_space_em_per_six_s[F_utf_space_em_per_six_s_length]     = { 0xe2, 0x80, 0x86 };

  const uint8_t f_utf_space_en_s[F_utf_space_en_s_length]           = { 0xe2, 0x80, 0x82 };
  const uint8_t f_utf_space_en_quad_s[F_utf_space_en_quad_s_length] = { 0xe2, 0x80, 0x80 };

  const uint8_t f_utf_space_line_feed_reverse_s[F_utf_space_line_feed_reverse_s_length] = { 0xc2, 0x8d };
  const uint8_t f_utf_space_line_next_s[F_utf_space_line_next_s_length]                 = { 0xc2, 0x85 };

  const uint8_t f_utf_space_medium_mathematical_s[F_utf_space_medium_mathematical_s_length] = { 0xe2, 0x81, 0x9f };

  const uint8_t f_utf_space_no_break_s[F_utf_space_no_break_s_length]               = { 0xc2, 0xa0 };
  const uint8_t f_utf_space_no_break_narrow_s[F_utf_space_no_break_narrow_s_length] = { 0xe2, 0x80, 0xaf };

  const uint8_t f_utf_space_ogham_s[F_utf_space_ogham_s_length]             = { 0xe1, 0x9a, 0x80 };
  const uint8_t f_utf_space_figure_s[F_utf_space_figure_s_length]           = { 0xe2, 0x80, 0x87 };
  const uint8_t f_utf_space_punctuation_s[F_utf_space_punctuation_s_length] = { 0xe2, 0x80, 0x88 };
  const uint8_t f_utf_space_thin_s[F_utf_space_thin_s_length]               = { 0xe2, 0x80, 0x89 };
  const uint8_t f_utf_space_hair_s[F_utf_space_hair_s_length]               = { 0xe2, 0x80, 0x8a };
  const uint8_t f_utf_space_ideographic_s[F_utf_space_ideographic_s_length] = { 0xe3, 0x80, 0x80 };

  const uint8_t f_utf_space_separator_line_s[F_utf_space_separator_line_s_length]           = { 0xe2, 0x80, 0xa8 };
  const uint8_t f_utf_space_separator_paragraph_s[F_utf_space_separator_paragraph_s_length] = { 0xe2, 0x80, 0xa8 };
#endif // _di_f_utf_space_

#ifndef _di_f_utf_substitute_
  const uint8_t f_utf_substitute_symbol_blank_s[F_utf_substitute_symbol_blank_s_length] = { 0xe2, 0x90, 0xa2 };
  const uint8_t f_utf_substitute_symbol_space_s[F_utf_substitute_symbol_space_s_length] = { 0xe2, 0x90, 0xa0 };

  const uint8_t f_utf_substitute_middle_dot_s[F_utf_substitute_middle_dot_s_length] = { 0xc2, 0xb7 };

  const uint8_t f_utf_substitute_open_box_s[F_utf_substitute_open_box_d_length]                       = { 0xe2, 0x90, 0xa3 };
  const uint8_t f_utf_substitute_open_box_shouldered_s[F_utf_substitute_open_box_shouldered_d_length] = { 0xe2, 0x8d, 0xbd };
#endif // _di_f_utf_substitute_

#ifdef __cplusplus
} // extern "C"
#endif
