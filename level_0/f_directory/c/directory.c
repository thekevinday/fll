#include "directory.h"
#include "private-directory.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_directory_create_
  f_status_t f_directory_create(const f_string_static_t path, const mode_t mode) {

    if (!path.used) {
      return F_data_not;
    }

    return private_f_directory_create(path, mode);
  }
#endif // _di_f_directory_create_

#ifndef _di_f_directory_create_at_
  f_status_t f_directory_create_at(const int at_id, const f_string_static_t path, const mode_t mode) {
    #ifndef _di_level_0_parameter_checking_
      if (at_id <= 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    return private_f_directory_create_at(at_id, path, mode);
  }
#endif // _di_f_directory_create_at_

#ifndef _di_f_directory_exists_
  f_status_t f_directory_exists(const f_string_static_t path) {

    if (!path.used) {
      return F_data_not;
    }

    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    if (stat(path.string, &file_stat) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_file_found_not;
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_false;
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);

      return F_status_set_error(F_file_stat);
    }

    if ((file_stat.st_mode & S_IFMT) == S_IFDIR) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_directory_exists_

#ifndef _di_f_directory_exists_at_
  f_status_t f_directory_exists_at(const int at_id, const f_string_static_t path, const int flag) {

    if (!path.used) {
      return F_data_not;
    }

    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    if (fstatat(at_id, path.string, &file_stat, flag) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_file_found_not;
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_false;
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);

      return F_status_set_error(F_file_stat);
    }

    if ((file_stat.st_mode & S_IFMT) == S_IFDIR) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_directory_exists_at_

#ifndef _di_f_directory_is_
  f_status_t f_directory_is(const f_string_static_t path) {

    if (!path.used) {
      return F_data_not;
    }

    struct stat file_stat;

    memset(&file_stat, AT_SYMLINK_NOFOLLOW, sizeof(struct stat));

    if (stat(path.string, &file_stat) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_file_found_not;
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_false;
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == ELOOP) return F_status_set_error(F_loop);

      return F_status_set_error(F_file_stat);
    }

    if ((file_stat.st_mode & S_IFMT) == S_IFDIR) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_directory_is_

#ifndef _di_f_directory_is_at_
  f_status_t f_directory_is_at(const int at_id, const f_string_static_t path, const int flag) {

    if (!path.used) {
      return F_data_not;
    }

    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    if (fstatat(at_id, path.string, &file_stat, flag) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_file_found_not;
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_false;
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == ELOOP) return F_status_set_error(F_loop);

      return F_status_set_error(F_file_stat);
    }

    if ((file_stat.st_mode & S_IFMT) == S_IFDIR) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_directory_is_at_

#ifndef _di_f_directory_list_
  f_status_t f_directory_list(const f_string_static_t path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), f_string_dynamics_t *names) {
    #ifndef _di_level_0_parameter_checking_
      if (!names) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    struct dirent **listing = 0;
    size_t i = 0;
    f_array_length_t size = 0;
    f_status_t status = F_none;

    const size_t length = scandir(path.string, &listing, filter, sort);

    if (length == -1) {
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      else return F_status_set_error(F_failure);
    }

    for (; i < length; ++i) {

      size = strnlen(listing[i]->d_name, F_directory_name_max_d);

      // There is no reason to include "." and ".." in the directory listing.
      if (!strncmp(listing[i]->d_name, "..", 3) || !strncmp(listing[i]->d_name, ".", 2))  {
        f_memory_delete(size, sizeof(unsigned char *), (void **) & listing[i]);

        continue;
      }

      if (names->used == names->size) {
        macro_f_memory_structure_increment(status, (*names), 1, F_directory_default_allocation_step_d, macro_f_string_dynamics_t_resize, F_array_too_large);
        if (F_status_is_error(status)) break;
      }

      names->array[names->used].used = 0;

      status = f_string_dynamic_increase_by(size, &names->array[names->used]);
      if (F_status_is_error(status)) break;

      memcpy(names->array[names->used].string, listing[i]->d_name, sizeof(unsigned char) * size);
      names->array[names->used++].used = size;

      f_memory_delete(size, sizeof(unsigned char *), (void **) & listing[i]);
    } // for

    for (; i < length; ++i) {
      f_memory_delete(size, sizeof(unsigned char *), (void **) & listing[i]);
    } // for

    f_memory_delete(1, sizeof(struct dirent *), (void **) & listing);

    if (F_status_is_error(status)) {
      return status;
    }

    if (!length) {
      return F_directory_empty;
    }

    return F_none;
  }
#endif // _di_f_directory_list_

#ifndef _di_f_directory_open_
  f_status_t f_directory_open(const f_string_static_t path, const bool dereference, int *id) {
    #ifndef _di_level_0_parameter_checking_
      if (!id) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    int flag = F_directory_flag_directory_d | F_directory_flag_close_execute_d | F_directory_flag_path_d;

    if (dereference) {
      flag |= F_directory_flag_no_follow_d;
    }

    *id = open(path.string, flag);

    if (*id < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EFBIG || errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOENT) return F_status_set_error(F_directory_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
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
  f_status_t f_directory_open_at(const int at_id, const f_string_static_t path, const bool dereference, int *id) {
    #ifndef _di_level_0_parameter_checking_
      if (at_id <= 0) return F_status_set_error(F_parameter);
      if (!id) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    int flag = F_directory_flag_directory_d | F_directory_flag_close_execute_d | F_directory_flag_path_d;

    if (dereference) {
      flag |= F_directory_flag_no_follow_d;
    }

    *id = openat(at_id, path.string, flag);

    if (*id < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EFBIG || errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOENT) return F_status_set_error(F_directory_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
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
  f_status_t f_directory_remove(const f_string_static_t path, const int depth_max, const bool preserve) {
    #ifndef _di_level_0_parameter_checking_
      if (depth_max < 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    int result = 0;

    if (depth_max) {
      result = nftw((char *) path.string, private_f_directory_remove_recursively, depth_max, FTW_DEPTH | FTW_PHYS);

      if (result == 0 && !preserve) {
        result = remove(path.string);
      }
    }
    else {

      // Not recursively deleting and the path is requested to be preserved, so there is nothing to delete.
      if (preserve) {
        return F_none;
      }

      result = remove(path.string);
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
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == ENOTEMPTY) return F_status_set_error(F_directory_empty_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_directory_remove_

#ifndef _di_f_directory_remove_custom_
  f_status_t f_directory_remove_custom(const f_string_static_t path, const int depth_max, const bool preserve, int (*custom) (const char *, const struct stat *, int, struct FTW *)) {
    #ifndef _di_level_0_parameter_checking_
      if (depth_max < 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    int result = 0;

    if (depth_max) {
      result = nftw((char *) path.string, custom, depth_max, FTW_DEPTH | FTW_PHYS);

      if (result == 0 && !preserve) {
        result = remove(path.string);
      }
    }
    else {

      // Not recursively deleting and the path is requested to be preserved, so there is nothing to delete.
      if (preserve) {
        return F_none;
      }

      result = remove(path.string);
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
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == ENOTEMPTY) return F_status_set_error(F_directory_empty_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_directory_remove_custom_

#ifndef _di_f_directory_touch_
  f_status_t f_directory_touch(const f_string_static_t path, const mode_t mode) {

    if (!path.used) {
      return F_data_not;
    }

    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    if (stat(path.string, &file_stat) < 0) {
      if (errno == ENOENT) {
        return private_f_directory_create(path, mode);
      }

      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == ELOOP) return F_status_set_error(F_loop);

      return F_status_set_error(F_file_stat);
    }

    if (utimensat(F_directory_at_current_working_d, path.string, 0, 0) < 0) {
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
  f_status_t f_directory_touch_at(const int at_id, const f_string_static_t path, const mode_t mode, const int flag) {

    if (!path.used) {
      return F_data_not;
    }

    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    if (fstatat(at_id, path.string, &file_stat, flag) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return private_f_directory_create_at(at_id, path, mode);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);

      return F_status_set_error(F_file_stat);
    }

    if (utimensat(at_id, path.string, 0, flag) < 0) {
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
