/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the string project.
 */
#ifndef _TEST__F_string_h
#define _TEST__F_string_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/string.h>

// Mock includes.
#include "mock-string.h"

// Test includes.
#include "test-string-append.h"
#include "test-string-append_assure.h"
#include "test-string-append_assure_nulless.h"
#include "test-string-append_nulless.h"
#include "test-string-dynamic_append.h"
#include "test-string-dynamic_append_assure.h"
#include "test-string-dynamic_append_assure_nulless.h"
#include "test-string-dynamic_append_nulless.h"
#include "test-string-dynamic_mash.h"
#include "test-string-dynamic_mash_nulless.h"
#include "test-string-dynamic_mish.h"
#include "test-string-dynamic_mish_nulless.h"
#include "test-string-dynamic_partial_append.h"
#include "test-string-dynamic_partial_append_assure.h"
#include "test-string-dynamic_partial_append_assure_nulless.h"
#include "test-string-dynamic_partial_append_nulless.h"
#include "test-string-dynamic_partial_mash.h"
#include "test-string-dynamic_partial_mash_nulless.h"
#include "test-string-dynamic_partial_mish.h"
#include "test-string-dynamic_partial_mish_nulless.h"
#include "test-string-dynamic_partial_prepend.h"
#include "test-string-dynamic_partial_prepend_assure.h"
#include "test-string-dynamic_partial_prepend_assure_nulless.h"
#include "test-string-dynamic_partial_prepend_nulless.h"
#include "test-string-dynamic_prepend.h"
#include "test-string-dynamic_prepend_assure.h"
#include "test-string-dynamic_prepend_assure_nulless.h"
#include "test-string-dynamic_prepend_nulless.h"
#include "test-string-dynamic_seek_line.h"
#include "test-string-dynamic_seek_line_to.h"
#include "test-string-dynamic_seek_to.h"
#include "test-string-dynamic_terminate.h"
#include "test-string-dynamic_terminate_after.h"
#include "test-string-dynamics_append.h"
#include "test-string-dynamics_append_all.h"
#include "test-string-dynamics_delete_callback.h"
#include "test-string-dynamics_destroy_callback.h"
#include "test-string-dynamicss_append.h"
#include "test-string-dynamicss_append_all.h"
#include "test-string-dynamicss_delete_callback.h"
#include "test-string-dynamicss_destroy_callback.h"
#include "test-string-map_multis_append.h"
#include "test-string-map_multis_append_all.h"
#include "test-string-map_multis_delete_callback.h"
#include "test-string-map_multis_destroy_callback.h"
#include "test-string-map_multiss_append.h"
#include "test-string-map_multiss_append_all.h"
#include "test-string-map_multiss_delete_callback.h"
#include "test-string-map_multiss_destroy_callback.h"
#include "test-string-maps_append.h"
#include "test-string-maps_append_all.h"
#include "test-string-maps_delete_callback.h"
#include "test-string-maps_destroy_callback.h"
#include "test-string-mapss_append.h"
#include "test-string-mapss_append_all.h"
#include "test-string-mapss_delete_callback.h"
#include "test-string-mapss_destroy_callback.h"
#include "test-string-mash.h"
#include "test-string-mash_nulless.h"
#include "test-string-mish.h"
#include "test-string-mish_nulless.h"
#include "test-string-prepend.h"
#include "test-string-prepend_assure.h"
#include "test-string-prepend_assure_nulless.h"
#include "test-string-prepend_nulless.h"
#include "test-string-quantitys_append.h"
#include "test-string-quantitys_append_all.h"
#include "test-string-quantityss_append.h"
#include "test-string-quantityss_append_all.h"
#include "test-string-quantityss_delete_callback.h"
#include "test-string-quantityss_destroy_callback.h"
#include "test-string-seek_line.h"
#include "test-string-seek_line_to.h"
#include "test-string-seek_to.h"
#include "test-string-triples_append.h"
#include "test-string-triples_append_all.h"
#include "test-string-triples_delete_callback.h"
#include "test-string-triples_destroy_callback.h"
#include "test-string-tripless_append.h"
#include "test-string-tripless_append_all.h"
#include "test-string-tripless_delete_callback.h"
#include "test-string-tripless_destroy_callback.h"

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

#endif // _TEST__F_string_h
