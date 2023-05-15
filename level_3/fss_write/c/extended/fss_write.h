/**
 * FLL - Level 3
 *
 * Project: FSS Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This program provides FSS write functionality for the FSS-0001 Extended.
 */
#ifndef _fss_write_extended_h
#define _fss_write_extended_h

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
#include <fll/level_1/fss/extended.h>
#include <fll/level_1/print.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// FSS Write includes.
#include <program/fss_write/main/common/define.h>
#include <program/fss_write/main/common/enumeration.h>
#include <program/fss_write/main/common/print.h>
#include <program/fss_write/main/common/string.h>
#include <program/fss_write/main/common/type.h>
#include <program/fss_write/main/common.h>
#include <program/fss_write/main/print/error.h>
#include <program/fss_write/main/print/message.h>
#include <program/fss_write/extended/common.h>
#include <program/fss_write/extended/print.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Process a single Content, printing the FSS-0001 (Extended) if valid or an error if invalid.
 *
 * @param main
 *   The program and settings data.
 *
 *   Must not be NULL.
 *   Must be of type fss_write_main_t.
 *
 *   This alters main.setting.state.status.
 *   This uses and alters main.setting.buffer.
 * @param last
 *   If TRUE, then this is the last Content in the Content set.
 *   If FALSE, then this is not the last Content in the Content set.
 */
#ifndef _di_fss_write_extended_process_content_
  extern void fss_write_extended_process_content(void * const main, const bool last);
#endif // _di_fss_write_extended_process_content_

/**
 * Process help for FSS-0001 (Extended).
 *
 * @param main
 *   The program and settings data.
 *
 *   Must not be NULL.
 *   Must be of type fss_write_main_t.
 *
 *   This does not alter main.setting.state.status.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fss_write_extended_process_help_
  extern void fss_write_extended_process_help(void * const main);
#endif // _di_fss_write_extended_process_help_

/**
 * Process a single Object, printing the FSS-0001 (Extended) if valid or an error if invalid.
 *
 * @param main
 *   The program and settings data.
 *
 *   Must not be NULL.
 *   Must be of type fss_write_main_t.
 *
 *   This alters main.setting.state.status.
 *   This uses and alters main.setting.buffer.
 */
#ifndef _di_fss_write_extended_process_object_
  extern void fss_write_extended_process_object(void * const main);
#endif // _di_fss_write_extended_process_object_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_extended_h
