/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * This is the Kevux Operating System Firewall program.
 * This program utilizes the Featureless Linux Library.
 * This program processes firewall commands and passes them to iptables from netfiler.org.
 */
#ifndef _firewall_h
#define _firewall_h

// Libc includes.
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/type_array.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/color.h>
#include <fll/level_0/console.h>
#include <fll/level_0/directory.h>
#include <fll/level_0/execute.h>
#include <fll/level_0/file.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/signal.h>

// FLL-1 includes.
#include <fll/level_1/console.h>
#include <fll/level_1/string.h>
#include <fll/level_1/print.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/execute.h>
#include <fll/level_2/fss_basic.h>
#include <fll/level_2/fss_basic_list.h>
#include <fll/level_2/fss_extended.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// Firewall includes.
#include <program/firewall/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print help.
 *
 * @param file
 *   The file to print to.
 * @param context
 *   The color context settings.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_firewall_print_help_
  extern f_status_t firewall_print_help(const f_file_t file, const f_color_context_t context);
#endif // _di_firewall_print_help_

/**
 * Execute main program.
 *
 * Be sure to call firewall_main_delete() after executing this.
 *
 * If main.signal is non-zero, then this blocks and handles the following signals:
 *   - F_signal_abort
 *   - F_signal_broken_pipe
 *   - F_signal_hangup
 *   - F_signal_interrupt
 *   - F_signal_quit
 *   - F_signal_termination
 *
 * @param data
 *   The main program data.
 * @param arguments
 *   The parameters passed to the process.
 *
 * @return
 *   F_none on success.
 *
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see firewall_main_delete()
 */
#ifndef _di_firewall_main_
  extern f_status_t firewall_main(firewall_main_t * const main, const f_console_arguments_t *arguments);
#endif // _di_firewall_main_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _firewall_h
