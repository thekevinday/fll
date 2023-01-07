/**
 * FLL - Level 3
 *
 * Project: FSS Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This program provides FSS write functionality for several FSS formats.
 */
#ifndef _fss_write_h
#define _fss_write_h

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
#include <fll/level_0/fss.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/signal.h>

// FLL-1 includes.
#include <fll/level_1/conversion.h>
#include <fll/level_1/print.h>
#include <fll/level_1/string.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// FSS Write includes.
#include <program/fss_write/main/common.h>
#include <program/fss_write/main/common-print.h>
#include <program/fss_write/main/print.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Execute main program.
 *
 * If main.signal is non-zero, then this blocks and handles the following signals:
 *   - F_signal_abort
 *   - F_signal_broken_pipe
 *   - F_signal_hangup
 *   - F_signal_interrupt
 *   - F_signal_quit
 *   - F_signal_termination
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.status:
 *     F_none on success.
 *     F_true on success when performing verification and verify passed.
 *     F_false on success when performing verification and verify failed.
 *     F_interrupt on (exit) signal received.
 *
 *     F_parameter (with error bit) if main is NULL or setting is NULL.
 */
#ifndef _di_fss_write_main_
  extern void fss_write_main(fll_program_data_t * const main, fss_write_setting_t * const setting);
#endif // _di_fss_write_main_

/**
 * Process normally, writing to the output for the assigned FSS format.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   Must be of type (fss_write_setting_t *).
 *
 *   This alters setting.status:
 *     status from fss_write_process_normal_data().
 *
 *     Errors (with error bit) from fss_write_process_normal_data().
 *
 * @see fss_write_process_normal_data()
 */
#ifndef _di_fss_write_process_normal_
  extern void fss_write_process_normal(fll_program_data_t * const main, void * const setting);
#endif // _di_fss_write_process_normal_

/**
 * Process the data normally, writing to the output for the assigned FSS format.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   Must be of type (fss_write_setting_t *).
 *
 *   This alters setting.status:
 *     F_none on success.
 *     F_interrupt on (exit) signal received.
 *
 *     F_parameter (with error bit) if main is NULL or setting is NULL.
 */
#ifndef _di_fss_write_process_normal_data_
  void fss_write_process_normal_data(fll_program_data_t * const main, fss_write_setting_t * const setting, const f_array_length_t length);
#endif // _di_fss_write_process_normal_data_

/**
 * Process the pipe, reading from the pipe and writing to the output for the assigned FSS format.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   Must be of type (fss_write_setting_t *).
 *
 *   This alters setting.status:
 *     F_none on success.
 *     F_data_not on success but pipe contained no relevant data.
 *     F_basic on success and the basic has been printed.
 *     F_interrupt on (exit) signal received.
 *
 *     F_parameter (with error bit) if main is NULL or setting is NULL.
 */
#ifndef _di_fss_write_process_pipe_
  extern void fss_write_process_pipe(fll_program_data_t * const main, void * const setting);
#endif // _di_fss_write_process_pipe_

/**
 * Process a given Object and Content, printing the assigned FSS format if valid or an error if invalid.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   Must be of type (fss_write_setting_t *).
 *
 *   This alters setting.status:
 *     F_none on success.
 *     F_interrupt on (exit) signal received.
 *
 *     F_parameter (with error bit) if main is NULL or setting is NULL.
 */
#ifndef _di_fss_write_process_set_
  extern void fss_write_process_set(fll_program_data_t * const main, void * const setting);
#endif // _di_fss_write_process_set_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_h