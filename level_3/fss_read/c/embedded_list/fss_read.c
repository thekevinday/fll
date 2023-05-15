#include "fss_read.h"
#include "../main/fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_embedded_list_process_help_
  void fss_read_embedded_list_process_help(void * const void_main) {

    if (!void_main) return;

    fss_read_embedded_list_print_help(&((fss_read_main_t *) void_main)->program.message);
  }
#endif // _di_fss_read_embedded_list_process_help_

#ifdef __cplusplus
} // extern "C"
#endif
