/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides build program functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _PRIVATE_build_program_h
#define _PRIVATE_build_program_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Build the script programs.
 *
 * If there ever are scripting languages that have a concept of programs, then this function is here to do the job.
 * None of the built in languages support this so this function does nothing.
 *
 * A script is often referred to as a program, but in this context "script" and "program" are not the same.
 * One potential use of this function could be to construct a script from pieces, effectively building a "program".
 *
 * @param data
 *   The program data.
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
#ifndef _di_fake_build_program_script_
  extern int fake_build_program_script(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t * const status);
#endif // _di_fake_build_program_script_

/**
 * Build the shared programs.
 *
 * @param data
 *   The program data.
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
#ifndef _di_fake_build_program_shared_
  extern int fake_build_program_shared(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t * const status);
#endif // _di_fake_build_program_shared_

/**
 * Build the static programs.
 *
 * @param data
 *   The program data.
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
#ifndef _di_fake_build_program_static_
  extern int fake_build_program_static(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t * const status);
#endif // _di_fake_build_program_static_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_build_program_h
