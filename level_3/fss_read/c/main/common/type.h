/**
 * FLL - Level 3
 *
 * Project: FSS Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_read_common_type_h
#define _fss_read_common_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The fss read main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * For all function pointers on this structure, the main variable must be of type fss_read_main_t.
 *
 * flag: Flags passed to the main function.
 *
 * status_thread: A status used eclusively by the threaded signal handler.
 * state:         The state data used when processing the FSS data.
 *
 * range: A range used as a buffer during processing.
 *
 * quote:    This holds the quote used during processing.
 * standard: A human-friendly string describing the standard in use, such as "FSS-0000 (Basic)".
 *
 * escaped: A buffer used for escaping strings during processing.
 * block:   A buffer used to storing one or more blocks while processing a file line by line.
 * buffer:  A buffer used during processing the file.
 * prepend: A string to prepend to each multi-line Content.
 *
 * ignoress:  An array of range sets passed as values to the "--ignore" parameter or via the input pipe.
 * objects:   An array of objects passed as values to the "--object" parameter or via the input pipe.
 * contentss: An array of content sets passed as values to the "--content" parameter or via the input pipe.
 *
 * object:   A pointer to a specific Object used during processing.
 * content:  A pointer to a specific Content used during processing.
 * contents: A pointer to a specific set of Content used during processing.
 *
 * process_content: Process a single Content.
 * process_help:    Process help (generally printing help).
 * process_normal:  Process normally (data from parameters and files).
 * process_object:  Process a single Object.
 * process_pipe:    Process using the data from input pipe.
 * process_set:     Process a set of Object and one or more Content.
 */
#ifndef _di_fss_read_setting_t_
  typedef struct {
    uint16_t flag;

    f_status_t status_thread;
    f_state_t state;

    f_string_range_t range;

    f_string_static_t quote;
    f_string_static_t standard;

    f_string_dynamic_t escaped;
    f_string_dynamic_t block;
    f_string_dynamic_t buffer;
    f_string_dynamic_t prepend;

    f_string_rangess_t ignoress;
    f_string_dynamics_t objects;
    f_string_dynamicss_t contentss;

    f_string_ranges_t *ignores;
    f_string_static_t *object;
    f_string_static_t *content;
    f_string_statics_t *contents;

    void (*process_content)(void * const main, const bool last);
    void (*process_help)(void * const main);
    void (*process_normal)(void * const main);
    void (*process_object)(void * const main);
    void (*process_pipe)(void * const main);
    void (*process_set)(void * const main);
  } fss_read_setting_t;

  #define fss_read_setting_t_initialize \
    { \
      fss_read_main_flag_none_e, \
      F_none, \
      macro_f_state_t_initialize_1(fss_read_allocation_large_d, fss_read_allocation_small_d, F_none, 0, 0, &fll_program_standard_signal_handle, 0, 0, 0, 0), \
      f_string_range_t_initialize, \
      f_string_static_t_initialize, \
      f_string_static_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_rangess_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_dynamicss_t_initialize, \
      0, \
      0, \
      0, \
      0, \
      0, \
      0, \
      0, \
      0, \
      0, \
      0, \
    }
#endif // _di_fss_read_setting_t_

/**
 * The main program data as a single structure.
 *
 * program: The main program data.
 * setting: The settings data.
 */
#ifndef _di_fss_read_main_t_
  typedef struct {
    fll_program_data_t program;
    fss_read_setting_t setting;
  } fss_read_main_t;

  #define fss_read_main_t_initialize \
    { \
      fll_program_data_t_initialize, \
      fss_read_setting_t_initialize, \
    }
#endif // _di_fss_read_main_t_

/**
 * Deallocate main program data.
 *
 * @param setting_make
 *   The make setting data.
 *
 *   This does not alter data_make.main.setting.state.status.
 */
#ifndef _di_fss_read_main_data_delete_
  extern void fss_read_main_delete(fss_read_main_t * const main);
#endif // _di_fss_read_main_data_delete_

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
#ifndef _di_fss_read_setting_delete_
  extern f_status_t fss_read_setting_delete(fss_read_setting_t * const setting);
#endif // _di_fss_read_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_read_common_type_h
