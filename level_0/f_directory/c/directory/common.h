/**
 * FLL - Level 0
 *
 * Project: Directory
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by project directory.
 *
 * This is auto-included by directory.h and should not need to be explicitly included.
 */
#ifndef _F_directory_common_h
#define _F_directory_common_h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_directory_s_
  #define F_directory_back_s    ".."
  #define F_directory_current_s "."

  #define F_directory_back_s_length    2
  #define F_directory_current_s_length 1

  #ifndef _di_f_directory_back_s_
    extern const f_string_static_t f_directory_back_s;
  #endif // _di_f_directory_back_s_

  #ifndef _di_f_directory_current_s_
    extern const f_string_static_t f_directory_current_s;
  #endif // _di_f_directory_current_s_
#endif // _di_f_directory_s_

/**
 * Directory AT_* define related functionality.
 */
#ifndef _di_f_directory_at_d_
  #define F_directory_at_current_working_d    -100
  #define F_directory_at_symlink_follow_d     0x400
  #define F_directory_at_symlink_follow_no_d  0x100
  #define F_directory_at_remove_directory_d   0x200
  #define F_directory_at_automount_no_d       0x800
  #define F_directory_at_path_empty_d         0x1000
  #define F_directory_at_statx_sync_type_d    0x6000
  #define F_directory_at_statx_sync_as_stat_d 0x0000
  #define F_directory_at_statx_sync_force_d   0x2000
  #define F_directory_at_statx_sync_no_d      0x4000
#endif // _di_f_directory_at_d_

/**
 * Directory flag related functionality.
 */
#ifndef _di_f_directory_flag_d_

  // Directory open flags.
  #define F_directory_flag_append_d             O_APPEND
  #define F_directory_flag_asynchronous_d       O_ASYNC
  #define F_directory_flag_create_d             O_CREAT
  #define F_directory_flag_close_execute_d      O_CLOEXEC
  #define F_directory_flag_direct_d             O_DIRECT
  #define F_directory_flag_directory_d          O_DIRECTORY
  #define F_directory_flag_exclusive_d          O_EXCL
  #define F_directory_flag_large_file_d         O_LARGEFILE
  #define F_directory_flag_no_access_time_d     O_NOATIME
  #define F_directory_flag_no_follow_d          O_NOFOLLOW
  #define F_directory_flag_no_tty_d             O_NOCTTY
  #define F_directory_flag_non_blocking_d       O_NONBLOCK
  #define F_directory_flag_path_d               010000000
  #define F_directory_flag_read_only_d          O_RDONLY
  #define F_directory_flag_read_write_d         O_RDWR
  #define F_directory_flag_synchronous_d        O_SYNC
  #define F_directory_flag_synchronous_direct_d O_DSYNC
  #define F_directory_flag_temporary_d          O_TMPFILE
  #define F_directory_flag_truncate_d           O_TRUNC
  #define F_directory_flag_write_only_d         O_WRONLY
#endif // _di_f_directory_flag_d_

/**
 * Provide limitations and related defines.
 *
 * The F_directory_max_list_d and F_directory_max_string_d parameters are used in recursive calls that general re-use memory space.
 * These designate that there be a maximum size to preserve to keep from preserving exceptionally large memory allocation sizes.
 *
 * F_directory_max_*_d:
 *   - descriptors:   The maximum directory descriptors, and is generally used for nftw().
 *   - list:          The maximum directory list length to preserve between recursive calls.
 *   - name:          The maximum name of a directory.
 *   - recurse_depth: The maximum recursion depth.
 *   - string:        The maximum directory list name length to preserve between recursive calls.
 */
#ifndef _di_f_directory_max_d_
  #define F_directory_max_descriptors_d   255
  #define F_directory_max_recurse_depth_d 65535
  #define F_directory_max_list_d          2048
  #define F_directory_max_string_d        256

  #ifdef NAME_MAX
    #define F_directory_max_name_d NAME_MAX
  #else
    #define F_directory_max_name_d 255
  #endif // NAME_MAX
#endif // _di_f_directory_max_d_

/**
 * Directory recurse flags.
 *
 * f_directory_recurse_flag_*:
 *   - none:        No flags are set.
 *   - clone:       Operate as clone instead of as copy, if applicable.
 *   - dereference: Dereference symbolic links rather than operating on the link itself.
 *   - exclusive:   File flag requiring that a file does not already exist.
 *   - group:       File flag representing copying the group.
 *   - owner:       File flag representing copying the owner.
 *   - top:         Operate on top directory and not just inside the directory.
 */
#ifndef _di_f_directory_recurse_flag_e_
  enum {
    f_directory_recurse_flag_none_e        = 0,
    f_directory_recurse_flag_clone_e       = 0x1,
    f_directory_recurse_flag_dereference_e = 0x2,
    f_directory_recurse_flag_exclusive_e   = 0x4,
    f_directory_recurse_flag_group_e       = 0x8,
    f_directory_recurse_flag_owner_e       = 0x10,
    f_directory_recurse_flag_top_e         = 0x20,
  }; // enum
#endif // _di_f_directory_recurse_flag_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_directory_common_h
