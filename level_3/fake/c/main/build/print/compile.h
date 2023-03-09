/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides build print compile functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_build_print_compile_h
#define _fake_build_print_compile_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print message when compiling a shared library.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_important_simple()
 */
#ifndef _di_fake_build_print_compile_library_shared_
  extern f_status_t fake_build_print_compile_library_shared(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_build_print_compile_library_shared_

/**
 * Print message when compiling a static library.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_important_simple()
 */
#ifndef _di_fake_build_print_compile_library_static_
  extern f_status_t fake_build_print_compile_library_static(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_build_print_compile_library_static_

/**
 * Print message when compiling a shared object.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_important_simple()
 */
#ifndef _di_fake_build_print_compile_object_shared_
  extern f_status_t fake_build_print_compile_object_shared(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_build_print_compile_object_shared_

/**
 * Print message when compiling a static object.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_important_simple()
 */
#ifndef _di_fake_build_print_compile_object_static_
  extern f_status_t fake_build_print_compile_object_static(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_build_print_compile_object_static_

/**
 * Print message when compiling a static object for a library.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_important_simple()
 */
#ifndef _di_fake_build_print_compile_object_static_library_
  extern f_status_t fake_build_print_compile_object_static_library(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_build_print_compile_object_static_library_

/**
 * Print message when compiling a shared program.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_important_simple()
 */
#ifndef _di_fake_build_print_compile_program_shared_
  extern f_status_t fake_build_print_compile_program_shared(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_build_print_compile_program_shared_

/**
 * Print message when compiling a static program.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.state.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_important_simple()
 */
#ifndef _di_fake_build_print_compile_program_static_
  extern f_status_t fake_build_print_compile_program_static(fake_setting_t * const setting, const fl_print_t print);
#endif // _di_fake_build_print_compile_program_static_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_build_print_compile_h