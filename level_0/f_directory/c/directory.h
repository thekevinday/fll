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
 * The directory max recursion is more of a default than a rule.
 */
#ifndef _di_f_directory_limitations_
  #define f_directory_default_allocation_step f_memory_default_allocation_step

  #define f_directory_name_max      255
  #define f_directory_max_recursion 2048
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
    if (!f_status_is_error(status)) f_macro_string_dynamics_delete(status, listing.character) \
    if (!f_status_is_error(status)) f_macro_string_dynamics_delete(status, listing.directory) \
    if (!f_status_is_error(status)) f_macro_string_dynamics_delete(status, listing.file) \
    if (!f_status_is_error(status)) f_macro_string_dynamics_delete(status, listing.link) \
    if (!f_status_is_error(status)) f_macro_string_dynamics_delete(status, listing.pipe) \
    if (!f_status_is_error(status)) f_macro_string_dynamics_delete(status, listing.socket) \
    if (!f_status_is_error(status)) f_macro_string_dynamics_delete(status, listing.unknown)

  #define f_macro_directory_listing_destroy(status, listing) \
    f_macro_string_dynamics_destroy(status, listing.block) \
    if (!f_status_is_error(status)) f_macro_string_dynamics_destroy(status, listing.character) \
    if (!f_status_is_error(status)) f_macro_string_dynamics_destroy(status, listing.directory) \
    if (!f_status_is_error(status)) f_macro_string_dynamics_destroy(status, listing.file) \
    if (!f_status_is_error(status)) f_macro_string_dynamics_destroy(status, listing.link) \
    if (!f_status_is_error(status)) f_macro_string_dynamics_destroy(status, listing.pipe) \
    if (!f_status_is_error(status)) f_macro_string_dynamics_destroy(status, listing.socket) \
    if (!f_status_is_error(status)) f_macro_string_dynamics_delete(status, listing.unknown)

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
 * A structure representing a directory.
 */
#ifndef _di_f_directory_
  typedef struct {
    struct dirent entity;
    int descriptor;
    f_directory_listing content;
  } f_directory;

  #define f_directory_initialize { \
      { 0, 0, 0, 0, 0 }, \
      0, \
      f_directory_listing_initialize, \
    }
#endif // _di_f_directory_

/**
 * Create a directory at the given path.
 *
 * @param path
 *   The path file name.
 * @param modes
 *   The directory modes to use when creating.
 *
 * @return
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_access_denied (with error bit) on access denied.
 *   f_loop (with error bit) on loop error.
 *   f_file_not_found (with error bit) if a file within the path is not found (such as a broken symbolic link).
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_prohibited (with error bit) if filesystem does not allow for removing.
 *   f_read_only (with error bit) if file is read-only.
 *   f_failure (with error bit) for any other (mkdir()) error.
 *   f_filesystem_quota_blocks (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   f_filesystem_quota_reached (with error bit) quota reached of filesystem is out of space.
 *   f_file_found (with error bit) of a directory aleady exists at the path.
 *   f_invalid_name (with error bit) on path name error.
 *   f_directory_error_link_max (with error bit) max links limit reached or exceeded.
 *   f_invalid_directory (with error bit) if a supposed directory in path is not actually a directory.
 *
 * @see mkdir()
 */
#ifndef _di_f_directory_create_
  extern f_return_status f_directory_create(const f_string path, const mode_t modes);
#endif // _di_f_directory_create_

/**
 * Create a directory at the given path within the directories specified by the file descriptor.
 *
 * @param at_id
 *   The file descriptor in which the directory will be created within.
 * @param path
 *   The path file name.
 * @param modes
 *   The directory modes to use when creating.
 *
 * @return
 *   f_none on success.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_access_denied (with error bit) on access denied.
 *   f_loop (with error bit) on loop error.
 *   f_file_not_found (with error bit) if a file within the path is not found (such as a broken symbolic link).
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_prohibited (with error bit) if filesystem does not allow for removing.
 *   f_read_only (with error bit) if file is read-only.
 *   f_failure (with error bit) for any other (mkdir()) error.
 *   f_filesystem_quota_blocks (with error bit) if filesystem's disk blocks or inodes are exhausted.
 *   f_filesystem_quota_reached (with error bit) quota reached of filesystem is out of space.
 *   f_file_found (with error bit) of a directory aleady exists at the path.
 *   f_invalid_name (with error bit) on path name error.
 *   f_directory_error_link_max (with error bit) max links limit reached or exceeded.
 *   f_invalid_directory (with error bit) if a supposed directory in path is not actually a directory.
 *
 * @see mkdir()
 *
#ifndef _di_f_directory_create_at_
  extern f_return_status f_directory_create_at(const int at_id, const f_string path, const mode_t modes);
#endif // _di_f_directory_create_at_

/**
 * Identify whether or not a file exists at the given path and if that file is a directory.
 *
 * @param path
 *   The path file name.
 *
 * @return
 *   t_true if path was found and path is a directory.
 *   f_false if path was found and path is not a directory.
 *   f_file_not_found if the path was not found.
 *   f_invalid_name (with error bit) if the name is somehow invalid.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_number_overflow (with error bit) on overflow error.
 *   f_access_denied (with error bit) if access to the file was denied.
 *   f_loop (with error bit) if a loop occurred.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
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
 *   f_false if path was found and path is not a directory.
 *   f_file_not_found if the path was not found.
 *   f_invalid_name (with error bit) if the name is somehow invalid.
 *   f_out_of_memory (with error bit) if out of memory.
 *   f_number_overflow (with error bit) on overflow error.
 *   f_access_denied (with error bit) if access to the file was denied.
 *   f_loop (with error bit) if a loop occurred.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
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
 *   f_none on success.
 *   f_no_data if directory is empty (@fixme: unlikely due to '.' and '..' probably always being returned.).
 *   f_failure (with error bit) if failed to read directory information.
 *   f_invalid_parameter (with error bit) if a parameter is invalid.
 *   f_error_reallocation (with error bit) on memory reallocation error.
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
 *   f_number_overflow (with error bit) on integer overflow.
 *   f_file_max_descriptors (with error bit) if max file descriptors was reached.
 *   f_file_max_open (with error bit) too many open files.
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
