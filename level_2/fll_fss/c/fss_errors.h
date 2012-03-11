/* FLL - Level 2
 * Project:       FSS
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * This provides fss error code translation.
 */
#ifndef _FLL_fss_errors_h
#define _FLL_fss_errors_h

// fll-0 includes
#include <level_0/strings.h>
#include <level_0/errors.h>
#include <level_0/types.h>
#include <level_0/memory.h>
#include <level_0/fss.h>

// fll-1 includes
#include <level_1/errors.h>
#include <level_1/fss.h>
#include <level_1/fss_macro.h>
#include <level_1/fss_errors.h>
#include <level_1/fss_basic.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fll_fss_errors_to_string_
  // Convert error codes to their string equivalents.
  extern f_return_status fll_fss_errors_to_string(const f_status error, f_string *string);
#endif // _di_fll_errors_to_string_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_fss_errors_h
