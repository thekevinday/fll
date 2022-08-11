#include "pipe.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_pipe_error_exists_
  f_status_t f_pipe_error_exists(void) {

    struct stat st_info;

    memset(&st_info, 0, sizeof(struct stat));

    if (fstat(F_type_descriptor_error_d, &st_info) != 0) {
      return F_status_set_error(F_file_stat);
    }

    return S_ISFIFO(st_info.st_mode) ? F_true : F_false;
  }
#endif // _di_f_pipe_error_exists_

#ifndef _di_f_pipe_input_exists_
  f_status_t f_pipe_input_exists(void) {

    struct stat st_info;

    memset(&st_info, 0, sizeof(struct stat));

    if (fstat(F_type_descriptor_input_d, &st_info) != 0) {
      return F_status_set_error(F_file_stat);
    }

    return S_ISFIFO(st_info.st_mode) ? F_true : F_false;
  }
#endif // _di_f_pipe_input_exists_

#ifndef _di_f_pipe_output_exists_
  f_status_t f_pipe_output_exists(void) {

    struct stat st_info;

    memset(&st_info, 0, sizeof(struct stat));

    if (fstat(F_type_descriptor_output_d, &st_info) != 0) {
      return F_status_set_error(F_file_stat);
    }

    return S_ISFIFO(st_info.st_mode) ? F_true : F_false;
  }
#endif // _di_f_pipe_output_exists_

#ifdef __cplusplus
} // extern "C"
#endif
