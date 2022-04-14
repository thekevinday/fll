#include "directory.h"
#include "private-directory.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_directory_clone_)
  f_status_t private_fl_directory_clone(const f_string_static_t source, const f_string_static_t destination, const fl_directory_recurse_t recurse, const f_number_unsigned_t depth) {

    f_status_t status = F_none;
    f_directory_listing_t listing = f_directory_listing_t_initialize;

    status = private_fl_directory_list(source, 0, 0, F_false, &listing);

    if (F_status_is_error(status)) {
      macro_f_directory_listing_t_delete_simple(listing);

      return status;
    }

    status = F_none;

    f_array_length_t failures_used = recurse.failures ? recurse.failures->used : 0;

    {
      f_string_dynamics_t * const list[] = {
        &listing.block,
        &listing.character,
        &listing.regular,
        &listing.link,
        &listing.fifo,
        &listing.socket,
        &listing.unknown,
      };

      uint8_t i = 0;
      f_array_length_t j = 0;

      for (; i < 7; ++i) {

        for (j = 0; F_status_is_fine(status) && j < list[i]->used; ++j) {
          status = private_fl_directory_clone_file(list[i]->array[j], source, destination, recurse);
        } // for

        f_string_dynamics_resize(0, list[i]);
      } // for
    }

    for (f_array_length_t i = 0; F_status_is_fine(status) && i < listing.directory.used; ++i) {

      f_string_static_t source_sub = f_string_static_t_initialize;
      f_string_static_t destination_sub = f_string_static_t_initialize;

      source_sub.used = source.used + listing.directory.array[i].used + 1;
      source_sub.size = source_sub.used;

      destination_sub.used = destination.used + listing.directory.array[i].used + 1;
      destination_sub.size = destination_sub.used;

      f_char_t path_source_sub[source_sub.used + 1];
      f_char_t path_destination_sub[destination_sub.used + 1];

      memcpy(path_source_sub, source.string, sizeof(f_char_t) * source.used);
      memcpy(path_source_sub + source.used + 1, listing.directory.array[i].string, sizeof(f_char_t) * listing.directory.array[i].used);

      memcpy(path_destination_sub, destination.string, sizeof(f_char_t) * destination.used);
      memcpy(path_destination_sub + destination.used + 1, listing.directory.array[i].string, sizeof(f_char_t) * listing.directory.array[i].used);

      path_source_sub[source.used] = f_path_separator_s.string[0];
      path_source_sub[source_sub.used] = 0;

      path_destination_sub[destination.used] = f_path_separator_s.string[0];
      path_destination_sub[destination_sub.used] = 0;

      source_sub.string = path_source_sub;
      destination_sub.string = path_destination_sub;

      status = f_directory_exists(source_sub);
      if (F_status_is_error(status)) break;

      if (status == F_false) {
        status = F_status_set_error(F_directory);

        break;
      }

      {
        struct stat source_stat;

        memset(&source_stat, 0, sizeof(struct stat));

        status = f_file_stat(source_sub, F_false, &source_stat);
        if (F_status_is_error(status)) break;

        status = f_directory_exists(destination_sub);
        if (F_status_is_error(status)) break;

        if (status == F_true) {
          if (recurse.flag & f_file_stat_flag_exclusive_e) {
            status = F_status_set_error(F_directory_found);

            break;
          }

          status = f_file_mode_set(destination_sub, source_stat.st_mode);
          if (F_status_is_error(status)) break;
        }
        else {
          status = f_directory_create(destination_sub, source_stat.st_mode);
          if (F_status_is_error(status)) break;
        }

        if (recurse.flag & (f_file_stat_flag_group_e | f_file_stat_flag_owner_e)) {
          status = f_file_role_change(destination_sub, source_stat.st_uid, source_stat.st_gid, F_true);
          if (F_status_is_error(status)) break;
        }
      }

      if (depth < recurse.depth_max) {
        status = private_fl_directory_clone(source_sub, destination_sub, recurse, depth + 1);

        if (status == F_none && (!recurse.output.stream || recurse.output.id != -1) && recurse.verbose) {
          recurse.verbose(recurse.output, source_sub, destination_sub);
        }
      }
    } // for

    f_string_dynamics_resize(0, &listing.directory);
    if (F_status_is_error(status)) return status;

    if (recurse.failures && failures_used < recurse.failures->used) {
      return F_failure;
    }

    return F_none;
  }
#endif // !defined(_di_fl_directory_clone_)

#if !defined(_di_fl_directory_clone_file_)
  f_status_t private_fl_directory_clone_file(const f_string_static_t file, const f_string_static_t source, const f_string_static_t destination, const fl_directory_recurse_t recurse) {

    f_string_static_t path_source = f_string_static_t_initialize;
    f_string_static_t path_destination = f_string_static_t_initialize;

    path_source.used = source.used + file.used + 2;
    path_destination.used = destination.used + file.used + 2;

    f_char_t path_source_string[path_source.used];
    f_char_t path_destination_string[path_destination.used];

    path_source.string = path_source_string;
    path_destination.string = path_destination_string;

    memcpy(path_source_string, source.string, sizeof(f_char_t) * source.used);
    memcpy(path_source_string + source.used + 1, file.string, sizeof(f_char_t) * file.used);
    path_source_string[source.used] = f_path_separator_s.string[0];
    path_source_string[source.used + file.used + 1] = 0;

    memcpy(path_destination_string, destination.string, sizeof(f_char_t) * destination.used);
    memcpy(path_destination_string + destination.used + 1, file.string, sizeof(f_char_t) * file.used);
    path_destination_string[destination.used] = f_path_separator_s.string[0];
    path_destination_string[destination.used + file.used + 1] = 0;

    f_status_t status = f_file_clone(path_source, path_destination, recurse.size_block, recurse.flag);

    if (F_status_is_error(status) || status == F_supported_not) {
      if (status == F_status_set_error(F_memory_not)) {
        return F_status_set_error(status);
      }

      if (!recurse.failures) return F_failure;

      const f_status_t status_failure = status;

      macro_f_memory_structure_increment(status, (*recurse.failures), 1, F_memory_default_allocation_small_d, macro_f_directory_statuss_t_resize, F_array_too_large);
      if (F_status_is_error(status)) return status;

      f_directory_status_t failure = f_directory_status_t_initialize;
      f_array_length_t size = 0;

      // identify if failure was because of source or destination.
      struct stat source_stat;

      memset(&source_stat, 0, sizeof(struct stat));

      status = f_file_stat(source, F_false, &source_stat);
      if (F_status_is_error(status)) {
        if (status == F_status_set_error(F_string_too_large)) {
          size = F_string_t_size_d - 1;
        }
        else {
          size = source.used + file.used + 1;
        }

        macro_f_directory_status_t_resize(status, failure, size + 1);
        if (F_status_is_error(status)) return status;

        memcpy(failure.path.string, path_source.string, sizeof(f_char_t) * size);
        failure.path.string[size] = 0;
      }
      else {
        if (status == F_status_set_error(F_string_too_large)) {
          size = F_string_t_size_d - 1;
        }
        else {
          size = destination.used + file.used + 1;
        }

        macro_f_directory_status_t_resize(status, failure, size + 1);
        if (F_status_is_error(status)) return status;

        memcpy(failure.path.string, path_destination.string, sizeof(f_char_t) * size);
        failure.path.string[size] = 0;
      }

      recurse.failures->array[recurse.failures->used].path.string = failure.path.string;
      recurse.failures->array[recurse.failures->used].path.used = size;
      recurse.failures->array[recurse.failures->used].path.size = size + 1;
      recurse.failures->array[recurse.failures->used++].status = status_failure;

      return F_failure;
    }

    if ((!recurse.output.stream || recurse.output.id != -1) && recurse.verbose) {
      recurse.verbose(recurse.output, path_source, path_destination);
    }

    return F_none;
  }
#endif // !defined(_di_fl_directory_clone_file_)

#if !defined(_di_fl_directory_copy_)
  f_status_t private_fl_directory_copy(const f_string_static_t source, const f_string_static_t destination, const f_mode_t mode, const fl_directory_recurse_t recurse, const f_number_unsigned_t depth) {

    f_status_t status = F_none;
    f_directory_listing_t listing = f_directory_listing_t_initialize;

    status = private_fl_directory_list(source, 0, 0, F_false, &listing);

    if (F_status_is_error(status)) {
      macro_f_directory_listing_t_delete_simple(listing);

      return status;
    }

    status = F_none;

    f_array_length_t failures_used = recurse.failures ? recurse.failures->used : 0;

    {
      f_string_dynamics_t * const list[] = {
        &listing.block,
        &listing.character,
        &listing.regular,
        &listing.link,
        &listing.fifo,
        &listing.socket,
        &listing.unknown,
      };

      uint8_t i = 0;
      f_array_length_t j = 0;

      for (; i < 7; ++i) {

        for (j = 0; F_status_is_fine(status) && j < list[i]->used; ++j) {
          status = private_fl_directory_copy_file(list[i]->array[j], source, destination, mode, recurse);
        } // for

        f_string_dynamics_resize(0, list[i]);
      } // for
    }

    for (f_array_length_t i = 0; F_status_is_fine(status) && i < listing.directory.used; ++i) {

      f_string_static_t source_sub = f_string_static_t_initialize;
      f_string_static_t destination_sub = f_string_static_t_initialize;

      source_sub.used = source.used + listing.directory.array[i].used + 1;
      source_sub.size = source_sub.used;

      destination_sub.used = destination.used + listing.directory.array[i].used + 1;
      destination_sub.size = destination_sub.used;

      f_char_t path_source_sub[source_sub.used + 1];
      f_char_t path_destination_sub[destination_sub.used + 1];

      memcpy(path_source_sub, source.string, sizeof(f_char_t) * source.used);
      memcpy(path_source_sub + source.used + 1, listing.directory.array[i].string, sizeof(f_char_t) * listing.directory.array[i].used);

      memcpy(path_destination_sub, destination.string, destination.used);
      memcpy(path_destination_sub + destination.used + 1, listing.directory.array[i].string, sizeof(f_char_t) * listing.directory.array[i].used);

      path_source_sub[source.used] = f_path_separator_s.string[0];
      path_source_sub[source_sub.used] = 0;

      path_destination_sub[destination.used] = f_path_separator_s.string[0];
      path_destination_sub[destination_sub.used] = 0;

      source_sub.string = path_source_sub;
      destination_sub.string = path_destination_sub;

      status = f_directory_exists(source_sub);
      if (F_status_is_error(status)) break;

      if (status == F_false) {
        status = F_status_set_error(F_directory);

        break;
      }

      status = f_directory_exists(destination_sub);
      if (F_status_is_error(status)) break;

      if (status == F_true) {
        if (recurse.flag & f_file_stat_flag_exclusive_e) {
          status = F_status_set_error(F_directory_found);

          break;
        }

        status = f_file_mode_set(destination_sub, mode.directory);
        if (F_status_is_error(status)) break;
      }
      else {
        status = f_directory_create(destination_sub, mode.directory);
        if (F_status_is_error(status)) break;
      }

      if (depth < recurse.depth_max) {
        status = private_fl_directory_copy(source_sub, destination_sub, mode, recurse, depth + 1);

        if (status == F_none && (!recurse.output.stream || recurse.output.id != -1) && recurse.verbose) {
          recurse.verbose(recurse.output, source_sub, destination_sub);
        }
      }
    } // for

    f_string_dynamics_resize(0, &listing.directory);

    if (F_status_is_error(status)) return status;

    if (recurse.failures && failures_used < recurse.failures->used) {
      return F_failure;
    }

    return F_none;
  }
#endif // !defined(_di_fl_directory_copy_)

#if !defined(_di_fl_directory_copy_file_)
  f_status_t private_fl_directory_copy_file(const f_string_static_t file, const f_string_static_t source, const f_string_static_t destination, const f_mode_t mode, const fl_directory_recurse_t recurse) {

    f_string_static_t path_source = f_string_static_t_initialize;
    f_string_static_t path_destination = f_string_static_t_initialize;

    path_source.used = source.used + file.used + 2;
    path_destination.used = destination.used + file.used + 2;

    f_char_t path_source_string[path_source.used];
    f_char_t path_destination_string[path_destination.used];

    path_source.string = path_source_string;
    path_destination.string = path_destination_string;

    memcpy(path_source_string, source.string, sizeof(f_char_t) * source.used);
    memcpy(path_source_string + source.used + 1, file.string, sizeof(f_char_t) * file.used);
    path_source_string[source.used] = f_path_separator_s.string[0];
    path_source_string[source.used + file.used + 1] = 0;

    memcpy(path_destination_string, destination.string, sizeof(f_char_t) * destination.used);
    memcpy(path_destination_string + destination.used + 1, file.string, sizeof(f_char_t) * file.used);
    path_destination_string[destination.used] = f_path_separator_s.string[0];
    path_destination_string[destination.used + file.used + 1] = 0;

    f_status_t status = f_file_copy(path_source, path_destination, mode, recurse.size_block, recurse.flag);

    if (F_status_is_error(status) || status == F_supported_not) {
      if (status == F_status_set_error(F_memory_not)) {
        return F_status_set_error(status);
      }

      if (!recurse.failures) {
        return F_failure;
      }

      const f_status_t status_failure = status;

      macro_f_memory_structure_increment(status, (*recurse.failures), 1, F_memory_default_allocation_small_d, macro_f_directory_statuss_t_resize, F_array_too_large);
      if (F_status_is_error(status)) return status;

      f_directory_status_t failure = f_directory_status_t_initialize;
      f_array_length_t size = 0;

      // identify if failure was because of source or destination.
      struct stat source_stat;

      memset(&source_stat, 0, sizeof(struct stat));

      status = f_file_stat(source, F_false, &source_stat);

      if (F_status_is_error(status)) {
        if (status == F_status_set_error(F_string_too_large)) {
          size = F_string_t_size_d - 1;
        }
        else {
          size = source.used + file.used + 1;
        }

        macro_f_directory_status_t_resize(status, failure, size + 1);
        if (F_status_is_error(status)) return status;

        memcpy(failure.path.string, path_source.string, sizeof(f_char_t) * size);
        failure.path.string[size] = 0;
      }
      else {
        if (status == F_status_set_error(F_string_too_large)) {
          size = F_string_t_size_d - 1;
        }
        else {
          size = destination.used + file.used + 1;
        }

        macro_f_directory_status_t_resize(status, failure, size + 1);
        if (F_status_is_error(status)) return status;

        memcpy(failure.path.string, path_destination.string, sizeof(f_char_t) * size);
        failure.path.string[size] = 0;
      }

      recurse.failures->array[recurse.failures->used].path.string = failure.path.string;
      recurse.failures->array[recurse.failures->used].path.used = size;
      recurse.failures->array[recurse.failures->used].path.size = size + 1;
      recurse.failures->array[recurse.failures->used++].status = status_failure;

      return F_failure;
    }

    if ((!recurse.output.stream || recurse.output.id != -1) && recurse.verbose) {
      recurse.verbose(recurse.output, path_source, path_destination);
    }

    return F_none;
  }
#endif // !defined(_di_fl_directory_copy_file_)

#if !defined(_di_fl_directory_list_)
  f_status_t private_fl_directory_list(const f_string_static_t path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), const bool dereference, f_directory_listing_t * const listing) {

    struct dirent **entity = 0;

    f_array_length_t size = 0;
    f_status_t status = F_none;

    DIR *parent = opendir(path.string);

    if (!parent) {
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == ENOENT) return F_status_set_error(F_directory_found_not);
      if (errno == EACCES) return F_status_set_error(F_access_denied);

      return F_status_set_error(F_directory_open);
    }

    int parent_fd = dirfd(parent);

    if (parent_fd < 0) {
      closedir(parent);

      if (errno == EINVAL) return F_status_set_error(F_directory_stream);
      if (errno == ENOTSUP) return F_status_set_error(F_directory_supported_not);

      return F_status_set_error(F_directory_descriptor);
    }

    const size_t length = scandir(path.string, &entity, filter, sort);

    if (length == -1) {
      closedir(parent);

      if (errno == ENOMEM) return F_status_set_error(F_memory_not);

      return F_status_set_error(F_failure);
    }

    f_string_static_t name_directory = f_string_static_t_initialize;
    f_string_dynamics_t *names = 0;
    f_array_length_t total = 0;
    struct stat file_stat;
    int mode = 0;
    size_t i = 0;

    for (; i < length; ++i) {

      name_directory.string = (f_string_t) entity[i]->d_name;
      name_directory.used = strnlen(name_directory.string, F_directory_name_max_d);

      // There is no reason to include "." and ".." in the directory listing.
      if (!strncmp(name_directory.string, "..", 3) || !strncmp(name_directory.string, ".", 2)) {
        f_memory_resize(1, 0, sizeof(f_string_t), (void **) & entity[i]);

        continue;
      }

      memset(&file_stat, 0, sizeof(struct stat));

      status = f_file_stat_at(parent_fd, name_directory, dereference ? 0 : AT_SYMLINK_NOFOLLOW, &file_stat);
      if (F_status_is_error(status)) break;

      mode = macro_f_file_type_get(file_stat.st_mode);

      if (mode == F_file_type_block_d) {
        names = &listing->block;
      }
      else if (mode == F_file_type_character_d) {
        names = &listing->character;
      }
      else if (mode == F_file_type_directory_d) {
        names = &listing->directory;
      }
      else if (mode == F_file_type_regular_d) {
        names = &listing->regular;
      }
      else if (mode == F_file_type_link_d) {
        names = &listing->link;
      }
      else if (mode == F_file_type_fifo_d) {
        names = &listing->fifo;
      }
      else if (mode == F_file_type_socket_d) {
        names = &listing->socket;
      }
      else {
        names = &listing->unknown;
      }

      if (names->used == names->size) {
        status = f_string_dynamics_increase_by(F_directory_default_allocation_step_d, names);
        if (F_status_is_error(status)) break;
      }

      names->array[names->used].used = 0;

      status = f_string_dynamic_increase_by(name_directory.used, &names->array[names->used]);
      if (F_status_is_error(status)) break;

      memcpy(names->array[names->used].string, name_directory.string, sizeof(f_char_t) * name_directory.used);
      names->array[names->used++].used = name_directory.used;

      f_memory_resize(1, 0, sizeof(f_char_t *), (void **) & entity[i]);
    } // for

    closedir(parent);

    for (; i < length; ++i) {
      f_memory_resize(1, 0, sizeof(f_char_t *), (void **) & entity[i]);
    } // for

    f_memory_resize(1, 0, sizeof(struct dirent *), (void **) & entity);

    if (F_status_is_error(status)) return status;
    if (!length) return F_directory_empty;

    return F_none;
  }
#endif // !defined(_di_fl_directory_list_)

#if !defined(_di_fl_directory_path_push_) || !defined(_di_fl_directory_path_push_dynamic_)
  f_status_t private_fl_directory_path_push(const f_string_static_t source, f_string_dynamic_t * const destination) {

    bool terminated_null = F_false;
    bool separator_prepend = F_false;
    bool separator_append = F_false;

    f_array_length_t total = 0;
    f_array_length_t start = 0;
    f_array_length_t length_truncated = source.used;
    f_status_t status = F_none;

    {
      f_array_length_t i = 0;
      f_array_length_t j = 0;

      if (destination->used > 0) {
        if (!destination->string[destination->used - 1]) {
          terminated_null = F_true;
          total = 1;

          --destination->used;
        }

        for (i = destination->used - 1; i > 0; --i) {

          if (!destination->string[i]) continue;

          status = f_utf_is_control(destination->string + i, destination->used - i);
          if (status == F_true) continue;

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_complete_not_utf) continue;

            return status;
          }

          if (destination->string[i] == f_path_separator_s.string[0]) {
            if (i - 1 > 0) {
              for (j = i - 1; j > 0; --j) {

                if (!destination->string[j]) continue;

                status = f_utf_is_control(destination->string + j, destination->used - j);
                if (status == F_true) continue;

                if (F_status_is_error(status)) {
                  if (F_status_set_fine(status) == F_complete_not_utf) continue;

                  return status;
                }

                if (destination->string[j] == f_path_separator_s.string[0]) {
                  destination->used = j + 1;
                }
                else {
                  break;
                }
              } // for
            }
          }
          else {
            separator_prepend = F_true;
            ++total;
          }

          break;
        } // for

        if (destination->used > 0 && !i) {
          if (destination->string[0] != 0 && destination->string[0] != f_path_separator_s.string[0]) {
            separator_prepend = F_true;
            ++total;
          }
        }
      }

      for (i = source.used - 1; i > 0; --i) {

        if (!source.string[i]) continue;

        status = f_utf_is_control(source.string + i, source.used - i);
        if (status == F_true) continue;

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_complete_not_utf) continue;

          return status;
        }

        if (source.string[i] == f_path_separator_s.string[0]) {
          if (!separator_prepend && destination->used > 0) {
            --destination->used;
          }

          if (i - 1 > 0) {
            for (j = i - 1; j > 0; --j) {

              if (!source.string[j]) continue;

              status = f_utf_is_control(source.string + j, source.used - j);
              if (status == F_true) continue;

              if (F_status_is_error(status)) {
                if (F_status_set_fine(status) == F_complete_not_utf) continue;

                return status;
              }

              if (source.string[j] == f_path_separator_s.string[0]) {
                length_truncated = j + 1;
              }
              else {
                break;
              }
            } // for
          }
        }
        else {
          separator_append = F_true;
          ++total;
        }

        break;
      } // for

      if (!i && source.string[0] != f_path_separator_s.string[0]) {
        separator_append = F_true;
        ++total;
      }

      for (i = 0; i < length_truncated; ++i) {

        if (!source.string[i]) continue;

        status = f_utf_is_control(source.string + i, source.used - i);
        if (status == F_true) continue;

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_complete_not_utf) continue;

          return status;
        }

        start = i;

        if (source.string[0] == f_path_separator_s.string[0]) {
          if (i + 1 < length_truncated) {
            for (j = i + 1; j < length_truncated; ++j) {

              if (!source.string[j]) continue;

              status = f_utf_is_control(source.string + j, source.used - j);
              if (status == F_true) continue;

              if (F_status_is_error(status)) {
                if (F_status_set_fine(status) == F_complete_not_utf) continue;

                return status;
              }

              if (source.string[j] == f_path_separator_s.string[0]) {
                start = j;
              }
              else {
                break;
              }
            } // for
          }
        }

        break;
      } // for

      total += length_truncated - start;

      if (destination->used + total > destination->size) {
        if (destination->used + total > F_string_t_size_d) {
          return F_status_set_error(F_string_too_large);
        }

        status = f_string_dynamic_resize(destination->used + total, destination);
        if (F_status_is_error(status)) return status;
      }
    }

    if (separator_prepend) {
      destination->string[destination->used++] = f_path_separator_s.string[0];
      --total;
    }

    if (length_truncated - start > 0) {
      memcpy(destination->string + destination->used, source.string + start, sizeof(f_char_t) * (length_truncated - start));
    }

    destination->used += total;

    if (separator_append) {
      if (terminated_null) {
        destination->string[destination->used - 2] = f_path_separator_s.string[0];
        destination->string[destination->used - 1] = 0;
      }
      else {
        destination->string[destination->used - 1] = f_path_separator_s.string[0];
      }
    }
    else if (terminated_null) {
      destination->string[destination->used - 1] = 0;
    }

    return F_none;
  }
#endif // !defined(_di_fl_directory_path_push_) || !defined(_di_fl_directory_path_push_dynamic_)

#ifdef __cplusplus
} // extern "C"
#endif
