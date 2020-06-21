/**
 * FLL - Level 0
 *
 * Project: Iki
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines iki common data.
 *
 * This is auto-included by iki.h and should not need to be explicitly included.
 */
#ifndef _F_iki_h
#define _F_iki_h

// libc includes
#include <stdio.h>
#include <sys/stat.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/string.h>
#include <level_0/type.h>

#ifdef __cplusplus
extern "C" {
#endif

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
  #define iki_vocabulary_0001_variable "var"

  #define iki_vocabulary_0001_variable_length 3
#endif // _di_iki_vocabulary_0001_

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

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_iki_h
