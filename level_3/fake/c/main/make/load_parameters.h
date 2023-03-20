/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides make load parameter functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_make_load_parameters_h
#define _fake_make_load_parameters_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Load the environment variables into a structure more readily available for using in parameter expansion.
 *
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 *
 *   This alters data_make.main->setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_string_dynamic_append().
 *     Errors (with error bit) from: f_string_dynamic_append_nulless().
 *     Errors (with error bit) from: f_string_dynamics_increase().
 *     Errors (with error bit) from: f_string_dynamics_increase_by().
 *
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_append_nulless()
 * @see f_string_dynamics_increase()
 * @see f_string_dynamics_increase_by()
 */
#ifndef _di_fake_make_load_parameters_
  extern void fake_make_load_parameters(fake_make_data_t * const data_make);
#endif // _di_fake_make_load_parameters_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_make_load_parameters_h
