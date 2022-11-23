/**
 * FLL - Level 3
 *
 * Project: FSS Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This program provides FSS write functionality for the FSS-000E Payload.
 */
#ifndef _fss_write_payload_h
#define _fss_write_payload_h

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
#include <fll/level_1/fss/basic_list.h>
#include <fll/level_1/print.h>
#include <fll/level_1/string.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/fss/payload.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// FSS Write includes.
#include <program/fss_write/payload/common.h>
#include <program/fss_write/main/common.h>
#include <program/fss_write/payload/print.h>
#include <program/fss_write/main/print.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Process help for FSS-000E (Payload).
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.status:
 *     F_none on success.
 *     F_interrupt on (exit) signal received.
 *
 *     F_parameter (with error bit) if main is NULL or setting is NULL.
 *
 * @return
 *   F_none on success.
 *   F_failure (with error bit) for any other failure.
 */
#ifndef _di_fss_write_payload_process_help_
  extern void fss_write_payload_process_help(fll_program_data_t * const main, fss_write_setting_t * const setting);
#endif // _di_fss_write_payload_process_help_

/**
 * Process normally, writing to the output.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.status:
 *     F_none on success.
 *     F_interrupt on (exit) signal received.
 *
 *     F_parameter (with error bit) if main is NULL or setting is NULL.
 */
#ifndef _di_fss_write_payload_process_normal_
  extern void fss_write_payload_process_normal(fll_program_data_t * const main, fss_write_setting_t * const setting);
#endif // _di_fss_write_payload_process_normal_

/**
 * Process the pipe, reading from the pipe and writing to the output.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.status:
 *     F_none on success.
 *     F_data_not on success but pipe contained no relevant data.
 *     F_payload on success and the payload has been printed.
 *     F_interrupt on (exit) signal received.
 *
 *     F_parameter (with error bit) if main is NULL or setting is NULL.
 */
#ifndef _di_fss_write_payload_process_pipe_
  extern void fss_write_payload_process_pipe(fll_program_data_t * const main, fss_write_setting_t * const setting);
#endif // _di_fss_write_payload_process_pipe_

/**
 * Process a given object and content, printing the FSS if valid or an error if invalid.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.status:
 *     F_none on success.
 *     F_interrupt on (exit) signal received.
 *
 *     F_parameter (with error bit) if main is NULL or setting is NULL.
 * @param object
 *   The object to validate and print.
 *   Set pointer address to 0 to not use.
 * @param content
 *   The content to escape and print.
 *   Set pointer address to 0 to not use.
 */
#ifndef _di_fss_write_process_payload_set_
  extern void fss_write_process_payload_set(fll_program_data_t * const main, fss_write_setting_t * const setting, const f_string_static_t *object, const f_string_static_t *content);
#endif // _di_fss_write_process_payload_set_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_payload_h
