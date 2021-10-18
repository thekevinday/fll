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
    #define FLL_fss_status_format_s "FL_fss_format"
    #define FLL_fss_status_format_s_length 13

    #define FLL_fss_status_format_eos_s "FL_fss_format_eos"
    #define FLL_fss_status_format_eos_s_length 17
  #endif // _di_fll_fss_status_error_

  #ifndef _di_fll_fss_status_warning_
    #define FLL_fss_status_accepted_invalid_s "FL_fss_accepted_invalid"
    #define FLL_fss_status_accepted_invalid_s_length 23

    #define FLL_fss_status_accepted_invalid_eos_s "FL_fss_accepted_invalid_eos"
    #define FLL_fss_status_accepted_invalid_eos_s_length 27
  #endif // _di_fll_fss_status_warning_

  #ifndef _di_fll_fss_status_success_
    #define FLL_fss_status_found_object_s "FL_fss_found_object"
    #define FLL_fss_status_found_object_s_length 19

    #define FLL_fss_status_found_content_s "FL_fss_found_content"
    #define FLL_fss_status_found_content_s_length 20

    #define FLL_fss_status_found_object_not_s "FL_fss_found_object_not"
    #define FLL_fss_status_found_object_not_s_length 23

    #define FLL_fss_status_found_content_not_s "FL_fss_found_content_not"
    #define FLL_fss_status_found_content_not_s_length 24

    #define FLL_fss_status_found_object_content_not_s "FL_fss_found_object_content_not"
    #define FLL_fss_status_found_object_content_not_s_length 31
  #endif // _di_fll_fss_status_success_

  #ifndef _di_fll_fss_status_codes_
    #define FLL_fss_status_found_comment_s "FL_fss_found_comment"
    #define FLL_fss_status_found_comment_length_s 14
  #endif // _di_fll_fss_status_codes_

  #define FLL_fss_status_status_code_first_s "FL_fss_status_code_first"
  #define FLL_fss_status_status_code_first_s_length 24

  #define FLL_fss_status_status_code_last_s "FL_fss_status_code_last"
  #define FLL_fss_status_status_code_last_s_length 22
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
 *
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
 *
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
