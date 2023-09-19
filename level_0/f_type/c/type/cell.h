/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines cell type data.
 *
 * This is auto-included by type.h and should not need to be explicitly included.
 */
#ifndef _F_type_cell_h
#define _F_type_cell_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure designating a row and column, just like a cell in a table.
 *
 * Properties:
 *   - row:    The row position.
 *   - column: The column position.
 */
#ifndef _di_f_cell_t_
  typedef struct {
    f_number_unsigned_t row;
    f_number_unsigned_t column;
  } f_cell_t;

  #define f_cell_t_initialize { 0, 0 }

  #define macro_f_cell_t_initialize_1(row, column) { row, column }

  #define macro_f_cell_t_clear(cell) \
    cell.row = 0; \
    cell.column = 0;
#endif // _di_f_cell_t_

/**
 * An array of f_cell_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: The array of f_cell_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_cells_t_
  typedef struct {
    f_cell_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_cells_t;

  #define f_cells_t_initialize { 0, 0, 0 }

  #define macro_f_cells_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_cells_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_cells_t_

/**
 * This holds an array of f_cells_t.
 *
 * The macros are defined in type_array.h or type_array-common.h.
 *
 * Properties:
 *   - array: The array of f_cell_t arrays.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_cellss_t_
  typedef struct {
    f_cells_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_cellss_t;

  #define f_cellss_t_initialize { 0, 0, 0 }

  #define macro_f_cellss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_cellss_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_cellss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_cell_h
