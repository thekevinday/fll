/**
 * FLL - Level 2
 *
 * Project: FSS
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Provides FSS status code functions, such as those that translate status codes into strings.
 */
#ifndef _FLL_fss_status_string_h
#define _FLL_fss_status_string_h

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/conversion.h>
#include <fll/level_0/fss.h>
#include <fll/level_0/status_string.h>

// FLL-1 includes.
#include <fll/level_1/string.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_status_string_
  #ifndef _di_fll_fss_status_error_
    #define FLL_fss_status_format_s     "F_fss_format"
    #define FLL_fss_status_format_eos_s "F_fss_format_eos"

    #define FLL_fss_status_format_s_length     12
    #define FLL_fss_status_format_eos_s_length 16

    extern const f_string_static_t fll_fss_status_format_s;
    extern const f_string_static_t fll_fss_status_format_eos_s;
  #endif // _di_fll_fss_status_error_

  #ifndef _di_fll_fss_status_warning_
    #define FLL_fss_status_accepted_invalid_s     "F_fss_accepted_invalid"
    #define FLL_fss_status_accepted_invalid_eos_s "F_fss_accepted_invalid_eos"

    #define FLL_fss_status_accepted_invalid_s_length     22
    #define FLL_fss_status_accepted_invalid_eos_s_length 26

    extern const f_string_static_t fll_fss_status_accepted_invalid_s;
    extern const f_string_static_t fll_fss_status_accepted_invalid_eos_s;
  #endif // _di_fll_fss_status_warning_

  #ifndef _di_fll_fss_status_success_
    #define FLL_fss_status_found_content_s            "F_fss_found_content"
    #define FLL_fss_status_found_content_not_s        "F_fss_found_content_not"
    #define FLL_fss_status_found_object_s             "F_fss_found_object"
    #define FLL_fss_status_found_object_content_not_s "F_fss_found_object_content_not"
    #define FLL_fss_status_found_object_not_s         "F_fss_found_object_not"

    #define FLL_fss_status_found_content_s_length            19
    #define FLL_fss_status_found_content_not_s_length        23
    #define FLL_fss_status_found_object_s_length             18
    #define FLL_fss_status_found_object_content_not_s_length 30
    #define FLL_fss_status_found_object_not_s_length         22

    extern const f_string_static_t fll_fss_status_found_content_s;
    extern const f_string_static_t fll_fss_status_found_content_not_s;
    extern const f_string_static_t fll_fss_status_found_object_s;
    extern const f_string_static_t fll_fss_status_found_object_content_not_s;
    extern const f_string_static_t fll_fss_status_found_object_not_s;
  #endif // _di_fll_fss_status_success_

  #ifndef _di_fll_fss_status_codes_
    #define FLL_fss_status_found_comment_s "F_fss_found_comment"

    #define FLL_fss_status_found_comment_s_length 19

    extern const f_string_static_t fll_fss_status_found_comment_s;
  #endif // _di_fll_fss_status_codes_

  #define FLL_fss_status_status_code_first_s "F_fss_status_code_first"
  #define FLL_fss_status_status_code_last_s  "F_fss_status_code_last"

  #define FLL_fss_status_status_code_first_s_length 23
  #define FLL_fss_status_status_code_last_s_length  22

  extern const f_string_static_t fll_fss_status_status_code_first_s;
  extern const f_string_static_t fll_fss_status_status_code_last_s;
#endif // _di_fll_fss_status_string_

/**
 * Convert FSS status codes from their string equivalents to a status code.
 *
 * Error, warning, and signal flags will not be assigned to the code.
 *
 * This processes the string until either a match or NULL is reached.
 *
 * @param name
 *   The status name to process.
 * @param code
 *   The status number a matched string represents.
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
#ifndef _di_fll_fss_status_string_from_
  extern f_status_t fll_fss_status_string_from(const f_string_static_t name, f_status_t * const code);
#endif // _di_fll_fss_status_string_from_

/**
 * Convert code codes to their string equivalents.
 *
 * @param code
 *   The status number to process.
 * @param name
 *   The status name that represents the given code.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_status_string_to().
 *
 * @see f_status_string_to()
 */
#ifndef _di_fll_fss_status_string_to_
  extern f_status_t fll_fss_status_string_to(const f_status_t code, f_string_static_t * const name);
#endif // _di_fll_fss_status_string_to_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_fss_status_string_h
