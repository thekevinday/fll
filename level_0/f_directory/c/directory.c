#include <level_0/directory.h>
#include "private-directory.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_directory_create_
  f_return_status f_directory_create(const f_string path, const mode_t mode) {
    return private_f_directory_create(path, mode);
  }
#endif // _di_f_directory_create_

#ifndef _di_f_directory_create_at_
  f_return_status f_directory_create_at(const int at_id, const f_string path, const mode_t mode) {
    #ifndef _di_level_0_parameter_checking_
      if (at_id <= 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_directory_create_at(at_id, path, mode);
  }
#endif // _di_f_directory_create_at_

#ifndef _di_f_directory_exists_
  f_return_status f_directory_exists(const f_string path) {
    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    if (stat(path, &file_stat) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_file_found_not;
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOTDIR) return F_false;
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);

      return F_status_set_error(F_file_stat);
    }

    if ((file_stat.st_mode & S_IFMT) == S_IFDIR) return F_true;

    return F_false;
  }
#endif // _di_f_directory_exists_

#ifndef _di_f_directory_exists_at_
  f_return_status f_directory_exists_at(const int at_id, const f_string path, const int flag) {
    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    if (fstatat(at_id, path, &file_stat, flag) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_file_found_not;
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOTDIR) return F_false;
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);

      return F_status_set_error(F_file_stat);
    }

    if ((file_stat.st_mode & S_IFMT) == S_IFDIR) return F_true;

    return F_false;
  }
#endif // _di_f_directory_exists_at_

#ifndef _di_f_directory_is_
  f_return_status f_directory_is(const f_string path) {
    struct stat file_stat;

    memset(&file_stat, AT_SYMLINK_NOFOLLOW, sizeof(struct stat));

    if (stat(path, &file_stat) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_file_found_not;
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOTDIR) return F_false;
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == ELOOP) return F_status_set_error(F_loop);

      return F_status_set_error(F_file_stat);
    }

    if ((file_stat.st_mode & S_IFMT) == S_IFDIR) return F_true;

    return F_false;
  }
#endif // _di_f_directory_is_

#ifndef _di_f_directory_is_at_
  f_return_status f_directory_is_at(const int at_id, const f_string path, const int flag) {
    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    if (fstatat(at_id, path, &file_stat, flag) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_file_found_not;
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOTDIR) return F_false;
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == ELOOP) return F_status_set_error(F_loop);

      return F_status_set_error(F_file_stat);
    }

    if ((file_stat.st_mode & S_IFMT) == S_IFDIR) return F_true;

    return F_false;
  }
#endif // _di_f_directory_is_at_

#ifndef _di_f_directory_list_
  f_return_status f_directory_list(const f_string path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), f_string_dynamics *names) {
    #ifndef _di_level_0_parameter_checking_
      if (names == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    struct dirent **listing = 0;
    size_t i = 0;
    f_string_length size = 0;
    f_status status = F_none;

    const size_t length = scandir(path, &listing, filter, sort);

    if (length == -1) {
      if (errno == ENOMEM) return F_status_set_error(F_memory_allocation);
      else return F_status_set_error(F_failure);
    }

    for (; i < length; i++) {
      size = strnlen(listing[i]->d_name, f_directory_name_max);

      // There is no reason to include "." and ".." in the directory listing.
      if (strncmp(listing[i]->d_name, "..", 3) == 0 || strncmp(listing[i]->d_name, ".", 2) == 0)  {
        f_memory_delete((void **) & listing[i], sizeof(char *), 1);
        continue;
      }

      if (names->used == names->size) {
        f_macro_memory_structure_macro_increment(status, (*names), 1, f_directory_default_allocation_step, f_macro_string_dynamics_resize, F_buffer_too_large);
        if (F_status_is_error(status)) break;
      }

      f_macro_string_dynamic_new(status, names->array[names->used], size);
      if (F_status_is_error(status)) break;

      memcpy(names->array[names->used].string, listing[i]->d_name, size);
      names->array[names->used].used = size;
      names->used++;

      f_memory_delete((void **) & listing[i], sizeof(char *), 1);
    } // for

    for (; i < length; i++) {
      f_memory_delete((void **) & listing[i], sizeof(char *), 1);
    } // for

    f_memory_delete((void **) & listing, sizeof(struct dirent *), 1);

    if (F_status_is_error(status)) return status;
    if (length == 0) return F_data_not;

    return F_none;
  }
#endif // _di_f_directory_list_

#ifndef _di_f_directory_open_
  f_return_status f_directory_open(const f_string path, const bool dereference, int *id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    int flag = f_directory_flag_directory | f_directory_flag_close_execute | f_directory_flag_path;

    if (dereference) {
      flag |= f_directory_flag_no_follow;
    }

    *id = open(path, flag);

    if (*id < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EFBIG || errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == EINTR) return F_status_set_error(F_interrupted);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOENT) return F_status_set_error(F_directory_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == ENOTDIR) return F_status_set_error(F_file_type_not_directory);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_directory_open_

#ifndef _di_f_directory_open_at_
  f_return_status f_directory_open_at(const int at_id, const f_string path, const bool dereference, int *id) {
    #ifndef _di_level_0_parameter_checking_
      if (at_id <= 0) return F_status_set_error(F_parameter);
      if (id == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    int flag = f_directory_flag_directory | f_directory_flag_close_execute | f_directory_flag_path;

    if (dereference) {
      flag |= f_directory_flag_no_follow;
    }

    *id = openat(at_id, path, flag);

    if (*id < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EFBIG || errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == EINTR) return F_status_set_error(F_interrupted);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOENT) return F_status_set_error(F_directory_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOTDIR) return F_status_set_error(F_file_type_not_directory);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_directory_open_at_

#ifndef _di_f_directory_remove_
  f_return_status f_directory_remove(const f_string path, const int recursion_max, const bool preserve) {
    #ifndef _di_level_0_parameter_checking_
      if (recursion_max < 0) return F_status_set_error(F_parameter);
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
      if (preserve) return F_none;

      result = remove(path);
    }

    if (result < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBUSY) return F_status_set_error(F_busy);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EISDIR) return F_status_set_error(F_file_type_directory);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_directory_remove_

#ifndef _di_f_directory_remove_custom_
  f_return_status f_directory_remove_custom(const f_string path, const int recursion_max, const bool preserve, int (*custom) (const char *, const struct stat *, int, struct FTW *)) {
    #ifndef _di_level_0_parameter_checking_
      if (recursion_max < 0) return F_status_set_error(F_parameter);
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
      if (preserve) return F_none;

      result = remove(path);
    }

    if (result < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBUSY) return F_status_set_error(F_busy);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EISDIR) return F_status_set_error(F_file_type_directory);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_directory_remove_custom_

#ifndef _di_f_directory_touch_
  f_return_status f_directory_touch(const f_string path, const mode_t mode) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = F_none;
    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    if (stat(path, &file_stat) < 0) {

      if (errno == ENOENT) {
        return private_f_directory_create(path, mode);
      }

      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == ELOOP) return F_status_set_error(F_loop);

      return F_status_set_error(F_file_stat);
    }

    if (utimensat(f_directory_at_current_working, path, 0, 0) < 0) {

      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == ESRCH) return  F_status_set_error(F_search);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_directory_touch_

#ifndef _di_f_directory_touch_at_
  f_return_status f_directory_touch_at(const int at_id, const f_string path, const mode_t mode, const int flag) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = F_none;
    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    if (fstatat(at_id, path, &file_stat, flag) < 0) {

      if (errno == ENOENT) {
        return private_f_directory_create_at(at_id, path, mode);
      }

      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);

      return F_status_set_error(F_file_stat);
    }

    if (utimensat(at_id, path, 0, flag) < 0) {

      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == ESRCH) return  F_status_set_error(F_search);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_directory_touch_at_

#ifdef __cplusplus
} // extern "C"
#endif
