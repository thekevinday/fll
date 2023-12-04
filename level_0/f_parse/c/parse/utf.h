/**
 * FLL - Level 0
 *
 * Project: Parse
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides basic UTF-8 string parse capabilities.
 */
#ifndef _F_parse_utf_h
#define _F_parse_utf_h

#ifdef __cplusplus
extern "C" {
#endif

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
 *   F_okay on success.
 *   F_okay_eol on success, but stopped at EOL.
 *   F_okay_eos on success, but stopped at end of buffer.
 *   F_data_not if buffer length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 */
#ifndef _di_f_parse_utf_dynamic_seek_line_to_char_
  extern f_status_t f_parse_utf_dynamic_seek_line_to_char(const f_utf_string_static_t buffer, f_range_t * const range, const f_char_t seek_to_this);
#endif // _di_f_parse_utf_dynamic_seek_line_to_char_

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
 *   F_okay on success.
 *   F_okay_eol on success, but stopped at EOL.
 *   F_okay_eos on success, but stopped at end of buffer.
 *   F_data_not if buffer length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *
 *   Errors (with error bit) from: f_utf_character_is_graph().
 *
 * @see f_utf_character_is_graph()
 */
#ifndef _di_f_parse_utf_dynamic_seek_line_until_graph_
  extern f_status_t f_parse_utf_dynamic_seek_line_until_graph(const f_utf_string_static_t buffer, f_range_t * const range, const f_utf_char_t placeholder);
#endif // _di_f_parse_utf_dynamic_seek_line_until_graph_

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
 *   F_okay on success.
 *   F_okay_eol on success, but stopped at EOL.
 *   F_okay_eos on success, but stopped at end of buffer.
 *   F_okay_stop on success, but stopped stop location.
 *   F_data_not if buffer length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *
 *   Errors (with error bit) from: f_utf_character_is_graph().
 *
 * @see f_utf_character_is_graph()
 */
#ifndef _di_f_parse_utf_dynamic_seek_line_until_graph_non_
  extern f_status_t f_parse_utf_dynamic_seek_line_until_graph_non(const f_utf_string_static_t buffer, f_range_t * const range, const f_utf_char_t placeholder);
#endif // _di_f_parse_utf_dynamic_seek_line_until_graph_non_

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
 *   F_okay on success.
 *   F_okay_eos on success, but stopped at end of buffer.
 *   F_okay_stop on success, but stopped stop location.
 *   F_data_not if buffer length is 0.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 */
#ifndef _di_f_parse_utf_dynamic_seek_to_char_
  extern f_status_t f_parse_utf_dynamic_seek_to_char(const f_utf_string_static_t buffer, f_range_t * const range, const f_char_t seek_to_this);
#endif // _di_f_parse_utf_dynamic_seek_to_char_

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
 *   F_okay on success.
 *   F_okay_eol on success, but stopped at EOL.
 *   F_okay_eos on success, but stopped at end of buffer.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 */
#ifndef _di_f_parse_utf_seek_line_to_char_
  extern f_status_t f_parse_utf_seek_line_to_char(const f_utf_string_t string, f_range_t * const range, const f_char_t seek_to_this);
#endif // _di_f_parse_utf_seek_line_to_char_

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
 *   F_okay on success.
 *   F_okay_eol on success, but stopped at EOL.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *
 *   Errors (with error bit) from: f_utf_character_is_graph().
 *
 * @see f_utf_character_is_graph()
 */
#ifndef _di_f_parse_utf_seek_line_until_graph_
  extern f_status_t f_parse_utf_seek_line_until_graph(const f_utf_string_t string, f_range_t * const range, const f_utf_char_t placeholder);
#endif // _di_f_parse_utf_seek_line_until_graph_

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
 *   F_okay on success.
 *   F_okay_eol on success, but stopped at EOL.
 *   F_okay_stop on success, but stopped stop location.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 *
 *   Errors (with error bit) from: f_utf_character_is_graph().
 *
 * @see f_utf_character_is_graph()
 */
#ifndef _di_f_parse_utf_seek_line_until_graph_non_
  extern f_status_t f_parse_utf_seek_line_until_graph_non(const f_utf_string_t string, f_range_t * const range, const f_utf_char_t placeholder);
#endif // _di_f_parse_utf_seek_line_until_graph_non_

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
 *   F_okay on success.
 *   F_okay_eos on success, but stopped at end of buffer.
 *   F_okay_stop on success, but stopped stop location.
 *   F_data_not_stop if range.start > range.stop.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf_fragment (with error bit) if character is a UTF-8 fragment.
 */
#ifndef _di_f_parse_utf_seek_to_character_
  extern f_status_t f_parse_utf_seek_to_char(const f_utf_string_t string, f_range_t * const range, const f_char_t seek_to_this);
#endif // _di_fl_utf_string__seek_to_character_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_parse_utf_h
