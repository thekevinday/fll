#include <level_2/directory.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_directory_list_
  f_return_status fll_directory_list(const f_string path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), f_directory_listing *listing) {
    #ifndef _di_level_2_parameter_checking_
      if (listing == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    struct dirent **entity = 0;

    f_string_length size = 0;
    f_status status = f_none;

    DIR *parent = opendir(path);

    if (parent == 0) {
      if (errno == ENOMEM) {
        return f_status_set_error(f_out_of_memory);
      }
      else if (errno == ENOMEM) {
        return f_status_set_error(f_out_of_memory);
      }
      else if (errno == EMFILE) {
        return f_status_set_error(f_file_max_descriptors);
      }
      else if (errno == ENFILE) {
        return f_status_set_error(f_file_max_open);
      }
      else if (errno == ENOTDIR) {
        return f_status_set_error(f_invalid_directory);
      }
      else if (errno == ENOENT) {
        return f_status_set_error(f_directory_not_found);
      }
      else if (errno == EACCES) {
        return f_status_set_error(f_access_denied);
      }

      return f_status_set_error(f_directory_error_open);
    }

    int parent_fd = dirfd(parent);

    if (parent_fd < 0) {
      closedir(parent);

      if (errno == EINVAL) {
        return f_status_set_error(f_directory_error_stream);
      }
      else if (errno == ENOTSUP) {
        return f_status_set_error(f_directory_error_unsupported);
      }

      return f_status_set_error(f_directory_error_descriptor);
    }

    const size_t length = scandir(path, &entity, filter, sort);

    if (length == -1) {
      closedir(parent);

      if (errno == ENOMEM) return f_status_set_error(f_error_allocation);
      else return f_status_set_error(f_failure);
    }

    f_string_dynamics *names = 0;
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

      memset(&file_stat, 0, sizeof(file_stat));

      status = f_file_stat_at(parent_fd, entity[i]->d_name, &file_stat, 0);
      if (f_status_is_error(status)) break;

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
        if (f_status_is_error(status)) break;
      }

      f_macro_string_dynamic_new(status, names->array[names->used], size);
      if (f_status_is_error(status)) break;

      fl_string_dynamic_terminate(&names->array[names->used]);
      if (f_status_is_error(status)) break;

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

    if (f_status_is_error(status)) return status;
    if (length == 0) return f_no_data;

    return f_none;
  }
#endif // _di_fll_directory_list_

#ifdef __cplusplus
} // extern "C"
#endif
