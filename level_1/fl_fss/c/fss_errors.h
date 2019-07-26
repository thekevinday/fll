/**
 * FLL - Level 1
 *
 * Project: Strings
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides fss-specific error definitions.
 *
 * Warning: changing error codes will break abi, so recompile every file that includes and uses these error codes when this gets changed.
 */
#ifndef _FL_fss_errors_h
#define _FL_fss_errors_h

// fll-0 includes
#include <level_0/errors.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_macro_test_for_fss_errors_
  #define fl_macro_test_for_fss_errors(potential_error) \
    ( !f_macro_test_for_non_errors(potential_error)  && \
      potential_error != fl_fss_no_header            && \
      potential_error != fl_fss_no_header_eos        && \
      potential_error != fl_fss_accepted_but_invalid && \
      potential_error != fl_fss_accepted_but_invalid_eos )
#endif // _di_fl_macro_test_for_fss_errors_

enum {
  fl_fss_error_start = f_last_error_code,

  #ifndef _di_fl_fss_errors_error_
    fl_fss_invalid_format,
    fl_fss_invalid_format_eos,
  #endif // _di_fl_fss_errors_error_

  #ifndef _di_fl_fss_errors_warning_
    fl_fss_no_header,
    fl_fss_accepted_but_invalid,
    fl_fss_no_header_eos,
    fl_fss_accepted_but_invalid_eos,
  #endif // _di_fl_fss_errors_warning_

  #ifndef _di_fl_fss_errors_success_
    fl_fss_found_object,
    fl_fss_found_content,
    fl_fss_found_no_object,
    fl_fss_found_no_content,
    fl_fss_found_object_no_content, // for the case where an object is found but no content could possibly exist
  #endif // _di_fl_fss_errors_success_
}; // enum

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_errors_h
