#include "directory.h"
#include "private-directory.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_directory_copy_)
  void private_fl_directory_copy_recurse(f_directory_recurse_t * const recurse) {

    f_string_dynamics_t directories = f_string_dynamics_t_initialize;
    f_string_dynamics_t directories_original = f_string_dynamics_t_initialize;

    directories_original.array = recurse->listing.directory.array;
    directories_original.used = recurse->listing.directory.used;
    directories_original.size = recurse->listing.directory.size;

    recurse->listing.directory.array = directories.array;
    recurse->listing.directory.used = directories.used;
    recurse->listing.directory.size = directories.size;

    recurse->state.status = private_fl_directory_list(*recurse->source, 0, 0, recurse->flag & f_directory_recurse_flag_dereference_e, &recurse->listing);

    if (F_status_is_error(recurse->state.status)) {

      // Only the directory is to be freed because all others are preserved between recursions.
      f_string_dynamics_resize(0, &directories);

      return;
    }

    recurse->state.status = F_none;

    {
      f_string_dynamics_t * const list[] = {
        &recurse->listing.block,
        &recurse->listing.character,
        &recurse->listing.regular,
        &recurse->listing.link,
        &recurse->listing.fifo,
        &recurse->listing.socket,
        &recurse->listing.unknown,
      };

      f_array_length_t j = 0;

      for (uint8_t i = 0; i < 7; ++i) {

        for (j = 0; F_status_is_fine(recurse->state.status) && j < list[i]->used; ++j) {
          private_fl_directory_copy_recurse_file(list[i]->array[j], recurse);
        } // for

        list[i]->used = 0;

        // Use an upper limit when retaining memory between recursion calls.
        if (list[i]->size > F_directory_max_list_d) {
          recurse->state.status = f_string_dynamics_resize(F_directory_max_list_d, list[i]);
          if (F_status_is_error(recurse->state.status)) break;
        }

        for (j = 0; j < list[i]->used; ++j) {

          list[i]->array[j].used = 0;

          if (list[i]->array[j].size > F_directory_max_string_d) {
            recurse->state.status = f_string_dynamic_resize(F_directory_max_string_d, &list[i]->array[j]);
            if (F_status_is_error(recurse->state.status)) break;
          }
        } // for
      } // for
    }

    if (F_status_is_error_not(recurse->state.status)) {
      for (f_array_length_t i = 0; i < recurse->listing.directory.used; ++i) {

        if (recurse->state.interrupt) {
          recurse->state.interrupt((void *) &recurse->state, (void *) recurse);
          if (F_status_set_fine(recurse->state.status) == F_interrupt) break;
        }

        f_string_static_t source_sub = f_string_static_t_initialize;
        f_string_static_t destination_sub = f_string_static_t_initialize;

        source_sub.used = recurse->source->used + recurse->listing.directory.array[i].used + 1;
        source_sub.size = source_sub.used;

        destination_sub.used = recurse->destination->used + recurse->listing.directory.array[i].used + 1;
        destination_sub.size = destination_sub.used;

        f_char_t path_source_sub[source_sub.used + 1];
        f_char_t path_destination_sub[destination_sub.used + 1];

        memcpy(path_source_sub, recurse->source->string, sizeof(f_char_t) * recurse->source->used);
        memcpy(path_source_sub + recurse->source->used + 1, recurse->listing.directory.array[i].string, sizeof(f_char_t) * recurse->listing.directory.array[i].used);

        memcpy(path_destination_sub, recurse->destination->string, sizeof(f_char_t) * recurse->destination->used);
        memcpy(path_destination_sub + recurse->destination->used + 1, recurse->listing.directory.array[i].string, sizeof(f_char_t) * recurse->listing.directory.array[i].used);

        path_source_sub[recurse->source->used] = f_path_separator_s.string[0];
        path_source_sub[source_sub.used] = 0;

        path_destination_sub[recurse->destination->used] = f_path_separator_s.string[0];
        path_destination_sub[destination_sub.used] = 0;

        source_sub.string = path_source_sub;
        destination_sub.string = path_destination_sub;

        recurse->state.status = f_directory_exists(source_sub);
        if (F_status_is_error(recurse->state.status)) break;

        if (recurse->state.status == F_false) {
          recurse->state.status = F_status_set_error(F_directory);

          break;
        }

        if (recurse->flag & f_directory_recurse_flag_clone_e) {
          struct stat source_stat;

          memset(&source_stat, 0, sizeof(struct stat));

          recurse->state.status = f_file_stat(source_sub, recurse->flag & f_directory_recurse_flag_dereference_e, &source_stat);
          if (F_status_is_error(recurse->state.status)) break;

          recurse->state.status = f_directory_exists(destination_sub);
          if (F_status_is_error(recurse->state.status)) break;

          if (recurse->state.status == F_true) {
            if (recurse->flag & f_directory_recurse_flag_exclusive_e) {
              recurse->state.status = F_status_set_error(F_directory_found);

              break;
            }

            recurse->state.status = f_file_mode_set(destination_sub, source_stat.st_mode);
            if (F_status_is_error(recurse->state.status)) break;
          }
          else {
            recurse->state.status = f_directory_create(destination_sub, source_stat.st_mode);
            if (F_status_is_error(recurse->state.status)) break;
          }

          if (recurse->flag & (f_directory_recurse_flag_group_e | f_directory_recurse_flag_owner_e)) {
            recurse->state.status = f_file_role_change(destination_sub, (recurse->flag & f_directory_recurse_flag_owner_e) ? source_stat.st_uid : -1, (recurse->flag & f_directory_recurse_flag_group_e) ? source_stat.st_gid : -1, recurse->flag & f_directory_recurse_flag_dereference_e);
            if (F_status_is_error(recurse->state.status)) break;
          }
        }
        else {
          if (recurse->state.status == F_true) {
            if (recurse->flag & f_directory_recurse_flag_exclusive_e) {
              recurse->state.status = F_status_set_error(F_directory_found);

              break;
            }

            recurse->state.status = f_file_mode_set(destination_sub, recurse->mode.directory);
            if (F_status_is_error(recurse->state.status)) break;
          }
          else {
            recurse->state.status = f_directory_create(destination_sub, recurse->mode.directory);
            if (F_status_is_error(recurse->state.status)) break;
          }
        }

        if (recurse->depth < recurse->max_depth) {
          recurse->source = (f_string_static_t * const) & source_sub;
          recurse->destination = (f_string_static_t * const) & destination_sub;

          ++recurse->depth;

          private_fl_directory_copy_recurse(recurse);

          // Data must be restored after recursion.
          recurse->source = (f_string_static_t * const) & source_sub;
          recurse->destination = (f_string_static_t * const) & destination_sub;

          // Success inside the recursed function is handled inside the recursed function, so handle at the current depth.
          if (recurse->state.status == F_none) {
            --recurse->depth;

            if (recurse->verbose) {
              recurse->verbose(source_sub, destination_sub, recurse);
            }
          }

          // Errors in the recursed function are handled outside the recursed function here.
          if (F_status_is_error(recurse->state.status)) {
            if (recurse->state.handle) {
              recurse->state.handle(&recurse->state, (void *) &recurse);
            }

            recurse->state.status = F_failure;
          }

          // Error is now handled, so update the depth and exit.
          if (recurse->state.status == F_failure) {
            --recurse->depth;

            break;
          }
        }

        recurse->state.status = F_none;
      } // for
    }

    recurse->listing.directory.array = directories_original.array;
    recurse->listing.directory.used = directories_original.used;
    recurse->listing.directory.size = directories_original.size;

    f_string_dynamics_resize(0, &directories);
  }
#endif // !defined(_di_fl_directory_copy_)

#if !defined(_di_fl_directory_copy_)
  void private_fl_directory_copy_recurse_file(const f_string_static_t file, f_directory_recurse_t * const recurse) {

    f_string_static_t path_source = f_string_static_t_initialize;
    f_string_static_t path_destination = f_string_static_t_initialize;

    path_source.used = recurse->source->used + file.used + 2;
    path_destination.used = recurse->destination->used + file.used + 2;

    f_char_t path_source_string[path_source.used];
    f_char_t path_destination_string[path_destination.used];

    path_source.string = path_source_string;
    path_destination.string = path_destination_string;

    memcpy(path_source_string, recurse->source->string, sizeof(f_char_t) * recurse->source->used);
    memcpy(path_source_string + recurse->source->used + 1, file.string, sizeof(f_char_t) * file.used);
    path_source_string[recurse->source->used] = f_path_separator_s.string[0];
    path_source_string[recurse->source->used + file.used + 1] = 0;

    memcpy(path_destination_string, recurse->destination->string, sizeof(f_char_t) * recurse->destination->used);
    memcpy(path_destination_string + recurse->destination->used + 1, file.string, sizeof(f_char_t) * file.used);
    path_destination_string[recurse->destination->used] = f_path_separator_s.string[0];
    path_destination_string[recurse->destination->used + file.used + 1] = 0;

    f_status_t status = F_none;
    int flag = (recurse->flag & f_directory_recurse_flag_dereference_e) ? 0 : f_file_stat_flag_reference_e;

    if (recurse->flag & f_directory_recurse_flag_exclusive_e) {
      flag |= f_file_stat_flag_exclusive_e;
    }

    if (recurse->flag & f_directory_recurse_flag_group_e) {
      flag |= f_file_stat_flag_group_e;
    }

    if (recurse->flag & f_directory_recurse_flag_owner_e) {
      flag |= f_file_stat_flag_owner_e;
    }

    if (recurse->flag & f_directory_recurse_flag_clone_e) {
      recurse->state.status = f_file_clone(path_source, path_destination, recurse->size_block, flag);
    }
    else {
      recurse->state.status = f_file_copy(path_source, path_destination, recurse->mode, recurse->size_block, flag);
    }

    if (F_status_is_error(status) || status == F_support_not) {
      if (recurse->state.handle) {
        recurse->state.handle(&recurse->state, (void *) &recurse);
      }

      if (status == F_status_set_error(F_memory_not)) return;

      recurse->state.status = F_failure;

      return;
    }

    if (recurse->verbose) {
      recurse->verbose(path_source, path_destination, (void *) recurse);
    }

    recurse->state.status = F_none;
  }
#endif // !defined(_di_fl_directory_copy_)

#if !defined(_di_fl_directory_copy_) || !defined(_di_fl_directory_list_)
  f_status_t private_fl_directory_list(const f_string_static_t path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), const bool dereference, f_directory_listing_t * const listing) {

    struct dirent **entity = 0;

    f_status_t status = F_none;

    DIR *parent = opendir(path.string);

    if (!parent) {
      if (errno == ENOMEM) return F_status_set_error(F_memory_not);
      if (errno == EMFILE) return F_status_set_error(F_file_descriptor_max);
      if (errno == ENFILE) return F_status_set_error(F_file_open_max);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == ENOENT) return F_status_set_error(F_directory_found_not);
      if (errno == EACCES) return F_status_set_error(F_access_denied);

      return F_status_set_error(F_directory_open);
    }

    const f_file_t directory = macro_f_file_t_initialize_id(dirfd(parent));

    if (directory.id < 0) {
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
    struct stat file_stat;
    int mode = 0;
    size_t i = 0;

    for (; i < length; ++i) {

      name_directory.string = (f_string_t) entity[i]->d_name;
      name_directory.used = strnlen(name_directory.string, F_directory_max_name_d);

      // There is no reason to include "." and ".." in the directory listing.
      if (!strncmp(name_directory.string, "..", 3) || !strncmp(name_directory.string, ".", 2)) {
        f_memory_resize(1, 0, sizeof(f_string_t), (void **) & entity[i]);

        continue;
      }

      memset(&file_stat, 0, sizeof(struct stat));

      status = f_file_stat_at(directory, name_directory, dereference ? 0 : AT_SYMLINK_NOFOLLOW, &file_stat);
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
        status = f_string_dynamics_increase_by(F_memory_default_allocation_small_d, names);
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
#endif // !defined(_di_fl_directory_copy_) || !defined(_di_fl_directory_list_)

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
