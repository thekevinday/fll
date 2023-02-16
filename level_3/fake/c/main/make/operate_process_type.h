/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _fake_make_operate_type_h
#define _fake_make_operate_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform the break operations process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on any error.
 */
#ifndef _di_fake_make_operate_process_type_break_
  extern f_status_t fake_make_operate_process_type_break(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_process_type_break_

/**
 * Perform the build operations process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 * @return
 *   F_interrupt (with error bit) on interrupt.
 *
 *   Success from: fake_make_operate_process_return().
 *
 *   Errors (with error bit) from: fake_make_operate_process_return().
 *
 * @see fake_build_operate()
 * @see fake_make_operate_process_return()
 */
#ifndef _di_fake_make_operate_process_type_build_
  extern f_status_t fake_make_operate_process_type_build(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_process_type_build_

/**
 * Perform the clean operations process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 * @return
 *   F_interrupt (with error bit) on interrupt.
 *
 *   Success from: fake_make_operate_process_return().
 *
 *   Errors (with error bit) from: fake_make_operate_process_return().
 *
 * @see fake_clean_operate()
 * @see fake_make_operate_process_return()
 */
#ifndef _di_fake_make_operate_process_type_clean_
  extern f_status_t fake_make_operate_process_type_clean(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_process_type_clean_

/**
 * Perform the define operation process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param status
 *   The status code.
 *
 *   Success from: fake_execute().
 *
 *   Errors (with error bit) from: fake_execute().
 *
 * @return
 *   The return code of the compile operation.
 *
 * @see fake_execute()
 */
#ifndef _di_fake_make_operate_process_type_compile_
  extern int fake_make_operate_process_type_compile(fake_make_data_t * const data_make, f_status_t * const status);
#endif // _di_fake_make_operate_process_type_compile_

/**
 * Perform the if, and, and or operations process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param state_process
 *   The operation and if-condition states.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on any error.
 */
#ifndef _di_fake_make_operate_process_type_condition_
  extern f_status_t fake_make_operate_process_type_condition(fake_make_data_t * const data_make, fake_state_process_t * const state_process);
#endif // _di_fake_make_operate_process_type_condition_

/**
 * Perform the copy and clone operation processes.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param clone
 *   If TRUE, perform a copy that is a clone (preserved timestamps, roles, and permissions).
 *   If FALSE, perforrm a normaly copy without preserving properties.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on any error.
 *
 * @see f_directory_is()
 * @see f_file_clone()
 * @see f_file_copy()
 * @see f_file_name_base()
 * @see fl_directory_clone()
 * @see fl_directory_copy()
 */
#ifndef _di_fake_make_operate_process_type_copy_
  extern f_status_t fake_make_operate_process_type_copy(fake_make_data_t * const data_make, const bool clone);
#endif // _di_fake_make_operate_process_type_copy_

/**
 * Perform the define operation process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 * @return
 *   Success from: f_environment_set().
 *
 *   Errors (with error bit) from: f_environment_set().
 *
 * @see f_environment_set()
 */
#ifndef _di_fake_make_operate_process_type_define_
  extern f_status_t fake_make_operate_process_type_define(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_process_type_define_

/**
 * Perform the delete and deletes operation processes.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param all
 *   If TRUE, then if the path is a directory, then recursively apply to all paths within the directory.
 *   If FALSE, then only apply to the given path.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on any error.
 *
 * @see f_file_remove()
 * @see f_file_stat()
 * @see f_directory_remove()
 * @see f_directory_remove_custom()
 */
#ifndef _di_fake_make_operate_process_type_deletes_
  extern f_status_t fake_make_operate_process_type_deletes(fake_make_data_t * const data_make, const bool all);
#endif // _di_fake_make_operate_process_type_deletes_

/**
 * Perform the exit operation process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 * @return
 *   F_none on unknown exit type (only success and failure are known).
 *   F_signal_quit to designate exit on success.
 *
 *   F_failure (with error bit) on any error.
 *   F_signal_quit (with error bit) to designate exit on failure.
 */
#ifndef _di_fake_make_operate_process_type_exit_
  extern f_status_t fake_make_operate_process_type_exit(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_process_type_exit_

/**
 * Perform the fail operation process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 */
#ifndef _di_fake_make_operate_process_type_fail_
  extern void fake_make_operate_process_type_fail(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_process_type_fail_

/**
 * Perform the group and groups operation processes.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param all
 *   If TRUE, then if the path is a directory, then recursively apply to all paths within the directory.
 *   If FALSE, then only apply to the given path.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on any error.
 *
 * @see f_file_role_change()
 * @see fll_file_role_change_all()
 *
 * @see fake_make_assure_inside_project()
 * @see fake_make_get_id_group()
 */
#ifndef _di_fake_make_operate_process_type_groups_
  extern f_status_t fake_make_operate_process_type_groups(fake_make_data_t * const data_make, const bool all);
#endif // _di_fake_make_operate_process_type_groups_

/**
 * Perform the if define operation process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param if_not
 *   When TRUE, perform the if not is.
 *   When FALSE, perform the if is.
 * @param state_process
 *   The operation process state.
 */
#ifndef _di_fake_make_operate_process_type_if_define_
  extern void fake_make_operate_process_type_if_define(fake_make_data_t * const data_make, const bool if_not, fake_state_process_t *state_process);
#endif // _di_fake_make_operate_process_type_if_define_

/**
 * Perform the if exists operation process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param if_not
 *   When TRUE, perform the if not is.
 *   When FALSE, perform the if is.
 * @param state_process
 *   The operation process state.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on any error.
 *
 * @see f_file_exists()
 */
#ifndef _di_fake_make_operate_process_type_if_exist_
  extern f_status_t fake_make_operate_process_type_if_exist(fake_make_data_t * const data_make, const bool if_not, fake_state_process_t *state_process);
#endif // _di_fake_make_operate_process_type_if_exist_

/**
 * Perform the if >, >=, <, and <= operation processes.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param state_process
 *   The operation process state.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on any error.
 *
 * @see fl_conversion_dynamic_partial_to_unsigned_detect()
 */
#ifndef _di_fake_make_operate_process_type_if_greater_if_lesser_
  extern f_status_t fake_make_operate_process_type_if_greater_if_lesser(fake_make_data_t * const data_make, fake_state_process_t *state_process);
#endif // _di_fake_make_operate_process_type_if_greater_if_lesser_

/**
 * Perform the if group operation process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param if_not
 *   When TRUE, perform the if not is.
 *   When FALSE, perform the if is.
 * @param state_process
 *   The operation process state.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on any error.
 *
 * @see f_file_group_read()
 *
 * @see fake_make_get_id_group()
 */
#ifndef _di_fake_make_operate_process_type_if_group_
  extern f_status_t fake_make_operate_process_type_if_group(fake_make_data_t * const data_make, const bool if_not, fake_state_process_t *state_process);
#endif // _di_fake_make_operate_process_type_if_group_

/**
 * Perform the if is operation process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param if_not
 *   When TRUE, perform the if not is.
 *   When FALSE, perform the if is.
 * @param state_process
 *   The operation process state.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on any error.
 *
 * @see f_file_mode_read()
 */
#ifndef _di_fake_make_operate_process_type_if_is_
  extern f_status_t fake_make_operate_process_type_if_is(fake_make_data_t * const data_make, const bool if_not, fake_state_process_t *state_process);
#endif // _di_fake_make_operate_process_type_if_is_

/**
 * Perform the if  operation process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param if_not
 *   When TRUE, perform the if not is.
 *   When FALSE, perform the if is.
 * @param state_process
 *   The operation process state.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on any error.
 *
 * @see f_file_mode_read()
 * @see f_file_mode_to_mode()
 *
 * @see fake_make_get_id_mode()
 */
#ifndef _di_fake_make_operate_process_type_if_mode_
  extern f_status_t fake_make_operate_process_type_if_mode(fake_make_data_t * const data_make, const bool if_not, fake_state_process_t *state_process);
#endif // _di_fake_make_operate_process_type_if_mode_

/**
 * Perform the if owner operation process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param if_not
 *   When TRUE, perform the if not is.
 *   When FALSE, perform the if is.
 * @param state_process
 *   The operation process state.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on any error.
 *
 * @see f_file_owner_read()
 *
 * @see fake_make_get_id_owner()
 */
#ifndef _di_fake_make_operate_process_type_if_owner_
  extern f_status_t fake_make_operate_process_type_if_owner(fake_make_data_t * const data_make, const bool if_not, fake_state_process_t *state_process);
#endif // _di_fake_make_operate_process_type_if_owner_

/**
 * Perform the if parameter operation process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param if_not
 *   When TRUE, perform the if not is.
 *   When FALSE, perform the if is.
 * @param state_process
 *   The operation process state.
 */
#ifndef _di_fake_make_operate_process_type_if_parameter_
  extern void fake_make_operate_process_type_if_parameter(fake_make_data_t * const data_make, const bool if_not, fake_state_process_t *state_process);
#endif // _di_fake_make_operate_process_type_if_parameter_

/**
 * Perform the index operation process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param status
 *   F_child on child process returning.
 *
 *   Success from: fake_make_operate_process_return().
 *
 *   Errors (with error bit) from: fake_make_operate_process_return().
 *
 * @return
 *   The return code of the index operation.
 *
 * @see fake_execute()
 * @see fake_make_operate_process_return()
 */
#ifndef _di_fake_make_operate_process_type_index_
  extern int fake_make_operate_process_type_index(fake_make_data_t * const data_make, f_status_t * const status);
#endif // _di_fake_make_operate_process_type_index_

/**
 * Perform the link operation processes.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on any error.
 *
 * @see f_file_link()
 */
#ifndef _di_fake_make_operate_process_type_link_
  extern f_status_t fake_make_operate_process_type_link(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_process_type_link_

/**
 * Perform the mode and modes operation processes.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param all
 *   If TRUE, then if the path is a directory, then recursively apply to all paths within the directory.
 *   If FALSE, then only apply to the given path.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on any error.
 *
 * @see f_file_mode_determine()
 * @see f_file_mode_read()
 * @see f_file_mode_set()
 * @see fll_file_mode_set_all()
 *
 * @see fake_make_get_id_mode()
 */
#ifndef _di_fake_make_operate_process_type_modes_
  extern f_status_t fake_make_operate_process_type_modes(fake_make_data_t * const data_make, const bool all);
#endif // _di_fake_make_operate_process_type_modes_

/**
 * Perform the move operation process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on any error.
 *
 * @see f_directory_is()
 * @see f_file_name_base()
 * @see fll_file_move()
 */
#ifndef _di_fake_make_operate_process_type_move_
  extern f_status_t fake_make_operate_process_type_move(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_process_type_move_

/**
 * Perform the operate operation process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param section_stack
 *   The current operation stack.
 * @param status
 *   The status code.
 *
 *   F_none on success.
 *
 *   F_failure (with error bit) on any error.
 *
 * @return
 *   The return code of the section operation.
 *
 * @see fake_make_operate_section()
 */
#ifndef _di_fake_make_operate_process_type_operate_
  extern int fake_make_operate_process_type_operate(fake_make_data_t * const data_make, f_array_lengths_t * const section_stack, f_status_t * const status);
#endif // _di_fake_make_operate_process_type_operate_

/**
 * Perform the owner and owners operation processes.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param all
 *   If TRUE, then if the path is a directory, then recursively apply to all paths within the directory.
 *   If FALSE, then only apply to the given path.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on any error.
 *
 * @see f_file_role_change()
 * @see fll_file_role_change_all()
 *
 * @see fake_make_assure_inside_project()
 * @see fake_make_get_id_owner()
 */
#ifndef _di_fake_make_operate_process_type_owners_
  extern f_status_t fake_make_operate_process_type_owners(fake_make_data_t * const data_make, const bool all);
#endif // _di_fake_make_operate_process_type_owners_

/**
 * Perform the parameter operation process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on any error.
 *
 * @see f_string_dynamic_resize()
 * @see f_string_dynamics_resize()
 * @see f_string_map_multis_resize()
 */
#ifndef _di_fake_make_operate_process_type_parameter_
  extern f_status_t fake_make_operate_process_type_parameter(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_process_type_parameter_

/**
 * Perform the pop operation process.
 *
 * Only call this function if the data_make.path.stack.used is greater than 1.
 * This does not validate the size of the stack.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on any error.
 *
 * @see f_path_change()
 * @see f_string_dynamic_resize()
 *
 * @see fake_make_path_relative()
 */
#ifndef _di_fake_make_operate_process_type_pop_
  extern f_status_t fake_make_operate_process_type_pop(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_process_type_pop_

/**
 * Perform the print operation process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *   This resets and uses data_make.cache_1.
 * @param arguments
 *   The arguments for print operation.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on any error.
 *
 * @see fake_make_operate_process_buffer_escape()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_increase_by()
 */
#ifndef _di_fake_make_operate_process_type_print_
  extern f_status_t fake_make_operate_process_type_print(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_process_type_print_

/**
 * Perform the skeleton operation process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 * @return
 *   F_interrupt (with error bit) on interrupt.
 *
 *   Success from: fake_make_operate_process_return().
 *
 *   Errors (with error bit) from: fake_make_operate_process_return().
 *
 * @see fake_make_operate_process_return()
 * @see fake_skeleton_operate()
 */
#ifndef _di_fake_make_operate_process_type_skeleton_
  extern f_status_t fake_make_operate_process_type_skeleton(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_process_type_skeleton_

/**
 * Perform the to operation process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on any error.
 *
 * @see f_path_change()
 * @see f_string_dynamic_append()
 * @see f_string_dynamics_increase_by()
 *
 * @see fake_make_assure_inside_project()
 * @see fake_make_path_relative()
 */
#ifndef _di_fake_make_operate_process_type_to_
  extern f_status_t fake_make_operate_process_type_to(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_process_type_to_

/**
 * Perform the top operation process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on any error.
 *
 * @see f_path_change_at()
 * @see f_string_dynamic_resize()
 */
#ifndef _di_fake_make_operate_process_type_top_
  extern f_status_t fake_make_operate_process_type_top(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_process_type_top_

/**
 * Perform the touch operation process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on any error.
 *
 * @see f_directory_touch()
 * @see f_file_touch()
 */
#ifndef _di_fake_make_operate_process_type_touch_
  extern f_status_t fake_make_operate_process_type_touch(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_process_type_touch_

/**
 * Perform the write operation process.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *   This resets and uses data_make.cache_1.
 *
 * @return
 *   F_none on success.
 *
 *   F_failure (with error bit) on any error.
 *
 * @see f_file_exists()
 * @see f_file_stream_open()
 * @see f_file_stream_write()
 */
#ifndef _di_fake_make_operate_process_type_write_
  extern f_status_t fake_make_operate_process_type_write(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_process_type_write_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_make_operate_type_h
