/**
 * FLL - Level 3
 *
 * Project: FSS Basic List Read
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
#ifndef _di_fss_basic_list_read_depth_t_
  typedef struct {
    f_array_length_t depth;

    f_array_length_t index_at;
    f_array_length_t index_name;

    f_number_unsigned_t value_at;
    f_string_dynamic_t  value_name;
  } fss_basic_list_read_depth_t;

  #define fss_basic_list_read_depth_t_initialize \
    { \
      0, \
      0, \
      0, \
      0, \
      f_string_dynamic_t_initialize, \
    }

  #define macro_fss_basic_list_read_depth_t_clear(structure) \
    structure.depth = 0; \
    structure.index_at = 0; \
    structure.index_name = 0; \
    structure.value_at = 0; \
    macro_f_string_dynamic_t_clear(structure.value_name)

  #define macro_fss_basic_list_read_depth_t_delete_simple(structure)  macro_f_string_dynamic_t_delete_simple(structure.value_name);
#endif // _di_fss_basic_list_read_depth_t_

/**
 * An array of depth parameters.
 *
 * array: the array of depths.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_fss_basic_list_read_depths_t_
  typedef struct {
    fss_basic_list_read_depth_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } fss_basic_list_read_depths_t;

  #define fss_basic_list_read_depths_t_initialize { 0, 0, 0 }

  #define macro_fss_basic_list_read_depths_t_clear(depths) macro_f_memory_structure_clear(depths)

  #define macro_fss_basic_list_read_depths_t_delete_simple(depths) \
    depths.used = depths.size; \
    while (depths.used > 0) { \
      depths.used--; \
      macro_fss_basic_list_read_depth_t_delete_simple(depths.array[depths.used]); \
    } \
    if (!depths.used) macro_f_memory_structure_delete_simple(depths, fss_basic_list_read_depth_t)

  #define macro_fss_basic_list_read_depths_t_resize(status, depths, new_length) \
    status = F_none; \
    if (new_length < depths.size) { \
      f_array_length_t i = depths.size - new_length; \
      for (; i < depths.size; i++) { \
        macro_fss_basic_list_read_depth_t_delete_simple(depths.array[i]); \
      } \
    } \
    if (status == F_none) status = f_memory_resize(depths.size, new_length, sizeof(fss_basic_list_read_depth_t), (void **) & depths.array); \
    if (status == F_none) { \
      depths.size = new_length; \
      if (depths.used > depths.size) depths.used = new_length; \
    }

  #define macro_fss_basic_list_read_depths_t_adjust(status, depths, new_length) \
    status = F_none; \
    if (new_length < depths.size) { \
      f_array_length_t i = depths.size - new_length; \
      for (; i < depths.size; i++) { \
        macro_fss_basic_list_read_depth_t_delete_simple(depths.array[i]); \
      } \
    } \
    if (status == F_none) status = f_memory_adjust(depths.size, new_length, sizeof(fss_basic_list_read_depth_t), (void **) & depths.array); \
    if (status == F_none) { \
      depths.size = new_length; \
      if (depths.used > depths.size) depths.used = new_length; \
    }
#endif // _di_fss_basic_list_read_depths_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
