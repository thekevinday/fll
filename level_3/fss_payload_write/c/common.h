/**
 * FLL - Level 3
 *
 * Project: FSS Payload Write
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_payload_write_common_h
#define _fss_payload_write_common_h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_payload_write_program_version_
  #define FSS_PAYLOAD_WRITE_program_version_major_s F_string_ascii_0_s
  #define FSS_PAYLOAD_WRITE_program_version_minor_s F_string_ascii_5_s
  #define FSS_PAYLOAD_WRITE_program_version_micro_s F_string_ascii_8_s

  #define FSS_PAYLOAD_WRITE_program_version_major_s_length F_string_ascii_0_s_length
  #define FSS_PAYLOAD_WRITE_program_version_minor_s_length F_string_ascii_5_s_length
  #define FSS_PAYLOAD_WRITE_program_version_micro_s_length F_string_ascii_8_s_length

  #if !(defined(FSS_PAYLOAD_WRITE_program_version_nano_prefix_s) && defined(FSS_PAYLOAD_WRITE_program_version_nano_prefix_s_length))
    #define FSS_PAYLOAD_WRITE_program_version_nano_prefix_s
    #define FSS_PAYLOAD_WRITE_program_version_nano_prefix_s_length 0
  #endif // !(defined(FSS_PAYLOAD_WRITE_program_version_nano_prefix_s) && defined(FSS_PAYLOAD_WRITE_program_version_nano_prefix_s_length))

  #if !(defined(FSS_PAYLOAD_WRITE_program_version_nano_s) && defined(FSS_PAYLOAD_WRITE_program_version_nano_s_length))
    #define FSS_PAYLOAD_WRITE_program_version_nano_s
    #define FSS_PAYLOAD_WRITE_program_version_nano_s_length 0
  #endif // !(defined(FSS_PAYLOAD_WRITE_program_version_nano_s) && defined(FSS_PAYLOAD_WRITE_program_version_nano_s_length))

  #define FSS_PAYLOAD_WRITE_program_version_s FSS_PAYLOAD_WRITE_program_version_major_s F_string_ascii_period_s FSS_PAYLOAD_WRITE_program_version_minor_s F_string_ascii_period_s FSS_PAYLOAD_WRITE_program_version_micro_s FSS_PAYLOAD_WRITE_program_version_nano_prefix_s FSS_PAYLOAD_WRITE_program_version_nano_s

  #define FSS_PAYLOAD_WRITE_program_version_s_length FSS_PAYLOAD_WRITE_program_version_major_s_length + F_string_ascii_period_s_length + FSS_PAYLOAD_WRITE_program_version_minor_s_length + F_string_ascii_period_s_length + FSS_PAYLOAD_WRITE_program_version_micro_s_length + FSS_PAYLOAD_WRITE_program_version_nano_prefix_s_length + FSS_PAYLOAD_WRITE_program_version_nano_s_length

  extern const f_string_static_t fss_payload_write_program_version_s;
#endif // _di_fss_payload_write_program_version_

#ifndef _di_fss_payload_write_program_name_
  #define FSS_PAYLOAD_WRITE_program_name_s      "fss_payload_write"
  #define FSS_PAYLOAD_WRITE_program_name_long_s "FSS Payload Write"

  #define FSS_PAYLOAD_WRITE_program_name_s_length      17
  #define FSS_PAYLOAD_WRITE_program_name_long_s_length 17

  extern const f_string_static_t fss_payload_write_program_name_s;
  extern const f_string_static_t fss_payload_write_program_name_long_s;
#endif // _di_fss_payload_write_program_name_

#ifndef _di_fss_payload_write_defines_
  #define fss_payload_write_signal_check_d 10000

  #define fss_payload_write_pipe_content_end_s    '\f'
  #define fss_payload_write_pipe_content_ignore_s '\v'
  #define fss_payload_write_pipe_content_start_s  '\b'

  #define fss_payload_write_short_file_s    "f"
  #define fss_payload_write_short_content_s "c"
  #define fss_payload_write_short_double_s  "d"
  #define fss_payload_write_short_ignore_s  "I"
  #define fss_payload_write_short_object_s  "o"
  #define fss_payload_write_short_partial_s "p"
  #define fss_payload_write_short_prepend_s "P"
  #define fss_payload_write_short_single_s  "s"
  #define fss_payload_write_short_trim_s    "T"

  #define fss_payload_write_long_file_s    "file"
  #define fss_payload_write_long_content_s "content"
  #define fss_payload_write_long_double_s  "double"
  #define fss_payload_write_long_ignore_s  "ignore"
  #define fss_payload_write_long_object_s  "object"
  #define fss_payload_write_long_partial_s "partial"
  #define fss_payload_write_long_prepend_s "prepend"
  #define fss_payload_write_long_single_s  "single"
  #define fss_payload_write_long_trim_s    "trim"

  enum {
    fss_payload_write_parameter_help_e,
    fss_payload_write_parameter_light_e,
    fss_payload_write_parameter_dark_e,
    fss_payload_write_parameter_no_color_e,
    fss_payload_write_parameter_verbosity_quiet_e,
    fss_payload_write_parameter_verbosity_normal_e,
    fss_payload_write_parameter_verbosity_verbose_e,
    fss_payload_write_parameter_verbosity_debug_e,
    fss_payload_write_parameter_version_e,

    fss_payload_write_parameter_file_e,
    fss_payload_write_parameter_content_e,
    fss_payload_write_parameter_double_e,
    fss_payload_write_parameter_ignore_e,
    fss_payload_write_parameter_object_e,
    fss_payload_write_parameter_partial_e,
    fss_payload_write_parameter_prepend_e,
    fss_payload_write_parameter_single_e,
    fss_payload_write_parameter_trim_e,
  };

  #define fss_payload_write_console_parameter_t_initialize \
    { \
      macro_f_console_parameter_t_initialize(f_console_standard_short_help_s.string, f_console_standard_long_help_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_light_s.string, f_console_standard_long_light_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_dark_s.string, f_console_standard_long_dark_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_no_color_s.string, f_console_standard_long_no_color_s.string, 0, F_false, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_quiet_s.string, f_console_standard_long_quiet_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_normal_s.string, f_console_standard_long_normal_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_verbose_s.string, f_console_standard_long_verbose_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_debug_s.string, f_console_standard_long_debug_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_version_s.string, f_console_standard_long_version_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(fss_payload_write_short_file_s, fss_payload_write_long_file_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_payload_write_short_content_s, fss_payload_write_long_content_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_payload_write_short_double_s, fss_payload_write_long_double_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_payload_write_short_ignore_s, fss_payload_write_long_ignore_s, 0, 2, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_payload_write_short_object_s, fss_payload_write_long_object_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_payload_write_short_partial_s, fss_payload_write_long_partial_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_payload_write_short_prepend_s, fss_payload_write_long_prepend_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_payload_write_short_single_s, fss_payload_write_long_single_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_payload_write_short_trim_s, fss_payload_write_long_trim_s, 0, 0, f_console_type_normal_e), \
    }

  #define fss_payload_write_total_parameters_d 18
#endif // _di_fss_payload_write_defines_

#ifndef _di_fss_payload_write_main_t_
  typedef struct {
    f_console_parameters_t parameters;

    f_array_lengths_t remaining;
    bool process_pipe;

    fl_print_t output;
    fl_print_t error;
    fl_print_t warning;

    f_signal_t signal;

    f_string_static_t prepend;

    f_color_context_t context;
  } fss_payload_write_main_t;

  #define fss_payload_write_main_t_initialize \
    { \
      f_console_parameters_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
      fl_print_t_initialize, \
      macro_fl_print_t_initialize_error(), \
      macro_fl_print_t_initialize_warning(), \
      f_signal_t_initialize, \
      f_string_static_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_fss_payload_write_main_t_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing fss_payload_write_main().
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_payload_write_main()
 */
#ifndef _di_fss_payload_write_main_delete_
  extern f_status_t fss_payload_write_main_delete(fss_payload_write_main_t * const main);
#endif // _di_fss_payload_write_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_payload_write_common_h
