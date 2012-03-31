/* FLL - Level 0
 * Project:       File
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 *  Provides structures and data types for a file I/O.
 *  Provides operations for opening/closing files
 */
#ifndef _F_file_h
#define _F_file_h

// libc includes
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

// fll-0 includes
#include <level_0/strings.h>
#include <level_0/types.h>
#include <level_0/errors.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_f_file_types_
  typedef f_s_int  f_file_id;
  typedef f_string f_file_mode;
  typedef f_mode_t f_file_mask;

  #define f_file_default_read_size 4096 // default to 4k read sizes
  #define f_file_max_path_length   1024
#endif // _di_f_file_types_

#ifndef _di_f_file_oldstyle_modes_
  #define f_file_read_only         "r"
  #define f_file_read_write        "r+"
  #define f_file_read_write_create "rw"
  #define f_file_read_write_append "a+"
  #define f_file_write_create      "w"
  #define f_file_write_append      "a"
#endif // _di_f_file_oldstyle_modes_

#ifndef _di_f_file_seeks_
  #define f_file_seek_from_beginning(file, bytes) fseek(file, bytes, SEEK_SET)
  #define f_file_seek_from_current(file, bytes)   fseek(file, bytes, SEEK_CUR)
  #define f_file_seek_from_end(file, bytes)       fseek(file, bytes, SEEK_END)
#endif // _di_f_file_seeks_

#ifndef _di_f_file_
  typedef struct {
    f_file_id    id;        // file descriptor
    f_file_type  file;      // the file data type
    f_file_mode  mode;      // how the file is to be accessed (or is being accessed)
    f_size_t     byte_size; // how many bytes to use on each read/write (for normal string handling this should be sizeof(f_string)
  } f_file;

  #define f_file_initialize { 0, 0, (f_file_mode) f_file_read_only, sizeof(f_autochar) }
#endif // _di_f_file_

#ifndef _di_f_file_position_
  // buffer_start designate where to start writing to the buffer
  // file_start is the positions where to begin reading the file
  // total_elements is the total number of elements to read from the file into the buffer
  // if total_elements is set to 0, then this means to buffer the entire file no matter how big it is (crazy?)
  typedef struct {
    f_string_length buffer_start;
    f_string_length file_start;
    f_string_length total_elements;
  } f_file_position;

  #define f_file_position_initialize { 0, 0, 0 }
#endif // _di_f_file_position_

// TODO: the information below needs to be confirmed and updated accordingly..
#ifndef _di_f_file_modes_

  // file open modes
  #define f_file_mode_read_only    O_RDONLY
  #define f_file_mode_write_only   O_WRONLY
  #define f_file_mode_read_write   O_RDWR
  #define f_file_mode_create       O_CREAT
  #define f_file_mode_exclusive    O_EXCL
  #define f_file_mode_no_tty       O_NOCTTY
  #define f_file_mode_truncate     O_TRUNC
  #define f_file_mode_append       O_APPEND
  #define f_file_mode_non_blocking O_NONBLOCK
  #define f_file_mode_synchronous  O_SYNC
  #define f_file_mode_no_follow    O_NOFOLLOW
  #define f_file_mode_directory    O_DIRECTORY
  #define f_file_mode_direct_io    O_DIRECT
  #define f_file_mode_asynchronous O_ASYNC
  #define f_file_mode_large_file   O_LARGEFILE

  // file open modes pre-combined with create
  #define f_file_mode_create_ro (O_CREAT | O_RDONLY)
  #define f_file_mode_create_wo (O_CREAT | O_WRONLY)
  #define f_file_mode_create_rw (O_CREAT | O_RDRW)

  // file open modes pre-combined will fail if file exists
  #define f_file_mode_create_new_ro (O_CREAT | O_EXCL | O_RDONLY)
  #define f_file_mode_create_new_wo (O_CREAT | O_EXCL | O_WRONLY)
  #define f_file_mode_create_new_rw (O_CREAT | O_EXCL | O_RDRW)

  // file open modes pre-combined with synchronous io
  #define f_file_mode_sync_ro            (O_SYNC | O_RDONLY)
  #define f_file_mode_sync_wo            (O_SYNC | O_WRONLY)
  #define f_file_mode_sync_rw            (O_SYNC | O_RDRW)
  #define f_file_mode_sync_create_ro     (O_SYNC | O_CREAT | O_RDONLY)
  #define f_file_mode_sync_create_wo     (O_SYNC | O_CREAT | O_WRONLY)
  #define f_file_mode_sync_create_rw     (O_SYNC | O_CREAT | O_RDRW)
  #define f_file_mode_sync_create_new_ro (O_SYNC | O_CREAT | O_EXCL | O_RDONLY)
  #define f_file_mode_sync_create_new_wo (O_SYNC | O_CREAT | O_EXCL | O_WRONLY)
  #define f_file_mode_sync_create_new_rw (O_SYNC | O_CREAT | O_EXCL | O_RDRW)

  // file open modes pre-combined with asynchronous io
  #define f_file_mode_async_ro            (O_ASYNC | O_RDONLY)
  #define f_file_mode_async_wo            (O_ASYNC | O_WRONLY)
  #define f_file_mode_async_rw            (O_ASYNC | O_RDRW)
  #define f_file_mode_async_create_ro     (O_ASYNC | O_CREAT | O_RDONLY)
  #define f_file_mode_async_create_wo     (O_ASYNC | O_CREAT | O_WRONLY)
  #define f_file_mode_async_create_rw     (O_ASYNC | O_CREAT | O_RDRW)
  #define f_file_mode_async_create_new_ro (O_ASYNC | O_CREAT | O_EXCL | O_RDONLY)
  #define f_file_mode_async_create_new_wo (O_ASYNC | O_CREAT | O_EXCL | O_WRONLY)
  #define f_file_mode_async_create_new_rw (O_ASYNC | O_CREAT | O_EXCL | O_RDRW)

  // file open modes pre-combined with direct io (which works synchronously)
  #define f_file_mode_direct_ro            (O_DIRECT | O_RDONLY)
  #define f_file_mode_direct_wo            (O_DIRECT | O_WRONLY)
  #define f_file_mode_direct_rw            (O_DIRECT | O_RDRW)
  #define f_file_mode_direct_create_ro     (O_DIRECT | O_CREAT | O_RDONLY)
  #define f_file_mode_direct_create_wo     (O_DIRECT | O_CREAT | O_WRONLY)
  #define f_file_mode_direct_create_rw     (O_DIRECT | O_CREAT | O_RDRW)
  #define f_file_mode_direct_create_new_ro (O_DIRECT | O_CREAT | O_EXCL | O_RDONLY)
  #define f_file_mode_direct_create_new_wo (O_DIRECT | O_CREAT | O_EXCL | O_WRONLY)
  #define f_file_mode_direct_create_new_rw (O_DIRECT | O_CREAT | O_EXCL | O_RDRW)

  // file open modes pre-combined with large_file
  #define f_file_mode_large_ro                  (O_LARGEFILE | O_RDONLY)
  #define f_file_mode_large_wo                  (O_LARGEFILE | O_WRONLY)
  #define f_file_mode_large_rw                  (O_LARGEFILE | O_RDRW)
  #define f_file_mode_large_sync_ro             (O_LARGEFILE | O_SYNC | O_RDONLY)
  #define f_file_mode_large_sync_wo             (O_LARGEFILE | O_SYNC | O_WRONLY)
  #define f_file_mode_large_sync_rw             (O_LARGEFILE | O_SYNC | O_RDRW)
  #define f_file_mode_large_sync_create_ro      (O_LARGEFILE | O_SYNC | O_CREAT | O_RDONLY)
  #define f_file_mode_large_sync_create_wo      (O_LARGEFILE | O_SYNC | O_CREAT | O_WRONLY)
  #define f_file_mode_large_sync_create_rw      (O_LARGEFILE | O_SYNC | O_CREAT | O_RDRW)
  #define f_file_mode_large_sync_create_new_ro  (O_LARGEFILE | O_SYNC | O_CREAT | O_EXCL | O_RDONLY)
  #define f_file_mode_large_sync_create_new_wo  (O_LARGEFILE | O_SYNC | O_CREAT | O_EXCL | O_WRONLY)
  #define f_file_mode_large_sync_create_new_rw  (O_LARGEFILE | O_SYNC | O_CREAT | O_EXCL | O_RDRW)
  #define f_file_mode_large_async_ro            (O_LARGEFILE | O_ASYNC | O_RDONLY)
  #define f_file_mode_large_async_wo            (O_LARGEFILE | O_ASYNC | O_WRONLY)
  #define f_file_mode_large_async_rw            (O_LARGEFILE | O_ASYNC | O_RDRW)
  #define f_file_mode_large_async_create_ro     (O_LARGEFILE | O_ASYNC | O_CREAT | O_RDONLY)
  #define f_file_mode_large_async_create_wo     (O_LARGEFILE | O_ASYNC | O_CREAT | O_WRONLY)
  #define f_file_mode_large_async_create_rw     (O_LARGEFILE | O_ASYNC | O_CREAT | O_RDRW)
  #define f_file_mode_large_async_create_new_ro (O_LARGEFILE | O_ASYNC | O_CREAT | O_EXCL | O_RDONLY)
  #define f_file_mode_large_async_create_new_wo (O_LARGEFILE | O_ASYNC | O_CREAT | O_EXCL | O_WRONLY)
  #define f_file_mode_large_async_create_new_rw (O_LARGEFILE | O_ASYNC | O_CREAT | O_EXCL | O_RDRW)

  // file permission modes
  #define f_file_mode_owner_rwx S_IRWXU
  #define f_file_mode_owner_r   S_IRUSR
  #define f_file_mode_owner_w   S_IWUSR
  #define f_file_mode_owner_x   S_IXUSR
  #define f_file_mode_owner_rw  (S_IRUSR | S_IWUSR)
  #define f_file_mode_owner_rx  (S_IRUSR | S_IXUSR)
  #define f_file_mode_owner_wx  (S_IWUSR | S_IXUSR)
  #define f_file_mode_group_rwx S_IRWXG
  #define f_file_mode_group_r   S_IRGRP
  #define f_file_mode_group_w   S_IWGRP
  #define f_file_mode_group_x   S_IXGRP
  #define f_file_mode_group_rw  (S_IRGRP | S_IWGRP)
  #define f_file_mode_group_rx  (S_IRGRP | S_IXGRP)
  #define f_file_mode_group_wx  (S_IWGRP | S_IXGRP)
  #define f_file_mode_world_rwx S_IRWXO
  #define f_file_mode_world_r   S_IROTH
  #define f_file_mode_world_w   S_IWOTH
  #define f_file_mode_world_x   S_IXOTH
  #define f_file_mode_world_rw  (S_IROTH | S_IWOTH)
  #define f_file_mode_world_rx  (S_IROTH | S_IXOTH)
  #define f_file_mode_world_wx  (S_IWOTH | S_IXOTH)
#endif // _di_f_file_modes_

#ifndef _di_f_file_open_
  // open a particular file and save its stream
  // filename = name of the file
  extern f_return_status f_file_open(f_file *file_information, const f_string filename);
#endif // _di_f_file_open_

#ifndef _di_f_file_close_
  // close file
  extern f_return_status f_file_close(f_file *file_information);
#endif // _di_f_file_close_

#ifndef _di_f_file_flush_
  // flush file
  extern f_return_status f_file_flush(f_file *file_information);
#endif // _di_f_file_flush_

#ifndef _di_f_file_read_
  // read a given amount of data from the buffer, will auto-seek to where
  extern f_return_status f_file_read(f_file *file_information, f_dynamic_string *buffer, const f_file_position location);
#endif // _di_f_file_read_

#ifndef _di_f_file_read_fifo_
  // read a given amount of data from the buffer, will not auto seek
  extern f_return_status f_file_read_fifo(f_file *file_information, f_dynamic_string *buffer);
#endif // _di_f_file_read_fifo_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_file_h
