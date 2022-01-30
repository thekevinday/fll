/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides datatype definitions.
 */
#ifndef _F_type_h
#define _F_type_h

// include pre-requirements
#ifndef _GNU_SOURCE
  #define _GNU_SOURCE
#endif // _GNU_SOURCE

// Libc includes.
#include <stdbool.h>
#include <stdint.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Compiler-specific attribute features.
 *
 * Use these macros for visibility-specific tweaks so that if these are not supported by any given compiler, then they can be easily disabled.
 *
 * F_attribute_*:
 *   - visibility_hidden:    Visibility is hidden.
 *   - visibility_internal:  Visibility is private.
 *   - visibility_protected: Visibility is protected.
 *   - visibility_public:    Visibility is public.
 *   - weak:                 Designate symbol is weak rather than global.
 */
#ifndef _di_compiler_attributes_
  #define F_attribute_visibility_hidden_d    __attribute__((visibility("hidden")))
  #define F_attribute_visibility_internal_d  __attribute__((visibility("internal")))
  #define F_attribute_visibility_protected_d __attribute__((visibility("protected")))
  #define F_attribute_visibility_public_d    __attribute__((visibility("default")))

  #define F_attribute_weak_d __attribute__((weak))
#endif // _di_compiler_attributes_

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
 *   - error:    The current status code (with error bit as appropriate) (only passed to handle()).
 *   - state:    The state data. Must be of type f_state_t. Must not be NULL.
 *   - internal: Additional data passed by the function being called, often containing internal data to the called function. May be NULL.
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

  #define f_state_t_initialize { F_memory_default_allocation_large_d, F_memory_default_allocation_small_d, 0, 0, 0, 0, 0 }

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
 * For example, F_type_size_8_negative_d is 2^7, or -1 to -128, therefore the max size here is -128 - 1 or -127.
 * For example, F_type_size_8_positive_d is 2^7, or 0 to 127, therefore the max size here is 127 - 1 or 126.
 * For example, F_type_size_8_unsigned_d is 2^8, or 0 to 255, therefore the max size here is 255 - 1 or 254.
 *
 * The max_size is provided for actual max sizes.
 * For example, F_type_size_8_negative_d is 2^7, or -1 to -128, therefore the max size here is -128.
 * For example, F_type_size_8_positive_d is 2^7, or 0 to 127, therefore the max size here is 127.
 * For example, F_type_size_8_unsigned_d is 2^8, or 0 to 255, therefore the max size here is 255.
 */
#ifndef _di_f_type_sizes_
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

  #ifndef _di_f_type_int_128_t_
    #define F_type_size_128_negative_d 0x7fffffffffffffffffffffff
    #define F_type_size_128_positive_d 0x7ffffffffffffffffffffffe
    #define F_type_size_128_unsigned_d 0xfffffffffffffffffffffffe
  #else
    #define F_type_size_128_negative_d F_type_size_64_negative_d
    #define F_type_size_128_positive_d F_type_size_64_positive_d
    #define F_type_size_128_unsigned_d F_type_size_64_unsigned_d
  #endif // _di_f_type_int_128_t_

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

  #ifndef _di_f_type_int_128_t_
    #define F_type_size_max_128_negative_d 0x800000000000000000000000
    #define F_type_size_max_128_positive_d 0x7fffffffffffffffffffffff
    #define F_type_size_max_128_unsigned_d 0xffffffffffffffffffffffff
  #else
    #define F_type_size_max_128_negative_d F_type_size_max_64_negative_d
    #define F_type_size_max_128_positive_d F_type_size_max_64_positive_d
    #define F_type_size_max_128_unsigned_d F_type_size_max_64_unsigned_d
  #endif // _di_f_type_int_128_t_
#endif // _di_f_type_sizes_

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
  typedef f_int_128_t  f_number_signed_t;
  typedef f_uint_128_t f_number_unsigned_t;

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
 * Standard Input/Output types.
 *
 * For most systems, there is no standard warning nor is there a standard debug.
 * Therefore, these will map to standard output.
 */
#ifndef _di_f_type_input_output_
  #define F_type_debug_d   stdout
  #define F_type_error_d   stderr
  #define F_type_input_d   stdin
  #define F_type_output_d  stdout
  #define F_type_warning_d stdout

  #define F_type_descriptor_debug_d   STDOUT_FILENO
  #define F_type_descriptor_error_d   STDERR_FILENO
  #define F_type_descriptor_input_d   STDIN_FILENO
  #define F_type_descriptor_output_d  STDOUT_FILENO
  #define F_type_descriptor_warning_d STDOUT_FILENO
#endif // _di_f_type_input_output_

/**
 * Defines a variable to be used by arrays.
 *
 * There are problems in some libc's and systems that do not handle lengths greater than 2^63.
 * This is primarily a problem with libc string functions.
 * This may need to be set to a signed 64-bit integer on some system (or a smaller unsigned).
 * There are problems, however, with signed integers and binary operations as well as with overflows to be aware of.
 */
#ifndef _di_f_array_t_
  typedef f_number_unsigned_t f_array_length_t;

  #define f_array_length_t_initialize 0

  #define F_array_length_t_size_d     F_number_t_size_unsigned_d
  #define F_array_length_t_size_max_d F_number_t_size_max_unsigned_d
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
    mode.block = F_file_mode_all_rw_d; \
    mode.character = F_file_mode_all_rw_d; \
    mode.directory = F_file_mode_all_rwx_d; \
    mode.fifo = F_file_mode_all_rw_d; \
    mode.regular = F_file_mode_all_rw_d; \
    mode.link = F_file_mode_all_rw_d; \
    mode.socket = F_file_mode_all_rw_d; \
    mode.unknown = F_file_mode_all_rw_d;

  #define macro_f_mode_t_set_default_umask(mode, mask) \
    mode.block = F_file_mode_all_rw_d & ~mask; \
    mode.character = F_file_mode_all_rw_d & ~mask; \
    mode.directory = F_file_mode_all_rwx_d & ~mask; \
    mode.fifo = F_file_mode_all_rw_d & ~mask; \
    mode.regular = F_file_mode_all_rw_d & ~mask; \
    mode.link = F_file_mode_all_rw_d & ~mask; \
    mode.socket = F_file_mode_all_rw_d & ~mask; \
    mode.unknown = F_file_mode_all_rw_d & ~mask;

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

  #define f_time_t_initialize 0
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
 * The macro_f_fll_id_t_clear() only performs a minimalistic clear on the id.name string.
 * The first character in the string array is assigned to NULL.
 * For a more accurate clear, use memset() or something similar.
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
    id.type = 0; \
    id.used = 0;
#endif // _di_f_fll_id_t_

/**
 * An array of f_fll_id_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: The array of f_fll_id_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fll_ids_t_
  typedef struct {
    f_fll_id_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_fll_ids_t;

  #define f_fll_ids_t_initialize { 0, 0, 0 }
#endif // _di_f_fll_ids_t_

/**
 * This holds an array of f_fll_ids_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * array: The array of f_fll_id_t arrays.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fll_idss_t_
  typedef struct {
    f_fll_ids_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_fll_idss_t;

  #define f_fll_idss_t_initialize { 0, 0, 0 }
#endif // _di_f_fll_idss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_h
