/**
 * FLL - Level 3
 *
 * Project: FSS Identify
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_identify_common_print_h
#define _fss_identify_common_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A special array of strings intended for representing funciton names.
 *
 * These are primarily used for printing errors with the function names.
 *
 * The macro macro_fss_identify_f() is used to reference the array index by the enum name.
 *
 * macro_fss_identify_f():
 *   - name: The name of the function.
 */
#ifndef _di_fss_identify_f_a_
  extern const f_string_t fss_identify_f_a[];

  #define macro_fss_identify_f(name) fss_identify_f_a[fss_identify_f_##name##_e]
#endif // _di_fss_identify_f_a_

/**
 * An enum representing specific indexes within the above array.
 *
 * This is a convenience enum used to make code slightly more readable.
 */
#ifndef _di_fss_identify_f_e_
  enum {
    fss_identify_f_f_console_parameter_prioritize_right_e,
    fss_identify_f_f_console_parameter_process_e,
    fss_identify_f_f_file_stream_open_e,
    fss_identify_f_f_file_stream_read_block_e,
    fss_identify_f_f_memory_array_increase_by_e,
    fss_identify_f_f_string_dynamic_append_nulless_e,
    fss_identify_f_f_thread_create_e,
    fss_identify_f_f_utf_is_word_dash_e,
    fss_identify_f_fll_fss_identify_e,
    fss_identify_f_fll_program_parameter_process_context_standard_e,
    fss_identify_f_fll_program_parameter_process_verbosity_standard_e,
  }; // enum
#endif // _di_fss_identify_f_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_identify_common_print_h
