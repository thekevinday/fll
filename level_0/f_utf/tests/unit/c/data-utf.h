/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Data for the string project tests.
 */
#ifndef _DATA__F_utf_h
#define _DATA__F_utf_h

// Libc includes.
#include <arpa/inet.h>
#include <stdint.h>
#include <stdio.h>

// FLL-0 includes.
#include <fll/level_0/utf.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Open the "symbols" bytesequence file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/symbols-all.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__symbols(void);

/**
 * Simple line reader that converts the line into a character.
 *
 * This assumes the following:
 * - The line only contains base-10 digits.
 * - The line only contains at most 32 characters.
 *
 * This should handle converting the number between big and little endian as needed.
 *
 * The input file is expected to be in base-10 so that existing standarrd functions like atoll() can be easily used.
 *
 * @param file
 *   The file stream.
 * @param character
 *   The character read from the file at the current line in the stream.
 *
 * @return
 *   positive number on success where number represents bytes read.
 *   0 on success and end of file is reached.
 *   0 on failure.
 *
 * @see atoll()
 * @see getline()
 * @see htonl()
 */
extern uint8_t data__bytesequence_get_line(FILE * const file, f_utf_char_t * const character);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _DATA__F_utf_h
