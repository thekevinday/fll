/**
 * FLL - Level 3
 *
 * Project: FSS Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common enumeration structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_write_common_enumeration_h
#define _fss_write_common_enumeration_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Flags passed to the main function or program.
 *
 * fss_write_main_flag_*_e:
 *   - none:             No flags set.
 *   - content:          The Content being written is specified.
 *   - content_end:      The Content end characters are to be printed.
 *   - content_multiple: Designate that multiple Content is allowed for an Object for this standard rather than a single Content per Object.
 *   - content_next:     The Content next characters are to be printed.
 *   - copyright:        Print copyright.
 *   - file_to:          Using a specified destination file.
 *   - help:             Print help.
 *   - ignore:           Ignore a given range within a Content (specify flag before setting loading to designate ignores is supported by standard).
 *   - object:           The Object being written is specified.
 *   - object_open:      The Object open characters are to be printed.
 *   - partial:          Do not write end of Object/Content character.
 *   - pipe:             Use the input pipe.
 *   - print_first:      When set, print new line to message output on program begin after loading settings.
 *   - print_last:       When set, print new line to message output on program end.
 *   - trim:             Trim Object names.
 *   - version:          Print version.
 */
#ifndef _di_fss_write_main_flag_e_
  enum {
    fss_write_main_flag_none_e             = 0x0,
    fss_write_main_flag_content_e          = 0x1,
    fss_write_main_flag_content_end_e      = 0x2,
    fss_write_main_flag_content_multiple_e = 0x4,
    fss_write_main_flag_content_next_e     = 0x8,
    fss_write_main_flag_copyright_e        = 0x10,
    fss_write_main_flag_file_to_e          = 0x20,
    fss_write_main_flag_help_e             = 0x40,
    fss_write_main_flag_ignore_e           = 0x80,
    fss_write_main_flag_object_e           = 0x100,
    fss_write_main_flag_object_open_e      = 0x200,
    fss_write_main_flag_partial_e          = 0x400,
    fss_write_main_flag_pipe_e             = 0x800,
    fss_write_main_flag_prepend_e          = 0x1000,
    fss_write_main_flag_print_first_e      = 0x2000,
    fss_write_main_flag_print_last_e       = 0x4000,
    fss_write_main_flag_trim_e             = 0x8000,
    fss_write_main_flag_version_e          = 0x10000,
  }; // enum
#endif // _di_fss_write_main_flag_e_

/**
 * The main program parameters.
 */
#ifndef _di_fss_write_parameter_e_
  enum {
    fss_write_parameter_as_e = f_console_standard_parameter_last_e,
    fss_write_parameter_backtick_e,
    fss_write_parameter_content_e,
    fss_write_parameter_content_end_e,
    fss_write_parameter_content_next_e,
    fss_write_parameter_double_e,
    fss_write_parameter_file_e,
    fss_write_parameter_ignore_e,
    fss_write_parameter_object_e,
    fss_write_parameter_object_open_e,
    fss_write_parameter_partial_e,
    fss_write_parameter_prepend_e,
    fss_write_parameter_single_e,
    fss_write_parameter_trim_e,
  }; // enum

  #define fss_write_console_parameter_t_initialize \
    { \
      macro_fll_program_console_parameter_standard_initialize, \
      \
      macro_f_console_parameter_t_initialize_3(fss_write_short_as_s,           fss_write_long_as_s,           1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_backtick_s,     fss_write_long_backtick_s,     0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_content_s,      fss_write_long_content_s,      1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_content_end_s,  fss_write_long_content_end_s,  0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_content_next_s, fss_write_long_content_next_s, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_double_s,       fss_write_long_double_s,       0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_file_s,         fss_write_long_file_s,         1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_ignore_s,       fss_write_long_ignore_s,       2, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_object_s,       fss_write_long_object_s,       1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_object_open_s,  fss_write_long_object_open_s,  0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_partial_s,      fss_write_long_partial_s,      0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_prepend_s,      fss_write_long_prepend_s,      1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_single_s,       fss_write_long_single_s,       0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fss_write_short_trim_s,         fss_write_long_trim_s,         0, f_console_flag_normal_e), \
    }

  #define fss_write_parameter_total_d 27
#endif // _di_fss_write_parameter_e_

/**
 * Flags for fine-tuned print control.
 *
 * fss_write_print_flag_*_e:
 *   - none:    No flags set.
 *   - debug:   Stream is for debug printing.
 *   - error:   Stream is for error printing.
 *   - in:      Stream is a source file.
 *   - message: Stream is for message printing.
 *   - out:     Stream is a destination file.
 *   - warning: Stream is for warning printing.
 */
#ifndef _di_fss_write_print_flag_e_
  enum {
    fss_write_print_flag_none_e    = 0x0,
    fss_write_print_flag_debug_e   = 0x1,
    fss_write_print_flag_error_e   = 0x2,
    fss_write_print_flag_file_e    = 0x4,
    fss_write_print_flag_in_e      = 0x8,
    fss_write_print_flag_out_e     = 0x10,
    fss_write_print_flag_message_e = 0x20,
    fss_write_print_flag_warning_e = 0x40,
  }; // enum
#endif // _di_fss_write_print_flag_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_common_enumeration_h
