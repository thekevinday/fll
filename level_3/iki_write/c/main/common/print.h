/**
 * FLL - Level 3
 *
 * Project: IKI Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _iki_write_common_print_h
#define _iki_write_common_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A special array of strings intended for representing funciton names.
 *
 * These are primarily used for printing errors with the function names.
 *
 * The macro macro_iki_write_f() is used to reference the array index by the enum name.
 *
 * macro_iki_write_f():
 *   - name: The name of the function.
 */
#ifndef _di_iki_write_f_a_
  extern const f_string_t iki_write_f_a[];

  #define macro_iki_write_f(name) iki_write_f_a[iki_write_f_##name##_e]
#endif // _di_iki_write_f_a_

/**
 * An enum representing specific indexes within the above array.
 *
 * This is a convenience enum used to make code slightly more readable.
 */
#ifndef _di_iki_write_f_e_
  enum {
    iki_write_f_f_console_parameter_process_e,
    iki_write_f_f_file_read_e,
    iki_write_f_f_iki_object_is_e,
    iki_write_f_f_string_dynamic_partial_append_nulless_e,
    iki_write_f_f_string_dynamic_seek_to_e,
    iki_write_f_f_string_dynamics_resize_e,
    iki_write_f_fll_iki_content_escape_e,
    iki_write_f_fll_program_parameter_process_context_e,
    iki_write_f_fll_program_parameter_process_verbosity_e,
  }; // enum
#endif // _di_iki_write_f_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_write_common_print_h
