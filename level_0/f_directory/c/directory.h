/**
 * FLL - Level 0
 *
 * Project: Directory
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides operations for directory handling.
 */
#ifndef _F_directory_h
#define _F_directory_h

// libc includes
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// work-around for out-dated systems.
#ifndef __USE_XOPEN_EXTENDED
  #define __USE_XOPEN_EXTENDED
  #include <ftw.h>
  #undef __USE_XOPEN_EXTENDED
#else
  #include <ftw.h>
#endif // __USE_XOPEN_EXTENDED

// fll-0 includes
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/type.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Provide limitations and related defines.
 *
 * The name max 255 because the directory name size is 256.
 * The last 1 is for the NULL character.
 *
 * The directory max descriptors is more of a default than a rule.
 * This is generally used for nftw() recursive operations to reduce the number of open file descriptors during recursion.
 */
#ifndef _di_f_directory_limitations_
  #define f_directory_default_allocation_step f_memory_default_allocation_step

  #define f_directory_name_max        255
  #define f_directory_descriptors_max 255
#endif // _di_f_directory_limitations_

/**
 * A structure representing a listing of paths found within a directory.
 *
 * Each property represents a set of paths grouped by directory entity file type.
 */
#ifndef _di_f_directory_listing_
  typedef struct {
    f_string_dynamics block;     // S_IFBLK
    f_string_dynamics character; // S_IFCHR
    f_string_dynamics directory; // S_IFDIR
    f_string_dynamics file;      // S_IFREG
    f_string_dynamics link;      // S_IFLNK
    f_string_dynamics pipe;      // S_IFIFO
    f_string_dynamics socket;    // S_IFSOCK
    f_string_dynamics unknown;
  } f_directory_listing;

  #define f_directory_listing_initialize { \
    f_string_dynamics_initialize, \
    f_string_dynamics_initialize, \
    f_string_dynamics_initialize, \
    f_string_dynamics_initialize, \
    f_string_dynamics_initialize, \
    f_string_dynamics_initialize, \
    f_string_dynamics_initialize, \
    f_string_dynamics_initialize, \
  }

  #define f_macro_directory_listing_delete(status, listing) \
    f_macro_string_dynamics_delete(status, listing.block) \
    if (!F_status_is_error(status)) f_macro_string_dynamics_delete(status, listing.character) \
    if (!F_status_is_error(status)) f_macro_string_dynamics_delete(status, listing.directory) \
    if (!F_status_is_error(status)) f_macro_string_dynamics_delete(status, listing.file) \
    if (!F_status_is_error(status)) f_macro_string_dynamics_delete(status, listing.link) \
    if (!F_status_is_error(status)) f_macro_string_dynamics_delete(status, listing.pipe) \
    if (!F_status_is_error(status)) f_macro_string_dynamics_delete(status, listing.socket) \
    if (!F_status_is_error(status)) f_macro_string_dynamics_delete(status, listing.unknown)

  #define f_macro_directory_listing_destroy(status, listing) \
    f_macro_string_dynamics_destroy(status, listing.block) \
    if (!F_status_is_error(status)) f_macro_string_dynamics_destroy(status, listing.character) \
    if (!F_status_is_error(status)) f_macro_string_dynamics_destroy(status, listing.directory) \
    if (!F_status_is_error(status)) f_macro_string_dynamics_destroy(status, listing.file) \
    if (!F_status_is_error(status)) f_macro_string_dynamics_destroy(status, listing.link) \
    if (!F_status_is_error(status)) f_macro_string_dynamics_destroy(status, listing.pipe) \
    if (!F_status_is_error(status)) f_macro_string_dynamics_destroy(status, listing.socket) \
    if (!F_status_is_error(status)) f_macro_string_dynamics_delete(status, listing.unknown)

  #define f_macro_directory_listing_delete_simple(listing) \
    f_macro_string_dynamics_delete_simple(listing.block) \
    f_macro_string_dynamics_delete_simple(listing.character) \
    f_macro_string_dynamics_delete_simple(listing.directory) \
    f_macro_string_dynamics_delete_simple(listing.file) \
    f_macro_string_dynamics_delete_simple(listing.link) \
    f_macro_string_dynamics_delete_simple(listing.pipe) \
    f_macro_string_dynamics_delete_simple(listing.socket) \
    f_macro_string_dynamics_delete_simple(listing.unknown)

  #define f_macro_directory_listing_destroy_simple(listing) \
    f_macro_string_dynamics_destroy_simple(listing.block) \
    f_macro_string_dynamics_destroy_simple(listing.character) \
    f_macro_string_dynamics_destroy_simple(listing.directory) \
    f_macro_string_dynamics_destroy_simple(listing.file) \
    f_macro_string_dynamics_destroy_simple(listing.link) \
    f_macro_string_dynamics_destroy_simple(listing.pipe) \
    f_macro_string_dynamics_destroy_simple(listing.socket) \
    f_macro_string_dynamics_destroy_simple(listing.unknown)
#endif // _di_f_directory_listing_

/**
 * A structure representing a set of modes intended to be used by directory operations.
 *
 * A small set of macros are provider to help simplify assigning modes.
 *
 * The pipe (S_IFIFO) is intentionally not supported.
 */
#ifndef _di_f_directory_mode_
  typedef struct {
    mode_t block;     // S_IFBLK
    mode_t character; // S_IFCHR
    mode_t directory; // S_IFDIR
    mode_t file;      // S_IFREG
    mode_t link;      // S_IFLNK
    mode_t socket;    // S_IFSOCK
    mode_t unknown;
  } f_directory_mode;

  #define f_directory_mode_initialize { \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
  }

  #define f_macro_directory_mode_set_all(modes, mode) \
    modes.block = mode; \
    modes.character = mode; \
    modes.directory = mode; \
    modes.file = mode; \
    modes.link = mode; \
    modes.socket = mode; \
    modes.unknown = mode;

  #define f_macro_directory_mode_set_common(modes, mode_directory, mode_file, mode_link) \
    modes.directory = mode_directory; \
    modes.file = mode_file; \
    modes.link = mode_link;

  #define f_macro_directory_mode_set_uncommon(modes, mode_block, mode_character, mode_socket, mode_unknown) \
    modes.block = mode_block; \
    modes.character = mode_character; \
    modes.socket = mode_socket; \
    modes.unknown = mode_unknown;
#endif // _di_f_directory_mode_

/**
 * A structure representing a directory.
 *
 * @todo review this and decide to keep and use it or just remove it.
 */
#ifndef _di_f_directory_
  typedef struct {
    struct dirent entity;
    f_directory_listing content;
  } f_directory;

  #define f_directory_initialize { \
      { 0, 0, 0, 0, 0 }, \
      f_directory_listing_initialize, \
    }
#endif // _di_f_directory_

/**
 * Create a directory at the given path.
 *
 * @param path
 *   The path file name.
 * @param mode
 *   The directory mode to use when creating.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_access_denied (with error bit) on access denied.
 *   F_loop (with error bit) on loop error.
 *   F_file_found_not (with error bit) if a file within the path is not found (such as a broken symbolic link).
 *   F_memory_out (with error bit) if out of memory.
 *   F_prohibited (with error bit) if filesystem does not allow for removing.
 *   F_read_only (with error bit) if file is read-only.
 *   F_failure (with error bit) for any other (mkdir()) error.
 *   F_filesystem_quota_block (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   F_space_not (with error bit) if filesystem is out of space (or filesystem quota is reached).
 *   F_file_found (with error bit) of a directory aleady exists at the path.
 *   F_name (with error bit) on path name error.
 *   F_directory_link_max (with error bit) max links limit reached or exceeded.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *
 * @see mkdir()
 */
#ifndef _di_f_directory_create_
  extern f_return_status f_directory_create(const f_string path, const mode_t mode);
#endif // _di_f_directory_create_

/**
 * Create a directory at the given path within the directories specified by the file descriptor.
 *
 * @param at_id
 *   The file descriptor in which the directory will be created within.
 * @param path
 *   The path file name.
 * @param mode
 *   The directory mode to use when creating.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_access_denied (with error bit) on access denied.
 *   F_loop (with error bit) on loop error.
 *   F_file_found_not (with error bit) if a file within the path is not found (such as a broken symbolic link).
 *   F_memory_out (with error bit) if out of memory.
 *   F_prohibited (with error bit) if filesystem does not allow for removing.
 *   F_read_only (with error bit) if file is read-only.
 *   F_failure (with error bit) for any other (mkdir()) error.
 *   F_filesystem_quota_block (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   F_space_not (with error bit) if filesystem is out of space (or filesystem quota is reached).
 *   F_file_found (with error bit) of a directory aleady exists at the path.
 *   F_name (with error bit) on path name error.
 *   F_directory_link_max (with error bit) max links limit reached or exceeded.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *
 * @see mkdir()
 */
#ifndef _di_f_directory_create_at_
  extern f_return_status f_directory_create_at(const int at_id, const f_string path, const mode_t mode);
#endif // _di_f_directory_create_at_

/**
 * Identify whether or not a file exists at the given path and if that file is a directory or a symlink to a directory.
 *
 * @param path
 *   The path file name.
 *
 * @return
 *   t_true if path was found and path is a directory (or a symlink to a directory).
 *   F_false if path was found and path is not a directory.
 *   F_file_found_not if the path was not found.
 *   F_name (with error bit) if the name is somehow invalid.
 *   F_memory_out (with error bit) if out of memory.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_access_denied (with error bit) if access to the file was denied.
 *   F_loop (with error bit) if a loop occurred.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fstat()
 */
#ifndef _di_f_directory_exists_
  extern f_return_status f_directory_exists(const f_string path);
#endif // _di_f_directory_exists_

/**
 * Identify whether or not a file exists at the given path and if that file is a directory.
 *
 * @param path
 *   The path file name.
 *
 * @return
 *   t_true if path was found and path is a directory.
 *   F_false if path was found and path is not a directory (this includes symlinks).
 *   F_file_found_not if the path was not found.
 *   F_name (with error bit) if the name is somehow invalid.
 *   F_memory_out (with error bit) if out of memory.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_access_denied (with error bit) if access to the file was denied.
 *   F_loop (with error bit) if a loop occurred.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fstat()
 */
#ifndef _di_f_directory_is_
  extern f_return_status f_directory_is(const f_string path);
#endif // _di_f_directory_is_

/**
 * Identify whether or not a file exists at the given path within the parent directory and if that file is a directory.
 *
 * @param file_id
 *   The file descriptor representing the parent directory to search within.
 * @param path
 *   The path file name.
 * @param follow
 *   Set to TRUE to follow symbolic links when determining if path is a file.
 *   Set to FALSE to not follow.
 *
 * @return
 *   t_true if path was found and path is a directory.
 *   F_false if path was found and path is not a directory.
 *   F_file_found_not if the path was not found.
 *   F_name (with error bit) if the name is somehow invalid.
 *   F_memory_out (with error bit) if out of memory.
 *   F_number_overflow (with error bit) on overflow error.
 *   F_access_denied (with error bit) if access to the file was denied.
 *   F_loop (with error bit) if a loop occurred.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 * @see fstatat()
 */
#ifndef _di_f_directory_is_at_
  extern f_return_status f_directory_is_at(const int file_id, const f_string path, const bool follow);
#endif // _di_f_directory_is_at_

/**
 * For some given path, print the names of each file and/or directory inside the directory.
 *
 * Allows specifying a custom filter and custom sort.
 *
 * @param path
 *   Filesystem path to the directory.
 * @param filter
 *   A filter function of the form: int xxx(const struct direct *).
 *   Set to 0 to not use (NULL).
 * @param sort
 *   A sort function of the form: int xxx(const struct direct *, const struct direct *).
 *   Set to 0 to not use (NULL).
 *   There are two pre-made libc functions available for this: alphasort() and versionsort().
 * @param names
 *   Will be populated with the names of each file and/or directory inside path.
 *
 * @return
 *   F_none on success.
 *   F_data_not if directory is empty (@fixme: unlikely due to '.' and '..' probably always being returned.).
 *   F_failure (with error bit) if failed to read directory information.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_memory_reallocation (with error bit) on memory reallocation error.
 *
 * @see alphasort()
 * @see scandir()
 * @see versionsort()
 */
#ifndef _di_f_directory_list_
  extern f_return_status f_directory_list(const f_string path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), f_string_dynamics *names);
#endif // _di_f_directory_list_

/**
 * Remove a directory and possibly its contents.
 *
 * @param path
 *   The path file name.
 * @param recursion_max
 *   Represents the max recursion depth, set to 0 to disable recursive delete.
 * @param preserve
 *   When recursion_max > 0, this designates whether or not to preserve the directory at path.
 *   If TRUE, then only the content within the directory is deleted.
 *   If FALSE, then the directory at path and its content are deleted.
 *   When recursion_max is 0, then this should only be FALSE (setting this to TRUE would be a no-op).
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_access_denied (with error bit) on access denied.
 *   F_busy (with error bit) if file is busy.
 *   F_input_output (with error bit) if an I/O error occurred.
 *   F_file_type_directory (with error bit) file is a directory (directories cannot be removed via this function).
 *   F_loop (with error bit) on loop error.
 *   F_name (with error bit) on path name error.
 *   F_file_found_not (with error bit) if file not found.
 *   F_memory_out (with error bit) if out of memory.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_prohibited (with error bit) if filesystem does not allow for removing.
 *   F_read_only (with error bit) if file is read-only.
 *   F_failure (with error bit) for any other (unlink()) error.
 *   F_number_overflow (with error bit) on integer overflow.
 *   F_file_descriptor_max (with error bit) if max file descriptors was reached.
 *   F_file_open_max (with error bit) too many open files.
 *
 * @see nftw()
 * @see remove()
 */
#ifndef _di_f_directory_remove_
  extern f_return_status f_directory_remove(const f_string path, const int recursion_max, const bool preserve);
#endif // _di_f_directory_remove_

/**
 * Remove a directory and possibly its contents.
 *
 * @param path
 *   The path file name.
 * @param recursion_max
 *   Represents the max recursion depth, set to 0 to disable recursive delete.
 * @param preserve
 *   When recursion_max > 0, this designates whether or not to preserve the directory at path.
 *   If TRUE, then only the content within the directory is deleted.
 *   If FALSE, then the directory at path and its content are deleted.
 *   When recursion_max is 0, then this should only be FALSE (setting this to TRUE would be a no-op).
 * @param custom
 *   A custom function to pass to nftw() instead of using the internal one.
 *   Such as a custom function for verbose printing of removed files.
 *
 * @return
 *   F_none on success.
 *   F_parameter (with error bit) if a parameter is invalid.
 *   F_access_denied (with error bit) on access denied.
 *   F_busy (with error bit) if file is busy.
 *   F_input_output (with error bit) if an I/O error occurred.
 *   F_file_type_directory (with error bit) file is a directory (directories cannot be removed via this function).
 *   F_loop (with error bit) on loop error.
 *   F_name (with error bit) on path name error.
 *   F_file_found_not (with error bit) if file not found.
 *   F_memory_out (with error bit) if out of memory.
 *   F_directory (with error bit) if a supposed directory in path is not actually a directory.
 *   F_prohibited (with error bit) if filesystem does not allow for removing.
 *   F_read_only (with error bit) if file is read-only.
 *   F_failure (with error bit) for any other (unlink()) error.
 *
 * @see nftw()
 * @see remove()
 */
#ifndef _di_f_directory_remove_custom_
  extern f_return_status f_directory_remove_custom(const f_string path, const int recursion_max, const bool preserve, int (*custom) (const char *, const struct stat *, int, struct FTW *));
#endif // _di_f_directory_remove_custom_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_directory_h
