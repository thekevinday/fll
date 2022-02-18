/**
 * FLL - Level 0
 *
 * Project: Control Group
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides control group (cgroup) related functionality.
 *
 * It appears that the control group, as documented in the Linux kernel, is changed via the sysfs instead of system calls.
 * If there are system calls to set the control group for a given process then this will need to be updated to utilize that.
 * Until then, this is an implementation that helps facilitate writing to the sysfs file system for adding a process to a particular control group.
 *
 * This is intended to be used with Control Groups (cgroups) Version 2.
 */
#ifndef _F_control_group_h
#define _F_control_group_h

// Libc includes.

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>

// FLL-1 control includes.
#include <fll/level_0/control_group/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Copy the source control group onto the destination control group.
 *
 * @param source
 *   The source to append.
 * @param destination
 *   The destination the source is appended onto.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_string_dynamic_append().
 *   Errors (with error bit) from: f_string_dynamics_append().
 *
 * @see f_string_dynamic_append()
 * @see f_string_dynamics_append()
 */
#ifndef _di_f_control_group_copy_
  extern f_status_t f_control_group_copy(const f_control_group_t source, f_control_group_t * const destination);
#endif // _di_f_control_group_copy_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_control_group_h
