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
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Status type.
 */
#ifndef _di_f_type_status_
  typedef uint16_t f_status;

  /**
   * The c language gives warnings about return types of constants.
   * Remove the const for c, but keep it for c++, which is only for function call declarations & prototypes.
   * Do not declare these for the return data types themselves, instead use f_status; only use these for function prototypes and declarations.
   */
  #ifdef __cplusplus
    #define f_return_status const f_status
  #else
    #define f_return_status f_status
  #endif // __cplusplus
#endif // _di_f_type_status_

/**
 * Conditional 128-bit support.
 *
 * This should work in GCC, but other compilers this may not be available.
 * When not supported, these will fallback to 64-bit.
 */
#ifndef _di_f_type_int_128_
  #ifdef __SIZEOF_INT128__
    typedef __int128_t  f_int_128;
    typedef __uint128_t f_uint_128;
  #else
    typedef int64_t  f_int_128;
    typedef uint64_t f_uint_128;
  #endif // __SIZEOF_INT128__
#endif // _di_f_type_int_128_

/**
 * Defines the maximum size to be supported.
 *
 * The size is to be the (max supported size - 1) such that that last number can be used for overflow operations.
 *
 * For example, f_type_size_8_negative is 2^7, or -1 to -128, therefore the max size here is -128 - 1 or -127.
 * For example, f_type_size_8_positive is 2^7, or 0 to 127, therefore the max size here is 127 - 1 or 126.
 * For example, f_type_size_8_unsigned is 2^8, or 0 to 255, therefore the max size here is 255 - 1 or 254.
 *
 * The max_size is provided for actual max sizes.
 * For example, f_type_size_8_negative is 2^7, or -1 to -128, therefore the max size here is -128.
 * For example, f_type_size_8_positive is 2^7, or 0 to 127, therefore the max size here is 127.
 * For example, f_type_size_8_unsigned is 2^8, or 0 to 255, therefore the max size here is 255.
 */
#ifndef _di_f_type_sizes_
  #define f_type_size_8_negative 0x7f
  #define f_type_size_8_positive 0x7e
  #define f_type_size_8_unsigned 0xfe

  #define f_type_size_16_negative 0x7fff
  #define f_type_size_16_positive 0x7ffe
  #define f_type_size_16_unsigned 0xfffe

  #define f_type_size_32_negative 0x7fffffff
  #define f_type_size_32_positive 0x7ffffffe
  #define f_type_size_32_unsigned 0xfffffffe

  #define f_type_size_64_negative 0x7fffffffffffffff
  #define f_type_size_64_positive 0x7ffffffffffffffe
  #define f_type_size_64_unsigned 0xfffffffffffffffe

  #ifndef _di_f_type_int_128_
    #define f_type_size_128_negative 0x7fffffffffffffffffffffff
    #define f_type_size_128_positive 0x7ffffffffffffffffffffffe
    #define f_type_size_128_unsigned 0xfffffffffffffffffffffffe
  #else
    #define f_type_size_128_negative f_type_size_64_negative
    #define f_type_size_128_positive f_type_size_64_positive
    #define f_type_size_128_unsigned f_type_size_64_unsigned
  #endif // _di_f_type_int_128_

  #define f_type_size_max_8_negative 0x80
  #define f_type_size_max_8_positive 0x7f
  #define f_type_size_max_8_unsigned 0xff

  #define f_type_size_max_16_negative 0x8000
  #define f_type_size_max_16_positive 0x7fff
  #define f_type_size_max_16_unsigned 0xffff

  #define f_type_size_max_32_negative 0x80000000
  #define f_type_size_max_32_positive 0x7fffffff
  #define f_type_size_max_32_unsigned 0xffffffff

  #define f_type_size_max_64_negative 0x8000000000000000
  #define f_type_size_max_64_positive 0x7fffffffffffffff
  #define f_type_size_max_64_unsigned 0xffffffffffffffff

  #ifndef _di_f_type_int_128_
    #define f_type_size_max_128_negative 0x800000000000000000000000
    #define f_type_size_max_128_positive 0x7fffffffffffffffffffffff
    #define f_type_size_max_128_unsigned 0xffffffffffffffffffffffff
  #else
    #define f_type_size_max_128_negative f_type_size_max_64_negative
    #define f_type_size_max_128_positive f_type_size_max_64_positive
    #define f_type_size_max_128_unsigned f_type_size_max_64_unsigned
  #endif // _di_f_type_int_128_
#endif // _di_f_type_sizes_

/**
 * Custom data type to be used throughout the project to represent general numbers.
 *
 * This is intended to be used in buffers, such as strings, and in argument parameters.
 *
 * Provides additional custom types so that it can be more easily be overwritten.
 * Specifically, there is support for using 32-bit, 64-bit or 128-bit lengths.
 *
 * 64-bit is the designed default.
 */
#ifndef _di_f_type_number_64_
  typedef int64_t  f_number_signed;
  typedef uint64_t f_number_unsigned;

  #define f_type_number_size_unsigned f_type_size_64_unsigned
  #define f_type_number_size_positive f_type_size_64_positive
  #define f_type_number_size_negative f_type_size_64_negative

  #define f_type_number_size_max_unsigned f_type_size_max_64_unsigned
  #define f_type_number_size_max_positive f_type_size_max_64_positive
  #define f_type_number_size_max_negative f_type_size_max_64_negative
#endif // _di_f_type_number_64_

#ifdef _en_f_type_number_32_
  typedef int32_t  f_number_signed;
  typedef uint32_t f_number_unsigned;

  #define f_type_number_size_unsigned f_type_size_32_unsigned
  #define f_type_number_size_positive f_type_size_32_positive
  #define f_type_number_size_negative f_type_size_32_negative

  #define f_type_number_size_max_unsigned f_type_size_max_32_unsigned
  #define f_type_number_size_max_positive f_type_size_max_32_positive
  #define f_type_number_size_max_negative f_type_size_max_32_negative
#endif // _en_f_type_number_32_

#ifdef _en_f_type_number_128_
  typedef f_int_128  f_number_signed;
  typedef f_uint_128 f_number_unsigned;

  #define f_type_number_size_unsigned f_type_size_128_unsigned
  #define f_type_number_size_positive f_type_size_128_positive
  #define f_type_number_size_negative f_type_size_128_negative

  #define f_type_number_size_max_unsigned f_type_size_max_128_unsigned
  #define f_type_number_size_max_positive f_type_size_max_128_positive
  #define f_type_number_size_max_negative f_type_size_max_128_negative
#endif // _en_f_type_number_128_

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
#ifndef _di_f_array_
  typedef f_number_unsigned f_array_length;

  #define f_array_max_size f_type_number_size_unsigned
#endif // _di_f_array_

/**
 * GCC-specific features.
 *
 * Use these macros for GCC-specific tweaks so that if GCC is not supported then they can be easily disabled.
 *
 * f_gcc_attribute_visibility_internal provides a way to make some functions effectively private.
 */
#ifndef _di_f_gcc_specific_
  #define f_gcc_attribute_visibility_default   __attribute__((visibility("default")))
  #define f_gcc_attribute_visibility_hidden    __attribute__((visibility("hidden")))
  #define f_gcc_attribute_visibility_internal  __attribute__((visibility("internal")))
  #define f_gcc_attribute_visibility_protected __attribute__((visibility("protected")))
#endif // _di_f_gcc_specific_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_types_h
