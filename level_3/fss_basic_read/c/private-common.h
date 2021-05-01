/**
 * FLL - Level 3
 *
 * Project: FSS Basic Read
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_common_h
#define _PRIVATE_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure of parameters applied at some depth.
 *
 * depth: the depth number in which this is to be processed at.
 *
 * index_at: position of the "--at" parameter value in the argv list, when 0 there is no parameter.
 * index_name: position of the "--name" parameter value in the argv list, when 0 there is no parameter.
 *
 * value_at: the value of the "--at" parameter, already processed and ready to use, only when index_at > 0.
 * value_name: the value of the "--name" parameter, already processed and ready to use, only when index_name > 0.
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
 * array: the array of depths.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
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
 * name: The name of the file representing the range. Set string to NULL to represent the STDIN pipe.
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
 * An array of depth parameters.
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
 * Fully deallocate all memory for the given depth without caring about return status.
 *
 * @param depth
 *   The depth to deallocate.
 */
#ifndef _di_fss_basic_read_depth_delete_simple_
  extern void fss_basic_read_depth_delete_simple(fss_basic_read_depth_t *depth) f_attribute_visibility_internal;
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
  extern f_status_t fss_basic_read_depths_resize(const f_array_length_t length, fss_basic_read_depths_t *depths) f_attribute_visibility_internal;
#endif // _di_fss_basic_read_depths_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
