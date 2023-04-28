/**
 * FLL - Level 3
 *
 * Project: FSS Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_read_common_string_h
#define _fss_read_common_string_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_fss_read_program_version_s_
  #define FSS_READ_program_version_major_s F_string_ascii_0_s
  #define FSS_READ_program_version_minor_s F_string_ascii_7_s
  #define FSS_READ_program_version_micro_s F_string_ascii_0_s

  #define FSS_READ_program_version_major_s_length F_string_ascii_0_s_length
  #define FSS_READ_program_version_minor_s_length F_string_ascii_7_s_length
  #define FSS_READ_program_version_micro_s_length F_string_ascii_0_s_length

  #if !(defined(FSS_READ_program_version_nano_prefix_s) && defined(FSS_READ_program_version_nano_prefix_s_length))
    #define FSS_READ_program_version_nano_prefix_s
    #define FSS_READ_program_version_nano_prefix_s_length 0
  #endif // !(defined(FSS_READ_program_version_nano_prefix_s) && defined(FSS_READ_program_version_nano_prefix_s_length))

  #if !(defined(FSS_READ_program_version_nano_s) && defined(FSS_READ_program_version_nano_s_length))
    #define FSS_READ_program_version_nano_s
    #define FSS_READ_program_version_nano_s_length 0
  #endif // !(defined(FSS_READ_program_version_nano_s) && defined(FSS_READ_program_version_nano_s_length))

  #define FSS_READ_program_version_s FSS_READ_program_version_major_s F_string_ascii_period_s FSS_READ_program_version_minor_s F_string_ascii_period_s FSS_READ_program_version_micro_s FSS_READ_program_version_nano_prefix_s FSS_READ_program_version_nano_s

  #define FSS_READ_program_version_s_length FSS_READ_program_version_major_s_length + F_string_ascii_period_s_length + FSS_READ_program_version_minor_s_length + F_string_ascii_period_s_length + FSS_READ_program_version_micro_s_length + FSS_READ_program_version_nano_prefix_s_length + FSS_READ_program_version_nano_s_length

  extern const f_string_static_t fss_read_program_version_s;
#endif // _di_fss_read_program_version_s_

/**
 * The program name.
 */
#ifndef _di_fss_read_program_name_s_
  #define FSS_READ_program_name_s      "fss_read"
  #define FSS_READ_program_name_long_s "FSS Read"

  #define FSS_READ_program_name_s_length      8
  #define FSS_READ_program_name_long_s_length 8

  extern const f_string_static_t fss_read_program_name_s;
  extern const f_string_static_t fss_read_program_name_long_s;
#endif // _di_fss_read_program_name_s_

/**
 * The program pipe strings.
 *
 * The fss_read_pipe_content_*_s strings are strings rather than characters to allow for wide characters.
 *
 * fss_read_pipe_content_*_s:
 *   - end:    The character representing the end of content.
 *   - ignore: The character representing the start of or end of a set of characters to ignore.
 *   - start:  The character representing the start of content.
 *
 * macro_fss_read_setting:
 *   - Used to represent a cast to ((fss_read_setting_t *) setting).
 *   - Simplifies the number of parenthesis used to make code slightly cleaner.
 *   - Is wrapped in a parenthesis and not a block.
 */
#ifndef _di_fss_read_pipe_s_
  #define FSS_READ_pipe_content_end_s    "\f"
  #define FSS_READ_pipe_content_ignore_s "\v"
  #define FSS_READ_pipe_content_start_s  "\b"

  #define FSS_READ_pipe_content_end_s_length    1
  #define FSS_READ_pipe_content_ignore_s_length 1
  #define FSS_READ_pipe_content_start_s_length  1

  extern const f_string_static_t fss_read_pipe_content_end_s;
  extern const f_string_static_t fss_read_pipe_content_ignore_s;
  extern const f_string_static_t fss_read_pipe_content_start_s;
#endif // _di_fss_read_pipe_s_

/**
 * A collection of static strings associated with FSS Read.
 */
#ifndef _di_fss_read_s_
  #define FSS_READ_string_two_s "two"

  #define FSS_READ_string_two_s_length 3

  extern const f_string_static_t fss_read_string_two_s;
#endif // _di_fss_read_s_

/**
 * FSS Delimit Parameter strings.
 *
 * fss_read_delimit_mode_*:
 *   - all:                    All delimits are to be aplied.
 *   - content:                Content are to have delimits applied.
 *   - content_greater:        Content at this number or higher are to have delimits applied.
 *   - content_greater_object: Objects and Content at this number or higher are to have delimits applied.
 *   - content_lesser:         Content at this number or lower are to have delimits applied.
 *   - content_lesser_object:  Objects and Content at this number or lower are to have delimits applied.
 *   - content_object:         Objects and Content are to have delimits applied
 *   - object:                 Objects arre to have delimits applied.
 */
#ifndef _di_fss_read_delimit_mode_s_
  #define FSS_READ_delimit_mode_name_none_s    "none"
  #define FSS_READ_delimit_mode_name_all_s     "all"
  #define FSS_READ_delimit_mode_name_object_s  "object"
  #define FSS_READ_delimit_mode_name_greater_s "+"
  #define FSS_READ_delimit_mode_name_lesser_s  "-"

  #define FSS_READ_delimit_mode_name_none_s_length    4
  #define FSS_READ_delimit_mode_name_all_s_length     3
  #define FSS_READ_delimit_mode_name_object_s_length  6
  #define FSS_READ_delimit_mode_name_greater_s_length 1
  #define FSS_READ_delimit_mode_name_lesser_s_length  1

  extern const f_string_static_t fss_read_delimit_mode_name_none_s;
  extern const f_string_static_t fss_read_delimit_mode_name_all_s;
  extern const f_string_static_t fss_read_delimit_mode_name_object_s;
  extern const f_string_static_t fss_read_delimit_mode_name_greater_s;
  extern const f_string_static_t fss_read_delimit_mode_name_lesser_s;
#endif // _di_fss_read_delimit_mode_s_

/**
 * The main program parameters.
 */
#ifndef _di_fss_read_parameter_s_
  #define FSS_READ_short_at_s       "a"
  #define FSS_READ_short_content_s  "c"
  #define FSS_READ_short_columns_s  "C"
  #define FSS_READ_short_delimit_s  "D"
  #define FSS_READ_short_depth_s    "d"
  #define FSS_READ_short_empty_s    "e"
  #define FSS_READ_short_line_s     "l"
  #define FSS_READ_short_name_s     "n"
  #define FSS_READ_short_object_s   "o"
  #define FSS_READ_short_pipe_s     "p"
  #define FSS_READ_short_original_s "O"
  #define FSS_READ_short_select_s   "s"
  #define FSS_READ_short_total_s    "t"
  #define FSS_READ_short_trim_s     "T"

  #define FSS_READ_long_at_s       "at"
  #define FSS_READ_long_content_s  "content"
  #define FSS_READ_long_columns_s  "columns"
  #define FSS_READ_long_delimit_s  "delimit"
  #define FSS_READ_long_depth_s    "depth"
  #define FSS_READ_long_empty_s    "empty"
  #define FSS_READ_long_line_s     "line"
  #define FSS_READ_long_name_s     "name"
  #define FSS_READ_long_object_s   "object"
  #define FSS_READ_long_pipe_s     "pipe"
  #define FSS_READ_long_original_s "original"
  #define FSS_READ_long_select_s   "select"
  #define FSS_READ_long_total_s    "total"
  #define FSS_READ_long_trim_s     "trim"

  #define FSS_READ_short_at_s_length       1
  #define FSS_READ_short_content_s_length  1
  #define FSS_READ_short_columns_s_length  1
  #define FSS_READ_short_delimit_s_length  1
  #define FSS_READ_short_depth_s_length    1
  #define FSS_READ_short_empty_s_length    1
  #define FSS_READ_short_line_s_length     1
  #define FSS_READ_short_name_s_length     1
  #define FSS_READ_short_object_s_length   1
  #define FSS_READ_short_pipe_s_length     1
  #define FSS_READ_short_original_s_length 1
  #define FSS_READ_short_select_s_length   1
  #define FSS_READ_short_total_s_length    1
  #define FSS_READ_short_trim_s_length     1

  #define FSS_READ_long_at_s_length       2
  #define FSS_READ_long_content_s_length  7
  #define FSS_READ_long_columns_s_length  7
  #define FSS_READ_long_delimit_s_length  7
  #define FSS_READ_long_depth_s_length    5
  #define FSS_READ_long_empty_s_length    5
  #define FSS_READ_long_line_s_length     4
  #define FSS_READ_long_name_s_length     4
  #define FSS_READ_long_object_s_length   6
  #define FSS_READ_long_pipe_s_length     4
  #define FSS_READ_long_original_s_length 8
  #define FSS_READ_long_select_s_length   6
  #define FSS_READ_long_total_s_length    5
  #define FSS_READ_long_trim_s_length     4

  extern const f_string_static_t fss_read_short_at_s;
  extern const f_string_static_t fss_read_short_content_s;
  extern const f_string_static_t fss_read_short_columns_s;
  extern const f_string_static_t fss_read_short_delimit_s;
  extern const f_string_static_t fss_read_short_depth_s;
  extern const f_string_static_t fss_read_short_empty_s;
  extern const f_string_static_t fss_read_short_line_s;
  extern const f_string_static_t fss_read_short_name_s;
  extern const f_string_static_t fss_read_short_object_s;
  extern const f_string_static_t fss_read_short_pipe_s;
  extern const f_string_static_t fss_read_short_original_s;
  extern const f_string_static_t fss_read_short_select_s;
  extern const f_string_static_t fss_read_short_total_s;
  extern const f_string_static_t fss_read_short_trim_s;

  extern const f_string_static_t fss_read_long_at_s;
  extern const f_string_static_t fss_read_long_content_s;
  extern const f_string_static_t fss_read_long_columns_s;
  extern const f_string_static_t fss_read_long_delimit_s;
  extern const f_string_static_t fss_read_long_depth_s;
  extern const f_string_static_t fss_read_long_empty_s;
  extern const f_string_static_t fss_read_long_line_s;
  extern const f_string_static_t fss_read_long_name_s;
  extern const f_string_static_t fss_read_long_object_s;
  extern const f_string_static_t fss_read_long_pipe_s;
  extern const f_string_static_t fss_read_long_original_s;
  extern const f_string_static_t fss_read_long_select_s;
  extern const f_string_static_t fss_read_long_total_s;
  extern const f_string_static_t fss_read_long_trim_s;
#endif // _di_fss_read_parameter_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_read_common_string_h
