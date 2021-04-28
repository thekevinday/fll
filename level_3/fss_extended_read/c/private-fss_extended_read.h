/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_fss_extended_read_h
#define _PRIVATE_fss_extended_read_h

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
#ifndef _di_fss_extended_read_depth_t_
  typedef struct {
    f_array_length_t depth;

    f_array_length_t index_at;
    f_array_length_t index_name;

    f_number_unsigned_t value_at;
    f_string_dynamic_t  value_name;
  } fss_extended_read_depth_t;

  #define fss_extended_read_depth_t_initialize \
    { \
      0, \
      0, \
      0, \
      0, \
      f_string_dynamic_t_initialize, \
    }

  #define fss_extended_read_macro_depth_t_clear(structure) \
    structure.depth = 0; \
    structure.index_at = 0; \
    structure.index_name = 0; \
    structure.value_at = 0; \
    f_macro_string_dynamic_t_clear(structure.value_name)

  #define fss_extended_read_macro_depth_t_delete_simple(structure)  f_macro_string_dynamic_t_delete_simple(structure.value_name)
#endif // _di_fss_extended_read_depth_t_

/**
 * An array of depth parameters.
 *
 * array: the array of depths.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_fss_extended_read_depths_t_
  typedef struct {
    fss_extended_read_depth_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } fss_extended_read_depths_t;

  #define fss_extended_read_depths_t_initialize { 0, 0, 0 }

  #define fss_extended_read_macro_depths_t_clear(depths) f_macro_memory_structure_clear(depths)

  #define fss_extended_read_macro_depths_t_delete_simple(depths) \
    depths.used = depths.size; \
    while (depths.used > 0) { \
      depths.used--; \
      fss_extended_read_macro_depth_t_delete_simple(depths.array[depths.used]); \
    } \
    if (!depths.used) f_macro_memory_structure_delete_simple(depths, fss_extended_read_depth_t)

  #define fss_extended_read_macro_depths_t_resize(status, depths, new_length) \
    status = F_none; \
    if (new_length < depths.size) { \
      f_array_length_t i = depths.size - new_length; \
      for (; i < depths.size; i++) { \
        fss_extended_read_macro_depth_t_delete_simple(depths.array[i]); \
      } \
    } \
    if (status == F_none) status = f_memory_resize(depths.size, new_length, sizeof(fss_extended_read_depth_t), (void **) & depths.array); \
    if (status == F_none) { \
      depths.size = new_length; \
      if (depths.used > depths.size) depths.used = new_length; \
    }

  #define fss_extended_read_macro_depths_t_adjust(status, depths, new_length) \
    status = F_none; \
    if (new_length < depths.size) { \
      f_array_length_t i = depths.size - new_length; \
      for (; i < depths.size; i++) { \
        fss_extended_read_macro_depth_t_delete_simple(depths.array[i]); \
      } \
    } \
    if (status == F_none) status = f_memory_adjust(depths.size, new_length, sizeof(fss_extended_read_depth_t), (void **) & depths.array); \
    if (status == F_none) { \
      depths.size = new_length; \
      if (depths.used > depths.size) depths.used = new_length; \
    }
#endif // _di_fss_extended_read_depths_t_

/**
 * Determine if the given depth is to be delimited or not.
 *
 * @param data
 *   The program specific data.
 * @param depth
 *   The depth to check.
 *
 * @return
 *   F_true if delimited.
 *   F_false if not delimited.
 */
#ifndef _di_fss_extended_read_is_delimited_at_depth_
  extern f_status_t fss_extended_read_is_delimited_at_depth(const fss_extended_read_data_t data, const f_array_length_t depth) f_attribute_visibility_internal;
#endif // _di_fss_extended_read_is_delimited_at_depth_

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
#ifndef _di_fss_extended_read_main_preprocess_depth_
  extern f_status_t fss_extended_read_main_preprocess_depth(const f_console_arguments_t arguments, const fss_extended_read_data_t data, fss_extended_read_depths_t *depths) f_attribute_visibility_internal;
#endif // _di_fss_extended_read_main_preprocess_depth_

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
 * @param objects_delimits
 *   An array of delimits detected during processing, for top-level objects.
 * @param contents_delimits
 *   An array of delimits detected during processing, for contents.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_extended_read_main_preprocess_depth()
 */
#ifndef _di_fss_extended_read_main_process_file_
  extern f_status_t fss_extended_read_main_process_file(const f_console_arguments_t arguments, fss_extended_read_data_t *data, const f_string_t file_name, const fss_extended_read_depths_t depths, f_fss_delimits_t *objects_delimits, f_fss_delimits_t *contents_delimits) f_attribute_visibility_internal;
#endif // _di_fss_extended_read_main_process_file_

/**
 * Print the end of an object (which is essentially the start of a content).
 *
 * @param data
 *   The program specific data.
 */
#ifndef _di_fss_extended_read_print_object_end_
  extern void fss_extended_read_print_object_end(const fss_extended_read_data_t data) f_attribute_visibility_internal;
#endif // _di_fss_extended_read_print_object_end_

/**
 * Print the end of an content.
 *
 * @param data
 *   The program specific data.
 */
#ifndef _di_fss_extended_read_print_content_end_
  extern void fss_extended_read_print_content_end(const fss_extended_read_data_t data) f_attribute_visibility_internal;
#endif // _di_fss_extended_read_print_content_end_

/**
 * Print the end of an object/content set.
 *
 * @param data
 *   The program specific data.
 */
#ifndef _di_fss_extended_read_print_set_end_
  extern void fss_extended_read_print_set_end(const fss_extended_read_data_t data) f_attribute_visibility_internal;
#endif // _di_fss_extended_read_print_set_end_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_fss_extended_read_h
