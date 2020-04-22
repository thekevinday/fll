/**
 * FLL - Level 1
 *
 * Project: String
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides basic string manipulation and processing capabilities.
 *
 * UTF-8 is handled within these functions via normal string characters (f_string).
 * Unlike f_utf_string, these f_string base functions do not force padding of ASCII or UTF-8 characters.
 * An ASCII character is 1-byte and a 4-byte wide UTF-8 character is 4-byte.
 *
 * This shortens the size of the string at the cost of complexity vs f_utf_string.
 *
 * Because of the variable width, it is generally unsafe to ignore invalid UTF-8 sequences.
 * Invalid UTF-8 will be generally result in an error.
 */
#ifndef _FL_string_h
#define _FL_string_h

// libc includes
#include <ctype.h>
#include <string.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/type.h>
#include <level_0/utf.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Compare two strings, similar to strncmp().
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
 *   f_equal_to when both strings equal.
 *   f_not_equal_to when both strings do not equal.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fl_string_dynamic_compare()
 * @see fl_string_dynamic_compare_trim()
 * @see fl_string_dynamic_partial_compare()
 * @see fl_string_dynamic_partial_compare_trim()
 */
#ifndef _di_fl_string_compare_
  extern f_return_status fl_string_compare(const f_string string1, const f_string string2, const f_string_length length1, const f_string_length length2);
#endif // _di_fl_string_compare_

/**
 * Compare two strings, similar to strncmp().
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
 *   f_equal_to when both strings equal.
 *   f_not_equal_to when both strings do not equal.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fl_string_dynamic_compare()
 * @see fl_string_dynamic_compare_trim()
 * @see fl_string_dynamic_partial_compare()
 * @see fl_string_dynamic_partial_compare_trim()
 */
#ifndef _di_fl_string_compare_trim_
  extern f_return_status fl_string_compare_trim(const f_string string1, const f_string string2, const f_string_length length1, const f_string_length length2);
#endif // _di_fl_string_compare_trim_

/**
 * Compare two strings, similar to strncmp().
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
 *   f_equal_to when both strings equal.
 *   f_not_equal_to when both strings do not equal.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fl_string_compare()
 * @see fl_string_compare_trim()
 * @see fl_string_dynamic_partial_compare()
 * @see fl_string_dynamic_partial_compare_trim()
 */
#ifndef _di_fl_string_dynamic_compare_
  extern f_return_status fl_string_dynamic_compare(const f_string_dynamic string1, const f_string_dynamic string2);
#endif // _di_fl_string_dynamic_compare_

/**
 * Compare two strings, similar to strncmp().
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
 *   f_equal_to when both strings equal.
 *   f_not_equal_to when both strings do not equal.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fl_string_compare()
 * @see fl_string_compare_trim()
 * @see fl_string_dynamic_partial_compare()
 * @see fl_string_dynamic_partial_compare_trim()
 */
#ifndef _di_fl_string_dynamic_compare_trim_
  extern f_return_status fl_string_dynamic_compare_trim(const f_string_dynamic string1, const f_string_dynamic string2);
#endif // _di_fl_string_dynamic_compare_trim_

/**
 * Compare two strings, similar to strncmp(), but restricted to the given ranges.
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param offset1
 *   A range within the string1 to restrict the comparison to.
 * @param offset2
 *   A range within the string2 to restrict the comparison to.
 *
 * @return
 *   f_equal_to when both strings equal.
 *   f_not_equal_to when both strings do not equal.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fl_string_compare()
 * @see fl_string_compare_trim()
 * @see fl_string_dynamic_compare()
 * @see fl_string_dynamic_compare_trim()
 */
#ifndef _di_fl_string_dynamic_partial_compare_
  extern f_return_status fl_string_dynamic_partial_compare(const f_string_dynamic string1, const f_string_dynamic string2, const f_string_location offset1, const f_string_location offset2);
#endif // _di_fl_string_dynamic_partial_compare_

/**
 * Compare two strings, similar to strncmp(), but restricted to the given ranges.
 *
 * This does not stop on NULL.
 * NULL characters are ignored.
 * Ignores leading and trailing whitespace.
 *
 * @param string1
 *   String to compare.
 * @param string2
 *   String to compare.
 * @param offset1
 *   A range within the string1 to restrict the comparison to.
 * @param offset2
 *   A range within the string2 to restrict the comparison to.
 *
 * @return
 *   f_equal_to when both strings equal.
 *   f_not_equal_to when both strings do not equal.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fl_string_compare()
 * @see fl_string_compare_trim()
 * @see fl_string_dynamic_compare()
 * @see fl_string_dynamic_compare_trim()
 */
#ifndef _di_fl_string_dynamic_partial_compare_trim_
  extern f_return_status fl_string_dynamic_partial_compare_trim(const f_string_dynamic string1, const f_string_dynamic string2, const f_string_location offset1, const f_string_location offset2);
#endif // _di_fl_string_dynamic_partial_compare_trim_

/**
 * Allocate a new string from the provided range in the buffer.
 *
 * @param buffer
 *   The buffer to rip from.
 * @param location
 *   A range within the buffer representing the string to rip.
 * @param result
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   f_none on success.
 *   f_no_data if nothing to rip, no allocations or reallocations are performed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on memory allocation error.
 *   f_error_reallocation (with error bit) on memory reallocation error.
 *
 * @see fl_string_dynamic_rip_trim()
 * @see fl_string_rip()
 * @see fl_string_rip_trim()
 */
#ifndef _di_fl_string_dynamic_rip_
  extern f_return_status fl_string_dynamic_rip(const f_string_dynamic buffer, const f_string_location location, f_string_dynamic *result);
#endif // _di_fl_string_dynamic_rip_

/**
 * Allocate a new string from the provided range in the buffer.
 *
 * Ignores leading and trailing whitespace.
 * As a result, resulting size may be smaller than requested range.
 *
 * @param buffer
 *   The buffer to rip from.
 * @param location
 *   A range within the buffer representing the string to rip.
 * @param result
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   f_none on success.
 *   f_no_data if nothing to rip, no allocations or reallocations are performed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on memory allocation error.
 *   f_error_reallocation (with error bit) on memory reallocation error.
 *
 * @see fl_string_dynamic_rip()
 * @see fl_string_dynamic_rip_trim()
 * @see fl_string_rip()
 */
#ifndef _di_fl_string_dynamic_rip_trim_
  extern f_return_status fl_string_dynamic_rip_trim(const f_string_dynamic buffer, const f_string_location location, f_string_dynamic *result);
#endif // _di_fl_string_dynamic_rip_trim_

/**
 * Seek the buffer location forward until the character (1-byte wide) or EOL is reached.
 *
 * @param buffer
 *   The buffer to traverse.
 * @param location
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param seek_to_this
 *   A single-width character representing a character to seek to.
 *
 * @return
 *   f_none on success.
 *   f_none_on_eol on success, but stopped at EOL.
 *   f_none_on_eos on success, but stopped at end of buffer.
 *   f_none_on_stop on success, but stopped stop location.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fl_string_dynamic_seek_line_to_utf_character()
 * @see fl_string_seek_line_to_utf_character()
 */
#ifndef _di_fl_string_dynamic_seek_line_to_
  extern f_return_status fl_string_dynamic_seek_line_to(const f_string_dynamic buffer, f_string_location *location, const int8_t seek_to_this);
#endif // _di_fl_string_dynamic_seek_line_to_

/**
 * Seek the buffer location forward until the character (up to 4-byte wide) or EOL is reached.
 *
 * @param buffer
 *   The buffer to traverse.
 * @param location
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param seek_to_this
 *   A 1-width, 2-width, 3-width, or 4-width character representing a character to seek to.
 *
 * @return
 *   f_none on success.
 *   f_none_on_eol on success, but stopped at EOL.
 *   f_none_on_eos on success, but stopped at end of buffer.
 *   f_invalid_utf (with error bit) if character is an invalid UTF-8 character.
 *   f_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   f_incomplete_utf_on_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   f_incomplete_utf_on_eos (with error bit) if end of string is reached before a complete UTF-8 character can be processed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fl_string_dynamic_seek_line_to()
 * @see fl_string_seek_line_to()
 */
#ifndef _di_fl_string_dynamic_seek_line_to_utf_character_
  extern f_return_status fl_string_dynamic_seek_line_to_utf_character(const f_string_dynamic buffer, f_string_location *location, const f_utf_character seek_to_this);
#endif // _di_fl_string_dynamic_seek_line_to_utf_character_

/**
 * Increment buffer location until a graph character (including UTF-8) or an EOL is matched.
 *
 * @param buffer
 *   The buffer to traverse.
 * @param location
 *   A range within the buffer representing the start and stop locations.
 * @param placeholder
 *   A single-width character representing a placeholder to ignore (may be NULL).
 *
 * @return
 *   f_none on success.
 *   f_none_on_eol on success, but stopped at EOL.
 *   f_none_on_eos on success, but stopped at end of buffer.
 *   f_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   f_incomplete_utf_on_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   f_incomplete_utf_on_eos (with error bit) if end of string is reached before a complete UTF-8 character can be processed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on memory allocation error.
 *   f_error_reallocation (with error bit) on memory reallocation error.
 *
 * @see fl_string_seek_line_until_graph()
 */
#ifndef _di_fl_string_dynamic_seek_line_until_graph_
  extern f_return_status fl_string_dynamic_seek_line_until_graph(const f_string_dynamic buffer, f_string_location *location, const int8_t placeholder);
#endif // _di_fl_string_dynamic_seek_line_until_graph_

/**
 * Increment buffer location until a non-graph character (including UTF-8) or an EOL is matched.
 *
 * @param buffer
 *   The buffer to traverse.
 * @param location
 *   A range within the buffer representing the start and stop locations.
 * @param placeholder
 *   A single-width character representing a placeholder to ignore (may be NULL).
 *
 * @return
 *   f_none on success.
 *   f_none_on_eol on success, but stopped at EOL.
 *   f_none_on_eos on success, but stopped at end of buffer.
 *   f_none_on_stop on success, but stopped stop location.
 *   f_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   f_incomplete_utf_on_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   f_incomplete_utf_on_eos (with error bit) if end of string is reached before a complete UTF-8 character can be processed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on memory allocation error.
 *   f_error_reallocation (with error bit) on memory reallocation error.
 *
 * @see fl_string_seek_line_until_non_graph()
 */
#ifndef _di_fl_string_dynamic_seek_line_until_non_graph_
  extern f_return_status fl_string_dynamic_seek_line_until_non_graph(const f_string_dynamic buffer, f_string_location *location, const int8_t placeholder);
#endif // _di_fl_string_dynamic_seek_line_until_non_graph_

/**
 * Seek the buffer location forward until the character (1-byte wide) is reached.
 *
 * @param buffer
 *   The buffer to traverse.
 * @param location
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param seek_to_this
 *   A single-width character representing a character to seek to.
 *
 * @return
 *   f_none on success.
 *   f_none_on_eos on success, but stopped at end of buffer.
 *   f_none_on_stop on success, but stopped stop location.
 *   f_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   f_incomplete_utf_on_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   f_incomplete_utf_on_eos (with error bit) if end of string is reached before a complete UTF-8 character can be processed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fl_string_dynamic_seek_to_utf_character()
 * @see fl_string_seek_to()
 * @see fl_string_seek_to_utf_character()
 */
#ifndef _di_fl_string_dynamic_seek_to_
  extern f_return_status fl_string_dynamic_seek_to(const f_string_dynamic buffer, f_string_location *location, const int8_t seek_to_this);
#endif // _di_fl_string_dynamic_seek_to_

/**
 * Seek the buffer location forward until the UTF-8 character (up to 4-byte wide) is reached.
 *
 * @param buffer
 *   The buffer to traverse.
 * @param location
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param seek_to_this
 *   A 1-width, 2-width, 3-width, or 4-width character representing a character to seek to.
 *
 * @return
 *   f_none on success.
 *   f_none_on_eos on success, but stopped at end of buffer.
 *   f_none_on_stop on success, but stopped stop location.
 *   f_invalid_utf (with error bit) if character is an invalid UTF-8 character.
 *   f_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   f_incomplete_utf_on_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   f_incomplete_utf_on_eos (with error bit) if end of string is reached before a complete UTF-8 character can be processed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fl_string_dynamic_seek_to()
 * @see fl_string_seek_to()
 * @see fl_string_seek_to_character()
 */
#ifndef _di_fl_string_dynamic_seek_to_utf_character_
  extern f_return_status fl_string_dynamic_seek_to_utf_character(const f_string_dynamic buffer, f_string_location *location, const f_utf_character seek_to_this);
#endif // _di_fl_string_dynamic_seek_to_utf_character_

/**
 * Allocate a new string from the provided range in the string.
 *
 * @param string
 *   The string to rip from.
 * @param start
 *   An inclusive start location within string.
 * @param stop
 *   An inclusive stop location within string.
 * @param result
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   f_none on success.
 *   f_no_data if nothing to rip, no allocations or reallocations are performed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on memory allocation error.
 *   f_error_reallocation (with error bit) on memory reallocation error.
 *
 * @see fl_string_dynamic_rip()
 * @see fl_string_dynamic_rip_trim()
 * @see fl_string_rip_trim()
 */
#ifndef _di_fl_string_rip_
  extern f_return_status fl_string_rip(const f_string string, const f_string_length start, const f_string_length stop, f_string_dynamic *result);
#endif // _di_fl_string_rip_

/**
 * Allocate a new string from the provided range in the string.
 *
 * Ignores leading and trailing whitespace.
 * As a result, resulting size may be smaller than requested range.
 *
 * @param string
 *   The string to rip from.
 * @param start
 *   An inclusive start location within string.
 * @param stop
 *   An inclusive stop location within string.
 * @param result
 *   The new string, which will be allocated or reallocated as necessary.
 *
 * @return
 *   f_none on success.
 *   f_no_data if nothing to rip, no allocations or reallocations are performed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on memory allocation error.
 *   f_error_reallocation (with error bit) on memory reallocation error.
 *
 * @see fl_string_dynamic_rip()
 * @see fl_string_rip()
 * @see fl_string_rip_trim()
 */
#ifndef _di_fl_string_rip_trim_
  extern f_return_status fl_string_rip_trim(const f_string string, const f_string_length start, const f_string_length stop, f_string_dynamic *result);
#endif // _di_fl_string_rip_trim_

/**
 * Seek the string location forward until the character (1-byte wide) or EOL is reached.
 *
 * @param string
 *   The string to traverse.
 * @param location
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param seek_to_this
 *   A single-width character representing a character to seek to.
 *
 * @return
 *   f_none on success.
 *   f_none_on_eol on success, but stopped at EOL.
 *   f_none_on_stop on success, but stopped stop location.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fl_string_dynamic_seek_line_to()
 * @see fl_string_dynamic_seek_line_to_utf_character()
 * @see fl_string_seek_line_to_utf_character()
 */
#ifndef _di_fl_string_seek_line_to_
  extern f_return_status fl_string_seek_line_to(const f_string string, f_string_location *location, const int8_t seek_to_this);
#endif // _di_fl_string_seek_line_to_

/**
 * Seek the string location forward until the character (up to 4-byte wide) or EOL is reached.
 *
 * @param string
 *   The string to traverse.
 * @param location
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param seek_to_this
 *   A 1-width, 2-width, 3-width, or 4-width character representing a character to seek to.
 *
 * @return
 *   f_none on success.
 *   f_none_on_eol on success, but stopped at EOL.
 *   f_invalid_utf (with error bit) if character is an invalid UTF-8 character.
 *   f_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   f_incomplete_utf_on_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fl_string_dynamic_seek_line_to()
 * @see fl_string_seek_line_to()
 */
#ifndef _di_fl_string_seek_line_to_utf_character_
  extern f_return_status fl_string_seek_line_to_utf_character(const f_string string, f_string_location *location, const f_utf_character seek_to_this);
#endif // _di_fl_string_seek_line_to_utf_character_

/**
 * Increment string location until a graph character (including UTF-8) or an EOL is matched.
 *
 * @param string
 *   The string to traverse.
 * @param location
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param placeholder
 *   A single-width character representing a placeholder to ignore (may be NULL).
 *
 * @return
 *   f_none on success.
 *   f_none_on_eol on success, but stopped at EOL.
 *   f_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   f_incomplete_utf_on_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on memory allocation error.
 *   f_error_reallocation (with error bit) on memory reallocation error.
 *
 * @see fl_string_dynamic_seek_line_until_graph()
 */
#ifndef _di_fl_string_seek_line_until_graph_
  extern f_return_status fl_string_seek_line_until_graph(const f_string string, f_string_location *location, const int8_t placeholder);
#endif // _di_fl_string_seek_line_until_graph_

/**
 * Increment string location until a non-graph character (including UTF-8) or an EOL is matched.
 *
 * @param string
 *   The string to traverse.
 * @param location
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param placeholder
 *   A single-width character representing a placeholder to ignore (may be NULL).
 *
 * @return
 *   f_none on success.
 *   f_none_on_eol on success, but stopped at EOL.
 *   f_none_on_stop on success, but stopped stop location.
 *   f_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   f_incomplete_utf_on_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_allocation (with error bit) on memory allocation error.
 *   f_error_reallocation (with error bit) on memory reallocation error.
 *
 * @see fl_string_dynamic_seek_line_until_non_graph()
 */
#ifndef _di_fl_string_seek_line_until_non_graph_
  extern f_return_status fl_string_seek_line_until_non_graph(const f_string string, f_string_location *location, const int8_t placeholder);
#endif // _di_fl_string_seek_line_until_non_graph_

/**
 * Seek the string location forward until the character (1-byte wide) is reached.
 *
 * @param string
 *   The string to traverse.
 * @param location
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param seek_to_this
 *   A single-width character representing a character to seek to.
 *
 * @return
 *   f_none on success.
 *   f_none_on_stop on success, but stopped stop location.
 *   f_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   f_incomplete_utf_on_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fl_string_dynamic_seek_to()
 * @see fl_string_dynamic_seek_to_utf_character()
 * @see fl_string_seek_to_utf_character()
 */
#ifndef _di_fl_string_seek_to_
  extern f_return_status fl_string_seek_to(const f_string string, f_string_location *location, const int8_t seek_to_this);
#endif // _di_fl_string_seek_to_

/**
 * Seek the string location forward until the UTF-8 character (up to 4-byte wide) is reached.
 *
 * @param string
 *   The string to traverse.
 * @param location
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param seek_to_this
 *   A 1-width, 2-width, 3-width, or 4-width character representing a character to seek to.
 *
 * @return
 *   f_none on success.
 *   f_none_on_stop on success, but stopped stop location.
 *   f_invalid_utf (with error bit) if character is an invalid UTF-8 character.
 *   f_incomplete_utf (with error bit) if character is an incomplete UTF-8 fragment.
 *   f_incomplete_utf_on_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fl_string_dynamic_seek_to()
 * @see fl_string_dynamic_seek_to_utf_character()
 * @see fl_string_seek_to()
 */
#ifndef _di_fl_string_seek_to_utf_character_
  extern f_return_status fl_string_seek_to_utf_character(const f_string string, f_string_location *location, const f_utf_character seek_to_this);
#endif // _di_fl_string_seek_to_utf_character_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_string_h
