#include <level_1/directory.h>
#include "private-directory.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_directory_clone_)
  f_return_status private_fl_directory_clone(const f_string_static source, const f_string_static destination, const bool role, const f_number_unsigned size_block, const bool exclusive, f_directory_statuss *failures) {
    f_status status = f_directory_exists(source.string);

    if (F_status_is_error(status)) return status;
    if (status == F_false) return F_status_set_error(F_directory);

    struct stat source_stat;

    memset(&source_stat, 0, sizeof(struct stat));

    status = f_file_stat(source.string, F_false, &source_stat);
    if (F_status_is_error(status)) return status;

    status = f_directory_exists(destination.string);
    if (F_status_is_error(status)) return status;

    if (status == F_true) {
      if (exclusive) {
        return F_status_set_error(F_directory_found);
      }

      status = f_file_change_mode(destination.string, source_stat.st_mode);
      if (F_status_is_error(status)) return status;
    }
    else {
      status = f_directory_create(destination.string, source_stat.st_mode);
      if (F_status_is_error(status)) return status;
    }

    if (role) {
      status = f_file_change_owner(destination.string, source_stat.st_uid, source_stat.st_gid, F_true);
      if (F_status_is_error(status)) return status;
    }

    f_directory_listing listing = f_directory_listing_initialize;

    status = private_fl_directory_list(source.string, 0, 0, F_false, &listing);
    if (F_status_is_error(status)) {
      f_macro_directory_listing_delete_simple(listing);
      return status;
    }

    status = F_none;

    f_array_length i = 0;

    int directory_fd = 0;
    f_string_length failures_used = failures ? failures->used : 0;

    for (; F_status_is_fine(status) && i < listing.block.used; i++) {
      status = private_fl_directory_clone_file(listing.block.array[i], source, destination, role, size_block, exclusive, failures);
    } // for

    f_macro_string_dynamics_delete_simple(listing.block);

    for (i = 0; F_status_is_fine(status) && i < listing.character.used; i++) {
      status = private_fl_directory_clone_file(listing.character.array[i], source, destination, role, size_block, exclusive, failures);
    } // for

    f_macro_string_dynamics_delete_simple(listing.character);

    for (i = 0; F_status_is_fine(status) && i < listing.regular.used; i++) {
      status = private_fl_directory_clone_file(listing.regular.array[i], source, destination, role, size_block, exclusive, failures);
    } // for

    f_macro_string_dynamics_delete_simple(listing.regular);

    for (i = 0; F_status_is_fine(status) && i < listing.link.used; i++) {
      status = private_fl_directory_clone_file(listing.link.array[i], source, destination, role, size_block, exclusive, failures);
    } // for

    f_macro_string_dynamics_delete_simple(listing.link);

    for (i = 0; F_status_is_fine(status) && i < listing.socket.used; i++) {
      status = private_fl_directory_clone_file(listing.socket.array[i], source, destination, role, size_block, exclusive, failures);
    } // for

    f_macro_string_dynamics_delete_simple(listing.socket);

    for (i = 0; F_status_is_fine(status) && i < listing.unknown.used; i++) {
      status = private_fl_directory_clone_file(listing.unknown.array[i], source, destination, role, size_block, exclusive, failures);
    } // for

    f_macro_string_dynamics_delete_simple(listing.unknown);

    for (i = 0; F_status_is_fine(status) && i < listing.directory.used; i++) {
      f_string_static source_sub = f_string_static_initialize;
      f_string_static destination_sub = f_string_static_initialize;

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

      path_source_sub[source.used] = f_path_separator[0];
      path_source_sub[source_sub.used] = 0;

      path_destination_sub[destination.used] = f_path_separator[0];
      path_destination_sub[destination_sub.used] = 0;

      source_sub.string = path_source_sub;
      destination_sub.string = path_destination_sub;

      status = private_fl_directory_clone(source_sub, destination_sub, role, size_block, exclusive, failures);
    } // for

    f_macro_string_dynamics_delete_simple(listing.directory);

    if (F_status_is_error(status)) return status;

    if (failures && failures_used < failures->used) return F_failure;

    return F_none;
  }
#endif // !defined(_di_fl_directory_clone_)

#if !defined(_di_fl_directory_clone_file_)
  f_return_status private_fl_directory_clone_file(const f_string_static file, const f_string_static source, const f_string_static destination, const bool role, const f_number_unsigned size_block, const bool exclusive, f_directory_statuss *failures) {
    char path_source[source.used + file.used + 2];
    char path_destination[destination.used + file.used + 2];

    memcpy(path_source, source.string, source.used);
    memcpy(path_source + source.used + 1, file.string, file.used);
    path_source[source.used] = f_path_separator[0];
    path_source[source.used + file.used + 1] = 0;

    memcpy(path_destination, destination.string, destination.used);
    memcpy(path_destination + destination.used + 1, file.string, file.used);
    path_destination[destination.used] = f_path_separator[0];
    path_destination[destination.used + file.used + 1] = 0;

    f_status status = f_file_clone(path_source, path_destination, role, size_block, exclusive);

    if (F_status_is_error(status) || status == F_unsupported) {
      if (status == F_status_set_error(F_memory_allocation) || status == F_status_set_error(F_memory_reallocation)) {
        return F_status_set_error(status);
      }

      if (!failures) return F_failure;

      const f_status status_failure = status;

      if (failures->used + 1 > failures->size) {
        if (failures->size + f_memory_default_allocation_step > f_array_length_size) {
          if (failures->size + 1 > f_array_length_size) {
            return F_status_set_error(F_buffer_too_large);
          }

          f_macro_directory_statuss_resize(status, (*failures), failures->used + 1);
          if (F_status_is_error(status)) return status;
        }
        else {
          f_macro_directory_statuss_resize(status, (*failures), failures->used + f_memory_default_allocation_step);
          if (F_status_is_error(status)) return status;
        }
      }

      f_directory_status failure = f_directory_status_initialize;
      f_string_length size = 0;

      // identify if failure was because of source or destination.
      struct stat source_stat;

      memset(&source_stat, 0, sizeof(struct stat));

      status = f_file_stat(source.string, F_false, &source_stat);
      if (F_status_is_error(status)) {
        if (status == F_status_set_error(F_string_too_large)) {
          size = f_string_length_size - 1;
        }
        else {
          size = source.used + file.used + 1;
        }

        f_macro_directory_status_resize(status, failure, size + 1);
        if (F_status_is_error(status)) return status;

        memcpy(failure.path.string, path_source, size);
        failure.path.string[size] = 0;
      }
      else {
        if (status == F_status_set_error(F_string_too_large)) {
          size = f_string_length_size - 1;
        }
        else {
          size = destination.used + file.used + 1;
        }

        f_macro_directory_status_resize(status, failure, size + 1);
        if (F_status_is_error(status)) return status;

        memcpy(failure.path.string, path_destination, size);
        failure.path.string[size] = 0;
      }

      failures->array[failures->used].path.string = failure.path.string;
      failures->array[failures->used].path.used = size;
      failures->array[failures->used].path.size = size + 1;
      failures->array[failures->used].status = status_failure;
      failures->used++;

      return F_failure;
    }

    return F_none;
  }
#endif // !defined(_di_fl_directory_clone_file_)

#if !defined(_di_fl_directory_copy_)
  f_return_status private_fl_directory_copy(const f_string_static source, const f_string_static destination, const f_directory_mode mode, const f_number_unsigned size_block, const bool exclusive, f_directory_statuss *failures) {
    f_status status = f_directory_exists(source.string);

    if (F_status_is_error(status)) return status;
    if (status == F_false) return F_status_set_error(F_directory);

    status = f_directory_exists(destination.string);
    if (F_status_is_error(status)) return status;

    if (status == F_true) {
      if (exclusive) {
        return F_status_set_error(F_directory_found);
      }

      status = f_file_change_mode(destination.string, mode.directory);
      if (F_status_is_error(status)) return status;
    }
    else {
      status = f_directory_create(destination.string, mode.directory);
      if (F_status_is_error(status)) return status;
    }

    f_directory_listing listing = f_directory_listing_initialize;

    status = private_fl_directory_list(source.string, 0, 0, F_false, &listing);
    if (F_status_is_error(status)) {
      f_macro_directory_listing_delete_simple(listing);
      return status;
    }

    status = F_none;

    f_array_length i = 0;

    int directory_fd = 0;
    f_string_length failures_used = failures ? failures->used : 0;

    for (; F_status_is_fine(status) && i < listing.block.used; i++) {
      status = private_fl_directory_copy_file(listing.block.array[i], source, destination, mode.block, size_block, exclusive, failures);
    } // for

    f_macro_string_dynamics_delete_simple(listing.block);

    for (i = 0; F_status_is_fine(status) && i < listing.character.used; i++) {
      status = private_fl_directory_copy_file(listing.character.array[i], source, destination, mode.character, size_block, exclusive, failures);
    } // for

    f_macro_string_dynamics_delete_simple(listing.character);

    for (i = 0; F_status_is_fine(status) && i < listing.regular.used; i++) {
      status = private_fl_directory_copy_file(listing.regular.array[i], source, destination, mode.regular, size_block, exclusive, failures);
    } // for

    f_macro_string_dynamics_delete_simple(listing.regular);

    for (i = 0; F_status_is_fine(status) && i < listing.link.used; i++) {
      status = private_fl_directory_copy_file(listing.link.array[i], source, destination, mode.link, size_block, exclusive, failures);
    } // for

    f_macro_string_dynamics_delete_simple(listing.link);

    for (i = 0; F_status_is_fine(status) && i < listing.socket.used; i++) {
      status = private_fl_directory_copy_file(listing.socket.array[i], source, destination, mode.socket, size_block, exclusive, failures);
    } // for

    f_macro_string_dynamics_delete_simple(listing.socket);

    for (i = 0; F_status_is_fine(status) && i < listing.unknown.used; i++) {
      status = private_fl_directory_copy_file(listing.unknown.array[i], source, destination, mode.unknown, size_block, exclusive, failures);
    } // for

    f_macro_string_dynamics_delete_simple(listing.unknown);

    for (i = 0; F_status_is_fine(status) && i < listing.directory.used; i++) {
      f_string_static source_sub = f_string_static_initialize;
      f_string_static destination_sub = f_string_static_initialize;

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

      path_source_sub[source.used] = f_path_separator[0];
      path_source_sub[source_sub.used] = 0;

      path_destination_sub[destination.used] = f_path_separator[0];
      path_destination_sub[destination_sub.used] = 0;

      source_sub.string = path_source_sub;
      destination_sub.string = path_destination_sub;

      status = private_fl_directory_copy(source_sub, destination_sub, mode, size_block, exclusive, failures);
    } // for

    f_macro_string_dynamics_delete_simple(listing.directory);

    if (F_status_is_error(status)) return status;

    if (failures && failures_used < failures->used) return F_failure;

    return F_none;
  }
#endif // !defined(_di_fl_directory_copy_)

#if !defined(_di_fl_directory_copy_file_)
  f_return_status private_fl_directory_copy_file(const f_string_static file, const f_string_static source, const f_string_static destination, const mode_t mode, const f_number_unsigned size_block, const bool exclusive, f_directory_statuss *failures) {
    char path_source[source.used + file.used + 2];
    char path_destination[destination.used + file.used + 2];

    memcpy(path_source, source.string, source.used);
    memcpy(path_source + source.used + 1, file.string, file.used);
    path_source[source.used] = f_path_separator[0];
    path_source[source.used + file.used + 1] = 0;

    memcpy(path_destination, destination.string, destination.used);
    memcpy(path_destination + destination.used + 1, file.string, file.used);
    path_destination[destination.used] = f_path_separator[0];
    path_destination[destination.used + file.used + 1] = 0;

    f_status status = f_file_copy(path_source, path_destination, mode, size_block, exclusive);

    if (F_status_is_error(status) || status == F_unsupported) {
      if (status == F_status_set_error(F_memory_allocation) || status == F_status_set_error(F_memory_reallocation)) {
        return F_status_set_error(status);
      }

      if (!failures) return F_failure;

      const f_status status_failure = status;

      if (failures->used + 1 > failures->size) {
        if (failures->size + f_memory_default_allocation_step > f_array_length_size) {
          if (failures->size + 1 > f_array_length_size) {
            return F_status_set_error(F_buffer_too_large);
          }

          f_macro_directory_statuss_resize(status, (*failures), failures->used + 1);
          if (F_status_is_error(status)) return status;
        }
        else {
          f_macro_directory_statuss_resize(status, (*failures), failures->used + f_memory_default_allocation_step);
          if (F_status_is_error(status)) return status;
        }
      }

      f_directory_status failure = f_directory_status_initialize;
      f_string_length size = 0;

      // identify if failure was because of source or destination.
      struct stat source_stat;

      memset(&source_stat, 0, sizeof(struct stat));

      status = f_file_stat(source.string, F_false, &source_stat);
      if (F_status_is_error(status)) {
        if (status == F_status_set_error(F_string_too_large)) {
          size = f_string_length_size - 1;
        }
        else {
          size = source.used + file.used + 1;
        }

        f_macro_directory_status_resize(status, failure, size + 1);
        if (F_status_is_error(status)) return status;

        memcpy(failure.path.string, path_source, size);
        failure.path.string[size] = 0;
      }
      else {
        if (status == F_status_set_error(F_string_too_large)) {
          size = f_string_length_size - 1;
        }
        else {
          size = destination.used + file.used + 1;
        }

        f_macro_directory_status_resize(status, failure, size + 1);
        if (F_status_is_error(status)) return status;

        memcpy(failure.path.string, path_destination, size);
        failure.path.string[size] = 0;
      }

      failures->array[failures->used].path.string = failure.path.string;
      failures->array[failures->used].path.used = size;
      failures->array[failures->used].path.size = size + 1;
      failures->array[failures->used].status = status_failure;
      failures->used++;

      return F_failure;
    }

    return F_none;
  }
#endif // !defined(_di_fl_directory_copy_file_)

#if !defined(_di_fl_directory_list_)
  f_return_status private_fl_directory_list(const f_string path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), const bool dereference, f_directory_listing *listing) {
    struct dirent **entity = 0;

    f_string_length size = 0;
    f_status status = F_none;

    DIR *parent = opendir(path);

    if (parent == 0) {
      if (errno == ENOMEM) {
        return F_status_set_error(F_memory_out);
      }
      else if (errno == ENOMEM) {
        return F_status_set_error(F_memory_out);
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
        return F_status_set_error(F_directory_unsupported);
      }

      return F_status_set_error(F_directory_descriptor);
    }

    const size_t length = scandir(path, &entity, filter, sort);

    if (length == -1) {
      closedir(parent);

      if (errno == ENOMEM) return F_status_set_error(F_memory_allocation);
      else return F_status_set_error(F_failure);
    }

    f_string_dynamics *names = 0;
    f_string_length total = 0;
    struct stat file_stat;
    int mode = 0;
    size_t i = 0;

    for (; i < length; i++) {
      size = strnlen(entity[i]->d_name, f_directory_name_max);

      // There is no reason to include "." and ".." in the directory listing.
      if (strncmp(entity[i]->d_name, "..", 3) == 0 || strncmp(entity[i]->d_name, ".", 2) == 0) {
        f_memory_delete((void **) & entity[i], sizeof(char *), 1);
        continue;
      }

      memset(&file_stat, 0, sizeof(struct stat));

      status = f_file_stat_at(parent_fd, entity[i]->d_name, dereference ? 0 : AT_SYMLINK_NOFOLLOW, &file_stat);
      if (F_status_is_error(status)) break;

      mode = f_macro_file_type_get(file_stat.st_mode);

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
      else if (mode == f_file_type_pipe) {
        names = &listing->pipe;
      }
      else if (mode == f_file_type_socket) {
        names = &listing->socket;
      }
      else {
        names = &listing->unknown;
      }

      if (names->used >= names->size) {
        f_macro_string_dynamics_resize(status, (*names), names->size + f_directory_default_allocation_step);
        if (F_status_is_error(status)) break;
      }

      f_macro_string_dynamic_new(status, names->array[names->used], size);
      if (F_status_is_error(status)) break;

      if (names->array[names->used].used > 0 && names->array[names->used].string[names->array[names->used].used - 1] != 0) {
        if (names->array[names->used].used + 1 > f_string_length_size) {
          status = F_status_set_error(F_string_too_large);
          break;
        }

        total = names->array[names->used].used + 1;
        if (total > names->array[names->used].size) {
          f_status status = F_none;

          f_macro_string_dynamics_resize(status, (*names), total);
          if (F_status_is_error(status)) break;
        }

        names->array[names->used].string[names->array[names->used].used] = 0;
        names->array[names->used].used = total;
      }

      memcpy(names->array[names->used].string, entity[i]->d_name, size);
      names->array[names->used].used = size;
      names->used++;

      f_memory_delete((void **) & entity[i], sizeof(char *), 1);
    } // for

    closedir(parent);

    for (; i < length; i++) {
      f_memory_delete((void **) & entity[i], sizeof(char *), 1);
    } // for

    f_memory_delete((void **) & entity, sizeof(struct dirent *), 1);

    if (F_status_is_error(status)) return status;
    if (length == 0) return F_data_not;

    return F_none;
  }
#endif // !defined(_di_fl_directory_list_)

#if !defined(_di_fl_directory_path_push_) || !defined(_di_fl_directory_path_push_dynamic_)
  f_return_status private_fl_directory_path_push(const f_string source, const f_string_length length, f_string_dynamic *destination) {
    bool terminated_null = F_false;
    bool separator_prepend = F_false;
    bool separator_append = F_false;

    f_string_length total = 0;
    f_string_length start = 0;
    f_string_length length_truncated = length;
    f_status status = F_none;

    {
      f_string_length i = 0;
      f_string_length j = 0;

      if (destination->used > 0) {
        if (destination->string[destination->used - 1] == 0) {
          terminated_null = F_true;
          total = 1;

          destination->used--;
        }

        for (i = destination->used - 1; i > 0; i--) {
          if (destination->string[i] == 0) continue;

          status = f_utf_is_control(destination->string + i, destination->used - i);
          if (status == F_true) continue;

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_incomplete_utf) continue;

            return status;
          }

          if (destination->string[i] == f_path_separator[0]) {
            if (i - 1 > 0) {
              for (j = i - 1; j > 0; j--) {
                if (destination->string[j] == 0) continue;

                status = f_utf_is_control(destination->string + j, destination->used - j);
                if (status == F_true) continue;

                if (F_status_is_error(status)) {
                  if (F_status_set_fine(status) == F_incomplete_utf) continue;

                  return status;
                }

                if (destination->string[j] == f_path_separator[0]) {
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
            total++;
          }

          break;
        } // for

        if (destination->used > 0 && i == 0) {
          if (destination->string[0] != 0 && destination->string[0] != f_path_separator[0]) {
            separator_prepend = F_true;
            total++;
          }
        }
      }

      for (i = length - 1; i > 0; i--) {
        if (source[i] == 0) continue;

        status = f_utf_is_control(source + i, length - i);
        if (status == F_true) continue;

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_incomplete_utf) continue;

          return status;
        }

        if (source[i] == f_path_separator[0]) {
          if (!separator_prepend && destination->used > 0) {
            destination->used--;
          }

          if (i - 1 > 0) {
            for (j = i - 1; j > 0; j--) {
              if (source[j] == 0) continue;

              status = f_utf_is_control(source + j, length - j);
              if (status == F_true) continue;

              if (F_status_is_error(status)) {
                if (F_status_set_fine(status) == F_incomplete_utf) continue;

                return status;
              }

              if (source[j] == f_path_separator[0]) {
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
          total++;
        }

        break;
      } // for

      if (i == 0 && source[0] != f_path_separator[0]) {
        separator_append = F_true;
        total++;
      }

      for (i = 0; i < length_truncated; i++) {
        if (source[i] == 0) continue;

        status = f_utf_is_control(source + i, length - i);
        if (status == F_true) continue;

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_incomplete_utf) continue;

          return status;
        }

        start = i;

        if (source[0] == f_path_separator[0]) {
          if (i + 1 < length_truncated) {
            for (j = i + 1; j < length_truncated; j++) {
              if (source[j] == 0) continue;

              status = f_utf_is_control(source + j, length - j);
              if (status == F_true) continue;

              if (F_status_is_error(status)) {
                if (F_status_set_fine(status) == F_incomplete_utf) continue;

                return status;
              }

              if (source[j] == f_path_separator[0]) {
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
        if (destination->used + total > f_string_length_size) {
          return F_status_set_error(F_string_too_large);
        }

        f_macro_string_dynamic_resize(status, (*destination), destination->used + total);
        if (F_status_is_error(status)) return status;
      }
    }

    if (separator_prepend) {
      destination->string[destination->used] = f_path_separator[0];
      destination->used++;
      total--;
    }

    if (length_truncated - start > 0) {
      memcpy(destination->string + destination->used, source + start, length_truncated - start);
    }

    destination->used += total;

    if (separator_append) {
      if (terminated_null) {
        destination->string[destination->used - 2] = f_path_separator[0];
        destination->string[destination->used - 1] = 0;
      }
      else {
        destination->string[destination->used - 1] = f_path_separator[0];
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
