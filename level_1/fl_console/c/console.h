/**
 * FLL - Level 1
 *
 * Project: Console
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Some console input/output commands.
 */
#ifndef _FL_console_h
#define _FL_console_h

// libc include
#include <limits.h>
#include <string.h>
#include <sys/stat.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/utf.h>
#include <level_0/console.h>
#include <level_0/conversion.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Validate and convert a console parameter additional argument to a file directory in a dynamic string.
 *
 * The directory path is validated to exist.
 *
 * The path to a directy has the following very basic cleanup operations performed:
 * - Ensures that it always ends in a '/'.
 * - Ensures that multiple '/' in front or multiple '/' at end of string is reduced to a single '/' in front and a single '/' at end.
 * - Ensures that multiple '/' following './' at the start of the string is reduced to only './' ('.////' would become './').
 * - Ensures that multiple '/' following '../' at the start of the string is reduced to only '../' ('..////' would become '../').
 *
 * This does not perform complex cleanup, such as '..///..///' to '../../'.
 *
 * The purpose of the cleanups is to ensure/enforce a consistent beginning and ending of the path strings.
 * These path strings can then, very simply, be checked to see how to join them with another string, such as a filename.
 *
 * @param argv
 *   The argument string expected to be a number.
 *   This is generally passed from the argv[].
 * @param directory
 *   The dynamically allocated processed directory string.
 *
 * @return
 *   F_none on success.
 *   F_memory_allocation (with error bit) on allocation error.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _fl_console_parameter_to_string_dynamic_directory_
  extern f_return_status fl_console_parameter_to_string_dynamic_directory(const f_string argument, f_string_dynamic *directory);
#endif // _fl_console_parameter_to_string_dynamic_directory_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_console_h
