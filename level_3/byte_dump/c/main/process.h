/**
 * FLL - Level 3
 *
 * Project: Byte Dump
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the process functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _byte_dump_process_h
#define _byte_dump_process_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Dump the contents of the file to standard out.
 *
 * @param main
 *   The main program and settings data.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *
 *     F_failure (with error bit) on failure, usually when read() fails.
 *     F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 * @param name
 *   The name of the file.
 * @param file
 *   Data for the file to print.
 *   Set to NULL if file is the STDIN pipe.
 */
#ifndef _di_byte_dump_process_file_
  extern void byte_dump_process_file(byte_dump_main_t * const main, const f_string_static_t name, const f_file_t file);
#endif // _di_byte_dump_process_file_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _byte_dump_process_h
