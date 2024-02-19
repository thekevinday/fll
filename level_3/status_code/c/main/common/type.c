#include "../status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_status_code_main_delete_
  void status_code_main_delete(status_code_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);
    status_code_setting_delete(&main->setting);
  }
#endif // _di_status_code_main_delete_

#ifndef _di_status_code_setting_delete_
  void status_code_setting_delete(status_code_setting_t * const setting) {

    if (!setting) return;
  }
#endif // _di_status_code_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif
