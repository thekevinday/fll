/**
 * FLL - Level 3
 *
 * Project: FSS Write
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This file is only ever included by main/main.c and should not normally be included anywhere else.
 * Anything that wants to include this should be providing the "main" program functionality in some manner.
 * Any program utilizing this should link to the "main" program library.
 */
#ifndef _fss_write_main_h
#define _fss_write_main_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Process printing help for when not specifying "--as".
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   Must be of type (fss_write_setting_t *).
 *
 *   This does not alter setting.status.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_fss_write_main_process_help_
  extern void fss_write_main_process_help(fll_program_data_t * const main, void * const setting);
#endif // _di_fss_write_main_process_help_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_write_main_h
