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
 * Open the "alphabetic" bytesequence file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/alphabetic-all.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__alphabetic(void);

/**
 * Open the "combining" bytesequence file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/combining-all.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__combining(void);

/**
 * Open the "control" bytesequence file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/control-all.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__control(void);

/**
 * Open the "digit" bytesequence file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/digit-all.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__digit(void);

/**
 * Open the "emoji" bytesequence file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/emoji-all.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__emoji(void);

/**
 * Open the "numeric" bytesequence file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/numeric-all.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__numeric(void);

/**
 * Open the "phonetic" bytesequence file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/phonetic-all.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__phonetic(void);

/**
 * Open the "private use area" bytesequence file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/private-all.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__private(void);

/**
 * Open the "punctuation" bytesequence file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/punctuation-all.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__punctuation(void);

/**
 * Open the "subscript" bytesequence file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/subscript-all.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__subscript(void);

/**
 * Open the "superscript" bytesequence file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/superscript-all.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__superscript(void);

/**
 * Open the "surrogate" bytesequence file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/surrogate-all.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__surrogate(void);

/**
 * Open the "symbols" bytesequence file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/symbol-all.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__symbol(void);

/**
 * Open the "valid" bytesequence file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/valid-all.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__valid(void);

/**
 * Open the "whitespace" bytesequence file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/whitespace-all.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__whitespace(void);

/**
 * Open the "wide" bytesequence file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/wide-all.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__wide(void);

/**
 * Open the "word" bytesequence file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/word-all.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__word(void);

/**
 * Open the "zero_width" bytesequence file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/zero_width-all.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__zero_width(void);

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
