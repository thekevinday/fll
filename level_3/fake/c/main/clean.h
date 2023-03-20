/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides clean functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_clean_h
#define _fake_clean_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Execute the clean operation.
 *
 * @param data
 *   The program data.
 *
 *   This alters data.main->setting.state.status:
 *     F_none on success.
 *
 *     F_interrupt (with error bit) on interrupt signal received.
 *
 *     Errors (with error bit) from: f_directory_remove()
 *     Errors (with error bit) from: f_directory_remove_custom()
 *
 * @see f_directory_remove()
 * @see f_directory_remove_custom()
 */
#ifndef _di_fake_clean_operate_
  extern void fake_clean_operate(fake_data_t * const data);
#endif // _di_fake_clean_operate_

/**
 * A special function intended to be used directly by nftw().
 *
 * This is intended to be used by the specified function as a function pointer and therefore follows the required structure.
 *
 * This is essentially a wrapper to remove().
 *
 * @param path
 *   The file path.
 * @param file_stat
 *   The file stat.
 * @param type
 *   The file type.
 * @param entity
 *   The FTW entity.
 *
 * @return
 *   0 on success.
 *   -1 on failure.
 *   Check errno for details.
 *
 * @see f_directory_remove()
 * @see nftw()
 * @see remove()
 */
#if !defined(_di_fake_clean_operate_)
  extern int fake_clean_remove_recursively_verbosely(const char * const path, const struct stat *file_stat, int type, struct FTW *entity);
#endif // !defined(_di_fake_clean_operate_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_clean_h
