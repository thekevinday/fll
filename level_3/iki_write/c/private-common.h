/**
 * FLL - Level 3
 *
 * Project: IKI Write
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_h
#define _PRIVATE_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program data.
 *
 * argv:  The argument structure in the progam data parameters for simplifying syntax.
 * main:  The main program data.
 * quote: The quote to use when writing.
 */
#ifndef _di_iki_write_data_t_
  typedef struct {
    fll_program_data_t *main;
    f_string_static_t *argv;

    f_string_static_t quote;
  } iki_write_data_t;

  #define iki_write_data_t_initialize \
    { \
      0, \
      0, \
      f_string_static_t_initialize, \
    }
#endif // _di_iki_write_data_t_

/**
 * Provide common/generic definitions.
 *
 * iki_write_common_allocation_*:
 *   - large: An allocation step used for buffers that are anticipated to have large buffers.
 *   - small: An allocation step used for buffers that are anticipated to have small buffers.
 */
#ifndef _di_iki_write_common_
  #define iki_write_common_allocation_large_d 256
  #define iki_write_common_allocation_small_d 16
#endif // _di_iki_write_common_

/**
 * Deallocate program data.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_iki_write_data_delete_
  extern void iki_write_data_delete(iki_write_data_t *data) F_attribute_visibility_internal_d;
#endif // _di_iki_write_data_delete_

/**
 * Print a message about a process signal being recieved, such as an interrupt signal.
 *
 * @param data
 *   The program data.
 */
#ifndef _di_iki_write_print_signal_received_
  extern void iki_write_print_signal_received(iki_write_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_iki_write_print_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
