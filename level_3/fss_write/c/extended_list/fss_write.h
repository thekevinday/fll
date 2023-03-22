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
#include <fll/level_0/fss.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/signal.h>

// FLL-1 includes.
#include <fll/level_1/conversion.h>
#include <fll/level_1/fss/extended_list.h>
#include <fll/level_1/print.h>
#include <fll/level_1/string.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// FSS Write includes.
#include <program/fss_write/main/common/define.h>
#include <program/fss_write/main/common/enumeration.h>
#include <program/fss_write/main/common-print.h>
#include <program/fss_write/main/common-string.h>
#include <program/fss_write/main/common-type.h>
#include <program/fss_write/main/common.h>
#include <program/fss_write/extended_list/common.h>
#include <program/fss_write/main/print.h>
#include <program/fss_write/extended_list/print.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Process a single Content, printing the FSS-0003 (Extended List) if valid or an error if invalid.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   Must be of type (fss_write_setting_t *).
 *
 *   This alters setting.status.
 *   This uses and alters setting.buffer.
 * @param last
 *   If TRUE, then this is the last Content in the Content set.
 *   If FALSE, then this is not the last Content in the Content set.
 */
#ifndef _di_fss_write_extended_list_process_content_
  extern void fss_write_extended_list_process_content(fll_program_data_t * const main, void * const setting, const bool last);
#endif // _di_fss_write_extended_list_process_content_

/**
 * Process help for FSS-0003 (Extended List).
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   Must be of type (fss_write_setting_t *).
 *
 *   This does not alter setting.state.status.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fss_write_extended_list_process_help_
  extern void fss_write_extended_list_process_help(fll_program_data_t * const main, void * const setting);
#endif // _di_fss_write_extended_list_process_help_

/**
 * Process a single Object, printing the FSS-0003 (Extended List) if valid or an error if invalid.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   Must be of type (fss_write_setting_t *).
 *
 *   This alters setting.status.
 *   This uses and alters setting.buffer.
 */
#ifndef _di_fss_write_extended_list_process_object_
  extern void fss_write_extended_list_process_object(fll_program_data_t * const main, void * const setting);
#endif // _di_fss_write_extended_list_process_object_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_extended_list_h
