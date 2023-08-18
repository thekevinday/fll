/**
 * FLL - Level 0
 *
 * Project: Compare
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the compare project.
 */
#ifndef _TEST__F_compare_h
#define _TEST__F_compare_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/compare.h>

// Test includes.
#include "test-compare-.h"
#include "test-compare-dynamic.h"
#include "test-compare-dynamic_partial.h"
#include "test-compare-dynamic_partial_dynamic.h"
#include "test-compare-dynamic_partial_except.h"
#include "test-compare-dynamic_partial_except_dynamic.h"
#include "test-compare-dynamic_partial_except_string.h"
#include "test-compare-dynamic_partial_except_trim.h"
#include "test-compare-dynamic_partial_except_trim_dynamic.h"
#include "test-compare-dynamic_partial_except_trim_string.h"
#include "test-compare-dynamic_partial_string.h"
#include "test-compare-dynamic_partial_trim.h"
#include "test-compare-dynamic_partial_trim_dynamic.h"
#include "test-compare-dynamic_partial_trim_string.h"
#include "test-compare-dynamic_string.h"
#include "test-compare-dynamic_trim.h"
#include "test-compare-dynamic_trim_string.h"
#include "test-compare-dynamic_except.h"
#include "test-compare-dynamic_except_string.h"
#include "test-compare-dynamic_except_trim.h"
#include "test-compare-dynamic_except_trim_string.h"
#include "test-compare-except.h"
#include "test-compare-except_trim.h"
#include "test-compare-trim.h"

#include "test-compare-utf.h"
#include "test-compare-utf_dynamic.h"
#include "test-compare-utf_dynamic_partial.h"
#include "test-compare-utf_dynamic_partial_dynamic.h"
#include "test-compare-utf_dynamic_partial_except.h"
#include "test-compare-utf_dynamic_partial_except_dynamic.h"
#include "test-compare-utf_dynamic_partial_except_string.h"
#include "test-compare-utf_dynamic_partial_except_trim.h"
#include "test-compare-utf_dynamic_partial_except_trim_dynamic.h"
#include "test-compare-utf_dynamic_partial_except_trim_string.h"
#include "test-compare-utf_dynamic_partial_string.h"
#include "test-compare-utf_dynamic_partial_trim.h"
#include "test-compare-utf_dynamic_partial_trim_dynamic.h"
#include "test-compare-utf_dynamic_partial_trim_string.h"
#include "test-compare-utf_dynamic_string.h"
#include "test-compare-utf_dynamic_trim.h"
#include "test-compare-utf_dynamic_trim_string.h"
#include "test-compare-utf_dynamic_except.h"
#include "test-compare-utf_dynamic_except_string.h"
#include "test-compare-utf_dynamic_except_trim.h"
#include "test-compare-utf_dynamic_except_trim_string.h"
#include "test-compare-utf_except.h"
#include "test-compare-utf_except_trim.h"
#include "test-compare-utf_trim.h"

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

/**
 * Helper function for converting an entire dynamic string to a complete utf dynamic string.
 *
 * @param dynamic
 *   The source string.
 * @param utf
 *   The UTF destination string.
 *
 * @return
 *   F_okay on success.
 *
 *   Errors (with error bit) from: f_utf_char_to_character().
 *   Errors (with error bit) from: f_utf_string_dynamic_resize().
 *
 * @see f_utf_char_to_character()
 * @see f_utf_string_dynamic_resize()
 */
extern f_status_t test_convert_dynamic_to_utf(const f_string_static_t dynamic, f_utf_string_dynamic_t * const utf);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _TEST__F_compare_h
