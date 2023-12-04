/**
 * FLL - Level 3
 *
 * Project: Control
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _control_common_type_h
#define _control_common_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The control cache.
 *
 * large:  A buffer for storing large sets of data.
 * small:  A buffer for storing small sets of data.
 * packet: A buffer for storing the send packet or the response payload.
 *
 * objects:  An array of ranges representing objects.
 * contents: An array of ranges representing contents.
 * delimits: An array of ranges representing delimits.
 *
 * packet_objects:  The FSS Objects for a packet.
 * packet_contents: The FSS Contents for a packet.
 *
 * header_objects:  The FSS Objects for a packet payload header.
 * header_contents: The FSS Contents for a packet payload header.
 *
 * delimits: The delimits cache.
 */
#ifndef _di_control_cache_t_
  typedef struct {
    f_string_dynamic_t large;
    f_string_dynamic_t small;
    f_string_dynamic_t packet;

    f_ranges_t objects;
    f_rangess_t contents;
    f_number_unsigneds_t delimits;

    f_ranges_t packet_objects;
    f_rangess_t packet_contents;

    f_ranges_t header_objects;
    f_rangess_t header_contents;
  } control_cache_t;

  #define control_cache_t_initialize \
    { \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_ranges_t_initialize, \
      f_rangess_t_initialize, \
      f_number_unsigneds_t_initialize, \
      f_ranges_t_initialize, \
      f_rangess_t_initialize, \
      f_ranges_t_initialize, \
      f_rangess_t_initialize, \
    }
#endif // _di_control_cache_t_

/**
 * The packet payload header data.
 *
 * The FSS-000E (Payload) supports multiple objects, but the Control packet does not support this, yet.
 *
 * action: The action type code, for any valid action (see: control_action_types enumeration).
 * type:   The packet type represented by the payload packet.
 * status: The status code represented by the payload packet.
 * length: The length of the payload content within the payload packet.
 */
#ifndef _di_control_payload_header_t_
  typedef struct {
    uint8_t action;
    uint8_t type;
    f_status_t status;
    uint16_t length;
  } control_payload_header_t;

  #define control_payload_header_t_initialize \
    { \
      0, \
      0, \
      f_status_t_initialize, \
      f_number_unsigned_t_initialize, \
    }
#endif // _di_control_payload_header_t_

/**
 * The control main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * Properties:
 *   - flag:       Flags passed to the main function.
 *   - action:     The action type code.
 *   - size_write: The write size of a packet request or response.
 *
 *   - status_signal: A status used eclusively by the threaded signal handler.
 *   - state:         The state data used when processing the data.
 *
 *   - range:  A range for any particular use.
 *   - socket: A socket used to connect to the controller.
 *
 *   - name_socket:   The name of the socket file.
 *   - path_settings: The path to the settings file.
 *   - path_socket:   The path to the socket file.
 *   - actions:       The requested actions.
 */
#ifndef _di_control_setting_t_
  typedef struct {
    uint16_t flag;
    uint8_t action;
    f_number_unsigned_t size_write;

    f_status_t status_signal;
    f_state_t state;

    f_range_t range;
    f_socket_t socket;

    f_string_dynamic_t name_socket;
    f_string_dynamic_t path_settings;
    f_string_dynamic_t path_socket;
    f_string_dynamics_t actions;
  } control_setting_t;

  #define control_setting_t_initialize \
    { \
      control_main_flag_none_e, \
      0, \
      0, \
      F_okay, \
      f_state_t_initialize, \
      f_range_t_initialize, \
      f_socket_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamics_t_initialize, \
    }
#endif // _di_control_setting_t_

/**
 * The main program data as a single structure.
 *
 * Properties:
 *   - program: The main program data.
 *   - setting: The settings data.
 *   - cache:   The cache data.
 */
#ifndef _di_control_main_t_
  typedef struct {
    fll_program_data_t program;
    control_setting_t setting;
    control_cache_t cache;
  } control_main_t;

  #define control_main_t_initialize \
    { \
      fll_program_data_t_initialize, \
      control_setting_t_initialize, \
      control_cache_t_initialize, \
    }
#endif // _di_control_main_t_

/**
 * Deallocate main program data.
 *
 * @param setting_make
 *   The make setting data.
 *
 *   This does not alter main.setting.state.status.
 *
 * @see f_memory_array_resize()
 * @see f_memory_arrays_resize()
 * @see fll_program_data_delete()
 */
#ifndef _di_control_main_delete_
  extern void control_main_delete(control_main_t * const main);
#endif // _di_control_main_delete_

/**
 * Delete the program main setting data.
 *
 * @param setting
 *   The program main setting data.
 *
 *   This does not alter setting.state.status.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_memory_array_resize()
 * @see f_memory_arrays_resize()
 */
#ifndef _di_control_setting_delete_
  extern f_status_t control_setting_delete(control_setting_t * const setting);
#endif // _di_control_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _control_common_type_h
