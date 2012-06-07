/* FLL - Level 0
 * Project:       Types Array
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provides datatypes that are arrays of some sort and require memory operations.
 */
#ifndef _F_types_array_h
#define _F_types_array_h

// libc includes
#include <sys/stat.h> // contains mode_t, dev_t, gid_t, uid_t, etc..
#include <signal.h>

// fll includes
#include <level_0/types.h>
#include <level_0/memory.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_f_array_lengths_
  typedef struct {
    f_array_length *array;
    f_array_length  size;  // total amount of allocated space
    f_array_length  used;  // total number of allocated spaces used
  } f_array_lengths;

  #define f_array_lengths_initialize { f_array_length_initialize, f_array_length_initialize, f_array_length_initialize }

  #define f_delete_array_lengths(status, lengths) \
    f_delete_structure(status, lengths, f_array_length)

  #define f_destroy_array_lengths(status, lengths) \
    f_destroy_structure(status, lengths, f_array_length)

  #define f_resize_array_lengths(status, lengths, new_length) \
    f_resize_structure(status, lengths, f_array_length, new_length)

  #define f_adjust_array_lengths(status, lengths, new_length) \
    f_adjust_structure(status, lengths, f_array_length, new_length)
#endif // _di_f_array_lengths_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_types_array_h
