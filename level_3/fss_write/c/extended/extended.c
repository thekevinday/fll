#include "fss_write_extended.h"
#include "private-common.h"
#include "private-extended.h"
#include "../main/fss_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_write_extended_process_help_
  void fss_write_extended_process_help(fll_program_data_t * const main, fss_write_setting_t * const setting) {

    fss_write_extended_print_help(main, setting);
  }
#endif // _di_fss_write_extended_process_help_

#ifdef __cplusplus
} // extern "C"
#endif
