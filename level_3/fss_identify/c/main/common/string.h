/**
 * FLL - Level 3
 *
 * Project: FSS Identify
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common string structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_identify_common_string_h
#define _fss_identify_common_string_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_fss_identify_program_version_s_
  #define FSS_IDENTIFY_program_version_major_s F_string_ascii_0_s
  #define FSS_IDENTIFY_program_version_minor_s F_string_ascii_7_s
  #define FSS_IDENTIFY_program_version_micro_s F_string_ascii_0_s

  #define FSS_IDENTIFY_program_version_major_s_length F_string_ascii_0_s_length
  #define FSS_IDENTIFY_program_version_minor_s_length F_string_ascii_7_s_length
  #define FSS_IDENTIFY_program_version_micro_s_length F_string_ascii_0_s_length

  #if !(defined(FSS_IDENTIFY_program_version_nano_prefix_s) && defined(FSS_IDENTIFY_program_version_nano_prefix_s_length))
    #define FSS_IDENTIFY_program_version_nano_prefix_s
    #define FSS_IDENTIFY_program_version_nano_prefix_s_length 0
  #endif // !(defined(FSS_IDENTIFY_program_version_nano_prefix_s) && defined(FSS_IDENTIFY_program_version_nano_prefix_s_length))

  #if !(defined(FSS_IDENTIFY_program_version_nano_s) && defined(FSS_IDENTIFY_program_version_nano_s_length))
    #define FSS_IDENTIFY_program_version_nano_s
    #define FSS_IDENTIFY_program_version_nano_s_length 0
  #endif // !(defined(FSS_IDENTIFY_program_version_nano_s) && defined(FSS_IDENTIFY_program_version_nano_s_length))

  #define FSS_IDENTIFY_program_version_s FSS_IDENTIFY_program_version_major_s F_string_ascii_period_s FSS_IDENTIFY_program_version_minor_s F_string_ascii_period_s FSS_IDENTIFY_program_version_micro_s FSS_IDENTIFY_program_version_nano_prefix_s FSS_IDENTIFY_program_version_nano_s

  #define FSS_IDENTIFY_program_version_s_length FSS_IDENTIFY_program_version_major_s_length + F_string_ascii_period_s_length + FSS_IDENTIFY_program_version_minor_s_length + F_string_ascii_period_s_length + FSS_IDENTIFY_program_version_micro_s_length + FSS_IDENTIFY_program_version_nano_prefix_s_length + FSS_IDENTIFY_program_version_nano_s_length

  extern const f_string_static_t fss_identify_program_version_s;
#endif // _di_fss_identify_program_version_s_

/**
 * The program name.
 */
#ifndef _di_fss_identify_program_name_s_
  #define FSS_IDENTIFY_program_name_s      "fss_identify"
  #define FSS_IDENTIFY_program_name_long_s "FSS Identify"

  #define FSS_IDENTIFY_program_name_s_length      12
  #define FSS_IDENTIFY_program_name_long_s_length 12

  extern const f_string_static_t fss_identify_program_name_s;
  extern const f_string_static_t fss_identify_program_name_long_s;
#endif // _di_fss_identify_program_name_s_

/**
 * The program help related data.
 */
#ifndef _di_fss_identify_program_help_parameters_s_
  #define FSS_IDENTIFY_program_help_parameters_s "filename(s)"
  #define FSS_IDENTIFY_program_help_parameters_s_length 11

  extern const f_string_static_t fss_identify_program_help_parameters_s;
#endif // _di_fss_identify_program_help_parameters_s_

/**
 * The main program parameters.
 */
#ifndef _di_fss_identify_parameter_s_
  #define FSS_IDENTIFY_short_content_s "c"
  #define FSS_IDENTIFY_short_line_s    "l"
  #define FSS_IDENTIFY_short_name_s    "n"
  #define FSS_IDENTIFY_short_object_s  "o"
  #define FSS_IDENTIFY_short_total_s   "t"

  #define FSS_IDENTIFY_long_content_s "content"
  #define FSS_IDENTIFY_long_line_s    "line"
  #define FSS_IDENTIFY_long_name_s    "name"
  #define FSS_IDENTIFY_long_object_s  "object"
  #define FSS_IDENTIFY_long_total_s   "total"

  #define FSS_IDENTIFY_short_content_s_length 1
  #define FSS_IDENTIFY_short_line_s_length    1
  #define FSS_IDENTIFY_short_name_s_length    1
  #define FSS_IDENTIFY_short_object_s_length  1
  #define FSS_IDENTIFY_short_total_s_length   1

  #define FSS_IDENTIFY_long_content_s_length 7
  #define FSS_IDENTIFY_long_line_s_length    4
  #define FSS_IDENTIFY_long_name_s_length    4
  #define FSS_IDENTIFY_long_object_s_length  6
  #define FSS_IDENTIFY_long_total_s_length   5

  extern const f_string_static_t fss_identify_short_content_s;
  extern const f_string_static_t fss_identify_short_line_s;
  extern const f_string_static_t fss_identify_short_name_s;
  extern const f_string_static_t fss_identify_short_object_s;
  extern const f_string_static_t fss_identify_short_total_s;

  extern const f_string_static_t fss_identify_long_content_s;
  extern const f_string_static_t fss_identify_long_line_s;
  extern const f_string_static_t fss_identify_long_name_s;
  extern const f_string_static_t fss_identify_long_object_s;
  extern const f_string_static_t fss_identify_long_total_s;
#endif // _di_fss_identify_parameter_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_identify_common_string_h
