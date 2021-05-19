/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines common data to be used for/by type (array) related functionality.
 *
 * This is auto-included by type_array.h and should not need to be explicitly included.
 */
#ifndef _F_type_array_common_h
#define _F_type_array_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Macros for f_statuss_t, see type.h for typedefs.
 */
#ifndef _di_f_statuss_t_
  #define macro_f_statuss_t_clear(statuss) macro_f_memory_structure_clear(statuss)

  #define macro_f_statuss_t_resize(status, statuss, length) macro_f_memory_structure_resize(status, statuss, f_status_t, length)
  #define macro_f_statuss_t_adjust(status, statuss, length) macro_f_memory_structure_adjust(status, statuss, f_status_t, length)

  #define macro_f_statuss_t_delete_simple(statuss)  macro_f_memory_structure_delete_simple(statuss, f_status_t)
  #define macro_f_statuss_t_destroy_simple(statuss) macro_f_memory_structure_destroy_simple(statuss, f_status_t)

  #define macro_f_statuss_t_increase(status, step, statuss)      macro_f_memory_structure_increase(status, step, statuss, f_status_t)
  #define macro_f_statuss_t_increase_by(status, statuss, amount) macro_f_memory_structure_increase_by(status, statuss, f_status_t, amount)
  #define macro_f_statuss_t_decrease_by(status, statuss, amount) macro_f_memory_structure_decrease_by(status, statuss, f_status_t, amount)
  #define macro_f_statuss_t_decimate_by(status, statuss, amount) macro_f_memory_structure_decimate_by(status, statuss, f_status_t, amount)
#endif // _di_f_statuss_t_

/**
 * Macros for f_statusss_t, see type.h for typedefs.
 */
#ifndef _di_f_statusss_t_
  #define macro_f_statusss_t_clear(rangess) macro_f_memory_structures_clear(rangess)

  #define macro_f_statusss_t_resize(status, statusss, length) status = f_type_statusss_resize(length, &statusss);
  #define macro_f_statusss_t_adjust(status, statusss, length) status = f_type_statusss_adjust(length, &statusss);

  #define macro_f_statusss_t_delete_simple(statusss)  f_type_statusss_resize(0, &statusss);
  #define macro_f_statusss_t_destroy_simple(statusss) f_type_statusss_adjust(0, &statusss);

  #define macro_f_statusss_t_increase(status, step, statusss)      status = f_type_statusss_increase(step, &statusss);
  #define macro_f_statusss_t_increase_by(status, statusss, amount) status = f_type_statusss_increase_by(amount, &statusss);
  #define macro_f_statusss_t_decrease_by(status, statusss, amount) status = f_type_statusss_decrease_by(amount, &statusss);
  #define macro_f_statusss_t_decimate_by(status, statusss, amount) status = f_type_statusss_decimate_by(amount, &statusss);
#endif // _di_f_statusss_t_

/**
 * Macros for f_states_t, see type.h for typedefs.
 */
#ifndef _di_f_states_t_
  #define macro_f_states_t_clear(states) macro_f_memory_structure_clear(states)

  #define macro_f_states_t_resize(status, states, length) macro_f_memory_structure_resize(status, states, f_state_t, length)
  #define macro_f_states_t_adjust(status, states, length) macro_f_memory_structure_adjust(status, states, f_state_t, length)

  #define macro_f_states_t_delete_simple(states)  macro_f_memory_structure_delete_simple(states, f_state_t)
  #define macro_f_states_t_destroy_simple(states) macro_f_memory_structure_destroy_simple(states, f_state_t)

  #define macro_f_states_t_increase(status,step,  states)      macro_f_memory_structure_increase(status, step, states, f_state_t)
  #define macro_f_states_t_increase_by(status, states, amount) macro_f_memory_structure_increase_by(status, states, f_state_t, amount)
  #define macro_f_states_t_decrease_by(status, states, amount) macro_f_memory_structure_decrease_by(status, states, f_state_t, amount)
  #define macro_f_states_t_decimate_by(status, states, amount) macro_f_memory_structure_decimate_by(status, states, f_state_t, amount)
#endif // _di_f_states_t_

/**
 * Macros for f_statess_t, see type.h for typedefs.
 */
#ifndef _di_f_statess_t_
  #define macro_f_statess_t_clear(rangess) macro_f_memory_structures_clear(rangess)

  #define macro_f_statess_t_resize(status, statess, length) status = f_type_statess_resize(length, &statess);
  #define macro_f_statess_t_adjust(status, statess, length) status = f_type_statess_adjust(length, &statess);

  #define macro_f_statess_t_delete_simple(statess)  f_type_statess_resize(0, &statess);
  #define macro_f_statess_t_destroy_simple(statess) f_type_statess_adjust(0, &statess);

  #define macro_f_statess_t_increase(status, step, statess)      status = f_type_statess_increase(step, &statess);
  #define macro_f_statess_t_increase_by(status, statess, amount) status = f_type_statess_increase_by(amount, &statess);
  #define macro_f_statess_t_decrease_by(status, statess, amount) status = f_type_statess_decrease_by(amount, &statess);
  #define macro_f_statess_t_decimate_by(status, statess, amount) status = f_type_statess_decimate_by(amount, &statess);
#endif // _di_f_statess_t_

/**
 * Macros for f_array_lengths_t, see type.h for typedefs.
 */
#ifndef _di_f_array_lengths_t_
  #define macro_f_array_lengths_t_clear(lengths) macro_f_memory_structure_clear(lengths)

  #define macro_f_array_lengths_t_resize(status, lengths, length) macro_f_memory_structure_resize(status, lengths, f_array_length_t, length)
  #define macro_f_array_lengths_t_adjust(status, lengths, length) macro_f_memory_structure_adjust(status, lengths, f_array_length_t, length)

  #define macro_f_array_lengths_t_delete_simple(lengths)  macro_f_memory_structure_delete_simple(lengths, f_array_length_t)
  #define macro_f_array_lengths_t_destroy_simple(lengths) macro_f_memory_structure_destroy_simple(lengths, f_array_length_t)

  #define macro_f_array_lengths_t_increase(status, step, lengths)      macro_f_memory_structure_increase(status, step, lengths, f_array_length_t)
  #define macro_f_array_lengths_t_increase_by(status, lengths, amount) macro_f_memory_structure_increase_by(status, lengths, f_array_length_t, amount)
  #define macro_f_array_lengths_t_decrease_by(status, lengths, amount) macro_f_memory_structure_decrease_by(status, lengths, f_array_length_t, amount)
  #define macro_f_array_lengths_t_decimate_by(status, lengths, amount) macro_f_memory_structure_decimate_by(status, lengths, f_array_length_t, amount)
#endif // _di_f_array_lengths_t_

/**
 * Macros for f_array_lengths_t, see type.h for typedefs.
 */
#ifndef _di_f_array_lengthss_t_
  #define macro_f_array_lengthss_t_clear(lengths) macro_f_memory_structures_clear(lengths)

  #define macro_f_array_lengthss_t_resize(status, lengths, length) status = f_type_array_lengthss_resize(length, &lengths);
  #define macro_f_array_lengthss_t_adjust(status, lengths, length) status = f_type_array_lengthss_adjust(length, &lengths);

  #define macro_f_array_lengthss_t_delete_simple(lengths)  f_type_array_lengthss_resize(0, &lengths);
  #define macro_f_array_lengthss_t_destroy_simple(lengths) f_type_array_lengthss_adjust(0, &lengths);

  #define macro_f_array_lengthss_t_increase(status, step, lengths)      status = f_type_array_lengthss_increase(step, &lengths);
  #define macro_f_array_lengthss_t_increase_by(status, lengths, amount) status = f_type_array_lengthss_increase_by(amount, &lengths);
  #define macro_f_array_lengthss_t_decrease_by(status, lengths, amount) status = f_type_array_lengthss_decrease_by(amount, &lengths);
  #define macro_f_array_lengthss_t_decimate_by(status, lengths, amount) status = f_type_array_lengthss_decimate_by(amount, &lengths);
#endif // _di_f_array_lengthss_t_

/**
 * Macros for f_cells_t, see type.h for typedefs.
 */
#ifndef _di_f_cells_t_
  #define macro_f_cells_t_clear(cells) macro_f_memory_structure_clear(cells)

  #define macro_f_cells_t_resize(status, cells, length) macro_f_memory_structure_resize(status, cells, f_cell_t, length)
  #define macro_f_cells_t_adjust(status, cells, length) macro_f_memory_structure_adjust(status, cells, f_cell_t, length)

  #define macro_f_cells_t_delete_simple(cells)  macro_f_memory_structure_delete_simple(cells, f_cell_t)
  #define macro_f_cells_t_destroy_simple(cells) macro_f_memory_structure_destroy_simple(cells, f_cell_t)

  #define macro_f_cells_t_increase(status, step, cells)      macro_f_memory_structure_increase(status, step, cells, f_cell_t)
  #define macro_f_cells_t_increase_by(status, cells, amount) macro_f_memory_structure_increase_by(status, cells, f_cell_t, amount)
  #define macro_f_cells_t_decrease_by(status, cells, amount) macro_f_memory_structure_decrease_by(status, cells, f_cell_t, amount)
  #define macro_f_cells_t_decimate_by(status, cells, amount) macro_f_memory_structure_decimate_by(status, cells, f_cell_t, amount)
#endif // _di_f_cells_t_

/**
 * Macros for f_cellss_t, see type.h for typedefs.
 */
#ifndef _di_f_cellss_t_
  #define macro_f_cellss_t_clear(rangess) macro_f_memory_structures_clear(rangess)

  #define macro_f_cellss_t_resize(status, cellss, length) status = f_type_cellss_resize(length, &cellss);
  #define macro_f_cellss_t_adjust(status, cellss, length) status = f_type_cellss_adjust(length, &cellss);

  #define macro_f_cellss_t_delete_simple(cellss)  f_type_cellss_resize(0, &cellss);
  #define macro_f_cellss_t_destroy_simple(cellss) f_type_cellss_adjust(0, &cellss);

  #define macro_f_cellss_t_increase(status, step, cellss)      status = f_type_cellss_increase(step, &cellss);
  #define macro_f_cellss_t_increase_by(status, cellss, amount) status = f_type_cellss_increase_by(amount, &cellss);
  #define macro_f_cellss_t_decrease_by(status, cellss, amount) status = f_type_cellss_decrease_by(amount, &cellss);
  #define macro_f_cellss_t_decimate_by(status, cellss, amount) status = f_type_cellss_decimate_by(amount, &cellss);
#endif // _di_f_cellss_t_

/**
 * Macros for f_array_lengths_t, see type.h for typedefs.
 */
#ifndef _di_f_array_t_int8_t_
  #define macro_f_int8s_t_clear(int8s) macro_f_memory_structure_clear(int8s)

  #define macro_f_int8s_t_resize(status, int8s, length) macro_f_memory_structure_resize(status, int8s, int8_t, length)
  #define macro_f_int8s_t_adjust(status, int8s, length) macro_f_memory_structure_adjust(status, int8s, int8_t, length)

  #define macro_f_int8s_t_delete_simple(int8s)  macro_f_memory_structure_delete_simple(int8s, int8_t)
  #define macro_f_int8s_t_destroy_simple(int8s) macro_f_memory_structure_destroy_simple(int8s, int8_t)

  #define macro_f_int8s_t_increase(status, step, int8s)      macro_f_memory_structure_increase(status, step, int8s, int8_t)
  #define macro_f_int8s_t_increase_by(status, int8s, amount) macro_f_memory_structure_increase_by(status, int8s, int8_t, amount)
  #define macro_f_int8s_t_decrease_by(status, int8s, amount) macro_f_memory_structure_decrease_by(status, int8s, int8_t, amount)
  #define macro_f_int8s_t_decimate_by(status, int8s, amount) macro_f_memory_structure_decimate_by(status, int8s, int8_t, amount)
#endif // _di_int8s_t_

/**
 * Macros for f_array_lengths_t, see type.h for typedefs.
 */
#ifndef _di_int8ss_t_
  #define macro_f_int8ss_t_clear(numbers) macro_f_memory_structures_clear(numbers)

  #define macro_f_int8ss_t_resize(status, int8ss, length) status = f_type_int8ss_resize(length, &int8ss);
  #define macro_f_int8ss_t_adjust(status, int8ss, length) status = f_type_int8ss_adjust(length, &int8ss);

  #define macro_f_int8ss_t_increase(status, step, int8ss)      status = f_type_int8ss_increase(step, &int8ss);
  #define macro_f_int8ss_t_increase_by(status, int8ss, amount) status = f_type_int8ss_increase_by(amount, &int8ss);
  #define macro_f_int8ss_t_decrease_by(status, int8ss, amount) status = f_type_int8ss_decrease_by(amount, &int8ss);
  #define macro_f_int8ss_t_decimate_by(status, int8ss, amount) status = f_type_int8ss_decimate_by(amount, &int8ss);

  #define macro_f_int8ss_t_delete_simple(int8ss)  f_type_int8ss_resize(0, &int8ss);
  #define macro_f_int8ss_t_destroy_simple(int8ss) f_type_int8ss_adjust(0, &int8ss);
#endif // _di_int8ss_t_

/**
 * Macros for f_array_lengths_t, see type.h for typedefs.
 */
#ifndef _di_uint8s_t_
  #define macro_f_uint8s_t_clear(uint8s) macro_f_memory_structure_clear(uint8s)

  #define macro_f_uint8s_t_resize(status, uint8s, length) macro_f_memory_structure_resize(status, uint8s, uint8_t, length)
  #define macro_f_uint8s_t_adjust(status, uint8s, length) macro_f_memory_structure_adjust(status, uint8s, uint8_t, length)

  #define macro_f_uint8s_t_increase(status, step, uint8s)      macro_f_memory_structure_increase(status, step, uint8s, uint8_t)
  #define macro_f_uint8s_t_increase_by(status, uint8s, amount) macro_f_memory_structure_increase_by(status, uint8s, uint8_t, amount)
  #define macro_f_uint8s_t_decrease_by(status, uint8s, amount) macro_f_memory_structure_decrease_by(status, uint8s, uint8_t, amount)
  #define macro_f_uint8s_t_decimate_by(status, uint8s, amount) macro_f_memory_structure_decimate_by(status, uint8s, uint8_t, amount)

  #define macro_f_uint8s_t_delete_simple(uint8s)  macro_f_memory_structure_delete_simple(uint8s, uint8_t)
  #define macro_f_uint8s_t_destroy_simple(uint8s) macro_f_memory_structure_destroy_simple(uint8s, uint8_t)
#endif // _di_uint8s_t_

/**
 * Macros for f_array_lengths_t, see type.h for typedefs.
 */
#ifndef _di_uint8ss_t_
  #define macro_f_uint8ss_t_clear(numbers) macro_f_memory_structures_clear(numbers)

  #define macro_f_uint8ss_t_resize(status, uint8ss, length) status = f_type_uint8ss_resize(length, &uint8ss);
  #define macro_f_uint8ss_t_adjust(status, uint8ss, length) status = f_type_uint8ss_adjust(length, &uint8ss);

  #define macro_f_uint8ss_t_delete_simple(uint8ss)  f_type_uint8ss_resize(0, &uint8ss);
  #define macro_f_uint8ss_t_destroy_simple(uint8ss) f_type_uint8ss_adjust(0, &uint8ss);

  #define macro_f_uint8ss_t_increase(status, step, uint8ss)      status = f_type_uint8ss_increase(step, &uint8ss);
  #define macro_f_uint8ss_t_increase_by(status, uint8ss, amount) status = f_type_uint8ss_increase(amount, &uint8ss);
  #define macro_f_uint8ss_t_decrease_by(status, uint8ss, amount) status = f_type_uint8ss_decrease_by(amount, &uint8ss);
  #define macro_f_uint8ss_t_decimate_by(status, uint8ss, amount) status = f_type_uint8ss_decimate_by(amount, &uint8ss);
#endif // _di_uint8ss_t_

/**
 * Macros for f_array_lengths_t, see type.h for typedefs.
 */
#ifndef _di_int16s_t_
  #define macro_f_int16s_t_clear(int16s) macro_f_memory_structure_clear(int16s)

  #define macro_f_int16s_t_resize(status, int16s, length) macro_f_memory_structure_resize(status, int16s, int16_t, length)
  #define macro_f_int16s_t_adjust(status, int16s, length) macro_f_memory_structure_adjust(status, int16s, int16_t, length)

  #define macro_f_int16s_t_delete_simple(int16s)  macro_f_memory_structure_delete_simple(int16s, int16_t)
  #define macro_f_int16s_t_destroy_simple(int16s) macro_f_memory_structure_destroy_simple(int16s, int16_t)

  #define macro_f_int16s_t_increase(status, step, int16s)      macro_f_memory_structure_increase(status, step, int16s, int16_t)
  #define macro_f_int16s_t_increase_by(status, int16s, amount) macro_f_memory_structure_increase_by(status, int16s, int16_t, amount)
  #define macro_f_int16s_t_decrease_by(status, int16s, amount) macro_f_memory_structure_decrease_by(status, int16s, int16_t, amount)
  #define macro_f_int16s_t_decimate_by(status, int16s, amount) macro_f_memory_structure_decimate_by(status, int16s, int16_t, amount)
#endif // _di_int16s_t_

/**
 * Macros for f_array_lengths_t, see type.h for typedefs.
 */
#ifndef _di_int16ss_t_
  #define macro_f_int16ss_t_clear(numbers) macro_f_memory_structures_clear(numbers)

  #define macro_f_int16ss_t_resize(status, int16ss, length) status = f_type_int16ss_resize(length, &int16ss);
  #define macro_f_int16ss_t_adjust(status, int16ss, length) status = f_type_int16ss_adjust(length, &int16ss);

  #define macro_f_int16ss_t_increase(status, step, int16ss)      status = f_type_int16ss_increase(step, &int16ss);
  #define macro_f_int16ss_t_increase_by(status, int16ss, amount) status = f_type_int16ss_increase(amount, &int16ss);
  #define macro_f_int16ss_t_decrease_by(status, int16ss, amount) status = f_type_int16ss_decrease_by(amount, &int16ss);
  #define macro_f_int16ss_t_decimate_by(status, int16ss, amount) status = f_type_int16ss_decimate_by(amount, &int16ss);

  #define macro_f_int16ss_t_delete_simple(int16ss)  f_type_int16ss_resize(0, &int16ss);
  #define macro_f_int16ss_t_destroy_simple(int16ss) f_type_int16ss_adjust(0, &int16ss);
#endif // _di_int16ss_t_

/**
 * Macros for f_array_lengths_t, see type.h for typedefs.
 */
#ifndef _di_uint16s_t_
  #define macro_f_uint16s_t_clear(uint16s) macro_f_memory_structure_clear(uint16s)

  #define macro_f_uint16s_t_resize(status, uint16s, length) macro_f_memory_structure_resize(status, uint16s, uint16_t, length)
  #define macro_f_uint16s_t_adjust(status, uint16s, length) macro_f_memory_structure_adjust(status, uint16s, uint16_t, length)

  #define macro_f_uint16s_t_delete_simple(uint16s)  macro_f_memory_structure_delete_simple(uint16s, uint16_t)
  #define macro_f_uint16s_t_destroy_simple(uint16s) macro_f_memory_structure_destroy_simple(uint16s, uint16_t)

  #define macro_f_uint16s_t_increase(status, step, uint16s)      macro_f_memory_structure_increase(status, step, uint16s, uint16_t)
  #define macro_f_uint16s_t_increase_by(status, uint16s, amount) macro_f_memory_structure_increase_by(status, uint16s, uint16_t, amount)
  #define macro_f_uint16s_t_decrease_by(status, uint16s, amount) macro_f_memory_structure_decrease_by(status, uint16s, uint16_t, amount)
  #define macro_f_uint16s_t_decimate_by(status, uint16s, amount) macro_f_memory_structure_decimate_by(status, uint16s, uint16_t, amount)
#endif // _di_uint16s_t_

/**
 * Macros for f_array_lengths_t, see type.h for typedefs.
 */
#ifndef _di_uint16ss_t_
  #define macro_f_uint16ss_t_clear(numbers) macro_f_memory_structures_clear(numbers)

  #define macro_f_uint16ss_t_resize(status, uint16ss, length) status = f_type_uint16ss_resize(length, &uint16ss);
  #define macro_f_uint16ss_t_adjust(status, uint16ss, length) status = f_type_uint16ss_adjust(length, &uint16ss);

  #define macro_f_uint16ss_t_delete_simple(uint16ss)  f_type_uint16ss_resize(0, &uint16ss);
  #define macro_f_uint16ss_t_destroy_simple(uint16ss) f_type_uint16ss_adjust(0, &uint16ss);

  #define macro_f_uint16ss_t_increase(status, step, uint16ss)      status = f_type_uint16ss_increase(step, &uint16ss);
  #define macro_f_uint16ss_t_increase_by(status, uint16ss, amount) status = f_type_uint16ss_increase(amount, &uint16ss);
  #define macro_f_uint16ss_t_decrease_by(status, uint16ss, amount) status = f_type_uint16ss_decrease_by(amount, &uint16ss);
  #define macro_f_uint16ss_t_decimate_by(status, uint16ss, amount) status = f_type_uint16ss_decimate_by(amount, &uint16ss);
#endif // _di_uint16ss_t_

/**
 * Macros for f_array_lengths_t, see type.h for typedefs.
 */
#ifndef _di_int32s_t_
  #define macro_f_int32s_t_clear(int32s) macro_f_memory_structure_clear(int32s)

  #define macro_f_int32s_t_resize(status, int32s, length) macro_f_memory_structure_resize(status, int32s, int32_t, length)
  #define macro_f_int32s_t_adjust(status, int32s, length) macro_f_memory_structure_adjust(status, int32s, int32_t, length)

  #define macro_f_int32s_t_delete_simple(int32s)  macro_f_memory_structure_delete_simple(int32s, int32_t)
  #define macro_f_int32s_t_destroy_simple(int32s) macro_f_memory_structure_destroy_simple(int32s, int32_t)

  #define macro_f_int32s_t_increase(status, step, int32s)      macro_f_memory_structure_increase(status, step, int32s, int32_t)
  #define macro_f_int32s_t_increase_by(status, int32s, amount) macro_f_memory_structure_increase_by(status, int32s, int32_t, amount)
  #define macro_f_int32s_t_decrease_by(status, int32s, amount) macro_f_memory_structure_decrease_by(status, int32s, int32_t, amount)
  #define macro_f_int32s_t_decimate_by(status, int32s, amount) macro_f_memory_structure_decimate_by(status, int32s, int32_t, amount)
#endif // _di_int32s_t_

/**
 * Macros for f_array_lengths_t, see type.h for typedefs.
 */
#ifndef _di_int32ss_t_
  #define macro_f_int32ss_t_clear(numbers) macro_f_memory_structures_clear(numbers)

  #define macro_f_int32ss_t_resize(status, int32ss, length) status = f_type_int32ss_resize(length, &int32ss);
  #define macro_f_int32ss_t_adjust(status, int32ss, length) status = f_type_int32ss_adjust(length, &int32ss);

  #define macro_f_int32ss_t_delete_simple(int32ss)  f_type_int32ss_resize(0, &int32ss);
  #define macro_f_int32ss_t_destroy_simple(int32ss) f_type_int32ss_adjust(0, &int32ss);

  #define macro_f_int32ss_t_increase(status, step, int32ss)      status = f_type_int32ss_increase(step, &int32ss);
  #define macro_f_int32ss_t_increase_by(status, int32ss, amount) status = f_type_int32ss_increase(amount, &int32ss);
  #define macro_f_int32ss_t_decrease_by(status, int32ss, amount) status = f_type_int32ss_decrease_by(amount, &int32ss);
  #define macro_f_int32ss_t_decimate_by(status, int32ss, amount) status = f_type_int32ss_decimate_by(amount, &int32ss);
#endif // _di_int32ss_t_

/**
 * Macros for f_array_lengths_t, see type.h for typedefs.
 */
#ifndef _di_uint32s_t_
  #define macro_f_uint32s_t_clear(uint32s) macro_f_memory_structure_clear(uint32s)

  #define macro_f_uint32s_t_resize(status, uint32s, length) macro_f_memory_structure_resize(status, uint32s, uint32_t, length)
  #define macro_f_uint32s_t_adjust(status, uint32s, length) macro_f_memory_structure_adjust(status, uint32s, uint32_t, length)

  #define macro_f_uint32s_t_delete_simple(uint32s)  macro_f_memory_structure_delete_simple(uint32s, uint32_t)
  #define macro_f_uint32s_t_destroy_simple(uint32s) macro_f_memory_structure_destroy_simple(uint32s, uint32_t)

  #define macro_f_uint32s_t_increase(status, step, uint32s)      macro_f_memory_structure_increase(status, step, uint32s, uint32_t)
  #define macro_f_uint32s_t_increase_by(status, uint32s, amount) macro_f_memory_structure_increase_by(status, uint32s, uint32_t, amount)
  #define macro_f_uint32s_t_decrease_by(status, uint32s, amount) macro_f_memory_structure_decrease_by(status, uint32s, uint32_t, amount)
  #define macro_f_uint32s_t_decimate_by(status, uint32s, amount) macro_f_memory_structure_decimate_by(status, uint32s, uint32_t, amount)
#endif // _di_uint32s_t_

/**
 * Macros for f_array_lengths_t, see type.h for typedefs.
 */
#ifndef _di_uint32ss_t_
  #define macro_f_uint32ss_t_clear(numbers) macro_f_memory_structures_clear(numbers)

  #define macro_f_uint32ss_t_resize(status, uint32ss, length) status = f_type_uint32ss_resize(length, &uint32ss);
  #define macro_f_uint32ss_t_adjust(status, uint32ss, length) status = f_type_uint32ss_adjust(length, &uint32ss);

  #define macro_f_uint32ss_t_delete_simple(uint32ss)  f_type_uint32ss_resize(0, &uint32ss);
  #define macro_f_uint32ss_t_destroy_simple(uint32ss) f_type_uint32ss_adjust(0, &uint32ss);

  #define macro_f_uint32ss_t_increase(status, step, uint32ss)      status = f_type_uint32ss_increase(step, &uint32ss);
  #define macro_f_uint32ss_t_increase_by(status, uint32ss, amount) status = f_type_uint32ss_increase(amount, &uint32ss);
  #define macro_f_uint32ss_t_decrease_by(status, uint32ss, amount) status = f_type_uint32ss_decrease_by(amount, &uint32ss);
  #define macro_f_uint32ss_t_decimate_by(status, uint32ss, amount) status = f_type_uint32ss_decimate_by(amount, &uint32ss);
#endif // _di_uint32ss_t_

/**
 * Macros for f_array_lengths_t, see type.h for typedefs.
 */
#ifndef _di_int64s_t_
  #define macro_f_int64s_t_clear(int64s) macro_f_memory_structure_clear(int64s)

  #define macro_f_int64s_t_adjust(status, int64s, length) macro_f_memory_structure_adjust(status, int64s, int64_t, length)
  #define macro_f_int64s_t_resize(status, int64s, length) macro_f_memory_structure_resize(status, int64s, int64_t, length)

  #define macro_f_int64s_t_delete_simple(int64s)  macro_f_memory_structure_delete_simple(int64s, int64_t)
  #define macro_f_int64s_t_destroy_simple(int64s) macro_f_memory_structure_destroy_simple(int64s, int64_t)

  #define macro_f_int64s_t_increase(status, step, int64s)      macro_f_memory_structure_increase(status, step, int64s, int64_t)
  #define macro_f_int64s_t_increase_by(status, int64s, amount) macro_f_memory_structure_increase_by(status, int64s, int64_t, amount)
  #define macro_f_int64s_t_decrease_by(status, int64s, amount) macro_f_memory_structure_decrease_by(status, int64s, int64_t, amount)
  #define macro_f_int64s_t_decimate_by(status, int64s, amount) macro_f_memory_structure_decimate_by(status, int64s, int64_t, amount)
#endif // _di_int64s_t_

/**
 * Macros for f_array_lengths_t, see type.h for typedefs.
 */
#ifndef _di_int64ss_t_
  #define macro_f_int64ss_t_clear(numbers) macro_f_memory_structures_clear(numbers)

  #define macro_f_int64ss_t_resize(status, int64ss, length) status = f_type_int64ss_resize(length, &int64ss);
  #define macro_f_int64ss_t_adjust(status, int64ss, length) status = f_type_int64ss_adjust(length, &int64ss);

  #define macro_f_int64ss_t_increase(status, step, int64ss)      status = f_type_int64ss_increase(step, &int64ss);
  #define macro_f_int64ss_t_increase_by(status, int64ss, amount) status = f_type_int64ss_increase(amount, &int64ss);
  #define macro_f_int64ss_t_decrease_by(status, int64ss, amount) status = f_type_int64ss_decrease_by(amount, &int64ss);
  #define macro_f_int64ss_t_decimate_by(status, int64ss, amount) status = f_type_int64ss_decimate_by(amount, &int64ss);

  #define macro_f_int64ss_t_delete_simple(int64ss)  f_type_int64ss_resize(0, &int64ss);
  #define macro_f_int64ss_t_destroy_simple(int64ss) f_type_int64ss_adjust(0, &int64ss);
#endif // _di_int64ss_t_

/**
 * Macros for f_array_lengths_t, see type.h for typedefs.
 */
#ifndef _di_uint64s_t_
  #define macro_f_uint64s_t_clear(uint64s) macro_f_memory_structure_clear(uint64s)

  #define macro_f_uint64s_t_adjust(status, uint64s, length) macro_f_memory_structure_adjust(status, uint64s, uint64_t, length)
  #define macro_f_uint64s_t_resize(status, uint64s, length) macro_f_memory_structure_resize(status, uint64s, uint64_t, length)

  #define macro_f_uint64s_t_delete_simple(uint64s)  macro_f_memory_structure_delete_simple(uint64s, uint64_t)
  #define macro_f_uint64s_t_destroy_simple(uint64s) macro_f_memory_structure_destroy_simple(uint64s, uint64_t)

  #define macro_f_uint64s_t_increase(status, step, uint64s)      macro_f_memory_structure_increase(status, step, uint64s, uint64_t)
  #define macro_f_uint64s_t_increase_by(status, uint64s, amount) macro_f_memory_structure_increase_by(status, uint64s, uint64_t, amount)
  #define macro_f_uint64s_t_decrease_by(status, uint64s, amount) macro_f_memory_structure_decrease_by(status, uint64s, uint64_t, amount)
  #define macro_f_uint64s_t_decimate_by(status, uint64s, amount) macro_f_memory_structure_decimate_by(status, uint64s, uint64_t, amount)
#endif // _di_uint64s_t_

/**
 * Macros for f_array_lengths_t, see type.h for typedefs.
 */
#ifndef _di_uint64ss_t_
  #define macro_f_uint64ss_t_clear(numbers) macro_f_memory_structures_clear(numbers)

  #define macro_f_uint64ss_t_resize(status, uint64ss, length) status = f_type_uint64ss_resize(length, &uint64ss);
  #define macro_f_uint64ss_t_adjust(status, uint64ss, length) status = f_type_uint64ss_adjust(length, &uint64ss);

  #define macro_f_uint64ss_t_increase(status, step, uint64ss)      status = f_type_uint64ss_increase(step, &uint64ss);
  #define macro_f_uint64ss_t_increase_by(status, uint64ss, amount) status = f_type_uint64ss_increase(amount, &uint64ss);
  #define macro_f_uint64ss_t_decrease_by(status, uint64ss, amount) status = f_type_uint64ss_decrease_by(amount, &uint64ss);
  #define macro_f_uint64ss_t_decimate_by(status, uint64ss, amount) status = f_type_uint64ss_decimate_by(amount, &uint64ss);

  #define macro_f_uint64ss_t_delete_simple(uint64ss)  f_type_uint64ss_resize(0, &uint64ss);
  #define macro_f_uint64ss_t_destroy_simple(uint64ss) f_type_uint64ss_adjust(0, &uint64ss);
#endif // _di_uint64ss_t_

/**
 * Macros for f_array_lengths_t, see type.h for typedefs.
 */
#ifndef _di_int128s_t_
  #define macro_f_int128s_t_clear(int128s) macro_f_memory_structure_clear(int128s)

  #define macro_f_int128s_t_adjust(status, int128s, length) macro_f_memory_structure_adjust(status, int128s, f_int128_t, length)
  #define macro_f_int128s_t_resize(status, int128s, length) macro_f_memory_structure_resize(status, int128s, f_int128_t, length)

  #define macro_f_int128s_t_delete_simple(int128s)  macro_f_memory_structure_delete_simple(int128s, f_int128_t)
  #define macro_f_int128s_t_destroy_simple(int128s) macro_f_memory_structure_destroy_simple(int128s, f_int128_t)

  #define macro_f_int128s_t_increase(status, step, int128s)      macro_f_memory_structure_increase(status, step, int128s, f_int128_t)
  #define macro_f_int128s_t_increase_by(status, int128s, amount) macro_f_memory_structure_increase_by(status, int128s, f_int128_t, amount)
  #define macro_f_int128s_t_decrease_by(status, int128s, amount) macro_f_memory_structure_decrease_by(status, int128s, f_int128_t, amount)
  #define macro_f_int128s_t_decimate_by(status, int128s, amount) macro_f_memory_structure_decimate_by(status, int128s, f_int128_t, amount)
#endif // _di_int128s_t_

/**
 * Macros for f_array_lengths_t, see type.h for typedefs.
 */
#ifndef _di_int128ss_t_
  #define macro_f_int128ss_t_clear(numbers) macro_f_memory_structures_clear(numbers)

  #define macro_f_int128ss_t_resize(status, int128ss, length) status = f_type_int128ss_resize(length, &int128ss);
  #define macro_f_int128ss_t_adjust(status, int128ss, length) status = f_type_int128ss_adjust(length, &int128ss);

  #define macro_f_int128ss_t_delete_simple(int128ss)  f_type_int128ss_resize(0, &int128ss);
  #define macro_f_int128ss_t_destroy_simple(int128ss) f_type_int128ss_adjust(0, &int128ss);

  #define macro_f_int128ss_t_increase(status, step, int128ss)      status = f_type_int128ss_increase(step, &int128ss);
  #define macro_f_int128ss_t_increase_by(status, int128ss, amount) status = f_type_int128ss_increase(amount, &int128ss);
  #define macro_f_int128ss_t_decrease_by(status, int128ss, amount) status = f_type_int128ss_decrease_by(amount, &int128ss);
  #define macro_f_int128ss_t_decimate_by(status, int128ss, amount) status = f_type_int128ss_decimate_by(amount, &int128ss);
#endif // _di_int128ss_t_

/**
 * Macros for f_array_lengths_t, see type.h for typedefs.
 */
#ifndef _di_uint128s_t_
  #define macro_f_uint128s_t_clear(uint128s) macro_f_memory_structure_clear(uint128s)

  #define macro_f_uint128s_t_adjust(status, uint128s, length) macro_f_memory_structure_adjust(status, uint128s, f_uint128_t, length)
  #define macro_f_uint128s_t_resize(status, uint128s, length) macro_f_memory_structure_resize(status, uint128s, f_uint128_t, length)

  #define macro_f_uint128s_t_delete_simple(uint128s)  macro_f_memory_structure_delete_simple(uint128s, f_uint128_t)
  #define macro_f_uint128s_t_destroy_simple(uint128s) macro_f_memory_structure_destroy_simple(uint128s, f_uint128_t)

  #define macro_f_uint128s_t_increase(status, step, uint128s)      macro_f_memory_structure_increase(status, step, uint128s, f_uint128_t)
  #define macro_f_uint128s_t_increase_by(status, uint128s, amount) macro_f_memory_structure_increase_by(status, uint128s, f_uint128_t, amount)
  #define macro_f_uint128s_t_decrease_by(status, uint128s, amount) macro_f_memory_structure_decrease_by(status, uint128s, f_uint128_t, amount)
  #define macro_f_uint128s_t_decimate_by(status, uint128s, amount) macro_f_memory_structure_decimate_by(status, uint128s, f_uint128_t, amount)
#endif // _di_uint128s_t_

/**
 * Macros for f_array_lengths_t, see type.h for typedefs.
 */
#ifndef _di_uint128ss_t_
  #define macro_f_uint128ss_t_clear(numbers) macro_f_memory_structures_clear(numbers)

  #define macro_f_uint128ss_t_resize(status, uint128ss, length) status = f_type_uint128ss_resize(length, &uint128ss);
  #define macro_f_uint128ss_t_adjust(status, uint128ss, length) status = f_type_uint128ss_adjust(length, &uint128ss);

  #define macro_f_uint128ss_t_delete_simple(uint128ss)  f_type_uint128ss_resize(0, &uint128ss);
  #define macro_f_uint128ss_t_destroy_simple(uint128ss) f_type_uint128ss_adjust(0, &uint128ss);

  #define macro_f_uint128ss_t_increase(status, step, uint128ss)      status = f_type_uint128ss_increase(step, &uint128ss);
  #define macro_f_uint128ss_t_increase_by(status, uint128ss, amount) status = f_type_uint128ss_increase(amount, &uint128ss);
  #define macro_f_uint128ss_t_decrease_by(status, uint128ss, amount) status = f_type_uint128ss_decrease_by(amount, &uint128ss);
  #define macro_f_uint128ss_t_decimate_by(status, uint128ss, amount) status = f_type_uint128ss_decimate_by(amount, &uint128ss);
#endif // _di_uint128ss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_array_common_h
