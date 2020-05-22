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
  #define f_file_default_read_size  8192 // default to 8k read sizes.
  #define f_file_default_write_size 8192 // default to 8k write sizes.
#endif // _di_f_file_types_

/**
 * Provide macros for file-seek operations.
 *
 * The fseek() function parameters can be confusing, so provide a hopefully more readibly code via these macros.
 *
 * The f_macro_file_seek_begin() sets the file pointer from this many bytes from the beginning of the file.
 * The f_macro_file_seek_data() sets the file pointer from this many bytes from the end of the file, relative to the next data.
 * The f_macro_file_seek_end() sets the file pointer from this many bytes from the end of the file.
 * The f_macro_file_seek_hole() sets the file pointer from this many bytes from the end of the file, relative to the next hole.
 * The f_macro_file_seek_to() sets the file pointer from this many bytes relative to the current position.
 */
#ifndef _di_f_file_seeks_
  #define f_macro_file_seek_begin(file, bytes) fseek(file, bytes, SEEK_SET)
  #define f_macro_file_seek_data(file, bytes)  fseek(file, bytes, SEEK_DATA)
  #define f_macro_file_seek_end(file)          fseek(file, bytes, SEEK_END)
  #define f_macro_file_seek_hole(file, bytes)  fseek(file, bytes, SEEK_HOLE)
  #define f_macro_file_seek_to(file, bytes)    fseek(file, bytes, SEEK_CUR)
#endif // _di_f_file_seeks_

/**
 * Provide file type macros.
 */
#ifndef _di_f_file_type_
  #define f_file_type_mask S_IFMT

  #define f_file_type_pipe      S_IFIFO
  #define f_file_type_character S_IFCHR
  #define f_file_type_directory S_IFDIR
  #define f_file_type_block     S_IFBLK
  #define f_file_type_file      S_IFREG
  #define f_file_type_link      S_IFLNK
  #define f_file_type_socket    S_IFSOCK

  #define f_macro_file_type_get(mode) (f_file_type_mask & mode)

  #define f_macro_file_type_is_pipe(mode)      f_macro_file_type_get(mode) == f_file_type_pipe
  #define f_macro_file_type_is_character(mode) f_macro_file_type_get(mode) == f_file_type_character
  #define f_macro_file_type_is_directory(mode) f_macro_file_type_get(mode) == f_file_type_directory
  #define f_macro_file_type_is_block(mode)     f_macro_file_type_get(mode) == f_file_type_block
  #define f_macro_file_type_is_file(mode)      f_macro_file_type_get(mode) == f_file_type_file
  #define f_macro_file_type_is_link(mode)      f_macro_file_type_get(mode) == f_file_type_link
  #define f_macro_file_type_is_socket(mode)    f_macro_file_type_get(mode) == f_file_type_socket
#endif // _di_f_file_type_

/**
 * Commonly used file related properties.
 *
 * id: File descriptor.
 * size_block: The default number of 1-byte characters to read at a time and is often used for the read/write buffer size.
 */
#ifndef _di_f_file_
  typedef struct {
    int    id;
    size_t size_read;
    size_t size_write;
  } f_file;

  #define f_file_initialize { 0, f_file_default_read_size, f_file_default_write_size }
#endif // _di_f_file_

/**
 * File mode relation functionality.
 */
#ifndef _di_f_file_modes_

  // file open flags
  #define f_file_flag_append             O_APPEND
  #define f_file_flag_asynchronous       O_ASYNC
  #define f_file_flag_create             O_CREAT
  #define f_file_flag_close_execute      O_CLOEXEC
  #define f_file_flag_direct             O_DIRECT
  #define f_file_flag_directory          O_DIRECTORY
  #define f_file_flag_exclusive          O_EXCL
  #define f_file_flag_large_file         O_LARGEFILE
  #define f_file_flag_no_access_time     O_NOATIME
  #define f_file_flag_no_follow          O_NOFOLLOW
  #define f_file_flag_no_tty             O_NOCTTY
  #define f_file_flag_non_blocking       O_NONBLOCK
  #define f_file_flag_path               O_PATH
  #define f_file_flag_read_only          O_RDONLY
  #define f_file_flag_read_write         O_RDWR
  #define f_file_flag_synchronous        O_SYNC
  #define f_file_flag_synchronous_direct O_DSYNC
  #define f_file_flag_temporary          O_TMPFILE
  #define f_file_flag_truncate           O_TRUNC
  #define f_file_flag_write_only         O_WRONLY

  // file open flags pre-combined with create.
  #define f_file_flag_create_ro (O_CREAT | O_RDONLY)
  #define f_file_flag_create_wo (O_CREAT | O_WRONLY)
  #define f_file_flag_create_rw (O_CREAT | O_RDRW)

  // file open flags pre-combined will fail if file exists.
  #define f_file_flag_create_new_ro (O_CREAT | O_EXCL | O_RDONLY)
  #define f_file_flag_create_new_wo (O_CREAT | O_EXCL | O_WRONLY)
  #define f_file_flag_create_new_rw (O_CREAT | O_EXCL | O_RDRW)

  // file open flags pre-combined will truncate any existing files to 0.
  #define f_file_flag_truncate_ro (O_CREAT | O_TRUNC | O_RDONLY)
  #define f_file_flag_truncate_rw (O_CREAT | O_TRUNC | O_RDRW)
  #define f_file_flag_truncate_wo (O_CREAT | O_TRUNC | O_WRONLY)

  // file open flags pre-combined with synchronous io.
  #define f_file_flag_sync_ro            (O_SYNC | O_RDONLY)
  #define f_file_flag_sync_wo            (O_SYNC | O_WRONLY)
  #define f_file_flag_sync_rw            (O_SYNC | O_RDRW)
  #define f_file_flag_sync_create_ro     (O_SYNC | O_CREAT | O_RDONLY)
  #define f_file_flag_sync_create_wo     (O_SYNC | O_CREAT | O_WRONLY)
  #define f_file_flag_sync_create_rw     (O_SYNC | O_CREAT | O_RDRW)
  #define f_file_flag_sync_create_new_ro (O_SYNC | O_CREAT | O_EXCL | O_RDONLY)
  #define f_file_flag_sync_create_new_wo (O_SYNC | O_CREAT | O_EXCL | O_WRONLY)
  #define f_file_flag_sync_create_new_rw (O_SYNC | O_CREAT | O_EXCL | O_RDRW)

  // file open flags pre-combined with asynchronous io.
  #define f_file_flag_async_ro            (O_ASYNC | O_RDONLY)
  #define f_file_flag_async_wo            (O_ASYNC | O_WRONLY)
  #define f_file_flag_async_rw            (O_ASYNC | O_RDRW)
  #define f_file_flag_async_create_ro     (O_ASYNC | O_CREAT | O_RDONLY)
  #define f_file_flag_async_create_wo     (O_ASYNC | O_CREAT | O_WRONLY)
  #define f_file_flag_async_create_rw     (O_ASYNC | O_CREAT | O_RDRW)
  #define f_file_flag_async_create_new_ro (O_ASYNC | O_CREAT | O_EXCL | O_RDONLY)
  #define f_file_flag_async_create_new_wo (O_ASYNC | O_CREAT | O_EXCL | O_WRONLY)
  #define f_file_flag_async_create_new_rw (O_ASYNC | O_CREAT | O_EXCL | O_RDRW)

  // file open flags pre-combined with direct io (which works synchronously).
  #define f_file_flag_direct_ro            (O_DIRECT | O_RDONLY)
  #define f_file_flag_direct_wo            (O_DIRECT | O_WRONLY)
  #define f_file_flag_direct_rw            (O_DIRECT | O_RDRW)
  #define f_file_flag_direct_create_ro     (O_DIRECT | O_CREAT | O_RDONLY)
  #define f_file_flag_direct_create_wo     (O_DIRECT | O_CREAT | O_WRONLY)
  #define f_file_flag_direct_create_rw     (O_DIRECT | O_CREAT | O_RDRW)
  #define f_file_flag_direct_create_new_ro (O_DIRECT | O_CREAT | O_EXCL | O_RDONLY)
  #define f_file_flag_direct_create_new_wo (O_DIRECT | O_CREAT | O_EXCL | O_WRONLY)
  #define f_file_flag_direct_create_new_rw (O_DIRECT | O_CREAT | O_EXCL | O_RDRW)

  // file open flags pre-combined with large_file.
  #define f_file_flag_large_ro                  (O_LARGEFILE | O_RDONLY)
  #define f_file_flag_large_wo                  (O_LARGEFILE | O_WRONLY)
  #define f_file_flag_large_rw                  (O_LARGEFILE | O_RDRW)
  #define f_file_flag_large_sync_ro             (O_LARGEFILE | O_SYNC | O_RDONLY)
  #define f_file_flag_large_sync_wo             (O_LARGEFILE | O_SYNC | O_WRONLY)
  #define f_file_flag_large_sync_rw             (O_LARGEFILE | O_SYNC | O_RDRW)
  #define f_file_flag_large_sync_create_ro      (O_LARGEFILE | O_SYNC | O_CREAT | O_RDONLY)
  #define f_file_flag_large_sync_create_wo      (O_LARGEFILE | O_SYNC | O_CREAT | O_WRONLY)
  #define f_file_flag_large_sync_create_rw      (O_LARGEFILE | O_SYNC | O_CREAT | O_RDRW)
  #define f_file_flag_large_sync_create_new_ro  (O_LARGEFILE | O_SYNC | O_CREAT | O_EXCL | O_RDONLY)
  #define f_file_flag_large_sync_create_new_wo  (O_LARGEFILE | O_SYNC | O_CREAT | O_EXCL | O_WRONLY)
  #define f_file_flag_large_sync_create_new_rw  (O_LARGEFILE | O_SYNC | O_CREAT | O_EXCL | O_RDRW)
  #define f_file_flag_large_async_ro            (O_LARGEFILE | O_ASYNC | O_RDONLY)
  #define f_file_flag_large_async_wo            (O_LARGEFILE | O_ASYNC | O_WRONLY)
  #define f_file_flag_large_async_rw            (O_LARGEFILE | O_ASYNC | O_RDRW)
  #define f_file_flag_large_async_create_ro     (O_LARGEFILE | O_ASYNC | O_CREAT | O_RDONLY)
  #define f_file_flag_large_async_create_wo     (O_LARGEFILE | O_ASYNC | O_CREAT | O_WRONLY)
  #define f_file_flag_large_async_create_rw     (O_LARGEFILE | O_ASYNC | O_CREAT | O_RDRW)
  #define f_file_flag_large_async_create_new_ro (O_LARGEFILE | O_ASYNC | O_CREAT | O_EXCL | O_RDONLY)
  #define f_file_flag_large_async_create_new_wo (O_LARGEFILE | O_ASYNC | O_CREAT | O_EXCL | O_WRONLY)
  #define f_file_flag_large_async_create_new_rw (O_LARGEFILE | O_ASYNC | O_CREAT | O_EXCL | O_RDRW)

  // file permission modes.
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

  #define f_file_mode_all_rwx (f_file_mode_owner_rwx | f_file_mode_group_rwx | f_file_mode_world_rwx)
  #define f_file_mode_all_rw  (f_file_mode_owner_rw | f_file_mode_group_rw | f_file_mode_world_rw)
  #define f_file_mode_all_wx  (f_file_mode_owner_wx | f_file_mode_group_wx | f_file_mode_world_wx)
  #define f_file_mode_all_rx  (f_file_mode_owner_rx | f_file_mode_group_rx | f_file_mode_world_rx)
  #define f_file_mode_all_r   (f_file_mode_owner_r | f_file_mode_group_r | f_file_mode_world_r)
  #define f_file_mode_all_w   (f_file_mode_owner_w | f_file_mode_group_w | f_file_mode_world_w)
  #define f_file_mode_all_x   (f_file_mode_owner_x | f_file_mode_group_x | f_file_mode_world_x)

  // file mode sticky-bits and all bits.
  #define f_file_mode_special_user  S_ISUID
  #define f_file_mode_special_group S_ISGID
  #define f_file_mode_special_world S_ISVTX
  #define f_file_mode_special_all   (S_ISUID | S_ISGID | S_ISVTX | S_IRWXU | S_IRWXG | S_IRWXO)

  // special file mode combinations.
  #define f_file_mode_user_access    (f_file_mode_owner_rwx | f_file_mode_group_rwx | f_file_mode_world_x)
  #define f_file_mode_user_directory (f_file_mode_owner_rwx | f_file_mode_group_rwx)
  #define f_file_mode_user_file      (f_file_mode_owner_rw | f_file_mode_group_rw)
  #define f_file_mode_user_program   (f_file_mode_owner_rx | f_file_mode_group_rx)
  #define f_file_mode_user_protected (f_file_mode_owner_r | f_file_mode_group_r)
#endif // _di_f_file_modes_

/**
 * Change mode of a given file at the specified path.
 *
 * @param path
 *   The path file name.
 * @param mode
 *   The new mode to use.
 * @param dereference
 *   Set to TRUE to dereferenc symlinks (often is what is desired).
 *   Set to FALSE to operate on the symlink itself.
 *
 * @return
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_access_denied (with error bit) on access denied.
 *   f_invalid_name (with error bit) if the filename is too long.
 *   f_loop (with error bit) on loop error.
 *   f_file_not_found (with error bit) if file at path was not found.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_invalid_directory (with error bit) on invalid directory.
 *   f_prohibited (with error bit) if filesystem does not allow for file changes.
 *   f_read_only (with error bit) if file is read-only.
 *   f_error_input_output (with error bit) on I/O error.
 *   f_failure (with error bit) for any other (mkdir()) error.
 *
 * @see chmod()
 */
#ifndef _di_f_file_change_mode_
  extern f_return_status f_file_change_mode(const f_string path, const mode_t mode, const bool dereference);
#endif // _di_f_file_change_mode_

/**
 * Change mode of a given file at the specified path.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param mode
 *   The new mode to use.
 * @param flags
 *   Any valid flag, such as AT_EMPTY_PATH, AT_NO_AUTOMOUNT, or AT_SYMLINK_NO_FOLLOW.
 *
 * @return
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_access_denied (with error bit) on access denied.
 *   f_invalid_name (with error bit) if the filename is too long.
 *   f_loop (with error bit) on loop error.
 *   f_file_not_found (with error bit) if file at path was not found.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_invalid_directory (with error bit) on invalid directory.
 *   f_prohibited (with error bit) if filesystem does not allow for file changes.
 *   f_read_only (with error bit) if file is read-only.
 *   f_error_input_output (with error bit) on I/O error.
 *   f_failure (with error bit) for any other (mkdir()) error.
 *
 * @see chmod()
 */
#ifndef _di_f_file_change_mode_at_
  extern f_return_status f_file_change_mode_at(const int at_id, const f_string path, const mode_t mode, const int flags);
#endif // _di_f_file_change_mode_at_

/**
 * Change owner and group of a given file at the specified path.
 *
 * @param path
 *   The path file name.
 * @param uid
 *   The new user id to use.
 * @param gid
 *   The new group id to use.
 * @param dereference
 *   Set to TRUE to dereferenc symlinks (often is what is desired).
 *   Set to FALSE to operate on the symlink itself.
 *
 * @return
 *   f_true if file exists.
 *   f_false if file does not exist.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_invalid_name (with error bit) if the filename is too long.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_number_overflow (with error bit) on overflow error.
 *   f_invalid_directory (with error bit) on invalid directory.
 *   f_access_denied (with error bit) on access denied.
 *   f_loop (with error bit) on loop error.
 *   f_false (with error bit) on unknown/unhandled errors.
 *
 * @see chown()
 */
#ifndef _di_f_file_change_owner_
  extern f_return_status f_file_change_owner(const f_string path, const uid_t uid, const gid_t gid, const bool dereference);
#endif // _di_f_file_change_owner_

/**
 * Change owner and group of a given file at the specified path.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param uid
 *   The new user id to use.
 * @param gid
 *   The new group id to use.
 * @param flags
 *   Any valid flag, such as AT_EMPTY_PATH, AT_NO_AUTOMOUNT, or AT_SYMLINK_NO_FOLLOW.
 *
 * @return
 *   f_true if file exists.
 *   f_false if file does not exist.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_invalid_name (with error bit) if the filename is too long.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_number_overflow (with error bit) on overflow error.
 *   f_invalid_directory (with error bit) on invalid directory.
 *   f_access_denied (with error bit) on access denied.
 *   f_loop (with error bit) on loop error.
 *   f_false (with error bit) on unknown/unhandled errors.
 *
 * @see chown()
 */
#ifndef _di_f_file_change_owner_at_
  extern f_return_status f_file_change_owner_at(const int at_id, const f_string path, const uid_t uid, const gid_t gid, const int flags);
#endif // _di_f_file_change_owner_at_

/**
 * Check if a file can be accessed.
 *
 * @param path
 *   The path file name.
 *
 * @return
 *   f_true if file exists.
 *   f_false if file does not exist.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_invalid_name (with error bit) if the filename is too long.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_number_overflow (with error bit) on overflow error.
 *   f_invalid_directory (with error bit) on invalid directory.
 *   f_access_denied (with error bit) on access denied.
 *   f_loop (with error bit) on loop error.
 *   f_false (with error bit) on unknown/unhandled errors.
 *
 * @see access()
 */
#ifndef _di_f_file_access_
  extern f_return_status f_file_access(const f_string path);
#endif // _di_f_file_access_

/**
 * Copy a file.
 *
 * The paths must not contain NULL except for the terminating NULL.
 * The paths must be NULL terminated.
 *
 * @param source
 *   The path to the file to copy from.
 * @param destination
 *   The path to copy to.
 * @param mode
 *   The file mode assigned to the destination file.
 * @param size_block
 *   The default number of chunks to read at a time with each chunk being 1-byte.
 *   Must be greater than 0.
 * @param exclusive
 *   If TRUE, will fail when file already exists.
 *   If FALSE, will not fail if file already exists (existing file will be replaced).
 *
 * @return
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_access_denied (with error bit) on access denied.
 *   f_loop (with error bit) on loop error.
 *   f_file_found (with error bit) if a file was found while exclusive is TRUE.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_prohibited (with error bit) if filesystem does not allow for removing.
 *   f_read_only (with error bit) if file is read-only.
 *   f_failure (with error bit) for any other (mkdir()) error.
 *   f_filesystem_quota_blocks (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   f_no_space (with error bit) if filesystem is out of space (or filesystem quota is reached).
 *   f_file_found (with error bit) of a directory aleady exists at the path.
 *   f_invalid_name (with error bit) on path name error.
 *   f_invalid_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   f_number_overflow (with error bit) on overflow error.
 *   f_interrupted (with error bit) when program received an interrupt signal, halting create.
 *   f_file_max_open (with error bit) when system-wide max open files is reached.
 *   f_busy (with error bit) if filesystem is too busy to perforrm write.
 *   f_file_error_read (with error bit) on file read error.
 *   f_file_error_write (with error bit) on file write error.
 */
#ifndef _di_f_file_copy_
  extern f_return_status f_file_copy(const f_string source, const f_string destination, const mode_t mode, const f_number_unsigned size_block, const bool exclusive);
#endif // _di_f_file_copy_

/**
 * Copy a file, as well as its file mode and possibly the owner and group.
 *
 * The paths must not contain NULL except for the terminating NULL.
 * The paths must be NULL terminated.
 *
 * @todo provide a return status for when owner/role cannot be assigned.
 * This will be returned when complete so that caller can decide if this is an error or not.
 *
 * @param source
 *   The path to the file to copy from.
 * @param destination
 *   The path to copy to.
 * @param size_block
 *   The default number of chunks to read at a time with each chunk being 1-byte.
 *   Must be greater than 0.
 * @param exclusive
 *   If TRUE, will fail when file already exists.
 *   If FALSE, will not fail if file already exists (existing file will be replaced).
 * @param roles
 *   If TRUE, will copy the owner and group ids.
 *   If FALSE, will not copy the owner and group ids.
 *   (In both cases the file mode is copied.)
 *
 * @return
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_access_denied (with error bit) on access denied.
 *   f_loop (with error bit) on loop error.
 *   f_file_found (with error bit) if a file was found while exclusive is TRUE.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_prohibited (with error bit) if filesystem does not allow for removing.
 *   f_read_only (with error bit) if file is read-only.
 *   f_failure (with error bit) for any other (mkdir()) error.
 *   f_filesystem_quota_blocks (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   f_no_space (with error bit) if filesystem is out of space (or filesystem quota is reached).
 *   f_file_found (with error bit) of a directory aleady exists at the path.
 *   f_invalid_name (with error bit) on path name error.
 *   f_invalid_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   f_number_overflow (with error bit) on overflow error.
 *   f_interrupted (with error bit) when program received an interrupt signal, halting create.
 *   f_file_max_open (with error bit) when system-wide max open files is reached.
 *   f_busy (with error bit) if filesystem is too busy to perforrm write.
 *   f_file_error_read (with error bit) on file read error.
 *   f_file_error_write (with error bit) on file write error.
 */
#ifndef _di_f_file_clone_
  extern f_return_status f_file_clone(const f_string source, const f_string destination, const f_number_unsigned size_block, const bool exclusive, const bool roles);
#endif // _di_f_file_clone_

/**
 * Close an open file.
 *
 * Will flush before closing.
 *
 * @param id
 *   The file descriptor.
 *
 * @return
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_file_error_descriptor (with error bit) if file descriptor is invalid.
 *   f_interrupted (with error bit) if interrupt was received.
 *   f_error_input_output (with error bit) on I/O error.
 *   f_filesystem_quota_blocks (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   f_no_space (with error bit) if filesystem is out of space (or filesystem quota is reached).
 *   f_file_error_synchronize (with error bit) on flush failure.
 *   f_file_error_close (with error bit) if fclose() failed for any other reason.
 *
 * @see fclose()
 */
#ifndef _di_f_file_close_
  extern f_return_status f_file_close(int *id);
#endif // _di_f_file_close_

/**
 * Create a file based on the given path and file mode.
 *
 * The file will not be open after calling this.
 *
 * @param path
 *   The path file name.
 * @param mode
 *   The file mode to open in.
 * @param exclusive
 *   If TRUE, will fail when file already exists.
 *   If FALSE, will not fail if file already exists.
 * @param dereference
 *   Set to TRUE to dereferenc symlinks (often is what is desired).
 *   Set to FALSE to fail if the path is a symbolic link.
 *   This does not write symbolic links. (@todo add function f_create_link() for creating symbolic links.)
 *
 * @return
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_access_denied (with error bit) on access denied.
 *   f_loop (with error bit) on loop error.
 *   f_file_found (with error bit) if a file was found while exclusive is TRUE.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_prohibited (with error bit) if filesystem does not allow for removing.
 *   f_read_only (with error bit) if file is read-only.
 *   f_failure (with error bit) for any other (mkdir()) error.
 *   f_filesystem_quota_blocks (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   f_no_space (with error bit) if filesystem is out of space (or filesystem quota is reached).
 *   f_file_found (with error bit) of a directory aleady exists at the path.
 *   f_invalid_name (with error bit) on path name error.
 *   f_invalid_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   f_number_overflow (with error bit) on overflow error.
 *   f_interrupted (with error bit) when program received an interrupt signal, halting create.
 *   f_file_max_open (with error bit) when system-wide max open files is reached.
 *   f_busy (with error bit) if filesystem is too busy to perforrm write.
 *
 * @see open()
 */
#ifndef _di_f_file_create_
  extern f_return_status f_file_create(const f_string path, const mode_t mode, const bool exclusive, const bool dereference);
#endif // _di_f_file_create_

/**
 * Create a file based on the given path and file mode.
 *
 * The file will not be open after calling this.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param mode
 *   The file mode to open in.
 * @param exclusive
 *   If TRUE, will fail when file already exists.
 *   If FALSE, will not fail if file already exists.
 * @param dereference
 *   Set to TRUE to dereferenc symlinks (often is what is desired).
 *   Set to FALSE to fail if the path is a symbolic link.
 *   This does not write symbolic links. (@todo add function f_create_link() for creating symbolic links.)
 *
 * @return
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_access_denied (with error bit) on access denied.
 *   f_loop (with error bit) on loop error.
 *   f_file_found (with error bit) if a file was found while exclusive is TRUE.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_prohibited (with error bit) if filesystem does not allow for removing.
 *   f_read_only (with error bit) if file is read-only.
 *   f_failure (with error bit) for any other (mkdir()) error.
 *   f_filesystem_quota_blocks (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   f_no_space (with error bit) if filesystem is out of space (or filesystem quota is reached).
 *   f_file_found (with error bit) of a directory aleady exists at the path.
 *   f_invalid_name (with error bit) on path name error.
 *   f_invalid_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   f_number_overflow (with error bit) on overflow error.
 *   f_interrupted (with error bit) when program received an interrupt signal, halting create.
 *   f_file_max_open (with error bit) when system-wide max open files is reached.
 *   f_busy (with error bit) if filesystem is too busy to perforrm write.
 *
 * @see openat()
 */
#ifndef _di_f_file_create_at_
  extern f_return_status f_file_create_at(const int at_id, const f_string path, const mode_t mode, const bool exclusive, const bool dereference);
#endif // _di_f_file_create_at_

/**
 * Identify whether or not a file exists at the given path.
 *
 * This does not require access on the file itself.
 * This only requires access via the parent directories in the path.
 *
 * @param path
 *   The path file name.
 *
 * @return
 *   t_true if path was found.
 *   f_false if path was not found.
 *   f_invalid_name (with error bit) if the name is somehow invalid.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_number_overflow (with error bit) on overflow error.
 *   f_invalid_directory (with error bit) on invalid directory.
 *   f_access_denied (with error bit) if access to the file was denied.
 *   f_loop (with error bit) if a loop occurred.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see stat()
 */
#ifndef _di_f_file_exists_
  extern f_return_status f_file_exists(const f_string path);
#endif // _di_f_file_exists_

/**
 * Identify whether or not a file exists at the given path.
 *
 * This does not require access on the file itself.
 * This only requires access via the parent directories in the path.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param flags
 *   Additional flags to pass, such as AT_EACCESS or AT_SYMLINK_NOFOLLOW.
 *
 * @return
 *   f_true if file exists.
 *   f_false if file does not exist.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_invalid_name (with error bit) if the filename is too long.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_number_overflow (with error bit) on overflow error.
 *   f_invalid_directory (with error bit) on invalid directory.
 *   f_access_denied (with error bit) on access denied.
 *   f_loop (with error bit) on loop error.
 *   f_false (with error bit) on unknown/unhandled errors.
 *
 * @see fstatat()
 */
#ifndef _di_f_file_exists_at_
  extern f_return_status f_file_exists_at(const int at_id, const f_string path, const bool follow);
#endif // _di_f_file_exists_at_

/**
 * Flush the file.
 *
 * @param id
 *   The file descriptor.
 *
 * @return
 *   f_none is returned on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_file_error_descriptor (with error bit) if file descriptor is invalid.
 *   f_error_input_output (with error bit) on I/O error.
 *   f_filesystem_quota_blocks (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   f_no_space (with error bit) if filesystem is out of space (or filesystem quota is reached).
 *   f_unsupported (with error bit) if the file system or file type does not support flushing.
 *   f_failure (with error bit) on any other failure.
 *
 * @see fsync()
 */
#ifndef _di_f_file_flush_
  extern f_return_status f_file_flush(const int id);
#endif // _di_f_file_flush_

/**
 * Identify whether or not a file exists at the given path and if that file is a specific type.
 *
 * This does not require access on the file itself.
 * This only requires access via the parent directories in the path.
 *
 * @param path
 *   The path file name.
 * @param type
 *   The type of the file
 *
 * @return
 *   t_true if path was found and path is type.
 *   f_false if path was found and path is not type.
 *   f_file_not_found if the path was not found.
 *   f_invalid_name (with error bit) if the name is somehow invalid.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_number_overflow (with error bit) on overflow error.
 *   f_invalid_directory (with error bit) on invalid directory.
 *   f_access_denied (with error bit) if access to the file was denied.
 *   f_loop (with error bit) if a loop occurred.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see stat()
 */
#ifndef _di_f_file_is_
  extern f_return_status f_file_is(const f_string path, const int type);
#endif // _di_f_file_is_

/**
 * Identify whether or not a file exists at the given path within the parent directory and if that file is a specific type.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param type
 *   The type of the file
 * @param follow
 *   Set to TRUE to follow symbolic links when determining if path is a file.
 *   Set to FALSE to not follow.
 *
 * @return
 *   t_true if path was found and path is type.
 *   f_false if path was found and path is not type.
 *   f_file_not_found if the path was not found.
 *   f_invalid_name (with error bit) if the name is somehow invalid.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_number_overflow (with error bit) on overflow error.
 *   f_invalid_directory (with error bit) on invalid directory.
 *   f_access_denied (with error bit) if access to the file was denied.
 *   f_loop (with error bit) if a loop occurred.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fstatat()
 */
#ifndef _di_f_file_is_at_
  extern f_return_status f_file_is_at(const int at_id, const f_string path, const int type, const bool follow);
#endif // _di_f_file_is_at_

/**
 * Create a symbolic link to a file.
 *
 * This will not replace existing files/links.
 * This does not validate the existence of target.
 *
 * @param target
 *   A path that the link points to.
 * @param point
 *   A path to the link that does the pointing.
 *
 * @return
 *
 * @see symlink()
 */
#ifndef _di_f_file_link_
  extern f_return_status f_file_link(const f_string target, const f_string point);
#endif // _di_f_file_link_

/**
 * Create a symbolic link to a file.
 *
 * This will not replace existing files/links.
 * This does not validate the existence of target.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which point path is relative to.
 * @param target
 *   A path that the link points to.
 * @param point
 *   A path to the link that does the pointing.
 *
 * @return
 *
 * @see symlinkat()
 */
#ifndef _di_f_file_link_at_
  extern f_return_status f_file_link_at(const int at_id, const f_string target, const f_string point);
#endif // _di_f_file_link_at_

/**
 * Create a hard link to a file.
 *
 * This will not replace existing files/links.
 *
 * @param target
 *   A path that the link points to.
 * @param point
 *   A path to the link that does the pointing.
 *
 * @return
 *
 * @see link()
 */
#ifndef _di_f_file_link_hard_
  extern f_return_status f_file_link_hard(const f_string target, const f_string point);
#endif // _di_f_file_link_hard_

/**
 * Create a hard link to a file.
 *
 * This will not replace existing files/links.
 *
 * @param at_id_target
 *   The parent directory, as an open directory file descriptor, in which target path is relative to.
 * @param at_id_point
 *   The parent directory, as an open directory file descriptor, in which point path is relative to.
 * @param target
 *   A path that the link points to.
 * @param point
 *   A path to the link that does the pointing.
 * @param flags
 *   Any valid flag, such as AT_EMPTY_PATH, AT_NO_AUTOMOUNT, or AT_SYMLINK_NO_FOLLOW.
 *
 * @return
 *
 * @see linkat()
 */
#ifndef _di_f_file_link_hard_at_
  extern f_return_status f_file_link_hard_at(const int at_id_target, const int at_id_point, const f_string target, const f_string point, const int flags);
#endif // _di_f_file_link_hard_at_

/**
 * Open a particular file and save its stream.
 *
 * This will open the file and obtain the file descriptor.
 *
 * @param path
 *   The path file name.
 * @param flags
 *   Any valid flag, such as AT_EMPTY_PATH, AT_NO_AUTOMOUNT, or AT_SYMLINK_NO_FOLLOW.
 * @param mode
 *   The file mode to open in.
 *   Set to 0 to not use.
 * @param file
 *   The data related to the file being opened.
 *   This will be updated with the file descriptor and file address.
 *
 * @return
 *   f_none on success.
 *   f_file_not_found (with error bit) if the file was not found.
 *   f_file_error_open (with error bit) if the file is already open.
 *   f_file_error_descriptor (with error bit) if unable to load the file descriptor (the file pointer may still be valid).
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see open()
 */
#ifndef _di_f_file_open_
  extern f_return_status f_file_open(const f_string path, const int flags, const mode_t mode, f_file *file);
#endif // _di_f_file_open_

/**
 * Open a particular file and save its stream.
 *
 * This will open the file and obtain the file descriptor.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param flags
 *   Any valid flag, such as AT_EMPTY_PATH, AT_NO_AUTOMOUNT, or AT_SYMLINK_NO_FOLLOW.
 * @param mode
 *   The file mode to open in.
 *   Set to 0 to not use.
 * @param file
 *   The data related to the file being opened.
 *   This will be updated with the file descriptor and file address.
 *
 * @return
 *   f_none on success.
 *   f_file_not_found (with error bit) if the file was not found.
 *   f_file_error_open (with error bit) if the file is already open.
 *   f_file_error_descriptor (with error bit) if unable to load the file descriptor (the file pointer may still be valid).
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see openat()
 */
#ifndef _di_f_file_open_at_
  extern f_return_status f_file_open_at(const int at_id, const f_string path, const int flags, const mode_t mode, f_file *file);
#endif // _di_f_file_open_at_

/**
 * Read until EOF is reached.
 *
 * To check how much was read into the buffer, record buffer->used before execution and compare to buffer->used after execution.
 *
 * @param file
 *   The file to read.
 *   The file must already be open.
 * @param buffer
 *   The buffer the file is being read into.
 *   The contents of the file is appended into this buffer.
 *
 * @return
 *   f_none on success.
 *   f_none_on_eof on success and EOF was reached.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_block (with error bit) if file descriptor is set to non-block and the read would result in a blocking operation.
 *   f_file_error_descriptor (with error bit) if the file descriptor is invalid.
 *   f_invalid_buffer (with error bit) if the buffer is invalid.
 *   f_interrupted (with error bit) if interrupt was received.
 *   f_error_input_output (with error bit) on I/O error.
 *   f_file_not_open (with error bit) if file is not open.
 *   f_file_is_type_directory (with error bit) if file descriptor represents a directory.
 *
 * @see read()
 */
#ifndef _di_f_file_read_
  extern f_return_status f_file_read(const f_file file, f_string_dynamic *buffer);
#endif // _di_f_file_read_

/**
 * Read until a single block is filled or EOF is reached.
 *
 * To check how much was read into the buffer, record buffer->used before execution and compare to buffer->used after execution.
 *
 * @param file
 *   The file to read.
 *   The file must already be open.
 * @param buffer
 *   The buffer the file is being read into.
 *   The contents of the file is appended into this buffer.
 *
 * @return
 *   f_none on success.
 *   f_none_on_eof on success and EOF was reached.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_block (with error bit) if file descriptor is set to non-block and the read would result in a blocking operation.
 *   f_file_error_descriptor (with error bit) if the file descriptor is invalid.
 *   f_invalid_buffer (with error bit) if the buffer is invalid.
 *   f_interrupted (with error bit) if interrupt was received.
 *   f_error_input_output (with error bit) on I/O error.
 *   f_file_not_open (with error bit) if file is not open.
 *   f_file_is_type_directory (with error bit) if file descriptor represents a directory.
 *
 * @see read()
 */
#ifndef _di_f_file_read_
  extern f_return_status f_file_read_block(const f_file file, f_string_dynamic *buffer);
#endif // _di_f_file_read_

/**
 * Read until a given number or EOF is reached, storing it in the buffer.
 *
 * To check how much was read into the buffer, record buffer->used before execution and compare to buffer->used after execution.
 *
 * @param file
 *   The file to read.
 *   The file must already be open.
 * @param buffer
 *   The buffer the file is being read into.
 * @param total
 *   The total bytes to read, unless EOF is reached first.
 *
 * @return
 *   f_none on success.
 *   f_none_on_eof on success and EOF was reached.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_block (with error bit) if file descriptor is set to non-block and the read would result in a blocking operation.
 *   f_file_error_descriptor (with error bit) if the file descriptor is invalid.
 *   f_invalid_buffer (with error bit) if the buffer is invalid.
 *   f_interrupted (with error bit) if interrupt was received.
 *   f_error_input_output (with error bit) on I/O error.
 *   f_file_not_open (with error bit) if file is not open.
 *   f_file_is_type_directory (with error bit) if file descriptor represents a directory.
 *
 * @see read()
 */
#ifndef _di_f_file_read_until_
  extern f_return_status f_file_read_until(const f_file file, f_string_dynamic *buffer, const f_string_length total);
#endif // _di_f_file_read_until_

/**
 * Remove a file.
 *
 * @param path
 *   The path file name.
 *
 * @return
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_access_denied (with error bit) on access denied.
 *   f_busy (with error bit) if file is busy.
 *   f_error_input_output (with error bit) if an I/O error occurred.
 *   f_file_is_type_directory (with error bit) file is a directory (directories cannot be removed via this function).
 *   f_loop (with error bit) on loop error.
 *   f_invalid_name (with error bit) on path name error.
 *   f_file_not_found (with error bit) if file not found.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_invalid_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   f_prohibited (with error bit) if filesystem does not allow for removing.
 *   f_read_only (with error bit) if file is read-only.
 *   f_failure (with error bit) for any other (unlink()) error.
 *
 * @see unlink()
 */
#ifndef _di_f_file_remove_
  extern f_return_status f_file_remove(const f_string path);
#endif // _di_f_file_remove_

/**
 * Remove a file.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path file name.
 * @param flags
 *   Any valid flag, such as AT_EMPTY_PATH, AT_NO_AUTOMOUNT, or AT_SYMLINK_NO_FOLLOW.
 *
 * @return
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_access_denied (with error bit) on access denied.
 *   f_busy (with error bit) if file is busy.
 *   f_error_input_output (with error bit) if an I/O error occurred.
 *   f_file_is_type_directory (with error bit) file is a directory (directories cannot be removed via this function).
 *   f_loop (with error bit) on loop error.
 *   f_invalid_name (with error bit) on path name error.
 *   f_file_not_found (with error bit) if file not found.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_invalid_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   f_prohibited (with error bit) if filesystem does not allow for removing.
 *   f_read_only (with error bit) if file is read-only.
 *   f_failure (with error bit) for any other (unlink()) error.
 *
 * @see unlinkat()
 */
#ifndef _di_f_file_remove_at_
  extern f_return_status f_file_remove_at(const int at_id, const f_string path, const int flags);
#endif // _di_f_file_remove_at_

/**
 * Given an open file descriptor, seek
 *
 * @param id
 *   The file descriptor.
 * @param whence
 *   One of: SEEK_SET, SEEK_CUR, SEEK_END, SEEK_DATA, SEEK_HOLE.
 * @param offset
 *   The offset to use, based off of whence.
 * @param seeked
 *   This gets update to represent the total amount seeked.
 *   To be compared against offset.
 *
 * @return
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_file_error_descriptor (with error bit) if the file descriptor is invalid.
 *   f_out_of_bound (with error bit) if SEEK_DATA or SEEK_HOLE is specified as whence and offset is beyond the end of file.
 *   f_number_overflow (with error bit) on overflow for offset.
 *   f_file_is_type_pipe (with error bit) if file descriptor represents a pipe, socket, or FIFO.
 *   f_failure (with error bit) on any other error.
 *
 * @see lseek
 */
#ifndef _di_f_file_seek_
  extern f_return_status f_file_seek(const int id, const int whence, const f_string_length offset, f_string_length *seeked);
#endif // _di_f_file_seek_

/**
 * Read the size of file.
 *
 * @param path
 *   The path to the file.
 * @param dereference
 *   Set to TRUE to dereferenc symlinks (often is what is desired).
 *   Set to FALSE to operate on the symlink itself.
 * @param size
 *   This gets set to the size of the file.
 *
 * @return
 *   f_none on success.
 *   f_invalid_name (with error bit) if the name is somehow invalid.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_number_overflow (with error bit) on overflow error.
 *   f_invalid_directory (with error bit) on invalid directory.
 *   f_file_not_found (with error bit) if the file was not found.
 *   f_access_denied (with error bit) if access to the file was denied.
 *   f_loop (with error bit) if a loop occurred.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_file_stat()
 */
#ifndef _di_f_file_size_
  extern f_return_status f_file_size(const f_string path, const bool dereference, f_string_length *size);
#endif // _di_f_file_size_

/**
 * Read the size of file.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path to the file.
 * @param dereference
 *   Set to TRUE to dereferenc symlinks (often is what is desired).
 *   Set to FALSE to operate on the symlink itself.
 * @param size
 *   This gets set to the size of the file.
 *
 * @return
 *   f_none on success.
 *   f_invalid_name (with error bit) if the name is somehow invalid.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_number_overflow (with error bit) on overflow error.
 *   f_invalid_directory (with error bit) on invalid directory.
 *   f_file_not_found (with error bit) if the file was not found.
 *   f_access_denied (with error bit) if access to the file was denied.
 *   f_loop (with error bit) if a loop occurred.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_file_stat_at()
 */
#ifndef _di_f_file_size_at_
  extern f_return_status f_file_size_at(const int at_id, const f_string path, const bool dereference, f_string_length *size);
#endif // _di_f_file_size_at_

/**
 * Read size of a file relative to the path represented by the file descriptor id.
 *
 * @param id
 *   The file descriptor.
 * @param size
 *   This gets set to the size of the file.
 *
 * @return
 *   f_none on success.
 *   f_invalid_name (with error bit) if the name is somehow invalid.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_number_overflow (with error bit) on overflow error.
 *   f_invalid_directory (with error bit) on invalid directory.
 *   f_file_not_found (with error bit) if the file was not found.
 *   f_access_denied (with error bit) if access to the file was denied.
 *   f_loop (with error bit) if a loop occurred.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see f_file_stat_by_id()
 */
#ifndef _di_f_file_size_by_id_
  extern f_return_status f_file_size_by_id(const int id, f_string_length *size);
#endif // _di_f_file_size_by_id_

/**
 * Read statistics of a file.
 *
 * @param path
 *   The path to the file.
 * @param dereference
 *   Set to TRUE to dereferenc symlinks (often is what is desired).
 *   Set to FALSE to operate on the symlink itself.
 * @param file_stat
 *   The statistics read.
 *
 * @return
 *   f_none on success.
 *   f_invalid_name (with error bit) if the name is somehow invalid.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_number_overflow (with error bit) on overflow error.
 *   f_invalid_directory (with error bit) on invalid directory.
 *   f_file_not_found (with error bit) if the file was not found.
 *   f_access_denied (with error bit) if access to the file was denied.
 *   f_loop (with error bit) if a loop occurred.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see stat()
 */
#ifndef _di_f_file_stat_
  extern f_return_status f_file_stat(const f_string path, const bool dereference, struct stat *file_stat);
#endif // _di_f_file_stat_

/**
 * Read statistics of a file relative to the path represented by the file descriptor id.
 *
 * @param at_id
 *   The parent directory, as an open directory file descriptor, in which path is relative to.
 * @param path
 *   The path to the file.
 * @param flags
 *   Any valid flag, such as AT_EMPTY_PATH, AT_NO_AUTOMOUNT, or AT_SYMLINK_NO_FOLLOW.
 * @param file_stat
 *   The statistics read.
 *
 * @return
 *   f_none on success.
 *   f_invalid_name (with error bit) if the name is somehow invalid.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_number_overflow (with error bit) on overflow error.
 *   f_invalid_directory (with error bit) on invalid directory.
 *   f_file_not_found (with error bit) if the file was not found.
 *   f_access_denied (with error bit) if access to the file was denied.
 *   f_loop (with error bit) if a loop occurred.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fstatat()
 */
#ifndef _di_f_file_stat_at_
  extern f_return_status f_file_stat_at(const int at_id, const f_string path, const int flags, struct stat *file_stat);
#endif // _di_f_file_stat_at_

/**
 * Read statistics of a file using a file descriptor id.
 *
 * @param id
 *   The file descriptor.
 * @param file_stat
 *   The statistics read.
 *
 * @return
 *   f_none on success.
 *   f_invalid_name (with error bit) if the name is somehow invalid.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_number_overflow (with error bit) on overflow error.
 *   f_invalid_directory (with error bit) on invalid directory.
 *   f_file_not_found (with error bit) if the file was not found.
 *   f_access_denied (with error bit) if access to the file was denied.
 *   f_loop (with error bit) if a loop occurred.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *
 * @see fstat()
 */
#ifndef _di_f_file_stat_by_id_
  extern f_return_status f_file_stat_by_id(const int id, struct stat *file_stat);
#endif // _di_f_file_stat_by_id_

/**
 * Write until entire buffer is written.
 *
 * @param file
 *   The file to write to.
 *   The file must already be open.
 * @param buffer
 *   The buffer to write to the file.
 * @param written
 *   The total bytes written.
 *
 * @return
 *   f_none on success.
 *   f_none_on_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   f_file_error_descriptor (with error bit) if the file descriptor is invalid.
 *   f_invalid_buffer (with error bit) if the buffer is invalid.
 *   f_interrupted (with error bit) if interrupt was received.
 *   f_error_input_output (with error bit) on I/O error.
 *   f_file_not_open (with error bit) if file is not open.
 *   f_file_is_type_directory (with error bit) if file descriptor represents a directory.
 *
 * @see write()
 */
#ifndef _di_f_file_write_
  extern f_return_status f_file_write(const f_file file, const f_string_dynamic buffer, f_string_length *written);
#endif // _di_f_file_write_

/**
 * Write until a single block is filled or entire buffer is written.
 *
 * To check how much was write into the buffer, record buffer->used before execution and compare to buffer->used after execution.
 *
 * @param file
 *   The file to write to.
 *   The file must already be open.
 * @param buffer
 *   The buffer to write to the file.
 * @param written
 *   The total bytes written.
 *
 * @return
 *   f_none on success.
 *   f_none_on_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   f_file_error_descriptor (with error bit) if the file descriptor is invalid.
 *   f_invalid_buffer (with error bit) if the buffer is invalid.
 *   f_interrupted (with error bit) if interrupt was received.
 *   f_error_input_output (with error bit) on I/O error.
 *   f_file_not_open (with error bit) if file is not open.
 *   f_file_is_type_directory (with error bit) if file descriptor represents a directory.
 *
 * @see write()
 */
#ifndef _di_f_file_write_block_
  extern f_return_status f_file_write_block(const f_file file, const f_string_dynamic buffer, f_string_length *written);
#endif // _di_f_file_write_block_

/**
 * Write until a given number or entire buffer is written.
 *
 * @param file
 *   The file to write to.
 *   The file must already be open.
 * @param buffer
 *   The buffer to write to the file.
 * @param total
 *   The total bytes to write, unless end of buffer is reached first.
 * @param written
 *   The total bytes written.
 *
 * @return
 *   f_none on success.
 *   f_none_on_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *   f_none_on_eos on success but range.stop exceeded buffer.used (only wrote up to buffer.used).
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   f_file_error_descriptor (with error bit) if the file descriptor is invalid.
 *   f_invalid_buffer (with error bit) if the buffer is invalid.
 *   f_interrupted (with error bit) if interrupt was received.
 *   f_error_input_output (with error bit) on I/O error.
 *   f_file_not_open (with error bit) if file is not open.
 *   f_file_is_type_directory (with error bit) if file descriptor represents a directory.
 *
 * @see write()
 */
#ifndef _di_f_file_write_until_
  extern f_return_status f_file_write_until(const f_file file, const f_string_dynamic buffer, const f_string_length total, f_string_length *written);
#endif // _di_f_file_write_until_

/**
 * Write a given range within the buffer.
 *
 * @param file
 *   The file to write to.
 *   The file must already be open.
 * @param buffer
 *   The buffer to write to the file.
 * @param range
 *   An inclusive start an stop range within the buffer to read.
 * @param written
 *   The total bytes written.
 *
 * @return
 *   f_none on success.
 *   f_none_on_stop on success but no data was written (written == 0) (not an error and often happens if file type is not a regular file).
 *   f_none_on_eos on success but range.stop exceeded buffer.used (only wrote up to buffer.used).
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_block (with error bit) if file descriptor is set to non-block and the write would result in a blocking operation.
 *   f_file_error_descriptor (with error bit) if the file descriptor is invalid.
 *   f_invalid_buffer (with error bit) if the buffer is invalid.
 *   f_interrupted (with error bit) if interrupt was received.
 *   f_error_input_output (with error bit) on I/O error.
 *   f_file_not_open (with error bit) if file is not open.
 *   f_file_is_type_directory (with error bit) if file descriptor represents a directory.
 *
 * @see write()
 */
#ifndef _di_f_file_write_range_
  extern f_return_status f_file_write_range(const f_file file, const f_string_dynamic buffer, const f_string_range range, f_string_length *written);
#endif // _di_f_file_write_range_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_file_h
