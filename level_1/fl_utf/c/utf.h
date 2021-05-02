/**
 * FLL - Level 1
 *
 * Project: Utf
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides UTF-8 character manipulation and processing capabilities.
 *
 * UTF-8 is handled within these functions via padded string characters (f_utf_string_t).
 * Unlike f_string_t, these f_utf_string_t base functions force padding of ASCII or UTF-8 characters.
 * With f_utf_string_t, a 1-byte wide ASCII character is stored as 4 bytes and a 4-byte wide UTF-8 character is stored as 4 bytes.
 *
 * This simplifies traversing the strings at the cost of size vs f_string_t.
 *
 * Because of the set width, it is generally safe to ignore invalid UTF-8 sequences.
 * Invalid UTF-8 will be generally ignored here, where reasonably possible.
 */
#ifndef _FL_string_h
#define _FL_string_h

// libc includes
#include <ctype.h>
#include <string.h>

// fll-0 includes
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Compare two UTF-8 strings, similar to strncmp().
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param length1
 *   Length of string1.
 * @param length2
 *   Length of string2.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_utf_string_compare_
  extern f_status_t fl_utf_string_compare(const f_utf_string_t string1, const f_utf_string_t string2, const f_array_length_t length1, const f_array_length_t length2);
#endif // _di_fl_utf_string_compare_

/**
 * Compare two UTF-8 strings, similar to strncmp().
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 * Ignores leading and trailing whitespace.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param length1
 *   Length of string1.
 * @param length2
 *   Length of string2.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_fl_utf_string_compare_trim_
  extern f_status_t fl_utf_string_compare_trim(const f_utf_string_t string1, const f_utf_string_t string2, const f_array_length_t length1, const f_array_length_t length2);
#endif // _di_fl_utf_string_compare_trim_

/**
 * Compare two UTF-8 strings, similar to strncmp().
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if a character in the string is an invalid UTF-8 character.
 */
#ifndef _di_fl_utf_string_dynamic_compare_
  extern f_status_t fl_utf_string_dynamic_compare(const f_utf_string_static_t string1, const f_utf_string_static_t string2);
#endif // _di_fl_utf_string_dynamic_compare_

/**
 * Compare two UTF-8 strings, similar to strncmp().
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 * Ignores leading and trailing whitespace.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if a character in the string is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_fl_utf_string_dynamic_compare_trim_
  extern f_status_t fl_utf_string_dynamic_compare_trim(const f_utf_string_static_t string1, const f_utf_string_static_t string2);
#endif // _di_fl_utf_string_dynamic_compare_trim_

/**
 * Compare two UTF-8 strings, similar to strncmp(), but restricted to the given ranges.
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param range1
 *   A range within the string1 to restrict the comparison to.
 * @param range2
 *   A range within the string2 to restrict the comparison to.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_utf_string_dynamic_partial_compare_
  extern f_status_t fl_utf_string_dynamic_partial_compare(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_utf_string_range_t range1, const f_utf_string_range_t range2);
#endif // _di_fl_utf_string_dynamic_partial_compare_

/**
 * Compare two UTF-8 strings, similar to strncmp(), but restricted to the given ranges.
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 * Ignores leading and trailing whitespace.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param range1
 *   A range within the string1 to restrict the comparison to.
 * @param range2
 *   A range within the string2 to restrict the comparison to.
 *
 * @return
 *   F_equal_to when both strings equal.
 *   F_equal_to_not when both strings do not equal.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_fl_utf_string_dynamic_partial_compare_trim_
  extern f_status_t fl_utf_string_dynamic_partial_compare_trim(const f_utf_string_static_t string1, const f_utf_string_static_t string2, const f_utf_string_range_t range1, const f_utf_string_range_t range2);
#endif // _di_fl_utf_string_dynamic_partial_compare_trim_

/**
 * Allocate a new UTF-8 string from the provided range in the buffer.
 *
 * Ignores leading and trailing whitespace.
 * As a result, resulting size may be smaller than requested range.
 *
 * @param source
 *   The buffer to rip from.
 * @param range
 *   A range within the buffer representing the string to rip.
 * @param destination
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if the combined string is too large.
 */
#ifndef _di_fl_utf_string_dynamic_rip_
  extern f_status_t fl_utf_string_dynamic_rip(const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination);
#endif // _di_fl_utf_string_dynamic_rip_

/**
 * Allocate a new UTF-8 string from the provided range in the buffer.
 *
 * Ignores leading and trailing whitespace.
 * As a result, resulting size may be smaller than requested range.
 *
 * Skips over NULL characters from source when appending.
 *
 * @param source
 *   The string to rip from.
 * @param range
 *   A range within the buffer representing the string to rip.
 * @param destination
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_utf_string_dynamic_rip_nulless_
  extern f_status_t fl_utf_string_dynamic_rip_nulless(const f_utf_string_static_t source, const f_utf_string_range_t range, f_utf_string_dynamic_t *destination);
#endif // _di_fl_utf_string_dynamic_rip_nulless_

/**
 * Seek the buffer location forward until the  (1-byte wide) character or EOL is reached.
 *
 * @param buffer
 *   The buffer to traverse.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param seek_to_this
 *   A single-width character.
 *
 * @return
 *   F_none on success.
 *   F_none_eol on success, but stopped at EOL.
 *   F_none_eos on success, but stopped at end of buffer.
 *   F_data_not_eos if buffer length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if a character in the buffer is an invalid UTF-8 character.
 */
#ifndef _di_fl_utf_string_dynamic_seek_line_to_char_
  extern f_status_t fl_utf_string_dynamic_seek_line_to_char(const f_utf_string_static_t buffer, f_utf_string_range_t *range, const char seek_to_this);
#endif // _di_fl_utf_string_dynamic_seek_line_to_char_

/**
 * Increment buffer location until a graph character or an EOL is matched.
 *
 * @param buffer
 *   The buffer to traverse.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 * @param placeholder
 *   A UTF-8 character representing a placeholder to ignore (may be NULL).
 *
 * @return
 *   F_none on success.
 *   F_none_eol on success, but stopped at EOL.
 *   F_none_eos on success, but stopped at end of buffer.
 *   F_data_not_eos if buffer length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid
 *   F_utf (with error bit) if a character in the buffer is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_character_is_graph().
 *
 * @see f_utf_character_is_graph()
 */
#ifndef _di_fl_utf_string_dynamic_seek_line_until_graph_
  extern f_status_t fl_utf_string_dynamic_seek_line_until_graph(const f_utf_string_static_t buffer, f_utf_string_range_t *range, const f_utf_character_t placeholder);
#endif // _di_fl_utf_string_dynamic_seek_line_until_graph_

/**
 * Increment buffer location until a non-graph character or an EOL is matched.
 *
 * @param buffer
 *   The buffer to traverse.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 * @param placeholder
 *   A single-width character representing a placeholder to ignore (may be NULL).
 *
 * @return
 *   F_none on success.
 *   F_none_eol on success, but stopped at EOL.
 *   F_none_eos on success, but stopped at end of buffer.
 *   F_none_stop on success, but stopped stop location.
 *   F_data_not_eos if buffer length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if a character in the buffer is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_character_is_graph().
 *
 * @see f_utf_character_is_graph()
 */
#ifndef _di_fl_utf_string_dynamic_seek_line_until_graph_non_
  extern f_status_t fl_utf_string_dynamic_seek_line_until_graph_non(const f_utf_string_static_t buffer, f_utf_string_range_t *range, const f_utf_character_t placeholder);
#endif // _di_fl_utf_string_dynamic_seek_line_until_graph_non_

/**
 * Seek the buffer location forward until the UTF-8 character (1-byte wide) is reached.
 *
 * @param buffer
 *   The buffer to traverse.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param seek_to_this
 *   A single-width non-UTF-8 character.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success, but stopped at end of buffer.
 *   F_none_stop on success, but stopped stop location.
 *   F_data_not_eos if buffer length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_utf (with error bit) if a character in the buffer is an invalid UTF-8 character.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_utf_string_dynamic_seek_to_char_
  extern f_status_t fl_utf_string_dynamic_seek_to_char(const f_utf_string_static_t buffer, f_utf_string_range_t *range, const char seek_to_this);
#endif // _di_fl_utf_string_dynamic_seek_to_char_

/**
 * Allocate a new UTF-8 string from the provided range in the string.
 *
 * Ignores leading and trailing whitespace.
 * As a result, resulting size may be smaller than requested length.
 *
 * @param source
 *   The string to rip from.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_fl_utf_string_rip_
  extern f_status_t fl_utf_string_rip(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination);
#endif // _di_fl_utf_string_rip_

/**
 * Allocate a new UTF-8 string from the provided range in the string.
 *
 * Ignores leading and trailing whitespace.
 * As a result, resulting size may be smaller than requested length.
 *
 * Skips over NULL characters from source when ripping.
 *
 * @param source
 *   The string to rip from.
 * @param length
 *   The length of source to append.
 * @param destination
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   F_none on success.
 *   F_data_not_eos if source length is 0.
 *
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_character_is_whitespace().
 *
 * @see f_utf_character_is_whitespace()
 */
#ifndef _di_fl_utf_string_rip_nulless_
  extern f_status_t fl_utf_string_rip_nulless(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t *destination);
#endif // _di_fl_utf_string_rip_nulless_

/**
 * Seek the string location forward until the 1-byte wide character or EOL is reached.
 *
 * @param string
 *   The string to traverse.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param seek_to_this
 *   A single-width character.
 *
 * @return
 *   F_none on success.
 *   F_none_eol on success, but stopped at EOL.
 *   F_none_eos on success, but stopped at end of buffer.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if a character in the buffer is an invalid UTF-8 character.
 */
#ifndef _di_fl_utf_string_seek_line_to_char_
  extern f_status_t fl_utf_string_seek_line_to_char(const f_utf_string_t string, f_utf_string_range_t *range, const char seek_to_this);
#endif // _di_fl_utf_string_seek_line_to_char_

/**
 * Increment string location until a UTF-8 graph character or an EOL is matched.
 *
 * @param string
 *   The string to traverse.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param placeholder
 *   A UTF-8 character representing a placeholder to ignore (may be NULL).
 *
 * @return
 *   F_none on success.
 *   F_none_eol on success, but stopped at EOL.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if a character in the string is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_character_is_graph().
 *
 * @see f_utf_character_is_graph()
 */
#ifndef _di_fl_utf_string_seek_line_until_graph_
  extern f_status_t fl_utf_string_seek_line_until_graph(const f_utf_string_t string, f_utf_string_range_t *range, const f_utf_character_t placeholder);
#endif // _di_fl_utf_string_seek_line_until_graph_

/**
 * Increment string location until a non-graph UTF-8 character or an EOL is matched.
 *
 * @param string
 *   The string to traverse.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param placeholder
 *   A UTF-8 character representing a placeholder to ignore (may be NULL).
 *
 * @return
 *   F_none on success.
 *   F_none_eol on success, but stopped at EOL.
 *   F_none_stop on success, but stopped stop location.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_complete_not_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   F_complete_not_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if a character in the string is an invalid UTF-8 character.
 *
 *   Errors (with error bit) from: f_utf_character_is_graph().
 *
 * @see f_utf_character_is_graph()
 */
#ifndef _di_fl_utf_string_seek_line_until_graph_non_
  extern f_status_t fl_utf_string_seek_line_until_graph_non(const f_utf_string_t string, f_utf_string_range_t *range, const f_utf_character_t placeholder);
#endif // _di_fl_utf_string_seek_line_until_graph_non_

/**
 * Seek the string location forward until the UTF-8 character (up to 4-byte wide) is reached.
 *
 * @param string
 *   The string to traverse.
 * @param range
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param seek_to_this
 *   A single-width non-UTF-8 character.
 *
 * @return
 *   F_none on success.
 *   F_none_eos on success, but stopped at end of buffer.
 *   F_none_stop on success, but stopped stop location.
 *
 *   F_data_not_stop if range.start > range.stop.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) if a character in the buffer is an invalid UTF-8 character.
 */
#ifndef _di_fl_utf_string_seek_to_character_
  extern f_status_t fl_utf_string_seek_to_char(const f_utf_string_t string, f_utf_string_range_t *range, const char seek_to_this);
#endif // _di_fl_utf_string__seek_to_character_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_string_h
