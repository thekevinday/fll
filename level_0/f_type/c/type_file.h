/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides file-related datatype definitions needed by multiple level_0 projects.
 * This should be kept to a bare minimum.
 * Most of the file related code should instead be in f_file project.
 *
 * This is not auto-included by type.h.
 * This is done to prevent depending on the stdio.h, unless required.
 */
#ifndef _F_type_file_h
#define _F_type_file_h

// Libc includes.
#include <stdio.h>
#include <fcntl.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Provide file defaults needed by f_file_t.
 *
 * These are intended to be in level 0 project f_file but are defined here due to a requirement by f_file_t.
 *
 * F_file_default_*:
 *   - read_size:  Default read size in bytes.
 *   - write_size: Default write size in bytes.
 */
#ifndef _di_f_type_file_defaults_d_
  #define F_file_default_size_read_d  8192
  #define F_file_default_size_write_d 8192
#endif // _di_f_type_file_defaults_d_

/**
 * File flag related functionality.
 */
#ifndef _di_f_type_file_flag_d_

  // This is not always defined, so ensure it is defined.
  #ifndef O_PATH
    #define O_PATH 010000000
  #endif // O_PATH

  // File open flags.
  #define F_file_flag_append_d             O_APPEND
  #define F_file_flag_asynchronous_d       O_ASYNC
  #define F_file_flag_create_d             O_CREAT
  #define F_file_flag_close_execute_d      O_CLOEXEC
  #define F_file_flag_direct_d             O_DIRECT
  #define F_file_flag_directory_d          O_DIRECTORY
  #define F_file_flag_exclusive_d          O_EXCL
  #define F_file_flag_large_file_d         O_LARGEFILE
  #define F_file_flag_no_access_time_d     O_NOATIME
  #define F_file_flag_no_follow_d          O_NOFOLLOW
  #define F_file_flag_no_tty_d             O_NOCTTY
  #define F_file_flag_non_blocking_d       O_NONBLOCK
  #define F_file_flag_path_d               O_PATH
  #define F_file_flag_read_only_d          O_RDONLY
  #define F_file_flag_read_write_d         O_RDWR
  #define F_file_flag_synchronous_d        O_SYNC
  #define F_file_flag_synchronous_direct_d O_DSYNC
  #define F_file_flag_temporary_d          O_TMPFILE
  #define F_file_flag_truncate_d           O_TRUNC
  #define F_file_flag_write_only_d         O_WRONLY

  // File open flags pre-combined with create.
  #define F_file_flag_create_ro_d (O_CREAT | O_RDONLY)
  #define F_file_flag_create_wo_d (O_CREAT | O_WRONLY)
  #define F_file_flag_create_rw_d (O_CREAT | O_RDRW)

  // File open flags pre-combined will fail if file exists.
  #define F_file_flag_create_new_ro_d (O_CREAT | O_EXCL | O_RDONLY)
  #define F_file_flag_create_new_wo_d (O_CREAT | O_EXCL | O_WRONLY)
  #define F_file_flag_create_new_rw_d (O_CREAT | O_EXCL | O_RDRW)

  // File open flags pre-combined will truncate any existing files to 0.
  #define F_file_flag_truncate_ro_d (O_CREAT | O_TRUNC | O_RDONLY)
  #define F_file_flag_truncate_rw_d (O_CREAT | O_TRUNC | O_RDRW)
  #define F_file_flag_truncate_wo_d (O_CREAT | O_TRUNC | O_WRONLY)

  // File open flags pre-combined will truncate any existing files to 0.
  #define F_file_flag_append_rw_d (O_CREAT | O_APPEND | O_RDRW)
  #define F_file_flag_append_wo_d (O_CREAT | O_APPEND | O_WRONLY)

  // File open flags pre-combined with synchronous io.
  #define F_file_flag_sync_ro_d            (O_SYNC | O_RDONLY)
  #define F_file_flag_sync_wo_d            (O_SYNC | O_WRONLY)
  #define F_file_flag_sync_rw_d            (O_SYNC | O_RDRW)
  #define F_file_flag_sync_create_ro_d     (O_SYNC | O_CREAT | O_RDONLY)
  #define F_file_flag_sync_create_wo_d     (O_SYNC | O_CREAT | O_WRONLY)
  #define F_file_flag_sync_create_rw_d     (O_SYNC | O_CREAT | O_RDRW)
  #define F_file_flag_sync_create_new_ro_d (O_SYNC | O_CREAT | O_EXCL | O_RDONLY)
  #define F_file_flag_sync_create_new_wo_d (O_SYNC | O_CREAT | O_EXCL | O_WRONLY)
  #define F_file_flag_sync_create_new_rw_d (O_SYNC | O_CREAT | O_EXCL | O_RDRW)

  // File open flags pre-combined with asynchronous io.
  #define F_file_flag_async_ro_d            (O_ASYNC | O_RDONLY)
  #define F_file_flag_async_wo_d            (O_ASYNC | O_WRONLY)
  #define F_file_flag_async_rw_d            (O_ASYNC | O_RDRW)
  #define F_file_flag_async_create_ro_d     (O_ASYNC | O_CREAT | O_RDONLY)
  #define F_file_flag_async_create_wo_d     (O_ASYNC | O_CREAT | O_WRONLY)
  #define F_file_flag_async_create_rw_d     (O_ASYNC | O_CREAT | O_RDRW)
  #define F_file_flag_async_create_new_ro_d (O_ASYNC | O_CREAT | O_EXCL | O_RDONLY)
  #define F_file_flag_async_create_new_wo_d (O_ASYNC | O_CREAT | O_EXCL | O_WRONLY)
  #define F_file_flag_async_create_new_rw_d (O_ASYNC | O_CREAT | O_EXCL | O_RDRW)

  // File open flags pre-combined with direct io (which works synchronously).
  #define F_file_flag_direct_ro_d            (O_DIRECT | O_RDONLY)
  #define F_file_flag_direct_wo_d            (O_DIRECT | O_WRONLY)
  #define F_file_flag_direct_rw_d            (O_DIRECT | O_RDRW)
  #define F_file_flag_direct_create_ro_d     (O_DIRECT | O_CREAT | O_RDONLY)
  #define F_file_flag_direct_create_wo_d     (O_DIRECT | O_CREAT | O_WRONLY)
  #define F_file_flag_direct_create_rw_d     (O_DIRECT | O_CREAT | O_RDRW)
  #define F_file_flag_direct_create_new_ro_d (O_DIRECT | O_CREAT | O_EXCL | O_RDONLY)
  #define F_file_flag_direct_create_new_wo_d (O_DIRECT | O_CREAT | O_EXCL | O_WRONLY)
  #define F_file_flag_direct_create_new_rw_d (O_DIRECT | O_CREAT | O_EXCL | O_RDRW)

  // File open flags pre-combined with large_file.
  #define F_file_flag_large_ro_d                  (O_LARGEFILE | O_RDONLY)
  #define F_file_flag_large_wo_d                  (O_LARGEFILE | O_WRONLY)
  #define F_file_flag_large_rw_d                  (O_LARGEFILE | O_RDRW)
  #define F_file_flag_large_sync_ro_d             (O_LARGEFILE | O_SYNC | O_RDONLY)
  #define F_file_flag_large_sync_wo_d             (O_LARGEFILE | O_SYNC | O_WRONLY)
  #define F_file_flag_large_sync_rw_d             (O_LARGEFILE | O_SYNC | O_RDRW)
  #define F_file_flag_large_sync_create_ro_d      (O_LARGEFILE | O_SYNC | O_CREAT | O_RDONLY)
  #define F_file_flag_large_sync_create_wo_d      (O_LARGEFILE | O_SYNC | O_CREAT | O_WRONLY)
  #define F_file_flag_large_sync_create_rw_d      (O_LARGEFILE | O_SYNC | O_CREAT | O_RDRW)
  #define F_file_flag_large_sync_create_new_ro_d  (O_LARGEFILE | O_SYNC | O_CREAT | O_EXCL | O_RDONLY)
  #define F_file_flag_large_sync_create_new_wo_d  (O_LARGEFILE | O_SYNC | O_CREAT | O_EXCL | O_WRONLY)
  #define F_file_flag_large_sync_create_new_rw_d  (O_LARGEFILE | O_SYNC | O_CREAT | O_EXCL | O_RDRW)
  #define F_file_flag_large_async_ro_d            (O_LARGEFILE | O_ASYNC | O_RDONLY)
  #define F_file_flag_large_async_wo_d            (O_LARGEFILE | O_ASYNC | O_WRONLY)
  #define F_file_flag_large_async_rw_d            (O_LARGEFILE | O_ASYNC | O_RDRW)
  #define F_file_flag_large_async_create_ro_d     (O_LARGEFILE | O_ASYNC | O_CREAT | O_RDONLY)
  #define F_file_flag_large_async_create_wo_d     (O_LARGEFILE | O_ASYNC | O_CREAT | O_WRONLY)
  #define F_file_flag_large_async_create_rw_d     (O_LARGEFILE | O_ASYNC | O_CREAT | O_RDRW)
  #define F_file_flag_large_async_create_new_ro_d (O_LARGEFILE | O_ASYNC | O_CREAT | O_EXCL | O_RDONLY)
  #define F_file_flag_large_async_create_new_wo_d (O_LARGEFILE | O_ASYNC | O_CREAT | O_EXCL | O_WRONLY)
  #define F_file_flag_large_async_create_new_rw_d (O_LARGEFILE | O_ASYNC | O_CREAT | O_EXCL | O_RDRW)
#endif // _di_f_type_file_flag_d_

/**
 * Commonly used file related properties.
 *
 * stream:     File stream.
 * id:         File descriptor, with a value of -1 represents a closed file.
 * flag:       Flags used for opening the file.
 * size_read:  The default number of 1-byte characters to read at a time and is often used for the read buffer size.
 * size_write: The default number of 1-byte characters to read at a time and is often used for the write buffer size.
 */
#ifndef _di_f_file_t_
  typedef struct {
    FILE   *stream;
    int    id;
    int    flag;
    size_t size_read;
    size_t size_write;
  } f_file_t;

  #define f_file_t_initialize { 0, -1, O_RDONLY, F_file_default_size_read_d, F_file_default_size_write_d }

  #define macro_f_file_t_initialize(stream, id, flag, read_size, write_size) { stream, id, flag, read_size, write_size }
  #define macro_f_file_t_initialize2(stream, id, flag) { stream, id, flag, F_file_default_size_read_d, F_file_default_size_write_d }
  #define macro_f_file_t_initialize_id(id) { 0, id, O_RDONLY, F_file_default_size_read_d, F_file_default_size_write_d }
  #define macro_f_file_t_initialize_stream(stream) { stream, -1, O_RDONLY, F_file_default_size_read_d, F_file_default_size_write_d }

  #define macro_f_file_t_clear(file) \
    file.stream = 0; \
    file.id = -1; \
    file.flag = 0; \
    file.size_read = 0; \
    file.size_write = 0;

  #define macro_f_file_t_reset(file) \
    file.stream = 0; \
    file.id = -1; \
    file.flag = O_RDONLY; \
    file.size_read = F_file_default_size_read_d; \
    file.size_write = F_file_default_size_write_d;
#endif // _di_f_file_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_file_h
