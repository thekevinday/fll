/**
 * FLL - Level 3
 *
 * Project: IKI Write
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _iki_write_common_h
#define _iki_write_common_h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_program_version_
  #define IKI_WRITE_program_version_major_s F_string_ascii_0_s
  #define IKI_WRITE_program_version_minor_s F_string_ascii_5_s
  #define IKI_WRITE_program_version_micro_s F_string_ascii_8_s

  #define IKI_WRITE_program_version_major_s_length F_string_ascii_0_s_length
  #define IKI_WRITE_program_version_minor_s_length F_string_ascii_5_s_length
  #define IKI_WRITE_program_version_micro_s_length F_string_ascii_8_s_length

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
#endif // _di_iki_write_program_version_

#ifndef _di_iki_write_program_name_
  #define iki_write_program_name_s      "iki_write"
  #define iki_write_program_name_long_s "IKI Write"

  #define IKI_WRITE_program_name_s_length      9
  #define IKI_WRITE_program_name_long_s_length 9

  extern const f_string_static_t iki_write_program_name_s;
  extern const f_string_static_t iki_write_program_name_long_s;
#endif // _di_iki_write_program_name_

#ifndef _di_iki_write_defines_
  #define iki_write_signal_check_d 10000

  #define iki_write_short_file_s    "f"
  #define iki_write_short_content_s "c"
  #define iki_write_short_double_s  "d"
  #define iki_write_short_object_s  "o"
  #define iki_write_short_single_s  "s"

  #define iki_write_long_file_s    "file"
  #define iki_write_long_content_s "content"
  #define iki_write_long_double_s  "double"
  #define iki_write_long_object_s  "object"
  #define iki_write_long_single_s  "single"

  enum {
    iki_write_parameter_help_e,
    iki_write_parameter_light_e,
    iki_write_parameter_dark_e,
    iki_write_parameter_no_color_e,
    iki_write_parameter_verbosity_quiet_e,
    iki_write_parameter_verbosity_normal_e,
    iki_write_parameter_verbosity_verbose_e,
    iki_write_parameter_verbosity_debug_e,
    iki_write_parameter_version_e,

    iki_write_parameter_file_e,
    iki_write_parameter_content_e,
    iki_write_parameter_double_e,
    iki_write_parameter_object_e,
    iki_write_parameter_single_e,
  };

  #define iki_write_console_parameter_t_initialize \
    { \
      macro_f_console_parameter_t_initialize(f_console_standard_short_help_s.string, f_console_standard_long_help_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_light_s.string, f_console_standard_long_light_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_dark_s.string, f_console_standard_long_dark_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_no_color_s.string, f_console_standard_long_no_color_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_quiet_s.string, f_console_standard_long_quiet_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_normal_s.string, f_console_standard_long_normal_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_verbose_s.string, f_console_standard_long_verbose_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_debug_s.string, f_console_standard_long_debug_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_version_s.string, f_console_standard_long_version_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(iki_write_short_file_s, iki_write_long_file_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_write_short_content_s, iki_write_long_content_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_write_short_double_s, iki_write_long_double_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_write_short_object_s, iki_write_long_object_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(iki_write_short_single_s, iki_write_long_single_s, 0, 0, f_console_type_normal_e), \
    }

  #define iki_write_total_parameters_d 14
#endif // _di_iki_write_defines_

#ifndef _di_iki_write_main_t_
  typedef struct {
    f_console_parameters_t parameters;

    f_array_lengths_t remaining;
    bool process_pipe;

    fl_print_t output;
    fl_print_t error;
    fl_print_t warning;

    f_signal_t signal;

    f_string_static_t quote;
    f_string_dynamic_t buffer;

    f_color_context_t context;
  } iki_write_main_t;

  #define iki_write_main_t_initialize \
    { \
      f_console_parameters_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
      fl_print_t_initialize, \
      macro_fl_print_t_initialize_error(), \
      macro_fl_print_t_initialize_warning(), \
      f_signal_t_initialize, \
      f_string_static_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_iki_write_main_t_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing iki_write_main().
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see iki_write_main()
 */
#ifndef _di_iki_write_main_delete_
  extern f_status_t iki_write_main_delete(iki_write_main_t * const main);
#endif // _di_iki_write_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_write_common_h
