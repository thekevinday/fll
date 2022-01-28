/**
 * FLL - Level 2
 *
 * Project: Error
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by project error.
 *
 * This is auto-included by error.h and should not need to be explicitly included.
 */
#ifndef _FLL_error_common_h
#define _FLL_error_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Error file types.
 *
 * fll_error_file_type_*:
 *   - file:      File error.
 *   - directory: Directory error.
 *   - path:      Path error.
 *   - pipe:      Pipe error.
 */
#ifndef _di_fll_error_file_type_
  enum {
    fll_error_file_type_file_e = 1,
    fll_error_file_type_directory_e,
    fll_error_file_type_path_e,
    fll_error_file_type_pipe_e,
  };

  #define FLL_error_file_type_directory_s "directory"
  #define FLL_error_file_type_file_s      "file"
  #define FLL_error_file_type_path_s      "path"
  #define FLL_error_file_type_pipe_s      "pipe"

  #define FLL_error_file_type_directory_s_length 9
  #define FLL_error_file_type_file_s_length      4
  #define FLL_error_file_type_path_s_length      4
  #define FLL_error_file_type_pipe_s_length      4

  extern const f_string_static_t fll_error_file_type_directory_s;
  extern const f_string_static_t fll_error_file_type_file_s;
  extern const f_string_static_t fll_error_file_type_path_s;
  extern const f_string_static_t fll_error_file_type_pipe_s;
#endif // _di_fll_error_file_type_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_error_common_h
