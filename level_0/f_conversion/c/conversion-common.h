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
 * Provide custom conversion scale limits based on selected type sizes.
 *
 * Utilize the f_type_number_* defines to determine the expected sizes to use for the scales.
 *
 * 64-bit is the designed default.
 */
#ifndef _di_f_type_number_64_t_
  #define f_conversion_scale_binary_unsigned 64
  #define f_conversion_scale_binary_signed   63

  #define f_conversion_scale_octal_unsigned 21
  #define f_conversion_scale_octal_signed   20

  #define f_conversion_scale_decimal_unsigned 19
  #define f_conversion_scale_decimal_signed   18

  #define f_conversion_scale_duodecimal_unsigned 17
  #define f_conversion_scale_duodecimal_signed   17

  #define f_conversion_scale_hexidecimal_unsigned 15
  #define f_conversion_scale_hexidecimal_signed   15
#endif // _di_f_type_number_64_t_

#ifdef _en_f_type_number_32_t_
  #define f_conversion_scale_binary_unsigned 32
  #define f_conversion_scale_binary_signed   31

  #define f_conversion_scale_octal_unsigned 10
  #define f_conversion_scale_octal_signed   10

  #define f_conversion_scale_decimal_unsigned 9
  #define f_conversion_scale_decimal_signed   9

  #define f_conversion_scale_duodecimal_unsigned 8
  #define f_conversion_scale_duodecimal_signed   8

  #define f_conversion_scale_hexidecimal_unsigned 7
  #define f_conversion_scale_hexidecimal_signed   7
#endif // _en_f_type_number_32_t_

#ifdef _en_f_type_number_128_t_
  #define f_conversion_scale_binary_unsigned 128
  #define f_conversion_scale_binary_signed   127

  #define f_conversion_scale_octal_unsigned 42
  #define f_conversion_scale_octal_signed   42

  #define f_conversion_scale_decimal_unsigned 38
  #define f_conversion_scale_decimal_signed   38

  #define f_conversion_scale_duodecimal_unsigned 35
  #define f_conversion_scale_duodecimal_signed   35

  #define f_conversion_scale_hexidecimal_unsigned 31
  #define f_conversion_scale_hexidecimal_signed   31
#endif // _en_f_type_number_128_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_conversion_common_h
