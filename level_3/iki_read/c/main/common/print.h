/**
 * FLL - Level 3
 *
 * Project: FSS Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _iki_read_common_print_h
#define _iki_read_common_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A special array of strings intended for representing funciton names.
 *
 * These are primarily used for printing errors with the function names.
 *
 * The macro macro_iki_read_f() is used to reference the array index by the enum name.
 *
 * macro_iki_read_f():
 *   - name: The name of the function.
 */
#ifndef _di_iki_read_f_a_
  extern const f_string_t iki_read_f_a[];

  #define macro_iki_read_f(name) iki_read_f_a[iki_read_f_##name##_e]
#endif // _di_iki_read_f_a_

/**
 * An enum representing specific indexes within the above array.
 *
 * This is a convenience enum used to make code slightly more readable.
 */
#ifndef _di_iki_read_f_e_
  enum {
    iki_read_f_f_console_parameter_process_e,
    iki_read_f_f_file_descriptor_e,
    iki_read_f_f_file_exists_e,
    iki_read_f_f_file_read_e,
    iki_read_f_f_file_size_by_id_e,
    iki_read_f_f_file_stream_open_e,
    iki_read_f_f_file_stream_read_until_e,
    iki_read_f_f_string_dynamic_append_nulless_e,
    iki_read_f_f_string_dynamic_increase_by_e,
    iki_read_f_f_string_dynamic_resize_e,
    iki_read_f_f_string_dynamics_append_e,
    iki_read_f_f_string_dynamics_increase_by_e,
    iki_read_f_f_string_dynamics_resize_e,
    iki_read_f_f_string_maps_increase_by_e,
    iki_read_f_f_string_triples_increase_by_e,
    iki_read_f_fl_iki_read_e,
    iki_read_f_fll_program_parameter_process_context_e,
    iki_read_f_fll_program_parameter_process_verbosity_e,
  }; // enum
#endif // _di_iki_read_f_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_read_common_print_h
