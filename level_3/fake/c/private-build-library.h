/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_build_library_h
#define _PRIVATE_build_library_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Build the script libraries.
 *
 * If there ever are scripting languages that have a concept of libraries, then this function is here to do the job.
 * None of the built in languages support this so this function does nothing.
 *
 * One potential use of this function could be to construct a script from pieces, effectively building an "library".
 *
 * @param main
 *   The main program data.
 * @param data_build
 *   The build data.
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
#ifndef _di_fake_build_library_script_
  extern int fake_build_library_script(fake_main_t * const main, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t * const status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_library_script_

/**
 * Build the shared libraries.
 *
 * @param main
 *   The main program data.
 * @param data_build
 *   The build data.
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
#ifndef _di_fake_build_library_shared_
  extern int fake_build_library_shared(fake_main_t * const main, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t * const status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_library_shared_

/**
 * Build the static libraries.
 *
 * @param main
 *   The main program data.
 * @param data_build
 *   The build data.
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
#ifndef _di_fake_build_library_static_
  extern int fake_build_library_static(fake_main_t * const main, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t * const status) F_attribute_visibility_internal_d;
#endif // _di_fake_build_library_static_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_build_library_h
