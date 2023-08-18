/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides print message functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_print_message_h
#define _fake_print_message_h

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Print a message about building.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param build_arguments
 *   (optional) The build arguments.
 * @param setting_build
 *   The build setting data.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_fake_print_message_building_
  extern f_status_t fake_print_message_building(fl_print_t * const print, const f_string_statics_t * const build_arguments, fake_build_setting_t * const setting_build);
#endif // _di_fake_print_message_building_

/**
 * Print a message about deleting all files.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 * @see fake_print_common_simple_variable()
 */
#ifndef _di_fake_print_message_delete_all_files_
  extern f_status_t fake_print_message_delete_all_files(fl_print_t * const print);
#endif // _di_fake_print_message_delete_all_files_

/**
 * Print a message about generating skeleton.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 * @see fake_print_common_simple()
 */
#ifndef _di_fake_print_message_generating_skeleton_
  extern f_status_t fake_print_message_generating_skeleton(fl_print_t * const print);
#endif // _di_fake_print_message_generating_skeleton_

/**
 * Print help.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_flush()
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see f_print_dynamic_raw()
 * @see fl_print_format()
 * @see fll_program_print_help_header()
 * @see fll_program_print_help_option()
 * @see fll_program_print_help_option_other()
 * @see fll_program_print_help_option_standard()
 * @see fll_program_print_help_usage()
 */
#ifndef _di_fake_print_message_help_
  extern f_status_t fake_print_message_help(fl_print_t * const print);
#endif // _di_fake_print_message_help_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_print_message_h
