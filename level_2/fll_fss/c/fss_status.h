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
#include <fll/level_0/conversion.h>
#include <fll/level_0/status.h>
#include <fll/level_0/fss.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/type.h>

// fll-1 includes
#include <fll/level_1/fss.h>
#include <fll/level_1/fss_basic.h>
#include <fll/level_1/fss_status.h>
#include <fll/level_1/status.h>
#include <fll/level_1/string.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_status_string_
  #ifndef _di_fll_fss_status_error_
    #define fll_fss_status_string_format "FL_fss_format"
    #define fll_fss_status_string_format_length 13

    #define fll_fss_status_string_format_eos "FL_fss_format_eos"
    #define fll_fss_status_string_format_eos_length 17
  #endif // _di_fll_fss_status_error_

  #ifndef _di_fll_fss_status_warning_
    #define fll_fss_status_string_header_not "FL_fss_header_not"
    #define fll_fss_status_string_header_not_length 17

    #define fll_fss_status_string_accepted_invalid "FL_fss_accepted_invalid"
    #define fll_fss_status_string_accepted_invalid_length 23

    #define fll_fss_status_string_header_not_eos "FL_fss_header_not_eos"
    #define fll_fss_status_string_header_not_eos_length 21

    #define fll_fss_status_string_accepted_invalid_eos "FL_fss_accepted_invalid_eos"
    #define fll_fss_status_string_accepted_invalid_eos_length 27
  #endif // _di_fll_fss_status_warning_

  #ifndef _di_fll_fss_status_success_
    #define fll_fss_status_string_found_object "FL_fss_found_object"
    #define fll_fss_status_string_found_object_length 19

    #define fll_fss_status_string_found_content "FL_fss_found_content"
    #define fll_fss_status_string_found_content_length 20

    #define fll_fss_status_string_found_object_not "FL_fss_found_object_not"
    #define fll_fss_status_string_found_object_not_length 23

    #define fll_fss_status_string_found_content_not "FL_fss_found_content_not"
    #define fll_fss_status_string_found_content_not_length 24

    #define fll_fss_status_string_found_object_content_not "FL_fss_found_object_content_not"
    #define fll_fss_status_string_found_object_content_not_length 31
  #endif // _di_fll_fss_status_success_

  #ifndef _di_fll_fss_status_codes_
    #define fll_fss_status_string_found_comment "FL_fss_found_comment"
    #define fll_fss_status_string_found_comment_length 14
  #endif // _di_fll_fss_status_codes_

  #define fll_fss_status_string_status_code_first "FL_fss_status_code_first"
  #define fll_fss_status_string_status_code_first_length 24

  #define fll_fss_status_string_status_code_last "FL_fss_status_code_last"
  #define fll_fss_status_string_status_code_last_length 22
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
 *   F_none on success.
 *   F_data_not if string is empty.
 *   F_data (with error bit) if not found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_conversion_character_is_decimal().
 */
#ifndef _di_fll_fss_status_from_string_
  extern f_status_t fll_fss_status_from_string(const f_string_t string, f_status_t *code);
#endif // _di_fll_fss_status_to_string_

/**
 * Convert code codes to their string equivalents.
 *
 * @param code
 *   The code to process.
 * @param string
 *   The code name that represents the given code.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: fl_status_to_string().
 *
 * @see fl_status_to_string()
 */
#ifndef _di_fll_fss_status_to_string_
  extern f_status_t fll_fss_status_to_string(const f_status_t code, f_string_t *string);
#endif // _di_fll_status_to_string_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_fss_status_h
