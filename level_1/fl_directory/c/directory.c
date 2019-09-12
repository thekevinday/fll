#include <level_1/directory.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_directory_list_
  // put the names of each file and/or directory inside the names parameter
  f_return_status fl_directory_list(const f_string directory_path, f_string_dynamics *names) {
    #ifndef _di_level_1_parameter_checking_
      if (names == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    struct dirent **listing = 0;
    int length = 0;
    int counter = 0;
    f_string_length size = 0;
    f_status status = f_none;

    length = scandir(directory_path, &listing, 0, alphasort);

    for (; counter < length; counter++) {
        size = strnlen(listing[counter]->d_name, fl_directory_name_max);

        // there is no reason to include "." and ".." in the directory listing
        if (strncmp(listing[counter]->d_name, "..", 3) != 0 && strncmp(listing[counter]->d_name, ".", 2) != 0) {
          if (names->used >= names->size) {
            f_macro_string_dynamics_resize(status, (*names), names->used + fl_directory_default_allocation_step);

            if (f_status_is_error(status)) {
              return status;
            }
          }

          f_macro_string_dynamic_resize(status, names->array[names->used], size);
          if (f_status_is_error(status)) {
            return status;
          }

          memcpy(names->array[names->used].string, listing[counter]->d_name, sizeof(int8_t) * size);
          names->array[names->used].used = size;
          names->used++;
        }

        // FIXME: the second and third paramater are probably wrong
        f_memory_delete((void **) & listing[counter], sizeof(struct dirent), 0);
    }

    // FIXME: the second and third paramater are probably wrong
    f_memory_delete((void **) & listing, sizeof(struct dirent *), 0);

    if (length == 0) {
      // an empty directory
      return f_no_data;
    }
    else if (length == -1) {
      if (errno == ENOMEM) return f_status_set_error(f_allocation_error);
      else return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // _di_fl_directory_list_

#ifdef __cplusplus
} // extern "C"
#endif
