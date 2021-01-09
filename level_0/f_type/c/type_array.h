/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides datatypes that require memory operations.
 *
 * Because memory requires status.h, this is moved to a separate file to prevent circular dependency issues.
 */
#ifndef _F_type_array_h
#define _F_type_array_h

// fll-0 includes
#include <level_0/type.h>
#include <level_0/memory.h>

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
#ifndef _di_f_array_lengths_t_
  typedef struct {
    f_array_length_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_array_lengths_t;

  #define f_array_lengths_t_initialize { 0, 0, 0 }

  #define f_macro_array_lengths_t_clear(lengths) f_macro_memory_structure_clear(lengths);

  #define f_macro_array_lengths_t_new(status, lengths, length) f_macro_memory_structure_new(status, lengths, f_array_length_t, length);

  #define f_macro_array_lengths_t_resize(status, lengths, length) f_macro_memory_structure_resize(status, lengths, f_array_length_t, length);
  #define f_macro_array_lengths_t_adjust(status, lengths, length) f_macro_memory_structure_adjust(status, lengths, f_array_length_t, length);

  #define f_macro_array_lengths_t_increase(status, lengths)            f_macro_memory_structure_increase(status, lengths, f_array_length_t);
  #define f_macro_array_lengths_t_increase_by(status, lengths, amount) f_macro_memory_structure_increase_by(status, lengths, f_array_length_t, amount);
  #define f_macro_array_lengths_t_decrease_by(status, lengths, amount) f_macro_memory_structure_decrease_by(status, lengths, f_array_length_t, amount);
  #define f_macro_array_lengths_t_decimate_by(status, lengths, amount) f_macro_memory_structure_decimate_by(status, lengths, f_array_length_t, amount);

  #define f_macro_array_lengths_t_delete(status, lengths)  f_macro_memory_structure_delete(status, lengths, f_array_length_t);
  #define f_macro_array_lengths_t_destroy(status, lengths) f_macro_memory_structure_destroy(status, lengths, f_array_length_t);

  #define f_macro_array_lengths_t_delete_simple(lengths)  f_macro_memory_structure_delete_simple(lengths, f_array_length_t);
  #define f_macro_array_lengths_t_destroy_simple(lengths) f_macro_memory_structure_destroy_simple(lengths, f_array_length_t);
#endif // _di_f_array_lengths_t_

/**
 * An array of an array of array lengths.
 *
 * array: the array of an array of array lengths.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_array_lengthss_t_
  typedef struct {
    f_array_lengths_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_array_lengthss_t;

  #define f_array_lengthss_t_initialize { 0, 0, 0 }

  #define f_macro_array_lengthss_t_clear(lengths) f_macro_memory_structures_clear(lengths);

  #define f_macro_array_lengthss_t_new(status, lengths, length) f_macro_memory_structures_new(status, lengths, f_array_length_t, length);

  #define f_macro_array_lengthss_t_delete(status, lengths)  f_macro_memory_structures_delete(status, lengths, f_array_length_t, f_array_lengths_t);
  #define f_macro_array_lengthss_t_destroy(status, lengths) f_macro_memory_structures_destroy(status, lengths, f_array_length_t, f_array_lengths_t);

  #define f_macro_array_lengthss_t_delete_simple(lengths)  f_macro_memory_structures_delete_simple(lengths, f_array_length_t, f_array_lengths_t);
  #define f_macro_array_lengthss_t_destroy_simple(lengths) f_macro_memory_structures_destroy_simple(lengths, f_array_length_t, f_array_lengths_t);

  #define f_macro_array_lengthss_t_resize(status, lengths, length) f_macro_memory_structures_resize(status, lengths, f_array_length_t, f_array_lengths_t, length, f_array_length_t);
  #define f_macro_array_lengthss_t_adjust(status, lengths, length) f_macro_memory_structures_adjust(status, lengths, f_array_length_t, f_array_lengths_t, length, f_array_length_t);
#endif // _di_f_array_lengthss_t_

/**
 * An array of f_cell_t.
 *
 * array: the array of f_cell_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_cells_t_
  typedef struct {
    f_cell_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_cells_t;

  #define f_cells_t_initialize {0, 0, 0}

  #define f_macro_cells_t_clear(cells) f_macro_memory_structure_clear(cells);

  #define f_macro_cells_t_new(status, cells, length) f_macro_memory_structure_new(status, cells, f_cell_t, length);

  #define f_macro_cells_t_resize(status, cells, length) f_macro_memory_structure_resize(status, cells, f_cell_t, length);
  #define f_macro_cells_t_adjust(status, cells, length) f_macro_memory_structure_adjust(status, cells, f_cell_t, length);

  #define f_macro_cells_t_increase(status, cells)            f_macro_memory_structure_increase(status, cells, f_cell_t);
  #define f_macro_cells_t_increase_by(status, cells, amount) f_macro_memory_structure_increase_by(status, cells, f_cell_t, amount);
  #define f_macro_cells_t_decrease_by(status, cells, amount) f_macro_memory_structure_decrease_by(status, cells, f_cell_t, amount);
  #define f_macro_cells_t_decimate_by(status, cells, amount) f_macro_memory_structure_decimate_by(status, cells, f_cell_t, amount);

  #define f_macro_cells_t_delete(status, cells)  f_macro_memory_structure_delete(status, cells, f_cell_t);
  #define f_macro_cells_t_destroy(status, cells) f_macro_memory_structure_destroy(status, cells, f_cell_t);

  #define f_macro_cells_t_delete_simple(cells)  f_macro_memory_structure_delete_simple(cells, f_cell_t);
  #define f_macro_cells_t_destroy_simple(cells) f_macro_memory_structure_destroy_simple(cells, f_cell_t);


#endif // _di_f_cells_t_

/**
 * This holds an array of f_cells_t.
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

  #define f_macro_cellss_t_clear(rangess) f_macro_memory_structures_clear(rangess);

  #define f_macro_cellss_t_new(status, rangess, length) f_macro_memory_structures_new(status, rangess, f_cells_t, length);

  #define f_macro_cellss_t_delete(status, rangess)  f_macro_memory_structures_delete(status, rangess, f_cell_t, f_cells_t);
  #define f_macro_cellss_t_destroy(status, rangess) f_macro_memory_structures_destroy(status, rangess, f_cell_t, f_cells_t);

  #define f_macro_cellss_t_delete_simple(rangess)  f_macro_memory_structures_delete_simple(rangess, f_cell_t, f_cells_t);
  #define f_macro_cellss_t_destroy_simple(rangess) f_macro_memory_structures_destroy_simple(rangess, f_cell_t, f_cells_t);

  #define f_macro_cellss_t_resize(status, rangess, length) f_macro_memory_structures_resize(status, rangess, f_cell_t, f_cells_t, length, f_array_length_t);
  #define f_macro_cellss_t_adjust(status, rangess, length) f_macro_memory_structures_adjust(status, rangess, f_cell_t, f_cells_t, length, f_array_length_t);
#endif // _di_f_cellss_t_

/**
 * An array of array int8_t.
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

  #define f_macro_int8s_t_clear(int8s) f_macro_memory_structure_clear(int8s);

  #define f_macro_int8s_t_new(status, int8s, length) f_macro_memory_structure_new(status, int8s, int8_t, length);

  #define f_macro_int8s_t_resize(status, int8s, length) f_macro_memory_structure_resize(status, int8s, int8_t, length);
  #define f_macro_int8s_t_adjust(status, int8s, length) f_macro_memory_structure_adjust(status, int8s, int8_t, length);

  #define f_macro_int8s_t_delete(status, int8s)  f_macro_memory_structure_delete(status, int8s, int8_t);
  #define f_macro_int8s_t_destroy(status, int8s) f_macro_memory_structure_destroy(status, int8s, int8_t);

  #define f_macro_int8s_t_delete_simple(int8s)  f_macro_memory_structure_delete_simple(int8s, int8_t);
  #define f_macro_int8s_t_destroy_simple(int8s) f_macro_memory_structure_destroy_simple(int8s, int8_t);

  #define f_macro_int8s_t_increase(status, int8s)            f_macro_memory_structure_increase(status, int8s, int8_t);
  #define f_macro_int8s_t_increase_by(status, int8s, amount) f_macro_memory_structure_increase_by(status, int8s, int8_t, amount);
  #define f_macro_int8s_t_decrease_by(status, int8s, amount) f_macro_memory_structure_decrease_by(status, int8s, int8_t, amount);
  #define f_macro_int8s_t_decimate_by(status, int8s, amount) f_macro_memory_structure_decimate_by(status, int8s, int8_t, amount);
#endif // _di_int8s_t_

/**
 * An array of an array of array int8_t.
 *
 * array: the array of an array of array int8_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_int8ss_t_
  typedef struct {
    f_int8s_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_int8ss_t;

  #define f_int8ss_t_initialize { 0, 0, 0 }

  #define f_macro_int8ss_t_clear(numbers) f_macro_memory_structures_clear(numbers);

  #define f_macro_int8ss_t_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, int8_t, length);

  #define f_macro_int8ss_t_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, int8_t, f_int8s_t);
  #define f_macro_int8ss_t_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, int8_t, f_int8s_t);

  #define f_macro_int8ss_t_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, int8_t, f_int8s_t);
  #define f_macro_int8ss_t_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, int8_t, f_int8s_t);

  #define f_macro_int8ss_t_resize(status, numbers, length) f_macro_memory_structures_resize(status, numbers, int8_t, f_int8s_t, length, f_array_length_t);
  #define f_macro_int8ss_t_adjust(status, numbers, length) f_macro_memory_structures_adjust(status, numbers, int8_t, f_int8s_t, length, f_array_length_t);
#endif // _di_int8ss_t_

/**
 * An array of array uint8_t.
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

  #define f_macro_uint8s_t_clear(uint8s) f_macro_memory_structure_clear(uint8s);

  #define f_macro_uint8s_t_new(status, uint8s, length) f_macro_memory_structure_new(status, uint8s, uint8_t, length);

  #define f_macro_uint8s_t_adjust(status, uint8s, length) f_macro_memory_structure_adjust(status, uint8s, uint8_t, length);
  #define f_macro_uint8s_t_resize(status, uint8s, length) f_macro_memory_structure_resize(status, uint8s, uint8_t, length);

  #define f_macro_uint8s_t_increase(status, uint8s)            f_macro_memory_structure_increase(status, uint8s, uint8_t);
  #define f_macro_uint8s_t_increase_by(status, uint8s, amount) f_macro_memory_structure_increase_by(status, uint8s, uint8_t, amount);
  #define f_macro_uint8s_t_decrease_by(status, uint8s, amount) f_macro_memory_structure_decrease_by(status, uint8s, uint8_t, amount);
  #define f_macro_uint8s_t_decimate_by(status, uint8s, amount) f_macro_memory_structure_decimate_by(status, uint8s, uint8_t, amount);

  #define f_macro_uint8s_t_delete(status, uint8s)  f_macro_memory_structure_delete(status, uint8s, uint8_t);
  #define f_macro_uint8s_t_destroy(status, uint8s) f_macro_memory_structure_destroy(status, uint8s, uint8_t);

  #define f_macro_uint8s_t_delete_simple(uint8s)  f_macro_memory_structure_delete_simple(uint8s, uint8_t);
  #define f_macro_uint8s_t_destroy_simple(uint8s) f_macro_memory_structure_destroy_simple(uint8s, uint8_t);
#endif // _di_uint8s_t_

/**
 * An array of an array of array uint8_t.
 *
 * array: the array of an array of array uint8_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_uint8ss_t_
  typedef struct {
    f_uint8s_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_uint8ss_t;

  #define f_uint8ss_t_initialize { 0, 0, 0 }

  #define f_macro_uint8ss_t_clear(numbers) f_macro_memory_structures_clear(numbers);

  #define f_macro_uint8ss_t_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, uint8_t, length);

  #define f_macro_uint8ss_t_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, uint8_t, f_uint8s_t);
  #define f_macro_uint8ss_t_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, uint8_t, f_uint8s_t);
  #define f_macro_uint8ss_t_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, uint8_t, f_uint8s_t);

  #define f_macro_uint8ss_t_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, uint8_t, f_uint8s_t);
  #define f_macro_uint8ss_t_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, uint8_t, f_uint8s_t);

  #define f_macro_uint8ss_t_resize(status, numbers, length) f_macro_memory_structures_resize(status, numbers, uint8_t, f_uint8s_t, length, f_array_length_t);
  #define f_macro_uint8ss_t_adjust(status, numbers, length) f_macro_memory_structures_adjust(status, numbers, uint8_t, f_uint8s_t, length, f_array_length_t);
#endif // _di_uint8ss_t_

/**
 * An array of array int16_t.
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

  #define f_macro_int16s_t_clear(int16s) f_macro_memory_structure_clear(int16s);

  #define f_macro_int16s_t_new(status, int16s, length) f_macro_memory_structure_new(status, int16s, int16_t, length);

  #define f_macro_int16s_t_adjust(status, int16s, length) f_macro_memory_structure_adjust(status, int16s, int16_t, length);
  #define f_macro_int16s_t_resize(status, int16s, length) f_macro_memory_structure_resize(status, int16s, int16_t, length);

  #define f_macro_int16s_t_increase(status, int16s)            f_macro_memory_structure_increase(status, int16s, int16_t);
  #define f_macro_int16s_t_increase_by(status, int16s, amount) f_macro_memory_structure_increase_by(status, int16s, int16_t, amount);
  #define f_macro_int16s_t_decrease_by(status, int16s, amount) f_macro_memory_structure_decrease_by(status, int16s, int16_t, amount);
  #define f_macro_int16s_t_decimate_by(status, int16s, amount) f_macro_memory_structure_decimate_by(status, int16s, int16_t, amount);

  #define f_macro_int16s_t_delete(status, int16s)  f_macro_memory_structure_delete(status, int16s, int16_t);
  #define f_macro_int16s_t_destroy(status, int16s) f_macro_memory_structure_destroy(status, int16s, int16_t);

  #define f_macro_int16s_t_delete_simple(int16s)  f_macro_memory_structure_delete_simple(int16s, int16_t);
  #define f_macro_int16s_t_destroy_simple(int16s) f_macro_memory_structure_destroy_simple(int16s, int16_t);
#endif // _di_int16s_t_

/**
 * An array of an array of array int16_t.
 *
 * array: the array of an array of array int16_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_int16ss_t_
  typedef struct {
    f_int16s_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_int16ss_t;

  #define f_int16ss_t_initialize { 0, 0, 0 }

  #define f_macro_int16ss_t_clear(numbers) f_macro_memory_structures_clear(numbers);

  #define f_macro_int16ss_t_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, int16_t, length);

  #define f_macro_int16ss_t_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, int16_t, f_int16s_t);
  #define f_macro_int16ss_t_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, int16_t, f_int16s_t);

  #define f_macro_int16ss_t_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, int16_t, f_int16s_t);
  #define f_macro_int16ss_t_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, int16_t, f_int16s_t);

  #define f_macro_int16ss_t_resize(status, numbers, length) f_macro_memory_structures_resize(status, numbers, int16_t, f_int16s_t, length, f_array_length_t);
  #define f_macro_int16ss_t_adjust(status, numbers, length) f_macro_memory_structures_adjust(status, numbers, int16_t, f_int16s_t, length, f_array_length_t);
#endif // _di_int16ss_t_

/**
 * An array of array uint16_t.
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

  #define f_macro_uint16s_t_clear(uint16s) f_macro_memory_structure_clear(uint16s);

  #define f_macro_uint16s_t_new(status, uint16s, length) f_macro_memory_structure_new(status, uint16s, uint16_t, length);

  #define f_macro_uint16s_t_adjust(status, uint16s, length) f_macro_memory_structure_adjust(status, uint16s, uint16_t, length);
  #define f_macro_uint16s_t_resize(status, uint16s, length) f_macro_memory_structure_resize(status, uint16s, uint16_t, length);

  #define f_macro_uint16s_t_increase(status, uint16s)            f_macro_memory_structure_increase(status, uint16s, uint16_t);
  #define f_macro_uint16s_t_increase_by(status, uint16s, amount) f_macro_memory_structure_increase_by(status, uint16s, uint16_t, amount);
  #define f_macro_uint16s_t_decrease_by(status, uint16s, amount) f_macro_memory_structure_decrease_by(status, uint16s, uint16_t, amount);
  #define f_macro_uint16s_t_decimate_by(status, uint16s, amount) f_macro_memory_structure_decimate_by(status, uint16s, uint16_t, amount);

  #define f_macro_uint16s_t_delete(status, uint16s)  f_macro_memory_structure_delete(status, uint16s, uint16_t);
  #define f_macro_uint16s_t_destroy(status, uint16s) f_macro_memory_structure_destroy(status, uint16s, uint16_t);

  #define f_macro_uint16s_t_delete_simple(uint16s)  f_macro_memory_structure_delete_simple(uint16s, uint16_t);
  #define f_macro_uint16s_t_destroy_simple(uint16s) f_macro_memory_structure_destroy_simple(uint16s, uint16_t);
#endif // _di_uint16s_t_

/**
 * An array of an array of array uint16_t.
 *
 * array: the array of an array of array uint16_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_uint16ss_t_
  typedef struct {
    f_uint16s_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_uint16ss_t;

  #define f_uint16ss_t_initialize { 0, 0, 0 }

  #define f_macro_uint16ss_t_clear(numbers) f_macro_memory_structures_clear(numbers);

  #define f_macro_uint16ss_t_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, uint16_t, length);

  #define f_macro_uint16ss_t_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, uint16_t, f_uint16s_t);
  #define f_macro_uint16ss_t_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, uint16_t, f_uint16s_t);

  #define f_macro_uint16ss_t_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, uint16_t, f_uint16s_t);
  #define f_macro_uint16ss_t_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, uint16_t, f_uint16s_t);

  #define f_macro_uint16ss_t_resize(status, numbers, length) f_macro_memory_structures_resize(status, numbers, uint16_t, f_uint16s_t, length, f_array_length_t);
  #define f_macro_uint16ss_t_adjust(status, numbers, length) f_macro_memory_structures_adjust(status, numbers, uint16_t, f_uint16s_t, length, f_array_length_t);
#endif // _di_uint16ss_t_

/**
 * An array of array int32_t.
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

  #define f_macro_int32s_t_clear(int32s) f_macro_memory_structure_clear(int32s);

  #define f_macro_int32s_t_new(status, int32s, length) f_macro_memory_structure_new(status, int32s, int32_t, length);

  #define f_macro_int32s_t_adjust(status, int32s, length) f_macro_memory_structure_adjust(status, int32s, int32_t, length);
  #define f_macro_int32s_t_resize(status, int32s, length) f_macro_memory_structure_resize(status, int32s, int32_t, length);

  #define f_macro_int32s_t_increase(status, int32s)            f_macro_memory_structure_increase(status, int32s, int32_t);
  #define f_macro_int32s_t_increase_by(status, int32s, amount) f_macro_memory_structure_increase_by(status, int32s, int32_t, amount);
  #define f_macro_int32s_t_decrease_by(status, int32s, amount) f_macro_memory_structure_decrease_by(status, int32s, int32_t, amount);
  #define f_macro_int32s_t_decimate_by(status, int32s, amount) f_macro_memory_structure_decimate_by(status, int32s, int32_t, amount);

  #define f_macro_int32s_t_delete(status, int32s)  f_macro_memory_structure_delete(status, int32s, int32_t);
  #define f_macro_int32s_t_destroy(status, int32s) f_macro_memory_structure_destroy(status, int32s, int32_t);

  #define f_macro_int32s_t_delete_simple(int32s)  f_macro_memory_structure_delete_simple(int32s, int32_t);
  #define f_macro_int32s_t_destroy_simple(int32s) f_macro_memory_structure_destroy_simple(int32s, int32_t);
#endif // _di_int32s_t_

/**
 * An array of an array of array int32_t.
 *
 * array: the array of an array of array int32_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_int32ss_t_
  typedef struct {
    f_int32s_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_int32ss_t;

  #define f_int32ss_t_initialize { 0, 0, 0 }

  #define f_macro_int32ss_t_clear(numbers) f_macro_memory_structures_clear(numbers);

  #define f_macro_int32ss_t_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, int32_t, length);

  #define f_macro_int32ss_t_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, int32_t, f_int32s_t);
  #define f_macro_int32ss_t_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, int32_t, f_int32s_t);

  #define f_macro_int32ss_t_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, int32_t, f_int32s_t);
  #define f_macro_int32ss_t_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, int32_t, f_int32s_t);

  #define f_macro_int32ss_t_resize(status, numbers, length) f_macro_memory_structures_resize(status, numbers, int32_t, f_int32s_t, length, f_array_length_t);
  #define f_macro_int32ss_t_adjust(status, numbers, length) f_macro_memory_structures_adjust(status, numbers, int32_t, f_int32s_t, length, f_array_length_t);
#endif // _di_int32ss_t_

/**
 * An array of array uint32_t.
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

  #define f_macro_uint32s_t_clear(uint32s) f_macro_memory_structure_clear(uint32s);

  #define f_macro_uint32s_t_new(status, uint32s, length) f_macro_memory_structure_new(status, uint32s, uint32_t, length);

  #define f_macro_uint32s_t_adjust(status, uint32s, length) f_macro_memory_structure_adjust(status, uint32s, uint32_t, length);
  #define f_macro_uint32s_t_resize(status, uint32s, length) f_macro_memory_structure_resize(status, uint32s, uint32_t, length);

  #define f_macro_uint32s_t_increase(status, uint32s)            f_macro_memory_structure_increase(status, uint32s, uint32_t);
  #define f_macro_uint32s_t_increase_by(status, uint32s, amount) f_macro_memory_structure_increase_by(status, uint32s, uint32_t, amount);
  #define f_macro_uint32s_t_decrease_by(status, uint32s, amount) f_macro_memory_structure_decrease_by(status, uint32s, uint32_t, amount);
  #define f_macro_uint32s_t_decimate_by(status, uint32s, amount) f_macro_memory_structure_decimate_by(status, uint32s, uint32_t, amount);

  #define f_macro_uint32s_t_delete(status, uint32s)  f_macro_memory_structure_delete(status, uint32s, uint32_t);
  #define f_macro_uint32s_t_destroy(status, uint32s) f_macro_memory_structure_destroy(status, uint32s, uint32_t);

  #define f_macro_uint32s_t_delete_simple(uint32s)  f_macro_memory_structure_delete_simple(uint32s, uint32_t);
  #define f_macro_uint32s_t_destroy_simple(uint32s) f_macro_memory_structure_destroy_simple(uint32s, uint32_t);
#endif // _di_uint32s_t_

/**
 * An array of an array of array uint32_t.
 *
 * array: the array of an array of array uint32_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_uint32ss_t_
  typedef struct {
    f_uint32s_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_uint32ss_t;

  #define f_uint32ss_t_initialize { 0, 0, 0 }

  #define f_macro_uint32ss_t_clear(numbers) f_macro_memory_structures_clear(numbers);

  #define f_macro_uint32ss_t_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, uint32_t, length);

  #define f_macro_uint32ss_t_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, uint32_t, f_uint32s_t);
  #define f_macro_uint32ss_t_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, uint32_t, f_uint32s_t);

  #define f_macro_uint32ss_t_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, uint32_t, f_uint32s_t);
  #define f_macro_uint32ss_t_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, uint32_t, f_uint32s_t);

  #define f_macro_uint32ss_t_resize(status, numbers, length) f_macro_memory_structures_resize(status, numbers, uint32_t, f_uint32s_t, length, f_array_length_t);
  #define f_macro_uint32ss_t_adjust(status, numbers, length) f_macro_memory_structures_adjust(status, numbers, uint32_t, f_uint32s_t, length, f_array_length_t);
#endif // _di_uint32ss_t_

/**
 * An array of array int64_t.
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

  #define f_macro_int64s_t_clear(int64s) f_macro_memory_structure_clear(int64s);

  #define f_macro_int64s_t_new(status, int64s, length) f_macro_memory_structure_new(status, int64s, int64_t, length);

  #define f_macro_int64s_t_adjust(status, int64s, length) f_macro_memory_structure_adjust(status, int64s, int64_t, length);
  #define f_macro_int64s_t_resize(status, int64s, length) f_macro_memory_structure_resize(status, int64s, int64_t, length);

  #define f_macro_int64s_t_increase(status, int64s)            f_macro_memory_structure_increase(status, int64s, int64_t);
  #define f_macro_int64s_t_increase_by(status, int64s, amount) f_macro_memory_structure_increase_by(status, int64s, int64_t, amount);
  #define f_macro_int64s_t_decrease_by(status, int64s, amount) f_macro_memory_structure_decrease_by(status, int64s, int64_t, amount);
  #define f_macro_int64s_t_decimate_by(status, int64s, amount) f_macro_memory_structure_decimate_by(status, int64s, int64_t, amount);

  #define f_macro_int64s_t_delete(status, int64s)  f_macro_memory_structure_delete(status, int64s, int64_t);
  #define f_macro_int64s_t_destroy(status, int64s) f_macro_memory_structure_destroy(status, int64s, int64_t);

  #define f_macro_int64s_t_delete_simple(int64s)  f_macro_memory_structure_delete_simple(int64s, int64_t);
  #define f_macro_int64s_t_destroy_simple(int64s) f_macro_memory_structure_destroy_simple(int64s, int64_t);
#endif // _di_int64s_t_

/**
 * An array of an array of array int64_t.
 *
 * array: the array of an array of array int64_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_int64ss_t_
  typedef struct {
    f_int64s_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_int64ss_t;

  #define f_int64ss_t_initialize { 0, 0, 0 }

  #define f_macro_int64ss_t_clear(numbers) f_macro_memory_structures_clear(numbers);

  #define f_macro_int64ss_t_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, int64_t, length);

  #define f_macro_int64ss_t_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, int64_t, f_int64s_t);
  #define f_macro_int64ss_t_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, int64_t, f_int64s_t);

  #define f_macro_int64ss_t_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, int64_t, f_int64s_t);
  #define f_macro_int64ss_t_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, int64_t, f_int64s_t);

  #define f_macro_int64ss_t_resize(status, numbers, length) f_macro_memory_structures_resize(status, numbers, int64_t, f_int64s_t, length, f_array_length_t);
  #define f_macro_int64ss_t_adjust(status, numbers, length) f_macro_memory_structures_adjust(status, numbers, int64_t, f_int64s_t, length, f_array_length_t);
#endif // _di_int64ss_t_

/**
 * An array of array uint64_t.
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

  #define f_macro_uint64s_t_clear(uint64s) f_macro_memory_structure_clear(uint64s);

  #define f_macro_uint64s_t_new(status, uint64s, length) f_macro_memory_structure_new(status, uint64s, uint64_t, length);

  #define f_macro_uint64s_t_adjust(status, uint64s, length) f_macro_memory_structure_adjust(status, uint64s, uint64_t, length);
  #define f_macro_uint64s_t_resize(status, uint64s, length) f_macro_memory_structure_resize(status, uint64s, uint64_t, length);

  #define f_macro_uint64s_t_increase(status, uint64s)            f_macro_memory_structure_increase(status, uint64s, uint64_t);
  #define f_macro_uint64s_t_increase_by(status, uint64s, amount) f_macro_memory_structure_increase_by(status, uint64s, uint64_t, amount);
  #define f_macro_uint64s_t_decrease_by(status, uint64s, amount) f_macro_memory_structure_decrease_by(status, uint64s, uint64_t, amount);
  #define f_macro_uint64s_t_decimate_by(status, uint64s, amount) f_macro_memory_structure_decimate_by(status, uint64s, uint64_t, amount);

  #define f_macro_uint64s_t_delete(status, uint64s)  f_macro_memory_structure_delete(status, uint64s, uint64_t);
  #define f_macro_uint64s_t_destroy(status, uint64s) f_macro_memory_structure_destroy(status, uint64s, uint64_t);

  #define f_macro_uint64s_t_delete_simple(uint64s)  f_macro_memory_structure_delete_simple(uint64s, uint64_t);
  #define f_macro_uint64s_t_destroy_simple(uint64s) f_macro_memory_structure_destroy_simple(uint64s, uint64_t);
#endif // _di_uint64s_t_

/**
 * An array of an array of array uint64_t.
 *
 * array: the array of an array of array uint64_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_uint64ss_t_
  typedef struct {
    f_uint64s_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_uint64ss_t;

  #define f_uint64ss_t_initialize { 0, 0, 0 }

  #define f_macro_uint64ss_t_clear(numbers) f_macro_memory_structures_clear(numbers);

  #define f_macro_uint64ss_t_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, uint64_t, length);

  #define f_macro_uint64ss_t_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, uint64_t, f_uint64s_t);
  #define f_macro_uint64ss_t_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, uint64_t, f_uint64s_t);

  #define f_macro_uint64ss_t_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, uint64_t, f_uint64s_t);
  #define f_macro_uint64ss_t_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, uint64_t, f_uint64s_t);

  #define f_macro_uint64ss_t_resize(status, numbers, length) f_macro_memory_structures_resize(status, numbers, uint64_t, f_uint64s_t, length, f_array_length_t);
  #define f_macro_uint64ss_t_adjust(status, numbers, length) f_macro_memory_structures_adjust(status, numbers, uint64_t, f_uint64s_t, length, f_array_length_t);
#endif // _di_uint64ss_t_

#ifndef __SIZEOF_INT128__
  /**
   * An array of array __int128_t.
   *
   * array: An array of __int128_t.
   * size:  Total amount of allocated space.
   * used:  Total number of allocated spaces used.
   */
  #ifndef _di_int128s_t_
    typedef struct {
      __int128_t *array;

      f_array_length_t size;
      f_array_length_t used;
    } f_int128s_t;

    #define f_int128s_t_initialize { 0, 0, 0 }

    #define f_macro_int128s_t_clear(int128s) f_macro_memory_structure_clear(int128s);

    #define f_macro_int128s_t_new(status, int128s, length) f_macro_memory_structure_new(status, int128s, __int128_t, length);

    #define f_macro_int128s_t_adjust(status, int128s, length) f_macro_memory_structure_adjust(status, int128s, __int128_t, length);
    #define f_macro_int128s_t_resize(status, int128s, length) f_macro_memory_structure_resize(status, int128s, __int128_t, length);

    #define f_macro_int128s_t_increase(status, int128s)            f_macro_memory_structure_increase(status, int128s, __int128_t);
    #define f_macro_int128s_t_increase_by(status, int128s, amount) f_macro_memory_structure_increase_by(status, int128s, __int128_t, amount);
    #define f_macro_int128s_t_decrease_by(status, int128s, amount) f_macro_memory_structure_decrease_by(status, int128s, __int128_t, amount);
    #define f_macro_int128s_t_decimate_by(status, int128s, amount) f_macro_memory_structure_decimate_by(status, int128s, __int128_t, amount);

    #define f_macro_int128s_t_delete(status, int128s)  f_macro_memory_structure_delete(status, int128s, __int128_t);
    #define f_macro_int128s_t_destroy(status, int128s) f_macro_memory_structure_destroy(status, int128s, __int128_t);

    #define f_macro_int128s_t_delete_simple(int128s)  f_macro_memory_structure_delete_simple(int128s, __int128_t);
    #define f_macro_int128s_t_destroy_simple(int128s) f_macro_memory_structure_destroy_simple(int128s, __int128_t);
  #endif // _di_int128s_t_

  /**
   * An array of an array of array __int128_t.
   *
   * array: the array of an array of array __int128_t.
   * size: total amount of allocated space.
   * used: total number of allocated spaces used.
   */
  #ifndef _di_int128ss_t_
    typedef struct {
      f_int128s_t *array;

      f_array_length_t size;
      f_array_length_t used;
    } f_int128ss_t;

    #define f_int128ss_t_initialize { 0, 0, 0 }

    #define f_macro_int128ss_t_clear(numbers) f_macro_memory_structures_clear(numbers);

    #define f_macro_int128ss_t_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, __int128_t, length);

    #define f_macro_int128ss_t_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, __int128_t, f_int128s_t);
    #define f_macro_int128ss_t_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, __int128_t, f_int128s_t);

    #define f_macro_int128ss_t_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, __int128_t, f_int128s_t);
    #define f_macro_int128ss_t_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, __int128_t, f_int128s_t);

    #define f_macro_int128ss_t_resize(status, numbers, length) f_macro_memory_structures_resize(status, numbers, __int128_t, f_int128s_t, length, f_array_length_t);
    #define f_macro_int128ss_t_adjust(status, numbers, length) f_macro_memory_structures_adjust(status, numbers, __int128_t, f_int128s_t, length, f_array_length_t);
  #endif // _di_int128ss_t_

  /**
   * An array of array __uint128_t.
   *
   * array: An array of __uint128_t.
   * size:  Total amount of allocated space.
   * used:  Total number of allocated spaces used.
   */
  #ifndef _di_uint128s_t_
    typedef struct {
      __uint128_t *array;

      f_array_length_t size;
      f_array_length_t used;
    } f_uint128s_t;

    #define f_uint128s_t_initialize { 0, 0, 0 }

    #define f_macro_uint128s_t_clear(uint128s) f_macro_memory_structure_clear(uint128s);

    #define f_macro_uint128s_t_new(status, uint128s, length) f_macro_memory_structure_new(status, uint128s, __uint128_t, length);

    #define f_macro_uint128s_t_adjust(status, uint128s, length) f_macro_memory_structure_adjust(status, uint128s, __uint128_t, length);
    #define f_macro_uint128s_t_resize(status, uint128s, length) f_macro_memory_structure_resize(status, uint128s, __uint128_t, length);

    #define f_macro_uint128s_t_increase(status, uint128s)            f_macro_memory_structure_increase(status, uint128s, __uint128_t);
    #define f_macro_uint128s_t_increase_by(status, uint128s, amount) f_macro_memory_structure_increase_by(status, uint128s, __uint128_t, amount);
    #define f_macro_uint128s_t_decrease_by(status, uint128s, amount) f_macro_memory_structure_decrease_by(status, uint128s, __uint128_t, amount);
    #define f_macro_uint128s_t_decimate_by(status, uint128s, amount) f_macro_memory_structure_decimate_by(status, uint128s, __uint128_t, amount);

    #define f_macro_uint128s_t_delete(status, uint128s)  f_macro_memory_structure_delete(status, uint128s, __uint128_t);
    #define f_macro_uint128s_t_destroy(status, uint128s) f_macro_memory_structure_destroy(status, uint128s, __uint128_t);

    #define f_macro_uint128s_t_delete_simple(uint128s)  f_macro_memory_structure_delete_simple(uint128s, __uint128_t);
    #define f_macro_uint128s_t_destroy_simple(uint128s) f_macro_memory_structure_destroy_simple(uint128s, __uint128_t);
  #endif // _di_uint128s_t_

  /**
   * An array of an array of array __uint128_t.
   *
   * array: the array of an array of array __uint128_t.
   * size: total amount of allocated space.
   * used: total number of allocated spaces used.
   */
  #ifndef _di_uint128ss_t_
    typedef struct {
      f_uint128s_t *array;

      f_array_length_t size;
      f_array_length_t used;
    } f_uint128ss_t;

    #define f_uint128ss_t_initialize { 0, 0, 0 }

    #define f_macro_uint128ss_t_clear(numbers) f_macro_memory_structures_clear(numbers);

    #define f_macro_uint128ss_t_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, __uint128_t, length);

    #define f_macro_uint128ss_t_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, __uint128_t, f_uint128s_t);
    #define f_macro_uint128ss_t_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, __uint128_t, f_uint128s_t);

    #define f_macro_uint128ss_t_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, __uint128_t, f_uint128s_t);
    #define f_macro_uint128ss_t_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, __uint128_t, f_uint128s_t);

    #define f_macro_uint128ss_t_resize(status, numbers, length) f_macro_memory_structures_resize(status, numbers, __uint128_t, f_uint128s_t, length, f_array_length_t);
    #define f_macro_uint128ss_t_adjust(status, numbers, length) f_macro_memory_structures_adjust(status, numbers, __uint128_t, f_uint128s_t, length, f_array_length_t);
  #endif // _di_uint128ss_t_
#else
  /**
   * An array of array int64_t acting in place of __int128_t when 128 is not supported.
   *
   * array: An array of int64_t acting in place of __int128_t when 128 is not supported.
   * size:  Total amount of allocated space.
   * used:  Total number of allocated spaces used.
   */
  #ifndef _di_int128s_t_
    typedef struct {
      int64_t *array;

      f_array_length_t size;
      f_array_length_t used;
    } f_int128s_t;

    #define f_int128s_t_initialize { 0, 0, 0 }

    #define f_macro_int128s_t_clear(int128s) f_macro_memory_structure_clear(int128s);

    #define f_macro_int128s_t_new(status, int128s, length) f_macro_memory_structure_new(status, int128s, int64_t, length);

    #define f_macro_int128s_t_adjust(status, int128s, length) f_macro_memory_structure_adjust(status, int128s, int64_t, length);
    #define f_macro_int128s_t_resize(status, int128s, length) f_macro_memory_structure_resize(status, int128s, int64_t, length);

    #define f_macro_int128s_t_increase(status, int128s)            f_macro_memory_structure_increase(status, int128s, int64_t);
    #define f_macro_int128s_t_increase_by(status, int128s, amount) f_macro_memory_structure_increase_by(status, int128s, int64_t, amount);
    #define f_macro_int128s_t_decrease_by(status, int128s, amount) f_macro_memory_structure_decrease_by(status, int128s, int64_t, amount);
    #define f_macro_int128s_t_decimate_by(status, int128s, amount) f_macro_memory_structure_decimate_by(status, int128s, int64_t, amount);

    #define f_macro_int128s_t_delete(status, int128s)  f_macro_memory_structure_delete(status, int128s, int64_t);
    #define f_macro_int128s_t_destroy(status, int128s) f_macro_memory_structure_destroy(status, int128s, int64_t);

    #define f_macro_int128s_t_delete_simple(int128s)  f_macro_memory_structure_delete_simple(int128s, int64_t);
    #define f_macro_int128s_t_destroy_simple(int128s) f_macro_memory_structure_destroy_simple(int128s, int64_t);
  #endif // _di_int128s_t_

  /**
   * An array of an array of array int64_t acting in place of __int128_t when 128 is not supported.
   *
   * array: the array of an array of array int64_t acting in place of __int128_t when 128 is not supported.
   * size: total amount of allocated space.
   * used: total number of allocated spaces used.
   */
  #ifndef _di_int128ss_t_
    typedef struct {
      f_int128s_t *array;

      f_array_length_t size;
      f_array_length_t used;
    } f_int128ss_t;

    #define f_int128ss_t_initialize { 0, 0, 0 }

    #define f_macro_int128ss_t_clear(numbers) f_macro_memory_structures_clear(numbers);

    #define f_macro_int128ss_t_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, int64_t, length);

    #define f_macro_int128ss_t_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, int64_t, f_int128s_t);
    #define f_macro_int128ss_t_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, int64_t, f_int128s_t);

    #define f_macro_int128ss_t_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, int64_t, f_int128s_t);
    #define f_macro_int128ss_t_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, int64_t, f_int128s_t);

    #define f_macro_int128ss_t_resize(status, numbers, length) f_macro_memory_structures_resize(status, numbers, int64_t, f_int128s_t, length, f_array_length_t);
    #define f_macro_int128ss_t_adjust(status, numbers, length) f_macro_memory_structures_adjust(status, numbers, int64_t, f_int128s_t, length, f_array_length_t);
  #endif // _di_int128ss_t_

  /**
   * An array of array uint64_t acting in place of __uint128_t when 128 is not supported.
   *
   * array: An array of uint64_t acting in place of __uint128_t when 128 is not supported.
   * size:  Total amount of allocated space.
   * used:  Total number of allocated spaces used.
   */
  #ifndef _di_uint128s_t_
    typedef struct {
      uint64_t *array;

      f_array_length_t size;
      f_array_length_t used;
    } f_uint128s_t;

    #define f_uint128s_t_initialize { 0, 0, 0 }

    #define f_macro_uint128s_t_clear(uint128s) f_macro_memory_structure_clear(uint128s);

    #define f_macro_uint128s_t_new(status, uint128s, length) f_macro_memory_structure_new(status, uint128s, uint64_t, length);

    #define f_macro_uint128s_t_adjust(status, uint128s, length) f_macro_memory_structure_adjust(status, uint128s, uint64_t, length);
    #define f_macro_uint128s_t_resize(status, uint128s, length) f_macro_memory_structure_resize(status, uint128s, uint64_t, length);

    #define f_macro_uint128s_t_increase(status, uint128s)            f_macro_memory_structure_increase(status, uint128s, uint64_t);
    #define f_macro_uint128s_t_increase_by(status, uint128s, amount) f_macro_memory_structure_increase_by(status, uint128s, uint64_t, amount);
    #define f_macro_uint128s_t_decrease_by(status, uint128s, amount) f_macro_memory_structure_decrease_by(status, uint128s, uint64_t, amount);
    #define f_macro_uint128s_t_decimate_by(status, uint128s, amount) f_macro_memory_structure_decimate_by(status, uint128s, uint64_t, amount);

    #define f_macro_uint128s_t_delete(status, uint128s)  f_macro_memory_structure_delete(status, uint128s, uint64_t);
    #define f_macro_uint128s_t_destroy(status, uint128s) f_macro_memory_structure_destroy(status, uint128s, uint64_t);

    #define f_macro_uint128s_t_delete_simple(uint128s)  f_macro_memory_structure_delete_simple(uint128s, uint64_t);
    #define f_macro_uint128s_t_destroy_simple(uint128s) f_macro_memory_structure_destroy_simple(uint128s, uint64_t);
  #endif // _di_uint128s_t_

  /**
   * An array of an array of array uint64_t acting in place of __uint128_t when 128 is not supported.
   *
   * array: the array of an array of array uint64_t acting in place of __uint128_t when 128 is not supported.
   * size: total amount of allocated space.
   * used: total number of allocated spaces used.
   */
  #ifndef _di_uint128ss_t_
    typedef struct {
      f_uint128s_t *array;

      f_array_length_t size;
      f_array_length_t used;
    } f_uint128ss_t;

    #define f_uint128ss_t_initialize { 0, 0, 0 }

    #define f_macro_uint128ss_t_clear(numbers) f_macro_memory_structures_clear(numbers);

    #define f_macro_uint128ss_t_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, uint64_t, length);

    #define f_macro_uint128ss_t_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, uint64_t, f_uint128s_t);
    #define f_macro_uint128ss_t_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, uint64_t, f_uint128s_t);

    #define f_macro_uint128ss_t_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, uint64_t, f_uint128s_t);
    #define f_macro_uint128ss_t_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, uint64_t, f_uint128s_t);

    #define f_macro_uint128ss_t_resize(status, numbers, length) f_macro_memory_structures_resize(status, numbers, uint64_t, f_uint128s_t, length, f_array_length_t);
    #define f_macro_uint128ss_t_adjust(status, numbers, length) f_macro_memory_structures_adjust(status, numbers, uint64_t, f_uint128s_t, length, f_array_length_t);
  #endif // _di_uint128ss_t_
#endif // __SIZEOF_INT128__

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_array_h
