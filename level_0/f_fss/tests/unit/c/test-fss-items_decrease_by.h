/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test items decrease by in the fss project.
 */
#ifndef _TEST__F_fss__items_decrease_by
#define _TEST__F_fss__items_decrease_by

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_fss_items_decrease_by()
 */
extern void test__f_fss_items_decrease_by__parameter_checking(void **state);

/**
 * Test that the function returns F_data_not.
 *
 * @see f_fss_items_decrease_by()
 */
extern void test__f_fss_items_decrease_by__returns_data_not(void **state);

/**
 * Test that the function works.
 *
 * @see f_fss_items_decrease_by()
 */
extern void test__f_fss_items_decrease_by__works(void **state);

#endif // _TEST__F_fss__items_decrease_by
