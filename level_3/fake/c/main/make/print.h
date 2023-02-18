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
 * Print operate break verbose message.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 * @param arguments
 *   The arguments passed to the break operation.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_make_print_operate_break_verbose_
  extern f_status_t fake_make_print_operate_break_verbose(fake_setting_t * const setting, const fl_print_t print, const f_string_statics_t arguments);
#endif // _di_fake_make_print_operate_break_verbose_

/**
 * Print operate copy verbose message.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.status.
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
 */
#ifndef _di_fake_make_print_operate_copy_verbose_
  extern f_status_t fake_make_print_operate_copy_verbose(fake_setting_t * const setting, const fl_print_t print, const bool clone, const f_string_static_t source, const f_string_static_t destination);
#endif // _di_fake_make_print_operate_copy_verbose_

/**
 * Print operate define verbose message.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 * @param variable
 *   The environment variable name.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_make_print_operate_define_verbose_
  extern f_status_t fake_make_print_operate_define_verbose(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t variable);
#endif // _di_fake_make_print_operate_define_verbose_

/**
 * Print operate delete verbose message.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.status.
 * @param print
 *   The output structure to print to.
 * @param path
 *   The path or file that is deleted.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fake_make_print_operate_delete_verbose_
  extern f_status_t fake_make_print_operate_delete_verbose(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path);
#endif // _di_fake_make_print_operate_delete_verbose_

/**
 * Print operate file or directory not found verbose message.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.status.
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
 */
#ifndef _di_fake_make_print_operate_file_not_found_verbose_
  extern f_status_t fake_make_print_operate_file_not_found_verbose(fake_setting_t * const setting, const fl_print_t print, const bool is_directory, const f_string_static_t file);
#endif // _di_fake_make_print_operate_file_not_found_verbose_

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

/**
 * Print verbose program message.
 *
 * @param setting
 *   The main program settings.
 *   (Must be of type fake_setting_t.)
 *
 *   This does not alter setting.status.
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
 */
#ifndef _di_fake_make_print_program_verbose_
  extern f_status_t fake_make_print_program_verbose(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t program, const f_string_statics_t arguments);
#endif // _di_fake_make_print_program_verbose_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_make_print_h
