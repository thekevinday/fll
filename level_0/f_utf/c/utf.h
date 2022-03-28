/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides UTF-8 capabilities.
 *
 * Identifiers:
 *   - UTF_8-1: 1000 0000
 *   - UTF_8-2: 1100 0000
 *   - UTF_8-3: 1110 0000
 *   - UTF_8-4: 1111 0000
 *
 * Values:
 *   - UTF_8-1: 1011 1111
 *   - UTF_8-2: 1101 1111
 *   - UTF_8-3: 1110 1111
 *   - UTF_8-4: 1111 0111
 *
 * Identifier Structure:
 *   - UTF_8-1: 1000 0000
 *   - UTF_8-2: 1100 0000 1000 0000
 *   - UTF_8-3: 1110 0000 1000 0000 1000 0000
 *   - UTF_8-4: 1111 0000 1000 0000 1000 0000 1000 0000
 *
 * Value Structure:
 *   - UTF_8-1: 10xx xxxx
 *   - UTF_8-2: 110x xxxx, 10xx xxxx
 *   - UTF_8-3: 1110 xxxx, 10xx xxxx, 10xx xxxx
 *   - UTF_8-4: 1111 0xxx, 10xx xxxx, 10xx xxxx, 10xx xxxx
 */
#ifndef _F_utf_h
#define _F_utf_h

// Libc includes.
#include <endian.h>
#include <ctype.h>
#include <string.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>

// FLL-0 utf includes.
#include <fll/level_0/utf/common.h>
#include <fll/level_0/utf/convert.h>
#include <fll/level_0/utf/dynamic.h>
#include <fll/level_0/utf/is.h>
#include <fll/level_0/utf/is_character.h>
#include <fll/level_0/utf/map.h>
#include <fll/level_0/utf/string.h>
#include <fll/level_0/utf/triple.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Continue to the previous character, based on step and character width.
 *
 * For navigating a range within the given buffer by a specific number of characters that could be of any width allowed by UTF-8.
 *
 * The start position must be at the start of a valid UTF-8 block.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The start and stop positions to be incremented.
 *   The start position will be incremented by step.
 * @param step
 *   The number of steps to decrement the start position.
 *   The steps refer to characters and not integers.
 *   Essentially this number is considered against the width of every character found.
 *   (For ASCII each step would be sizeof(uint8_t), which is 1.
 *   (For UTF-8 character of width 3, each step would be (3 * sizeof(uint8_t)).
 *
 * @return
 *   F_none on success.
 *   F_none_stop if the stop range is reached before all steps are completed.
 *   F_none_eos if the end of buffer is reached before all steps are completed.
 *   F_data_not if buffer is empty or out of range.
 *
 *   F_complete_not_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_buffer_decrement_
  extern f_status_t f_utf_buffer_decrement(const f_string_static_t buffer, f_string_range_t *range, const f_array_length_t step);
#endif // _di_f_utf_buffer_decrement_

/**
 * Continue to the next character, based on step and character width.
 *
 * For navigating a range within the given buffer by a specific number of characters that could be of any width allowed by UTF-8.
 *
 * The start position must be at the start of a valid UTF-8 block.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   The start and stop positions to be incremented.
 *   The start position will be incremented by step.
 * @param step
 *   The number of steps to increment the start position.
 *   The steps refer to characters and not integers.
 *   Essentially this number is considered against the width of every character found.
 *   (For ASCII each step would be sizeof(uint8_t), which is 1.
 *   (For UTF-8 character of width 3, each step would be (3 * sizeof(uint8_t)).
 *
 * @return
 *   F_none on success.
 *   F_none_stop if the stop range is reached before all steps are completed.
 *   F_none_eos if the end of buffer is reached before all steps are completed.
 *   F_data_not if buffer is empty or out of range.
 *
 *   F_complete_not_utf_stop (with error bit) if the stop range is reached before the complete UTF-8 character can be processed.
 *   F_complete_not_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_utf_buffer_increment_
  extern f_status_t f_utf_buffer_increment(const f_string_static_t buffer, f_string_range_t *range, const f_array_length_t step);
#endif // _di_f_utf_buffer_increment_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_utf_h
