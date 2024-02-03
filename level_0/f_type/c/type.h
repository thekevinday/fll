/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides datatype definitions.
 *
 * This does not auto-include type/file.h, which must be manually included when needed.
 */
#ifndef _F_type_h
#define _F_type_h

// Include pre-requirements.
#ifndef _GNU_SOURCE
  #define _GNU_SOURCE
#endif // _GNU_SOURCE

// Libc includes.
#include <stdbool.h>
#include <stdint.h>
#include <sys/stat.h>
#include <unistd.h>

// FLL-0 type includes.
#include <fll/level_0/type/number.h>
#include <fll/level_0/type/status.h>
#include <fll/level_0/type/cell.h>
#include <fll/level_0/type/fll.h>
#include <fll/level_0/type/mode.h>
#include <fll/level_0/type/quantity.h>
#include <fll/level_0/type/range.h>
#include <fll/level_0/type/range_double.h>
#include <fll/level_0/type/state.h>
#include <fll/level_0/type/time.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Compiler-specific attribute features.
 *
 * Use these macros for visibility-specific tweaks so that if these are not supported by any given compiler, then they can be easily disabled.
 *
 * F_attribute_*:
 *   - visibility_hidden:    Visibility is hidden.
 *   - visibility_internal:  Visibility is private.
 *   - visibility_protected: Visibility is protected.
 *   - visibility_public:    Visibility is public.
 *   - weak:                 Designate symbol is weak rather than global.
 */
#ifndef _di_compiler_attributes_d_
  #define F_attribute_visibility_hidden_d    __attribute__((visibility("hidden")))
  #define F_attribute_visibility_internal_d  __attribute__((visibility("internal")))
  #define F_attribute_visibility_protected_d __attribute__((visibility("protected")))
  #define F_attribute_visibility_public_d    __attribute__((visibility("default")))

  #define F_attribute_weak_d __attribute__((weak))
#endif // _di_compiler_attributes_d_

/**
 * Standard file types defines.
 *
 * F_type_*_d:
 *   - error:  Standard error stream.
 *   - input:  Standard input stream.
 *   - output: Standard output stream.
 *
 * F_type_descriptor_*_d:
 *   - error:  Standard error file descriptor.
 *   - input:  Standard input file descriptor.
 *   - output: Standard output file descriptor.
 */
#ifndef _di_f_type_d_
  #define F_type_error_d  stderr
  #define F_type_input_d  stdin
  #define F_type_output_d stdout

  #define F_type_descriptor_error_d  STDERR_FILENO
  #define F_type_descriptor_input_d  STDIN_FILENO
  #define F_type_descriptor_output_d STDOUT_FILENO
#endif // _di_f_type_d_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_h
