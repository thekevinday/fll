/**
 * FLL - Level 3
 *
 * Project: FSS Identify
 * API Version: 0.6
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
 * argv:    The argument structure in the progam data parameters for simplifying syntax.
 * current: The current position within the ids, used to determine when the line is matched.
 * line:    The line number to select.
 * names:   The names to select.
 * total:   The total ids across all files.
 */
#ifndef _di_fss_identify_data_t_
  typedef struct {
    f_array_length_t current;
    f_array_length_t line;
    f_array_length_t total;

    f_string_static_t *argv;

    f_string_dynamics_t names;
  } fss_identify_data_t;

  #define fss_identify_data_t_initialize \
    { \
      0, \
      0, \
      0, \
      0, \
      f_string_dynamics_t_initialize, \
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
 */
#ifndef _di_fss_identify_print_signal_received_
  extern void fss_identify_print_signal_received(fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_identify_print_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
