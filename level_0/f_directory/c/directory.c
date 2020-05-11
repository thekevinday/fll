#include <level_0/directory.h>
#include "private-directory.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_directory_list_
  f_return_status f_directory_list(const f_string path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), f_string_dynamics *names) {
    #ifndef _di_level_0_parameter_checking_
      if (names == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    struct dirent **listing = 0;
    size_t i = 0;
    f_string_length size = 0;
    f_status status = f_none;

    const size_t length = scandir(path, &listing, filter, sort);

    if (length == -1) {
      if (errno == ENOMEM) return f_status_set_error(f_error_allocation);
      else return f_status_set_error(f_failure);
    }

    for (; i < length; i++) {
      size = strnlen(listing[i]->d_name, f_directory_name_max);

      // There is no reason to include "." and ".." in the directory listing.
      if (strncmp(listing[i]->d_name, "..", 3) == 0 || strncmp(listing[i]->d_name, ".", 2) == 0)  {
        f_memory_delete((void **) & listing[i], sizeof(char *), 1);
        continue;
      }

      if (names->used >= names->size) {
        f_macro_string_dynamics_resize(status, (*names), names->size + f_directory_default_allocation_step);
        if (f_status_is_error(status)) break;
      }

      f_macro_string_dynamic_new(status, names->array[names->used], size);
      if (f_status_is_error(status)) break;

      memcpy(names->array[names->used].string, listing[i]->d_name, size);
      names->array[names->used].used = size;
      names->used++;

      f_memory_delete((void **) & listing[i], sizeof(char *), 1);
    } // for

    for (; i < length; i++) {
      f_memory_delete((void **) & listing[i], sizeof(char *), 1);
    } // for

    f_memory_delete((void **) & listing, sizeof(struct dirent *), 1);

    if (f_status_is_error(status)) return status;
    if (length == 0) return f_no_data;

    return f_none;
  }
#endif // _di_f_directory_list_

#ifndef _di_f_directory_remove_
  f_return_status f_directory_remove(const f_string path, const int recursion_max, const bool preserve) {
    #ifndef _di_level_0_parameter_checking_
      if (recursion_max < 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    int result = 0;

    if (recursion_max) {
      result = nftw(path, private_f_directory_remove_recursively, recursion_max, FTW_DEPTH | FTW_PHYS);

      if (result == 0 && !preserve) {
        result = remove(path);
      }
    }
    else {
      // Not recursively deleting and the path is requested to be preserved, so there is nothing to delete.
      if (preserve) return f_none;

      result = remove(path);
    }

    if (result < 0) {
      if (errno == EACCES) {
        return f_status_set_error(f_access_denied);
      }
      else if (errno == EBUSY) {
        return f_status_set_error(f_busy);
      }
      else if (errno == EIO) {
        return f_status_set_error(f_error_input_output);
      }
      else if (errno == EISDIR) {
        return f_status_set_error(f_file_is_type_directory);
      }
      else if (errno == ELOOP) {
        return f_status_set_error(f_loop);
      }
      else if (errno == ENAMETOOLONG || errno == EFAULT) {
        return f_status_set_error(f_invalid_name);
      }
      else if (errno == ENOENT) {
        return f_status_set_error(f_file_not_found);
      }
      else if (errno == ENOMEM) {
        return f_status_set_error(f_out_of_memory);
      }
      else if (errno == ENOTDIR) {
        return f_status_set_error(f_invalid_directory);
      }
      else if (errno == EPERM) {
        return f_status_set_error(f_prohibited);
      }
      else if (errno == EROFS) {
        return f_status_set_error(f_read_only);
      }
      else if (errno == EOVERFLOW) {
        return f_status_set_error(f_number_overflow);
      }
      else if (errno == EMFILE) {
        return f_status_set_error(f_file_max_descriptors);
      }
      else if (errno == ENFILE) {
        return f_status_set_error(f_file_max_open);
      }
      else if (errno == EINVAL) {
        return f_status_set_error(f_invalid_parameter);
      }

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // _di_f_directory_remove_

#ifndef _di_f_directory_remove_custom_
  f_return_status f_directory_remove_custom(const f_string path, const int recursion_max, const bool preserve, int (*custom) (const char *, const struct stat *, int, struct FTW *)) {
    #ifndef _di_level_0_parameter_checking_
      if (recursion_max < 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    int result = 0;

    if (recursion_max) {
      result = nftw(path, custom, recursion_max, FTW_DEPTH | FTW_PHYS);

      if (result == 0 && !preserve) {
        result = remove(path);
      }
    }
    else {
      // Not recursively deleting and the path is requested to be preserved, so there is nothing to delete.
      if (preserve) return f_none;

      result = remove(path);
    }

    if (result < 0) {
      if (errno == EACCES) {
        return f_status_set_error(f_access_denied);
      }
      else if (errno == EBUSY) {
        return f_status_set_error(f_busy);
      }
      else if (errno == EIO) {
        return f_status_set_error(f_error_input_output);
      }
      else if (errno == EISDIR) {
        return f_status_set_error(f_file_is_type_directory);
      }
      else if (errno == ELOOP) {
        return f_status_set_error(f_loop);
      }
      else if (errno == ENAMETOOLONG || errno == EFAULT) {
        return f_status_set_error(f_invalid_name);
      }
      else if (errno == ENOENT) {
        return f_status_set_error(f_file_not_found);
      }
      else if (errno == ENOMEM) {
        return f_status_set_error(f_out_of_memory);
      }
      else if (errno == ENOTDIR) {
        return f_status_set_error(f_invalid_directory);
      }
      else if (errno == EPERM) {
        return f_status_set_error(f_prohibited);
      }
      else if (errno == EROFS) {
        return f_status_set_error(f_read_only);
      }
      else if (errno == EOVERFLOW) {
        return f_status_set_error(f_number_overflow);
      }
      else if (errno == EMFILE) {
        return f_status_set_error(f_file_max_descriptors);
      }
      else if (errno == ENFILE) {
        return f_status_set_error(f_file_max_open);
      }
      else if (errno == EINVAL) {
        return f_status_set_error(f_invalid_parameter);
      }

      return f_status_set_error(f_failure);
    }

    return f_none;
  }
#endif // _di_f_directory_remove_custom_

#ifdef __cplusplus
} // extern "C"
#endif
