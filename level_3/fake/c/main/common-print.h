/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_common_print_h
#define _fake_common_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A special array of strings intended for representing funciton names.
 *
 * These are primarily used for printing errors with the function names.
 *
 * The macro macro_fake_f() is used to reference the array index by the enum name.
 *
 * macro_fake_f():
 *   - name: The name of the function.
 */
#ifndef _di_fake_f_a_
  extern const f_string_t fake_f_a[];

  #define macro_fake_f(name) fake_f_a[fake_f_##name##_e]
#endif // _di_fake_f_a_

/**
 * An enum representing specific indexes within the above array.
 *
 * This is a convenience enum used to make code slightly more readable.
 */
#ifndef _di_fake_f_e_
  enum {
    fake_f_f_console_parameter_prioritize_right_e,
    fake_f_f_console_parameter_process_e,
    fake_f_f_file_is_e,
    fake_f_f_file_name_base_e,
    fake_f_f_string_append_e,
    fake_f_f_string_dynamic_append_e,
    fake_f_f_string_dynamic_append_nulless_e,
    fake_f_f_string_dynamic_increase_by_e,
    fake_f_f_string_dynamic_mash_e,
    fake_f_f_string_dynamic_resize_e,
    fake_f_f_uint8s_increase_by_e,
    fake_f_f_utf_is_word_dash_plus_e,
    fake_f_fl_directory_copy_e,
    fake_f_fll_execute_arguments_add_e,
    fake_f_fll_execute_arguments_add_parameter_set_e,
    fake_f_fll_execute_program_e,
    fake_f_fll_program_parameter_process_context_e,
    fake_f_fll_program_parameter_process_verbosity_e,
  }; // enum
#endif // _di_fake_f_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_common_print_h
