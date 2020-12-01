/**
 * FLL - Level 0
 *
 * Project: Account
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines common data to be used for/by account related functionality.
 *
 * This is auto-included by account.h and should not need to be explicitly included.
 */
#ifndef _F_account_common_h
#define _F_account_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Custom defines for f_account.
 *
 * f_account_pwd_length_fallback_first: provide a fallback max length for when sysconf(_SC_GETPW_R_SIZE_MAX) return -1 (aka: infinite).
 * f_account_pwd_length_fallback_second: provide a fallback max length for when f_account_pwd_length_fallback_first is too small.
 */
#ifndef _di_f_account_defines_
  #define f_account_pwd_length_fallback_first  8192
  #define f_account_pwd_length_fallback_second 32767
#endif // _di_f_account_defines_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_account_common_h
