/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides datatype definitions.
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
 * The size is to be the (max supported size - 1) such that that last number can be used for overflow operations.
 *
 * For example, f_type_size_8_unsigned is 2^8, or 0 to 255, therefore the max size here is 255 - 1 or 254.
 * For example, f_type_size_8_signed is 2^7, or 0 to 127, therefore the max size here is 127 - 1 or 126.
 *
 * The max_size is provided for actual max sizes.
 * For example, f_type_size_8_unsigned is 2^8, or 0 to 255, therefore the max size here is 255.
 * For example, f_type_size_8_signed is 2^7, or 0 to 127, therefore the max size here is 127.
 */
#ifndef _di_f_type_sizes_
  #define f_type_size_8_unsigned  0xfe
  #define f_type_size_8_signed    0x7e
  #define f_type_size_16_unsigned 0xfffe
  #define f_type_size_16_signed   0x7ffe
  #define f_type_size_32_unsigned 0xfffffffe
  #define f_type_size_32_signed   0x7ffffffe
  #define f_type_size_64_unsigned 0xfffffffffffffffe
  #define f_type_size_64_signed   0x7ffffffffffffffe

  #define f_type_size_max_8_unsigned  0xff
  #define f_type_size_max_8_signed    0x7f
  #define f_type_size_max_16_unsigned 0xffff
  #define f_type_size_max_16_signed   0x7fff
  #define f_type_size_max_32_unsigned 0xffffffff
  #define f_type_size_max_32_signed   0x7fffffff
  #define f_type_size_max_64_unsigned 0xffffffffffffffff
  #define f_type_size_max_64_signed   0x7fffffffffffffff
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
