/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides build library functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_build_library_h
#define _fake_build_library_h

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
 * @param data
 *   The program data.
 *
 *   This alters data.setting.state.status:
 *     F_none on success.
 *
 *     Status codes (with error bit) are returned on any problem.
 * @param data_build
 *   The build data.
 * @param mode
 *   The file mode.
 * @param file_stage
 *   The specific stage file path.
 *
 * @return
 *   The return code of the execution process.
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 */
#ifndef _di_fake_build_library_script_
  extern int fake_build_library_script(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage);
#endif // _di_fake_build_library_script_

/**
 * Build the shared libraries.
 *
 * @param data
 *   The program data.
 *
 *   This alters data.setting.state.status:
 *     F_none on success.
 *
 *     Status codes (with error bit) are returned on any problem.
 * @param data_build
 *   The build data.
 * @param mode
 *   The file mode.
 * @param file_stage
 *   The specific stage file path.
 *
 * @return
 *   The return code of the execution process.
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 */
#ifndef _di_fake_build_library_shared_
  extern int fake_build_library_shared(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage);
#endif // _di_fake_build_library_shared_

/**
 * Build the static libraries.
 *
 * @param data
 *   The program data.
 *
 *   This alters data.setting.state.status:
 *     F_none on success.
 *
 *     Status codes (with error bit) are returned on any problem.
 * @param data_build
 *   The build data.
 * @param mode
 *   The file mode.
 * @param file_stage
 *   The specific stage file path.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @return
 *   The return code of the execution process.
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 */
#ifndef _di_fake_build_library_static_
  extern int fake_build_library_static(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage);
#endif // _di_fake_build_library_static_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_build_library_h
