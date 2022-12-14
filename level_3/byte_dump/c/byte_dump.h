/**
 * FLL - Level 3
 *
 * Project: Byte Dump
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This is intended to support Unicode 15.0.
 *
 * When using "text" mode, this program attempts to translate UTF-8 sequences such that certain codes don't cause printing problems.
 * There may be cases where there are unknown codes that get printed and the invalid UTF-8 marker may be displayed not by this program but instead by the shell or some other program.
 * This can potentially be seen with the program "less".
 * The solution is to add the invalid character codes to this project so that this project can properly print the invalid UTF-8 marker and therefore properly display the information.
 */
#ifndef _byte_dump_h
#define _byte_dump_h

// Libc includes.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/color.h>
#include <fll/level_0/console.h>
#include <fll/level_0/conversion.h>
#include <fll/level_0/file.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/signal.h>

// FLL-1 includes.
#include <fll/level_1/conversion.h>
#include <fll/level_1/print.h>
#include <fll/level_1/string.h>
#include <fll/level_1/utf.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// Byte Dump includes.
#include <program/byte_dump/common.h>
#include <program/byte_dump/print.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Execute main program.
 *
 * @param main
 *   The main program data.
 * @param arguments
 *   The parameters passed to the process.
 *
 * If main.signal is non-zero, then this blocks and handles the following signals:
 *   - F_signal_abort
 *   - F_signal_broken_pipe
 *   - F_signal_hangup
 *   - F_signal_interrupt
 *   - F_signal_quit
 *   - F_signal_termination
 *
 * @return
 *   F_none on success.
 *
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *   F_parameter (with error bit) on an argument error.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_byte_dump_main_
  extern f_status_t byte_dump_main(fll_program_data_t * const main, byte_dump_setting_t * const setting);
#endif // _di_byte_dump_main_

/**
 * Delete the program main setting data.
 *
 * @param setting
 *   The program main setting data.
 *
 *   This does not alter setting.status.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_byte_dump_setting_delete_
  extern f_status_t byte_dump_setting_delete(byte_dump_setting_t * const setting);
#endif // _di_byte_dump_setting_delete_

/**
 * Perform the standard program setting load process.
 *
 * This prints error messages as appropriate.
 *
 * If either main or setting is NULL, then this immediately returns without doing anything.
 *
 * @param arguments
 *   The parameters passed to the process (often referred to as command line arguments).
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_console_parameter_process().
 *     Errors (with error bit) from: fll_program_parameter_process_context().
 *
 * @see f_console_parameter_process()
 * @see fll_program_parameter_process_context()
 */
#ifndef _di_byte_dump_setting_load_
  extern void byte_dump_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, byte_dump_setting_t * const setting);
#endif // _di_byte_dump_setting_load_

/**
 * Perform the standard program setting unload process.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   All buffers are deallocated.
 *
 *   This does not alter setting.status.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: utf8_setting_delete().
 *
 * @see utf8_setting_delete()
 */
#ifndef _di_byte_dump_setting_unload_
  extern f_status_t byte_dump_setting_unload(fll_program_data_t * const main, byte_dump_setting_t * const setting);
#endif // _di_byte_dump_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _byte_dump_h
