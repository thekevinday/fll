/**
 * FLL - Level 0
 *
 * Project: IKI
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides a Wiki-Like syntax meant to be much simpler.
 *
 * This simpler Wiki-Like syntax, called Iki, focuses just on simply adding context.
 * The context itself is not explicitly defined but a few common standards are provided.
 */
#ifndef _F_iki_h
#define _F_iki_h

// Libc includes.
#include <stdio.h>
#include <sys/stat.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/type_array.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>

// FLL-0 iki includes.
#include <fll/level_0/iki/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Determine if an content is a valid IKI content name.
 *
 * @param content
 *   The string to validate as an content name.
 * @param quote
 *   The quote character in use.
 *   This must be either a single (') or double (") quote.
 *
 * @return
 *   F_true on success and string is a valid content name.
 *   F_false on success and string is not a valid content name.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_iki_content_is_
  extern f_status_t f_iki_content_is(const f_string_static_t content, const f_string_static_t quote);
#endif // _di_f_iki_content_is_

/**
 * Determine if an content, found within the given range, is a valid IKI content name.
 *
 * @param content
 *   The string to validate as an content name.
 * @param range
 *   The range within the buffer that represents the content name.
 * @param quote
 *   The quote character in use.
 *   This must be either a single (') or double (") quote.
 *
 * @return
 *   F_true on success and string is a valid content name.
 *   F_false on success and string is not a valid content name.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_iki_content_partial_is_
  extern f_status_t f_iki_content_partial_is(const f_string_static_t content, const f_string_range_t range, const f_string_static_t quote);
#endif // _di_f_iki_content_partial_is_

/**
 * Determine if an object is a valid IKI object name.
 *
 * @param object
 *   The string to validate as an object name.
 *
 * @return
 *   F_true on success and string is a valid object name.
 *   F_false on success and string is not a valid object name.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_word().
 */
#ifndef _di_f_iki_object_is_
  extern f_status_t f_iki_object_is(const f_string_static_t object);
#endif // _di_f_iki_object_is_

/**
 * Determine if an object, found within the buffer, is a valid IKI object name.
 *
 * @param object
 *   The string to validate as an object name.
 * @param range
 *   The range within the buffer that represents the object name.
 *
 * @return
 *   F_true on success and string is a valid object name.
 *   F_false on success and string is not a valid object name.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_utf_is_word().
 */
#ifndef _di_f_iki_object_partial_is_
  extern f_status_t f_iki_object_partial_is(const f_string_static_t object, const f_string_range_t range);
#endif // _di_f_iki_object_partial_is_

/**
 * Read a single iki Vocabulary and Content.
 *
 * This does not verify if the vocabulary name is known.
 * This only finds a complete vocabulary name and content.
 *
 * This will increment the range after the end of any valud vocabulary and content set.
 *
 * This will update the buffer at the given range with any placeholders to escaped data.
 * Calling this more than once on the same buffer range could result in multiple escaping.
 *
 * @param state
 *   A state for handling interrupts during long running operations.
 *   There is no print_error() usage at this time (@todo this should be implemented and supported).
 *   There is no functions structure.
 *   There is no data structure passed to these functions (@todo the additional parameters could be moved to a custom structure).
 *
 *   When interrupt() returns, only F_interrupt and F_interrupt_not are processed.
 *   Error bit designates an error but must be passed along with F_interrupt.
 *   All other statuses are ignored.
 * @param buffer
 *   The string to process.
 * @param range
 *   The start/stop location within the buffer to be processed.
 *   The start location will be updated as the buffer is being processed.
 *   The start location will represent where the read stopped on return.
 *   A start location past the stop location or buffer used means that the entire range was processed.
 * @param variable
 *   The entire vocabulary name, content, and syntax.
 * @param vocabulary
 *   The vocabulary name list to store the found vocabulary name.
 * @param content
 *   The content list to store the content associated with the found vocabulary name.
 * @param delimits
 *   A delimits array representing where delimits exist within the buffer.
 *
 * @return
 *   F_none on success and an IKI vocabulary name was found.
 *   F_none_eos on success and an IKI vocabulary name was found and end of string was reached.
 *   F_none_stop on success and an IKI vocabulary name was found and stop point was reached.
 *   F_data_not on success, but there were no IKI vocabulary names found.
 *   F_data_not_eos on success and EOS was reached, but there were no IKI vocabulary names found.
 *   F_data_not_stop on success and stop point was reached, but there were no IKI vocabulary names found.
 *
 *   F_interrupt (with error bit) if stopping due to an interrupt.
 *   F_memory_not (with error bit) on out of memory.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if a string length is too large to store in the buffer.
 */
#ifndef _di_f_iki_read_
  extern f_status_t f_iki_read(const f_state_t state, f_string_static_t * const buffer, f_string_range_t *range, f_iki_variable_t *variable, f_iki_vocabulary_t *vocabulary, f_iki_content_t *content, f_iki_delimits_t *delimits);
#endif // _di_f_iki_read_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_iki_h
