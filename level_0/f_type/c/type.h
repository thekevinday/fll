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
 * Compiler-specific attribute visibility features.
 *
 * Use these macros for visibility-specific tweaks so that if these are not supported by any given compiler, then they can be easily disabled.
 *
 * f_attribute_visibility_internal provides a way to make some functions effectively private.
 */
#ifndef _di_f_attribute_visibility_
  #define f_attribute_visibility_hidden    __attribute__((visibility("hidden")))
  #define f_attribute_visibility_internal  __attribute__((visibility("internal")))
  #define f_attribute_visibility_protected __attribute__((visibility("protected")))
  #define f_attribute_visibility_public    __attribute__((visibility("default")))
#endif // _di_f_attribute_visibility_

/**
 * A status intended to be used as the return value status of some function or operation.
 */
#ifndef _di_f_type_status_t_
  typedef uint16_t f_status_t;
#endif // _di_f_type_status_t_

/**
 * A representation of a state to be shared between different levels for some function.
 *
 * This is used to provide advanced controls on different levels of the project to something outside.
 *
 * The allocate provides an allocation step so that the caller can determine a better performing allocation step for their purpose.
 * For example, if the caller knows that they need to allocate a hundred megabytes of data of which is separated into blocks of 8k, then allocate could be set to 8192.
 *
 * There are two standard callbacks that are expected to be commonly available: interrupt() and handle().
 * Additional callbacks are stored in the structure "callbacks" as defined by the class requiring the use of this structure (f_state_t).
 *
 * All state values may be NULL, in which case they are to be ignored.
 *
 * The general interpretation of the return results of interrupt() or any of the functions should have an error bit to designate an error and not an error bit to designate no error.
 * In the case of interrupt(), the F_interrupt and F_interrupt_not must be returned as appropriate and if not an error (the F_interrupt and F_interrupt_not may have an error bit).
 * To keep the logic simple, it is recommended that F_interrupt always be returned with the error bit set.
 *
 * The general interpretation of handle() is to either print an error message or to perform additional tasks when an error occurs (such as saving state data for use at a higher level).
 * This allows for the error to be processed with all relevant data before the function returns.
 *
 * These two callbacks (handle() and interrupt()) accept the following parameters:
 * - error:    The current status code (with error bit as appropriate) (only passed to handle()).
 * - state:    The state data. Must be of type f_state_t. Must not be NULL.
 * - internal: Additional data passed by the function being called, often containing internal data to the called function. May be NULL.
 *
 * The "custom" property on f_state_t is intended to be used so that the callback, such as the interrupt(), can make changes to something within the scope of the parent.
 *
 * For example:
 *   There exists some project "bob" with some functions "bob_does()" and "bob_interrupts()".
 *   The function "bob_does()" maintains a state (f_state_t) called "bob_state".
 *   The function "bob_does()" will call "f_talk()" that accepts a state (f_state_t) and defines the data structure type "f_interject_t" to be called interject.
 *   While "f_talk()" executes, "bob_interrupts()" is periodically with the state (f_state_t) "bob_state" as the first parameter and the data structure (f_interject_t) "interject" as the second parameter.
 *   If Bob interjects the talk, then bob_interrupts() would return F_interrupt.
 *   If Bob does not interject the talk, then bob_interrupts() would return F_interrupt_not.
 *   This response is handled within f_talk().
 *   The f_talk() function will then return status when done and might immediately return with F_interrupt (with error bit) if bob_interrupts() returns F_interrupt (with/without error bit).
 *
 * step_large: The allocation step to use for large buffers.
 * step_small: The allocation step to use for small buffers.
 * handle:     A function to call on a specific error (allowing for the error to be handled before function returns). May be NULL.
 * interrupt:  A function to call for checking to see if an interrupt is to be called (return result is passed to and handled by caller). May be NULL.
 * callbacks:  A structure (defined by function/project using this) of additional functions to call. May be NULL.
 * custom:     A structure (defined by caller/parent) for holding custom data to be passed along to the interrupt() or one of the functions. May be NULL.
 * data:       A structure (defined by function) for holding data relevant to the function. May be NULL. May be required.
 */
#ifndef _di_f_type_state_t_
  typedef struct {
    uint16_t step_large;
    uint16_t step_small;

    f_status_t (*handle)(const f_status_t error, void *state, void *internal);
    f_status_t (*interrupt)(void *state, void *internal);

    void *callbacks;
    void *custom;
    void *data;
  } f_state_t;

  #define f_state_t_initialize { f_memory_default_allocation_large, f_memory_default_allocation_small, 0, 0, 0, 0, 0 }

  #define macro_f_state_t_initialize(step_large, step_small, handle, interrupt, callbacks, custom, data) { \
    step_large, \
    step_small, \
    handle, \
    interrupt, \
    callbacks, \
    custom, \
    data \
  }

  #define macro_f_state_t_clear(state) \
    state.step_large = 0; \
    state.step_small = 0; \
    state.handle = 0; \
    state.interrupt = 0; \
    state.callbacks = 0; \
    state.custom = 0; \
    state.data = 0;
#endif // _di_f_type_state_t_

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
 *
 * There are problems in some libc's and systems that do not handle lengths greater than 2^63.
 * This is primarily a problem with libc string functions.
 * For general compatiblity reasons, this is set to a signed 64-bit integer.
 */
#ifndef _di_f_array_t_
  typedef f_number_signed_t f_array_length_t;

  #define f_array_length_t_size     f_type_size_64_positive
  #define f_array_length_t_size_max f_type_size_max_64_positive
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

  #define macro_f_cell_t_clear(cell) \
    cell.row = 0; \
    cell.column = 0;
#endif // _di_f_cell_t_

/**
 * An array of f_cell_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: The array of f_cell_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_cells_t_
  typedef struct {
    f_cell_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_cells_t;

  #define f_cells_t_initialize { 0, 0, 0 }
#endif // _di_f_cells_t_

/**
 * This holds an array of f_cells_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: The array of f_cell_t arrays.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_cellss_t_
  typedef struct {
    f_cells_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_cellss_t;

  #define f_cellss_t_initialize { 0, 0, 0 }
#endif // _di_f_cellss_t_

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

  #define macro_f_mode_t_set_default(mode) \
    mode.block = f_file_mode_all_rw; \
    mode.character = f_file_mode_all_rw; \
    mode.directory = f_file_mode_all_rwx; \
    mode.fifo = f_file_mode_all_rw; \
    mode.regular = f_file_mode_all_rw; \
    mode.link = f_file_mode_all_rw; \
    mode.socket = f_file_mode_all_rw; \
    mode.unknown = f_file_mode_all_rw;

  #define macro_f_mode_t_set_default_umask(mode, mask) \
    mode.block = f_file_mode_all_rw & ~mask; \
    mode.character = f_file_mode_all_rw & ~mask; \
    mode.directory = f_file_mode_all_rwx & ~mask; \
    mode.fifo = f_file_mode_all_rw & ~mask; \
    mode.regular = f_file_mode_all_rw & ~mask; \
    mode.link = f_file_mode_all_rw & ~mask; \
    mode.socket = f_file_mode_all_rw & ~mask; \
    mode.unknown = f_file_mode_all_rw & ~mask;

  #define macro_f_mode_t_set_all(mode, value) \
    mode.block = value; \
    mode.character = value; \
    mode.directory = value; \
    mode.fifo = value; \
    mode.regular = value; \
    mode.link = value; \
    mode.socket = value; \
    mode.unknown = value;

  #define macro_f_mode_t_set_common(mode, value_directory, value_file, value_link) \
    mode.directory = value_directory; \
    mode.regular = value_file; \
    mode.link = value_link;

  #define macro_f_mode_t_set_uncommon(mode, value_block, value_character, value_fifo, value_socket, value_unknown) \
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

  #define macro_f_time_spec_t_clear(spec) \
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

  #define macro_f_date_t_clear(date) \
    date.year = 0; \
    date.time = 0;
#endif // _di_f_date_t_

/**
 * An array of array lengths.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: An array of array lengths.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_array_lengths_t_
  typedef struct {
    f_array_length_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_array_lengths_t;

  #define f_array_lengths_t_initialize { 0, 0, 0 }
#endif // _di_f_array_lengths_t_

/**
 * An array of an array of array lengths.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: The array of an array of array lengths.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_array_lengthss_t_
  typedef struct {
    f_array_lengths_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_array_lengthss_t;

  #define f_array_lengthss_t_initialize { 0, 0, 0 }
#endif // _di_f_array_lengthss_t_

/**
 * An array of array int8_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: An array of int8_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_array_t_int8_t_
  typedef struct {
    int8_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_int8s_t;

  #define f_int8s_t_initialize { 0, 0, 0 }
#endif // _di_int8s_t_

/**
 * An array of an array of array int8_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: The array of an array of array int8_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_int8ss_t_
  typedef struct {
    f_int8s_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_int8ss_t;

  #define f_int8ss_t_initialize { 0, 0, 0 }
#endif // _di_int8ss_t_

/**
 * An array of array uint8_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: An array of uint8_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_uint8s_t_
  typedef struct {
    uint8_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_uint8s_t;

  #define f_uint8s_t_initialize { 0, 0, 0 }
#endif // _di_uint8s_t_

/**
 * An array of an array of array uint8_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: The array of an array of array uint8_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_uint8ss_t_
  typedef struct {
    f_uint8s_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_uint8ss_t;

  #define f_uint8ss_t_initialize { 0, 0, 0 }
#endif // _di_uint8ss_t_

/**
 * An array of array int16_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: An array of int16_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_int16s_t_
  typedef struct {
    int16_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_int16s_t;

  #define f_int16s_t_initialize { 0, 0, 0 }
#endif // _di_int16s_t_

/**
 * An array of an array of array int16_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: The array of an array of array int16_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_int16ss_t_
  typedef struct {
    f_int16s_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_int16ss_t;

  #define f_int16ss_t_initialize { 0, 0, 0 }
#endif // _di_int16ss_t_

/**
 * An array of array uint16_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: An array of uint16_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_uint16s_t_
  typedef struct {
    uint16_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_uint16s_t;

  #define f_uint16s_t_initialize { 0, 0, 0 }
#endif // _di_uint16s_t_

/**
 * An array of an array of array uint16_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: The array of an array of array uint16_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_uint16ss_t_
  typedef struct {
    f_uint16s_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_uint16ss_t;

  #define f_uint16ss_t_initialize { 0, 0, 0 }
#endif // _di_uint16ss_t_

/**
 * An array of array int32_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: An array of int32_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_int32s_t_
  typedef struct {
    int32_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_int32s_t;

  #define f_int32s_t_initialize { 0, 0, 0 }

  #define macro_f_int32s_t_initialize(structure)
#endif // _di_int32s_t_

/**
 * An array of an array of array int32_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: The array of an array of array int32_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_int32ss_t_
  typedef struct {
    f_int32s_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_int32ss_t;

  #define f_int32ss_t_initialize { 0, 0, 0 }
#endif // _di_int32ss_t_

/**
 * An array of array uint32_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: An array of uint32_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_uint32s_t_
  typedef struct {
    uint32_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_uint32s_t;

  #define f_uint32s_t_initialize { 0, 0, 0 }
#endif // _di_uint32s_t_

/**
 * An array of an array of array uint32_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: The array of an array of array uint32_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_uint32ss_t_
  typedef struct {
    f_uint32s_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_uint32ss_t;

  #define f_uint32ss_t_initialize { 0, 0, 0 }
#endif // _di_uint32ss_t_

/**
 * An array of array int64_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: An array of int64_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_int64s_t_
  typedef struct {
    int64_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_int64s_t;

  #define f_int64s_t_initialize { 0, 0, 0 }
#endif // _di_int64s_t_

/**
 * An array of an array of array int64_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: The array of an array of array int64_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_int64ss_t_
  typedef struct {
    f_int64s_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_int64ss_t;

  #define f_int64ss_t_initialize { 0, 0, 0 }
#endif // _di_int64ss_t_

/**
 * An array of array uint64_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: An array of uint64_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_uint64s_t_
  typedef struct {
    uint64_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_uint64s_t;

  #define f_uint64s_t_initialize { 0, 0, 0 }
#endif // _di_uint64s_t_

/**
 * An array of an array of array uint64_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: The array of an array of array uint64_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_uint64ss_t_
  typedef struct {
    f_uint64s_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_uint64ss_t;

  #define f_uint64ss_t_initialize { 0, 0, 0 }
#endif // _di_uint64ss_t_

/**
 * Provide a 128-bit type wrapper, which could be either 64-bit or 128-bit depending on support.
 *
 * This is __int128_t when 128-bit is supported and int64_t when not supported.
 */
#ifndef __SIZEOF_INT128__

  #ifndef _di_int128_t_
    typedef __int128_t f_int128_t;
  #endif // _di_int128_t_

  #ifndef _di_uint128_t_
    typedef __uint128_t f_uint128_t;
  #endif // _di_uint128_t_

#else // __SIZEOF_INT128__

  #ifndef _di_int128_t_
    typedef int64_t f_int128_t;
  #endif // _di_int128_t_

  #ifndef _di_uint128_t_
    typedef uint64_t f_uint128_t;
  #endif // _di_uint128_t_

#endif // __SIZEOF_INT128__

/**
 * An array of f_int128_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: The array of f_int128_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_int128s_t_
  typedef struct {
    f_int128_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_int128s_t;

  #define f_int128s_t_initialize { 0, 0, 0 }
#endif // _di_int128s_t_

/**
 * An array of and array of f_int128_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: The array of and array of f_int128_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_int128ss_t_
  typedef struct {
    f_int128s_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_int128ss_t;

  #define f_int128ss_t_initialize { 0, 0, 0 }
#endif // _di_int128ss_t_

/**
 * An array of f_uint128_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: The array of f_uint128_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_uint128s_t_
  typedef struct {
    f_uint128_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_uint128s_t;

  #define f_uint128s_t_initialize { 0, 0, 0 }
#endif // _di_uint128s_t_

/**
 * An array of and array of f_uint128_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: The array of and array of f_uint128_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_uint128ss_t_
  typedef struct {
    f_uint128s_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_uint128ss_t;

  #define f_uint128ss_t_initialize { 0, 0, 0 }
#endif // _di_uint128ss_t_

/**
 * This holds an array of f_status_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: The array of f_status_t arrays.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_type_statuss_t_
  typedef struct {
    f_status_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_statuss_t;

  #define f_statuss_t_initialize { 0, 0, 0 }
#endif // _di_f_type_statuss_t_

/**
 * This holds an array of f_statuss_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: The array of f_status_t arrays.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_type_statusss_t_
  typedef struct {
    f_statuss_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_statusss_t;

  #define f_statusss_t_initialize { 0, 0, 0 }
#endif // _di_f_type_statusss_t_

/**
 * This holds an array of f_state_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: The array of f_state_t arrays.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_type_states_t_
  typedef struct {
    f_state_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_states_t;

  #define f_states_t_initialize { 0, 0, 0 }
#endif // _di_f_type_states_t_

/**
 * This holds an array of f_states_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: The array of f_state_t arrays.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_type_statess_t_
  typedef struct {
    f_states_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_statess_t;

  #define f_statess_t_initialize { 0, 0, 0 }
#endif // _di_f_type_statess_t_

/**
 * An FLL Identifier represents a way to identify FLL related text files and possibly binary files.
 *
 * This was originally designed for FSS (Featureless Settings Specification) but has been expanded to be used by the entire project.
 *
 * An FLL Identifier consists of two parts:
 * 1) A 64-byte long string representing a machine-name for the type.
 * 2) A 16-bit digit representing 2^16 possible type classifications, which is representeed by 4 hexadecial 1-byte strings for text.
 *
 * For example "fss-1234" is a valid type such that:
 * 1) name: "fss".
 * 2) type: "1234", (or 0x1 in binary.
 *
 * UTF-8 codes are available, but one must consider that 1 4-byte characte still takes up 4-bytes.
 * Therefore for all 4-byte UTF-8 characters, there is a maximum of 16 characters available.
 *
 * This intentionally utilizes a fixed array to avoid the need of dynamic allocation.
 *
 * The macro_f_fll_id_t_clear() is provided for "consistency in design" reasons.
 * However, it is probably a better idea to use memset to clear the name array.
 *
 * The name must only be "word" characters (therefore "-" is not allowed).
 *
 * name: The string representing the name of the FLL Identifier (This is not a NULL terminated string).
 * type: The code representing the type of the Identifier.
 * used: A representation of how many bytes in name are in used (if 0, then there is no name, thus this can be seen as not a valid identifier).
 */
#ifndef _di_f_fll_id_t_
  typedef struct {
    char name[64];

    uint16_t type;
    uint8_t used;
  } f_fll_id_t;

  #define f_fll_id_t_initialize { \
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, \
    0, \
    0, \
  }

  #define macro_f_fll_id_t_clear(id) \
    id.name[0] = 0; \
    id.name[1] = 0; \
    id.name[2] = 0; \
    id.name[3] = 0; \
    id.name[4] = 0; \
    id.name[5] = 0; \
    id.name[6] = 0; \
    id.name[7] = 0; \
    id.name[8] = 0; \
    id.name[9] = 0; \
    id.name[10] = 0; \
    id.name[11] = 0; \
    id.name[12] = 0; \
    id.name[13] = 0; \
    id.name[14] = 0; \
    id.name[15] = 0; \
    id.name[16] = 0; \
    id.name[17] = 0; \
    id.name[18] = 0; \
    id.name[19] = 0; \
    id.name[20] = 0; \
    id.name[21] = 0; \
    id.name[22] = 0; \
    id.name[23] = 0; \
    id.name[24] = 0; \
    id.name[25] = 0; \
    id.name[26] = 0; \
    id.name[27] = 0; \
    id.name[28] = 0; \
    id.name[29] = 0; \
    id.name[30] = 0; \
    id.name[31] = 0; \
    id.name[32] = 0; \
    id.name[33] = 0; \
    id.name[34] = 0; \
    id.name[35] = 0; \
    id.name[36] = 0; \
    id.name[37] = 0; \
    id.name[38] = 0; \
    id.name[39] = 0; \
    id.name[40] = 0; \
    id.name[41] = 0; \
    id.name[42] = 0; \
    id.name[43] = 0; \
    id.name[44] = 0; \
    id.name[45] = 0; \
    id.name[46] = 0; \
    id.name[47] = 0; \
    id.name[48] = 0; \
    id.name[49] = 0; \
    id.name[50] = 0; \
    id.name[51] = 0; \
    id.name[52] = 0; \
    id.name[53] = 0; \
    id.name[54] = 0; \
    id.name[55] = 0; \
    id.name[56] = 0; \
    id.name[57] = 0; \
    id.name[58] = 0; \
    id.name[59] = 0; \
    id.name[60] = 0; \
    id.name[61] = 0; \
    id.name[62] = 0; \
    id.name[63] = 0; \
    id.type = 0; \
    id.used = 0;
#endif // _di_f_fll_id_t__

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_h
