/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines common string data.
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_string_common_h
#define _F_string_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * BUG: for whatever reason strnlen is considered not included with -Wall, even with __USE_GNU defined.
 *      therefore this gets defined here.
 */
#ifdef _en_BUG_strnlen_
  extern size_t strnlen (const char *string, size_t max_length);
#endif // _en_BUG_strnlen_

/**
 * Define the basic string type.
 *
 * Dynamic allocation macros are provided, but it is recommended to utilize the f_string_dynamic_t for dynamic allocation.
 */
#ifndef _di_f_string_t_
  typedef char *f_string_t;

  #define f_string_t_initialize 0

  #define f_macro_string_t_clear(string) string = 0;

  #define f_macro_string_t_resize(status, string, length_old, length_new) status = f_memory_resize(length_old, length_new, sizeof(f_string_t), (void **) & string);
  #define f_macro_string_t_adjust(status, string, length_old, length_new) status = f_memory_adjust(length_old, length_new, sizeof(f_string_t), (void **) & string);

  #define f_macro_string_t_delete_simple(string, length)  f_memory_resize(length, 0, sizeof(f_string_t), (void **) & string);
  #define f_macro_string_t_destroy_simple(string, length) f_memory_adjust(length, 0, sizeof(f_string_t), (void **) & string);
#endif // _di_f_string_t_

#ifndef _di_f_string_length_t_
  typedef f_number_unsigned_t f_string_length_t;

  // string size is set to (size - 4) to compensate for UTF-8 4-byte character such that it can easily act as a (size - 1) regardless of UTF-8.
  #define f_string_length_t_size     0xfffffffffffffffb
  #define f_string_length_t_size_max f_number_t_size_max_unsigned

  #define f_string_length_t_printf string_format_long_integer
#endif // _di_f_string_length_t_

/**
 * A structure containing an array of string lengths.
 *
 * array: the array of string lengths.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_lengths_t_
  typedef struct {
    f_string_length_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_lengths_t;

  #define f_string_lengths_t_initialize { 0, 0, 0 }

  #define f_macro_string_lengths_t_clear(string_lengths) f_macro_memory_structures_clear(string_lengths)

  #define f_macro_string_lengths_t_resize(status, string_lengths, length) f_macro_memory_structure_resize(status, string_lengths, f_string_length_t, length)
  #define f_macro_string_lengths_t_adjust(status, string_lengths, length) f_macro_memory_structure_adjust(status, string_lengths, f_string_length_t, length)

  #define f_macro_string_lengths_t_delete_simple(string_lengths)  f_macro_memory_structure_delete_simple(string_lengths, f_string_length_t)
  #define f_macro_string_lengths_t_destroy_simple(string_lengths) f_macro_memory_structure_destroy_simple(string_lengths, f_string_length_t)

  #define f_macro_string_lengths_t_increase(status, string_lengths)            f_macro_memory_structure_increase(status, string_lengths, f_string_length_t)
  #define f_macro_string_lengths_t_increase_by(status, string_lengths, amount) f_macro_memory_structure_increase_by(status, string_lengths, f_string_length_t, amount)
  #define f_macro_string_lengths_t_decrease_by(status, string_lengths, amount) f_macro_memory_structure_decrease_by(status, string_lengths, f_string_length_t, amount)
  #define f_macro_string_lengths_t_decimate_by(status, string_lengths, amount) f_macro_memory_structure_decimate_by(status, string_lengths, f_string_length_t, amount)
#endif // _di_f_string_lengths_t_

/**
 * This holds an array of f_string_lengths_t.
 *
 * array: the array of string lenths arrays.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_string_lengthss_t_
  typedef struct {
    f_string_lengths_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_string_lengthss_t;

  #define f_string_lengthss_t_initialize { 0, 0, 0 }

  #define f_macro_string_lengthss_t_clear(lengthss) f_macro_memory_structures_clear(lengthss)

  #define f_macro_string_lengthss_t_resize(status, lengthss, length) f_macro_memory_structures_resize(status, lengthss, f_string_length_t, f_string_lengths_t, length, f_array_length_t)
  #define f_macro_string_lengthss_t_adjust(status, lengthss, length) f_macro_memory_structures_adjust(status, lengthss, f_string_length_t, f_string_lengths_t, length, f_array_length_t)

  #define f_macro_string_lengthss_t_delete_simple(lengthss)  f_macro_memory_structures_delete_simple(lengthss, f_string_length_t, f_string_lengths_t)
  #define f_macro_string_lengthss_t_destroy_simple(lengthss) f_macro_memory_structures_destroy_simple(lengthss, f_string_length_t, f_string_lengths_t)

  #define f_macro_string_lengthss_t_increase(status, string_lengths) f_macro_memory_structures_increase(status, string_lengths, f_string_length_t, f_array_length_t)
  #define f_macro_string_lengthss_t_increase_by(status, string_lengths, amount) f_macro_memory_structures_increase_by(status, string_lengths, f_string_length_t, f_array_length_t, amount)
  #define f_macro_string_lengthss_t_decrease_by(status, string_lengths, amount) f_macro_memory_structures_decrease_by(status, string_lengths, f_string_length_t, f_string_lengths_t, f_array_length_t, amount)
  #define f_macro_string_lengthss_t_decimate_by(status, string_lengths, amount) f_macro_memory_structures_decimate_by(status, string_lengths, f_string_length_t, f_string_lengths_t, f_array_length_t, amount)
#endif // _di_f_string_lengthss_t_

/**
 * Define the end of line character.
 * FLL forbids '\r' and '\r\n' as end of line characters, \r will be silently ignored.
 */
#ifndef _di_f_string_eol_s_
  #define f_string_eol "\n"
  #define f_string_eol_length 1

  const extern f_string_t f_string_eol_s;
#endif // _di_f_string_eol_s_

#ifndef _di_f_string_empty_s_
  const extern f_string_t f_string_empty_s;
#endif // _di_f_string_empty_s_

#ifndef _di_f_string_placeholder_s_
  #define f_string_placeholder ""
  #define f_string_placeholder_length 1

  const extern f_string_t f_string_placeholder_s;
#endif // _di_f_string_placeholder_s_

#ifndef _di_f_string_space_s_
  #define f_string_space " "
  #define f_string_space_length 1

  const extern f_string_t f_string_space_s;
#endif // _di_f_string_space_s_

#ifndef _di_string_format_s_
  #define f_string_format_string             "%s"
  #define f_string_format_character          "%c"
  #define f_string_format_wide_string        "%ls"
  #define f_string_format_wide_character     "%lc"
  #define f_string_format_integer            "%i"
  #define f_string_format_unsigned           "%u"
  #define f_string_format_digit              "%d"
  #define f_string_format_float              "%f"
  #define f_string_format_short_integer      "%hi"
  #define f_string_format_short_unsigned     "%hu"
  #define f_string_format_long_integer       "%li"
  #define f_string_format_long_unsigned      "%lu"
  #define f_string_format_long_double        "%ld"
  #define f_string_format_long_long_integer  "%lli"
  #define f_string_format_long_long_unsigned "%llu"

  extern const f_string_t f_string_format_string_s;
  extern const f_string_t f_string_format_character_s;
  extern const f_string_t f_string_format_wide_string_s;
  extern const f_string_t f_string_format_wide_character_s;
  extern const f_string_t f_string_format_integer_s;
  extern const f_string_t f_string_format_unsigned_s;
  extern const f_string_t f_string_format_digit_s;
  extern const f_string_t f_string_format_float_s;
  extern const f_string_t f_string_format_short_integer_s;
  extern const f_string_t f_string_format_short_unsigned_s;
  extern const f_string_t f_string_format_long_integer_s;
  extern const f_string_t f_string_format_long_unsigned_s;
  extern const f_string_t f_string_format_long_double_s;
  extern const f_string_t f_string_format_long_long_integer_s;
  extern const f_string_t f_string_format_long_long_unsigned_s;
#endif // _di_string_format_s_

#ifndef _di_f_array_length_printf_
  #define f_array_length_printf       string_format_integer
  #define f_array_length_short_printf string_format_short_integer
  #define f_array_length_long_printf  string_format_long_integer
#endif // _di_f_array_length_printf_

/**
 * Provide a set of ASCII strings.
 *
 * This is not intended to be exhaustive or language-specific.
 * Instead, this is for very common uses such as converting a hex-digit string into a number.
 * These are standardized not be the language, per-say, but instead by the specific standard (such as hexidecimal).
 *
 * @todo provide most (printable) ASCII-characters.
 */
#ifndef _di_string_ascii_s_
  #define f_string_ascii_0 "0"
  #define f_string_ascii_1 "1"
  #define f_string_ascii_2 "2"
  #define f_string_ascii_3 "3"
  #define f_string_ascii_4 "4"
  #define f_string_ascii_5 "5"
  #define f_string_ascii_6 "6"
  #define f_string_ascii_7 "7"
  #define f_string_ascii_8 "8"
  #define f_string_ascii_9 "9"

  #define f_string_ascii_a "a"
  #define f_string_ascii_b "b"
  #define f_string_ascii_c "c"
  #define f_string_ascii_d "d"
  #define f_string_ascii_e "e"
  #define f_string_ascii_f "f"
  #define f_string_ascii_g "g"
  #define f_string_ascii_h "h"
  #define f_string_ascii_i "i"
  #define f_string_ascii_j "j"
  #define f_string_ascii_k "k"
  #define f_string_ascii_l "l"
  #define f_string_ascii_m "m"
  #define f_string_ascii_n "n"
  #define f_string_ascii_o "o"
  #define f_string_ascii_p "p"
  #define f_string_ascii_q "q"
  #define f_string_ascii_r "r"
  #define f_string_ascii_s "s"
  #define f_string_ascii_t "t"
  #define f_string_ascii_u "u"
  #define f_string_ascii_v "v"
  #define f_string_ascii_w "w"
  #define f_string_ascii_x "x"
  #define f_string_ascii_y "y"
  #define f_string_ascii_z "z"

  #define f_string_ascii_A "A"
  #define f_string_ascii_B "B"
  #define f_string_ascii_C "C"
  #define f_string_ascii_D "D"
  #define f_string_ascii_E "E"
  #define f_string_ascii_F "F"
  #define f_string_ascii_G "G"
  #define f_string_ascii_H "H"
  #define f_string_ascii_I "I"
  #define f_string_ascii_J "J"
  #define f_string_ascii_K "K"
  #define f_string_ascii_L "L"
  #define f_string_ascii_M "M"
  #define f_string_ascii_N "N"
  #define f_string_ascii_O "O"
  #define f_string_ascii_P "P"
  #define f_string_ascii_Q "Q"
  #define f_string_ascii_R "R"
  #define f_string_ascii_S "S"
  #define f_string_ascii_T "T"
  #define f_string_ascii_U "U"
  #define f_string_ascii_V "V"
  #define f_string_ascii_W "W"
  #define f_string_ascii_X "X"
  #define f_string_ascii_Y "Y"
  #define f_string_ascii_Z "Z"

  #define f_string_ascii_comma          ","
  #define f_string_ascii_colon          ":"
  #define f_string_ascii_colon_semi     ";"
  #define f_string_ascii_equal          "="
  #define f_string_ascii_minus          "-"
  #define f_string_ascii_period         "."
  #define f_string_ascii_plus           "+"
  #define f_string_ascii_slash_forward  "/"
  #define f_string_ascii_slash_backward "\\"
  #define f_string_ascii_tilde          "~"

  extern const f_string_t f_string_ascii_0_s;
  extern const f_string_t f_string_ascii_1_s;
  extern const f_string_t f_string_ascii_2_s;
  extern const f_string_t f_string_ascii_3_s;
  extern const f_string_t f_string_ascii_4_s;
  extern const f_string_t f_string_ascii_5_s;
  extern const f_string_t f_string_ascii_6_s;
  extern const f_string_t f_string_ascii_7_s;
  extern const f_string_t f_string_ascii_8_s;
  extern const f_string_t f_string_ascii_9_s;

  extern const f_string_t f_string_ascii_a_s;
  extern const f_string_t f_string_ascii_b_s;
  extern const f_string_t f_string_ascii_c_s;
  extern const f_string_t f_string_ascii_d_s;
  extern const f_string_t f_string_ascii_e_s;
  extern const f_string_t f_string_ascii_f_s;
  extern const f_string_t f_string_ascii_g_s;
  extern const f_string_t f_string_ascii_h_s;
  extern const f_string_t f_string_ascii_i_s;
  extern const f_string_t f_string_ascii_j_s;
  extern const f_string_t f_string_ascii_k_s;
  extern const f_string_t f_string_ascii_l_s;
  extern const f_string_t f_string_ascii_m_s;
  extern const f_string_t f_string_ascii_n_s;
  extern const f_string_t f_string_ascii_o_s;
  extern const f_string_t f_string_ascii_p_s;
  extern const f_string_t f_string_ascii_q_s;
  extern const f_string_t f_string_ascii_r_s;
  extern const f_string_t f_string_ascii_s_s;
  extern const f_string_t f_string_ascii_t_s;
  extern const f_string_t f_string_ascii_u_s;
  extern const f_string_t f_string_ascii_v_s;
  extern const f_string_t f_string_ascii_w_s;
  extern const f_string_t f_string_ascii_x_s;
  extern const f_string_t f_string_ascii_y_s;
  extern const f_string_t f_string_ascii_z_s;

  extern const f_string_t f_string_ascii_A_s;
  extern const f_string_t f_string_ascii_B_s;
  extern const f_string_t f_string_ascii_C_s;
  extern const f_string_t f_string_ascii_D_s;
  extern const f_string_t f_string_ascii_E_s;
  extern const f_string_t f_string_ascii_F_s;
  extern const f_string_t f_string_ascii_G_s;
  extern const f_string_t f_string_ascii_H_s;
  extern const f_string_t f_string_ascii_I_s;
  extern const f_string_t f_string_ascii_J_s;
  extern const f_string_t f_string_ascii_K_s;
  extern const f_string_t f_string_ascii_L_s;
  extern const f_string_t f_string_ascii_M_s;
  extern const f_string_t f_string_ascii_N_s;
  extern const f_string_t f_string_ascii_O_s;
  extern const f_string_t f_string_ascii_P_s;
  extern const f_string_t f_string_ascii_Q_s;
  extern const f_string_t f_string_ascii_R_s;
  extern const f_string_t f_string_ascii_S_s;
  extern const f_string_t f_string_ascii_T_s;
  extern const f_string_t f_string_ascii_U_s;
  extern const f_string_t f_string_ascii_V_s;
  extern const f_string_t f_string_ascii_W_s;
  extern const f_string_t f_string_ascii_X_s;
  extern const f_string_t f_string_ascii_Y_s;
  extern const f_string_t f_string_ascii_Z_s;

  extern const f_string_t f_string_ascii_comma_s;
  extern const f_string_t f_string_ascii_colon_s;
  extern const f_string_t f_string_ascii_colon_semi_s;
  extern const f_string_t f_string_ascii_equal_s;
  extern const f_string_t f_string_ascii_minus_s;
  extern const f_string_t f_string_ascii_period_s;
  extern const f_string_t f_string_ascii_plus_s;
  extern const f_string_t f_string_ascii_slash_forward_s;
  extern const f_string_t f_string_ascii_slash_backward_s;
  extern const f_string_t f_string_ascii_tilde_s;
#endif // _di_string_ascii_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_common_h
