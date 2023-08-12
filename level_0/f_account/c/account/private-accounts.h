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
  extern f_status_t private_f_accounts_append_all(const f_accounts_t source, f_accounts_t * const destination) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_accounts_append_) || !defined(_di_f_accounts_append_all_) || !defined(_di_f_accountss_append_all_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_account_accounts_h
