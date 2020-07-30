#include <level_0/file.h>
#include "private-file.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_file_access_
  f_return_status f_file_access(const f_string path) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (access(path, F_OK)) {
      if (errno == ENOENT) return F_false;
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == ELOOP) return F_status_set_error(F_loop);

      return F_status_set_error(F_false);
    }

    return F_true;
  }
#endif // _di_f_file_access_

#ifndef _di_f_file_change_mode_
  f_return_status f_file_change_mode(const f_string path, const mode_t mode) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_change_mode(path, mode);
  }
#endif // _di_f_file_change_mode_

#ifndef _di_f_file_change_mode_at_
  f_return_status f_file_change_mode_at(const int at_id, const f_string path, const mode_t mode) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_change_mode_at(at_id, path, mode);
  }
#endif // _di_f_file_change_mode_at_

#ifndef _di_f_file_change_role_
  f_return_status f_file_change_role(const f_string path, const uid_t uid, const gid_t gid, const bool dereference) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
      if (uid < 0 && gid < 0) return F_status_set_error(F_parameter);
      if (uid < -1 || gid < -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_change_role(path, uid, gid, dereference);
  }
#endif // _di_f_file_change_role_

#ifndef _di_f_file_change_role_at_
  f_return_status f_file_change_role_at(const int at_id, const f_string path, const uid_t uid, const gid_t gid, const int flag) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
      if (uid < 0 && gid < 0) return F_status_set_error(F_parameter);
      if (uid < -1 || gid < -1) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_change_role_at(at_id, path, uid, gid, flag);
  }
#endif // _di_f_file_change_role_at_

#ifndef _di_f_file_clone_
  f_return_status f_file_clone(const f_string source, const f_string destination, const bool role, const f_number_unsigned size_block, const bool exclusive) {
    #ifndef _di_level_0_parameter_checking_
      if (source == 0) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = F_none;
    struct stat source_stat;

    memset(&source_stat, 0, sizeof(struct stat));

    status = private_f_file_stat(source, F_false, &source_stat);
    if (F_status_is_error(status)) return status;

    if (f_macro_file_type_is_regular(source_stat.st_mode)) {
      status = private_f_file_create(destination, source_stat.st_mode, exclusive);
      if (F_status_is_error(status)) return status;

      if (!exclusive) {
        status = private_f_file_change_mode(destination, source_stat.st_mode);
        if (F_status_is_error(status)) return status;
      }

      if (role) {
        status = private_f_file_change_role(destination, source_stat.st_uid, source_stat.st_gid, F_false);
        if (F_status_is_error(status)) return status;
      }

      return private_f_file_copy_content(source, destination, size_block == 0 ? f_file_default_read_size : size_block);
    }
    else if (f_macro_file_type_is_link(source_stat.st_mode)) {
      status = private_f_file_link(destination, source);
      if (F_status_set_fine(status) == F_file_found) {
        if (exclusive) return status;
      }
      else if (F_status_is_error(status)) {
        return status;
      }

      status = private_f_file_change_mode(destination, source_stat.st_mode);
      if (F_status_is_error(status)) return status;

      if (role) {
        status = private_f_file_change_role(destination, source_stat.st_uid, source_stat.st_gid, F_false);
        if (F_status_is_error(status)) return status;
      }

      return F_none;
    }

    return F_unsupported;
  }
#endif // _di_f_file_clone_

#ifndef _di_f_file_close_
  f_return_status f_file_close(int *id) {
    #ifndef _di_level_0_parameter_checking_
      if (id == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_close(id);
  }
#endif // _di_f_file_close_

#ifndef _di_f_file_copy_
  f_return_status f_file_copy(const f_string source, const f_string destination, const f_mode mode, const f_number_unsigned size_block, const bool exclusive) {
    #ifndef _di_level_0_parameter_checking_
      if (source == 0) return F_status_set_error(F_parameter);
      if (destination == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = F_none;
    struct stat source_stat;

    memset(&source_stat, 0, sizeof(struct stat));

    status = private_f_file_stat(source, F_false, &source_stat);
    if (F_status_is_error(status)) return status;

    if (f_macro_file_type_is_regular(source_stat.st_mode)) {

      status = private_f_file_create(destination, (~f_file_type_mask) & mode.regular, exclusive);
      if (F_status_is_error(status)) return status;

      if (!exclusive) {
        status = private_f_file_change_mode(destination, (~f_file_type_mask) & mode.regular);
        if (F_status_is_error(status)) return status;
      }

      return private_f_file_copy_content(source, destination, size_block == 0 ? f_file_default_read_size : size_block);
    }
    else if (f_macro_file_type_is_directory(source_stat.st_mode)) {
      status = private_f_file_create_directory(destination, (~f_file_type_mask) & mode.directory);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) != F_file_found || exclusive) {
          return status;
        }
      }

      status = private_f_file_change_mode(destination, (~f_file_type_mask) & mode.directory);
      if (F_status_is_error(status)) return status;

      return F_none;
    }
    else if (f_macro_file_type_is_link(source_stat.st_mode)) {
      f_string_dynamic target = f_string_dynamic_initialize;

      status = private_f_file_link_read(source, source_stat, &target);
      if (F_status_is_error(status)) {
        f_macro_string_dynamic_delete_simple(target);
        return status;
      }

      status = private_f_file_link(target.string, destination);

      f_macro_string_dynamic_delete_simple(target);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) != F_file_found || exclusive) {
          return status;
        }
      }

      return F_none;
    }
    else if (f_macro_file_type_is_fifo(source_stat.st_mode)) {
      status = private_f_file_create_fifo(destination, (~f_file_type_mask) & mode.fifo);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) != F_file_found || exclusive) {
          return status;
        }
      }

      status = private_f_file_change_mode(destination, (~f_file_type_mask) & mode.fifo);
      if (F_status_is_error(status)) return status;

      return F_none;
    }
    else if (f_macro_file_type_is_socket(source_stat.st_mode)) {
      status = private_f_file_create_node(destination, f_macro_file_type_get(source_stat.st_mode) | (~f_file_type_mask) & mode.socket, source_stat.st_rdev);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) != F_file_found || exclusive) {
          return status;
        }
      }

      status = private_f_file_change_mode(destination, (~f_file_type_mask) & mode.socket);
      if (F_status_is_error(status)) return status;

      return F_none;
    }
    else if (f_macro_file_type_is_block(source_stat.st_mode) || f_macro_file_type_is_character(source_stat.st_mode)) {
      status = private_f_file_create_node(destination, f_macro_file_type_get(source_stat.st_mode) | (~f_file_type_mask) & mode.block, source_stat.st_rdev);

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) != F_file_found || exclusive) {
          return status;
        }
      }

      status = private_f_file_change_mode(destination, (~f_file_type_mask) & mode.block);
      if (F_status_is_error(status)) return status;

      return F_none;
    }

    return F_unsupported;
  }
#endif // _di_f_file_copy_

#ifndef _di_f_file_create_
  f_return_status f_file_create(const f_string path, const mode_t mode, const bool exclusive) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_create(path, mode, exclusive);
  }
#endif // _di_f_file_create_

#ifndef _di_f_file_create_at_
  f_return_status f_file_create_at(const int at_id, const f_string path, const mode_t mode, const bool exclusive) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_create_at(at_id, path, mode, exclusive);
  }
#endif // _di_f_file_create_at_

#ifndef _di_f_file_create_device_
  f_return_status f_file_create_device(const f_string path, const mode_t mode, const unsigned int major, const unsigned int minor) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_


    if (!f_macro_file_type_is_fifo(mode) && !f_macro_file_type_is_character(mode) && !f_macro_file_type_is_block(mode)) {
      return F_status_set_error(F_unsupported);
    }

    const dev_t device = makedev(major, minor);

    return private_f_file_create_node(path, mode, device);
  }
#endif // _di_f_file_create_device_

#ifndef _di_f_file_create_device_at_
  f_return_status f_file_create_device_at(const int at_id, const f_string path, const mode_t mode, const unsigned int major, const unsigned int minor) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!f_macro_file_type_is_fifo(mode) && !f_macro_file_type_is_character(mode) && !f_macro_file_type_is_block(mode)) {
      return F_status_set_error(F_unsupported);
    }

    const dev_t device = makedev(major, minor);

    return private_f_file_create_node_at(at_id, path, mode, device);
  }
#endif // _di_f_file_create_device_at_

#ifndef _di_f_file_create_fifo_
  f_return_status f_file_create_fifo(const f_string path, const mode_t mode) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_create_fifo(path, mode);
  }
#endif // _di_f_file_create_fifo_

#ifndef _di_f_file_create_fifo_at_
  f_return_status f_file_create_fifo_at(const int at_id, const f_string path, const mode_t mode) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_create_fifo_at(at_id, path, mode);
  }
#endif // _di_f_file_create_fifo_at_

#ifndef _di_f_file_create_node_
  f_return_status f_file_create_node(const f_string path, const mode_t mode, const dev_t device) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!f_macro_file_type_is_fifo(mode) && !f_macro_file_type_is_character(mode) && !f_macro_file_type_is_block(mode)) {
      return F_status_set_error(F_unsupported);
    }

    return private_f_file_create_node(path, mode, device);
  }
#endif // _di_f_file_create_node_

#ifndef _di_f_file_create_node_at_
  f_return_status f_file_create_node_at(const int at_id, const f_string path, const mode_t mode, const dev_t device) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!f_macro_file_type_is_fifo(mode) && !f_macro_file_type_is_character(mode) && !f_macro_file_type_is_block(mode)) {
      return F_status_set_error(F_unsupported);
    }

    return private_f_file_create_node_at(at_id, path, mode, device);
  }
#endif // _di_f_file_create_node_at_

#ifndef _di_f_file_exists_
  f_return_status f_file_exists(const f_string path) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = F_none;
    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    status = private_f_file_stat(path, F_false, &file_stat);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_file_found_not) return F_false;

      return status;
    }

    return F_true;
  }
#endif // _di_f_file_exists_

#ifndef _di_f_file_exists_at_
  f_return_status f_file_exists_at(const int at_id, const f_string path, const int flag) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = F_none;
    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    status = private_f_file_stat_at(at_id, path, flag, &file_stat);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_file_found_not) return F_false;

      return status;
    }

    return F_true;
  }
#endif // _di_f_file_exists_at_

#ifndef _di_f_file_flush_
  f_return_status f_file_flush(const int id) {
    return private_f_file_flush(id);
  }
#endif // _di_f_file_flush_

#ifndef _di_f_file_is_
  f_return_status f_file_is(const f_string path, const int type) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    if (stat(path, &file_stat) < 0) {
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == ENOENT) return F_file_found_not;
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == ELOOP) return F_status_set_error(F_loop);

      return F_status_set_error(F_file_stat);
    }

    if (f_macro_file_type_get(file_stat.st_mode) == type) return F_true;

    return F_false;
  }
#endif // _di_f_file_is_

#ifndef _di_f_file_is_at_
  f_return_status f_file_is_at(const int at_id, const f_string path, const int type, const int flag) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    if (fstatat(at_id, path, &file_stat, flag) < 0) {
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == ENOENT) return F_file_found_not;
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);

      return F_status_set_error(F_file_stat);
    }

    if (file_stat.st_mode == (S_IFMT & S_IFDIR)) return F_true;

    return F_false;
  }
#endif // _di_f_file_is_at_

#ifndef _di_f_file_link_
  f_return_status f_file_link(const f_string target, const f_string point) {
    #ifndef _di_level_0_parameter_checking_
      if (target == 0) return F_status_set_error(F_parameter);
      if (point == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_link(target, point);
  }
#endif // _di_f_file_link_

#ifndef _di_f_file_link_at_
  f_return_status f_file_link_at(const int at_id, const f_string target, const f_string point) {
    #ifndef _di_level_0_parameter_checking_
      if (target == 0) return F_status_set_error(F_parameter);
      if (point == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_link_at(at_id, target, point);
  }
#endif // _di_f_file_link_at_

#ifndef _di_f_file_link_hard_
  f_return_status f_file_link_hard(const f_string target, const f_string point) {
    #ifndef _di_level_0_parameter_checking_
      if (target == 0) return F_status_set_error(F_parameter);
      if (point == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (link(target, point) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EFBIG || errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == EINTR) return F_status_set_error(F_interrupted);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
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
  f_return_status f_file_link_hard_at(const int at_id_target, const int at_id_point, const f_string target, const f_string point, const int flag) {
    #ifndef _di_level_0_parameter_checking_
      if (target == 0) return F_status_set_error(F_parameter);
      if (point == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (linkat(at_id_target, target, at_id_point, point, flag) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EDQUOT) return F_status_set_error(F_filesystem_quota_block);
      if (errno == EEXIST) return F_status_set_error(F_file_found);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EFBIG || errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == EINTR) return F_status_set_error(F_interrupted);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
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
  f_return_status f_file_link_read(const f_string path, const struct stat link_stat, f_string_dynamic *target) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
      if (link_stat.st_size == 0) return F_status_set_error(F_parameter);
      if (target == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_link_read(path, link_stat, target);
  }
#endif // _di_f_file_link_read_

#ifndef _di_f_file_link_read_at_
  f_return_status f_file_link_read_at(const int at_id, const f_string path, const struct stat link_stat, f_string_dynamic *target) {
    #ifndef _di_level_0_parameter_checking_
      if (link_stat.st_size == 0) return F_status_set_error(F_parameter);
      if (target == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_link_read_at(at_id, path, link_stat, target);
  }
#endif // _di_f_file_link_read_at_

#ifndef _di_f_file_mode_from_string_
  f_return_status f_file_mode_from_string(const f_string string, f_file_mode *mode, uint8_t *replace) {
    #ifndef _di_level_0_parameter_checking_
      if (string == 0) return F_status_set_error(F_parameter);
      if (string[0] == 0) return F_status_set_error(F_parameter);
      if (mode == 0) return F_status_set_error(F_parameter);
      if (replace == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    uint8_t syntax = 0;

    *mode = 0;
    *replace = 0;

    switch (string[0]) {

      case '+':
      case '-':
      case '=':
        switch (string[1]) {

          case 'r':
          case 'w':
          case 'x':
          case 'X':
          case 's':
          case 't':
            syntax = 1;
            break;

          case '0':
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
            syntax = 2;
            break;

          default:
            return F_status_set_error(F_syntax);
        }

        syntax = 1;
        break;

      case 'u':
      case 'g':
      case 'o':
      case 'a':
        syntax = 1;
        break;

      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
        syntax = 2;
        break;

      default:
        return F_status_set_error(F_syntax);
    }

    if (syntax == 1) {
      uint8_t on = 0; // 1 = user, 2 = group, 4 = world/sticky, 7 = all.
      uint8_t how = 0; // 1 = add, 2 = replace, 3 = subtract, 4 = umask add, 5 = umask replace, 6 = umask subtract.
      bool active = F_false;

      f_file_mode mask = 0;
      f_file_mode what = 0;

      for (f_string_length i = 0; syntax && i < string[i]; i++) {

        switch (string[i]) {
          case 'o':
            if (active) {
              syntax = 0;
              break;
            }

            on = 1;
            mask |= f_file_mode_block_world;
            break;

          case 'g':
            if (active) {
              syntax = 0;
              break;
            }

            on = 2;
            mask |= f_file_mode_block_group;
            break;

          case 'u':
            if (active) {
              syntax = 0;
              break;
            }

            on = 4;
            mask |= f_file_mode_block_owner;
            break;

          case 'a':
            if (active) {
              syntax = 0;
              break;
            }

            on = 7;
            mask = f_file_mode_block_owner | f_file_mode_block_group | f_file_mode_block_world;
            break;

          case '+':
          case '-':
          case '=':
            active = F_true;

            if (string[i] == '+') {
              how = on ? 1 : 4;
            }
            else if (string[i] == '-') {
              how = on ? 3 : 6;
            }
            else {
              how = on ? 2 : 5;

              // only the parts designated by the mask should be replaced.
              *mode -= (*mode) & mask;
            }

            if (!on) {
              on = 7;
              mask = f_file_mode_block_owner | f_file_mode_block_group | f_file_mode_block_world;
            }

            for (i++; i < string[i]; i++) {

              if (string[i] == 'r') {
                what = f_file_mode_mask_bit_read;
              }
              else if (string[i] == 'w') {
                what = f_file_mode_mask_bit_write;
              }
              else if (string[i] == 'x') {
                what = f_file_mode_mask_bit_execute;
              }
              else if (string[i] == 'X') {
                what = f_file_mode_mask_bit_execute_only;
              }
              else if (string[i] == 's') {
                if (on & 4) {
                  what = f_file_mode_mask_bit_set_owner;
                }
                else if (on & 2) {
                  what = f_file_mode_mask_bit_set_group;
                }
                else {
                  what = 0;
                }
              }
              else if (string[i] == 't') {
                if (on & 1) {
                  what = f_file_mode_mask_bit_sticky;
                }
                else {
                  what = 0;
                }
              }
              else if (string[i] == ',') {
                active = F_false;
                on = 0;
                how = 0;
                mask = 0;
                break;
              }
              else if (string[i] == '+' || string[i] == '-' || string[i] == '=') {
                // have the outer loop resume at this character after it increments.
                i--;
                break;
              }
              else {
                syntax = 0;
                break;
              }

              if (how == 1 || how == 2) {
                *mode |= what & mask & f_file_mode_mask_how_add;
              }
              else if (how == 3) {
                *mode |= what & mask & f_file_mode_mask_how_subtract;
              }
              else if (how == 4 || how == 5) {
                *mode |= what & mask & f_file_mode_mask_how_umask_add;
              }
              else if (how == 6) {
                *mode |= what & mask & f_file_mode_mask_how_umask_subtract;
              }
            } // for

            break;

        default:
          syntax = 0;
          break;
        }
      } // for
    }
    else if (syntax == 2) {
      // 1 = add, 2 = replace, 3 = subtract, 4 = umask add, 5 = umask replace, 6 = umask subtract.
      uint8_t how = 0;

      mode_t classic = 0;

      f_string_length i = 0;

      if (string[0] == '+') {
        how = 1;
        i = 1;
      }
      else if (string[0] == '-') {
        how = 3;
        i = 1;
      }
      else if (string[0] == '=' || string[0] == '0') {
        how = 2;
        i = 1;
      }
      else {
        how = 5;
      }

      for (; string[i] == '0'; i++) {
        // seek past leading '0's.
      } // for

      if (string[i]) {
        f_string_length j = 0;

        for (; string[i + j] && j < 4; j++) {

          if (j) {
            classic <<= 3;
          }

          switch (string[i]) {
            case '0':
              // already is a zero.
              break;

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
              // this assumes ASCII/UTF-8.
              classic |= string[i] - 0x30;

              break;

            default:
              j = 4;
              break;
          }
        } // for

        if (j == 4) {
          syntax = 0;
        }

        // @fixme: classic is a different structure than mode masks, properly expand. (maybe just use f_file_mode instead of classic and shift by 6 instead of 3.)
        if (syntax) {
          if (how == 1) {
            *mode = classic & f_file_mode_mask_how_add;
          }
          else if (how == 2) {
            *mode = classic & f_file_mode_mask_how_add;
            *replace = f_file_mode_replace_all;
          }
          else if (how == 3) {
            *mode = classic & f_file_mode_mask_how_subtract;
          }
          else if (how == 5) {
            *mode = classic & f_file_mode_mask_how_add;
            *replace = f_file_mode_replace_umask_all;
          }
        }
      }
      else {
        *replace = f_file_mode_replace_all;
      }
    }

    if (syntax) {
      return F_none;
    }

    *mode = 0;
    *replace = 0;

    return F_status_set_error(F_syntax);
  }
#endif // _di_f_file_mode_from_string_

// @todo: needs f_file_mode_to_mode_t() to convert f_file_mode to a mode_t (requires f_file_mode, a source mode_t, and a destination mode_t).

#ifndef _di_f_file_name_base_
  f_return_status f_file_name_base(const f_string path, const f_string_length length, f_string_dynamic *name_base) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
      if (name_base == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    // POSIX basename() modifies the path, so protect it (and add a terminating NULL).
    char path_argument[length + 1];
    f_string path_to_name;

    memcpy(path_argument, path, length);
    path_argument[length] = 0;

    path_to_name = basename(path_argument);

    f_string_length size = strnlen(path_to_name, length);

    if (name_base->used + size > name_base->size) {
      if (name_base->used + size > f_string_length_size) {
        return F_status_set_error(F_string_too_large);
      }

      f_status status = F_none;

      f_macro_string_dynamic_resize(status, (*name_base), name_base->used + size);
      if (F_status_is_error(status)) return status;
    }

    memcpy(name_base->string + name_base->used, path_to_name, size);
    name_base->used += size;

    return F_none;
  }
#endif // _di_f_file_name_base_

#ifndef _di_f_file_name_directory_
  f_return_status f_file_name_directory(const f_string path, const f_string_length length, f_string_dynamic *name_directory) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
      if (name_directory == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    // POSIX dirname() modifies the path, so protect it (and add a terminating NULL).
    char path_argument[length + 1];
    f_string path_to_name;

    memcpy(path_argument, path, length);
    path_argument[length] = 0;

    path_to_name = dirname(path_argument);

    f_string_length size = strnlen(path_to_name, length);

    if (name_directory->used + size > name_directory->size) {
      if (name_directory->used + size > f_string_length_size) {
        return F_status_set_error(F_string_too_large);
      }

      f_status status = F_none;

      f_macro_string_dynamic_resize(status, (*name_directory), name_directory->used + size);
      if (F_status_is_error(status)) return status;
    }

    memcpy(name_directory->string + name_directory->used, path_to_name, size);
    name_directory->used += size;

    return F_none;
  }
#endif // _di_f_file_name_directory_

#ifndef _di_f_file_open_
  f_return_status f_file_open(const f_string path, const mode_t mode, f_file *file) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
      if (file == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_open(path, mode, file);
  }
#endif // _di_f_file_open_

#ifndef _di_f_file_open_at_
  f_return_status f_file_open_at(const int at_id, const f_string path, const mode_t mode, f_file *file) {
    #ifndef _di_level_0_parameter_checking_
      if (file == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_open_at(at_id, path, mode, file);
  }
#endif // _di_f_file_open_at_

#ifndef _di_f_file_read_
  f_return_status f_file_read(const f_file file, f_string_dynamic *buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (file.size_read == 0) return F_status_set_error(F_parameter);
      if (buffer->used > buffer->size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file.id < 0) return F_status_set_error(F_file);
    if (file.id == 0) return F_status_set_error(F_file_closed);

    f_status status = F_none;
    ssize_t size_read = 0;

    char buffer_read[file.size_read];

    memset(&buffer_read, 0, sizeof(file.size_read));

    while ((size_read = read(file.id, buffer_read, file.size_read)) > 0) {
      if (buffer->used + size_read > buffer->size) {
        if (buffer->size + size_read > f_string_length_size) {
          return F_status_set_error(F_string_too_large);
        }

        f_macro_string_dynamic_resize(status, (*buffer), buffer->size + size_read);
        if (F_status_is_error(status)) return status;
      }

      memcpy(buffer->string + buffer->used, buffer_read, size_read);
      buffer->used += size_read;
    } // while

    if (size_read == 0) {
      return F_none_eof;
    }

    if (size_read < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupted);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_file_read_

#ifndef _di_f_file_read_block_
  f_return_status f_file_read_block(const f_file file, f_string_dynamic *buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (file.size_read == 0) return F_status_set_error(F_parameter);
      if (buffer->used > buffer->size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file.id < 0) return F_status_set_error(F_file);
    if (file.id == 0) return F_status_set_error(F_file_closed);

    f_status status = F_none;
    ssize_t size_read = 0;

    char buffer_read[file.size_read];

    memset(&buffer_read, 0, sizeof(file.size_read));

    if ((size_read = read(file.id, buffer_read, file.size_read)) > 0) {
      if (buffer->used + size_read > buffer->size) {
        if (buffer->size + size_read > f_string_length_size) {
          return F_status_set_error(F_string_too_large);
        }

        f_macro_string_dynamic_resize(status, (*buffer), buffer->size + size_read);
        if (F_status_is_error(status)) return status;
      }

      memcpy(buffer->string + buffer->used, buffer_read, size_read);
      buffer->used += size_read;
    }

    if (size_read == 0) {
      return F_none_eof;
    }

    if (size_read < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupted);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_file_read_block_

#ifndef _di_f_file_read_until_
  f_return_status f_file_read_until(const f_file file, f_string_dynamic *buffer, const f_string_length total) {
    #ifndef _di_level_0_parameter_checking_
      if (file.size_read == 0) return F_status_set_error(F_parameter);
      if (buffer->used > buffer->size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file.id < 0) return F_status_set_error(F_file);
    if (file.id == 0) return F_status_set_error(F_file_closed);

    f_status status = F_none;
    ssize_t size_read = 0;

    f_string_length buffer_size = file.size_read;
    f_string_length buffer_count = 0;

    if (total < buffer_size) {
      buffer_size = total;
    }

    char buffer_read[buffer_size];

    memset(&buffer_read, 0, sizeof(buffer_size));

    while (buffer_count < total && (size_read = read(file.id, buffer_read, buffer_size)) > 0) {
      if (buffer->used + size_read > buffer->size) {
        if (buffer->size + size_read > f_string_length_size) {
          return F_status_set_error(F_string_too_large);
        }

        f_macro_string_dynamic_resize(status, (*buffer), buffer->size + size_read);
        if (F_status_is_error(status)) return status;
      }

      memcpy(buffer->string + buffer->used, buffer_read, size_read);
      buffer->used += size_read;
      buffer_count += size_read;
    } // while

    if (size_read == 0) {
      return F_none_eof;
    }

    if (size_read < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) return F_status_set_error(F_block);
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINTR) return F_status_set_error(F_interrupted);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EISDIR) return F_status_set_error(F_file_type_directory);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_file_read_until_

#ifndef _di_f_file_remove_
  f_return_status f_file_remove(const f_string path) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (unlink(path) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBUSY) return F_status_set_error(F_busy);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EISDIR) return F_status_set_error(F_file_type_directory);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_file_remove_

#ifndef _di_f_file_remove_at_
  f_return_status f_file_remove_at(const int at_id, const f_string path, const int flag) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (unlinkat(at_id, path, flag) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EBUSY) return F_status_set_error(F_busy);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == EISDIR) return F_status_set_error(F_file_type_directory);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EPERM) return F_status_set_error(F_prohibited);
      if (errno == EROFS) return F_status_set_error(F_read_only);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_file_remove_at_

#ifndef _di_f_file_seek_
  f_return_status f_file_seek(const int id, const int whence, const f_string_length offset, f_string_length *seeked) {
    #ifndef _di_level_0_parameter_checking_
      if (id <= 0) return F_status_set_error(F_parameter);
      if (whence < 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    *seeked = lseek(id, offset, whence);

    if (*seeked < 0) {
      if (errno == EBADF) return F_status_set_error(F_file_descriptor);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENXIO) return F_status_set_error(F_bound_out);
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == ESPIPE) return F_status_set_error(F_file_type_pipe);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_file_seek_

#ifndef _di_f_file_size_
  f_return_status f_file_size(const f_string path, const bool dereference, f_string_length *size) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
      if (size == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    f_status status = private_f_file_stat(path, dereference, &file_stat);

    if (F_status_is_error(status)) return status;

    *size = file_stat.st_size;

    return F_none;
  }
#endif // _di_f_file_size_

#ifndef _di_f_file_size_at_
  f_return_status f_file_size_at(const int at_id, const f_string path, const bool dereference, f_string_length *size) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
      if (at_id <= 0) return F_status_set_error(F_parameter);
      if (size == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    f_status status = private_f_file_stat_at(at_id, path, dereference, &file_stat);

    if (F_status_is_error(status)) return status;

    *size = file_stat.st_size;

    return F_none;
  }
#endif // _di_f_file_size_at_

#ifndef _di_f_file_size_by_id_
  f_return_status f_file_size_by_id(const int id, f_string_length *size) {
    #ifndef _di_level_0_parameter_checking_
      if (id <= 0) return F_status_set_error(F_parameter);
      if (size == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    f_status status = private_f_file_stat_by_id(id, &file_stat);

    if (F_status_is_error(status)) return status;

    *size = file_stat.st_size;

    return F_none;
  }
#endif // _di_f_file_size_by_id_

#ifndef _di_f_file_stat_
  f_return_status f_file_stat(const f_string path, const bool dereference, struct stat *file_stat) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
      if (file_stat == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_stat(path, dereference, file_stat);
  }
#endif // _di_f_file_stat_

#ifndef _di_f_file_stat_at_
  f_return_status f_file_stat_at(const int at_id, const f_string path, const int flag, struct stat *file_stat) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
      if (at_id <= 0) return F_status_set_error(F_parameter);
      if (file_stat == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_stat_at(at_id, path, flag, file_stat);
  }
#endif // _di_f_file_stat_at_

#ifndef _di_f_file_stat_by_id_
  f_return_status f_file_stat_by_id(const int id, struct stat *file_stat) {
    #ifndef _di_level_0_parameter_checking_
      if (id <= 0) return F_status_set_error(F_parameter);
      if (file_stat == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_file_stat_by_id(id, file_stat);
  }
#endif // _di_f_file_stat_by_id_

#ifndef _di_f_file_touch_
  f_return_status f_file_touch(const f_string path, const mode_t mode, const bool dereference) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = F_none;
    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    status = private_f_file_stat(path, F_false, &file_stat);

    if (F_status_set_fine(status) == F_file_found_not) {
      return private_f_file_create(path, mode, dereference);
    }
    else if (F_status_is_error(status)) {
      return status;
    }

    if (utimensat(f_file_at_current_working, path, 0, dereference ? 0 : f_file_at_symlink_follow_no) < 0) {
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
  f_return_status f_file_touch_at(const int at_id, const f_string path, const mode_t mode, const int flag) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = F_none;
    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    status = private_f_file_stat_at(at_id, path, flag, &file_stat);

    if (F_status_set_fine(status) == F_file_found_not) {
      return private_f_file_create_at(at_id, path, mode, F_false);
    }
    else if (F_status_is_error(status)) {
      return status;
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
#endif // _di_f_file_touch_at_

#ifndef _di_f_file_type_
  f_return_status f_file_type(const f_string path, int *type) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
      if (type == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    if (stat(path, &file_stat) < 0) {
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == ENOENT) return F_file_found_not;
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == ELOOP) return F_status_set_error(F_loop);

      return F_status_set_error(F_file_stat);
    }

    *type = f_macro_file_type_get(file_stat.st_mode);

    return F_none;
  }
#endif // _di_f_file_type_

#ifndef _di_f_file_type_at_
  f_return_status f_file_type_at(const int at_id, const f_string path, const int flag, int *type) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
      if (type == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    struct stat file_stat;

    memset(&file_stat, 0, sizeof(struct stat));

    if (fstatat(at_id, path, &file_stat, flag) < 0) {
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == EOVERFLOW) return F_status_set_error(F_number_overflow);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == ENOENT) return F_file_found_not;
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);

      return F_status_set_error(F_file_stat);
    }

    *type = f_macro_file_type_get(file_stat.st_mode);

    return F_none;
  }
#endif // _di_f_file_type_at_

#ifndef _di_f_file_write_
  f_return_status f_file_write(const f_file file, const f_string_static buffer, f_string_length *written) {
    #ifndef _di_level_0_parameter_checking_
      if (file.size_write == 0) return F_status_set_error(F_parameter);
      if (buffer.used > buffer.size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file.id < 0) return F_status_set_error(F_file);
    if (file.id == 0) return F_status_set_error(F_file_closed);

    if (buffer.used == 0) {
      if (written) *written = 0;
      return F_data_not;
    }

    f_status status = F_none;

    if (written) {
      private_f_file_write_until(file, buffer.string, buffer.used, written);

      if (status == F_none && *written == buffer.used) return F_none_eos;
    }
    else {
      f_string_length written_local = 0;

      private_f_file_write_until(file, buffer.string, buffer.used, &written_local);

      if (status == F_none && written_local == buffer.used) return F_none_eos;
    }

    if (F_status_is_error(status)) return F_status_set_error(status);

    return status;
  }
#endif // _di_f_file_write_

#ifndef _di_f_file_write_block_
  f_return_status f_file_write_block(const f_file file, const f_string_static buffer, f_string_length *written) {
    #ifndef _di_level_0_parameter_checking_
      if (file.size_write == 0) return F_status_set_error(F_parameter);
      if (buffer.used > buffer.size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file.id < 0) return F_status_set_error(F_file);
    if (file.id == 0) return F_status_set_error(F_file_closed);

    if (buffer.used == 0) {
      if (written) *written = 0;
      return F_data_not;
    }

    f_string_length write_max = file.size_write;

    if (write_max > buffer.used) {
      write_max = buffer.used;
    }

    f_status status = F_none;

    if (written) {
      private_f_file_write_until(file, buffer.string, write_max, written);

      if (status == F_none) {
        if (*written == buffer.used) return F_none_eos;
        if (*written == write_max) return F_none_stop;
      }
    }
    else {
      f_string_length written_local = 0;

      private_f_file_write_until(file, buffer.string, write_max, &written_local);

      if (status == F_none) {
        if (written_local == buffer.used) return F_none_eos;
        if (written_local == write_max) return F_none_stop;
      }
    }

    return status;
  }
#endif // _di_f_file_write_block_

#ifndef _di_f_file_write_until_
  f_return_status f_file_write_until(const f_file file, const f_string_static buffer, const f_string_length total, f_string_length *written) {
    #ifndef _di_level_0_parameter_checking_
      if (file.size_write == 0) return F_status_set_error(F_parameter);
      if (buffer.used > buffer.size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file.id < 0) return F_status_set_error(F_file);
    if (file.id == 0) return F_status_set_error(F_file_closed);

    if (buffer.used == 0 || total == 0) {
      if (written) *written = 0;
      return F_data_not;
    }

    f_string_length write_max = file.size_write;

    if (write_max > buffer.used) {
      write_max = buffer.used;
    }

    f_status status = F_none;

    if (written) {
      private_f_file_write_until(file, buffer.string, write_max, written);

      if (status == F_none) {
        if (*written == buffer.used) return F_none_eos;
        if (*written == write_max) return F_none_stop;
      }
    }
    else {
      f_string_length written_local = 0;

      private_f_file_write_until(file, buffer.string, buffer.used, &written_local);

      if (status == F_none) {
        if (written_local == buffer.used) return F_none_eos;
        if (written_local == write_max) return F_none_stop;
      }
    }

    return status;
  }
#endif // _di_f_file_write_until_

#ifndef _di_f_file_write_range_
  f_return_status f_file_write_range(const f_file file, const f_string_static buffer, const f_string_range range, f_string_length *written) {
    #ifndef _di_level_0_parameter_checking_
      if (file.size_write == 0) return F_status_set_error(F_parameter);
      if (buffer.used > buffer.size) return F_status_set_error(F_parameter);
      if (range.stop < range.start) return F_status_set_error(F_parameter);
      if (range.start >= buffer.used) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (file.id < 0) return F_status_set_error(F_file);
    if (file.id == 0) return F_status_set_error(F_file_closed);

    if (buffer.used == 0) {
      if (written) *written = 0;
      return F_data_not;
    }

    const f_string_length total = (range.stop - range.start) + 1;
    f_string_length write_max = total;

    if (write_max > buffer.used) {
      write_max = buffer.used;
    }

    f_status status = F_none;

    if (written) {
      private_f_file_write_until(file, buffer.string + range.start, write_max, written);

      if (status == F_none) {
        if (range.start + *written == buffer.used) return F_none_stop;
        if (range.start + *written == total) return F_none_eos;
      }
    }
    else {
      f_string_length written_local = 0;

      private_f_file_write_until(file, buffer.string + range.start, write_max, &written_local);

      if (status == F_none) {
        if (range.start + written_local == buffer.used) return F_none_eos;
        if (range.start + written_local == total) return F_none_stop;
      }
    }

    return status;
  }
#endif // _di_f_file_write_range_

#ifdef __cplusplus
} // extern "C"
#endif
