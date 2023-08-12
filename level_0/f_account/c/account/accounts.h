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
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_accountss_t structure.
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
 *
 * @see f_memory_array_adjust()
 * @see f_memory_arrays_adjust()
 */
#ifndef _di_f_accounts_adjust_callback_
  extern f_status_t f_accounts_adjust_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_accounts_adjust_callback_

/**
 * Append the single source account onto the destination.
 *
 * @param source
 *   The source account to append.
 * @param destination
 *   The destination accounts the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: f_string_dynamic_append().
 *
 * @see f_memory_resize()
 * @see f_string_dynamic_append()
 */
#ifndef _di_f_accounts_append_
  extern f_status_t f_accounts_append(const f_account_t source, f_accounts_t * const destination);
#endif // _di_f_accounts_append_

/**
 * Append the source accounts onto the destination.
 *
 * @param source
 *   The source accounts to append.
 * @param destination
 *   The destination accounts the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: f_string_dynamic_append().
 *
 * @see f_memory_resize()
 * @see f_string_dynamic_append()
 */
#ifndef _di_f_accounts_append_all_
  extern f_status_t f_accounts_append_all(const f_accounts_t source, f_accounts_t * const destination);
#endif // _di_f_accounts_append_all_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_accountss_t structure.
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
 *
 * @see f_memory_array_resize()
 * @see f_memory_arrays_resize()
 */
#ifndef _di_f_accounts_resize_callback_
  extern f_status_t f_accounts_resize_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_accounts_resize_callback_

/**
 * Append the single source accounts onto the destination.
 *
 * @param source
 *   The source accounts to append.
 * @param destination
 *   The destination ranges the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_memory_resize()
 * @see f_string_dynamic_resize()
 */
#ifndef _di_f_accountss_append_
  extern f_status_t f_accountss_append(const f_accounts_t source, f_accountss_t * const destination);
#endif // _di_f_accountss_append_

/**
 * Append the source accountss onto the destination.
 *
 * @param source
 *   The source accountss to append.
 * @param destination
 *   The destination ranges the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_memory_resize()
 * @see f_string_dynamic_resize()
 */
#ifndef _di_f_accountss_append_all_
  extern f_status_t f_accountss_append_all(const f_accountss_t source, f_accountss_t * const destination);
#endif // _di_f_accountss_append_all_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_account_accounts_h
