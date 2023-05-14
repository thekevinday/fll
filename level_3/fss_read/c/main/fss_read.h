/**
 * FLL - Level 3
 *
 * Project: FSS Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This program provides FSS write functionality for several FSS formats.
 */
#ifndef _fss_read_h
#define _fss_read_h

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
#include <fll/level_0/compare.h>
#include <fll/level_0/console.h>
#include <fll/level_0/conversion.h>
#include <fll/level_0/file.h>
#include <fll/level_0/fss.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/rip.h>
#include <fll/level_0/signal.h>

#ifndef _di_thread_support_
  #include <fll/level_0/thread.h>
#endif // _di_thread_support_

// FLL-1 includes.
#include <fll/level_1/conversion.h>
#include <fll/level_1/print.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// FSS Write includes.
#include <program/fss_read/main/common/define.h>
#include <program/fss_read/main/common/enumeration.h>
#include <program/fss_read/main/common/print.h>
#include <program/fss_read/main/common/string.h>
#include <program/fss_read/main/common/type.h>
#include <program/fss_read/main/common.h>
#include <program/fss_read/basic/common.h>
#include <program/fss_read/main/print/error.h>
#include <program/fss_read/main/print/message.h>
#include <program/fss_read/basic/print.h>
#include <program/fss_read/main/process_normal.h>
#include <program/fss_read/main/signal.h>
#include <program/fss_read/main/thread.h>

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
 *   The program and settings data.
 *   Must be of type fss_read_main_t.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *     F_true on success when performing verification and verify passed.
 *     F_false on success when performing verification and verify failed.
 *     F_interrupt on (exit) signal received.
 *
 *     F_parameter (with error bit) if main is NULL or setting is NULL.
 */
#ifndef _di_fss_read_main_
  extern void fss_read_main(void * const main);
#endif // _di_fss_read_main_

/**
 * Process based on at parameter.
 *
 * @param main
 *   The program and settings data.
 *   Must be of type fss_read_main_t.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *
 *     F_parameter (with error bit) if main is NULL or setting is NULL.
 *
 *     Errors (with error bit) from: f_string_dynamic_append_assure().
 *
 *     Errors (with error bit) from: fss_read_signal_check().
 * @param at
 *   The "at" position to be printed.
 * @param delimits_object
 *   The delimits array representing a delimited Object.
 *   This represents the positions within the current Object at the "at" position.
 * @param delimits_content
 *   The delimits array representing a delimited Content.
 *   This represents the positions within the current Content at the "at" position.
 * @param line
 *   The current line being processed.
 *   This will be incremented as necessary.
 *   Must not be NULL.
 *
 * @return
 *   F_none on success.
 *
 * @see fss_read_process_at_line()
 */
#ifndef _di_fss_read_process_at_
  extern f_status_t fss_read_process_at_line(fss_read_main_t * const main, const f_array_length_t at, const f_array_lengths_t delimits_object, const f_array_lengths_t delimits_content, f_array_length_t * const line);
#endif // _di_fss_read_process_at_

/**
 * Process the current buffer, guarantee that a newline exists at the end of the buffer.
 *
 * Most standards are new line sensitive.
 * When appending files to the buffer, if the file lacks a final new line then this could break the format for files appended thereafter.
 *
 * @param main
 *   The program and settings data.
 *   Must be of type fss_read_main_t.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *
 *     F_parameter (with error bit) if main is NULL or setting is NULL.
 *
 *     Errors (with error bit) from: f_string_dynamic_append_assure().
 *
 *     Errors (with error bit) from: fss_read_signal_check().
 *
 * @see f_string_dynamic_append_assure()
 *
 * @see fss_read_signal_check()
 */
#ifndef _di_fss_read_process_last_line_
  extern void fss_read_process_last_line(void * const void_main);
#endif // _di_fss_read_process_last_line_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_read_h
