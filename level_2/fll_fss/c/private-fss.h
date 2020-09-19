/**
 * FLL - Level 2
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_FLL_fss_h
#define _PRIVATE_FLL_fss_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of fll_fss_identify().
 *
 * Intended to be shared to each of the different implementation variations.
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
 *   Errors (with error bit) from: fl_conversion_string_to_hexidecimal_unsigned().
 *
 * @see fll_fss_identify()
 * @see fll_fss_identify_file()
 */
#if !defined(_di_fll_fss_identify_) || !defined(_di_fll_fss_identify_file_)
  extern f_return_status private_fll_fss_identify(const f_string_static_t buffer, f_fss_header_t *header) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fll_fss_identify_) || !defined(_di_fll_fss_identify_file_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FLL_fss_h
