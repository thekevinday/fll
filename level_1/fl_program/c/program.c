#include <level_1/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_program_print_version_
  f_return_status fl_program_print_version(const f_string version) {
    printf("%s\n", version);

    return f_none;
  }
#endif // _di_fl_program_print_version_

#ifdef __cplusplus
} // extern "C"
#endif
