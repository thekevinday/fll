#include <level_0/path.h>
#include "private-path.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_path_change_
  f_return_status f_path_change(const f_string path) {

    if (chdir(path) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_path_change_

#ifndef _di_f_path_change_at_
  f_return_status f_path_change_at(const int at_id) {
    #ifndef _di_level_0_parameter_checking_
      if (at_id <= 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (fchdir(at_id) < 0) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EIO) return F_status_set_error(F_input_output);
      if (errno == ELOOP) return F_status_set_error(F_loop);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ENOTDIR) return F_status_set_error(F_directory);
      if (errno == EBADF) return F_status_set_error(F_directory_descriptor);

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_f_path_change_at_

#ifndef _di_f_path_current_
  f_return_status f_path_current(const bool real, f_string_dynamic *path) {
    #ifndef _di_level_0_parameter_checking_
      if (path == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    char buffer[f_path_max];

    if (!getcwd(buffer, f_path_max)) {
      if (errno == EACCES) return F_status_set_error(F_access_denied);
      if (errno == EFAULT) return F_status_set_error(F_buffer);
      if (errno == EINVAL) return F_status_set_error(F_parameter);
      if (errno == ENAMETOOLONG) return F_status_set_error(F_name);
      if (errno == ENOENT) return F_status_set_error(F_file_found_not);
      if (errno == ENOMEM) return F_status_set_error(F_memory_out);
      if (errno == ERANGE) return F_status_set_error(F_buffer_too_small);

      return F_status_set_error(F_failure);
    }

    if (real) {
      return private_f_path_real(buffer, path);
    }

    const f_string_length length = strnlen(buffer, f_path_max);

    if (length + 1 > path->size) {
      f_status status = F_none;

      f_macro_string_dynamic_new(status, (*path), length + 1);
      if (F_status_is_error(status)) return status;
    }

    memcpy(path->string, buffer, length);

    path->string[length] = 0;
    path->used = length;

    return F_none;
  }
#endif // _di_f_path_current_

#ifndef _di_f_path_explode_
  f_return_status f_path_explode(const f_string path, f_string_dynamics *paths) {
    #ifndef _di_level_0_parameter_checking_
      if (paths == 0) return F_status_set_error(F_parameter);
      if (paths->used > paths->size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = F_none;
    const f_string_length length = strnlen(path, PATH_MAX);

    if (length == 0) {
      // When PATH is "", this is actually a valid search path for PWD.
      // Therefore append an equivalent representation of PWD (string used length is 0).
      f_macro_memory_structure_macro_increment(status, (*paths), 1, f_memory_default_allocation_step, f_macro_string_dynamics_resize, F_buffer_too_large);
      if (F_status_is_error(status)) return status;

      f_macro_string_dynamic_clear(paths->array[paths->used]);
      paths->used++;

      return F_none;
    }

    f_string_length i = length;
    f_string_length first = 0;
    f_string_length total = 0;

    for (i = 0; i <= length; i++) {
      if (i == length || path[i] == f_path_separator_variable[0]) {
        f_macro_memory_structure_macro_increment(status, (*paths), 1, f_memory_default_allocation_step, f_macro_string_dynamics_resize, F_buffer_too_large);
        if (F_status_is_error(status)) return status;

        if (i == 0) {
          f_macro_string_dynamic_clear(paths->array[paths->used]);
          paths->used++;

          first = 1;
          continue;
        }

        f_string_dynamic part = f_string_dynamic_initialize;

        total = i - first;

        if (total > 0) {
          if (path[i - 1] == f_path_separator[0]) {
            f_macro_string_dynamic_new(status, part, total);
            if (F_status_is_error(status)) return status;

            part.used = total;
          }
          else {
            f_macro_string_dynamic_new(status, part, total + 1);
            if (F_status_is_error(status)) return status;

            part.string[total] = f_path_separator[0];
            part.used = total + 1;
          }

          memcpy(part.string, path + first, total);
        }

        paths->array[paths->used].string = part.string;
        paths->array[paths->used].used = part.used;
        paths->array[paths->used].size = part.size;
        paths->used++;

        first = i + 1;
      }
    } // for

    return F_none;
  }
#endif // _di_f_path_explode_

#ifndef _di_f_path_explode_dynamic_
  f_return_status f_path_explode_dynamic(const f_string_static path, f_string_dynamics *paths) {
    #ifndef _di_level_0_parameter_checking_
      if (path.used > path.size) return F_status_set_error(F_parameter);
      if (paths == 0) return F_status_set_error(F_parameter);
      if (paths->used > paths->size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = F_none;

    if (path.used == 0) {
      // When PATH is "", this is actually a valid search path for PWD.
      // Therefore append an equivalent representation of PWD (string used length is 0).
      f_macro_memory_structure_macro_increment(status, (*paths), 1, f_memory_default_allocation_step, f_macro_string_dynamics_resize, F_buffer_too_large);
      if (F_status_is_error(status)) return status;

      f_macro_string_dynamic_clear(paths->array[paths->used]);
      paths->used++;

      return F_none;
    }

    f_string_length i = 0;
    f_string_length j = 0;
    f_string_length first = 0;
    f_string_length total = 0;

    f_string_dynamic part = f_string_dynamic_initialize;

    for (i = 0; i <= path.used; i++) {
      if (i == path.used || path.string[i] == f_path_separator_variable[0]) {
        f_macro_memory_structure_macro_increment(status, (*paths), 1, f_memory_default_allocation_step, f_macro_string_dynamics_resize, F_buffer_too_large);
        if (F_status_is_error(status)) return status;

        if (i == 0) {
          f_macro_string_dynamic_clear(paths->array[paths->used]);
          paths->used++;

          first = 1;
          continue;
        }

        total = i - first;

        if (total > 0) {
          f_macro_string_dynamic_new(status, part, total);
          if (F_status_is_error(status)) return status;

          for (j = 0; j < total; j++) {
            if (path.string[first + j] == 0) continue;

            part.string[part.used] = path.string[first + j];
            part.used++;
          } // for

          if (part.string[part.used - 1] != f_path_separator[0]) {
            f_macro_string_dynamic_resize(status, part, total + 1);
            if (F_status_is_error(status)) return status;

            part.string[part.used] = f_path_separator[0];
            part.used++;
          }
        }

        paths->array[paths->used].string = part.string;
        paths->array[paths->used].used = part.used;
        paths->array[paths->used].size = part.size;
        paths->used++;

        first = i + 1;
      }
    } // for

    return F_none;
  }
#endif // _di_f_path_explode_dynamic_

#ifndef _di_f_path_real_
  f_return_status f_path_real(const f_string path, f_string_dynamic *real) {
    #ifndef _di_level_0_parameter_checking_
      if (real == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_path_real(path, real);
  }
#endif // _di_f_path_real_

#ifndef _di_f_path_explode_reverse_
  f_return_status f_path_explode_reverse(const f_string path, f_string_dynamics *paths) {
    #ifndef _di_level_0_parameter_checking_
      if (paths == 0) return F_status_set_error(F_parameter);
      if (paths->used > paths->size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = F_none;
    const f_string_length length = strnlen(path, PATH_MAX);

    if (length == 0) {
      // When PATH is "", this is actually a valid search path for PWD.
      // Therefore append an equivalent representation of PWD (string used length is 0).
      f_macro_memory_structure_macro_increment(status, (*paths), 1, f_memory_default_allocation_step, f_macro_string_dynamics_resize, F_buffer_too_large);
      if (F_status_is_error(status)) return status;

      paths->array[paths->used].string = 0;
      paths->array[paths->used].used = 0;
      paths->array[paths->used].size = 0;
      paths->used++;

      return F_none;
    }

    f_string_length i = length;
    f_string_length j = length;
    f_string_length last = length;
    f_string_length total = 0;

    f_string_dynamic part = f_string_dynamic_initialize;

    for (; i > 0; i--) {
      j--;

      if (j == 0 || path[j] == f_path_separator_variable[0]) {
        f_macro_memory_structure_macro_increment(status, (*paths), 1, f_memory_default_allocation_step, f_macro_string_dynamics_resize, F_buffer_too_large);
        if (F_status_is_error(status)) return status;

        if (path[j] == f_path_separator_variable[0]) {
          total = last - i;

          if (total > 0) {
            if (path[j + total] == f_path_separator[0]) {
              f_macro_string_dynamic_new(status, part, total);
              if (F_status_is_error(status)) return status;

              part.used = total;
            }
            else {
              f_macro_string_dynamic_new(status, part, total + 1);
              if (F_status_is_error(status)) return status;

              part.string[total] = f_path_separator[0];
              part.used = total + 1;
            }

            memcpy(part.string, path + i, total);
          }

          last = j;
        }
        else if (j == 0) {
          // when j = 0, the total is actually the entire length to max.
          total = last - j;

          if (total > 0) {
            if (path[last - 1] == f_path_separator[0]) {
              f_macro_string_dynamic_new(status, part, total);
              if (F_status_is_error(status)) return status;

              part.used = total;
            }
            else {
              f_macro_string_dynamic_new(status, part, total + 1);
              if (F_status_is_error(status)) return status;

              part.used = total + 1;
              part.string[total] = f_path_separator[0];
            }

            memcpy(part.string, path, total);
          }
        }

        paths->array[paths->used].string = part.string;
        paths->array[paths->used].used = part.used;
        paths->array[paths->used].size = part.size;
        paths->used++;
      }
    } // for

    return F_none;
  }
#endif // _di_f_path_explode_reverse_

#ifndef _di_f_path_explode_reverse_dynamic_
  f_return_status f_path_explode_reverse_dynamic(const f_string_static path, f_string_dynamics *paths) {
    #ifndef _di_level_0_parameter_checking_
      if (path.used > path.size) return F_status_set_error(F_parameter);
      if (paths == 0) return F_status_set_error(F_parameter);
      if (paths->used > paths->size) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = F_none;

    if (path.used == 0) {
      // When PATH is "", this is actually a valid search path for PWD.
      // Therefore append an equivalent representation of PWD (string used length is 0).
      f_macro_memory_structure_macro_increment(status, (*paths), 1, f_memory_default_allocation_step, f_macro_string_dynamics_resize, F_buffer_too_large);
      if (F_status_is_error(status)) return status;

      f_macro_string_dynamic_clear(paths->array[paths->used]);
      paths->used++;

      return F_none;
    }

    f_string_length i = path.used;
    f_string_length j = path.used;
    f_string_length k = 0;
    f_string_length last = path.used;
    f_string_length total = 0;

    f_string_dynamic part = f_string_dynamic_initialize;

    for (; i > 0; i--) {
      j--;

      if (j == 0 || path.string[j] == f_path_separator_variable[0]) {
        f_macro_memory_structure_macro_increment(status, (*paths), 1, f_memory_default_allocation_step, f_macro_string_dynamics_resize, F_buffer_too_large);
        if (F_status_is_error(status)) return status;

        if (path.string[j] == f_path_separator_variable[0]) {
          total = last - i;

          if (total > 0) {
            f_macro_string_dynamic_new(status, part, total);
            if (F_status_is_error(status)) return status;

            for (k = 0; k < total; k++) {
              if (path.string[i + k] == 0) continue;

              part.string[part.used] = path.string[i + k];
              part.used++;
            } // for

            if (part.string[part.used - 1] != f_path_separator[0]) {
              f_macro_string_dynamic_resize(status, part, total + 1);
              if (F_status_is_error(status)) return status;

              part.string[part.used] = f_path_separator[0];
              part.used++;
            }
          }

          last = j;
        }
        else if (j == 0) {
          // when j = 0, the total is actually the entire length to max.
          total = last - j;

          f_macro_string_dynamic_new(status, part, total);
          if (F_status_is_error(status)) return status;

          for (k = 0; k < total; k++) {
            if (path.string[i + k] == 0) continue;

            part.string[part.used] = path.string[i + k];
            part.used++;
          } // for

          if (part.string[part.used - 1] != f_path_separator[0]) {
            f_macro_string_dynamic_resize(status, part, total + 1);
            if (F_status_is_error(status)) return status;

            part.string[part.used - 1] = f_path_separator[0];
            part.used++;
          }
        }

        paths->array[paths->used].string = part.string;
        paths->array[paths->used].used = part.used;
        paths->array[paths->used].size = part.size;
        paths->used++;
      }
    } // for

    return F_none;
  }
#endif // _di_f_path_explode_reverse_dynamic_

#ifdef __cplusplus
} // extern "C"
#endif
