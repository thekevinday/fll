#include "pipe.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_pipe_input_exists_
  f_status_t f_pipe_input_exists(void) {
    struct stat st_info;

    if (fstat(F_type_descriptor_input_d, &st_info) != 0) {
      return F_status_set_error(F_file_stat);
    }

    if (S_ISFIFO(st_info.st_mode)) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_pipe_input_exists_

#ifndef _di_f_pipe_warning_exists_
  f_status_t f_pipe_warning_exists(void) {
    struct stat st_info;

    if (fstat(F_type_descriptor_warning_d, &st_info) != 0) {
      return F_status_set_error(F_file_stat);
    }

    if (S_ISFIFO(st_info.st_mode)) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_pipe_warning_exists_

#ifndef _di_f_pipe_error_exists_
  f_status_t f_pipe_error_exists(void) {
    struct stat st_info;

    if (fstat(F_type_descriptor_error_d, &st_info) != 0) {
      return F_status_set_error(F_file_stat);
    }

    if (S_ISFIFO(st_info.st_mode)) {
      return F_true;
    }

    return F_false;
  }
#endif // _di_f_pipe_error_exists_

#ifndef _di_f_pipe_debug_exists_
  f_status_t f_pipe_debug_exists(void) {
    struct stat st_info;

    if (fstat(F_type_descriptor_debug_d, &st_info) != 0) {
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
