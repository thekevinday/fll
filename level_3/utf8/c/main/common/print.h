/**
 * FLL - Level 3
 *
 * Project: UTF8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _utf8_common_print_h
#define _utf8_common_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A special array of strings intended for representing funciton names.
 *
 * These are primarily used for printing errors with the function names.
 *
 * The macro macro_utf8_f() is used to reference the array index by the enum name.
 *
 * macro_utf8_f():
 *   - name: The name of the function.
 */
#ifndef _di_utf8_f_a_
  extern const f_string_t utf8_f_a[];

  #define macro_utf8_f(name) utf8_f_a[utf8_f_##name##_e]
#endif // _di_utf8_f_a_

/**
 * An enum representing specific indexes within the above array.
 *
 * This is a convenience enum used to make code slightly more readable.
 */
#ifndef _di_utf8_f_e_
  enum {
    utf8_f_f_console_parameter_prioritize_right_e,
    utf8_f_f_console_parameter_process_e,
    utf8_f_f_file_stream_open_e,
    utf8_f_f_string_dynamic_append_nulless_e,
    utf8_f_f_string_dynamics_increase_by_e,
    utf8_f_fll_program_parameter_process_context_e,
    utf8_f_fll_program_parameter_process_verbosity_e,
    utf8_f_utf8_detect_codepoint_e,
    utf8_f_utf8_process_file_bytesequence_e,
    utf8_f_utf8_process_file_codepoint_e,
  }; // enum
#endif // _di_utf8_f_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _utf8_common_print_h
