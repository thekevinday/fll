/**
 * FLL - Level 2
 *
 * Project: Control Group
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Provides control group (cgroup) related functionality.
 */
#ifndef _FLL_control_h
#define _FLL_control_h

// Libc includes.

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/control_group.h>
#include <fll/level_0/directory.h>
#include <fll/level_0/file.h>
#include <fll/level_0/path.h>

// FLL-1 includes.
#include <fll/level_1/control_group.h>
#include <fll/level_1/directory.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Make sure all directories specified in groups exist, creating all directories in the path.
 *
 * This does not, however, create the control_group.path and will error out if that directory does not exist.
 *
 * @param control_group
 *   The control group(s) to ensure the directories exist.
 *
 * @return
 *   F_none on success.
 *
 *   F_directory_not (with error bit) if control_group.path does not exist.
 *
 *   Errors (with error bit) from: f_directory_exists().
 *   Errors (with error bit) from: fl_directory_create().
 *
 * @see f_directory_exists()
 * @see fl_directory_create()
 */
#ifndef _di_fll_control_group_prepare_
  extern f_status_t fll_control_group_prepare(const f_control_group_t control_group);
#endif // _di_fll_control_group_prepare_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_control_h
