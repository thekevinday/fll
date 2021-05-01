/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_make_h
#define _PRIVATE_make_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Assure that a path is within the project root path.
 *
 * @param main
 *   The main data.
 * @param path
 *   file path to get the real path of.
 * @param main_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 *   The data_make.path_cache will be updated to reflect the full path to this file.
 *
 * @return
 *   F_true if inside the project.
 *   F_false (with error bit) if path exists outside of the root project path.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_assure_inside_project_
  extern f_status_t fake_make_assure_inside_project(const fake_main_t main, const f_string_static_t path, fake_make_data_t *data_make) f_attribute_visibility_internal;
#endif // _di_fake_make_assure_inside_project_

/**
 * Get the group id from either a string representing the number or a string representing the name.
 *
 * @param main
 *   The main data.
 * @param error
 *   The error/warning print data.
 * @param buffer
 *   The string containing the name or number.
 * @param id
 *   The detected group id.
 *
 * @return
 *   F_none on success.
 *   F_exist_not if there is no group by the given name.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_get_id_group_
  f_status_t fake_make_get_id_group(const fake_main_t main, const fll_error_print_t error, const f_string_static_t buffer, gid_t *id) f_attribute_visibility_internal;
#endif // _di_fake_make_get_id_group_

/**
 * Get the mode id from either a string representing the number or a string representing the mode.
 *
 * @param main
 *   The main data.
 * @param error
 *   The error/warning print data.
 * @param buffer
 *   The string containing the name or number.
 * @param mode
 *   The determined mode.
 *   This uses bitwise data.
 * @param replace
 *   The determined modes that are to be replaced, such as: f_file_mode_t_replace_owner.
 *   This uses bitwise data.
 *
 * @return
 *   F_none on success.
 *   F_exist_not if there is no mode by the given name.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_get_id_mode_
  f_status_t fake_make_get_id_mode(const fake_main_t main, const fll_error_print_t error, const f_string_static_t buffer, f_file_mode_t *mode, uint8_t *replace) f_attribute_visibility_internal;
#endif // _di_fake_make_get_id_mode_

/**
 * Get the user id from either a string representing the number or a string representing the name.
 *
 * @param main
 *   The main data.
 * @param error
 *   The error/warning print data.
 * @param buffer
 *   The string containing the name or number.
 * @param id
 *   The detected user id.
 *
 * @return
 *   F_none on success.
 *   F_exist_not if there is no user by the given name.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_get_id_owner_
  f_status_t fake_make_get_id_owner(const fake_main_t main, const fll_error_print_t error, const f_string_static_t buffer, uid_t *id) f_attribute_visibility_internal;
#endif // _di_fake_make_get_id_owner_

/**
 * Find the fake file, load it, validate it, and process it.
 *
 * This will process any additional files as necessary, such as the build settings file.
 *
 * @param main
 *   The main data.
 * @param main_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param status
 *   The return status.
 *
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fake_build_load_setting()
 */
#ifndef _di_fake_make_load_fakefile_
  extern void fake_make_load_fakefile(const fake_main_t main, fake_make_data_t *data_make, f_status_t *status) f_attribute_visibility_internal;
#endif // _di_fake_make_load_fakefile_

/**
 * Load the environment variables into a structure more readily available for using in parameter expansion.
 *
 * @param main
 *   The main data.
 * @param main_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param status
 *   The return status.
 *
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_load_parameters_
  extern void fake_make_load_parameters(const fake_main_t main, fake_make_data_t *data_make, f_status_t *status) f_attribute_visibility_internal;
#endif // _di_fake_make_load_parameters_

/**
 * Execute the make sections and their respective operations.
 *
 * The first section operated on is the 'main' section.
 * The 'settings' section is only loaded into settings and is never operated on.
 *
 * @param main
 *   The main data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_
  extern f_status_t fake_make_operate(fake_main_t *main) f_attribute_visibility_internal;
#endif // _di_fake_make_operate_

/**
 * For a given make section operation, expand the content into an arguments array for that operation.
 *
 * This prints errors via data_make.error.
 *
 * @param main
 *   The main data.
 * @param section_name
 *   The section name.
 * @param operation
 *   The operation being performed.
 * @param operation_name
 *   The operation name.
 * @param content
 *   The content array.
 * @param quoteds
 *   The array of quoted associated with the content.
 * @param main_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The expanded arguments.
 * @param status
 *   The return status.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_expand_
  extern void fake_make_operate_expand(const fake_main_t main, const f_string_range_t section_name, const f_array_length_t operation, const f_string_static_t operation_name, const f_fss_content_t content, const f_fss_quotes_t quoteds, fake_make_data_t *data_make, f_string_dynamics_t *arguments, f_status_t *status) f_attribute_visibility_internal;
#endif // _di_fake_make_operate_expand_

/**
 * Perform the expand operation, specifically for the environment variables.
 *
 * @param main
 *   The main data.
 * @param quoted
 *   The quoted associated with the content.
 * @param range_name
 *   The range representing the variable content name string within the data_make->buffer.
 * @param main_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The expanded arguments.
 *
 * @return
 *   F_true on success and match expanded.
 *   F_false on no matches to expand.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_expand_environment_
  extern f_status_t fake_make_operate_expand_environment(const fake_main_t main, const f_fss_quote_t quoted, const f_string_range_t range_name, fake_make_data_t *data_make, f_string_dynamics_t *arguments) f_attribute_visibility_internal;
#endif // _di_fake_make_operate_expand_environment_

/**
 * Perform the expand operation, specifically for the build settings.
 *
 * @param main
 *   The main data.
 * @param quoted
 *   The quoted associated with the content.
 * @param range_name
 *   The range representing the variable content name string within the data_make->buffer.
 * @param main_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The expanded arguments.
 *
 * @return
 *   F_true on success and match expanded.
 *   F_false on no matches to expand.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_expand_build_
  extern f_status_t fake_make_operate_expand_build(const fake_main_t main, const f_fss_quote_t quoted, const f_string_range_t range_name, fake_make_data_t *data_make, f_string_dynamics_t *arguments) f_attribute_visibility_internal;
#endif // _di_fake_make_operate_expand_build_

/**
 * Perform the make operations within the given section.
 *
 * @param id_section
 *   The array location id within the fakefile of the section to operate on.
 * @param main
 *   The main data.
 * @param main_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param section_stack
 *   The current operation stack.
 * @param status
 *   F_none on success.
 *   F_valid_not (with error bit) is returned if any part of the section is invalid, such as an invalid operation name.
 *   F_recurse (with error bit) is returned if unable to recurse to another operation section (usually max stack depth reached).
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @return
 *   The return code of the execution process.
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 */
#ifndef _di_fake_make_operate_section_
  int fake_make_operate_section(const f_array_length_t id_section, fake_main_t *main, fake_make_data_t *data_make, f_array_lengths_t *section_stack, f_status_t *status) f_attribute_visibility_internal;
#endif // _di_fake_make_operate_section_

/**
 * Perform a specific make operation within the given section.
 *
 * @param section_name
 *   The section name.
 * @param operation
 *   The operation type.
 * @param operation_name
 *   The operation name.
 * @param arguments
 *   The expanded arguments.
 * @param success
 *   Whether or not a previous section operation succeeded or failed.
 * @param operation_if
 *   The if-condition status for the current operation.
 * @param main
 *   The main data.
 * @param main_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param section_stack
 *   The current operation stack.
 * @param status
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @return
 *   The return code of the execution process.
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 */
#ifndef _di_fake_make_operate_process_
  extern int fake_make_operate_process(const f_string_range_t section_name, const uint8_t operation, const f_string_static_t operation_name, const f_string_dynamics_t arguments, const bool success, uint8_t *operation_if, fake_main_t *main, fake_make_data_t *data_make, f_array_lengths_t *section_stack, f_status_t *status) f_attribute_visibility_internal;
#endif // _di_fake_make_operate_process_

/**
 * Execute either the run operation or the shell operation.
 *
 * @param main
 *   The main data.
 * @param program
 *   The program to be executed.
 * @param arguments
 *   The arguments for the run or shell operation.
 * @param as_shell
 *   When TRUE, this is a shell operation.
 *   When FALSE, this is a run operation.
 * @param main_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 *
 * @return
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_process_execute_
  extern f_status_t fake_make_operate_process_execute(const fake_main_t main, const f_string_static_t program, const f_string_statics_t arguments, const bool as_shell, fake_make_data_t *data_make) f_attribute_visibility_internal;
#endif // _di_fake_make_operate_process_execute_

/**
 * Handle the return code, converting it to a number.
 *
 * @param main
 *   The main data.
 * @param return_code
 *   The return code to process.
 * @param main_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param status
 *   The return status.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_process_return_
  extern void fake_make_operate_process_return(const fake_main_t main, const int return_code, fake_make_data_t *data_make, f_status_t *status) f_attribute_visibility_internal;
#endif // _di_fake_make_operate_process_return_

/**
 * Execute either the run operation or the shell operation.
 *
 * @param main
 *   The main data.
 * @param arguments
 *   The arguments for the run or shell operation.
 * @param as_shell
 *   When TRUE, this is a shell operation.
 *   When FALSE, this is a run operation.
 * @param main_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 *
 * @return
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_process_run_
  extern f_status_t fake_make_operate_process_run(const fake_main_t main, const f_string_statics_t arguments, const bool as_shell, fake_make_data_t *data_make) f_attribute_visibility_internal;
#endif // _di_fake_make_operate_process_run_

/**
 * For a given make section operation, validate the given operation.
 *
 * This performs pre-operation validations.
 * Additional issues may occure when running operations that are not detected nor detectable by this.
 *
 * @param main
 *   The main data.
 * @param section_name
 *   The section name.
 * @param operation
 *   The operation being performed.
 * @param operation_name
 *   The operation name.
 * @param arguments
 *   The expanded arguments.
 * @param operation_if
 *   The if-condition status for the current operation.
 * @param main_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param section_stack
 *   The current operation stack.
 * @param status
 *   The return status.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_validate_
  extern void fake_make_operate_validate(const fake_main_t main, const f_string_range_t section_name, const f_array_length_t operation, const f_string_static_t operation_name, const f_string_dynamics_t arguments, uint8_t *operation_if, fake_make_data_t *data_make, f_array_lengths_t *section_stack, f_status_t *status) f_attribute_visibility_internal;
#endif // _di_fake_make_operate_validate_

/**
 * Validate that the given define variable name is valid.
 *
 * A valid define variable name must begin with an alpha-character or an underscore.
 * Every character after that may be alphanumeric or underscore.
 * All other characters, including Unicode characters, are invalid.
 *
 * @fixme make this UTF-8 friendly.
 *
 * @param name
 *   The variable name string to validate.
 *
 * @return
 *   F_true on valid.
 *   F_false on invalid.
 *   F_none if there is no string to validate (used = 0).
 */
#ifndef _di_fake_make_operate_validate_define_name_
  extern f_status_t fake_make_operate_validate_define_name(const f_string_static_t name) f_attribute_visibility_internal;
#endif // _di_fake_make_operate_validate_define_name_

/**
 * Get a path, relative to the project root.
 *
 * @param main
 *   The main data.
 * @param path
 *   The NULL terminated path to get the relative path of.
 * @param main_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 *   The relative path is stored in data_make.path_cache.
 *
 * @return
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_path_relative_
  extern f_status_t fake_make_path_relative(const fake_main_t main, const f_string_static_t path, fake_make_data_t *data_make) f_attribute_visibility_internal;
#endif // _di_fake_make_path_relative_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_make_h
