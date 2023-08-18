#include "../fss_identify.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_identify_print_data_id_
  f_status_t fss_identify_print_data_id(fl_print_t * const print, const f_fll_id_t id) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    fss_identify_main_t * const main = (fss_identify_main_t *) print->custom;

    f_file_stream_lock(print->to);

    if (main->setting.flag & fss_identify_main_flag_object_e) {
      f_print((const f_string_t) id.name, id.used, print->to);

      if (main->setting.flag & fss_identify_main_flag_content_e) {
        f_print_dynamic_raw(f_fss_type_header_part5_s, print->to);
      }
    }

    if (main->setting.flag & fss_identify_main_flag_content_e) {
      fl_print_format("%04_ui", print->to, id.type);
    }

    f_print_dynamic_raw(f_string_eol_s, print->to);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fss_identify_print_data_id_

#ifndef _di_fss_identify_print_data_total_
  f_status_t fss_identify_print_data_total(fl_print_t * const print) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    fss_identify_main_t * const main = (fss_identify_main_t *) print->custom;

    fll_print_format("%ul%r", print->to, main->setting.total, f_string_eol_s);

    return F_okay;
  }
#endif // _di_fss_identify_print_data_total_

#ifdef __cplusplus
} // extern "C"
#endif
