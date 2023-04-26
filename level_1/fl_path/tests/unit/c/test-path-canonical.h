/**
 * FLL - Level 2
 *
 * Project: IKI
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the fll_path project.
 */
#ifndef _TEST__FLL_path_canonical_h
#define _TEST__FLL_path_canonical_h

/**
 * Test that function works with back paths (such as '../').
 *
 * @see fl_path_canonical()
 */
extern void test__fll_path_canonical__back_paths(void **state);

/**
 * Test that function returns the present working directory when path is an empty string.
 *
 * @see fl_path_canonical()
 */
extern void test__fll_path_canonical__empty_becomes_pwd(void **state);

/**
 * Test that function works with present directory paths.
 *
 * @see fl_path_canonical()
 */
extern void test__fll_path_canonical__present_paths(void **state);

/**
 * Test that function works with root paths.
 *
 * @see fl_path_canonical()
 */
extern void test__fll_path_canonical__root_paths(void **state);

/**
 * Test that function returns the string without expanding the tilde.
 *
 * @see fl_path_canonical()
 */
extern void test__fll_path_canonical__tilde_remains(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see fl_path_canonical()
 */
extern void test__fll_path_canonical__parameter_checking(void **state);

#endif // _TEST__FLL_path_canonical_h
