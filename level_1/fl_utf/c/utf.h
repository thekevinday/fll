/**
 * FLL - Level 1
 *
 * Project: Utf
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides UTF-8 character manipulation and processing capabilities.
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
 * Increment buffer location until a graph character or an EOL is matched.
 *
 * This will ignore the UTF-8 BOM.
 *
 * @param buffer
 *   The buffer to traverse.
 * @param location
 *   A range within the buffer representing the start and stop locations.
 * @param placeholder
 *   A UTF-8 character representing a placeholder to ignore (may be NULL).
 *
 * @return
 *   f_none on success.
 *   f_none_on_eol on success, but stopped at EOL.
 *   f_none_on_eos on success, but stopped at end of buffer.
 *   f_invalid_utf (with error bit) if a character in the buffer is an invalid UTF-8 character.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_utf_seek_line_until_graph_
  extern f_return_status fl_utf_seek_line_until_graph(const f_utf_string_dynamic buffer, f_utf_string_location *location, const f_utf_character placeholder);
#endif // _di_fl_utf_seek_line_until_graph_

/**
 * Increment buffer location until a non-graph character or an EOL is matched.
 *
 * This will ignore the UTF-8 BOM.
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
 *   f_invalid_utf (with error bit) if a character in the buffer is an invalid UTF-8 character.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_fl_utf_seek_line_until_non_graph_
  extern f_return_status fl_utf_seek_line_until_non_graph(const f_utf_string_dynamic buffer, f_utf_string_location *location, const f_utf_character placeholder);
#endif // _di_fl_utf_seek_line_until_non_graph_

/**
 * Seek the buffer location forward until the UTF-8 character or EOL is reached.
 *
 * @param buffer
 *   The buffer to traverse.
 * @param location
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param seek_to_this
 *   A UTF-8 character representing a character to seek to.
 *
 * @return
 *   f_none on success.
 *   f_none_on_eol on success, but stopped at EOL.
 *   f_none_on_eos on success, but stopped at end of buffer.
 *   f_none_on_stop on success, but stopped stop location.
 *   f_invalid_utf (with error bit) if a character in the buffer is an invalid UTF-8 character.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fl_utf_seek_line_to_char()
 */
#ifndef _di_fl_utf_seek_line_to_
  extern f_return_status fl_utf_seek_line_to(const f_utf_string_dynamic buffer, f_utf_string_location *location, const f_utf_character seek_to_this);
#endif // _di_fl_utf_seek_line_to_

/**
 * Allocated a new UTF-8 string from the provided range in the buffer.
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
 *   f_allocation_error (with error bit) on memory allocation error.
 *   f_reallocation_error (with error bit) on memory reallocation error.
 */
#ifndef _di_fl_utf_string_rip_
  extern f_return_status fl_utf_string_rip(const f_utf_string_dynamic buffer, const f_utf_string_location location, f_utf_string_dynamic *result);
#endif // _di_fl_utf_string_rip_

/**
 * Seek the buffer location forward until the 1-byte wide character or EOL is reached.
 *
 * @param buffer
 *   The buffer to traverse.
 * @param location
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param seek_to_this
 *   A single-width non-UTF-8 character.
 *
 * @return
 *   f_none on success.
 *   f_none_on_eol on success, but stopped at EOL.
 *   f_none_on_eos on success, but stopped at end of buffer.
 *   f_invalid_utf (with error bit) if a character in the buffer is an invalid UTF-8 character.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fl_utf_seek_line_to()
 */
#ifndef _di_fl_utf_string_seek_line_to_char_
  extern f_return_status fl_utf_seek_line_to_char(const f_utf_string_dynamic buffer, f_utf_string_location *location, const int8_t seek_to_this);
#endif // _di_fl_utf_string_seek_line_to_char_

/**
 * Seek the buffer location forward until the character (1-byte wide) is reached.
 *
 * @param buffer
 *   The buffer to traverse.
 * @param location
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param seek_to_this
 *   A UTF-8 character representing a character to seek to.
 *
 * @return
 *   f_none on success.
 *   f_none_on_eos on success, but stopped at end of buffer.
 *   f_none_on_stop on success, but stopped stop location.
 *   f_invalid_utf (with error bit) if a character in the buffer is an invalid UTF-8 character.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fl_utf_string_seek_to_char()
 */
#ifndef _di_fl_utf_string_seek_to_
  extern f_return_status fl_utf_string_seek_to(const f_utf_string_dynamic buffer, f_utf_string_location *location, const f_utf_character seek_to_this);
#endif // _di_fl_utf_string_seek_to_

/**
 * Seek the buffer location forward until the UTF-8 character (up to 4-byte wide) is reached.
 *
 * @param buffer
 *   The buffer to traverse.
 * @param location
 *   A range within the buffer representing the start and stop locations.
 *   The start location will be incremented by seek.
 * @param seek_to_this
 *   A single-width non-UTF-8 character.
 *
 * @return
 *   f_none on success.
 *   f_none_on_eos on success, but stopped at end of buffer.
 *   f_none_on_stop on success, but stopped stop location.
 *   f_invalid_utf (with error bit) if a character in the buffer is an invalid UTF-8 character.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fl_utf_string_seek_to()
 */
#ifndef _di_fl_utf_string_seek_to_character_
  extern f_return_status fl_utf_string_seek_to_char(const f_utf_string_dynamic buffer, f_utf_string_location *location, const int8_t seek_to_this);
#endif // _di_fl_utf_string_seek_to_character_

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
 * @see fl_utf_string_dynamic_compare()
 * @see fl_utf_string_dynamic_partial_compare()
 */
#ifndef _di_fl_utf_string_compare_
  extern f_return_status fl_utf_string_compare(const f_utf_string string1, const f_utf_string string2, const f_utf_string_length length1, const f_utf_string_length length2);
#endif // _di_fl_utf_string_compare_

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
 * @see fl_utf_string_compare()
 * @see fl_utf_string_dynamic_partial_compare()
 */
#ifndef _di_fl_utf_string_dynamic_compare_
  extern f_return_status fl_utf_string_dynamic_compare(const f_utf_string_dynamic string1, const f_utf_string_dynamic string2);
#endif // _di_fl_utf_string_dynamic_compare_

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
 * @see fl_utf_string_compare()
 * @see fl_utf_string_dynamic_compare()
 */
#ifndef _di_fl_utf_string_dynamic_partial_compare_
  extern f_return_status fl_utf_string_dynamic_partial_compare(const f_utf_string_dynamic string1, const f_utf_string_dynamic string2, const f_utf_string_location offset1, const f_utf_string_location offset2);
#endif // _di_fl_utf_string_dynamic_partial_compare_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_string_h
