#include "file.h"
#include "private-file.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fll_file_mode_set_all_)
  f_return_status private_fll_file_mode_set_all(const f_string_t path, const mode_t mode, const f_number_unsigned_t depth_max, const f_number_unsigned_t depth) {
    f_status_t status = F_none;

    status = f_directory_is(path);
    if (F_status_is_error(status)) return status;

    if (status == F_false) {
      return f_file_mode_set(path, mode);
    }

    f_directory_listing_t listing = f_directory_listing_t_initialize;

    status = fl_directory_list(path, 0, 0, F_false, &listing);

    if (F_status_is_error(status)) {
      f_macro_directory_listing_t_delete_simple(listing);
      return status;
    }

    status = F_none;

    const f_string_length_t path_length = strnlen(path, f_path_max);

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

      for (; i < 7; i++) {

        for (j = 0; F_status_is_fine(status) && j < list[i]->used; j++) {

          const f_string_length_t length = path_length + list[i]->array[j].used + 1;

          char path_sub[length + 1];

          memcpy(path_sub, path, path_length);
          memcpy(path_sub + path_length + 1, list[i]->array[j].string, list[i]->array[j].used);

          path_sub[path_length] = f_path_separator[0];
          path_sub[length] = 0;

          status = f_file_mode_set(path_sub, mode);
        } // for

        f_macro_string_dynamics_t_delete_simple((*list[i]));
      } // for
    }

    f_macro_string_dynamics_t_delete_simple(listing.unknown);

    for (f_array_length_t i = 0; F_status_is_fine(status) && i < listing.directory.used; i++) {

      const f_string_length_t length = path_length + listing.directory.array[i].used + 1;

      char path_sub[length + 1];

      memcpy(path_sub, path, path_length);
      memcpy(path_sub + path_length + 1, listing.directory.array[i].string, listing.directory.array[i].used);

      path_sub[path_length] = f_path_separator[0];
      path_sub[length] = 0;

      status = f_directory_exists(path_sub);
      if (F_status_is_error(status)) break;

      if (status == F_false) {
        status = F_status_set_error(F_directory);
        break;
      }

      if (depth < depth_max) {
        status = private_fll_file_mode_set_all(path_sub, mode, depth_max, depth + 1);
        if (F_status_is_error(status)) break;
      }
    } // for

    f_macro_string_dynamics_t_delete_simple(listing.directory);

    if (F_status_is_error(status)) {
      return status;
    }

    return f_file_mode_set(path, mode);
  }
#endif // !defined(_di_fll_file_mode_set_all_)

#if !defined(_di_fll_file_role_change_all_)
  f_return_status private_fll_file_role_change_all(const f_string_t path, const uid_t uid, const gid_t gid, const bool dereference, const f_number_unsigned_t depth_max, const f_number_unsigned_t depth) {
    f_status_t status = F_none;

    status = f_directory_is(path);
    if (F_status_is_error(status)) return status;

    if (status == F_false) {
      return f_file_role_change(path, uid, gid, dereference);
    }

    f_directory_listing_t listing = f_directory_listing_t_initialize;

    status = fl_directory_list(path, 0, 0, F_false, &listing);

    if (F_status_is_error(status)) {
      f_macro_directory_listing_t_delete_simple(listing);
      return status;
    }

    status = F_none;

    const f_string_length_t path_length = strnlen(path, f_path_max);

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

      for (; i < 7; i++) {

        for (j = 0; F_status_is_fine(status) && j < list[i]->used; j++) {

          const f_string_length_t length = path_length + list[i]->array[j].used + 1;

          char path_sub[length + 1];

          memcpy(path_sub, path, path_length);
          memcpy(path_sub + path_length + 1, list[i]->array[j].string, list[i]->array[j].used);

          path_sub[path_length] = f_path_separator[0];
          path_sub[length] = 0;

          status = f_file_role_change(path_sub, uid, gid, dereference);
        } // for

        f_macro_string_dynamics_t_delete_simple((*list[i]));
      } // for
    }

    for (f_array_length_t i = 0; F_status_is_fine(status) && i < listing.directory.used; i++) {

      const f_string_length_t length = path_length + listing.directory.array[i].used + 1;

      char path_sub[length + 1];

      memcpy(path_sub, path, path_length);
      memcpy(path_sub + path_length + 1, listing.directory.array[i].string, listing.directory.array[i].used);

      path_sub[path_length] = f_path_separator[0];
      path_sub[length] = 0;

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

    f_macro_string_dynamics_t_delete_simple(listing.directory);

    if (F_status_is_error(status)) {
      return status;
    }

    return f_file_role_change(path, uid, gid, dereference);
  }
#endif // !defined(_di_fll_file_role_change_all_)

#ifdef __cplusplus
} // extern "C"
#endif
