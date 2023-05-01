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
 * A structure for designating where within the buffer a particular file exists, using a statically allocated array.
 *
 * name:  The name of the file representing the range.
 * range: A range within the buffer representing the file.
 */
#ifndef _di_fss_read_file_t_
  typedef struct {
    f_string_static_t name;
    f_string_range_t range;
  } fss_read_file_t;

  #define fss_read_file_t_initialize \
    { \
      f_string_static_t_initialize, \
      f_string_range_t_initialize, \
    }
#endif // _di_fss_read_file_t_

/**
 * An array of files.
 *
 * This is intended to be defined and used statically allocated and as such no dynamic allocation or dynamic deallocation methods are provided.
 *
 * The STDIN pipe is reserved for index 0 and as such the first index must be reserved and the used should be set to at least 1.
 *
 * array: The array of depths.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_fss_read_files_t_
  typedef struct {
    fss_read_file_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } fss_read_files_t;

  #define fss_read_files_t_initialize { 0, 0, 0 }
#endif // _di_fss_read_files_t_

/**
 * The fss read main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * For all function pointers on this structure, the main variable must be of type fss_read_main_t.
 *
 * flag:         Flags passed to the main function.
 * delimit_mode: The delimit mode.
 *
 * status_thread: A status used eclusively by the threaded signal handler.
 * state:         The state data used when processing the FSS data.
 *
 * delimit_depth: The delimit depth.
 * select:        The Content to select (column number).
 * line:          The Content to select (row number).
 *
 * range: A range used in conjunction with some buffer during processing.
 *
 * files:  A statically allocated array of files for designating where in the buffer a file is represented.
 * depths: The array of parameters for each given depth.
 *
 * standard: A human-friendly string describing the standard in use, such as "FSS-0000 (Basic)".
 * buffer:   The buffer containing all loaded files (and STDIN pipe).
 *
 * objects:          The positions within the buffer representing Objects.
 * contents:         The positions within the buffer representing Contents.
 * delimits_object:  The positions within the buffer representing Object character delimits.
 * delimits_content: The positions within the buffer representing Content character delimits.
 * comments:         The positions within the buffer representing comments.
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
    uint8_t delimit_mode;

    f_status_t status_thread;
    f_state_t state;

    f_array_length_t delimit_depth;
    f_number_unsigned_t select;
    f_number_unsigned_t line;

    f_string_range_t range;

    fss_read_files_t files;
    fss_read_depths_t depths;

    f_string_static_t standard;
    f_string_dynamic_t buffer;

    f_fss_objects_t objects;
    f_fss_contents_t contents;
    f_fss_delimits_t delimits_object;
    f_fss_delimits_t delimits_content;
    f_fss_comments_t comments;

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
      fss_read_delimit_mode_all_e, \
      F_none, \
      macro_f_state_t_initialize_1(fss_read_allocation_large_d, fss_read_allocation_small_d, F_none, 0, 0, &fll_program_standard_signal_handle, 0, 0, 0, 0), \
      0, \
      0, \
      0, \
      f_string_range_t_initialize, \
      fss_read_files_t_initialize, \
      fss_read_depths_t_initialize, \
      f_string_static_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_fss_objects_t_initialize, \
      f_fss_contents_t_initialize, \
      f_fss_delimits_t_initialize, \
      f_fss_delimits_t_initialize, \
      f_fss_comments_t_initialize, \
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
