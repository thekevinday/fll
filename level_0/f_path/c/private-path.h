/**
 * FLL - Level 0
 *
 * Project: Path
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_F_path_h
#define _PRIVATE_F_path_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of f_path_real().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param path
 *   The source path to determine what the real path is.
 * @param real
 *   The (allocated) real file path.
 *   This will have a max size of f_path_max + 1.
 *   This will be NULL terminated at real->used + 1.
 *
 * @return
 *   F_none on success.
 *   F_access_denied (with error bit) on access denied.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_input_output (with error bit) on I/O error.
 *   F_loop (with error bit) on loop error.
 *   F_memory_allocation (with error bit) on allocation error.
 *   F_memory_out (with error bit) if out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_failure (with error bit) for any other error.
 *
 * @see f_path_current()
 * @see f_path_real()
 */
#if !defined(_di_f_path_current_) || !defined(_di_f_path_real_)
  extern f_return_status private_f_path_real(const f_string_t path, f_string_dynamic_t *real) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_f_path_current_) || !defined(_di_f_path_real_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_F_path_h
