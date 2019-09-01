/**
 * FLL - Level 2
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is the fss-0000 implementation.
 */
#ifndef _FLL_fss_basic_h
#define _FLL_fss_basic_h

// fll-0 includes
#include <level_0/status.h>
#include <level_0/fss.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/types.h>
#include <level_0/utf.h>

// fll-1 includes
#include <level_1/fss.h>
#include <level_1/fss_macro.h>
#include <level_1/fss_status.h>
#include <level_1/fss_basic.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_basic_read_
  /**
   * read an fss-0000 object and then content.
   */
  extern f_return_status fll_fss_basic_read(f_string_dynamic *buffer, f_string_location *input, f_fss_objects *objects, f_fss_contents *contents);
#endif // _di_fll_fss_basic_read_

#ifndef _di_fll_fss_basic_write_
  /**
   * write an fss-0000 object and then content.
   */
  extern f_return_status fll_fss_basic_write(const f_string_dynamic object, const f_string_dynamics contents, f_string_dynamic *buffer);
#endif // _di_fll_fss_basic_write_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_fss_basic_h
