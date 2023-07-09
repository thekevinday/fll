/**
 * FLL - Level 3
 *
 * Project: FSS Identify
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides load functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fss_identify_load_h
#define _fss_identify_load_h

/**
 * Load a pipe or a file 1 block at a time untul a newline is found.
 *
 * @param main
 *   The main program and settings data.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_file_stream_read_block().
 *     Errors (with error bit) from: f_string_dynamic_resize().
 *
 * @param main
 *   The main program data.
 * @param name
 *   The name of the file.
 *   file_name.used to 0 to designate that this is a pipe.
 *
 * @see f_file_stream_read_block()
 * @see f_string_dynamic_resize()
 */
#ifndef _di_fss_identify_load_line_
  extern void fss_identify_load_line(fss_identify_main_t * const main, const f_string_static_t name);
#endif // _di_fss_identify_load_line_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fss_identify_load_h
