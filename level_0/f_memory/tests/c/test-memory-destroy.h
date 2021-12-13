/**
 * FLL - Level 0
 *
 * Project: Memory
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the memory project.
 */
#ifndef _TEST__F_memory__destroy
#define _TEST__F_memory__destroy

/**
 * Test that deallocation works for adjusted memory.
 *
 * @see f_memory_adjust()
 * @see f_memory_destroy()
 * @see f_memory_new()
 */
extern void test__f_memory_destroy__frees_adjusted_memory(void **state);

/**
 * Test that deallocation works for aligned memory.
 *
 * @see f_memory_destroy()
 * @see f_memory_new_aligned()
 */
extern void test__f_memory_destroy__frees_aligned_memory(void **state);

/**
 * Test that deallocation works.
 *
 * @see f_memory_destroy()
 * @see f_memory_new()
 */
extern void test__f_memory_destroy__frees_memory(void **state);

/**
 * Test that deallocation works for resized memory.
 *
 * @see f_memory_destroy()
 * @see f_memory_new()
 * @see f_memory_resize()
 */
extern void test__f_memory_destroy__frees_resized_memory(void **state);

#endif // _TEST__F_memory__destroy
