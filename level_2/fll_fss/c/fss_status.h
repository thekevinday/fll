/**
 * FLL - Level 2
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This provides fss status code translation.
 */
#ifndef _FLL_fss_status_h
#define _FLL_fss_status_h

// fll-0 includes
#include <level_0/conversion.h>
#include <level_0/status.h>
#include <level_0/fss.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/type.h>

// fll-1 includes
#include <level_1/fss.h>
#include <level_1/fss_basic.h>
#include <level_1/fss_status.h>
#include <level_1/fss_macro.h>
#include <level_1/status.h>
#include <level_1/string.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_status_string_
  #ifndef _di_fll_fss_status_error_
    #define fll_fss_status_string_invalid_format "fl_fss_invalid_format"
    #define fll_fss_status_string_invalid_format_length 22

    #define fll_fss_status_string_invalid_format_eos "fl_fss_invalid_format_eos"
    #define fll_fss_status_string_invalid_format_eos_length 26
  #endif // _di_fll_fss_status_error_

  #ifndef _di_fll_fss_status_warning_
    #define fll_fss_status_string_no_header "fl_fss_no_header"
    #define fll_fss_status_string_no_header_length 17

    #define fll_fss_status_string_accepted_but_invalid "fl_fss_accepted_but_invalid"
    #define fll_fss_status_string_accepted_but_invalid_length 28

    #define fll_fss_status_string_no_header_eos "fl_fss_no_header_eos"
    #define fll_fss_status_string_no_header_eos_length 21

    #define fll_fss_status_string_accepted_but_invalid_eos "fl_fss_accepted_but_invalid_eos"
    #define fll_fss_status_string_accepted_but_invalid_eos_length 32
  #endif // _di_fll_fss_status_warning_

  #ifndef _di_fll_fss_status_success_
    #define fll_fss_status_string_found_object "fl_fss_found_object"
    #define fll_fss_status_string_found_object_length 20

    #define fll_fss_status_string_found_content "fl_fss_found_content"
    #define fll_fss_status_string_found_content_length 21

    #define fll_fss_status_string_found_no_object "fl_fss_found_no_object"
    #define fll_fss_status_string_found_no_object_length 23

    #define fll_fss_status_string_found_no_content "fl_fss_found_no_content"
    #define fll_fss_status_string_found_no_content_length 24

    #define fll_fss_status_string_found_object_no_content "fl_fss_found_object_no_content"
    #define fll_fss_status_string_found_object_no_content_length 31
  #endif // _di_fll_fss_status_success_

  #ifndef _di_fll_fss_status_codes_
    #define fll_fss_status_string_found_comment "fl_fss_found_comment"
    #define fll_fss_status_string_found_comment_length 15
  #endif // _di_fll_fss_status_codes_

  #define fll_fss_status_string_status_code_first "fl_fss_status_code_first"
  #define fll_fss_status_string_status_code_first_length 25

  #define fll_fss_status_string_status_code_last "fl_fss_status_code_last"
  #define fll_fss_status_string_status_code_last_length 23
#endif // _di_fll_fss_status_string_

/**
 * Convert FSS status codes from their string equivalents to a status code.
 *
 * Error, warning, and signal flags will not be assigned to the code.
 *
 * This process the string until either a match or NULL is reached.
 *
 * @param string
 *   The code name to process.
 * @param code
 *   The code code a matched string represents.
 *
 * @return
 *   f_none on success.
 *   f_no_data if string is empty.
 *   f_invalid_data (with error bit) if not found.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fll_status_from_string
 */
#ifndef _di_fll_fss_status_from_string_
  extern f_return_status fll_fss_status_from_string(const f_string string, f_status *code);
#endif // _di_fll_fss_status_to_string_

#ifndef _di_fll_fss_status_to_string_
  /**
   * Convert code codes to their string equivalents.
   */
  extern f_return_status fll_fss_status_to_string(const f_status code, f_string *string);
#endif // _di_fll_status_to_string_

#ifndef _di_fll_fss_status_is_error_
  /**
   * Returns true or false depending on whether the standard context of the code code represents an code.
   * Keep in mind that many of the code codes are context-specific and may be reported as an code here when it is in fact not an code.
   */
  extern f_return_status fll_fss_status_is_error(const f_status code);
#endif // _di_fll_fss_status_is_error_

#ifndef _di_fll_fss_status_is_warning_
  /**
   * Returns true or false depending on whether the standard context of the code code represents a warning.
   * Keep in mind that many of the code codes are context-specific and may be reported as a warning here when it is in fact not a warning.
   */
  extern f_return_status fll_fss_status_is_warning(const f_status code);
#endif // _di_fll_fss_status_is_warning_

#ifndef _di_fll_fss_status_is_fine_
  /**
   * Returns true or false depending on whether the standard context of the code code represents an normal return status and not an code.
   * Keep in mind that many of the code codes are context-specific and may be reported as "fine" here when it is in fact not fine.
   */
  extern f_return_status fll_fss_status_is_fine(const f_status code);
#endif // _di_fll_fss_status_is_fine_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_fss_status_h
