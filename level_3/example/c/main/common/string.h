/**
 * FLL - Level 3
 *
 * Project: Example
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common string structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _example_common_string_h
#define _example_common_string_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_example_program_version_s_
  #define EXAMPLE_program_version_major_s F_string_ascii_0_s
  #define EXAMPLE_program_version_minor_s F_string_ascii_7_s
  #define EXAMPLE_program_version_micro_s F_string_ascii_0_s

  #define EXAMPLE_program_version_major_s_length F_string_ascii_0_s_length
  #define EXAMPLE_program_version_minor_s_length F_string_ascii_7_s_length
  #define EXAMPLE_program_version_micro_s_length F_string_ascii_0_s_length

  #if !(defined(EXAMPLE_program_version_nano_prefix_s) && defined(EXAMPLE_program_version_nano_prefix_s_length))
    #define EXAMPLE_program_version_nano_prefix_s
    #define EXAMPLE_program_version_nano_prefix_s_length 0
  #endif // !(defined(EXAMPLE_program_version_nano_prefix_s) && defined(EXAMPLE_program_version_nano_prefix_s_length))

  #if !(defined(EXAMPLE_program_version_nano_s) && defined(EXAMPLE_program_version_nano_s_length))
    #define EXAMPLE_program_version_nano_s
    #define EXAMPLE_program_version_nano_s_length 0
  #endif // !(defined(EXAMPLE_program_version_nano_s) && defined(EXAMPLE_program_version_nano_s_length))

  #define EXAMPLE_program_version_s EXAMPLE_program_version_major_s F_string_ascii_period_s EXAMPLE_program_version_minor_s F_string_ascii_period_s EXAMPLE_program_version_micro_s EXAMPLE_program_version_nano_prefix_s EXAMPLE_program_version_nano_s

  #define EXAMPLE_program_version_s_length EXAMPLE_program_version_major_s_length + F_string_ascii_period_s_length + EXAMPLE_program_version_minor_s_length + F_string_ascii_period_s_length + EXAMPLE_program_version_micro_s_length + EXAMPLE_program_version_nano_prefix_s_length + EXAMPLE_program_version_nano_s_length

  extern const f_string_static_t example_program_version_s;
#endif // _di_example_program_version_s_

/**
 * The program name.
 */
#ifndef _di_example_program_name_s_
  #define EXAMPLE_program_name_s      "example"
  #define EXAMPLE_program_name_long_s "Example"

  #define EXAMPLE_program_name_s_length      7
  #define EXAMPLE_program_name_long_s_length 7

  extern const f_string_static_t example_program_name_s;
  extern const f_string_static_t example_program_name_long_s;
#endif // _di_example_program_name_s_

/**
 * The main program parameters.
 */
#ifndef _di_example_parameter_s_
  #define EXAMPLE_short_example_s "e"

  #define EXAMPLE_long_example_s "example"

  #define EXAMPLE_short_example_s_length 1

  #define EXAMPLE_long_example_s_length 7

  extern const f_string_static_t example_short_example_s;

  extern const f_string_static_t example_long_example_s;
#endif // _di_example_parameter_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _example_common_string_h
