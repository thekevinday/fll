/**
 * FLL - Level 3
 *
 * Project: FSS Read
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This program provides FSS write functionality for the FSS-000E Payload.
 */
#ifndef _fss_read_payload_h
#define _fss_read_payload_h

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

// FLL-1 includes.
#include <fll/level_1/conversion.h>
#include <fll/level_1/fss/basic_list.h>
#include <fll/level_1/print.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/fss/extended.h>
#include <fll/level_2/fss/payload.h>
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
#include <program/fss_read/payload/common.h>
#include <program/fss_read/payload/print.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Process help for FSS-000E (Payload).
 *
 * @param main
 *   The program and settings data.
 *
 *   Must not be NULL.
 *   Must be of type fss_read_main_t.
 *
 *   This does not alter main.setting.state.status.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fss_read_payload_process_help_
  extern void fss_read_payload_process_help(void * const main);
#endif // _di_fss_read_payload_process_help_

/**
 * Process the buffer, loading the FSS data.
 *
 * This will print an error message on error.
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
 *     F_data_not_stop (with warning bit) on no valid FSS data found and reached stopping point.
 *     F_data_not_eos (with warning bit) on no valid FSS data found and reached end of string.
 *
 *     Errors (with error bit) from: fll_fss_payload_read()
 *
 *     Errors (with error bit) from: fss_read_ensure_quotes_length()
 *
 * @see fss_read_ensure_quotes_length()
 * @see fll_fss_payload_read()
 *
 * @see fss_read_file_identify()
 */
#ifndef _di_fss_read_payload_process_load_
  extern void fss_read_payload_process_load(void * const main);
#endif // _di_fss_read_payload_process_load_

/**
 * Process a given object and content, printing the FSS if valid or an error if invalid.
 *
 * @param main
 *   The program and settings data.
 *
 *   Must not be NULL.
 *   Must be of type fss_read_main_t.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 */
#ifndef _di_fss_read_payload_process_set_
  extern void fss_read_payload_process_set(void * const main);
#endif // _di_fss_read_payload_process_set_

/**
 * Perform the payload-specific program setting load process.
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
 *   This alters setting.state.status:
 *     F_none on success.
 *
 *     F_parameter (with error bit) on parameter error.
 *
 *   This alters setting.state.status:
 *     F_none on success.
 *     F_data_not on success but nothing was provided to operate with.
 *
 * @see fss_read_setting_load()
 * @see fss_read_signal_check()
 */
#ifndef _di_fss_read_payload_setting_load_
  extern void fss_read_payload_setting_load(const f_console_arguments_t arguments, fss_read_main_t * const main);
#endif // _di_fss_read_payload_setting_load_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_read_payload_h
