/**
 * FLL - Level 0
 *
 * Project: Parse
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides basic string parse capabilities.
 */
#ifndef _F_parse_h
#define _F_parse_h

// Libc includes.
#include <string.h>

// FLL-0 includes.
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/type.h>
#include <fll/level_0/utf.h>

// FLL-0 compare includes.
#include <fll/level_0/parse/utf.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Seek the buffer location forward until the character (up to 4-byte wide) or EOL is reached.
 *
 * @param buffer
 *   The string to traverse.
 * @param seek_to_this
 *   A 1-width, 2-width, 3-width, or 4-width character representing a character to seek to.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_okay on success.
 *   F_okay_eol on success, but stopped at EOL.
 *   F_okay_eos on success, but stopped at end of buffer.
 *   F_okay_stop on success, but stopped at end of range.
 *   F_data_not on success, but there was no string data to seek.
 *   F_data_not_eos on success, but the range.start >= buffer.used.
 *   F_data_not_stop on success, but the range.start > range.stop.
 *
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_complete_not_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_char_to_character().
 *
 * @see f_utf_char_to_character()
 */
#ifndef _di_f_parse_dynamic_seek_line_to_utf_character_
  extern f_status_t f_parse_dynamic_seek_line_to_utf_character(const f_string_static_t buffer, const f_utf_char_t seek_to_this, f_string_range_t * const range);
#endif // _di_f_parse_dynamic_seek_line_to_utf_character_

/**
 * Increment buffer location until a graph character (including UTF-8) or an EOL is matched.
 *
 * @param buffer
 *   The string to traverse.
 * @param placeholder
 *   A single-width character representing a placeholder to ignore (may be NULL).
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *
 * @return
 *   F_okay on success.
 *   F_okay_eol on success, but stopped at EOL.
 *   F_okay_eos on success, but stopped at end of buffer.
 *   F_okay_stop on success, but stopped at end of range.
 *   F_data_not on success, but there was no string data to seek.
 *   F_data_not_eos on success, but the range.start >= buffer.used.
 *   F_data_not_stop on success, but the range.start > range.stop.
 *
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_complete_not_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_graph().
 *
 * @see f_utf_is_graph()
 */
#ifndef _di_f_parse_dynamic_seek_line_until_graph_
  extern f_status_t f_parse_dynamic_seek_line_until_graph(const f_string_static_t buffer, const uint8_t placeholder, f_string_range_t * const range);
#endif // _di_f_parse_dynamic_seek_line_until_graph_

/**
 * Increment buffer location until a non-graph character (including UTF-8) or an EOL is matched.
 *
 * @param buffer
 *   The string to traverse.
 * @param placeholder
 *   A single-width character representing a placeholder to ignore (may be NULL).
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *
 * @return
 *   F_okay on success.
 *   F_okay_eol on success, but stopped at EOL.
 *   F_okay_eos on success, but stopped at end of buffer.
 *   F_okay_stop on success, but stopped at end of range.
 *   F_data_not on success, but there was no string data to seek.
 *   F_data_not_eos on success, but the range.start >= buffer.used.
 *   F_data_not_stop on success, but the range.start > range.stop.
 *
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_complete_not_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_graph().
 *
 * @see f_utf_is_graph()
 */
#ifndef _di_f_parse_dynamic_seek_line_until_graph_non_
  extern f_status_t f_parse_dynamic_seek_line_until_graph_non(const f_string_static_t buffer, const uint8_t placeholder, f_string_range_t * const range);
#endif // _di_f_parse_dynamic_seek_line_until_graph_non_

/**
 * Seek the buffer location forward until the UTF-8 character (up to 4-byte wide) is reached.
 *
 * @param buffer
 *   The string to traverse.
 * @param seek_to_this
 *   A 1-width, 2-width, 3-width, or 4-width character representing a character to seek to.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_okay on success.
 *   F_okay_eol on success, but stopped at EOL.
 *   F_okay_eos on success, but stopped at end of buffer.
 *   F_okay_stop on success, but stopped at end of range.
 *   F_data_not on success, but there was no string data to seek.
 *   F_data_not_eos on success, but the range.start >= buffer.used.
 *   F_data_not_stop on success, but the range.start > range.stop.
 *
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_complete_not_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_char_to_character().
 *
 * @see f_utf_char_to_character()
 */
#ifndef _di_f_parse_dynamic_seek_to_utf_character_
  extern f_status_t f_parse_dynamic_seek_to_utf_character(const f_string_static_t buffer, const f_utf_char_t seek_to_this, f_string_range_t * const range);
#endif // _di_f_parse_dynamic_seek_to_utf_character_

/**
 * Identify whether or not the given string represents a single valid FLL Identifier and possibly save the FLL Identifier.
 *
 * This will always change the FLL Identifier used and type codes, if a FLL Identifier is provided.
 *
 * Whitespace may be before and after the FLL Identifier and will be ignored.
 * NULLs will be ignored.
 * Anything else will result in treating the character as a possible FLL Identifier.
 *
 * A valid FLL Identifier must terminate on either whitespace, EOL, or the stop point (length).
 *
 * The id.name might not be NULL terminated.
 * An id.name using all 64-bytes will not be NULL terminated.
 *
 * If a newline ("\n") is encountered, range->start will be set to 1 byte after the newline.
 *
 * @param buffer
 *   The string to process.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The caller must ensure that the stop point does not exceed the buffer size.
 *
 *   The range->start will be updated by this function.
 *   On error, the range->start may represent the last position looked at.
 *   On success, the range->start should be after the last valid position (for example for "fss-1234", the ast valid position would be the byte after the "4").
 *   Be aware that if a UTF-8 character exists at the end of the string but extends beyond the range stop, the stop position may be after the UTF-8 byte and not 1 byte after the stop point.
 * @param id
 *   (optional) The FLL Identifier found.
 *   Set to NULL to not use.
 *
 * @return
 *   F_data_not if length is 0.
 *   F_data_not_eos on success, but the range.start >= buffer.used.
 *   F_data_not_stop on success, but the range.start > range.stop.
 *   F_found if the buffer does represent a valid FLL Identifier.
 *   F_found_not if the buffer does not represent a valid FLL Identifier.
 *
 *   F_complete_not_utf (with error bit) if a character is an incomplete UTF-8 fragment.
 *   F_maybe (with error bit) if a character could be a whitespace but width is not long enough. (This is only returned for an otherwise valid FLL Identifier.)
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   F_parameter (with error bit) from: f_utf_is_combining().
 *   F_parameter (with error bit) from: f_utf_is_whitespace().
 *   F_parameter (with error bit) from: f_utf_is_word().
 *
 * @see isxdigit()
 *
 * @see f_utf_is_combining()
 * @see f_utf_is_whitespace()
 * @see f_utf_is_word()
 */
#ifndef _di_f_parse_dynamic_partial_fll_identify_
  extern f_status_t f_parse_dynamic_partial_fll_identify(const f_string_static_t buffer, f_string_range_t * const range, f_fll_id_t * const id);
#endif // _di_f_parse_dynamic_partial_fll_identify_

/**
 * Seek the string location forward until the character (up to 4-byte wide) or EOL is reached.
 *
 * @param string
 *   The string to traverse.
 * @param seek_to
 *   A 1-width, 2-width, 3-width, or 4-width character representing a character to seek to.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_okay on success.
 *   F_okay_eol on success, but stopped at EOL.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_char_to_character().
 *
 * @see f_utf_char_to_character()
 */
#ifndef _di_f_parse_seek_line_to_utf_character_
  extern f_status_t f_parse_seek_line_to_utf_character(const f_string_t string, const f_utf_char_t seek_to, f_string_range_t * const range);
#endif // _di_f_parse_seek_line_to_utf_character_

/**
 * Increment string location until a graph character (including UTF-8) or an EOL is matched.
 *
 * @param string
 *   The string to traverse.
 * @param placeholder
 *   A single-width character representing a placeholder to ignore (may be NULL).
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_okay on success.
 *   F_okay_eol on success, but stopped at EOL.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_graph().
 *
 * @see f_utf_is_graph()
 */
#ifndef _di_f_parse_seek_line_until_graph_
  extern f_status_t f_parse_seek_line_until_graph(const f_string_t string, const uint8_t placeholder, f_string_range_t * const range);
#endif // _di_f_parse_seek_line_until_graph_

/**
 * Increment string location until a non-graph character (including UTF-8) or an EOL is matched.
 *
 * @param string
 *   The string to traverse.
 * @param placeholder
 *   A single-width character representing a placeholder to ignore (may be NULL).
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_okay on success.
 *   F_okay_eol on success, but stopped at EOL.
 *   F_okay_stop on success, but stopped stop location.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   F_parameter (with error bit) from: f_utf_is_combining().
 *   F_parameter (with error bit) from: f_utf_is_whitespace().
 *
 * @see f_utf_is_combining()
 * @see f_utf_is_whitespace()
 */
#ifndef _di_f_parse_seek_line_until_graph_non_
  extern f_status_t f_parse_seek_line_until_graph_non(const f_string_t string, const uint8_t placeholder, f_string_range_t * const range);
#endif // _di_f_parse_seek_line_until_graph_non_

/**
 * Seek the string location forward until the UTF-8 character (up to 4-byte wide) is reached.
 *
 * @param string
 *   The string to traverse.
 * @param seek_to
 *   A 1-width, 2-width, 3-width, or 4-width character representing a character to seek to.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 *
 * @return
 *   F_okay on success.
 *   F_okay_stop on success, but stopped stop location.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_not (with error bit) if character is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_char_to_character().
 *
 * @see f_utf_char_to_character()
 */
#ifndef _di_f_parse_seek_to_utf_character_
  extern f_status_t f_parse_seek_to_utf_character(const f_string_t string, const f_utf_char_t seek_to, f_string_range_t * const range);
#endif // _di_f_parse_seek_to_utf_character_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_parse_h
