#include "console.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _fl_console_parameter_to_string_dynamic_directory_
  f_status_t fl_console_parameter_to_string_dynamic_directory(const f_string_static_t argument, f_string_dynamic_t *directory) {
    #ifndef _di_level_1_parameter_checking_
      if (!directory) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_array_length_t length = argument.used;

    if (!length) {
      directory->used = 0;

      return F_none;
    }

    f_status_t status = F_none;

    if (length > 1) {
      while (length > 1 && argument.string[length - 1] == f_path_separator_s.string[0]) {
        --length;
      } // while

      if (argument.string[0] == f_path_separator_s.string[0]) {
        f_array_length_t begin = 1;

        while (begin < length && argument.string[begin] == f_path_separator_s.string[0]) {
          ++begin;
        } // while

        length -= begin;
        directory->used = 0;

        if (length) {
          directory->used = 0;

          status = f_string_dynamic_increase_by(length + 3, directory);
          if (F_status_is_error(status)) return status;

          memcpy(directory->string + 1, argument.string + begin, length);

          directory->string[0] = f_path_separator_s.string[0];
          directory->string[length + 1] = f_path_separator_s.string[0];
          directory->string[length + 2] = 0;
          directory->used = length + 2;
        }
        else {
          status = f_string_dynamic_increase_by(2, directory);
          if (F_status_is_error(status)) return status;

          directory->string[0] = f_path_separator_s.string[0];
          directory->string[length + 1] = 0;
          directory->used = length + 1;
        }
      }
      else if (length > 3 && argument.string[0] == f_path_separator_current_s.string[0] && argument.string[1] == f_path_separator_current_s.string[0] && argument.string[2] == f_path_separator_s.string[0]) {
        f_array_length_t begin = 3;

        while (begin < length && argument.string[begin] == f_path_separator_s.string[0]) {
          ++begin;
        } // while

        length -= begin;
        directory->used = 0;

        if (length) {
          status = f_string_dynamic_increase_by(length + 5, directory);
          if (F_status_is_error(status)) return status;

          memcpy(directory->string + 3, argument.string + begin, length);

          directory->string[0] = f_path_separator_current_s.string[0];
          directory->string[1] = f_path_separator_current_s.string[0];
          directory->string[2] = f_path_separator_s.string[0];
          directory->string[length] = f_path_separator_s.string[0];
          directory->string[length + 4] = 0;
          directory->used = length + 4;
        }
        else {
          status = f_string_dynamic_increase_by(5, directory);
          if (F_status_is_error(status)) return status;

          directory->string[0] = f_path_separator_current_s.string[0];
          directory->string[1] = f_path_separator_current_s.string[0];
          directory->string[2] = f_path_separator_s.string[0];
          directory->string[3] = f_path_separator_s.string[0];
          directory->string[4] = 0;
          directory->used = 4;
        }
      }
      else if (length > 2 && argument.string[0] == f_path_separator_current_s.string[0] && argument.string[1] == f_path_separator_s.string[0]) {
        f_array_length_t begin = 2;

        while (begin < length && argument.string[begin] == f_path_separator_s.string[0]) {
          ++begin;
        } // while

        length -= begin;
        directory->used = 0;

        if (length) {
          status = f_string_dynamic_increase_by(length + 4, directory);
          if (F_status_is_error(status)) return status;

          memcpy(directory->string + 2, argument.string + begin, length);

          directory->string[0] = f_path_separator_current_s.string[0];
          directory->string[1] = f_path_separator_s.string[0];
          directory->string[length] = f_path_separator_s.string[0];
          directory->string[length + 3] = 0;
          directory->used = length + 3;
        }
        else {
          status = f_string_dynamic_increase_by(4, directory);
          if (F_status_is_error(status)) return status;

          directory->string[0] = f_path_separator_current_s.string[0];
          directory->string[1] = f_path_separator_s.string[0];
          directory->string[2] = f_path_separator_s.string[0];
          directory->string[3] = 0;
          directory->used = 3;
        }
      }
      else {
        directory->used = 0;

        status = f_string_dynamic_increase_by(length + 2, directory);
        if (F_status_is_error(status)) return status;

        memcpy(directory->string, argument.string, length);

        directory->string[length] = f_path_separator_s.string[0];
        directory->string[length + 1] = 0;
        directory->used = length + 1;
      }
    }
    else if (argument.string[0] != f_path_separator_s.string[0]) {
      directory->used = 0;

      status = f_string_dynamic_increase_by(2, directory);
      if (F_status_is_error(status)) return status;

      directory->string[0] = f_path_separator_s.string[0];
      directory->string[1] = 0;
      directory->used = 1;
    }
    else {
      directory->used = 0;

      status = f_string_dynamic_increase_by(2, directory);
      if (F_status_is_error(status)) return status;

      directory->string[0] = argument.string[0];
      directory->string[1] = 0;
      directory->used = 1;
    }

    return F_none;
  }
#endif // _fl_console_parameter_to_string_dynamic_directory_

#ifdef __cplusplus
} // extern "C"
#endif
