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
 * Flags for fine-tuned print control.
 *
 * iki_read_print_flag_*_e:
 *   - none:      No flags set.
 *   - debug:     Stream is for debug printing.
 *   - error:     Stream is for error printing.
 *   - message:   Stream is for message printing.
 *   - warning:   Stream is for warning printing.
 *   - file_to:   Stream is a destination file.
 *   - file_from: Stream is a source file.
 */
#ifndef _di_iki_read_print_flag_e_
  enum {
    iki_read_print_flag_none_e      = 0x0,
    iki_read_print_flag_debug_e     = 0x1,
    iki_read_print_flag_error_e     = 0x2,
    iki_read_print_flag_message_e   = 0x4,
    iki_read_print_flag_warning_e   = 0x8,
    iki_read_print_flag_file_to_e   = 0x10,
    iki_read_print_flag_file_from_e = 0x20,
  }; // enum
#endif // _di_iki_read_print_flag_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _iki_read_common_enumeration_h
