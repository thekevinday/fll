#include <level_1/console.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _fl_console_parameter_to_string_dynamic_directory_
  f_return_status fl_console_parameter_to_string_dynamic_directory(const f_string argument, f_string_dynamic *directory) {
    #ifndef _di_level_0_parameter_checking_
      if (argument == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_f

    f_status status = F_none;
    f_string_length length = strlen(argument);

    if (length == 0) {
      directory->used = 0;
      return F_none;
    }

    if (length > 1) {
      while (length > 1 && argument[length - 1] == '/') {
        length--;
      } // while

      if (argument[0] == '/') {
        f_string_length begin = 1;

        while (begin < length && argument[begin] == '/') {
          begin++;
        } // while

        length -= begin;

        if (length > 0) {
          length += 2;

          f_macro_string_dynamic_new(status, (*directory), length);
          if (F_status_is_error(status)) return status;

          memcpy(directory->string + 1, argument + begin, length - 2);

          directory->used = length;
          directory->size = length;
          directory->string[0] = '/';
          directory->string[length - 1] = '/';
        }
        else {
          f_macro_string_dynamic_new(status, (*directory), 1);
          if (F_status_is_error(status)) return status;

          directory->used = 1;
          directory->size = 1;
          directory->string[0] = '/';
        }
      }
      else if (length > 3 && argument[0] == '.' && argument[1] == '.' && argument[2] == '/') {
        f_string_length begin = 3;

        while (begin < length && argument[begin] == '/') {
          begin++;
        } // while

        length -= begin;

        if (length > 0) {
          length += 4;

          f_macro_string_dynamic_new(status, (*directory), length);
          if (F_status_is_error(status)) return status;

          memcpy(directory->string + 3, argument + begin, length - 4);

          directory->used = length;
          directory->size = length;
          directory->string[0] = '.';
          directory->string[1] = '.';
          directory->string[2] = '/';
          directory->string[length - 1] = '/';
        }
        else {
          f_macro_string_dynamic_new(status, (*directory), 3);
          if (F_status_is_error(status)) return status;

          directory->used = 3;
          directory->size = 3;
          directory->string[0] = '.';
          directory->string[1] = '.';
          directory->string[2] = '/';
        }
      }
      else if (length > 2 && argument[0] == '.' && argument[1] == '/') {
        f_string_length begin = 2;

        while (begin < length && argument[begin] == '/') {
          begin++;
        } // while

        length -= begin;

        if (length > 0) {
          length += 3;

          f_macro_string_dynamic_new(status, (*directory), length);
          if (F_status_is_error(status)) return status;

          memcpy(directory->string + 2, argument + begin, length - 3);

          directory->used = length;
          directory->size = length;
          directory->string[0] = '.';
          directory->string[1] = '/';
          directory->string[length - 1] = '/';
        }
        else {
          f_macro_string_dynamic_new(status, (*directory), 2);
          if (F_status_is_error(status)) return status;

          directory->used = 2;
          directory->size = 2;
          directory->string[0] = '.';
          directory->string[1] = '/';
        }
      }
      else {
        length++;

        f_macro_string_dynamic_new(status, (*directory), length);
        if (F_status_is_error(status)) return status;

        memcpy(directory->string, argument, length - 1);

        directory->used = length;
        directory->size = length;
        directory->string[length - 1] = '/';
      }
    }
    else if (argument[0] != '/') {
      f_macro_string_dynamic_new(status, (*directory), 2);
      if (F_status_is_error(status)) return status;

      memcpy(directory->string, argument, 2);

      directory->used = 2;
      directory->size = 2;
      directory->string[1] = '/';
    }
    else {
      f_macro_string_dynamic_new(status, (*directory), 1);
      if (F_status_is_error(status)) return status;

      memcpy(directory->string, argument, 1);

      directory->used = 1;
      directory->size = 1;
    }

    return F_none;
  }
#endif // _fl_console_parameter_to_string_dynamic_directory_

#ifndef _fl_console_parameter_to_number_signed_
  f_return_status fl_console_parameter_to_number_signed(const f_string argument, f_number_signed *number) {
    #ifndef _di_level_0_parameter_checking_
      if (argument == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_f

    if (argument[0] == 0) {
      return F_data_not;
    }

    f_string_range range = f_string_range_initialize;
    range.start = 0;
    range.stop = strlen(argument) - 1;

    return f_conversion_string_to_number_signed(argument, number, range);
  }
#endif // _fl_console_parameter_to_number_signed_

#ifndef _fl_console_parameter_to_number_unsigned_
  f_return_status fl_console_parameter_to_number_unsigned(const f_string argument, f_number_unsigned *number) {
    #ifndef _di_level_0_parameter_checking_
      if (argument == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_f

    if (argument[0] == 0) {
      return F_data_not;
    }

    f_string_range range = f_string_range_initialize;
    range.start = 0;
    range.stop = strlen(argument) - 1;

    return f_conversion_string_to_number_unsigned(argument, number, range);
  }
#endif // _fl_console_parameter_to_number_unsigned_

#ifdef __cplusplus
} // extern "C"
#endif
