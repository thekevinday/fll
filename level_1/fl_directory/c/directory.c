#include <level_1/directory.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_directory_list_
  f_return_status fl_directory_list(const f_string directory_path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), f_string_dynamics *names) {
    #ifndef _di_level_1_parameter_checking_
      if (names == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    struct dirent **listing = 0;
    int length = 0;
    int i = 0;
    f_string_length size = 0;
    f_status status = f_none;

    length = scandir(directory_path, &listing, filter, sort);

    for (; i < length; i++) {
      size = strnlen(listing[i]->d_name, fl_directory_name_max);

      // There is no reason to include "." and ".." in the directory listing.
      if (strncmp(listing[i]->d_name, "..", 3) == 0 || strncmp(listing[i]->d_name, ".", 2) == 0) {
        f_memory_delete((void **) & listing[i], sizeof(char *), 1);
        continue;
      }

      if (names->used >= names->size) {
        f_macro_string_dynamics_resize(status, (*names), names->size + fl_directory_default_allocation_step);

        if (f_status_is_error(status)) {
          f_status status2 = f_none;

          for (int j = i; j < length; j++) {
            f_memory_delete((void **) & listing[i], sizeof(char *), 1);
          }

          f_macro_string_dynamics_delete(status2, (*names));
          f_memory_delete((void **) & listing, sizeof(struct dirent *), 1);

          return status;
        }
      }

      f_macro_string_dynamic_new(status, names->array[names->used], size);

      if (f_status_is_error(status)) {
        f_status status2 = f_none;

        for (int j = i; j < length; j++) {
          f_memory_delete((void **) & listing[i], sizeof(char *), 1);
        }

        f_macro_string_dynamics_delete(status2, (*names));
        f_memory_delete((void **) & listing, sizeof(struct dirent *), 1);

        return status;
      }

      memcpy(names->array[names->used].string, listing[i]->d_name, size);
      names->array[names->used].used = size;
      names->used++;

      f_memory_delete((void **) & listing[i], sizeof(char *), 1);
    } // for

    for (int j = i; j < length; j++) {
      f_memory_delete((void **) & listing[i], sizeof(char *), 1);
    }

    f_memory_delete((void **) & listing, sizeof(struct dirent *), 1);

    if (length == 0) {
      return f_no_data;
    }
    else if (length == -1) {
      if (errno == ENOMEM) {
        return f_status_set_error(f_error_allocation);
      }
      else {
        return f_status_set_error(f_failure);
      }
    }

    return f_none;
  }
#endif // _di_fl_directory_list_

#ifdef __cplusplus
} // extern "C"
#endif
