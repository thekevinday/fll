/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the type_array project.
 */
#ifndef _MOCK__type_array_h
#define _MOCK__type_array_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/type_array.h>
#include <fll/level_0/type_array_file.h>

#ifdef __cplusplus
extern "C" {
#endif

const static int mock_errno_generic = 32767;

extern int mock_unwrap;
extern int mock_unwrap_f_memory;

extern f_status_t __real_f_memory_array_adjust(const f_number_unsigned_t length, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size);
extern f_status_t __real_f_memory_array_resize(const f_number_unsigned_t length, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size);

extern f_status_t __real_f_memory_arrays_adjust(const f_number_unsigned_t length, const size_t width, void ** const array, f_number_unsigned_t * const used, f_number_unsigned_t * const size, f_status_t (*callback)(const f_number_unsigned_t start, const f_number_unsigned_t size, void * const array));
extern f_status_t __real_f_memory_arrays_resize(const f_number_unsigned_t length, const size_t width, void ** const array, f_number_unsigned_t * const used, f_number_unsigned_t * const size, f_status_t (*callback)(const f_number_unsigned_t start, const f_number_unsigned_t size, void * const array));

extern int __real_poll(f_poll_t *fds, nfds_t nfds, int timeout);

extern f_status_t __wrap_f_memory_array_adjust(const f_number_unsigned_t length, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size);
extern f_status_t __wrap_f_memory_array_resize(const f_number_unsigned_t length, const size_t width, void ** array, f_number_unsigned_t * const used, f_number_unsigned_t * const size);

extern f_status_t __wrap_f_memory_arrays_adjust(const f_number_unsigned_t length, const size_t width, void ** const array, f_number_unsigned_t * const used, f_number_unsigned_t * const size, f_status_t (*callback)(const f_number_unsigned_t start, const f_number_unsigned_t size, void * const array));
extern f_status_t __wrap_f_memory_arrays_resize(const f_number_unsigned_t length, const size_t width, void ** const array, f_number_unsigned_t * const used, f_number_unsigned_t * const size, f_status_t (*callback)(const f_number_unsigned_t start, const f_number_unsigned_t size, void * const array));

extern int __wrap_poll(f_poll_t *fds, nfds_t nfds, int timeout);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _MOCK__type_array_h