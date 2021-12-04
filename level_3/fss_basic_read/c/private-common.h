/**
 * FLL - Level 3
 *
 * Project: FSS Basic Read
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
 * basic_read_common_allocation_*:
 *   - large: An allocation step used for buffers that are anticipated to have large buffers.
 *   - small: An allocation step used for buffers that are anticipated to have small buffers.
 */
#ifndef _di_fss_basic_read_common_
  #define fss_basic_read_common_allocation_large_d 256
  #define fss_basic_read_delimit_common_allocation_small_d 16
#endif // _di_fss_basic_read_common_

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
#ifndef _di_fss_basic_read_depth_t_
  typedef struct {
    f_array_length_t depth;

    f_array_length_t index_at;
    f_array_length_t index_name;

    f_number_unsigned_t value_at;
    f_string_dynamic_t  value_name;
  } fss_basic_read_depth_t;

  #define fss_basic_read_depth_t_initialize \
    { \
      0, \
      0, \
      0, \
      0, \
      f_string_dynamic_t_initialize, \
    }

  #define macro_fss_basic_read_depth_t_clear(structure) \
    structure.depth = 0; \
    structure.index_at = 0; \
    structure.index_name = 0; \
    structure.value_at = 0; \
    macro_f_string_dynamic_t_clear(structure.value_name)
#endif // _di_fss_basic_read_depth_t_

/**
 * An array of depth parameters.
 *
 * array: The array of depths.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_fss_basic_read_depths_t_
  typedef struct {
    fss_basic_read_depth_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } fss_basic_read_depths_t;

  #define fss_basic_read_depths_t_initialize { 0, 0, 0 }

  #define macro_fss_basic_read_depths_t_clear(depths) macro_f_memory_structure_clear(depths)
#endif // _di_fss_basic_read_depths_t_

/**
 * A structure for designating where within the buffer a particular file exists, using a statically allocated array.
 *
 * name:  The name of the file representing the range. Set string to NULL to represent the STDIN pipe.
 * range: A range within the buffer representing the file.
 */
#ifndef _di_fss_basic_read_file_t_
  typedef struct {
    f_string_t name;
    f_string_range_t range;
  } fss_basic_read_file_t;

  #define fss_basic_read_file_t_initialize \
    { \
      f_string_t_initialize, \
      f_string_range_t_initialize, \
    }
#endif // _di_fss_basic_read_file_t_

/**
 * An array of files.
 *
 * This is intended to be defined and used statically allocated and as such no dynamic allocation or dynamic deallocation methods are provided.
 *
 * The STDIN pipe is reserved for index 0 and as such size and used must be initialized to 1.
 *
 * array: The array of depths.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_fss_basic_read_files_t_
  typedef struct {
    fss_basic_read_file_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } fss_basic_read_files_t;

  #define fss_basic_read_files_t_initialize { 0, 1, 1 }
#endif // _di_fss_basic_read_files_t_

/**
 * The data structure for FSS Basic Read.
 *
 * fss_basic_read_data_option_*:
 *   - at:      The object at the given position is being selected (Think of this as select a row for some Object).
 *   - columns: The total columns found and selected is printed instead of the Content.
 *   - content: The Content is to be printed.
 *   - empty:   Empty Content will be printed (Objects that have no Content will have their empty Content printed).
 *   - line:    A specific Content at a given line is to be selected (Think of this as select a row for some Content).
 *   - name:    A specific Object name has been requested.
 *   - object:  The Object is to be printed.
 *   - raw:     Enable raw printing, where the quotes are printed and no delimits are applied.
 *   - select:  A specific Content at a given position is to be selected (Think of this as select a column for some Content).
 *   - total:   The total lines found and selected is printed instead of the Content.
 *   - trim:    Empty space before and after Objects and Content will not be printed (They will be trimmed).
 *
 * options:       Bitwise flags representing parameters.
 * delimit_mode:  The delimit mode.
 * delimit_depth: The delimit depth.
 * select:        The Content to select (column number).
 * line:          The Content to select (row number).
 * files:         A statically allocated array of files for designating where in the buffer a file is represented.
 * depths:        The array of parameters for each given depth.
 * buffer:        The buffer containing all loaded files (and STDIN pipe).
 * objects:       The positions within the buffer representing Objects.
 * contents:      The positions within the buffer representing Contents.
 * delimits:      The positions within the buffer representing character delimits.
 */
#ifndef _di_fss_basic_read_data_t_
  #define fss_basic_read_data_option_at      0x1
  #define fss_basic_read_data_option_columns 0x2
  #define fss_basic_read_data_option_content 0x4
  #define fss_basic_read_data_option_empty   0x8
  #define fss_basic_read_data_option_line    0x10
  #define fss_basic_read_data_option_name    0x20
  #define fss_basic_read_data_option_object  0x40
  #define fss_basic_read_data_option_raw     0x80
  #define fss_basic_read_data_option_select  0x100
  #define fss_basic_read_data_option_total   0x200
  #define fss_basic_read_data_option_trim    0x400

  typedef struct {
    uint16_t option;
    uint8_t delimit_mode;
    f_array_length_t delimit_depth;
    f_number_unsigned_t select;
    f_number_unsigned_t line;

    fss_basic_read_files_t files;
    fss_basic_read_depths_t depths;

    f_string_dynamic_t buffer;
    f_fss_objects_t objects;
    f_fss_contents_t contents;
    f_fss_delimits_t delimits;
    f_fss_quotes_t quotes;
  } fss_basic_read_data_t;

  #define fss_basic_read_data_t_initialize \
    { \
      0, \
      fss_basic_read_delimit_mode_all, \
      0, \
      0, \
      0, \
      fss_basic_read_files_t_initialize, \
      fss_basic_read_depths_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_fss_objects_t_initialize, \
      f_fss_contents_t_initialize, \
      f_fss_delimits_t_initialize, \
      f_fss_quotes_t_initialize, \
    }
#endif // _di_fss_basic_read_data_t_

/**
 * Fully deallocate all memory for the given data without caring about return status.
 *
 * @param data
 *   The data to deallocate.
 */
#ifndef _di_fss_basic_read_data_delete_simple_
  extern void fss_basic_read_data_delete_simple(fss_basic_read_data_t *data) F_attribute_visibility_internal_d;
#endif // _di_fss_basic_read_data_delete_simple_

/**
 * Fully deallocate all memory for the given depth without caring about return status.
 *
 * @param depth
 *   The depth to deallocate.
 */
#ifndef _di_fss_basic_read_depth_delete_simple_
  extern void fss_basic_read_depth_delete_simple(fss_basic_read_depth_t *depth) F_attribute_visibility_internal_d;
#endif // _di_fss_basic_read_depth_delete_simple_

/**
 * Resize the depth array.
 *
 * @param length
 *   The new size to use.
 * @param depths
 *   The depth array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_memory_resize().
 *
 *   Errors (with error bit) from: fss_basic_read_depths_increase().
 *
 * @see f_memory_resize()
 *
 * @see fss_basic_read_depth_delete_simple()
 * @see fss_basic_read_depths_increase()
 */
#ifndef _di_fss_basic_read_depths_resize_
  extern f_status_t fss_basic_read_depths_resize(const f_array_length_t length, fss_basic_read_depths_t *depths) F_attribute_visibility_internal_d;
#endif // _di_fss_basic_read_depths_resize_

/**
 * Print a message about a process signal being recieved, such as an interrupt signal.
 *
 * @param main
 *   The main program data.
 * @param signal
 *   The signal received.
 */
#ifndef _di_fss_basic_read_print_signal_received_
  extern void fss_basic_read_print_signal_received(fss_basic_read_main_t * const main, const f_status_t signal) F_attribute_visibility_internal_d;
#endif // _di_fss_basic_read_print_signal_received_

/**
 * Check to see if a process signal is received.
 *
 * Only signals that are blocked via main.signal will be received.
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   A positive number representing a valid signal on signal received.
 *   F_false on no signal received.
 *
 * @see f_signal_read()
 */
#ifndef _di_fss_basic_read_signal_received_
  extern f_status_t fss_basic_read_signal_received(fss_basic_read_main_t * const main);
#endif // _di_fss_basic_read_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
