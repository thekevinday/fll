/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the utf project.
 */
#ifndef _TEST__F_utf_h
#define _TEST__F_utf_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/utf.h>

// Mock includes.
//#include "mock-utf.h"

// Data includes.
#include "data-utf.h"

// Test includes.
#include "test-utf-append.h"
#include "test-utf-append_assure.h"
#include "test-utf-append_assure_nulless.h"
#include "test-utf-append_nulless.h"
#include "test-utf-character_is_alphabetic.h"
#include "test-utf-character_is_alphabetic_digit.h"
#include "test-utf-character_is_alphabetic_numeric.h"
#include "test-utf-character_is_combining.h"
#include "test-utf-character_is_control.h"
#include "test-utf-character_is_digit.h"
#include "test-utf-character_is_digit.h"
#include "test-utf-character_is_emoji.h"
#include "test-utf-character_is_numeric.h"
#include "test-utf-character_is_phonetic.h"
#include "test-utf-character_is_private.h"
#include "test-utf-character_is_punctuation.h"
#include "test-utf-character_is_subscript.h"
#include "test-utf-character_is_superscript.h"
#include "test-utf-character_is_symbol.h"
#include "test-utf-character_is_valid.h"
#include "test-utf-character_is_whitespace.h"
#include "test-utf-character_is_whitespace_modifier.h"
#include "test-utf-character_is_whitespace_other.h"
#include "test-utf-character_is_whitespace_zero_width.h"
#include "test-utf-character_is_wide.h"
#include "test-utf-character_is_word.h"
#include "test-utf-character_is_word_dash.h"
#include "test-utf-character_is_word_dash_plus.h"
#include "test-utf-character_is_zero_width.h"
#include "test-utf-dynamic_adjust.h"
#include "test-utf-dynamic_append.h"
#include "test-utf-dynamic_append_assure.h"
#include "test-utf-dynamic_append_assure_nulless.h"
#include "test-utf-dynamic_append_nulless.h"
#include "test-utf-dynamic_decimate_by.h"
#include "test-utf-dynamic_decrease_by.h"
#include "test-utf-dynamic_increase.h"
#include "test-utf-dynamic_increase_by.h"
#include "test-utf-dynamic_mash.h"
#include "test-utf-dynamic_mash_nulless.h"
#include "test-utf-dynamic_mish.h"
#include "test-utf-dynamic_mish_nulless.h"
#include "test-utf-dynamic_partial_append.h"
#include "test-utf-dynamic_partial_append_assure.h"
#include "test-utf-dynamic_partial_append_assure_nulless.h"
#include "test-utf-dynamic_partial_append_nulless.h"
#include "test-utf-dynamic_partial_mash.h"
#include "test-utf-dynamic_partial_mash_nulless.h"
#include "test-utf-dynamic_partial_mish.h"
#include "test-utf-dynamic_partial_mish_nulless.h"
#include "test-utf-dynamic_partial_prepend.h"
#include "test-utf-dynamic_partial_prepend_assure.h"
#include "test-utf-dynamic_partial_prepend_assure_nulless.h"
#include "test-utf-dynamic_partial_prepend_nulless.h"
#include "test-utf-dynamic_prepend.h"
#include "test-utf-dynamic_prepend_assure.h"
#include "test-utf-dynamic_prepend_assure_nulless.h"
#include "test-utf-dynamic_prepend_nulless.h"
#include "test-utf-dynamic_resize.h"
#include "test-utf-dynamic_seek_line.h"
#include "test-utf-dynamic_seek_line_to.h"
#include "test-utf-dynamic_seek_to.h"
#include "test-utf-dynamic_terminate.h"
#include "test-utf-dynamic_terminate_after.h"
#include "test-utf-dynamics_adjust.h"
#include "test-utf-dynamics_append.h"
#include "test-utf-dynamics_append_all.h"
#include "test-utf-dynamics_decimate_by.h"
#include "test-utf-dynamics_decrease_by.h"
#include "test-utf-dynamics_increase.h"
#include "test-utf-dynamics_increase_by.h"
#include "test-utf-dynamics_resize.h"
#include "test-utf-dynamicss_adjust.h"
#include "test-utf-dynamicss_append.h"
#include "test-utf-dynamicss_append_all.h"
#include "test-utf-dynamicss_decimate_by.h"
#include "test-utf-dynamicss_decrease_by.h"
#include "test-utf-dynamicss_increase.h"
#include "test-utf-dynamicss_increase_by.h"
#include "test-utf-dynamicss_resize.h"
#include "test-utf-is_alphabetic.h"
#include "test-utf-is_alphabetic_digit.h"
#include "test-utf-is_alphabetic_numeric.h"
#include "test-utf-is_combining.h"
#include "test-utf-is_control.h"
#include "test-utf-is_digit.h"
#include "test-utf-is_digit.h"
#include "test-utf-is_emoji.h"
#include "test-utf-is_numeric.h"
#include "test-utf-is_phonetic.h"
#include "test-utf-is_private.h"
#include "test-utf-is_punctuation.h"
#include "test-utf-is_subscript.h"
#include "test-utf-is_superscript.h"
#include "test-utf-is_symbol.h"
#include "test-utf-is_valid.h"
#include "test-utf-is_whitespace.h"
#include "test-utf-is_whitespace_modifier.h"
#include "test-utf-is_whitespace_other.h"
#include "test-utf-is_whitespace_zero_width.h"
#include "test-utf-is_wide.h"
#include "test-utf-is_word.h"
#include "test-utf-is_word_dash.h"
#include "test-utf-is_word_dash_plus.h"
#include "test-utf-is_zero_width.h"
#include "test-utf-map_multis_adjust.h"
#include "test-utf-map_multis_append.h"
#include "test-utf-map_multis_append_all.h"
#include "test-utf-map_multis_decimate_by.h"
#include "test-utf-map_multis_decrease_by.h"
#include "test-utf-map_multis_increase.h"
#include "test-utf-map_multis_increase_by.h"
#include "test-utf-map_multis_resize.h"
#include "test-utf-map_multiss_adjust.h"
#include "test-utf-map_multiss_append.h"
#include "test-utf-map_multiss_append_all.h"
#include "test-utf-map_multiss_decimate_by.h"
#include "test-utf-map_multiss_decrease_by.h"
#include "test-utf-map_multiss_increase.h"
#include "test-utf-map_multiss_increase_by.h"
#include "test-utf-map_multiss_resize.h"
#include "test-utf-maps_adjust.h"
#include "test-utf-maps_append.h"
#include "test-utf-maps_append_all.h"
#include "test-utf-maps_decimate_by.h"
#include "test-utf-maps_decrease_by.h"
#include "test-utf-maps_increase.h"
#include "test-utf-maps_increase_by.h"
#include "test-utf-maps_resize.h"
#include "test-utf-mapss_adjust.h"
#include "test-utf-mapss_append.h"
#include "test-utf-mapss_append_all.h"
#include "test-utf-mapss_decimate_by.h"
#include "test-utf-mapss_decrease_by.h"
#include "test-utf-mapss_increase.h"
#include "test-utf-mapss_increase_by.h"
#include "test-utf-mapss_resize.h"
#include "test-utf-mash.h"
#include "test-utf-mash_nulless.h"
#include "test-utf-mish.h"
#include "test-utf-mish_nulless.h"
#include "test-utf-prepend.h"
#include "test-utf-prepend_assure.h"
#include "test-utf-prepend_assure_nulless.h"
#include "test-utf-prepend_nulless.h"
#include "test-utf-seek_line.h"
#include "test-utf-seek_line_to.h"
#include "test-utf-seek_to.h"
#include "test-utf-triples_adjust.h"
#include "test-utf-triples_append.h"
#include "test-utf-triples_append_all.h"
#include "test-utf-triples_decimate_by.h"
#include "test-utf-triples_decrease_by.h"
#include "test-utf-triples_increase.h"
#include "test-utf-triples_increase_by.h"
#include "test-utf-triples_resize.h"
#include "test-utf-tripless_adjust.h"
#include "test-utf-tripless_append.h"
#include "test-utf-tripless_append_all.h"
#include "test-utf-tripless_decimate_by.h"
#include "test-utf-tripless_decrease_by.h"
#include "test-utf-tripless_increase.h"
#include "test-utf-tripless_increase_by.h"
#include "test-utf-tripless_resize.h"

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

#endif // _TEST__F_utf_h
