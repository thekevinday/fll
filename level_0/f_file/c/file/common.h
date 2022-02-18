/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
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
 * Provide file defaults.
 *
 * F_file_default_*:
 *   - read_size:  Default read size in bytes.
 *   - write_size: Default write size in bytes.
 */
#ifndef _di_f_file_defaults_
  #define F_file_default_read_size_d  8192
  #define F_file_default_write_size_d 8192
#endif // _di_f_file_defaults_

/**
 * Provide macros for file-seek operations.
 *
 * The fseek() function parameters can be confusing, so provide a hopefully more readibly code via these macros.
 *
 * macro_f_file_seek_*:
 *   - begin: sets the file pointer from this many bytes from the beginning of the file.
 *   - data:  sets the file pointer from this many bytes from the end of the file, relative to the next data.
 *   - end:   sets the file pointer from this many bytes from the end of the file.
 *   - hole:  sets the file pointer from this many bytes from the end of the file, relative to the next hole.
 *   - to:    sets the file pointer from this many bytes relative to the current position.
 */
#ifndef _di_f_file_seeks_
  #define macro_f_file_seek_begin(file, bytes) fseek(file, bytes, SEEK_SET)
  #define macro_f_file_seek_data(file, bytes)  fseek(file, bytes, SEEK_DATA)
  #define macro_f_file_seek_end(file)          fseek(file, bytes, SEEK_END)
  #define macro_f_file_seek_hole(file, bytes)  fseek(file, bytes, SEEK_HOLE)
  #define macro_f_file_seek_to(file, bytes)    fseek(file, bytes, SEEK_CUR)
#endif // _di_f_file_seeks_

/**
 * Provide file type macros.
 *
 * These type macros are of size 32-bit (int32_t).
 */
#ifndef _di_f_file_type_
  #define F_file_type_mask_d S_IFMT

  #define F_file_type_block_d     S_IFBLK
  #define F_file_type_character_d S_IFCHR
  #define F_file_type_directory_d S_IFDIR
  #define F_file_type_fifo_d      S_IFIFO
  #define F_file_type_link_d      S_IFLNK
  #define F_file_type_regular_d   S_IFREG
  #define F_file_type_socket_d    S_IFSOCK

  #define F_file_type_name_block_s     "block"
  #define F_file_type_name_character_s "character"
  #define F_file_type_name_directory_s "directory"
  #define F_file_type_name_fifo_s      "fifo"
  #define F_file_type_name_link_s      "link"
  #define F_file_type_name_regular_s   "regular"
  #define F_file_type_name_socket_s    "socket"

  #define F_file_type_name_block_s_length     5
  #define F_file_type_name_character_s_length 9
  #define F_file_type_name_directory_s_length 9
  #define F_file_type_name_fifo_s_length      4
  #define F_file_type_name_link_s_length      4
  #define F_file_type_name_regular_s_length   7
  #define F_file_type_name_socket_s_length    6

  #define macro_f_file_type_get(mode) (F_file_type_mask_d & mode)

  #define macro_f_file_type_is_block(mode)     (macro_f_file_type_get(mode) == F_file_type_block_d)
  #define macro_f_file_type_is_character(mode) (macro_f_file_type_get(mode) == F_file_type_character_d)
  #define macro_f_file_type_is_directory(mode) (macro_f_file_type_get(mode) == F_file_type_directory_d)
  #define macro_f_file_type_is_fifo(mode)      (macro_f_file_type_get(mode) == F_file_type_fifo_d)
  #define macro_f_file_type_is_link(mode)      (macro_f_file_type_get(mode) == F_file_type_link_d)
  #define macro_f_file_type_is_regular(mode)   (macro_f_file_type_get(mode) == F_file_type_regular_d)
  #define macro_f_file_type_is_socket(mode)    (macro_f_file_type_get(mode) == F_file_type_socket_d)

  #define F_file_open_mode_append_s        "a"
  #define F_file_open_mode_read_s          "r"
  #define F_file_open_mode_read_append_s   "a+"
  #define F_file_open_mode_read_truncate_s "w+"
  #define F_file_open_mode_read_write_s    "r+"
  #define F_file_open_mode_truncate_s      "w"

  #define F_file_open_mode_append_s_length        1
  #define F_file_open_mode_read_s_length          1
  #define F_file_open_mode_read_append_s_length   2
  #define F_file_open_mode_read_truncate_s_length 2
  #define F_file_open_mode_read_write_s_length    2
  #define F_file_open_mode_truncate_s_length      1

  extern const f_string_static_t f_file_type_name_block_s;
  extern const f_string_static_t f_file_type_name_character_s;
  extern const f_string_static_t f_file_type_name_directory_s;
  extern const f_string_static_t f_file_type_name_fifo_s;
  extern const f_string_static_t f_file_type_name_link_s;
  extern const f_string_static_t f_file_type_name_regular_s;
  extern const f_string_static_t f_file_type_name_socket_s;

  extern const f_string_static_t f_file_open_mode_append_s;
  extern const f_string_static_t f_file_open_mode_read_s;
  extern const f_string_static_t f_file_open_mode_read_append_s;
  extern const f_string_static_t f_file_open_mode_read_truncate_s;
  extern const f_string_static_t f_file_open_mode_read_write_s;
  extern const f_string_static_t f_file_open_mode_truncate_s;
#endif // _di_f_file_type_

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

  #define f_file_t_initialize { 0, -1, F_file_flag_read_only_d, F_file_default_read_size_d, F_file_default_write_size_d }

  #define macro_f_file_t_initialize(stream, id, flag, read_size, write_size) { stream, id, flag, read_size, write_size }
  #define macro_f_file_t_initialize2(stream, id, flag) { stream, id, flag, F_file_default_read_size_d, F_file_default_write_size_d }

  #define macro_f_file_t_clear(file) \
    file.stream = 0; \
    file.id = -1; \
    file.flag = 0; \
    file.size_read = 0; \
    file.size_write = 0;

  #define macro_f_file_t_reset(file) \
    file.stream = 0; \
    file.id = -1; \
    file.flag = F_file_flag_read_only_d; \
    file.size_read = F_file_default_read_size_d; \
    file.size_write = F_file_default_write_size_d;
#endif // _di_f_file_t_

/**
 * File AT_* define related functionality.
 */
#ifndef _di_f_file_at_
  #define F_file_at_current_working_d    -100
  #define F_file_at_symlink_follow_d     0x400
  #define F_file_at_symlink_follow_no_d  0x100
  #define F_file_at_remove_directory_d   0x200
  #define F_file_at_automount_no_d       0x800
  #define F_file_at_path_empty_d         0x1000
  #define F_file_at_statx_sync_type_d    0x6000
  #define F_file_at_statx_sync_as_stat_d 0x0000
  #define F_file_at_statx_sync_force_d   0x2000
  #define F_file_at_statx_sync_no_d      0x4000
#endif // _di_f_file_at_

/**
 * File flag related functionality.
 */
#ifndef _di_f_file_flag_

  // file open flags
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
  #define F_file_flag_path_d               010000000
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
#endif // _di_f_file_flag_

/**
 * File mode related functionality.
 *
 * There are two types of file modes that the f_file_mode_t macros are associated with.
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

  #define f_file_mode_t_initialize 0

  #define F_file_mode_t_block_special_d 0x77000000 // 0111 0111 0000 0000 0000 0000 0000 0000
  #define F_file_mode_t_block_owner_d   0x00ff0000 // 0000 0000 1111 1111 0000 0000 0000 0000
  #define F_file_mode_t_block_group_d   0x0000ff00 // 0000 0000 0000 0000 1111 1111 0000 0000
  #define F_file_mode_t_block_world_d   0x000000ff // 0000 0000 0000 0000 0000 0000 1111 1111

  #define F_file_mode_t_block_all_d      0x77ffffff // 0111 0111 1111 1111 1111 1111 1111 1111
  #define F_file_mode_t_block_standard_d 0x00ffffff // 0000 0000 1111 1111 1111 1111 1111 1111

  #define F_file_mode_t_mask_how_add_d      0x070f0f0f // 0000 0111 0000 1111 0000 1111 0000 1111
  #define F_file_mode_t_mask_how_subtract_d 0x70f0f0f0 // 0111 0000 1111 0000 1111 0000 1111 0000

  #define F_file_mode_t_mask_bit_execute_d      0x00111111 // 0000 0000 0001 0001 0001 0001 0001 0001
  #define F_file_mode_t_mask_bit_execute_only_d 0x00888888 // 0000 0000 1000 1000 1000 1000 1000 1000
  #define F_file_mode_t_mask_bit_read_d         0x00444444 // 0000 0000 0100 0100 0100 0100 0100 0100
  #define F_file_mode_t_mask_bit_set_group_d    0x22000000 // 0010 0010 0000 0000 0000 0000 0000 0000
  #define F_file_mode_t_mask_bit_set_owner_d    0x44000000 // 0100 0100 0000 0000 0000 0000 0000 0000
  #define F_file_mode_t_mask_bit_sticky_d       0x11000000 // 0001 0001 0000 0000 0000 0000 0000 0000
  #define F_file_mode_t_mask_bit_write_d        0x00222222 // 0000 0000 0010 0010 0010 0010 0010 0010

  #define F_file_mode_t_replace_world_d     0x1  // 0000 0001
  #define F_file_mode_t_replace_group_d     0x2  // 0000 0010
  #define F_file_mode_t_replace_owner_d     0x4  // 0000 0100
  #define F_file_mode_t_replace_special_d   0x8  // 0000 1000
  #define F_file_mode_t_replace_directory_d 0x10 // 0001 0000

  #define F_file_mode_t_replace_all_d      0x1f // 0001 1111
  #define F_file_mode_t_replace_other_d    0x18 // 0001 1000
  #define F_file_mode_t_replace_standard_d 0x7  // 0000 0111

  // File permission modes (mode_t).
  #define F_file_mode_owner_rwx_d S_IRWXU
  #define F_file_mode_owner_r_d   S_IRUSR
  #define F_file_mode_owner_w_d   S_IWUSR
  #define F_file_mode_owner_x_d   S_IXUSR
  #define F_file_mode_owner_rw_d  (S_IRUSR | S_IWUSR)
  #define F_file_mode_owner_rx_d  (S_IRUSR | S_IXUSR)
  #define F_file_mode_owner_wx_d  (S_IWUSR | S_IXUSR)
  #define F_file_mode_group_rwx_d S_IRWXG
  #define F_file_mode_group_r_d   S_IRGRP
  #define F_file_mode_group_w_d   S_IWGRP
  #define F_file_mode_group_x_d   S_IXGRP
  #define F_file_mode_group_rw_d  (S_IRGRP | S_IWGRP)
  #define F_file_mode_group_rx_d  (S_IRGRP | S_IXGRP)
  #define F_file_mode_group_wx_d  (S_IWGRP | S_IXGRP)
  #define F_file_mode_world_rwx_d S_IRWXO
  #define F_file_mode_world_r_d   S_IROTH
  #define F_file_mode_world_w_d   S_IWOTH
  #define F_file_mode_world_x_d   S_IXOTH
  #define F_file_mode_world_rw_d  (S_IROTH | S_IWOTH)
  #define F_file_mode_world_rx_d  (S_IROTH | S_IXOTH)
  #define F_file_mode_world_wx_d  (S_IWOTH | S_IXOTH)

  #define F_file_mode_all_rwx_d (F_file_mode_owner_rwx_d | F_file_mode_group_rwx_d | F_file_mode_world_rwx_d)
  #define F_file_mode_all_rw_d  (F_file_mode_owner_rw_d | F_file_mode_group_rw_d | F_file_mode_world_rw_d)
  #define F_file_mode_all_wx_d  (F_file_mode_owner_wx_d | F_file_mode_group_wx_d | F_file_mode_world_wx_d)
  #define F_file_mode_all_rx_d  (F_file_mode_owner_rx_d | F_file_mode_group_rx_d | F_file_mode_world_rx_d)
  #define F_file_mode_all_r_d   (F_file_mode_owner_r_d | F_file_mode_group_r_d | F_file_mode_world_r_d)
  #define F_file_mode_all_w_d   (F_file_mode_owner_w_d | F_file_mode_group_w_d | F_file_mode_world_w_d)
  #define F_file_mode_all_x_d   (F_file_mode_owner_x_d | F_file_mode_group_x_d | F_file_mode_world_x_d)

  // File mode set-uid/set-gid/sticky-bits and all bits (mode_t).
  #define F_file_mode_special_set_user_d  S_ISUID
  #define F_file_mode_special_set_group_d S_ISGID
  #define F_file_mode_special_sticky_d    S_ISVTX
  #define F_file_mode_special_all_d       (S_ISUID | S_ISGID | S_ISVTX)

  // All permissions modes and special modes (mode_t).
  #define F_file_mode_all_d (F_file_mode_special_all_d | F_file_mode_all_rwx_d)

  // Special file mode combinations (mode_t).
  #define F_file_mode_user_access_d    (F_file_mode_owner_rwx_d | F_file_mode_group_rwx_d | F_file_mode_world_x_d)
  #define F_file_mode_user_directory_d (F_file_mode_owner_rwx_d | F_file_mode_group_rwx_d)
  #define F_file_mode_user_file_d      (F_file_mode_owner_rw_d | F_file_mode_group_rw_d)
  #define F_file_mode_user_program_d   (F_file_mode_owner_rx_d | F_file_mode_group_rx_d)
  #define F_file_mode_user_protected_d (F_file_mode_owner_r_d | F_file_mode_group_r_d)
#endif // _di_f_file_mode_

/**
 * Provide common file operation strings.
 *
 * F_file_operation_*:
 *   - access:       Access a file.
 *   - analyze:      Analyze a file.
 *   - append:       Append to a file.
 *   - change_group: Change group of a file.
 *   - change_mode:  Change mode of a file (read, write, execute, etc.. permissions).
 *   - change_owner: Change owner of a file.
 *   - change_type:  Change type of a file.
 *   - clone:        Clone a file.
 *   - close:        Close a file.
 *   - concatenate:  Concatenate a file.
 *   - connect:      Connect to a file (such as a socket file).
 *   - copy:         Copy a file.
 *   - create:       Create a file.
 *   - decrypt:      Decrypt a file.
 *   - delete:       Delete a file.
 *   - disconnect:   Disconnect from a file (such as a socket file).
 *   - encrypt:      Encrypt a file.
 *   - find:         Find a file.
 *   - from:         Do something from a file.
 *   - flush:        Flush a file.
 *   - get_group:    Get group of a file.
 *   - get_mode:     Get mode of a file (read, write, execute, etc.. permissions).
 *   - get_owner:    Get owner of a file.
 *   - get_type:     Get type of a file.
 *   - identify:     Identify a file.
 *   - link:         Link a file.
 *   - list:         List a file.
 *   - move:         Move a file.
 *   - open:         Open a file.
 *   - pipe:         Pipe a file.
 *   - process:      Process a file.
 *   - read:         Read a file.
 *   - receive:      Receive a file.
 *   - rename:       Rename a file.
 *   - send:         Send a file.
 *   - shred:        Shred a file.
 *   - stat:         Determine file statistics.
 *   - to:           Do someting to a file.
 *   - touch:        Touch a file (Create it if it does not exist or update its last write time stamp).
 *   - truncate:     Truncate a file.
 *   - unlink:       Unlink a file.
 *   - verify:       Verify a file.
 *   - wipe:         Wipe a file.
 *   - write:        Write a file.
 */
#ifndef _di_f_file_operation_strings_
  #define F_file_operation_access_s       "access"
  #define F_file_operation_analyze_s      "analyze"
  #define F_file_operation_append_s       "append"
  #define F_file_operation_change_group_s "change group of"
  #define F_file_operation_change_mode_s  "change mode of"
  #define F_file_operation_change_owner_s "change owner of"
  #define F_file_operation_change_type_s  "change type of"
  #define F_file_operation_clone_s        "clone"
  #define F_file_operation_close_s        "close"
  #define F_file_operation_concatenate_s  "concatenate"
  #define F_file_operation_connect_s      "connect"
  #define F_file_operation_copy_s         "copy"
  #define F_file_operation_create_s       "create"
  #define F_file_operation_decrypt_s      "decrypt"
  #define F_file_operation_delete_s       "delete"
  #define F_file_operation_disconnect_s   "disconnect"
  #define F_file_operation_encrypt_s      "encrypt"
  #define F_file_operation_find_s         "find"
  #define F_file_operation_from_s         "from"
  #define F_file_operation_flush_s        "flush"
  #define F_file_operation_get_group_s    "get group of"
  #define F_file_operation_get_mode_s     "get mode of"
  #define F_file_operation_get_owner_s    "get owner of"
  #define F_file_operation_get_type_s     "get type of"
  #define F_file_operation_identify_s     "identify"
  #define F_file_operation_link_s         "link"
  #define F_file_operation_list_s         "list"
  #define F_file_operation_move_s         "move"
  #define F_file_operation_open_s         "open"
  #define F_file_operation_pipe_s         "pipe"
  #define F_file_operation_process_s      "process"
  #define F_file_operation_read_s         "read"
  #define F_file_operation_receive_s      "receive"
  #define F_file_operation_rename_s       "rename"
  #define F_file_operation_send_s         "send"
  #define F_file_operation_shred_s        "shred"
  #define F_file_operation_stat_s         "stat"
  #define F_file_operation_to_s           "to"
  #define F_file_operation_touch_s        "touch"
  #define F_file_operation_truncate_s     "truncate"
  #define F_file_operation_unlink_s       "unlink"
  #define F_file_operation_verify_s       "verify"
  #define F_file_operation_wipe_s         "wipe"
  #define F_file_operation_write_s        "write"

  #define F_file_operation_access_s_length       6
  #define F_file_operation_analyze_s_length      7
  #define F_file_operation_append_s_length       6
  #define F_file_operation_change_group_s_length 15
  #define F_file_operation_change_mode_s_length  14
  #define F_file_operation_change_owner_s_length 15
  #define F_file_operation_change_type_s_length  14
  #define F_file_operation_clone_s_length        5
  #define F_file_operation_close_s_length        5
  #define F_file_operation_concatenate_s_length  11
  #define F_file_operation_connect_s_length      7
  #define F_file_operation_copy_s_length         4
  #define F_file_operation_create_s_length       6
  #define F_file_operation_decrypt_s_length      7
  #define F_file_operation_delete_s_length       6
  #define F_file_operation_disconnect_s_length   10
  #define F_file_operation_encrypt_s_length      7
  #define F_file_operation_find_s_length         4
  #define F_file_operation_from_s_length         4
  #define F_file_operation_flush_s_length        5
  #define F_file_operation_get_group_s_length    12
  #define F_file_operation_get_mode_s_length     11
  #define F_file_operation_get_owner_s_length    12
  #define F_file_operation_get_type_s_length     11
  #define F_file_operation_identify_s_length     8
  #define F_file_operation_link_s_length         4
  #define F_file_operation_list_s_length         4
  #define F_file_operation_move_s_length         4
  #define F_file_operation_open_s_length         4
  #define F_file_operation_pipe_s_length         4
  #define F_file_operation_process_s_length      7
  #define F_file_operation_read_s_length         4
  #define F_file_operation_rename_s_length       6
  #define F_file_operation_receive_s_length      7
  #define F_file_operation_send_s_length         4
  #define F_file_operation_shred_s_length        5
  #define F_file_operation_stat_s_length         4
  #define F_file_operation_to_s_length           2
  #define F_file_operation_touch_s_length        5
  #define F_file_operation_truncate_s_length     8
  #define F_file_operation_unlink_s_length       6
  #define F_file_operation_verify_s_length       6
  #define F_file_operation_wipe_s_length         4
  #define F_file_operation_write_s_length        5

  extern const f_string_static_t f_file_operation_access_s;
  extern const f_string_static_t f_file_operation_analyze_s;
  extern const f_string_static_t f_file_operation_append_s;
  extern const f_string_static_t f_file_operation_change_group_s;
  extern const f_string_static_t f_file_operation_change_mode_s;
  extern const f_string_static_t f_file_operation_change_owner_s;
  extern const f_string_static_t f_file_operation_change_type_s;
  extern const f_string_static_t f_file_operation_clone_s;
  extern const f_string_static_t f_file_operation_close_s;
  extern const f_string_static_t f_file_operation_concatenate_s;
  extern const f_string_static_t f_file_operation_connect_s;
  extern const f_string_static_t f_file_operation_copy_s;
  extern const f_string_static_t f_file_operation_create_s;
  extern const f_string_static_t f_file_operation_decrypt_s;
  extern const f_string_static_t f_file_operation_delete_s;
  extern const f_string_static_t f_file_operation_disconnect_s;
  extern const f_string_static_t f_file_operation_encrypt_s;
  extern const f_string_static_t f_file_operation_find_s;
  extern const f_string_static_t f_file_operation_from_s;
  extern const f_string_static_t f_file_operation_flush_s;
  extern const f_string_static_t f_file_operation_get_group_s;
  extern const f_string_static_t f_file_operation_get_mode_s;
  extern const f_string_static_t f_file_operation_get_owner_s;
  extern const f_string_static_t f_file_operation_get_type_s;
  extern const f_string_static_t f_file_operation_identify_s;
  extern const f_string_static_t f_file_operation_link_s;
  extern const f_string_static_t f_file_operation_list_s;
  extern const f_string_static_t f_file_operation_move_s;
  extern const f_string_static_t f_file_operation_open_s;
  extern const f_string_static_t f_file_operation_pipe_s;
  extern const f_string_static_t f_file_operation_process_s;
  extern const f_string_static_t f_file_operation_read_s;
  extern const f_string_static_t f_file_operation_receive_s;
  extern const f_string_static_t f_file_operation_rename_s;
  extern const f_string_static_t f_file_operation_send_s;
  extern const f_string_static_t f_file_operation_shred_s;
  extern const f_string_static_t f_file_operation_stat_s;
  extern const f_string_static_t f_file_operation_to_s;
  extern const f_string_static_t f_file_operation_touch_s;
  extern const f_string_static_t f_file_operation_truncate_s;
  extern const f_string_static_t f_file_operation_unlink_s;
  extern const f_string_static_t f_file_operation_verify_s;
  extern const f_string_static_t f_file_operation_wipe_s;
  extern const f_string_static_t f_file_operation_write_s;
#endif // _di_f_file_operation_strings_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_file_h
