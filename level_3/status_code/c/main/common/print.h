/**
 * FLL - Level 3
 *
 * Project: Status Code
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _status_code_common_print_h
#define _status_code_common_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A special array of strings intended for representing funciton names.
 *
 * These are primarily used for printing errors with the function names.
 *
 * The macro macro_status_code_f() is used to reference the array index by the enum name.
 *
 * macro_status_code_f():
 *   - name: The name of the function.
 */
#ifndef _di_status_code_f_a_
  extern const f_string_t status_code_f_a[];

  #define macro_status_code_f(name) status_code_f_a[status_code_f_##name##_e]
#endif // _di_status_code_f_a_

/**
 * An enum representing specific indexes within the above array.
 *
 * This is a convenience enum used to make code slightly more readable.
 */
#ifndef _di_status_code_f_e_
  enum {
    status_code_f_f_console_parameter_process_e,
    status_code_f_status_string_from_e,
    status_code_f_status_string_to_e,
    status_code_f_fll_program_parameter_process_context_e,
    status_code_f_fll_program_parameter_process_verbosity_e,
  }; // enum
#endif // _di_status_code_f_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _status_code_common_print_h
