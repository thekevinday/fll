/**
 * FLL - Level 3
 *
 * Project: Control
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * This is the Control program.
 *
 * This program utilizes the Featureless Linux Library.
 * This program is used to communicate with the "controller" program that exists as a system init (an alternative to sysvinit, initng, etc..).
 */
#ifndef _control_h
#define _control_h

// Libc includes.
#include <unistd.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/color.h>
#include <fll/level_0/console.h>
#include <fll/level_0/directory.h>
#include <fll/level_0/file.h>
#include <fll/level_0/fss.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/signal.h>
#include <fll/level_0/socket.h>

// FLL-1 includes.
#include <fll/level_1/console.h>
#include <fll/level_1/fss.h>
#include <fll/level_1/print.h>
#include <fll/level_1/string.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/fss_extended.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// Control includes.
#include <program/control/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print help.
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 * @see control_main()
 */
#ifndef _di_control_print_help_
  extern f_status_t control_print_help(control_main_t * const main);
#endif // _di_control_print_help_

/**
 * Execute main program.
 *
 * Be sure to call control_main_delete() after executing this.
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
 * @see control_main_delete()
 */
#ifndef _di_control_main_
  extern f_status_t control_main(control_main_t * const main, const f_console_arguments_t *arguments);
#endif // _di_control_main_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _control_h
