/**
 * FLL - Level 0
 *
 * Project: IKI
 * API Version: 0.7
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
 * Provide a default allocation step.
 *
 * For a UTF-8 friendly allocation step, set to at least 4.
 *
 * F_iki_default_allocation_*:
 *   - large: The large allocation size.
 *   - small: The small allocation size, in particular used for allocation iki strings.
 */
#ifndef _di_f_iki_default_d_
  #define F_iki_default_allocation_large_d F_memory_default_allocation_large_d
  #define F_iki_default_allocation_small_d 8
#endif // _di_f_iki_default_d_

/**
 * State flags associated with iki functions.
 *
 * These flags are meant to be bitwise for the 32-bit f_state_t flag property.
 *
 * The f_iki_state_flag_none_e is expected to be 0, therefore it must be safe to use 0 directly.
 *
 * f_iki_state_flag_*:
 *   - none:                  No flags are set.
 *   - utf_fail_on_valid_not: Immediately fail on invalid UTF-8 character (including incomplete).
 */
#ifndef _di_f_iki_state_flag_e_
  enum {
    f_iki_state_flag_none_e                  = 0,
    f_iki_state_flag_utf_fail_on_valid_not_e = 0x1,
  }; // enum
#endif // _di_f_iki_state_flag_e_

/**
 * IKI-specific syntax.
 */
#ifndef _di_f_iki_syntax_s_
  #define F_iki_syntax_separator_s      F_string_ascii_colon_s
  #define F_iki_syntax_placeholder_s    F_string_placeholder_s
  #define F_iki_syntax_quote_backtick_s F_string_ascii_grave_s
  #define F_iki_syntax_quote_double_s   F_string_ascii_quote_double_s
  #define F_iki_syntax_quote_single_s   F_string_ascii_quote_single_s
  #define F_iki_syntax_slash_s          F_string_ascii_slash_backward_s

  #define F_iki_syntax_separator_s_length      F_string_ascii_colon_s_length
  #define F_iki_syntax_placeholder_s_length    F_string_placeholder_s_length
  #define F_iki_syntax_quote_backtick_s_length F_string_ascii_grave_s_length
  #define F_iki_syntax_quote_double_s_length   F_string_ascii_quote_double_s_length
  #define F_iki_syntax_quote_single_s_length   F_string_ascii_quote_single_s_length
  #define F_iki_syntax_slash_s_length          F_string_ascii_slash_backward_s_length

  #ifndef _di_f_iki_syntax_separator_s_
    extern const f_string_static_t f_iki_syntax_separator_s;
  #endif // _di_f_iki_syntax_separator_s_

  #ifndef _di_f_iki_syntax_placeholder_s_
    extern const f_string_static_t f_iki_syntax_placeholder_s;
  #endif // _di_f_iki_syntax_placeholder_s_

  #ifndef _di_f_iki_syntax_quote_backtick_s_
    extern const f_string_static_t f_iki_syntax_quote_backtick_s;
  #endif // _di_f_iki_syntax_quote_backtick_s_

  #ifndef _di_f_iki_syntax_quote_double_s_
    extern const f_string_static_t f_iki_syntax_quote_double_s;
  #endif // _di_f_iki_syntax_quote_double_s_

  #ifndef _di_f_iki_syntax_quote_single_s_
    extern const f_string_static_t f_iki_syntax_quote_single_s;
  #endif // _di_f_iki_syntax_quote_single_s_

  #ifndef _di_f_iki_syntax_slash_s_
    extern const f_string_static_t f_iki_syntax_slash_s;
  #endif // _di_f_iki_syntax_slash_s_
#endif //_di_f_iki_syntax_s_

#ifndef _di_f_iki_vocabulary_0001_s_
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

  #ifndef _di_f_iki_vocabulary_0001_address_s_
    extern const f_string_static_t f_iki_vocabulary_0001_address_s;
  #endif // _di_f_iki_vocabulary_0001_address_s_

  #ifndef _di_f_iki_vocabulary_0001_code_s_
    extern const f_string_static_t f_iki_vocabulary_0001_code_s;
  #endif // _di_f_iki_vocabulary_0001_code_s_

  #ifndef _di_f_iki_vocabulary_0001_email_s_
    extern const f_string_static_t f_iki_vocabulary_0001_email_s;
  #endif // _di_f_iki_vocabulary_0001_email_s_

  #ifndef _di_f_iki_vocabulary_0001_name_s_
    extern const f_string_static_t f_iki_vocabulary_0001_name_s;
  #endif // _di_f_iki_vocabulary_0001_name_s_

  #ifndef _di_f_iki_vocabulary_0001_phone_s_
    extern const f_string_static_t f_iki_vocabulary_0001_phone_s;
  #endif // _di_f_iki_vocabulary_0001_phone_s_

  #ifndef _di_f_iki_vocabulary_0001_quote_s_
    extern const f_string_static_t f_iki_vocabulary_0001_quote_s;
  #endif // _di_f_iki_vocabulary_0001_quote_s_

  #ifndef _di_f_iki_vocabulary_0001_uri_s_
    extern const f_string_static_t f_iki_vocabulary_0001_uri_s;
  #endif // _di_f_iki_vocabulary_0001_uri_s_

  #ifndef _di_f_iki_vocabulary_0001_url_s_
    extern const f_string_static_t f_iki_vocabulary_0001_url_s;
  #endif // _di_f_iki_vocabulary_0001_url_s_

  #ifndef _di_f_iki_vocabulary_0001_urn_s_
    extern const f_string_static_t f_iki_vocabulary_0001_urn_s;
  #endif // _di_f_iki_vocabulary_0001_urn_s_

  #ifndef _di_f_iki_vocabulary_0001_variable_s_
    extern const f_string_static_t f_iki_vocabulary_0001_variable_s;
  #endif // _di_f_iki_vocabulary_0001_variable_s_
#endif // _di_f_iki_vocabulary_0001_s_

#ifndef _di_f_iki_vocabulary_0002_s_
  #define F_iki_vocabulary_0002_context_s   "context"
  #define F_iki_vocabulary_0002_define_s    "define"
  #define F_iki_vocabulary_0002_parameter_s "parameter"

  #define F_iki_vocabulary_0002_context_s_length   7
  #define F_iki_vocabulary_0002_define_s_length    6
  #define F_iki_vocabulary_0002_parameter_s_length 9

  #ifndef _di_f_iki_vocabulary_0002_context_s_
    extern const f_string_static_t f_iki_vocabulary_0002_context_s;
  #endif // _di_f_iki_vocabulary_0002_context_s_

  #ifndef _di_f_iki_vocabulary_0002_define_s_
    extern const f_string_static_t f_iki_vocabulary_0002_define_s;
  #endif // _di_f_iki_vocabulary_0002_define_s_

  #ifndef _di_f_iki_vocabulary_0002_parameter_s_
    extern const f_string_static_t f_iki_vocabulary_0002_parameter_s;
  #endif // _di_f_iki_vocabulary_0002_parameter_s_
#endif // _di_f_iki_vocabulary_0002_s_

/**
 * This containg all of the IKI data.
 *
 * content:    A set of ranges representing the content (variable value) list to store the content associated with the found vocabulary name.
 * delimits:   A delimits array representing where delimits exist within the buffer.
 * variable:   A set of ranges representing the entire vocabulary (variable name), content, and the syntax.
 * vocabulary: A set of ranges representing the vocabulary (variable name) list to store the found vocabulary name.
 */
#ifndef _di_f_iki_data_t_
  typedef struct {
    f_string_ranges_t content;
    f_array_lengths_t delimits;
    f_string_ranges_t variable;
    f_string_ranges_t vocabulary;
  } f_iki_data_t;

  #define f_iki_data_t_initialize { \
    f_string_ranges_t_initialize, \
    f_array_lengths_t_initialize, \
    f_string_ranges_t_initialize, \
    f_string_ranges_t_initialize, \
  }

  #define macro_f_iki_data_t_initialize(content, delimits, variable, vocabulary) { content, delimits, variable, vocabulary }

  #define macro_f_iki_data_t_clear(data) \
    f_string_ranges_t_clear(data.content) \
    f_array_lengths_t_clear(data.delimits) \
    f_string_ranges_t_clear(data.variable) \
    f_string_ranges_t_clear(data.vocabulary)

  #define macro_f_iki_data_t_delete_simple(data)  status = f_iki_data_delete(data);
  #define macro_f_iki_data_t_destroy_simple(data) status = f_iki_data_destroy(data);
#endif // _di_f_iki_data_t_

/**
 * An array of f_iki_data_t.
 *
 * array: The array of IKI data.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_iki_datas_t_
  typedef struct {
    f_iki_data_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_iki_datas_t;

  #define f_iki_datas_t_initialize { 0, 0, 0 }

  #define macro_f_iki_datas_t_initialize(content, size, used) { array, size, used }
  #define macro_f_iki_datas_t_initialize2(array, length) { array, length, length }

  #define macro_f_iki_datas_t_clear(datas) macro_f_memory_structure_clear(datas)

  #define macro_f_iki_datas_t_resize(status, datas, length) status = f_iki_datas_resize(length, &datas);
  #define macro_f_iki_datas_t_adjust(status, datas, length) status = f_iki_datas_adjust(length, &datas);

  #define macro_f_iki_datas_t_delete_simple(datas)  status = f_iki_datas_resize(0, &datas);
  #define macro_f_iki_datas_t_destroy_simple(datas) status = f_iki_datas_adjust(0, &datas);

  #define macro_f_iki_datas_t_increase(status, step, datas)      status = f_iki_datas_increase(step, &datas);
  #define macro_f_iki_datas_t_increase_by(status, datas, amount) status = f_iki_datas_increase_by(amount, &datas);
  #define macro_f_iki_datas_t_decrease_by(status, datas, amount) status = f_iki_datas_decrease_by(amount, &datas);
  #define macro_f_iki_datas_t_decimate_by(status, datas, amount) status = f_iki_datas_decimate_by(amount, &datas);
#endif // _di_f_iki_datas_t_

/**
 * An array of f_iki_datas_t.
 *
 * array: The array of IKI datas.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_iki_datass_t_
  typedef struct {
    f_iki_datas_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } f_iki_datass_t;

  #define f_iki_datass_t_initialize { 0, 0, 0 }

  #define macro_f_iki_datass_t_initialize(content, size, used) { array, size, used }
  #define macro_f_iki_datass_t_initialize2(array, length) { array, length, length }

  #define macro_f_iki_datass_t_clear(datas) macro_f_memory_structure_clear(datas)

  #define macro_f_iki_datass_t_resize(status, datas, length) status = f_iki_datass_resize(length, &datas);
  #define macro_f_iki_datass_t_adjust(status, datas, length) status = f_iki_datass_adjust(length, &datas);

  #define macro_f_iki_datass_t_delete_simple(datas)  status = f_iki_datass_resize(0, &datas);
  #define macro_f_iki_datass_t_destroy_simple(datas) status = f_iki_datass_adjust(0, &datas);

  #define macro_f_iki_datass_t_increase(status, step, datas)      status = f_iki_datass_increase(step, &datas);
  #define macro_f_iki_datass_t_increase_by(status, datas, amount) status = f_iki_datass_increase_by(amount, &datas);
  #define macro_f_iki_datass_t_decrease_by(status, datas, amount) status = f_iki_datass_decrease_by(amount, &datas);
  #define macro_f_iki_datass_t_decimate_by(status, datas, amount) status = f_iki_datass_decimate_by(amount, &datas);
#endif // _di_f_iki_datass_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_iki_common_h
