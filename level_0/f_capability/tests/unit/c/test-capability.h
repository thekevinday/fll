/**
 * FLL - Level 0
 *
 * Project: Capability
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the capability project.
 */
#ifndef _TEST__F_capability_h
#define _TEST__F_capability_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdio.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/capability.h>

// Mock includes.
#include "mock-capability.h"

// Test includes.
#include "test-capability-ambient_get.h"
#include "test-capability-ambient_reset.h"
#include "test-capability-ambient_set.h"
#include "test-capability-clear.h"
#include "test-capability-clear_flag.h"
#include "test-capability-compare.h"
#include "test-capability-copy.h"
#include "test-capability-copy_external.h"
#include "test-capability-copy_internal.h"
#include "test-capability-delete.h"
#include "test-capability-file_descriptor_get.h"
#include "test-capability-file_descriptor_set.h"
#include "test-capability-file_get.h"
#include "test-capability-file_set.h"
#include "test-capability-flag_get.h"
#include "test-capability-flag_set.h"
#include "test-capability-from_name.h"
#include "test-capability-from_text.h"
#include "test-capability-groups_set.h"
#include "test-capability-initialize.h"
#include "test-capability-mode_get.h"
#include "test-capability-mode_get_name.h"
#include "test-capability-mode_set.h"
#include "test-capability-owner_get.h"
#include "test-capability-owner_set.h"
#include "test-capability-process_bound_drop.h"
#include "test-capability-process_bound_get.h"
#include "test-capability-process_get_by_id.h"
#include "test-capability-process_get.h"
#include "test-capability-process_set.h"
#include "test-capability-security_bits_get.h"
#include "test-capability-security_bits_set.h"
#include "test-capability-size.h"
#include "test-capability-supported_ambient.h"
#include "test-capability-supported.h"
#include "test-capability-supported_code.h"
#include "test-capability-to_name.h"
#include "test-capability-to_text.h"
#include "test-capability-user_set.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform any setup operations.
 *
 * @param state
 *   The test state.
 *
 * @return
 *   The status of this function, where 0 means success.
 */
extern int setup(void **state);

/**
 * Peform any setdown operations.
 *
 * @param state
 *   The test state.
 *
 * @return
 *   The status of this function, where 0 means success.
 */
extern int setdown(void **state);

/**
 * Run all tests.
 *
 * @return
 *   The final result of the tests.
 *
 * @see cmocka_run_group_tests()
 * @see cmocka_unit_test()
 */
extern int main(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _TEST__F_capability_h
