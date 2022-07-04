/**
 * FLL - Level 0
 *
 * Project: Limit
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the limit project.
 */
#ifndef _TEST__F_limit_h
#define _TEST__F_limit_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <string.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/limit.h>

// Mock includes.
#include "mock-limit.h"

// Test includes.
#include "test-limit-process.h"
#include "test-limit-sets_adjust.h"
#include "test-limit-sets_append.h"
#include "test-limit-sets_append_all.h"
#include "test-limit-sets_decimate_by.h"
#include "test-limit-sets_decrease_by.h"
#include "test-limit-sets_increase.h"
#include "test-limit-sets_increase_by.h"
#include "test-limit-sets_resize.h"
#include "test-limit-setss_adjust.h"
#include "test-limit-setss_append.h"
#include "test-limit-setss_append_all.h"
#include "test-limit-setss_decimate_by.h"
#include "test-limit-setss_decrease_by.h"
#include "test-limit-setss_increase.h"
#include "test-limit-setss_increase_by.h"
#include "test-limit-setss_resize.h"
#include "test-limit-values_adjust.h"
#include "test-limit-values_append.h"
#include "test-limit-values_append_all.h"
#include "test-limit-values_decimate_by.h"
#include "test-limit-values_decrease_by.h"
#include "test-limit-values_increase.h"
#include "test-limit-values_increase_by.h"
#include "test-limit-values_resize.h"
#include "test-limit-valuess_adjust.h"
#include "test-limit-valuess_append.h"
#include "test-limit-valuess_append_all.h"
#include "test-limit-valuess_decimate_by.h"
#include "test-limit-valuess_decrease_by.h"
#include "test-limit-valuess_increase.h"
#include "test-limit-valuess_increase_by.h"
#include "test-limit-valuess_resize.h"

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

#endif // _TEST__F_limit_h
