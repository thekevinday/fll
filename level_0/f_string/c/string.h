/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides string capabilities.
 *
 * It is highly recommended that all string arrays are set to a max size of f_string_length_t_size.
 * Any calculations against the length (aka: string.used) can always perform (A < B) operators such that the B is f_string_length_t_size + 1 without integer overflow.
 */
#ifndef _F_string_h
#define _F_string_h

// libc includes
#include <string.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/type.h>

// fll-0 string includes
#include <level_0/string-common.h>
#include <level_0/string_dynamic.h>
#include <level_0/string_map.h>
#include <level_0/string_quantity.h>
#include <level_0/string_range.h>
#include <level_0/string_tuple.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_string_has_empty_
  const static f_string_t f_string_empty_s = "";
#endif // _di_f_string_has_empty_

#ifndef _di_f_string_has_eol_
  const static f_string_t f_string_eol_s = f_string_eol;
#endif // _di_f_string_has_eol_

#ifndef _di_f_string_has_placeholder_
  const static f_string_t f_string_placeholder_s = f_string_placeholder;
#endif // _di_f_string_has_placeholder_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_h
