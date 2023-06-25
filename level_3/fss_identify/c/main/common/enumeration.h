/**
 * FLL - Level 3
 *
 * Project: FSS Identify
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common enumeration types.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_identify_common_enumeration_h
#define _fss_identify_common_enumeration_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Flags passed to the main function or program.
 *
 * fss_identify_main_flag_*_e:
 *   - none:          No flags set.
 *   - content:       Use the content (The "0000" part of "FSS-0000").
 *   - copyright:     Print copyright.
 *   - file_from:     Using a specified source file.
 *   - file_to:       Using a specified destination file. (Not used at this time.)
 *   - help:          Print help.
 *   - header:        Enable printing of headers.
 *   - line:          Print only the identifier at a given line.
 *   - name:          Select using this full or partial type name or code.
 *   - object:        Use the object (The "FSS" part of "FSS-0000").
 *   - pipe:          Use the input pipe.
 *   - print_first:   When set, print new line to message output on program begin after loading settings.
 *   - print_last:    When set, print new line to message output on program end.
 *   - total:         Print the total Identifiers found.
 *   - version:       Print version.
 */
#ifndef _di_fss_identify_main_flag_e_
  enum {
    fss_identify_main_flag_none_e          = 0x0,
    fss_identify_main_flag_content_e       = 0x1,
    fss_identify_main_flag_copyright_e     = 0x2,
    fss_identify_main_flag_file_from_e     = 0x4,
    fss_identify_main_flag_file_to_e       = 0x8,
    fss_identify_main_flag_header_e        = 0x10,
    fss_identify_main_flag_help_e          = 0x20,
    fss_identify_main_flag_line_e          = 0x40,
    fss_identify_main_flag_name_e          = 0x80,
    fss_identify_main_flag_object_e        = 0x100,
    fss_identify_main_flag_pipe_e          = 0x200,
    fss_identify_main_flag_print_first_e   = 0x400,
    fss_identify_main_flag_print_last_e    = 0x800,
    fss_identify_main_flag_total_e         = 0x1000,
    fss_identify_main_flag_version_e       = 0x2000,
  }; // enum
#endif // _di_fss_identify_main_flag_e_

/**
 * The main program parameters.
 */
#ifndef _di_fss_identify_parameter_e_
  enum {
    fss_identify_parameter_help_e,
    fss_identify_parameter_copyright_e,
    fss_identify_parameter_light_e,
    fss_identify_parameter_dark_e,
    fss_identify_parameter_no_color_e,
    fss_identify_parameter_verbosity_quiet_e,
    fss_identify_parameter_verbosity_error_e,
    fss_identify_parameter_verbosity_normal_e,
    fss_identify_parameter_verbosity_verbose_e,
    fss_identify_parameter_verbosity_debug_e,
    fss_identify_parameter_version_e,
    fss_identify_parameter_line_first_no_e,
    fss_identify_parameter_line_last_no_e,

    fss_identify_parameter_content_e,
    fss_identify_parameter_line_e,
    fss_identify_parameter_name_e,
    fss_identify_parameter_object_e,
    fss_identify_parameter_total_e,
  }; // enum

  #define fss_identify_console_parameter_t_initialize \
    { \
      macro_fll_program_console_parameter_standard_initialize, \
      \
      macro_f_console_parameter_t_initialize_3(fss_identify_short_content_s, fss_identify_long_content_s, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_identify_short_line_s, fss_identify_long_line_s, 1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_identify_short_name_s, fss_identify_long_name_s, 1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_identify_short_object_s, fss_identify_long_object_s, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_identify_short_total_s, fss_identify_long_total_s, 0, f_console_flag_normal_e), \
    }

  #define fss_identify_parameter_total_d 18
#endif // _di_fss_identify_parameter_e_

/**
 * Flags for fine-tuned print control.
 *
 * fss_identify_print_flag_*_e:
 *   - none:    No flags set.
 *   - debug:   Stream is for debug printing.
 *   - error:   Stream is for error printing.
 *   - in:      Stream is a source file.
 *   - message: Stream is for message printing.
 *   - out:     Stream is a destination file.
 *   - warning: Stream is for warning printing.
 */
#ifndef _di_fss_identify_print_flag_e_
  enum {
    fss_identify_print_flag_none_e    = 0x0,
    fss_identify_print_flag_debug_e   = 0x1,
    fss_identify_print_flag_error_e   = 0x2,
    fss_identify_print_flag_file_e    = 0x4,
    fss_identify_print_flag_in_e      = 0x8,
    fss_identify_print_flag_out_e     = 0x10,
    fss_identify_print_flag_message_e = 0x20,
    fss_identify_print_flag_warning_e = 0x40,
  }; // enum
#endif // _di_fss_identify_print_flag_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_identify_common_enumeration_h
