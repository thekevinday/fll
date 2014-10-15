/* FLL - Level 1
 * Project:       Strings
 * Version:       0.4.2
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provides basic string manipulation and processing capabilities
 */
#ifndef _FL_strings_h
#define _FL_strings_h

// libc includes
#include <string.h>
#include <ctype.h>

// fll includes
#include <level_0/types.h>
#include <level_0/errors.h>
#include <level_0/strings.h>
#include <level_0/memory.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fl_rip_string_
  // given a start and stop position, this will return a new string based from the supplied buffer, based on the passed positions
  // this will replace/overwrite existing information inside of the results variable
  f_extern f_return_status fl_rip_string(const f_dynamic_string buffer, const f_string_location position, f_dynamic_string *results);
#endif // _di_fl_rip_string_

#ifndef _di_fl_seek_line_past_non_graph_
  // given a dynamic string and a string location, seek past all non-graph characters until a graph is reached
  // will ignore the given placeholder
  f_extern f_return_status fl_seek_line_past_non_graph(const f_dynamic_string buffer, f_string_location *position, const f_autochar placeholder);
#endif // _di_fl_seek_line_past_non_graph_

#ifndef _di_fl_seek_line_until_non_graph_
  // given a dynamic string and a string location, seek past all graph characters until a non-graph is reached
  // will ignore the given placeholder
  f_extern f_return_status fl_seek_line_until_non_graph(const f_dynamic_string buffer, f_string_location *position, const f_autochar placeholder);
#endif // _di_fl_seek_line_until_non_graph_

#ifndef _di_fl_seek_to_
  // given a dynamic string and a string location, seek past all characters until the given character is reached
  f_extern f_return_status fl_seek_to(const f_dynamic_string buffer, f_string_location *position, const f_autochar seek_to_this);
#endif // _di_fl_seek_to_

#ifndef _di_fl_compare_strings_
  // this compares two strings and works similar to that of strncmp(..) but has significant differences to strncmp(..)
  // given two strings, this will return either f_equal_to or f_not_equal_to
  // this does not stop on f_eos and f_eos will be ignored as if it were not taking up any space, therefor a 5 character string could return f_equal_to if the 5 character string contains an f_eos anywhere within it
  f_extern f_return_status fl_compare_strings(const f_string string1, const f_string string2, const f_string_length length1, const f_string_length length2);
#endif // _di_fl_compare_strings_

#ifndef _di_fl_compare_dynamic_strings_
  // this compares two dynamic strings and works similar to that of strncmp(..) but has significant differences to strncmp(..)
  // given two strings, this will return either f_equal_to or f_not_equal_to
  // this is far safer than fl_compare_strings(..) as dynamic string contain size information within them
  // this does not stop on f_eos and f_eos will be ignored as if it were not taking up any space, therefor a 5 character string could return f_equal_to if the 5 character string contains an f_eos anywhere within it
  f_extern f_return_status fl_compare_dynamic_strings(const f_dynamic_string string1, const f_dynamic_string string2);
#endif // _di_fl_compare_dynamic_strings_

#ifndef _di_fl_compare_partial_dynamic_strings_
  // this functions identical to fl_compare_dynamic_strings, but uses offsets for both strings
  f_extern f_return_status fl_compare_partial_dynamic_strings(const f_dynamic_string string1, const f_dynamic_string string2, const f_string_location offset1, const f_string_location offset2);
#endif // _di_fl_compare_partial_dynamic_strings_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_strings_h
