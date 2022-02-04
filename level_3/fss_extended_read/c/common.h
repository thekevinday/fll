/**
 * FLL - Level 3
 *
 * Project: FSS Extended Read
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_extended_read_common_h
#define _fss_extended_read_common_h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_read_program_version_
  #define FSS_EXTENDED_READ_program_version_major_s F_string_ascii_0_s
  #define FSS_EXTENDED_READ_program_version_minor_s F_string_ascii_5_s
  #define FSS_EXTENDED_READ_program_version_micro_s F_string_ascii_8_s

  #define FSS_EXTENDED_READ_program_version_major_s_length F_string_ascii_0_s_length
  #define FSS_EXTENDED_READ_program_version_minor_s_length F_string_ascii_5_s_length
  #define FSS_EXTENDED_READ_program_version_micro_s_length F_string_ascii_8_s_length

  #if !(defined(FSS_EXTENDED_READ_program_version_nano_prefix_s) && defined(FSS_EXTENDED_READ_program_version_nano_prefix_s_length))
    #define FSS_EXTENDED_READ_program_version_nano_prefix_s
    #define FSS_EXTENDED_READ_program_version_nano_prefix_s_length 0
  #endif // !(defined(FSS_EXTENDED_READ_program_version_nano_prefix_s) && defined(FSS_EXTENDED_READ_program_version_nano_prefix_s_length))

  #if !(defined(FSS_EXTENDED_READ_program_version_nano_s) && defined(FSS_EXTENDED_READ_program_version_nano_s_length))
    #define FSS_EXTENDED_READ_program_version_nano_s
    #define FSS_EXTENDED_READ_program_version_nano_s_length 0
  #endif // !(defined(FSS_EXTENDED_READ_program_version_nano_s) && defined(FSS_EXTENDED_READ_program_version_nano_s_length))

  #define FSS_EXTENDED_READ_program_version_s FSS_EXTENDED_READ_program_version_major_s F_string_ascii_period_s FSS_EXTENDED_READ_program_version_minor_s F_string_ascii_period_s FSS_EXTENDED_READ_program_version_micro_s FSS_EXTENDED_READ_program_version_nano_prefix_s FSS_EXTENDED_READ_program_version_nano_s

  #define FSS_EXTENDED_READ_program_version_s_length FSS_EXTENDED_READ_program_version_major_s_length + F_string_ascii_period_s_length + FSS_EXTENDED_READ_program_version_minor_s_length + F_string_ascii_period_s_length + FSS_EXTENDED_READ_program_version_micro_s_length + FSS_EXTENDED_READ_program_version_nano_prefix_s_length + FSS_EXTENDED_READ_program_version_nano_s_length

  extern const f_string_static_t fss_extended_read_program_version_s;
#endif // _di_fss_extended_read_program_version_

#ifndef _di_fss_extended_read_program_name_
  #define FSS_EXTENDED_READ_program_name_s      "fss_extended_read"
  #define FSS_EXTENDED_READ_program_name_long_s "FSS Extended Read"

  #define FSS_EXTENDED_READ_program_name_s_length      17
  #define FSS_EXTENDED_READ_program_name_long_s_length 17

  extern const f_string_static_t fss_extended_read_program_name_s;
  extern const f_string_static_t fss_extended_read_program_name_long_s;
#endif // _di_fss_extended_read_program_name_

#ifndef _di_fss_extended_read_defines_
  #define fss_extended_read_signal_check_d 10000

  #define fss_extended_read_pipe_content_end_s    '\f'
  #define fss_extended_read_pipe_content_ignore_s '\v'
  #define fss_extended_read_pipe_content_start_s  '\b'

  #define fss_extended_read_short_at_s      "a"
  #define fss_extended_read_short_content_s "c"
  #define fss_extended_read_short_columns_s "C"
  #define fss_extended_read_short_delimit_s "D"
  #define fss_extended_read_short_depth_s   "d"
  #define fss_extended_read_short_empty_s   "e"
  #define fss_extended_read_short_line_s    "l"
  #define fss_extended_read_short_name_s    "n"
  #define fss_extended_read_short_object_s  "o"
  #define fss_extended_read_short_pipe_s    "p"
  #define fss_extended_read_short_raw_s     "R"
  #define fss_extended_read_short_select_s  "s"
  #define fss_extended_read_short_total_s   "t"
  #define fss_extended_read_short_trim_s    "T"

  #define fss_extended_read_long_at_s      "at"
  #define fss_extended_read_long_content_s "content"
  #define fss_extended_read_long_columns_s "columns"
  #define fss_extended_read_long_delimit_s "delimit"
  #define fss_extended_read_long_depth_s   "depth"
  #define fss_extended_read_long_empty_s   "empty"
  #define fss_extended_read_long_line_s    "line"
  #define fss_extended_read_long_name_s    "name"
  #define fss_extended_read_long_object_s  "object"
  #define fss_extended_read_long_pipe_s    "pipe"
  #define fss_extended_read_long_raw_s     "raw"
  #define fss_extended_read_long_select_s  "select"
  #define fss_extended_read_long_total_s   "total"
  #define fss_extended_read_long_trim_s    "trim"

  enum {
    fss_extended_read_parameter_help_e,
    fss_extended_read_parameter_light_e,
    fss_extended_read_parameter_dark_e,
    fss_extended_read_parameter_no_color_e,
    fss_extended_read_parameter_verbosity_quiet_e,
    fss_extended_read_parameter_verbosity_normal_e,
    fss_extended_read_parameter_verbosity_verbose_e,
    fss_extended_read_parameter_verbosity_debug_e,
    fss_extended_read_parameter_version_e,

    fss_extended_read_parameter_at_e,
    fss_extended_read_parameter_content_e,
    fss_extended_read_parameter_columns_e,
    fss_extended_read_parameter_delimit_e,
    fss_extended_read_parameter_depth_e,
    fss_extended_read_parameter_empty_e,
    fss_extended_read_parameter_line_e,
    fss_extended_read_parameter_name_e,
    fss_extended_read_parameter_object_e,
    fss_extended_read_parameter_pipe_e,
    fss_extended_read_parameter_raw_e,
    fss_extended_read_parameter_select_e,
    fss_extended_read_parameter_total_e,
    fss_extended_read_parameter_trim_e,
  };

  #define fss_extended_read_console_parameter_t_initialize \
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
      macro_f_console_parameter_t_initialize(fss_extended_read_short_at_s, fss_extended_read_long_at_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_extended_read_short_content_s, fss_extended_read_long_content_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_extended_read_short_columns_s, fss_extended_read_long_columns_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_extended_read_short_delimit_s, fss_extended_read_long_delimit_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_extended_read_short_depth_s, fss_extended_read_long_depth_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_extended_read_short_empty_s, fss_extended_read_long_empty_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_extended_read_short_line_s, fss_extended_read_long_line_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_extended_read_short_name_s, fss_extended_read_long_name_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_extended_read_short_object_s, fss_extended_read_long_object_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_extended_read_short_pipe_s, fss_extended_read_long_pipe_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_extended_read_short_raw_s, fss_extended_read_long_raw_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_extended_read_short_select_s, fss_extended_read_long_select_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_extended_read_short_total_s, fss_extended_read_long_total_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_extended_read_short_trim_s, fss_extended_read_long_trim_s, 0, 0, f_console_type_normal_e), \
    }

  #define fss_extended_read_total_parameters_d 23
#endif // _di_fss_extended_read_defines_

/**
 * FSS Delimit Parameter data.
 *
 * fss_extended_read_delimit_mode_*:
 *   - all:                    All delimits are to be aplied.
 *   - content:                Content are to have delimits applied.
 *   - content_greater:        Content at this number or higher are to have delimits applied.
 *   - content_greater_object: Objects and Content at this number or higher are to have delimits applied.
 *   - content_lesser:         Content at this number or lower are to have delimits applied.
 *   - content_lesser_object:  Objects and Content at this number or lower are to have delimits applied.
 *   - content_object:         Objects and Content are to have delimits applied
 *   - object:                 Objects arre to have delimits applied.
 */
#ifndef _di_fss_extended_read_delimit_mode_
  #define fss_extended_read_delimit_mode_name_none    "none"
  #define fss_extended_read_delimit_mode_name_all     "all"
  #define fss_extended_read_delimit_mode_name_object  "object"
  #define fss_extended_read_delimit_mode_name_greater "+"
  #define fss_extended_read_delimit_mode_name_lesser  "-"

  #define fss_extended_read_delimit_mode_name_none_length    4
  #define fss_extended_read_delimit_mode_name_all_length     3
  #define fss_extended_read_delimit_mode_name_object_length  6
  #define fss_extended_read_delimit_mode_name_greater_length 1
  #define fss_extended_read_delimit_mode_name_lesser_length  1

  enum {
    fss_extended_read_delimit_mode_none_e = 1,
    fss_extended_read_delimit_mode_all_e,
    fss_extended_read_delimit_mode_content_e,
    fss_extended_read_delimit_mode_content_greater_e,
    fss_extended_read_delimit_mode_content_greater_object_e,
    fss_extended_read_delimit_mode_content_lesser_e,
    fss_extended_read_delimit_mode_content_lesser_object_e,
    fss_extended_read_delimit_mode_content_object_e,
    fss_extended_read_delimit_mode_object_e,
  };
#endif // _di_fss_extended_read_delimit_modes_


#ifndef _di_fss_extended_read_main_t_
  typedef struct {
    f_console_parameters_t parameters;

    f_array_lengths_t remaining;
    bool process_pipe;

    fl_print_t output;
    fl_print_t error;
    fl_print_t warning;

    f_signal_t signal;

    f_color_context_t context;
  } fss_extended_read_main_t;

  #define fss_extended_read_main_t_initialize \
    { \
      f_console_parameters_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
      fl_print_t_initialize, \
      macro_fl_print_t_initialize_error(), \
      macro_fl_print_t_initialize_warning(), \
      f_signal_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_fss_extended_read_main_t_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing fss_extended_read_main().
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_extended_read_main()
 */
#ifndef _di_fss_extended_read_main_delete_
  extern f_status_t fss_extended_read_main_delete(fss_extended_read_main_t * const main);
#endif // _di_fss_extended_read_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_extended_read_common_h
