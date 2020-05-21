#include <level_0/directory.h>
#include "private-directory.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_directory_create_
  f_return_status f_directory_create(const f_string path, const mode_t mode) {
    if (mkdir(path, mode) < 0) {
      if (errno == EACCES) return f_status_set_error(f_access_denied);
      if (errno == EDQUOT) return f_status_set_error(f_filesystem_quota_blocks);
      if (errno == EEXIST) return f_status_set_error(f_file_found);
      if (errno == ENAMETOOLONG) return f_status_set_error(f_invalid_name);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == EINVAL) return f_status_set_error(f_invalid_parameter);
      if (errno == ELOOP) return f_status_set_error(f_loop);
      if (errno == EMLINK) return f_status_set_error(f_directory_error_link_max);
      if (errno == ENOENT) return f_status_set_error(f_file_not_found);
      if (errno == ENOMEM) return f_status_set_error(f_out_of_memory);
      if (errno == ENOSPC) return f_status_set_error(f_no_space);
      if (errno == ENOTDIR) return f_status_set_error(f_invalid_directory);
      if (errno == EPERM) return f_status_set_error(f_prohibited);
      if (errno == EROFS) return f_status_set_error(f_read_only);

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // _di_f_directory_create_

#ifndef _di_f_directory_create_at_
  f_return_status f_directory_create_at(const int at_id, const f_string path, const mode_t mode) {
    #ifndef _di_level_0_parameter_checking_
      if (at_id <= 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    if (mkdirat(at_id, path, mode) < 0) {
      if (errno == EACCES) return f_status_set_error(f_access_denied);
      if (errno == EDQUOT) return f_status_set_error(f_filesystem_quota_blocks);
      if (errno == EEXIST) return f_status_set_error(f_file_found);
      if (errno == ENAMETOOLONG) return f_status_set_error(f_invalid_name);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == EINVAL || errno == EBADF) return f_status_set_error(f_invalid_parameter);
      if (errno == ELOOP) return f_status_set_error(f_loop);
      if (errno == EMLINK) return f_status_set_error(f_directory_error_link_max);
      if (errno == ENOENT) return f_status_set_error(f_file_not_found);
      if (errno == ENOMEM) return f_status_set_error(f_out_of_memory);
      if (errno == ENOSPC) return f_status_set_error(f_no_space);
      if (errno == ENOTDIR) return f_status_set_error(f_invalid_directory);
      if (errno == EPERM) return f_status_set_error(f_prohibited);
      if (errno == EROFS) return f_status_set_error(f_read_only);

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // _di_f_directory_create_at_

#ifndef _di_f_directory_exists_
  f_return_status f_directory_exists(const f_string path) {
    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    if (stat(path, &file_stat) < 0) {
      if (errno == ENAMETOOLONG) return f_status_set_error(f_invalid_name);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == ENOMEM) return f_status_set_error(f_out_of_memory);
      if (errno == EOVERFLOW) return f_status_set_error(f_number_overflow);
      if (errno == ENOTDIR) return f_false;
      if (errno == ENOENT) return f_file_not_found;
      if (errno == EACCES) return f_status_set_error(f_access_denied);
      if (errno == ELOOP) return f_status_set_error(f_loop);

      return f_status_set_error(f_file_error_stat);
    }

    if ((file_stat.st_mode & S_IFMT) == S_IFDIR) return f_true;

    return f_false;
  }
#endif // _di_f_directory_exists_

#ifndef _di_f_directory_is_
  f_return_status f_directory_is(const f_string path) {
    struct stat file_stat;

    memset(&file_stat, AT_SYMLINK_NOFOLLOW, sizeof(struct stat));

    if (stat(path, &file_stat) < 0) {
      if (errno == ENAMETOOLONG) return f_status_set_error(f_invalid_name);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == ENOMEM) return f_status_set_error(f_out_of_memory);
      if (errno == EOVERFLOW) return f_status_set_error(f_number_overflow);
      if (errno == ENOTDIR) return f_false;
      if (errno == ENOENT) return f_file_not_found;
      if (errno == EACCES) return f_status_set_error(f_access_denied);
      if (errno == ELOOP) return f_status_set_error(f_loop);

      return f_status_set_error(f_file_error_stat);
    }

    if ((file_stat.st_mode & S_IFMT) == S_IFDIR) return f_true;

    return f_false;
  }
#endif // _di_f_directory_is_

#ifndef _di_f_directory_is_at_
  f_return_status f_directory_is_at(const int file_id, const f_string path, const bool follow) {
    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    if (fstatat(file_id, path, &file_stat, follow ? 0 : AT_SYMLINK_NOFOLLOW) < 0) {
      if (errno == ENAMETOOLONG) return f_status_set_error(f_invalid_name);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == ENOMEM) return f_status_set_error(f_out_of_memory);
      if (errno == EOVERFLOW) return f_status_set_error(f_number_overflow);
      if (errno == ENOTDIR) return f_false;
      if (errno == ENOENT) return f_file_not_found;
      if (errno == EACCES) return f_status_set_error(f_access_denied);
      if (errno == ELOOP) return f_status_set_error(f_loop);

      return f_status_set_error(f_file_error_stat);
    }

    if ((file_stat.st_mode & S_IFMT) == S_IFDIR) return f_true;

    return f_false;
  }
#endif // _di_f_directory_is_at_

#ifndef _di_f_directory_list_
  f_return_status f_directory_list(const f_string path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), f_string_dynamics *names) {
    #ifndef _di_level_0_parameter_checking_
      if (names == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    struct dirent **listing = 0;
    size_t i = 0;
    f_string_length size = 0;
    f_status status = f_none;

    const size_t length = scandir(path, &listing, filter, sort);

    if (length == -1) {
      if (errno == ENOMEM) return f_status_set_error(f_error_allocation);
      else return f_status_set_error(f_failure);
    }

    for (; i < length; i++) {
      size = strnlen(listing[i]->d_name, f_directory_name_max);

      // There is no reason to include "." and ".." in the directory listing.
      if (strncmp(listing[i]->d_name, "..", 3) == 0 || strncmp(listing[i]->d_name, ".", 2) == 0)  {
        f_memory_delete((void **) & listing[i], sizeof(char *), 1);
        continue;
      }

      if (names->used >= names->size) {
        f_macro_string_dynamics_resize(status, (*names), names->size + f_directory_default_allocation_step);
        if (f_status_is_error(status)) break;
      }

      f_macro_string_dynamic_new(status, names->array[names->used], size);
      if (f_status_is_error(status)) break;

      memcpy(names->array[names->used].string, listing[i]->d_name, size);
      names->array[names->used].used = size;
      names->used++;

      f_memory_delete((void **) & listing[i], sizeof(char *), 1);
    } // for

    for (; i < length; i++) {
      f_memory_delete((void **) & listing[i], sizeof(char *), 1);
    } // for

    f_memory_delete((void **) & listing, sizeof(struct dirent *), 1);

    if (f_status_is_error(status)) return status;
    if (length == 0) return f_no_data;

    return f_none;
  }
#endif // _di_f_directory_list_

#ifndef _di_f_directory_remove_
  f_return_status f_directory_remove(const f_string path, const int recursion_max, const bool preserve) {
    #ifndef _di_level_0_parameter_checking_
      if (recursion_max < 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    int result = 0;

    if (recursion_max) {
      result = nftw(path, private_f_directory_remove_recursively, recursion_max, FTW_DEPTH | FTW_PHYS);

      if (result == 0 && !preserve) {
        result = remove(path);
      }
    }
    else {
      // Not recursively deleting and the path is requested to be preserved, so there is nothing to delete.
      if (preserve) return f_none;

      result = remove(path);
    }

    if (result < 0) {
      if (errno == EACCES) return f_status_set_error(f_access_denied);
      if (errno == EBUSY) return f_status_set_error(f_busy);
      if (errno == EIO) return f_status_set_error(f_error_input_output);
      if (errno == EISDIR) return f_status_set_error(f_file_is_type_directory);
      if (errno == ELOOP) return f_status_set_error(f_loop);
      if (errno == ENAMETOOLONG) return f_status_set_error(f_invalid_name);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == ENOENT) return f_status_set_error(f_file_not_found);
      if (errno == ENOMEM) return f_status_set_error(f_out_of_memory);
      if (errno == ENOTDIR) return f_status_set_error(f_invalid_directory);
      if (errno == EPERM) return f_status_set_error(f_prohibited);
      if (errno == EROFS) return f_status_set_error(f_read_only);
      if (errno == EOVERFLOW) return f_status_set_error(f_number_overflow);
      if (errno == EMFILE) return f_status_set_error(f_file_max_descriptors);
      if (errno == ENFILE) return f_status_set_error(f_file_max_open);
      if (errno == EINVAL) return f_status_set_error(f_invalid_parameter);

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // _di_f_directory_remove_

#ifndef _di_f_directory_remove_custom_
  f_return_status f_directory_remove_custom(const f_string path, const int recursion_max, const bool preserve, int (*custom) (const char *, const struct stat *, int, struct FTW *)) {
    #ifndef _di_level_0_parameter_checking_
      if (recursion_max < 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    int result = 0;

    if (recursion_max) {
      result = nftw(path, custom, recursion_max, FTW_DEPTH | FTW_PHYS);

      if (result == 0 && !preserve) {
        result = remove(path);
      }
    }
    else {
      // Not recursively deleting and the path is requested to be preserved, so there is nothing to delete.
      if (preserve) return f_none;

      result = remove(path);
    }

    if (result < 0) {
      if (errno == EACCES) return f_status_set_error(f_access_denied);
      if (errno == EBUSY) return f_status_set_error(f_busy);
      if (errno == EIO) return f_status_set_error(f_error_input_output);
      if (errno == EISDIR) return f_status_set_error(f_file_is_type_directory);
      if (errno == ELOOP) return f_status_set_error(f_loop);
      if (errno == ENAMETOOLONG) return f_status_set_error(f_invalid_name);
      if (errno == EFAULT) return f_status_set_error(f_invalid_buffer);
      if (errno == ENOENT) return f_status_set_error(f_file_not_found);
      if (errno == ENOMEM) return f_status_set_error(f_out_of_memory);
      if (errno == ENOTDIR) return f_status_set_error(f_invalid_directory);
      if (errno == EPERM) return f_status_set_error(f_prohibited);
      if (errno == EROFS) return f_status_set_error(f_read_only);
      if (errno == EOVERFLOW) return f_status_set_error(f_number_overflow);
      if (errno == EMFILE) return f_status_set_error(f_file_max_descriptors);
      if (errno == ENFILE) return f_status_set_error(f_file_max_open);
      if (errno == EINVAL) return f_status_set_error(f_invalid_parameter);

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // _di_f_directory_remove_custom_

#ifdef __cplusplus
} // extern "C"
#endif
