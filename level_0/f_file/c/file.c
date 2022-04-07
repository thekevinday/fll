#include "file.h"
#include "private-file.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_file_access_
  f_status_t f_file_access(const f_string_static_t path) {

    if (!path.used) {
      return F_data_not;
    }

    if (access(path.string, F_OK)) {
      if (errno == ENOENT) return F_false;
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == ELOOP) return F_status_set_error(F_loop);

      return F_status_set_error(F_false);
    }

    return F_true;
  }
#endif // _di_f_file_access_

#ifndef _di_f_file_clone_
  f_status_t f_file_clone(const f_string_static_t source, const f_string_static_t destination, const bool role, const f_number_unsigned_t size_block, const bool exclusive) {

    if (!source.used || !destination.used) {
      return F_data_not;
    }

    f_status_t status = F_none;
    struct stat source_stat;

    memset(&source_stat, 0, sizeof(struct stat));

    status = private_f_file_stat(source, F_false, &source_stat);
    if (F_status_is_error(status)) return status;

    if (macro_f_file_type_is_regular(source_stat.st_mode)) {
      status = private_f_file_create(destination, source_stat.st_mode, exclusive);
      if (F_status_is_error(status)) return status;

      if (!exclusive) {
        status = private_f_file_mode_set(destination, source_stat.st_mode);
        if (F_status_is_error(status)) return status;
      }

      if (role) {
        status = private_f_file_role_change(destination, source_stat.st_uid, source_stat.st_gid, F_false);
        if (F_status_is_error(status)) return status;
      }

      return private_f_file_copy_content(source, destination, size_block == 0 ? F_file_default_read_size_d : size_block);
    }

    if (macro_f_file_type_is_link(source_stat.st_mode)) {
      status = private_f_file_link(destination, source);

      if (F_status_set_fine(status) == F_file_found) {
        if (exclusive) return status;
      }
      else if (F_status_is_error(status)) {
        return status;
      }

      status = private_f_file_mode_set(destination, source_stat.st_mode);
      if (F_status_is_error(status)) return status;

      if (role) {
        status = private_f_file_role_change(destination, source_stat.st_uid, source_stat.st_gid, F_false);
        if (F_status_is_error(status)) return status;
      }

      return F_none;
    }

    return F_supported_not;
  }
#endif // _di_f_file_clone_

#ifndef _di_f_file_close_
  f_status_t f_file_close(int * const id) {
    #ifndef _di_level_0_parameter_checking_
      if (!id) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_close(id, F_false);
  }
#endif // _di_f_file_close_

#ifndef _di_f_file_close_flush_
  f_status_t f_file_close_flush(int * const id) {
    #ifndef _di_level_0_parameter_checking_
      if (!id) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_close(id, F_true);
  }
#endif // _di_f_file_close_flush_

#ifndef _di_f_file_copy_
  f_status_t f_file_copy(const f_string_static_t source, const f_string_static_t destination, const f_mode_t mode, const f_number_unsigned_t size_block, const bool exclusive) {

    if (!source.used || !destination.used) {
      return F_data_not;
    }

    f_status_t status = F_none;
    struct stat source_stat;

    memset(&source_stat, 0, sizeof(struct stat));

    status = private_f_file_stat(source, F_false, &source_stat);
    if (F_status_is_error(status)) return status;

    if (macro_f_file_type_is_regular(source_stat.st_mode)) {

      status = private_f_file_create(destination, (~F_file_type_mask_d) & mode.regular, exclusive);
      if (F_status_is_error(status)) return status;

      if (!exclusive) {
        status = private_f_file_mode_set(destination, (~F_file_type_mask_d) & mode.regular);
        if (F_status_is_error(status)) return status;
      }

      return private_f_file_copy_content(source, destination, size_block == 0 ? F_file_default_read_size_d : size_block);
    }

    if (macro_f_file_type_is_directory(source_stat.st_mode)) {
      status = private_f_file_create_directory(destination, (~F_file_type_mask_d) & mode.directory);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) != F_file_found || exclusive) {
          return status;
        }
      }

      status = private_f_file_mode_set(destination, (~F_file_type_mask_d) & mode.directory);
      if (F_status_is_error(status)) return status;

      return F_none;
    }

    if (macro_f_file_type_is_link(source_stat.st_mode)) {
      f_string_dynamic_t target = f_string_dynamic_t_initialize;

      status = private_f_file_link_read(source, source_stat, &target);
      if (F_status_is_error(status)) {
        f_string_dynamic_resize(0, &target);

        return status;
      }

      status = private_f_file_link(target, destination);

      f_string_dynamic_resize(0, &target);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) != F_file_found || exclusive) {
          return status;
        }
      }

      return F_none;
    }

    if (macro_f_file_type_is_fifo(source_stat.st_mode)) {
      status = private_f_file_create_fifo(destination, (~F_file_type_mask_d) & mode.fifo);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) != F_file_found || exclusive) {
          return status;
        }
      }

      status = private_f_file_mode_set(destination, (~F_file_type_mask_d) & mode.fifo);
      if (F_status_is_error(status)) return status;

      return F_none;
    }

    if (macro_f_file_type_is_socket(source_stat.st_mode)) {
      status = private_f_file_create_node(destination, macro_f_file_type_get(source_stat.st_mode) | ((~F_file_type_mask_d) & mode.socket), source_stat.st_rdev);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) != F_file_found || exclusive) {
          return status;
        }
      }

      status = private_f_file_mode_set(destination, (~F_file_type_mask_d) & mode.socket);
      if (F_status_is_error(status)) return status;

      return F_none;
    }

    if (macro_f_file_type_is_block(source_stat.st_mode) || macro_f_file_type_is_character(source_stat.st_mode)) {
      status = private_f_file_create_node(destination, macro_f_file_type_get(source_stat.st_mode) | ((~F_file_type_mask_d) & mode.block), source_stat.st_rdev);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) != F_file_found || exclusive) {
          return status;
        }
      }

      status = private_f_file_mode_set(destination, (~F_file_type_mask_d) & mode.block);
      if (F_status_is_error(status)) return status;

      return F_none;
    }

    return F_supported_not;
  }
#endif // _di_f_file_copy_

#ifndef _di_f_file_create_
  f_status_t f_file_create(const f_string_static_t path, const mode_t mode, const bool exclusive) {

    if (!path.used) {
      return F_data_not;
    }

    return private_f_file_create(path, mode, exclusive);
  }
#endif // _di_f_file_create_

#ifndef _di_f_file_create_at_
  f_status_t f_file_create_at(const int at_id, const f_string_static_t path, const mode_t mode, const bool exclusive) {

    if (!path.used) {
      return F_data_not;
    }

    return private_f_file_create_at(at_id, path, mode, exclusive);
  }
#endif // _di_f_file_create_at_

#ifndef _di_f_file_create_device_
  f_status_t f_file_create_device(const f_string_static_t path, const mode_t mode, const unsigned int major, const unsigned int minor) {

    if (!path.used) {
      return F_data_not;
    }

    if (!macro_f_file_type_is_fifo(mode) && !macro_f_file_type_is_character(mode) && !macro_f_file_type_is_block(mode)) {
      return F_status_set_error(F_supported_not);
    }

    const dev_t device = makedev(major, minor);

    return private_f_file_create_node(path, mode, device);
  }
#endif // _di_f_file_create_device_

#ifndef _di_f_file_create_device_at_
  f_status_t f_file_create_device_at(const int at_id, const f_string_static_t path, const mode_t mode, const unsigned int major, const unsigned int minor) {

    if (!path.used) {
      return F_data_not;
    }

    if (!macro_f_file_type_is_fifo(mode) && !macro_f_file_type_is_character(mode) && !macro_f_file_type_is_block(mode)) {
      return F_status_set_error(F_supported_not);
    }

    const dev_t device = makedev(major, minor);

    return private_f_file_create_node_at(at_id, path, mode, device);
  }
#endif // _di_f_file_create_device_at_

#ifndef _di_f_file_create_fifo_
  f_status_t f_file_create_fifo(const f_string_static_t path, const mode_t mode) {

    if (!path.used) {
      return F_data_not;
    }

    return private_f_file_create_fifo(path, mode);
  }
#endif // _di_f_file_create_fifo_

#ifndef _di_f_file_create_fifo_at_
  f_status_t f_file_create_fifo_at(const int at_id, const f_string_static_t path, const mode_t mode) {

    if (!path.used) {
      return F_data_not;
    }

    return private_f_file_create_fifo_at(at_id, path, mode);
  }
#endif // _di_f_file_create_fifo_at_

#ifndef _di_f_file_create_node_
  f_status_t f_file_create_node(const f_string_static_t path, const mode_t mode, const dev_t device) {

    if (!path.used) {
      return F_data_not;
    }

    if (!macro_f_file_type_is_fifo(mode) && !macro_f_file_type_is_character(mode) && !macro_f_file_type_is_block(mode)) {
      return F_status_set_error(F_supported_not);
    }

    return private_f_file_create_node(path, mode, device);
  }
#endif // _di_f_file_create_node_

#ifndef _di_f_file_create_node_at_
  f_status_t f_file_create_node_at(const int at_id, const f_string_static_t path, const mode_t mode, const dev_t device) {

    if (!path.used) {
      return F_data_not;
    }

    if (!macro_f_file_type_is_fifo(mode) && !macro_f_file_type_is_character(mode) && !macro_f_file_type_is_block(mode)) {
      return F_status_set_error(F_supported_not);
    }

    return private_f_file_create_node_at(at_id, path, mode, device);
  }
#endif // _di_f_file_create_node_at_

#ifndef _di_f_file_descriptor_
  f_status_t f_file_descriptor(f_file_t *file) {

    file->id = fileno(file->stream);

    if (file->id == -1) {
      return F_status_set_error(F_file);
    }

    return F_none;
  }
#endif // _di_f_file_descriptor_

#ifndef _di_f_file_exists_
  f_status_t f_file_exists(const f_string_static_t path) {

    if (!path.used) {
      return F_data_not;
    }

    struct stat stat_file;

    memset(&stat_file, 0, sizeof(struct stat));

    const f_status_t status = private_f_file_stat(path, F_false, &stat_file);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_file_found_not) {
        return F_false;
      }

      return status;
    }

    return F_true;
  }
#endif // _di_f_file_exists_

#ifndef _di_f_file_exists_at_
  f_status_t f_file_exists_at(const int at_id, const f_string_static_t path, const int flag) {

    if (!path.used) {
      return F_data_not;
    }

    struct stat stat_file;

    memset(&stat_file, 0, sizeof(struct stat));

    const f_status_t status = private_f_file_stat_at(at_id, path, flag, &stat_file);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_file_found_not) {
        return F_false;
      }

      return status;
    }

    return F_true;
  }
#endif // _di_f_file_exists_at_

#ifndef _di_f_file_flush_
  f_status_t f_file_flush(const int id) {

    return private_f_file_flush(id);
  }
#endif // _di_f_file_flush_

#ifndef _di_f_file_group_read_
  f_status_t f_file_group_read(const f_string_static_t path, gid_t * const group) {
    #ifndef _di_level_0_parameter_checking_
      if (!group) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    struct stat stat_file;

    memset(&stat_file, 0, sizeof(struct stat));

    {
      const f_status_t status = private_f_file_stat(path, F_true, &stat_file);
      if (F_status_is_error(status)) return status;
    }

    *group = stat_file.st_gid;

    return F_none;
  }
#endif // _di_f_file_group_read_

#ifndef _di_f_file_is_
  f_status_t f_file_is(const f_string_static_t path, const int type, const bool dereference) {

    if (!path.used) {
      return F_data_not;
    }

    struct stat stat_file;

    memset(&stat_file, 0, sizeof(struct stat));

    {
      const f_status_t status = private_f_file_stat(path, dereference, &stat_file);
      if (F_status_is_error(status)) return status;
    }

    if (macro_f_file_type_get(stat_file.st_mode) == type) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_file_is_

#ifndef _di_f_file_is_at_
  f_status_t f_file_is_at(const int at_id, const f_string_static_t path, const int type, const int flag) {

    if (!path.used) {
      return F_data_not;
    }

    struct stat stat_file;

    memset(&stat_file, 0, sizeof(struct stat));

    if (fstatat(at_id, path.string, &stat_file, flag) < 0) {
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == ENOENT) return F_file_found_not;
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);

      return F_status_set_error(F_file_stat);
    }

    if (stat_file.st_mode == (S_IFMT & S_IFDIR)) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_file_is_at_

#ifndef _di_f_file_link_
  f_status_t f_file_link(const f_string_static_t target, const f_string_static_t point) {

    if (!target.used || !point.used) {
      return F_data_not;
    }

    return private_f_file_link(target, point);
  }
#endif // _di_f_file_link_

#ifndef _di_f_file_link_at_
  f_status_t f_file_link_at(const int at_id, const f_string_static_t target, const f_string_static_t point) {

    if (!target.used || !point.used) {
      return F_data_not;
    }

    return private_f_file_link_at(at_id, target, point);
  }
#endif // _di_f_file_link_at_

#ifndef _di_f_file_link_hard_
  f_status_t f_file_link_hard(const f_string_static_t target, const f_string_static_t point) {

    if (!target.used || !point.used) {
      return F_data_not;
    }

    if (link(target.string, point.string) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EFBIG || errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == ETXTBSY) return F_status_set_error(F_busy);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_file_link_hard_

#ifndef _di_f_file_link_hard_at_
  f_status_t f_file_link_hard_at(const int at_id_target, const int at_id_point, const f_string_static_t target, const f_string_static_t point, const int flag) {

    if (linkat(at_id_target, target.string, at_id_point, point.string, flag) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EFBIG || errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == ETXTBSY) return F_status_set_error(F_busy);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_file_link_hard_at_

#ifndef _di_f_file_link_read_
  f_status_t f_file_link_read(const f_string_static_t path, const struct stat link_stat, f_string_dynamic_t * const target) {
    #ifndef _di_level_0_parameter_checking_
      if (!link_stat.st_size) return F_status_set_error(F_parameter);
      if (!target) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    return private_f_file_link_read(path, link_stat, target);
  }
#endif // _di_f_file_link_read_

#ifndef _di_f_file_link_read_at_
  f_status_t f_file_link_read_at(const int at_id, const f_string_static_t path, const struct stat link_stat, f_string_dynamic_t * const target) {
    #ifndef _di_level_0_parameter_checking_
      if (!link_stat.st_size) return F_status_set_error(F_parameter);
      if (!target) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    return private_f_file_link_read_at(at_id, path, link_stat, target);
  }
#endif // _di_f_file_link_read_at_

#ifndef _di_f_file_mode_determine_
  f_status_t f_file_mode_determine(const mode_t mode_file, const f_file_mode_t mode_change, const uint8_t mode_replace, const bool directory_is, mode_t *mode) {
    #ifndef _di_level_0_parameter_checking_
      if (!mode) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_file_mode_t change = mode_change & F_file_mode_t_block_special_d;

    *mode = 0;

    if (mode_replace & F_file_mode_t_replace_special_d) {
      if (change & F_file_mode_t_mask_bit_set_owner_d & F_file_mode_t_mask_how_add_d) {
        *mode = F_file_mode_special_set_user_d;
      }

      if (change & F_file_mode_t_mask_bit_set_group_d & F_file_mode_t_mask_how_add_d) {
        *mode |= F_file_mode_special_set_group_d;
      }

      if (change & F_file_mode_t_mask_bit_sticky_d & F_file_mode_t_mask_how_add_d) {
        *mode |= F_file_mode_special_sticky_d;
      }
    }
    else {
      *mode = mode_file & F_file_mode_special_all_d;

      if (mode_change & F_file_mode_t_block_special_d) {
        if (change & F_file_mode_t_mask_bit_set_owner_d & F_file_mode_t_mask_how_subtract_d) {
          if (*mode & F_file_mode_special_set_user_d) {
            *mode -= F_file_mode_special_set_user_d;
          }
        }
        else if (change & F_file_mode_t_mask_bit_set_owner_d & F_file_mode_t_mask_how_add_d) {
          if (!(*mode & F_file_mode_special_set_user_d)) {
            *mode |= F_file_mode_special_set_user_d;
          }
        }

        if (change & F_file_mode_t_mask_bit_set_group_d & F_file_mode_t_mask_how_subtract_d) {
          if (*mode & F_file_mode_special_set_group_d) {
            *mode -= F_file_mode_special_set_group_d;
          }
        }
        else if (change & F_file_mode_t_mask_bit_set_group_d & F_file_mode_t_mask_how_add_d) {
          if (!(*mode & F_file_mode_special_set_group_d)) {
            *mode |= F_file_mode_special_set_group_d;
          }
        }

        if (change & F_file_mode_t_mask_bit_sticky_d & F_file_mode_t_mask_how_subtract_d) {
          if (*mode & F_file_mode_special_sticky_d) {
            *mode -= F_file_mode_special_sticky_d;
          }
        }
        else if (change & F_file_mode_t_mask_bit_sticky_d & F_file_mode_t_mask_how_add_d) {
          if (!(*mode & F_file_mode_special_sticky_d)) {
            *mode |= F_file_mode_special_sticky_d;
          }
        }
      }
    }

    change = mode_change & F_file_mode_t_block_owner_d;

    if (mode_replace & F_file_mode_t_replace_owner_d) {
      if (change & F_file_mode_t_mask_bit_read_d & F_file_mode_t_mask_how_add_d) {
        *mode |= F_file_mode_owner_r_d;
      }

      if (change & F_file_mode_t_mask_bit_write_d & F_file_mode_t_mask_how_add_d) {
        *mode |= F_file_mode_owner_w_d;
      }

      if (change & F_file_mode_t_mask_bit_execute_d & F_file_mode_t_mask_how_add_d) {
        *mode |= F_file_mode_owner_x_d;
      }
      else if (change & F_file_mode_t_mask_bit_execute_only_d & F_file_mode_t_mask_how_add_d) {
        if (directory_is || (mode_file & F_file_mode_owner_x_d)) {
          *mode |= F_file_mode_owner_x_d;
        }
      }
    }
    else {
      *mode |= mode_file & F_file_mode_owner_rwx_d;

      if (mode_change & F_file_mode_t_block_owner_d) {
        if (change & F_file_mode_t_mask_bit_read_d & F_file_mode_t_mask_how_subtract_d) {
          if (*mode & F_file_mode_owner_r_d) {
            *mode -= F_file_mode_owner_r_d;
          }
        }
        else if (change & F_file_mode_t_mask_bit_read_d & F_file_mode_t_mask_how_add_d) {
          if (!(*mode & F_file_mode_owner_r_d)) {
            *mode |= F_file_mode_owner_r_d;
          }
        }

        if (change & F_file_mode_t_mask_bit_write_d & F_file_mode_t_mask_how_subtract_d) {
          if (*mode & F_file_mode_owner_w_d) {
            *mode -= F_file_mode_owner_w_d;
          }
        }
        else if (change & F_file_mode_t_mask_bit_write_d & F_file_mode_t_mask_how_add_d) {
          if (!(*mode & F_file_mode_owner_w_d)) {
            *mode |= F_file_mode_owner_w_d;
          }
        }

        if (change & F_file_mode_t_mask_bit_execute_d) {
          change &= F_file_mode_t_mask_bit_execute_d;

          if (change & F_file_mode_t_mask_how_subtract_d) {
            if (*mode & F_file_mode_owner_x_d) {
              *mode -= F_file_mode_owner_x_d;
            }
          }
          else if (change & F_file_mode_t_mask_how_add_d) {
            if (!(*mode & F_file_mode_owner_x_d)) {
              *mode |= F_file_mode_owner_x_d;
            }
          }
        }
        else if (change & F_file_mode_t_mask_bit_execute_only_d) {
          change &= F_file_mode_t_mask_bit_execute_only_d;

          if (directory_is || (mode_file & F_file_mode_owner_x_d)) {
            if (change & F_file_mode_t_mask_how_subtract_d) {
              if (*mode & F_file_mode_owner_x_d) {
                *mode -= F_file_mode_owner_x_d;
              }
            }
            else if (change & F_file_mode_t_mask_how_add_d) {
              if (!(*mode & F_file_mode_owner_x_d)) {
                *mode |= F_file_mode_owner_x_d;
              }
            }
          }
        }
      }
    }

    change = mode_change & F_file_mode_t_block_group_d;

    if (mode_replace & F_file_mode_t_replace_group_d) {
      if (change & F_file_mode_t_mask_bit_read_d & F_file_mode_t_mask_how_add_d) {
        *mode |= F_file_mode_group_r_d;
      }

      if (change & F_file_mode_t_mask_bit_write_d & F_file_mode_t_mask_how_add_d) {
        *mode |= F_file_mode_group_w_d;
      }

      if (change & F_file_mode_t_mask_bit_execute_d & F_file_mode_t_mask_how_add_d) {
        *mode |= F_file_mode_group_x_d;
      }
      else if (change & F_file_mode_t_mask_bit_execute_only_d & F_file_mode_t_mask_how_add_d) {
        if (directory_is || (mode_file & F_file_mode_group_x_d)) {
          *mode |= F_file_mode_group_x_d;
        }
      }
    }
    else {
      *mode |= mode_file & F_file_mode_group_rwx_d;

      if (mode_change & F_file_mode_t_block_group_d) {
        if (change & F_file_mode_t_mask_bit_read_d & F_file_mode_t_mask_how_subtract_d) {
          if (*mode & F_file_mode_group_r_d) {
            *mode -= F_file_mode_group_r_d;
          }
        }
        else if (change & F_file_mode_t_mask_bit_read_d & F_file_mode_t_mask_how_add_d) {
          if (!(*mode & F_file_mode_group_r_d)) {
            *mode |= F_file_mode_group_r_d;
          }
        }

        if (change & F_file_mode_t_mask_bit_write_d & F_file_mode_t_mask_how_subtract_d) {
          if (*mode & F_file_mode_group_w_d) {
            *mode -= F_file_mode_group_w_d;
          }
        }
        else if (change & F_file_mode_t_mask_bit_write_d & F_file_mode_t_mask_how_add_d) {
          if (!(*mode & F_file_mode_group_w_d)) {
            *mode |= F_file_mode_group_w_d;
          }
        }

        if (change & F_file_mode_t_mask_bit_execute_d) {
          change &= F_file_mode_t_mask_bit_execute_d;

          if (change & F_file_mode_t_mask_how_subtract_d) {
            if (*mode & F_file_mode_group_x_d) {
              *mode -= F_file_mode_group_x_d;
            }
          }
          else if (change & F_file_mode_t_mask_how_add_d) {
            if (!(*mode & F_file_mode_group_x_d)) {
              *mode |= F_file_mode_group_x_d;
            }
          }
        }
        else if (change & F_file_mode_t_mask_bit_execute_only_d) {
          change &= F_file_mode_t_mask_bit_execute_only_d;

          if (directory_is || (mode_file & F_file_mode_group_x_d)) {
            if (change & F_file_mode_t_mask_how_subtract_d) {
              if (*mode & F_file_mode_group_x_d) {
                *mode -= F_file_mode_group_x_d;
              }
            }
            else if (change & F_file_mode_t_mask_how_add_d) {
              if (!(*mode & F_file_mode_group_x_d)) {
                *mode |= F_file_mode_group_x_d;
              }
            }
          }
        }
      }
    }

    change = mode_change & F_file_mode_t_block_world_d;

    if (mode_replace & F_file_mode_t_replace_world_d) {
      if (change & F_file_mode_t_mask_bit_read_d & F_file_mode_t_mask_how_add_d) {
        *mode |= F_file_mode_world_r_d;
      }

      if (change & F_file_mode_t_mask_bit_write_d & F_file_mode_t_mask_how_add_d) {
        *mode |= F_file_mode_world_w_d;
      }

      if (change & F_file_mode_t_mask_bit_execute_d & F_file_mode_t_mask_how_add_d) {
        *mode |= F_file_mode_world_x_d;
      }
      else if (change & F_file_mode_t_mask_bit_execute_only_d & F_file_mode_t_mask_how_add_d) {
        if (directory_is || (mode_file & F_file_mode_world_x_d)) {
          *mode |= F_file_mode_world_x_d;
        }
      }
    }
    else {
      *mode |= mode_file & F_file_mode_world_rwx_d;

      if (mode_change & F_file_mode_t_block_world_d) {
        if (change & F_file_mode_t_mask_bit_read_d & F_file_mode_t_mask_how_subtract_d) {
          if (*mode & F_file_mode_world_r_d) {
            *mode -= F_file_mode_world_r_d;
          }
        }
        else if (change & F_file_mode_t_mask_bit_read_d & F_file_mode_t_mask_how_add_d) {
          if (!(*mode & F_file_mode_world_r_d)) {
            *mode |= F_file_mode_world_r_d;
          }
        }

        if (change & F_file_mode_t_mask_bit_write_d & F_file_mode_t_mask_how_subtract_d) {
          if (*mode & F_file_mode_world_w_d) {
            *mode -= F_file_mode_world_w_d;
          }
        }
        else if (change & F_file_mode_t_mask_bit_write_d & F_file_mode_t_mask_how_add_d) {
          if (!(*mode & F_file_mode_world_w_d)) {
            *mode |= F_file_mode_world_w_d;
          }
        }

        if (change & F_file_mode_t_mask_bit_execute_d) {
          change &= F_file_mode_t_mask_bit_execute_d;

          if (change & F_file_mode_t_mask_how_subtract_d) {
            if (*mode & F_file_mode_world_x_d) {
              *mode -= F_file_mode_world_x_d;
            }
          }
          else if (change & F_file_mode_t_mask_how_add_d) {
            if (!(*mode & F_file_mode_world_x_d)) {
              *mode |= F_file_mode_world_x_d;
            }
          }
        }
        else if (change & F_file_mode_t_mask_bit_execute_only_d) {
          change &= F_file_mode_t_mask_bit_execute_only_d;

          if (directory_is || (mode_file & F_file_mode_world_x_d)) {
            if (change & F_file_mode_t_mask_how_subtract_d) {
              if (*mode & F_file_mode_world_x_d) {
                *mode -= F_file_mode_world_x_d;
              }
            }
            else if (change & F_file_mode_t_mask_how_add_d) {
              if (!(*mode & F_file_mode_world_x_d)) {
                *mode |= F_file_mode_world_x_d;
              }
            }
          }
        }
      }
    }

    return F_none;
  }
#endif // _di_f_file_mode_determine_

#ifndef _di_f_file_mode_from_string_
  f_status_t f_file_mode_from_string(const f_string_static_t code, const mode_t umask, f_file_mode_t * const mode, uint8_t * const replace) {
    #ifndef _di_level_0_parameter_checking_
      if (!mode) return F_status_set_error(F_parameter);
      if (!replace) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!code.used) {
      return F_data_not;
    }

    uint8_t syntax = 0;
    uint8_t replace_result = 0;
    f_file_mode_t mode_result = 0;

    if (code.string[0] == f_string_ascii_plus_s.string[0] || code.string[0] == f_string_ascii_minus_s.string[0] || code.string[0] == f_string_ascii_equal_s.string[0]) {
      if (code.string[1] == f_string_ascii_r_s.string[0] || f_string_ascii_w_s.string[0] || f_string_ascii_x_s.string[0] || f_string_ascii_X_s.string[0] || f_string_ascii_s_s.string[0] ||f_string_ascii_t_s.string[0]) {
        syntax = 1;
      }
      else if (code.string[1] == f_string_ascii_0_s.string[0] || code.string[1] == f_string_ascii_1_s.string[0] || code.string[1] == f_string_ascii_2_s.string[0] || code.string[1] == f_string_ascii_3_s.string[0] || code.string[1] == f_string_ascii_4_s.string[0] || code.string[1] == f_string_ascii_5_s.string[0] || code.string[1] == f_string_ascii_6_s.string[0] || code.string[1] == f_string_ascii_7_s.string[0]) {
        syntax = 2;
      }
      else {
        return F_status_set_error(F_syntax);
      }
    }
    else if (code.string[0] == f_string_ascii_u_s.string[0] || code.string[0] == f_string_ascii_g_s.string[0] || code.string[0] == f_string_ascii_o_s.string[0] || code.string[0] == f_string_ascii_a_s.string[0]) {
      syntax = 1;
    }
    else if (code.string[0] == f_string_ascii_0_s.string[0] || code.string[0] == f_string_ascii_1_s.string[0] || code.string[0] == f_string_ascii_2_s.string[0] || code.string[0] == f_string_ascii_3_s.string[0] || code.string[0] == f_string_ascii_4_s.string[0] || code.string[0] == f_string_ascii_5_s.string[0] || code.string[0] == f_string_ascii_6_s.string[0] || code.string[0] == f_string_ascii_7_s.string[0]) {
      syntax = 2;
    }
    else {
      return F_status_set_error(F_syntax);
    }

    if (syntax == 1) {
      uint8_t on = 0; // 1 = user, 2 = group, 4 = world/sticky, 7 = all.
      uint8_t how = 0; // 1 = add, 2 = replace, 3 = subtract, 4 = add when no "on", 5 = replace when no "on", and 6 = subtract when no "on".

      f_file_mode_t mode_mask = 0;
      f_file_mode_t mode_umask = 0;
      f_file_mode_t what = 0;

      // Translate the umask into an f_file_mode_t umask equivalent.
      if (umask & F_file_mode_special_set_user_d) {
        mode_umask = F_file_mode_t_block_special_d & F_file_mode_t_mask_bit_set_owner_d;
      }

      if (umask & F_file_mode_special_set_group_d) {
        mode_umask |= F_file_mode_t_block_special_d & F_file_mode_t_mask_bit_set_group_d;
      }

      if (umask & F_file_mode_special_sticky_d) {
        mode_umask |= F_file_mode_t_block_special_d & F_file_mode_t_mask_bit_sticky_d;
      }

      if (umask & F_file_mode_owner_r_d) {
        mode_umask |= F_file_mode_t_block_owner_d & F_file_mode_t_mask_bit_read_d;
      }

      if (umask & F_file_mode_owner_w_d) {
        mode_umask |= F_file_mode_t_block_owner_d & F_file_mode_t_mask_bit_write_d;
      }

      if (umask & F_file_mode_owner_x_d) {
        mode_umask |= F_file_mode_t_block_owner_d & F_file_mode_t_mask_bit_execute_d;
      }

      if (umask & F_file_mode_group_r_d) {
        mode_umask |= F_file_mode_t_block_group_d & F_file_mode_t_mask_bit_read_d;
      }

      if (umask & F_file_mode_group_w_d) {
        mode_umask |= F_file_mode_t_block_group_d & F_file_mode_t_mask_bit_write_d;
      }

      if (umask & F_file_mode_group_x_d) {
        mode_umask |= F_file_mode_t_block_group_d & F_file_mode_t_mask_bit_execute_d;
      }

      if (umask & F_file_mode_world_r_d) {
        mode_umask |= F_file_mode_t_block_world_d & F_file_mode_t_mask_bit_read_d;
      }

      if (umask & F_file_mode_world_w_d) {
        mode_umask |= F_file_mode_t_block_world_d & F_file_mode_t_mask_bit_write_d;
      }

      if (umask & F_file_mode_world_x_d) {
        mode_umask |= F_file_mode_t_block_world_d & F_file_mode_t_mask_bit_execute_d;
      }

      for (f_array_length_t i = 0; syntax && code.string[i]; ++i) {

        if (code.string[i] == f_string_ascii_u_s.string[0]) {
          on |= 1;
          mode_mask |= F_file_mode_t_block_owner_d;
        }
        else if (code.string[i] == f_string_ascii_g_s.string[0]) {
          on |= 2;
          mode_mask |= F_file_mode_t_block_group_d;
        }
        else if (code.string[i] == f_string_ascii_o_s.string[0]) {
          on |= 4;
          mode_mask |= F_file_mode_t_block_world_d;
        }
        else if (code.string[i] == f_string_ascii_a_s.string[0]) {
          on = 7;
          mode_mask = F_file_mode_t_block_standard_d;
        }
        else if (code.string[i] == f_string_ascii_plus_s.string[0] || code.string[i] == f_string_ascii_minus_s.string[0] || code.string[i] == f_string_ascii_equal_s.string[0]) {
          if (code.string[i] == f_string_ascii_plus_s.string[0]) {
            how = on ? 1 : 4;
          }
          else if (code.string[i] == f_string_ascii_minus_s.string[0]) {
            how = on ? 3 : 6;
          }
          else {
            how = on ? 2 : 5;

            // Clear by mask to prepare for replacement, which includes clearing the special block.
            mode_mask |= F_file_mode_t_block_special_d;
            mode_result -= mode_result & mode_mask;

            replace_result |= F_file_mode_t_replace_special_d;

            if (mode_mask & F_file_mode_t_block_owner_d) {
              replace_result |= F_file_mode_t_replace_owner_d;
            }

            if (mode_mask & F_file_mode_t_block_group_d) {
              replace_result |= F_file_mode_t_replace_group_d;
            }

            if (mode_mask & F_file_mode_t_block_world_d) {
              replace_result |= F_file_mode_t_replace_world_d;
            }
          }

          if (!on) {
            on = 7;
            mode_mask = F_file_mode_t_block_all_d;
          }

          what = 0;

          for (++i; code.string[i]; ++i) {

            if (code.string[i] == f_string_ascii_r_s.string[0]) {
              what = F_file_mode_t_mask_bit_read_d;
            }
            else if (code.string[i] == f_string_ascii_w_s.string[0]) {
              what = F_file_mode_t_mask_bit_write_d;
            }
            else if (code.string[i] == f_string_ascii_x_s.string[0]) {
              what = F_file_mode_t_mask_bit_execute_d;
            }
            else if (code.string[i] == f_string_ascii_X_s.string[0]) {
              what = F_file_mode_t_mask_bit_execute_only_d;
            }
            else if (code.string[i] == f_string_ascii_s_s.string[0]) {
              mode_mask |= F_file_mode_t_block_special_d;

              if (on & 1) {
                what = F_file_mode_t_mask_bit_set_owner_d;
              }
              else if (on & 2) {
                what = F_file_mode_t_mask_bit_set_group_d;
              }
              else {
                what = 0;
              }
            }
            else if (code.string[i] == f_string_ascii_t_s.string[0]) {
              mode_mask |= F_file_mode_t_block_special_d;

              if (on & 4) {
                what = F_file_mode_t_mask_bit_sticky_d;
              }
              else {
                what = 0;
              }
            }
            else if (code.string[i] == f_string_ascii_comma_s.string[0]) {
              if (how > 3) {
                mode_result -= mode_result & mode_umask;
              }

              on = 0;
              how = 0;
              mode_mask = 0;

              break;
            }
            else if (code.string[i] == f_string_ascii_plus_s.string[0] || code.string[i] == f_string_ascii_minus_s.string[0] || code.string[i] == f_string_ascii_equal_s.string[0]) {
              what = 0;

              if (code.string[i] == f_string_ascii_plus_s.string[0]) {
                how = on ? 1 : 4;
              }
              else if (code.string[i] == f_string_ascii_minus_s.string[0]) {
                how = on ? 3 : 6;
              }
              else {
                how = on ? 2 : 5;

                // Clear by mask to prepare for replacement, which includes clearing the special block.
                mode_mask |= F_file_mode_t_block_special_d;
                mode_result -= mode_result & mode_mask;

                replace_result |= F_file_mode_t_replace_special_d;

                if (mode_mask & F_file_mode_t_block_owner_d) {
                  replace_result |= F_file_mode_t_replace_owner_d;
                }

                if (mode_mask & F_file_mode_t_block_group_d) {
                  replace_result |= F_file_mode_t_replace_group_d;
                }

                if (mode_mask & F_file_mode_t_block_world_d) {
                  replace_result |= F_file_mode_t_replace_world_d;
                }
              }
            }
            else {
              syntax = 0;

              break;
            }

            if (what) {
              if (how == 1 || how == 2 || how == 4 || how == 5) {
                mode_result |= what & mode_mask & F_file_mode_t_mask_how_add_d;

                if (mode_result & what & mode_mask & F_file_mode_t_mask_how_subtract_d) {
                  mode_result -= mode_result & what & mode_mask & F_file_mode_t_mask_how_subtract_d;
                }
              }
              else if (how == 3 || how == 6) {
                mode_result |= what & mode_mask & F_file_mode_t_mask_how_subtract_d;

                if (mode_result & what & mode_mask & F_file_mode_t_mask_how_add_d) {
                  mode_result -= mode_result & what & mode_mask & F_file_mode_t_mask_how_add_d;
                }
              }
            }
          } // for

          if (how > 3) {
            mode_result -= mode_result & mode_umask;
          }

          if (!code.string[i]) break;
        }
        else {
          syntax = 0;
        }
      } // for
    }
    else if (syntax == 2) {

      // 1 = add, 2 = replace, 3 = subtract.
      uint8_t how = 0;

      // 0 = none, 0x1 = leading zero.
      uint8_t option = 0;

      f_array_length_t i = 0;
      f_array_length_t j = 0;

      if (code.string[0] == f_string_ascii_plus_s.string[0]) {
        how = 1;
        i = 1;
      }
      else if (code.string[0] == f_string_ascii_minus_s.string[0]) {
        how = 3;
        i = 1;
      }
      else if (code.string[0] == f_string_ascii_equal_s.string[0]) {
        how = 2;
        i = 1;

        replace_result = F_file_mode_t_replace_standard_d;
      }
      else {
        how = 2;

        replace_result = F_file_mode_t_replace_standard_d | F_file_mode_t_replace_directory_d;
      }

      // Seek past leading '0's.
      while (code.string[i] == f_string_ascii_0_s.string[0]) {
        ++i;
      } // while

      if (code.string[i]) {
        f_array_length_t j = 0;

        for (; code.string[i + j] && j < 4; ++j) {

          if (j) {
            mode_result <<= 8;
          }

          if (code.string[i] == f_string_ascii_0_s.string[0]) {
            // Already is a zero.
          }
          else if (code.string[i] == f_string_ascii_1_s.string[0] || code.string[i] == f_string_ascii_2_s.string[0] || code.string[i] == f_string_ascii_3_s.string[0] || code.string[i] == f_string_ascii_4_s.string[0] || code.string[i] == f_string_ascii_5_s.string[0] || code.string[i] == f_string_ascii_6_s.string[0] || code.string[i] == f_string_ascii_7_s.string[0]) {

            // This assumes ASCII/UTF-8.
            if (how == 3) {
              mode_result |= (code.string[i + j] - 0x30) << 4;
            }
            else {
              mode_result |= code.string[i + j] - 0x30;
            }
          }
          else {

            // Designate that this is invalid.
            j = 4;
            break;
          }
        } // for

        if (j == 4) {
          syntax = 0;
        }
        else if (how == 2) {

          // If there are only '0's then the standard and setuid/setgid/sticky bits are to be replaced.
          if (!mode_result) {
            replace_result = F_file_mode_t_replace_standard_d | F_file_mode_t_replace_special_d;
          }
        }
      }
    }

    if (syntax) {
      *mode = mode_result;
      *replace = replace_result;

      return F_none;
    }

    return F_status_set_error(F_syntax);
  }
#endif // _di_f_file_mode_from_string_

#ifndef _di_f_file_mode_read_
  f_status_t f_file_mode_read(const f_string_static_t path, mode_t * const mode) {
    #ifndef _di_level_0_parameter_checking_
      if (!mode) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    struct stat stat_file;

    memset(&stat_file, 0, sizeof(struct stat));

    {
      const f_status_t status = private_f_file_stat(path, F_true, &stat_file);
      if (F_status_is_error(status)) return status;
    }

    *mode = stat_file.st_mode;

    return F_none;
  }
#endif // _di_f_file_mode_read_

#ifndef _di_f_file_mode_read_at_
  f_status_t f_file_mode_read_at(const int at_id, const f_string_static_t path, mode_t * const mode) {
    #ifndef _di_level_0_parameter_checking_
      if (!mode) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    struct stat stat_file;

    memset(&stat_file, 0, sizeof(struct stat));

    {
      const f_status_t status = private_f_file_stat(path, F_true, &stat_file);
      if (F_status_is_error(status)) return status;
    }

    *mode = stat_file.st_mode;

    return F_none;
  }
#endif // _di_f_file_mode_read_at_

#ifndef _di_f_file_mode_set_
  f_status_t f_file_mode_set(const f_string_static_t path, const mode_t mode) {
    #ifndef _di_level_0_parameter_checking_
      if (!path.used) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    return private_f_file_mode_set(path, mode);
  }
#endif // _di_f_file_mode_set_

#ifndef _di_f_file_mode_set_at_
  f_status_t f_file_mode_set_at(const int at_id, const f_string_static_t path, const mode_t mode) {

    if (!path.used) {
      return F_data_not;
    }

    return private_f_file_mode_set_at(at_id, path, mode);
  }
#endif // _di_f_file_mode_set_at_

#ifndef _di_f_file_mode_to_mode_
  f_status_t f_file_mode_to_mode(const f_file_mode_t from, mode_t * const to) {
    #ifndef _di_level_0_parameter_checking_
      if (!to) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const f_file_mode_t add = from & F_file_mode_t_mask_how_add_d;

    *to = 0;

    if (add & F_file_mode_t_mask_bit_set_owner_d) {
      *to |= F_file_mode_special_set_user_d;
    }

    if (add & F_file_mode_t_mask_bit_set_group_d) {
      *to |= F_file_mode_special_set_group_d;
    }

    if (add & F_file_mode_t_mask_bit_sticky_d) {
      *to |= F_file_mode_special_sticky_d;
    }

    if (add & F_file_mode_t_block_owner_d & F_file_mode_t_mask_bit_read_d) {
      *to |= F_file_mode_owner_r_d;
    }

    if (add & F_file_mode_t_block_group_d & F_file_mode_t_mask_bit_read_d) {
      *to |= F_file_mode_group_r_d;
    }

    if (add & F_file_mode_t_block_world_d & F_file_mode_t_mask_bit_read_d) {
      *to |= F_file_mode_world_r_d;
    }

    if (add & F_file_mode_t_block_owner_d & F_file_mode_t_mask_bit_write_d) {
      *to |= F_file_mode_owner_w_d;
    }

    if (add & F_file_mode_t_block_group_d & F_file_mode_t_mask_bit_write_d) {
      *to |= F_file_mode_group_w_d;
    }

    if (add & F_file_mode_t_block_world_d & F_file_mode_t_mask_bit_write_d) {
      *to |= F_file_mode_world_w_d;
    }

    if (add & F_file_mode_t_block_owner_d & (F_file_mode_t_mask_bit_execute_d | F_file_mode_t_mask_bit_execute_only_d)) {
      *to |= F_file_mode_owner_x_d;
    }

    if (add & F_file_mode_t_block_group_d & (F_file_mode_t_mask_bit_execute_d | F_file_mode_t_mask_bit_execute_only_d)) {
      *to |= F_file_mode_group_x_d;
    }

    if (add & F_file_mode_t_block_world_d & (F_file_mode_t_mask_bit_execute_d | F_file_mode_t_mask_bit_execute_only_d)) {
      *to |= F_file_mode_world_x_d;
    }

    return F_none;
  }
#endif // _di_f_file_mode_to_mode_

#ifndef _di_f_file_name_base_
  f_status_t f_file_name_base(const f_string_static_t path, f_string_dynamic_t * const name_base) {
    #ifndef _di_level_0_parameter_checking_
      if (!name_base) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    // POSIX basename() modifies the path, so protect it (and add a terminating NULL).
    char path_argument[path.used + 1];
    f_string_t path_to_name;

    memcpy(path_argument, path.string, sizeof(f_char_t) * path.used);
    path_argument[path.used] = 0;

    path_to_name = (f_string_t) basename(path_argument);

    const f_array_length_t size = strnlen(path_to_name, path.used);

    const f_status_t status = f_string_dynamic_increase_by(size + 1, name_base);
    if (F_status_is_error(status)) return status;

    memcpy(name_base->string + name_base->used, path_to_name, sizeof(f_char_t) * size);
    name_base->used += size;
    name_base->string[name_base->used] = 0;

    return F_none;
  }
#endif // _di_f_file_name_base_

#ifndef _di_f_file_name_directory_
  f_status_t f_file_name_directory(const f_string_static_t path, f_string_dynamic_t * const name_directory) {
    #ifndef _di_level_0_parameter_checking_
      if (!name_directory) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    // POSIX dirname() modifies the path, so protect it (and add a terminating NULL).
    char path_argument[path.used + 1];
    f_string_t path_to_name;

    memcpy(path_argument, path.string, sizeof(f_char_t) * path.used);
    path_argument[path.used] = 0;

    path_to_name = (f_string_t) dirname(path_argument);

    const f_array_length_t size = strnlen(path_to_name, path.used);

    // Do not treat '.' as a directory.
    if (size == 1 && f_string_ascii_plus_s.string[0]) {
      return F_none;
    }

    {
      const f_status_t status = f_string_dynamic_increase_by(size + 1, name_directory);
      if (F_status_is_error(status)) return status;
    }

    memcpy(name_directory->string + name_directory->used, path_to_name, sizeof(f_char_t) * size);
    name_directory->used += size;
    name_directory->string[name_directory->used] = 0;

    return F_none;
  }
#endif // _di_f_file_name_directory_

#ifndef _di_f_file_open_
  f_status_t f_file_open(const f_string_static_t path, const mode_t mode, f_file_t * const file) {
    #ifndef _di_level_0_parameter_checking_
      if (!file) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    return private_f_file_open(path, mode, file);
  }
#endif // _di_f_file_open_

#ifndef _di_f_file_open_at_
  f_status_t f_file_open_at(const int at_id, const f_string_static_t path, const mode_t mode, f_file_t * const file) {
    #ifndef _di_level_0_parameter_checking_
      if (!file) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    return private_f_file_open_at(at_id, path, mode, file);
  }
#endif // _di_f_file_open_at_

#ifndef _di_f_file_owner_read_
  f_status_t f_file_owner_read(const f_string_static_t path, uid_t * const owner) {
    #ifndef _di_level_0_parameter_checking_
      if (!owner) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    struct stat stat_file;

    memset(&stat_file, 0, sizeof(struct stat));

    {
      const f_status_t status = private_f_file_stat(path, F_true, &stat_file);
      if (F_status_is_error(status)) return status;
    }

    *owner = stat_file.st_uid;

    return F_none;
  }
#endif // _di_f_file_owner_read_

#ifndef _di_f_file_read_
  f_status_t f_file_read(const f_file_t file, f_string_dynamic_t * const buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file.id == -1) {
      return F_status_set_error(F_file_closed);
    }

    f_status_t status = F_none;
    ssize_t size_read = 0;

    do {

      status = f_string_dynamic_increase_by(file.size_read, buffer);
      if (F_status_is_error(status)) return status;

      size_read = read(file.id, buffer->string + buffer->used, file.size_read);

      if (size_read < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
        if (errno == EBADF) return F_status_set_error(F_file_descriptor);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

        return F_status_set_error(F_failure);
      }

      buffer->used += size_read;

    } while (size_read == file.size_read);

    return F_none_eof;
  }
#endif // _di_f_file_read_

#ifndef _di_f_file_read_block_
  f_status_t f_file_read_block(const f_file_t file, f_string_dynamic_t * const buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file.id == -1) {
      return F_status_set_error(F_file_closed);
    }

    ssize_t size_read = 0;

    {
      const f_status_t status = f_string_dynamic_increase_by(file.size_read, buffer);
      if (F_status_is_error(status)) return status;
    }

    size_read = read(file.id, buffer->string + buffer->used, file.size_read);

    if (size_read > 0) {
      buffer->used += size_read;
    }

    if (size_read < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

      return F_status_set_error(F_failure);
    }

    if (size_read < file.size_read) {
      return F_none_eof;
    }

    return F_none;
  }
#endif // _di_f_file_read_block_

#ifndef _di_f_file_read_until_
  f_status_t f_file_read_until(const f_file_t file, const f_array_length_t total, f_string_dynamic_t * const buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file.id == -1) {
      return F_status_set_error(F_file_closed);
    }

    f_array_length_t buffer_size = file.size_read;
    f_array_length_t buffer_count = 0;

    f_status_t status = F_none;
    ssize_t size_read = 0;

    for (;;) {

      if (buffer_count + buffer_size > total) {
        buffer_size = total - buffer_count;
      }

      status = f_string_dynamic_increase_by(buffer_size, buffer);
      if (F_status_is_error(status)) return status;

      size_read = read(file.id, buffer->string + buffer->used, buffer_size);

      if (size_read < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
        if (errno == EBADF) return F_status_set_error(F_file_descriptor);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

        return F_status_set_error(F_failure);
      }

      buffer->used += size_read;

      if (size_read < buffer_size) {
        return F_none_eof;
      }

      buffer_count += size_read;

      if (buffer_count >= total) break;
    } // for

    return F_none_stop;
  }
#endif // _di_f_file_read_until_

#ifndef _di_f_file_remove_
  f_status_t f_file_remove(const f_string_static_t path) {

    if (!path.used) {
      return F_data_not;
    }

    if (unlink(path.string) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBUSY) return F_status_set_error(F_busy);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EISDIR) return F_status_set_error(F_file_type_directory);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_file_remove_

#ifndef _di_f_file_remove_at_
  f_status_t f_file_remove_at(const int at_id, const f_string_static_t path, const int flag) {

    if (!path.used) {
      return F_data_not;
    }

    if (unlinkat(at_id, path.string, flag) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBUSY) return F_status_set_error(F_busy);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EISDIR) return F_status_set_error(F_file_type_directory);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_file_remove_at_

#ifndef _di_f_file_rename_
  f_status_t f_file_rename(const f_string_static_t source, const f_string_static_t destination) {

    if (!source.used || !destination.used) {
      return F_data_not;
    }

    if (rename(source.string, destination.string) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBUSY) return F_status_set_error(F_busy);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EISDIR) return F_status_set_error(F_file_type_directory);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == EMLINK) return F_status_set_error(F_link);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == ENOTEMPTY) return F_status_set_error(F_directory_empty_not);
      if (errno == EEXIST) return F_status_set_error(F_directory_empty_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == EXDEV) return F_status_set_error(F_mount);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_file_rename_

#ifndef _di_f_file_rename_at_
  f_status_t f_file_rename_at(const int at_id, const int to_id, const f_string_static_t source, const f_string_static_t destination) {

    if (!source.used || !destination.used) {
      return F_data_not;
    }

    if (renameat(at_id, source.string, to_id, destination.string) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBUSY) return F_status_set_error(F_busy);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EISDIR) return F_status_set_error(F_file_type_directory);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == EMLINK) return F_status_set_error(F_link);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == ENOTEMPTY) return F_status_set_error(F_directory_empty_not);
      if (errno == EEXIST) return F_status_set_error(F_directory_empty_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == EXDEV) return F_status_set_error(F_mount);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_file_rename_at_

#ifndef _di_f_file_role_change_
  f_status_t f_file_role_change(const f_string_static_t path, const uid_t uid, const gid_t gid, const bool dereference) {

    if (uid == -1 && gid == -1 || !path.used) {
      return F_data_not;
    }

    return private_f_file_role_change(path, uid, gid, dereference);
  }
#endif // _di_f_file_role_change_

#ifndef _di_f_file_role_change_at_
  f_status_t f_file_role_change_at(const int at_id, const f_string_static_t path, const uid_t uid, const gid_t gid, const int flag) {

    if (uid == -1 && gid == -1) {
      return F_data_not;
    }

    return private_f_file_role_change_at(at_id, path, uid, gid, flag);
  }
#endif // _di_f_file_role_change_at_

#ifndef _di_f_file_seek_
  f_status_t f_file_seek(const int id, const int whence, const off_t offset, off_t * const seeked) {
    #ifndef _di_level_0_parameter_checking_
      if (id <= 0) return F_status_set_error(F_parameter);
      if (whence < 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    *seeked = lseek(id, offset, whence);

    if (*seeked < 0) {
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENXIO) return F_status_set_error(F_bound_not);
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == ESPIPE) return F_status_set_error(F_file_type_pipe);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_file_seek_

#ifndef _di_f_file_size_
  f_status_t f_file_size(const f_string_static_t path, const bool dereference, off_t * const size) {
    #ifndef _di_level_0_parameter_checking_
      if (!size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    struct stat stat_file;

    memset(&stat_file, 0, sizeof(struct stat));

    {
      const f_status_t status = private_f_file_stat(path, dereference, &stat_file);
      if (F_status_is_error(status)) return status;
    }

    *size = stat_file.st_size;

    return F_none;
  }
#endif // _di_f_file_size_

#ifndef _di_f_file_size_at_
  f_status_t f_file_size_at(const int at_id, const f_string_static_t path, const bool dereference, off_t * const size) {
    #ifndef _di_level_0_parameter_checking_
      if (!size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    struct stat stat_file;

    memset(&stat_file, 0, sizeof(struct stat));

    {
      const f_status_t status = private_f_file_stat_at(at_id, path, dereference, &stat_file);
      if (F_status_is_error(status)) return status;
    }

    *size = stat_file.st_size;

    return F_none;
  }
#endif // _di_f_file_size_at_

#ifndef _di_f_file_size_by_id_
  f_status_t f_file_size_by_id(const int id, off_t * const size) {
    #ifndef _di_level_0_parameter_checking_
      if (id <= 0) return F_status_set_error(F_parameter);
      if (!size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    struct stat stat_file;

    memset(&stat_file, 0, sizeof(struct stat));

    {
      const f_status_t status = private_f_file_stat_by_id(id, &stat_file);
      if (F_status_is_error(status)) return status;
    }

    *size = stat_file.st_size;

    return F_none;
  }
#endif // _di_f_file_size_by_id_

#ifndef _di_f_file_stat_
  f_status_t f_file_stat(const f_string_static_t path, const bool dereference, struct stat * const stat_file) {
    #ifndef _di_level_0_parameter_checking_
      if (!stat_file) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    return private_f_file_stat(path, dereference, stat_file);
  }
#endif // _di_f_file_stat_

#ifndef _di_f_file_stat_at_
  f_status_t f_file_stat_at(const int at_id, const f_string_static_t path, const int flag, struct stat * const stat_file) {
    #ifndef _di_level_0_parameter_checking_
      if (!stat_file) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    return private_f_file_stat_at(at_id, path, flag, stat_file);
  }
#endif // _di_f_file_stat_at_

#ifndef _di_f_file_stat_by_id_
  f_status_t f_file_stat_by_id(const int id, struct stat * const stat_file) {
    #ifndef _di_level_0_parameter_checking_
      if (id <= 0) return F_status_set_error(F_parameter);
      if (!stat_file) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_stat_by_id(id, stat_file);
  }
#endif // _di_f_file_stat_by_id_

#ifndef _di_f_file_stream_close_
  f_status_t f_file_stream_close(const bool complete, f_file_t * const file) {
    #ifndef _di_level_0_parameter_checking_
      if (!file) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file->stream) {
      if (fclose(file->stream) == EOF) {
        if (errno == EACCES) return F_status_set_error(F_access_denied);
        if (errno == EAGAIN) return F_status_set_error(F_prohibited);
        if (errno == EBADF) return F_status_set_error(F_file_descriptor);
        if (errno == EFBIG) return F_status_set_error(F_file_overflow);
        if (errno == EDEADLK) return F_status_set_error(F_deadlock);
        if (errno == EDESTADDRREQ) return F_status_set_error(F_socket_not);
        if (errno == EDQUOT) return F_status_set_error(F_space_not);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
        if (errno == ENOLCK) return F_status_set_error(F_lock);
        if (errno == ENOSPC) return F_status_set_error(F_space_not);
        if (errno == ENOTDIR) return F_status_set_error(F_file_type_not_directory);
        if (errno == EPERM) return F_status_set_error(F_prohibited);
        if (errno == EPIPE) return F_status_set_error(F_pipe_not);
        if (errno == EWOULDBLOCK) return F_status_set_error(F_block);

        return F_status_set_error(F_failure);
      }

      file->stream = 0;

      // File stream will result in the file descriptor being invalid because it is already closed.
      if (complete) {
        file->id = -1;
      }

      return F_none;
    }

    if (complete) {
      return private_f_file_close(&file->id, F_true);
    }

    return F_none;
  }
#endif // _di_f_file_stream_close_

#ifndef _di_f_file_stream_descriptor_
  f_status_t f_file_stream_descriptor(const f_string_static_t mode, f_file_t * const file) {
    #ifndef _di_level_0_parameter_checking_
      if (!file) return F_status_set_error(F_parameter);
      if (file->id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (mode.string) {
      file->stream = fdopen(file->id, mode.string);
    }
    else {
      file->stream = fdopen(file->id, private_f_file_stream_open_mode_determine(file->flag));
    }

    if (!file->stream) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EAGAIN) return F_status_set_error(F_prohibited);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EDEADLK) return F_status_set_error(F_deadlock);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENOLCK) return F_status_set_error(F_lock);
      if (errno == ENOTDIR) return F_status_set_error(F_file_type_not_directory);
      if (errno == EPERM) return F_status_set_error(F_prohibited);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_file_stream_descriptor_


#ifndef _di_f_file_stream_open_
  f_status_t f_file_stream_open(const f_string_static_t path, const f_string_static_t mode, f_file_t * const file) {
    #ifndef _di_level_0_parameter_checking_
      if (!file) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (mode.used) {
      file->stream = fopen(path.string, mode.string);
    }
    else {
      file->stream = fopen(path.string, private_f_file_stream_open_mode_determine(file->flag));
    }

    if (!file->stream) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EFBIG || errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOTDIR) return F_status_set_error(F_file_type_not_directory);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOSPC) return F_status_set_error(F_space_not);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == ETXTBSY) return F_status_set_error(F_busy);
      if (errno == EISDIR) return F_status_set_error(F_directory);
      if (errno == EOPNOTSUPP) return F_status_set_error(F_supported_not);

      return F_status_set_error(F_failure);
    }

    file->id = fileno(file->stream);

    if (file->id == -1) {
      return F_status_set_error(F_file_descriptor);
    }

    return F_none;
  }
#endif // _di_f_file_stream_open_

#ifndef _di_f_file_stream_read_
  f_status_t f_file_stream_read(const f_file_t file, f_string_dynamic_t * const buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!file.stream) {
      return F_status_set_error(F_file_closed);
    }

    flockfile(file.stream);

    if (feof(file.stream)) {
      funlockfile(file.stream);

      return F_none_eof;
    }

    if (ferror(file.stream)) {
      funlockfile(file.stream);

      return F_status_set_error(F_failure); // @todo create F_error and return F_error.
    }

    f_status_t status = F_none;
    size_t size_read = 0;

    do {
      status = f_string_dynamic_increase_by(file.size_read, buffer);

      if (F_status_is_error(status)) {
        funlockfile(file.stream);

        return status;
      }

      size_read = fread_unlocked(buffer->string + buffer->used, sizeof(f_char_t), file.size_read, file.stream);

      if (ferror(file.stream)) {
        funlockfile(file.stream);

        if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
        if (errno == EBADF) return F_status_set_error(F_file_descriptor);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

        return F_status_set_error(F_failure);
      }

      buffer->used += size_read;

    } while (size_read == file.size_read && !feof(file.stream));

    funlockfile(file.stream);

    return F_none_eof;
  }
#endif // _di_f_file_stream_read_

#ifndef _di_f_file_stream_read_block_
  f_status_t f_file_stream_read_block(const f_file_t file, f_string_dynamic_t * const buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (!file.size_read) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!file.stream) return F_status_set_error(F_file_closed);

    if (feof(file.stream)) {
      return F_none_eof;
    }

    if (ferror(file.stream)) {
      return F_status_set_error(F_failure); // @todo create F_error and return F_error.
    }

    {
      const f_status_t status = f_string_dynamic_increase_by(file.size_read, buffer);
      if (F_status_is_error(status)) return status;
    }

    const size_t size_read = fread(buffer->string + buffer->used, sizeof(f_char_t), file.size_read, file.stream);

    if (ferror(file.stream)) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

      return F_status_set_error(F_failure);
    }

    if (size_read) {
      buffer->used += size_read;
    }

    if (feof(file.stream)) {
      return F_none_eof;
    }

    return F_none;
  }
#endif // _di_f_file_stream_read_block_

#ifndef _di_f_file_stream_read_until_
  f_status_t f_file_stream_read_until(const f_file_t file, const f_array_length_t total, f_string_dynamic_t * const buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!file.stream) return F_status_set_error(F_file_closed);

    flockfile(file.stream);

    if (feof(file.stream)) {
      funlockfile(file.stream);

      return F_none_eof;
    }

    if (ferror(file.stream)) {
      funlockfile(file.stream);

      return F_status_set_error(F_failure); // @todo create F_error and return F_error.
    }

    {
      const f_status_t status = f_string_dynamic_increase_by(total, buffer);

      if (F_status_is_error(status)) {
        funlockfile(file.stream);

        return F_none_eof;
      }
    }

    f_array_length_t buffer_size = file.size_read;
    f_array_length_t buffer_count = 0;

    size_t size_read = 0;

    for (;;) {

      if (buffer_count + buffer_size > total) {
        buffer_size = total - buffer_count;
      }

      size_read = fread(buffer->string + buffer->used, sizeof(f_char_t), file.size_read, file.stream);

      if (ferror(file.stream)) {
        funlockfile(file.stream);

        if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
        if (errno == EBADF) return F_status_set_error(F_file_descriptor);
        if (errno == EFAULT) return F_status_set_error(F_buffer);
        if (errno == EINTR) return F_status_set_error(F_interrupt);
        if (errno == EINVAL) return F_status_set_error(F_parameter);
        if (errno == EIO) return F_status_set_error(F_input_output);
        if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

        return F_status_set_error(F_failure);
      }

      buffer->used += size_read;

      if (feof(file.stream)) {
        funlockfile(file.stream);

        return F_none_eof;
      }

      buffer_count += size_read;

      if (buffer_count >= total) break;
    } // for

    funlockfile(file.stream);

    return F_none_stop;
  }
#endif // _di_f_file_stream_read_until_

#ifndef _di_f_file_stream_reopen_
  f_status_t f_file_stream_reopen(const f_string_static_t path, const f_string_static_t mode, f_file_t * const file) {
    #ifndef _di_level_0_parameter_checking_
      if (!file) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    FILE *result = 0;

    if (mode.used) {
      result = freopen(path.string, mode.string, file->stream);
    }
    else {
      result = freopen(path.string, private_f_file_stream_open_mode_determine(file->flag), file->stream);
    }

    if (!result) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EAGAIN) return F_status_set_error(F_prohibited);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EDEADLK) return F_status_set_error(F_deadlock);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupt);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENOLCK) return F_status_set_error(F_lock);
      if (errno == ENOTDIR) return F_status_set_error(F_file_type_not_directory);
      if (errno == EPERM) return F_status_set_error(F_prohibited);

      return F_status_set_error(F_failure);
    }

    file->id = fileno(file->stream);

    if (file->id == -1) {
      return F_status_set_error(F_file_descriptor);
    }

    return F_none;
  }
#endif // _di_f_file_stream_reopen_

#ifndef _di_f_file_stream_write_
  f_status_t f_file_stream_write(const f_file_t file, const f_string_static_t buffer, f_array_length_t * const written) {
    #ifndef _di_level_0_parameter_checking_
      if (!file.size_write) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!file.stream) {
      return F_status_set_error(F_file_closed);
    }

    if (!buffer.used) {
      if (written) {
        *written = 0;
      }

      return F_data_not;
    }

    f_status_t status = F_none;

    if (written) {
      private_f_file_stream_write_until(file, buffer, buffer.used, written);

      if (status == F_none && *written == buffer.used) {
        return F_none_eos;
      }
    }
    else {
      f_array_length_t written_local = 0;

      private_f_file_stream_write_until(file, buffer, buffer.used, &written_local);

      if (status == F_none && written_local == buffer.used) {
        return F_none_eos;
      }
    }

    if (F_status_is_error(status)) {
      return F_status_set_error(status);
    }

    return status;
  }
#endif // _di_f_file_stream_write_

#ifndef _di_f_file_stream_write_block_
  f_status_t f_file_stream_write_block(const f_file_t file, const f_string_static_t buffer, f_array_length_t * const written) {
    #ifndef _di_level_0_parameter_checking_
      if (!file.size_write) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!file.stream) {
      return F_status_set_error(F_file_closed);
    }

    if (!buffer.used) {
      if (written) {
        *written = 0;
      }

      return F_data_not;
    }

    f_array_length_t write_max = file.size_write;

    if (write_max > buffer.used) {
      write_max = buffer.used;
    }

    f_status_t status = F_none;

    if (written) {
      private_f_file_stream_write_until(file, buffer, write_max, written);

      if (status == F_none) {
        if (*written == buffer.used) {
          return F_none_eos;
        }

        if (*written == write_max) {
          return F_none_stop;
        }
      }
    }
    else {
      f_array_length_t written_local = 0;

      private_f_file_stream_write_until(file, buffer, write_max, &written_local);

      if (status == F_none) {
        if (written_local == buffer.used) {
          return F_none_eos;
        }

        if (written_local == write_max) {
          return F_none_stop;
        }
      }
    }

    return status;
  }
#endif // _di_f_file_stream_write_block_

#ifndef _di_f_file_stream_write_until_
  f_status_t f_file_stream_write_until(const f_file_t file, const f_string_static_t buffer, const f_array_length_t total, f_array_length_t * const written) {
    #ifndef _di_level_0_parameter_checking_
      if (!file.size_write) return F_status_set_error(F_parameter);
      if (!total) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!file.stream) {
      return F_status_set_error(F_file_closed);
    }

    if (!buffer.used || !total) {
      if (written) {
        *written = 0;
      }

      return F_data_not;
    }

    f_array_length_t write_max = total;

    if (write_max > buffer.used) {
      write_max = buffer.used;
    }

    f_status_t status = F_none;

    if (written) {
      private_f_file_stream_write_until(file, buffer, write_max, written);

      if (status == F_none) {
        if (*written == buffer.used) {
          return F_none_eos;
        }

        if (*written == write_max) {
          return F_none_stop;
        }
      }
    }
    else {
      f_array_length_t written_local = 0;

      private_f_file_stream_write_until(file, buffer, buffer.used, &written_local);

      if (status == F_none) {
        if (written_local == buffer.used) {
          return F_none_eos;
        }

        if (written_local == write_max) {
          return F_none_stop;
        }
      }
    }

    return status;
  }
#endif // _di_f_file_stream_write_until_

#ifndef _di_f_file_stream_write_range_
  f_status_t f_file_stream_write_range(const f_file_t file, const f_string_static_t buffer, const f_string_range_t range, f_array_length_t * const written) {
    #ifndef _di_level_0_parameter_checking_
      if (!file.size_write) return F_status_set_error(F_parameter);
      if (range.start >= buffer.used) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!file.stream) {
      return F_status_set_error(F_file_closed);
    }

    if (!buffer.used || range.start >= buffer.used) {
      if (written) {
        *written = 0;
      }

      return F_data_not;
    }

    const f_array_length_t total = (range.stop - range.start) + 1;
    f_array_length_t write_max = total;

    if (write_max > buffer.used) {
      write_max = buffer.used;
    }

    f_status_t status = F_none;

    if (written) {
      const f_string_static_t buffer_adjusted = macro_f_string_static_t_initialize(buffer.string + range.start, 0, buffer.used - range.start);

      private_f_file_stream_write_until(file, buffer_adjusted, write_max, written);

      if (status == F_none) {
        if (range.start + *written == buffer.used) {
          return F_none_stop;
        }

        if (range.start + *written == total) {
          return F_none_eos;
        }
      }
    }
    else {
      const f_string_static_t buffer_adjusted = macro_f_string_static_t_initialize(buffer.string + range.start, 0, buffer.used - range.start);
      f_array_length_t written_local = 0;

      private_f_file_stream_write_until(file, buffer_adjusted, write_max, &written_local);

      if (status == F_none) {
        if (range.start + written_local == buffer.used) {
          return F_none_eos;
        }

        if (range.start + written_local == total) {
          return F_none_stop;
        }
      }
    }

    return status;
  }
#endif // _di_f_file_stream_write_range_

#ifndef _di_f_file_touch_
  f_status_t f_file_touch(const f_string_static_t path, const mode_t mode, const bool dereference) {

    if (!path.used) {
      return F_data_not;
    }

    f_status_t status = F_none;
    struct stat stat_file;

    memset(&stat_file, 0, sizeof(struct stat));

    status = private_f_file_stat(path, F_false, &stat_file);

    if (F_status_set_fine(status) == F_file_found_not) {
      return private_f_file_create(path, mode, dereference);
    }

    if (F_status_is_error(status)) {
      return status;
    }

    if (utimensat(F_file_at_current_working_d, path.string, 0, dereference ? 0 : F_file_at_symlink_follow_no_d) < 0) {
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
#endif // _di_f_file_touch_

#ifndef _di_f_file_touch_at_
  f_status_t f_file_touch_at(const int at_id, const f_string_static_t path, const mode_t mode, const int flag) {

    if (!path.used) {
      return F_data_not;
    }

    f_status_t status = F_none;
    struct stat stat_file;

    memset(&stat_file, 0, sizeof(struct stat));

    status = private_f_file_stat_at(at_id, path, flag, &stat_file);

    if (F_status_set_fine(status) == F_file_found_not) {
      return private_f_file_create_at(at_id, path, mode, F_false);
    }

    if (F_status_is_error(status)) return status;

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
#endif // _di_f_file_touch_at_

#ifndef _di_f_file_type_
  f_status_t f_file_type(const f_string_static_t path, int * const type) {
    #ifndef _di_level_0_parameter_checking_
      if (!type) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    struct stat stat_file;

    memset(&stat_file, 0, sizeof(struct stat));

    if (stat(path.string, &stat_file) < 0) {
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == ENOENT) return F_file_found_not;
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == ELOOP) return F_status_set_error(F_loop);

      return F_status_set_error(F_file_stat);
    }

    *type = macro_f_file_type_get(stat_file.st_mode);

    return F_none;
  }
#endif // _di_f_file_type_

#ifndef _di_f_file_type_at_
  f_status_t f_file_type_at(const int at_id, const f_string_static_t path, const int flag, int * const type) {
    #ifndef _di_level_0_parameter_checking_
      if (!type) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!path.used) {
      return F_data_not;
    }

    struct stat stat_file;

    memset(&stat_file, 0, sizeof(struct stat));

    if (fstatat(at_id, path.string, &stat_file, flag) < 0) {
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == ENOENT) return F_file_found_not;
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);

      return F_status_set_error(F_file_stat);
    }

    *type = macro_f_file_type_get(stat_file.st_mode);

    return F_none;
  }
#endif // _di_f_file_type_at_

#ifndef _di_f_file_umask_get_
  f_status_t f_file_umask_get(mode_t * const mask) {

    // Bad design in POSIX where there is no get umask without setting it.
    *mask = umask(0);

    // Restore umask.
    umask(*mask);

    return F_none;
  }
#endif // _di_f_file_umask_get_

#ifndef _di_f_file_umask_set_
  f_status_t f_file_umask_set(const mode_t mask) {

    umask(mask);

    return F_none;
  }
#endif // _di_f_file_umask_set_

#ifndef _di_f_file_write_
  f_status_t f_file_write(const f_file_t file, const f_string_static_t buffer, f_array_length_t * const written) {
    #ifndef _di_level_0_parameter_checking_
      if (!file.size_write) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file.id == -1) {
      return F_status_set_error(F_file_closed);
    }

    if (!buffer.used) {
      if (written) *written = 0;

      return F_data_not;
    }

    f_status_t status = F_none;

    if (written) {
      private_f_file_write_until(file, buffer, buffer.used, written);

      if (status == F_none && *written == buffer.used) {
        return F_none_eos;
      }
    }
    else {
      f_array_length_t written_local = 0;

      private_f_file_write_until(file, buffer, buffer.used, &written_local);

      if (status == F_none && written_local == buffer.used) {
        return F_none_eos;
      }
    }

    if (F_status_is_error(status)) {
      return F_status_set_error(status);
    }

    return status;
  }
#endif // _di_f_file_write_

#ifndef _di_f_file_write_block_
  f_status_t f_file_write_block(const f_file_t file, const f_string_static_t buffer, f_array_length_t * const written) {
    #ifndef _di_level_0_parameter_checking_
      if (!file.size_write) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file.id == -1) {
      return F_status_set_error(F_file_closed);
    }

    if (!buffer.used) {
      if (written) *written = 0;

      return F_data_not;
    }

    f_array_length_t write_max = file.size_write;

    if (write_max > buffer.used) {
      write_max = buffer.used;
    }

    f_status_t status = F_none;

    if (written) {
      private_f_file_write_until(file, buffer, write_max, written);

      if (status == F_none) {
        if (*written == buffer.used) {
          return F_none_eos;
        }

        if (*written == write_max) {
          return F_none_stop;
        }
      }
    }
    else {
      f_array_length_t written_local = 0;

      private_f_file_write_until(file, buffer, write_max, &written_local);

      if (status == F_none) {
        if (written_local == buffer.used) {
          return F_none_eos;
        }

        if (written_local == write_max) {
          return F_none_stop;
        }
      }
    }

    return status;
  }
#endif // _di_f_file_write_block_

#ifndef _di_f_file_write_until_
  f_status_t f_file_write_until(const f_file_t file, const f_string_static_t buffer, const f_array_length_t total, f_array_length_t * const written) {
    #ifndef _di_level_0_parameter_checking_
      if (!file.size_write) return F_status_set_error(F_parameter);
      if (!total) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file.id == -1) {
      return F_status_set_error(F_file_closed);
    }

    if (!buffer.used || !total) {
      if (written) *written = 0;

      return F_data_not;
    }

    f_array_length_t write_max = total;

    if (write_max > buffer.used) {
      write_max = buffer.used;
    }

    f_status_t status = F_none;

    if (written) {
      private_f_file_write_until(file, buffer, write_max, written);

      if (status == F_none) {
        if (*written == buffer.used) {
          return F_none_eos;
        }

        if (*written == write_max) {
          return F_none_stop;
        }
      }
    }
    else {
      f_array_length_t written_local = 0;

      private_f_file_write_until(file, buffer, buffer.used, &written_local);

      if (status == F_none) {
        if (written_local == buffer.used) {
          return F_none_eos;
        }

        if (written_local == write_max) {
          return F_none_stop;
        }
      }
    }

    return status;
  }
#endif // _di_f_file_write_until_

#ifndef _di_f_file_write_range_
  f_status_t f_file_write_range(const f_file_t file, const f_string_static_t buffer, const f_string_range_t range, f_array_length_t * const written) {
    #ifndef _di_level_0_parameter_checking_
      if (!file.size_write) return F_status_set_error(F_parameter);
      if (range.start >= buffer.used) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file.id == -1) {
      return F_status_set_error(F_file_closed);
    }

    if (!buffer.used || range.start >= buffer.used) {
      if (written) {
        *written = 0;
      }

      return F_data_not;
    }

    const f_array_length_t total = (range.stop - range.start) + 1;
    f_array_length_t write_max = total;

    if (write_max > buffer.used) {
      write_max = buffer.used;
    }

    f_status_t status = F_none;

    if (written) {
      const f_string_static_t buffer_adjusted = macro_f_string_static_t_initialize(buffer.string + range.start, 0, buffer.used - range.start);

      private_f_file_write_until(file, buffer_adjusted, write_max, written);

      if (status == F_none) {
        if (range.start + *written == buffer.used) {
          return F_none_stop;
        }

        if (range.start + *written == total) {
          return F_none_eos;
        }
      }
    }
    else {
      const f_string_static_t buffer_adjusted = macro_f_string_static_t_initialize(buffer.string + range.start, 0, buffer.used - range.start);
      f_array_length_t written_local = 0;

      private_f_file_write_until(file, buffer_adjusted, write_max, &written_local);

      if (status == F_none) {
        if (range.start + written_local == buffer.used) {
          return F_none_eos;
        }

        if (range.start + written_local == total) {
          return F_none_stop;
        }
      }
    }

    return status;
  }
#endif // _di_f_file_write_range_

#ifdef __cplusplus
} // extern "C"
#endif
