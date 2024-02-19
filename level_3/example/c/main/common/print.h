/**
 * FLL - Level 3
 *
 * Project: Example
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _example_common_print_h
#define _example_common_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A special array of strings intended for representing funciton names.
 *
 * These are primarily used for printing errors with the function names.
 *
 * The macro macro_example_f() is used to reference the array index by the enum name.
 *
 * macro_example_f():
 *   - name: The name of the function.
 */
#ifndef _di_example_f_a_
  extern const f_string_t example_f_a[];

  #define macro_example_f(name) example_f_a[example_f_##name##_e]
#endif // _di_example_f_a_

/**
 * An enum representing specific indexes within the above array.
 *
 * This is a convenience enum used to make code slightly more readable.
 */
#ifndef _di_example_f_e_
  enum {
    example_f_f_console_parameter_process_e,
    example_f_f_thread_create_e,
    example_f_fll_program_parameter_process_context_standard_e,
    example_f_fll_program_parameter_process_verbosity_standard_e,
  }; // enum
#endif // _di_example_f_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _example_common_print_h
