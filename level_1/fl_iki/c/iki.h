/**
 * FLL - Level 1
 *
 * Project: Iki
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides a Wiki-Like syntax meant to be much simpler.
 *
 * This simpler Wiki-Like syntax, called Iki, focuses just on simply adding context.
 * The context itself is not explicitly defined but a few common standards are provided.
 */
#ifndef _FL_iki_h
#define _FL_iki_h

// libc includes
#include <stdio.h>
#include <sys/stat.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/type.h>
#include <level_0/utf.h>
#include <level_0/iki.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read all iki Vocabulary and Content in the given range of the given buffer.
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
 * @param variable
 *   The entire vocabulary name, content, and syntax.
 * @param vocabulary
 *   The vocabulary name list to store the found vocabulary names.
 * @param content
 *   The content list to store the content associated with the found vocabulary names.
 *
 * @return
 *   F_none on success and an IKI vocabulary name was found.
 *   F_none_stop on success and an IKI vocabulary name was found and stop point was reached.
 *   F_none_eos on success and an IKI vocabulary name was found and end of string was reached.
 *   F_data_not_eos on success and EOS was reached, but there were no IKI vocabularie names found.
 *   F_data_not_stop on success and stop point was reached, but there were no IKI vocabularie names found.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_string_too_large (with error bit) if a string length is too large to store in the buffer.
 */
#ifndef _di_fl_iki_read_
  extern f_return_status fl_iki_read(f_string_static *buffer, f_string_range *range, f_iki_variable *variable, f_iki_vocabulary *vocabulary, f_iki_content *content);
#endif // _di_fl_iki_read_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_iki_h
