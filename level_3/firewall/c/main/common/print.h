/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _firewall_common_print_h
#define _firewall_common_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A special array of strings intended for representing funciton names.
 *
 * These are primarily used for printing errors with the function names.
 *
 * The macro macro_firewall_f() is used to reference the array index by the enum name.
 *
 * macro_firewall_f():
 *   - name: The name of the function.
 */
#ifndef _di_firewall_f_a_
  extern const f_string_t firewall_f_a[];

  #define macro_firewall_f(name) firewall_f_a[firewall_f_##name##_e]
#endif // _di_firewall_f_a_

/**
 * An enum representing specific indexes within the above array.
 *
 * This is a convenience enum used to make code slightly more readable.
 */
#ifndef _di_firewall_f_e_
  enum {
    firewall_f_f_console_parameter_process_e,
    firewall_f_f_directory_list_e,
    firewall_f_f_file_open_e,
    firewall_f_f_file_read_e,
    firewall_f_f_fss_apply_delimit_e,
    firewall_f_f_memory_array_increase_e,
    firewall_f_f_memory_array_increase_by_e,
    firewall_f_f_string_dynamic_append_e,
    firewall_f_f_string_dynamic_partial_append_e,
    firewall_f_f_string_dynamic_partial_append_nulless_e,
    firewall_f_f_string_dynamic_terminate_after_e,
    firewall_f_f_thread_create_e,
    firewall_f_firewall_operate_process_rules_e,
    firewall_f_fll_execute_program_e,
    firewall_f_fll_fss_basic_read_e,
    firewall_f_fll_fss_basic_list_read_e,
    firewall_f_fll_fss_extended_read_e,
    firewall_f_fll_program_parameter_process_context_standard_e,
    firewall_f_fll_program_parameter_process_verbosity_standard_e,
  }; // enum
#endif // _di_firewall_f_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_common_print_h
