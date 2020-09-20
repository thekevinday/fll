/**
 * FLL - Level 0
 *
 * Project: Directory
 * API Version: 0.5
 * Licenses: lgplv2.1
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
  #define f_directory_at_current_working    -100
  #define f_directory_at_symlink_follow     0x400
  #define f_directory_at_symlink_follow_no  0x100
  #define f_directory_at_remove_directory   0x200
  #define f_directory_at_automount_no       0x800
  #define f_directory_at_path_empty         0x1000
  #define f_directory_at_statx_sync_type    0x6000
  #define f_directory_at_statx_sync_as_stat 0x0000
  #define f_directory_at_statx_sync_force   0x2000
  #define f_directory_at_statx_sync_no      0x4000
#endif // _di_f_directory_at_

/**
 * Directory flag related functionality.
 */
#ifndef _di_f_directory_flag_

  // directory open flags
  #define f_directory_flag_append             O_APPEND
  #define f_directory_flag_asynchronous       O_ASYNC
  #define f_directory_flag_create             O_CREAT
  #define f_directory_flag_close_execute      O_CLOEXEC
  #define f_directory_flag_direct             O_DIRECT
  #define f_directory_flag_directory          O_DIRECTORY
  #define f_directory_flag_exclusive          O_EXCL
  #define f_directory_flag_large_file         O_LARGEFILE
  #define f_directory_flag_no_access_time     O_NOATIME
  #define f_directory_flag_no_follow          O_NOFOLLOW
  #define f_directory_flag_no_tty             O_NOCTTY
  #define f_directory_flag_non_blocking       O_NONBLOCK
  #define f_directory_flag_path               010000000
  #define f_directory_flag_read_only          O_RDONLY
  #define f_directory_flag_read_write         O_RDWR
  #define f_directory_flag_synchronous        O_SYNC
  #define f_directory_flag_synchronous_direct O_DSYNC
  #define f_directory_flag_temporary          O_TMPFILE
  #define f_directory_flag_truncate           O_TRUNC
  #define f_directory_flag_write_only         O_WRONLY
#endif // _di_f_directory_flag_

/**
 * Provide limitations and related defines.
 *
 * The directory max descriptors is more of a default than a rule.
 * This is generally used for nftw() recursive operations to reduce the number of open file descriptors during recursion.
 */
#ifndef _di_f_directory_limitations_
  #define f_directory_default_allocation_step f_memory_default_allocation_step

  #define f_directory_descriptors_max 255
  #define f_directory_name_max        NAME_MAX
#endif // _di_f_directory_limitations_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_directory_common_h
