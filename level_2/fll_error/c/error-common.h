/**
 * FLL - Level 2
 *
 * Project: Error
 * API Version: 0.5
 * Licenses: lgplv2.1
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
 */
#ifndef _di_fll_error_file_type_
  enum {
    fll_error_file_type_file = 1,
    fll_error_file_type_directory,
    fll_error_file_type_pipe,
  };

  #define fll_error_file_type_string_directory "directory"
  #define fll_error_file_type_string_file      "file"
  #define fll_error_file_type_string_pipe      "pipe"

  #define fll_error_file_type_length_directory 9
  #define fll_error_file_type_length_file      4
  #define fll_error_file_type_length_pipe      4

  extern const f_string_t fll_error_file_type_string_directory_s;
  extern const f_string_t fll_error_file_type_string_file_s;
  extern const f_string_t fll_error_file_type_string_pipe_s;
#endif // _di_fll_error_file_type_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_error_common_h
