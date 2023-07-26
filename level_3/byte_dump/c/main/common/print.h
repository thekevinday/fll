/**
 * FLL - Level 3
 *
 * Project: Byte Dump
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _byte_dump_common_print_h
#define _byte_dump_common_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A special array of strings intended for representing funciton names.
 *
 * These are primarily used for printing errors with the function names.
 *
 * The macro macro_byte_dump_f() is used to reference the array index by the enum name.
 *
 * macro_byte_dump_f():
 *   - name: The name of the function.
 */
#ifndef _di_byte_dump_f_a_
  extern const f_string_t byte_dump_f_a[];

  #define macro_byte_dump_f(name) byte_dump_f_a[byte_dump_f_##name##_e]
#endif // _di_byte_dump_f_a_

/**
 * An enum representing specific indexes within the above array.
 *
 * This is a convenience enum used to make code slightly more readable.
 */
#ifndef _di_byte_dump_f_e_
  enum {
    byte_dump_f_f_console_parameter_prioritize_right_e,
    byte_dump_f_f_console_parameter_process_e,
    byte_dump_f_f_file_exists_e,
    byte_dump_f_f_file_stream_open_e,
    byte_dump_f_f_string_dynamics_increase_by_e,
    byte_dump_f_f_thread_create_e,
    byte_dump_f_fl_conversion_dynamic_to_unsigned_detect_e,
    byte_dump_f_fll_program_parameter_process_context_e,
    byte_dump_f_fll_program_parameter_process_verbosity_e,
  }; // enum
#endif // _di_byte_dump_f_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _byte_dump_common_print_h
