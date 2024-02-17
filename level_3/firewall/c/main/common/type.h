/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _firewall_common_type_h
#define _firewall_common_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A cache used for during processing.
 *
 * Properties:
 *   - file: The file structure.
 *
 *   - buffer:             A buffer used when proessing the basic objects and contents cache.
 *   - device:             The device.
 *   - ip_list:            The ip list.
 *   - path_file:          The path to a file.
 *   - path_file_specific: The specific path to a file.
 *   - protocol:           The protocol.
 *   - arguments:          The arguments array.
 *
 *   - delimits: The delimits array used when loading FSS data.
 *
 *   - basic_objects:  The FSS Basic Objects.
 *   - basic_contents: The FSS Basic Contents.
 */
#ifndef _di_firewall_cache_t_
  typedef struct {
    f_file_t file;

    f_string_dynamic_t buffer;
    f_string_dynamic_t device;
    f_string_dynamic_t ip_list;
    f_string_dynamic_t path_file;
    f_string_dynamic_t path_file_specific;
    f_string_dynamic_t protocol;
    f_string_dynamics_t arguments;

    f_number_unsigneds_t delimits;

    f_ranges_t basic_objects;
    f_rangess_t basic_contents;
  } firewall_cache_t;

  #define firewall_cache_t_initialize \
    { \
      f_file_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_number_unsigneds_t_initialize, \
      f_ranges_t_initialize, \
      f_rangess_t_initialize, \
    }
#endif // _di_firewall_cache_t_

/**
 * A data used for building and processing firewall rules.
 *
 * Properties:
 *   - is:  Flags used to represent the state in the current set being processed.
 *   - has: Flags used to represent if each at has a position.
 *
 *   - chain:  The chain currently being processed (fom chain_contents).
 *   - device: The device position.
 *   - lock:   The lock position.
 *   - main:   The main position.
 *   - stop:   The stop position.
 *   - range:  A range used during operation processing.
 *
 *   - file:   The file name currently in use.
 *   - buffer: The entire set of chains and rules to operate on.
 *
 *   - chain_ids: The list of chain IDs.
 *
 *   - chain_objects:  The list of chain Objects.
 *   - rule_objects:   The list of rule Objects.
 *   - chain_contents: The list of chain Contents.
 *   - rule_contents:  The list of rule Contents.
 */
#ifndef _di_firewall_data_t_
  typedef struct {
    uint8_t is;
    uint8_t has;

    f_number_unsigned_t chain;
    f_number_unsigned_t device;
    f_number_unsigned_t lock;
    f_number_unsigned_t main;
    f_number_unsigned_t stop;
    f_range_t range;

    f_string_static_t  file;
    f_string_dynamic_t buffer;

    f_number_unsigneds_t chain_ids;

    f_ranges_t comments;
    f_ranges_t chain_objects;
    f_ranges_t rule_objects;
    f_rangess_t chain_contents;
    f_rangess_t rule_contents;
  } firewall_data_t;

  #define firewall_data_t_initialize \
    { \
      firewall_data_is_none_e, \
      firewall_data_has_none_e, \
      0, \
      0, \
      0, \
      0, \
      0, \
      f_range_t_initialize, \
      f_string_static_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_number_unsigneds_t_initialize, \
      f_ranges_t_initialize, \
      f_ranges_t_initialize, \
      f_ranges_t_initialize, \
      f_rangess_t_initialize, \
      f_rangess_t_initialize, \
    }
#endif // _di_firewall_data_t_

/**
 * The firewall main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * Properties:
 *   - flag: Flags passed to the main function.
 *
 *   - status_signal: A status used eclusively by the threaded signal handler.
 *   - state:         The state information.
 *
 *   - chains:  An array of all chains. @todo probably should be moved into data.
 *   - devices: An array of all devices. @todo probably should be moved into data.
 */
#ifndef _di_firewall_setting_t_
  typedef struct {
    uint16_t flag;

    f_status_t status_signal;
    f_state_t state;

    f_string_dynamics_t chains;
    f_string_dynamics_t devices;
  } firewall_setting_t;

  #define firewall_setting_t_initialize \
    { \
      firewall_main_flag_none_e, \
      F_okay, \
      f_state_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_dynamics_t_initialize, \
    }
#endif // _di_firewall_setting_t_

/**
 * The main program data as a single structure.
 *
 * Properties:
 *   - program: The main program data.
 *   - setting: The settings data.
 *   - data:    The firewall data.
 *   - cache:   The firewall cache.
 */
#ifndef _di_firewall_main_t_
  typedef struct {
    fll_program_data_t program;
    firewall_setting_t setting;
    firewall_data_t data;
    firewall_cache_t cache;
  } firewall_main_t;

  #define firewall_main_t_initialize \
    { \
      fll_program_data_t_initialize, \
      firewall_setting_t_initialize, \
      firewall_data_t_initialize, \
      firewall_cache_t_initialize, \
    }
#endif // _di_firewall_main_t_

/**
 * Deallocate firewall cache.
 *
 * @param cache
 *   The firewall cache.
 *
 *   This does not alter main.setting.state.status.
 */
#ifndef _di_firewall_cache_delete_
  extern void firewall_cache_delete(firewall_cache_t * const cache);
#endif // _di_firewall_cache_delete_

/**
 * Deallocate firewall data.
 *
 * @param data
 *   The firewall data.
 *
 *   This does not alter main.setting.state.status.
 */
#ifndef _di_firewall_data_delete_
  extern void firewall_data_delete(firewall_data_t * const data);
#endif // _di_firewall_data_delete_

/**
 * Deallocate main program data.
 *
 * @param setting_make
 *   The make setting data.
 *
 *   This does not alter main.setting.state.status.
 */
#ifndef _di_firewall_main_delete_
  extern void firewall_main_delete(firewall_main_t * const main);
#endif // _di_firewall_main_delete_

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
 */
#ifndef _di_firewall_setting_delete_
  extern f_status_t firewall_setting_delete(firewall_setting_t * const setting);
#endif // _di_firewall_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_common_type_h
