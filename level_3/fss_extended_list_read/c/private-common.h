/**
 * FLL - Level 3
 *
 * Project: Extended List Read
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_common_h
#define _PRIVATE_common_h

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Provide common/generic definitions.
 *
 * extended_list_read_common_allocation_*:
 *   - large: An allocation step used for buffers that are anticipated to have large buffers.
 *   - small: An allocation step used for buffers that are anticipated to have small buffers.
 */
#ifndef _di_fss_extended_list_read_common_
  #define fss_extended_list_read_common_allocation_large 256
  #define fss_extended_list_read_common_allocation_small 16
#endif // _di_fss_extended_list_read_common_

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
#ifndef _di_fss_extended_list_read_depth_t_
  typedef struct {
    f_array_length_t depth;

    f_array_length_t index_at;
    f_array_length_t index_name;

    f_number_unsigned_t value_at;
    f_string_dynamic_t  value_name;
  } fss_extended_list_read_depth_t;

  #define fss_extended_list_read_depth_t_initialize \
    { \
      0, \
      0, \
      0, \
      0, \
      f_string_dynamic_t_initialize, \
    }

  #define macro_fss_extended_list_read_depth_t_clear(structure) \
    structure.depth = 0; \
    structure.index_at = 0; \
    structure.index_name = 0; \
    structure.value_at = 0; \
    macro_f_string_dynamic_t_clear(structure.value_name)
#endif // _di_fss_extended_list_read_depth_t_

/**
 * An array of depth parameters.
 *
 * array: The array of depths.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_fss_extended_list_read_depths_t_
  typedef struct {
    fss_extended_list_read_depth_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } fss_extended_list_read_depths_t;

  #define fss_extended_list_read_depths_t_initialize { 0, 0, 0 }

  #define macro_fss_extended_list_read_depths_t_clear(depths) macro_f_memory_structure_clear(depths)
#endif // _di_fss_extended_list_read_depths_t_

/**
 * A structure for designating where within the buffer a particular file exists, using a statically allocated array.
 *
 * name:  The name of the file representing the range. Set string to NULL to represent the STDIN pipe.
 * range: A range within the buffer representing the file.
 */
#ifndef _di_fss_extended_list_read_file_t_
  typedef struct {
    f_string_t name;
    f_string_range_t range;
  } fss_extended_list_read_file_t;

  #define fss_extended_list_read_file_t_initialize \
    { \
      f_string_t_initialize, \
      f_string_range_t_initialize, \
    }
#endif // _di_fss_extended_list_read_file_t_

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
#ifndef _di_fss_extended_list_read_files_t_
  typedef struct {
    fss_extended_list_read_file_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } fss_extended_list_read_files_t;

  #define fss_extended_list_read_files_t_initialize { 0, 1, 1 }
#endif // _di_fss_extended_list_read_files_t_

/**
 * The data structure for FSS Basic Read.
 *
 * fss_extended_list_read_data_option_*:
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
 * options:          Bitwise flags representing parameters.
 * delimit_mode:     The delimit mode.
 * delimit_depth:    The delimit depth.
 * select:           The Content to select (column number).
 * line:             The Content to select (row number).
 * files:            A statically allocated array of files for designating where in the buffer a file is represented.
 * depths:           The array of parameters for each given depth.
 * buffer:           The buffer containing all loaded files (and STDIN pipe).
 * objects:          The positions within the buffer representing Objects.
 * contents:         The positions within the buffer representing Contents.
 * delimits_object:  The positions within the buffer representing Object character delimits.
 * delimits_content: The positions within the buffer representing Content character delimits.
 */
#ifndef _di_fss_extended_list_read_data_t_
  #define fss_extended_list_read_data_option_at      0x1
  #define fss_extended_list_read_data_option_columns 0x2
  #define fss_extended_list_read_data_option_content 0x4
  #define fss_extended_list_read_data_option_empty   0x8
  #define fss_extended_list_read_data_option_line    0x10
  #define fss_extended_list_read_data_option_name    0x20
  #define fss_extended_list_read_data_option_object  0x40
  #define fss_extended_list_read_data_option_raw     0x80
  #define fss_extended_list_read_data_option_select  0x100
  #define fss_extended_list_read_data_option_total   0x200
  #define fss_extended_list_read_data_option_trim    0x400

  typedef struct {
    uint16_t option;
    uint8_t delimit_mode;
    f_array_length_t delimit_depth;
    f_number_unsigned_t select;
    f_number_unsigned_t line;

    fss_extended_list_read_files_t files;
    fss_extended_list_read_depths_t depths;

    f_string_dynamic_t buffer;
    f_fss_objects_t objects;
    f_fss_contents_t contents;
    f_fss_delimits_t delimits_object;
    f_fss_delimits_t delimits_content;
    f_fss_quotes_t quotes;
    f_fss_comments_t comments;
  } fss_extended_list_read_data_t;

  #define fss_extended_list_read_data_t_initialize \
    { \
      0, \
      fss_extended_list_read_delimit_mode_all, \
      0, \
      0, \
      0, \
      fss_extended_list_read_files_t_initialize, \
      fss_extended_list_read_depths_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_fss_objects_t_initialize, \
      f_fss_contents_t_initialize, \
      f_fss_delimits_t_initialize, \
      f_fss_delimits_t_initialize, \
      f_fss_quotes_t_initialize, \
      f_fss_comments_t_initialize, \
    }
#endif // _di_fss_extended_list_read_data_t_

/**
 * Fully deallocate all memory for the given data without caring about return status.
 *
 * @param data
 *   The data to deallocate.
 */
#ifndef _di_fss_extended_list_read_data_delete_simple_
  extern void fss_extended_list_read_data_delete_simple(fss_extended_list_read_data_t *data) f_attribute_visibility_internal;
#endif // _di_fss_extended_list_read_data_delete_simple_

/**
 * Fully deallocate all memory for the given depth without caring about return status.
 *
 * @param depth
 *   The depth to deallocate.
 */
#ifndef _di_fss_extended_list_read_depth_delete_simple_
  extern void fss_extended_list_read_depth_delete_simple(fss_extended_list_read_depth_t *depth) f_attribute_visibility_internal;
#endif // _di_fss_extended_list_read_depth_delete_simple_

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
 *   Errors (with error bit) from: fss_extended_list_read_depths_increase().
 *
 * @see f_memory_resize()
 *
 * @see fss_extended_list_read_depth_delete_simple()
 * @see fss_extended_list_read_depths_increase()
 */
#ifndef _di_fss_extended_list_read_depths_resize_
  extern f_status_t fss_extended_list_read_depths_resize(const f_array_length_t length, fss_extended_list_read_depths_t *depths) f_attribute_visibility_internal;
#endif // _di_fss_extended_list_read_depths_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
