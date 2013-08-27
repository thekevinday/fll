/* FLL - Level 0
 * Project:       Types
 * Version:       0.4.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provides datatype re-definitions
 * If your compiler lacks the ability to produce such, simply re-define them as needed
 * An "ideal" definition for a standard expected size would be (64-bit):
 *   char:      2^16  = 65536
 *   short:     2^32  = 4294967296
 *   int:       2^64  = 1.84467e19
 *   long:      2^128 = 3.40282e38
 *   long long: 2^256 = 1.15792e77
 *
 * If you need exact size, use one of the following:
 *   int8_t:   2^8 (signed)
 *   uint8_t:  2^8 (unsigned)
 *   int16_t:  2^16 (signed)
 *   uint16_t: 2^16 (unsigned)
 *   int32_t:  2^32 (signed)
 *   uint32_t: 2^32 (unsigned)
 *   int64_t:  2^64 (signed)
 *   uint64_t: 2^64 (unsigned)
 *
 * TODO: Should a range type be implemented? (ie: f_range_short_long -> min=short, max=long)
 */
#ifndef _F_types_h
#define _F_types_h

// libc includes
#include <sys/stat.h> // contains mode_t, dev_t, gid_t, uid_t, etc..
#include <signal.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_f_types_normal
  #define f_s_int          signed int
  #define f_s_long         signed long
  #define f_s_short        signed short
  #define f_s_long_long    signed long long
  #define f_s_short_short  signed short
  #define f_s_double       double
  #define f_s_long_double  long double
  #define f_u_int          unsigned int
  #define f_u_short        unsigned short
  #define f_u_short_short  unsigned short
  #define f_u_long         unsigned long
  #define f_u_long_long    unsigned long long
  #define f_u_double       double
  #define f_u_long_double  long double
  #define f_char           char                 // should ONLY be char
  #define f_wchar          wchar                // should ONLY be wchar
  #define f_autochar       char                 // can be wchar or char
  #define f_size_t         size_t
  #define f_bool           unsigned short
  #define f_mode_t         mode_t
  #define f_dev_t          dev_t
  #define f_uid_t          uid_t
  #define f_gid_t          gid_t
  #define f_ino_t          ino_t
  #define f_nlink_t        nlink_t
  #define f_off_t          off_t
  #define f_fpos_t         fpos_t
  #define f_file_type      FILE *
  #define f_null           NULL
#endif // _di_f_types_normal

// The minimal types represent to the system admin or whomever else handles compilation that the data type should NOT be smaller than the specified size, but can be any size larger.
// TODO: Should min_char be implemented?
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

// The maximum types represent to the system admin or whomever else handles compilation that the data type should NOT be larger than the specified size, but can be any size smaller.
// TODO: Should max_char be implemented?
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

  // The c language gives warnings about return types of constants, I pretty much hate not being able to forcefully specify that these are not the be changed as that could be a security issue
  // Therefore, I need to remove the const for c, but keep it for c++, thus I define the type f_return_status, which is only for function call declarations & prototypes
  // DO NOT DECLARE THESE FOR THE RETURN DATA TYPES THEMSELVES, USE f_status. ONLY USE THESE FOR FUNCTION PROTOTYPES AND DECLARATIONS
  #ifdef __cplusplus
    #define f_return_status const f_status
  #else
    #define f_return_status f_status
  #endif // __cplusplus
#endif // _di_f_status_

// Defines the maximum size to be supported
// I hope these don't get optimized away and are detected at runtime as a result of the bitwise operator
#ifndef _di_f_types_sizes_
  #define f_unsigned_char_size        (~(unsigned char) 0)
  #define f_unsigned_short_size       (~(unsigned short) 0)
  #define f_unsigned_int_size         (~(unsigned int) 0)
  #define f_unsigned_long_size        (~(unsigned long) 0)
  #define f_unsigned_long_long_size   (~(unsigned long long) 0)
  #define f_unsigned_double_size      (~(unsigned double) 0)
  #define f_unsigned_long_double_size (~(unsigned double) 0)
  #define f_signed_char_size          ((~(unsigned char) 0) / 2)
  #define f_signed_short_size         ((~(unsigned short) 0) / 2)
  #define f_signed_int_size           ((~(unsigned int) 0) / 2)
  #define f_signed_long_size          ((~(unsigned long) 0) / 2)
  #define f_signed_long_long_size     ((~(unsigned long long) 0) / 2)
  #define f_signed_double_size        ((~(unsigned double) 0) / 2)
  #define f_signed_long_double_size   ((~(unsigned double) 0) / 2)
#endif // _di_f_types_sizes_

// These should define some types use by stdio
#ifndef _di_f_types_standard_output_
  #define f_standard_input   stdin
  #define f_standard_output  stdout
  #define f_standard_error   stderr
  #define f_standard_warning stdout // I still hope for a separate pipe for warnings
#endif // _di_f_types_standard_output_

// Defines a variable to be used by arrays.
#ifndef _di_f_array_length_
  typedef f_u_long      f_array_length;
  typedef f_u_int       f_array_length_short;
  typedef f_u_long_long f_array_length_long;
#endif // _di_f_array_length_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_types_h
