/**
 * FLL - Level 3
 *
 * Project: FSS Embedded List Read
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
 * embedded_list_read_common_allocation_*:
 *   - large: An allocation step used for buffers that are anticipated to have large buffers.
 *   - small: An allocation step used for buffers that are anticipated to have small buffers.
 *
 * fss_embedded_list_read_block_*:
 *   - max:        The max block read size before checking for interrupt.
 *   - read_small: The block read size for small files.
 *   - read_large: The block read size for large files.
 */
#ifndef _di_fss_embedded_list_read_common_
  #define fss_embedded_list_read_common_allocation_large_d 2048
  #define fss_embedded_list_read_common_allocation_small_d 128

  #define fss_embedded_list_read_block_max        16777216
  #define fss_embedded_list_read_block_read_small 8192
  #define fss_embedded_list_read_block_read_large 65536
#endif // _di_fss_embedded_list_read_common_

/**
 * A structure of parameters applied at some depth.
 *
 * depth: the depth number in which this is to be processed at.
 *
 * index_at:   position of the "--at" parameter value in the argv list, when 0 there is no parameter.
 * index_name: position of the "--name" parameter value in the argv list, when 0 there is no parameter.
 *
 * value_at:   the value of the "--at" parameter, already processed and ready to use, only when index_at > 0.
 * value_name: the value of the "--name" parameter, already processed and ready to use, only when index_name > 0.
 */
#ifndef _di_fss_embedded_list_read_depth_t_
  typedef struct {
    f_array_length_t depth;

    f_array_length_t index_at;
    f_array_length_t index_name;

    f_number_unsigned_t value_at;
    f_string_dynamic_t  value_name;
  } fss_embedded_list_read_depth_t;

  #define fss_embedded_list_read_depth_t_initialize \
    { \
      0, \
      0, \
      0, \
      0, \
      f_string_dynamic_t_initialize, \
    }

  #define macro_fss_embedded_list_read_depth_t_clear(structure) \
    structure.depth = 0; \
    structure.index_at = 0; \
    structure.index_name = 0; \
    structure.value_at = 0; \
    macro_f_string_dynamic_t_clear(structure.value_name)

  #define macro_fss_embedded_list_read_depth_t_delete_simple(structure)  macro_f_string_dynamic_t_delete_simple(structure.value_name)
#endif // _di_fss_embedded_list_read_depth_t_

/**
 * A structure containing a statically allocated array of booleans and the array length.
 *
 * skip: a statically allocated array representing list items that are to be skipped.
 * used: the length of the statically allocated skip array.
 */
#ifndef _di_fss_embedded_list_read_skip_t_
  typedef struct {
    bool *skip;
    f_array_length_t used;
  } fss_embedded_list_read_skip_t;

  #define fss_embedded_list_read_skip_t_initialize \
    { \
      0, \
      0, \
    }

  #define macro_fss_embedded_list_read_skip_t_initialize(skip, used) \
    { \
      skip, \
      used, \
    }
#endif // _di_fss_embedded_list_read_skip_t_

/**
 * An array of depth parameters.
 *
 * array: the array of depths.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_fss_embedded_list_read_depths_t_
  typedef struct {
    fss_embedded_list_read_depth_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } fss_embedded_list_read_depths_t;

  #define fss_embedded_list_read_depths_t_initialize { 0, 0, 0 }

  #define macro_fss_embedded_list_read_depths_t_clear(depths) macro_f_memory_structure_clear(depths)

  #define macro_fss_embedded_list_read_depths_t_delete_simple(depths) \
    depths.used = depths.size; \
    while (depths.used > 0) { \
      --depths.used; \
      macro_fss_embedded_list_read_depth_t_delete_simple(depths.array[depths.used]); \
    } \
    if (!depths.used) macro_f_memory_structure_delete_simple(depths, fss_embedded_list_read_depth_t)

  #define macro_fss_embedded_list_read_depths_t_resize(status, depths, new_length) \
    status = F_none; \
    if (new_length < depths.size) { \
      f_array_length_t i = depths.size - new_length; \
      for (; i < depths.size; ++i) { \
        macro_fss_embedded_list_read_depth_t_delete_simple(depths.array[i]); \
      } \
    } \
    if (status == F_none) status = f_memory_resize(depths.size, new_length, sizeof(fss_embedded_list_read_depth_t), (void **) & depths.array); \
    if (status == F_none) { \
      depths.size = new_length; \
      if (depths.used > depths.size) depths.used = new_length; \
    }

  #define macro_fss_embedded_list_read_depths_t_adjust(status, depths, new_length) \
    status = F_none; \
    if (new_length < depths.size) { \
      f_array_length_t i = depths.size - new_length; \
      for (; i < depths.size; ++i) { \
        macro_fss_embedded_list_read_depth_t_delete_simple(depths.array[i]); \
      } \
    } \
    if (status == F_none) status = f_memory_adjust(depths.size, new_length, sizeof(fss_embedded_list_read_depth_t), (void **) & depths.array); \
    if (status == F_none) { \
      depths.size = new_length; \
      if (depths.used > depths.size) depths.used = new_length; \
    }
#endif // _di_fss_embedded_list_read_depths_t_

/**
 * The program data.
 *
 * process_pipe: Designate whether or not to process the input pipe.
 * context:      The color context.
 */
#ifndef _di_fss_embedded_list_read_data_t_
  typedef struct {
    fll_program_data_t *main;
    f_string_static_t *argv;

    f_string_dynamic_t buffer;
    f_fss_nest_t nest;

    uint8_t delimit_mode;
    f_array_length_t delimit_depth;
  } fss_embedded_list_read_data_t;

  #define fss_embedded_list_read_data_t_initialize \
    { \
      0, \
      0, \
      f_string_dynamic_t_initialize, \
      f_fss_nest_t_initialize, \
      fss_embedded_list_read_delimit_mode_all_e, \
      0, \
    }
#endif // _di_fss_embedded_list_read_data_t_

/**
 * Deallocate program data.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_embedded_list_read_main()
 */
#ifndef _di_fss_embedded_list_read_data_delete_
  extern f_status_t fss_embedded_list_read_data_delete(fss_embedded_list_read_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_fss_embedded_list_read_data_delete_

/**
 * Print a message about a process signal being recieved, such as an interrupt signal.
 *
 * @param data
 *   The program data.
 */
#ifndef _di_fss_embedded_list_read_print_signal_received_
  extern void fss_embedded_list_read_print_signal_received(fss_embedded_list_read_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_fss_embedded_list_read_print_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
