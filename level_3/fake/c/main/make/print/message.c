#include "../../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_print_message_now_making_
  f_status_t fake_make_print_message_now_making(fl_print_t * const print, const f_string_static_t fakefile) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    fake_main_t * const main = (fake_main_t *) print->custom;

    f_file_stream_lock(print->to);

    fl_print_format("%[Now making using '%]", print->to, print->set->important, print->set->important);
    fl_print_format("%[%Q%]", print->to, print->set->notable, fakefile, print->set->notable);

    if (main->setting.modes.used) {
      fl_print_format("%[' with modes '%]", print->to, print->set->important, print->set->important);

      for (f_number_unsigned_t i = 0; i < main->setting.modes.used; ) {

        fl_print_format("%[%Q%]", print->to, print->set->notable, main->setting.modes.array[i], print->set->notable);

        if (++i < main->setting.modes.used) {
          fl_print_format("%[', '%]", print->to, print->set->important, print->set->important);
        }
      } // for
    }

    fl_print_format("%['.%]%r", print->to, print->set->important, print->set->important, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fake_make_print_message_now_making_

#ifndef _di_fake_make_print_message_processing_section_
  f_status_t fake_make_print_message_processing_section(fl_print_t * const print, const f_string_static_t buffer, const f_fss_named_t section) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%r%[Processing Section '%]", print->to, f_string_eol_s, print->set->important, print->set->important);
    fl_print_format("%[%/Q%]", print->to, print->set->notable, buffer, section.name, print->set->notable);
    fl_print_format("%['.%]%r", print->to, print->set->important, print->set->important, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fake_make_print_message_processing_section_

#ifdef __cplusplus
} // extern "C"
#endif
