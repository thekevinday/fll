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

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_conversion_common_h
