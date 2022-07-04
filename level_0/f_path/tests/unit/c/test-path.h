/**
 * FLL - Level 0
 *
 * Project: Path
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the path project.
 */
#ifndef _TEST__F_path_h
#define _TEST__F_path_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/path.h>

// Mock includes.
#include "mock-path.h"

// Test includes.
#include "test-path-change.h"
#include "test-path-change_at.h"
#include "test-path-current.h"
#include "test-path-directory_cleanup.h"
#include "test-path-is.h"
#include "test-path-is_absolute.h"
#include "test-path-is_relative.h"
#include "test-path-is_relative_current.h"
#include "test-path-real.h"

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

#endif // _TEST__F_path_h
