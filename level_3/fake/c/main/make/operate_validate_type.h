/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides make operate validate type functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_make_operate_validate_type_h
#define _fake_make_operate_validate_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform the break operation validation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.setting.state:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 */
#ifndef _di_fake_make_operate_validate_type_break_
  extern void fake_make_operate_validate_type_break(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_validate_type_break_

/**
 * Perform the build operation validation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.setting.state:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 */
#ifndef _di_fake_make_operate_validate_type_build_
  extern void fake_make_operate_validate_type_build(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_validate_type_build_

/**
 * Perform the clean, top, and skeleton operations validation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.setting.state:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 */
#ifndef _di_fake_make_operate_validate_type_clean_top_skeleton_
  extern void fake_make_operate_validate_type_clean_top_skeleton(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_validate_type_clean_top_skeleton_

/**
 * Perform the clone operation validation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.setting.state:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 *
 * @see f_directory_is()
 *
 * @see fake_make_assure_inside_project()
 */
#ifndef _di_fake_make_operate_validate_type_clone_
  extern void fake_make_operate_validate_type_clone(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_validate_type_clone_

/**
 * Perform the compile operation validation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.setting.state:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 */
#ifndef _di_fake_make_operate_validate_type_compile_
  extern void fake_make_operate_validate_type_compile(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_validate_type_compile_

/**
 * Perform the if, and, and or operations validation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param state_process
 *   The operation and if-condition operation states.
 *   This condition will be updated by this as appropriate.
 *
 *   This alters data_make.setting.state:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 *
 * @see f_file_exists()
 *
 * @see fake_make_assure_inside_project()
 * @see fake_make_get_id()
 * @see fake_make_get_id_mode()
 */
#ifndef _di_fake_make_operate_validate_type_condition_
  extern void fake_make_operate_validate_type_condition(fake_make_data_t * const data_make, fake_state_process_t * const state_process);
#endif // _di_fake_make_operate_validate_type_condition_

/**
 * Perform the copy and clone operation validation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.setting.state:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 *
 * @see f_directory_is()
 * @see f_file_exists()
 *
 * @see fake_make_assure_inside_project()
 */
#ifndef _di_fake_make_operate_validate_type_copy_
  extern void fake_make_operate_validate_type_copy(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_validate_type_copy_

/**
 * Perform the define operation validation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.setting.state:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 *
 * @see fake_make_operate_validate_define_name()
 */
#ifndef _di_fake_make_operate_validate_type_define_
  extern void fake_make_operate_validate_type_define(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_validate_type_define_

/**
 * Perform the delete and deletes operations validation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.setting.state:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 *
 * @see fake_make_assure_inside_project()
 */
#ifndef _di_fake_make_operate_validate_type_delete_
  extern void fake_make_operate_validate_type_delete(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_validate_type_delete_

/**
 * Perform the else operation validation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param state_process
 *   The operation and if-condition operation states.
 *   This condition will be updated by this as appropriate.
 *
 *   This alters data_make.setting.state:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 */
#ifndef _di_fake_make_operate_validate_type_else_
  extern void fake_make_operate_validate_type_else(fake_make_data_t * const data_make, fake_state_process_t * const state_process);
#endif // _di_fake_make_operate_validate_type_else_

/**
 * Perform the exit operation validation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.setting.state:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 */
#ifndef _di_fake_make_operate_validate_type_exit_
  extern void fake_make_operate_validate_type_exit(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_validate_type_exit_

/**
 * Perform the else operation validation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.setting.state:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 */
#ifndef _di_fake_make_operate_validate_type_fail_
  extern void fake_make_operate_validate_type_fail(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_validate_type_fail_

/**
 * Perform the index operation validation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.setting.state:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 */
#ifndef _di_fake_make_operate_validate_type_index_
  extern void fake_make_operate_validate_type_index(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_validate_type_index_

/**
 * Perform the link operation validation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.setting.state:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 */
#ifndef _di_fake_make_operate_validate_type_link_
  extern void fake_make_operate_validate_type_link(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_validate_type_link_

/**
 * Perform the move operation validation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.setting.state:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 *
 * @see f_file_name_directory()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_append_assure()
 *
 * @see fake_make_assure_inside_project()
 */
#ifndef _di_fake_make_operate_validate_type_move_
  extern void fake_make_operate_validate_type_move(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_validate_type_move_

/**
 * Perform the operate operation validation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param section_stack
 *   The current operation stack.
 *
 *   This alters data_make.setting.state:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 */
#ifndef _di_fake_make_operate_validate_type_operate_
  extern void fake_make_operate_validate_type_operate(fake_make_data_t * const data_make, f_array_lengths_t * const section_stack);
#endif // _di_fake_make_operate_validate_type_operate_

/**
 * Perform the touch operation validation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.setting.state:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 */
#ifndef _di_fake_make_operate_validate_type_parameter_
  extern void fake_make_operate_validate_type_parameter(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_validate_type_parameter_

/**
 * Perform the goup, groups, mode, modes, owner, and owners operations validation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param state_process
 *   The operation and if-condition operation states.
 *   This condition will be updated by this as appropriate.
 *
 *   This alters data_make.setting.state:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 *
 * @see f_file_is()
 */
#ifndef _di_fake_make_operate_validate_type_permission_
  extern void fake_make_operate_validate_type_permission(fake_make_data_t * const data_make, fake_state_process_t * const state_process);
#endif // _di_fake_make_operate_validate_type_permission_

/**
 * Perform the pop operation validation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.setting.state:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 */
#ifndef _di_fake_make_operate_validate_type_pop_
  extern void fake_make_operate_validate_type_pop(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_validate_type_pop_

/**
 * Perform the run and shell operation validation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.setting.state:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 */
#ifndef _di_fake_make_operate_validate_type_run_
  extern void fake_make_operate_validate_type_run(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_validate_type_run_

/**
 * Perform the to operation validation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.setting.state:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 *
 * @see f_file_is()
 */
#ifndef _di_fake_make_operate_validate_type_to_
  extern void fake_make_operate_validate_type_to(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_validate_type_to_

/**
 * Perform the touch operation validation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.setting.state:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 *
 * @see fake_make_assure_inside_project()
 */
#ifndef _di_fake_make_operate_validate_type_touch_
  extern void fake_make_operate_validate_type_touch(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_validate_type_touch_

/**
 * Perform the touch operation validation.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.setting.state:
 *     F_none on success.
 *
 *     F_failure (with error bit) on any error.
 *
 * @see fake_make_assure_inside_project()
 */
#ifndef _di_fake_make_operate_validate_type_write_
  extern void fake_make_operate_validate_type_write(fake_make_data_t * const data_make);
#endif // _di_fake_make_operate_validate_type_write_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_make_operate_validate_type_h
