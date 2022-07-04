/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the fss project.
 */
#ifndef _TEST__F_fss_h
#define _TEST__F_fss_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/fss.h>

// Mock includes.
#include "mock-fss.h"

// Test includes.
#include "test-fss-apply_delimit.h"
#include "test-fss-apply_delimit_range.h"
#include "test-fss-count_lines.h"
#include "test-fss-count_lines_range.h"
#include "test-fss-fail_utf.h"
#include "test-fss-fail_utf_to_false.h"
#include "test-fss-is_combining.h"
#include "test-fss-is_graph.h"
#include "test-fss-is_space.h"
#include "test-fss-is_zero_width.h"
#include "test-fss-items_adjust.h"
#include "test-fss-items_decimate_by.h"
#include "test-fss-items_decrease_by.h"
#include "test-fss-items_increase.h"
#include "test-fss-items_increase_by.h"
#include "test-fss-items_resize.h"
#include "test-fss-named_adjust.h"
#include "test-fss-named_decimate_by.h"
#include "test-fss-named_decrease_by.h"
#include "test-fss-named_increase.h"
#include "test-fss-named_increase_by.h"
#include "test-fss-named_resize.h"
#include "test-fss-nameds_adjust.h"
#include "test-fss-nameds_decimate_by.h"
#include "test-fss-nameds_decrease_by.h"
#include "test-fss-nameds_increase.h"
#include "test-fss-nameds_increase_by.h"
#include "test-fss-nameds_resize.h"
#include "test-fss-nest_adjust.h"
#include "test-fss-nest_decimate_by.h"
#include "test-fss-nest_decrease_by.h"
#include "test-fss-nest_increase.h"
#include "test-fss-nest_increase_by.h"
#include "test-fss-nest_resize.h"
#include "test-fss-nests_adjust.h"
#include "test-fss-nests_decimate_by.h"
#include "test-fss-nests_decrease_by.h"
#include "test-fss-nests_increase.h"
#include "test-fss-nests_increase_by.h"
#include "test-fss-nests_resize.h"
#include "test-fss-seek_to_eol.h"
#include "test-fss-set_adjust.h"
#include "test-fss-set_decimate_by.h"
#include "test-fss-set_decrease_by.h"
#include "test-fss-set_increase.h"
#include "test-fss-set_increase_by.h"
#include "test-fss-set_resize.h"
#include "test-fss-set_quote_adjust.h"
#include "test-fss-set_quote_decimate_by.h"
#include "test-fss-set_quote_decrease_by.h"
#include "test-fss-set_quote_increase.h"
#include "test-fss-set_quote_increase_by.h"
#include "test-fss-set_quote_resize.h"
#include "test-fss-set_quotes_adjust.h"
#include "test-fss-set_quotes_decimate_by.h"
#include "test-fss-set_quotes_decrease_by.h"
#include "test-fss-set_quotes_increase.h"
#include "test-fss-set_quotes_increase_by.h"
#include "test-fss-set_quotes_resize.h"
#include "test-fss-sets_adjust.h"
#include "test-fss-sets_decimate_by.h"
#include "test-fss-sets_decrease_by.h"
#include "test-fss-sets_increase.h"
#include "test-fss-sets_increase_by.h"
#include "test-fss-sets_resize.h"
#include "test-fss-skip_past_delimit.h"
#include "test-fss-skip_past_space.h"

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

#endif // _TEST__F_fss_h
