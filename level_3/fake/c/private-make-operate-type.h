/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_make_operate_type_h
#define _PRIVATE_make_operate_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform the clone operation process.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The arguments for the run or shell operation.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_path_change().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_path_change()
 * @see f_string_dynamic_resize()
 *
 * @see fake_make_path_relative()
 */
#ifndef _di_fake_make_operate_process_type_clone_
  extern f_status_t fake_make_operate_process_type_clone(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_type__

/**
 * Perform the copy operation process.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The arguments for the run or shell operation.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_path_change().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_path_change()
 * @see f_string_dynamic_resize()
 *
 * @see fake_make_path_relative()
 */
#ifndef _di_fake_make_operate_process_type_copy_
  extern f_status_t fake_make_operate_process_type_copy(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_type_copy_

/**
 * Perform the delete and deletes operation processes.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The arguments for the run or shell operation.
 * @param all
 *   If TRUE, then if the path is a directory, then recursively apply to all paths within the directory.
 *   If FALSE, then only apply to the given path.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_path_change().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_path_change()
 * @see f_string_dynamic_resize()
 *
 * @see fake_make_path_relative()
 */
#ifndef _di_fake_make_operate_process_type_deletes_
  extern f_status_t fake_make_operate_process_type_deletes(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments, const bool all) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_type_deletes_

/**
 * Perform the exit operation process.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The arguments for the run or shell operation.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_path_change().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_path_change()
 * @see f_string_dynamic_resize()
 *
 * @see fake_make_path_relative()
 */
#ifndef _di_fake_make_operate_process_type_exit_
  extern f_status_t fake_make_operate_process_type_exit(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_type_exit_

/**
 * Perform the fail operation process.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The arguments for the run or shell operation.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_path_change().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_path_change()
 * @see f_string_dynamic_resize()
 *
 * @see fake_make_path_relative()
 */
#ifndef _di_fake_make_operate_process_type_fail_
  extern f_status_t fake_make_operate_process_type_fail(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_type_fail_

/**
 * Perform the group operation process.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The arguments for the run or shell operation.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_path_change().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_path_change()
 * @see f_string_dynamic_resize()
 *
 * @see fake_make_path_relative()
 */
#ifndef _di_fake_make_operate_process_type_group_
  extern f_status_t fake_make_operate_process_type_group(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_type_group_

/**
 * Perform the groups operation process.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The arguments for the run or shell operation.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_path_change().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_path_change()
 * @see f_string_dynamic_resize()
 *
 * @see fake_make_path_relative()
 */
#ifndef _di_fake_make_operate_process_type_groups_
  extern f_status_t fake_make_operate_process_type_groups(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_type_groups_

/**
 * Perform the if group operation process.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The arguments for the run or shell operation.
 * @param operation_if
 *   The if-condition status for the current operation.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_file_group_read().
 *
 *   Errors (with error bit) from: fake_make_get_id_group().
 *
 * @see f_file_group_read()
 *
 * @see fake_make_get_id_group()
 */
#ifndef _di_fake_make_operate_process_type_if_group_
  extern f_status_t fake_make_operate_process_type_if_group(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments, uint8_t *operation_if) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_type_if_group_

/**
 * Perform the if  operation process.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The arguments for the run or shell operation.
 * @param operation_if
 *   The if-condition status for the current operation.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_file_mode_read().
 *   Errors (with error bit) from: f_file_mode_to_mode().
 *
 *   Errors (with error bit) from: fake_make_get_id_mode().
 *
 * @see f_file_mode_read()
 * @see f_file_mode_to_mode()
 *
 * @see fake_make_get_id_mode()
 */
#ifndef _di_fake_make_operate_process_type_if_mode_
  extern f_status_t fake_make_operate_process_type_if_mode(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments, uint8_t *operation_if) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_type_if_mode_

/**
 * Perform the if owner operation process.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The arguments for the run or shell operation.
 * @param operation_if
 *   The if-condition status for the current operation.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_file_owner_read().
 *
 *   Errors (with error bit) from: fake_make_get_id_owner().
 *
 * @see f_file_owner_read()
 *
 * @see fake_make_get_id_owner()
 */
#ifndef _di_fake_make_operate_process_type_if_owner_
  extern f_status_t fake_make_operate_process_type_if_owner(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments, uint8_t *operation_if) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_type_if_owner_

/**
 * Perform the if is operation process.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The arguments for the run or shell operation.
 * @param operation_if
 *   The if-condition status for the current operation.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_file_mode_read().
 *
 * @see f_file_mode_read()
 */
#ifndef _di_fake_make_operate_process_type_if_is_
  extern f_status_t fake_make_operate_process_type_if_is(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments, uint8_t *operation_if) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_type_if_is_

/**
 * Perform the if defined operation process.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The arguments for the run or shell operation.
 * @param operation_if
 *   The if-condition status for the current operation.
 */
#ifndef _di_fake_make_operate_process_type_if_defined_
  extern void fake_make_operate_process_type_if_defined(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments, uint8_t *operation_if) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_type_if_defined_

/**
 * Perform the if >, >=, <, and <= operation processes.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The arguments for the run or shell operation.
 * @param operation_if
 *   The if-condition status for the current operation.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: fl_conversion_string_to_number_unsigned().
 *
 * @see fl_conversion_string_to_number_unsigned()
 */
#ifndef _di_fake_make_operate_process_type_if_greater_if_lesser_
  extern f_status_t fake_make_operate_process_type_if_greater_if_lesser(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments, uint8_t *operation_if) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_type_if_greater_if_lesser_

/**
 * Perform the mode operation process.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The arguments for the run or shell operation.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_path_change().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_path_change()
 * @see f_string_dynamic_resize()
 *
 * @see fake_make_path_relative()
 */
#ifndef _di_fake_make_operate_process_type_mode_
  extern f_status_t fake_make_operate_process_type_mode(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_type_mode_

/**
 * Perform the mode and modes operation processes.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The arguments for the run or shell operation.
 * @param all
 *   If TRUE, then if the path is a directory, then recursively apply to all paths within the directory.
 *   If FALSE, then only apply to the given path.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_file_mode_determine().
 *   Errors (with error bit) from: f_file_mode_read().
 *   Errors (with error bit) from: f_file_mode_set().
 *   Errors (with error bit) from: fll_file_mode_set_all().
 *
 * @see f_file_mode_determine()
 * @see f_file_mode_read()
 * @see f_file_mode_set()
 * @see fll_file_mode_set_all()
 *
 * @see fake_make_get_id_mode()
 */
#ifndef _di_fake_make_operate_process_type_modes_
  extern f_status_t fake_make_operate_process_type_modes(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments, const bool all) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_type_modes_

/**
 * Perform the move operation process.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The arguments for the run or shell operation.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_directory_is().
 *   Errors (with error bit) from: fll_file_move().
 *
 * @see f_directory_is()
 * @see fll_file_move()
 */
#ifndef _di_fake_make_operate_process_type_move_
  extern f_status_t fake_make_operate_process_type_move(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_type_move_

/**
 * Perform the owner and owners operation processes.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The arguments for the run or shell operation.
 * @param all
 *   If TRUE, then if the path is a directory, then recursively apply to all paths within the directory.
 *   If FALSE, then only apply to the given path.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_file_role_change().
 *   Errors (with error bit) from: fll_file_role_change_all().
 *
 *   Errors (with error bit) from: fake_make_assure_inside_project().
 *   Errors (with error bit) from: fake_make_get_id_owner().
 *
 * @see f_file_role_change()
 * @see fll_file_role_change_all()
 *
 * @see fake_make_assure_inside_project()
 * @see fake_make_get_id_owner()
 */
#ifndef _di_fake_make_operate_process_type_owners_
  extern f_status_t fake_make_operate_process_type_owners(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments, const bool all) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_type_owners_

/**
 * Perform the pop operation process.
 *
 * Only call this function if the data_make.path.stack.used is greater than 1.
 * This does not validate the size of the stack.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The arguments for the run or shell operation.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_path_change().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_path_change()
 * @see f_string_dynamic_resize()
 *
 * @see fake_make_path_relative()
 */
#ifndef _di_fake_make_operate_process_type_pop_
  extern f_status_t fake_make_operate_process_type_pop(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_type_pop_

/**
 * Perform the to operation process.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The arguments for the run or shell operation.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_path_change().
 *   Errors (with error bit) from: f_string_dynamic_append().
 *   Errors (with error bit) from: f_string_dynamics_increase_by().
 *
 *   Errors (with error bit) from: fake_make_assure_inside_project().
 *
 * @see f_path_change()
 * @see f_string_dynamic_append()
 * @see f_string_dynamics_increase_by()
 *
 * @see fake_make_assure_inside_project()
 * @see fake_make_path_relative()
 */
#ifndef _di_fake_make_operate_process_type_to_
  extern f_status_t fake_make_operate_process_type_to(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_type_to_

/**
 * Perform the top operation process.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The arguments for the run or shell operation.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_path_change_at().
 *   Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @see f_path_change_at()
 * @see f_string_dynamic_resize()
 */
#ifndef _di_fake_make_operate_process_type_top_
  extern f_status_t fake_make_operate_process_type_top(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_type_top_

/**
 * Perform the touch operation process.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The arguments for the run or shell operation.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_directory_touch().
 *   Errors (with error bit) from: f_file_touch().
 *
 * @see f_directory_touch()
 * @see f_file_touch()
 */
#ifndef _di_fake_make_operate_process_type_touch_
  extern f_status_t fake_make_operate_process_type_touch(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_dynamics_t arguments) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_process_type_touch_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_make_operate_type_h
