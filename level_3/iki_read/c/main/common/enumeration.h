/**
 * FLL - Level 3
 *
 * Project: IKI Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common enumeration types.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _iki_read_common_enumeration_h
#define _iki_read_common_enumeration_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Flags passed to the main function or program.
 *
 * iki_read_main_flag_*_e:
 *   - none:                   No flags set.
 *   - at:                     Selecting at a specific index.
 *   - content:                Print Contents.
 *   - copyright:              Print copyright.
 *   - help:                   Print help.
 *   - literal:                Print as literal data (printing entire variable).
 *   - line:                   Selecting at a specific line.
 *   - name:                   Selecting using a specific Vocabulary name.
 *   - object:                 Print Objects.
 *   - pipe:                   Use the input pipe.
 *   - print_first:            When set, print new line to message output on program begin after loading settings.
 *   - print_last:             When set, print new line to message output on program end.
 *   - replace:                Using re-assignments.
 *   - replace:                Using replacements.
 *   - substitute:             Using substitutions.
 *   - total:                  Enable printing of "total" count.
 *   - version:                Print version.
 *   - version_copyright_help: A helper flag representing version, copyright, and help flag bits being set.
 *   - whole:                  Print all data.
 *   - wrap:                   Using wrapping.
 */
#ifndef _di_iki_read_main_flag_e_
  enum {
    iki_read_main_flag_none_e                   = 0x0,
    iki_read_main_flag_at_e                     = 0x1,
    iki_read_main_flag_content_e                = 0x2,
    iki_read_main_flag_copyright_e              = 0x4,
    iki_read_main_flag_help_e                   = 0x8,
    iki_read_main_flag_literal_e                = 0x10,
    iki_read_main_flag_line_e                   = 0x20,
    iki_read_main_flag_name_e                   = 0x40,
    iki_read_main_flag_object_e                 = 0x80,
    iki_read_main_flag_pipe_e                   = 0x100,
    iki_read_main_flag_print_first_e            = 0x200,
    iki_read_main_flag_print_last_e             = 0x400,
    iki_read_main_flag_reassign_e               = 0x800,
    iki_read_main_flag_replace_e                = 0x1000,
    iki_read_main_flag_substitute_e             = 0x2000,
    iki_read_main_flag_total_e                  = 0x4000,
    iki_read_main_flag_version_e                = 0x8000,
    iki_read_main_flag_version_copyright_help_e = 0x800c,
    iki_read_main_flag_whole_e                  = 0x10000,
    iki_read_main_flag_wrap_e                   = 0x20000,
  }; // enum
#endif // _di_iki_read_main_flag_e_

/**
 * The main program parameters.
 */
#ifndef _di_iki_read_parameter_e_
  enum {
    iki_read_parameter_at_e = f_console_standard_parameter_last_e,
    iki_read_parameter_content_e,
    iki_read_parameter_line_e,
    iki_read_parameter_literal_e,
    iki_read_parameter_name_e,
    iki_read_parameter_object_e,
    iki_read_parameter_reassign_e,
    iki_read_parameter_replace_e,
    iki_read_parameter_substitute_e,
    iki_read_parameter_total_e,
    iki_read_parameter_whole_e,
    iki_read_parameter_wrap_e,
  }; // enum

  #define iki_read_console_parameter_t_initialize \
    { \
      macro_fll_program_console_parameter_standard_initialize, \
      \
      macro_f_console_parameter_t_initialize_3(iki_read_short_at_s,         iki_read_long_at_s,         1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_read_short_content_s,    iki_read_long_content_s,    0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_read_short_line_s,       iki_read_long_line_s,       1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_read_short_literal_s,    iki_read_long_literal_s,    0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_read_short_name_s,       iki_read_long_name_s,       1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_read_short_object_s,     iki_read_long_object_s,     0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_read_short_reassign_s,   iki_read_long_reassign_s,   3, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_read_short_replace_s,    iki_read_long_replace_s,    2, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_read_short_substitute_s, iki_read_long_substitute_s, 3, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_read_short_total_s,      iki_read_long_total_s,      0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_read_short_whole_s,      iki_read_long_whole_s,      0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(iki_read_short_wrap_s,       iki_read_long_wrap_s,       3, f_console_flag_normal_e), \
    }

  #define iki_read_parameter_total_d (f_console_parameter_state_type_total_d + 12)
#endif // _di_iki_read_parameter_e_

/**
 * Flags for fine-tuned print control.
 *
 * iki_read_print_flag_*_e:
 *   - none:    No flags set.
 *   - debug:   Stream is for debug printing.
 *   - error:   Stream is for error printing.
 *   - in:      Stream is a source file.
 *   - message: Stream is for message printing.
 *   - out:     Stream is a destination file.
 *   - warning: Stream is for warning printing.
 */
#ifndef _di_iki_read_print_flag_e_
  enum {
    iki_read_print_flag_none_e    = 0x0,
    iki_read_print_flag_debug_e   = 0x1,
    iki_read_print_flag_error_e   = 0x2,
    iki_read_print_flag_file_e    = 0x4,
    iki_read_print_flag_in_e      = 0x8,
    iki_read_print_flag_out_e     = 0x10,
    iki_read_print_flag_message_e = 0x20,
    iki_read_print_flag_warning_e = 0x40,
  }; // enum
#endif // _di_iki_read_print_flag_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_read_common_enumeration_h
