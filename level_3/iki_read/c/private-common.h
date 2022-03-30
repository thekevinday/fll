/**
 * FLL - Level 3
 *
 * Project: IKI Read
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_h
#define _PRIVATE_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Provide common/generic definitions.
 *
 * iki_read_common_allocation_*:
 *   - large: An allocation step used for buffers that are anticipated to have large buffers.
 *   - small: An allocation step used for buffers that are anticipated to have small buffers.
 */
#ifndef _di_iki_read_common_
  #define iki_read_common_allocation_large_d 256
  #define iki_read_common_allocation_small_d 16
#endif // _di_iki_read_common_

/**
 * The program data.
 *
 * argv:   The argument structure in the progam data parameters for simplifying syntax.
 * at:     The processed at parameter value.
 * buffer: The buffer containing the file.
 * line:   The processed line parameter value.
 * main:   The main program data.
 * mode:   The read mode to operate in.
 */
#ifndef _di_iki_read_data_t_
  typedef struct {
    fll_program_data_t *main;
    f_string_static_t *argv;

    uint8_t mode;

    f_number_unsigned_t at;
    f_number_unsigned_t line;

    f_string_dynamic_t buffer;
  } iki_read_data_t;

  #define iki_read_data_t_initialize \
    { \
      0, \
      0, \
      0, \
      0, \
      0, \
      f_string_dynamic_t_initialize, \
    }
#endif // _di_iki_read_data_t_

/**
 * Deallocate program data.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_iki_read_data_delete_
  extern f_status_t iki_read_data_delete(iki_read_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_iki_read_data_delete_

/**
 * Print a message about a process signal being recieved, such as an interrupt signal.
 *
 * @param data
 *   The program data.
 * @param signal
 *   The signal received.
 */
#ifndef _di_iki_read_print_signal_received_
  extern void iki_read_print_signal_received(iki_read_data_t * const data, const f_status_t signal) F_attribute_visibility_internal_d;
#endif // _di_iki_read_print_signal_received_

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
#ifndef _di_iki_read_signal_received_
  extern f_status_t iki_read_signal_received(iki_read_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_iki_read_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
