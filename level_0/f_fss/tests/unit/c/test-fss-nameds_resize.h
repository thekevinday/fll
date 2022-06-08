/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test nameds resize in the fss project.
 */
#ifndef _TEST__F_fss__nameds_resize
#define _TEST__F_fss__nameds_resize

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_fss_nameds_resize()
 */
extern void test__f_fss_nameds_resize__parameter_checking(void **state);

/**
 * Test that the function works.
 *
 * @see f_fss_nameds_resize()
 */
extern void test__f_fss_nameds_resize__works(void **state);

#endif // _TEST__F_fss__nameds_resize