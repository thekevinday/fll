/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This is the Controller program.
 *
 * This program utilizes the Featureless Linux Library.
 * This program provides system service management, much like sysvcontroller and controllerng.
 * This program can be controlled from user-space via the "control" program.
 * This program can be used in an initrd and should be capable of pivot root operations.
 */
#ifndef _controller_h
#define _controller_h

// Include pre-requirements.
#define _GNU_SOURCE

// Libc includes.
#include <sched.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <linux/sched.h>
#include <unistd.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/type_array.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/account.h>
#include <fll/level_0/capability.h>
#include <fll/level_0/color.h>
#include <fll/level_0/console.h>
#include <fll/level_0/control_group.h>
#include <fll/level_0/directory.h>
#include <fll/level_0/environment.h>
#include <fll/level_0/execute.h>
#include <fll/level_0/file.h>
#include <fll/level_0/fss.h>
#include <fll/level_0/iki.h>
#include <fll/level_0/path.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/signal.h>
#include <fll/level_0/socket.h>
#include <fll/level_0/status_string.h>

// FLL-1 includes.
#include <fll/level_1/control_group.h>
#include <fll/level_1/environment.h>
#include <fll/level_1/fss.h>
#include <fll/level_1/iki.h>
#include <fll/level_1/print.h>
#include <fll/level_1/string.h>

// FLL-2 includes.
#include <fll/level_2/control_group.h>
#include <fll/level_2/error.h>
#include <fll/level_2/execute.h>
#include <fll/level_2/fss.h>
#include <fll/level_2/fss/basic_list.h>
#include <fll/level_2/fss/extended.h>
#include <fll/level_2/fss/extended_list.h>
#include <fll/level_2/fss/payload.h>
#include <fll/level_2/path.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>
#include <fll/level_2/status_string.h>

// Controller includes.
#include <program/controller/common.h>

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
 * @see controller_main()
 */
#ifndef _di_controller_print_help_
  extern f_status_t controller_print_help(controller_main_t * const main);
#endif // _di_controller_print_help_

/**
 * Execute main program.
 *
 * Be sure to call controller_main_delete() after executing this.
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
 *   F_child if this is a child process returning.
 *
 *   F_interrupt (with error bit) on receiving a process signal, such as an interrupt signal.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see controller_main_delete()
 */
#ifndef _di_controller_main_
  extern f_status_t controller_main(controller_main_t * const main, const f_console_arguments_t arguments);
#endif // _di_controller_main_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_h
