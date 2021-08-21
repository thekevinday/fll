/**
 * FLL - Level 0
 *
 * Project: Conversion
 * API Version: 0.5
 * Licenses: lgplv2.1
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
#ifndef _di_f_type_number_64_t_
  #define f_conversion_digits_binary_unsigned 64
  #define f_conversion_digits_binary_signed   63

  #define f_conversion_digits_octal_unsigned 22
  #define f_conversion_digits_octal_signed   22

  #define f_conversion_digits_decimal_unsigned 19
  #define f_conversion_digits_decimal_signed   19

  #define f_conversion_digits_duodecimal_unsigned 18
  #define f_conversion_digits_duodecimal_signed   18

  #define f_conversion_digits_hexidecimal_unsigned 16
  #define f_conversion_digits_hexidecimal_signed   16
#endif // _di_f_type_number_64_t_

#ifdef _en_f_type_number_32_t_
  #define f_conversion_digits_binary_unsigned 32
  #define f_conversion_digits_binary_signed   31

  #define f_conversion_digits_octal_unsigned 10
  #define f_conversion_digits_octal_signed   10

  #define f_conversion_digits_decimal_unsigned 9
  #define f_conversion_digits_decimal_signed   9

  #define f_conversion_digits_duodecimal_unsigned 8
  #define f_conversion_digits_duodecimal_signed   8

  #define f_conversion_digits_hexidecimal_unsigned 8
  #define f_conversion_digits_hexidecimal_signed   8
#endif // _en_f_type_number_32_t_

#ifdef _en_f_type_number_128_t_
  #define f_conversion_digits_binary_unsigned 128
  #define f_conversion_digits_binary_signed   127

  #define f_conversion_digits_octal_unsigned 43
  #define f_conversion_digits_octal_signed   43

  #define f_conversion_digits_decimal_unsigned 38
  #define f_conversion_digits_decimal_signed   38

  #define f_conversion_digits_duodecimal_unsigned 36
  #define f_conversion_digits_duodecimal_signed   36

  #define f_conversion_digits_hexidecimal_unsigned 32
  #define f_conversion_digits_hexidecimal_signed   32
#endif // _en_f_type_number_128_t_

/**
 * Provide a structure for customizing conversion settings for a conversion function using this.
 *
 * base:  The base unit the number is to be represented as, only the numbers 2 through 16 are supported as a base.
 * flag:  Store flags from f_conversion_data_flag_*.
 * width: The number of digits representing a minimum width (a width of 0, should result in not printing a 0 when the number is 0).
 */
#ifndef _di_f_conversion_data_t_
  typedef struct {
    uint8_t base;
    uint8_t flag;

    int width;
  } f_conversion_data_t;

  #define f_conversion_data_t_initialize { 10, 0, 1 }

  #define macro_f_conversion_data_t_initialize(base, flag, width) { base, flag, width }

  #define macro_f_conversion_data_t_clear(data) \
    data.base = 0; \
    data.flag = 0; \
    data.width = 0;
#endif // _di_f_conversion_data_t_

/**
 * The defines for conversion data.
 *
 * f_conversion_data_base_*:
 * - 2:  Basic base-2 conversion structure.
 * - 8:  Basic base-8 conversion structure.
 * - 10: Basic base-10 conversion structure.
 * - 12: Basic base-12 conversion structure.
 * - 16: Basic base-16 conversion structure.
 */
#ifndef _di_f_conversion_data_t_defines_
  extern const f_conversion_data_t f_conversion_data_base_2_s;
  extern const f_conversion_data_t f_conversion_data_base_8_s;
  extern const f_conversion_data_t f_conversion_data_base_10_s;
  extern const f_conversion_data_t f_conversion_data_base_12_s;
  extern const f_conversion_data_t f_conversion_data_base_16_s;
#endif // _di_f_conversion_data_t_defines_

/**
 * Define flags used by f_conversion_data_t.
 *
 * f_conversion_data_flag_*:
 * - align_left:    Use left-justification.
 * - base_prepend:  Prepend the base character, such as "0x", or "0X", defaulting to lowercase (this includes base 10) (does nothing for unsupported base units).
 * - base_upper:    Any alphabet characters in the number are made uppercase rather than lowercase and when *_base_prepend flag is used, use uppercase in the base prepend.
 * - sign_always:   Always show the signs ("+" or "-").
 * - sign_pad:      If the sign is not to be shown, then add a space as a placeholder (ignored when *_sign_always is used).
 * - zeros_leading: If the number has fewer digits that specified in the padding, then display leading zeros to fill the pad length.
 *
 * Supported base prepend base units:
 * - base 2:  0b, 0B.
 * - base 8:  0o, 0O.
 * - base 10: 0t, 0T.
 * - base 12: 0d, 0D.
 * - base 16: 0x, 0X.
 */
#ifndef _di_f_conversion_data_flag_
  #define f_conversion_data_flag_align_left    0x1
  #define f_conversion_data_flag_base_prepend  0x2
  #define f_conversion_data_flag_base_upper    0x4
  #define f_conversion_data_flag_sign_always   0x8
  #define f_conversion_data_flag_sign_pad      0x10
  #define f_conversion_data_flag_zeros_leading 0x20
#endif // _di_f_conversion_data_flag_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_conversion_common_h
