/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Defines common data to be used for/by project file.
 *
 * This is auto-included by file.h and should not need to be explicitly included.
 */
#ifndef _F_file_common_h
#define _F_file_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Provide common file-typ specific data types.
 */
#ifndef _di_f_file_types_
  #define f_file_default_read_size  8192 // default to 8k read sizes. // @fixme: rename and move into _di_f_file_type_
  #define f_file_default_write_size 8192 // default to 8k write sizes. // @fixme: rename and move into _di_f_file_type_
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
 *
 * These type macros are of size 32-bit (int32_t).
 */
#ifndef _di_f_file_type_
  #define f_file_type_mask S_IFMT

  #define f_file_type_block     S_IFBLK
  #define f_file_type_character S_IFCHR
  #define f_file_type_directory S_IFDIR
  #define f_file_type_fifo      S_IFIFO
  #define f_file_type_link      S_IFLNK
  #define f_file_type_regular   S_IFREG
  #define f_file_type_socket    S_IFSOCK

  #define f_file_type_name_block     "block"
  #define f_file_type_name_character "character"
  #define f_file_type_name_directory "directory"
  #define f_file_type_name_fifo      "fifo"
  #define f_file_type_name_link      "link"
  #define f_file_type_name_regular   "regular"
  #define f_file_type_name_socket    "socket"

  #define f_file_type_name_block_length     5
  #define f_file_type_name_character_length 9
  #define f_file_type_name_directory_length 9
  #define f_file_type_name_fifo_length      4
  #define f_file_type_name_link_length      4
  #define f_file_type_name_regular_length   7
  #define f_file_type_name_socket_length    6

  #define f_macro_file_type_get(mode) (f_file_type_mask & mode)

  #define f_macro_file_type_is_block(mode)     f_macro_file_type_get(mode) == f_file_type_block
  #define f_macro_file_type_is_character(mode) f_macro_file_type_get(mode) == f_file_type_character
  #define f_macro_file_type_is_directory(mode) f_macro_file_type_get(mode) == f_file_type_directory
  #define f_macro_file_type_is_fifo(mode)      f_macro_file_type_get(mode) == f_file_type_fifo
  #define f_macro_file_type_is_link(mode)      f_macro_file_type_get(mode) == f_file_type_link
  #define f_macro_file_type_is_regular(mode)   f_macro_file_type_get(mode) == f_file_type_regular
  #define f_macro_file_type_is_socket(mode)    f_macro_file_type_get(mode) == f_file_type_socket

  #define f_macro_file_open_mode_append        "a"
  #define f_macro_file_open_mode_read          "r"
  #define f_macro_file_open_mode_read_append   "a+"
  #define f_macro_file_open_mode_read_truncate "w+"
  #define f_macro_file_open_mode_read_write    "r+"
  #define f_macro_file_open_mode_truncate      "w"

  // @todo consider adding the following for the different strings in this project.
  //static char * const f_file_open_mode_append_s = f_macro_file_open_mode_append;
#endif // _di_f_file_type_

/**
 * Commonly used file related properties.
 *
 * stream: File stream.
 * id: File descriptor, with a value of -1 represents a closed file.
 * flag: Flags used for opening the file.
 * size_read: The default number of 1-byte characters to read at a time and is often used for the read buffer size.
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

  #define f_file_t_initialize { 0, -1, f_file_flag_read_only, f_file_default_read_size, f_file_default_write_size }

  #define f_macro_file_t_initialize(stream, id, flag, read_size, write_size) { stream, id, flag, read_size, write_size }
  #define f_macro_file_t_initialize2(stream, id, flag) { stream, id, flag, f_file_default_read_size, f_file_default_write_size }

  #define f_macro_file_t_clear(file) \
    file.stream = 0; \
    file.id = -1; \
    file.flag = 0; \
    file.size_read = 0; \
    file.size_write = 0;

  #define f_macro_file_t_reset(file) \
    file.stream = 0; \
    file.id = -1; \
    file.flag = f_file_flag_read_only; \
    file.size_read = f_file_default_read_size; \
    file.size_write = f_file_default_write_size;
#endif // _di_f_file_t_

/**
 * File AT_* define related functionality.
 */
#ifndef _di_f_file_at_
  #define f_file_at_current_working    -100
  #define f_file_at_symlink_follow     0x400
  #define f_file_at_symlink_follow_no  0x100
  #define f_file_at_remove_directory   0x200
  #define f_file_at_automount_no       0x800
  #define f_file_at_path_empty         0x1000
  #define f_file_at_statx_sync_type    0x6000
  #define f_file_at_statx_sync_as_stat 0x0000
  #define f_file_at_statx_sync_force   0x2000
  #define f_file_at_statx_sync_no      0x4000
#endif // _di_f_file_at_

/**
 * File flag related functionality.
 */
#ifndef _di_f_file_flag_

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
  #define f_file_flag_path               010000000
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

  // file open flags pre-combined will truncate any existing files to 0.
  #define f_file_flag_append_rw (O_CREAT | O_APPEND | O_RDRW)
  #define f_file_flag_append_wo (O_CREAT | O_APPEND | O_WRONLY)

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
#endif // _di_f_file_flag_

/**
 * File mode related functionality.
 *
 * There are two types of file modes the f_file_mode_t macros associate with.
 *
 * The first type is the traditional mode type, associated with mode_t.
 *
 * The second type is f_file_mode_t, which utilizes 8-bit types with the following structure:
 *
 *   There should only be a single bit for each 'r', 'w', 'x', and 'X' bit (as well as 'S', 's', and 't'):
 *     'r' = read bit.
 *     'w' = write bit.
 *     'x' = execute bit.
 *     'X' = execute only if already execute bit.
 *     'S' = set user bit (setuid).
 *     's' = set group bit (setgid).
 *     't' = sticky bit.
 *
 * The file mode macros with "f_file_mode_" prefix (has no "_t") refer to the first type (mode_t).
 * The file mode macros with "f_file_mode_t" prefix refer to the second type (f_file_mode_t).
 */
#ifndef _di_f_file_mode_
  typedef uint32_t f_file_mode_t;

  #define f_file_mode_t_block_special 0x77000000 // 0111 0111 0000 0000 0000 0000 0000 0000
  #define f_file_mode_t_block_owner   0x00ff0000 // 0000 0000 1111 1111 0000 0000 0000 0000
  #define f_file_mode_t_block_group   0x0000ff00 // 0000 0000 0000 0000 1111 1111 0000 0000
  #define f_file_mode_t_block_world   0x000000ff // 0000 0000 0000 0000 0000 0000 1111 1111

  #define f_file_mode_t_block_all      0x77ffffff // 0111 0111 1111 1111 1111 1111 1111 1111
  #define f_file_mode_t_block_standard 0x00ffffff // 0000 0000 1111 1111 1111 1111 1111 1111

  #define f_file_mode_t_mask_how_add      0x070f0f0f // 0000 0111 0000 1111 0000 1111 0000 1111
  #define f_file_mode_t_mask_how_subtract 0x70f0f0f0 // 0111 0000 1111 0000 1111 0000 1111 0000

  #define f_file_mode_t_mask_bit_execute      0x00111111 // 0000 0000 0001 0001 0001 0001 0001 0001
  #define f_file_mode_t_mask_bit_execute_only 0x00888888 // 0000 0000 1000 1000 1000 1000 1000 1000
  #define f_file_mode_t_mask_bit_read         0x00444444 // 0000 0000 0100 0100 0100 0100 0100 0100
  #define f_file_mode_t_mask_bit_set_group    0x22000000 // 0010 0010 0000 0000 0000 0000 0000 0000
  #define f_file_mode_t_mask_bit_set_owner    0x44000000 // 0100 0100 0000 0000 0000 0000 0000 0000
  #define f_file_mode_t_mask_bit_sticky       0x11000000 // 0001 0001 0000 0000 0000 0000 0000 0000
  #define f_file_mode_t_mask_bit_write        0x00222222 // 0000 0000 0010 0010 0010 0010 0010 0010

  #define f_file_mode_t_replace_owner     0x1  // 0000 0001
  #define f_file_mode_t_replace_group     0x2  // 0000 0010
  #define f_file_mode_t_replace_world     0x4  // 0000 0100
  #define f_file_mode_t_replace_special   0x8  // 0000 1000
  #define f_file_mode_t_replace_directory 0x10 // 0001 0000

  #define f_file_mode_t_replace_all      0x1f // 0001 1111
  #define f_file_mode_t_replace_other    0x18 // 0001 1000
  #define f_file_mode_t_replace_standard 0x7  // 0000 0111

  // file permission modes (mode_t).
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

  // file mode set-uid/set-gid/sticky-bits and all bits (mode_t).
  #define f_file_mode_special_set_user  S_ISUID
  #define f_file_mode_special_set_group S_ISGID
  #define f_file_mode_special_sticky    S_ISVTX
  #define f_file_mode_special_all       (S_ISUID | S_ISGID | S_ISVTX)

  // all permissions modes and special modes (mode_t).
  #define f_file_mode_all (f_file_mode_special_all | f_file_mode_all_rwx)

  // special file mode combinations (mode_t).
  #define f_file_mode_user_access    (f_file_mode_owner_rwx | f_file_mode_group_rwx | f_file_mode_world_x)
  #define f_file_mode_user_directory (f_file_mode_owner_rwx | f_file_mode_group_rwx)
  #define f_file_mode_user_file      (f_file_mode_owner_rw | f_file_mode_group_rw)
  #define f_file_mode_user_program   (f_file_mode_owner_rx | f_file_mode_group_rx)
  #define f_file_mode_user_protected (f_file_mode_owner_r | f_file_mode_group_r)
#endif // _di_f_file_mode_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_file_h
