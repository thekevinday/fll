/**
 * FLL - Level 1
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is the fss-0002 implementation.
 */
#ifndef _FL_fss_basic_list_h
#define _FL_fss_basic_list_h

// libc includes
#include <ctype.h>
#include <string.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/fss.h>
#include <level_0/memory.h>
#include <level_0/strings.h>
#include <level_0/types.h>
#include <level_0/utf.h>

// fll-1 includes
#include <level_1/fss.h>
#include <level_1/fss_basic.h>
#include <level_1/fss_status.h>
#include <level_1/fss_macro.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_basic_list_object_read_
  /**
   * read an fss-0002 object.
   */
  extern f_return_status fl_fss_basic_list_object_read(f_dynamic_string *buffer, f_string_location *input, f_fss_object *found);
#endif // _di_fl_fss_basic_list_object_read_

#ifndef _di_fl_fss_basic_list_content_read_
  /**
   * read an fss-0002 content.
   */
  extern f_return_status fl_fss_basic_list_content_read(f_dynamic_string *buffer, f_string_location *input, f_fss_content *found);
#endif // _di_fl_fss_basic_list_content_read_

#ifndef _di_fl_fss_basic_list_object_write_
  /**
   * write an fss-0002 object.
   */
  extern f_return_status fl_fss_basic_list_object_write(const f_dynamic_string object, f_string_location *input, f_dynamic_string *buffer);
#endif // _di_fl_fss_basic_list_object_write_

#ifndef _di_fl_fss_basic_list_content_write_
  /**
   * write an fss-0002 content.
   */
  extern f_return_status fl_fss_basic_list_content_write(const f_dynamic_string content, f_string_location *input, f_dynamic_string *buffer);
#endif // _di_fl_fss_basic_list_content_write_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_basic_list_h
