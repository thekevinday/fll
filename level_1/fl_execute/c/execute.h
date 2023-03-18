/**
 * FLL - Level 1
 *
 * Project: Execute
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides execute processing functionality.
 *
 * This utilizes setgroups() to set multiple supplementary groups.
 * It appears that POSIX failed to provide this (despite providing getgroups()).
 * There may be compatibility issues as a result of supporting setgroups().
 */
#ifndef _FL_execute_h
#define _FL_execute_h

// Include pre-requirements.
#ifndef _GNU_SOURCE
  #define _GNU_SOURCE
#endif // _GNU_SOURCE

// Libc includes.
#include <grp.h>
#include <sched.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/type_array.h>
#include <fll/level_0/string.h>
#include <fll/level_0/capability.h>
#include <fll/level_0/control_group.h>
#include <fll/level_0/execute.h>
#include <fll/level_0/limit.h>
#include <fll/level_0/signal.h>

// FLL-1 execute includes.
#include <fll/level_1/execute/common.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_execute_h
