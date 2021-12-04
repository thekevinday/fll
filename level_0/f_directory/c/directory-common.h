/**
 * FLL - Level 0
 *
 * Project: Directory
 * API Version: 0.5
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

/**
 * Directory AT_* define related functionality.
 */
#ifndef _di_f_directory_at_
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
#endif // _di_f_directory_at_

/**
 * Directory flag related functionality.
 */
#ifndef _di_f_directory_flag_

  // directory open flags
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
#endif // _di_f_directory_flag_

/**
 * Provide limitations and related defines.
 *
 * The directory max descriptors is more of a default than a rule.
 * This is generally used for nftw() recursive operations to reduce the number of open file descriptors during recursion.
 */
#ifndef _di_f_directory_limitations_
  #define F_directory_default_allocation_step_d F_memory_default_allocation_small_d

  #define F_directory_descriptors_max_d 255
  #define F_directory_name_max_d        NAME_MAX
#endif // _di_f_directory_limitations_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_directory_common_h
