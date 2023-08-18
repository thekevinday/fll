/**
 * FLL - Level 3
 *
 * Project: Control
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the action functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _control_action_h
#define _control_action_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Identify the action code the given name represents.
 *
 * @param action
 *   The string representing an action.
 *
 * @return
 *   The action type code on success.
 *   0 if name is unknown.
 */
#ifndef _di_control_action_type_identify_
  extern const uint8_t control_action_type_identify(const f_string_static_t action);
#endif // _di_control_action_type_identify_

/**
 * Get a string representing the action type.
 *
 * @param type
 *   The action type id.
 *
 * @return
 *   The string with used > 0 on success.
 *   The string with used == 0 if no match was found.
 */
#ifndef _di_control_action_type_name_
  extern const f_string_static_t control_action_type_name(const uint8_t type);
#endif // _di_control_action_type_name_

/**
 * Verify that the additional parameters are reasonably correct for the identified action.
 *
 * @param main
 *   The main program data.
 *
 *   This alters main.setting.state.status:
 *     F_okay on success.
 *
 *     F_parameter (with error bit) on parameter validation/verification failure.
 */
#ifndef _di_control_action_verify_
  extern void control_action_verify(control_main_t * const main);
#endif // _di_control_action_verify_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _control_action_h
