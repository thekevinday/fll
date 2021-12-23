/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_make_load_parameters_h
#define _PRIVATE_make_load_parameters_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Load the environment variables into a structure more readily available for using in parameter expansion.
 *
 * @param main
 *   The main program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and the build settings file.
 * @param status
 *   The return status.
 *
 *   F_none on success.
 *
 *   F_interrupt (with error bit) on receiving a terminate process signal, such as an interrupt signal.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_load_parameters_
  extern void fake_make_load_parameters(fake_main_t * const main, fake_make_data_t * const data_make, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_make_load_parameters_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_make_load_parameters_h
