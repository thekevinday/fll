#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_print_verbose_cloning_
  f_status_t fake_print_verbose_cloning(fl_print_t * const print, const f_string_static_t source, const f_string_static_t destination) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_common_wrapped_variables(print, "Cloning file ", source, " to ", destination, f_string_empty_s.string);

    return F_none;
  }
#endif // _di_fake_print_verbose_cloning_

#ifndef _di_fake_print_verbose_copying_
  f_status_t fake_print_verbose_copying(fl_print_t * const print, const f_string_static_t source, const f_string_static_t destination) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_common_wrapped_variables(print, "Copying file ", source, " to ", destination, f_string_empty_s.string);

    return F_none;
  }
#endif // _di_fake_print_verbose_copying_

#ifndef _di_fake_print_verbose_create_directory_
  void fake_print_verbose_create_directory(fl_print_t * const print, const f_string_static_t path) {

    if (!print) return;
    if (print->verbosity < f_console_verbosity_verbose_e) return;

    fake_print_common_simple_variable(print, "Created directory ", path);
  }
#endif // _di_fake_print_verbose_create_directory_

#ifndef _di_fake_print_verbose_create_file_
  f_status_t fake_print_verbose_create_file(fl_print_t * const print, const f_string_static_t path) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_common_simple_variable(print, "Created file ", path);

    return F_none;
  }
#endif // _di_fake_print_verbose_create_file_

#ifndef _di_fake_print_verbose_directory_exists_
  f_status_t fake_print_verbose_directory_exists(fl_print_t * const print, const f_string_static_t path) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_common_wrapped_variable(print, "Directory ", path, " already exists");

    return F_none;
  }
#endif // _di_fake_print_verbose_directory_exists_

#ifndef _di_fake_print_verbose_file_exists_
  f_status_t fake_print_verbose_file_exists(fl_print_t * const print, const f_string_static_t path) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_common_wrapped_variable(print, "File ", path, " already exists");

    return F_none;
  }
#endif // _di_fake_print_verbose_file_exists_

#ifndef _di_fake_print_verbose_file_exists_as_link_
  f_status_t fake_print_verbose_file_exists_as_link(fl_print_t * const print, const f_string_static_t path) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_common_wrapped_variable(print, "File ", path, " already exists (as a symbolic link)");

    return F_none;
  }
#endif // _di_fake_print_verbose_file_exists_as_link_

#ifndef _di_fake_print_verbose_file_exists_not_regular_or_link_
  f_status_t fake_print_verbose_file_exists_not_regular_or_link(fl_print_t * const print, const f_string_static_t path) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_common_wrapped_variable(print, "File ", path, " already exists but is not a regular file (or a symbolic link)");

    return F_none;
  }
#endif // _di_fake_print_verbose_file_exists_not_regular_or_link_

#ifndef _di_fake_print_verbose_file_pre_populated_
  f_status_t fake_print_verbose_file_pre_populated(fl_print_t * const print, const f_string_static_t path) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_common_simple_variable(print, "Pre-populated file ", path);

    return F_none;
  }
#endif // _di_fake_print_verbose_file_pre_populated_

#ifndef _di_fake_print_verbose_moving_
  f_status_t fake_print_verbose_moving(fl_print_t * const print, const f_string_static_t source, const f_string_static_t destination) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_common_wrapped_variables(print, "Moving file ", source, " to ", destination, f_string_empty_s.string);

    return F_none;
  }
#endif // _di_fake_print_verbose_moving_

#ifdef __cplusplus
} // extern "C"
#endif
