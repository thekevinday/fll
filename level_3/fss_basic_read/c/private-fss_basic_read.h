/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_fss_basic_read_h
#define _PRIVATE_fss_basic_read_h

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

  #define macro_fss_basic_read_depth_t_delete(status, structure) status = macro_f_string_dynamic_t_delete_simple(structure.value_name);
  #define macro_fss_basic_read_depth_t_delete_simple(structure)  macro_f_string_dynamic_t_delete_simple(structure.value_name);
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

  #define macro_fss_basic_read_depths_t_delete(status, depths) \
    status = F_none; \
    depths.used = depths.size; \
    while (depths.used > 0) { \
      depths.used--; \
      macro_fss_basic_read_depth_t_delete(status, depths.array[depths.used]); \
      if (F_status_is_error(status)) break; \
    } \
    if (status == F_none) macro_f_memory_structure_delete(depths, fss_basic_read_depth_t)

  #define macro_fss_basic_read_depths_t_delete_simple(depths) \
    depths.used = depths.size; \
    while (depths.used > 0) { \
      depths.used--; \
      macro_fss_basic_read_depth_t_delete_simple(depths.array[depths.used]); \
    } \
    if (!depths.used) macro_f_memory_structure_delete_simple(depths, fss_basic_read_depth_t)

  #define macro_fss_basic_read_depths_t_resize(status, depths, new_length) \
    status = F_none; \
    if (new_length < depths.size) { \
      f_array_length_t i = depths.size - new_length; \
      for (; i < depths.size; i++) { \
        macro_fss_basic_read_depth_t_delete(status, depths.array[i]); \
        if (F_status_is_error(status)) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize(depths.size, new_length, sizeof(fss_basic_read_depth_t), (void **) & depths.array); \
    if (status == F_none) { \
      depths.size = new_length; \
      if (depths.used > depths.size) depths.used = new_length; \
    }

  #define macro_fss_basic_read_depths_t_adjust(status, depths, new_length) \
    status = F_none; \
    if (new_length < depths.size) { \
      f_array_length_t i = depths.size - new_length; \
      for (; i < depths.size; i++) { \
        macro_fss_basic_read_depth_t_delete(status, depths.array[i]); \
        if (F_status_is_error(status)) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust(depths.size, new_length, sizeof(fss_basic_read_depth_t), (void **) & depths.array); \
    if (status == F_none) { \
      depths.size = new_length; \
      if (depths.used > depths.size) depths.used = new_length; \
    }
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
 * Process the parameters, parsing out and handling the depth and depth related parameters.
 *
 * Will handle depth-sensitive parameter conflicts, such as --name being used with --at (which is not allowed).
 *
 * @param arguments
 *   The console arguments to pre-process.
 * @param main
 *   The program specific main.
 * @param depths
 *   This stores the pre-processed depth parameters.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fss_basic_read_depth_process_
  extern f_status_t fss_basic_read_depth_process(const f_console_arguments_t arguments, const fss_basic_read_main_t main, fss_basic_read_depths_t *depths) f_attribute_visibility_internal;
#endif // _di_fss_basic_read_depth_process_

/**
 * Get the name of the file the given position represents within the buffer.
 *
 * @param at
 *   The position within the buffer.
 * @param files
 *   The representation of files and their respective ranges within the buffer.
 *
 * @return
 *   A string with the name when found.
 *   NULL is returned if the range represents the STDIN pipe.
 *
 *   On failure to identify, an empty string is returned.
 */
#ifndef _di_fss_basic_read_file_identify_
  extern f_string_t fss_basic_read_file_identify(const f_array_length_t at, const fss_basic_read_files_t files) f_attribute_visibility_internal;
#endif // _di_fss_basic_read_file_identify_

/**
 * Load a given number parameter.
 *
 * @param arguments
 *   The console arguments passed to the program.
 * @param main
 *   The program specific main.
 * @param parameter
 *   An ID representing the parameter.
 * @param name
 *   The parameter name to print on error.
 * @param number
 *   The location to store the loaded number.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fss_basic_read_load_number_
  extern f_status_t fss_basic_read_load_number(const f_console_arguments_t arguments, const fss_basic_read_main_t main, const f_array_length_t parameter, const f_string_t name, f_number_unsigned_t *number) f_attribute_visibility_internal;
#endif // _di_fss_basic_read_load_number_

/**
 * Print the Object and Content at the given position.
 *
 * Only what is requested to print (Object, Content, both, or neither) will be printed, if there is something to print.
 *
 * @param main
 *   The program specific main.
 * @param at
 *   The index in the Objects and Contents to print.
 * @param include_empty
 *   If TRUE, empty Content is printed.
 *   If FALSE, empty Content is ignored.
 * @param delimits
 *   The delimits in the objects and contents.
 * @param print_this
 *   Set bit 0x1 for printing Object.
 *   Set bit 0x2 for printing Content.
 *
 *   This is a temporary parameter to be used until other structural changes are made and completed.
 */
#ifndef _di_fss_basic_read_print_at_
  extern void fss_basic_read_print_at(const fss_basic_read_main_t main, const f_array_length_t at, const bool include_empty, const f_fss_delimits_t delimits, const uint8_t print_this) f_attribute_visibility_internal;
#endif // _di_fss_basic_read_print_at_

/**
 * Print the end of an object (which is essentially the start of a content).
 *
 * @param main
 *   The program specific main.
 */
#ifndef _di_fss_basic_read_print_object_end_
  extern void fss_basic_read_print_object_end(const fss_basic_read_main_t main) f_attribute_visibility_internal;
#endif // _di_fss_basic_read_print_object_end_

/**
 * Print the number one and a newline.
 *
 * @param main
 *   The program specific main.
 */
#ifndef _di_fss_basic_read_print_one_
  extern void fss_basic_read_print_one(const fss_basic_read_main_t main) f_attribute_visibility_internal;
#endif // _di_fss_basic_read_print_one_

/**
 * Print the end of an object/content set.
 *
 * @param main
 *   The program specific main.
 */
#ifndef _di_fss_basic_read_print_set_end_
  extern void fss_basic_read_print_set_end(const fss_basic_read_main_t main) f_attribute_visibility_internal;
#endif // _di_fss_basic_read_print_set_end_

/**
 * Print the number zero and a newline.
 *
 * @param main
 *   The program specific main.
 */
#ifndef _di_fss_basic_read_print_zero_
  extern void fss_basic_read_print_zero(const fss_basic_read_main_t main) f_attribute_visibility_internal;
#endif // _di_fss_basic_read_print_zero_

/**
 * Perform the basic read processing on the buffer.
 *
 * @param arguments
 *   The console arguments passed to the program.
 * @param files
 *   An array representing the ranges in which a given file exists in the buffer.
 * @param depths
 *   The processed depth parameters.
 * @param main
 *   The program specific main.
 * @param delimits
 *   An array of delimits detected during processing.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_basic_read_load_setting()
 */
#ifndef _di_fss_basic_read_process_
  extern f_status_t fss_basic_read_process(const f_console_arguments_t arguments, const fss_basic_read_files_t files, const fss_basic_read_depths_t depths, fss_basic_read_main_t *main, f_fss_delimits_t *delimits) f_attribute_visibility_internal;
#endif // _di_fss_basic_read_process_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_fss_basic_read_h
