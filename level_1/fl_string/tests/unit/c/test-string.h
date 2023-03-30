/**
 * FLL - Level 1
 *
 * Project: String
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the string project.
 */
#ifndef _TEST__FL_string_h
#define _TEST__FL_string_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-1 includes.
#include <fll/level_1/string.h>

// Test includes.
#include "test-string-compare.h"
#include "test-string-compare_dynamic.h"
#include "test-string-compare_dynamic_partial.h"
#include "test-string-compare_dynamic_partial_dynamic.h"
#include "test-string-compare_dynamic_partial_except.h"
#include "test-string-compare_dynamic_partial_except_dynamic.h"
#include "test-string-compare_dynamic_partial_except_string.h"
#include "test-string-compare_dynamic_partial_except_trim.h"
#include "test-string-compare_dynamic_partial_except_trim_dynamic.h"
#include "test-string-compare_dynamic_partial_except_trim_string.h"
#include "test-string-compare_dynamic_partial_string.h"
#include "test-string-compare_dynamic_partial_trim.h"
#include "test-string-compare_dynamic_partial_trim_dynamic.h"
#include "test-string-compare_dynamic_partial_trim_string.h"
#include "test-string-compare_dynamic_string.h"
#include "test-string-compare_dynamic_trim.h"
#include "test-string-compare_dynamic_trim_string.h"
#include "test-string-compare_dynamic_except.h"
#include "test-string-compare_dynamic_except_string.h"
#include "test-string-compare_dynamic_except_trim.h"
#include "test-string-compare_dynamic_except_trim_string.h"
#include "test-string-compare_except.h"
#include "test-string-compare_except_trim.h"
#include "test-string-compare_trim.h"

#ifdef __cplusplus
extern "C" {
#endif

// Back ported from 0.7.x here for convenience in tests.
extern const f_string_range_t f_string_range_empty_c;

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

#endif // _TEST__FL_string_h
