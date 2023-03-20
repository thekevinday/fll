/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides make print message functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_make_print_message_h
#define _fake_make_print_message_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print the now making message.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param fakefile
 *   The name or path of the file that is empty.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_make_print_message_now_making_
  extern f_status_t fake_make_print_message_now_making(fl_print_t * const print, const f_string_static_t fakefile);
#endif // _di_fake_make_print_message_now_making_

/**
 * Print the processing section message.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param buffer
 *   The string containing the section name.
 * @param section
 *   The section structure containing the section name range.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_make_print_message_processing_section_
  extern f_status_t fake_make_print_message_processing_section(fl_print_t * const print, const f_string_static_t buffer, const f_fss_named_t section);
#endif // _di_fake_make_print_message_processing_section_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_make_print_message_h
