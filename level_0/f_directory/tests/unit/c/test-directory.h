/**
 * FLL - Level 0
 *
 * Project: Directory
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the directory project.
 */
#ifndef _TEST__F_directory_h
#define _TEST__F_directory_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/directory.h>

// Mock includes.
#include "mock-directory.h"

// Test includes.
#include "test-directory-create.h"
#include "test-directory-create_at.h"
#include "test-directory-exists.h"
#include "test-directory-exists_at.h"
#include "test-directory-is.h"
#include "test-directory-is_at.h"
#include "test-directory-list.h"
#include "test-directory-open.h"
#include "test-directory-open_at.h"
#include "test-directory-remove.h"
#include "test-directory-remove_custom.h"
#include "test-directory-touch.h"
#include "test-directory-touch_at.h"

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

#endif // _TEST__F_directory_h
