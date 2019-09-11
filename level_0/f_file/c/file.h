/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides structures and data types for a file I/O.
 * Provides operations for opening/closing files.
 */
#ifndef _F_file_h
#define _F_file_h

// libc includes
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/string.h>
#include <level_0/type.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Provide common file-typ specific data types.
 */
#ifndef _di_f_file_types_
  typedef int  f_file_id;
  typedef f_string f_file_mode;
  typedef mode_t f_file_mask;

  #define f_file_default_read_size 4096 // default to 4k read sizes.
  #define f_file_max_path_length   1024
#endif // _di_f_file_types_

/**
 * Provide classic string-based file modes.
 */
#ifndef _di_f_file_oldstyle_modes_
  #define f_file_read_only         "r"
  #define f_file_read_write        "r+"
  #define f_file_read_write_create "rw"
  #define f_file_read_write_append "a+"
  #define f_file_write_create      "w"
  #define f_file_write_append      "a"
#endif // _di_f_file_oldstyle_modes_

/**
 * Provide macros for file-seek operations.
 *
 * The fseek() function parameters can be confusing, so provide a hopefully more readibly code via these macros.
 *
 * The f_macro_file_seek_begin() sets the file pointer from this many bytes from the beginning of the file.
 * The f_macro_file_seek_to() sets the file pointer from this many bytes relative to the current position.
 * The f_macro_file_seek_end() sets the file pointer from this many bytes from the end of the file.
 */
#ifndef _di_f_file_seeks_
  #define f_macro_file_seek_begin(file, bytes) fseek(file, bytes, SEEK_SET)
  #define f_macro_file_seek_to(file, bytes)    fseek(file, bytes, SEEK_CUR)
  #define f_macro_file_seek_end(file)          fseek(file, bytes, SEEK_END)
#endif // _di_f_file_seeks_

/**
 * Commonly used file related properties.
 *
 * id: File descriptor.
 * byte_size: How many bytes to use on each read/write (for normal string handling this should be sizeof(f_string).
 * address: A pointer to a file (generally opened).
 * mode: How the file is to be accessed (or is being accessed).
 */
#ifndef _di_f_file_
  typedef struct {
    f_file_id   id;
    size_t      byte_size;
    FILE *      address;
    f_file_mode mode;
  } f_file;

  #define f_file_initialize { 0, sizeof(char), 0, (f_file_mode) f_file_read_only }
#endif // _di_f_file_

/**
 * Store file positions.
 *
 * This is commonly used to instruct functions how to buffer and use a file.
 *
 * buffer_start: Designate where to start writing to the buffer.
 * file_start: The positions where to begin reading the file.
 * total_elements: The total number of elements to read from the file into the buffer.
 * if total_elements: If set to 0, then this means to buffer the entire file no matter how big it is (crazy?).
 */
#ifndef _di_f_file_position_
  typedef struct {
    f_string_length buffer_start;
    f_string_length file_start;
    f_string_length total_elements;
  } f_file_position;

  #define f_file_position_initialize { 0, 0, 0 }
#endif // _di_f_file_position_

/**
 * File mode relation functionality.
 *
 * TODO: This information below needs to be confirmed and updated accordingly..
 */
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

/**
 * Macro for resetting the file position and the total elements to the size of the file.
 *
 * @todo review why this is being done this way and consider renaming, changing, or removing this.
 */
#ifndef _di_f_macro_file_reset_position_
  #define f_macro_file_reset_position(position, file) \
    if (position.total_elements == 0) { \
      fseek(file.address, 0L, SEEK_END); \
      position.total_elements = ftell(file.address); \
      fseek(file.address, 0L, SEEK_SET); \
    }
#endif // _di_f_macro_file_reset_position_

/**
 * Open a particular file and save its stream.
 *
 * This will open the file and obtain the file descriptor.
 *
 * @param file
 *   The data related to the file being opened.
 *   This will be updated with the file descriptor and file address.
 * @param file_name
 *   The name of the file to be opened.
 *
 * @return
 *   f_none on success.
 *   f_file_not_found (with error bit) if the file was not found.
 *   f_file_open_error (with error bit) if the file is already open.
 *   f_file_descriptor_error (with error bit) if unable to load the file descriptor (the file pointer may still be valid).
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_file_open_
  extern f_return_status f_file_open(f_file *file, const f_string file_name);
#endif // _di_f_file_open_

/**
 * Close an opened file.
 *
 * If the file descriptor is defined, then fsync() is called before closing.
 *
 * @param file
 *   The file to close.
 *
 * @return
 *   f_none on success.
 *   f_file_not_open (with error bit) if the file is not open.
 *   f_file_synchronize_error (with error bit) on fsync() failure.
 *   f_file_close_error (with error bit) if fclose() failed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fsync()
 * @see fclose()
 */
#ifndef _di_f_file_close_
  extern f_return_status f_file_close(f_file *file);
#endif // _di_f_file_close_

/**
 * Check if a file exists.
 *
 * @param file_name
 *   The file name.
 *
 * @return
 *   f_true if file exists.
 *   f_false if file does not exist.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_invalid_name (with error bit) if the filename is too long.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_overflow (with error bit) on overflow error.
 *   f_invalid_directory (with error bit) on invalid directory.
 *   f_access_denied (with error bit) on access denied.
 *   f_loop (with error bit) on loop error.
 *   f_false (with error bit) on unknown/unhandled errors.
 */
#ifndef _di_f_file_exists_
  extern f_return_status f_file_exists(const f_string file_name);
#endif // _di_f_file_exists_

/**
 * Check if a file exists at a given directory.
 *
 * @param directory_file_descriptor
 *   The file descriptor of the directory.
 * @param file_name
 *   The file name.
 * @param flags
 *   Additional flags to pass, such as AT_EACCESS or AT_SYMLINK_NOFOLLOW.
 *
 * @return
 *   f_true if file exists.
 *   f_false if file does not exist.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_invalid_name (with error bit) if the filename is too long.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_overflow (with error bit) on overflow error.
 *   f_invalid_directory (with error bit) on invalid directory.
 *   f_access_denied (with error bit) on access denied.
 *   f_loop (with error bit) on loop error.
 *   f_false (with error bit) on unknown/unhandled errors.
 */
#ifndef _di_f_file_exists_at_
  extern f_return_status f_file_exists_at(const int directory_file_descriptor, const f_string file_name, const int flags);
#endif // _di_f_file_exists_at_

/**
 * Flush the file.
 *
 * This calls fflush().
 *
 * @param file
 *   The file to flush.
 *
 * @return
 *   f_none is returned on success.
 *   f_file_not_open (with error bit) if the file is not open.
 *   f_file_flush_error (with error bit) if the flush failed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fflush()
 */
#ifndef _di_f_file_flush_
  extern f_return_status f_file_flush(f_file *file);
#endif // _di_f_file_flush_

/**
 * Read a until the entire buffer is filled or EOF is reached.
 *
 * @param file
 *   The file to read.
 * @param buffer
 *   The buffer the file is being read into.
 *
 * @return
 *   f_none on success.
 *   f_none_on_eof on success and EOF was reached.
 *   f_file_not_open (with error bit) if file is not open.
 *   f_file_read_error (with error bit) if file read failed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_file_read_
  extern f_return_status f_file_read(f_file *file, f_string_dynamic *buffer);
#endif // _di_f_file_read_

/**
 * Read a given amount of data from the buffer, specified by the given range.
 *
 * @param file
 *   The file to read.
 * @param buffer
 *   The buffer the file is being read into.
 * @param buffer_start
 *   The start position of the buffer.
 * @param total_elements
 *   The total elements to read.
 *   When set to 0, this will read until the entire buffer is filled or the EOF is reached.
 *
 * @return
 *   f_none on success.
 *   f_none is returned if file_stat has a non-zero address.
 *   f_none_on_eof on success and EOF was reached.
 *   f_file_not_open (with error bit) if file is not open.
 *   f_file_read_error (with error bit) if file read failed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_file_read_range_
  extern f_return_status f_file_read_range(f_file *file, f_string_dynamic *buffer, const f_string_length buffer_start, const f_string_length total_elements);
#endif // _di_f_file_read_range_

/**
 * Read a given amount of data from the buffer, specified by the given range.
 *
 * Will auto-seek file position to position.file_start.
 *
 * @param file
 *   The file to read.
 * @param buffer
 *   The buffer the file is being read into.
 * @param position
 *   The file position information.
 *   When position.total_elemenets is set to 0, this will read until the entire buffer is filled or the EOF is reached.
 *
 * @return
 *   f_none on success.
 *   f_none is returned if file_stat has a non-zero address.
 *   f_none_on_eof on success and EOF was reached.
 *   f_file_not_open (with error bit) if file is not open.
 *   f_file_seek_error (with error bit) if file seek failed.
 *   f_file_read_error (with error bit) if file read failed.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_f_file_read_at_
  extern f_return_status f_file_read_at(f_file *file, f_string_dynamic *buffer, const f_file_position position);
#endif // _di_f_file_read_at_

/**
 * Read statistics of a file.
 *
 * This will not re-read the file statistics., file_status must not be allocated.
 * This is because fstatat() will allocate to this variable.
 *
 * This is essentially a wrapper to fstatat() converting any error codes into the FLL format.
 *
 * @param file_id
 *   The file descriptor.
 * @param file_name
 *   The name of the file.
 * @param file_stat
 *   The statistics read.
 * @param flags
 *   Any valid flag used by fstatat(), such as AT_EMPTY_PATH, AT_NO_AUTOMOUNT, or AT_SYMLINK_NO_FOLLOW.
 *
 * @return
 *   f_none on success.
 *   f_none is returned if file_stat has a non-zero address.
 *   f_invalid_name (with error bit) if the name is somehow invalid.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_overflow (with error bit) on overflow error.
 *   f_invalid_directory (with error bit) on invalid directory.
 *   f_file_not_found (with error bit) if the file was not found.
 *   f_access_denied (with error bit) if access to the file was denied.
 *   f_loop (with error bit) if a loop occurred.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fstatat()
 */
#ifndef _di_f_file_stat_at_
  extern f_return_status f_file_stat_at(const int file_id, const f_string file_name, struct stat *file_stat, const int flags);
#endif // _di_f_file_stat_at_

/**
 * Read statistics of a file.
 *
 * This will not re-read the file statistics., file_status must not be allocated.
 * This is because stat() will allocate to this variable.
 *
 * This is essentially a wrapper to stat() converting any error codes into the FLL format.
 *
 * @param file_name
 *   The name of the file.
 * @param file_stat
 *   The statistics read.
 *
 * @return
 *   f_none on success.
 *   f_invalid_name (with error bit) if the name is somehow invalid.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_overflow (with error bit) on overflow error.
 *   f_invalid_directory (with error bit) on invalid directory.
 *   f_file_not_found (with error bit) if the file was not found.
 *   f_access_denied (with error bit) if access to the file was denied.
 *   f_loop (with error bit) if a loop occurred.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see stat()
 */
#ifndef _di_f_file_stat_
  extern f_return_status f_file_stat(const f_string file_name, struct stat *file_stat);
#endif // _di_f_file_stat_

/**
 * Read statistics of a file.
 *
 * This will not re-read the file statistics., file_status must not be allocated.
 * This is because fstat() will allocate to this variable.
 *
 * This is essentially a wrapper to fstat() converting any error codes into the FLL format.
 *
 * @param file_id
 *   The file descriptor.
 * @param file_stat
 *   The statistics read.
 *
 * @return
 *   f_none on success.
 *   f_invalid_name (with error bit) if the name is somehow invalid.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_overflow (with error bit) on overflow error.
 *   f_invalid_directory (with error bit) on invalid directory.
 *   f_file_not_found (with error bit) if the file was not found.
 *   f_access_denied (with error bit) if access to the file was denied.
 *   f_loop (with error bit) if a loop occurred.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fstat()
 */
#ifndef _di_f_file_stat_by_id_
  extern f_return_status f_file_stat_by_id(const int file_id, struct stat *file_stat);
#endif // _di_f_file_stat_by_id_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_file_h
