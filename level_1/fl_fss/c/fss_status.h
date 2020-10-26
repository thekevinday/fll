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
 * @fixme this can be moved into level_0 because level_0/status is now a special case that can be included by other level_0 projects.
 */
#ifndef _FL_fss_status_h
#define _FL_fss_status_h

// fll-0 includes
#include <level_0/status.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
  FL_fss_status_code_first = F_status_code_last + 1,

  #ifndef _di_FL_fss_status_error_
    FL_fss_format,
    FL_fss_format_eos,
  #endif // _di_FL_fss_status_error_

  #ifndef _di_FL_fss_status_warning_
    FL_fss_accepted_invalid,
    FL_fss_accepted_invalid_eos,
    FL_fss_header_not,
    FL_fss_header_not_eos,
  #endif // _di_FL_fss_status_warning_

  #ifndef _di_FL_fss_status_success_
    FL_fss_found_content,
    FL_fss_found_object,
    FL_fss_found_object_content_not,
    FL_fss_found_content_not,
    FL_fss_found_object_not,
  #endif // _di_FL_fss_status_success_

  #ifndef _di_FL_fss_status_codes_
    FL_fss_found_comment,
  #endif // _di_FL_fss_status_codes_

  FL_fss_status_code_last,
}; // enum

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_status_h
