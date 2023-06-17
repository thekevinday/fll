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

// FSS Read includes.
#include <program/fss_read/main/common/define.h>
#include <program/fss_read/main/common/enumeration.h>
#include <program/fss_read/main/common/print.h>
#include <program/fss_read/main/common/static.h>
#include <program/fss_read/main/common/string.h>
#include <program/fss_read/main/common/type.h>
#include <program/fss_read/main/common.h>
#include <program/fss_read/main/print/data.h>
#include <program/fss_read/main/print/error.h>
#include <program/fss_read/main/print/message.h>
#include <program/fss_read/main/process_normal.h>
#include <program/fss_read/main/signal.h>
#include <program/fss_read/main/thread.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Determine if the given depth is to be delimited or not for Content.
 *
 * @param main
 *   The program and settings data.
 *
 *   Must not be NULL.
 *
 *   This does not alter main.setting.state.status.
 * @param depth
 *   The depth to check.
 *
 * @return
 *   F_true if to apply delimits.
 *   F_false if to not apply delimits (fallback when main is NULL).
 */
#ifndef _di_fss_read_delimit_content_is_
  extern f_status_t fss_read_delimit_content_is(fss_read_main_t * const main, const f_number_unsigned_t depth);
#endif // _di_fss_read_delimit_content_is_

/**
 * Determine if the given depth is to be delimited or not for an Object.
 *
 * @param main
 *   The program and settings data.
 *
 *   Must not be NULL.
 *
 *   This does not alter main.setting.state.status.
 * @param depth
 *   The depth to check.
 *
 * @return
 *   F_true if to apply delimits.
 *   F_false if to not apply delimits (fallback when main is NULL).
 */
#ifndef _di_fss_read_delimit_object_is_
  extern f_status_t fss_read_delimit_object_is(fss_read_main_t * const main, const f_number_unsigned_t depth);
#endif // _di_fss_read_delimit_object_is_

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
 *
 *   Must not be NULL.
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
 * Get the name of the file the given position represents within the buffer.
 *
 * @param at
 *   The position within the buffer.
 * @param files
 *   The representation of files and their respective ranges within the buffer.
 *
 * @return
 *   A string with the name when found.
 *   NULL is returned if the range represents the STDIN pipe.
 *
 *   On failure to identify, an empty string is returned.
 */
#ifndef _di_fss_read_file_identify_
  extern f_string_static_t fss_read_file_identify(const f_number_unsigned_t at, const fss_read_files_t files);
#endif // _di_fss_read_file_identify_

/**
 * Process the current buffer, guarantee that a newline exists at the end of the buffer.
 *
 * Most standards are new line sensitive.
 * When appending files to the buffer, if the file lacks a final new line then this could break the format for files appended thereafter.
 *
 * @param main
 *   The program and settings data.
 *
 *   Must not be NULL.
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
