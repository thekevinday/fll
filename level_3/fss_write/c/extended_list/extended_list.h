/**
 * FLL - Level 3
 *
 * Project: FSS Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This program provides FSS write functionality for the FSS-0003 Extended List.
 */
#ifndef _fss_write_extended_list_h
#define _fss_write_extended_list_h

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
#include <fll/level_1/fss/extended.h>
#include <fll/level_1/print.h>
#include <fll/level_1/string.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/fss/extended.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// FSS Write includes.
#include <program/fss_write/extended/common.h>
#include <program/fss_write/main/common.h>
#include <program/fss_write/extended/print.h>
#include <program/fss_write/main/print.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Process help for FSS-0003 (Extended List).
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
#ifndef _di_fss_write_extended_list_process_help_
  extern void fss_write_extended_list_process_help(fll_program_data_t * const main, fss_write_setting_t * const setting);
#endif // _di_fss_write_extended_list_process_help_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_extended_list_h
