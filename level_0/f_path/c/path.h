/**
 * FLL - Level 0
 *
 * Project: Path
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provide path-related functionality.
 */
#ifndef _F_path_h
#define _F_path_h

// fll-0 includes

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Standard path defines.
 *
 * The path separator, intended to be represented as a single character.
 *
 * The length is intended to provide a UTF-8 compatible width and therefore represents bytes and not characters.
 * A length of 1 = 1-byte wide character, a length of 4 = 4-byte wide character.
 */
#ifndef _di_f_path_defines_
  #define f_path_separator "/"
  #define f_path_separator_length 1
#endif // _di_f_path_defines_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_path_h
