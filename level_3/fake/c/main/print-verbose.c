#include "fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_print_verbose_clone_
  f_status_t fake_print_verbose_clone(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t source, const f_string_static_t destination) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_wrapped_variables(setting, print, "Cloned ", source, " to ", destination, 0);

    return F_none;
  }
#endif // _di_fake_print_verbose_clone_

#ifndef _di_fake_print_verbose_copy_
  f_status_t fake_print_verbose_copy(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t source, const f_string_static_t destination) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fll_print_format("Copied '%Q' to '%Q'.%r", output, source, destination, f_string_eol_s);
  }
#endif // _di_fake_print_verbose_copy_

#ifndef _di_fake_print_verbose_create_directory_
  f_status_t fake_print_verbose_create_directory(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_simple_variable(setting, print, "Created directory ", path);

    return F_none;
  }
#endif // _di_fake_print_verbose_create_directory_

#ifndef _di_fake_print_verbose_create_file_
  f_status_t fake_print_verbose_create_file(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_simple_variable(setting, print, "Created file ", path);

    return F_none;
  }
#endif // _di_fake_print_verbose_create_file_

#ifndef _di_fake_print_verbose_directory_exists_
  f_status_t fake_print_verbose_directory_exists(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_wrapped_variable(setting, print, "Directory ", path, " already exists");

    return F_none;
  }
#endif // _di_fake_print_verbose_directory_exists_

#ifndef _di_fake_print_verbose_file_exists_
  f_status_t fake_print_verbose_file_exists(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_wrapped_variable(setting, print, "File ", path, " already exists");
  }
#endif // _di_fake_print_verbose_file_exists_

#ifndef _di_fake_print_verbose_file_exists_as_link_
  f_status_t fake_print_verbose_file_exists_as_link(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_wrapped_variable(setting, print, "File ", path, " already exists (as a symbolic link)");
  }
#endif // _di_fake_print_verbose_file_exists_as_link_

#ifndef _di_fake_print_verbose_file_exists_not_regular_or_link_
  f_status_t fake_print_verbose_file_exists_not_regular_or_link(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_wrapped_variable(setting, print, "File ", path, " already exists but is not a regular file (or a symbolic link)");
  }
#endif // _di_fake_print_verbose_file_exists_not_regular_or_link_

#ifndef _di_fake_print_verbose_file_pre_populated_
  f_status_t fake_print_verbose_file_pre_populated(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_simple_variable(setting, print, "Pre-populated file ", path);
  }
#endif // _di_fake_print_verbose_file_pre_populated_

#ifndef _di_fake_print_verbose_move_
  f_status_t fake_print_verbose_move(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t source, const f_string_static_t destination) {

    if (!setting || print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fll_print_format("Moved '%Q' to '%Q'.%r", output, source, destination, f_string_eol_s);
  }
#endif // _di_fake_print_verbose_move_

#ifdef __cplusplus
} // extern "C"
#endif
