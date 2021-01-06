#include "console.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _fl_console_parameter_to_string_dynamic_directory_
  f_status_t fl_console_parameter_to_string_dynamic_directory(const f_string_t argument, f_string_dynamic_t *directory) {
    #ifndef _di_level_1_parameter_checking_
      if (!argument) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;
    f_string_length_t length = strlen(argument);

    if (!length) {
      directory->used = 0;
      return F_none;
    }

    if (length > 1) {
      while (length > 1 && argument[length - 1] == f_path_separator_s[0]) {
        length--;
      } // while

      if (argument[0] == f_path_separator_s[0]) {
        f_string_length_t begin = 1;

        while (begin < length && argument[begin] == f_path_separator_s[0]) {
          begin++;
        } // while

        length -= begin;

        if (length > 0) {
          length += 2;

          f_macro_string_dynamic_t_new(status, (*directory), length);
          if (F_status_is_error(status)) return status;

          memcpy(directory->string + 1, argument + begin, length - 2);

          directory->used = length;
          directory->size = length;
          directory->string[0] = f_path_separator_s[0];
          directory->string[length - 1] = f_path_separator_s[0];
        }
        else {
          f_macro_string_dynamic_t_new(status, (*directory), 1);
          if (F_status_is_error(status)) return status;

          directory->used = 1;
          directory->size = 1;
          directory->string[0] = f_path_separator_s[0];
        }
      }
      else if (length > 3 && argument[0] == f_path_separator_current_s[0] && argument[1] == f_path_separator_current_s[0] && argument[2] == f_path_separator_s[0]) {
        f_string_length_t begin = 3;

        while (begin < length && argument[begin] == f_path_separator_s[0]) {
          begin++;
        } // while

        length -= begin;

        if (length > 0) {
          length += 4;

          f_macro_string_dynamic_t_new(status, (*directory), length);
          if (F_status_is_error(status)) return status;

          memcpy(directory->string + 3, argument + begin, length - 4);

          directory->used = length;
          directory->size = length;
          directory->string[0] = f_path_separator_current_s[0];
          directory->string[1] = f_path_separator_current_s[0];
          directory->string[2] = f_path_separator_s[0];
          directory->string[length - 1] = f_path_separator_s[0];
        }
        else {
          f_macro_string_dynamic_t_new(status, (*directory), 3);
          if (F_status_is_error(status)) return status;

          directory->used = 3;
          directory->size = 3;
          directory->string[0] = f_path_separator_current_s[0];
          directory->string[1] = f_path_separator_current_s[0];
          directory->string[2] = f_path_separator_s[0];
        }
      }
      else if (length > 2 && argument[0] == f_path_separator_current_s[0] && argument[1] == f_path_separator_s[0]) {
        f_string_length_t begin = 2;

        while (begin < length && argument[begin] == f_path_separator_s[0]) {
          begin++;
        } // while

        length -= begin;

        if (length > 0) {
          length += 3;

          f_macro_string_dynamic_t_new(status, (*directory), length);
          if (F_status_is_error(status)) return status;

          memcpy(directory->string + 2, argument + begin, length - 3);

          directory->used = length;
          directory->size = length;
          directory->string[0] = f_path_separator_current_s[0];
          directory->string[1] = f_path_separator_s[0];
          directory->string[length - 1] = f_path_separator_s[0];
        }
        else {
          f_macro_string_dynamic_t_new(status, (*directory), 2);
          if (F_status_is_error(status)) return status;

          directory->used = 2;
          directory->size = 2;
          directory->string[0] = f_path_separator_current_s[0];
          directory->string[1] = f_path_separator_s[0];
        }
      }
      else {
        length++;

        f_macro_string_dynamic_t_new(status, (*directory), length);
        if (F_status_is_error(status)) return status;

        memcpy(directory->string, argument, length - 1);

        directory->used = length;
        directory->size = length;
        directory->string[length - 1] = f_path_separator_s[0];
      }
    }
    else if (argument[0] != f_path_separator_s[0]) {
      f_macro_string_dynamic_t_new(status, (*directory), 2);
      if (F_status_is_error(status)) return status;

      memcpy(directory->string, argument, 2);

      directory->used = 2;
      directory->size = 2;
      directory->string[1] = f_path_separator_s[0];
    }
    else {
      f_macro_string_dynamic_t_new(status, (*directory), 1);
      if (F_status_is_error(status)) return status;

      memcpy(directory->string, argument, 1);

      directory->used = 1;
      directory->size = 1;
    }

    return F_none;
  }
#endif // _fl_console_parameter_to_string_dynamic_directory_

#ifdef __cplusplus
} // extern "C"
#endif
