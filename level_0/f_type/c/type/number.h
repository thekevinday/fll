/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines number type data.
 *
 * This is auto-included by type.h and should not need to be explicitly included.
 */
#ifndef _F_type_number_h
#define _F_type_number_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Defines the maximum size to be supported.
 *
 * The size is to be the (max supported size - 1) such that that last number can be used for overflow operations.
 *
 * For example, F_type_size_8_negative_d is 2^7, or -1 to -128, therefore the max size here is -128 - 1 or -127.
 * For example, F_type_size_8_positive_d is 2^7, or 0 to 127, therefore the max size here is 127 - 1 or 126.
 * For example, F_type_size_8_unsigned_d is 2^8, or 0 to 255, therefore the max size here is 255 - 1 or 254.
 *
 * The max_size is provided for actual max sizes.
 * For example, F_type_size_8_negative_d is 2^7, or -1 to -128, therefore the max size here is -128.
 * For example, F_type_size_8_positive_d is 2^7, or 0 to 127, therefore the max size here is 127.
 * For example, F_type_size_8_unsigned_d is 2^8, or 0 to 255, therefore the max size here is 255.
 */
#ifndef _di_f_type_sizes_d_
  #define F_type_size_8_negative_d 0x7f
  #define F_type_size_8_positive_d 0x7e
  #define F_type_size_8_unsigned_d 0xfe

  #define F_type_size_16_negative_d 0x7fff
  #define F_type_size_16_positive_d 0x7ffe
  #define F_type_size_16_unsigned_d 0xfffe

  #define F_type_size_32_negative_d 0x7fffffff
  #define F_type_size_32_positive_d 0x7ffffffe
  #define F_type_size_32_unsigned_d 0xfffffffe

  #define F_type_size_64_negative_d 0x7fffffffffffffff
  #define F_type_size_64_positive_d 0x7ffffffffffffffe
  #define F_type_size_64_unsigned_d 0xfffffffffffffffe

  #ifdef __SIZEOF_INT128__
    #define F_type_size_128_negative_d 0x7fffffffffffffffffffffff
    #define F_type_size_128_positive_d 0x7ffffffffffffffffffffffe
    #define F_type_size_128_unsigned_d 0xfffffffffffffffffffffffe
  #else
    #define F_type_size_128_negative_d F_type_size_64_negative_d
    #define F_type_size_128_positive_d F_type_size_64_positive_d
    #define F_type_size_128_unsigned_d F_type_size_64_unsigned_d
  #endif // __SIZEOF_INT128__

  #define F_type_size_max_8_negative_d 0x80
  #define F_type_size_max_8_positive_d 0x7f
  #define F_type_size_max_8_unsigned_d 0xff

  #define F_type_size_max_16_negative_d 0x8000
  #define F_type_size_max_16_positive_d 0x7fff
  #define F_type_size_max_16_unsigned_d 0xffff

  #define F_type_size_max_32_negative_d 0x80000000
  #define F_type_size_max_32_positive_d 0x7fffffff
  #define F_type_size_max_32_unsigned_d 0xffffffff

  #define F_type_size_max_64_negative_d 0x8000000000000000
  #define F_type_size_max_64_positive_d 0x7fffffffffffffff
  #define F_type_size_max_64_unsigned_d 0xffffffffffffffff

  #ifdef __SIZEOF_INT128__
    #define F_type_size_max_128_negative_d 0x800000000000000000000000
    #define F_type_size_max_128_positive_d 0x7fffffffffffffffffffffff
    #define F_type_size_max_128_unsigned_d 0xffffffffffffffffffffffff
  #else
    #define F_type_size_max_128_negative_d F_type_size_max_64_negative_d
    #define F_type_size_max_128_positive_d F_type_size_max_64_positive_d
    #define F_type_size_max_128_unsigned_d F_type_size_max_64_unsigned_d
  #endif // __SIZEOF_INT128__
#endif // _di_f_type_sizes_d_

/**
 * Conditional 128-bit support.
 *
 * This should work in GCC, but other compilers this may not be available.
 * When not supported, these will fallback to 64-bit.
 */
#ifndef _di_f_int128_t_
  #ifdef __SIZEOF_INT128__
    typedef __int128_t  f_int128_t;
    typedef __uint128_t f_uint128_t;
  #else
    typedef int64_t  f_int128_t;
    typedef uint64_t f_uint128_t;
  #endif // __SIZEOF_INT128__
#endif // _di_f_int128_t_

/**
 * Provide a 128-bit type wrapper, which could be either 64-bit or 128-bit depending on support.
 *
 * This is __int128_t when 128-bit is supported and int64_t when not supported.
 *
 * This provides the types without the normal "f_" leading prefixes to be more in line with the core types like int64_t.
 */
#ifdef __SIZEOF_INT128__
  #ifndef _di_f_int128_t_
    typedef __int128_t int128_t;
  #endif // _di_f_int128_t_

  #ifndef _di_f_uint128_t_
    typedef __uint128_t uint128_t;
  #endif // _di_f_uint128_t_
#else // __SIZEOF_INT128__
  #ifndef _di_f_int128_t_
    typedef int64_t int128_t;
  #endif // _di_f_int128_t_

  #ifndef _di_f_uint128_t_
    typedef uint64_t uint128_t;
  #endif // _di_f_uint128_t_
#endif // __SIZEOF_INT128__

/**
 * Custom data type to be used throughout the project to represent general numbers.
 *
 * This is intended to be used in buffers, such as strings, and in argument parameters.
 *
 * Provides additional custom types so that it can be more easily be overwritten.
 * Specifically, there is support for using 32-bit, 64-bit, or 128-bit lengths.
 *
 * 64-bit is the designed default.
 */
#ifndef _di_f_type_number_64_t_
  typedef int64_t  f_number_signed_t;
  typedef uint64_t f_number_unsigned_t;

  #define f_number_signed_t_initialize 0
  #define f_number_unsigned_t_initialize 0

  #define F_number_t_size_unsigned_d F_type_size_64_unsigned_d
  #define F_number_t_size_positive_d F_type_size_64_positive_d
  #define F_number_t_size_negative_d F_type_size_64_negative_d

  #define F_number_t_size_max_unsigned_d F_type_size_max_64_unsigned_d
  #define F_number_t_size_max_positive_d F_type_size_max_64_positive_d
  #define F_number_t_size_max_negative_d F_type_size_max_64_negative_d
#elif defined(_en_f_type_number_32_t_)
  typedef int32_t  f_number_signed_t;
  typedef uint32_t f_number_unsigned_t;

  #define f_number_signed_t_initialize 0
  #define f_number_unsigned_t_initialize 0

  #define F_number_t_size_unsigned_d F_type_size_32_unsigned_d
  #define F_number_t_size_positive_d F_type_size_32_positive_d
  #define F_number_t_size_negative_d F_type_size_32_negative_d

  #define F_number_t_size_max_unsigned_d F_type_size_max_32_unsigned_d
  #define F_number_t_size_max_positive_d F_type_size_max_32_positive_d
  #define F_number_t_size_max_negative_d F_type_size_max_32_negative_d
#elif defined(_en_f_type_number_128_t_)
  typedef f_int128_t  f_number_signed_t;
  typedef f_uint128_t f_number_unsigned_t;

  #define f_number_signed_t_initialize 0
  #define f_number_unsigned_t_initialize 0

  #define F_number_t_size_unsigned_d F_type_size_128_unsigned_d
  #define F_number_t_size_positive_d F_type_size_128_positive_d
  #define F_number_t_size_negative_d F_type_size_128_negative_d

  #define F_number_t_size_max_unsigned_d F_type_size_max_128_unsigned_d
  #define F_number_t_size_max_positive_d F_type_size_max_128_positive_d
  #define F_number_t_size_max_negative_d F_type_size_max_128_negative_d
#endif // _en_f_type_number_128_t_

/**
 * An array of array lengths.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: An array of array lengths.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_number_signeds_t_
  typedef struct {
    f_number_signed_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_number_signeds_t;

  #define f_number_signeds_t_initialize { 0, 0, 0 }

  #define macro_f_number_signeds_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_number_signeds_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_number_signeds_t_

/**
 * An array of an array of array lengths.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: The array of an array of array lengths.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_number_signedss_t_
  typedef struct {
    f_number_signeds_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_number_signedss_t;

  #define f_number_signedss_t_initialize { 0, 0, 0 }

  #define macro_f_number_signedss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_number_signedss_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_number_signedss_t_

/**
 * An array of array lengths.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: An array of array lengths.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_number_unsigneds_t_
  typedef struct {
    f_number_unsigned_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_number_unsigneds_t;

  #define f_number_unsigneds_t_initialize { 0, 0, 0 }

  #define macro_f_number_unsigneds_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_number_unsigneds_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_number_unsigneds_t_

/**
 * An array of an array of array lengths.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: The array of an array of array lengths.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_number_unsignedss_t_
  typedef struct {
    f_number_unsigneds_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_number_unsignedss_t;

  #define f_number_unsignedss_t_initialize { 0, 0, 0 }

  #define macro_f_number_unsignedss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_number_unsignedss_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_number_unsignedss_t_

/**
 * An array of array int8_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: An array of int8_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_int8s_t_
  typedef struct {
    int8_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_int8s_t;

  #define f_int8s_t_initialize { 0, 0, 0 }

  #define macro_f_int8s_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_int8s_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_int8s_t_

/**
 * An array of an array of array int8_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: The array of an array of array int8_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_int8ss_t_
  typedef struct {
    f_int8s_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_int8ss_t;

  #define f_int8ss_t_initialize { 0, 0, 0 }

  #define macro_f_int8ss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_int8ss_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_int8ss_t_

/**
 * An array of array uint8_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: An array of uint8_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_uint8s_t_
  typedef struct {
    uint8_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_uint8s_t;

  #define f_uint8s_t_initialize { 0, 0, 0 }

  #define macro_f_uint8s_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_uint8s_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_uint8s_t_

/**
 * An array of an array of array uint8_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: The array of an array of array uint8_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_uint8ss_t_
  typedef struct {
    f_uint8s_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_uint8ss_t;

  #define f_uint8ss_t_initialize { 0, 0, 0 }

  #define macro_f_uint8ss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_uint8ss_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_uint8ss_t_

/**
 * An array of array int16_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: An array of int16_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_int16s_t_
  typedef struct {
    int16_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_int16s_t;

  #define f_int16s_t_initialize { 0, 0, 0 }

  #define macro_f_int16s_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_int16s_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_int16s_t_

/**
 * An array of an array of array int16_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: The array of an array of array int16_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_int16ss_t_
  typedef struct {
    f_int16s_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_int16ss_t;

  #define f_int16ss_t_initialize { 0, 0, 0 }

  #define macro_f_int16ss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_int16ss_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_int16ss_t_

/**
 * An array of array uint16_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: An array of uint16_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_uint16s_t_
  typedef struct {
    uint16_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_uint16s_t;

  #define f_uint16s_t_initialize { 0, 0, 0 }

  #define macro_f_uint16s_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_uint16s_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_uint16s_t_

/**
 * An array of an array of array uint16_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: The array of an array of array uint16_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_uint16ss_t_
  typedef struct {
    f_uint16s_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_uint16ss_t;

  #define f_uint16ss_t_initialize { 0, 0, 0 }

  #define macro_f_uint16s_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_uint16s_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_uint16ss_t_

/**
 * An array of array int32_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: An array of int32_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_int32s_t_
  typedef struct {
    int32_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_int32s_t;

  #define f_int32s_t_initialize { 0, 0, 0 }

  #define macro_f_int32s_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_int32s_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_int32s_t_

/**
 * An array of an array of array int32_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: The array of an array of array int32_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_int32ss_t_
  typedef struct {
    f_int32s_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_int32ss_t;

  #define f_int32ss_t_initialize { 0, 0, 0 }

  #define macro_f_int32ss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_int32ss_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_int32ss_t_

/**
 * An array of array uint32_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: An array of uint32_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_uint32s_t_
  typedef struct {
    uint32_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_uint32s_t;

  #define f_uint32s_t_initialize { 0, 0, 0 }

  #define macro_f_uint32s_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_uint32s_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_uint32s_t_

/**
 * An array of an array of array uint32_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: The array of an array of array uint32_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_uint32ss_t_
  typedef struct {
    f_uint32s_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_uint32ss_t;

  #define f_uint32ss_t_initialize { 0, 0, 0 }

  #define macro_f_uint32ss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_uint32ss_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_uint32ss_t_

/**
 * An array of array int64_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: An array of int64_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_int64s_t_
  typedef struct {
    int64_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_int64s_t;

  #define f_int64s_t_initialize { 0, 0, 0 }

  #define macro_f_int64s_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_int64s_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_int64s_t_

/**
 * An array of an array of array int64_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: The array of an array of array int64_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_int64ss_t_
  typedef struct {
    f_int64s_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_int64ss_t;

  #define f_int64ss_t_initialize { 0, 0, 0 }

  #define macro_f_int64ss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_int64ss_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_int64ss_t_

/**
 * An array of array uint64_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: An array of uint64_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_uint64s_t_
  typedef struct {
    uint64_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_uint64s_t;

  #define f_uint64s_t_initialize { 0, 0, 0 }

  #define macro_f_uint64s_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_uint64s_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_uint64s_t_

/**
 * An array of an array of array uint64_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: The array of an array of array uint64_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_uint64ss_t_
  typedef struct {
    f_uint64s_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_uint64ss_t;

  #define f_uint64ss_t_initialize { 0, 0, 0 }

  #define macro_f_uint64ss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_uint64ss_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_uint64ss_t_

/**
 * An array of int128_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: The array of int128_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_int128s_t_
  typedef struct {
    int128_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_int128s_t;

  #define f_int128s_t_initialize { 0, 0, 0 }

  #define macro_f_int128s_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_int128s_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_int128s_t_

/**
 * An array of and array of int128_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: The array of and array of int128_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_int128ss_t_
  typedef struct {
    f_int128s_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_int128ss_t;

  #define f_int128ss_t_initialize { 0, 0, 0 }

  #define macro_f_int128ss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_int128ss_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_int128ss_t_

/**
 * An array of uint128_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: The array of uint128_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_uint128s_t_
  typedef struct {
    uint128_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_uint128s_t;

  #define f_uint128s_t_initialize { 0, 0, 0 }

  #define macro_f_uint128s_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_uint128s_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_uint128s_t_

/**
 * An array of and array of uint128_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: The array of and array of uint128_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_uint128ss_t_
  typedef struct {
    f_uint128s_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_uint128ss_t;

  #define f_uint128ss_t_initialize { 0, 0, 0 }

  #define macro_f_uint128ss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_uint128ss_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_uint128ss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_number_h
