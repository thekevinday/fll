/**
 * FLL - Level 0
 *
 * Project: Limit
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Provides limit related functionality.
 */
#ifndef _F_limit_h
#define _F_limit_h

// Include pre-requirements.
#define _GNU_SOURCE

// Libc includes.
#include <sys/time.h>
#include <sys/resource.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>

// FLL-0 control includes.
#include <fll/level_0/limit/value.h>
#include <fll/level_0/limit/set.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get or set the resource limits for some process.
 *
 * Either value_next or value_current must be non-zero.
 *
 * @param id
 *   The PID to set the resources of.
 * @param type
 *   The resource type to set limit of or get limit of.
 * @param value_next
 *   The resource value to assign.
 *   If 0 is used instead of a valid value, then value_current must be non-zero and will be populated with the current resource value.
 * @param value_current
 *   The resource value currently assigned.
 *   If 0, then value_next is assigning the value but the previous value will not be returned.
 *   If both value_next and value_current are non-zero, then this represents the value prior to the assignment of value_next.
 *
 * @return
 *   F_none on success.
 *   F_address_not (with error bit) if a pointer is outside of valid address space.
 *   F_found_not (with error bit) if no process by the given PID was found.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_prohibited (with error bit) if not allowed to perform this action.
 *
 * @see prlimit()
 */
#ifndef _di_f_limit_process_
  extern f_status_t f_limit_process(const pid_t id, const int type, const f_limit_value_t * const value_next, f_limit_value_t * const value_current);
#endif // _di_f_limit_process_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_limit_h
