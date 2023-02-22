/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _fake_make_print_h
#define _fake_make_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print the now making message.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 * @param fakefile
 *   The name or path of the file that is empty.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_make_print_now_making_
  extern f_status_t fake_make_print_now_making(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t fakefile);
#endif // _di_fake_make_print_now_making_

/**
 * Print the processing section message.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 * @param buffer
 *   The string containing the section name.
 * @param section
 *   The section structure containing the section name range.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_make_print_processing_section_
  extern f_status_t fake_make_print_processing_section(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t buffer, const f_fss_named_t section);
#endif // _di_fake_make_print_processing_section_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_make_print_h
