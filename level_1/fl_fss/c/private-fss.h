/**
 * FLL - Level 1
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * These are provided for internal reduction in redundant code.
 * These should not be exposed/used outside of this project.
 */
#ifndef _PRIVATE_FL_fss_h
#define _PRIVATE_FL_fss_h

// libc includes
#include <ctype.h>
#include <string.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/fss.h>
#include <level_0/string.h>
#include <level_0/type.h>
#include <level_0/memory.h>
#include <level_0/utf.h>

// fll-1 includes
#include <level_1/fss_status.h>
#include <level_1/fss_macro.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Private implementation of fl_fss_basic_object_read().
 *
 * Intended to be shared to each of the different implementation variations.
 *
 * @param is_basic
 *   Set to TRUE if this is a basic read.
 *   Set to FALSE if this is an extended read.
 * @param buffer
 *   The buffer to read from.
 *   This will be updated with delimit placeholders as it is being processed.
 * @param range
 *   The start/stop location within the buffer to be processed.
 *   The start location will be updated as the buffer is being processed.
 *   The start location will represent where the read stopped on return.
 *   A start location past the stop location or buffer used means that the entire range was processed.
 * @param found
 *   A set of all locations where a valid object was found.
 *
 * @return
 *   FL_fss_found_object on success and object was found (start location is at end of object).
 *   FL_fss_found_object_not on success and no object was found (start location is after character designating this is not an object).
 *   F_none_eos on success after reaching the end of the buffer (a valid object is not yet confirmed).
 *   F_none_stop on success after reaching stopping point (a valid object is not yet confirmed).
 *   F_data_not_eos no objects found after reaching the end of the buffer (essentially only comments are found).
 *   F_data_not_stop no data found after reaching stopping point (essentially only comments are found).
 *   F_unterminated_group_eos (with warning bit) if EOS was reached before the a group termination was reached.
 *   F_unterminated_group_stop (with warning bit) if stop point was reached before the a group termination was reached.
 *   F_incomplete_utf (with error bit) is returned on failure to read/process a UTF-8 character due to the character being potentially incomplete.
 *   F_incomplete_utf_eos (with error bit) if the end of buffer is reached before the complete UTF-8 character can be processed.
 *   F_incomplete_utf_stop (with error bit) if the stop location is reached before the complete UTF-8 character can be processed.
 *   F_memory_reallocation (with error bit) on reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_utf (with error bit) is returned on failure to read/process a UTF-8 character.
 *
 *   Errors from (with error bit): f_utf_buffer_increment().
 *   Errors from (with error bit): f_fss_is_graph().
 *   Errors from (with error bit): f_fss_is_space().
 *   Errors from (with error bit): f_fss_skip_past_space().
 *
 * @see fl_fss_basic_object_read()
 * @see fl_fss_extended_object_read()
 */
#if !defined(_di_fl_fss_basic_object_read_) || !defined(_di_fl_fss_extended_object_read_)
  extern f_return_status private_fl_fss_basic_object_read(const bool is_basic, f_string_dynamic *buffer, f_string_range *range, f_fss_object *found) f_gcc_attribute_visibility_internal;
#endif // !defined(_di_fl_fss_basic_object_read_) || !defined(_di_fl_fss_extended_object_read_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_FL_fss_h
