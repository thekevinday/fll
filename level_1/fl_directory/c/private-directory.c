#include "directory.h"
#include "private-directory.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_directory_clone_)
  f_status_t private_fl_directory_clone(const f_string_static_t source, const f_string_static_t destination, const bool role, const fl_directory_recurse_t recurse, const f_number_unsigned_t depth) {

    f_status_t status = F_none;
    f_directory_listing_t listing = f_directory_listing_t_initialize;

    status = private_fl_directory_list(source.string, 0, 0, F_false, &listing);

    if (F_status_is_error(status)) {
      macro_f_directory_listing_t_delete_simple(listing);
      return status;
    }

    status = F_none;

    int directory_fd = 0;
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
          status = private_fl_directory_clone_file(list[i]->array[j], source, destination, role, recurse);
        } // for

        macro_f_string_dynamics_t_delete_simple((*list[i]));
      } // for
    }

    for (f_array_length_t i = 0; F_status_is_fine(status) && i < listing.directory.used; ++i) {

      f_string_static_t source_sub = f_string_static_t_initialize;
      f_string_static_t destination_sub = f_string_static_t_initialize;

      source_sub.used = source.used + listing.directory.array[i].used + 1;
      source_sub.size = source_sub.used;

      destination_sub.used = destination.used + listing.directory.array[i].used + 1;
      destination_sub.size = destination_sub.used;

      char path_source_sub[source_sub.used + 1];
      char path_destination_sub[destination_sub.used + 1];

      memcpy(path_source_sub, source.string, source.used);
      memcpy(path_source_sub + source.used + 1, listing.directory.array[i].string, listing.directory.array[i].used);

      memcpy(path_destination_sub, destination.string, destination.used);
      memcpy(path_destination_sub + destination.used + 1, listing.directory.array[i].string, listing.directory.array[i].used);

      path_source_sub[source.used] = f_path_separator_s[0];
      path_source_sub[source_sub.used] = 0;

      path_destination_sub[destination.used] = f_path_separator_s[0];
      path_destination_sub[destination_sub.used] = 0;

      source_sub.string = path_source_sub;
      destination_sub.string = path_destination_sub;

      status = f_directory_exists(source_sub.string);
      if (F_status_is_error(status)) break;

      if (status == F_false) {
        status = F_status_set_error(F_directory);
        break;
      }

      {
        struct stat source_stat;

        memset(&source_stat, 0, sizeof(struct stat));

        status = f_file_stat(source_sub.string, F_false, &source_stat);
        if (F_status_is_error(status)) break;

        status = f_directory_exists(destination_sub.string);
        if (F_status_is_error(status)) break;

        if (status == F_true) {
          if (recurse.exclusive) {
            status = F_status_set_error(F_directory_found);
            break;
          }

          status = f_file_mode_set(destination_sub.string, source_stat.st_mode);
          if (F_status_is_error(status)) break;
        }
        else {
          status = f_directory_create(destination_sub.string, source_stat.st_mode);
          if (F_status_is_error(status)) break;
        }

        if (role) {
          status = f_file_role_change(destination_sub.string, source_stat.st_uid, source_stat.st_gid, F_true);
          if (F_status_is_error(status)) break;
        }
      }

      if (depth < recurse.depth_max) {
        status = private_fl_directory_clone(source_sub, destination_sub, role, recurse, depth + 1);

        if (status == F_none && (!recurse.output.stream || recurse.output.id != -1) && recurse.verbose) {
          recurse.verbose(recurse.output, source_sub.string, destination_sub.string);
        }
      }
    } // for

    macro_f_string_dynamics_t_delete_simple(listing.directory);

    if (F_status_is_error(status)) {
      return status;
    }

    if (recurse.failures && failures_used < recurse.failures->used) {
      return F_failure;
    }

    return F_none;
  }
#endif // !defined(_di_fl_directory_clone_)

#if !defined(_di_fl_directory_clone_file_)
  f_status_t private_fl_directory_clone_file(const f_string_static_t file, const f_string_static_t source, const f_string_static_t destination, const bool role, const fl_directory_recurse_t recurse) {

    char path_source[source.used + file.used + 2];
    char path_destination[destination.used + file.used + 2];

    memcpy(path_source, source.string, source.used);
    memcpy(path_source + source.used + 1, file.string, file.used);
    path_source[source.used] = f_path_separator_s[0];
    path_source[source.used + file.used + 1] = 0;

    memcpy(path_destination, destination.string, destination.used);
    memcpy(path_destination + destination.used + 1, file.string, file.used);
    path_destination[destination.used] = f_path_separator_s[0];
    path_destination[destination.used + file.used + 1] = 0;

    f_status_t status = f_file_clone(path_source, path_destination, role, recurse.size_block, recurse.exclusive);

    if (F_status_is_error(status) || status == F_supported_not) {
      if (status == F_status_set_error(F_memory_not)) {
        return F_status_set_error(status);
      }

      if (!recurse.failures) return F_failure;

      const f_status_t status_failure = status;

      macro_f_memory_structure_increment(status, (*recurse.failures), 1, f_memory_default_allocation_step, macro_f_directory_statuss_t_resize, F_array_too_large);
      if (F_status_is_error(status)) return status;

      f_directory_status_t failure = f_directory_status_t_initialize;
      f_array_length_t size = 0;

      // identify if failure was because of source or destination.
      struct stat source_stat;

      memset(&source_stat, 0, sizeof(struct stat));

      status = f_file_stat(source.string, F_false, &source_stat);
      if (F_status_is_error(status)) {
        if (status == F_status_set_error(F_string_too_large)) {
          size = f_array_length_t_size - 1;
        }
        else {
          size = source.used + file.used + 1;
        }

        macro_f_directory_status_t_resize(status, failure, size + 1);
        if (F_status_is_error(status)) return status;

        memcpy(failure.path.string, path_source, size);
        failure.path.string[size] = 0;
      }
      else {
        if (status == F_status_set_error(F_string_too_large)) {
          size = f_array_length_t_size - 1;
        }
        else {
          size = destination.used + file.used + 1;
        }

        macro_f_directory_status_t_resize(status, failure, size + 1);
        if (F_status_is_error(status)) return status;

        memcpy(failure.path.string, path_destination, size);
        failure.path.string[size] = 0;
      }

      recurse.failures->array[recurse.failures->used].path.string = failure.path.string;
      recurse.failures->array[recurse.failures->used].path.used = size;
      recurse.failures->array[recurse.failures->used].path.size = size + 1;
      recurse.failures->array[recurse.failures->used].status = status_failure;
      ++recurse.failures->used;

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

    status = private_fl_directory_list(source.string, 0, 0, F_false, &listing);

    if (F_status_is_error(status)) {
      macro_f_directory_listing_t_delete_simple(listing);

      return status;
    }

    status = F_none;

    int directory_fd = 0;
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

        macro_f_string_dynamics_t_delete_simple((*list[i]));
      } // for
    }

    for (f_array_length_t i = 0; F_status_is_fine(status) && i < listing.directory.used; ++i) {

      f_string_static_t source_sub = f_string_static_t_initialize;
      f_string_static_t destination_sub = f_string_static_t_initialize;

      source_sub.used = source.used + listing.directory.array[i].used + 1;
      source_sub.size = source_sub.used;

      destination_sub.used = destination.used + listing.directory.array[i].used + 1;
      destination_sub.size = destination_sub.used;

      char path_source_sub[source_sub.used + 1];
      char path_destination_sub[destination_sub.used + 1];

      memcpy(path_source_sub, source.string, source.used);
      memcpy(path_source_sub + source.used + 1, listing.directory.array[i].string, listing.directory.array[i].used);

      memcpy(path_destination_sub, destination.string, destination.used);
      memcpy(path_destination_sub + destination.used + 1, listing.directory.array[i].string, listing.directory.array[i].used);

      path_source_sub[source.used] = f_path_separator_s[0];
      path_source_sub[source_sub.used] = 0;

      path_destination_sub[destination.used] = f_path_separator_s[0];
      path_destination_sub[destination_sub.used] = 0;

      source_sub.string = path_source_sub;
      destination_sub.string = path_destination_sub;

      status = f_directory_exists(source_sub.string);
      if (F_status_is_error(status)) break;

      if (status == F_false) {
        status = F_status_set_error(F_directory);
        break;
      }

      status = f_directory_exists(destination_sub.string);
      if (F_status_is_error(status)) break;

      if (status == F_true) {
        if (recurse.exclusive) {
          status = F_status_set_error(F_directory_found);
          break;
        }

        status = f_file_mode_set(destination_sub.string, mode.directory);
        if (F_status_is_error(status)) break;
      }
      else {
        status = f_directory_create(destination_sub.string, mode.directory);
        if (F_status_is_error(status)) break;
      }

      if (depth < recurse.depth_max) {
        status = private_fl_directory_copy(source_sub, destination_sub, mode, recurse, depth + 1);

        if (status == F_none && (!recurse.output.stream || recurse.output.id != -1) && recurse.verbose) {
          recurse.verbose(recurse.output, source_sub.string, destination_sub.string);
        }
      }
    } // for

    macro_f_string_dynamics_t_delete_simple(listing.directory);

    if (F_status_is_error(status)) {
      return status;
    }

    if (recurse.failures && failures_used < recurse.failures->used) {
      return F_failure;
    }

    return F_none;
  }
#endif // !defined(_di_fl_directory_copy_)

#if !defined(_di_fl_directory_copy_file_)
  f_status_t private_fl_directory_copy_file(const f_string_static_t file, const f_string_static_t source, const f_string_static_t destination, const f_mode_t mode, const fl_directory_recurse_t recurse) {
    char path_source[source.used + file.used + 2];
    char path_destination[destination.used + file.used + 2];

    memcpy(path_source, source.string, source.used);
    memcpy(path_source + source.used + 1, file.string, file.used);
    path_source[source.used] = f_path_separator_s[0];
    path_source[source.used + file.used + 1] = 0;

    memcpy(path_destination, destination.string, destination.used);
    memcpy(path_destination + destination.used + 1, file.string, file.used);
    path_destination[destination.used] = f_path_separator_s[0];
    path_destination[destination.used + file.used + 1] = 0;

    f_status_t status = f_file_copy(path_source, path_destination, mode, recurse.size_block, recurse.exclusive);

    if (F_status_is_error(status) || status == F_supported_not) {
      if (status == F_status_set_error(F_memory_not)) {
        return F_status_set_error(status);
      }

      if (!recurse.failures) {
        return F_failure;
      }

      const f_status_t status_failure = status;

      macro_f_memory_structure_increment(status, (*recurse.failures), 1, f_memory_default_allocation_step, macro_f_directory_statuss_t_resize, F_array_too_large);
      if (F_status_is_error(status)) return status;

      f_directory_status_t failure = f_directory_status_t_initialize;
      f_array_length_t size = 0;

      // identify if failure was because of source or destination.
      struct stat source_stat;

      memset(&source_stat, 0, sizeof(struct stat));

      status = f_file_stat(source.string, F_false, &source_stat);

      if (F_status_is_error(status)) {
        if (status == F_status_set_error(F_string_too_large)) {
          size = f_array_length_t_size - 1;
        }
        else {
          size = source.used + file.used + 1;
        }

        macro_f_directory_status_t_resize(status, failure, size + 1);
        if (F_status_is_error(status)) return status;

        memcpy(failure.path.string, path_source, size);
        failure.path.string[size] = 0;
      }
      else {
        if (status == F_status_set_error(F_string_too_large)) {
          size = f_array_length_t_size - 1;
        }
        else {
          size = destination.used + file.used + 1;
        }

        macro_f_directory_status_t_resize(status, failure, size + 1);
        if (F_status_is_error(status)) return status;

        memcpy(failure.path.string, path_destination, size);
        failure.path.string[size] = 0;
      }

      recurse.failures->array[recurse.failures->used].path.string = failure.path.string;
      recurse.failures->array[recurse.failures->used].path.used = size;
      recurse.failures->array[recurse.failures->used].path.size = size + 1;
      recurse.failures->array[recurse.failures->used].status = status_failure;
      ++recurse.failures->used;

      return F_failure;
    }

    if ((!recurse.output.stream || recurse.output.id != -1) && recurse.verbose) {
      recurse.verbose(recurse.output, path_source, path_destination);
    }

    return F_none;
  }
#endif // !defined(_di_fl_directory_copy_file_)

#if !defined(_di_fl_directory_list_)
  f_status_t private_fl_directory_list(const f_string_t path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), const bool dereference, f_directory_listing_t *listing) {

    struct dirent **entity = 0;

    f_array_length_t size = 0;
    f_status_t status = F_none;

    DIR *parent = opendir(path);

    if (!parent) {
      if (errno == ENOMEM) {
        return F_status_set_error(F_memory_not);
      }
      else if (errno == ENOMEM) {
        return F_status_set_error(F_memory_not);
      }
      else if (errno == EMFILE) {
        return F_status_set_error(F_file_descriptor_max);
      }
      else if (errno == ENFILE) {
        return F_status_set_error(F_file_open_max);
      }
      else if (errno == ENOTDIR) {
        return F_status_set_error(F_directory);
      }
      else if (errno == ENOENT) {
        return F_status_set_error(F_directory_found_not);
      }
      else if (errno == EACCES) {
        return F_status_set_error(F_access_denied);
      }

      return F_status_set_error(F_directory_open);
    }

    int parent_fd = dirfd(parent);

    if (parent_fd < 0) {
      closedir(parent);

      if (errno == EINVAL) {
        return F_status_set_error(F_directory_stream);
      }
      else if (errno == ENOTSUP) {
        return F_status_set_error(F_directory_supported_not);
      }

      return F_status_set_error(F_directory_descriptor);
    }

    const size_t length = scandir(path, &entity, filter, sort);

    if (length == -1) {
      closedir(parent);

      if (errno == ENOMEM) {
        return F_status_set_error(F_memory_not);
      }
      else {
        return F_status_set_error(F_failure);
      }
    }

    f_string_dynamics_t *names = 0;
    f_array_length_t total = 0;
    struct stat file_stat;
    int mode = 0;
    size_t i = 0;

    for (; i < length; ++i) {

      size = strnlen(entity[i]->d_name, f_directory_name_max);

      // There is no reason to include "." and ".." in the directory listing.
      if (!strncmp(entity[i]->d_name, "..", 3) || !strncmp(entity[i]->d_name, ".", 2)) {
        f_memory_resize(1, 0, sizeof(char *), (void **) & entity[i]);

        continue;
      }

      memset(&file_stat, 0, sizeof(struct stat));

      status = f_file_stat_at(parent_fd, entity[i]->d_name, dereference ? 0 : AT_SYMLINK_NOFOLLOW, &file_stat);
      if (F_status_is_error(status)) break;

      mode = macro_f_file_type_get(file_stat.st_mode);

      if (mode == f_file_type_block) {
        names = &listing->block;
      }
      else if (mode == f_file_type_character) {
        names = &listing->character;
      }
      else if (mode == f_file_type_directory) {
        names = &listing->directory;
      }
      else if (mode == f_file_type_regular) {
        names = &listing->regular;
      }
      else if (mode == f_file_type_link) {
        names = &listing->link;
      }
      else if (mode == f_file_type_fifo) {
        names = &listing->fifo;
      }
      else if (mode == f_file_type_socket) {
        names = &listing->socket;
      }
      else {
        names = &listing->unknown;
      }

      if (names->used == names->size) {
        macro_f_string_dynamics_t_resize(status, (*names), names->size + f_directory_default_allocation_step);
        if (F_status_is_error(status)) break;
      }

      macro_f_string_dynamic_t_clear(names->array[names->used])
      macro_f_string_dynamic_t_resize(status, names->array[names->used], size);
      if (F_status_is_error(status)) break;

      if (names->array[names->used].used > 0 && names->array[names->used].string[names->array[names->used].used - 1] != 0) {
        if (names->array[names->used].used == f_array_length_t_size) {
          status = F_status_set_error(F_string_too_large);
          break;
        }

        total = names->array[names->used].used + 1;
        if (total > names->array[names->used].size) {
          f_status_t status = F_none;

          macro_f_string_dynamics_t_resize(status, (*names), total);
          if (F_status_is_error(status)) break;
        }

        names->array[names->used].string[names->array[names->used].used] = 0;
        names->array[names->used].used = total;
      }

      memcpy(names->array[names->used].string, entity[i]->d_name, size);
      names->array[names->used].used = size;
      ++names->used;

      f_memory_resize(1, 0, sizeof(char *), (void **) & entity[i]);
    } // for

    closedir(parent);

    for (; i < length; ++i) {
      f_memory_resize(1, 0, sizeof(char *), (void **) & entity[i]);
    } // for

    f_memory_resize(1, 0, sizeof(struct dirent *), (void **) & entity);

    if (F_status_is_error(status)) return status;
    if (!length) return F_data_not;

    return F_none;
  }
#endif // !defined(_di_fl_directory_list_)

#if !defined(_di_fl_directory_path_push_) || !defined(_di_fl_directory_path_push_dynamic_)
  f_status_t private_fl_directory_path_push(const f_string_t source, const f_array_length_t length, f_string_dynamic_t *destination) {

    bool terminated_null = F_false;
    bool separator_prepend = F_false;
    bool separator_append = F_false;

    f_array_length_t total = 0;
    f_array_length_t start = 0;
    f_array_length_t length_truncated = length;
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

          if (destination->string[i] == f_path_separator_s[0]) {
            if (i - 1 > 0) {
              for (j = i - 1; j > 0; --j) {

                if (!destination->string[j]) continue;

                status = f_utf_is_control(destination->string + j, destination->used - j);
                if (status == F_true) continue;

                if (F_status_is_error(status)) {
                  if (F_status_set_fine(status) == F_complete_not_utf) continue;

                  return status;
                }

                if (destination->string[j] == f_path_separator_s[0]) {
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
          if (destination->string[0] != 0 && destination->string[0] != f_path_separator_s[0]) {
            separator_prepend = F_true;
            ++total;
          }
        }
      }

      for (i = length - 1; i > 0; --i) {
        if (!source[i]) continue;

        status = f_utf_is_control(source + i, length - i);
        if (status == F_true) continue;

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_complete_not_utf) continue;

          return status;
        }

        if (source[i] == f_path_separator_s[0]) {
          if (!separator_prepend && destination->used > 0) {
            --destination->used;
          }

          if (i - 1 > 0) {
            for (j = i - 1; j > 0; --j) {

              if (!source[j]) continue;

              status = f_utf_is_control(source + j, length - j);
              if (status == F_true) continue;

              if (F_status_is_error(status)) {
                if (F_status_set_fine(status) == F_complete_not_utf) continue;

                return status;
              }

              if (source[j] == f_path_separator_s[0]) {
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

      if (!i && source[0] != f_path_separator_s[0]) {
        separator_append = F_true;
        ++total;
      }

      for (i = 0; i < length_truncated; ++i) {

        if (!source[i]) continue;

        status = f_utf_is_control(source + i, length - i);
        if (status == F_true) continue;

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_complete_not_utf) continue;

          return status;
        }

        start = i;

        if (source[0] == f_path_separator_s[0]) {
          if (i + 1 < length_truncated) {
            for (j = i + 1; j < length_truncated; ++j) {

              if (!source[j]) continue;

              status = f_utf_is_control(source + j, length - j);
              if (status == F_true) continue;

              if (F_status_is_error(status)) {
                if (F_status_set_fine(status) == F_complete_not_utf) continue;

                return status;
              }

              if (source[j] == f_path_separator_s[0]) {
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
        if (destination->used + total > f_array_length_t_size) {
          return F_status_set_error(F_string_too_large);
        }

        macro_f_string_dynamic_t_resize(status, (*destination), destination->used + total);
        if (F_status_is_error(status)) return status;
      }
    }

    if (separator_prepend) {
      destination->string[destination->used] = f_path_separator_s[0];
      ++destination->used;
      --total;
    }

    if (length_truncated - start > 0) {
      memcpy(destination->string + destination->used, source + start, length_truncated - start);
    }

    destination->used += total;

    if (separator_append) {
      if (terminated_null) {
        destination->string[destination->used - 2] = f_path_separator_s[0];
        destination->string[destination->used - 1] = 0;
      }
      else {
        destination->string[destination->used - 1] = f_path_separator_s[0];
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
