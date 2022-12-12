/**
 * FLL - Level 0
 *
 * Project: Execute
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Provides execute processing functionality.
 */
#ifndef _F_execute_h
#define _F_execute_h

// Include pre-requirements.
#ifndef _GNU_SOURCE
  #define _GNU_SOURCE
#endif // _GNU_SOURCE

// Libc includes.
#include <sched.h>
#include <termios.h>
#include <sys/types.h>
#include <unistd.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>

// FLL-0 execute includes.
#include <fll/level_0/execute/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Convert from F_status_t to execute status.
 *
 * @param status
 *   The status to convert from.
 *   The execute status does not support flags and so flags on this are ignored.
 *
 * @return
 *   The appropriate execute status code is returned on match.
 *
 *   F_execute_code_last is returned when there are no matching execute states.
 */
#ifndef _di_f_execute_status_from_status_
  extern uint8_t f_execute_status_from_status(f_status_t status);
#endif // _di_f_execute_status_from_status_

/**
 * Convert execute status to F_status_t.
 *
 * @param status
 *   An execute status number to convert.
 *   The execute status has no flags and is only 8-bits wide.
 *
 * @return
 *   The appropriate status code is returned on match (no bits, error or otherwise are set).
 *
 *   F_known_not (with error bit) if the given number has no known execute state to convert.
 */
#ifndef _di_f_execute_status_to_status_
  extern f_status_t f_execute_status_to_status(uint8_t status);
#endif // _di_f_execute_status_to_status_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_execute_h
