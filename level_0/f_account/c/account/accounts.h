/**
 * FLL - Level 0
 *
 * Project: Account
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines data to be used for/by account (array) related functionality.
 *
 * This is auto-included by account.h and should not need to be explicitly included.
 */
#ifndef _F_account_accounts_h
#define _F_account_accounts_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Delete the account.
 *
 * @param account
 *   The account to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_string_dynamic_resize()
 */
#ifndef _di_f_account_delete_
  extern f_status_t f_account_delete(f_account_t * const account);
#endif // _di_f_account_delete_

/**
 * Destroy the account.
 *
 * @param account
 *   The account to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_adjust().
 *
 * @see f_string_dynamic_adjust()
 */
#ifndef _di_f_account_destroy_
  extern f_status_t f_account_destroy(f_account_t * const account);
#endif // _di_f_account_destroy_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_accounts_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_string_dynamic_resize()
 */
#ifndef _di_f_accounts_delete_callback_
  extern f_status_t f_accounts_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_accounts_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_accounts_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_adjust().
 *
 * @see f_string_dynamic_adjust()
 */
#ifndef _di_f_accounts_destroy_callback_
  extern f_status_t f_accounts_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_accounts_destroy_callback_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_accountss_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_memory_array_resize()
 * @see f_string_dynamic_resize()
 */
#ifndef _di_f_accountss_delete_callback_
  extern f_status_t f_accountss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_accountss_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_accountss_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *   Errors (with error bit) from: f_string_dynamic_adjust().
 *
 * @see f_memory_array_adjust()
 * @see f_string_dynamic_adjust()
 */
#ifndef _di_f_accountss_destroy_callback_
  extern f_status_t f_accountss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_accountss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_account_accounts_h
