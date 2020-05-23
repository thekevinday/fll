#include <level_1/directory.h>
#include "private-directory.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_directory_copy_
  f_return_status private_f_directory_copy(const f_string source, const f_string destination, const f_directory_mode mode, const f_number_unsigned size_block, const bool exclusive) {
    f_status status = F_none;

    status = f_directory_exists(source);
    if (F_status_is_error(status)) return status;
    if (status == F_false) return F_status_set_error(F_directory);

    status = f_directory_exists(destination);
    if (F_status_is_error(status)) return status;

    if (status == F_true) {
      if (exclusive) {
        return F_status_set_error(F_directory_found);
      }

      status = f_file_change_mode(destination, mode.directory, F_false);
      if (F_status_is_error(status)) return status;
    }
    else {
      status = f_directory_create(destination, mode.directory);
      if (F_status_is_error(status)) return status;
    }

    f_directory_listing listing = f_directory_listing_initialize;

    status = private_fl_directory_list(source, 0, 0, &listing);
    if (F_status_is_error(status)) {
      f_macro_directory_listing_delete_simple(listing);
      return status;
    }

    f_array_length i = 0;
    int directory_fd = 0;

    for (; i < listing.block.used; i++) {
      // @todo
    } // for

    f_macro_string_dynamics_delete_simple(listing.block);

    for (; i < listing.character.used; i++) {
      // @todo
    } // for

    f_macro_string_dynamics_delete_simple(listing.character);

    for (; i < listing.file.used; i++) {
      // @todo
    } // for

    f_macro_string_dynamics_delete_simple(listing.file);

    for (; i < listing.link.used; i++) {
      // @todo
    } // for

    f_macro_string_dynamics_delete_simple(listing.link);

    for (; i < listing.socket.used; i++) {
      // @todo
    } // for

    f_macro_string_dynamics_delete_simple(listing.socket);

    for (; i < listing.unknown.used; i++) {
      // @todo
    } // for

    f_macro_string_dynamics_delete_simple(listing.unknown);

    // @todo copy all file types and clear the set when finished.

    // @todo: recurse through each directory, calling this private function.
    // @todo: use a create at directory operation.
    // @todo: build the full path and use that in a recursive function.
    f_string_dynamic path_full = f_string_dynamic_initialize;

    for (; i < listing.directory.used; i++) {
      // @todo
    } // for

    f_macro_string_dynamics_delete_simple(listing.directory);
    return F_none;
  }
#endif // _di_f_directory_copy_

#if !defined(_di_fl_directory_list_)
  f_return_status private_fl_directory_list(const f_string path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), f_directory_listing *listing) {
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
        return F_status_set_error(F_file_descriptors_max);
      }
      else if (errno == ENFILE) {
        return F_status_set_error(F_file_open_max);
      }
      else if (errno == ENOTDIR) {
        return F_status_set_error(F_directory);
      }
      else if (errno == ENOENT) {
        return F_status_set_error(F_directory_not_found);
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

      status = f_file_stat_at(parent_fd, entity[i]->d_name, 0, &file_stat);
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
      else if (mode == f_file_type_file) {
        names = &listing->file;
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

#ifdef __cplusplus
} // extern "C"
#endif
