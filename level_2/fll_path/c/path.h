/**
 * FLL - Level 2
 *
 * Project: Path
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides path-related functionality.
 */
#ifndef _FLL_path_h
#define _FLL_path_h

// libc includes
#include <stdio.h>

// fll-0 includes
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/path.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get the canonical (real) path for some path.
 *
 * This does not check if the path exists or not.
 * This processes the relative parts: './', '../', and extra '/'.
 * This does not process symbolic links.
 * This has a max size of F_string_t_size_d.
 *
 * @param path
 *   The source path to determine what the canonical path is.
 *   This is a NULL terminated string.
 * @param canonical
 *   The (allocated) canonical file path.
 *   The canonical->used is reset to 0 before processing.
 *   This will be NULL terminated at canonical->used + 1.
 *
 * @return
 *   F_none on success.
 *
 *   Errors (with error bit) from: f_path_current().
 *   Errors (with error bit) from: f_string_append().
 *   Errors (with error bit) from: f_string_append_assure().
 *   Errors (with error bit) from: f_string_dynamic_terminate_after().
 */
#ifndef _di_fll_path_canonical_
  extern f_status_t fll_path_canonical(const f_string_t path, f_string_dynamic_t *canonical);
#endif // _di_fll_path_canonical_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_path_h
