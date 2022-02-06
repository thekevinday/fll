/**
 * FLL - Level 3
 *
 * Project: FSS Embedded List Read
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_embedded_list_read_common_h
#define _fss_embedded_list_read_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_fss_embedded_list_read_program_version_
  #define FSS_EMBEDDED_LIST_READ_program_version_major_s F_string_ascii_0_s
  #define FSS_EMBEDDED_LIST_READ_program_version_minor_s F_string_ascii_5_s
  #define FSS_EMBEDDED_LIST_READ_program_version_micro_s F_string_ascii_8_s

  #define FSS_EMBEDDED_LIST_READ_program_version_major_s_length F_string_ascii_0_s_length
  #define FSS_EMBEDDED_LIST_READ_program_version_minor_s_length F_string_ascii_5_s_length
  #define FSS_EMBEDDED_LIST_READ_program_version_micro_s_length F_string_ascii_8_s_length

  #if !(defined(FSS_EMBEDDED_LIST_READ_program_version_nano_prefix_s) && defined(FSS_EMBEDDED_LIST_READ_program_version_nano_prefix_s_length))
    #define FSS_EMBEDDED_LIST_READ_program_version_nano_prefix_s
    #define FSS_EMBEDDED_LIST_READ_program_version_nano_prefix_s_length 0
  #endif // !(defined(FSS_EMBEDDED_LIST_READ_program_version_nano_prefix_s) && defined(FSS_EMBEDDED_LIST_READ_program_version_nano_prefix_s_length))

  #if !(defined(FSS_EMBEDDED_LIST_READ_program_version_nano_s) && defined(FSS_EMBEDDED_LIST_READ_program_version_nano_s_length))
    #define FSS_EMBEDDED_LIST_READ_program_version_nano_s
    #define FSS_EMBEDDED_LIST_READ_program_version_nano_s_length 0
  #endif // !(defined(FSS_EMBEDDED_LIST_READ_program_version_nano_s) && defined(FSS_EMBEDDED_LIST_READ_program_version_nano_s_length))

  #define FSS_EMBEDDED_LIST_READ_program_version_s FSS_EMBEDDED_LIST_READ_program_version_major_s F_string_ascii_period_s FSS_EMBEDDED_LIST_READ_program_version_minor_s F_string_ascii_period_s FSS_EMBEDDED_LIST_READ_program_version_micro_s FSS_EMBEDDED_LIST_READ_program_version_nano_prefix_s FSS_EMBEDDED_LIST_READ_program_version_nano_s

  #define FSS_EMBEDDED_LIST_READ_program_version_s_length FSS_EMBEDDED_LIST_READ_program_version_major_s_length + F_string_ascii_period_s_length + FSS_EMBEDDED_LIST_READ_program_version_minor_s_length + F_string_ascii_period_s_length + FSS_EMBEDDED_LIST_READ_program_version_micro_s_length + FSS_EMBEDDED_LIST_READ_program_version_nano_prefix_s_length + FSS_EMBEDDED_LIST_READ_program_version_nano_s_length

  extern const f_string_static_t fss_embedded_list_read_program_version_s;
#endif // _di_fss_embedded_list_read_program_version_

/**
 * The program name.
 */
#ifndef _di_fss_embedded_list_read_program_name_
  #define FSS_EMBEDDED_LIST_READ_program_name_s      "fss_embedded_list_read"
  #define FSS_EMBEDDED_LIST_READ_program_name_long_s "FSS Embedded List Read"

  #define FSS_EMBEDDED_LIST_READ_program_name_s_length      22
  #define FSS_EMBEDDED_LIST_READ_program_name_long_s_length 22

  extern const f_string_static_t fss_embedded_list_read_program_name_s;
  extern const f_string_static_t fss_embedded_list_read_program_name_long_s;
#endif // _di_fss_embedded_list_read_program_name_

/**
 * The program defines.
 */
#ifndef _di_fss_embedded_list_read_defines_
  #define fss_embedded_list_read_signal_check_d 10000

  #define FSS_EMBEDDED_LIST_READ_pipe_content_end_s    "\f"
  #define FSS_EMBEDDED_LIST_READ_pipe_content_ignore_s "\v"
  #define FSS_EMBEDDED_LIST_READ_pipe_content_start_s  "\b"

  #define FSS_EMBEDDED_LIST_READ_pipe_content_end_s_length    1
  #define FSS_EMBEDDED_LIST_READ_pipe_content_ignore_s_length 1
  #define FSS_EMBEDDED_LIST_READ_pipe_content_start_s_length  1

  extern const f_string_static_t fss_embedded_list_read_pipe_content_end_s;
  extern const f_string_static_t fss_embedded_list_read_pipe_content_ignore_s;
  extern const f_string_static_t fss_embedded_list_read_pipe_content_start_s;
#endif // _di_fss_embedded_list_read_defines_

/**
 * The main program parameters.
 */
#ifndef _di_fss_embedded_list_read_parameters_
  #define FSS_EMBEDDED_LIST_READ_short_at_s      "a"
  #define FSS_EMBEDDED_LIST_READ_short_content_s "c"
  #define FSS_EMBEDDED_LIST_READ_short_columns_s "C"
  #define FSS_EMBEDDED_LIST_READ_short_delimit_s "D"
  #define FSS_EMBEDDED_LIST_READ_short_depth_s   "d"
  #define FSS_EMBEDDED_LIST_READ_short_empty_s   "e"
  #define FSS_EMBEDDED_LIST_READ_short_line_s    "l"
  #define FSS_EMBEDDED_LIST_READ_short_name_s    "n"
  #define FSS_EMBEDDED_LIST_READ_short_object_s  "o"
  #define FSS_EMBEDDED_LIST_READ_short_pipe_s    "p"
  #define FSS_EMBEDDED_LIST_READ_short_raw_s     "R"
  #define FSS_EMBEDDED_LIST_READ_short_select_s  "s"
  #define FSS_EMBEDDED_LIST_READ_short_total_s   "t"
  #define FSS_EMBEDDED_LIST_READ_short_trim_s    "T"

  #define FSS_EMBEDDED_LIST_READ_long_at_s      "at"
  #define FSS_EMBEDDED_LIST_READ_long_content_s "content"
  #define FSS_EMBEDDED_LIST_READ_long_columns_s "columns"
  #define FSS_EMBEDDED_LIST_READ_long_delimit_s "delimit"
  #define FSS_EMBEDDED_LIST_READ_long_depth_s   "depth"
  #define FSS_EMBEDDED_LIST_READ_long_empty_s   "empty"
  #define FSS_EMBEDDED_LIST_READ_long_line_s    "line"
  #define FSS_EMBEDDED_LIST_READ_long_name_s    "name"
  #define FSS_EMBEDDED_LIST_READ_long_object_s  "object"
  #define FSS_EMBEDDED_LIST_READ_long_pipe_s    "pipe"
  #define FSS_EMBEDDED_LIST_READ_long_raw_s     "raw"
  #define FSS_EMBEDDED_LIST_READ_long_select_s  "select"
  #define FSS_EMBEDDED_LIST_READ_long_total_s   "total"
  #define FSS_EMBEDDED_LIST_READ_long_trim_s    "trim"

  #define FSS_EMBEDDED_LIST_READ_short_at_s_length      1
  #define FSS_EMBEDDED_LIST_READ_short_content_s_length 1
  #define FSS_EMBEDDED_LIST_READ_short_columns_s_length 1
  #define FSS_EMBEDDED_LIST_READ_short_delimit_s_length 1
  #define FSS_EMBEDDED_LIST_READ_short_depth_s_length   1
  #define FSS_EMBEDDED_LIST_READ_short_empty_s_length   1
  #define FSS_EMBEDDED_LIST_READ_short_line_s_length    1
  #define FSS_EMBEDDED_LIST_READ_short_name_s_length    1
  #define FSS_EMBEDDED_LIST_READ_short_object_s_length  1
  #define FSS_EMBEDDED_LIST_READ_short_pipe_s_length    1
  #define FSS_EMBEDDED_LIST_READ_short_raw_s_length     1
  #define FSS_EMBEDDED_LIST_READ_short_select_s_length  1
  #define FSS_EMBEDDED_LIST_READ_short_total_s_length   1
  #define FSS_EMBEDDED_LIST_READ_short_trim_s_length    1

  #define FSS_EMBEDDED_LIST_READ_long_at_s_length      2
  #define FSS_EMBEDDED_LIST_READ_long_content_s_length 7
  #define FSS_EMBEDDED_LIST_READ_long_columns_s_length 7
  #define FSS_EMBEDDED_LIST_READ_long_delimit_s_length 7
  #define FSS_EMBEDDED_LIST_READ_long_depth_s_length   5
  #define FSS_EMBEDDED_LIST_READ_long_empty_s_length   5
  #define FSS_EMBEDDED_LIST_READ_long_line_s_length    4
  #define FSS_EMBEDDED_LIST_READ_long_name_s_length    4
  #define FSS_EMBEDDED_LIST_READ_long_object_s_length  6
  #define FSS_EMBEDDED_LIST_READ_long_pipe_s_length    4
  #define FSS_EMBEDDED_LIST_READ_long_raw_s_length     3
  #define FSS_EMBEDDED_LIST_READ_long_select_s_length  6
  #define FSS_EMBEDDED_LIST_READ_long_total_s_length   5
  #define FSS_EMBEDDED_LIST_READ_long_trim_s_length    4

  extern const f_string_static_t fss_embedded_list_read_short_at_s;
  extern const f_string_static_t fss_embedded_list_read_short_content_s;
  extern const f_string_static_t fss_embedded_list_read_short_columns_s;
  extern const f_string_static_t fss_embedded_list_read_short_delimit_s;
  extern const f_string_static_t fss_embedded_list_read_short_depth_s;
  extern const f_string_static_t fss_embedded_list_read_short_empty_s;
  extern const f_string_static_t fss_embedded_list_read_short_line_s;
  extern const f_string_static_t fss_embedded_list_read_short_name_s;
  extern const f_string_static_t fss_embedded_list_read_short_object_s;
  extern const f_string_static_t fss_embedded_list_read_short_pipe_s;
  extern const f_string_static_t fss_embedded_list_read_short_raw_s;
  extern const f_string_static_t fss_embedded_list_read_short_select_s;
  extern const f_string_static_t fss_embedded_list_read_short_total_s;
  extern const f_string_static_t fss_embedded_list_read_short_trim_s;

  extern const f_string_static_t fss_embedded_list_read_long_at_s;
  extern const f_string_static_t fss_embedded_list_read_long_content_s;
  extern const f_string_static_t fss_embedded_list_read_long_columns_s;
  extern const f_string_static_t fss_embedded_list_read_long_delimit_s;
  extern const f_string_static_t fss_embedded_list_read_long_depth_s;
  extern const f_string_static_t fss_embedded_list_read_long_empty_s;
  extern const f_string_static_t fss_embedded_list_read_long_line_s;
  extern const f_string_static_t fss_embedded_list_read_long_name_s;
  extern const f_string_static_t fss_embedded_list_read_long_object_s;
  extern const f_string_static_t fss_embedded_list_read_long_pipe_s;
  extern const f_string_static_t fss_embedded_list_read_long_raw_s;
  extern const f_string_static_t fss_embedded_list_read_long_select_s;
  extern const f_string_static_t fss_embedded_list_read_long_total_s;
  extern const f_string_static_t fss_embedded_list_read_long_trim_s;

  enum {
    fss_embedded_list_read_parameter_help_e,
    fss_embedded_list_read_parameter_light_e,
    fss_embedded_list_read_parameter_dark_e,
    fss_embedded_list_read_parameter_no_color_e,
    fss_embedded_list_read_parameter_verbosity_quiet_e,
    fss_embedded_list_read_parameter_verbosity_normal_e,
    fss_embedded_list_read_parameter_verbosity_verbose_e,
    fss_embedded_list_read_parameter_verbosity_debug_e,
    fss_embedded_list_read_parameter_version_e,

    fss_embedded_list_read_parameter_at_e,
    fss_embedded_list_read_parameter_content_e,
    fss_embedded_list_read_parameter_columns_e,
    fss_embedded_list_read_parameter_delimit_e,
    fss_embedded_list_read_parameter_depth_e,
    fss_embedded_list_read_parameter_empty_e,
    fss_embedded_list_read_parameter_line_e,
    fss_embedded_list_read_parameter_name_e,
    fss_embedded_list_read_parameter_object_e,
    fss_embedded_list_read_parameter_pipe_e,
    fss_embedded_list_read_parameter_raw_e,
    fss_embedded_list_read_parameter_select_e,
    fss_embedded_list_read_parameter_total_e,
    fss_embedded_list_read_parameter_trim_e,
  };

  #define fss_embedded_list_read_console_parameter_t_initialize \
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
      macro_f_console_parameter_t_initialize(fss_embedded_list_read_short_at_s.string, fss_embedded_list_read_long_at_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_embedded_list_read_short_content_s.string, fss_embedded_list_read_long_content_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_embedded_list_read_short_columns_s.string, fss_embedded_list_read_long_columns_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_embedded_list_read_short_delimit_s.string, fss_embedded_list_read_long_delimit_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_embedded_list_read_short_depth_s.string, fss_embedded_list_read_long_depth_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_embedded_list_read_short_empty_s.string, fss_embedded_list_read_long_empty_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_embedded_list_read_short_line_s.string, fss_embedded_list_read_long_line_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_embedded_list_read_short_name_s.string, fss_embedded_list_read_long_name_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_embedded_list_read_short_object_s.string, fss_embedded_list_read_long_object_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_embedded_list_read_short_pipe_s.string, fss_embedded_list_read_long_pipe_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_embedded_list_read_short_raw_s.string, fss_embedded_list_read_long_raw_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_embedded_list_read_short_select_s.string, fss_embedded_list_read_long_select_s.string, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_embedded_list_read_short_total_s.string, fss_embedded_list_read_long_total_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fss_embedded_list_read_short_trim_s.string, fss_embedded_list_read_long_trim_s.string, 0, 0, f_console_type_normal_e), \
    }

  #define fss_embedded_list_read_total_parameters_d 23
#endif // _di_fss_embedded_list_read_parameters_

/**
 * Provide delimit management.
 */
#ifndef _di_fss_embedded_list_read_delimit_mode_
  #define fss_embedded_list_read_delimit_mode_name_none_s    "none"
  #define fss_embedded_list_read_delimit_mode_name_all_s     "all"
  #define fss_embedded_list_read_delimit_mode_name_greater_s "+"
  #define fss_embedded_list_read_delimit_mode_name_lesser_s  "-"

  #define fss_embedded_list_read_delimit_mode_name_none_s_length    4
  #define fss_embedded_list_read_delimit_mode_name_all_s_length     3
  #define fss_embedded_list_read_delimit_mode_name_greater_s_length 1
  #define fss_embedded_list_read_delimit_mode_name_lesser_s_length  1

  enum {
    fss_embedded_list_read_delimit_mode_none_e = 1,
    fss_embedded_list_read_delimit_mode_all_e,
    fss_embedded_list_read_delimit_mode_depth_e,
    fss_embedded_list_read_delimit_mode_depth_greater_e,
    fss_embedded_list_read_delimit_mode_depth_lesser_e,
  };
#endif // _di_fss_embedded_list_read_delimit_modes_

/**
 * The main program data.
 *
 * parameters:   The state of pre-defined parameters passed to the program.
 * remaining:    The remaining, non-pre-defined parameters, passed to the program.
 * process_pipe: Designate whether or not to process the input pipe.
 * output:       The output file for general printing.
 * error:        The output file for error printing.
 * warning:      The output file for warning printing.
 * signal:       The process signal management structure.
 * context:      The color context.
 */
#ifndef _di_fss_embedded_list_read_main_t_
  typedef struct {
    f_console_parameters_t parameters;

    f_array_lengths_t remaining;
    bool process_pipe;

    fl_print_t output;
    fl_print_t error;
    fl_print_t warning;

    f_signal_t signal;

    f_string_dynamic_t buffer;
    f_fss_nest_t nest;
    f_string_quantity_t quantity;

    uint8_t delimit_mode;
    f_array_length_t delimit_depth;

    f_color_context_t context;
  } fss_embedded_list_read_main_t;

  #define fss_embedded_list_read_main_t_initialize \
    { \
      f_console_parameters_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
      fl_print_t_initialize, \
      macro_fl_print_t_initialize_error(), \
      macro_fl_print_t_initialize_warning(), \
      f_signal_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_fss_nest_t_initialize, \
      f_string_quantity_t_initialize, \
      fss_embedded_list_read_delimit_mode_all_e, \
      0, \
      f_color_context_t_initialize, \
    }
#endif // _di_fss_embedded_list_read_main_t_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing fss_embedded_list_read_main().
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fss_embedded_list_read_main()
 */
#ifndef _di_fss_embedded_list_read_main_delete_
  extern f_status_t fss_embedded_list_read_main_delete(fss_embedded_list_read_main_t * const main);
#endif // _di_fss_embedded_list_read_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_embedded_list_read_common_h
