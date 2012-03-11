/* FLL - Level 2
 * Project:       FSS
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * This is the fss-0002 implementation
 */
#ifndef _FLL_fss_basic_list_h
#define _FLL_fss_basic_list_h

// fll-0 includes
#include <level_0/strings.h>
#include <level_0/errors.h>
#include <level_0/types.h>
#include <level_0/memory.h>
#include <level_0/fss.h>

// fll-1 includes
#include <level_1/fss.h>
#include <level_1/fss_macro.h>
#include <level_1/fss_errors.h>
#include <level_1/fss_basic_list.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fll_fss_basic_list_read_
  // read an fss-0002 object and then content
  extern f_return_status fll_fss_basic_list_read(f_dynamic_string *buffer, f_string_location *input, f_fss_objects *objects, f_fss_contents *contents);
#endif // _di_fll_fss_basic_list_read_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_fss_basic_list_h
