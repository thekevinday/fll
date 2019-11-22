/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides datatypes that are arrays of some sort and require memory operations.
 */
#ifndef _F_type_array_h
#define _F_type_array_h

// fll-0 includes
#include <level_0/memory.h>
#include <level_0/type.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * An array of array lengths.
 *
 * array: An array of array lengths.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_array_lengths_
  typedef struct {
    f_array_length *array;
    f_array_length size;
    f_array_length used;
  } f_array_lengths;

  #define f_array_lengths_initialize { 0, 0, 0 }

  #define f_macro_array_lengths_clear(lengths) f_macro_memory_structure_clear(lengths)

  #define f_macro_array_lengths_new(status, lengths, length) f_macro_memory_structure_new(status, lengths, f_array_length, length)

  #define f_macro_array_lengths_delete(status, lengths)  f_macro_memory_structure_delete(status, lengths, f_array_length)
  #define f_macro_array_lengths_destroy(status, lengths) f_macro_memory_structure_destroy(status, lengths, f_array_length)

  #define f_macro_array_lengths_delete_simple(lengths)  f_macro_memory_structure_delete_simple(lengths, f_array_length)
  #define f_macro_array_lengths_destroy_simple(lengths) f_macro_memory_structure_destroy_simple(lengths, f_array_length)

  #define f_macro_array_lengths_resize(status, lengths, new_length) f_macro_memory_structure_resize(status, lengths, f_array_length, new_length)
  #define f_macro_array_lengths_adjust(status, lengths, new_length) f_macro_memory_structure_adjust(status, lengths, f_array_length, new_length)
#endif // _di_f_array_lengths_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_array_h
