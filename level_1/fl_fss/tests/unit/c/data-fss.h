/**
 * FLL - Level 1
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Data for the fss project tests.
 */
#ifndef _DATA__FL_fss_h
#define _DATA__FL_fss_h

// Libc includes.
#include <arpa/inet.h>
#include <stdint.h>
#include <stdio.h>

// FLL-0 includes.

// FLL-1 includes.
#include <fll/level_1/fss.h>
#include <fll/level_1/fss/basic.h>
#include <fll/level_1/fss/basic_list.h>
#include <fll/level_1/fss/embedded_list.h>
#include <fll/level_1/fss/extended.h>
#include <fll/level_1/fss/extended_list.h>
#include <fll/level_1/fss/payload.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Open the test data file for the given set with the given name.
 *
 * This requires the following:
 *   - The file path is relative to the current working directory (tests are run from project root).
 *   - The file path is "data/tests/${set}/${name}-all_read.txt".
 *   - Where "${set}" represents the directory set, like "contents", "objects", or "strings".
 *   - Where "${name}" represents the standard name, such as "basic" or "extended".
 *
 * @param at
 *   A number representing the specific content index position.
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__file_open__named__all_read(const f_string_t set, const f_string_t name);

/**
 * Open the test data file for the given set with the given name and the given at index.
 *
 * This requires the following:
 *   - The file path is relative to the current working directory (tests are run from project root).
 *   - The file path is "data/tests/${set}/${name}-all_read-${at}.txt".
 *   - Where "${at}" represents the index.
 *   - Where "${set}" represents the directory set, like "contents", "objects", or "strings".
 *   - Where "${name}" represents the standard name, such as "basic" or "extended".
 *
 * @param at
 *   A number representing the specific content index position.
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__file_open__named_at__all_read(const f_string_t set, const f_string_t name, const uint8_t at);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _DATA__FL_fss_h
