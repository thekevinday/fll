#include "color.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_color_strings_s_
  const f_string_t f_color_string_begin_s = "\033[";
  const f_string_t f_color_string_end_s = "m";
  const f_string_t f_color_string_medium_s = ";";

  const f_string_t f_color_string_code_reset_s = "0";
  const f_string_t f_color_string_code_bold_s = "1";
  const f_string_t f_color_string_code_underline_s = "4";
  const f_string_t f_color_string_code_blink_s = "5";
  const f_string_t f_color_string_code_reverse_s = "7";
  const f_string_t f_color_string_code_conceal_s = "8";
  const f_string_t f_color_string_code_black_s = "30";
  const f_string_t f_color_string_code_red_s = "31";
  const f_string_t f_color_string_code_green_s = "32";
  const f_string_t f_color_string_code_yellow_s = "33";
  const f_string_t f_color_string_code_blue_s = "34";
  const f_string_t f_color_string_code_purple_s = "35";
  const f_string_t f_color_string_code_teal_s = "36";
  const f_string_t f_color_string_code_white_s = "37";
  const f_string_t f_color_string_code_black_bg_s = "40";
  const f_string_t f_color_string_code_red_bg_s = "41";
  const f_string_t f_color_string_code_green_bg_s = "42";
  const f_string_t f_color_string_code_yellow_bg_s = "43";
  const f_string_t f_color_string_code_blue_bg_s = "44";
  const f_string_t f_color_string_code_purple_bg_s = "45";
  const f_string_t f_color_string_code_teal_bg_s = "46";
  const f_string_t f_color_string_code_white_bg_s = "47";
  const f_string_t f_color_string_code_bright_black_s = "90";
  const f_string_t f_color_string_code_bright_red_s = "91";
  const f_string_t f_color_string_code_bright_green_s = "92";
  const f_string_t f_color_string_code_bright_yellow_s = "93";
  const f_string_t f_color_string_code_bright_blue_s = "94";
  const f_string_t f_color_string_code_bright_purple_s = "95";
  const f_string_t f_color_string_code_bright_teal_s = "96";
  const f_string_t f_color_string_code_bright_white_s = "97";
  const f_string_t f_color_string_code_bright_black_bg_s = "100";
  const f_string_t f_color_string_code_bright_red_bg_s = "101";
  const f_string_t f_color_string_code_bright_green_bg_s = "102";
  const f_string_t f_color_string_code_bright_yellow_bg_s = "103";
  const f_string_t f_color_string_code_bright_blue_bg_s = "104";
  const f_string_t f_color_string_code_bright_purple_bg_s = "105";
  const f_string_t f_color_string_code_bright_teal_bg_s = "106";
  const f_string_t f_color_string_code_bright_white_bg_s = "107";
#endif // _di_f_color_strings_s_

#ifndef _di_f_color_set_string_empty_s_
  const f_color_set_t f_color_set_empty_s = macro_f_color_set_t_initialize(&f_string_static_empty_s, &f_string_static_empty_s);
#endif // _di_f_color_set_string_empty_s_

#ifdef __cplusplus
} // extern "C"
#endif
