/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the file project.
 */
#ifndef _TEST__F_file_h
#define _TEST__F_file_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/file.h>

// Mock includes.
#include "mock-file.h"

// Test includes.
#include "test-file-access.h"
#include "test-file-access_at.h"
#include "test-file-clone.h"
#include "test-file-close.h"
#include "test-file-close_id.h"
#include "test-file-copy.h"
#include "test-file-create.h"
#include "test-file-create_at.h"
#include "test-file-create_device.h"
#include "test-file-create_device_at.h"
#include "test-file-create_fifo.h"
#include "test-file-create_fifo_at.h"
#include "test-file-create_node.h"
#include "test-file-create_node_at.h"
#include "test-file-descriptor.h"
#include "test-file-exists.h"
#include "test-file-exists_at.h"
#include "test-file-flush.h"
#include "test-file-group_read.h"
#include "test-file-is.h"
#include "test-file-is_at.h"
#include "test-file-is_stat.h"
#include "test-file-link.h"
#include "test-file-link_at.h"
#include "test-file-link_hard.h"
#include "test-file-link_hard_at.h"
#include "test-file-link_read.h"
#include "test-file-link_read_at.h"
#include "test-file-manipulate.h"
#include "test-file-mode_determine.h"
#include "test-file-mode_from_string.h"
#include "test-file-mode_read.h"
#include "test-file-mode_read_at.h"
#include "test-file-mode_set.h"
#include "test-file-mode_set_at.h"
#include "test-file-mode_to_mode.h"
#include "test-file-name_base.h"
#include "test-file-name_directory.h"
#include "test-file-open.h"
#include "test-file-open_at.h"
#include "test-file-owner_read.h"
#include "test-file-poll.h"
#include "test-file-read.h"
#include "test-file-read_block.h"
#include "test-file-read_until.h"
#include "test-file-remove.h"
#include "test-file-remove_at.h"
#include "test-file-rename.h"
#include "test-file-rename_at.h"
#include "test-file-role_change.h"
#include "test-file-role_change_at.h"
#include "test-file-seek.h"
#include "test-file-select.h"
#include "test-file-select_signal.h"
#include "test-file-size.h"
#include "test-file-size_at.h"
#include "test-file-size_by_id.h"
#include "test-file-stat.h"
#include "test-file-stat_at.h"
#include "test-file-stat_by_id.h"
#include "test-file-stream_close.h"
#include "test-file-stream_open_descriptor.h"
#include "test-file-stream_open.h"
#include "test-file-stream_read.h"
#include "test-file-stream_read_block.h"
#include "test-file-stream_read_until.h"
#include "test-file-stream_reopen.h"
#include "test-file-stream_write.h"
#include "test-file-stream_write_block.h"
#include "test-file-stream_write_until.h"
#include "test-file-stream_write_range.h"
#include "test-file-touch.h"
#include "test-file-touch_at.h"
#include "test-file-type.h"
#include "test-file-type_at.h"
#include "test-file-umask_get.h"
#include "test-file-umask_set.h"
#include "test-file-write.h"
#include "test-file-write_block.h"
#include "test-file-write_until.h"
#include "test-file-write_range.h"

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

#endif // _TEST__F_file_h
