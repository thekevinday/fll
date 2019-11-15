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
 * parameter: the index representing the parameter enum of either the "at" parameter or the "name" parameter.
 * position: the parameter position index within the argv representing the value associated with the designated parameter.
 */
#ifndef _di_fss_extended_read_depth_
  typedef struct {
    f_string_length depth;

    f_array_length index_at;
    f_array_length index_name;

    f_number_unsigned value_at;
    f_string          value_name;
  } fss_extended_read_depth;

  #define fss_extended_read_depth_initialize \
    { \
      0, \
      0, \
      0, \
      0, \
      f_string_initialize, \
    }
#endif // _di_fss_extended_read_depth_

/**
 * An array of depth parameters.
 *
 * array: the array of depths.
 * size: total amount of allocated space.
 * used: total number of allocated spaces used.
 */
#ifndef _di_fss_extended_read_depths_
  typedef struct {
    fss_extended_read_depth *array;

    f_array_length size;
    f_array_length used;
  } fss_extended_read_depths;

  #define fss_extended_read_depths_initialize { 0, 0, 0 }

  #define macro_fss_extended_read_depths_clear(depths) f_macro_memory_structure_clear(depths)

  #define macro_fss_extended_read_depths_new(status, depths, length) f_macro_memory_structure_new(status, depths, fss_extended_read_depth, length)

  #define macro_fss_extended_read_depths_delete(status, depths) f_macro_memory_structure_delete(status, depths, fss_extended_read_depth)
  #define macro_fss_extended_read_depths_destroy(status, depths) f_macro_memory_structure_destroy(status, depths, fss_extended_read_depth)

  #define macro_fss_extended_read_depths_resize(status, depths, new_length) f_macro_memory_structure_resize(status, depths, fss_extended_read_depth, new_length)
  #define macro_fss_extended_read_depths_adjust(status, depths, new_length) f_macro_memory_structure_adjust(status, depths, fss_extended_read_depth, new_length)
#endif // _di_fss_extended_read_depths_

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
#ifndef _di_fss_extended_read_print_file_error_
  extern void fss_extended_read_print_file_error(const fl_color_context context, const f_string function_name, const f_string file_name, const f_status status) f_gcc_attribute_visibility_internal;
#endif // _di_fss_extended_read_print_file_error_

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
#ifndef _di_fss_extended_read_print_number_argument_error_
  extern void fss_extended_read_print_number_argument_error(const fl_color_context context, const f_string function_name, const f_string parameter_name, const f_string argument, const f_status status) f_gcc_attribute_visibility_internal;
#endif // _di_fss_extended_read_print_number_argument_error_

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
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fss_extended_read_main_preprocess_depth_
  extern f_return_status fss_extended_read_main_preprocess_depth(const f_console_arguments arguments, const fss_extended_read_data data, fss_extended_read_depths *depths) f_gcc_attribute_visibility_internal;
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
 *
 * @see fss_extended_read_main_preprocess_depth()
 */
#ifndef _di_fss_extended_read_main_process_file_
  extern f_return_status fss_extended_read_main_process_file(const f_console_arguments arguments, fss_extended_read_data *data, const f_string file_name, const fss_extended_read_depths depths) f_gcc_attribute_visibility_internal;
#endif // _di_fss_extended_read_main_process_file_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_fss_extended_read_h
