/**
 * FLL - Level 2
 *
 * Project: IKI
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the fll_path project.
 */
#ifndef _TEST__FLL_path_h
#define _TEST__FLL_path_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

// cmocka includes.
#include <cmocka.h>

// FLL-2 includes.
#include <fll/level_1/path.h>

// Mock includes.
//#include "mock-path.h"

// Test includes.
#include "test-path-canonical.h"

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

#endif // _TEST__FLL_path_h
