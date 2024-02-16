/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This is the program is intended to be used to manage iptables.
 *
 * This program utilizes the Featureless Linux Library.
 */
#ifndef _firewall_h
#define _firewall_h

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
#include <fll/level_2/execute.h>
#include <fll/level_2/fss.h>
#include <fll/level_2/fss/basic.h>
#include <fll/level_2/fss/basic_list.h>
#include <fll/level_2/fss/extended.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// Firewall includes.
#include <program/firewall/main/common/define.h>
#include <program/firewall/main/common/enumeration.h>
#include <program/firewall/main/common/print.h>
#include <program/firewall/main/common/string.h>
#include <program/firewall/main/common/type.h>
#include <program/firewall/main/common.h>
#include <program/firewall/main/print/debug.h>
#include <program/firewall/main/print/error.h>
#include <program/firewall/main/print/message.h>
#include <program/firewall/main/print/warning.h>
#include <program/firewall/main/operate.h>
#include <program/firewall/main/operate/buffer.h>
#include <program/firewall/main/operate/create.h>
#include <program/firewall/main/operate/default.h>
#include <program/firewall/main/operate/delete.h>
#include <program/firewall/main/operate/process.h>
#include <program/firewall/main/signal.h>
#include <program/firewall/main/thread.h>

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
 *     Errors (with error bit) from: firewall_load_line()
 *     Errors (with error bit) from: firewall_process()
 *
 * @see f_file_stream_open()
 * @see firewall_load_line()
 * @see firewall_process()
 */
#ifndef _di_firewall_main_
  extern void firewall_main(firewall_main_t * const main);
#endif // _di_firewall_main_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_h
