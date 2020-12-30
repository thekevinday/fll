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
#ifndef _F_control_group_h
#define _F_control_group_h

// libc includes

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>

// fll-1 control includes
#include <level_0/control_group-common.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_control_group_h
