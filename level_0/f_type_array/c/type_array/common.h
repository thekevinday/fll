/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
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
  #define macro_f_statuss_t_clear(statuss) macro_f_memory_structures_clear(statuss)

  #define macro_f_statuss_t_resize(status, statuss, length) status = f_statuss_resize(length, &statuss);
  #define macro_f_statuss_t_adjust(status, statuss, length) status = f_statuss_adjust(length, &statuss);

  #define macro_f_statuss_t_delete_simple(statuss)  f_statuss_resize(0, &statuss);
  #define macro_f_statuss_t_destroy_simple(statuss) f_statuss_adjust(0, &statuss);

  #define macro_f_statuss_t_increase(status, step, statuss)      status = f_statuss_increase(step, &statuss);
  #define macro_f_statuss_t_increase_by(status, statuss, amount) status = f_statuss_increase_by(amount, &statuss);
  #define macro_f_statuss_t_decrease_by(status, statuss, amount) status = f_statuss_decrease_by(amount, &statuss);
  #define macro_f_statuss_t_decimate_by(status, statuss, amount) status = f_statuss_decimate_by(amount, &statuss);
#endif // _di_f_statuss_t_

/**
 * Macros for f_statusss_t, see type.h for typedefs.
 */
#ifndef _di_f_statusss_t_
  #define macro_f_statusss_t_clear(statusss) macro_f_memory_structures_clear(statusss)

  #define macro_f_statusss_t_resize(status, statusss, length) status = f_statusss_resize(length, &statusss);
  #define macro_f_statusss_t_adjust(status, statusss, length) status = f_statusss_adjust(length, &statusss);

  #define macro_f_statusss_t_delete_simple(statusss)  f_statusss_resize(0, &statusss);
  #define macro_f_statusss_t_destroy_simple(statusss) f_statusss_adjust(0, &statusss);

  #define macro_f_statusss_t_increase(status, step, statusss)      status = f_statusss_increase(step, &statusss);
  #define macro_f_statusss_t_increase_by(status, statusss, amount) status = f_statusss_increase_by(amount, &statusss);
  #define macro_f_statusss_t_decrease_by(status, statusss, amount) status = f_statusss_decrease_by(amount, &statusss);
  #define macro_f_statusss_t_decimate_by(status, statusss, amount) status = f_statusss_decimate_by(amount, &statusss);
#endif // _di_f_statusss_t_

/**
 * Macros for f_states_t, see type.h for typedefs.
 */
#ifndef _di_f_states_t_
  #define macro_f_states_t_clear(states) macro_f_memory_structures_clear(states)

  #define macro_f_states_t_resize(status, states, length) status = f_states_resize(length, &states);
  #define macro_f_states_t_adjust(status, states, length) status = f_states_adjust(length, &states);

  #define macro_f_states_t_delete_simple(states)  f_states_resize(0, &states);
  #define macro_f_states_t_destroy_simple(states) f_states_adjust(0, &states);

  #define macro_f_states_t_increase(status, step, states)      status = f_states_increase(step, &states);
  #define macro_f_states_t_increase_by(status, states, amount) status = f_states_increase_by(amount, &states);
  #define macro_f_states_t_decrease_by(status, states, amount) status = f_states_decrease_by(amount, &states);
  #define macro_f_states_t_decimate_by(status, states, amount) status = f_states_decimate_by(amount, &states);
#endif // _di_f_states_t_

/**
 * Macros for f_statess_t, see type.h for typedefs.
 */
#ifndef _di_f_statess_t_
  #define macro_f_statess_t_clear(statess) macro_f_memory_structures_clear(statess)

  #define macro_f_statess_t_resize(status, statess, length) status = f_statess_resize(length, &statess);
  #define macro_f_statess_t_adjust(status, statess, length) status = f_statess_adjust(length, &statess);

  #define macro_f_statess_t_delete_simple(statess)  f_statess_resize(0, &statess);
  #define macro_f_statess_t_destroy_simple(statess) f_statess_adjust(0, &statess);

  #define macro_f_statess_t_increase(status, step, statess)      status = f_statess_increase(step, &statess);
  #define macro_f_statess_t_increase_by(status, statess, amount) status = f_statess_increase_by(amount, &statess);
  #define macro_f_statess_t_decrease_by(status, statess, amount) status = f_statess_decrease_by(amount, &statess);
  #define macro_f_statess_t_decimate_by(status, statess, amount) status = f_statess_decimate_by(amount, &statess);
#endif // _di_f_statess_t_

/**
 * Macros for f_cells_t, see type.h for typedefs.
 */
#ifndef _di_f_cells_t_
  #define macro_f_cells_t_clear(cells) macro_f_memory_structures_clear(cells)

  #define macro_f_cells_t_resize(status, cells, length) status = f_cells_resize(length, &cells);
  #define macro_f_cells_t_adjust(status, cells, length) status = f_cells_adjust(length, &cells);

  #define macro_f_cells_t_delete_simple(cells)  f_cells_resize(0, &cells);
  #define macro_f_cells_t_destroy_simple(cells) f_cells_adjust(0, &cells);

  #define macro_f_cells_t_increase(status, step, cells)      status = f_cells_increase(step, &cells);
  #define macro_f_cells_t_increase_by(status, cells, amount) status = f_cells_increase_by(amount, &cells);
  #define macro_f_cells_t_decrease_by(status, cells, amount) status = f_cells_decrease_by(amount, &cells);
  #define macro_f_cells_t_decimate_by(status, cells, amount) status = f_cells_decimate_by(amount, &cells);
#endif // _di_f_cells_t_

/**
 * Macros for f_cellss_t, see type.h for typedefs.
 */
#ifndef _di_f_cellss_t_
  #define macro_f_cellss_t_clear(cellss) macro_f_memory_structures_clear(cellss)

  #define macro_f_cellss_t_resize(status, cellss, length) status = f_cellss_resize(length, &cellss);
  #define macro_f_cellss_t_adjust(status, cellss, length) status = f_cellss_adjust(length, &cellss);

  #define macro_f_cellss_t_delete_simple(cellss)  f_cellss_resize(0, &cellss);
  #define macro_f_cellss_t_destroy_simple(cellss) f_cellss_adjust(0, &cellss);

  #define macro_f_cellss_t_increase(status, step, cellss)      status = f_cellss_increase(step, &cellss);
  #define macro_f_cellss_t_increase_by(status, cellss, amount) status = f_cellss_increase_by(amount, &cellss);
  #define macro_f_cellss_t_decrease_by(status, cellss, amount) status = f_cellss_decrease_by(amount, &cellss);
  #define macro_f_cellss_t_decimate_by(status, cellss, amount) status = f_cellss_decimate_by(amount, &cellss);
#endif // _di_f_cellss_t_

/**
 * Macros for f_fll_ids_t, see type.h for typedefs.
 */
#ifndef _di_f_fll_ids_t_
  #define macro_f_fll_ids_t_clear(fll_ids) macro_f_memory_structures_clear(fll_ids)

  #define macro_f_fll_ids_t_resize(status, fll_ids, length) status = f_fll_ids_resize(length, &fll_ids);
  #define macro_f_fll_ids_t_adjust(status, fll_ids, length) status = f_fll_ids_adjust(length, &fll_ids);

  #define macro_f_fll_ids_t_delete_simple(fll_ids)  f_fll_ids_resize(0, &fll_ids);
  #define macro_f_fll_ids_t_destroy_simple(fll_ids) f_fll_ids_adjust(0, &fll_ids);

  #define macro_f_fll_ids_t_increase(status, step, fll_ids)      status = f_fll_ids_increase(step, &fll_ids);
  #define macro_f_fll_ids_t_increase_by(status, fll_ids, amount) status = f_fll_ids_increase_by(amount, &fll_ids);
  #define macro_f_fll_ids_t_decrease_by(status, fll_ids, amount) status = f_fll_ids_decrease_by(amount, &fll_ids);
  #define macro_f_fll_ids_t_decimate_by(status, fll_ids, amount) status = f_fll_ids_decimate_by(amount, &fll_ids);
#endif // _di_f_fll_ids_t_

/**
 * Macros for f_fll_idss_t, see type.h for typedefs.
 */
#ifndef _di_f_fll_idss_t_
  #define macro_f_fll_idss_t_clear(fll_idss) macro_f_memory_structures_clear(fll_idss)

  #define macro_f_fll_idss_t_resize(status, fll_idss, length) status = f_fll_idss_resize(length, &fll_idss);
  #define macro_f_fll_idss_t_adjust(status, fll_idss, length) status = f_fll_idss_adjust(length, &fll_idss);

  #define macro_f_fll_idss_t_delete_simple(fll_idss)  f_fll_idss_resize(0, &fll_idss);
  #define macro_f_fll_idss_t_destroy_simple(fll_idss) f_fll_idss_adjust(0, &fll_idss);

  #define macro_f_fll_idss_t_increase(status, step, fll_idss)      status = f_fll_idss_increase(step, &fll_idss);
  #define macro_f_fll_idss_t_increase_by(status, fll_idss, amount) status = f_fll_idss_increase_by(amount, &fll_idss);
  #define macro_f_fll_idss_t_decrease_by(status, fll_idss, amount) status = f_fll_idss_decrease_by(amount, &fll_idss);
  #define macro_f_fll_idss_t_decimate_by(status, fll_idss, amount) status = f_fll_idss_decimate_by(amount, &fll_idss);
#endif // _di_f_fll_idss_t_

/**
 * Macros for f_number_unsigneds_t, see type.h for typedefs.
 */
#ifndef _di_f_number_unsigneds_t_
  #define macro_f_number_unsigneds_t_clear(lengths) macro_f_memory_structures_clear(lengths)

  #define macro_f_number_unsigneds_t_resize(status, lengths, length) status = f_number_unsigneds_resize(length, &lengths);
  #define macro_f_number_unsigneds_t_adjust(status, lengths, length) status = f_number_unsigneds_adjust(length, &lengths);

  #define macro_f_number_unsigneds_t_delete_simple(lengths)  f_number_unsigneds_resize(0, &lengths);
  #define macro_f_number_unsigneds_t_destroy_simple(lengths) f_number_unsigneds_adjust(0, &lengths);

  #define macro_f_number_unsigneds_t_increase(status, step, lengths)      status = f_number_unsigneds_increase(step, &lengths);
  #define macro_f_number_unsigneds_t_increase_by(status, lengths, amount) status = f_number_unsigneds_increase_by(amount, &lengths);
  #define macro_f_number_unsigneds_t_decrease_by(status, lengths, amount) status = f_number_unsigneds_decrease_by(amount, &lengths);
  #define macro_f_number_unsigneds_t_decimate_by(status, lengths, amount) status = f_number_unsigneds_decimate_by(amount, &lengths);
#endif // _di_f_number_unsigneds_t_

/**
 * Macros for f_number_unsigneds_t, see type.h for typedefs.
 */
#ifndef _di_f_number_unsignedss_t_
  #define macro_f_number_unsignedss_t_clear(lengthss) macro_f_memory_structures_clear(lengthss)

  #define macro_f_number_unsignedss_t_resize(status, lengths, length) status = f_number_unsignedss_resize(length, &lengths);
  #define macro_f_number_unsignedss_t_adjust(status, lengths, length) status = f_number_unsignedss_adjust(length, &lengths);

  #define macro_f_number_unsignedss_t_delete_simple(lengths)  f_number_unsignedss_resize(0, &lengths);
  #define macro_f_number_unsignedss_t_destroy_simple(lengths) f_number_unsignedss_adjust(0, &lengths);

  #define macro_f_number_unsignedss_t_increase(status, step, lengths)      status = f_number_unsignedss_increase(step, &lengths);
  #define macro_f_number_unsignedss_t_increase_by(status, lengths, amount) status = f_number_unsignedss_increase_by(amount, &lengths);
  #define macro_f_number_unsignedss_t_decrease_by(status, lengths, amount) status = f_number_unsignedss_decrease_by(amount, &lengths);
  #define macro_f_number_unsignedss_t_decimate_by(status, lengths, amount) status = f_number_unsignedss_decimate_by(amount, &lengths);
#endif // _di_f_number_unsignedss_t_

/**
 * Macros for int8_t, see type.h for typedefs.
 */
#ifndef _di_f_int8_t_
  #define macro_f_int8s_t_clear(int8s) macro_f_memory_structures_clear(int8s)

  #define macro_f_int8s_t_resize(status, int8s, length) status = f_int8s_resize(length, &int8s);
  #define macro_f_int8s_t_adjust(status, int8s, length) status = f_int8s_adjust(length, &int8s);

  #define macro_f_int8s_t_increase(status, step, int8s)      status = f_int8s_increase(step, &int8s);
  #define macro_f_int8s_t_increase_by(status, int8s, amount) status = f_int8s_increase_by(amount, &int8s);
  #define macro_f_int8s_t_decrease_by(status, int8s, amount) status = f_int8s_decrease_by(amount, &int8s);
  #define macro_f_int8s_t_decimate_by(status, int8s, amount) status = f_int8s_decimate_by(amount, &int8s);

  #define macro_f_int8s_t_delete_simple(int8s)  f_int8s_resize(0, &int8s);
  #define macro_f_int8s_t_destroy_simple(int8s) f_int8s_adjust(0, &int8s);
#endif // _di_f_int8_t_

/**
 * Macros for f_int8s_t, see type.h for typedefs.
 */
#ifndef _di_f_int8ss_t_
  #define macro_f_int8ss_t_clear(int8ss) macro_f_memory_structures_clear(int8ss)

  #define macro_f_int8ss_t_resize(status, int8ss, length) status = f_int8ss_resize(length, &int8ss);
  #define macro_f_int8ss_t_adjust(status, int8ss, length) status = f_int8ss_adjust(length, &int8ss);

  #define macro_f_int8ss_t_increase(status, step, int8ss)      status = f_int8ss_increase(step, &int8ss);
  #define macro_f_int8ss_t_increase_by(status, int8ss, amount) status = f_int8ss_increase_by(amount, &int8ss);
  #define macro_f_int8ss_t_decrease_by(status, int8ss, amount) status = f_int8ss_decrease_by(amount, &int8ss);
  #define macro_f_int8ss_t_decimate_by(status, int8ss, amount) status = f_int8ss_decimate_by(amount, &int8ss);

  #define macro_f_int8ss_t_delete_simple(int8ss)  f_int8ss_resize(0, &int8ss);
  #define macro_f_int8ss_t_destroy_simple(int8ss) f_int8ss_adjust(0, &int8ss);
#endif // _di_f_int8ss_t_

/**
 * Macros for f_uint8s_t, see type.h for typedefs.
 */
#ifndef _di_f_uint8s_t_
  #define macro_f_uint8s_t_clear(uint8s) macro_f_memory_structures_clear(uint8s)

  #define macro_f_uint8s_t_resize(status, uint8s, length) status = f_uint8s_resize(length, &uint8s);
  #define macro_f_uint8s_t_adjust(status, uint8s, length) status = f_uint8s_adjust(length, &uint8s);

  #define macro_f_uint8s_t_delete_simple(uint8s)  f_uint8s_resize(0, &uint8s);
  #define macro_f_uint8s_t_destroy_simple(uint8s) f_uint8s_adjust(0, &uint8s);

  #define macro_f_uint8s_t_increase(status, step, uint8s)      status = f_uint8s_increase(step, &uint8s);
  #define macro_f_uint8s_t_increase_by(status, uint8s, amount) status = f_uint8s_increase_by(amount, &uint8s);
  #define macro_f_uint8s_t_decrease_by(status, uint8s, amount) status = f_uint8s_decrease_by(amount, &uint8s);
  #define macro_f_uint8s_t_decimate_by(status, uint8s, amount) status = f_uint8s_decimate_by(amount, &uint8s);
#endif // _di_f_uint8s_t_

/**
 * Macros for f_uint8ss_t, see type.h for typedefs.
 */
#ifndef _di_f_uint8ss_t_
  #define macro_f_uint8ss_t_clear(uint8ss) macro_f_memory_structures_clear(uint8ss)

  #define macro_f_uint8ss_t_resize(status, uint8ss, length) status = f_uint8ss_resize(length, &uint8ss);
  #define macro_f_uint8ss_t_adjust(status, uint8ss, length) status = f_uint8ss_adjust(length, &uint8ss);

  #define macro_f_uint8ss_t_delete_simple(uint8ss)  f_uint8ss_resize(0, &uint8ss);
  #define macro_f_uint8ss_t_destroy_simple(uint8ss) f_uint8ss_adjust(0, &uint8ss);

  #define macro_f_uint8ss_t_increase(status, step, uint8ss)      status = f_uint8ss_increase(step, &uint8ss);
  #define macro_f_uint8ss_t_increase_by(status, uint8ss, amount) status = f_uint8ss_increase_by(amount, &uint8ss);
  #define macro_f_uint8ss_t_decrease_by(status, uint8ss, amount) status = f_uint8ss_decrease_by(amount, &uint8ss);
  #define macro_f_uint8ss_t_decimate_by(status, uint8ss, amount) status = f_uint8ss_decimate_by(amount, &uint8ss);
#endif // _di_f_uint8ss_t_

/**
 * Macros for f_int16s_t, see type.h for typedefs.
 */
#ifndef _di_f_int16s_t_
  #define macro_f_int16s_t_clear(int16s) macro_f_memory_structures_clear(int16s)

  #define macro_f_int16s_t_resize(status, int16s, length) status = f_int16s_resize(length, &int16s);
  #define macro_f_int16s_t_adjust(status, int16s, length) status = f_int16s_adjust(length, &int16s);

  #define macro_f_int16s_t_increase(status, step, int16s)      status = f_int16s_increase(step, &int16s);
  #define macro_f_int16s_t_increase_by(status, int16s, amount) status = f_int16s_increase_by(amount, &int16s);
  #define macro_f_int16s_t_decrease_by(status, int16s, amount) status = f_int16s_decrease_by(amount, &int16s);
  #define macro_f_int16s_t_decimate_by(status, int16s, amount) status = f_int16s_decimate_by(amount, &int16s);

  #define macro_f_int16s_t_delete_simple(int16s)  f_int16s_resize(0, &int16s);
  #define macro_f_int16s_t_destroy_simple(int16s) f_int16s_adjust(0, &int16s);
#endif // _di_f_int16s_t_

/**
 * Macros for f_int16ss_t, see type.h for typedefs.
 */
#ifndef _di_f_int16ss_t_
  #define macro_f_int16ss_t_clear(int16ss) macro_f_memory_structures_clear(int16ss)

  #define macro_f_int16ss_t_resize(status, int16ss, length) status = f_int16ss_resize(length, &int16ss);
  #define macro_f_int16ss_t_adjust(status, int16ss, length) status = f_int16ss_adjust(length, &int16ss);

  #define macro_f_int16ss_t_increase(status, step, int16ss)      status = f_int16ss_increase(step, &int16ss);
  #define macro_f_int16ss_t_increase_by(status, int16ss, amount) status = f_int16ss_increase_by(amount, &int16ss);
  #define macro_f_int16ss_t_decrease_by(status, int16ss, amount) status = f_int16ss_decrease_by(amount, &int16ss);
  #define macro_f_int16ss_t_decimate_by(status, int16ss, amount) status = f_int16ss_decimate_by(amount, &int16ss);

  #define macro_f_int16ss_t_delete_simple(int16ss)  f_int16ss_resize(0, &int16ss);
  #define macro_f_int16ss_t_destroy_simple(int16ss) f_int16ss_adjust(0, &int16ss);
#endif // _di_f_int16ss_t_

/**
 * Macros for f_uint16s_t, see type.h for typedefs.
 */
#ifndef _di_f_uint16s_t_
  #define macro_f_uint16s_t_clear(uint16s) macro_f_memory_structures_clear(uint16s)

  #define macro_f_uint16s_t_resize(status, uint16s, length) status = f_uint16s_resize(length, &uint16s);
  #define macro_f_uint16s_t_adjust(status, uint16s, length) status = f_uint16s_adjust(length, &uint16s);

  #define macro_f_uint16s_t_delete_simple(uint16s)  f_uint16s_resize(0, &uint16s);
  #define macro_f_uint16s_t_destroy_simple(uint16s) f_uint16s_adjust(0, &uint16s);

  #define macro_f_uint16s_t_increase(status, step, uint16s)      status = f_uint16s_increase(step, &uint16s);
  #define macro_f_uint16s_t_increase_by(status, uint16s, amount) status = f_uint16s_increase_by(amount, &uint16s);
  #define macro_f_uint16s_t_decrease_by(status, uint16s, amount) status = f_uint16s_decrease_by(amount, &uint16s);
  #define macro_f_uint16s_t_decimate_by(status, uint16s, amount) status = f_uint16s_decimate_by(amount, &uint16s);
#endif // _di_f_uint16s_t_

/**
 * Macros for f_uint16ss_t, see type.h for typedefs.
 */
#ifndef _di_f_uint16ss_t_
  #define macro_f_uint16ss_t_clear(uint16ss) macro_f_memory_structures_clear(uint16ss)

  #define macro_f_uint16ss_t_resize(status, uint16ss, length) status = f_uint16ss_resize(length, &uint16ss);
  #define macro_f_uint16ss_t_adjust(status, uint16ss, length) status = f_uint16ss_adjust(length, &uint16ss);

  #define macro_f_uint16ss_t_delete_simple(uint16ss)  f_uint16ss_resize(0, &uint16ss);
  #define macro_f_uint16ss_t_destroy_simple(uint16ss) f_uint16ss_adjust(0, &uint16ss);

  #define macro_f_uint16ss_t_increase(status, step, uint16ss)      status = f_uint16ss_increase(step, &uint16ss);
  #define macro_f_uint16ss_t_increase_by(status, uint16ss, amount) status = f_uint16ss_increase_by(amount, &uint16ss);
  #define macro_f_uint16ss_t_decrease_by(status, uint16ss, amount) status = f_uint16ss_decrease_by(amount, &uint16ss);
  #define macro_f_uint16ss_t_decimate_by(status, uint16ss, amount) status = f_uint16ss_decimate_by(amount, &uint16ss);
#endif // _di_f_uint16ss_t_

/**
 * Macros for f_int32s_t, see type.h for typedefs.
 */
#ifndef _di_f_int32s_t_
  #define macro_f_int32s_t_clear(int32s) macro_f_memory_structures_clear(int32s)

  #define macro_f_int32s_t_resize(status, int32s, length) status = f_int32s_resize(length, &int32s);
  #define macro_f_int32s_t_adjust(status, int32s, length) status = f_int32s_adjust(length, &int32s);

  #define macro_f_int32s_t_delete_simple(int32s)  f_int32s_resize(0, &int32s);
  #define macro_f_int32s_t_destroy_simple(int32s) f_int32s_adjust(0, &int32s);

  #define macro_f_int32s_t_increase(status, step, int32s)      status = f_int32s_increase(step, &int32s);
  #define macro_f_int32s_t_increase_by(status, int32s, amount) status = f_int32s_increase_by(amount, &int32s);
  #define macro_f_int32s_t_decrease_by(status, int32s, amount) status = f_int32s_decrease_by(amount, &int32s);
  #define macro_f_int32s_t_decimate_by(status, int32s, amount) status = f_int32s_decimate_by(amount, &int32s);
#endif // _di_f_int32s_t_

/**
 * Macros for f_number_unsigneds_t, see type.h for typedefs.
 */
#ifndef _di_f_int32ss_t_
  #define macro_f_int32ss_t_clear(int32ss) macro_f_memory_structures_clear(int32ss)

  #define macro_f_int32ss_t_resize(status, int32ss, length) status = f_int32ss_resize(length, &int32ss);
  #define macro_f_int32ss_t_adjust(status, int32ss, length) status = f_int32ss_adjust(length, &int32ss);

  #define macro_f_int32ss_t_delete_simple(int32ss)  f_int32ss_resize(0, &int32ss);
  #define macro_f_int32ss_t_destroy_simple(int32ss) f_int32ss_adjust(0, &int32ss);

  #define macro_f_int32ss_t_increase(status, step, int32ss)      status = f_int32ss_increase(step, &int32ss);
  #define macro_f_int32ss_t_increase_by(status, int32ss, amount) status = f_int32ss_increase_by(amount, &int32ss);
  #define macro_f_int32ss_t_decrease_by(status, int32ss, amount) status = f_int32ss_decrease_by(amount, &int32ss);
  #define macro_f_int32ss_t_decimate_by(status, int32ss, amount) status = f_int32ss_decimate_by(amount, &int32ss);
#endif // _di_f_int32ss_t_

/**
 * Macros for f_uint32s_t, see type.h for typedefs.
 */
#ifndef _di_f_uint32s_t_
  #define macro_f_uint32s_t_clear(uint32s) macro_f_memory_structures_clear(uint32s)

  #define macro_f_uint32s_t_resize(status, uint32s, length) status = f_uint32s_resize(length, &uint32s);
  #define macro_f_uint32s_t_adjust(status, uint32s, length) status = f_uint32s_adjust(length, &uint32s);

  #define macro_f_uint32s_t_delete_simple(uint32s)  f_uint32s_resize(0, &uint32s);
  #define macro_f_uint32s_t_destroy_simple(uint32s) f_uint32s_adjust(0, &uint32s);

  #define macro_f_uint32s_t_increase(status, step, uint32s)      status = f_uint32s_increase(step, &uint32s);
  #define macro_f_uint32s_t_increase_by(status, uint32s, amount) status = f_uint32s_increase_by(amount, &uint32s);
  #define macro_f_uint32s_t_decrease_by(status, uint32s, amount) status = f_uint32s_decrease_by(amount, &uint32s);
  #define macro_f_uint32s_t_decimate_by(status, uint32s, amount) status = f_uint32s_decimate_by(amount, &uint32s);
#endif // _di_f_uint32s_t_

/**
 * Macros for f_uint32ss_t, see type.h for typedefs.
 */
#ifndef _di_f_uint32ss_t_
  #define macro_f_uint32ss_t_clear(uint32ss) macro_f_memory_structures_clear(uint32ss)

  #define macro_f_uint32ss_t_resize(status, uint32ss, length) status = f_uint32ss_resize(length, &uint32ss);
  #define macro_f_uint32ss_t_adjust(status, uint32ss, length) status = f_uint32ss_adjust(length, &uint32ss);

  #define macro_f_uint32ss_t_delete_simple(uint32ss)  f_uint32ss_resize(0, &uint32ss);
  #define macro_f_uint32ss_t_destroy_simple(uint32ss) f_uint32ss_adjust(0, &uint32ss);

  #define macro_f_uint32ss_t_increase(status, step, uint32ss)      status = f_uint32ss_increase(step, &uint32ss);
  #define macro_f_uint32ss_t_increase_by(status, uint32ss, amount) status = f_uint32ss_increase_by(amount, &uint32ss);
  #define macro_f_uint32ss_t_decrease_by(status, uint32ss, amount) status = f_uint32ss_decrease_by(amount, &uint32ss);
  #define macro_f_uint32ss_t_decimate_by(status, uint32ss, amount) status = f_uint32ss_decimate_by(amount, &uint32ss);
#endif // _di_f_uint32ss_t_

/**
 * Macros for f_int64s_t, see type.h for typedefs.
 */
#ifndef _di_f_int64s_t_
  #define macro_f_int64s_t_clear(int64s) macro_f_memory_structures_clear(int64s)

  #define macro_f_int64s_t_resize(status, int64s, length) status = f_int64s_resize(length, &int64s);
  #define macro_f_int64s_t_adjust(status, int64s, length) status = f_int64s_adjust(length, &int64s);

  #define macro_f_int64s_t_increase(status, step, int64s)      status = f_int64s_increase(step, &int64s);
  #define macro_f_int64s_t_increase_by(status, int64s, amount) status = f_int64s_increase_by(amount, &int64s);
  #define macro_f_int64s_t_decrease_by(status, int64s, amount) status = f_int64s_decrease_by(amount, &int64s);
  #define macro_f_int64s_t_decimate_by(status, int64s, amount) status = f_int64s_decimate_by(amount, &int64s);

  #define macro_f_int64s_t_delete_simple(int64s)  f_int64s_resize(0, &int64s);
  #define macro_f_int64s_t_destroy_simple(int64s) f_int64s_adjust(0, &int64s);
#endif // _di_f_int64s_t_

/**
 * Macros for f_int64ss_t, see type.h for typedefs.
 */
#ifndef _di_f_int64ss_t_
  #define macro_f_int64ss_t_clear(int64ss) macro_f_memory_structures_clear(int64ss)

  #define macro_f_int64ss_t_resize(status, int64ss, length) status = f_int64ss_resize(length, &int64ss);
  #define macro_f_int64ss_t_adjust(status, int64ss, length) status = f_int64ss_adjust(length, &int64ss);

  #define macro_f_int64ss_t_increase(status, step, int64ss)      status = f_int64ss_increase(step, &int64ss);
  #define macro_f_int64ss_t_increase_by(status, int64ss, amount) status = f_int64ss_increase_by(amount, &int64ss);
  #define macro_f_int64ss_t_decrease_by(status, int64ss, amount) status = f_int64ss_decrease_by(amount, &int64ss);
  #define macro_f_int64ss_t_decimate_by(status, int64ss, amount) status = f_int64ss_decimate_by(amount, &int64ss);

  #define macro_f_int64ss_t_delete_simple(int64ss)  f_int64ss_resize(0, &int64ss);
  #define macro_f_int64ss_t_destroy_simple(int64ss) f_int64ss_adjust(0, &int64ss);
#endif // _di_f_int64ss_t_

/**
 * Macros for f_uint64s_t, see type.h for typedefs.
 */
#ifndef _di_f_uint64s_t_
  #define macro_f_uint64s_t_clear(uint64s) macro_f_memory_structures_clear(uint64s)

  #define macro_f_uint64s_t_resize(status, uint64s, length) status = f_uint64s_resize(length, &uint64s);
  #define macro_f_uint64s_t_adjust(status, uint64s, length) status = f_uint64s_adjust(length, &uint64s);

  #define macro_f_uint64s_t_increase(status, step, uint64s)      status = f_uint64s_increase(step, &uint64s);
  #define macro_f_uint64s_t_increase_by(status, uint64s, amount) status = f_uint64s_increase_by(amount, &uint64s);
  #define macro_f_uint64s_t_decrease_by(status, uint64s, amount) status = f_uint64s_decrease_by(amount, &uint64s);
  #define macro_f_uint64s_t_decimate_by(status, uint64s, amount) status = f_uint64s_decimate_by(amount, &uint64s);

  #define macro_f_uint64s_t_delete_simple(uint64s)  f_uint64s_resize(0, &uint64s);
  #define macro_f_uint64s_t_destroy_simple(uint64s) f_uint64s_adjust(0, &uint64s);
#endif // _di_f_uint64s_t_

/**
 * Macros for f_uint64ss_t, see type.h for typedefs.
 */
#ifndef _di_f_uint64ss_t_
  #define macro_f_uint64ss_t_clear(uint64ss) macro_f_memory_structures_clear(uint64ss)

  #define macro_f_uint64ss_t_resize(status, uint64ss, length) status = f_uint64ss_resize(length, &uint64ss);
  #define macro_f_uint64ss_t_adjust(status, uint64ss, length) status = f_uint64ss_adjust(length, &uint64ss);

  #define macro_f_uint64ss_t_increase(status, step, uint64ss)      status = f_uint64ss_increase(step, &uint64ss);
  #define macro_f_uint64ss_t_increase_by(status, uint64ss, amount) status = f_uint64ss_increase_by(amount, &uint64ss);
  #define macro_f_uint64ss_t_decrease_by(status, uint64ss, amount) status = f_uint64ss_decrease_by(amount, &uint64ss);
  #define macro_f_uint64ss_t_decimate_by(status, uint64ss, amount) status = f_uint64ss_decimate_by(amount, &uint64ss);

  #define macro_f_uint64ss_t_delete_simple(uint64ss)  f_uint64ss_resize(0, &uint64ss);
  #define macro_f_uint64ss_t_destroy_simple(uint64ss) f_uint64ss_adjust(0, &uint64ss);
#endif // _di_f_uint64ss_t_

/**
 * Macros for f_int128s_t, see type.h for typedefs.
 */
#ifndef _di_f_int128s_t_
  #define macro_f_int128s_t_clear(int128s) macro_f_memory_structures_clear(int128s)

  #define macro_f_int128s_t_resize(status, int128s, length) status = f_int128s_resize(length, &int128s);
  #define macro_f_int128s_t_adjust(status, int128s, length) status = f_int128s_adjust(length, &int128s);

  #define macro_f_int128s_t_delete_simple(int128s)  f_int128s_resize(0, &int128s);
  #define macro_f_int128s_t_destroy_simple(int128s) f_int128s_adjust(0, &int128s);

  #define macro_f_int128s_t_increase(status, step, int128s)      status = f_int128s_increase(step, &int128s);
  #define macro_f_int128s_t_increase_by(status, int128s, amount) status = f_int128s_increase_by(amount, &int128s);
  #define macro_f_int128s_t_decrease_by(status, int128s, amount) status = f_int128s_decrease_by(amount, &int128s);
  #define macro_f_int128s_t_decimate_by(status, int128s, amount) status = f_int128s_decimate_by(amount, &int128s);
#endif // _di_f_int128s_t_

/**
 * Macros for f_int128ss_t, see type.h for typedefs.
 */
#ifndef _di_f_int128ss_t_
  #define macro_f_int128ss_t_clear(int128ss) macro_f_memory_structures_clear(int128ss)

  #define macro_f_int128ss_t_resize(status, int128ss, length) status = f_int128ss_resize(length, &int128ss);
  #define macro_f_int128ss_t_adjust(status, int128ss, length) status = f_int128ss_adjust(length, &int128ss);

  #define macro_f_int128ss_t_delete_simple(int128ss)  f_int128ss_resize(0, &int128ss);
  #define macro_f_int128ss_t_destroy_simple(int128ss) f_int128ss_adjust(0, &int128ss);

  #define macro_f_int128ss_t_increase(status, step, int128ss)      status = f_int128ss_increase(step, &int128ss);
  #define macro_f_int128ss_t_increase_by(status, int128ss, amount) status = f_int128ss_increase_by(amount, &int128ss);
  #define macro_f_int128ss_t_decrease_by(status, int128ss, amount) status = f_int128ss_decrease_by(amount, &int128ss);
  #define macro_f_int128ss_t_decimate_by(status, int128ss, amount) status = f_int128ss_decimate_by(amount, &int128ss);
#endif // _di_f_int128ss_t_

/**
 * Macros for f_uint128s_t, see type.h for typedefs.
 */
#ifndef _di_f_uint128s_t_
  #define macro_f_uint128s_t_clear(uint128s) macro_f_memory_structures_clear(uint128s)

  #define macro_f_uint128s_t_resize(status, uint128s, length) status = f_uint128s_resize(length, &uint128s);
  #define macro_f_uint128s_t_adjust(status, uint128s, length) status = f_uint128s_adjust(length, &uint128s);

  #define macro_f_uint128s_t_delete_simple(uint128s)  f_uint128s_resize(0, &uint128s);
  #define macro_f_uint128s_t_destroy_simple(uint128s) f_uint128s_adjust(0, &uint128s);

  #define macro_f_uint128s_t_increase(status, step, uint128s)      status = f_uint128s_increase(step, &uint128s);
  #define macro_f_uint128s_t_increase_by(status, uint128s, amount) status = f_uint128s_increase_by(amount, &uint128s);
  #define macro_f_uint128s_t_decrease_by(status, uint128s, amount) status = f_uint128s_decrease_by(amount, &uint128s);
  #define macro_f_uint128s_t_decimate_by(status, uint128s, amount) status = f_uint128s_decimate_by(amount, &uint128s);
#endif // _di_f_uint128s_t_

/**
 * Macros for f_uint128ss_t, see type.h for typedefs.
 */
#ifndef _di_f_uint128ss_t_
  #define macro_f_uint128ss_t_clear(uint128ss) macro_f_memory_structures_clear(uint128ss)

  #define macro_f_uint128ss_t_resize(status, uint128ss, length) status = f_uint128ss_resize(length, &uint128ss);
  #define macro_f_uint128ss_t_adjust(status, uint128ss, length) status = f_uint128ss_adjust(length, &uint128ss);

  #define macro_f_uint128ss_t_delete_simple(uint128ss)  f_uint128ss_resize(0, &uint128ss);
  #define macro_f_uint128ss_t_destroy_simple(uint128ss) f_uint128ss_adjust(0, &uint128ss);

  #define macro_f_uint128ss_t_increase(status, step, uint128ss)      status = f_uint128ss_increase(step, &uint128ss);
  #define macro_f_uint128ss_t_increase_by(status, uint128ss, amount) status = f_uint128ss_increase_by(amount, &uint128ss);
  #define macro_f_uint128ss_t_decrease_by(status, uint128ss, amount) status = f_uint128ss_decrease_by(amount, &uint128ss);
  #define macro_f_uint128ss_t_decimate_by(status, uint128ss, amount) status = f_uint128ss_decimate_by(amount, &uint128ss);
#endif // _di_f_uint128ss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_array_common_h
