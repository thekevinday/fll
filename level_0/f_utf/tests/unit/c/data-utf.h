/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.7
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
 * Open the "whitespace_modifier" bytesequence file, the "modifier" variation.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/whitespace-modifier.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__whitespace__modifier(void);

/**
 * Open the "whitespace_other" bytesequence file, the "other" variation.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/whitespace-other.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__whitespace__other(void);

/**
 * Open the "whitespace_zero_width" bytesequence file, the "zero_width" variation.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/whitespace-zero_width.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__whitespace__zero_width(void);

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
 * Open the "word_dash" bytesequence file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/word_dash-all.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__word_dash(void);

/**
 * Open the "word_dash_plus" bytesequence file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/word_dash_plus-all.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__word_dash_plus(void);

/**
 * Open the "word" bytesequence file, the "lax" variation.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/word-lax.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__word__lax(void);

/**
 * Open the "word_dash" bytesequence file, the "lax" variation.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/word_dash-lax.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__word_dash__lax(void);

/**
 * Open the "word_dash_plus" bytesequence file, the "lax" variation.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/bytesequences/word_dash_plus-lax.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__bytesequence_file_open__word_dash_plus__lax(void);

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
 * The input file is expected to be in base-10 so that existing standard functions like atoll() can be easily used.
 *
 * @param file
 *   The file stream.
 * @param character
 *   The character read from the file at the current line in the stream.
 *
 * @return
 *   positive number on success where number represents bytes read.
 *   0 on success and end of file is reached.
 *   -1 on failure.
 *
 * @see atoll()
 * @see getline()
 */
extern ssize_t data__bytesequence_get_line(FILE * const file, f_utf_char_t * const character);

/**
 * Open the "decimal_number" values file.
 *
 * This assumes the following:
 * - The file path is relative to the current working directory (tests are run from project root).
 * - The file path is "data/tests/values/digit-all.txt".
 *
 * @return
 *   Non-zero on success.
 *   0 on failure.
 *
 * @see fopen()
 */
extern FILE *data__value_file_open__digit(void);

/**
 * Simple line reader that converts the line into a long long.
 *
 * This assumes the following:
 * - The line only contains base-10 digits as ASCII characters.
 *
 * The input file is expected to be in base-10 so that existing standard functions like atoll() can be easily used.
 *
 * @param file
 *   The file stream.
 * @param value
 *   The number read from the file at the current line in the stream.
 *
 * @return
 *   positive number on success where number represents bytes read.
 *   0 on success and end of file is reached.
 *   -1 on failure.
 *
 * @see atoll()
 * @see getline()
 */
extern ssize_t data__value_get_line_long_long(FILE * const file, uint64_t * const value);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _DATA__F_utf_h
