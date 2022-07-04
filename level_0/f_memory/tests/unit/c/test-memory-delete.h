/**
 * FLL - Level 0
 *
 * Project: Memory
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the memory project.
 */
#ifndef _TEST__F_memory__delete
#define _TEST__F_memory__delete

/**
 * Test that deallocation works for adjusted memory.
 *
 * @see f_memory_adjust()
 * @see f_memory_delete()
 * @see f_memory_new()
 */
extern void test__f_memory_delete__frees_adjusted_memory(void **state);

/**
 * Test that deallocation works for aligned memory.
 *
 * @see f_memory_delete()
 * @see f_memory_new_aligned()
 */
extern void test__f_memory_delete__frees_aligned_memory(void **state);

/**
 * Test that deallocation works.
 *
 * @see f_memory_delete()
 * @see f_memory_new()
 */
extern void test__f_memory_delete__frees_memory(void **state);

/**
 * Test that deallocation works for resized memory.
 *
 * @see f_memory_delete()
 * @see f_memory_new()
 * @see f_memory_resize()
 */
extern void test__f_memory_delete__frees_resized_memory(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_memory_delete()
 */
extern void test__f_memory_delete__parameter_checking(void **state);

#endif // _TEST__F_memory__delete
