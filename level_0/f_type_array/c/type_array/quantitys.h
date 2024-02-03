/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines data to be used for/by type (array) related functionality.
 *
 * This is auto-included by type_array.h and should not need to be explicitly included.
 */
#ifndef _F_type_array_quantitys_h
#define _F_type_array_quantitys_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Append the single source quantity onto the destination.
 *
 * @param source
 *   The source quantity to append.
 * @param destination
 *   The destination quantitys the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_quantitys_append_
  extern f_status_t f_quantitys_append(const f_quantity_t source, f_quantitys_t * const destination);
#endif // _di_f_quantitys_append_

/**
 * Append the source quantitys onto the destination.
 *
 * @param source
 *   The source quantitys to append.
 * @param destination
 *   The destination quantitys the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_quantitys_append_all_
  extern f_status_t f_quantitys_append_all(const f_quantitys_t source, f_quantitys_t * const destination);
#endif // _di_f_quantitys_append_all_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_array_quantitys_h
