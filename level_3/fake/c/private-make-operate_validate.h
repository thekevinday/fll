/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_make_operate_validate_h
#define _PRIVATE_make_operate_validate_h

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
 * @param section_name
 *   The section name.
 * @param arguments
 *   The expanded arguments.
 * @param state_process
 *   The operation and if-condition operation states.
 *   This condition will be updated by this as appropriate.
 * @param section_stack
 *   The current operation stack.
 * @param status
 *   The return status.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_validate_
  extern void fake_make_operate_validate(fake_make_data_t * const data_make, const f_string_range_t section_name, const f_string_dynamics_t arguments, fake_state_process_t *state_process, f_array_lengths_t *section_stack, f_status_t *status) F_attribute_visibility_internal_d;
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
  extern f_status_t fake_make_operate_validate_define_name(const f_string_static_t name) F_attribute_visibility_internal_d;
#endif // _di_fake_make_operate_validate_define_name_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_make_operate_validate_h
