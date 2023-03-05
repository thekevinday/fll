/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides make verbose print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_make_print_verbose_h
#define _fake_make_print_verbose_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print operate break verbose message.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.state.status.
 * @param print
 *   The output structure to print to.
 * @param arguments
 *   The arguments where the first argument, if defined, is the exiting as string.
 *   Set arguments.used to 0 to use the default "success" exiting as string.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_verbose_operate_break_
  extern f_status_t fake_make_print_verbose_operate_break(fake_setting_t * const setting, const fl_print_t print, const f_string_statics_t arguments);
#endif // _di_fake_make_print_verbose_operate_break_

/**
 * Print operate copy verbose message.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.state.status.
 * @param print
 *   The output structure to print to.
 * @param clone
 *   If TRUE, then this is a clone operation.
 *   If FALSE< then this is a copy operation.
 * @param source
 *   The source to copy from.
 * @param destination
 *   The destination to copy to.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_verbose_operate_copy_
  extern f_status_t fake_make_print_verbose_operate_copy(fake_setting_t * const setting, const fl_print_t print, const bool clone, const f_string_static_t source, const f_string_static_t destination);
#endif // _di_fake_make_print_verbose_operate_copy_

/**
 * Print operate define verbose message.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.state.status.
 * @param print
 *   The output structure to print to.
 * @param variable
 *   The environment variable name.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_verbose_operate_define_
  extern f_status_t fake_make_print_verbose_operate_define(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t variable);
#endif // _di_fake_make_print_verbose_operate_define_

/**
 * Print operate delete verbose message.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.state.status.
 * @param print
 *   The output structure to print to.
 * @param path
 *   The path or file that is deleted.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_verbose_operate_delete_
  extern f_status_t fake_make_print_verbose_operate_delete(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path);
#endif // _di_fake_make_print_verbose_operate_delete_

/**
 * Print operate exiting as verbose message.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.state.status.
 * @param print
 *   The output structure to print to.
 * @param arguments
 *   The arguments where the first argument, if defined, is the exiting as string.
 *   Set arguments.used to 0 to use the default "success" exiting as string.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_verbose_operate_exiting_as_
  extern f_status_t fake_make_print_verbose_operate_exiting_as(fake_setting_t * const setting, const fl_print_t print, const f_string_statics_t arguments);
#endif // _di_fake_make_print_verbose_operate_exiting_as_

/**
 * Print operate file or directory not found verbose message.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.state.status.
 * @param print
 *   The output structure to print to.
 * @param is_directory
 *   If TRUE, then the file is type directory.
 *   If FALSE, then the file is type regular.
 * @param file
 *   The file or directory path or name.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_verbose_operate_file_not_found_
  extern f_status_t fake_make_print_verbose_operate_file_not_found(fake_setting_t * const setting, const fl_print_t print, const bool is_directory, const f_string_static_t file);
#endif // _di_fake_make_print_verbose_operate_file_not_found_

/**
 * Print verbose program message.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.state.status.
 * @param print
 *   The output structure to print to.
 * @param program
 *   The program name.
 * @param arguments
 *   The arguments pass to the program.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_verbose_operate_program_
  extern f_status_t fake_make_print_verbose_operate_program(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t program, const f_string_statics_t arguments);
#endif // _di_fake_make_print_verbose_operate_program_

/**
 * Print verbose message about setting failure state.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.state.status.
 * @param print
 *   The output structure to print to.
 * @param fail
 *   The failure state code being set to.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_verbose_operate_set_failure_state_
  extern f_status_t fake_make_print_verbose_operate_set_failure_state(fake_setting_t * const setting, const fl_print_t print, const uint8_t fail);
#endif // _di_fake_make_print_verbose_operate_set_failure_state_

/**
 * Print verbose message about setting the file mode.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.state.status.
 * @param print
 *   The output structure to print to.
 * @param path
 *   The file path having the mode changed.
 * @param mode
 *   The mode being changed to.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_verbose_operate_set_mode_
  extern f_status_t fake_make_print_verbose_operate_set_mode(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path, const mode_t mode);
#endif // _di_fake_make_print_verbose_operate_set_mode_

/**
 * Print verbose message about changing the project path.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.state.status.
 * @param print
 *   The output structure to print to.
 * @param path
 *   The path being changed to.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_verbose_operate_set_path_
  extern f_status_t fake_make_print_verbose_operate_set_path(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path);
#endif // _di_fake_make_print_verbose_operate_set_path_

/**
 * Print verbose message about setting owner or group.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.state.status.
 * @param print
 *   The output structure to print to.
 * @param what
 *   Bitwise flags tweaking the message printed.
 *   - 0x1 = When set, print as recursive; When not set, print as non-recursive.
 *   - 0x2 = When set, print as Owner; When not set, print as Group.
 * @param role
 *   A string representing the owner or group name.
 * @param id
 *   The uid_t or gid_t representing the owner or group.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_verbose_operate_set_role_
  extern f_status_t fake_make_print_verbose_operate_set_role(fake_setting_t * const setting, const fl_print_t print, const uint8_t what, f_string_static_t role, f_number_unsigned_t id);
#endif // _di_fake_make_print_verbose_operate_set_role_

/**
 * Print verbose message about create a symbolic link.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.state.status.
 * @param print
 *   The output structure to print to.
 * @param source
 *   A string the symbolic link is from.
 * @param destination
 *   A string the symbolic link is to.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_verbose_operate_symbolic_link_
  extern f_status_t fake_make_print_verbose_operate_symbolic_link(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t source, const f_string_static_t destination);
#endif // _di_fake_make_print_verbose_operate_symbolic_link_

/**
 * Print verbose message about touching a file.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.state.status.
 * @param print
 *   The output structure to print to.
 * @param path
 *   The file path being touched.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_fake_make_print_verbose_operate_touch_
  extern f_status_t fake_make_print_verbose_operate_touch(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path);
#endif // _di_fake_make_print_verbose_operate_touch_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_make_print_verbose_h
