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
  extern f_status_t f_account_delete(f_account_t *account);
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
  extern f_status_t f_account_destroy(f_account_t *account);
#endif // _di_f_account_destroy_

/**
 * Resize the accounts array.
 *
 * @param length
 *   The new size to use.
 * @param accounts
 *   The accounts array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_string_dynamic_adjust().
 *
 * @see f_memory_adjust()
 * @see f_string_dynamic_adjust()
 */
#ifndef _di_f_accounts_adjust_
  extern f_status_t f_accounts_adjust(const f_number_unsigned_t length, f_accounts_t *accounts);
#endif // _di_f_accounts_adjust_

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
  extern f_status_t f_accounts_append(const f_account_t source, f_accounts_t *destination);
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
  extern f_status_t f_accounts_append_all(const f_accounts_t source, f_accounts_t *destination);
#endif // _di_f_accounts_append_all_

/**
 * Resize the accounts array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param accounts
 *   The accounts array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_string_dynamic_adjust().
 *
 * @see f_memory_adjust()
 * @see f_string_dynamic_adjust()
 */
#ifndef _di_f_accounts_decimate_by_
  extern f_status_t f_accounts_decimate_by(const f_number_unsigned_t amount, f_accounts_t *accounts);
#endif // _di_f_accounts_decimate_by_

/**
 * Resize the accounts array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param accounts
 *   The accounts array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_memory_resize()
 * @see f_string_dynamic_resize()
 */
#ifndef _di_f_accounts_decrease_by_
  extern f_status_t f_accounts_decrease_by(const f_number_unsigned_t amount, f_accounts_t *accounts);
#endif // _di_f_accounts_decrease_by_

/**
 * Increase the size of the accounts array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param accounts
 *   The accounts array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_memory_resize()
 * @see f_string_dynamic_resize()
 */
#ifndef _di_f_accounts_increase_
  extern f_status_t f_accounts_increase(const f_number_unsigned_t step, f_accounts_t *accounts);
#endif // _di_f_accounts_increase_

/**
 * Resize the accounts array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param accounts
 *   The accounts array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_memory_resize()
 * @see f_string_dynamic_resize()
 */
#ifndef _di_f_accounts_increase_by_
  extern f_status_t f_accounts_increase_by(const f_number_unsigned_t amount, f_accounts_t *accounts);
#endif // _di_f_accounts_increase_by_

/**
 * Resize the accounts array.
 *
 * @param length
 *   The new size to use.
 * @param accounts
 *   The accounts array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_memory_resize()
 * @see f_string_dynamic_resize()
 */
#ifndef _di_f_accounts_resize_
  extern f_status_t f_accounts_resize(const f_number_unsigned_t length, f_accounts_t *accounts);
#endif // _di_f_accounts_resize_

/**
 * Resize the string accountss array.
 *
 * @param length
 *   The new size to use.
 * @param accountss
 *   The string accountss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_string_dynamic_adjust().
 *
 * @see f_memory_adjust()
 * @see f_string_dynamic_adjust()
 */
#ifndef _di_f_accountss_adjust_
  extern f_status_t f_accountss_adjust(const f_number_unsigned_t length, f_accountss_t *accountss);
#endif // _di_f_accountss_adjust_

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
  extern f_status_t f_accountss_append(const f_accounts_t source, f_accountss_t *destination);
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
  extern f_status_t f_accountss_append_all(const f_accountss_t source, f_accountss_t *destination);
#endif // _di_f_accountss_append_all_

/**
 * Resize the string accountss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param accountss
 *   The string accountss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_string_dynamic_adjust().
 *
 * @see f_memory_adjust()
 * @see f_string_dynamic_adjust()
 */
#ifndef _di_f_accountss_decimate_by_
  extern f_status_t f_accountss_decimate_by(const f_number_unsigned_t amount, f_accountss_t *accountss);
#endif // _di_f_accountss_decimate_by_

/**
 * Resize the string accountss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param accountss
 *   The string accountss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_memory_resize()
 * @see f_string_dynamic_resize()
 */
#ifndef _di_f_accountss_decrease_by_
  extern f_status_t f_accountss_decrease_by(const f_number_unsigned_t amount, f_accountss_t *accountss);
#endif // _di_f_accountss_decrease_by_

/**
 * Increase the size of the string accountss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param accountss
 *   The string accountss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_memory_resize()
 * @see f_string_dynamic_resize()
 */
#ifndef _di_f_accountss_increase_
  extern f_status_t f_accountss_increase(const f_number_unsigned_t step, f_accountss_t *accountss);
#endif // _di_f_accountss_increase_

/**
 * Resize the string accountss array to a larger size.
 *
 * This will resize making the array larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_number_t_size_unsigned_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param accountss
 *   The string accountss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_memory_resize()
 * @see f_string_dynamic_resize()
 */
#ifndef _di_f_accountss_increase_by_
  extern f_status_t f_accountss_increase_by(const f_number_unsigned_t amount, f_accountss_t *accountss);
#endif // _di_f_accountss_increase_by_

/**
 * Resize the string accountss array.
 *
 * @param length
 *   The new size to use.
 * @param accountss
 *   The accounts array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_memory_resize()
 * @see f_string_dynamic_resize()
 */
#ifndef _di_f_accountss_resize_
  extern f_status_t f_accountss_resize(const f_number_unsigned_t length, f_accountss_t *accountss);
#endif // _di_f_accountss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_account_accounts_h
