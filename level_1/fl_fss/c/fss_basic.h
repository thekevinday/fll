/**
 * FLL - Level 1
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is the fss-0000 implementation.
 */
#ifndef _FL_fss_basic_h
#define _FL_fss_basic_h

// libc includes
#include <ctype.h>
#include <string.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/fss.h>
#include <level_0/string.h>
#include <level_0/type.h>
#include <level_0/memory.h>
#include <level_0/utf.h>

// fll-1 includes
#include <level_1/fss.h>
#include <level_1/fss_status.h>
#include <level_1/fss_macro.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_basic_object_read_
  /**
   * read an fss-0000 object.
   */
  extern f_return_status fl_fss_basic_object_read(f_string_dynamic *buffer, f_string_location *input, f_fss_object *found);
#endif // _di_fl_fss_basic_object_read_

#ifndef _di_fl_fss_basic_content_read_
  /**
   * read an fss-0000 content.
   */
  extern f_return_status fl_fss_basic_content_read(f_string_dynamic *buffer, f_string_location *input, f_fss_content *found);
#endif // _di_fl_fss_basic_content_read_

#ifndef _di_fl_fss_basic_object_write_
  /**
   * write an fss-0000 object.
   */
  extern f_return_status fl_fss_basic_object_write(f_string_dynamic *buffer, const f_string_dynamic object, f_string_location *input);
#endif // _di_fl_fss_basic_object_write_

#ifndef _di_fl_fss_basic_content_write_
  /**
   * write an fss-0000 content.
   */
  extern f_return_status fl_fss_basic_content_write(f_string_dynamic *buffer, const f_string_dynamic content, f_string_location *input);
#endif // _di_fl_fss_basic_content_write_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_basic_h
