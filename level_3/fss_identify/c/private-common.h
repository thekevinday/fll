/**
 * FLL - Level 3
 *
 * Project: FSS Identify
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_h
#define _PRIVATE_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The data structure for FSS Identify.
 *
 * current: The current position within the ids, used to determine when the line is matched.
 * line:    The line number to select.
 * total:   The total ids across all files.
 * name:    The name to select.
 */
#ifndef _di_fss_identify_data_t_
  typedef struct {
    f_array_length_t current;
    f_array_length_t line;
    f_array_length_t total;

    f_string_dynamic_t name;
  } fss_identify_data_t;

  #define fss_identify_data_t_initialize \
    { \
      0, \
      0, \
      0, \
      f_string_dynamic_t_initialize, \
    }
#endif // _di_fss_identify_data_t_

/**
 * Fully deallocate all memory.
 *
 * @param data
 *   The data to deallocate.
 */
#ifndef _di_fss_identify_data_delete_
  extern void fss_identify_data_delete(fss_identify_data_t *data) F_attribute_visibility_internal_d;
#endif // _di_fss_identify_data_delete_

/**
 * Print a message about a process signal being recieved, such as an interrupt signal.
 *
 * @param main
 *   The main program data.
 * @param signal
 *   The signal received.
 */
#ifndef _di_fss_identify_print_signal_received_
  extern void fss_identify_print_signal_received(fll_program_data_t * const main, const f_status_t signal) F_attribute_visibility_internal_d;
#endif // _di_fss_identify_print_signal_received_

/**
 * Check to see if a process signal is received.
 *
 * Only signals that are blocked via main.signal will be received.
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   A positive number representing a valid signal on signal received.
 *   F_false on no signal received.
 *
 * @see f_signal_read()
 */
#ifndef _di_fss_identify_signal_received_
  extern f_status_t fss_identify_signal_received(fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_identify_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
