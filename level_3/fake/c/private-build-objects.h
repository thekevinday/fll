/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_build_objects_h
#define _PRIVATE_build_objects_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Build the static objects.
 *
 * @param main
 *   The main program data.
 * @param data_build
 *   All build related data.
 * @param mode
 *   The file mode.
 * @param file_stage
 *   The specific stage file path.
 * @param status
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @return
 *   The return code of the execution process.
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 */
#ifndef _di_fake_build_objects_static_
  extern int fake_build_objects_static(fake_main_t * const main, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_objects_static_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_build_objects_h
