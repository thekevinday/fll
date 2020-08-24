#include "pipe.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_pipe_input_exists_
  f_return_status f_pipe_input_exists() {
    struct stat st_info;

    if (fstat(f_type_descriptor_input, &st_info) != 0) {
      return F_status_set_error(F_file_stat);
    }

    if (S_ISFIFO(st_info.st_mode)) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_pipe_input_exists_

#ifndef _di_f_pipe_warning_exists_
  f_return_status f_pipe_warning_exists() {
    struct stat st_info;

    if (fstat(f_type_descriptor_warning, &st_info) != 0) {
      return F_status_set_error(F_file_stat);
    }

    if (S_ISFIFO(st_info.st_mode)) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_pipe_warning_exists_

#ifndef _di_f_pipe_error_exists_
  f_return_status f_pipe_error_exists() {
    struct stat st_info;

    if (fstat(f_type_descriptor_error, &st_info) != 0) {
      return F_status_set_error(F_file_stat);
    }

    if (S_ISFIFO(st_info.st_mode)) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_pipe_error_exists_

#ifndef _di_f_pipe_debug_exists_
  f_return_status f_pipe_debug_exists() {
    struct stat st_info;

    if (fstat(f_type_descriptor_debug, &st_info) != 0) {
      return F_status_set_error(F_file_stat);
    }

    if (S_ISFIFO(st_info.st_mode)) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_pipe_debug_exists_

#ifdef __cplusplus
} // extern "C"
#endif
