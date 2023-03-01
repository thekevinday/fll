#include "file.h"
#include "private-file.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fll_file_mode_set_all_)
  f_status_t private_fll_file_mode_set_all(const f_string_static_t path, const bool dereference, const mode_t mode, const f_number_unsigned_t depth_max, const f_number_unsigned_t depth) {

    f_status_t status = F_none;

    status = f_directory_is(path);
    if (F_status_is_error(status)) return status;

    if (status == F_false) {
      return f_file_mode_set(path, mode);
    }

    f_directory_listing_t listing = f_directory_listing_t_initialize;

    status = fl_directory_list(path, 0, 0, dereference, &listing);

    if (F_status_is_error(status)) {
      f_directory_listing_delete(&listing);

      return status;
    }

    status = F_none;

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
      f_string_static_t path_sub = f_string_static_t_initialize;

      for (; i < 7; ++i) {

        for (j = 0; F_status_is_fine(status) && j < list[i]->used; ++j) {

          path_sub.used = path.used + list[i]->array[j].used + 1;

          f_char_t path_sub_string[path_sub.used + 1];
          path_sub.string = path_sub_string;

          memcpy(path_sub.string, path.string, sizeof(f_char_t) * path.used);
          memcpy(path_sub.string + path.used + 1, list[i]->array[j].string, sizeof(f_char_t) * list[i]->array[j].used);

          path_sub.string[path.used] = f_path_separator_s.string[0];
          path_sub.string[path_sub.used] = 0;

          status = f_file_mode_set(path_sub, mode);
        } // for

        f_string_dynamics_resize(0, list[i]);
      } // for
    }

    f_string_dynamics_resize(0, &listing.unknown);

    f_string_static_t path_sub = f_string_static_t_initialize;

    for (f_array_length_t i = 0; F_status_is_fine(status) && i < listing.directory.used; ++i) {

      path_sub.used = path.used + listing.directory.array[i].used + 1;

      f_char_t path_sub_string[path_sub.used + 1];
      path_sub.string = path_sub_string;

      memcpy(path_sub.string, path.string, sizeof(f_char_t) * path.used);
      memcpy(path_sub.string + path.used + 1, listing.directory.array[i].string, sizeof(f_char_t) * listing.directory.array[i].used);

      path_sub.string[path.used] = f_path_separator_s.string[0];
      path_sub.string[path_sub.used] = 0;

      status = f_directory_exists(path_sub);
      if (F_status_is_error(status)) break;

      if (status == F_false) {
        status = F_status_set_error(F_directory);

        break;
      }

      if (depth < depth_max) {
        status = private_fll_file_mode_set_all(path_sub, dereference, mode, depth_max, depth + 1);
        if (F_status_is_error(status)) break;
      }
    } // for

    f_directory_listing_delete(&listing);

    if (F_status_is_error(status)) return status;

    return f_file_mode_set(path, mode);
  }
#endif // !defined(_di_fll_file_mode_set_all_)

#if !defined(_di_fll_file_role_change_all_)
  f_status_t private_fll_file_role_change_all(const f_string_static_t path, const uid_t uid, const gid_t gid, const bool dereference, const f_number_unsigned_t depth_max, const f_number_unsigned_t depth) {

    f_status_t status = F_none;

    status = f_directory_is(path);
    if (F_status_is_error(status)) return status;

    if (status == F_false) {
      return f_file_role_change(path, uid, gid, dereference);
    }

    f_directory_listing_t listing = f_directory_listing_t_initialize;

    status = fl_directory_list(path, 0, 0, dereference, &listing);

    if (F_status_is_error(status)) {
      f_directory_listing_delete(&listing);

      return status;
    }

    status = F_none;

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
      f_string_static_t path_sub = f_string_static_t_initialize;

      for (; i < 7; ++i) {

        for (j = 0; F_status_is_fine(status) && j < list[i]->used; ++j) {

          path_sub.used = path.used + list[i]->array[j].used + 1;

          f_char_t path_sub_string[path_sub.used + 1];
          path_sub.string = path_sub_string;

          memcpy(path_sub.string, path.string, sizeof(f_char_t) * path.used);
          memcpy(path_sub.string + path.used + 1, list[i]->array[j].string, sizeof(f_char_t) * list[i]->array[j].used);

          path_sub.string[path.used] = f_path_separator_s.string[0];
          path_sub.string[path_sub.used] = 0;

          status = f_file_role_change(path_sub, uid, gid, dereference);
        } // for

        f_string_dynamics_resize(0, list[i]);
      } // for
    }

    {
      f_string_static_t path_sub = f_string_static_t_initialize;

      for (f_array_length_t i = 0; F_status_is_fine(status) && i < listing.directory.used; ++i) {

        path_sub.used = path.used + listing.directory.array[i].used + 1;

        f_char_t path_sub_string[path_sub.used + 1];
        path_sub.string = path_sub_string;

        memcpy(path_sub.string, path.string, sizeof(f_char_t) * path.used);
        memcpy(path_sub.string + path.used + 1, listing.directory.array[i].string, sizeof(f_char_t) * listing.directory.array[i].used);

        path_sub.string[path.used] = f_path_separator_s.string[0];
        path_sub.string[path_sub.used] = 0;

        status = f_directory_exists(path_sub);
        if (F_status_is_error(status)) break;

        if (status == F_false) {
          status = F_status_set_error(F_directory);

          break;
        }

        if (depth < depth_max) {
          status = private_fll_file_role_change_all(path_sub, uid, gid, dereference, depth_max, depth + 1);
          if (F_status_is_error(status)) break;
        }
      } // for
    }

    f_directory_listing_delete(&listing);

    if (F_status_is_error(status)) return status;

    return f_file_role_change(path, uid, gid, dereference);
  }
#endif // !defined(_di_fll_file_role_change_all_)

#ifdef __cplusplus
} // extern "C"
#endif
