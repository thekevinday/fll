/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides datatype re-definitions
 * If your compiler lacks the ability to produce such, simply re-define them as needed
 * An "ideal" definition for a standard expected size would be:
 *   char:      2^8   = 256
 *   short:     2^16  = 65536
 *   int:       2^32  = 4294967296
 *   long:      2^64  = 1.84467e19
 *   long long: 2^128 = 3.40282e38
 *
 * If you need exact size, use one of the following:
 *   int8_t:   2^7  (8-bit  signed)
 *   uint8_t:  2^8  (8-bit  unsigned)
 *   int16_t:  2^15 (16-bit signed)
 *   uint16_t: 2^16 (16-bit unsigned)
 *   int32_t:  2^31 (32-bit signed)
 *   uint32_t: 2^32 (32-bit unsigned)
 *   int64_t:  2^63 (64-bit signed)
 *   uint64_t: 2^64 (64-bit unsigned)
 */
#ifndef _F_types_h
#define _F_types_h

// libc includes
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Boolean type.
 */
#ifndef _di_f_type_bool_
  typedef uint8_t f_bool;
#endif // _di_f_type_bool_

/**
 * Status type.
 */
#ifndef _di_f_type_status_
  typedef uint16_t f_status;

  // The c language gives warnings about return types of constants.
  // Remove the const for c, but keep it for c++, which is only for function call declarations & prototypes.
  // Do not declare these for the return data types themselves, instead use f_status; only use these for function prototypes and declarations.
  #ifdef __cplusplus
    #define f_return_status const f_status
  #else
    #define f_return_status f_status
  #endif // __cplusplus
#endif // _di_f_type_status_

/**
 * Defines the maximum size to be supported.
 *
 * The max size is to be the (max supported size - 1) such that that last number can be used for overflow operations.
 */
#ifndef _di_f_type_sizes_
  #define f_unsigned_char_size        (((uint8_t) -1) - 1)
  #define f_unsigned_short_size       (((unsigned short) -1) - 1)
  #define f_unsigned_int_size         (((unsigned int) -1) - 1)
  #define f_unsigned_long_size        (((unsigned long) -1) - 1)
  #define f_unsigned_long_long_size   (((unsigned long long) -1) - 1)
  #define f_unsigned_double_size      (((unsigned double) -1) - 1)
  #define f_unsigned_long_double_size (((unsigned double) -1) - 1)
  #define f_signed_char_size          ((((uint8_t) -1) / 2) - 1)
  #define f_signed_short_size         ((((unsigned short) -1) / 2) - 1)
  #define f_signed_int_size           ((((unsigned int) -1) / 2) - 1)
  #define f_signed_long_size          ((((unsigned long) -1) / 2) - 1)
  #define f_signed_long_long_size     ((((unsigned long long) -1) / 2) - 1)
#endif // _di_f_type_sizes_

/**
 * Standard Input/Output types.
 *
 * For most systems, there is no standard warning nor is there a standard debug.
 * Therefore, these will map to standard output.
 */
#ifndef _di_f_type_standard_input_output_
  #define f_standard_debug   stdout
  #define f_standard_error   stderr
  #define f_standard_input   stdin
  #define f_standard_output  stdout
  #define f_standard_warning stdout
#endif // _di_f_type_standard_input_output_

/**
 * Defines a variable to be used by arrays.
 */
#ifndef _di_f_array_length_
  typedef long      f_array_length;
  typedef int       f_array_length_short;
  typedef long long f_array_length_long;
#endif // _di_f_array_length_

/**
 * GCC-specific features.
 *
 * Use these macros for GCC-specific tweaks so that if GCC is not supported then they can be easily disabled.
 *
 * f_gcc_attribute_visibility_internal provides a way to make some functions effectively private.
 *
 * @todo there is probably some sort of macro that GCC likely defines that can be utilized here to automatically enable/disable this.
 */
#ifndef _di_f_gcc_specific_
  #define f_gcc_attribute_visibility_internal __attribute__((visibility("internal")))
#endif // _di_f_gcc_specific_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_types_h
