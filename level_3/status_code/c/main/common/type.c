#include "../status_code.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_status_code_main_data_delete_
  void status_code_main_delete(status_code_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);
    status_code_setting_delete(&main->setting);
  }
#endif // _di_status_code_main_data_delete_

#ifndef _di_status_code_setting_delete_
  f_status_t status_code_setting_delete(status_code_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    return F_none;
  }
#endif // _di_status_code_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif
