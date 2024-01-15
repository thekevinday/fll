/**
 * FLL - Level 3
 *
 * Project: IKI Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common string structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _iki_write_common_string_h
#define _iki_write_common_string_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_iki_write_program_version_s_
  #define IKI_WRITE_program_version_major_s F_string_ascii_0_s
  #define IKI_WRITE_program_version_minor_s F_string_ascii_7_s
  #define IKI_WRITE_program_version_micro_s F_string_ascii_0_s

  #define IKI_WRITE_program_version_major_s_length F_string_ascii_0_s_length
  #define IKI_WRITE_program_version_minor_s_length F_string_ascii_7_s_length
  #define IKI_WRITE_program_version_micro_s_length F_string_ascii_0_s_length

  #if !(defined(IKI_WRITE_program_version_nano_prefix_s) && defined(IKI_WRITE_program_version_nano_prefix_s_length))
    #define IKI_WRITE_program_version_nano_prefix_s
    #define IKI_WRITE_program_version_nano_prefix_s_length 0
  #endif // !(defined(IKI_WRITE_program_version_nano_prefix_s) && defined(IKI_WRITE_program_version_nano_prefix_s_length))

  #if !(defined(IKI_WRITE_program_version_nano_s) && defined(IKI_WRITE_program_version_nano_s_length))
    #define IKI_WRITE_program_version_nano_s
    #define IKI_WRITE_program_version_nano_s_length 0
  #endif // !(defined(IKI_WRITE_program_version_nano_s) && defined(IKI_WRITE_program_version_nano_s_length))

  #define IKI_WRITE_program_version_s IKI_WRITE_program_version_major_s F_string_ascii_period_s IKI_WRITE_program_version_minor_s F_string_ascii_period_s IKI_WRITE_program_version_micro_s IKI_WRITE_program_version_nano_prefix_s IKI_WRITE_program_version_nano_s

  #define IKI_WRITE_program_version_s_length IKI_WRITE_program_version_major_s_length + F_string_ascii_period_s_length + IKI_WRITE_program_version_minor_s_length + F_string_ascii_period_s_length + IKI_WRITE_program_version_micro_s_length + IKI_WRITE_program_version_nano_prefix_s_length + IKI_WRITE_program_version_nano_s_length

  extern const f_string_static_t iki_write_program_version_s;
#endif // _di_iki_write_program_version_s_

/**
 * The program name.
 */
#ifndef _di_iki_write_program_name_s_
  #define IKI_WRITE_program_name_s      "iki_write"
  #define IKI_WRITE_program_name_long_s "IKI Write"

  #define IKI_WRITE_program_name_s_length      9
  #define IKI_WRITE_program_name_long_s_length 9

  extern const f_string_static_t iki_write_program_name_s;
  extern const f_string_static_t iki_write_program_name_long_s;
#endif // _di_iki_write_program_name_s_

/**
 * Special strings used by this program.
 */
#ifndef _di_iki_write_s_
  #define IKI_WRITE_object_s  "object"

  #define IKI_WRITE_object_s_length 6

  extern const f_string_static_t iki_write_object_s;
#endif // _di_iki_write_s_

/**
 * The main program parameters.
 */
#ifndef _di_iki_write_parameter_s_
  #define IKI_WRITE_short_content_s "c"
  #define IKI_WRITE_short_double_s  "d"
  #define IKI_WRITE_short_file_s    "f"
  #define IKI_WRITE_short_grave_s   "g"
  #define IKI_WRITE_short_object_s  "o"
  #define IKI_WRITE_short_single_s  "s"
  #define IKI_WRITE_short_wrap_s    "w"

  #define IKI_WRITE_long_content_s "content"
  #define IKI_WRITE_long_double_s  "double"
  #define IKI_WRITE_long_file_s    "file"
  #define IKI_WRITE_long_grave_s   "grave"
  #define IKI_WRITE_long_object_s  "object"
  #define IKI_WRITE_long_single_s  "single"
  #define IKI_WRITE_long_wrap_s    "wrap"

  #define IKI_WRITE_short_content_s_length 1
  #define IKI_WRITE_short_double_s_length  1
  #define IKI_WRITE_short_file_s_length    1
  #define IKI_WRITE_short_grave_s_length   1
  #define IKI_WRITE_short_object_s_length  1
  #define IKI_WRITE_short_single_s_length  1
  #define IKI_WRITE_short_wrap_s_length    1

  #define IKI_WRITE_long_content_s_length 7
  #define IKI_WRITE_long_double_s_length  6
  #define IKI_WRITE_long_file_s_length    4
  #define IKI_WRITE_long_grave_s_length   5
  #define IKI_WRITE_long_object_s_length  6
  #define IKI_WRITE_long_single_s_length  6
  #define IKI_WRITE_long_wrap_s_length    4

  extern const f_string_static_t iki_write_short_content_s;
  extern const f_string_static_t iki_write_short_double_s;
  extern const f_string_static_t iki_write_short_file_s;
  extern const f_string_static_t iki_write_short_grave_s;
  extern const f_string_static_t iki_write_short_object_s;
  extern const f_string_static_t iki_write_short_single_s;
  extern const f_string_static_t iki_write_short_wrap_s;

  extern const f_string_static_t iki_write_long_content_s;
  extern const f_string_static_t iki_write_long_double_s;
  extern const f_string_static_t iki_write_long_file_s;
  extern const f_string_static_t iki_write_long_grave_s;
  extern const f_string_static_t iki_write_long_object_s;
  extern const f_string_static_t iki_write_long_single_s;
  extern const f_string_static_t iki_write_long_wrap_s;
#endif // _di_iki_write_parameter_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_write_common_string_h
