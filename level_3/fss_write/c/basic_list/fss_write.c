#include "fss_write.h"
#include "private-common.h"
#include "private-write.h"
#include "../main/fss_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_write_basic_list_process_help_
  void fss_write_basic_list_process_help(fll_program_data_t * const main, void * const setting) {

    fss_write_basic_list_print_help((fss_write_setting_t *) setting, main->message);
  }
#endif // _di_fss_write_basic_list_process_help_

#ifndef _di_fss_write_basic_list_process_normal_
  void fss_write_basic_list_process_normal(fll_program_data_t * const main, void * const setting) {

    // @todo
  }
#endif // _di_fss_write_basic_list_process_normal_

#ifndef _di_fss_write_basic_list_process_pipe_
  void fss_write_basic_list_process_pipe(fll_program_data_t * const main, void * const setting) {

    // @todo
  }
#endif // _di_fss_write_basic_list_process_pipe_

#ifdef __cplusplus
} // extern "C"
#endif
