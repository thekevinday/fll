/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
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
#include "test-fss-item_delete.h"
#include "test-fss-item_destroy.h"
#include "test-fss-items_delete_callback.h"
#include "test-fss-items_destroy_callback.h"
#include "test-fss-itemss_delete_callback.h"
#include "test-fss-itemss_destroy_callback.h"
#include "test-fss-named_delete.h"
#include "test-fss-named_destroy.h"
#include "test-fss-nameds_delete_callback.h"
#include "test-fss-nameds_destroy_callback.h"
#include "test-fss-namedss_delete_callback.h"
#include "test-fss-namedss_destroy_callback.h"
#include "test-fss-nest_delete.h"
#include "test-fss-nest_destroy.h"
#include "test-fss-nests_delete_callback.h"
#include "test-fss-nests_destroy_callback.h"
#include "test-fss-nestss_delete_callback.h"
#include "test-fss-nestss_destroy_callback.h"
#include "test-fss-seek_to_eol.h"
#include "test-fss-set_delete.h"
#include "test-fss-set_destroy.h"
#include "test-fss-sets_delete_callback.h"
#include "test-fss-sets_destroy_callback.h"
#include "test-fss-setss_delete_callback.h"
#include "test-fss-setss_destroy_callback.h"
#include "test-fss-set_quote_delete.h"
#include "test-fss-set_quote_destroy.h"
#include "test-fss-set_quotes_delete_callback.h"
#include "test-fss-set_quotes_destroy_callback.h"
#include "test-fss-set_quotess_delete_callback.h"
#include "test-fss-set_quotess_destroy_callback.h"
#include "test-fss-simple_packet_decode.h"
#include "test-fss-simple_packet_decode_range.h"
#include "test-fss-simple_packet_delete.h"
#include "test-fss-simple_packet_destroy.h"
#include "test-fss-simple_packet_encode.h"
#include "test-fss-simple_packets_delete_callback.h"
#include "test-fss-simple_packets_destroy_callback.h"
#include "test-fss-simple_packetss_delete_callback.h"
#include "test-fss-simple_packetss_destroy_callback.h"
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
