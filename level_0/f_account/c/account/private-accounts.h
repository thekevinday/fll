/**
 * FLL - Level 0
 *
 * Project: Account
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_account_accounts_h
#define _PRIVATE_F_account_accounts_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation for resizing the account.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param account
 *   The account to delete.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_string_dynamic_resize()
 *
 * @see f_account_delete()
 * @see f_accounts_append()
 * @see f_accounts_decimate_by()
 * @see f_accounts_resize()
 * @see f_accountss_append()
 * @see f_accountss_decrease_by()
 * @see f_accountss_increase()
 * @see f_accountss_increase_by()
 * @see f_accountss_resize()
 */
#if !defined(_di_f_account_delete_) || !defined(_di_f_accounts_resize_) || !defined(_di_f_accounts_append_) || !defined(_di_f_accounts_decimate_by_) || !defined(_di_f_accountss_append_) || !defined(_di_f_accountss_decrease_by_) || !defined(_di_f_accountss_increase_) || !defined(_di_f_accountss_increase_by_) || !defined(_di_f_accountss_resize_)
  extern f_status_t private_f_account_delete(f_account_t *account) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_account_delete_) || !defined(_di_f_accounts_resize_) || !defined(_di_f_accounts_append_) || !defined(_di_f_accounts_decimate_by_) || !defined(_di_f_accountss_append_) || !defined(_di_f_accountss_decrease_by_) || !defined(_di_f_accountss_increase_) || !defined(_di_f_accountss_increase_by_) || !defined(_di_f_accountss_resize_)

/**
 * Private implementation for resizing the account.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param account
 *   The account to delete.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_string_dynamic_adjust().
 *
 * @see f_string_dynamic_adjust()
 *
 * @see f_account_destroy()
 * @see f_accounts_adjust()
 * @see f_accounts_decimate_by()
 * @see f_accountss_adjust()
 * @see f_accountss_decimate_by()
 */
#if !defined(_di_f_account_destroy_) || !defined(_di_f_accounts_adjust_) || !defined(_di_f_accounts_decimate_by_) || !defined(_di_f_accountss_adjust_) || !defined(_di_f_accountss_decimate_by_)
  extern f_status_t private_f_account_destroy(f_account_t *account) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_account_destroy_) || !defined(_di_f_accounts_adjust_) || !defined(_di_f_accounts_decimate_by_) || !defined(_di_f_accountss_adjust_) || !defined(_di_f_accountss_decimate_by_)

/**
 * Private implementation for resizing the accounts array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param accounts
 *   The accounts array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_string_dynamic_adjust().
 *
 * @see f_memory_adjust()
 * @see f_string_dynamic_adjust()
 *
 * @see f_accounts_adjust()
 * @see f_accounts_decimate_by()
 * @see f_accountss_adjust()
 * @see f_accountss_decimate_by()
 */
#if !defined(_di_f_accounts_adjust_) || !defined(_di_f_accounts_decimate_by_) || !defined(_di_f_accountss_adjust_) || !defined(_di_f_accountss_decimate_by_)
  extern f_status_t private_f_accounts_adjust(const f_number_unsigned_t length, f_accounts_t *accounts) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_accounts_adjust_) || !defined(_di_f_accounts_decimate_by_) || !defined(_di_f_accountss_adjust_) || !defined(_di_f_accountss_decimate_by_)

/**
 * Private implementation for appending the account array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source account to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: f_string_dynamic_append().
 *
 * @see f_memory_resize()
 * @see f_string_dynamic_append()
 *
 * @see f_accounts_append()
 * @see f_accountss_append()
 */
#if !defined(_di_f_accounts_append_) || !defined(_di_f_accountss_append_)
  extern f_status_t private_f_accounts_append(const f_account_t source, f_accounts_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_accounts_append_) || !defined(_di_f_accountss_append_)

/**
 * Private implementation for appending the account array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param source
 *   The source accounts to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: f_string_dynamic_append().
 *
 * @see f_memory_resize()
 * @see f_string_dynamic_append()
 *
 * @see f_accounts_append_all()
 * @see f_accountss_append()
 * @see f_accountss_append_all()
 */
#if !defined(_di_f_accounts_append_) || !defined(_di_f_accounts_append_all_) || !defined(_di_f_accountss_append_all_)
  extern f_status_t private_f_accounts_append_all(const f_accounts_t source, f_accounts_t *destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_accounts_append_) || !defined(_di_f_accounts_append_all_) || !defined(_di_f_accountss_append_all_)

/**
 * Private implementation for resizing the accounts array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param accounts
 *   The accounts array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   Errors (with error bit) from: f_memory_resize().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_memory_resize()
 * @see f_string_dynamic_resize()
 *
 * @see f_accounts_append()
 * @see f_accounts_decimate_by()
 * @see f_accounts_resize()
 * @see f_accountss_append()
 * @see f_accountss_decrease_by()
 * @see f_accountss_increase()
 * @see f_accountss_increase_by()
 * @see f_accountss_resize()
 */
#if !defined(_di_f_accounts_resize_) || !defined(_di_f_accounts_append_) || !defined(_di_f_accounts_decimate_by_) || !defined(_di_f_accountss_append_) || !defined(_di_f_accountss_decrease_by_) || !defined(_di_f_accountss_increase_) || !defined(_di_f_accountss_increase_by_) || !defined(_di_f_accountss_resize_)
  extern f_status_t private_f_accounts_resize(const f_number_unsigned_t length, f_accounts_t *accounts) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_accounts_resize_) || !defined(_di_f_accounts_append_) || !defined(_di_f_accounts_decimate_by_) || !defined(_di_f_accountss_append_) || !defined(_di_f_accountss_decrease_by_) || !defined(_di_f_accountss_increase_) || !defined(_di_f_accountss_increase_by_) || !defined(_di_f_accountss_resize_)

/**
 * Private implementation for resizing the accountss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to adjust to.
 * @param accountss
 *   The accountss array to adjust.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 *   Errors (with error bit) from: f_string_dynamic_adjust().
 *
 * @see f_memory_adjust()
 * @see f_string_dynamic_adjust()
 *
 * @see f_accountss_adjust()
 * @see f_accountss_decimate_by()
 */
#if !defined(_di_f_accountss_adjust_) || !defined(_di_f_accountss_decimate_by_)
  extern f_status_t private_f_accountss_adjust(const f_number_unsigned_t length, f_accountss_t *accountss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_accountss_adjust_) || !defined(_di_f_accountss_decimate_by_)

/**
 * Private implementation for resizing the accountss array.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param length
 *   The length to resize to.
 * @param accountss
 *   The accountss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if new length is larger than max array length.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_delete().
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_accountss_decrease_by()
 * @see f_accountss_increase()
 * @see f_accountss_increase_by()
 * @see f_accountss_resize()
 */
#if !defined(_di_f_accountss_decrease_by_) || !defined(_di_f_accountss_increase_) || !defined(_di_f_accountss_increase_by_) || !defined(_di_f_accountss_resize_)
  extern f_status_t private_f_accountss_resize(const f_number_unsigned_t length, f_accountss_t *accountss) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_accountss_decrease_by_) || !defined(_di_f_accountss_increase_) || !defined(_di_f_accountss_increase_by_) || !defined(_di_f_accountss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_account_accounts_h
