/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides datatypes that require memory operations.
 *
 * Because memory requires status.h, this is moved to a separate file to reduce potential circular dependency issues.
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

/**
 * An array of an array of array lengths.
 *
 * array: the array of an array of array lengths.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_array_lengthss_
  typedef struct {
    f_array_lengths *array;

    f_array_length size;
    f_array_length used;
  } f_array_lengthss;

  #define f_array_lengthss_initialize { 0, 0, 0 }

  #define f_macro_array_lengthss_clear(lengths) f_macro_memory_structures_clear(lengths)

  #define f_macro_array_lengthss_new(status, lengths, length) f_macro_memory_structures_new(status, lengths, f_array_length, length)

  #define f_macro_array_lengthss_delete(status, lengths)  f_macro_memory_structures_delete(status, lengths, f_array_length, f_array_lengths)
  #define f_macro_array_lengthss_destroy(status, lengths) f_macro_memory_structures_destroy(status, lengths, f_array_length, f_array_lengths)

  #define f_macro_array_lengthss_delete_simple(lengths)  f_macro_memory_structures_delete_simple(lengths, f_array_length, f_array_lengths)
  #define f_macro_array_lengthss_destroy_simple(lengths) f_macro_memory_structures_destroy_simple(lengths, f_array_length, f_array_lengths)

  #define f_macro_array_lengthss_resize(status, lengths, new_length) f_macro_memory_structures_resize(status, lengths, f_array_length, f_array_lengths, new_length, f_array_length)
  #define f_macro_array_lengthss_adjust(status, lengths, new_length) f_macro_memory_structures_adjust(status, lengths, f_array_length, f_array_lengths, new_length, f_array_length)
#endif // _di_f_array_lengthss_

/**
 * An array of f_cell.
 *
 * array: the array of f_cell.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_f_cells_
  typedef struct {
    f_cell *array;

    f_array_length size;
    f_array_length used;
  } f_cells;

  #define f_cells_initialize {0, 0, 0}

  #define f_macro_cells_clear(ranges) f_macro_memory_structure_clear(ranges)

  #define f_macro_cells_new(status, ranges, length) f_macro_memory_structure_new(status, ranges, f_cell, length)

  #define f_macro_cells_delete(status, ranges)  f_macro_memory_structure_delete(status, ranges, f_cell)
  #define f_macro_cells_destroy(status, ranges) f_macro_memory_structure_destroy(status, ranges, f_cell)

  #define f_macro_cells_delete_simple(ranges)  f_macro_memory_structure_delete_simple(ranges, f_cell)
  #define f_macro_cells_destroy_simple(ranges) f_macro_memory_structure_destroy_simple(ranges, f_cell)

  #define f_macro_cells_resize(status, ranges, new_length) f_macro_memory_structure_resize(status, ranges, f_cell, new_length)
  #define f_macro_cells_adjust(status, ranges, new_length) f_macro_memory_structure_adjust(status, ranges, f_cell, new_length)
#endif // _di_f_cells_

/**
 * This holds an array of f_cells.
 *
 * array: The array of f_cell arrays.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_cellss_
  typedef struct {
    f_cells *array;

    f_array_length size;
    f_array_length used;
  } f_cellss;

  #define f_cellss_initialize { 0, 0, 0 }

  #define f_macro_cellss_clear(rangess) f_macro_memory_structures_clear(rangess)

  #define f_macro_cellss_new(status, rangess, length) f_macro_memory_structures_new(status, rangess, f_cells, length)

  #define f_macro_cellss_delete(status, rangess)  f_macro_memory_structures_delete(status, rangess, f_cell, f_cells)
  #define f_macro_cellss_destroy(status, rangess) f_macro_memory_structures_destroy(status, rangess, f_cell, f_cells)

  #define f_macro_cellss_delete_simple(rangess)  f_macro_memory_structures_delete_simple(rangess, f_cell, f_cells)
  #define f_macro_cellss_destroy_simple(rangess) f_macro_memory_structures_destroy_simple(rangess, f_cell, f_cells)

  #define f_macro_cellss_resize(status, rangess, new_length) f_macro_memory_structures_resize(status, rangess, f_cell, f_cells, new_length, f_array_length)
  #define f_macro_cellss_adjust(status, rangess, new_length) f_macro_memory_structures_adjust(status, rangess, f_cell, f_cells, new_length, f_array_length)
#endif // _di_f_cellss_

/**
 * An array of array int8_t.
 *
 * array: An array of int8_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_array_int8_t_
  typedef struct {
    int8_t *array;

    f_array_length size;
    f_array_length used;
  } f_int8_ts;

  #define f_int8_ts_initialize { 0, 0, 0 }

  #define f_macro_int8_ts_clear(numbers) f_macro_memory_structure_clear(numbers)

  #define f_macro_int8_ts_new(status, numbers, length) f_macro_memory_structure_new(status, numbers, int8_t, length)

  #define f_macro_int8_ts_delete(status, numbers)  f_macro_memory_structure_delete(status, numbers, int8_t)
  #define f_macro_int8_ts_destroy(status, numbers) f_macro_memory_structure_destroy(status, numbers, int8_t)

  #define f_macro_int8_ts_delete_simple(numbers)  f_macro_memory_structure_delete_simple(numbers, int8_t)
  #define f_macro_int8_ts_destroy_simple(numbers) f_macro_memory_structure_destroy_simple(numbers, int8_t)

  #define f_macro_int8_ts_resize(status, numbers, new_length) f_macro_memory_structure_resize(status, numbers, int8_t, new_length)
  #define f_macro_int8_ts_adjust(status, numbers, new_length) f_macro_memory_structure_adjust(status, numbers, int8_t, new_length)
#endif // _di_int8_ts_

/**
 * An array of an array of array int8_t.
 *
 * array: the array of an array of array int8_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_int8_tss_
  typedef struct {
    f_int8_ts *array;

    f_array_length size;
    f_array_length used;
  } f_int8_tss;

  #define f_int8_tss_initialize { 0, 0, 0 }

  #define f_macro_int8_tss_clear(numbers) f_macro_memory_structures_clear(numbers)

  #define f_macro_int8_tss_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, int8_t, length)

  #define f_macro_int8_tss_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, int8_t, f_int8_ts)
  #define f_macro_int8_tss_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, int8_t, f_int8_ts)

  #define f_macro_int8_tss_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, int8_t, f_int8_ts)
  #define f_macro_int8_tss_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, int8_t, f_int8_ts)

  #define f_macro_int8_tss_resize(status, numbers, new_length) f_macro_memory_structures_resize(status, numbers, int8_t, f_int8_ts, new_length, f_array_length)
  #define f_macro_int8_tss_adjust(status, numbers, new_length) f_macro_memory_structures_adjust(status, numbers, int8_t, f_int8_ts, new_length, f_array_length)
#endif // _di_int8_tss_

/**
 * An array of array uint8_t.
 *
 * array: An array of uint8_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_uint8_ts_
  typedef struct {
    uint8_t *array;

    f_array_length size;
    f_array_length used;
  } f_uint8_ts;

  #define f_uint8_ts_initialize { 0, 0, 0 }

  #define f_macro_uint8_ts_clear(numbers) f_macro_memory_structure_clear(numbers)

  #define f_macro_uint8_ts_new(status, numbers, length) f_macro_memory_structure_new(status, numbers, uint8_t, length)

  #define f_macro_uint8_ts_delete(status, numbers)  f_macro_memory_structure_delete(status, numbers, uint8_t)
  #define f_macro_uint8_ts_destroy(status, numbers) f_macro_memory_structure_destroy(status, numbers, uint8_t)

  #define f_macro_uint8_ts_delete_simple(numbers)  f_macro_memory_structure_delete_simple(numbers, uint8_t)
  #define f_macro_uint8_ts_destroy_simple(numbers) f_macro_memory_structure_destroy_simple(numbers, uint8_t)

  #define f_macro_uint8_ts_resize(status, numbers, new_length) f_macro_memory_structure_resize(status, numbers, uint8_t, new_length)
  #define f_macro_uint8_ts_adjust(status, numbers, new_length) f_macro_memory_structure_adjust(status, numbers, uint8_t, new_length)
#endif // _di_uint8_ts_

/**
 * An array of an array of array uint8_t.
 *
 * array: the array of an array of array uint8_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_uint8_tss_
  typedef struct {
    f_uint8_ts *array;

    f_array_length size;
    f_array_length used;
  } f_uint8_tss;

  #define f_uint8_tss_initialize { 0, 0, 0 }

  #define f_macro_uint8_tss_clear(numbers) f_macro_memory_structures_clear(numbers)

  #define f_macro_uint8_tss_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, uint8_t, length)

  #define f_macro_uint8_tss_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, uint8_t, f_uint8_ts)
  #define f_macro_uint8_tss_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, uint8_t, f_uint8_ts)

  #define f_macro_uint8_tss_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, uint8_t, f_uint8_ts)
  #define f_macro_uint8_tss_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, uint8_t, f_uint8_ts)

  #define f_macro_uint8_tss_resize(status, numbers, new_length) f_macro_memory_structures_resize(status, numbers, uint8_t, f_uint8_ts, new_length, f_array_length)
  #define f_macro_uint8_tss_adjust(status, numbers, new_length) f_macro_memory_structures_adjust(status, numbers, uint8_t, f_uint8_ts, new_length, f_array_length)
#endif // _di_uint8_tss_

/**
 * An array of array int16_t.
 *
 * array: An array of int16_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_int16_ts_
  typedef struct {
    int16_t *array;

    f_array_length size;
    f_array_length used;
  } f_int16_ts;

  #define f_int16_ts_initialize { 0, 0, 0 }

  #define f_macro_int16_ts_clear(numbers) f_macro_memory_structure_clear(numbers)

  #define f_macro_int16_ts_new(status, numbers, length) f_macro_memory_structure_new(status, numbers, int16_t, length)

  #define f_macro_int16_ts_delete(status, numbers)  f_macro_memory_structure_delete(status, numbers, int16_t)
  #define f_macro_int16_ts_destroy(status, numbers) f_macro_memory_structure_destroy(status, numbers, int16_t)

  #define f_macro_int16_ts_delete_simple(numbers)  f_macro_memory_structure_delete_simple(numbers, int16_t)
  #define f_macro_int16_ts_destroy_simple(numbers) f_macro_memory_structure_destroy_simple(numbers, int16_t)

  #define f_macro_int16_ts_resize(status, numbers, new_length) f_macro_memory_structure_resize(status, numbers, int16_t, new_length)
  #define f_macro_int16_ts_adjust(status, numbers, new_length) f_macro_memory_structure_adjust(status, numbers, int16_t, new_length)
#endif // _di_int16_ts_

/**
 * An array of an array of array int16_t.
 *
 * array: the array of an array of array int16_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_int16_tss_
  typedef struct {
    f_int16_ts *array;

    f_array_length size;
    f_array_length used;
  } f_int16_tss;

  #define f_int16_tss_initialize { 0, 0, 0 }

  #define f_macro_int16_tss_clear(numbers) f_macro_memory_structures_clear(numbers)

  #define f_macro_int16_tss_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, int16_t, length)

  #define f_macro_int16_tss_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, int16_t, f_int16_ts)
  #define f_macro_int16_tss_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, int16_t, f_int16_ts)

  #define f_macro_int16_tss_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, int16_t, f_int16_ts)
  #define f_macro_int16_tss_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, int16_t, f_int16_ts)

  #define f_macro_int16_tss_resize(status, numbers, new_length) f_macro_memory_structures_resize(status, numbers, int16_t, f_int16_ts, new_length, f_array_length)
  #define f_macro_int16_tss_adjust(status, numbers, new_length) f_macro_memory_structures_adjust(status, numbers, int16_t, f_int16_ts, new_length, f_array_length)
#endif // _di_int16_tss_

/**
 * An array of array uint16_t.
 *
 * array: An array of uint16_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_uint16_ts_
  typedef struct {
    uint16_t *array;

    f_array_length size;
    f_array_length used;
  } f_uint16_ts;

  #define f_uint16_ts_initialize { 0, 0, 0 }

  #define f_macro_uint16_ts_clear(numbers) f_macro_memory_structure_clear(numbers)

  #define f_macro_uint16_ts_new(status, numbers, length) f_macro_memory_structure_new(status, numbers, uint16_t, length)

  #define f_macro_uint16_ts_delete(status, numbers)  f_macro_memory_structure_delete(status, numbers, uint16_t)
  #define f_macro_uint16_ts_destroy(status, numbers) f_macro_memory_structure_destroy(status, numbers, uint16_t)

  #define f_macro_uint16_ts_delete_simple(numbers)  f_macro_memory_structure_delete_simple(numbers, uint16_t)
  #define f_macro_uint16_ts_destroy_simple(numbers) f_macro_memory_structure_destroy_simple(numbers, uint16_t)

  #define f_macro_uint16_ts_resize(status, numbers, new_length) f_macro_memory_structure_resize(status, numbers, uint16_t, new_length)
  #define f_macro_uint16_ts_adjust(status, numbers, new_length) f_macro_memory_structure_adjust(status, numbers, uint16_t, new_length)
#endif // _di_uint16_ts_

/**
 * An array of an array of array uint16_t.
 *
 * array: the array of an array of array uint16_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_uint16_tss_
  typedef struct {
    f_uint16_ts *array;

    f_array_length size;
    f_array_length used;
  } f_uint16_tss;

  #define f_uint16_tss_initialize { 0, 0, 0 }

  #define f_macro_uint16_tss_clear(numbers) f_macro_memory_structures_clear(numbers)

  #define f_macro_uint16_tss_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, uint16_t, length)

  #define f_macro_uint16_tss_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, uint16_t, f_uint16_ts)
  #define f_macro_uint16_tss_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, uint16_t, f_uint16_ts)

  #define f_macro_uint16_tss_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, uint16_t, f_uint16_ts)
  #define f_macro_uint16_tss_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, uint16_t, f_uint16_ts)

  #define f_macro_uint16_tss_resize(status, numbers, new_length) f_macro_memory_structures_resize(status, numbers, uint16_t, f_uint16_ts, new_length, f_array_length)
  #define f_macro_uint16_tss_adjust(status, numbers, new_length) f_macro_memory_structures_adjust(status, numbers, uint16_t, f_uint16_ts, new_length, f_array_length)
#endif // _di_uint16_tss_

/**
 * An array of array int32_t.
 *
 * array: An array of int32_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_int32_ts_
  typedef struct {
    int32_t *array;

    f_array_length size;
    f_array_length used;
  } f_int32_ts;

  #define f_int32_ts_initialize { 0, 0, 0 }

  #define f_macro_int32_ts_clear(numbers) f_macro_memory_structure_clear(numbers)

  #define f_macro_int32_ts_new(status, numbers, length) f_macro_memory_structure_new(status, numbers, int32_t, length)

  #define f_macro_int32_ts_delete(status, numbers)  f_macro_memory_structure_delete(status, numbers, int32_t)
  #define f_macro_int32_ts_destroy(status, numbers) f_macro_memory_structure_destroy(status, numbers, int32_t)

  #define f_macro_int32_ts_delete_simple(numbers)  f_macro_memory_structure_delete_simple(numbers, int32_t)
  #define f_macro_int32_ts_destroy_simple(numbers) f_macro_memory_structure_destroy_simple(numbers, int32_t)

  #define f_macro_int32_ts_resize(status, numbers, new_length) f_macro_memory_structure_resize(status, numbers, int32_t, new_length)
  #define f_macro_int32_ts_adjust(status, numbers, new_length) f_macro_memory_structure_adjust(status, numbers, int32_t, new_length)
#endif // _di_int32_ts_

/**
 * An array of an array of array int32_t.
 *
 * array: the array of an array of array int32_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_int32_tss_
  typedef struct {
    f_int32_ts *array;

    f_array_length size;
    f_array_length used;
  } f_int32_tss;

  #define f_int32_tss_initialize { 0, 0, 0 }

  #define f_macro_int32_tss_clear(numbers) f_macro_memory_structures_clear(numbers)

  #define f_macro_int32_tss_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, int32_t, length)

  #define f_macro_int32_tss_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, int32_t, f_int32_ts)
  #define f_macro_int32_tss_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, int32_t, f_int32_ts)

  #define f_macro_int32_tss_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, int32_t, f_int32_ts)
  #define f_macro_int32_tss_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, int32_t, f_int32_ts)

  #define f_macro_int32_tss_resize(status, numbers, new_length) f_macro_memory_structures_resize(status, numbers, int32_t, f_int32_ts, new_length, f_array_length)
  #define f_macro_int32_tss_adjust(status, numbers, new_length) f_macro_memory_structures_adjust(status, numbers, int32_t, f_int32_ts, new_length, f_array_length)
#endif // _di_int32_tss_

/**
 * An array of array uint32_t.
 *
 * array: An array of uint32_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_uint32_ts_
  typedef struct {
    uint32_t *array;

    f_array_length size;
    f_array_length used;
  } f_uint32_ts;

  #define f_uint32_ts_initialize { 0, 0, 0 }

  #define f_macro_uint32_ts_clear(numbers) f_macro_memory_structure_clear(numbers)

  #define f_macro_uint32_ts_new(status, numbers, length) f_macro_memory_structure_new(status, numbers, uint32_t, length)

  #define f_macro_uint32_ts_delete(status, numbers)  f_macro_memory_structure_delete(status, numbers, uint32_t)
  #define f_macro_uint32_ts_destroy(status, numbers) f_macro_memory_structure_destroy(status, numbers, uint32_t)

  #define f_macro_uint32_ts_delete_simple(numbers)  f_macro_memory_structure_delete_simple(numbers, uint32_t)
  #define f_macro_uint32_ts_destroy_simple(numbers) f_macro_memory_structure_destroy_simple(numbers, uint32_t)

  #define f_macro_uint32_ts_resize(status, numbers, new_length) f_macro_memory_structure_resize(status, numbers, uint32_t, new_length)
  #define f_macro_uint32_ts_adjust(status, numbers, new_length) f_macro_memory_structure_adjust(status, numbers, uint32_t, new_length)
#endif // _di_uint32_ts_

/**
 * An array of an array of array uint32_t.
 *
 * array: the array of an array of array uint32_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_uint32_tss_
  typedef struct {
    f_uint32_ts *array;

    f_array_length size;
    f_array_length used;
  } f_uint32_tss;

  #define f_uint32_tss_initialize { 0, 0, 0 }

  #define f_macro_uint32_tss_clear(numbers) f_macro_memory_structures_clear(numbers)

  #define f_macro_uint32_tss_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, uint32_t, length)

  #define f_macro_uint32_tss_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, uint32_t, f_uint32_ts)
  #define f_macro_uint32_tss_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, uint32_t, f_uint32_ts)

  #define f_macro_uint32_tss_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, uint32_t, f_uint32_ts)
  #define f_macro_uint32_tss_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, uint32_t, f_uint32_ts)

  #define f_macro_uint32_tss_resize(status, numbers, new_length) f_macro_memory_structures_resize(status, numbers, uint32_t, f_uint32_ts, new_length, f_array_length)
  #define f_macro_uint32_tss_adjust(status, numbers, new_length) f_macro_memory_structures_adjust(status, numbers, uint32_t, f_uint32_ts, new_length, f_array_length)
#endif // _di_uint32_tss_

/**
 * An array of array int64_t.
 *
 * array: An array of int64_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_int64_ts_
  typedef struct {
    int64_t *array;

    f_array_length size;
    f_array_length used;
  } f_int64_ts;

  #define f_int64_ts_initialize { 0, 0, 0 }

  #define f_macro_int64_ts_clear(numbers) f_macro_memory_structure_clear(numbers)

  #define f_macro_int64_ts_new(status, numbers, length) f_macro_memory_structure_new(status, numbers, int64_t, length)

  #define f_macro_int64_ts_delete(status, numbers)  f_macro_memory_structure_delete(status, numbers, int64_t)
  #define f_macro_int64_ts_destroy(status, numbers) f_macro_memory_structure_destroy(status, numbers, int64_t)

  #define f_macro_int64_ts_delete_simple(numbers)  f_macro_memory_structure_delete_simple(numbers, int64_t)
  #define f_macro_int64_ts_destroy_simple(numbers) f_macro_memory_structure_destroy_simple(numbers, int64_t)

  #define f_macro_int64_ts_resize(status, numbers, new_length) f_macro_memory_structure_resize(status, numbers, int64_t, new_length)
  #define f_macro_int64_ts_adjust(status, numbers, new_length) f_macro_memory_structure_adjust(status, numbers, int64_t, new_length)
#endif // _di_int64_ts_

/**
 * An array of an array of array int64_t.
 *
 * array: the array of an array of array int64_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_int64_tss_
  typedef struct {
    f_int64_ts *array;

    f_array_length size;
    f_array_length used;
  } f_int64_tss;

  #define f_int64_tss_initialize { 0, 0, 0 }

  #define f_macro_int64_tss_clear(numbers) f_macro_memory_structures_clear(numbers)

  #define f_macro_int64_tss_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, int64_t, length)

  #define f_macro_int64_tss_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, int64_t, f_int64_ts)
  #define f_macro_int64_tss_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, int64_t, f_int64_ts)

  #define f_macro_int64_tss_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, int64_t, f_int64_ts)
  #define f_macro_int64_tss_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, int64_t, f_int64_ts)

  #define f_macro_int64_tss_resize(status, numbers, new_length) f_macro_memory_structures_resize(status, numbers, int64_t, f_int64_ts, new_length, f_array_length)
  #define f_macro_int64_tss_adjust(status, numbers, new_length) f_macro_memory_structures_adjust(status, numbers, int64_t, f_int64_ts, new_length, f_array_length)
#endif // _di_int64_tss_

/**
 * An array of array uint64_t.
 *
 * array: An array of uint64_t.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_uint64_ts_
  typedef struct {
    uint64_t *array;

    f_array_length size;
    f_array_length used;
  } f_uint64_ts;

  #define f_uint64_ts_initialize { 0, 0, 0 }

  #define f_macro_uint64_ts_clear(numbers) f_macro_memory_structure_clear(numbers)

  #define f_macro_uint64_ts_new(status, numbers, length) f_macro_memory_structure_new(status, numbers, uint64_t, length)

  #define f_macro_uint64_ts_delete(status, numbers)  f_macro_memory_structure_delete(status, numbers, uint64_t)
  #define f_macro_uint64_ts_destroy(status, numbers) f_macro_memory_structure_destroy(status, numbers, uint64_t)

  #define f_macro_uint64_ts_delete_simple(numbers)  f_macro_memory_structure_delete_simple(numbers, uint64_t)
  #define f_macro_uint64_ts_destroy_simple(numbers) f_macro_memory_structure_destroy_simple(numbers, uint64_t)

  #define f_macro_uint64_ts_resize(status, numbers, new_length) f_macro_memory_structure_resize(status, numbers, uint64_t, new_length)
  #define f_macro_uint64_ts_adjust(status, numbers, new_length) f_macro_memory_structure_adjust(status, numbers, uint64_t, new_length)
#endif // _di_uint64_ts_

/**
 * An array of an array of array uint64_t.
 *
 * array: the array of an array of array uint64_t.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_uint64_tss_
  typedef struct {
    f_uint64_ts *array;

    f_array_length size;
    f_array_length used;
  } f_uint64_tss;

  #define f_uint64_tss_initialize { 0, 0, 0 }

  #define f_macro_uint64_tss_clear(numbers) f_macro_memory_structures_clear(numbers)

  #define f_macro_uint64_tss_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, uint64_t, length)

  #define f_macro_uint64_tss_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, uint64_t, f_uint64_ts)
  #define f_macro_uint64_tss_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, uint64_t, f_uint64_ts)

  #define f_macro_uint64_tss_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, uint64_t, f_uint64_ts)
  #define f_macro_uint64_tss_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, uint64_t, f_uint64_ts)

  #define f_macro_uint64_tss_resize(status, numbers, new_length) f_macro_memory_structures_resize(status, numbers, uint64_t, f_uint64_ts, new_length, f_array_length)
  #define f_macro_uint64_tss_adjust(status, numbers, new_length) f_macro_memory_structures_adjust(status, numbers, uint64_t, f_uint64_ts, new_length, f_array_length)
#endif // _di_uint64_tss_

#ifndef __SIZEOF_INT128__
  /**
   * An array of array __int128_t.
   *
   * array: An array of __int128_t.
   * size:  Total amount of allocated space.
   * used:  Total number of allocated spaces used.
   */
  #ifndef _di_int128_ts_
    typedef struct {
      __int128_t *array;

      f_array_length size;
      f_array_length used;
    } f_int128_ts;

    #define f_int128_ts_initialize { 0, 0, 0 }

    #define f_macro_int128_ts_clear(numbers) f_macro_memory_structure_clear(numbers)

    #define f_macro_int128_ts_new(status, numbers, length) f_macro_memory_structure_new(status, numbers, __int128_t, length)

    #define f_macro_int128_ts_delete(status, numbers)  f_macro_memory_structure_delete(status, numbers, __int128_t)
    #define f_macro_int128_ts_destroy(status, numbers) f_macro_memory_structure_destroy(status, numbers, __int128_t)

    #define f_macro_int128_ts_delete_simple(numbers)  f_macro_memory_structure_delete_simple(numbers, __int128_t)
    #define f_macro_int128_ts_destroy_simple(numbers) f_macro_memory_structure_destroy_simple(numbers, __int128_t)

    #define f_macro_int128_ts_resize(status, numbers, new_length) f_macro_memory_structure_resize(status, numbers, __int128_t, new_length)
    #define f_macro_int128_ts_adjust(status, numbers, new_length) f_macro_memory_structure_adjust(status, numbers, __int128_t, new_length)
  #endif // _di_int128_ts_

  /**
   * An array of an array of array __int128_t.
   *
   * array: the array of an array of array __int128_t.
   * size: total amount of allocated space.
   * used: total number of allocated spaces used.
   */
  #ifndef _di_int128_tss_
    typedef struct {
      f_int128_ts *array;

      f_array_length size;
      f_array_length used;
    } f_int128_tss;

    #define f_int128_tss_initialize { 0, 0, 0 }

    #define f_macro_int128_tss_clear(numbers) f_macro_memory_structures_clear(numbers)

    #define f_macro_int128_tss_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, __int128_t, length)

    #define f_macro_int128_tss_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, __int128_t, f_int128_ts)
    #define f_macro_int128_tss_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, __int128_t, f_int128_ts)

    #define f_macro_int128_tss_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, __int128_t, f_int128_ts)
    #define f_macro_int128_tss_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, __int128_t, f_int128_ts)

    #define f_macro_int128_tss_resize(status, numbers, new_length) f_macro_memory_structures_resize(status, numbers, __int128_t, f_int128_ts, new_length, f_array_length)
    #define f_macro_int128_tss_adjust(status, numbers, new_length) f_macro_memory_structures_adjust(status, numbers, __int128_t, f_int128_ts, new_length, f_array_length)
  #endif // _di_int128_tss_

  /**
   * An array of array __uint128_t.
   *
   * array: An array of __uint128_t.
   * size:  Total amount of allocated space.
   * used:  Total number of allocated spaces used.
   */
  #ifndef _di_uint128_ts_
    typedef struct {
      __uint128_t *array;

      f_array_length size;
      f_array_length used;
    } f_uint128_ts;

    #define f_uint128_ts_initialize { 0, 0, 0 }

    #define f_macro_uint128_ts_clear(numbers) f_macro_memory_structure_clear(numbers)

    #define f_macro_uint128_ts_new(status, numbers, length) f_macro_memory_structure_new(status, numbers, __uint128_t, length)

    #define f_macro_uint128_ts_delete(status, numbers)  f_macro_memory_structure_delete(status, numbers, __uint128_t)
    #define f_macro_uint128_ts_destroy(status, numbers) f_macro_memory_structure_destroy(status, numbers, __uint128_t)

    #define f_macro_uint128_ts_delete_simple(numbers)  f_macro_memory_structure_delete_simple(numbers, __uint128_t)
    #define f_macro_uint128_ts_destroy_simple(numbers) f_macro_memory_structure_destroy_simple(numbers, __uint128_t)

    #define f_macro_uint128_ts_resize(status, numbers, new_length) f_macro_memory_structure_resize(status, numbers, __uint128_t, new_length)
    #define f_macro_uint128_ts_adjust(status, numbers, new_length) f_macro_memory_structure_adjust(status, numbers, __uint128_t, new_length)
  #endif // _di_uint128_ts_

  /**
   * An array of an array of array __uint128_t.
   *
   * array: the array of an array of array __uint128_t.
   * size: total amount of allocated space.
   * used: total number of allocated spaces used.
   */
  #ifndef _di_uint128_tss_
    typedef struct {
      f_uint128_ts *array;

      f_array_length size;
      f_array_length used;
    } f_uint128_tss;

    #define f_uint128_tss_initialize { 0, 0, 0 }

    #define f_macro_uint128_tss_clear(numbers) f_macro_memory_structures_clear(numbers)

    #define f_macro_uint128_tss_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, __uint128_t, length)

    #define f_macro_uint128_tss_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, __uint128_t, f_uint128_ts)
    #define f_macro_uint128_tss_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, __uint128_t, f_uint128_ts)

    #define f_macro_uint128_tss_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, __uint128_t, f_uint128_ts)
    #define f_macro_uint128_tss_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, __uint128_t, f_uint128_ts)

    #define f_macro_uint128_tss_resize(status, numbers, new_length) f_macro_memory_structures_resize(status, numbers, __uint128_t, f_uint128_ts, new_length, f_array_length)
    #define f_macro_uint128_tss_adjust(status, numbers, new_length) f_macro_memory_structures_adjust(status, numbers, __uint128_t, f_uint128_ts, new_length, f_array_length)
  #endif // _di_uint128_tss_
#else
  /**
   * An array of array int64_t acting in place of __int128_t when 128 is not supported.
   *
   * array: An array of int64_t acting in place of __int128_t when 128 is not supported.
   * size:  Total amount of allocated space.
   * used:  Total number of allocated spaces used.
   */
  #ifndef _di_int128_ts_
    typedef struct {
      int64_t *array;

      f_array_length size;
      f_array_length used;
    } f_int128_ts;

    #define f_int128_ts_initialize { 0, 0, 0 }

    #define f_macro_int128_ts_clear(numbers) f_macro_memory_structure_clear(numbers)

    #define f_macro_int128_ts_new(status, numbers, length) f_macro_memory_structure_new(status, numbers, int64_t, length)

    #define f_macro_int128_ts_delete(status, numbers)  f_macro_memory_structure_delete(status, numbers, int64_t)
    #define f_macro_int128_ts_destroy(status, numbers) f_macro_memory_structure_destroy(status, numbers, int64_t)

    #define f_macro_int128_ts_delete_simple(numbers)  f_macro_memory_structure_delete_simple(numbers, int64_t)
    #define f_macro_int128_ts_destroy_simple(numbers) f_macro_memory_structure_destroy_simple(numbers, int64_t)

    #define f_macro_int128_ts_resize(status, numbers, new_length) f_macro_memory_structure_resize(status, numbers, int64_t, new_length)
    #define f_macro_int128_ts_adjust(status, numbers, new_length) f_macro_memory_structure_adjust(status, numbers, int64_t, new_length)
  #endif // _di_int128_ts_

  /**
   * An array of an array of array int64_t acting in place of __int128_t when 128 is not supported.
   *
   * array: the array of an array of array int64_t acting in place of __int128_t when 128 is not supported.
   * size: total amount of allocated space.
   * used: total number of allocated spaces used.
   */
  #ifndef _di_int128_tss_
    typedef struct {
      f_int128_ts *array;

      f_array_length size;
      f_array_length used;
    } f_int128_tss;

    #define f_int128_tss_initialize { 0, 0, 0 }

    #define f_macro_int128_tss_clear(numbers) f_macro_memory_structures_clear(numbers)

    #define f_macro_int128_tss_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, int64_t, length)

    #define f_macro_int128_tss_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, int64_t, f_int128_ts)
    #define f_macro_int128_tss_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, int64_t, f_int128_ts)

    #define f_macro_int128_tss_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, int64_t, f_int128_ts)
    #define f_macro_int128_tss_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, int64_t, f_int128_ts)

    #define f_macro_int128_tss_resize(status, numbers, new_length) f_macro_memory_structures_resize(status, numbers, int64_t, f_int128_ts, new_length, f_array_length)
    #define f_macro_int128_tss_adjust(status, numbers, new_length) f_macro_memory_structures_adjust(status, numbers, int64_t, f_int128_ts, new_length, f_array_length)
  #endif // _di_int128_tss_

  /**
   * An array of array uint64_t acting in place of __uint128_t when 128 is not supported.
   *
   * array: An array of uint64_t acting in place of __uint128_t when 128 is not supported.
   * size:  Total amount of allocated space.
   * used:  Total number of allocated spaces used.
   */
  #ifndef _di_uint128_ts_
    typedef struct {
      uint64_t *array;

      f_array_length size;
      f_array_length used;
    } f_uint128_ts;

    #define f_uint128_ts_initialize { 0, 0, 0 }

    #define f_macro_uint128_ts_clear(numbers) f_macro_memory_structure_clear(numbers)

    #define f_macro_uint128_ts_new(status, numbers, length) f_macro_memory_structure_new(status, numbers, uint64_t, length)

    #define f_macro_uint128_ts_delete(status, numbers)  f_macro_memory_structure_delete(status, numbers, uint64_t)
    #define f_macro_uint128_ts_destroy(status, numbers) f_macro_memory_structure_destroy(status, numbers, uint64_t)

    #define f_macro_uint128_ts_delete_simple(numbers)  f_macro_memory_structure_delete_simple(numbers, uint64_t)
    #define f_macro_uint128_ts_destroy_simple(numbers) f_macro_memory_structure_destroy_simple(numbers, uint64_t)

    #define f_macro_uint128_ts_resize(status, numbers, new_length) f_macro_memory_structure_resize(status, numbers, uint64_t, new_length)
    #define f_macro_uint128_ts_adjust(status, numbers, new_length) f_macro_memory_structure_adjust(status, numbers, uint64_t, new_length)
  #endif // _di_uint128_ts_

  /**
   * An array of an array of array uint64_t acting in place of __uint128_t when 128 is not supported.
   *
   * array: the array of an array of array uint64_t acting in place of __uint128_t when 128 is not supported.
   * size: total amount of allocated space.
   * used: total number of allocated spaces used.
   */
  #ifndef _di_uint128_tss_
    typedef struct {
      f_uint128_ts *array;

      f_array_length size;
      f_array_length used;
    } f_uint128_tss;

    #define f_uint128_tss_initialize { 0, 0, 0 }

    #define f_macro_uint128_tss_clear(numbers) f_macro_memory_structures_clear(numbers)

    #define f_macro_uint128_tss_new(status, numbers, length) f_macro_memory_structures_new(status, numbers, uint64_t, length)

    #define f_macro_uint128_tss_delete(status, numbers)  f_macro_memory_structures_delete(status, numbers, uint64_t, f_uint128_ts)
    #define f_macro_uint128_tss_destroy(status, numbers) f_macro_memory_structures_destroy(status, numbers, uint64_t, f_uint128_ts)

    #define f_macro_uint128_tss_delete_simple(numbers)  f_macro_memory_structures_delete_simple(numbers, uint64_t, f_uint128_ts)
    #define f_macro_uint128_tss_destroy_simple(numbers) f_macro_memory_structures_destroy_simple(numbers, uint64_t, f_uint128_ts)

    #define f_macro_uint128_tss_resize(status, numbers, new_length) f_macro_memory_structures_resize(status, numbers, uint64_t, f_uint128_ts, new_length, f_array_length)
    #define f_macro_uint128_tss_adjust(status, numbers, new_length) f_macro_memory_structures_adjust(status, numbers, uint64_t, f_uint128_ts, new_length, f_array_length)
  #endif // _di_uint128_tss_
#endif // __SIZEOF_INT128__

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_array_h
