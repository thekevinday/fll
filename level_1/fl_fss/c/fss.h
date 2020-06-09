/**
 * FLL - Level 1
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _FL_fss_h
#define _FL_fss_h

// libc includes
#include <ctype.h>
#include <string.h>

// fll-0 includes
#include <level_0/conversion.h>
#include <level_0/status.h>
#include <level_0/file.h>
#include <level_0/fss.h>
#include <level_0/string.h>
#include <level_0/type.h>
#include <level_0/utf.h>

// fll-1 includes
#include <level_1/fss_status.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Identify FSS type from a buffered string.
 *
 * @param buffer
 *   The string to process.
 * @param header
 *   The header data to populate with results of this function.
 *
 * @return
 *   F_none on success
 *   FL_fss_header_not if no header is found.
 *   FL_fss_accepted_invalid (with warning bit) if header is technically invalid but can be identified.
 *   FL_fss_header_not (with error bit) if the an error occurred prior to identifying a valid header.
 *
 *   Errors from (with error bit): f_conversion_string_to_hexidecimal_unsigned().
 */
#ifndef _di_fl_fss_identify_
  extern f_return_status fl_fss_identify(const f_string_static buffer, f_fss_header *header);
#endif // _di_fl_fss_identify_

/**
 * Identify FSS type from a file.
 *
 * @param file
 *   The file information.
 * @param header
 *   The header data to populate with results of this function.
 *
 * @return
 *   F_none on success.
 *   FL_fss_header_not if no header is found.
 *   FL_fss_accepted_invalid (with warning bit) if header is technically invalid but can be identified.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   FL_fss_header_not (with error bit) if the an error occurred prior to identifying a valid header.
 *
 *   Errors from (with error bit): f_conversion_string_to_hexidecimal_unsigned().
 *   Errors from (with error bit): f_file_read_until().
 *   Errors from (with error bit): f_file_seek().
 *
 * @see f_file_read_until()
 * @see fl_fss_identify()
 */
#ifndef _di_fl_fss_identify_file_
  extern f_return_status fl_fss_identify_file(f_file *file, f_fss_header *header);
#endif // _di_fl_fss_identify_file_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_h
