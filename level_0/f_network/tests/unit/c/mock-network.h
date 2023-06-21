/**
 * FLL - Level 0
 *
 * Project: Network
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the network project.
 */
#ifndef _MOCK__network_h
#define _MOCK__network_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/network.h>

#ifdef __cplusplus
extern "C" {
#endif

const static int mock_errno_generic = 32767;

extern uint32_t __wrap_htonl(uint32_t hostlong);
extern uint16_t __wrap_htons(uint16_t hostshort);
extern uint32_t __wrap_ntohl(uint32_t netlong);
extern uint16_t __wrap_ntohs(uint16_t netshort);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _MOCK__network_h
