/**
 * FLL - Level 2
 *
 * Project: Print
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides print-related functionality.
 */
#ifndef _FLL_print_h
#define _FLL_print_h

// Libc includes.
#include <stdio.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/conversion.h>
#include <fll/level_0/print.h>

// FLL-1 includes.
#include <fll/level_1/print.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This is a variation of f_print() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print().
 *
 *   Errors (with error bit) from: f_print().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print()
 */
#ifndef _di_fll_print_
  extern f_status_t fll_print(const f_string_t string, const f_array_length_t length, FILE * const output);
#endif // _di_fll_print_

/**
 * This is a variation of f_print_character() that uses locking.
 *
 * @param character
 *   The character to verify as safe or not and then print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_character().
 *
 *   Errors (with error bit) from: f_print_character().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_character()
 */
#ifndef _di_fll_print_character_
  extern f_status_t fll_print_character(const char character, FILE * const output);
#endif // _di_fll_print_character_

/**
 * This is a variation of f_print_character_safely() that uses locking.
 *
 * @param character
 *   The character to verify as safe or not and then print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_character_safely().
 *
 *   Errors (with error bit) from: f_print_character_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_character_safely()
 */
#ifndef _di_fll_print_character_safely_
  extern f_status_t fll_print_character_safely(const char character, FILE * const output);
#endif // _di_fll_print_character_safely_

/**
 * This is a variation of f_print_dynamic() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_dynamic().
 *
 *   Errors (with error bit) from: f_print_dynamic().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_dynamic()
 */
#ifndef _di_fll_print_dynamic_
  extern f_status_t fll_print_dynamic(const f_string_static_t buffer, FILE * const output);
#endif // _di_fll_print_dynamic_

/**
 * This is a variation of f_print_dynamic_partial() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_dynamic_partial().
 *
 *   Errors (with error bit) from: f_print_dynamic_partial().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_dynamic_partial()
 */
#ifndef _di_fll_print_dynamic_partial_
  extern f_status_t fll_print_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, FILE * const output);
#endif // _di_fll_print_dynamic_partial_

/**
 * This is a variation of f_print_dynamic_partial_raw() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_dynamic_partial_raw().
 *
 *   Errors (with error bit) from: f_print_dynamic_partial_raw().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_dynamic_partial_raw()
 */
#ifndef _di_fll_print_dynamic_partial_raw_
  extern f_status_t fll_print_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, FILE * const output);
#endif // _di_fll_print_dynamic_partial_raw_

/**
 * This is a variation of f_print_dynamic_partial_raw_safely() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_dynamic_partial_raw_safely().
 *
 *   Errors (with error bit) from: f_print_dynamic_partial_raw_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_dynamic_partial_raw_safely()
 */
#ifndef _di_fll_print_dynamic_partial_raw_safely_
  extern f_status_t fll_print_dynamic_partial_raw_safely(const f_string_static_t buffer, const f_string_range_t range, FILE * const output);
#endif // _di_fll_print_dynamic_partial_raw_safely_

/**
 * This is a variation of f_print_dynamic_partial_safely() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_dynamic_partial_safely().
 *
 *   Errors (with error bit) from: f_print_dynamic_partial_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_dynamic_partial_safely()
 */
#ifndef _di_fll_print_dynamic_partial_safely_
  extern f_status_t fll_print_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, FILE * const output);
#endif // _di_fll_print_dynamic_partial_safely_

/**
 * This is a variation of f_print_dynamic_raw() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_dynamic_raw().
 *
 *   Errors (with error bit) from: f_print_dynamic_raw().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_dynamic_raw()
 */
#ifndef _di_fll_print_dynamic_raw_
  extern f_status_t fll_print_dynamic_raw(const f_string_static_t buffer, FILE * const output);
#endif // _di_fll_print_dynamic_raw_

/**
 * This is a variation of f_print_dynamic_raw_safely() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_dynamic_raw_safely().
 *
 *   Errors (with error bit) from: f_print_dynamic_raw_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_dynamic_raw_safely()
 */
#ifndef _di_fll_print_dynamic_raw_safely_
  extern f_status_t fll_print_dynamic_raw_safely(const f_string_static_t buffer, FILE * const output);
#endif // _di_fll_print_dynamic_raw_safely_

/**
 * This is a variation of f_print_dynamic_safely() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_dynamic_safely().
 *
 *   Errors (with error bit) from: f_print_dynamic_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_dynamic_safely()
 */
#ifndef _di_fll_print_dynamic_safely_
  extern f_status_t fll_print_dynamic_safely(const f_string_static_t buffer, FILE * const output);
#endif // _di_fll_print_dynamic_safely_

/**
 * This is a variation of f_print_except() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except().
 *
 *   Errors (with error bit) from: f_print_except().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except()
 */
#ifndef _di_fll_print_except_
  extern f_status_t fll_print_except(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_except_

/**
 * This is a variation of f_print_except_dynamic() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_dynamic().
 *
 *   Errors (with error bit) from: f_print_except_dynamic().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_dynamic()
 */
#ifndef _di_fll_print_except_dynamic_
  extern f_status_t fll_print_except_dynamic(const f_string_static_t buffer, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_except_dynamic_

/**
 * This is a variation of f_print_except_dynamic_partial() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_dynamic_partial().
 *
 *   Errors (with error bit) from: f_print_except_dynamic_partial().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_dynamic_partial()
 */
#ifndef _di_fll_print_except_dynamic_partial_
  extern f_status_t fll_print_except_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_except_dynamic_partial_

/**
 * This is a variation of f_print_except_dynamic_partial_raw() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_dynamic_partial_raw().
 *
 *   Errors (with error bit) from: f_print_except_dynamic_partial_raw().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_dynamic_partial_raw()
 */
#ifndef _di_fll_print_except_dynamic_partial_raw_
  extern f_status_t fll_print_except_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_except_dynamic_partial_raw_

/**
 * This is a variation of f_print_except_dynamic_partial_raw_safely() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_dynamic_partial_raw_safely().
 *
 *   Errors (with error bit) from: f_print_except_dynamic_partial_raw_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_dynamic_partial_raw_safely()
 */
#ifndef _di_fll_print_except_dynamic_partial_raw_safely_
  extern f_status_t fll_print_except_dynamic_partial_raw_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_except_dynamic_partial_raw_safely_

/**
 * This is a variation of f_print_except_dynamic_partial_safely() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_dynamic_partial_safely().
 *
 *   Errors (with error bit) from: f_print_except_dynamic_partial_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_dynamic_partial_safely()
 */
#ifndef _di_fll_print_except_dynamic_partial_safely_
  extern f_status_t fll_print_except_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_except_dynamic_partial_safely_

/**
 * This is a variation of f_print_except_dynamic_raw() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_dynamic_raw().
 *
 *   Errors (with error bit) from: f_print_except_dynamic_raw().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_dynamic_raw()
 */
#ifndef _di_fll_print_except_dynamic_raw_
  extern f_status_t fll_print_except_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_except_dynamic_raw_

/**
 * This is a variation of f_print_except_dynamic_raw_safely() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_dynamic_raw_safely().
 *
 *   Errors (with error bit) from: f_print_except_dynamic_raw_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_dynamic_raw_safely()
 */
#ifndef _di_fll_print_except_dynamic_raw_safely_
  extern f_status_t fll_print_except_dynamic_raw_safely(const f_string_static_t buffer, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_except_dynamic_raw_safely_

/**
 * This is a variation of f_print_except_dynamic_safely() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_dynamic_safely().
 *
 *   Errors (with error bit) from: f_print_except_dynamic_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_dynamic_safely()
 */
#ifndef _di_fll_print_except_dynamic_safely_
  extern f_status_t fll_print_except_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_except_dynamic_safely_

/**
 * This is a variation of f_print_except_in() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_in().
 *
 *   Errors (with error bit) from: f_print_except_in().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_in()
 */
#ifndef _di_fll_print_except_in_
  extern f_status_t fll_print_except_in(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_except_in_

/**
 * This is a variation of f_print_except_in_raw() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_in_raw().
 *
 *   Errors (with error bit) from: f_print_except_in_raw().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_in_raw()
 */
#ifndef _di_fll_print_except_in_raw_
  extern f_status_t fll_print_except_in_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_except_in_raw_

/**
 * This is a variation of f_print_except_in_raw_safely() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_in_raw_safely().
 *
 *   Errors (with error bit) from: f_print_except_in_raw_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_in_raw_safely()
 */
#ifndef _di_fll_print_except_in_raw_safely_
  extern f_status_t fll_print_except_in_raw_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_except_in_raw_safely_

/**
 * This is a variation of f_print_except_in_safely() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_in_safely().
 *
 *   Errors (with error bit) from: f_print_except_in_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_in_safely()
 */
#ifndef _di_fll_print_except_in_safely_
  extern f_status_t fll_print_except_in_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_except_in_safely_

/**
 * This is a variation of f_print_except_in_dynamic() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_in_dynamic().
 *
 *   Errors (with error bit) from: f_print_except_in_dynamic().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_in_dynamic()
 */
#ifndef _di_fll_print_except_in_dynamic_
  extern f_status_t fll_print_except_in_dynamic(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_except_in_dynamic_

/**
 * This is a variation of f_print_except_in_dynamic_partial() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_in_dynamic_partial().
 *
 *   Errors (with error bit) from: f_print_except_in_dynamic_partial().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_in_dynamic_partial()
 */
#ifndef _di_fll_print_except_in_dynamic_partial_
  extern f_status_t fll_print_except_in_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_except_in_dynamic_partial_

/**
 * This is a variation of f_print_except_in_dynamic_partial_raw() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_in_dynamic_partial_raw().
 *
 *   Errors (with error bit) from: f_print_except_in_dynamic_partial_raw().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_in_dynamic_partial_raw()
 */
#ifndef _di_fll_print_except_in_dynamic_partial_raw_
  extern f_status_t fll_print_except_in_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_except_in_dynamic_partial_raw_

/**
 * This is a variation of f_print_except_in_dynamic_partial_raw_safely() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_in_dynamic_partial_raw_safely().
 *
 *   Errors (with error bit) from: f_print_except_in_dynamic_partial_raw_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_in_dynamic_partial_raw_safely()
 */
#ifndef _di_fll_print_except_in_dynamic_partial_raw_safely_
  extern f_status_t fll_print_except_in_dynamic_partial_raw_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_except_in_dynamic_partial_raw_safely_

/**
 * This is a variation of f_print_except_in_dynamic_partial_safely() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_in_dynamic_partial_safely().
 *
 *   Errors (with error bit) from: f_print_except_in_dynamic_partial_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_in_dynamic_partial_safely()
 */
#ifndef _di_fll_print_except_in_dynamic_partial_safely_
  extern f_status_t fll_print_except_in_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_except_in_dynamic_partial_safely_

/**
 * This is a variation of f_print_except_in_dynamic_raw() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_in_dynamic_raw().
 *
 *   Errors (with error bit) from: f_print_except_in_dynamic_raw().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_in_dynamic_raw()
 */
#ifndef _di_fll_print_except_in_dynamic_raw_
  extern f_status_t fll_print_except_in_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_except_in_dynamic_raw_

/**
 * This is a variation of f_print_except_in_dynamic_raw_safely() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_in_dynamic_raw_safely().
 *
 *   Errors (with error bit) from: f_print_except_in_dynamic_raw_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_in_dynamic_raw_safely()
 */
#ifndef _di_fll_print_except_in_dynamic_raw_safely_
  extern f_status_t fll_print_except_in_dynamic_raw_safely(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_except_in_dynamic_raw_safely_

/**
 * This is a variation of f_print_except_in_dynamic_safely() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_in_dynamic_safely().
 *
 *   Errors (with error bit) from: f_print_except_in_dynamic_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_in_dynamic_safely()
 */
#ifndef _di_fll_print_except_in_dynamic_safely_
  extern f_status_t fll_print_except_in_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_except_in_dynamic_safely_

/**
 * This is a variation of f_print_except_raw() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_raw().
 *
 *   Errors (with error bit) from: f_print_except_raw().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_raw()
 */
#ifndef _di_fll_print_except_raw_
  extern f_status_t fll_print_except_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_except_raw_

/**
 * This is a variation of f_print_except_raw_safely() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_raw_safely().
 *
 *   Errors (with error bit) from: f_print_except_raw_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_raw_safely()
 */
#ifndef _di_fll_print_except_raw_safely_
  extern f_status_t fll_print_except_raw_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_except_raw_safely_

/**
 * This is a variation of f_print_except_safely() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_safely().
 *
 *   Errors (with error bit) from: f_print_except_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_safely()
 */
#ifndef _di_fll_print_except_safely_
  extern f_status_t fll_print_except_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_except_safely_

/**
 * This is a variation of fl_print_format() that uses locking.
 *
 * @param string
 *   The formatted string to process and output.
 *   This is a NULL terminated string.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 * @param ...
 *   Additional arguments relating to the string.
 *
 * @return
 *   Success from: fl_print_format().
 *
 *   Errors (with error bit) from: fl_print_format().
 *
 * @see flockfile()
 * @see funlockfile()
 * @see va_start()
 * @see va_end()
 *
 * @see fl_print_format()
 */
#ifndef _di_fll_print_format_
  extern f_status_t fll_print_format(const f_string_t string, FILE * const output, ...);
#endif // _di_fll_print_format_

/**
 * This is a variation of fl_print_format_convert() that uses locking.
 *
 * @param current
 *   The current character position within the string.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 * @param ap
 *   The variable arguments list.
 * @param status
 *   The status is stored here rather then via the return.
 *
 * @return
 *   Result from: fl_print_format_convert().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_format_convert()
 */
#ifndef _di_fll_print_format_convert_
  extern f_string_t fll_print_format_convert(const f_string_t current, FILE * const output, va_list *ap, f_status_t *status);
#endif // _di_fll_print_format_convert_

/**
 * This is a variation of f_print_raw() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_raw().
 *
 *   Errors (with error bit) from: f_print_raw().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_raw()
 */
#ifndef _di_fll_print_raw_
  extern f_status_t fll_print_raw(const f_string_t string, const f_array_length_t length, FILE * const output);
#endif // _di_fll_print_raw_

/**
 * This is a variation of f_print_raw_safely() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_raw_safely().
 *
 *   Errors (with error bit) from: f_print_raw_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_raw_safely()
 */
#ifndef _di_fll_print_raw_safely_
  extern f_status_t fll_print_raw_safely(const f_string_t string, const f_array_length_t length, FILE * const output);
#endif // _di_fll_print_raw_safely_

/**
 * This is a variation of f_print_raw_terminated() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_raw_terminated().
 *
 *   Errors (with error bit) from: f_print_raw_terminated().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_raw_terminated()
 */
#ifndef _di_fll_print_raw_terminated_
  extern f_status_t fll_print_raw_terminated(const f_string_t string, FILE * const output);
#endif // _di_fll_print_raw_terminated_

/**
 * This is a variation of f_print_safely() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_safely().
 *
 *   Errors (with error bit) from: f_print_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_safely()
 */
#ifndef _di_fll_print_safely_
  extern f_status_t fll_print_safely(const f_string_t string, const f_array_length_t length, FILE * const output);
#endif // _di_fll_print_safely_

/**
 * This is a variation of f_print_safely_terminated() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_safely_terminated().
 *
 *   Errors (with error bit) from: f_print_safely_terminated().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_safely_terminated()
 */
#ifndef _di_fll_print_safely_terminated_
  extern f_status_t fll_print_safely_terminated(const f_string_t string, FILE * const output);
#endif // _di_fll_print_safely_terminated_

/**
 * This is a variation of fl_print_string_va() that uses locking.
 *
 * @param string
 *   The formatted string to process and output.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 * @param ap
 *   The variable list.
 *   The va_start(ap, string) and va_end(ap) is required to be called outside this function.
 *
 * @return
 *   Success from: fl_print_string_va().
 *
 *   Errors (with error bit) from: fl_print_string_va().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_string_va()
 */
#ifndef _di_fll_print_string_va_
  extern f_status_t fll_print_string_va(const f_string_t string, FILE * const output, va_list *ap);
#endif // _di_fll_print_string_va_

/**
 * This is a variation of f_print_terminated() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_terminated().
 *
 *   Errors (with error bit) from: f_print_terminated().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_terminated()
 */
#ifndef _di_fll_print_terminated_
  extern f_status_t fll_print_terminated(const f_string_t string, FILE * const output);
#endif // _di_fll_print_terminated_

/**
 * This is a variation of fl_print_trim() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim().
 *
 *   Errors (with error bit) from: fl_print_trim().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_dynamic_partial()
 */
#ifndef _di_fll_print_trim_
  extern f_status_t fll_print_trim(const f_string_t string, const f_array_length_t length, FILE * const output);
#endif // _di_fll_print_trim_

/**
 * This is a variation of fl_print_trim_raw() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_raw().
 *
 *   Errors (with error bit) from: fl_print_trim_raw().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_raw()
 */
#ifndef _di_fll_print_trim_raw_
  extern f_status_t fll_print_trim_raw(const f_string_t string, const f_array_length_t length, FILE * const output);
#endif // _di_fll_print_trim_raw_

/**
 * This is a variation of fl_print_trim_raw_safely() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_raw_safely().
 *
 *   Errors (with error bit) from: fl_print_trim_raw_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_raw_safely()
 */
#ifndef _di_fll_print_trim_raw_safely_
  extern f_status_t fll_print_trim_raw_safely(const f_string_t string, const f_array_length_t length, FILE * const output);
#endif // _di_fll_print_trim_raw_safely_

/**
 * This is a variation of fl_print_trim_safely() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param length
 *   The total number of characters to print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_safely().
 *
 *   Errors (with error bit) from: fl_print_trim_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_safely()
 */
#ifndef _di_fll_print_trim_safely_
  extern f_status_t fll_print_trim_safely(const f_string_t string, const f_array_length_t length, FILE * const output);
#endif // _di_fll_print_trim_safely_

/**
 * This is a variation of fl_print_trim_dynamic() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_dynamic().
 *
 *   Errors (with error bit) from: fl_print_trim_dynamic().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_dynamic()
 */
#ifndef _di_fll_print_trim_dynamic_
  extern f_status_t fll_print_trim_dynamic(const f_string_static_t buffer, FILE * const output);
#endif // _di_fll_print_trim_dynamic_

/**
 * This is a variation of fl_print_trim_dynamic_raw() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_dynamic_raw().
 *
 *   Errors (with error bit) from: fl_print_trim_dynamic_raw().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_dynamic_raw()
 */
#ifndef _di_fll_print_trim_dynamic_raw_
  extern f_status_t fll_print_trim_dynamic_raw(const f_string_static_t buffer, FILE * const output);
#endif // _di_fll_print_trim_dynamic_raw_

/**
 * This is a variation of fl_print_trim_dynamic_raw_safely() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_dynamic_raw_safely().
 *
 *   Errors (with error bit) from: fl_print_trim_dynamic_raw_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_dynamic_raw_safely()
 */
#ifndef _di_fll_print_trim_dynamic_raw_safely_
  extern f_status_t fll_print_trim_dynamic_raw_safely(const f_string_static_t buffer, FILE * const output);
#endif // _di_fll_print_trim_dynamic_raw_safely_

/**
 * This is a variation of fl_print_trim_dynamic_safely() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_dynamic_safely().
 *
 *   Errors (with error bit) from: fl_print_trim_dynamic_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_dynamic_safely()
 */
#ifndef _di_fll_print_trim_dynamic_safely_
  extern f_status_t fll_print_trim_dynamic_safely(const f_string_static_t buffer, FILE * const output);
#endif // _di_fll_print_trim_dynamic_safely_

/**
 * This is a variation of fl_print_trim_dynamic_partial() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_dynamic_partial().
 *
 *   Errors (with error bit) from: fl_print_trim_dynamic_partial().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_dynamic_partial()
 */
#ifndef _di_fll_print_trim_dynamic_partial_
  extern f_status_t fll_print_trim_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, FILE * const output);
#endif // _di_fll_print_trim_dynamic_partial_

/**
 * This is a variation of fl_print_trim_dynamic_partial_raw() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_dynamic_partial_raw().
 *
 *   Errors (with error bit) from: fl_print_trim_dynamic_partial_raw().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_dynamic_partial_raw()
 */
#ifndef _di_fll_print_trim_dynamic_partial_raw_
  extern f_status_t fll_print_trim_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, FILE * const output);
#endif // _di_fll_print_trim_dynamic_partial_raw_

/**
 * This is a variation of f_print_except_dynamic_partial() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_dynamic_partial().
 *
 *   Errors (with error bit) from: f_print_except_dynamic_partial().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_dynamic_partial()
 */
#ifndef _di_fll_print_trim_dynamic_partial_raw_safely_
  extern f_status_t fll_print_trim_dynamic_partial_raw_safely(const f_string_static_t buffer, const f_string_range_t range, FILE * const output);
#endif // _di_fll_print_trim_dynamic_partial_raw_safely_

/**
 * This is a variation of f_print_except_dynamic_partial() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: f_print_except_dynamic_partial().
 *
 *   Errors (with error bit) from: f_print_except_dynamic_partial().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_dynamic_partial()
 */
#ifndef _di_fll_print_trim_dynamic_partial_safely_
  extern f_status_t fll_print_trim_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, FILE * const output);
#endif // _di_fll_print_trim_dynamic_partial_safely_

/**
 * This is a variation of fl_print_trim_except() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except().
 *
 *   Errors (with error bit) from: fl_print_trim_except().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_except()
 */
#ifndef _di_fll_print_trim_except_
  extern f_status_t fll_print_trim_except(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_trim_except_

/**
 * This is a variation of fl_print_trim_except_raw() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except_raw().
 *
 *   Errors (with error bit) from: fl_print_trim_except_raw().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_except_raw()
 */
#ifndef _di_fll_print_trim_except_raw_
  extern f_status_t fll_print_trim_except_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_trim_except_raw_

/**
 * This is a variation of fl_print_trim_except_raw_safely() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except_raw_safely().
 *
 *   Errors (with error bit) from: fl_print_trim_except_raw_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_except_raw_safely()
 */
#ifndef _di_fll_print_trim_except_raw_safely_
  extern f_status_t fll_print_trim_except_raw_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_trim_except_raw_safely_

/**
 * This is a variation of fl_print_trim_except_safely() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except_safely().
 *
 *   Errors (with error bit) from: fl_print_trim_except_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_except_safely()
 */
#ifndef _di_fll_print_trim_except_safely_
  extern f_status_t fll_print_trim_except_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_trim_except_safely_

/**
 * This is a variation of fl_print_trim_except_dynamic() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except_dynamic().
 *
 *   Errors (with error bit) from: fl_print_trim_except_dynamic().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_except_dynamic()
 */
#ifndef _di_fll_print_trim_except_dynamic_
  extern f_status_t fll_print_trim_except_dynamic(const f_string_static_t buffer, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_trim_except_dynamic_

/**
 * This is a variation of fl_print_trim_except_dynamic_raw() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except_dynamic_raw().
 *
 *   Errors (with error bit) from: fl_print_trim_except_dynamic_raw().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_except_dynamic_raw()
 */
#ifndef _di_fll_print_trim_except_dynamic_raw_
  extern f_status_t fll_print_trim_except_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_trim_except_dynamic_raw_

/**
 * This is a variation of fl_print_trim_except_dynamic_raw_safely() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except_dynamic_raw_safely().
 *
 *   Errors (with error bit) from: fl_print_trim_except_dynamic_raw_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_except_dynamic_raw_safely()
 */
#ifndef _di_fll_print_trim_except_dynamic_raw_safely_
  extern f_status_t fll_print_trim_except_dynamic_raw_safely(const f_string_static_t buffer, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_trim_except_dynamic_raw_safely_

/**
 * This is a variation of fl_print_trim_except_dynamic_safely() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except_dynamic_safely().
 *
 *   Errors (with error bit) from: fl_print_trim_except_dynamic_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_except_dynamic_safely()
 */
#ifndef _di_fll_print_trim_except_dynamic_safely_
  extern f_status_t fll_print_trim_except_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_trim_except_dynamic_safely_

/**
 * This is a variation of fl_print_trim_except_in() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except_in().
 *
 *   Errors (with error bit) from: fl_print_trim_except_in().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_except_in()
 */
#ifndef _di_fll_print_trim_except_in_
  extern f_status_t fll_print_trim_except_in(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_trim_except_in_

/**
 * This is a variation of fl_print_trim_except_in_raw() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except_in_raw().
 *
 *   Errors (with error bit) from: fl_print_trim_except_in_raw().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_except_in_raw()
 */
#ifndef _di_fll_print_trim_except_in_raw_
  extern f_status_t fll_print_trim_except_in_raw(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_trim_except_in_raw_

/**
 * This is a variation of fl_print_trim_except_in_raw_safely() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except_in_raw_safely().
 *
 *   Errors (with error bit) from: fl_print_trim_except_in_raw_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_except_in_raw_safely()
 */
#ifndef _di_fll_print_trim_except_in_raw_safely_
  extern f_status_t fll_print_trim_except_in_raw_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_trim_except_in_raw_safely_

/**
 * This is a variation of fl_print_trim_except_in_safely() that uses locking.
 *
 * @param string
 *   The string to output.
 * @param offset
 *   The inclusive start point to start printing.
 * @param length
 *   The total number of characters to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except_in_safely().
 *
 *   Errors (with error bit) from: fl_print_trim_except_in_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_except_in_safely()
 */
#ifndef _di_fll_print_trim_except_in_safely_
  extern f_status_t fll_print_trim_except_in_safely(const f_string_t string, const f_array_length_t offset, const f_array_length_t length, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_trim_except_in_safely_

/**
 * This is a variation of fl_print_trim_except_in_dynamic() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except_in_dynamic().
 *
 *   Errors (with error bit) from: fl_print_trim_except_in_dynamic().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_except_in_dynamic()
 */
#ifndef _di_fll_print_trim_except_in_dynamic_
  extern f_status_t fll_print_trim_except_in_dynamic(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_trim_except_in_dynamic_

/**
 * This is a variation of fl_print_trim_except_in_dynamic_raw() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except_in_dynamic_raw().
 *
 *   Errors (with error bit) from: fl_print_trim_except_in_dynamic_raw().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_except_in_dynamic_raw()
 */
#ifndef _di_fll_print_trim_except_in_dynamic_raw_
  extern f_status_t fll_print_trim_except_in_dynamic_raw(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_trim_except_in_dynamic_raw_

/**
 * This is a variation of fl_print_trim_except_in_dynamic_raw_safely() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except_in_dynamic_raw_safely().
 *
 *   Errors (with error bit) from: fl_print_trim_except_in_dynamic_raw_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_except_in_dynamic_raw_safely()
 */
#ifndef _di_fll_print_trim_except_in_dynamic_raw_safely_
  extern f_status_t fll_print_trim_except_in_dynamic_raw_safely(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_trim_except_in_dynamic_raw_safely_

/**
 * This is a variation of fl_print_trim_except_in_dynamic_safely() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except_in_dynamic_safely().
 *
 *   Errors (with error bit) from: fl_print_trim_except_in_dynamic_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_except_in_dynamic_safely()
 */
#ifndef _di_fll_print_trim_except_in_dynamic_safely_
  extern f_status_t fll_print_trim_except_in_dynamic_safely(const f_string_static_t buffer, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_trim_except_in_dynamic_safely_

/**
 * This is a variation of fl_print_trim_except_in_dynamic_partial() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except_in_dynamic_partial().
 *
 *   Errors (with error bit) from: fl_print_trim_except_in_dynamic_partial().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_except_in_dynamic_partial()
 */
#ifndef _di_fll_print_trim_except_in_dynamic_partial_
  extern f_status_t fll_print_trim_except_in_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_trim_except_in_dynamic_partial_

/**
 * This is a variation of fl_print_trim_except_in_dynamic_partial_raw() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except_in_dynamic_partial_raw().
 *
 *   Errors (with error bit) from: fl_print_trim_except_in_dynamic_partial_raw().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_dynamic_partial()
 */
#ifndef _di_fll_print_trim_except_in_dynamic_partial_raw_
  extern f_status_t fll_print_trim_except_in_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_trim_except_in_dynamic_partial_raw_

/**
 * This is a variation of fl_print_trim_except_in_dynamic_partial_raw_safely() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except_in_dynamic_partial_raw_safely().
 *
 *   Errors (with error bit) from: fl_print_trim_except_in_dynamic_partial_raw_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_dynamic_partial()
 */
#ifndef _di_fll_print_trim_except_in_dynamic_partial_raw_safely_
  extern f_status_t fll_print_trim_except_in_dynamic_partial_raw_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_trim_except_in_dynamic_partial_raw_safely_

/**
 * This is a variation of fl_print_trim_except_in_dynamic_partial_safely() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except_at
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param except_in
 *   An array of ranges within the string to not print.
 *   The array of ranges is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except_in_dynamic_partial_safely().
 *
 *   Errors (with error bit) from: fl_print_trim_except_in_dynamic_partial_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see f_print_except_dynamic_partial()
 */
#ifndef _di_fll_print_trim_except_in_dynamic_partial_safely_
  extern f_status_t fll_print_trim_except_in_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except_at, const f_string_ranges_t except_in, FILE * const output);
#endif // _di_fll_print_trim_except_in_dynamic_partial_safely_

/**
 * This is a variation of fl_print_trim_except_dynamic_partial() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except_dynamic_partial().
 *
 *   Errors (with error bit) from: fl_print_trim_except_dynamic_partial().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_except_dynamic_partial()
 */
#ifndef _di_fll_print_trim_except_dynamic_partial_
  extern f_status_t fll_print_trim_except_dynamic_partial(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_trim_except_dynamic_partial_

/**
 * This is a variation of fl_print_trim_except_dynamic_partial_raw() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except_dynamic_partial_raw().
 *
 *   Errors (with error bit) from: fl_print_trim_except_dynamic_partial_raw().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_except_dynamic_partial_raw()
 */
#ifndef _di_fll_print_trim_except_dynamic_partial_raw_
  extern f_status_t fll_print_trim_except_dynamic_partial_raw(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_trim_except_dynamic_partial_raw_

/**
 * This is a variation of fl_print_trim_except_dynamic_partial_raw_safely() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except_dynamic_partial_raw_safely().
 *
 *   Errors (with error bit) from: fl_print_trim_except_dynamic_partial_raw_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_except_dynamic_partial_raw_safely()
 */
#ifndef _di_fll_print_trim_except_dynamic_partial_raw_safely_
  extern f_status_t fll_print_trim_except_dynamic_partial_raw_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_trim_except_dynamic_partial_raw_safely_

/**
 * This is a variation of fl_print_trim_except_dynamic_partial_safely() that uses locking.
 *
 * @param buffer
 *   The string to output.
 * @param range
 *   The range within the provided string to print.
 * @param except
 *   An array of locations within the given string to not print.
 *   The array of locations is required/assumed to be in linear order.
 * @param output
 *   The file stream to output to, including standard streams such as stdout and stderr.
 *
 * @return
 *   Success from: fl_print_trim_except_dynamic_partial_safely().
 *
 *   Errors (with error bit) from: fl_print_trim_except_dynamic_partial_safely().
 *
 * @see flockfile()
 * @see funlockfile()
 *
 * @see fl_print_trim_except_dynamic_partial_safely()
 */
#ifndef _di_fll_print_trim_except_dynamic_partial_safely_
  extern f_status_t fll_print_trim_except_dynamic_partial_safely(const f_string_static_t buffer, const f_string_range_t range, const f_array_lengths_t except, FILE * const output);
#endif // _di_fll_print_trim_except_dynamic_partial_safely_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_print_h
