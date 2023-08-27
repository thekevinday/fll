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
 * A structure of parameters applied at some depth.
 *
 * depth: The depth number in which this is to be processed at.
 *
 * index_at:   Position of the "--at" parameter value in the argv list, when 0 there is no parameter.
 * index_name: Position of the "--name" parameter value in the argv list, when 0 there is no parameter.
 *
 * value_at:   The value of the "--at" parameter, already processed and ready to use, only when index_at > 0.
 * value_name: The value of the "--name" parameter, already processed and ready to use, only when index_name > 0.
 */
#ifndef _di_fss_read_depth_t_
  typedef struct {
    f_number_unsigned_t depth;

    f_number_unsigned_t index_at;
    f_number_unsigned_t index_name;

    f_number_unsigned_t value_at;
    f_string_dynamic_t value_name;
  } fss_read_depth_t;

  #define fss_read_depth_t_initialize \
    { \
      0, \
      0, \
      0, \
      0, \
      f_string_dynamic_t_initialize, \
    }

  #define macro_fss_read_depth_t_clear(structure) \
    structure.depth = 0; \
    structure.index_at = 0; \
    structure.index_name = 0; \
    structure.value_at = 0; \
    macro_f_string_dynamic_t_clear(structure.value_name)
#endif // _di_fss_read_depth_t_

/**
 * An array of depth parameters.
 *
 * array: The array of depths.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_fss_read_depths_t_
  typedef struct {
    fss_read_depth_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } fss_read_depths_t;

  #define fss_read_depths_t_initialize { 0, 0, 0 }
#endif // _di_fss_read_depths_t_

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

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } fss_read_files_t;

  #define fss_read_files_t_initialize { 0, 0, 0 }
#endif // _di_fss_read_files_t_

/**
 * The FSS read callbacks.
 *
 * process_help:      Process help (generally printing help).
 * process_last_line: Process printing last line if necessary when loading in a file (or pipe).
 * process_normal:    Process normally (data from parameters and files).
 *
 * process_at:      Process at parameter, usually called by the process_normal() callback.
 * process_at_line: Process line parameter for some Object index position, usually called by the process_normal() callback.
 * process_columns: Process columns parameter, usually called by the process_normal() callback.
 * process_load:    Process loading of FSS data from buffer (not to be confused with loading settings), usually called by the process_normal() callback.
 * process_name:    Process name parameter, usually called by the process_normal() callback.
 * process_total:   Process total parameter, usually called by the process_normal() callback.
 *
 * print_at:             Print at the given location, usually called by the process_normal() callback.
 * print_object:         Print the Object, usually called by the process_normal() callback.
 * print_content:        Print the Content, usually called by the process_normal() callback.
 * print_content_ignore: Print the Content ignore character, usually called by several callbacks within the process_normal() callback for a pipe.
 * print_content_next:   Print the Content next (content separator), usually called by several callbacks within the process_normal() callback.
 * print_object_end:     Print the Object end, usually called by several callbacks within the process_normal() callback.
 * print_set_end:        Print the Content set end, usually called by several callbacks within the process_normal() callback.
 */
#ifndef _di_fss_read_callback_t_
  typedef struct {
    void (*process_help)(void * const main);
    void (*process_last_line)(void * const main);
    void (*process_normal)(void * const main);

    void (*process_at)(void * const main, const bool names[], const f_number_unsigneds_t delimits_object, const f_number_unsigneds_t delimits_content);
    void (*process_at_line)(void * const void_main, const f_number_unsigned_t at, const f_number_unsigneds_t delimits_object, const f_number_unsigneds_t delimits_content, f_number_unsigned_t * const line);
    void (*process_columns)(void * const main, const bool names[]);
    void (*process_load)(void * const main);
    void (*process_name)(void * const main, bool names[]);
    void (*process_total)(void * const main, const bool names[]);

    f_status_t (*print_at)(fl_print_t * const print, const f_number_unsigned_t at, const f_number_unsigneds_t delimits_object, const f_number_unsigneds_t delimits_content);
    f_status_t (*print_object)(fl_print_t * const print, const f_number_unsigned_t at, const f_number_unsigneds_t delimits);
    f_status_t (*print_content)(fl_print_t * const print, const f_string_range_t range, const uint8_t quote, const f_number_unsigneds_t delimits);
    f_status_t (*print_content_ignore)(fl_print_t * const print);
    f_status_t (*print_content_next)(fl_print_t * const print);
    f_status_t (*print_object_end)(fl_print_t * const print);
    f_status_t (*print_set_end)(fl_print_t * const print);
  } fss_read_callback_t;

  #define fss_read_callback_t_initialize \
    { \
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
      0, \
      0, \
      0, \
      0, \
      0, \
      0, \
    }
#endif // _di_fss_read_callback_t_

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
 * status_signal: A status used eclusively by the threaded signal handler.
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
 * comments:         The positions within the buffer representing comments.
 * contents:         The positions within the buffer representing Contents.
 * delimits_object:  The positions within the buffer representing Object character delimits.
 * delimits_content: The positions within the buffer representing Content character delimits.
 * nests:            The positions within the buffer representing nested Objects and Contents.
 * objects:          The positions within the buffer representing Objects.
 * quotes_object:    The quotes within the Object structure.
 * quotes_content:   The quotes within the Content structure.
 */
#ifndef _di_fss_read_setting_t_
  typedef struct {
    uint32_t flag;
    uint8_t delimit_mode;

    f_status_t status_signal;
    f_state_t state;

    f_number_unsigned_t delimit_depth;
    f_number_unsigned_t select;
    f_number_unsigned_t line;

    f_string_range_t range;

    fss_read_files_t files;
    fss_read_depths_t depths;

    f_string_static_t standard;
    f_string_dynamic_t buffer;

    f_string_ranges_t comments;
    f_string_rangess_t contents;
    f_number_unsigneds_t delimits_object;
    f_number_unsigneds_t delimits_content;
    f_fss_nest_t nest;
    f_string_ranges_t objects;

    f_uint8s_t quotes_object;
    f_uint8ss_t quotes_content;
  } fss_read_setting_t;

  #define fss_read_setting_t_initialize \
    { \
      fss_read_main_flag_none_e, \
      fss_read_delimit_mode_all_e, \
      F_okay, \
      macro_f_state_t_initialize_1(fss_read_allocation_large_d, fss_read_allocation_small_d, F_okay, 0, 0, &fll_program_standard_signal_handle, 0, 0, 0, 0), \
      0, \
      0, \
      0, \
      f_string_range_t_initialize, \
      fss_read_files_t_initialize, \
      fss_read_depths_t_initialize, \
      f_string_static_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_ranges_t_initialize, \
      f_string_rangess_t_initialize, \
      f_number_unsigneds_t_initialize, \
      f_number_unsigneds_t_initialize, \
      f_fss_nest_t_initialize, \
      f_string_ranges_t_initialize, \
      f_uint8s_t_initialize, \
      f_uint8ss_t_initialize, \
    }
#endif // _di_fss_read_setting_t_

/**
 * The main program data as a single structure.
 *
 * callback: The callback data.
 * program:  The main program data.
 * setting:  The settings data.
 */
#ifndef _di_fss_read_main_t_
  typedef struct {
    fss_read_callback_t callback;
    fll_program_data_t program;
    fss_read_setting_t setting;
  } fss_read_main_t;

  #define fss_read_main_t_initialize \
    { \
      fss_read_callback_t_initialize, \
      fll_program_data_t_initialize, \
      fss_read_setting_t_initialize, \
    }
#endif // _di_fss_read_main_t_

/**
 * Deallocate the read depth.
 *
 * @param depth
 *   The depth to deallocate.
 *
 *   Must not be NULL.
 */
#ifndef _di_fss_read_depth_delete_
  extern void fss_read_depth_delete(fss_read_depth_t * const depth);
#endif // _di_fss_read_depth_delete_

/**
 * Resize the program setting depths data.
 *
 * @param length
 *   The new size to use.
 * @param depths
 *   The depths to resize.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 */
#ifndef _di_fss_read_depths_resize_
  extern f_status_t fss_read_depths_resize(const f_number_unsigned_t length, fss_read_depths_t * const depths);
#endif // _di_fss_read_depths_resize_

/**
 * Resize the program setting files data.
 *
 * @param length
 *   The new size to use.
 * @param files
 *   The files to resize.
 *
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 * @see f_memory_resize()
 */
#ifndef _di_fss_read_files_resize_
  extern f_status_t fss_read_files_resize(const f_number_unsigned_t length, fss_read_files_t * const files);
#endif // _di_fss_read_files_resize_

/**
 * Deallocate main program data.
 *
 * @param main
 *   The program and settings data.
 *
 *   Must not be NULL.
 *   Must be of type fss_read_main_t.
 *
 *   This does not alter main.setting.state.status.
 */
#ifndef _di_fss_read_main_delete_
  extern void fss_read_main_delete(fss_read_main_t * const main);
#endif // _di_fss_read_main_delete_

/**
 * Delete the program main setting data.
 *
 * @param setting
 *   The program main setting data.
 *
 *   Must not be NULL.
 *
 *   This does not alter setting.state.status.
 *
 * @return
 *   F_okay on success.
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
