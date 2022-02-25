/**
 * FLL - Level 0
 *
 * Project: IKI
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Defines iki common data.
 *
 * This is auto-included by iki.h and should not need to be explicitly included.
 */
#ifndef _F_iki_common_h
#define _F_iki_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * IKI-specific syntax.
 */
#ifndef _di_f_iki_syntax_
  #define F_iki_syntax_separator_s    ":"
  #define F_iki_syntax_placeholder_s  ""
  #define F_iki_syntax_quote_double_s "\""
  #define F_iki_syntax_quote_single_s "\'"
  #define F_iki_syntax_slash_s        "\\"

  #define F_iki_syntax_separator_s_length    1
  #define F_iki_syntax_placeholder_s_length  1
  #define F_iki_syntax_quote_double_s_length 1
  #define F_iki_syntax_quote_single_s_length 1
  #define F_iki_syntax_slash_s_length        1

  extern const f_string_static_t f_iki_syntax_separator_s;
  extern const f_string_static_t f_iki_syntax_placeholder_s;
  extern const f_string_static_t f_iki_syntax_quote_double_s;
  extern const f_string_static_t f_iki_syntax_quote_single_s;
  extern const f_string_static_t f_iki_syntax_slash_s;
#endif //_di_f_iki_syntax_

#ifndef _di_f_iki_vocabulary_0001_
  #define F_iki_vocabulary_0001_address_s  "address"
  #define F_iki_vocabulary_0001_code_s     "code"
  #define F_iki_vocabulary_0001_email_s    "email"
  #define F_iki_vocabulary_0001_name_s     "name"
  #define F_iki_vocabulary_0001_phone_s    "phone"
  #define F_iki_vocabulary_0001_quote_s    "quote"
  #define F_iki_vocabulary_0001_uri_s      "uri"
  #define F_iki_vocabulary_0001_url_s      "url"
  #define F_iki_vocabulary_0001_urn_s      "urn"
  #define F_iki_vocabulary_0001_variable_s "var"

  #define F_iki_vocabulary_0001_address_s_length  7
  #define F_iki_vocabulary_0001_code_s_length     4
  #define F_iki_vocabulary_0001_email_s_length    5
  #define F_iki_vocabulary_0001_name_s_length     4
  #define F_iki_vocabulary_0001_phone_s_length    5
  #define F_iki_vocabulary_0001_quote_s_length    5
  #define F_iki_vocabulary_0001_uri_s_length      3
  #define F_iki_vocabulary_0001_url_s_length      3
  #define F_iki_vocabulary_0001_urn_s_length      3
  #define F_iki_vocabulary_0001_variable_s_length 3

  extern const f_string_static_t f_iki_vocabulary_0001_address_s;
  extern const f_string_static_t f_iki_vocabulary_0001_code_s;
  extern const f_string_static_t f_iki_vocabulary_0001_email_s;
  extern const f_string_static_t f_iki_vocabulary_0001_name_s;
  extern const f_string_static_t f_iki_vocabulary_0001_phone_s;
  extern const f_string_static_t f_iki_vocabulary_0001_quote_s;
  extern const f_string_static_t f_iki_vocabulary_0001_uri_s;
  extern const f_string_static_t f_iki_vocabulary_0001_url_s;
  extern const f_string_static_t f_iki_vocabulary_0001_urn_s;
  extern const f_string_static_t f_iki_vocabulary_0001_variable_s;
#endif // _di_f_iki_vocabulary_0001_

#ifndef _di_f_iki_vocabulary_0002_
  #define F_iki_vocabulary_0002_context_s   "context"
  #define F_iki_vocabulary_0002_define_s    "define"
  #define F_iki_vocabulary_0002_parameter_s "parameter"

  #define F_iki_vocabulary_0002_context_s_length   7
  #define F_iki_vocabulary_0002_define_s_length    6
  #define F_iki_vocabulary_0002_parameter_s_length 9

  extern const f_string_static_t f_iki_vocabulary_0002_context_s;
  extern const f_string_static_t f_iki_vocabulary_0002_define_s;
  extern const f_string_static_t f_iki_vocabulary_0002_parameter_s;
#endif // _di_f_iki_vocabulary_0002_

/**
 * Designate an iki delimit location.
 */
#ifndef _di_f_iki_delimit_t_
  typedef f_array_length_t f_iki_delimit_t;
#endif // _di_f_iki_delimit_t_

/**
 * An array of f_iki_delimit_t.
 *
 * array: The array of iki quote.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_iki_delimits_t_
  typedef f_array_lengths_t f_iki_delimits_t;

  #define f_iki_delimits_t_initialize f_array_lengths_t_initialize

  #define macro_f_iki_delimits_t_clear(delimits) macro_f_array_lengths_t_clear(delimits)

  #define macro_f_iki_delimits_t_resize(status, delimits, length) macro_f_array_lengths_t_resize(status, delimits, length)
  #define macro_f_iki_delimits_t_adjust(status, delimits, length) macro_f_array_lengths_t_adjust(status, delimits, length)

  #define macro_f_iki_delimits_t_delete_simple(delimits)  macro_f_array_lengths_t_delete_simple(delimits)
  #define macro_f_iki_delimits_t_destroy_simple(delimits) macro_f_array_lengths_t_destroy_simple(delimits)

  #define macro_f_iki_delimits_t_increase(status, step, delimits)      macro_f_array_lengths_t_increase(status, step, delimits)
  #define macro_f_iki_delimits_t_increase_by(status, delimits, amount) macro_f_array_lengths_t_increase_by(status, delimits, amount)
  #define macro_f_iki_delimits_t_decrease_by(status, delimits, amount) macro_f_array_lengths_t_decrease_by(status, delimits, amount)
  #define macro_f_iki_delimits_t_decimate_by(status, delimits, amount) macro_f_array_lengths_t_decimate_by(status, delimits, amount)
#endif // _di_f_iki_delimits_t_

/**
 * An array of f_iki_delimits_t.
 *
 * array: The array of iki quotes.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_iki_delimitss_t_
  typedef f_array_lengthss_t f_iki_delimitss_t;

  #define f_iki_delimitss_t_initialize f_array_lengthss_t_initialize

  #define macro_f_iki_delimitss_t_clear(delimitss) macro_f_array_lengthss_t_clear(delimitss)

  #define macro_f_iki_delimitss_t_resize(status, delimitss, length) macro_f_array_lengthss_t_resize(status, delimitss, length)
  #define macro_f_iki_delimitss_t_adjust(status, delimitss, length) macro_f_array_lengthss_t_adjust(status, delimitss, length)

  #define macro_f_iki_delimitss_t_delete_simple(delimitss)  macro_f_array_lengthss_t_delete_simple(delimitss)
  #define macro_f_iki_delimitss_t_destroy_simple(delimitss) macro_f_array_lengthss_t_destroy_simple(delimitss)

  #define macro_f_iki_delimitss_t_increase(status, step, delimitss)      macro_f_array_lengthss_t_increase(status, step, delimitss)
  #define macro_f_iki_delimitss_t_increase_by(status, delimitss, amount) macro_f_array_lengthss_t_increase_by(status, delimitss, amount)
  #define macro_f_iki_delimitss_t_decrease_by(status, delimitss, amount) macro_f_array_lengthss_t_decrease_by(status, delimitss, amount)
  #define macro_f_iki_delimitss_t_decimate_by(status, delimitss, amount) macro_f_array_lengthss_t_decimate_by(status, delimitss, amount)
#endif // _di_f_iki_delimitss_t_


/**
 * This holds an array of string ranges that represent the entire vocabulary name, content, and syntax.
 *
 * array: The array of variable.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_iki_variable_t_
  typedef f_string_ranges_t f_iki_variable_t;

  #define f_iki_variable_t_initialize f_string_ranges_t_initialize

  #define macro_f_iki_variable_t_clear(variable) macro_f_string_ranges_t_clear(variable)

  #define macro_f_iki_variable_t_resize(status, variable, new_length) macro_f_string_ranges_t_resize(status, variable, new_length)
  #define macro_f_iki_variable_t_adjust(status, variable, new_length) macro_f_string_ranges_t_adjust(status, variable, new_length)

  #define macro_f_iki_variable_t_delete_simple(variable)  macro_f_string_ranges_t_delete_simple(variable)
  #define macro_f_iki_variable_t_destroy_simple(variable) macro_f_string_ranges_t_destroy_simple(variable)

#endif // _di_f_iki_variable_t_

/**
 * This holds an array of string ranges that represent the vocabulary names.
 *
 * array: The array of vocabulary names.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_iki_vocabulary_t_
  typedef f_string_ranges_t f_iki_vocabulary_t;

  #define f_iki_vocabulary_t_initialize f_string_ranges_t_initialize

  #define macro_f_iki_vocabulary_t_clear(vocabulary) macro_f_string_ranges_t_clear(vocabulary)

  #define macro_f_iki_vocabulary_t_resize(status, vocabulary, new_length) macro_f_string_ranges_t_resize(status, vocabulary, new_length)
  #define macro_f_iki_vocabulary_t_adjust(status, vocabulary, new_length) macro_f_string_ranges_t_adjust(status, vocabulary, new_length)

  #define macro_f_iki_vocabulary_t_delete_simple(vocabulary)  macro_f_string_ranges_t_delete_simple(vocabulary)
  #define macro_f_iki_vocabulary_t_destroy_simple(vocabulary) macro_f_string_ranges_t_destroy_simple(vocabulary)
#endif // _di_f_iki_vocabulary_t_

/**
 * This holds an array of f_iki_vocabulary_t.
 *
 * array: The array of content.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_iki_vocabularys_t_
  typedef f_string_rangess_t f_iki_vocabularys_t;

  #define f_iki_vocabularys_t_initialize f_string_rangess_t_initialize

  #define macro_f_iki_vocabularys_t_clear(content) macro_f_string_rangess_t_clear(content)

  #define macro_f_iki_vocabularys_t_resize(status, content, new_length) macro_f_string_rangess_t_resize(status, content, new_length)
  #define macro_f_iki_vocabularys_t_adjust(status, content, new_length) macro_f_string_rangess_t_adjust(status, content, new_length)

  #define macro_f_iki_vocabularys_t_delete_simple(content)  macro_f_string_rangess_t_delete_simple(content)
  #define macro_f_iki_vocabularys_t_destroy_simple(content) macro_f_string_rangess_t_destroy_simple(content)
#endif // _di_f_iki_vocabularys_t_

/**
 * This holds an array of string ranges that represent the content.
 *
 * The very first string range will represent the first content found.
 *
 * array: The array of content.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_iki_content_t_
  typedef f_string_ranges_t f_iki_content_t;

  #define f_iki_content_t_initialize f_string_ranges_t_initialize

  #define macro_f_iki_content_t_clear(content) macro_f_string_ranges_t_clear(content)

  #define macro_f_iki_content_t_resize(status, content, new_length) macro_f_string_ranges_t_resize(status, content, new_length)
  #define macro_f_iki_content_t_adjust(status, content, new_length) macro_f_string_ranges_t_adjust(status, content, new_length)

  #define macro_f_iki_content_t_delete_simple(content)  macro_f_string_ranges_t_delete_simple(content)
  #define macro_f_iki_content_t_destroy_simple(content) macro_f_string_ranges_t_destroy_simple(content)
#endif // _di_f_iki_content_t_

/**
 * This holds an array of f_iki_content_t.
 *
 * array: The array of content.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_iki_contents_t_
  typedef f_string_rangess_t f_iki_contents_t;

  #define f_iki_contents_t_initialize f_string_rangess_t_initialize

  #define macro_f_iki_contents_t_clear(content) macro_f_string_rangess_t_clear(content)

  #define macro_f_iki_contents_t_resize(status, content, new_length) macro_f_string_rangess_t_resize(status, content, new_length)
  #define macro_f_iki_contents_t_adjust(status, content, new_length) macro_f_string_rangess_t_adjust(status, content, new_length)

  #define macro_f_iki_contents_t_delete_simple(content)  macro_f_string_rangess_t_delete_simple(content)
  #define macro_f_iki_contents_t_destroy_simple(content) macro_f_string_rangess_t_destroy_simple(content)
#endif // _di_f_iki_contents_t_

/**
 * This containg all of the IKI data.
 *
 * content:    A set of ranges representing the content list to store the content associated with the found vocabulary name.
 * delimits:   A delimits array representing where delimits exist within the buffer.
 * variable:   A set of ranges representing the entire vocabulary name, content, and syntax.
 * vocabulary: A set of ranges representing the vocabulary name list to store the found vocabulary name.
 */
#ifndef _di_f_iki_data_t_
  typedef struct {
    f_iki_content_t content;
    f_iki_delimits_t delimits;
    f_iki_variable_t variable;
    f_iki_vocabulary_t vocabulary;
  } f_iki_data_t;

  #define f_iki_data_t_initialize { \
    f_iki_content_t_initialize, \
    f_iki_delimits_t_initialize, \
    f_iki_variable_t_initialize, \
    f_iki_vocabulary_t_initialize, \
  }

  #define macro_f_iki_data_t_clear(data) \
    f_iki_content_t_clear(data.content) \
    f_iki_delimits_t_clear(data.delimits) \
    f_iki_variable_t_clear(data.variable) \
    f_iki_vocabulary_t_clear(data.vocabulary)

  #define macro_f_iki_data_t_delete_simple(data)  status = f_iki_data_delete(data);
  #define macro_f_iki_data_t_destroy_simple(data) status = f_iki_data_destroy(data);
#endif // _di_f_iki_data_t_

/**
 * An array of f_iki_data_t.
 *
 * array: The array of fss quotes.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_iki_datas_t_
  typedef struct {
    f_iki_data_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_iki_datas_t;

  #define f_fss_iki_datas_t_initialize { 0, 0, 0 }

  #define macro_f_fss_iki_datas_t_clear(datas) macro_f_memory_structure_clear(datas)

  #define macro_f_fss_iki_datas_t_resize(status, datas, length) status = f_iki_datas_resize(length, &datas);
  #define macro_f_fss_iki_datas_t_adjust(status, datas, length) status = f_iki_datas_adjust(length, &datas);

  #define macro_f_fss_iki_datas_t_delete_simple(datas)  status = f_iki_datas_resize(0, &datas);
  #define macro_f_fss_iki_datas_t_destroy_simple(datas) status = f_iki_datas_adjust(0, &datas);

  #define macro_f_fss_iki_datas_t_increase(status, step, datas)      status = f_iki_datas_increase(step, &datas);
  #define macro_f_fss_iki_datas_t_increase_by(status, datas, amount) status = f_iki_datas_increase_by(amount, &datas);
  #define macro_f_fss_iki_datas_t_decrease_by(status, datas, amount) status = f_iki_datas_decrease_by(amount, &datas);
  #define macro_f_fss_iki_datas_t_decimate_by(status, datas, amount) status = f_iki_datas_decimate_by(amount, &datas);
#endif // _di_f_iki_datas_t_

/**
 * Provide a default allocation step.
 *
 * For a UTF-8 friendly allocation step, set to at least 4.
 */
#ifndef _di_f_iki_default_allocation_step_
  #define F_iki_default_allocation_step_d 4
#endif // _di_f_iki_default_allocation_step_

/**
 * Delete the IKI data.
 *
 * @param data
 *   The IKI data to delete.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_array_lengths_resize().
 *   Errors (with error bit) from: f_string_ranges_resize().
 *
 * @see f_array_lengths_resize()
 * @see f_string_ranges_resize()
 */
#ifndef _di_f_iki_data_delete_
  extern f_status_t f_iki_data_delete(f_iki_data_t *data);
#endif // _di_f_iki_data_delete_

/**
 * Destroy the IKI data.
 *
 * @param data
 *   The IKI data to destroy.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_array_lengths_adjust().
 *   Errors (with error bit) from: f_string_ranges_adjust().
 *
 * @see f_array_lengths_adjust()
 * @see f_string_ranges_adjust()
 */
#ifndef _di_f_iki_data_destroy_
  extern f_status_t f_iki_data_destroy(f_iki_data_t *data);
#endif // _di_f_iki_data_destroy_

/**
 * Resize the string lengths array.
 *
 * @param length
 *   The new size to use.
 * @param lengths
 *   The string lengths array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_iki_datas_adjust_
  extern f_status_t f_iki_datas_adjust(const f_array_length_t length, f_iki_datas_t *datas);
#endif // _di_f_iki_datas_adjust_

/**
 * Append the source lengths onto the destination.
 *
 * @param source
 *   The source lengths to append.
 * @param destination
 *   The destination lengths the source is appended onto.
 *
 * @return
 *   F_none on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_iki_datas_append_
  extern f_status_t f_iki_datas_append(const f_iki_datas_t source, f_iki_datas_t *destination);
#endif // _di_f_iki_datas_append_

/**
 * Resize the string lengths array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decimate the size by.
 * @param lengths
 *   The string lengths array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_adjust().
 */
#ifndef _di_f_iki_datas_decimate_by_
  extern f_status_t f_iki_datas_decimate_by(const f_array_length_t amount, f_iki_datas_t *datas);
#endif // _di_f_iki_datas_decimate_by_

/**
 * Resize the string lengths array to a smaller size.
 *
 * This will resize making the array smaller based on (size - given length).
 * If the given length is too small, then the resize will fail.
 * This will not shrink the size to les than 0.
 *
 * @param amount
 *   A positive number representing how much to decrease the size by.
 * @param lengths
 *   The string lengths array to resize.
 *
 * @return
 *   F_none on success.
 *   F_data_not if amount is 0.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_iki_datas_decrease_by_
  extern f_status_t f_iki_datas_decrease_by(const f_array_length_t amount, f_iki_datas_t *datas);
#endif // _di_f_iki_datas_decrease_by_

/**
 * Increase the size of the string lengths array, but only if necesary.
 *
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param step
 *   The allocation step to use.
 *   Must be greater than 0.
 * @param lengths
 *   The string lengths array to resize.
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
#ifndef _di_f_iki_datas_increase_
  extern f_status_t f_iki_datas_increase(const f_array_length_t step, f_iki_datas_t *datas);
#endif // _di_f_iki_datas_increase_

/**
 * Resize the string lengths array to a larger size.
 *
 * This will resize making the string larger based on the given length.
 * If the given length is too large for the buffer, then attempt to set max buffer size (F_array_length_t_size_d).
 * If already set to the maximum buffer size, then the resize will fail.
 *
 * @param amount
 *   A positive number representing how much to increase the size by.
 * @param lengths
 *   The string lengths array to resize.
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
#ifndef _di_f_iki_datas_increase_by_
  extern f_status_t f_iki_datas_increase_by(const f_array_length_t amount, f_iki_datas_t *datas);
#endif // _di_f_iki_datas_increase_by_

/**
 * Resize the string lengths array.
 *
 * @param length
 *   The new size to use.
 * @param lengths
 *   The string lengths array to adjust.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_iki_datas_resize_
  extern f_status_t f_iki_datas_resize(const f_array_length_t length, f_iki_datas_t *datas);
#endif // _di_f_iki_datas_resize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_iki_common_h
