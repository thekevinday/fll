/**
 * FLL - Level 0
 *
 * Project: Abstruse
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_abstruse_h
#define _PRIVATE_F_abstruse_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Helper function for abstruse delete callbacks, performing the switch logic against the abstruse type.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param abstruse
 *   The abstruse to perform the switch-based delete operation on.
 *
 * @return
 *   F_okay on success, including when nothing done due to no match against the type.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *   Errors (with error bit) from: f_memory_arrays_resize().
 *
 * @see f_memory_array_resize()
 * @see f_memory_arrays_resize()
 */
#if !defined(_di_f_abstruses_delete_callback_) || !defined(_di_f_abstrusess_delete_callback_) || !defined(_di_f_abstruse_maps_delete_callback_) || !defined(_di_f_abstruse_mapss_delete_callback_)
  extern f_status_t private_f_abstruses_delete_switch(f_abstruse_t * const abstruse) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_abstruses_delete_callback_) || !defined(_di_f_abstrusess_delete_callback_) || !defined(_di_f_abstruse_maps_delete_callback_) || !defined(_di_f_abstruse_mapss_delete_callback_)

/**
 * Helper function for abstruse destroy callbacks, performing the switch logic against the abstruse type.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param abstruse
 *   The abstruse to perform the switch-based destroy operation on.
 *
 * @return
 *   F_okay on success, including when nothing done due to no match against the type.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *   Errors (with error bit) from: f_memory_arrays_adjust().
 *
 * @see f_memory_array_adjust()
 * @see f_memory_arrays_adjust()
 */
#if !defined(_di_f_abstruses_destroy_callback_) || !defined(_di_f_abstrusess_destroy_callback_) || !defined(_di_f_abstruse_maps_destroy_callback_) || !defined(_di_f_abstruse_mapss_destroy_callback_)
  extern f_status_t private_f_abstruses_destroy_switch(f_abstruse_t * const abstruse) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_abstruses_destroy_callback_) || !defined(_di_f_abstrusess_destroy_callback_) || !defined(_di_f_abstruse_maps_destroy_callback_) || !defined(_di_f_abstruse_mapss_destroy_callback_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_abstruse_h
