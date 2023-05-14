#include "../fss_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_read_print_content_
  f_status_t fss_read_print_content(fl_print_t * const print, const f_string_range_t range, const f_fss_delimits_t delimits) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    fss_read_main_t * const main = (fss_read_main_t *) print->custom,

    f_print_except_in_dynamic_partial(main->setting.buffer, range, delimits, main->setting.comments, print->to);

    return F_none;
  }
#endif _di_fss_read_print_content_

#ifndef _di_fss_read_print_number_
  f_status_t fss_read_print_number(fl_print_t * const print, const f_number_unsigned_t number) {

    if (!print) return F_status_set_error(F_output_not);

    fll_print_format("%ul%r", print->to, number, f_string_eol_s);

    return F_none;
  }
#endif // _di_fss_read_print_number_

#ifndef _di_fss_read_print_object_at_
  f_status_t fss_read_print_object_at(fl_print_t * const print, const f_array_length_t at, const f_fss_delimits_t delimits) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    fss_read_main_t * const main = (fss_read_main_t *) print->custom,

    if (at >= main->setting.objects.used) return F_output_not;

    if (main->setting.flag & fss_read_main_flag_trim_e) {
      fl_print_trim_except_dynamic_partial(main->setting.buffer, main->setting.array[at], delimits, print->to);
    }
    else {
      f_print_except_dynamic_partial(main->setting.buffer, main->setting.array[at], delimits, print->to);
    }

    fss_read_print_object_end(print); // @todo replace with a callback because each standard may have a different Object end.

    return F_none;
  }
#endif // _di_fss_read_print_object_at_

#ifdef __cplusplus
} // extern "C"
#endif
