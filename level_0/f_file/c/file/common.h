/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.7
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
#ifndef _di_f_file_seeks_d_
  #define macro_f_file_seek_begin(file, bytes) fseek(file, bytes, SEEK_SET)
  #define macro_f_file_seek_data(file, bytes)  fseek(file, bytes, SEEK_DATA)
  #define macro_f_file_seek_end(file)          fseek(file, bytes, SEEK_END)
  #define macro_f_file_seek_hole(file, bytes)  fseek(file, bytes, SEEK_HOLE)
  #define macro_f_file_seek_to(file, bytes)    fseek(file, bytes, SEEK_CUR)
#endif // _di_f_file_seeks_d_

/**
 * Provide file type macros.
 *
 * These type macros are of size 32-bit (int32_t).
 *
 * F_file_type_*:
 *   - block:     The file type is a block device.
 *   - character: The file type is a character device.
 *   - directory: The file type is a directory.
 *   - fifo:      The file type is a File-In-File-Out pipe.
 *   - mask:      A mask used to get the bits of the file data representing the file type.
 *   - link:      The file type is a file link.
 *   - regular:   The file type is a regular file.
 *   - socket:    The file type is a socket file.
 */
#ifndef _di_f_file_type_d_
  #define F_file_type_block_d     S_IFBLK
  #define F_file_type_character_d S_IFCHR
  #define F_file_type_directory_d S_IFDIR
  #define F_file_type_fifo_d      S_IFIFO
  #define F_file_type_link_d      S_IFLNK
  #define F_file_type_mask_d      S_IFMT
  #define F_file_type_regular_d   S_IFREG
  #define F_file_type_socket_d    S_IFSOCK

  #define macro_f_file_type_get(mode) (F_file_type_mask_d & mode)

  #define macro_f_file_type_is_block(mode)     (macro_f_file_type_get(mode) == F_file_type_block_d)
  #define macro_f_file_type_is_character(mode) (macro_f_file_type_get(mode) == F_file_type_character_d)
  #define macro_f_file_type_is_directory(mode) (macro_f_file_type_get(mode) == F_file_type_directory_d)
  #define macro_f_file_type_is_fifo(mode)      (macro_f_file_type_get(mode) == F_file_type_fifo_d)
  #define macro_f_file_type_is_link(mode)      (macro_f_file_type_get(mode) == F_file_type_link_d)
  #define macro_f_file_type_is_regular(mode)   (macro_f_file_type_get(mode) == F_file_type_regular_d)
  #define macro_f_file_type_is_socket(mode)    (macro_f_file_type_get(mode) == F_file_type_socket_d)
#endif // _di_f_file_type_d_

/**
 * Provide file type strings.
 *
 * F_file_type_name_*:
 *  - block:     A string representing the block file type.
 *  - character: A string representing the character file type.
 *  - directory: A string representing the directory file type.
 *  - fifo:      A string representing the fifo file type.
 *  - file:      A string representing the common term for a regular file.
 *  - link:      A string representing the link file type.
 *  - regular:   A string representing the regular file type.
 *  - socket:    A string representing the socket file type.
 */
#ifndef _di_f_file_type_s_
  #define F_file_type_name_block_s     "block"
  #define F_file_type_name_character_s "character"
  #define F_file_type_name_directory_s "directory"
  #define F_file_type_name_fifo_s      "fifo"
  #define F_file_type_name_file_s      "file"
  #define F_file_type_name_link_s      "link"
  #define F_file_type_name_regular_s   "regular"
  #define F_file_type_name_socket_s    "socket"

  #define F_file_type_name_block_s_length     5
  #define F_file_type_name_character_s_length 9
  #define F_file_type_name_directory_s_length 9
  #define F_file_type_name_fifo_s_length      4
  #define F_file_type_name_file_s_length      4
  #define F_file_type_name_link_s_length      4
  #define F_file_type_name_regular_s_length   7
  #define F_file_type_name_socket_s_length    6

  #ifndef _di_f_file_type_name_block_s_
    extern const f_string_static_t f_file_type_name_block_s;
  #endif // _di_f_file_type_name_block_s_

  #ifndef _di_f_file_type_name_character_s_
    extern const f_string_static_t f_file_type_name_character_s;
  #endif // _di_f_file_type_name_character_s_

  #ifndef _di_f_file_type_name_directory_s_
    extern const f_string_static_t f_file_type_name_directory_s;
  #endif // _di_f_file_type_name_directory_s_

  #ifndef _di_f_file_type_name_fifo_s_
    extern const f_string_static_t f_file_type_name_fifo_s;
  #endif // _di_f_file_type_name_fifo_s_

  #ifndef _di_f_file_type_name_file_s_
    extern const f_string_static_t f_file_type_name_file_s;
  #endif // _di_f_file_type_name_file_s_

  #ifndef _di_f_file_type_name_link_s_
    extern const f_string_static_t f_file_type_name_link_s;
  #endif // _di_f_file_type_name_link_s_

  #ifndef _di_f_file_type_name_regular_s_
    extern const f_string_static_t f_file_type_name_regular_s;
  #endif // _di_f_file_type_name_regular_s_

  #ifndef _di_f_file_type_name_socket_s_
    extern const f_string_static_t f_file_type_name_socket_s;
  #endif // _di_f_file_type_name_socket_s_
#endif // _di_f_file_type_s_

/**
 * Provide macros for file access mode operations.
 *
 * F_file_access_mode_*:
 *   - execute: Check if file can be executed.
 *   - exist:   Check if file exists.
 *   - read:    Check if file can be read.
 *   - write:   Check if file can be written to.
 */
#ifndef _di_f_file_access_mode_d_
  #define F_file_access_mode_execute_d X_OK
  #define F_file_access_mode_exist_d   F_OK
  #define F_file_access_mode_read_d    R_OK
  #define F_file_access_mode_write_d   W_OK
#endif // _di_f_file_access_mode_d_

/**
 * Provide file open mode macros.
 *
 * F_file_open_mode_*:
 *   - read:           Open file in read only mode.
 *   - read_append:    Open file in read append mode.
 *   - read_truncate:  Open file in read truncate mode.
 *   - read_write:     Open file in read write mode.
 *   - write_append:   Open file in write append mode.
 *   - write_truncate: Open file in write truncate mode.
 */
#ifndef _di_f_file_open_mode_s_
  #define F_file_open_mode_read_s           "r"
  #define F_file_open_mode_read_append_s    "a+"
  #define F_file_open_mode_read_truncate_s  "w+"
  #define F_file_open_mode_read_write_s     "r+"
  #define F_file_open_mode_write_append_s   "a"
  #define F_file_open_mode_write_truncate_s "w"

  #define F_file_open_mode_read_s_length           1
  #define F_file_open_mode_read_append_s_length    2
  #define F_file_open_mode_read_truncate_s_length  2
  #define F_file_open_mode_read_write_s_length     2
  #define F_file_open_mode_write_append_s_length   1
  #define F_file_open_mode_write_truncate_s_length 1

  #ifndef _di_f_file_open_mode_read_s_
    extern const f_string_static_t f_file_open_mode_read_s;
  #endif // _di_f_file_open_mode_read_s_

  #ifndef _di_f_file_open_mode_read_append_s_
    extern const f_string_static_t f_file_open_mode_read_append_s;
  #endif // _di_f_file_open_mode_read_append_s_

  #ifndef _di_f_file_open_mode_read_truncate_s_
    extern const f_string_static_t f_file_open_mode_read_truncate_s;
  #endif // _di_f_file_open_mode_read_truncate_s_

  #ifndef _di_f_file_open_mode_read_write_s_
    extern const f_string_static_t f_file_open_mode_read_write_s;
  #endif // _di_f_file_open_mode_read_write_s_

  #ifndef _di_f_file_open_mode_write_append_s_
    extern const f_string_static_t f_file_open_mode_write_append_s;
  #endif // _di_f_file_open_mode_write_append_s_

  #ifndef _di_f_file_open_mode_write_truncate_s_
    extern const f_string_static_t f_file_open_mode_write_truncate_s;
  #endif // _di_f_file_open_mode_write_truncate_s_
#endif // _di_f_file_open_mode_s_

/**
 * File AT_* define related functionality.
 */
#ifndef _di_f_file_at_d_
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
#endif // _di_f_file_at_d_

/**
 * File mode related functionality.
 *
 * There are two types of file modes that the f_file_mode_t macros are associated with.
 *
 * The first type is the traditional mode type, associated with mode_t.
 *
 * The second type is f_file_mode_t, which utilizes 8-bit types with the following structure:
 *
 *   The f_file_mode_t structure is a 32-bit unsigned integer designed to directly represent the special, owner, group, and world mode bits along with their respective read, write, and execute bits (setuid, setgid, and sticky for the special bits).
 *
 *   Each bit is structured in 8-bit blocks as follows:
 *     [ special ][ owner ][ group ][ world ]
 *
 *   Each block, from left to right, has 4 bits representing "subtract" followed by 4 bits representing "add".
 *   As an exceptional case, the first bit (left most bit) for the "special" block is not used and expected to be 0.
 *
 *   Each of these 4-bits, respectively, represents "special", "read", "write", and "execute".
 *
 *   Each bit maps to some character 'r', 'w', 'x', and 'X' bit (as well as 'S', 's', and 't' for each "special"):
 *     'r' = read bit.
 *     'w' = write bit.
 *     'x' = execute bit.
 *     'X' = execute only if already execute bit.
 *     'S' = set user bit (setuid).
 *     's' = set group bit (setgid).
 *     't' = sticky bit.
 *
 *   There exists both an "add" and a "subtract" block so that both operations can be passed.
 *   Such as "+r,-w" meaning add read and subtract write.
 *
 *   For replacements, additional bits and masks are provided which are intended to be used in a separate variable given that only 8-bits are needed for replacements.
 *
 *   The replacements are, also from left to write, are broken up into the following bits of a single byte:
 *     [ unused ] [ unused ] [ unused ] [ directory ] [ special ] [ owner ] [ group ] [ world ]
 *
 *   The directory bit is a special case bit used to declare that these bits are in respect to a directory.
 *   Directory has special representation when it comes to the execute bit, namely when the "execute only" mode is being applied.
 *   The directory bit may be applied even when there are no replacements.
 *   This can be used to designate that the "add" or "subtract" is being applied to a directory.
 *
 *   When, say the "owner" bit is set in this replacement, this means that the owner bit is to be replaced before performing any add/subtract operations.
 *   When using the replacement variable, the "subtract" is considered a no-op and is ignored.
 *   Use only the "add" bits in conjuction with respective "replace" bits.
 *
 * The file mode macros with "f_file_mode_" prefix (has no "_t") refer to the first type (mode_t).
 * The file mode macros with "f_file_mode_t" prefix refer to the second type (f_file_mode_t).
 */
#ifndef _di_f_file_mode_t_
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
#endif // _di_f_file_mode_t_

/**
 * File flag related to file statistics.
 *
 * f_file_stat_flag_*:
 *   - none:      No flags are set (enables non-exclusive and dereference).
 *   - exclusive: Require that a file does not already exist.
 *   - group:     Copy the group.
 *   - owner:     Copy the owner.
 *   - reference: Do not perform dereference.
 */
#ifndef _di_f_file_stat_flags_e_
  enum {
    f_file_stat_flag_none_e      = 0x0,
    f_file_stat_flag_exclusive_e = 0x1,
    f_file_stat_flag_group_e     = 0x2,
    f_file_stat_flag_owner_e     = 0x4,
    f_file_stat_flag_reference_e = 0x8,
  }; // enum
#endif // _di_f_file_stat_flags_e_

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
#ifndef _di_f_file_operation_s_
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

  #ifndef _di_f_file_operation_access_s_
    extern const f_string_static_t f_file_operation_access_s;
  #endif // _di_f_file_operation_access_s_

  #ifndef _di_f_file_operation_analyze_s_
    extern const f_string_static_t f_file_operation_analyze_s;
  #endif // _di_f_file_operation_analyze_s_

  #ifndef _di_f_file_operation_append_s_
    extern const f_string_static_t f_file_operation_append_s;
  #endif // _di_f_file_operation_append_s_

  #ifndef _di_f_file_operation_change_group_s_
    extern const f_string_static_t f_file_operation_change_group_s;
  #endif // _di_f_file_operation_change_group_s_

  #ifndef _di_f_file_operation_change_mode_s_
    extern const f_string_static_t f_file_operation_change_mode_s;
  #endif // _di_f_file_operation_change_mode_s_

  #ifndef _di_f_file_operation_change_owner_s_
    extern const f_string_static_t f_file_operation_change_owner_s;
  #endif // _di_f_file_operation_change_owner_s_

  #ifndef _di_f_file_operation_change_type_s_
    extern const f_string_static_t f_file_operation_change_type_s;
  #endif // _di_f_file_operation_change_type_s_

  #ifndef _di_f_file_operation_clone_s_
    extern const f_string_static_t f_file_operation_clone_s;
  #endif // _di_f_file_operation_clone_s_

  #ifndef _di_f_file_operation_close_s_
    extern const f_string_static_t f_file_operation_close_s;
  #endif // _di_f_file_operation_close_s_

  #ifndef _di_f_file_operation_concatenate_s_
    extern const f_string_static_t f_file_operation_concatenate_s;
  #endif // _di_f_file_operation_concatenate_s_

  #ifndef _di_f_file_operation_connect_s_
    extern const f_string_static_t f_file_operation_connect_s;
  #endif // _di_f_file_operation_connect_s_

  #ifndef _di_f_file_operation_copy_s_
    extern const f_string_static_t f_file_operation_copy_s;
  #endif // _di_f_file_operation_copy_s_

  #ifndef _di_f_file_operation_create_s_
    extern const f_string_static_t f_file_operation_create_s;
  #endif // _di_f_file_operation_create_s_

  #ifndef _di_f_file_operation_decrypt_s_
    extern const f_string_static_t f_file_operation_decrypt_s;
  #endif // _di_f_file_operation_decrypt_s_

  #ifndef _di_f_file_operation_delete_s_
    extern const f_string_static_t f_file_operation_delete_s;
  #endif // _di_f_file_operation_delete_s_

  #ifndef _di_f_file_operation_disconnect_s_
    extern const f_string_static_t f_file_operation_disconnect_s;
  #endif // _di_f_file_operation_disconnect_s_

  #ifndef _di_f_file_operation_encrypt_s_
    extern const f_string_static_t f_file_operation_encrypt_s;
  #endif // _di_f_file_operation_encrypt_s_

  #ifndef _di_f_file_operation_find_s_
    extern const f_string_static_t f_file_operation_find_s;
  #endif // _di_f_file_operation_find_s_

  #ifndef _di_f_file_operation_from_s_
    extern const f_string_static_t f_file_operation_from_s;
  #endif // _di_f_file_operation_from_s_

  #ifndef _di_f_file_operation_flush_s_
    extern const f_string_static_t f_file_operation_flush_s;
  #endif // _di_f_file_operation_flush_s_

  #ifndef _di_f_file_operation_get_group_s_
    extern const f_string_static_t f_file_operation_get_group_s;
  #endif // _di_f_file_operation_get_group_s_

  #ifndef _di_f_file_operation_get_mode_s_
    extern const f_string_static_t f_file_operation_get_mode_s;
  #endif // _di_f_file_operation_get_mode_s_

  #ifndef _di_f_file_operation_get_owner_s_
    extern const f_string_static_t f_file_operation_get_owner_s;
  #endif // _di_f_file_operation_get_owner_s_

  #ifndef _di_f_file_operation_get_type_s_
    extern const f_string_static_t f_file_operation_get_type_s;
  #endif // _di_f_file_operation_get_type_s_

  #ifndef _di_f_file_operation_identify_s_
    extern const f_string_static_t f_file_operation_identify_s;
  #endif // _di_f_file_operation_identify_s_

  #ifndef _di_f_file_operation_link_s_
    extern const f_string_static_t f_file_operation_link_s;
  #endif // _di_f_file_operation_link_s_

  #ifndef _di_f_file_operation_list_s_
    extern const f_string_static_t f_file_operation_list_s;
  #endif // _di_f_file_operation_list_s_

  #ifndef _di_f_file_operation_move_s_
    extern const f_string_static_t f_file_operation_move_s;
  #endif // _di_f_file_operation_move_s_

  #ifndef _di_f_file_operation_open_s_
    extern const f_string_static_t f_file_operation_open_s;
  #endif // _di_f_file_operation_open_s_

  #ifndef _di_f_file_operation_pipe_s_
    extern const f_string_static_t f_file_operation_pipe_s;
  #endif // _di_f_file_operation_pipe_s_

  #ifndef _di_f_file_operation_process_s_
    extern const f_string_static_t f_file_operation_process_s;
  #endif // _di_f_file_operation_process_s_

  #ifndef _di_f_file_operation_read_s_
    extern const f_string_static_t f_file_operation_read_s;
  #endif // _di_f_file_operation_read_s_

  #ifndef _di_f_file_operation_receive_s_
    extern const f_string_static_t f_file_operation_receive_s;
  #endif // _di_f_file_operation_receive_s_

  #ifndef _di_f_file_operation_rename_s_
    extern const f_string_static_t f_file_operation_rename_s;
  #endif // _di_f_file_operation_rename_s_

  #ifndef _di_f_file_operation_send_s_
    extern const f_string_static_t f_file_operation_send_s;
  #endif // _di_f_file_operation_send_s_

  #ifndef _di_f_file_operation_shred_s_
    extern const f_string_static_t f_file_operation_shred_s;
  #endif // _di_f_file_operation_shred_s_

  #ifndef _di_f_file_operation_stat_s_
    extern const f_string_static_t f_file_operation_stat_s;
  #endif // _di_f_file_operation_stat_s_

  #ifndef _di_f_file_operation_to_s_
    extern const f_string_static_t f_file_operation_to_s;
  #endif // _di_f_file_operation_to_s_

  #ifndef _di_f_file_operation_touch_s_
    extern const f_string_static_t f_file_operation_touch_s;
  #endif // _di_f_file_operation_touch_s_

  #ifndef _di_f_file_operation_truncate_s_
    extern const f_string_static_t f_file_operation_truncate_s;
  #endif // _di_f_file_operation_truncate_s_

  #ifndef _di_f_file_operation_unlink_s_
    extern const f_string_static_t f_file_operation_unlink_s;
  #endif // _di_f_file_operation_unlink_s_

  #ifndef _di_f_file_operation_verify_s_
    extern const f_string_static_t f_file_operation_verify_s;
  #endif // _di_f_file_operation_verify_s_

  #ifndef _di_f_file_operation_wipe_s_
    extern const f_string_static_t f_file_operation_wipe_s;
  #endif // _di_f_file_operation_wipe_s_

  #ifndef _di_f_file_operation_write_s_
    extern const f_string_static_t f_file_operation_write_s;
  #endif // _di_f_file_operation_write_s_
#endif // _di_f_file_operation_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_file_common_h
