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

  extern const f_string_t f_iki_syntax_separator_s;
  extern const f_string_t f_iki_syntax_placeholder_s;
  extern const f_string_t f_iki_syntax_quote_double_s;
  extern const f_string_t f_iki_syntax_quote_single_s;
  extern const f_string_t f_iki_syntax_slash_s;
#endif //_di_f_iki_syntax_

#ifndef _di_iki_vocabulary_0001_
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

  extern const f_string_t f_iki_vocabulary_0001_address_s;
  extern const f_string_t f_iki_vocabulary_0001_code_s;
  extern const f_string_t f_iki_vocabulary_0001_email_s;
  extern const f_string_t f_iki_vocabulary_0001_name_s;
  extern const f_string_t f_iki_vocabulary_0001_phone_s;
  extern const f_string_t f_iki_vocabulary_0001_quote_s;
  extern const f_string_t f_iki_vocabulary_0001_uri_s;
  extern const f_string_t f_iki_vocabulary_0001_url_s;
  extern const f_string_t f_iki_vocabulary_0001_urn_s;
  extern const f_string_t f_iki_vocabulary_0001_variable_s;
#endif // _di_iki_vocabulary_0001_

#ifndef _di_iki_vocabulary_0002_
  #define F_iki_vocabulary_0002_define_s    "define"
  #define F_iki_vocabulary_0002_parameter_s "parameter"

  #define F_iki_vocabulary_0002_define_s_length    6
  #define F_iki_vocabulary_0002_parameter_s_length 9

  extern const f_string_t f_iki_vocabulary_0002_define_s;
  extern const f_string_t f_iki_vocabulary_0002_parameter_s;
#endif // _di_iki_vocabulary_0002_

// @todo consider IKI-0003 = vocabulary based on context from HTML5 and accessibility-related?

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
#ifndef _di_iki_variable_t_
  typedef f_string_ranges_t f_iki_variable_t;

  #define f_iki_variable_t_initialize f_string_ranges_t_initialize

  #define macro_f_iki_variable_t_clear(variable) macro_f_string_ranges_t_clear(variable)

  #define macro_f_iki_variable_t_resize(status, variable, new_length) macro_f_string_ranges_t_resize(status, variable, new_length)
  #define macro_f_iki_variable_t_adjust(status, variable, new_length) macro_f_string_ranges_t_adjust(status, variable, new_length)

  #define macro_f_iki_variable_t_delete_simple(variable)  macro_f_string_ranges_t_delete_simple(variable)
  #define macro_f_iki_variable_t_destroy_simple(variable) macro_f_string_ranges_t_destroy_simple(variable)

#endif // _di_iki_variable_t_

/**
 * This holds an array of string ranges that represent the vocabulary names.
 *
 * array: The array of vocabulary names.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_iki_vocabulary_t_
  typedef f_string_ranges_t f_iki_vocabulary_t;

  #define f_iki_vocabulary_t_initialize f_string_ranges_t_initialize

  #define macro_f_iki_vocabulary_t_clear(vocabulary) macro_f_string_ranges_t_clear(vocabulary)

  #define macro_f_iki_vocabulary_t_resize(status, vocabulary, new_length) macro_f_string_ranges_t_resize(status, vocabulary, new_length)
  #define macro_f_iki_vocabulary_t_adjust(status, vocabulary, new_length) macro_f_string_ranges_t_adjust(status, vocabulary, new_length)

  #define macro_f_iki_vocabulary_t_delete_simple(vocabulary)  macro_f_string_ranges_t_delete_simple(vocabulary)
  #define macro_f_iki_vocabulary_t_destroy_simple(vocabulary) macro_f_string_ranges_t_destroy_simple(vocabulary)
#endif // _di_iki_vocabulary_t_

/**
 * This holds an array of f_iki_vocabulary_t.
 *
 * array: The array of content.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_iki_vocabularys_t_
  typedef f_string_rangess_t f_iki_vocabularys_t;

  #define f_iki_vocabularys_t_initialize f_string_rangess_t_initialize

  #define macro_f_iki_vocabularys_t_clear(content) macro_f_string_rangess_t_clear(content)

  #define macro_f_iki_vocabularys_t_resize(status, content, new_length) macro_f_string_rangess_t_resize(status, content, new_length)
  #define macro_f_iki_vocabularys_t_adjust(status, content, new_length) macro_f_string_rangess_t_adjust(status, content, new_length)

  #define macro_f_iki_vocabularys_t_delete_simple(content)  macro_f_string_rangess_t_delete_simple(content)
  #define macro_f_iki_vocabularys_t_destroy_simple(content) macro_f_string_rangess_t_destroy_simple(content)
#endif // _di_iki_vocabularys_t_

/**
 * This holds an array of string ranges that represent the content.
 *
 * The very first string range will represent the first content found.
 *
 * array: The array of content.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_iki_content_t_
  typedef f_string_ranges_t f_iki_content_t;

  #define f_iki_content_t_initialize f_string_ranges_t_initialize

  #define macro_f_iki_content_t_clear(content) macro_f_string_ranges_t_clear(content)

  #define macro_f_iki_content_t_resize(status, content, new_length) macro_f_string_ranges_t_resize(status, content, new_length)
  #define macro_f_iki_content_t_adjust(status, content, new_length) macro_f_string_ranges_t_adjust(status, content, new_length)

  #define macro_f_iki_content_t_delete_simple(content)  macro_f_string_ranges_t_delete_simple(content)
  #define macro_f_iki_content_t_destroy_simple(content) macro_f_string_ranges_t_destroy_simple(content)
#endif // _di_iki_content_t_

/**
 * This holds an array of f_iki_content_t.
 *
 * array: The array of content.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_iki_contents_t_
  typedef f_string_rangess_t f_iki_contents_t;

  #define f_iki_contents_t_initialize f_string_rangess_t_initialize

  #define macro_f_iki_contents_t_clear(content) macro_f_string_rangess_t_clear(content)

  #define macro_f_iki_contents_t_resize(status, content, new_length) macro_f_string_rangess_t_resize(status, content, new_length)
  #define macro_f_iki_contents_t_adjust(status, content, new_length) macro_f_string_rangess_t_adjust(status, content, new_length)

  #define macro_f_iki_contents_t_delete_simple(content)  macro_f_string_rangess_t_delete_simple(content)
  #define macro_f_iki_contents_t_destroy_simple(content) macro_f_string_rangess_t_destroy_simple(content)
#endif // _di_iki_contents_t_

/**
 * Provide a default allocation step.
 *
 * For a UTF-8 friendly allocation step, set to at least 4.
 */
#ifndef _di_f_iki_default_allocation_step_
  #define F_iki_default_allocation_step_d 4
#endif // _di_f_iki_default_allocation_step_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_iki_common_h
