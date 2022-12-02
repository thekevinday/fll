/**
 * FLL - Level 3
 *
 * Project: FSS Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This program provides FSS write functionality for the FSS-0002 Basic List.
 */
#ifndef _fss_write_basic_list_h
#define _fss_write_basic_list_h

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
#include <fll/level_1/fss/basic_list.h>
#include <fll/level_1/print.h>
#include <fll/level_1/string.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/fss/basic_list.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// FSS Write includes.
#include <program/fss_write/main/common.h>
#include <program/fss_write/basic_list/common.h>
#include <program/fss_write/main/print.h>
#include <program/fss_write/basic_list/print.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Process help for FSS-0002 (Basic List).
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   Must be of type (fss_write_setting_t *).
 *
 *   This does not alter setting.status.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fss_write_basic_list_process_help_
  extern void fss_write_basic_list_process_help(fll_program_data_t * const main, void * const setting);
#endif // _di_fss_write_basic_list_process_help_

/**
 * Process normally, writing to the output.
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
#ifndef _di_fss_write_basic_list_process_normal_
  extern void fss_write_basic_list_process_normal(fll_program_data_t * const main, void * const setting);
#endif // _di_fss_write_basic_list_process_normal_

/**
 * Process the pipe, reading from the pipe and writing to the output.
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
 *     F_basic_list on success and the basic_list has been printed.
 *     F_interrupt on (exit) signal received.
 *
 *     F_parameter (with error bit) if main is NULL or setting is NULL.
 */
#ifndef _di_fss_write_basic_list_process_pipe_
  extern void fss_write_basic_list_process_pipe(fll_program_data_t * const main, void * const setting);
#endif // _di_fss_write_basic_list_process_pipe_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_basic_list_h
