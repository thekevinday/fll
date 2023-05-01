/**
 * FLL - Level 3
 *
 * Project: FSS Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common enumeration structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_read_common_enumeration_h
#define _fss_read_common_enumeration_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Flags passed to the main function or program.
 *
 * fss_read_main_flag_*_e:
 *   - none:        No flags set.
 *   - at:          The object at the given position is being selected (Think of this as select a row for some Object).
 *   - columns:     The total columns found and selected is printed instead of the Content.
 *   - content:     The Content is to be printed.
 *   - copyright:   Print copyright.
 *   - empty:       Empty Content will be printed (Objects that have no Content will have their empty Content printed).
 *   - help:        Print help.
 *   - line:        A specific Content at a given line is to be selected (Think of this as select a row for some Content).
 *   - name:        A specific Object name has been requested.
 *   - object:      The Object is to be printed.
 *   - original:    Enable original printing, where the quotes are printed and no delimits are applied.
 *   - print_first: When set, print new line to message output on program begin after loading settings.
 *   - print_last:  When set, print new line to message output on program end.
 *   - select:      A specific Content at a given position is to be selected (Think of this as select a column for some Content).
 *   - total:       The total lines found and selected is printed instead of the Content.
 *   - trim:        Empty space before and after Objects and Content will not be printed (They will be trimmed).
 *   - version:     Print version.
 */
#ifndef _di_fss_read_main_flag_e_
  enum {
    fss_read_main_flag_none_e        = 0x0,
    fss_read_main_flag_at_d          = 0x1,
    fss_read_main_flag_columns_d     = 0x2,
    fss_read_main_flag_content_d     = 0x4,
    fss_read_main_flag_copyright_e   = 0x8,
    fss_read_main_flag_empty_d       = 0x10,
    fss_read_main_flag_help_e        = 0x20,
    fss_read_main_flag_line_d        = 0x40,
    fss_read_main_flag_name_d        = 0x80,
    fss_read_main_flag_object_d      = 0x100,
    fss_read_main_flag_original_d    = 0x200,
    fss_read_main_flag_print_first_e = 0x400,
    fss_read_main_flag_print_last_e  = 0x800,
    fss_read_main_flag_select_d      = 0x1000,
    fss_read_main_flag_total_d       = 0x2000,
    fss_read_main_flag_trim_e        = 0x4000,
    fss_read_main_flag_version_e     = 0x8000,
  }; // enum
#endif // _di_fss_read_main_flag_e_

/**
 * The main program parameters.
 */
#ifndef _di_fss_read_parameter_e_
  enum {
    fss_read_parameter_help_e,
    fss_read_parameter_copyright_e,
    fss_read_parameter_light_e,
    fss_read_parameter_dark_e,
    fss_read_parameter_no_color_e,
    fss_read_parameter_verbosity_quiet_e,
    fss_read_parameter_verbosity_error_e,
    fss_read_parameter_verbosity_normal_e,
    fss_read_parameter_verbosity_verbose_e,
    fss_read_parameter_verbosity_debug_e,
    fss_read_parameter_version_e,
    fss_read_parameter_line_first_no_e,
    fss_read_parameter_line_last_no_e,

    fss_read_parameter_at_e,
    fss_read_parameter_content_e,
    fss_read_parameter_columns_e,
    fss_read_parameter_delimit_e,
    fss_read_parameter_depth_e,
    fss_read_parameter_empty_e,
    fss_read_parameter_line_e,
    fss_read_parameter_name_e,
    fss_read_parameter_object_e,
    fss_read_parameter_pipe_e,
    fss_read_parameter_original_e,
    fss_read_parameter_select_e,
    fss_read_parameter_total_e,
    fss_read_parameter_trim_e,
  }; // enum

  #define fss_read_console_parameter_t_initialize \
    { \
      macro_fll_program_console_parameter_standard_initialize, \
      \
      macro_f_console_parameter_t_initialize_3(fss_read_short_at_s, fss_read_long_at_s, 0, 1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_read_short_content_s, fss_read_long_content_s, 0, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_read_short_columns_s, fss_read_long_columns_s, 0, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_read_short_delimit_s, fss_read_long_delimit_s, 0, 1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_read_short_depth_s, fss_read_long_depth_s, 0, 1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_read_short_empty_s, fss_read_long_empty_s, 0, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_read_short_line_s, fss_read_long_line_s, 0, 1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_read_short_name_s, fss_read_long_name_s, 0, 1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_read_short_object_s, fss_read_long_object_s, 0, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_read_short_pipe_s, fss_read_long_pipe_s, 0, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_read_short_original_s, fss_read_long_original_s, 0, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_read_short_select_s, fss_read_long_select_s, 0, 1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_read_short_total_s, fss_read_long_total_s, 0, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_read_short_trim_s, fss_read_long_trim_s, 0, 0, f_console_flag_normal_e), \
    }

  #define fss_read_total_parameters_d 27
#endif // _di_fss_read_parameter_e_

/**
 * Flags for fine-tuned print control.
 *
 * fss_read_print_flag_*_e:
 *   - none:    No flags set.
 *   - debug:   Stream is for debug printing.
 *   - error:   Stream is for error printing.
 *   - in:      Stream is a source file.
 *   - message: Stream is for message printing.
 *   - out:     Stream is a destination file.
 *   - warning: Stream is for warning printing.
 */
#ifndef _di_fss_read_print_flag_e_
  enum {
    fss_read_print_flag_none_e    = 0x0,
    fss_read_print_flag_debug_e   = 0x1,
    fss_read_print_flag_error_e   = 0x2,
    fss_read_print_flag_file_e    = 0x4,
    fss_read_print_flag_in_e      = 0x8,
    fss_read_print_flag_out_e     = 0x10,
    fss_read_print_flag_message_e = 0x20,
    fss_read_print_flag_warning_e = 0x40,
  }; // enum
#endif // _di_fss_read_print_flag_e_

/**
 * FSS Delimit Parameter enumerations.
 *
 * fss_read_delimit_mode_*_e:
 *   - auto:                   Delimit mode is automatically set.
 *   - none:                   Delimit mode is set to none.
 *   - all:                    All delimits are to be applied.
 *   - content:                Content are to have delimits applied.
 *   - content_greater:        Content at this number or higher are to have delimits applied.
 *   - content_greater_object: Objects and Content at this number or higher are to have delimits applied.
 *   - content_lesser:         Content at this number or lower are to have delimits applied.
 *   - content_lesser_object:  Objects and Content at this number or lower are to have delimits applied.
 *   - content_object:         Objects and Content are to have delimits applied
 *   - object:                 Objects arre to have delimits applied.
 */
#ifndef _di_fss_read_delimit_mode_e_
  enum {
    fss_read_delimit_mode_auto_e = 0,
    fss_read_delimit_mode_none_e,
    fss_read_delimit_mode_all_e,
    fss_read_delimit_mode_content_e,
    fss_read_delimit_mode_content_greater_e,
    fss_read_delimit_mode_content_greater_object_e,
    fss_read_delimit_mode_content_lesser_e,
    fss_read_delimit_mode_content_lesser_object_e,
    fss_read_delimit_mode_content_object_e,
    fss_read_delimit_mode_object_e,
  }; // enum
#endif // _di_fss_read_delimit_mode_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_read_common_enumeration_h
