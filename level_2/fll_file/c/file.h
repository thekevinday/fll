/**
 * FLL - Level 2
 *
 * Project: File
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides file-related functionality.
 */
#ifndef _FLL_file_h
#define _FLL_file_h

// libc includes
#include <stdio.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/type.h>
#include <level_0/utf.h>

// fll-1 includes
#include <level_1/color.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print file error messages.
 *
 * @param file
 *   The file to write to, such as f_type_output or f_type_error.
 * @param context
 *   The color context information to use when printing.
 * @param function_name
 *   The name of the function responsible for the error.
 * @param file_name
 *   The name of the file with the error.
 * @param status
 *   The status code representing the error.
 *   The status code should be passed through F_status_set_fine() if it contains error or warning bits.
 *
 * @return
 *   F_true if error message was printed.
 *   F_false if no error message was printed.
 */
#ifndef _di_fll_file_error_print_
  extern f_return_status fll_file_error_print(FILE *file, const fl_color_context context, const f_string function_name, const f_string file_name, const f_status status);
#endif // _di_fll_file_error_print_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_file_h
