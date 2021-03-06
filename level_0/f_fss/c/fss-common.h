/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines common data to be used for/by project fss.
 *
 * This is auto-included by fss.h and should not need to be explicitly included.
 */
#ifndef _F_fss_common_h
#define _F_fss_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * FSS-specific types.
 */
#ifndef _di_f_fss_types_t_
  #define f_fss_brace_close_s  f_string_ascii_brace_close_s
  #define f_fss_brace_open_s   f_string_ascii_brace_open_s
  #define f_fss_colon_s        f_string_ascii_colon_s
  #define f_fss_minus_s         f_string_ascii_minus_s
  #define f_fss_f_s            f_string_ascii_f_s
  #define f_fss_pound_s        f_string_ascii_pound_s
  #define f_fss_quote_double_s f_string_ascii_quote_double_s
  #define f_fss_quote_single_s f_string_ascii_quote_single_s
  #define f_fss_s_s            f_string_ascii_s_s
  #define f_fss_slash_s        f_string_ascii_slash_backward_s
  #define f_fss_space_s        f_string_ascii_space_s
  #define f_fss_underscore_s   f_string_ascii_underscore_s

  #define f_fss_comment                 f_fss_pound_s[0]
  #define f_fss_eol                     f_string_eol_s[0]
  #define f_fss_space                   f_fss_space_s[0]
  #define f_fss_space_holder            f_fss_underscore_s[0]
  #define f_fss_basic_open              f_fss_space_s[0]
  #define f_fss_basic_close             f_string_eol_s[0]
  #define f_fss_extended_open           f_fss_space_s[0]
  #define f_fss_extended_next           f_fss_space_s[0]
  #define f_fss_extended_close          f_string_eol_s[0]
  #define f_fss_basic_list_open         f_fss_colon_s[0]
  #define f_fss_basic_list_open_end     f_string_eol_s[0]
  #define f_fss_basic_list_close        f_string_eol_s[0]
  #define f_fss_extended_list_open      f_fss_brace_open_s[0]
  #define f_fss_extended_list_open_end  f_string_eol_s[0]
  #define f_fss_extended_list_close     f_fss_brace_close_s[0]
  #define f_fss_extended_list_close_end f_string_eol_s[0]
  #define f_fss_embedded_list_open      f_fss_brace_open_s[0]
  #define f_fss_embedded_list_open_end  f_string_eol_s[0]
  #define f_fss_embedded_list_close     f_fss_brace_close_s[0]
  #define f_fss_embedded_list_close_end f_string_eol_s[0]
  #define f_fss_type_header_open        f_fss_pound_s[0]
  #define f_fss_type_header_part1       f_fss_space_s[0]
  #define f_fss_type_header_part2       f_fss_f_s[0]
  #define f_fss_type_header_part3       f_fss_s_s[0]
  #define f_fss_type_header_part4       f_fss_s_s[0]
  #define f_fss_type_header_part5       f_fss_minus_s[0]
  #define f_fss_type_header_close       f_string_eol_s[0]
#endif // _di_f_fss_types_t_

/**
 * FSS-specific delimiters.
 */
#ifndef _di_f_fss_delimiters_
  #define f_fss_delimit_placeholder  f_string_placeholder_s[0]
  #define f_fss_delimit_quote_single f_fss_quote_single_s[0]
  #define f_fss_delimit_quote_double f_fss_quote_double_s[0]
  #define f_fss_delimit_slash        f_fss_slash_s[0]
#endif //_di_f_fss_delimiters_

/**
 * Codes for every FSS standard.
 */
#ifndef _di_f_fss_codes_
  enum {
    f_fss_basic = 1,
    f_fss_extended,
    f_fss_basic_list,
    f_fss_extended_list,
    f_fss_very_basic_list,
    f_fss_somewhat_basic_list,
    f_fss_somewhat_extended_list,
    f_fss_very_extended_list,
    f_fss_embeded_list,
    f_fss_reverse_mapping,
    f_fss_extended_reverse_mapping,
    f_fss_simple_list,
    f_fss_iki_text,
    f_fss_basic_rule,
  };
#endif // _di_f_fss_codes_

/**
 * Codes for FSS completeness.
 *
 * The details on how these work are specific to individual specifications.
 * The notes below provide the intended purpose but be sure to still read the individual function documentation.
 *
 * Only "next" and "end" are only meaningful for a Content and will be treated as "none" for an Object.
 *
 * none:         Disable completeness.
 * end:          Complete as if this is the final piece of a set (such as FSS-0001, adding terminating EOL).
 * full:         Complete and add terminating EOL, where applicable.
 * full_trim:    Complete and add terminating EOL but remove any leading or trailing whitespace, where applicable.
 * next:         Complete as if this is a piece of a set (such as FSS-0001, adding a separating space).
 * partial:      Complete, but do not add terminating EOL, where applicable.
 * partial_trim: Complete, but do not add terminating EOL and remove any leading or trailing whitespace, where applicable.
 */
#ifndef _di_f_fss_complete_
  enum {
    f_fss_complete_none = 1,
    f_fss_complete_end,
    f_fss_complete_full,
    f_fss_complete_full_trim,
    f_fss_complete_next,
    f_fss_complete_partial,
    f_fss_complete_partial_trim,
  };
#endif // _di_f_fss_complete_

/**
 * Default allocation steps.
 *
 * Recommended to be set to at least 4 to be UTF-8 friendlier.
 */
#ifndef _di_f_fss_default_allocation_step_
  #define f_fss_default_allocation_step f_memory_default_allocation_small
  #define f_fss_default_allocation_step_small f_memory_default_allocation_small
  #define f_fss_default_allocation_step_large f_memory_default_allocation_large
#endif // _di_f_fss_default_allocation_step_

/**
 * This is a range that represents an object.
 */
#ifndef _di_fss_object_t_
  typedef f_string_range_t f_fss_object_t;

  #define f_fss_object_t_initialize f_string_range_t_initialize

  #define macro_f_fss_object_t_clear(object) macro_f_string_range_t_clear(object)
#endif // _di_fss_object_t_

/**
 * This holds an array of fss_object.
 *
 * array: The array of objects.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_fss_objects_t_
  typedef f_string_ranges_t f_fss_objects_t;

  #define f_fss_objects_t_initialize f_string_ranges_t_initialize

  #define macro_f_fss_objects_t_clear(objects) macro_f_string_ranges_t_clear(objects)

  #define macro_f_fss_objects_t_resize(status, objects, length) macro_f_string_ranges_t_resize(status, objects, length)
  #define macro_f_fss_objects_t_adjust(status, objects, length) macro_f_string_ranges_t_adjust(status, objects, length)

  #define macro_f_fss_objects_t_delete_simple(objects)  macro_f_string_ranges_t_delete_simple(objects)
  #define macro_f_fss_objects_t_destroy_simple(objects) macro_f_string_ranges_t_destroy_simple(objects)

  #define macro_f_fss_objects_t_increase(status, step, objects)      macro_f_string_ranges_t_increase(status, step, objects)
  #define macro_f_fss_objects_t_increase_by(status, objects, amount) macro_f_string_ranges_t_increase_by(status, objects, amount)
  #define macro_f_fss_objects_t_decrease_by(status, objects, amount) macro_f_string_ranges_t_decrease_by(status, objects, amount)
  #define macro_f_fss_objects_t_decimate_by(status, objects, amount) macro_f_string_ranges_t_decimate_by(status, objects, amount)
#endif // _di_fss_objects_t_

/**
 * This holds an array of string ranges that represent the content.
 *
 * The very first string range will represent the first content found.
 *
 * array: The array of content.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_fss_content_
  typedef f_string_ranges_t f_fss_content_t;

  #define f_fss_content_t_initialize f_string_ranges_t_initialize

  #define macro_f_fss_content_t_clear(content) macro_f_string_ranges_t_clear(content)

  #define macro_f_fss_content_t_resize(status, content, length) macro_f_string_ranges_t_resize(status, content, length)
  #define macro_f_fss_content_t_adjust(status, content, length) macro_f_string_ranges_t_adjust(status, content, length)

  #define macro_f_fss_content_t_delete_simple(content)  macro_f_string_ranges_t_delete_simple(content)
  #define macro_f_fss_content_t_destroy_simple(content) macro_f_string_ranges_t_destroy_simple(content)

  #define macro_f_fss_content_t_increase(status, step, content)      macro_f_string_ranges_t_increase(status, step, content)
  #define macro_f_fss_content_t_increase_by(status, content, amount) macro_f_string_ranges_t_increase_by(status, content, amount)
  #define macro_f_fss_content_t_decrease_by(status, content, amount) macro_f_string_ranges_t_decrease_by(status, content, amount)
  #define macro_f_fss_content_t_decimate_by(status, content, amount) macro_f_string_ranges_t_decimate_by(status, content, amount)
#endif // _di_fss_content_

/**
 * This holds an array of fss_content.
 *
 * array: The array of content arrays.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_fss_contents_t_
  typedef f_string_rangess_t f_fss_contents_t;

  #define f_fss_contents_t_initialize f_string_rangess_t_initialize

  #define macro_f_fss_contents_t_clear(contents) macro_f_string_rangess_t_clear(contents)

  #define macro_f_fss_contents_t_resize(status, contents, length) macro_f_string_rangess_t_resize(status, contents, length)
  #define macro_f_fss_contents_t_adjust(status, contents, length) macro_f_string_rangess_t_adjust(status, contents, length)

  #define macro_f_fss_contents_t_delete_simple(contents)  macro_f_string_rangess_t_delete_simple(contents)
  #define macro_f_fss_contents_t_destroy_simple(contents) macro_f_string_rangess_t_destroy_simple(contents)

  #define macro_f_fss_contents_t_increase(status, step, contents)            macro_f_string_rangess_t_increase(status, step, contents)
  #define macro_f_fss_contents_t_increase_by(status, contents, amount) macro_f_string_rangess_t_increase_by(status, contents, amount)
  #define macro_f_fss_contents_t_decrease_by(status, contents, amount) macro_f_string_rangess_t_decrease_by(status, contents, amount)
  #define macro_f_fss_contents_t_decimate_by(status, contents, amount) macro_f_string_rangess_t_decimate_by(status, contents, amount)
#endif // _di_f_fss_contents_t_

/**
 * Resize the string quantitys array.
 *
 * @param length
 *   The new size to use.
 * @param quantitys
 *   The string quantitys array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantitys_adjust_
  extern f_status_t f_string_quantitys_adjust(const f_array_length_t length, f_string_quantitys_t *quantitys);
#endif // _di_f_string_quantitys_adjust_

/**
 * Append the source quantitys onto the destination.
 *
 * @param source
 *   The source quantitys to append.
 * @param destination
 *   The destination quantitys the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantitys_append_
  extern f_status_t f_string_quantitys_append(const f_string_quantitys_t source, f_string_quantitys_t *destination);
#endif // _di_f_string_quantitys_append_

/**
 * Resize the string quantitys array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param quantitys
 *   The string quantitys array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantitys_decimate_by_
  extern f_status_t f_string_quantitys_decimate_by(const f_array_length_t amount, f_string_quantitys_t *quantitys);
#endif // _di_f_string_quantitys_decimate_by_

/**
 * Resize the string quantitys array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param quantitys
 *   The string quantitys array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantitys_decrease_by_
  extern f_status_t f_string_quantitys_decrease_by(const f_array_length_t amount, f_string_quantitys_t *quantitys);
#endif // _di_f_string_quantitys_decrease_by_

/**
 * Increase the size of the string quantitys array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param quantitys
 *   The string quantitys array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantitys_increase_
  extern f_status_t f_string_quantitys_increase(const uint16_t step, f_string_quantitys_t *quantitys);
#endif // _di_f_string_quantitys_increase_

/**
 * Resize the string quantitys array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param quantitys
 *   The string quantitys array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantitys_increase_by_
  extern f_status_t f_string_quantitys_increase_by(const f_array_length_t amount, f_string_quantitys_t *quantitys);
#endif // _di_f_string_quantitys_increase_by_

/**
 * Resize the string quantitys array.
 *
 * @param length
 *   The new size to use.
 * @param quantitys
 *   The string quantitys array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantitys_resize_
  extern f_status_t f_string_quantitys_resize(const f_array_length_t length, f_string_quantitys_t *quantitys);
#endif // _di_f_string_quantitys_resize_

/**
 * Resize the string quantityss array.
 *
 * @param length
 *   The new size to use.
 * @param quantityss
 *   The string quantityss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantityss_adjust_
  extern f_status_t f_string_quantityss_adjust(const f_array_length_t length, f_string_quantityss_t *quantityss);
#endif // _di_f_string_quantityss_adjust_

/**
 * Resize the string quantityss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param quantityss
 *   The string quantityss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantityss_decimate_by_
  extern f_status_t f_string_quantityss_decimate_by(const f_array_length_t amount, f_string_quantityss_t *quantityss);
#endif // _di_f_string_quantityss_decimate_by_

/**
 * Resize the string quantityss array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to less than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param quantityss
 *   The string quantityss array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantityss_decrease_by_
  extern f_status_t f_string_quantityss_decrease_by(const f_array_length_t amount, f_string_quantityss_t *quantityss);
#endif // _di_f_string_quantityss_decrease_by_

/**
 * Increase the size of the string quantityss array, but only if necessary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param quantityss
 *   The string quantityss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + 1 <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantityss_increase_
  extern f_status_t f_string_quantityss_increase(const uint16_t step, f_string_quantityss_t *quantityss);
#endif // _di_f_string_quantityss_increase_

/**
 * Resize the string quantityss array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (f_array_length_t_size).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param quantityss
 *   The string quantityss array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is no reason to increase size (used + amount <= size).
 *
 *   F_array_too_large (with error bit) if the new array length is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantityss_increase_by_
  extern f_status_t f_string_quantityss_increase_by(const f_array_length_t amount, f_string_quantityss_t *quantityss);
#endif // _di_f_string_quantityss_increase_by_

/**
 * Resize the string quantityss array.
 *
 * @param length
 *   The new size to use.
 * @param quantityss
 *   The string quantityss array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantityss_resize_
  extern f_status_t f_string_quantityss_resize(const f_array_length_t length, f_string_quantityss_t *quantityss);
#endif // _di_f_string_quantityss_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fss_common_h
