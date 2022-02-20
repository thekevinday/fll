/**
 * FLL - Level 1
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
#ifndef _FL_iki_h
#define _FL_iki_h

// Libc includes.
#include <stdio.h>
#include <sys/stat.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/iki.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read all IKI Vocabulary and Content in the given range of the given buffer.
 *
 * This does not verify if any vocabulary name is known.
 * This only finds complete vocabulary names and their respective content.
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
 *   The vocabulary name list to store the found vocabulary names.
 * @param content
 *   The content list to store the content associated with the found vocabulary names.
 * @param delimits
 *   A delimits array representing where delimits exist within the buffer.
 *
 * @return
 *   F_none on success and an IKI vocabulary name was found.
 *   F_none_stop on success and an IKI vocabulary name was found and stop point was reached.
 *   F_none_eos on success and an IKI vocabulary name was found and end of string was reached.
 *   F_data_not_eos on success and EOS was reached, but there were no IKI vocabularie names found.
 *   F_data_not_stop on success and stop point was reached, but there were no IKI vocabularie names found.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Success from: f_iki_read().
 *   Errors (with error bit) from: f_iki_read().
 *
 * @see f_iki_read()
 */
#ifndef _di_fl_iki_read_
  extern f_status_t fl_iki_read(const f_state_t state, f_string_static_t * const buffer, f_string_range_t * const range, f_iki_variable_t * const variable, f_iki_vocabulary_t * const vocabulary, f_iki_content_t * const content, f_iki_delimits_t * const delimits);
#endif // _di_fl_iki_read_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_iki_h
