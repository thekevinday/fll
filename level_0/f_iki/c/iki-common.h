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

#ifndef _di_iki_vocabulary_0000_
  #define iki_vocabulary_0000_emphasis "emphasis"
  #define iki_vocabulary_0000_code     "code"
  #define iki_vocabulary_0000_quote    "quote"
  #define iki_vocabulary_0000_uri      "uri"
  #define iki_vocabulary_0000_url      "url"
  #define iki_vocabulary_0000_urn      "urn"
  #define iki_vocabulary_0000_variable "var"

  #define iki_vocabulary_0000_emphasis_length 8
  #define iki_vocabulary_0000_code_length     4
  #define iki_vocabulary_0000_quote_length    5
  #define iki_vocabulary_0000_uri_length      3
  #define iki_vocabulary_0000_url_length      3
  #define iki_vocabulary_0000_urn_length      3
  #define iki_vocabulary_0000_variable_length 3
#endif // _di_iki_vocabulary_0000_

#ifndef _di_iki_vocabulary_0001_
  #define iki_vocabulary_0001_define    "define"
  #define iki_vocabulary_0001_parameter "parameter"

  #define iki_vocabulary_0001_define_length    6
  #define iki_vocabulary_0001_parameter_length 9
#endif // _di_iki_vocabulary_0001_

/**
 * This holds an array of string ranges that represent the entire vocabulary name, content, and syntax.
 *
 * array: The array of variable.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_iki_variable_
  typedef f_string_ranges f_iki_variable;

  #define f_iki_variable_initialize f_string_ranges_initialize

  #define f_macro_iki_variable_clear(variable) f_macro_string_ranges_clear(variable)

  #define f_macro_iki_variable_new(status, variable, length) f_macro_string_ranges_new(status, variable, length)

  #define f_macro_iki_variable_delete(status, variable)  f_macro_string_ranges_delete(status, variable)
  #define f_macro_iki_variable_destroy(status, variable) f_macro_string_ranges_destroy(status, variable)

  #define f_macro_iki_variable_delete_simple(variable)  f_macro_string_ranges_delete_simple(variable)
  #define f_macro_iki_variable_destroy_simple(variable) f_macro_string_ranges_destroy_simple(variable)

  #define f_macro_iki_variable_resize(status, variable, new_length) f_macro_string_ranges_resize(status, variable, new_length)
  #define f_macro_iki_variable_adjust(status, variable, new_length) f_macro_string_ranges_destroy(status, variable, new_length)
#endif // _di_iki_variable_

/**
 * This holds an array of string ranges that represent the vocabulary names.
 *
 * array: The array of vocabulary names.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_iki_vocabulary_
  typedef f_string_ranges f_iki_vocabulary;

  #define f_iki_vocabulary_initialize f_string_ranges_initialize

  #define f_macro_iki_vocabulary_clear(vocabulary) f_macro_string_ranges_clear(vocabulary)

  #define f_macro_iki_vocabulary_new(status, vocabulary, length) f_macro_string_ranges_new(status, vocabulary, length)

  #define f_macro_iki_vocabulary_delete(status, vocabulary)  f_macro_string_ranges_delete(status, vocabulary)
  #define f_macro_iki_vocabulary_destroy(status, vocabulary) f_macro_string_ranges_destroy(status, vocabulary)

  #define f_macro_iki_vocabulary_delete_simple(vocabulary)  f_macro_string_ranges_delete_simple(vocabulary)
  #define f_macro_iki_vocabulary_destroy_simple(vocabulary) f_macro_string_ranges_destroy_simple(vocabulary)

  #define f_macro_iki_vocabulary_resize(status, vocabulary, new_length) f_macro_string_ranges_resize(status, vocabulary, new_length)
  #define f_macro_iki_vocabulary_adjust(status, vocabulary, new_length) f_macro_string_ranges_destroy(status, vocabulary, new_length)
#endif // _di_iki_vocabulary_

/**
 * This holds an array of f_iki_vocabulary.
 *
 * array: The array of content.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_iki_vocabularys_
  typedef f_string_rangess f_iki_vocabularys;

  #define f_iki_vocabularys_initialize f_string_rangess_initialize

  #define f_macro_iki_vocabularys_clear(content) f_macro_string_rangess_clear(content)

  #define f_macro_iki_vocabularys_new(status, content, length) f_macro_string_rangess_new(status, content, length)

  #define f_macro_iki_vocabularys_delete(status, content)  f_macro_string_rangess_delete(status, content)
  #define f_macro_iki_vocabularys_destroy(status, content) f_macro_string_rangess_destroy(status, content)

  #define f_macro_iki_vocabularys_delete_simple(content)  f_macro_string_rangess_delete_simple(content)
  #define f_macro_iki_vocabularys_destroy_simple(content) f_macro_string_rangess_destroy_simple(content)

  #define f_macro_iki_vocabularys_resize(status, content, new_length) f_macro_string_rangess_resize(status, content, new_length)
  #define f_macro_iki_vocabularys_adjust(status, content, new_length) f_macro_string_rangess_adjust(status, content, new_length)
#endif // _di_iki_vocabularys_

/**
 * This holds an array of string ranges that represent the content.
 *
 * The very first string range will represent the first content found.
 *
 * array: The array of content.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_iki_content_
  typedef f_string_ranges f_iki_content;

  #define f_iki_content_initialize f_string_ranges_initialize

  #define f_macro_iki_content_clear(content) f_macro_string_ranges_clear(content)

  #define f_macro_iki_content_new(status, content, length) f_macro_string_ranges_new(status, content, length)

  #define f_macro_iki_content_delete(status, content)  f_macro_string_ranges_delete(status, content)
  #define f_macro_iki_content_destroy(status, content) f_macro_string_ranges_destroy(status, content)

  #define f_macro_iki_content_delete_simple(content)  f_macro_string_ranges_delete_simple(content)
  #define f_macro_iki_content_destroy_simple(content) f_macro_string_ranges_destroy_simple(content)

  #define f_macro_iki_content_resize(status, content, new_length) f_macro_string_ranges_resize(status, content, new_length)
  #define f_macro_iki_content_adjust(status, content, new_length) f_macro_string_ranges_adjust(status, content, new_length)
#endif // _di_iki_content_

/**
 * This holds an array of f_iki_content.
 *
 * array: The array of content.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_iki_contents_
  typedef f_string_rangess f_iki_contents;

  #define f_iki_contents_initialize f_string_rangess_initialize

  #define f_macro_iki_contents_clear(content) f_macro_string_rangess_clear(content)

  #define f_macro_iki_contents_new(status, content, length) f_macro_string_rangess_new(status, content, length)

  #define f_macro_iki_contents_delete(status, content)  f_macro_string_rangess_delete(status, content)
  #define f_macro_iki_contents_destroy(status, content) f_macro_string_rangess_destroy(status, content)

  #define f_macro_iki_contents_delete_simple(content)  f_macro_string_rangess_delete_simple(content)
  #define f_macro_iki_contents_destroy_simple(content) f_macro_string_rangess_destroy_simple(content)

  #define f_macro_iki_contents_resize(status, content, new_length) f_macro_string_rangess_resize(status, content, new_length)
  #define f_macro_iki_contents_adjust(status, content, new_length) f_macro_string_rangess_adjust(status, content, new_length)
#endif // _di_iki_contents_

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
 * status:   The return status to use.
 * delimits: The delimit array to conditionally reallocate.
 */
#ifndef _di_f_macro_iki_allocate_delimits_if_necessary_
  #define f_macro_iki_allocate_delimits_if_necessary(status, delimits) \
    status = F_none; \
    if (delimits.used + 1 > delimits.size) { \
      if (delimits.used + f_iki_default_allocation_step > f_string_length_size) { \
        if (delimits.used + 1 > f_string_length_size) { \
          status = F_status_set_error(F_string_too_large); \
        } \
        else { \
          f_macro_string_lengths_resize(status, delimits, delimits.size + 1); \
        } \
      } \
      else { \
        f_macro_string_lengths_resize(status, delimits, delimits.size + f_iki_default_allocation_step); \
      } \
    }
#endif // _di_f_macro_iki_allocate_delimits_if_necessary_

/**
 * Reallocate delimits array if necessary for appending a new ranges.
 *
 * status: The return status to use.
 * ranges: The delimit array to conditionally reallocate.
 */
#ifndef _di_f_macro_iki_allocate_ranges_if_necessary_
  #define f_macro_iki_allocate_ranges_if_necessary(status, ranges) \
    status = F_none; \
    if (ranges.used + 1 > ranges.size) { \
      if (ranges.used + f_iki_default_allocation_step > f_string_length_size) { \
        if (ranges.used + 1 > f_string_length_size) { \
          status = F_status_set_error(F_string_too_large); \
        } \
        else { \
          f_macro_string_ranges_resize(status, ranges, ranges.size + 1); \
        } \
      } \
      else { \
        f_macro_string_ranges_resize(status, ranges, ranges.size + f_iki_default_allocation_step); \
      } \
    }
#endif // _di_f_macro_iki_allocate_ranges_if_necessary_

/**
 * Determine what the max width is based on the buffer and the range.
 *
 * buffer:    (A pointer) The buffer to determine width against.
 * range:     (A pointer) The range within that buffer to determine against.
 * width_max: The determined width max.
 */
#ifndef _di_f_macro_iki_determine_width_max_
  #define f_macro_iki_determine_width_max(buffer, range, width_max) \
    width_max = (range->stop - range->start) + 1; \
    if (width_max > buffer->used - range->start) { \
      width_max = buffer->used - range->start; \
    }
#endif // _di_f_macro_iki_determine_width_max_

/**
 * Seek until whitespace is found or not found.
 *
 * This will ignore the delimit placeholder.
 *
 * status:    The return status to use.
 * buffer:    (A pointer) The buffer to seek through.
 * range:     (A pointer) The range within that buffer to seek through.
 * condition: Set to TRUE to seek until whitespace is found and FALSE to seek until non-whitespace.
 */
#ifndef _di_f_macro_iki_seek_whitespace_
  #define f_macro_iki_seek_whitespace(status, buffer, range, width_max, condition) \
    while (range->start <= range->stop && range->start < buffer->used) { \
      if (buffer->string[range->start] == f_iki_syntax_placeholder) { \
        range->start++; \
        continue; \
      } \
      f_macro_iki_determine_width_max(buffer, range, width_max); \
      status = f_utf_is_whitespace(buffer->string + range->start, width_max); \
      if (status == condition) break; \
      else if (F_status_is_error(status)) break; \
      status = f_utf_buffer_increment(*buffer, range, 1); \
      if (F_status_is_error(status)) break; \
    }
#endif // _di_f_macro_iki_seek_whitespace_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_iki_common_h
