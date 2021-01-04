/**
 * FLL - Level 0
 *
 * Project: Limit
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_limit_h
#define _PRIVATE_F_limit_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of f_limit_sets_delete().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param sets
 *   The sets to delete.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_limit_sets_t_delete().
 *
 * @see f_macro_limit_sets_t_delete()
 * @see f_limit_sets_decrease()
 * @see f_limit_sets_decrease_by()
 * @see f_limit_sets_delete()
 */
#if !defined(_di_f_limit_sets_decrease_) || !defined(_di_f_limit_sets_decrease_by_) || !defined(_di_f_limit_sets_delete_)
  extern f_return_status private_f_limit_sets_delete(f_limit_sets_t *sets) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_limit_sets_decrease_) || !defined(_di_f_limit_sets_decrease_by_) || !defined(_di_f_limit_sets_delete_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param sets
 *   The sets to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_limit_sets_t_resize().
 *
 * @see f_macro_limit_sets_t_resize()
 * @see f_limit_sets_decrease()
 * @see f_limit_sets_decrease_by()
 * @see f_limit_sets_increase()
 * @see f_limit_sets_increase_by()
 */
#if !defined(_di_f_limit_sets_decrease_) || !defined(_di_f_limit_sets_decrease_by_) || !defined(_di_f_limit_sets_increase_) || !defined(_di_f_limit_sets_increase_by_)
  extern f_return_status private_f_limit_sets_resize(const f_array_length_t length, f_limit_sets_t *sets) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_limit_sets_decrease_) || !defined(_di_f_limit_sets_decrease_by_) || !defined(_di_f_limit_sets_increase_) || !defined(_di_f_limit_sets_increase_by_)

/**
 * Private implementation of f_limit_values_delete().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param values
 *   The values to delete.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_limit_values_t_delete().
 *
 * @see f_macro_limit_values_t_delete()
 * @see f_limit_values_decrease()
 * @see f_limit_values_decrease_by()
 * @see f_limit_values_delete()
 */
#if !defined(_di_f_limit_values_decrease_) || !defined(_di_f_limit_values_decrease_by_) || !defined(_di_f_limit_values_delete_)
  extern f_return_status private_f_limit_values_delete(f_limit_values_t *values) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_limit_values_decrease_) || !defined(_di_f_limit_values_decrease_by_) || !defined(_di_f_limit_values_delete_)

/**
 * Private implementation for resizing.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The new size to use.
 * @param values
 *   The values to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_macro_limit_values_t_resize().
 *
 * @see f_macro_limit_values_t_resize()
 * @see f_limit_values_decrease()
 * @see f_limit_values_decrease_by()
 * @see f_limit_values_increase()
 * @see f_limit_values_increase_by()
 */
#if !defined(_di_f_limit_values_decrease_) || !defined(_di_f_limit_values_decrease_by_) || !defined(_di_f_limit_values_increase_) || !defined(_di_f_limit_values_increase_by_)
  extern f_return_status private_f_limit_values_resize(const f_array_length_t length, f_limit_values_t *values) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_limit_values_decrease_) || !defined(_di_f_limit_values_decrease_by_) || !defined(_di_f_limit_values_increase_) || !defined(_di_f_limit_values_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_limit_h
