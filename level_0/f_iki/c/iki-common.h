/**
 * FLL - Level 0
 *
 * Project: IKI
 * API Version: 0.5
 * Licenses: lgplv2.1
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
  #define f_iki_syntax_separator   ':'
  #define f_iki_syntax_placeholder  0
  #define f_iki_syntax_quote_double '"'
  #define f_iki_syntax_quote_single '\''
  #define f_iki_syntax_slash        '\\'
#endif //_di_f_iki_syntax_

#ifndef _di_iki_vocabulary_0001_s_
  #define iki_vocabulary_0001_address  "address"
  #define iki_vocabulary_0001_code     "code"
  #define iki_vocabulary_0001_email    "email"
  #define iki_vocabulary_0001_name     "name"
  #define iki_vocabulary_0001_phone    "phone"
  #define iki_vocabulary_0001_quote    "quote"
  #define iki_vocabulary_0001_uri      "uri"
  #define iki_vocabulary_0001_url      "url"
  #define iki_vocabulary_0001_urn      "urn"
  #define iki_vocabulary_0001_variable "var"

  #define iki_vocabulary_0001_address_length  7
  #define iki_vocabulary_0001_code_length     4
  #define iki_vocabulary_0001_email_length    5
  #define iki_vocabulary_0001_name_length     4
  #define iki_vocabulary_0001_phone_length    5
  #define iki_vocabulary_0001_quote_length    5
  #define iki_vocabulary_0001_uri_length      3
  #define iki_vocabulary_0001_url_length      3
  #define iki_vocabulary_0001_urn_length      3
  #define iki_vocabulary_0001_variable_length 3

  extern const f_string_t iki_vocabulary_0001_address_s;
  extern const f_string_t iki_vocabulary_0001_code_s;
  extern const f_string_t iki_vocabulary_0001_email_s;
  extern const f_string_t iki_vocabulary_0001_name_s;
  extern const f_string_t iki_vocabulary_0001_phone_s;
  extern const f_string_t iki_vocabulary_0001_quote_s;
  extern const f_string_t iki_vocabulary_0001_uri_s;
  extern const f_string_t iki_vocabulary_0001_url_s;
  extern const f_string_t iki_vocabulary_0001_urn_s;
  extern const f_string_t iki_vocabulary_0001_variable_s;
#endif // _di_iki_vocabulary_0001_s_

#ifndef _di_iki_vocabulary_0002_s_
  #define iki_vocabulary_0002_define    "define"
  #define iki_vocabulary_0002_parameter "parameter"

  #define iki_vocabulary_0002_define_length    6
  #define iki_vocabulary_0002_parameter_length 9

  extern const f_string_t iki_vocabulary_0002_define_s;
  extern const f_string_t iki_vocabulary_0002_parameter_s;
#endif // _di_iki_vocabulary_0002_s_

// @todo: consider IKI-0003 = vocabulary based on context from HTML5 and accessibility-related?

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
  #define f_iki_default_allocation_step 4
#endif // _di_f_iki_default_allocation_step_

/**
 * Reallocate delimits array if necessary for appending a new delimit.
 *
 * state:    The state.
 * status:   The return status to use.
 * delimits: The delimit array to conditionally reallocate.
 */
#ifndef _di_macro_f_iki_allocate_delimits_if_necessary_
  #define macro_f_iki_allocate_delimits_if_necessary(state, status, delimits) \
    status = F_none; \
    if (delimits.used == delimits.size) { \
      if (delimits.used + state.step_small > f_array_length_t_size) { \
        if (delimits.used == f_array_length_t_size) { \
          status = F_status_set_error(F_string_too_large); \
        } \
        else { \
          macro_f_array_lengths_t_resize(status, delimits, delimits.size + 1); \
        } \
      } \
      else { \
        macro_f_array_lengths_t_resize(status, delimits, delimits.size + state.step_small); \
      } \
    }
#endif // _di_macro_f_iki_allocate_delimits_if_necessary_

/**
 * Reallocate delimits array if necessary for appending a new ranges.
 *
 * state:  The state.
 * status: The return status to use.
 * ranges: The delimit array to conditionally reallocate.
 */
#ifndef _di_macro_f_iki_allocate_ranges_if_necessary_
  #define macro_f_iki_allocate_ranges_if_necessary(state, status, ranges) \
    status = F_none; \
    if (ranges.used == ranges.size) { \
      if (ranges.used + state.step_small > f_array_length_t_size) { \
        if (ranges.used == f_array_length_t_size) { \
          status = F_status_set_error(F_string_too_large); \
        } \
        else { \
          macro_f_string_ranges_t_resize(status, ranges, ranges.size + 1); \
        } \
      } \
      else { \
        macro_f_string_ranges_t_resize(status, ranges, ranges.size + state.step_small); \
      } \
    }
#endif // _di_macro_f_iki_allocate_ranges_if_necessary_

/**
 * Determine what the max width is based on the buffer and the range.
 *
 * buffer:    (A pointer) The buffer to determine width against.
 * range:     (A pointer) The range within that buffer to determine against.
 * width_max: The determined width max.
 */
#ifndef _di_macro_f_iki_determine_width_max_
  #define macro_f_iki_determine_width_max(buffer, range, width_max) \
    width_max = (range->stop - range->start) + 1; \
    if (width_max > buffer->used - range->start) { \
      width_max = buffer->used - range->start; \
    }
#endif // _di_macro_f_iki_determine_width_max_

/**
 * Seek until whitespace is found or not found.
 *
 * This will ignore the delimit placeholder.
 *
 * status:    The return status to use.
 * buffer:    (A pointer) The buffer to seek through.
 * range:     (A pointer) The range within that buffer to seek through.
 * width_max: The width_max variable to use fo calculating width_max.
 * condition: Set to TRUE to seek until whitespace is found and FALSE to seek until non-whitespace.
 */
#ifndef _di_macro_f_iki_seek_whitespace_
  #define macro_f_iki_seek_whitespace(status, buffer, range, width_max, condition) \
    while (range->start <= range->stop && range->start < buffer->used) { \
      if (buffer->string[range->start] == f_iki_syntax_placeholder) { \
        range->start++; \
        continue; \
      } \
      macro_f_iki_determine_width_max(buffer, range, width_max); \
      status = f_utf_is_whitespace(buffer->string + range->start, width_max); \
      if (status == condition) break; \
      else if (F_status_is_error(status)) break; \
      status = f_utf_buffer_increment(*buffer, range, 1); \
      if (F_status_is_error(status)) break; \
    }
#endif // _di_macro_f_iki_seek_whitespace_

/**
 * Seek until a word, dash, or plus is found or not found.
 *
 * This will ignore the delimit placeholder.
 *
 * status:    The return status to use.
 * buffer:    (A pointer) The buffer to seek through.
 * range:     (A pointer) The range within that buffer to seek through.
 * width_max: The width_max variable to use fo calculating width_max.
 * condition: Set to TRUE to seek until a word character, dash character, or plus character is found and FALSE to seek until the opposite is found.
 */
#ifndef _di_macro_f_iki_seek_word_dash_plus_
  #define macro_f_iki_seek_word_dash_plus(status, buffer, range, width_max, condition) \
    while (range->start <= range->stop && range->start < buffer->used) { \
      if (buffer->string[range->start] == f_iki_syntax_placeholder) { \
        range->start++; \
        continue; \
      } \
      macro_f_iki_determine_width_max(buffer, range, width_max); \
      status = f_utf_is_word_dash_plus(buffer->string + range->start, width_max, F_false); \
      if (status == condition) break; \
      else if (F_status_is_error(status)) break; \
      status = f_utf_buffer_increment(*buffer, range, 1); \
      if (F_status_is_error(status)) break; \
    }
#endif // _di_macro_f_iki_seek_word_dash_plus_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_iki_common_h
