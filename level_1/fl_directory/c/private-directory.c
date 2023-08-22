#include "directory.h"
#include "private-directory.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fl_directory_do_)
  void private_fl_directory_do_recurse(f_directory_recurse_do_t * const recurse) {

    f_string_dynamics_t directories_original = f_string_dynamics_t_initialize;

    directories_original.array = recurse->listing.directory.array;
    directories_original.used = recurse->listing.directory.used;
    directories_original.size = recurse->listing.directory.size;

    recurse->listing.directory.array = 0;
    recurse->listing.directory.used = 0;
    recurse->listing.directory.size = 0;

    // Use a clean set for each recursion.
    recurse->listing.block.used = 0;
    recurse->listing.character.used = 0;
    recurse->listing.directory.used = 0;
    recurse->listing.regular.used = 0;
    recurse->listing.link.used = 0;
    recurse->listing.fifo.used = 0;
    recurse->listing.socket.used = 0;
    recurse->listing.unknown.used = 0;

    recurse->state.status = private_fl_directory_list(recurse->path, 0, 0, recurse->flag & f_directory_recurse_do_flag_dereference_e, &recurse->listing);

    if (F_status_is_error(recurse->state.status)) {
      private_inline_fl_directory_do_handle(recurse, f_string_empty_s, f_directory_recurse_do_flag_list_e | f_directory_recurse_do_flag_path_e);

      // Only the directory is to be freed because all others are preserved between recursions.
      if (F_status_is_error(recurse->state.status)) {
        f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &recurse->listing.directory.array, &recurse->listing.directory.used, &recurse->listing.directory.size, &f_string_dynamics_delete_callback);

        recurse->listing.directory.array = directories_original.array;
        recurse->listing.directory.used = directories_original.used;
        recurse->listing.directory.size = directories_original.size;

        return;
      }
    }

    recurse->state.status = F_okay;

    if (recurse->flag & f_directory_recurse_do_flag_list_e) {
      recurse->action((void *) recurse, recurse->path, f_directory_recurse_do_flag_list_e);

      if (F_status_is_error(recurse->state.status)) {
        private_inline_fl_directory_do_handle(recurse, recurse->path, f_directory_recurse_do_flag_list_e);
        if (F_status_is_error(recurse->state.status)) return;
      }

      if (recurse->state.status != F_done && F_status_is_error_not(recurse->state.status)) {
        recurse->state.status = F_okay;
      }
    }

    f_number_unsigned_t i = 0;
    uint8_t j = 0;
    const f_number_unsigned_t used_original = recurse->path.used;

    static const uint8_t flag_actions[] = {
      f_directory_recurse_do_flag_before_e,
      0,
      f_directory_recurse_do_flag_after_e,
    };

    static const uint16_t flags[] = {
      f_directory_recurse_do_flag_block_e,
      f_directory_recurse_do_flag_character_e,
      f_directory_recurse_do_flag_regular_e,
      f_directory_recurse_do_flag_link_e,
      f_directory_recurse_do_flag_fifo_e,
      f_directory_recurse_do_flag_socket_e,
      f_directory_recurse_do_flag_unknown_e,
    };

    if (recurse->state.status != F_done && F_status_is_error_not(recurse->state.status)) {
      f_string_dynamics_t * const list[] = {
        &recurse->listing.block,
        &recurse->listing.character,
        &recurse->listing.regular,
        &recurse->listing.link,
        &recurse->listing.fifo,
        &recurse->listing.socket,
        &recurse->listing.unknown,
      };

      for (uint8_t k = 0; k < 7; ++k) {

        for (i = 0; i < list[k]->used; ++i) {

          if (recurse->state.interrupt) {
            recurse->state.interrupt((void *) &recurse->state, (void *) recurse);
            if (F_status_set_fine(recurse->state.status) == F_interrupt) break;
          }

          recurse->path.used = used_original;

          recurse->state.status = f_memory_array_increase_by(f_path_separator_s.used + list[k]->array[i].used + 1, sizeof(f_char_t), (void **) &recurse->path.string, &recurse->path.used, &recurse->path.size);

          if (F_status_is_error_not(recurse->state.status)) {
            recurse->state.status = f_string_dynamic_append_assure(f_path_separator_s, &recurse->path);
          }

          if (F_status_is_error_not(recurse->state.status)) {
            recurse->state.status = f_string_dynamic_append_nulless(list[k]->array[i], &recurse->path);
          }

          // Guarantee NULL termination.
          recurse->path.string[recurse->path.used] = 0;

          if (F_status_is_error(recurse->state.status)) {
            private_inline_fl_directory_do_handle(recurse, list[k]->array[i], f_directory_recurse_do_flag_directory_e);
            if (F_status_is_error(recurse->state.status)) break;
            if (recurse->state.status == F_break || recurse->state.status == F_done) break;
            if (recurse->state.status == F_continue) continue;
          }

          // Convenience and code simplification loop for processing before action, action, and after action.
          for (j = 0; j < 3; ++j) {

            if (!flag_actions[j] || (recurse->flag & flag_actions[j])) {
              recurse->state.status = F_okay;

              recurse->action((void *) recurse, list[k]->array[i], flag_actions[j] | flags[k]);

              if (F_status_is_error(recurse->state.status)) {
                private_inline_fl_directory_do_handle(recurse, recurse->listing.directory.array[i], f_directory_recurse_do_flag_before_e | flags[k]);
                if (F_status_is_error(recurse->state.status)) break;
              }

              // This loop is not considered a loop for breaking and continuing.
              if (recurse->state.status == F_break || recurse->state.status == F_done || recurse->state.status == F_continue) break;
            }
          } // for

          if (F_status_is_error(recurse->state.status)) break;
          if (recurse->state.status == F_break || recurse->state.status == F_done) break;
          if (recurse->state.status == F_continue) continue;
        } // for

        if (F_status_is_error(recurse->state.status) || recurse->state.status == F_done) break;
      } // for
    }

    if (recurse->state.status != F_done && F_status_is_error_not(recurse->state.status)) {
      for (i = 0; i < recurse->listing.directory.used; ++i) {

        if (recurse->state.interrupt) {
          recurse->state.interrupt((void *) &recurse->state, (void *) recurse);
          if (F_status_set_fine(recurse->state.status) == F_interrupt) break;
        }

        recurse->path.used = used_original;

        recurse->state.status = f_memory_array_increase_by(f_path_separator_s.used + recurse->listing.directory.array[i].used + 1, sizeof(f_char_t), (void **) &recurse->path.string, &recurse->path.used, &recurse->path.size);

        if (F_status_is_error_not(recurse->state.status)) {
          recurse->state.status = f_string_dynamic_append_assure(f_path_separator_s, &recurse->path);
        }

        if (F_status_is_error_not(recurse->state.status)) {
          recurse->state.status = f_string_dynamic_append_nulless(recurse->listing.directory.array[i], &recurse->path);
        }

        // Guarantee NULL termination.
        recurse->path.string[recurse->path.used] = 0;

        if (F_status_is_error_not(recurse->state.status)) {
          recurse->state.status = f_directory_exists(recurse->path);

          if (recurse->state.status == F_false) {
            recurse->state.status = F_status_set_error(F_directory_not);
          }
        }

        if (F_status_is_error(recurse->state.status)) {
          private_inline_fl_directory_do_handle(recurse, recurse->listing.directory.array[i], f_directory_recurse_do_flag_directory_e);
          if (F_status_is_error(recurse->state.status)) break;
          if (recurse->state.status == F_break || recurse->state.status == F_done) break;
          if (recurse->state.status == F_continue) continue;
        }

        // Convenience and code simplification loop for processing before action, action, and after action.
        for (j = 0; j < 3; ++j) {

          if (flag_actions[j]) {
            if (recurse->flag & flag_actions[j]) {
              recurse->action((void *) recurse, recurse->listing.directory.array[i], flag_actions[j] | f_directory_recurse_do_flag_directory_e);

              if (F_status_is_error(recurse->state.status)) {
                private_inline_fl_directory_do_handle(recurse, recurse->listing.directory.array[i], flag_actions[j] | f_directory_recurse_do_flag_directory_e);
                if (F_status_is_error(recurse->state.status)) break;
              }
            }
          }
          else {
            recurse->state.status = F_okay;

            if (recurse->depth < recurse->depth_max) {
              ++recurse->depth;

              private_fl_directory_do_recurse(recurse);

              --recurse->depth;

              if (F_status_is_error(recurse->state.status)) break;
            }
            else {
              recurse->action((void *) recurse, recurse->listing.directory.array[i], f_directory_recurse_do_flag_directory_e);

              if (F_status_is_error(recurse->state.status)) {
                private_inline_fl_directory_do_handle(recurse, recurse->listing.directory.array[i], f_directory_recurse_do_flag_directory_e);
                if (F_status_is_error(recurse->state.status)) break;
              }
            }

            // This loop is not considered a loop for breaking and continuing.
            if (recurse->state.status == F_break || recurse->state.status == F_done || recurse->state.status == F_continue) break;
          }

          if (F_status_is_error(recurse->state.status)) break;
          if (recurse->state.status == F_break || recurse->state.status == F_done) break;
          if (recurse->state.status == F_continue) continue;
        } // for

        if (F_status_is_error(recurse->state.status) || recurse->state.status == F_done) break;

        recurse->state.status = F_okay;
      } // for
    }

    recurse->path.used = used_original;

    // Only the directory is to be freed because all others are preserved between recursions.
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &recurse->listing.directory.array, &recurse->listing.directory.used, &recurse->listing.directory.size, &f_string_dynamics_delete_callback);

    recurse->listing.directory.array = directories_original.array;
    recurse->listing.directory.used = directories_original.used;
    recurse->listing.directory.size = directories_original.size;
  }
#endif // !defined(_di_fl_directory_do_)

#if !defined(_di_fl_directory_do_) || !defined(_di_fl_directory_list_)
  f_status_t private_fl_directory_list(const f_string_static_t path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), const bool dereference, f_directory_listing_t * const listing) {

    struct dirent **entity = 0;

    f_status_t status = F_okay;

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
      if (errno == ENOTSUP) return F_status_set_error(F_directory_support_not);

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
        f_memory_resize(1, 0, sizeof(f_char_t), (void **) & entity[i]);

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

      status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &names->array, &names->used, &names->size);
      if (F_status_is_error(status)) break;

      names->array[names->used].used = 0;

      status = f_memory_array_increase_by(name_directory.used + 1, sizeof(f_char_t), (void **) &names->array[names->used].string, &names->array[names->used].used, &names->array[names->used].size);
      if (F_status_is_error(status)) break;

      memcpy(names->array[names->used].string, name_directory.string, sizeof(f_char_t) * name_directory.used);
      names->array[names->used].string[name_directory.used] = 0;
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

    return F_okay;
  }
#endif // !defined(_di_fl_directory_do_) || !defined(_di_fl_directory_list_)

#if !defined(_di_fl_directory_path_push_) || !defined(_di_fl_directory_path_push_dynamic_)
  f_status_t private_fl_directory_path_push(const f_string_static_t source, f_string_dynamic_t * const destination) {

    bool terminated_null = F_false;
    bool separator_prepend = F_false;
    bool separator_append = F_false;

    f_number_unsigned_t total = 0;
    f_number_unsigned_t start = 0;
    f_number_unsigned_t length_truncated = source.used;
    f_status_t status = F_okay;

    {
      f_number_unsigned_t i = 0;
      f_number_unsigned_t j = 0;

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

        status = f_memory_array_resize(destination->used + total, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
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

    return F_okay;
  }
#endif // !defined(_di_fl_directory_path_push_) || !defined(_di_fl_directory_path_push_dynamic_)

#ifdef __cplusplus
} // extern "C"
#endif
