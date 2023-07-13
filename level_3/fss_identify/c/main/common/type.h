/**
 * FLL - Level 3
 *
 * Project: FSS Identify
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_identify_common_type_h
#define _fss_identify_common_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The fss identify main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * flag: Flags passed to the main function.
 *
 * current: The current position within the ids, used to determine when the line is matched.
 * line:    The line number to select.
 * total:   The total ids across all files.
 *
 * range: A range used for processing as needed.
 *
 * status_signal: A status used eclusively by the threaded signal handler.
 * state:         The state information.
 *
 * buffer:A buffer used for processing files.
 * ids:   A cache for FLL IDs.
 * names: An array of names to select.
 * files: The files to process.
 */
#ifndef _di_fss_identify_setting_t_
  typedef struct {
    uint16_t flag;

    f_number_unsigned_t current;
    f_number_unsigned_t line;
    f_number_unsigned_t total;

    f_string_range_t range;

    f_status_t status_signal;
    f_state_t state;

    f_file_t file;

    f_string_dynamic_t buffer;
    f_fll_ids_t ids;
    f_string_dynamics_t names;
    f_string_dynamics_t files;
  } fss_identify_setting_t;

  #define fss_identify_setting_t_initialize \
    { \
      fss_identify_main_flag_none_e, \
      0, \
      0, \
      0, \
      f_string_range_t_initialize, \
      F_none, \
      f_state_t_initialize, \
      f_file_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_fll_ids_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_dynamics_t_initialize, \
    }
#endif // _di_fss_identify_setting_t_

/**
 * The main program data as a single structure.
 *
 * program: The main program data.
 * setting: The settings data.
 */
#ifndef _di_fss_identify_main_t_
  typedef struct {
    fll_program_data_t program;
    fss_identify_setting_t setting;
  } fss_identify_main_t;

  #define fss_identify_main_t_initialize \
    { \
      fll_program_data_t_initialize, \
      fss_identify_setting_t_initialize, \
    }
#endif // _di_fss_identify_main_t_

/**
 * Deallocate main program data.
 *
 * @param setting_make
 *   The make setting data.
 *
 *   This does not alter main.setting.state.status.
 */
#ifndef _di_fss_identify_main_delete_
  extern void fss_identify_main_delete(fss_identify_main_t * const main);
#endif // _di_fss_identify_main_delete_

/**
 * Delete the program main setting data.
 *
 * @param setting
 *   The program main setting data.
 *
 *   This does not alter setting.state.status.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fss_identify_setting_delete_
  extern f_status_t fss_identify_setting_delete(fss_identify_setting_t * const setting);
#endif // _di_fss_identify_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_identify_common_type_h
