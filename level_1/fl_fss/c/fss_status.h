/**
 * FLL - Level 1
 *
 * Project: Strings
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides fss-specific status definitions.
 *
 * Warning: changing status codes will break abi, so recompile every file that includes and uses these error codes when this gets changed.
 */
#ifndef _FL_fss_status_h
#define _FL_fss_status_h

// fll-0 includes
#include <level_0/status.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
  fl_fss_status_start = f_last_status_code,

  #ifndef _di_fl_fss_status_error_
    fl_fss_invalid_format,
    fl_fss_invalid_format_eos,
  #endif // _di_fl_fss_status_error_

  #ifndef _di_fl_fss_status_warning_
    fl_fss_no_header,
    fl_fss_accepted_but_invalid,
    fl_fss_no_header_eos,
    fl_fss_accepted_but_invalid_eos,
  #endif // _di_fl_fss_status_warning_

  #ifndef _di_fl_fss_status_success_
    fl_fss_found_object,
    fl_fss_found_content,
    fl_fss_found_no_object,
    fl_fss_found_no_content,
    fl_fss_found_object_no_content, // for the case where an object is found but no content could possibly exist
  #endif // _di_fl_fss_status_success_

  #ifndef _di_fl_fss_status_codes_
    fl_fss_found_comment,
  #endif // _di_fl_fss_status_codes_

  fl_fss_last_error_code,
}; // enum

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_status_h
