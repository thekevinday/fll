/**
 * FLL - Level 3
 *
 * Project: UTF8
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _byte_dump_print_h
#define _byte_dump_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print help.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param output
 *   The file to print to.
 * @param context
 *   The color context settings.
 *
 * @return
 *   F_none on success.
 *
 * @see byte_dump_main()
 */
#ifndef _di_byte_dump_print_help_
  extern f_status_t byte_dump_print_help(byte_dump_setting_t * const setting, const fl_print_t print);
#endif // _di_byte_dump_print_help_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _byte_dump_print_h
