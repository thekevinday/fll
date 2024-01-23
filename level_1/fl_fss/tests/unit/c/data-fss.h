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
 * Open the "FSS basic" contents file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/contents/basic-all_read.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__contents_file_open__basic_all_read(void);

/**
 * Open the "FSS basic" objects file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/objects/basic-all_read.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__objects_file_open__basic_all_read(void);

/**
 * Open the "fss basic" strings file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/strings/basic-all_read.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__strings_file_open__basic_all_read(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _DATA__FL_fss_h
