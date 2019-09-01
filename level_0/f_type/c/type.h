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

#ifndef _di_f_types_normal
  #define f_s_int         signed int
  #define f_s_long        signed long
  #define f_s_short       signed short
  #define f_s_long_long   signed long long
  #define f_s_short_short signed short
  #define f_s_double      double
  #define f_s_long_double long double
  #define f_u_int         unsigned int
  #define f_u_short       unsigned short
  #define f_u_short_short unsigned short
  #define f_u_long        unsigned long
  #define f_u_long_long   unsigned long long
  #define f_u_double      double
  #define f_u_long_double long double
  #define f_bool          unsigned short
#endif // _di_f_types_normal

/**
 * The minimal types represent to the system admin or whomever else handles compilation that the data type should NOT be smaller than the specified size, but can be any size larger.
 */
#ifndef _di_f_types_min
  #define f_min_s_int          f_s_int
  #define f_min_s_short        f_s_short
  #define f_min_s_long         f_s_long
  #define f_min_s_short_short  f_s_short_short
  #define f_min_s_long_long    f_s_long_long
  #define f_min_s_double       f_s_double
  #define f_min_s_long_double  f_s_long_double
  #define f_min_u_int          f_u_int
  #define f_min_u_short        f_u_short
  #define f_min_u_long         f_u_long
  #define f_min_u_short_short  f_u_short_short
  #define f_min_u_long_long    f_u_long_long
  #define f_min_u_double       f_u_double
  #define f_min_u_long_double  f_u_long_double
#endif // _di_f_types_min

/**
 * The maximum types represent to the system admin or whomever else handles compilation that the data type should NOT be larger than the specified size, but can be any size smaller.
 */
#ifndef _di_f_types_max
  #define f_max_s_int          f_s_int
  #define f_max_s_short        f_s_short
  #define f_max_s_long         f_s_long
  #define f_max_s_short_short  f_s_short_short
  #define f_max_s_long_long    f_s_long_long
  #define f_max_s_double       f_s_double
  #define f_max_s_long_double  f_s_long_double
  #define f_max_u_int          f_u_int
  #define f_max_u_short        f_u_short
  #define f_max_u_long         f_u_long
  #define f_max_u_short_short  f_u_short_short
  #define f_max_u_long_long    f_u_long_long
  #define f_max_u_double       f_u_double
  #define f_max_u_long_double  f_u_long_double
#endif // _di_f_types_max

#ifndef _di_f_status_
  typedef uint16_t f_status;

  // The c language gives warnings about return types of constants.
  // Remove the const for c, but keep it for c++, which is only for function call declarations & prototypes.
  // Do not declare these for the return data types themselves, instead use f_status; only use these for function prototypes and declarations.
  #ifdef __cplusplus
    #define f_return_status const f_status
  #else
    #define f_return_status f_status
  #endif // __cplusplus
#endif // _di_f_status_

/**
 * Defines the maximum size to be supported.
 * Ideally these don't get optimized away and are detected at runtime as a result of the bitwise operator.
 */
#ifndef _di_f_types_sizes_
  #define f_unsigned_char_size        ((unsigned char) -1)
  #define f_unsigned_short_size       ((unsigned short) -1)
  #define f_unsigned_int_size         ((unsigned int) -1)
  #define f_unsigned_long_size        ((unsigned long) -1)
  #define f_unsigned_long_long_size   ((unsigned long long) -1)
  #define f_unsigned_double_size      ((unsigned double) -1)
  #define f_unsigned_long_double_size ((unsigned double) -1)
  #define f_signed_char_size          (((unsigned char) -1) / 2)
  #define f_signed_short_size         (((unsigned short) -1) / 2)
  #define f_signed_int_size           (((unsigned int) -1) / 2)
  #define f_signed_long_size          (((unsigned long) -1) / 2)
  #define f_signed_long_long_size     (((unsigned long long) -1) / 2)
#endif // _di_f_types_sizes_

#ifndef _di_f_types_standard_output_
  #define f_standard_debug   stdout
  #define f_standard_error   stderr
  #define f_standard_input   stdin
  #define f_standard_output  stdout
  #define f_standard_warning stdout
#endif // _di_f_types_standard_output_

/**
 * Defines a variable to be used by arrays.
 */
#ifndef _di_f_array_length_
  typedef f_s_long      f_array_length;
  typedef f_s_int       f_array_length_short;
  typedef f_s_long_long f_array_length_long;
#endif // _di_f_array_length_

#ifndef _di_f_gcc_specific_
#define f_gcc_attribute_visibility_internal __attribute__((visibility("internal")))
#endif // _di_f_gcc_specific_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_types_h
