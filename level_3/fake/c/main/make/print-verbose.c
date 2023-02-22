#include "../fake.h"
#include "print-verbose.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_print_verbose_operate_break_
  f_status_t fake_make_print_verbose_operate_break(fake_setting_t * const setting, const fl_print_t print, const f_string_statics_t arguments) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_context_simple_variable(setting, print, "Breaking as", arguments.used ? arguments.array[0] : fake_make_operation_argument_success_s, 0);

    return F_none;
  }
#endif // _di_fake_make_print_verbose_operate_break_

#ifndef _di_fake_make_print_verbose_operate_copy_
  f_status_t fake_make_print_verbose_operate_copy(fake_setting_t * const setting, const fl_print_t print, const bool clone, const f_string_static_t source, const f_string_static_t destination) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%s '%[%Q%]' to '", print.to, clone ? "Cloned" : "Copied", print.set->notable, source, print.set->notable);
    fl_print_format("%[%Q%]'.%r", print.to, print.set->notable, destination, print.set->notable, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_verbose_operate_copy_

#ifndef _di_fake_make_print_verbose_operate_define_
  f_status_t fake_make_print_verbose_operate_define(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t variable) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_context_simple_variable(setting, print, "Defined environment variable", variable, 0);

    return F_none;
  }
#endif // _di_fake_make_print_verbose_operate_define_

#ifndef _di_fake_make_print_verbose_operate_delete_
  f_status_t fake_make_print_verbose_operate_delete(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_context_simple_variable(setting, print, "Removed", path, 0);

    return F_none;
  }
#endif // _di_fake_make_print_verbose_operate_delete_

#ifndef _di_fake_make_print_verbose_operate_exiting_as_
  f_status_t fake_make_print_verbose_operate_exiting_as(fake_setting_t * const setting, const fl_print_t print, const f_string_statics_t arguments) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_context_simple_variable(setting, print, "Exiting as", arguments.used ? arguments.array[0] : fake_make_operation_argument_success_s, 0);

    return F_none;
  }
#endif // _di_fake_make_print_verbose_operate_exiting_as_

#ifndef _di_fake_make_print_verbose_operate_file_not_found_
  f_status_t fake_make_print_verbose_operate_file_not_found(fake_setting_t * const setting, const fl_print_t print, const bool is_directory, const f_string_static_t file) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("The %Q '%[%Q%]' is not found.%]%r", print.to, print.set->notable, is_directory ? f_file_type_name_directory_s : f_file_type_name_file_s, file, print.set->notable, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_verbose_operate_file_not_found_

#ifndef _di_fake_make_print_verbose_operate_program_
  f_status_t fake_make_print_verbose_operate_program(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t program, const f_string_statics_t arguments) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

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
#endif // _di_fake_make_print_verbose_operate_program_

#ifndef _di_fake_make_print_verbose_operate_set_failure_state_
  f_status_t fake_make_print_verbose_operate_set_failure_state(fake_setting_t * const setting, const fl_print_t print, const uint8_t fail) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    f_print_terminated("Set failure state to '", print.to);

    if (fail == fake_make_operation_fail_exit_e) {
      fl_print_format("%[%r%]", print.to, print.set->notable, fake_make_operation_argument_exit_s, print.set->notable);
    }
    else if (fail == fake_make_operation_fail_warn_e) {
      fl_print_format("%[%r%]", print.to, print.set->notable, fake_make_operation_argument_warn_s, print.set->notable);
    }
    else {
      fl_print_format("%[%r%]", print.to, print.set->notable, fake_make_operation_argument_ignore_s, print.set->notable);
    }

    fl_print_format("'.%r", print.to, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_verbose_operate_set_failure_state_

#ifndef _di_fake_make_print_verbose_operate_set_mode_
  f_status_t fake_make_print_verbose_operate_set_mode(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path, const mode_t mode) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fll_print_format("Changed mode of '%[%Q%]' to %[%#@u%].%r", print.to, print.set->notable, path, print.set->notable, print.set->notable, mode, print.set->notable, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_verbose_operate_set_mode_

#ifndef _di_fake_make_print_verbose_operate_set_path_
  f_status_t fake_make_print_verbose_operate_set_path(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path) {

    if (print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_context_simple_variable(setting, print, "Changed project path to", path, 0);

    return F_none;
  }
#endif // _di_fake_make_print_verbose_operate_set_path_

#ifndef _di_fake_make_print_verbose_operate_set_role_
  f_status_t fake_make_print_verbose_operate_set_role(fake_setting_t * const setting, const fl_print_t print, const uint8_t what, f_string_static_t role, f_number_unsigned_t id) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%r %r of '%[%r%]'", print.to, (what & 0x1) ? "Recursively changed" : "Changed", (what & 0x2) ? "owner" : "group", print.set->notable, role, print.set->notable);
    fl_print_format(" to %[%ul%].%r", print.to, print.set->notable, id, print.set->notable, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_verbose_operate_set_role_

#ifndef _di_fake_make_print_verbose_operate_symbolic_link_
  f_status_t fake_make_print_verbose_operate_symbolic_link(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t source, const f_string_static_t destination) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("Created symbolic link from '%[%Q%]", print.to, print.set->notable, source, print.set->notable);
    fl_print_format("' to %[%Q%].%r", print.to, print.set->notable, destination, print.set->notable, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_make_print_verbose_operate_symbolic_link_

#ifndef _di_fake_make_print_verbose_operate_touch_
  f_status_t fake_make_print_verbose_operate_touch(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_context_simple_variable(setting, print, "Touched", path, 0);

    return F_none;
  }
#endif // _di_fake_make_print_verbose_operate_touch_

#ifdef __cplusplus
} // extern "C"
#endif
