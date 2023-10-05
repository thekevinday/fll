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
#include <poll.h>

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
 * Properties:
 *   - stream:     File stream.
 *   - id:         File descriptor, with a value of -1 represents a closed file.
 *   - flag:       Flags used for opening the file.
 *   - size_read:  The default number of 1-byte characters to read at a time and is often used for the read buffer size.
 *   - size_write: The default number of 1-byte characters to read at a time and is often used for the write buffer size.
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

  #define macro_f_file_t_initialize_1(stream, id, flag, read_size, write_size) { stream, id, flag, read_size, write_size }
  #define macro_f_file_t_initialize_2(stream, id, flag) { stream, id, flag, F_file_default_size_read_d, F_file_default_size_write_d }
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

/**
 * An array of f_file_t.
 *
 * The macros are defined in type_array.h or type_array_file.h.
 *
 * Properties:
 *   - array: The array of f_file_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_files_t_
  typedef struct {
    f_file_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_files_t;

  #define f_files_t_initialize { 0, 0, 0 }

  #define macro_f_files_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_files_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_files_t_

/**
 * This holds an array of f_files_t.
 *
 * The macros are defined in type_array.h or type_array_file.h.
 *
 * Properties:
 *   - array: The array of f_file_t arrays.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_filess_t_
  typedef struct {
    f_files_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_filess_t;

  #define f_filess_t_initialize { 0, 0, 0 }

  #define macro_f_filess_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_filess_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_filess_t_

/**
 * An enumeration of poll codes.
 *
 * f_poll_*_e:
 *   - error:   There is an error.
 *   - hang_up: Hang up (disconnect).
 *   - invalid: Invalid polling request.
 *   - read:    There is data to read.
 *   - urgent:  There is urgent data to read (aka "out of band").
 *   - write:   Writing will not block.
 *
 *   - message:      GNU poll message.
 *   - remove:       GNU poll remove.
 *   - hang_up_read: GNU poll hang up read.
 */
#ifndef _di_f_poll_e_
  enum {
    f_poll_error_e   = POLLERR,
    f_poll_hang_up_e = POLLHUP,
    f_poll_invalid_e = POLLNVAL,
    f_poll_read_e    = POLLIN,
    f_poll_urgent_e  = POLLPRI,
    f_poll_write_e   = POLLOUT,

    #ifdef POLLMSG
      f_poll_message_e = POLLMSG,
    #else
      f_poll_message_e = 0x400,
    #endif // POLLMSG

    #ifdef POLLREMOVE
      f_poll_remove_e = POLLREMOVE,
    #else
      f_poll_remove_e = 0x1000,
    #endif // POLLREMOVE

    #ifdef POLLRDHUP
      f_poll_hang_up_read_e = POLLRDHUP,
    #else
      f_poll_hang_up_read_e = 0x2000,
    #endif // POLLRDHUP
  }; // enum
#endif // _di_f_poll_e_

/**
 * A typdef for representing struct pollfd.
 */
#ifndef _di_f_poll_t_
  typedef struct pollfd f_poll_t;

  #define f_poll_t_initialize { 0 }

  #define macro_f_poll_t_initialize_1(fd, events, revents) { fd, events, revents }
  #define macro_f_poll_t_initialize_2(fd, events) { fd, events, 0 }
  #define macro_f_poll_t_initialize_3(fd) { fd, 0, 0 }
  #define macro_f_poll_t_initialize_4(events) { 0, events, 0 }
#endif // _di_f_poll_t_

/**
 * An array of pollfd structures.
 *
 * The macros are defined in type_array.h or type_array_file.h.
 *
 * If used for functions like poll() (a common use) then the max array length for used is limited to nfds_t which might be different from f_number_unsigned_t.
 * The nfds_t is often either uint32_t or an uint64_t.
 * The f_number_unsigned_t is often an uint64_t.
 *
 * Properties:
 *   - array: An array of f_poll_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_polls_t_
  typedef struct {
    f_poll_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_polls_t;

  #define f_polls_t_initialize { 0, 0, 0 }

  #define macro_f_polls_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_polls_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_polls_t_

/**
 * An array of f_polls_t.
 *
 * The macros are defined in type_array.h or type_array_file.h.
 *
 * Properties:
 *   - array: The array of f_polls_t.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_pollss_t_
  typedef struct {
    f_polls_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_pollss_t;

  #define f_pollss_t_initialize { 0, 0, 0 }

  #define macro_f_pollss_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_pollss_t_initialize_2(array, length) { array, length, length }
#endif // _di_f_pollss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_file_h
