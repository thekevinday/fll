/**
 * FLL - Level 3
 *
 * Project: FSS Identify
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This is the program is intended to be used to identify an FSS file or FSS data.
 *
 * A valid FSS file or FSS data will have a header starting with the pound character '#'.
 *
 * This program utilizes the Featureless Linux Library.
 */
#ifndef _fss_identify_h
#define _fss_identify_h

// Libc includes.
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
#include <fll/level_0/directory.h>
#include <fll/level_0/fss.h>
#include <fll/level_0/file.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/rip.h>
#include <fll/level_0/signal.h>
#include <fll/level_0/thread.h>

// FLL-1 includes.
#include <fll/level_1/conversion.h>
#include <fll/level_1/fss.h>
#include <fll/level_1/print.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/fss.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// FSS Identify includes.
#include <program/fss_identify/main/common/define.h>
#include <program/fss_identify/main/common/enumeration.h>
#include <program/fss_identify/main/common/print.h>
#include <program/fss_identify/main/common/string.h>
#include <program/fss_identify/main/common/type.h>
#include <program/fss_identify/main/common.h>
#include <program/fss_identify/main/load.h>
#include <program/fss_identify/main/print/data.h>
#include <program/fss_identify/main/print/error.h>
#include <program/fss_identify/main/print/message.h>
#include <program/fss_identify/main/process.h>
#include <program/fss_identify/main/signal.h>
#include <program/fss_identify/main/thread.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Execute main program.
 *
 * @param main
 *   The main program and setting data.
 *
 *   This alters main.setting.state.status:
 *     F_okay on success.
 *
 *     F_interrupt (with error bit) on interrupt signal received.
 *
 *     Errors (with error bit) from: f_file_stream_open()
 *     Errors (with error bit) from: fss_identify_load_line()
 *     Errors (with error bit) from: fss_identify_process()
 *
 * @see f_file_stream_open()
 * @see fss_identify_load_line()
 * @see fss_identify_process()
 */
#ifndef _di_fss_identify_main_
  extern void fss_identify_main(fss_identify_main_t * const main);
#endif // _di_fss_identify_main_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_identify_h
