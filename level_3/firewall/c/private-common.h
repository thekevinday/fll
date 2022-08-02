/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_h
#define _PRIVATE_common_h

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  bool is_global;
  bool is_main;
  bool is_stop;
  bool is_lock;

  f_array_length_t device;

  f_string_dynamic_t buffer;
  f_array_length_t chain;
  f_array_lengths_t chain_ids;
  f_fss_objects_t chain_objects;
  f_fss_contents_t chain_contents;
  f_fss_objects_t rule_objects;
  f_fss_contents_t rule_contents;
} firewall_local_data_t;

#define firewall_local_data_t_initialize \
  { \
    F_true, \
    F_false, \
    F_false, \
    F_false, \
    0, \
    f_string_dynamic_t_initialize, \
    0, \
    f_array_lengths_t_initialize, \
    f_fss_objects_t_initialize, \
    f_fss_contents_t_initialize, \
    f_fss_objects_t_initialize, \
    f_fss_contents_t_initialize, \
  }

typedef struct {
  bool has_main;
  bool has_stop;
  bool has_lock;

  f_array_length_t main_at;
  f_array_length_t stop_at;
  f_array_length_t lock_at;
} firewall_reserved_chains_t;

#define firewall_reserved_chains_t_initialize \
  { \
    F_false, \
    F_false, \
    F_false, \
    0, \
    0, \
    0, \
  }

/**
 * The program data.
 *
 * argv:    The argument structure in the progam data parameters for simplifying syntax.
 * main:    The main program data.
 * chains:  a
 * devices: A
 */
#ifndef _di_firewall_data_t_
  typedef struct {
    fll_program_data_t *main;
    f_string_static_t *argv;

    f_string_dynamics_t chains;
    f_string_dynamics_t devices;
  } firewall_data_t;

  #define firewall_data_t_initialize \
    { \
      0, \
      0, \
      f_string_dynamics_t_initialize, \
      f_string_dynamics_t_initialize, \
    }
#endif // _di_firewall_data_t_

/**
 * De-allocate data.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see firewall_main()
 */
#ifndef _di_firewall_data_delete_
  extern f_status_t firewall_data_delete(firewall_data_t * const data);
#endif // _di_firewall_data_delete_

/**
 * Print debug information about tool execution.
 *
 * @param output
 *   The output to print to.
 * @param tool
 *   The iptables tool.
 * @param arguments
 *   The arguments passed to the tool.
 */
extern void firewall_print_debug_tool(const fl_print_t output, const f_string_static_t tool, const f_string_statics_t arguments) F_attribute_visibility_internal_d;

/**
 * Print an memory allocation error.
 *
 * @param output
 *   The output to print to.
 */
extern void firewall_print_error_on_allocation_failure(const fl_print_t output) F_attribute_visibility_internal_d;

/**
 * Print an invalid parameter error for the given function.
 *
 * @param output
 *   The output to print to.
 * @param function
 *   The function that failed.
 */
extern void firewall_print_error_on_invalid_parameter(const fl_print_t output, const char *function) F_attribute_visibility_internal_d;

/**
 * Print an invalid parameter error for the given function.
 *
 * @param output
 *   The output to print to.
 * @param function
 *   The function that failed.
 * @param filename
 *   The name of the file.
 */
extern void firewall_print_error_on_invalid_parameter_for_file(const fl_print_t output, const char *function, const f_string_static_t filename) F_attribute_visibility_internal_d;

/**
 * Print an error about the given operation failed.
 *
 * @param output
 *   The output to print to.
 * @param tool
 *   The iptables tool that failed.
 * @param arguments
 *   The arguments passed to the tool.
 */
extern void firewall_print_error_on_operation(const fl_print_t output, const f_string_static_t tool, const f_string_statics_t arguments) F_attribute_visibility_internal_d;

/**
 * Print an unhandled error for the given function.
 *
 * @param output
 *   The output to print to.
 * @param function
 *   The function that failed.
 * @param status
 *   The failure status code.
 */
extern void firewall_print_error_on_unhandled(const fl_print_t output, const char *function, const f_status_t status) F_attribute_visibility_internal_d;

/**
 * Print an unhandled error for the given function for some given file.
 *
 * @param output
 *   The output to print to.
 * @param function
 *   The function that failed.
 * @param status
 *   The failure status code.
 * @param filename
 *   The name of the file.
 */
extern void firewall_print_error_on_unhandled_for_file(const fl_print_t output, const char *function, const f_status_t status, const f_string_static_t filename) F_attribute_visibility_internal_d;

/**
 * Print a message about a process signal being recieved, such as an interrupt signal.
 *
 * @param data
 *   The program data.
 * @param signal
 *   The signal received.
 */
#ifndef _di_firewall_print_signal_received_
  extern void firewall_print_signal_received(firewall_data_t * const data, const f_status_t signal) F_attribute_visibility_internal_d;
#endif // _di_firewall_print_signal_received_

/**
 * Check to see if a process signal is received.
 *
 * Only signals that are blocked via main.signal will be received.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   A positive number representing a valid signal on signal received.
 *   F_false on no signal received.
 *
 * @see f_signal_read()
 */
#ifndef _di_firewall_signal_received_
  extern f_status_t firewall_signal_received(firewall_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_firewall_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
