/**
 * FLL - Level 3
 *
 * Project: IKI Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _iki_read_common_type_h
#define _iki_read_common_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The iki read main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * flag: Flags passed to the main function.
 *
 * status_thread: A status used eclusively by the threaded signal handler.
 * state:         The state data used when processing the FSS data.
 *
 * at:   The position representing the "at" index.
 * line: The position representing the "line" index.
 *
 * buffer: A buffer used for loading the files and other miscellaneous tasks.
 * name:   A string representing the IKI vocabulary name being selected.
 * files:  An array of all files to process (except for the input pipe).
 *
 * replace:    A map containing the Vocabulary name and its replacement as the value.
 * reassign:   A triple containing the Vocabulary name (a), Content to match (b), and the string used as the reassign (c).
 * substitute: A triple containing the Vocabulary name (a), Content to match (b), and the string used as the substitute (c).
 * wrap:       A triple containing the Vocabulary name (a), the string to prepend (b), and the string to append (c).
 *
 * map_replaces: A pointer representing an array with length of setting->data.vocabulary.used mapping the vocabulary location to a replace array location.
 * map_wraps:    A pointer representing an array with length of setting->data.vocabulary.used mapping the vocabulary location to a wrap array location.
 *
 * data: The loaded IKI data.
 */
#ifndef _di_iki_read_setting_t_
  typedef struct {
    uint16_t flag;

    f_status_t status_thread;
    f_state_t state;

    f_array_length_t at;
    f_array_length_t line;

    f_string_dynamic_t buffer;
    f_string_dynamics_t names;
    f_string_dynamics_t files;

    f_string_maps_t replace;
    f_string_triples_t reassign;
    f_string_triples_t substitute;
    f_string_triples_t wrap;

    f_array_length_t *map_replaces;
    f_array_length_t *map_wraps;

    f_iki_data_t data;
  } iki_read_setting_t;

  #define iki_read_setting_t_initialize \
    { \
      iki_read_main_flag_none_e, \
      F_none, \
      macro_f_state_t_initialize_1(iki_read_allocation_large_d, iki_read_allocation_small_d, F_none, 0, 0, 0, 0, 0, 0), \
      0, \
      0, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_maps_t_initialize, \
      f_string_triples_t_initialize, \
      f_string_triples_t_initialize, \
      f_string_triples_t_initialize, \
      0, \
      0, \
      f_iki_data_t_initialize, \
    }
#endif // _di_iki_read_setting_t_

/**
 * The main program data as a single structure.
 *
 * program: The main program data.
 * setting: The settings data.
 */
#ifndef _di_iki_read_main_t_
  typedef struct {
    fll_program_data_t program;
    iki_read_setting_t setting;
  } iki_read_main_t;

  #define iki_read_main_t_initialize \
    { \
      fll_program_data_t_initialize, \
      iki_read_setting_t_initialize, \
    }
#endif // _di_iki_read_main_t_

/**
 * Deallocate main program data.
 *
 * @param setting_make
 *   The make setting data.
 *
 *   This does not alter data_make.main.setting.state.status.
 */
#ifndef _di_iki_read_main_data_delete_
  extern void iki_read_main_delete(iki_read_main_t * const main);
#endif // _di_iki_read_main_data_delete_

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
#ifndef _di_iki_read_setting_delete_
  extern f_status_t iki_read_setting_delete(iki_read_setting_t * const setting);
#endif // _di_iki_read_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_read_common_type_h
