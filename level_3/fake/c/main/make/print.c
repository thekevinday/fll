#include "../fake.h"
#include "print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_print_now_making_
  f_status_t fake_make_print_now_making(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t fakefile) {

    if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

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

#ifndef _di_fake_make_print_operate_break_verbose_
  f_status_t fake_make_print_operate_break_verbose(fake_setting_t * const setting, const fl_print_t print, const f_string_statics_t arguments) {

    if (print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("Breaking as '", print.to);
    fl_print_format("%[%Q%]", print.to, print.set->notable, arguments.used ? arguments.array[0] : fake_make_operation_argument_success_s, print.set->notable);
    fl_print_format("'.%r", print.to, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_operate_break_verbose_

#ifndef _di_fake_make_print_operate_copy_verbose_
  f_status_t fake_make_print_operate_copy_verbose(fake_setting_t * const setting, const fl_print_t print, const bool clone, const f_string_static_t source, const f_string_static_t destination) {

    if (print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%s '%[%Q%]' to '", print.to, clone ? "Cloned" : "Copied", print.set->notable, source, print.set->notable);
    fl_print_format("%[%Q%]'.%r", print.to, print.set->notable, destination, print.set->notable, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_operate_copy_verbose_

#ifndef _di_fake_make_print_operate_define_verbose_
  f_status_t fake_make_print_operate_define_verbose(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t variable) {

    if (print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fll_print_format("Defined environment variable '%[%Q%]'.%r", print.to, print.set->notable, variable, print.set->notable, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_operate_define_verbose_

#ifndef _di_fake_make_print_operate_delete_verbose_
  f_status_t fake_make_print_operate_delete_verbose(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path) {

    if (print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fll_print_format("Removed '%[%Q%]'.%r", print.to, print.set->notable, path, print.set->notable, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_operate_delete_verbose_

#ifndef _di_fake_make_print_operate_file_not_found_verbose_
  f_status_t fake_make_print_operate_file_not_found_verbose(fake_setting_t * const setting, const fl_print_t print, const bool is_directory, const f_string_static_t file) {

    if (print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("The %s '%[%Q%]' is not found.%]%r", print.to, print.notable, is_directory ? "directory" : "file", file, print.notable, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_operate_file_not_found_verbose_

#ifndef _di_fake_make_print_processing_section_
  f_status_t fake_make_print_processing_section(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t buffer, const f_fss_named_t section) {

    if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[Processing Section '%]", print.to, print.set->important, print.set->important);
    fl_print_format("%[%/Q%]", print.to, print.set->notable, buffer, section.name, print.set->notable);
    fl_print_format("%['.%]%r", print.to, print.set->important, print.set->important, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_processing_section_

#ifndef _di_fake_make_print_program_verbose_
  f_status_t fake_make_print_program_verbose(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t program, const f_string_statics_t arguments) {

    if (print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print.to);

    f_array_length_t i = 0;

    if (program.used) {
      f_print_dynamic_safely(program, print.to);
    }
    else {
      i = 1;

      f_print_dynamic_safely(arguments.array[0], print.to);
    }

    for (; i < arguments.used; ++i) {
      if (arguments.array[i].used) fll_print_format(" %Q", print.to, arguments.array[i]);
    } // for

    f_print_dynamic_raw(f_string_eol_s, print.to);

    // Flush to stdout before executing command.
    f_file_stream_flush(print.to);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_program_verbose_

#ifdef __cplusplus
} // extern "C"
#endif
