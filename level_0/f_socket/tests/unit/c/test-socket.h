/**
 * FLL - Level 0
 *
 * Project: Socket
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the socket project.
 */
#ifndef _TEST__F_socket_h
#define _TEST__F_socket_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/socket.h>

// Mock includes.
#include "mock-socket.h"

// Test includes.
#include "test-socket-accept.h"
#include "test-socket-addressss_delete_callback.h"
#include "test-socket-addressss_destroy_callback.h"
#include "test-socket-bind.h"
#include "test-socket-bind_inet4.h"
#include "test-socket-bind_inet6.h"
#include "test-socket-bind_local.h"
#include "test-socket-connect.h"
#include "test-socket-create.h"
#include "test-socket-create_pair.h"
#include "test-socket-disconnect.h"
#include "test-socket-listen.h"
#include "test-socket-name_host.h"
#include "test-socket-name_peer.h"
#include "test-socket-option_get.h"
#include "test-socket-option_set.h"
#include "test-socket-read.h"
#include "test-socket-read_message.h"
#include "test-socket-read_stream.h"
#include "test-socket-ss_delete_callback.h"
#include "test-socket-ss_destroy_callback.h"
#include "test-socket-write.h"
#include "test-socket-write_message.h"
#include "test-socket-write_stream.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform any setup operations.
 *
 * @param state
 *   The test state.
 *
 * @return
 *   The status of this function, where 0 means success.
 */
extern int setup(void **state);

/**
 * Peform any setdown operations.
 *
 * @param state
 *   The test state.
 *
 * @return
 *   The status of this function, where 0 means success.
 */
extern int setdown(void **state);

/**
 * Run all tests.
 *
 * @return
 *   The final result of the tests.
 *
 * @see cmocka_run_group_tests()
 * @see cmocka_unit_test()
 */
extern int main(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _TEST__F_socket_h
