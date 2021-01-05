/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides datatype definitions.
 */
#ifndef _F_type_h
#define _F_type_h

// include pre-requirements
#ifndef _GNU_SOURCE
  #define _GNU_SOURCE
#endif // _GNU_SOURCE

// libc includes
#include <stdbool.h>
#include <stdint.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Status type.
 */
#ifndef _di_f_type_status_t_
  typedef uint16_t f_status_t;
#endif // _di_f_type_status_t_

/**
 * Conditional 128-bit support.
 *
 * This should work in GCC, but other compilers this may not be available.
 * When not supported, these will fallback to 64-bit.
 */
#ifndef _di_f_type_int_128_t_
  #ifdef __SIZEOF_INT128__
    typedef __int128_t  f_int_128_t;
    typedef __uint128_t f_uint_128_t;
  #else
    typedef int64_t  f_int_128_t;
    typedef uint64_t f_uint_128_t;
  #endif // __SIZEOF_INT128__
#endif // _di_f_type_int_128_t_

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

  #ifndef _di_f_type_int_128_t_
    #define f_type_size_128_negative 0x7fffffffffffffffffffffff
    #define f_type_size_128_positive 0x7ffffffffffffffffffffffe
    #define f_type_size_128_unsigned 0xfffffffffffffffffffffffe
  #else
    #define f_type_size_128_negative f_type_size_64_negative
    #define f_type_size_128_positive f_type_size_64_positive
    #define f_type_size_128_unsigned f_type_size_64_unsigned
  #endif // _di_f_type_int_128_t_

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

  #ifndef _di_f_type_int_128_t_
    #define f_type_size_max_128_negative 0x800000000000000000000000
    #define f_type_size_max_128_positive 0x7fffffffffffffffffffffff
    #define f_type_size_max_128_unsigned 0xffffffffffffffffffffffff
  #else
    #define f_type_size_max_128_negative f_type_size_max_64_negative
    #define f_type_size_max_128_positive f_type_size_max_64_positive
    #define f_type_size_max_128_unsigned f_type_size_max_64_unsigned
  #endif // _di_f_type_int_128_t_
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
#ifndef _di_f_type_number_64_t_
  typedef int64_t  f_number_signed_t;
  typedef uint64_t f_number_unsigned_t;

  #define f_number_t_size_unsigned f_type_size_64_unsigned
  #define f_number_t_size_positive f_type_size_64_positive
  #define f_number_t_size_negative f_type_size_64_negative

  #define f_number_t_size_max_unsigned f_type_size_max_64_unsigned
  #define f_number_t_size_max_positive f_type_size_max_64_positive
  #define f_number_t_size_max_negative f_type_size_max_64_negative
#endif // _di_f_type_number_64_t_

#ifdef _en_f_type_number_32_t_
  typedef int32_t  f_number_signed_t;
  typedef uint32_t f_number_unsigned_t;

  #define f_number_t_size_unsigned f_type_size_32_unsigned
  #define f_number_t_size_positive f_type_size_32_positive
  #define f_number_t_size_negative f_type_size_32_negative

  #define f_number_t_size_max_unsigned f_type_size_max_32_unsigned
  #define f_number_t_size_max_positive f_type_size_max_32_positive
  #define f_number_t_size_max_negative f_type_size_max_32_negative
#endif // _en_f_type_number_32_t_

#ifdef _en_f_type_number_128_t_
  typedef f_int_128_t  f_number_signed_t;
  typedef f_uint_128_t f_number_unsigned_t;

  #define f_number_t_size_unsigned f_type_size_128_unsigned
  #define f_number_t_size_positive f_type_size_128_positive
  #define f_number_t_size_negative f_type_size_128_negative

  #define f_number_t_size_max_unsigned f_type_size_max_128_unsigned
  #define f_number_t_size_max_positive f_type_size_max_128_positive
  #define f_number_t_size_max_negative f_type_size_max_128_negative
#endif // _en_f_type_number_128_t_

/**
 * Standard Input/Output types.
 *
 * For most systems, there is no standard warning nor is there a standard debug.
 * Therefore, these will map to standard output.
 */
#ifndef _di_f_type_input_output_
  #define f_type_debug   stdout
  #define f_type_error   stderr
  #define f_type_input   stdin
  #define f_type_output  stdout
  #define f_type_warning stdout

  #define f_type_descriptor_debug   STDOUT_FILENO
  #define f_type_descriptor_error   STDERR_FILENO
  #define f_type_descriptor_input   STDIN_FILENO
  #define f_type_descriptor_output  STDOUT_FILENO
  #define f_type_descriptor_warning STDOUT_FILENO
#endif // _di_f_type_input_output_

/**
 * Defines a variable to be used by arrays.
 */
#ifndef _di_f_array_t_
  typedef f_number_unsigned_t f_array_length_t;

  #define f_array_length_t_size     f_number_t_size_unsigned
  #define f_array_length_t_size_max f_number_t_size_max_unsigned
#endif // _di_f_array_t_

/**
 * A structure designating a row and column, just like a cell in a table.
 *
 * row:    the row position.
 * column: the column position.
 */
#ifndef _di_f_cell_t_
  typedef struct {
    f_array_length_t row;
    f_array_length_t column;
  } f_cell_t;

  #define f_cell_t_initialize { 0, 0 }

  #define f_macro_cell_t_clear(cell) \
    cell.row = 0; \
    cell.column = 0;
#endif // _di_f_cell_t_

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

/**
 * A structure representing a set of modes intended to be used by file or directory operations.
 */
#ifndef _di_f_mode_t_
  typedef struct {
    mode_t block;     // S_IFBLK
    mode_t character; // S_IFCHR
    mode_t directory; // S_IFDIR
    mode_t fifo;      // S_IFIFO
    mode_t regular;   // S_IFREG
    mode_t link;      // S_IFLNK
    mode_t socket;    // S_IFSOCK
    mode_t unknown;
  } f_mode_t;

  #define f_mode_t_initialize { \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
  }

  #define f_macro_mode_t_set_default(mode) \
    mode.block = f_file_mode_all_rw; \
    mode.character = f_file_mode_all_rw; \
    mode.directory = f_file_mode_all_rwx; \
    mode.fifo = f_file_mode_all_rw; \
    mode.regular = f_file_mode_all_rw; \
    mode.link = f_file_mode_all_rw; \
    mode.socket = f_file_mode_all_rw; \
    mode.unknown = f_file_mode_all_rw;

  #define f_macro_mode_t_set_default_umask(mode, mask) \
    mode.block = f_file_mode_all_rw & ~mask; \
    mode.character = f_file_mode_all_rw & ~mask; \
    mode.directory = f_file_mode_all_rwx & ~mask; \
    mode.fifo = f_file_mode_all_rw & ~mask; \
    mode.regular = f_file_mode_all_rw & ~mask; \
    mode.link = f_file_mode_all_rw & ~mask; \
    mode.socket = f_file_mode_all_rw & ~mask; \
    mode.unknown = f_file_mode_all_rw & ~mask;

  #define f_macro_mode_t_set_all(mode, value) \
    mode.block = value; \
    mode.character = value; \
    mode.directory = value; \
    mode.fifo = value; \
    mode.regular = value; \
    mode.link = value; \
    mode.socket = value; \
    mode.unknown = value;

  #define f_macro_mode_t_set_common(mode, value_directory, value_file, value_link) \
    mode.directory = value_directory; \
    mode.regular = value_file; \
    mode.link = value_link;

  #define f_macro_mode_t_set_uncommon(mode, value_block, value_character, value_fifo, value_socket, value_unknown) \
    mode.block = value_block; \
    mode.character = value_character; \
    mode.fifo = value_fifo; \
    mode.socket = value_socket; \
    mode.unknown = value_unknown;
#endif // _di_f_directory_mode_

/**
 * A non-kernel dependent version of "struct timespec".
 *
 * seconds:     The total number of seconds.
 * nanoseconds: The total number of nanoseconds.
 */
#ifndef _di_f_time_spec_t_
  typedef struct {
    uint64_t seconds;
    uint64_t nanoseconds;
  } f_time_spec_t;

  #define f_time_spec_t_initialize { 0, 0 }

  #define f_macro_time_spec_t_clear(spec) \
    spec.seconds = 0; \
    spec.nanoseconds = 0;
#endif // _di_f_time_spec_t_

/**
 * Hold a unit of Time.
 *
 * This utilizes the unit of measurement called a "Time", represented with uppercase "T".
 * For comparison, a unit of Time is equivalent to a nanosecond, or 10^-9 seconds.
 *
 * A unit of Time is intended to represent some unit of Time such that a single 64-bit integer may hold all units of Time for a single calendar year.
 * This unit of Time does not and must not include Years (unlike Unixtime).
 *
 * A MegaTime (MT) is therefore equivalent to a millisecond such that a millisecond is 10^-3 seconds.
 *
 * To convert from Time to Unixtime, one must have a year (which could be assumed to be the current year) and then calculate all of those calendar od
 *
 * A unit of Time by default is assumed to be in UTC.
 * 1 (Earth) year ~= 31536000000000000 Time or 31536000 GT (GigaTime).
 * 1 (Earth) day = 86400000000000 Time or 86400 GT (GigaTime).
 * 1 (Earth) hour = 3600000000000 Time or 3600 GT (GigaTime).
 * 1 (Earth) minute = 60000000000 Time or 60 GT (GigaTime).
 * 1 (Earth) second = 1000000000 Time or 1 GT (GigaTime).
 *
 * Consequentially, 1 day in units of Time is easily represented as 86.4 TT (TeraTime).
 */
#ifndef _di_f_time_t_
  typedef uint64_t f_time_t;
#endif // _di_f_time_t_

/**
 * Hold a unit of Time along with a year to represent a date.
 *
 * This implementation of a date using the unit of Time is limited on the size of the year.
 * The value for year is expected to be a signed number.
 * For anything that needs a larger (or smaller) year, create a new type or use the "year string format" of Time.
 *
 * In "year string format" of Time, a Year may be prepended to the Time followed by a single colon ':' to associate a year with the Time.
 * This Year has no minimum or maximum but may not have decimals.
 *
 * For example, "2020:86400000000000" would represent: January 02, 2020 0:00 UTC.
 * For example, "2020:86.4 TT" would represent: January 02, 2020 0:00 UTC.
 */
#ifndef _di_f_date_t_
  typedef struct {
    f_number_signed_t year;
    f_time_t time;
  } f_date_t;

  #define f_date_t_initialize { 0, 0 }

  #define f_macro_date_t_clear(date) \
    date.year = 0; \
    date.time = 0;
#endif // _di_f_date_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_h
