/**
 * FLL - Level 3
 *
 * Project: FSS Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_write_common_string_h
#define _fss_write_common_string_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_fss_write_program_version_s_
  #define FSS_WRITE_program_version_major_s F_string_ascii_0_s
  #define FSS_WRITE_program_version_minor_s F_string_ascii_7_s
  #define FSS_WRITE_program_version_micro_s F_string_ascii_0_s

  #define FSS_WRITE_program_version_major_s_length F_string_ascii_0_s_length
  #define FSS_WRITE_program_version_minor_s_length F_string_ascii_7_s_length
  #define FSS_WRITE_program_version_micro_s_length F_string_ascii_0_s_length

  #if !(defined(FSS_WRITE_program_version_nano_prefix_s) && defined(FSS_WRITE_program_version_nano_prefix_s_length))
    #define FSS_WRITE_program_version_nano_prefix_s
    #define FSS_WRITE_program_version_nano_prefix_s_length 0
  #endif // !(defined(FSS_WRITE_program_version_nano_prefix_s) && defined(FSS_WRITE_program_version_nano_prefix_s_length))

  #if !(defined(FSS_WRITE_program_version_nano_s) && defined(FSS_WRITE_program_version_nano_s_length))
    #define FSS_WRITE_program_version_nano_s
    #define FSS_WRITE_program_version_nano_s_length 0
  #endif // !(defined(FSS_WRITE_program_version_nano_s) && defined(FSS_WRITE_program_version_nano_s_length))

  #define FSS_WRITE_program_version_s FSS_WRITE_program_version_major_s F_string_ascii_period_s FSS_WRITE_program_version_minor_s F_string_ascii_period_s FSS_WRITE_program_version_micro_s FSS_WRITE_program_version_nano_prefix_s FSS_WRITE_program_version_nano_s

  #define FSS_WRITE_program_version_s_length FSS_WRITE_program_version_major_s_length + F_string_ascii_period_s_length + FSS_WRITE_program_version_minor_s_length + F_string_ascii_period_s_length + FSS_WRITE_program_version_micro_s_length + FSS_WRITE_program_version_nano_prefix_s_length + FSS_WRITE_program_version_nano_s_length

  extern const f_string_static_t fss_write_program_version_s;
#endif // _di_fss_write_program_version_s_

/**
 * The program name.
 */
#ifndef _di_fss_write_program_name_s_
  #define FSS_WRITE_program_name_s      "fss_write"
  #define FSS_WRITE_program_name_long_s "FSS Write"

  #define FSS_WRITE_program_name_s_length      9
  #define FSS_WRITE_program_name_long_s_length 9

  extern const f_string_static_t fss_write_program_name_s;
  extern const f_string_static_t fss_write_program_name_long_s;
#endif // _di_fss_write_program_name_s_

/**
 * The program pipe strings.
 *
 * The fss_write_pipe_content_*_s strings are strings rather than characters to allow for wide characters.
 *
 * fss_write_pipe_content_*_s:
 *   - end:    The character representing the end of content.
 *   - ignore: The character representing the start of or end of a set of characters to ignore.
 *   - start:  The character representing the start of content.
 *
 * macro_fss_write_setting:
 *   - Used to represent a cast to ((fss_write_setting_t *) setting).
 *   - Simplifies the number of parenthesis used to make code slightly cleaner.
 *   - Is wrapped in a parenthesis and not a block.
 */
#ifndef _di_fss_write_pipe_s_
  #define FSS_WRITE_pipe_content_end_s    "\f"
  #define FSS_WRITE_pipe_content_ignore_s "\v"
  #define FSS_WRITE_pipe_content_start_s  "\b"

  #define FSS_WRITE_pipe_content_end_s_length    1
  #define FSS_WRITE_pipe_content_ignore_s_length 1
  #define FSS_WRITE_pipe_content_start_s_length  1

  extern const f_string_static_t fss_write_pipe_content_end_s;
  extern const f_string_static_t fss_write_pipe_content_ignore_s;
  extern const f_string_static_t fss_write_pipe_content_start_s;
#endif // _di_fss_write_pipe_s_

/**
 * A collection of static strings associated with FSS Payload Write.
 */
#ifndef _di_fss_write_s_
  #define FSS_WRITE_string_two_s "two"

  #define FSS_WRITE_string_two_s_length 3

  extern const f_string_static_t fss_write_string_two_s;
#endif // _di_fss_write_s_

/**
 * The main program parameters.
 */
#ifndef _di_fss_write_parameter_s_
  #define FSS_WRITE_short_as_s           "A"
  #define FSS_WRITE_short_backtick_s     "b"
  #define FSS_WRITE_short_content_s      "c"
  #define FSS_WRITE_short_content_end_s  "E"
  #define FSS_WRITE_short_content_next_s "N"
  #define FSS_WRITE_short_double_s       "d"
  #define FSS_WRITE_short_file_s         "f"
  #define FSS_WRITE_short_ignore_s       "I"
  #define FSS_WRITE_short_object_s       "o"
  #define FSS_WRITE_short_object_open_s  "O"
  #define FSS_WRITE_short_partial_s      "p"
  #define FSS_WRITE_short_prepend_s      "P"
  #define FSS_WRITE_short_single_s       "s"
  #define FSS_WRITE_short_trim_s         "T"

  #define FSS_WRITE_long_as_s           "as"
  #define FSS_WRITE_long_backtick_s     "backtick"
  #define FSS_WRITE_long_content_s      "content"
  #define FSS_WRITE_long_content_end_s  "content_end"
  #define FSS_WRITE_long_content_next_s "content_next"
  #define FSS_WRITE_long_double_s       "double"
  #define FSS_WRITE_long_file_s         "file"
  #define FSS_WRITE_long_ignore_s       "ignore"
  #define FSS_WRITE_long_object_s       "object"
  #define FSS_WRITE_long_object_open_s  "object_open"
  #define FSS_WRITE_long_partial_s      "partial"
  #define FSS_WRITE_long_prepend_s      "prepend"
  #define FSS_WRITE_long_single_s       "single"
  #define FSS_WRITE_long_trim_s         "trim"

  #define FSS_WRITE_short_as_s_length           1
  #define FSS_WRITE_short_backtick_s_length     1
  #define FSS_WRITE_short_content_s_length      1
  #define FSS_WRITE_short_content_end_s_length  1
  #define FSS_WRITE_short_content_next_s_length 1
  #define FSS_WRITE_short_double_s_length       1
  #define FSS_WRITE_short_file_s_length         1
  #define FSS_WRITE_short_ignore_s_length       1
  #define FSS_WRITE_short_object_s_length       1
  #define FSS_WRITE_short_object_open_s_length  1
  #define FSS_WRITE_short_partial_s_length      1
  #define FSS_WRITE_short_prepend_s_length      1
  #define FSS_WRITE_short_single_s_length       1
  #define FSS_WRITE_short_trim_s_length         1

  #define FSS_WRITE_long_as_s_length           2
  #define FSS_WRITE_long_backtick_s_length     8
  #define FSS_WRITE_long_content_s_length      7
  #define FSS_WRITE_long_content_end_s_length  11
  #define FSS_WRITE_long_content_next_s_length 12
  #define FSS_WRITE_long_double_s_length       6
  #define FSS_WRITE_long_file_s_length         4
  #define FSS_WRITE_long_ignore_s_length       6
  #define FSS_WRITE_long_object_s_length       6
  #define FSS_WRITE_long_object_open_s_length  11
  #define FSS_WRITE_long_partial_s_length      7
  #define FSS_WRITE_long_prepend_s_length      7
  #define FSS_WRITE_long_single_s_length       6
  #define FSS_WRITE_long_trim_s_length         4

  extern const f_string_static_t fss_write_short_as_s;
  extern const f_string_static_t fss_write_short_backtick_s;
  extern const f_string_static_t fss_write_short_content_s;
  extern const f_string_static_t fss_write_short_content_end_s;
  extern const f_string_static_t fss_write_short_content_next_s;
  extern const f_string_static_t fss_write_short_double_s;
  extern const f_string_static_t fss_write_short_file_s;
  extern const f_string_static_t fss_write_short_ignore_s;
  extern const f_string_static_t fss_write_short_object_s;
  extern const f_string_static_t fss_write_short_object_open_s;
  extern const f_string_static_t fss_write_short_partial_s;
  extern const f_string_static_t fss_write_short_prepend_s;
  extern const f_string_static_t fss_write_short_single_s;
  extern const f_string_static_t fss_write_short_trim_s;

  extern const f_string_static_t fss_write_long_as_s;
  extern const f_string_static_t fss_write_long_backtick_s;
  extern const f_string_static_t fss_write_long_content_s;
  extern const f_string_static_t fss_write_long_content_end_s;
  extern const f_string_static_t fss_write_long_content_next_s;
  extern const f_string_static_t fss_write_long_double_s;
  extern const f_string_static_t fss_write_long_file_s;
  extern const f_string_static_t fss_write_long_ignore_s;
  extern const f_string_static_t fss_write_long_object_s;
  extern const f_string_static_t fss_write_long_object_open_s;
  extern const f_string_static_t fss_write_long_partial_s;
  extern const f_string_static_t fss_write_long_prepend_s;
  extern const f_string_static_t fss_write_long_single_s;
  extern const f_string_static_t fss_write_long_trim_s;
#endif // _di_fss_write_parameter_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_common_string_h
