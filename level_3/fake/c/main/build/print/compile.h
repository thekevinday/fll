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
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_important_simple()
 */
#ifndef _di_fake_build_print_compile_library_shared_
  extern f_status_t fake_build_print_compile_library_shared(fl_print_t * const print);
#endif // _di_fake_build_print_compile_library_shared_

/**
 * Print message when compiling a static library.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_important_simple()
 */
#ifndef _di_fake_build_print_compile_library_static_
  extern f_status_t fake_build_print_compile_library_static(fl_print_t * const print);
#endif // _di_fake_build_print_compile_library_static_

/**
 * Print message when compiling a shared object.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_important_simple()
 */
#ifndef _di_fake_build_print_compile_object_shared_
  extern f_status_t fake_build_print_compile_object_shared(fl_print_t * const print);
#endif // _di_fake_build_print_compile_object_shared_

/**
 * Print message when compiling a static object.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_important_simple()
 */
#ifndef _di_fake_build_print_compile_object_static_
  extern f_status_t fake_build_print_compile_object_static(fl_print_t * const print);
#endif // _di_fake_build_print_compile_object_static_

/**
 * Print message when compiling a static object for a library.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_important_simple()
 */
#ifndef _di_fake_build_print_compile_object_static_library_
  extern f_status_t fake_build_print_compile_object_static_library(fl_print_t * const print);
#endif // _di_fake_build_print_compile_object_static_library_

/**
 * Print message when compiling a shared program.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_important_simple()
 */
#ifndef _di_fake_build_print_compile_program_shared_
  extern f_status_t fake_build_print_compile_program_shared(fl_print_t * const print);
#endif // _di_fake_build_print_compile_program_shared_

/**
 * Print message when compiling a static program.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fake_print_context_important_simple()
 */
#ifndef _di_fake_build_print_compile_program_static_
  extern f_status_t fake_build_print_compile_program_static(fl_print_t * const print);
#endif // _di_fake_build_print_compile_program_static_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_build_print_compile_h
