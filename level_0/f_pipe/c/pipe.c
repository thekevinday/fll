/* FLL - Level 0
 * Project:       Pipe
 * Version:       0.4.3
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provides pipe functionality.
 */
#include <level_0/pipe.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_f_pipe_exists_
  // returns f_true if the standard input contains piped data.
  f_return_status f_pipe_exists() {
    struct stat st_info;

    if (fstat(fileno(f_pipe), &st_info) != 0) {
      return f_error_set_error(f_file_stat_error);
    }

    if (S_ISFIFO(st_info.st_mode)) {
      return f_true;
    }

    return f_false;
  }
#endif // _di_f_pipe_exists_

#ifdef __cplusplus
} // extern "C"
#endif
