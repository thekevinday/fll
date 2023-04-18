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
#ifndef _fss_write_common_print_h
#define _fss_write_common_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A special array of strings intended for representing funciton names.
 *
 * These are primarily used for printing errors with the function names.
 *
 * The macro macro_fss_write_f() is used to reference the array index by the enum name.
 *
 * macro_fss_write_f():
 *   - name: The name of the function.
 */
#ifndef _di_fss_write_f_a_
  extern const f_string_t fss_write_f_a[];

  #define macro_fss_write_f(name) fss_write_f_a[fss_write_f_##name##_e]
#endif // _di_fss_write_f_a_

/**
 * An enum representing specific indexes within the above array.
 *
 * This is a convenience enum used to make code slightly more readable.
 */
#ifndef _di_fss_write_f_e_
  enum {
    fss_write_f_f_console_parameter_process_e,
    fss_write_f_f_file_read_block_e,
    fss_write_f_f_file_stream_open_e,
    fss_write_f_f_fss_is_space_e,
    fss_write_f_f_string_dynamic_append_e,
    fss_write_f_f_string_dynamic_append_nulless_e,
    fss_write_f_f_string_dynamic_increase_by_e,
    fss_write_f_f_string_dynamics_increase_e,
    fss_write_f_f_string_dynamics_increase_by_e,
    fss_write_f_f_string_dynamics_resize_e,
    fss_write_f_f_string_dynamicss_increase_e,
    fss_write_f_f_string_dynamicss_increase_by_e,
    fss_write_f_f_string_ranges_increase_e,
    fss_write_f_f_string_ranges_increase_by_e,
    fss_write_f_f_string_rangess_increase_e,
    fss_write_f_f_string_rangess_increase_by_e,
    fss_write_f_f_string_read_block_increase_e,
    fss_write_f_f_thread_create_e,
    fss_write_f_fl_fss_basic_content_write_e,
    fss_write_f_fl_fss_basic_list_content_write_e,
    fss_write_f_fl_fss_basic_list_object_write_e,
    fss_write_f_fl_fss_basic_object_write_e,
    fss_write_f_fl_fss_embedded_list_content_write_e,
    fss_write_f_fl_fss_embedded_list_object_write_e,
    fss_write_f_fl_fss_extended_content_write_e,
    fss_write_f_fl_fss_extended_list_content_write_e,
    fss_write_f_fl_fss_extended_list_object_write_e,
    fss_write_f_fl_fss_extended_object_write_e,
    fss_write_f_fl_fss_payload_content_write_e,
    fss_write_f_fll_program_parameter_process_context_e,
    fss_write_f_fll_program_parameter_process_verbosity_e,
    fss_write_f_fll_fss_payload_write_e,
  }; // enum
#endif // _di_fss_write_f_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_common_print_h
