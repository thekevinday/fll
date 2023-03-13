#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_print_verbose_clone_
  void fake_print_verbose_clone(const f_string_static_t source, const f_string_static_t destination, void * const void_recurse) {

    if (!void_recurse) return;

    f_directory_recurse_t * const recurse = (f_directory_recurse_t * const) void_recurse;

    if (!recurse->state.custom) {
      recurse->state.status = F_output_not;

      return;
    }

    fake_data_t * const data = (fake_data_t *) recurse->state.custom;

    if (data->main->message.verbosity < f_console_verbosity_verbose_e) {
      recurse->state.status = F_output_not;

      return;
    }

    fake_print_wrapped_variables(data->setting, data->main->message, "Cloned ", source, " to ", destination, 0);
  }
#endif // _di_fake_print_verbose_clone_

#ifndef _di_fake_print_verbose_copy_
  void fake_print_verbose_copy(const f_string_static_t source, const f_string_static_t destination, void * const void_recurse) {

    if (!void_recurse) return;

    f_directory_recurse_t * const recurse = (f_directory_recurse_t * const) void_recurse;

    if (!recurse->state.custom) {
      recurse->state.status = F_output_not;

      return;
    }

    fake_data_t * const data = (fake_data_t *) recurse->state.custom;

    if (data->main->message.verbosity < f_console_verbosity_verbose_e) {
      recurse->state.status = F_output_not;

      return;
    }

    fake_print_wrapped_variables(data->setting, data->main->message, "Copied ", source, " to ", destination, 0);
  }
#endif // _di_fake_print_verbose_copy_

#ifndef _di_fake_print_verbose_create_directory_
  void fake_print_verbose_create_directory(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path) {

    if (!setting) return;
    if (print.verbosity < f_console_verbosity_verbose_e) return;

    fake_print_simple_variable(setting, print, "Created directory ", path);
  }
#endif // _di_fake_print_verbose_create_directory_

#ifndef _di_fake_print_verbose_create_file_
  f_status_t fake_print_verbose_create_file(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_simple_variable(setting, print, "Created file ", path);

    return F_none;
  }
#endif // _di_fake_print_verbose_create_file_

#ifndef _di_fake_print_verbose_directory_exists_
  f_status_t fake_print_verbose_directory_exists(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_wrapped_variable(setting, print, "Directory ", path, " already exists");

    return F_none;
  }
#endif // _di_fake_print_verbose_directory_exists_

#ifndef _di_fake_print_verbose_file_exists_
  f_status_t fake_print_verbose_file_exists(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_wrapped_variable(setting, print, "File ", path, " already exists");
  }
#endif // _di_fake_print_verbose_file_exists_

#ifndef _di_fake_print_verbose_file_exists_as_link_
  f_status_t fake_print_verbose_file_exists_as_link(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_wrapped_variable(setting, print, "File ", path, " already exists (as a symbolic link)");
  }
#endif // _di_fake_print_verbose_file_exists_as_link_

#ifndef _di_fake_print_verbose_file_exists_not_regular_or_link_
  f_status_t fake_print_verbose_file_exists_not_regular_or_link(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_wrapped_variable(setting, print, "File ", path, " already exists but is not a regular file (or a symbolic link)");
  }
#endif // _di_fake_print_verbose_file_exists_not_regular_or_link_

#ifndef _di_fake_print_verbose_file_pre_populated_
  f_status_t fake_print_verbose_file_pre_populated(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_simple_variable(setting, print, "Pre-populated file ", path);
  }
#endif // _di_fake_print_verbose_file_pre_populated_

#ifndef _di_fake_print_verbose_move_
  void fake_print_verbose_move(const f_string_static_t source, const f_string_static_t destination, void * const void_recurse) {

    if (!void_recurse) return;

    f_directory_recurse_t * const recurse = (f_directory_recurse_t * const) void_recurse;

    if (!recurse->state.custom) {
      recurse->state.status = F_output_not;

      return;
    }

    fake_data_t * const data = (fake_data_t *) recurse->state.custom;

    if (data->main->message.verbosity < f_console_verbosity_verbose_e) {
      recurse->state.status = F_output_not;

      return;
    }

    fake_print_wrapped_variables(data->setting, data->main->message, "Moved ", source, " to ", destination, 0);
  }
#endif // _di_fake_print_verbose_move_

#ifdef __cplusplus
} // extern "C"
#endif
