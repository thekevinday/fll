/**
 * FLL - Level 1
 *
 * Project: IKI
 * API Version: 0.7
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
 * @param buffer
 *   The string to process.
 * @param range
 *   The start/stop location within the buffer to be processed.
 *   The start location will be updated as the buffer is being processed.
 *   The start location will represent where the read stopped on return.
 *   A start location past the stop location or buffer used means that the entire range was processed.
 * @param data
 *   The IKI data.
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *   This must not be NULL.
 *
 *   This alters state.status:
 *     F_okay on success and an IKI vocabulary name was found.
 *     F_okay_stop on success and an IKI vocabulary name was found and stop point was reached.
 *     F_okay_eos on success and an IKI vocabulary name was found and end of string was reached.
 *     F_complete_not_utf_eos on success and EOS was reached, but at an incomplete UTF-8 sequence.
 *     F_complete_not_utf_stop on success and stop point was reached, but at an incomplete UTF-8 sequence.
 *     F_data_not_eos on success and EOS was reached, but there were no IKI vocabularie names found.
 *     F_data_not_stop on success and stop point was reached, but there were no IKI vocabularie names found.
 *
 *     F_parameter (with error bit) if a parameter is invalid.
 *
 *     Success from: f_iki_read().
 *     Errors (with error bit) from: f_iki_read().
 *
 * @see f_iki_read()
 */
#ifndef _di_fl_iki_read_
  extern void fl_iki_read(f_string_static_t * const buffer, f_string_range_t * const range, f_iki_data_t * const data, f_state_t * const state);
#endif // _di_fl_iki_read_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_iki_h
