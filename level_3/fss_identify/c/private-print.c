#include "fss_identify.h"
#include "private-common.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_identify_print_
  void fss_identify_print(fss_identify_main_t * const main, f_fll_id_t id) {

    flockfile(main->output.to.stream);

    if (main->parameters[fss_identify_parameter_object_e].result == f_console_result_found_e || main->parameters[fss_identify_parameter_content_e].result != f_console_result_found_e) {
      f_print(id.name, id.used, main->output.to.stream);

      if (main->parameters[fss_identify_parameter_object_e].result != f_console_result_found_e || main->parameters[fss_identify_parameter_content_e].result == f_console_result_found_e) {
        f_print_terminated(f_fss_type_header_part5_s, main->output.to.stream);
      }
    }

    if (main->parameters[fss_identify_parameter_object_e].result != f_console_result_found_e || main->parameters[fss_identify_parameter_content_e].result == f_console_result_found_e) {
      fl_print_format("%04_ui", main->output.to.stream, id.type);
    }

    f_print_character(f_string_eol_s[0], main->output.to.stream);

    funlockfile(main->output.to.stream);
  }
#endif // _di_fss_identify_print_

#ifdef __cplusplus
} // extern "C"
#endif
