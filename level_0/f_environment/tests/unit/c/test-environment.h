/**
 * FLL - Level 0
 *
 * Project: Environment
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the environment project.
 */
#ifndef _TEST__F_environment_h
#define _TEST__F_environment_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/environment.h>

// Mock includes.
#include "mock-environment.h"

// Test includes.
#include "test-environment-clear.h"
#include "test-environment-exists.h"
#include "test-environment-get.h"
#include "test-environment-get_all.h"
#include "test-environment-secure_is.h"
#include "test-environment-set.h"
#include "test-environment-unset.h"

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

#endif // _TEST__F_environment_h
