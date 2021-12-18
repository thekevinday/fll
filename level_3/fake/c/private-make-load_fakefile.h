/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_make_load_fakefile_h
#define _PRIVATE_make_load_fakefile_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Find the fake file, load it, validate it, and process it.
 *
 * This will process any additional files as necessary, such as the build settings file.
 *
 * @param main
 *   The main program data.
 * @param main_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param status
 *   The return status.
 *
 *   F_none on success.
 *
 *   F_interrupt (with error bit) on receiving a terminate process signal, such as an interrupt signal.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fake_build_load_setting()
 */
#ifndef _di_fake_make_load_fakefile_
  extern void fake_make_load_fakefile(fake_main_t * const main, fake_make_data_t *data_make, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_make_load_fakefile_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_make_load_fakefile_h
