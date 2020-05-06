/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_build_h
#define _PRIVATE_build_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Execute the Pre-Process or Post-pocess build script.
 *
 * @param data
 *   The program data.
 * @param process_script
 *   The setting_data file name fo the appropriate process script.
 *   This is expected to be eithe data.settings_data.process_pre or data.settings_data.process_post.
 *
 * @return
 *   f_none on success.
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_execute_process_script_
  extern f_return_status fake_build_execute_process_script(const fake_data data, const f_string_dynamic process_script) f_gcc_attribute_visibility_internal;
#endif // _di_fake_build_execute_process_script_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_build_h
