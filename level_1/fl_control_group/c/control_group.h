/**
 * FLL - Level 1
 *
 * Project: Control Group
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides control group (cgroup) related functionality.
 *
 * It appears that the control group, as documented in the Linux kernel, is changed via the sysfs instead of system calls.
 * If there are system calls to set the control group for a given process then this will need to be updated to utilize that.
 * Until then, this is an implementation that helps facilitate writing to the sysfs filesystem for adding a process to a particular control group.
 *
 * This is intended to be used with Control Groups (cgroups) Version 2.
 */
#ifndef _FL_control_group_h
#define _FL_control_group_h

// include pre-requirements
#define _GNU_SOURCE

// libc includes
#include <sched.h>
#include <stdio.h>
#include <string.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/control_group.h>
#include <level_0/file.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Apply the given control groups to the process represented by the PID.
 *
 * @param control
 *   The control group(s) to apply.
 * @param id
 *   The PID of the process to apply the control group(s) to.
 *
 * @return
 *   F_none on success.
 *   F_memory_not (with error bit) if a out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if the current user/process has insufficient privileges to set certain cgroup settings.
 *   F_space_not (with error bit) if a maximum resource limit is reached and there is not enough space.
 *   F_failure (with error bit) on any other error.
 *
 *   Errors (with error bit) from: f_file_stream_open().
 *
 * @see fprintf()
 * @see fflush()
 * @see memcpy()
 * @see unshare()
 *
 * @see f_file_stream_close()
 * @see f_file_stream_open()
 */
#ifndef _di_fl_control_group_apply_
  extern f_return_status fl_control_group_apply(const f_control_group_t control_group, const pid_t id);
#endif // _di_fl_control_group_apply_

/**
 * Delete the control group structure.
 *
 * @param control_group
 *   The control group to delete.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_control_group_delete_
  extern f_return_status fl_control_group_delete(f_control_group_t *control_group);
#endif // _di_fl_control_group_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_control_group_h
