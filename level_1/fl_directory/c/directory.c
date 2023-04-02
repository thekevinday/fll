#include "directory.h"
#include "private-directory.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_directory_create_
  f_status_t fl_directory_create(const f_string_static_t path, const mode_t mode) {

    if (!path.used) return F_data_not;

    f_status_t status = f_directory_exists(path);
    if (F_status_is_error(status)) return status;
    if (status == F_true) return F_directory_found;

    {
      f_array_length_t at_tree = 0;
      f_array_length_t at_path = 0;
      f_string_static_t tree = f_string_static_t_initialize;

      f_char_t tree_string[path.used + 1];
      tree.string = tree_string;
      tree.used = path.used;
      tree_string[path.used] = 0;

      for (; at_path < path.used; ++at_path) {

        if (at_path && path.string[at_path] == f_path_separator_s.string[0]) {
          memcpy(tree.string, path.string + at_tree, sizeof(f_char_t) * (at_path - at_tree));
          tree.string[at_path - at_tree] = 0;

          status = f_directory_exists(tree);
          if (F_status_is_error(status)) return status;

          if (status == F_false) {
            status = f_directory_create(tree, mode);
            if (F_status_is_error(status)) return status;
          }

          at_tree = at_path;
        }
      } // for
    }

    return f_directory_create(path, mode);
  }
#endif // _di_fl_directory_create_

#ifndef _di_fl_directory_copy_
  void fl_directory_copy(const f_string_static_t source, const f_string_static_t destination, f_directory_recurse_copy_t * const recurse) {
    #ifndef _di_level_1_parameter_checking_
      if (!recurse) return;
    #endif // _di_level_1_parameter_checking_

    recurse->source = recurse->source_top;
    recurse->source_top = &source;
    recurse->destination = recurse->destination_top;
    recurse->destination_top = &destination;
    recurse->depth = 0;
    recurse->state.status = F_none;
    recurse->state.data = (void *) recurse;

    if (!recurse->source_top->used || !recurse->destination_top->used) {
      recurse->state.status = F_data_not;

      if (recurse->state.handle) {
        recurse->state.handle(&recurse->state, (void *) recurse);
      }

      return;
    }

    recurse->state.status = f_directory_exists(*recurse->source_top);

    if (recurse->state.status == F_false) {
      recurse->state.status = F_status_set_error(F_directory_not);
    }

    if (F_status_is_error(recurse->state.status)) {
      if (recurse->state.handle) {
        recurse->state.handle(&recurse->state, (void *) recurse);
      }

      return;
    }

    if (recurse->flag & f_directory_recurse_copy_flag_top_e) {
      if (recurse->flag & f_directory_recurse_copy_flag_clone_e) {
        struct stat source_stat;

        memset(&source_stat, 0, sizeof(struct stat));

        recurse->state.status = f_file_stat(*recurse->source_top, recurse->flag & f_directory_recurse_copy_flag_dereference_e, &source_stat);

        if (F_status_is_error_not(recurse->state.status)) {
          recurse->state.status = f_directory_exists(*recurse->destination_top);
        }

        if (F_status_is_error_not(recurse->state.status)) {
          if (recurse->state.status == F_true) {
            if (recurse->flag & f_directory_recurse_copy_flag_exclusive_e) {
              recurse->state.status = F_status_set_error(F_directory_found);
            }
            else {
              recurse->state.status = f_file_mode_set(*recurse->destination_top, source_stat.st_mode);
            }
          }
          else {
            recurse->state.status = f_directory_create(*recurse->destination_top, source_stat.st_mode);
          }
        }

        if (F_status_is_error_not(recurse->state.status) && (recurse->flag & (f_directory_recurse_copy_flag_group_e | f_directory_recurse_copy_flag_owner_e))) {
          recurse->state.status = f_file_role_change(*recurse->destination_top, (recurse->flag & f_directory_recurse_copy_flag_owner_e) ? source_stat.st_uid : -1, (recurse->flag & f_directory_recurse_copy_flag_group_e) ? source_stat.st_gid : -1, recurse->flag & f_directory_recurse_copy_flag_dereference_e);
        }
      }
      else {
        if (recurse->state.status == F_true) {
          if (recurse->flag & f_directory_recurse_copy_flag_exclusive_e) {
            recurse->state.status = F_status_set_error(F_directory_found);
          }
          else {
            recurse->state.status = f_file_mode_set(*recurse->destination_top, recurse->mode.directory);
          }
        }
        else {
          recurse->state.status = f_directory_create(*recurse->destination_top, recurse->mode.directory);
        }
      }
    }
    else {
      recurse->state.status = f_directory_exists(*recurse->destination_top);

      if (recurse->state.status == F_false) {
        recurse->state.status = F_status_set_error(F_directory_not);
      }
    }

    if (F_status_is_error(recurse->state.status)) {
      if (recurse->state.handle) {
        recurse->state.handle(&recurse->state, (void *) &recurse);
      }

      return;
    }

    if (recurse->max_depth) {
      f_array_length_t i = recurse->source_top->used;

      // Do not allow null termination or trailing path separators in the string's length calculation.
      for (; i > 0; --i) {

        if (!recurse->source_top->string[i - 1]) continue;
        if (recurse->source_top->string[i - 1] == f_path_separator_s.string[0]) continue;

        break;
      } // for

      const f_string_static_t static_source = macro_f_string_static_t_initialize(recurse->source_top->string, recurse->source_top->size, i);

      for (i = recurse->destination_top->used; i > 0; --i) {

        if (!recurse->destination_top->string[i - 1]) continue;
        if (recurse->destination_top->string[i - 1] == f_path_separator_s.string[0]) continue;

        break;
      } // for

      const f_string_static_t static_destination = macro_f_string_static_t_initialize(recurse->destination_top->string, recurse->destination_top->size, i);

      recurse->source = &static_source;
      recurse->destination = &static_destination;
      recurse->depth = 1;

      private_fl_directory_copy_recurse(recurse);

      recurse->source = recurse->source_top;
      recurse->destination = recurse->destination_top;
      recurse->depth = 0;
    }
    else {
      recurse->state.status = F_none;
    }

    if (recurse->state.status == F_none && recurse->verbose) {
      recurse->verbose(*recurse->source, *recurse->destination, (void *) recurse);
    }
    else if (F_status_is_error(recurse->state.status)) {
      if (recurse->state.handle) {
        recurse->state.handle(&recurse->state, (void *) &recurse);
      }
    }
  }
#endif // _di_fl_directory_copy_

#ifndef _di_fl_directory_do_
  void fl_directory_do(const f_string_static_t path, f_directory_recurse_do_t * const recurse) {
    #ifndef _di_level_1_parameter_checking_
      if (!recurse) return;

      if (!recurse->action) {
        recurse->state.status = F_status_set_error(F_parameter);

        if (recurse->handle) {
          recurse->handle((void *) recurse, path, f_directory_recurse_do_flag_top_e | f_directory_recurse_do_flag_path_e);
        }
        else if (recurse->state.handle) {
          recurse->state.handle(&recurse->state, (void *) recurse);
        }

        return;
      }
    #endif // _di_level_1_parameter_checking_

    recurse->path = recurse->path_top;
    recurse->path_top = &path;
    recurse->depth = 0;
    recurse->state.status = F_none;
    recurse->state.data = (void *) recurse;

    if (!recurse->path_top->used) {
      recurse->state.status = F_data_not;

      if (recurse->handle) {
        recurse->handle((void *) recurse, path, f_directory_recurse_do_flag_top_e | f_directory_recurse_do_flag_path_e);
      }
      else if (recurse->state.handle) {
        recurse->state.handle(&recurse->state, (void *) recurse);
      }

      return;
    }

    recurse->state.status = f_directory_exists(*recurse->path_top);

    if (recurse->state.status == F_false) {
      recurse->state.status = F_status_set_error(F_directory_not);
    }

    if (F_status_is_error(recurse->state.status)) {
      if (recurse->handle) {
        recurse->handle((void *) recurse, path, f_directory_recurse_do_flag_top_e | f_directory_recurse_do_flag_path_e);
      }
      else if (recurse->state.handle) {
        recurse->state.handle(&recurse->state, (void *) recurse);
      }

      return;
    }

    if ((recurse->flag & f_directory_recurse_do_flag_top_e) && (recurse->flag & f_directory_recurse_do_flag_first_e)) {
      recurse->action((void *) recurse, path, f_directory_recurse_do_flag_top_e | f_directory_recurse_do_flag_first_e | f_directory_recurse_do_flag_path_e);
    }

    if (F_status_is_error_not(recurse->state.status)) {
      if (recurse->max_depth) {
        f_array_length_t i = recurse->path_top->used;

        // Do not allow null termination or trailing path separators in the string's length calculation.
        for (; i > 0; --i) {

          if (!recurse->path_top->string[i - 1]) continue;
          if (recurse->path_top->string[i - 1] == f_path_separator_s.string[0]) continue;

          break;
        } // for

        const f_string_static_t static_path = macro_f_string_static_t_initialize(recurse->path_top->string, recurse->path_top->size, i);

        recurse->path = &static_path;
        recurse->depth = 1;

        private_fl_directory_do_recurse(recurse);

        recurse->path = recurse->path_top;
        recurse->depth = 0;
      }
      else {
        recurse->state.status = F_none;
      }
    }

    if (F_status_is_error_not(recurse->state.status)) {
      if ((recurse->flag & f_directory_recurse_do_flag_top_e) && (recurse->flag & f_directory_recurse_do_flag_last_e)) {
        recurse->action((void *) recurse, path, f_directory_recurse_do_flag_top_e | f_directory_recurse_do_flag_last_e | f_directory_recurse_do_flag_path_e);
      }
    }

    if (F_status_is_error(recurse->state.status)) {
      if (recurse->handle) {
        recurse->handle((void *) recurse, path, f_directory_recurse_do_flag_top_e | f_directory_recurse_do_flag_path_e);
      }
      else if (recurse->state.handle) {
        recurse->state.handle(&recurse->state, (void *) recurse);
      }
    }
    else {
      recurse->state.status = F_none;
    }
  }
#endif // _di_fl_directory_do_

#ifndef _di_fl_directory_list_
  f_status_t fl_directory_list(const f_string_static_t path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), const bool dereference, f_directory_listing_t * const listing) {
    #ifndef _di_level_1_parameter_checking_
      if (!listing) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!path.used) return F_data_not;

    return private_fl_directory_list(path, filter, sort, dereference, listing);
  }
#endif // _di_fl_directory_list_

#ifndef _di_fl_directory_path_pop_
  f_status_t fl_directory_path_pop(f_string_static_t * const path) {
    #ifndef _di_level_1_parameter_checking_
      if (!path) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!path->used) return F_data_not;

    const bool null_terminated = path->string[path->used] == 0;
    bool first_nulless = F_false;

    f_array_length_t i = path->used - 1;
    f_array_length_t j = 0;

    f_status_t status = F_none;

    for (; i > 0; --i) {

      if (!path->string[i]) continue;

      status = f_utf_is_control(path->string + i, path->used - i);
      if (status == F_true) continue;

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_complete_not_utf) continue;

        return status;
      }

      if (first_nulless) {
        if (path->string[i] == f_path_separator_s.string[0]) {
          if (null_terminated) {
            path->string[i + 1] = 0;
            path->used = i + 2;
          }
          else {
            path->used = i + 1;
          }

          return F_none;
        }
      }
      else {
        first_nulless = F_true;

        for (j = i; j > 0; --j) {
          if (!path->string[j]) continue;

          status = f_utf_is_control(path->string + j, path->used - j);
          if (status == F_true) continue;

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_complete_not_utf) continue;

            return status;
          }

          if (path->string[j] != f_path_separator_s.string[0]) {
            i = j + 1;

            break;
          }
        } // for
      }
    } // for

    path->used = 0;

    return F_none;
  }
#endif // _di_fl_directory_path_pop_

#ifndef _di_fl_directory_path_push_
  f_status_t fl_directory_path_push(const f_string_static_t source, f_string_dynamic_t * const destination) {
    #ifndef _di_level_1_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (!source.used) return F_data_not;

    return private_fl_directory_path_push(source, destination);
  }
#endif // _di_fl_directory_path_push_

#ifdef __cplusplus
} // extern "C"
#endif
