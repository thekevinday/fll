/**
 * FLL - Level 1
 *
 * Project: Execute
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides execute processing functionality.
 *
 * This utilizes setgroups() to set multiple supplementary groups.
 * It appears that POSIX failed to provide this (despite providing getgroups()).
 * There may be compatibility issues as a result of supporting setgroups().
 */
#ifndef _FL_execute_h
#define _FL_execute_h

// include pre-requirements
#define _GNU_SOURCE

// libc includes
#include <grp.h>
#include <sched.h>

// fll-0 includes
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/type_array.h>
#include <fll/level_0/execute.h>
#include <fll/level_0/limit.h>
#include <fll/level_0/signal.h>

// fll-1 execute includes
#include <fll/level_1/execute-common.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_execute_h
