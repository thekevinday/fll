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
#ifndef _di_fss_basic_list_read_depth_
  typedef struct {
    f_string_length depth;

    f_array_length index_at;
    f_array_length index_name;

    f_number_unsigned value_at;
    f_string_dynamic  value_name;
  } fss_basic_list_read_depth;

  #define fss_basic_list_read_depth_initialize \
    { \
      0, \
      0, \
      0, \
      0, \
      f_string_dynamic_initialize, \
    }

  #define macro_fss_basic_list_read_depth_clear(structure) \
    structure.depth = 0; \
    structure.index_at = 0; \
    structure.index_name = 0; \
    structure.value_at = 0; \
    f_macro_string_dynamic_clear(structure.value_name)

  #define macro_fss_basic_list_read_depth_delete(status, structure)  f_macro_string_dynamic_delete(status, structure.value_name)
  #define macro_fss_basic_list_read_depth_destroy(status, structure) f_macro_string_dynamic_destroy(status, structure.value_name)

  #define macro_fss_basic_list_read_depth_delete_simple(structure)  f_macro_string_dynamic_delete_simple(structure.value_name)
  #define macro_fss_basic_list_read_depth_destroy_simple(structure) f_macro_string_dynamic_destroy_simple(structure.value_name)
#endif // _di_fss_basic_list_read_depth_

/**
 * An array of depth parameters.
 *
 * array: the array of depths.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_fss_basic_list_read_depths_
  typedef struct {
    fss_basic_list_read_depth *array;

    f_array_length size;
    f_array_length used;
  } fss_basic_list_read_depths;

  #define fss_basic_list_read_depths_initialize { 0, 0, 0 }

  #define macro_fss_basic_list_read_depths_clear(depths) f_macro_memory_structure_clear(depths)

  #define macro_fss_basic_list_read_depths_new(status, depths, length) f_macro_memory_structure_new(status, depths, fss_basic_list_read_depth, length)

  #define macro_fss_basic_list_read_depths_delete(status, depths) \
    status = F_none; \
    depths.used = depths.size; \
    while (depths.used > 0) { \
      depths.used--; \
      macro_fss_basic_list_read_depth_delete(status, depths.array[depths.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) f_macro_memory_structure_delete(depths, fss_basic_list_read_depth)

  #define macro_fss_basic_list_read_depths_destroy(status, depths) \
    status = F_none; \
    depths.used = depths.size; \
    while (depths.used > 0) { \
      depths.used--; \
      macro_fss_basic_list_read_depth_destroy(status, depths.array[depths.used]); \
      if (status != F_none) break; \
    } \
    if (status == F_none) f_macro_memory_structure_destroy(depths, fss_basic_list_read_depth)

  #define macro_fss_basic_list_read_depths_delete_simple(depths) \
    depths.used = depths.size; \
    while (depths.used > 0) { \
      depths.used--; \
      macro_fss_basic_list_read_depth_delete_simple(depths.array[depths.used]); \
    } \
    if (depths.used == 0) f_macro_memory_structure_delete_simple(depths, fss_basic_list_read_depth)

  #define macro_fss_basic_list_read_depths_destroy_simple(depths) \
    depths.used = depths.size; \
    while (depths.used > 0) { \
      depths.used--; \
      macro_fss_basic_list_read_depth_destroy_simple(depths.array[depths.used]); \
    } \
    if (depths.used == 0) f_macro_memory_structure_destroy_simple(depths, fss_basic_list_read_depth)

  #define macro_fss_basic_list_read_depths_resize(status, depths, new_length) \
    status = F_none; \
    if (new_length < depths.size) { \
      f_array_length i = depths.size - new_length; \
      for (; i < depths.size; i++) { \
        macro_fss_basic_list_read_depth_delete(status, depths.array[i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & depths.array, sizeof(fss_basic_list_read_depth), depths.size, new_length); \
    if (status == F_none) { \
      if (new_length > depths.size) { \
        f_array_length i = depths.size; \
        for (; i < new_length; i++) { \
          memset(&depths.array[i], 0, sizeof(fss_basic_list_read_depth)); \
        } \
      } \
      depths.size = new_length; \
      if (depths.used > depths.size) depths.used = new_length; \
    }

  #define macro_fss_basic_list_read_depths_adjust(status, depths, new_length) \
    status = F_none; \
    if (new_length < depths.size) { \
      f_array_length i = depths.size - new_length; \
      for (; i < depths.size; i++) { \
        macro_fss_basic_list_read_depth_delete(status, depths.array[i]); \
        if (status != F_none) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & depths.array, sizeof(fss_basic_list_read_depth), depths.size, new_length); \
    if (status == F_none) { \
      if (new_length > depths.size) { \
        f_array_length i = depths.size; \
        for (; i < new_length; i++) { \
          memset(&depths.array[i], 0, sizeof(fss_basic_list_read_depth)); \
        } \
      } \
      depths.size = new_length; \
      if (depths.used > depths.size) depths.used = new_length; \
    }
#endif // _di_fss_basic_list_read_depths_

/**
 * Print file error messages.
 *
 * @param context
 *   The color context information to use when printing.
 * @param function_name
 *   The name of the function responsible for the error.
 * @param file_name
 *   The name of the file with the error.
 * @param status
 *   The status code representing the error.
 */
#ifndef _di_fss_basic_list_read_print_file_error_
  extern void fss_basic_list_read_print_file_error(const fl_color_context context, const f_string function_name, const f_string file_name, const f_status status) f_gcc_attribute_visibility_internal;
#endif // _di_fss_basic_list_read_print_file_error_

/**
 * Print number parameter argument error messages.
 *
 * @param context
 *   The color context information to use when printing.
 * @param function_name
 *   The name of the function responsible for the error.
 * @param parameter_name
 *   The name of the parameter responsible for the error.
 * @param argument
 *   The value of the argument that is invalid.
 * @param status
 *   The status code representing the error.
 */
#ifndef _di_fss_basic_list_read_print_number_argument_error_
  extern void fss_basic_list_read_print_number_argument_error(const fl_color_context context, const f_string function_name, const f_string parameter_name, const f_string argument, const f_status status) f_gcc_attribute_visibility_internal;
#endif // _di_fss_basic_list_read_print_number_argument_error_

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
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fss_basic_list_read_main_preprocess_depth_
  extern f_return_status fss_basic_list_read_main_preprocess_depth(const f_console_arguments arguments, const fss_basic_list_read_data data, fss_basic_list_read_depths *depths) f_gcc_attribute_visibility_internal;
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
 *
 * @see fss_basic_list_read_main_preprocess_depth()
 */
#ifndef _di_fss_basic_list_read_main_process_file_
  extern f_return_status fss_basic_list_read_main_process_file(const f_console_arguments arguments, fss_basic_list_read_data *data, const f_string file_name, const fss_basic_list_read_depths depths) f_gcc_attribute_visibility_internal;
#endif // _di_fss_basic_list_read_main_process_file_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_fss_basic_list_read_h
