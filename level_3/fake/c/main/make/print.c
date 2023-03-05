#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_print_now_making_
  f_status_t fake_make_print_now_making(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t fakefile) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[Now making using '%]", print.to, print.set->important, print.set->important);
    fl_print_format("%[%Q%]", print.to, print.set->notable, fakefile, print.set->notable);

    if (setting->modes.used) {
      fl_print_format("%[' with modes '%]", print.to, print.set->important, print.set->important);

      for (f_array_length_t i = 0; i < setting->modes.used; ) {

        fl_print_format("%[%Q%]", print.to, print.set->notable, setting->modes.array[i], print.set->notable);

        if (++i < setting->modes.used) {
          fl_print_format("%[', '%]", print.to, print.set->important, print.set->important);
        }
      } // for
    }

    fl_print_format("%['.%]%r", print.to, print.set->important, print.set->important, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_now_making_

#ifndef _di_fake_make_print_processing_section_
  f_status_t fake_make_print_processing_section(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t buffer, const f_fss_named_t section) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[Processing Section '%]", print.to, print.set->important, print.set->important);
    fl_print_format("%[%/Q%]", print.to, print.set->notable, buffer, section.name, print.set->notable);
    fl_print_format("%['.%]%r", print.to, print.set->important, print.set->important, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_processing_section_

#ifdef __cplusplus
} // extern "C"
#endif
