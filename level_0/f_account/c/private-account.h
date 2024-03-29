/**
 * FLL - Level 0
 *
 * Project: Account
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_account_h
#define _PRIVATE_F_account_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private helper for converting an entire "struct passwd" to a complete f_account_t.
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param passwd
 *   The password structure.
 * @param passwd_length
 *   The length of the password structure buffer.
 * @param account
 *   This is replaced with by the account information.
 *   All strings will be NULL terminated.
 *   This assumes that all strings in account have their used set to the desired length, such as 0.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_string_dynamic_resize()
 */
#if !defined(_di_f_account_by_name_) || !defined(_di_f_account_by_id_)
  extern f_status_t private_f_account_from_passwd(const struct passwd password, const f_array_length_t password_length, f_account_t * const account) F_attribute_visibility_internal_d;
#endif // !defined(_di_f_account_by_name_) || !defined(_di_f_account_by_id_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_account_h
