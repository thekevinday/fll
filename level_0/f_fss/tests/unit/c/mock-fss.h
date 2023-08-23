/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the fss project.
 */
#ifndef _MOCK__fss_h
#define _MOCK__fss_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/fss.h>

#ifdef __cplusplus
extern "C" {
#endif

const static int mock_errno_generic = 32767;

extern int mock_unwrap;
extern int mock_unwrap_f_memory;

extern f_status_t __real_f_memory_array_adjust(const f_number_unsigned_t length, const size_t width, void ** const array, f_number_unsigned_t * const used, f_number_unsigned_t * const size);
extern f_status_t __real_f_memory_array_resize(const f_number_unsigned_t length, const size_t width, void ** const array, f_number_unsigned_t * const used, f_number_unsigned_t * const size);
extern f_status_t __real_f_memory_arrays_adjust(const f_number_unsigned_t length, const size_t width, void ** const array, f_number_unsigned_t * const used, f_number_unsigned_t * const size, f_status_t (*callback)(const f_number_unsigned_t start, const f_number_unsigned_t size, void * const array));
extern f_status_t __real_f_memory_arrays_resize(const f_number_unsigned_t length, const size_t width, void ** const array, f_number_unsigned_t * const used, f_number_unsigned_t * const size, f_status_t (*callback)(const f_number_unsigned_t start, const f_number_unsigned_t size, void * const array));

extern f_status_t __real_f_string_ranges_adjust(const f_number_unsigned_t length, f_string_ranges_t * const structure);
extern f_status_t __real_f_string_ranges_resize(const f_number_unsigned_t length, f_string_ranges_t * const structure);
extern f_status_t __real_f_string_rangess_adjust(const f_number_unsigned_t length, f_string_ranges_t * const structure);
extern f_status_t __real_f_string_rangess_resize(const f_number_unsigned_t length, f_string_ranges_t * const structure);

extern f_status_t __wrap_f_memory_array_adjust(const f_number_unsigned_t length, const size_t width, void ** const array, f_number_unsigned_t * const used, f_number_unsigned_t * const size);
extern f_status_t __wrap_f_memory_array_resize(const f_number_unsigned_t length, const size_t width, void ** const array, f_number_unsigned_t * const used, f_number_unsigned_t * const size);
extern f_status_t __wrap_f_memory_arrays_adjust(const f_number_unsigned_t length, const size_t width, void ** const array, f_number_unsigned_t * const used, f_number_unsigned_t * const size, f_status_t (*callback)(const f_number_unsigned_t start, const f_number_unsigned_t size, void * const array));
extern f_status_t __wrap_f_memory_arrays_resize(const f_number_unsigned_t length, const size_t width, void ** const array, f_number_unsigned_t * const used, f_number_unsigned_t * const size, f_status_t (*callback)(const f_number_unsigned_t start, const f_number_unsigned_t size, void * const array));

extern f_status_t __wrap_f_string_ranges_adjust(const f_number_unsigned_t length, f_string_ranges_t * const structure);
extern f_status_t __wrap_f_string_ranges_resize(const f_number_unsigned_t length, f_string_ranges_t * const structure);
extern f_status_t __wrap_f_string_rangess_adjust(const f_number_unsigned_t length, f_string_ranges_t * const structure);
extern f_status_t __wrap_f_string_rangess_resize(const f_number_unsigned_t length, f_string_ranges_t * const structure);

//extern long __wrap_sysconf(int name);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _MOCK__fss_h
