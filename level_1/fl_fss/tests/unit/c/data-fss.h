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

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Open the test data file for the given set with the given name.
 *
 * This requires the following:
 *   - The file path is relative to the current working directory (tests are run from project root).
 *   - The file path is "data/tests/${set}/${name}-${context}.txt".
 *   - Where "${set}" represents the directory set, like "contents", "objects", or "strings".
 *   - Where "${name}" represents the standard name, such as "basic" or "extended".
 *   - Where "${context}" represents the test context, such as "all_read" or "header_map".
 *
 * @param set
 *   The name of the test set, representing the directory the the files are stored within.
 * @param context
 *   The test file directory set.
 * @param name
 *   The test file standard name.
 * @param at
 *   A number representing the specific content index position.
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__file_open__named(const f_string_t set, const f_string_t name, const f_string_t context);

/**
 * Open the test data file for the given set with the given name and the given at index.
 *
 * This requires the following:
 *   - The file path is relative to the current working directory (tests are run from project root).
 *   - The file path is "data/tests/${set}/${name}-${context}-${at}.txt".
 *   - Where "${set}" represents the directory set, like "contents", "headers", "objects", "strings", or "variables".
 *   - Where "${name}" represents the standard name, such as "basic", "extended", or "payload".
 *   - Where "${context}" represents the test context, such as "all_read" or "abstruse_signed".
 *   - Where "${at}" represents the index.
 *
 * @param set
 *   The name of the test set, representing the directory the the files are stored within.
 * @param context
 *   The test file directory set.
 * @param name
 *   The test file standard name.
 * @param at
 *   A number representing the specific content index position.
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__file_open__named_at(const f_string_t set, const f_string_t name, const f_string_t context, const uint16_t at);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _DATA__FL_fss_h
