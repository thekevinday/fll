/* FLL - Level 1
 * Project:       File
 * Version:       0.2.0
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 */
#include <level_1/file.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fl_file_read_
  f_return_status fl_file_read(f_file file, const f_file_position position, f_dynamic_string *buffer){
    #ifndef _di_level_1_parameter_checking_
      if (buffer == f_null) return f_invalid_parameter;

      if (position.buffer_start   < 0) return f_invalid_parameter;
      if (position.file_start     < 0) return f_invalid_parameter;
      if (position.total_elements < 0) return f_invalid_parameter;
    #endif // _di_level_1_parameter_checking_

    if (file.file == 0) return f_file_not_open;

    f_status        status   = f_status_initialize;
    f_string_length size     = f_string_length_initialize;
    f_bool          infinite = f_false;

    // when total_elements is 0, this means the file read will until EOF is reached
    if (position.total_elements == 0){
      infinite = f_true;
      size = f_file_default_read_size;
    } else {
      size = position.total_elements;
    }

    // populate the buffer
    do{
      f_resize_dynamic_string(status, (*buffer), size);

      if (f_macro_test_for_allocation_errors(status)){
        return status;
      }

      status = f_file_read(&file, buffer, position);

      if (status == f_none_on_eof){
        break;
      } else if (status != f_none){
        return status;
      }

      if (infinite){
        if (size + f_file_default_read_size > f_string_max_size){
          return f_overflow;
        }

        size += f_file_default_read_size;
      }
    } while (infinite);

    return f_none;
  }
#endif // _di_fl_file_read_

#ifdef __cplusplus
} // extern "C"
#endif

