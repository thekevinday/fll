/**
 * FLL - Level 3
 *
 * Project: IKI Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common string structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _iki_read_common_string_h
#define _iki_read_common_string_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_iki_read_program_version_s_
  #define IKI_READ_program_version_major_s F_string_ascii_0_s
  #define IKI_READ_program_version_minor_s F_string_ascii_7_s
  #define IKI_READ_program_version_micro_s F_string_ascii_0_s

  #define IKI_READ_program_version_major_s_length F_string_ascii_0_s_length
  #define IKI_READ_program_version_minor_s_length F_string_ascii_7_s_length
  #define IKI_READ_program_version_micro_s_length F_string_ascii_0_s_length

  #if !(defined(IKI_READ_program_version_nano_prefix_s) && defined(IKI_READ_program_version_nano_prefix_s_length))
    #define IKI_READ_program_version_nano_prefix_s
    #define IKI_READ_program_version_nano_prefix_s_length 0
  #endif // !(defined(IKI_READ_program_version_nano_prefix_s) && defined(IKI_READ_program_version_nano_prefix_s_length))

  #if !(defined(IKI_READ_program_version_nano_s) && defined(IKI_READ_program_version_nano_s_length))
    #define IKI_READ_program_version_nano_s
    #define IKI_READ_program_version_nano_s_length 0
  #endif // !(defined(IKI_READ_program_version_nano_s) && defined(IKI_READ_program_version_nano_s_length))

  #define IKI_READ_program_version_s IKI_READ_program_version_major_s F_string_ascii_period_s IKI_READ_program_version_minor_s F_string_ascii_period_s IKI_READ_program_version_micro_s IKI_READ_program_version_nano_prefix_s IKI_READ_program_version_nano_s

  #define IKI_READ_program_version_s_length IKI_READ_program_version_major_s_length + F_string_ascii_period_s_length + IKI_READ_program_version_minor_s_length + F_string_ascii_period_s_length + IKI_READ_program_version_micro_s_length + IKI_READ_program_version_nano_prefix_s_length + IKI_READ_program_version_nano_s_length

  extern const f_string_static_t iki_read_program_version_s;
#endif // _di_iki_read_program_version_s_

/**
 * The program name.
 */
#ifndef _di_iki_read_program_name_s_
  #define IKI_READ_program_name_s      "iki_read"
  #define IKI_READ_program_name_long_s "IKI Read"

  #define IKI_READ_program_name_s_length      8
  #define IKI_READ_program_name_long_s_length 8

  extern const f_string_static_t iki_read_program_name_s;
  extern const f_string_static_t iki_read_program_name_long_s;
#endif // _di_iki_read_program_name_s_

/**
 * A collection of static strings associated with IKI Read.
 */
#ifndef _di_iki_read_s_
  #define IKI_READ_string_two_s   "two"
  #define IKI_READ_string_three_s "three"

  #define IKI_READ_string_two_s_length   3
  #define IKI_READ_string_three_s_length 5

  extern const f_string_static_t iki_read_string_two_s;
  extern const f_string_static_t iki_read_string_three_s;
#endif // _di_iki_read_s_

#ifndef _di_iki_read_substitution_s_
  #define IKI_READ_substitution_after_s      "after"
  #define IKI_READ_substitution_before_s     "before"
  #define IKI_READ_substitution_replace_s    "replace"
  #define IKI_READ_substitution_vocabulary_s "vocabulary"
  #define IKI_READ_substitution_with_s       "with"

  #define IKI_READ_substitution_after_s_length      5
  #define IKI_READ_substitution_before_s_length     6
  #define IKI_READ_substitution_replace_s_length    7
  #define IKI_READ_substitution_vocabulary_s_length 10
  #define IKI_READ_substitution_with_s_length       4

  extern const f_string_static_t iki_read_substitution_after_s;
  extern const f_string_static_t iki_read_substitution_before_s;
  extern const f_string_static_t iki_read_substitution_replace_s;
  extern const f_string_static_t iki_read_substitution_vocabulary_s;
  extern const f_string_static_t iki_read_substitution_with_s;
#endif // _di_iki_read_substitution_s_

/**
 * The main program parameters.
 */
#ifndef _di_iki_read_parameter_s_
  #define IKI_READ_short_at_s         "a"
  #define IKI_READ_short_content_s    "c"
  #define IKI_READ_short_line_s       "l"
  #define IKI_READ_short_literal_s    "L"
  #define IKI_READ_short_name_s       "n"
  #define IKI_READ_short_object_s     "o"
  #define IKI_READ_short_reassign_s   "R"
  #define IKI_READ_short_replace_s    "r"
  #define IKI_READ_short_substitute_s "s"
  #define IKI_READ_short_total_s      "t"
  #define IKI_READ_short_whole_s      "w"
  #define IKI_READ_short_wrap_s       "W"

  #define IKI_READ_long_at_s         "at"
  #define IKI_READ_long_content_s    "content"
  #define IKI_READ_long_line_s       "line"
  #define IKI_READ_long_literal_s    "literal"
  #define IKI_READ_long_name_s       "name"
  #define IKI_READ_long_object_s     "object"
  #define IKI_READ_long_reassign_s   "reassign"
  #define IKI_READ_long_replace_s    "replace"
  #define IKI_READ_long_substitute_s "substitute"
  #define IKI_READ_long_total_s      "total"
  #define IKI_READ_long_whole_s      "whole"
  #define IKI_READ_long_wrap_s       "wrap"

  #define IKI_READ_short_at_s_length         1
  #define IKI_READ_short_content_s_length    1
  #define IKI_READ_short_line_s_length       1
  #define IKI_READ_short_literal_s_length    1
  #define IKI_READ_short_name_s_length       1
  #define IKI_READ_short_object_s_length     1
  #define IKI_READ_short_reassign_s_length   1
  #define IKI_READ_short_replace_s_length    1
  #define IKI_READ_short_substitute_s_length 1
  #define IKI_READ_short_total_s_length      1
  #define IKI_READ_short_whole_s_length      1
  #define IKI_READ_short_wrap_s_length       1

  #define IKI_READ_long_at_s_length         2
  #define IKI_READ_long_content_s_length    7
  #define IKI_READ_long_line_s_length       4
  #define IKI_READ_long_literal_s_length    7
  #define IKI_READ_long_name_s_length       4
  #define IKI_READ_long_object_s_length     6
  #define IKI_READ_long_reassign_s_length   8
  #define IKI_READ_long_replace_s_length    7
  #define IKI_READ_long_substitute_s_length 10
  #define IKI_READ_long_total_s_length      5
  #define IKI_READ_long_whole_s_length      5
  #define IKI_READ_long_wrap_s_length       4

  extern const f_string_static_t iki_read_short_at_s;
  extern const f_string_static_t iki_read_short_content_s;
  extern const f_string_static_t iki_read_short_line_s;
  extern const f_string_static_t iki_read_short_literal_s;
  extern const f_string_static_t iki_read_short_name_s;
  extern const f_string_static_t iki_read_short_object_s;
  extern const f_string_static_t iki_read_short_reassign_s;
  extern const f_string_static_t iki_read_short_replace_s;
  extern const f_string_static_t iki_read_short_substitute_s;
  extern const f_string_static_t iki_read_short_total_s;
  extern const f_string_static_t iki_read_short_whole_s;
  extern const f_string_static_t iki_read_short_wrap_s;

  extern const f_string_static_t iki_read_long_at_s;
  extern const f_string_static_t iki_read_long_content_s;
  extern const f_string_static_t iki_read_long_line_s;
  extern const f_string_static_t iki_read_long_literal_s;
  extern const f_string_static_t iki_read_long_name_s;
  extern const f_string_static_t iki_read_long_object_s;
  extern const f_string_static_t iki_read_long_reassign_s;
  extern const f_string_static_t iki_read_long_replace_s;
  extern const f_string_static_t iki_read_long_substitute_s;
  extern const f_string_static_t iki_read_long_total_s;
  extern const f_string_static_t iki_read_long_whole_s;
  extern const f_string_static_t iki_read_long_wrap_s;
#endif // _di_iki_read_parameter_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_read_common_string_h
