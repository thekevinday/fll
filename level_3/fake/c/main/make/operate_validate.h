/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides make operate validate functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_make_operate_validate_h
#define _fake_make_operate_validate_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * For a given make section operation, validate the given operation.
 *
 * This performs pre-operation validations.
 * Additional issues may occure when running operations that are not detected nor detectable by this.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.main->setting.status:
 *     F_none on success.
 *
 *     F_parameter (with error bit) on invalid parameter.
 *
 *     Errors (with error bit) from: fake_make_operate_validate_type_break()
 *     Errors (with error bit) from: fake_make_operate_validate_type_build()
 *     Errors (with error bit) from: fake_make_operate_validate_type_clean_top_skeleton()
 *     Errors (with error bit) from: fake_make_operate_validate_type_clone()
 *     Errors (with error bit) from: fake_make_operate_validate_type_compile()
 *     Errors (with error bit) from: fake_make_operate_validate_type_copy()
 *     Errors (with error bit) from: fake_make_operate_validate_type_define()
 *     Errors (with error bit) from: fake_make_operate_validate_type_delete()
 *     Errors (with error bit) from: fake_make_operate_validate_type_else()
 *     Errors (with error bit) from: fake_make_operate_validate_type_exit()
 *     Errors (with error bit) from: fake_make_operate_validate_type_exit()
 *     Errors (with error bit) from: fake_make_operate_validate_type_permission()
 *     Errors (with error bit) from: fake_make_operate_validate_type_condition()
 *     Errors (with error bit) from: fake_make_operate_validate_type_index()
 *     Errors (with error bit) from: fake_make_operate_validate_type_link()
 *     Errors (with error bit) from: fake_make_operate_validate_type_move()
 *     Errors (with error bit) from: fake_make_operate_validate_type_operate()
 *     Errors (with error bit) from: fake_make_operate_validate_type_run()
 *     Errors (with error bit) from: fake_make_operate_validate_type_parameter()
 *     Errors (with error bit) from: fake_make_operate_validate_type_pop()
 *     Errors (with error bit) from: fake_make_operate_validate_type_to()
 *     Errors (with error bit) from: fake_make_operate_validate_type_touch()
 *     Errors (with error bit) from: fake_make_operate_validate_type_write()
 * @param section_name
 *   The section name.
 * @param state_process
 *   The operation and if-condition operation states.
 *   This condition will be updated by this as appropriate.
 * @param section_stack
 *   The current operation stack.
 *
 * @see fake_make_operate_validate_type_break()
 * @see fake_make_operate_validate_type_build()
 * @see fake_make_operate_validate_type_clean_top_skeleton()
 * @see fake_make_operate_validate_type_clone()
 * @see fake_make_operate_validate_type_compile()
 * @see fake_make_operate_validate_type_copy()
 * @see fake_make_operate_validate_type_define()
 * @see fake_make_operate_validate_type_delete()
 * @see fake_make_operate_validate_type_else()
 * @see fake_make_operate_validate_type_exit()
 * @see fake_make_operate_validate_type_exit()
 * @see fake_make_operate_validate_type_permission()
 * @see fake_make_operate_validate_type_condition()
 * @see fake_make_operate_validate_type_index()
 * @see fake_make_operate_validate_type_link()
 * @see fake_make_operate_validate_type_move()
 * @see fake_make_operate_validate_type_operate()
 * @see fake_make_operate_validate_type_run()
 * @see fake_make_operate_validate_type_parameter()
 * @see fake_make_operate_validate_type_pop()
 * @see fake_make_operate_validate_type_to()
 * @see fake_make_operate_validate_type_touch()
 * @see fake_make_operate_validate_type_write()
 */
#ifndef _di_fake_make_operate_validate_
  extern void fake_make_operate_validate(fake_make_data_t * const data_make, const f_string_range_t section_name, fake_state_process_t * const state_process, f_number_unsigneds_t * const section_stack);
#endif // _di_fake_make_operate_validate_

/**
 * Validate that the given define variable name is valid.
 *
 * A valid define variable name must begin with an alpha-character or an underscore.
 * Every character after that may be alphanumeric or underscore.
 * All other characters, including Unicode characters, are invalid.
 *
 * @param name
 *   The variable name string to validate.
 *
 * @return
 *   F_data_not if there is no string to validate (used = 0).
 *   F_true on valid.
 *   F_false on invalid.
 *
 * @see isalpha()
 * @see isalnum()
 */
#ifndef _di_fake_make_operate_validate_define_name_
  extern f_status_t fake_make_operate_validate_define_name(const f_string_static_t name);
#endif // _di_fake_make_operate_validate_define_name_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_make_operate_validate_h
