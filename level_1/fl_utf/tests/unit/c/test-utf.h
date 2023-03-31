/**
 * FLL - Level 1
 *
 * Project: Utf
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the utf project.
 */
#ifndef _TEST__FL_utf_h
#define _TEST__FL_utf_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-1 includes.
#include <fll/level_1/utf.h>

// Test includes.
#include "test-utf-string_compare.h"
#include "test-utf-string_compare_trim.h"
#include "test-utf-string_dynamic_compare.h"
#include "test-utf-string_dynamic_compare_trim.h"
#include "test-utf-string_dynamic_partial_compare.h"
#include "test-utf-string_dynamic_partial_compare_trim.h"

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

/**
 * Helper function for converting an entire dynamic string to a complete utf dynamic string.
 *
 * @param dynamic
 *   The source string.
 * @param utf
 *   The UTF destination string.
 *
 * @return
 *   F_none on success.
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

#endif // _TEST__FL_utf_h
