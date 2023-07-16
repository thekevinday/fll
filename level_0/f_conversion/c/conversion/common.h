/**
 * FLL - Level 0
 *
 * Project: Conversion
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by project conversion.
 *
 * This is auto-included by conversion.h and should not need to be explicitly included.
 */
#ifndef _F_conversion_common_h
#define _F_conversion_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Provide custom conversion digit limits based on selected type sizes.
 *
 * These designate the number of digits required to represent some number for some base unit.
 *
 * 64-bit is the designed default.
 */
#ifndef _di_f_conversion_d_
  #ifndef _di_f_type_number_64_t_
    #define F_conversion_digits_binary_unsigned_d 64
    #define F_conversion_digits_binary_signed_d   63

    #define F_conversion_digits_octal_unsigned_d 22
    #define F_conversion_digits_octal_signed_d   22

    #define F_conversion_digits_decimal_unsigned_d 19
    #define F_conversion_digits_decimal_signed_d   19

    #define F_conversion_digits_duodecimal_unsigned_d 18
    #define F_conversion_digits_duodecimal_signed_d   18

    #define F_conversion_digits_hexidecimal_unsigned_d 16
    #define F_conversion_digits_hexidecimal_signed_d   16
  #endif // _di_f_type_number_64_t_

  #ifdef _en_f_type_number_32_t_
    #define F_conversion_digits_binary_unsigned_d 32
    #define F_conversion_digits_binary_signed_d   31

    #define F_conversion_digits_octal_unsigned_d 10
    #define F_conversion_digits_octal_signed_d   10

    #define F_conversion_digits_decimal_unsigned_d 9
    #define F_conversion_digits_decimal_signed_d   9

    #define F_conversion_digits_duodecimal_unsigned_d 8
    #define F_conversion_digits_duodecimal_signed_d   8

    #define F_conversion_digits_hexidecimal_unsigned_d 8
    #define F_conversion_digits_hexidecimal_signed_d   8
  #endif // _en_f_type_number_32_t_

  #ifdef _en_f_type_number_128_t_
    #define F_conversion_digits_binary_unsigned_d 128
    #define F_conversion_digits_binary_signed_d   127

    #define F_conversion_digits_octal_unsigned_d 43
    #define F_conversion_digits_octal_signed_d   43

    #define F_conversion_digits_decimal_unsigned_d 38
    #define F_conversion_digits_decimal_signed_d   38

    #define F_conversion_digits_duodecimal_unsigned_d 36
    #define F_conversion_digits_duodecimal_signed_d   36

    #define F_conversion_digits_hexidecimal_unsigned_d 32
    #define F_conversion_digits_hexidecimal_signed_d   32
  #endif // _en_f_type_number_128_t_
#endif // _di_f_conversion_d_

/**
 * Provide a structure for customizing conversion settings for a conversion function to use.
 *
 * Properties:
 *   - base:  The base unit the number is to be represented as, only the numbers 2 through 16 are supported as a base.
 *   - flag:  Store flags from f_conversion_data_flag_*.
 *   - width: The number of digits representing a minimum width (a width of 0, should result in not printing a 0 when the number is 0).
 */
#ifndef _di_f_conversion_data_t_
  typedef struct {
    uint8_t base;
    uint16_t flag;

    int width;
  } f_conversion_data_t;

  #define f_conversion_data_t_initialize { 10, 0, 1 }

  #define macro_f_conversion_data_t_initialize_1(base, flag, width) { base, flag, width }

  #define macro_f_conversion_data_t_clear(data) \
    data.base = 0; \
    data.flag = 0; \
    data.width = 0;
#endif // _di_f_conversion_data_t_

/**
 * The defines for conversion data.
 *
 * f_conversion_data_base_*_c:
 *   - 2:  Basic base-2 conversion structure.
 *   - 8:  Basic base-8 conversion structure.
 *   - 10: Basic base-10 conversion structure.
 *   - 12: Basic base-12 conversion structure.
 *   - 16: Basic base-16 conversion structure.
 */
#ifndef _di_f_conversion_data_c_
  #ifndef _di_f_conversion_data_base_2_c_
    extern const f_conversion_data_t f_conversion_data_base_2_c;
  #endif // _di_f_conversion_data_base_2_c_

  #ifndef _di_f_conversion_data_base_8_c_
    extern const f_conversion_data_t f_conversion_data_base_8_c;
  #endif // _di_f_conversion_data_base_8_c_

  #ifndef _di_f_conversion_data_base_10_c_
    extern const f_conversion_data_t f_conversion_data_base_10_c;
  #endif // _di_f_conversion_data_base_10_c_

  #ifndef _di_f_conversion_data_base_12_c_
    extern const f_conversion_data_t f_conversion_data_base_12_c;
  #endif // _di_f_conversion_data_base_12_c_

  #ifndef _di_f_conversion_data_base_16_c_
    extern const f_conversion_data_t f_conversion_data_base_16_c;
  #endif // _di_f_conversion_data_base_16_c_
#endif // _di_f_conversion_data_c_

/**
 * Define flags used by f_conversion_data_t.
 *
 * f_conversion_data_flag_*:
 *   - align_left:      Use left-justification.
 *   - base_prepend:    Prepend the base character, such as "0x", or "0X", defaulting to lowercase (this includes base 10) (does nothing for unsupported base units).
 *   - base_upper:      Any alphabet characters in the number are made uppercase rather than lowercase and when *_base_prepend flag is used, use uppercase in the base prepend.
 *   - endian_big:      Use big-endian rather than host byte order or little-endian when converting.
 *   - endian_little:   Use little-endian rather than host byte order or big-endian when converting.
 *   - exponent:        Use exponent rather than decimal for printing double values.
 *   - exponent_either: Use either exponent or decimila for printing double values.
 *   - exponent_upper:  When using exponent, display the exponent 'e' as uppercase 'E'.
 *   - sign_always:     Always show the signs ("+" or "-").
 *   - sign_pad:        If the sign is not to be shown, then add a space as a placeholder (ignored when *_sign_always is used).
 *   - zeros_leading:   If the number has fewer digits that specified in the padding, then display leading zeros to fill the pad length.
 *
 * Supported base prepend base units:
 *   - base 2:  0b, 0B.
 *   - base 8:  0o, 0O.
 *   - base 10: 0t, 0T.
 *   - base 12: 0d, 0D.
 *   - base 16: 0x, 0X.
 */
#ifndef _di_f_conversion_data_flag_d_
  #define F_conversion_data_flag_align_left_d      0x1
  #define F_conversion_data_flag_base_prepend_d    0x2
  #define F_conversion_data_flag_base_upper_d      0x4
  #define F_conversion_data_flag_endian_big_d      0x8
  #define F_conversion_data_flag_endian_little_d   0x10
  #define F_conversion_data_flag_exponent_d        0x20
  #define F_conversion_data_flag_exponent_either_d 0x40
  #define F_conversion_data_flag_exponent_upper_d  0x80
  #define F_conversion_data_flag_sign_always_d     0x100
  #define F_conversion_data_flag_sign_pad_d        0x200
  #define F_conversion_data_flag_zeros_leading_d   0x400
#endif // _di_f_conversion_data_flag_d_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_conversion_common_h
