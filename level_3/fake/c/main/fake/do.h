/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides functions, usually callbacks, for functions like fl_directory_do().
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_fake_do_h
#define _fake_fake_do_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Callback for performing an action regarding the copy operation for fake_build_copy().
 *
 * This can also be used for a clone or a move operation when the appropriate flags or set.
 *
 * @param recurse
 *   The recuse structure.
 *   Must be of type f_directory_recurse_do_t.
 *
 *   The recurse.state.code relevant flags:
 *     - fake_state_code_clone_e: Designate that this is a clone instead of copy.
 *     - fake_state_code_local_e: This is required and assumed to be set.
 *
 *   This alters recurse.state.custom.main.setting.state.status and recurse.state.status:
 *     F_none on success.
 *
 *     F_parameter (with error bit) on invalid parameter to the callback.
 *
 *     Errors (with error bit) from: f_file_clone().
 *     Errors (with error bit) from: f_file_copy().
 *     Errors (with error bit) from: f_string_dynamic_append_assure().
 *     Errors (with error bit) from: f_string_dynamic_append_nulless().
 *     Errors (with error bit) from: f_string_dynamic_increase_by().
 * @param name
 *   The directory name currently being process based on the flag.
 * @param flag
 *   The flags representing the action.
 *
 * @see f_file_clone()
 * @see f_file_copy()
 * @see f_string_dynamic_append_assure()
 * @see f_string_dynamic_append_nulless()
 * @see f_string_dynamic_increase_by()
 *
 * @see fake_build_copy()
 */
#ifndef _di_fake_do_copy_action_
  extern void fake_do_copy_action(void * const recurse, const f_string_static_t name, const uint16_t flag);
#endif // _di_fake_do_copy_action_

/**
 * Callback for handling an error regarding the copy operation for fake_build_copy().
 *
 * This can also be used for a clone or a move operation when the appropriate flags or set.
 *
 * @param recurse
 *   The recuse structure.
 *   Must be of type f_directory_recurse_do_t.
 *
 *   The recurse.state.code relevant flags:
 *     - fake_state_code_clone_e: Designate that this is a clone instead of copy.
 *     - fake_state_code_local_e: This is required and assumed to be set.
 *
 *   This alters recurse.state.custom.main.setting.state.status:
 *     Assigns value from recurse.state.status.
 *
 *   This does not alter recurse.state.status.
 * @param name
 *   The directory name currently being process based on the flag.
 * @param flag
 *   The flags representing the action.
 */
#ifndef _di_fake_do_copy_handle_
  extern void fake_do_copy_handle(void * const recurse, const f_string_static_t name, const uint16_t flag);
#endif // _di_fake_do_copy_handle_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_fake_do_h
