/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_fss_basic_list_read_h
#define _PRIVATE_fss_basic_list_read_h

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
    f_string_length_t depth;

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
    f_macro_string_dynamic_t_clear(structure.value_name)

  #define macro_fss_basic_list_read_depth_t_delete(status, structure)  f_macro_string_dynamic_t_delete(status, structure.value_name)
  #define macro_fss_basic_list_read_depth_t_destroy(status, structure) f_macro_string_dynamic_t_destroy(status, structure.value_name)

  #define macro_fss_basic_list_read_depth_t_delete_simple(structure)  f_macro_string_dynamic_t_delete_simple(structure.value_name)
  #define macro_fss_basic_list_read_depth_t_destroy_simple(structure) f_macro_string_dynamic_t_destroy_simple(structure.value_name)
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

  #define macro_fss_basic_list_read_depths_t_clear(depths) f_macro_memory_structure_t_clear(depths)

  #define macro_fss_basic_list_read_depths_t_new(status, depths, length) f_macro_memory_structure_t_new(status, depths, fss_basic_list_read_depth_t, length)

  #define macro_fss_basic_list_read_depths_t_delete(status, depths) \
    status = F_none; \
    depths.used = depths.size; \
    while (depths.used > 0) { \
      depths.used--; \
      macro_fss_basic_list_read_depth_t_delete(status, depths.array[depths.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) f_macro_memory_structure_t_delete(depths, fss_basic_list_read_depth_t)

  #define macro_fss_basic_list_read_depths_t_destroy(status, depths) \
    status = F_none; \
    depths.used = depths.size; \
    while (depths.used > 0) { \
      depths.used--; \
      macro_fss_basic_list_read_depth_t_destroy(status, depths.array[depths.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) f_macro_memory_structure_t_destroy(depths, fss_basic_list_read_depth_t)

  #define macro_fss_basic_list_read_depths_t_delete_simple(depths) \
    depths.used = depths.size; \
    while (depths.used > 0) { \
      depths.used--; \
      macro_fss_basic_list_read_depth_t_delete_simple(depths.array[depths.used]); \
    } \
    if (!depths.used) f_macro_memory_structure_t_delete_simple(depths, fss_basic_list_read_depth_t)

  #define macro_fss_basic_list_read_depths_t_destroy_simple(depths) \
    depths.used = depths.size; \
    while (depths.used > 0) { \
      depths.used--; \
      macro_fss_basic_list_read_depth_t_destroy_simple(depths.array[depths.used]); \
    } \
    if (!depths.used) f_macro_memory_structure_t_destroy_simple(depths, fss_basic_list_read_depth_t)

  #define macro_fss_basic_list_read_depths_t_resize(status, depths, new_length) \
    status = F_none; \
    if (new_length < depths.size) { \
      f_array_length_t i = depths.size - new_length; \
      for (; i < depths.size; i++) { \
        macro_fss_basic_list_read_depth_t_delete(status, depths.array[i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & depths.array, sizeof(fss_basic_list_read_depth_t), depths.size, new_length); \
    if (status == F_none) { \
      if (new_length > depths.size) { \
        f_array_length_t i = depths.size; \
        for (; i < new_length; i++) { \
          memset(&depths.array[i], 0, sizeof(fss_basic_list_read_depth_t)); \
        } \
      } \
      depths.size = new_length; \
      if (depths.used > depths.size) depths.used = new_length; \
    }

  #define macro_fss_basic_list_read_depths_t_adjust(status, depths, new_length) \
    status = F_none; \
    if (new_length < depths.size) { \
      f_array_length_t i = depths.size - new_length; \
      for (; i < depths.size; i++) { \
        macro_fss_basic_list_read_depth_t_delete(status, depths.array[i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & depths.array, sizeof(fss_basic_list_read_depth_t), depths.size, new_length); \
    if (status == F_none) { \
      if (new_length > depths.size) { \
        f_array_length_t i = depths.size; \
        for (; i < new_length; i++) { \
          memset(&depths.array[i], 0, sizeof(fss_basic_list_read_depth_t)); \
        } \
      } \
      depths.size = new_length; \
      if (depths.used > depths.size) depths.used = new_length; \
    }
#endif // _di_fss_basic_list_read_depths_t_

/**
 * Pre-process the parameters, parsing out and handling the depth and depth related parameters.
 *
 * Will handle depth-sensitive parameter conflicts, such as --name being used with --at (which is not allowed).
 *
 * @param arguments
 *   The console arguments to pre-process.
 * @param data
 *   The program specific data.
 * @param depths
 *   This stores the pre-processed depth parameters.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fss_basic_list_read_main_preprocess_depth_
  extern f_return_status fss_basic_list_read_main_preprocess_depth(const f_console_arguments_t arguments, const fss_basic_list_read_data_t data, fss_basic_list_read_depths_t *depths) f_gcc_attribute_visibility_internal;
#endif // _di_fss_basic_list_read_main_preprocess_depth_

/**
 * Process a given file.
 *
 * @param arguments
 *   The console arguments passed to the program.
 * @param data
 *   The program specific data.
 * @param file_name
 *   The name of the file being processed.
 * @param depths
 *   The processed depth parameters.
 * @param delimits
 *   An array of delimits detected during processing.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_basic_list_read_main_preprocess_depth()
 */
#ifndef _di_fss_basic_list_read_main_process_file_
  extern f_return_status fss_basic_list_read_main_process_file(const f_console_arguments_t arguments, fss_basic_list_read_data_t *data, const f_string_t file_name, const fss_basic_list_read_depths_t depths, f_fss_delimits_t *delimits) f_gcc_attribute_visibility_internal;
#endif // _di_fss_basic_list_read_main_process_file_

/**
 * Print the end of an object (which is essentially the start of a content).
 *
 * @param data
 *   The program specific data.
 */
#ifndef _di_fss_basic_list_read_print_object_end_
  extern void fss_basic_list_read_print_object_end(const fss_basic_list_read_data_t data) f_gcc_attribute_visibility_internal;
#endif // _di_fss_basic_list_read_print_object_end_

/**
 * Print the end of an content.
 *
 * @param data
 *   The program specific data.
 */
#ifndef _di_fss_basic_list_read_print_content_end_
  extern void fss_basic_list_read_print_content_end(const fss_basic_list_read_data_t data) f_gcc_attribute_visibility_internal;
#endif // _di_fss_basic_list_read_print_content_end_

/**
 * Print the end of an object/content set.
 *
 * @param data
 *   The program specific data.
 */
#ifndef _di_fss_basic_list_read_print_set_end_
  extern void fss_basic_list_read_print_set_end(const fss_basic_list_read_data_t data) f_gcc_attribute_visibility_internal;
#endif // _di_fss_basic_list_read_print_set_end_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_fss_basic_list_read_h
